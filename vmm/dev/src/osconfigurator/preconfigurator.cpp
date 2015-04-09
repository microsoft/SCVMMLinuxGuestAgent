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
   \file        preconfigurator.cpp

   \brief       Class that invokes preconfiguration scripts
                
   \date        07-03-2012 20:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#include <preconfigurator.h>

#include <stdlib.h>
#include <unistd.h>

#include <isofetcher.h>
#include <argumentmanager.h>
#include <commandexecutor.h>
#include <statusmessage.h>
#include <statusmessagestrings.h>

#include <scxcorelib/stringaid.h>

using VMM::GuestAgent::OSConfigurator::PreConfigurator;
using VMM::GuestAgent::Fetcher::ISOFetcher;
using VMM::GuestAgent::StatusManager::StatusMessage;
using VMM::GuestAgent::Utilities::ArgumentManager;
using SCX::Util::Xml::XElement;
using SCX::Util::Xml::XElementPtr;

using namespace VMM::GuestAgent::StatusManager;

// Const strings
const std::string PreConfiguratorStatus = "PreConfiguratorStatus";
const std::string PreConfiguratorSuccessfull = "Successful";
const std::string PreConfiguratorFailed = "Failed";

void PreConfigurator::Execute()
{
    SCX_LOGINFO(m_logHandle, "Executing pre-configuration script");

    // indicate that specialization has started
    StatusMessage::Instance().AddChildToRoot(XElementPtr(new XElement(StatusMessageStrings::SpecializationStarted, 
                                                                      StatusMessageStrings::SpecializationStarted)));

    // Get the status so far
    std::string preconfigValue;
    bool found = StatusMessage::Instance().ReadChildOfRoot(PreConfiguratorStatus, 
                                                           preconfigValue);
    
    if (!found)
    {
        SCX_LOGINFO(m_logHandle, "Pre-Configuration was never run before");

        if (setenv("HISTIGNORE", "*", 1) != 0)
        {
            SCX_LOGERROR(m_logHandle, "failed to set HISTIGNORE");
        }

        std::string command = ArgumentManager::Instance().GetVMMHome() + "/bin/cfgpre";
        SCX_LOGINFO(m_logHandle, "Shell Command:" + command);
    
        // Use execute script
        VMM::GuestAgent::Utilities::CommandExecutor commandExec;
        int ret = commandExec.Execute(SCXCoreLib::StrFromMultibyte(command), 
                                      m_componentName);

        SCX_LOGINFO(m_logHandle, "Ret:" + SCXCoreLib::StrToMultibyte(SCXCoreLib::StrFrom(ret)));

        if (!ret)
        {
            SCX_LOGINFO(m_logHandle, "Preconfig completed successfully. Will reboot now");
            
            // Create the control file
            StatusMessage::Instance().AddChildToRoot(XElementPtr(new XElement(PreConfiguratorStatus, 
                                                                              PreConfiguratorSuccessfull)));
            // Restart
            ISOFetcher::Instance().ModifyGrub();

            char const* args[] = { "shutdown", "-r", "now", 0 };

            execv ("/sbin/shutdown", const_cast<char * const*>(args));
            execv ("/etc/shutdown", const_cast<char * const*>(args));
            execv ("/bin/shutdown", const_cast<char * const*>(args));

            SCX_LOGERROR(m_logHandle, "Unable to reboot after preconfig. Aborting");
        }
        else if (ret < 0)
        {
            SCX_LOGINFO(m_logHandle, "Preconfig did not finish. No reboot");
            StatusMessage::Instance().AddChildToRoot(XElementPtr(new XElement(PreConfiguratorStatus, 
                                                                              PreConfiguratorFailed)));
            StatusMessage::Instance().AddChildToRoot(XElementPtr(new XElement( StatusMessageStrings::SpecializationFailed, "")));

            ISOFetcher::Instance().TerminateSetup();
        }
        
    }
    else if (preconfigValue == PreConfiguratorSuccessfull)
    {
        SCX_LOGINFO(m_logHandle, "Preconfigurator was run previously sucessfully. Continuing with other configurations");
    }
    else if (preconfigValue == PreConfiguratorFailed)
    {
        // TODO - Check with KBash - retry?
        SCX_LOGINFO(m_logHandle, "Failed to run preconfigurator previously.");
    }
}
            
    
