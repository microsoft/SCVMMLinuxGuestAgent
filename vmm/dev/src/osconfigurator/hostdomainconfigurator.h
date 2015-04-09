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
   \file        hostdomainconfigurator.h

   \brief       This class provides an abstraction layer to execute host/domain configuration
                scripts based on 
                
   \date        06-24-2012 19:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/

#ifndef HOSTDOMAINCONFIGURATOR_H
#define HOSTDOMAINCONFIGURATOR_H

#include <util/LogHandleCache.h>
#include <util/Unicode.h>

#include <osconfigurator.h>

namespace VMM
{

    namespace GuestAgent
    {

        namespace OSConfigurator
        {

            class HostDomainConfigurator : public VMM::GuestAgent::OSConfigurator::OSConfigurator
            {

            private:
                
                /** Log Handle */
                SCXCoreLib::SCXLogHandle m_logHandle;

                /** Const strings */
                const std::string        m_componentName;

                std::string RandomHostName();

                bool LegitimateCharacter(char val);

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for Host/Domain Configurator

                */
                HostDomainConfigurator()
                  : m_logHandle(SCX::Util::LogHandleCache::Instance().GetLogHandle(
                                "scx.vmmguestagent.osconfigurator.hostdomainconfigurator"))
                  , m_componentName("HostDomain-Configurator")
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Virtual Destructor for Host/Domain Configurator

                */
                virtual ~HostDomainConfigurator()
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   Accept function for the visitor

                   \param  visitor    Visitor base class
                */
                inline void Accept(VMM::GuestAgent::OSConfigurator::Visitor& visitor)
                {
                    visitor.Visit(this);
                }

                /*----------------------------------------------------------------------------*/
                /**
                   Function that invokes the host/domain configuration script

                   \param      hostName      Hostname of the VM
                   
                   \param      domainName    Domain name of the VM

                   \return     None

                */
                void Execute(SCX::Util::Utf8String& hostname, 
                             SCX::Util::Utf8String& domainName);

            }; // End of HostDomainConfigurator class

        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* HOSTDOMAINCONFIGURATOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
