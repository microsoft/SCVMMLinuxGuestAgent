/**
 *  Copyright (c) Microsoft Corporation
 *
 *  All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy
 *  of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *  THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
 *  WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
 *  MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *  See the Apache Version 2.0 License for specific language governing
 *  permissions and limitations under the License.
 *
 **/

/**
   \file        isofetcher.cpp

   \brief       Loads and fetches the ISO mounted on CDROM drive.
   
   \date        05-22-2012 13:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#include <commandexecutor.h>
#include <isofetcher.h>
#include <isofetcherexception.h>
#include <osspecializationreader.h>
#include <statusmessage.h>
#include <statusmessagestrings.h>

#include <unistd.h>
#include <sys/mount.h>
#include <sys/utsname.h>
#include <sys/stat.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cerrno>

#include <scxcorelib/scxdirectoryinfo.h>

using VMM::GuestAgent::Fetcher::ISOFetcher;
using VMM::GuestAgent::Fetcher::ISOFetcherException;
using VMM::GuestAgent::SpecializationReader::OSSpecializationReader;
using VMM::GuestAgent::StatusManager::StatusMessage;
using VMM::GuestAgent::Utilities::CommandExecutor;

using SCX::Util::Xml::XElement;
using SCX::Util::Xml::XElementPtr;
using SCX::Util::Xml::XmlException;

using namespace VMM::GuestAgent::StatusManager;

// Constants
std::string const MOUNT_POINT = "/mnt/vmmcdrom/";
std::string const LINUX_OS_CONFIG_FILE = "linuxosconfiguration.xml";
std::string const INSTALL_UPGRADE = "setsid /mnt/vmmcdrom/install -u -v ";
std::string const GRUB_COMMAND = "grub-editenv - set recordfail=0";
std::string const GRUB_FILE = "/usr/bin/grub-editenv";


void ISOFetcher::ObtainMountPoint()
{
    SCX_LOGINFO(m_logHandle, "Obtaining CD ROM mount point");

    // Support multiple cdrom drives. With certain versions of LIC, even hdd/hdc needs
    // to be looked into.
    const char* possibleDevices[] = { 
        "/dev/cdrom", 
        "/dev/cdrom1", 
        "/dev/cdrom2",
        "/dev/cdrom3",
        "/dev/cdrom4",
        "/dev/cdrom5",
        "/dev/cdrom6",
        "/dev/cdrom7",
        "/dev/cdrom8",
        "/dev/cdrom9", 
        "/dev/hdd",
        "/dev/hdc"
    };

    // check for the existence of any cdrom device.  If none are found,
    // load the driver.
    int size = sizeof(possibleDevices)/sizeof(char*);
    bool deviceFound = false;
    for (int i=0; i<size; i++)
    {
        struct stat statbuf;

        int status = stat(possibleDevices[i], &statbuf);

        if (status != 0)
        {
            continue;
        }
        else
        {
            deviceFound = true;
        }
    }

    int numRetries = 1;

    if (deviceFound == false)
    {
        SCX_LOGINFO(m_logHandle, "CD ROM device not found, injecting driver");

        if (!InvokeInsmod())
        {
            SCX_LOGERROR(m_logHandle, "Could not inject driver");
            return;
        }

        numRetries = 3;
    }

    int retryCount = 0;
    bool foundSpecialization = false;
    while (retryCount < numRetries && (!foundSpecialization))
    {
        for (int i=0; i<size; i++)
        {
            struct stat statbuf;

            int status = stat(possibleDevices[i], &statbuf);

            if (status != 0)
            {
                SCX_LOGERROR(
                    m_logHandle, SCXCoreLib::StrFromMultibyte(
                    std::string("Unable to stat ") +
                    std::string(possibleDevices[i]) + 
                    std::string(" errno: ") + 
                    SCXCoreLib::StrToUTF8(SCXCoreLib::StrFrom(errno))));
                continue;
            }
            else
            {
                SCX_LOGINFO(m_logHandle, SCXCoreLib::StrFromMultibyte(
                            "CD ROM device already present:" + 
                            std::string(possibleDevices[i]) +
                            ", checking for OSSpecialization file"));
                m_mountSource = possibleDevices[i];
                if (MountISO() && ReadDataFromMountPoint())
                {
                    foundSpecialization = true;
                    break;
                }
                else
                {
                    if (m_targetMounted)
                    {
                        UnmountISO();
                    }
                    continue;
                }
            }
            
        }

        // Sleep and retry - insmod sometimes takes time and does not make the device available immediately.
        sleep (30);
        retryCount++;
    }

    if (!foundSpecialization)
    {
        if (m_mountSource.empty())
        {
            SCX_LOGINFO(m_logHandle, "CD ROM device not found");
        }

        throw ISOFetcherException(
            L"Unable to find specialization file:" +
            SCXCoreLib::StrFromMultibyte(LINUX_OS_CONFIG_FILE));
    }
}

bool ISOFetcher::MountISO()
{
    SCX_LOGINFO(m_logHandle, "Mounting CD ROM");

    SCXCoreLib::SCXFilePath mountPointPath(SCXCoreLib::StrFromMultibyte((MOUNT_POINT)));

    // Check if mount point exists
    if (!SCXCoreLib::SCXDirectory::Exists(mountPointPath))
    {
        SCX_LOGINFO(m_logHandle, "Creating " + MOUNT_POINT);
        SCXCoreLib::SCXDirectory::CreateDirectory(mountPointPath);
    }


    int result = mount(m_mountSource.c_str(), MOUNT_POINT.c_str(), "iso9660", MS_RDONLY, 0);
    if (result != 0)
    {
        m_targetMounted = false;

        if (errno == EBUSY)
        {
            SCX_LOGERROR(m_logHandle,
                         SCXCoreLib::StrFromMultibyte(m_mountSource) +
                         L"already mounted");
            // TODO: unmount source and remount
            return true;
        }

        SCX_LOGERROR(m_logHandle, std::string("mount of ") + 
                     m_mountSource + 
                     std::string(" failed error: ") +
                     SCXCoreLib::StrToUTF8(SCXCoreLib::StrFrom(errno)));
        return false;
    }
    else
    {
        m_targetMounted = true;
    }

    return true;
}

void ISOFetcher::UnmountISO()
{
    std::string tagValue;
    bool insModPerformed = StatusMessage::Instance().ReadChildOfRoot(StatusMessageStrings::InsmodStatus, tagValue);

    SCX_LOGINFO(m_logHandle, "Unmounting CD ROM");

    if (umount(MOUNT_POINT.c_str()) != 0)
    {
        SCX_LOGERROR(m_logHandle, "umount /mnt/vmmcdrom failed");
        return;
    }

    if (rmdir(MOUNT_POINT.c_str()) != 0)
    {
        SCX_LOGERROR(m_logHandle, "rmdir /mnt/vmmcdrom failed");
    }

    if (insModPerformed)
    {
        InvokeRmmod();
    }

}

bool ISOFetcher::InvokeInsmod()
{
    SCX_LOGINFO(m_logHandle, "Invoking insmod");

    struct utsname un;

    if (uname(&un) == -1)
    {
        SCX_LOGERROR(m_logHandle, "uname failed");
        return false;
    }

    std::string insModCommand = "insmod /lib/modules/" + std::string(un.release) + "/kernel/drivers/ata/ata_piix.ko";
    CommandExecutor ce;

    if (ce.Execute(SCXCoreLib::StrFromMultibyte(insModCommand), "insmod") != 0)
    {
        SCX_LOGERROR(m_logHandle, "insmod failed");
        return false;
    }

    StatusMessage::Instance().AddChildToRoot(XElementPtr(new XElement(StatusMessageStrings::InsmodStatus, 
        StatusMessageStrings::InsmodCommandComplete)));

    return true;
}

bool ISOFetcher::InvokeRmmod()
{
    SCX_LOGINFO(m_logHandle, "Invoking rmmod");

    struct utsname un;

    if (uname(&un) == -1)
    {
        SCX_LOGERROR(m_logHandle, "uname failed");
        return false;
    }

    std::string rmModCommand = "rmmod /lib/modules/" + std::string(un.release) + "/kernel/drivers/ata/ata_piix.ko";
    CommandExecutor ce;

    if (ce.Execute(SCXCoreLib::StrFromMultibyte(rmModCommand), "rmmod") != 0)
    {
        SCX_LOGERROR(m_logHandle, "rmmod failed");
        return false;
    }

    return true;
}

bool isConfigFile(SCXCoreLib::SCXFilePath const& filepath)
{
    std::string fileName(SCXCoreLib::StrToMultibyte(filepath.GetFilename()));
    return LINUX_OS_CONFIG_FILE == fileName;
}

bool
ISOFetcher::ReadDataFromMountPoint()
{
    SCX_LOGTRACE(m_logHandle, "Entering ReadDataFromMountPoint");

    m_foundOSSpecializationFile = false;
    
    try
    {
        SCXCoreLib::SCXFilePath mountPointPath(SCXCoreLib::StrFromMultibyte(
            MOUNT_POINT));

        // Check if mount point exists
        if (!SCXCoreLib::SCXDirectory::Exists(mountPointPath))
        {
            SCX_LOGERROR(m_logHandle, L"Failed to find mount point " +
                         SCXCoreLib::StrFromMultibyte(MOUNT_POINT));
            throw ISOFetcherException(
                L"Could not find mount point " +
                SCXCoreLib::StrFromMultibyte(MOUNT_POINT));
        }

        // Fetch all the files found in the CDROM mount point directory
        typedef std::vector<SCXCoreLib::SCXFilePath> FilePaths_t;
        FilePaths_t files = SCXCoreLib::SCXDirectory::GetFiles(mountPointPath);
        FilePaths_t::const_iterator fileIter =
            find_if (files.begin(), files.end(), isConfigFile);
        if (files.end() != fileIter)
        {
            std::string fileName(SCXCoreLib::StrToMultibyte(
                fileIter->GetFilename()));

            // Check of specialization file
            ReadConfigFile(SCXCoreLib::StrFromMultibyte(MOUNT_POINT));
        } 
    }
    catch (SCXCoreLib::SCXFilePathNotFoundException& e)
    {
        SCX_LOGERROR(m_logHandle, "Unable to find the file path:" +
                     SCXCoreLib::StrToMultibyte(e.What()));
        throw ISOFetcherException(L"Unable to find the file path:" + e.What());
    }

    // Check if we found what we were looking for
    if (!m_foundOSSpecializationFile)
    {
        SCX_LOGERROR(m_logHandle, L"Unable to find specialization file:" +
                     SCXCoreLib::StrFromMultibyte(LINUX_OS_CONFIG_FILE));
    }

    return m_foundOSSpecializationFile;
}

int
ISOFetcher::ReadConfigFile(
    std::wstring const& path)
{
    int result = EXIT_SUCCESS;

    m_osConfigurationXMLPath = path;
    std::wstring::size_type len = m_osConfigurationXMLPath.length();
    if (0 < len &&
        L'/' != m_osConfigurationXMLPath[len -1])
    {
        m_osConfigurationXMLPath.push_back(L'/');
    }

    std::wstring filename =
        path + SCXCoreLib::StrFromMultibyte(LINUX_OS_CONFIG_FILE);

    SCX_LOGINFO(
        m_logHandle,
        L"Attempting to open Specialization file:\"" + filename + L"\"");
    // Read the file contents
    std::ifstream fileStream(SCXCoreLib::StrToMultibyte(filename).c_str());

    if (fileStream.is_open() &&
        fileStream.good())
    {
        // Find the length of the file
        fileStream.seekg(0, std::ios::end);
        std::streampos length = fileStream.tellg();
        fileStream.seekg(0, std::ios::beg);

        std::vector<char> buffer(length);
        std::vector<unsigned char> data(length);

        // Create a buffer of length to read the file into
        SCX_LOGINFO(m_logHandle,
                    "File Len:" + SCXCoreLib::StrToMultibyte(
                        SCXCoreLib::StrFrom(length)));

        fileStream.read(&(buffer[0]), length);
        data.assign(&(buffer[0]), &(buffer[0]) + length);

        // XML String
        SCX::Util::Utf8String temp(data);
        m_osConfigurationXMLString = temp;
        SCX_LOGINFO(
            m_logHandle,
            "Specialization file contents len:" + SCXCoreLib::StrToMultibyte(
                SCXCoreLib::StrFrom(m_osConfigurationXMLString.Size())));
        m_foundOSSpecializationFile = true;
    }
    else
    {
        SCX_LOGERROR(m_logHandle, "Could not read specialization file");
        result = EXIT_FAILURE;
    }
    fileStream.close();

    return result;
}

void ISOFetcher::InstallOrUpgradeAgent()
{
    if (FoundSpecializationFile())
    {
        std::string newAgentVersion = GetNewAgentVersion();
        std::string installUpgradeCommand = INSTALL_UPGRADE + newAgentVersion;


        if (newAgentVersion != "")
        {

            CommandExecutor ce;
            int ret = ce.Execute(SCXCoreLib::StrFromMultibyte(installUpgradeCommand), "Install/Upgrade");
            if (ret == 0)
            {
                SCX_LOGINFO(m_logHandle, ("No upgrade was required - its the same version"));
            }
            else if (ret == -1)
            {
                // TODO - WI 396154 - Handle failures from upgrade post beta
                SCX_LOGERROR(m_logHandle, ("Unable to upgrade"));
            }
            else if (ret == 1)
            {
                SCX_LOGINFO(m_logHandle, ("Upgrade was successfull"));
            }
        }
    }
    else
    {
        SCX_LOGERROR(m_logHandle, ("Failed to find specialization file ISOFetcher::InstallOrUpgradeAgent terminating"));
    }
}


std::string ISOFetcher::GetNewAgentVersion()
{
    SCX_LOGINFO(m_logHandle, ("Entering GetNewAgentVersion"));

    if (FoundSpecializationFile() == false)
    {
        SCX_LOGERROR(m_logHandle, ("OS Specialization file not found"));
        return "";
    }

    // Get OSSpecialization
    OSSpecializationReader::LinuxOSSpecialization spec;
    OSSpecializationReader::Instance().GetLinuxOSSpecialization(spec);

    SCX::Util::Utf8String agentVersion;
    if (spec.GetAgentVersion(agentVersion))
    {
        return agentVersion.Str();
    }
    else
    {
        return "";
    }
}

void ISOFetcher::TerminateSetup()
{
    SCX_LOGINFO(m_logHandle, ("Entering TerminateSetup"));

    std::string tagValue;

    bool specializationComplete = StatusMessage::Instance().ReadChildOfRoot(
        StatusMessageStrings::SpecializationComplete, tagValue);

    if (specializationComplete)
    {
        CommandExecutor ce;
        
        if (0 != ce.Execute(m_osConfigurationXMLPath +
                                SCXCoreLib::StrFromMultibyte("install -r "),
                            "install"))
        {
            SCX_LOGERROR(m_logHandle, ("daemon removal failed"));
        }
        else
        {
            SCX_LOGINFO(m_logHandle, ("daemon removal complete"));
        }
    }

    // working here
    std::wstring path = SCXCoreLib::StrFromMultibyte(MOUNT_POINT);
    if (0 == m_osConfigurationXMLPath.compare(0, path.length(), path))
    {
        UnmountISO();
    }


    if (specializationComplete)
    {
        // bug workaround for ubuntu
        ModifyGrub();

        char const* args[] = { "shutdown", "-h", "now", 0 };

        execv ("/sbin/shutdown", const_cast<char* const*>(args));
        execv ("/etc/shutdown", const_cast<char* const*>(args));
        execv ("/bin/shutdown", const_cast<char* const*>(args));

        SCX_LOGERROR(m_logHandle, ("system shutdown failed"));
    }
    else
    {
        SCX_LOGERROR(m_logHandle, ("Terminating abnormally due to a failed specialization step."));
        exit(-1);
    }
}

void ISOFetcher::ModifyGrub()
{
    // On some of the distros, mainly Ubuntu, grub menu shows up after reboot. So, forcing
    // record fail to 0 will fix this issue. This is a documented bug.
    struct stat statbuf;

    int status = stat(GRUB_FILE.c_str(), &statbuf);
    if (status == 0)
    {
        CommandExecutor ce;
        int ret = ce.Execute(SCXCoreLib::StrFromMultibyte(GRUB_COMMAND), "grub-editenv");
        if (ret != 0)
        {
            SCX_LOGERROR(
                m_logHandle,
                "failed to set recordfail=0 in /boot/grub/grubenv errno=" +
                SCXCoreLib::StrToMultibyte(SCXCoreLib::StrFrom(ret)));
        }
        else
        {
            SCX_LOGINFO(m_logHandle, ("set recordfail=0 in /boot/grub/grubenv"));
        }
    }
    else
    {
        //TODO: this meant to assist with internal debugging, may want to remove prior to field release
        SCX_LOGTRACE(m_logHandle, SCXCoreLib::StrFromMultibyte(GRUB_FILE) +
                     L" not found on this system");
    }
}
