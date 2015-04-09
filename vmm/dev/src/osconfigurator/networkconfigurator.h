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
   \file        networkconfigurator.h

   \brief       This class provides an abstraction layer to execute network configuration
                scripts, which are provided in the XMl file.
                
   \date        06-25-2012 05:04:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#ifndef NETWORKCONFIGURATOR_H
#define NETWORKCONFIGURATOR_H

#include <util/LogHandleCache.h>

#include <osconfigurator.h>
#include <osspecializationreader.h>

namespace VMM
{

    namespace GuestAgent
    {

        namespace OSConfigurator
        {

            class NetworkConfigurator : public VMM::GuestAgent::OSConfigurator::OSConfigurator
            {

            private:
                
                /** Log Handle */
                SCXCoreLib::SCXLogHandle m_logHandle;

                /** Component name */
                const std::string        m_componentName;

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for Network-Configurator

                */
                NetworkConfigurator()
                  : m_logHandle(SCX::Util::LogHandleCache::Instance().GetLogHandle(
                                "scx.vmmguestagent.osconfigurator.networkconfigurator"))
                  , m_componentName("Network-Configurator")
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Virutal Destructor for Network-Configurator
                   
                */
                virtual ~NetworkConfigurator()
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
                   Function that invokes the networkconfig script

                   \return     None

                */
                void Execute(const std::vector<VMM::GuestAgent::SpecializationReader::OSSpecializationReader::VNetAdapter>& 
                             vNetAdapters);

            private:
                /*----------------------------------------------------------------------------*/
                /**
                   Helper function that configures one network adapter configuration

                   \param      vNetAdapter    Network Adapter object

                   \return     None

                */
                void ConfigureNetworkAdapter(const VMM::GuestAgent::SpecializationReader::OSSpecializationReader::VNetAdapter&
                                             vNetAdapter);

                /*----------------------------------------------------------------------------*/
                /**
                   Helper function that configures unspecified net adapters as DHCP

                   \param      None   

                   \return     None

                */
                void ConfigureUnspecifiedNetAdaptersForDHCP();
                

            }; // End of NetworkConfigurator class

        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* NETWORKCONFIGURATOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
