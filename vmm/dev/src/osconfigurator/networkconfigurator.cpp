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
   \file        runoncecommandconfigurator.cpp

   \brief       Implementation for run-once command execution
                
                
   \date        06-24-2012 20:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#include <networkconfigurator.h>

#include <isofetcher.h>
#include <argumentmanager.h>
#include <commandexecutor.h>
#include <statusmessage.h>
#include <statusmessagestrings.h>

using VMM::GuestAgent::Fetcher::ISOFetcher;
using VMM::GuestAgent::OSConfigurator::NetworkConfigurator;
using VMM::GuestAgent::StatusManager::StatusMessage;
using VMM::GuestAgent::Utilities::ArgumentManager;
using SCX::Util::Xml::XElement;
using SCX::Util::Xml::XElementPtr;
using SCX::Util::Utf8String;

using namespace VMM::GuestAgent::SpecializationReader;
using namespace VMM::GuestAgent::StatusManager;

void NetworkConfigurator::Execute(const std::vector<OSSpecializationReader::VNetAdapter>& vNetAdapters)
{
    
    SCX_LOGINFO(m_logHandle, ("Executing network configuration"));

    if (vNetAdapters.size())
    {
        std::vector<OSSpecializationReader::VNetAdapter>::const_iterator iter;
        for (iter = vNetAdapters.begin(); iter != vNetAdapters.end(); ++iter)
        {
            ConfigureNetworkAdapter(*iter);
        }
    }
    else
    {
        SCX_LOGINFO(m_logHandle, ("Unable to find any network configurations in configuration file."));
    }

    // Configure unspecified network adapters as DHCP - parity with windows agent
    ConfigureUnspecifiedNetAdaptersForDHCP();

}

void NetworkConfigurator::ConfigureUnspecifiedNetAdaptersForDHCP()
{

    SCX_LOGINFO(m_logHandle, ("Configuring unspecified network adapters as DHCP"));
    if (setenv("HISTIGNORE", "*", 1) != 0)
    {
        SCX_LOGERROR(m_logHandle, ("failed to set HISTIGNORE"));
    }

    std::string command = ArgumentManager::Instance().GetVMMHome() + "/bin/cfgdynnetadapter ";
    SCX_LOGINFO(m_logHandle, "Shell Command:" + command);

    // Execute
    VMM::GuestAgent::Utilities::CommandExecutor commandExec;
    int ret = commandExec.Execute(SCXCoreLib::StrFromMultibyte(command),
                                  m_componentName);
    if (ret < 0)
    {
        SCX_LOGERROR(m_logHandle, ("Network configuration failed. Fatal failure"));
        
        StatusMessage::Instance().AddChildToRoot(XElementPtr(new XElement(StatusMessageStrings::SpecializationStatus, 
                                                                          StatusMessageStrings::SpecializationFailed)));
        
        ISOFetcher::Instance().TerminateSetup();
    }
    
}

