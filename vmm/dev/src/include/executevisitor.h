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
   \file        executevisitor.h

   \brief       This class calls the execute method of all osconfigurator classes
                
   
   \date        06-25-2012 05:06:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/

#ifndef EXECUTEVISITOR_H
#define EXECUTEVISITOR_H

#include <util/Unicode.h>

#include <osspecializationreader.h>
#include <osconfiguratorvisitor.h>
#include <osconfigurator.h>
#include <hostdomainconfigurator.h>
#include <networkconfigurator.h>
#include <preconfigurator.h>
#include <postconfigurator.h>
#include <usersconfigurator.h>
#include <timezoneconfigurator.h>
#include <runoncecommandconfigurator.h>

namespace VMM
{

    namespace GuestAgent
    {

        namespace OSConfigurator
        {

            class ExecuteVisitor : public VMM::GuestAgent::OSConfigurator::Visitor
            {

            private:

                /** XML object with specialization */
                VMM::GuestAgent::SpecializationReader::OSSpecializationReader::OSConfiguration m_xmlConfigurator;

                /** Log Handle */
                SCXCoreLib::SCXLogHandle m_logHandle;
                
            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for ExecuteVisitor

                */
                ExecuteVisitor(const VMM::GuestAgent::SpecializationReader::OSSpecializationReader::OSConfiguration& configObject)
                  : m_xmlConfigurator(configObject)
                  , m_logHandle(SCX::Util::LogHandleCache::Instance().GetLogHandle(
                                    "scx.vmmguestagent.osconfigurator.executevisitor"))
                {}
                
                /*----------------------------------------------------------------------------*/
                /**
                   Visit function for Pre-Configurator

                   \param     preConfigurator    Pointer to PreConfigurator class

                */
                virtual void Visit(VMM::GuestAgent::OSConfigurator::PreConfigurator* preconfigurator);

                /*----------------------------------------------------------------------------*/
                /**
                   Visit function for HostDomain-Configurator

                   \param     hostDomainConfigurator    Pointer to HostDomainConfigurator class

                */
                virtual void Visit(VMM::GuestAgent::OSConfigurator::HostDomainConfigurator* hostDomainConfigurator);

                /*----------------------------------------------------------------------------*/
                /**
                   Visit function for TimeZone-Configurator

                   \param     timeZoneConfigurator    Pointer to TimeZoneConfigurator class

                */
                virtual void Visit(VMM::GuestAgent::OSConfigurator::TimeZoneConfigurator* timeZoneConfigurator);

                /*----------------------------------------------------------------------------*/
                /**
                   Visit function for Netowrk Configurator

                   \param     networkConfigurator    Pointer to NetworkConfigurator class

                */
                virtual void Visit(VMM::GuestAgent::OSConfigurator::NetworkConfigurator* networkConfigurator);

                /*----------------------------------------------------------------------------*/
                /**
                   Visit function for User-Configurator

                   \param     userConfigurator    Pointer to UserConfigurator class

                */
                virtual void Visit(VMM::GuestAgent::OSConfigurator::UsersConfigurator* usersConfigurator);

                /*----------------------------------------------------------------------------*/
                /**
                   Visit function for RunOnce Comamnds Configurator

                   \param     runOnceConfigurator    Pointer to RunOnceCommandConfigurator class

                */
                virtual void Visit(VMM::GuestAgent::OSConfigurator::RunOnceCommandConfigurator* runOnceConfigurator);

                /*----------------------------------------------------------------------------*/
                /**
                   Visit function for Post-Configurator

                   \param     postConfigurator    Pointer to PostConfigurator class

                */
                virtual void Visit(VMM::GuestAgent::OSConfigurator::PostConfigurator* postConfigurator);

            }; // End of ExecuteVisitor base class

            void CreateOSConfigurators(const VMM::GuestAgent::SpecializationReader::OSSpecializationReader::OSConfiguration& 
                                              xmlConfigurator);
        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* EXECUTEVISITOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
