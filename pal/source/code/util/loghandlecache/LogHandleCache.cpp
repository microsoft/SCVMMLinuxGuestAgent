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

#include <util/LogHandleCache.h>

#include <string>
#include <iostream>

using namespace SCX::Util;

SCXCoreLib::SCXLogHandle LogHandleCache::GetLogHandle(const std::string& name) 
{

    // Acquire the Cache lock
    SCXCoreLib::SCXThreadLock lock(m_cacheLockHandle);

    SCXASSERT(!name.empty());

    // Query the internal map to see if we have a cached handle
    std::map<std::string, SCXLogHandlePtr>::const_iterator iter = m_logHandleMap.find(name);
    SCXLogHandlePtr logHandlePtr;

    // Something is cached
    if (iter != m_logHandleMap.end())
    {
        // Get the logHandle
        logHandlePtr = iter->second;
    }
    else
    {
        // Create a new one and insert that
        logHandlePtr = SCXLogHandlePtr (new SCXCoreLib::SCXLogHandle());        
        *logHandlePtr = SCXCoreLib::SCXLogHandleFactory::GetLogHandle(SCXCoreLib::StrFromMultibyte(name));
        m_logHandleMap.insert(std::make_pair<std::string, SCXLogHandlePtr> (name, logHandlePtr));
    }

    return *logHandlePtr;
}
