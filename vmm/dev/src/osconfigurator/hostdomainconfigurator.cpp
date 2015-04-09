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
   \file        hostdomainconfigurator.cpp

   \brief       This class provides an abstraction layer to execute host/domain configuration
                scripts based on 
                
   \date        06-24-2012 20:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#include <hostdomainconfigurator.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include <argumentmanager.h>
#include <commandexecutor.h>
#include <isofetcher.h>
#include <statusmessage.h>
#include <statusmessagestrings.h>

#include <util/Unicode.h>
#include <scxcorelib/stringaid.h>

using VMM::GuestAgent::OSConfigurator::HostDomainConfigurator;
using VMM::GuestAgent::Fetcher::ISOFetcher;
using VMM::GuestAgent::StatusManager::StatusMessage;
using VMM::GuestAgent::Utilities::ArgumentManager;
using SCX::Util::Xml::XElement;
using SCX::Util::Xml::XElementPtr;
using SCX::Util::Utf8String;

using namespace VMM::GuestAgent::StatusManager;

void HostDomainConfigurator::Execute(Utf8String& hostName, 
                                     Utf8String& domainName)
{
    
    SCX_LOGINFO(m_logHandle, ("Executing host-domain configuration"));

    if (setenv("HISTIGNORE", "*", 1) != 0)
    {
        SCX_LOGERROR(m_logHandle, ("failed to set HISTIGNORE"));
    }

    std::wstring command;

    if (hostName == "*")
    {
        command = SCXCoreLib::StrFromMultibyte(ArgumentManager::Instance().GetVMMHome() + 
                                               ("/bin/cfghostdomain hostname=") +
                                               RandomHostName());
    }
    else
    {

        SCX_LOGINFO(m_logHandle, "It was not a * hostname");
        std::wstring wHostName;
        hostName.ToWideString(wHostName);
        command = SCXCoreLib::StrFromMultibyte(ArgumentManager::Instance().GetVMMHome() +
                                               ("/bin/cfghostdomain hostname=")) + 
        wHostName;

    }
    // Invoke script
    if (domainName.Size())
    {

        std::wstring wDomainName;
        domainName.ToWideString(wDomainName);
        command += SCXCoreLib::StrFromMultibyte(" dnsdomainname=") + 
            wDomainName;
    }

    // Execute the command - scx logger crashes on printing UTF-8
    //SCX_LOGINFO(m_logHandle, SCXSTRING("Shell command:") + command);
    
    // Use execute script
    VMM::GuestAgent::Utilities::CommandExecutor commandExec;
    int ret = commandExec.Execute(command, 
                                  m_componentName);

    if (ret < 0)
    {
        SCX_LOGINFO(m_logHandle, ("Failed to set host/domain. Fatal failure."));
        StatusMessage::Instance().AddChildToRoot(XElementPtr(new XElement(StatusMessageStrings::SpecializationStatus, 
                                                                          StatusMessageStrings::SpecializationFailed)));
        ISOFetcher::Instance().TerminateSetup();
    }
     

}

std::string HostDomainConfigurator::RandomHostName()
{
    srand(time(NULL));
    char rndCh = 'a';
    std::string hostname(8, ' ');

    do
    {
        rndCh = rand()/(RAND_MAX/('z' - 'a')) + 'a';
        hostname[0] = rndCh;
    }
    while (!LegitimateCharacter(rndCh));

    for (int i=1; i<8; i++)
    {
        do
        {
            int rnd = rand()/(RAND_MAX/('z' - 'a' + 10));
            rndCh = rnd < 26 ? rnd + 'a' : (rnd - 26) + '0';
            hostname[i] = rndCh;
        }
        while (!LegitimateCharacter(rndCh));
    }

    return hostname;
}

bool HostDomainConfigurator::LegitimateCharacter(char val)
{
    switch (val)
    {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'y':
        case '1':
        case '0':
        case '3':
            return false;
        default:
            return true;
    }        
}
