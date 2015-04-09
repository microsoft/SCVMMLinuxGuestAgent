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

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxlog.h>
#include <scxcorelib/scxlogpolicy.h>
#include <scxcorelib/stringaid.h>

#include <logpolicy.h>
#include <util/LogHandleCache.h>

#include <isofetcher.h>
#include <isofetcherexception.h>
#include <osspecializationreader.h>
#include <osspecializationparserexception.h>
#include <executevisitor.h>
#include <isofetcher.h>
#include <argumentmanager.h>

#include <fcntl.h>

using SCX::Util::LogHandleCache;
using SCX::Util::Utf8String;
using VMM::GuestAgent::Fetcher::ISOFetcher;
using VMM::GuestAgent::Fetcher::ISOFetcherException;
using VMM::GuestAgent::SpecializationReader::OSSpecializationReader;
using VMM::GuestAgent::SpecializationReader::OSSpecializationParserException;
using VMM::GuestAgent::Fetcher::ISOFetcher;
using VMM::GuestAgent::Utilities::ArgumentManager;

//
// Support making us a daemon
//

int Process_Daemonize()
{
    int pid;

    /* Fork for the first time */
    pid = fork();
    if (pid == -1)
        return -1;

    /* If parent, then exit; let child live on. */
    if (pid > 0)
        exit(0);

    /* Become the session leader (return if this fails) */
    if (setsid() == -1)
        return -1;

    /* Fork a second time */
    pid = fork();
    if (pid == -1)
        return -1;

    /* If parent (first child), then exit; let second child live on */
    if (pid > 0)
        exit(0);

    /* Close all file descriptors inherited by this process */
    close(0);
    close(1);
    close(2);

    /* Tie stdin to /dev/null */
    open("/dev/null", O_RDONLY);

    /* Tie stdout to /dev/null */
    open("/dev/null", O_RDWR);

    /* Tie stderr to /dev/null */
    open("/dev/null", O_RDWR);

    return 0;
}

void
InitializeSystem(
    int const& argc,
    char const* const* argv)
{

    // Set the locale for the program
    std::setlocale(LC_ALL, "en_US.UTF8");

    // Create handle
    SCXCoreLib::SCXLogHandle logHandle =
        LogHandleCache::Instance().GetLogHandle("scx.vmmguestagent.main.main");

    SCX_LOGINFO(logHandle, "Initializing VMM Guest Agent");

    // Get Specialization file and execute actions
    try
    {
        ArgumentManager& argMgr = ArgumentManager::Instance();
        ISOFetcher& fetcher = ISOFetcher::Instance();
        // parse commandline
        argMgr.LoadArgs(argc, argv, logHandle);

        if (Process_Daemonize() == -1)
        {
            SCX_LOGERROR(
                logHandle,
                "Error converting the agent process to a daemon.  errno=" +
                    SCXCoreLib::StrToUTF8(SCXCoreLib::StrFrom(errno)));
            exit (1);
        }

        if (!argMgr.GetConfigFilename().empty())
        {
            fetcher.ReadConfigFile(SCXCoreLib::StrFromMultibyte(
                argMgr.GetConfigFilename()));
        }
        else
        {
            // obtain a cdrom mountpoint
            fetcher.ObtainMountPoint();
        }

        if (fetcher.FoundSpecializationFile())
        {
            // Fetch specialization XML String
            const Utf8String osSpecializationString =
                fetcher.GetOSConfigurationXMLString();
            OSSpecializationReader::Instance().LoadXML(osSpecializationString);

            // upgrade if new agent is present
            if (argMgr.GetConfigFilename().empty())
            {
                fetcher.InstallOrUpgradeAgent();
            }

            // Get OSSpecialization
            OSSpecializationReader::LinuxOSSpecialization spec;
            OSSpecializationReader::Instance().GetLinuxOSSpecialization(spec);

            // Get configuration values
            OSSpecializationReader::OSConfiguration osconf;
            spec.GetOSConfiguration(osconf);

            // Create and execute all configurators
            VMM::GuestAgent::OSConfigurator::CreateOSConfigurators(osconf);

            SCX_LOGINFO(logHandle, "Sucessfully initialized VMM Guest Agent!");
        
        }
    }
    catch (ISOFetcherException& e)
    {
        SCX_LOGERROR(
            logHandle,
            L"Error Initializing the VMM Guest Agent! Exception:" + e.What());
    }
    catch (OSSpecializationParserException& e)
    {
        SCX_LOGERROR(
            logHandle,
            "Error Initializing the VMM Guest Agent! Exception:" + e.What());
    }
}

int
main(
    int const argc,
    char const* const* argv)
{
    // Init
    InitializeSystem(argc, argv);
    
    return 0;
}
