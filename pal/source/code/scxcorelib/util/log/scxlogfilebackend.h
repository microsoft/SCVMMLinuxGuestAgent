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

    \brief       Definitions for a file scxlog backend.

    \date        2008-07-23 15:15:20

*/
/*----------------------------------------------------------------------------*/
#ifndef SCXLOGFILEBACKEND_H
#define SCXLOGFILEBACKEND_H

#include "scxlogbackend.h"
#include <scxcorelib/scxfilepath.h>
#include <scxcorelib/scxfile.h>
#include <scxcorelib/scxprocess.h>
#include <scxcorelib/scxthread.h>

namespace SCXCoreLib
{
    /*----------------------------------------------------------------------------*/
    /**
        Simple file backend.
    */
    class SCXLogFileBackend : public SCXLogBackend
    {
    public:
        SCXLogFileBackend();
        SCXLogFileBackend(const SCXFilePath& filePath);

        virtual ~SCXLogFileBackend();

        virtual void SetProperty(const std::wstring& key, const std::wstring& value);
        virtual bool IsInitialized() const;

        virtual const SCXFilePath& GetFilePath() const;
    private:
        void DoLogItem(const SCXLogItem& item);
        void AddUserNameToFilePath();
        virtual void HandleLogRotate();
        const std::wstring Format(const SCXLogItem& item) const;

        SCXFilePath m_FilePath; //!< Path of log file.
        SCXHandle<std::wfstream> m_FileStream; //!< Stream to log file.

        int m_LogFileRunningNumber;            //!< Keep track of number of rotates
        SCXCalendarTime m_procStartTimestamp;  //!< Timestamp when first log from process was made, regardless of rotations
    };

} /* namespace SCXCoreLib */
#endif /* SCXLOGFILEBACKEND_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
