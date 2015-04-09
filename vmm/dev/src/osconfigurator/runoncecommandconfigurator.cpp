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
   \file        runoncecommandconfigurator.cpp

   \brief       Implementation for run-once command execution
                
                
   \date        06-24-2012 20:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#include <runoncecommandconfigurator.h>
#include <commandexecutor.h>

using VMM::GuestAgent::OSConfigurator::RunOnceCommandConfigurator;
using VMM::GuestAgent::Utilities::CommandExecutor;
using namespace VMM::GuestAgent::Utilities;

const std::string RunOnceCommandConfiguratorComponent = "RunOnceCommandConfigurator";

void RunOnceCommandConfigurator::Execute(const std::map<int, SCX::Util::Utf8String>& commands)
{
    CommandExecutor commandExecutor;
    int exitstatus = 0;

    for (std::map<int, SCX::Util::Utf8String>::const_iterator it = commands.begin(); it != commands.end(); ++it)
    {
        std::ostringstream st;
        st << it->first;
        SCX_LOGINFO(m_logHandle, "Executing run-once command item: " +
                    st.str() +
                    " command: " +
                    it->second.Str());

        if (setenv("HISTIGNORE", "*", 1) != 0)
        {
            SCX_LOGERROR(m_logHandle, "failed to set HISTIGNORE");
        }
        std::string command = it->second.Str();

        unsigned int timeout = readConfig ();
        if (DEFAULT_TIMEOUT != timeout)
        {
            std::ostringstream strm;
            strm << "Timeout value overridden to " << timeout << " seconds";
            SCX_LOGINFO (m_logHandle, strm.str ());
        }

        int ret = commandExecutor.Execute(SCXCoreLib::StrFromMultibyte(command), 
                                          RunOnceCommandConfiguratorComponent,
                                          timeout);

        if (ret != 0)
        {
            SCX_LOGERROR(m_logHandle, "Failed Run once command: " + command);
            exitstatus = 1;
        }
    }

    if (exitstatus == 1)
    {
        SCX_LOGWARNING(m_logHandle, ("At least one run-once command failed."));
    }
}
