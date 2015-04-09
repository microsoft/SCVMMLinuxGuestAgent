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

    \brief      Enumeration of Memory. Only contains the total instance.
    
    \date       2007-07-03 09:56:20

*/
/*----------------------------------------------------------------------------*/
#ifndef MEMORYENUMERATION_H
#define MEMORYENUMERATION_H

#include <scxsystemlib/entityenumeration.h>
#include <scxsystemlib/memoryinstance.h>
#include <scxcorelib/scxlog.h>

namespace SCXSystemLib
{

    /*----------------------------------------------------------------------------*/
    /**
        Class that represents a colletion of Memory instances. Acutally only
        contains the total instance.
        
        PAL Holding the memory instance.

    */
    class MemoryEnumeration : public EntityEnumeration<MemoryInstance>
    {
    public:
        MemoryEnumeration();
        virtual void Init();

        virtual const std::wstring DumpString() const;
        
    private:
        SCXCoreLib::SCXLogHandle m_log;  //!< Log handle.
    };

}

#endif /* MEMORYENUMERATION_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
