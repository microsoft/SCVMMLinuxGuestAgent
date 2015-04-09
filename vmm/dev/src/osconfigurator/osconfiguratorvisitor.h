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
   \file        osconfiguratorvisitor.h

   \brief       Visitor abstract base class for OSConfiguration
                
   
   \date        06-24-2012 13:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/

#ifndef OSCONFIGURATORVISITOR_H
#define OSCONFIGURATORVISITOR_H

namespace VMM
{

    namespace GuestAgent
    {

        namespace OSConfigurator
        {

            // Forward declarations of the child configurator classes
            class PreConfigurator;
            class HostDomainConfigurator;
            class TimeZoneConfigurator;
            class NetworkConfigurator;
            class UsersConfigurator;
            class RunOnceCommandConfigurator;
            class PostConfigurator;
            
            class Visitor
            {

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Virtual Destructor for Visitor

                */
                virtual ~Visitor()
                {}

                // Pure virtual functions for all the configurators
                /*----------------------------------------------------------------------------*/
                /**
                   
                   Pure-virtual function to perform Pre-Configuration
                   
                   \param PreConfigurator  A pointer to PreConfigurator class

                */
                virtual void Visit(PreConfigurator*) = 0;

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Pure-virtual function to configure Host/Domain
                   
                   \param hostDomainConfigurator  A pointer to HostDomainConfigurator class

                */
                virtual void Visit(HostDomainConfigurator* hostDomainConfigurator) = 0;

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Pure-virtual function to configure TimeZone
                   
                   \param timezoneConfigurator  A pointer to TimeZoneConfigurator class

                */
                virtual void Visit(TimeZoneConfigurator* timezoneConfigurator) = 0;

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Pure-virtual function to configure Network
                   
                   \param networkConfigurator  A pointer to NetworkConfigurator class

                */
                virtual void Visit(NetworkConfigurator* network) = 0;

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Pure-virtual function to configure users
                   
                   \param userConfigurator  A pointer to UsersConfigurator class

                */
                virtual void Visit(UsersConfigurator* userConfigurator) = 0;

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Pure-virtual function to run certain commands
                   
                   \param   commandConfigurator  A pointer to PreConfigurator class

                */
                virtual void Visit(RunOnceCommandConfigurator* commandConfigurator) = 0;

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Pure-virtual function to run Post-Configurator
                   
                   \param   postConfigurator   A pointer to PostConfigurator class

                */
                virtual void Visit(PostConfigurator* postConfigurator) = 0;
                
            }; // End of OSConfiguratorVisitor base class

        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* OSCONFIGURATORVISITOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
