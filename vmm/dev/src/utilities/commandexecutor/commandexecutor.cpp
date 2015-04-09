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
   \file        commandexecutor.cpp

   \brief       Utility class to execute commands using scxprocess
                
   \date        06-24-2012 19:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#include <commandexecutor.h>

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>

namespace
{

size_t const BUFFSIZE = 1024;

inline char*
skipws (
    char* startPos,
    char* endPos)
{
    return std::find_if (startPos, endPos, std::not1 (std::ptr_fun (isspace)));
}

}


namespace VMM
{
namespace GuestAgent
{
namespace Utilities
{

unsigned int
readConfig ()
{
    unsigned int timeout = DEFAULT_TIMEOUT;
    std::fstream configFile (CONFIG_FILE_NAME);
    if (configFile.good ())
    {
        char buffer[BUFFSIZE] = "";
        configFile.getline (buffer, BUFFSIZE);
        char* startPos = skipws (buffer, buffer + BUFFSIZE);
        if ((configFile.good () ||
             configFile.eof ()) &&
            isdigit (*startPos))
        {
            char* endPos = startPos;
            unsigned long val = strtoul (startPos, &endPos, 0);
            if (endPos != startPos &&
                0 == strlen (skipws (endPos, buffer + BUFFSIZE)) &&
                !(ULONG_MAX == val &&
                  ERANGE == errno))
            {
                if (MINIMUM_TIMEOUT > val)
                {
                    timeout = MINIMUM_TIMEOUT;
                }
                else if (MAXIMUM_TIMEOUT < val)
                {
                    timeout = MAXIMUM_TIMEOUT;
                }
                else
                {
                    timeout = static_cast<unsigned int> (val);
                }
            }
        }
    }
    return timeout;
}

}
}
}

using VMM::GuestAgent::Utilities::CommandExecutor;

int CommandExecutor::Execute(const std::wstring& command, 
                             const std::string& component,
                             unsigned int const timeoutSecs)
{

    std::istringstream stdInStream("");
    std::ostringstream stdOutStream;
    std::ostringstream stdErrStream;
    
    SCXCoreLib::SCXFilePath workingPath(L".");
    int exitStatus = 0;

    // Use execute script
    try
    {
        exitStatus = SCXCoreLib::SCXProcess::Run(command,
                                                 stdInStream,
                                                 stdOutStream,
                                                 stdErrStream,
                                                 timeoutSecs * 1000,
                                                 workingPath
                                                 /* , ChrootPath */ );
    }
    catch (SCXCoreLib::SCXInterruptedProcessException /* e */)
    {   
        SCX_LOGWARNING(m_logHandle, SCXCoreLib::StrFromMultibyte(component) +
                       L" timed out");
        exitStatus = -1;
    }
    catch (...)
    {
        SCX_LOGERROR(m_logHandle, SCXCoreLib::StrFromMultibyte(component) +
                     L" failed due to exceptions");
        exitStatus = -1;
    }
    
    // Check return codes
    if (exitStatus == 0)
    {
        // Success
        SCX_LOGINFO(m_logHandle, L"Successfully configured " +
                    SCXCoreLib::StrFromMultibyte(component));
        
    }
    else if (exitStatus == 1)
    {
        // Success with warnings
        SCX_LOGWARNING(m_logHandle, SCXCoreLib::StrFromMultibyte(component) +
                       L" completed with warnings");
    }
    else if (exitStatus == -1)
    {
        // Critical failure
        SCX_LOGERROR(m_logHandle, SCXCoreLib::StrFromMultibyte(component) +
                     L" failed with exitcode:-1");
    }
    else
    {
        
        SCX_LOGERROR(m_logHandle, SCXCoreLib::StrFromMultibyte(component) +
                     L" failed with other exitcode:");
        SCX_LOGERROR(
            m_logHandle,
            SCXCoreLib::StrToMultibyte(SCXCoreLib::StrFrom(exitStatus)));
    }

    // Printing stderr/stdout
    SCX_LOGINFO(m_logHandle, std::string("stdout as a result of running command:") + stdOutStream.str());
    SCX_LOGERROR(m_logHandle, std::string("stderr as a result of running command:") + stdErrStream.str());

    return exitStatus;

}
