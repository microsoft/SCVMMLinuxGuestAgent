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
   \file        commandexecutor.h

   \brief       Utility class to execute commands using scxprocess
                
   \date        06-24-2012 19:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#ifndef SCRIPTEXECUTOR_H
#define SCRIPTEXECUTOR_H

#include <scxcorelib/stringaid.h>
#include <scxcorelib/scxprocess.h>

#include <util/LogHandleCache.h>

#include <climits>


namespace VMM
{

    namespace GuestAgent
    {

        namespace Utilities
        {
            unsigned int const DEFAULT_TIMEOUT = 300;            
            unsigned int const MINIMUM_TIMEOUT = 1;
            unsigned int const MAXIMUM_TIMEOUT = UINT_MAX / 1000;
            char const CONFIG_FILE_NAME[] =
                "/opt/microsoft/scvmmguestagent/etc/commandtimeout";

            /**
              \brief Attempts to open and read a timeout value from
                     CONFIG_FILE_NAME.  The value is also clamped between
                     MINIMUM_TIMEOUT and MAXIMUM_TIMEOUT.

              \return If the file exist and a value is successfully read, that
                      is clamped to (MINIMUM_TIMEOUT ... MAXIMUM_TIMEOUT) and
                      returned.  If the file does not exist, or if the value
                      cannot be read, DEFAULT_TIMEOUT is returned.
              */
            unsigned int readConfig ();

            class CommandExecutor 
            {

            private:
                
                /** Log Handle */
                SCXCoreLib::SCXLogHandle m_logHandle;

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for Command executor

                */
                CommandExecutor()
                  : m_logHandle(SCX::Util::LogHandleCache::Instance().GetLogHandle(
                                      "scx.vmmguestagent.osconfigurator.commandexecutor"))
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Destructor for Command executor

                */
                ~CommandExecutor() 
                {}

                /**
                  \ brief Runs a script.

                  \param command The script to run
                  \param component Text identifier used in log output
                  \param timeoutSecs The time to wait for the script to
                                     run in seconds

                  \return int Return value of the command executed
                  */
                int Execute(const std::wstring& command, 
                            const std::string& component,
                            unsigned int const timeoutSecs = DEFAULT_TIMEOUT);


            }; // End of CommandExecutor class

        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* COMMANDEXECUTOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
