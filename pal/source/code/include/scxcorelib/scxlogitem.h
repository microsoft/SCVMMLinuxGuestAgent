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
    \file        

    \brief       Contains the definitions of log item class.

    \date        07-06-08 13:56:00
    
*/
/*----------------------------------------------------------------------------*/
#ifndef SCXLOGITEM_H
#define SCXLOGITEM_H

#include <scxcorelib/scxlog.h>
#include <scxcorelib/scxthread.h>
#include <scxcorelib/scxtime.h>
#include <string>

namespace SCXCoreLib
{
    /*----------------------------------------------------------------------------*/
    /**
        This is the data carrier for logs.
    
        Data carrier class for logging.

        This is how a log item is represented internally.

    */
    class SCXLogItem
    {
    public:
        SCXLogItem();
        SCXLogItem(const std::wstring& module,
                   SCXLogSeverity severity,
                   const std::wstring& message,
                   const SCXCodeLocation& location,
                   SCXCoreLib::SCXThreadId threadId);
        SCXLogItem(const SCXLogItem& o);
        virtual ~SCXLogItem();
	SCXLogItem& operator=(const SCXLogItem& o);
        
        const std::wstring& GetModule() const;
        SCXLogSeverity GetSeverity() const;
        const std::wstring& GetMessage() const;
        const SCXCodeLocation& GetLocation() const;
        SCXThreadId GetThreadId() const;
        const SCXCalendarTime& GetTimestamp() const;

        virtual const std::wstring DumpString() const;

    protected:
        std::wstring m_module;       //!< Module string.
        SCXLogSeverity m_severity;   //!< Severity of log item.
        std::wstring m_message;      //!< Original log message.
        SCXCodeLocation m_location;  //!< Code location where log occurred.
        SCXThreadId m_threadId;      //!< Thread id of originating thread.
        SCXCalendarTime m_timestamp; //!< Timestamp when log item was created.
    };
}

#endif /* SCXLOGITEM_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
