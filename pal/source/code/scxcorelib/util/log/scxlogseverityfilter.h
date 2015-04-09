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

    \brief       Contains the definition of the log severity filter class.

    \date        2008-07-24 15:21:39

*/
/*----------------------------------------------------------------------------*/
#ifndef SCXLOGSEVERITYFILTER_H
#define SCXLOGSEVERITYFILTER_H

#include <map>
#include <scxcorelib/scxlog.h>

namespace SCXCoreLib
{
    /*----------------------------------------------------------------------------*/
    /**
        An SCXLogSeverityFilter is used to filter log items according to
        severity thresholds set in the module hierarchy.
    */
    class SCXLogSeverityFilter
    {
        typedef std::map<std::wstring, SCXLogSeverity> SeverityMap; //!< Type for mapping
    public:
        SCXLogSeverityFilter();
        virtual bool IsLogable(const SCXLogItem& item) const;
        virtual SCXLogSeverity GetSeverityThreshold(const std::wstring& module) const;
        virtual bool SetSeverityThreshold(const std::wstring& module, SCXLogSeverity severity);
        virtual bool ClearSeverityThreshold(const std::wstring& module);
        virtual SCXLogSeverity GetMinActiveSeverityThreshold() const;

        /**
            Virtual destructor.
         */
        virtual ~SCXLogSeverityFilter() {};
    private:
        SCXLogSeverity m_DefaultSeverity; //!< Severity of root module.
        SeverityMap m_ModuleMap; //!< Module severity mapping.
    };
} /* namespace SCXCoreLib */
#endif /* SCXLOGSEVERITYFILTER_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
