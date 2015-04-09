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

    \brief       Defines the statistical disk information instance PAL for physical disks.
    
    \date        2008-04-28 15:20:00
    
*/
/*----------------------------------------------------------------------------*/
#ifndef STATISTICALPHYSICALDISKINSTANCE_H
#define STATISTICALPHYSICALDISKINSTANCE_H

#include <scxsystemlib/statisticaldiskinstance.h>

namespace SCXSystemLib
{
    /*----------------------------------------------------------------------------*/
    /**
        Represents a single statistical physical disk instance.
    */
    class StatisticalPhysicalDiskInstance : public StatisticalDiskInstance
    {
        friend class StatisticalPhysicalDiskEnumeration;
    public:
        StatisticalPhysicalDiskInstance(SCXCoreLib::SCXHandle<DiskDepend> deps, bool isTotal = false);

        virtual bool GetReadsPerSecond(scxulong& value) const;
        virtual bool GetWritesPerSecond(scxulong& value) const;
        virtual bool GetBytesPerSecond(scxulong& read, scxulong& write) const;
        virtual bool GetDiskSize(scxulong& mbUsed, scxulong& mbFree) const;
        virtual bool GetBlockSize(scxulong& blockSize) const;

        virtual void Sample();

        virtual bool GetLastMetrics(scxulong& numR, scxulong& numW, scxulong& bytesR, scxulong& bytesW, scxulong& msR, scxulong& msW) const;
    };
}
#endif /* STATISTICALPHYSICALDISKINSTANCE_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