void NetworkConfigurator::ConfigureNetworkAdapter(const OSSpecializationReader::VNetAdapter& netAdapter)
{
    
    std::string command;
    std::string commandParams;

    // Add MACAddress if present
    Utf8String macAddress;
    if (netAdapter.GetMACAddress(macAddress))
    {
        commandParams.append((" macaddress=") + macAddress.Str());
    }
    else
    {
        SCX_LOGWARNING(m_logHandle, ("No MAC Address to configure"));
    }

    // Get IPV4 Properties
    OSSpecializationReader::NetworkProperties ipv4;
    if (netAdapter.GetIPV4(ipv4))
    {
        if (ipv4.IsStatic())
        {
            Utf8String staticIPAddress;
            if (ipv4.GetStaticIP(staticIPAddress))
            {
                commandParams.append(" ipv4addresstype=static");
                commandParams.append(" ipv4address=" +  staticIPAddress.Str());
            }
            else
            {
                SCX_LOGERROR(m_logHandle, ("No static IP address to configure for IPV4 network adapter"));
            }
        }
        else
        {
            commandParams.append((" ipv4addresstype=dhcp"));
        }
    }
    else
    {
        SCX_LOGWARNING(m_logHandle, ("No IPV4 properties to handle"));
    }

    // Get IPV6 properties
    OSSpecializationReader::NetworkProperties ipv6;
    if (netAdapter.GetIPV6(ipv6))
    {

        if (ipv6.IsStatic())
        {
            Utf8String staticIPAddress;
            if (ipv6.GetStaticIP(staticIPAddress))
            {
                commandParams.append(" ipv6addresstype=static");
                commandParams.append(" ipv6address=" +  staticIPAddress.Str());
            }
            else
            {
                SCX_LOGERROR(m_logHandle, ("No static IP address to configure for IPV6 network adapter"));
            }
        }
        else
        {
            commandParams.append((" ipv6addresstype=dhcp"));
        }

    }
    else
    {
        SCX_LOGWARNING(m_logHandle, ("No IPV6 properties to configure"));
    }

    // Get Gateways
    std::vector<OSSpecializationReader::Gateway> gateways = netAdapter.Gateways;
    if (gateways.size())
    {
      
        // TODO - Handle cost associated with gateways later. Need more work 
        // from the script.
        std::vector<OSSpecializationReader::Gateway>::const_iterator iter;
        commandParams.append(" gateways=");
        for (iter = gateways.begin(); iter != gateways.end(); iter++)
        {
            // Comma seprated gateways
            Utf8String gatewayAddress;
            if (iter->GetAddress(gatewayAddress))
            {
                commandParams.append(gatewayAddress.Str());
                commandParams.append(",");
            }
        }
    }
    else
    {
        SCX_LOGWARNING(m_logHandle, ("No gateways to configure"));
    }

    // Get Nameservers
    std::vector<Utf8String> nameServers = netAdapter.NameServers;
    if (nameServers.size())
    {

        std::vector<Utf8String>::const_iterator iter;
        commandParams.append(" nameservers=");
        for (iter = nameServers.begin(); iter != nameServers.end(); iter++)
        {
            // Comma seprated nameservers
            commandParams.append(iter->Str());
            commandParams.append(",");
        }
        
    }
    else
    {
        SCX_LOGWARNING(m_logHandle, ("No nameservers to configure"));
    }

    // Get DNS Search Suffixes
    std::vector<Utf8String> dnsSuffixes = netAdapter.DNSSearchSuffixes;
    if (dnsSuffixes.size())
    {
        std::vector<Utf8String>::const_iterator iter;
        commandParams.append(" dnssearchsuffix=");
        for (iter = dnsSuffixes.begin(); iter != dnsSuffixes.end(); iter++)
        {
            // Comma seprated Search sufffixes
            commandParams.append(iter->Str());
            commandParams.append(",");
        }

    }
    else
    {
        SCX_LOGWARNING(m_logHandle, ("No DNS Search suffixes to configure"));
    }

    // Invoke script
    if (!commandParams.empty())
    {
        SCX_LOGINFO(m_logHandle, ("Executing network configuration script"));
        if (setenv("HISTIGNORE", "*", 1) != 0)
        {
            SCX_LOGERROR(m_logHandle, "failed to set HISTIGNORE");
        }

        std::string command = ArgumentManager::Instance().GetVMMHome() + "/bin/cfgnetadapter " + commandParams;
        SCX_LOGINFO(m_logHandle, ("Shell Command:") + (command));

        // Execute
        VMM::GuestAgent::Utilities::CommandExecutor commandExec;
        int ret = commandExec.Execute(SCXCoreLib::StrFromMultibyte(command),
                                      m_componentName);
        if (ret < 0)
        {
            SCX_LOGERROR(m_logHandle, "Network configuration failed. Fatal failure");
            
            StatusMessage::Instance().AddChildToRoot(XElementPtr(new XElement(StatusMessageStrings::SpecializationStatus, 
                                                                              StatusMessageStrings::SpecializationFailed)));

            ISOFetcher::Instance().TerminateSetup();
        }
    }

}
