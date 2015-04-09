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

    \brief       Defines the full static disk information enumeration PAL for logical disks.
    
    \date        2011-05-06 13:40:00

*/
/*----------------------------------------------------------------------------*/
#ifndef STATICLOGICALDISFULLKENUMERATION_H
#define STATICLOGICALDISKFULLENUMERATION_H

#include <scxsystemlib/entityenumeration.h>
#include <scxsystemlib/staticlogicaldiskinstance.h>
#include <scxsystemlib/diskdepend.h>
#include <scxcorelib/scxhandle.h>
#include <vector>
#include <scxsystemlib/staticlogicaldiskenumeration.h>

namespace SCXSystemLib
{
/*----------------------------------------------------------------------------*/
/**
    Represents a set of discovered logical disks and their static data.
    Override the function Update() to support all logical disk,including all file system types.
*/
    class StaticLogicalDiskFullEnumeration : public StaticLogicalDiskEnumeration 
    {
    public:
        StaticLogicalDiskFullEnumeration(SCXCoreLib::SCXHandle<DiskDepend> deps);
        virtual ~StaticLogicalDiskFullEnumeration();

        virtual void Update(bool updateInstances=true);
    private:
        std::vector<std::wstring> m_mntTaboptions;
    };

} /* namespace SCXSystemLib */
#endif /* STATICLOGICALDISKFULLENUMERATION_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
