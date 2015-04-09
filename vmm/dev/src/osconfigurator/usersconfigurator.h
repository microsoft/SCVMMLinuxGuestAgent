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
   \file        usersconfigurator.h

   \brief       This class provides an abstraction layer to execute user config scripts
                
   \date        06-25-2012 04:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#ifndef USERSCONFIGURATOR_H
#define USERSCONFIGURATOR_H

#include <scxcorelib/stringaid.h>

#include <util/LogHandleCache.h>
#include <osconfigurator.h>
#include <commandexecutor.h>
#include <osspecializationreader.h>

namespace VMM
{

    namespace GuestAgent
    {

        namespace OSConfigurator
        {

            class UsersConfigurator : public VMM::GuestAgent::OSConfigurator::OSConfigurator
            {

            private:
                
                /** Log Handle */
                SCXCoreLib::SCXLogHandle m_logHandle;

                /** Const strings */
                const std::string        m_componentName;

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for Users-Configurator

                */
                UsersConfigurator()
                  : m_logHandle(SCX::Util::LogHandleCache::Instance().GetLogHandle(
                                "scx.vmmguestagent.osconfigurator.usersconfigurator"))
                  , m_componentName("User-Configurator")
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Virtual Destructor for Users-Configurator

                */
                virtual ~UsersConfigurator()
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
                   Function that invokes the users config script

                   \param      user    User object that has to be applied

                   \return     None

                */
                void Execute(const VMM::GuestAgent::SpecializationReader::OSSpecializationReader::User& user);

            }; // End of UsersConfigurator class

        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* USERSCONFIGURATOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
