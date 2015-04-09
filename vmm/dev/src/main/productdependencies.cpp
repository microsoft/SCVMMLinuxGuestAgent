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
    \file        productdependencies.cpp

    \brief       Implements the product-specific dependencies for SCXCore
    \date        2013-02-26 13:38:00

    \note        This module is supplied solely to implement hooks for unit
                 test purposes.  This module provides hooks that must be
                 implemented by any consumer of the SCXCore code base.
*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/stringaid.h>
#include <scxcorelib/scxprocess.h>
#include <scxcorelib/scxproductdependencies.h>
#include <scxsystemlib/scxproductdependencies.h>
#include <vmmbuildversion.h>

namespace SCXCoreLib
{
    namespace SCXProductDependencies
    {
        void WriteLogFileHeader( SCXHandle<std::wfstream> &stream, int logFileRunningNumber, SCXCalendarTime& procStartTimestamp )
        {
            std::wstringstream continuationLogMsg;
            if ( logFileRunningNumber > 1 )
            {
                continuationLogMsg << L"* Log file number: " << StrFrom(logFileRunningNumber) << std::endl;
            }

            (*stream) << L"*" << std::endl
                      << L"* SC VMM Guest Agent" << std::endl
#if !defined(WIN32)
                      << L"* Build number: "
                      << VMM_BUILDVERSION_MAJOR << L'.'
                      << VMM_BUILDVERSION_MINOR << L'.'
                      << VMM_BUILDVERSION_PATCH << L'-'
                      << VMM_BUILDVERSION_BUILDNR << std::endl
#endif
                      << L"* Process id: " << StrFrom(SCXProcess::GetCurrentProcessID()) << std::endl
                      << L"* Process started: " << procStartTimestamp.ToExtendedISO8601() << std::endl
                      << continuationLogMsg.str() 
                      << L"*" << std::endl
                      << L"* Log format: <date> <severity>     [<code module>:<line number>:<process id>:<thread id>] <message>" << std::endl
                      << L"*" << std::endl;
        }

        void WrtieItemToLog( SCXHandle<std::wfstream> &stream, const SCXLogItem& item, const std::wstring& message )
        {
            (void) item;

            (*stream) << message << std::endl;
        }
    }
}
