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
   \file        usersconfigurator.cpp

   \brief       This class provides an abstraction layer to execute user config scripts
                
   \date        07-03-2012 20:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#include <usersconfigurator.h>

#include <argumentmanager.h>
#include <Base64Helper.h>
#include <commandexecutor.h>
#include <isofetcher.h>
#include <statusmessage.h>
#include <statusmessagestrings.h>

#include <scxcorelib/stringaid.h>

using VMM::GuestAgent::Fetcher::ISOFetcher;
using VMM::GuestAgent::OSConfigurator::UsersConfigurator;
using VMM::GuestAgent::StatusManager::StatusMessage;
using VMM::GuestAgent::Utilities::ArgumentManager;
using util::Base64Helper;
using SCX::Util::Xml::XElement;
using SCX::Util::Xml::XElementPtr;
using SCX::Util::Utf8String;

using namespace VMM::GuestAgent::StatusManager;

void UsersConfigurator::Execute(const VMM::GuestAgent::SpecializationReader::OSSpecializationReader::User& user)
{
    
    SCX_LOGINFO(m_logHandle, "Executing users-configuration script");
    
    Utf8String password;
    Utf8String sshKey;
                    
    bool gotPassword = user.GetPassword(password);
    bool gotSSHKey   = user.GetSSHKey(sshKey);
    
    std::string command;
    
    std::vector<unsigned char> outputBuffer;
    bool ret = Base64Helper::Decode(password.Str(), outputBuffer);
    if (ret == false)
    {
        SCX_LOGERROR(m_logHandle, ("Unable to decode password, terminating specialization"));
        StatusMessage::Instance().AddChildToRoot(
            XElementPtr(new XElement(StatusMessageStrings::SpecializationStatus, 
                                        StatusMessageStrings::SpecializationFailed)));

        ISOFetcher::Instance().TerminateSetup();
    }

    std::string decodedPassword(outputBuffer.begin(), outputBuffer.end());

    if (gotPassword && gotSSHKey)
    {
        command = ArgumentManager::Instance().GetVMMHome() + "/bin/cfgroot pw=\"" + decodedPassword + "\" sshkey=\"" + sshKey.Str() + "\""; 
    }  
    else if (gotPassword && (!gotSSHKey))
    {
        command = ArgumentManager::Instance().GetVMMHome() + "/bin/cfgroot pw=\"" + decodedPassword + "\""; 
    }
    
    // Execute command
    if (!command.empty())
    {
        if (setenv("HISTIGNORE", "*", 1) != 0)
        {
            SCX_LOGERROR(m_logHandle, "failed to set HISTIGNORE");
        }

        // Use execute script
        VMM::GuestAgent::Utilities::CommandExecutor commandExec;
        int ret = commandExec.Execute(SCXCoreLib::StrFromMultibyte(command), 
                                      m_componentName);
        if (ret < 0)
        {
            SCX_LOGERROR(m_logHandle, "User configuration failed. Fatal failure");
            
            StatusMessage::Instance().AddChildToRoot(
                XElementPtr(new XElement(StatusMessageStrings::SpecializationStatus, 
                                         StatusMessageStrings::SpecializationFailed)));

            ISOFetcher::Instance().TerminateSetup();
        }
        
    }
    else
    {
        SCX_LOGINFO(m_logHandle, "No root user to customize");
    }
    
}
