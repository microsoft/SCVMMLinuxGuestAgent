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
   \file        isofetcher.h

   \brief       Provides an abstraction layer that reads the contents of 
                CDROM mount point, which contains content from CDROM device.
   
   \date        05-22-2012 13:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/

#ifndef ISOFETCHER_H
#define ISOFETCHER_H

#include <string>
#include <iostream>

#include <util/LogHandleCache.h>

#include <scxcorelib/scxsingleton.h>
#include <util/Unicode.h>

namespace VMM
{

    namespace GuestAgent
    {

        namespace Fetcher
        {

            class ISOFetcher : public SCXCoreLib::SCXSingleton<ISOFetcher>
            {
                
                /** Making the class a friend to enable destruction */
                friend class SCXCoreLib::SCXSingleton<ISOFetcher>;

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   Return the Linux OS Configuration file found on the mount point

                   \return     XMLString Representation of the specialization file

                   \throws     ISOFetcherException if unable to fetch file

                */
                inline SCX::Util::Utf8String GetOSConfigurationXMLString()
                {
                    return m_osConfigurationXMLString;
                }

                /*----------------------------------------------------------------------------*/
                /**
                   Return result of search for specialization file.

                   \return     was the specialization file found?

                   \throws     ISOFetcherException if unable to fetch file

                */
                inline bool FoundSpecializationFile()
                {
                    return m_foundOSSpecializationFile;
                }

                /*----------------------------------------------------------------------------*/
                /**
                   Return path to the guest agent upgrade bits.

                   \return     SCXFilePath Absolute path of the upgrade bits

                   \throws     ISOFetcherException if unable to fetch file

                */
                inline SCXCoreLib::SCXFilePath GetGuestAgentUpgradeBitsPath()
                {
                    return m_guestAgentUpgradeBitsPath;
                }
                
                /*----------------------------------------------------------------------------*/
                /**
                   
                   Look for cd rom device and mount it

                */
                void ObtainMountPoint();

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Unmount the cd rom

                */
                void UnmountISO();

                /*----------------------------------------------------------------------------*/
                /**
                   Helper function to read the contents of the cdrom mount point, which will 
                   have contents mounted from /dev/cdrom during installation

                   \throws     ISOFetcherException if operation failed

                */
                bool ReadDataFromMountPoint();

                int ReadConfigFile(std::wstring const& path);

                /*----------------------------------------------------------------------------*/
                /**
                   
                   mount cdrom, retrieve agent version, and run install script

                */
                void InstallOrUpgradeAgent();

                /*----------------------------------------------------------------------------*/
                /**
                   
                   clean up from completed or aborted setup

                */
                void TerminateSetup();

                /*----------------------------------------------------------------------------*/
                /**
                   
                   alter the grubenv file (if it exists) to disable the grub menu on restart

                */
                void ModifyGrub();

            private:
                
                /** Lock for log handle cache */
                SCXCoreLib::SCXLogHandle  m_logHandle;

                /** OS Configuration XML String */
                SCX::Util::Utf8String   m_osConfigurationXMLString;

                /** OS Configuration XML file Path */
                std::wstring                 m_osConfigurationXMLPath;

                /** Guest Agent Upgrade bits Path */
                SCXCoreLib::SCXFilePath   m_guestAgentUpgradeBitsPath;

                /** did we mount the cdrom? */
                bool                      m_targetMounted;

                /** did we find the specialization file? */
                bool                      m_foundOSSpecializationFile;

                /** CD Rom device (usually /dev/cdrom) */
                std::string               m_mountSource;

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for ISOFetcher

                */
                ISOFetcher() 
                    : m_logHandle(
                          SCX::Util::LogHandleCache::Instance().GetLogHandle(
                          "scx.vmmguestagent.src.fetcher.isofetcher"))
                {
                }

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Mount the cd rom

                */
                bool MountISO();

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Invoke the insmod command

                */
                bool InvokeInsmod();

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Invoke the rmmod command

                */
                bool InvokeRmmod();
                
                /*----------------------------------------------------------------------------*/
                /**
                   
                   Retrieve the agent version on the cd

                */
                std::string GetNewAgentVersion();

			public:
				virtual /*dtor*/ ~ISOFetcher () {}
            }; // End of ISOFetcher class

        } // End of Fetcher namespace

    } // End of GuestAgent

} // End of VMM

#endif /* ISOFETCHER_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
