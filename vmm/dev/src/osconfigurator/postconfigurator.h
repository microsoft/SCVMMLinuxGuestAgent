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
   \file        postconfigurator.h

   \brief       This class provides an abstraction layer to execute post-configuraiton
                scripts, which are run irrespective of any specialization.
                
   \date        06-24-2012 19:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#ifndef POSTCONFIGURATOR_H
#define POSTCONFIGURATOR_H

#include <scxcorelib/stringaid.h>

#include <util/LogHandleCache.h>

#include <isofetcher.h>
#include <argumentmanager.h>
#include <osconfigurator.h>
#include <commandexecutor.h>
#include <statusmessage.h>
#include <statusmessagestrings.h>


namespace VMM
{

    namespace GuestAgent
    {

        namespace OSConfigurator
        {

            class PostConfigurator : public VMM::GuestAgent::OSConfigurator::OSConfigurator
            {

            private:
                
                /** Log Handle */
                SCXCoreLib::SCXLogHandle m_logHandle;

                /** Const strings */
                const std::string        m_componentName;

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for Post-Configurator

                */
                PostConfigurator()
                  : m_logHandle(SCX::Util::LogHandleCache::Instance().GetLogHandle(
                                "scx.vmmguestagent.osconfigurator.postconfigurator"))
                  , m_componentName("Post-Configurator")
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Virtual Destructor for Post-Configurator

                */
                virtual ~PostConfigurator()
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
                inline void Execute()
                {
                    using namespace VMM::GuestAgent::Utilities;
                    using namespace VMM::GuestAgent::StatusManager;
                    using namespace VMM::GuestAgent::Fetcher;
                    using namespace SCX::Util::Xml;

                    SCX_LOGINFO(m_logHandle, ("Executing post-configuration script"));
                    
                    if (setenv("HISTIGNORE", "*", 1) != 0)
                    {
                        SCX_LOGERROR(m_logHandle, ("failed to set HISTIGNORE"));
                    }

                    // Invoke script
                    std::string command =
                        ArgumentManager::Instance().GetVMMHome() +
                        "/bin/cfgpost";
                    SCX_LOGINFO(m_logHandle, ("Shell Command:") + (command));

                    // Use execute script
                    CommandExecutor commandExec;
                    if (commandExec.Execute(SCXCoreLib::StrFromMultibyte(command),
                                            m_componentName) < 0)
                    {
                        SCX_LOGERROR(m_logHandle, "Post-Config script failed");
                        StatusMessage::Instance().AddChildToRoot(
                            XElementPtr(
                                new XElement(
                                    StatusMessageStrings::SpecializationStatus,
                                    StatusMessageStrings::SpecializationFailed)));
                    }
                    else 
                    {
                        StatusMessage::Instance().AddChildToRoot(
                            XElementPtr(new XElement(StatusMessageStrings::SpecializationComplete, 
                                                     StatusMessageStrings::SpecializationComplete)));
                    }

                    ISOFetcher::Instance().TerminateSetup();

                }

            }; // End of PostConfigurator class

        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* POSTCONFIGURATOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
