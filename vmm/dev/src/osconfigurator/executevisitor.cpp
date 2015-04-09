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
   \file        executevisitor.cpp

   \brief       This class calls the execute method of all osconfigurator classes
                
   
   \date        06-25-2012 05:06:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#include <executevisitor.h>

using VMM::GuestAgent::OSConfigurator::PreConfigurator;
using VMM::GuestAgent::OSConfigurator::HostDomainConfigurator;
using VMM::GuestAgent::OSConfigurator::TimeZoneConfigurator;
using VMM::GuestAgent::OSConfigurator::NetworkConfigurator;
using VMM::GuestAgent::OSConfigurator::UsersConfigurator;
using VMM::GuestAgent::OSConfigurator::RunOnceCommandConfigurator;
using VMM::GuestAgent::OSConfigurator::PostConfigurator;
using VMM::GuestAgent::OSConfigurator::ExecuteVisitor;
using SCX::Util::Utf8String;

void ExecuteVisitor::Visit(PreConfigurator* preconfigurator)
{
    preconfigurator->Execute();
}

void ExecuteVisitor::Visit(HostDomainConfigurator* hostDomainConfigurator)
{
    Utf8String hostName;
    Utf8String domainName;
    
    bool foundHostName = m_xmlConfigurator.GetHostName(hostName);
    bool foundDomainName = m_xmlConfigurator.GetDomainName(domainName);

    // If hostname and/or domainname, then execute script
    if ((foundHostName && foundDomainName) || 
        (foundHostName && (!foundDomainName)))
    {
        hostDomainConfigurator->Execute(hostName, 
                                        domainName);
    }
    else
    {
        SCX_LOGWARNING(m_logHandle, ("Unable to find hostname/domain name in configuration file."));
    }
}

void ExecuteVisitor::Visit(TimeZoneConfigurator* timeZoneConfigurator)
{
    int timeZone;
    if (m_xmlConfigurator.GetTimeZone(timeZone))
    {
        timeZoneConfigurator->Execute(timeZone);
    }
    else
    {
        SCX_LOGWARNING(m_logHandle, ("Unable to find timeZone in configuration file."));
    }
}

void ExecuteVisitor::Visit(NetworkConfigurator* networkConfigurator)
{

    networkConfigurator->Execute(m_xmlConfigurator.VNetAdapters);
    
}

void ExecuteVisitor::Visit(UsersConfigurator* usersConfigurator)
{
    VMM::GuestAgent::SpecializationReader::OSSpecializationReader::User user;
    if (m_xmlConfigurator.GetRoot(user))
    {
        usersConfigurator->Execute(user);
    }
    else
    {
        SCX_LOGWARNING(m_logHandle, ("Unable to find any root user configurations in configuration file."));
    }
}

void ExecuteVisitor::Visit(RunOnceCommandConfigurator* runOnceConfigurator)
{
    if (m_xmlConfigurator.RunOnceCommands.size())
    {
        runOnceConfigurator->Execute(m_xmlConfigurator.RunOnceCommands);
    }
    else
    {
        SCX_LOGINFO(m_logHandle, ("Unable to find any run-once commands in configuration file."));
    }
}

void ExecuteVisitor::Visit(PostConfigurator* postConfigurator)
{
    postConfigurator->Execute();
}

void VMM::GuestAgent::OSConfigurator::CreateOSConfigurators(
	const VMM::GuestAgent::SpecializationReader::OSSpecializationReader::OSConfiguration& 
	xmlConfigurator)
{
	// Create the configurators. Order is important
	VMM::GuestAgent::OSConfigurator::OSConfigurator *configurators[] = 
		{
			new VMM::GuestAgent::OSConfigurator::PreConfigurator(), 
			new VMM::GuestAgent::OSConfigurator::TimeZoneConfigurator(),
			new VMM::GuestAgent::OSConfigurator::HostDomainConfigurator(),
			new VMM::GuestAgent::OSConfigurator::UsersConfigurator(),
			new VMM::GuestAgent::OSConfigurator::NetworkConfigurator(),
			new VMM::GuestAgent::OSConfigurator::RunOnceCommandConfigurator(),
			new VMM::GuestAgent::OSConfigurator::PostConfigurator()
		};
	
	// Double dispatch actions
	VMM::GuestAgent::OSConfigurator::ExecuteVisitor executeVisitor(xmlConfigurator);
	for (int i = 0; i < 7; i++)
	{
		configurators[i]->Accept(executeVisitor);
	}
	
	// Clean up
	for (int i = 0; i < 7; i++)
	{
		delete configurators[i];
	} 
}
