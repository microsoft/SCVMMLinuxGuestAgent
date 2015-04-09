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
   \file        preconfigurator.h

   \brief       This class provides an abstraction layer to execute pre-configuraiton
                scripts, which are run irrespective of any specialization.
                
   \date        06-24-2012 19:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#ifndef PRECONFIGURATOR_H
#define PRECONFIGURATOR_H

#include <sys/reboot.h>
#include <scxcorelib/stringaid.h>

#include <util/LogHandleCache.h>

#include <osconfigurator.h>
#include <commandexecutor.h>

namespace VMM
{

    namespace GuestAgent
    {

        namespace OSConfigurator
        {

            class PreConfigurator : public VMM::GuestAgent::OSConfigurator::OSConfigurator
            {

            private:
                
                /** Log Handle */
                SCXCoreLib::SCXLogHandle m_logHandle;

                /** Const strings */
                const std::string        m_componentName;
                  
            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for Pre-Configurator

                */
                PreConfigurator()
                  : m_logHandle(SCX::Util::LogHandleCache::Instance().GetLogHandle(
                                "scx.vmmguestagent.osconfigurator.preconfigurator"))
                  , m_componentName("Pre-Configurator")
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Virtual Destructor for Pre-Configurator

                */
                virtual ~PreConfigurator() 
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
                   Function that invokes the preconfig script

                   \return     None

                */
                void Execute();

            }; // End of PreConfigurator class

        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* PRECONFIGURATOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
