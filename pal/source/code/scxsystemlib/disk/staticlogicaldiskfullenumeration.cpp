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

    \brief       Implements the full logical disk enumeration pal for static information.
    
    \date        2011-05-06 13:40:00

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxsystemlib/staticlogicaldiskfullenumeration.h>
#include <scxsystemlib/staticdiskpartitionenumeration.h>

namespace SCXSystemLib
{
    /*----------------------------------------------------------------------------*/
    /**
       Constructor.
    
    \param       deps A StaticDiscDepend object which can be used.
        
*/
    StaticLogicalDiskFullEnumeration::StaticLogicalDiskFullEnumeration(SCXCoreLib::SCXHandle<DiskDepend> deps) 
                                    : StaticLogicalDiskEnumeration(deps) 
    {

    }

    /*----------------------------------------------------------------------------*/
    /**
       Virtual destructor.
    */
    StaticLogicalDiskFullEnumeration::~StaticLogicalDiskFullEnumeration()
    {

    }

    /*----------------------------------------------------------------------------*/
    /**
       Update the enumeration.

       \param updateInstances If true (default) all instances will be updated.
                              Otherwise only the content of teh enumeration will be updated.

    */
    void StaticLogicalDiskFullEnumeration::Update(bool updateInstances/*=true*/)
    {
#if defined(aix)
        StaticLogicalDiskEnumeration::Update(updateInstances);
#else
#if defined(hpux)
        vector<SCXLogicalVolumes> logVol;
        GetLogicalVolumes(m_log, m_deps, logVol);
        size_t i = 0;
        for(i = 0; i < logVol.size(); i++)
        {
            if(logVol[i].mntDir.size() == 0)
            {
                continue;
            }
            SCXCoreLib::SCXHandle<StaticLogicalDiskInstance> disk = GetInstance(logVol[i].mntDir);
            if (NULL == disk)
            {
                disk = new StaticLogicalDiskInstance(m_deps);
                disk->m_device = logVol[i].name;
                disk->m_mountPoint = logVol[i].mntDir;
                disk->SetId(logVol[i].mntDir);
                disk->m_fileSystemType = logVol[i].mntType;
                disk->m_logicDiskOptions = logVol[i].mntOpts;

                AddInstance(disk);
            }
            disk->m_online = true;
        }
#else
        unsigned int index = 0;
        m_deps->RefreshMNTTab();
        m_deps->readMNTTab(m_mntTaboptions);
        for (std::vector<MntTabEntry>::const_iterator it = m_deps->GetMNTTab().begin(); 
             it != m_deps->GetMNTTab().end(); it++)
        {
            SCXCoreLib::SCXHandle<StaticLogicalDiskInstance> disk = GetInstance(it->mountPoint);
            if(m_deps->FileSystemIgnored(it->fileSystem))
            {
                continue;
            }

            if (NULL == disk)
            {
                disk = new StaticLogicalDiskInstance(m_deps);
                disk->m_device = it->device;
                disk->m_mountPoint = it->mountPoint;
                disk->SetId(disk->m_mountPoint);
                disk->m_fileSystemType = it->fileSystem;
                disk->m_logicDiskOptions = m_mntTaboptions[index];
                index++;

                AddInstance(disk);
            }
            disk->m_online = true;
        }
#endif
        if (updateInstances)
        {
            UpdateInstances();
        }
#endif
    }

} /* namespace SCXSystemLib */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
