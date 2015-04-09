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

    \brief          Enumeration of Operating System
    \date           08-03-04 14:14:00
    
*/
/*----------------------------------------------------------------------------*/
#ifndef OSENUMERATION_H
#define OSENUMERATION_H

#include <scxsystemlib/entityenumeration.h>
#include <scxsystemlib/osinstance.h>
#include <scxcorelib/scxlog.h>

namespace SCXSystemLib
{
    /*----------------------------------------------------------------------------*/
    /**
       Class that represents a collection of OperatingSystem data.
       There is only one instance.
    */
    class OSEnumeration : public EntityEnumeration<OSInstance>
    {
    public:
        static const wchar_t *moduleIdentifier;         //!< Module identifier

        OSEnumeration();
        ~OSEnumeration();
        virtual void Init();

        virtual const std::wstring DumpString() const;

    private:
        SCXCoreLib::SCXLogHandle m_log;                 //!< Handle to log file 
    };

}

#endif /* OSENUMERATION_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
