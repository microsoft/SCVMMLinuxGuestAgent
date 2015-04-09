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
   \file        timezoneconfigurator.h

   \brief       This class provides an abstraction layer to execute time zone configuraiton
                scripts based on the values provided in the XML file
                
   \date        06-25-2012 04:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#ifndef TIMEZONECONFIGURATOR_H
#define TIMEZONECONFIGURATOR_H

#include <scxcorelib/stringaid.h>

#include <util/LogHandleCache.h>

#include <argumentmanager.h>
#include <osconfigurator.h>
#include <commandexecutor.h>


namespace VMM
{

    namespace GuestAgent
    {

        namespace OSConfigurator
        {

            class TimeZoneConfigurator : public VMM::GuestAgent::OSConfigurator::OSConfigurator
            {

            private:
                
                /** Log Handle */
                SCXCoreLib::SCXLogHandle m_logHandle;

                // Const strings
                const std::string        m_componentName;

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for Time Zone Configurator

                */
                TimeZoneConfigurator()
                  : m_logHandle(SCX::Util::LogHandleCache::Instance().GetLogHandle(
                                "scx.vmmguestagent.osconfigurator.timezoneconfigurator"))
                  , m_componentName("TimeZone-Configurator")
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Virutal Destructor for Time Zone Configurator

                */
                virtual ~TimeZoneConfigurator()
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
                   Function that invokes the timezone config script

                   \return     None

                */
                inline void Execute(const int& timezoneID)
                {
                    using VMM::GuestAgent::Utilities::ArgumentManager;
                    SCX_LOGINFO(m_logHandle, ("Executing time zone configuration script"));
                    
                    // Construct command
                    if (setenv("HISTIGNORE", "*", 1) != 0)
                    {
                        SCX_LOGERROR(m_logHandle, ("failed to set HISTIGNORE"));
                    }
                    std::ostringstream oss;
                    oss << ArgumentManager::Instance().GetVMMHome() << "/bin/cfgtimezone tzid=" << timezoneID;

                    SCX_LOGINFO(m_logHandle, ("Shell command:") + (oss.str()));
                    
                    // Use execute script
                    VMM::GuestAgent::Utilities::CommandExecutor commandExec;
                    commandExec.Execute(SCXCoreLib::StrFromMultibyte(oss.str()), 
                                        m_componentName);
                    

                }

            }; // End of TimeZoneConfigurator class

        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* TIMEZONECONFIGURATOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
