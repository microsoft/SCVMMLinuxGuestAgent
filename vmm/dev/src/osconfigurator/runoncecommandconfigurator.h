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
   \file        runconcecommandconfigurator.h

   \brief       This class provides an abstraction layer to execute run-once commands

                
   \date        06-25-2012 04:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#ifndef RUNONCECOMMANDCONFIGURATOR_H
#define RUNONCECOMMANDCONFIGURATOR_H

#include <map>

#include <util/Unicode.h>

#include <osconfigurator.h>
#include <util/LogHandleCache.h>

namespace VMM
{

    namespace GuestAgent
    {

        namespace OSConfigurator
        {

            class RunOnceCommandConfigurator : public VMM::GuestAgent::OSConfigurator::OSConfigurator
            {

            private:
                
                /** Log Handle */
                SCXCoreLib::SCXLogHandle m_logHandle;

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for RunOnceCommandConfigurator

                */
                RunOnceCommandConfigurator()
                  : m_logHandle(SCX::Util::LogHandleCache::Instance().GetLogHandle(
                                    "scx.vmmguestagent.osconfigurator.runoncecommandconfigurator"))
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Virtual Destructor for RunOnceCommandConfigurator

                */
                virtual ~RunOnceCommandConfigurator()
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   Accept function for the visitor

                   \param  visitor    Visitor base class
                */
                inline virtual void Accept(VMM::GuestAgent::OSConfigurator::Visitor& visitor)
                {
                    visitor.Visit(this);
                }

                /*----------------------------------------------------------------------------*/
                /**
                   Function that executes the run-once commands

                   \return     None

                */
                void Execute(const std::map<int, SCX::Util::Utf8String>& commands);


            }; // End of RunOnceCommandConfigurator class

        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* RUNONCECOMMANDCONFIGURATOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
