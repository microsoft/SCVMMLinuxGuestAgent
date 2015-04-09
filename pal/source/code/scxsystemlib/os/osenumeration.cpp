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

   \brief       Enumeration of Operating System 

   \date        08-03-04 14:12:00

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxexception.h>

#include <scxsystemlib/osenumeration.h>
#include <scxsystemlib/osinstance.h>

using namespace SCXCoreLib;

namespace SCXSystemLib
{
    /** Module name string */
    const wchar_t *OSEnumeration::moduleIdentifier = L"scx.core.common.pal.system.os.osenumeration";

    /*----------------------------------------------------------------------------*/
    /**
        Default constructor
    */
    OSEnumeration::OSEnumeration() : EntityEnumeration<OSInstance>()
    {
        m_log = SCXLogHandleFactory::GetLogHandle(moduleIdentifier);

        SCX_LOGTRACE(m_log, L"OSEnumeration default constructor");
    }

    /*----------------------------------------------------------------------------*/
    /**
       Desctructor.
    */
    OSEnumeration::~OSEnumeration()
    {
        SCX_LOGTRACE(m_log, L"OSEnumeration::~OSEnumeration()");
    }

    /*----------------------------------------------------------------------------*/
    /**
        Creates the total OS instances.
    */
    void OSEnumeration::Init()
    {
        SCX_LOGTRACE(m_log, L"OSEnumeration Init()");

        SetTotalInstance(SCXCoreLib::SCXHandle<OSInstance>(new OSInstance()));
        Update(true);
    }

    /*----------------------------------------------------------------------------*/
    /**
        Dump object as string (for logging).
    
        Parameters:  None
        Retval:      The object represented as a string suitable for logging.
    
    */
    const std::wstring OSEnumeration::DumpString() const
    {
        return L"OSEnumeration";
    }
}

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/

