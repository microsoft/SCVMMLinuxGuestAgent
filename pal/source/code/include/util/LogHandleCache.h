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
\file        LogHandleCache.h

\brief       Creates and maintains a cache of log handles. 

\date        07-12-11 02:46:03

\author      Jayashree Singanallur (jayasing)

*/
/*----------------------------------------------------------------------------*/

#ifndef LOGHANDLECACHE_H
#define LOGHANDLECACHE_H

#include <scxcorelib/scxsingleton.h>
#include <scxcorelib/scxthreadlock.h>
#include <scxcorelib/scxlog.h>

#include <string>
#include <map>

namespace SCX
{
    namespace Util
    {

        class LogHandleCache : public SCXCoreLib::SCXSingleton<LogHandleCache>
        {

            // Making the class a friend to enable destruction 
            friend class SCXCoreLib::SCXSingleton<LogHandleCache>;

        public:

            typedef SCXCoreLib::SCXHandle<SCXCoreLib::SCXLogHandle> SCXLogHandlePtr;

            LogHandleCache() : m_cacheLockHandle(SCXCoreLib::ThreadLockHandleGet())
            {}

            ~LogHandleCache()
            {}

            /*----------------------------------------------------------------------------*/
            /**
               Get LogHandle by name

               \param [in]  name   Name of the log handle, typically the module name, 
                                   which should be unique

               \Return             Cached SCXLogHandle to be used for logging

            */
            SCXCoreLib::SCXLogHandle GetLogHandle(const std::string& name);

        private:

            // Internal map for loghandle lookup
            std::map<std::string, SCXLogHandlePtr> m_logHandleMap;

            // Lock for log handle cache
            SCXCoreLib::SCXThreadLockHandle        m_cacheLockHandle;
        };
    }
}

#endif /* LOGHANDLECACHE_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
