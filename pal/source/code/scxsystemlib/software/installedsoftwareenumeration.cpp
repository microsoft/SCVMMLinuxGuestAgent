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
\file       installedsoftwareenumeration.cpp

\brief      Enumeration of Software Instances.

\date       2011-01-18 14:56:20

*/
/*----------------------------------------------------------------------------*/

#include <scxsystemlib/entityenumeration.h>
#include <scxsystemlib/installedsoftwaredepend.h>
#include <scxsystemlib/installedsoftwareinstance.h>
#include <scxsystemlib/installedsoftwareenumeration.h>
#include <scxcorelib/stringaid.h>
#include <scxcorelib/scxlog.h>

using namespace std;
using namespace SCXCoreLib;

namespace SCXSystemLib
{
    /*----------------------------------------------------------------------------*/
    /**
    Default Constructor

    \param[in] deps Dependencies for the Installed software Enumeration.
    */
    InstalledSoftwareEnumeration::InstalledSoftwareEnumeration(SCXCoreLib::SCXHandle<InstalledSoftwareDependencies> deps):
        EntityEnumeration<InstalledSoftwareInstance>(),
        m_deps( deps )
    {
        m_log = SCXLogHandleFactory::GetLogHandle(L"scx.core.common.pal.system.software.installedsoftwareenumeration");
        SCX_LOGTRACE(m_log, L"InstalledSoftwareEnumeration constructor");
    }

    /*----------------------------------------------------------------------------*/
    /**
    Destructor
    */
    InstalledSoftwareEnumeration::~InstalledSoftwareEnumeration()
    {
        SCX_LOGTRACE(m_log, L"InstalledSoftwareEnumeration destructor");
    }

    /*----------------------------------------------------------------------------*/
    /**
    Create installed software instances

    */
    void InstalledSoftwareEnumeration::Init()
    {
        SCX_LOGTRACE(m_log, L"InstalledSoftwareEnumeration Init()");
    }

    /*----------------------------------------------------------------------------*/
    /**
    Update all installed software data

    */
    void InstalledSoftwareEnumeration::Update(bool updateInstances)
    {
        SCX_LOGTRACE(m_log, L"InstalledSoftwareEnumeration Update");
        vector<wstring> ids;
        m_deps->GetInstalledSoftwareIds(ids);

        SCX_LOGTRACE(m_log, StrAppend(wstring(L"Retreive the value of Installed software ids : "), ids.size()));
        for (std::vector<wstring>::iterator it = ids.begin(); it != ids.end(); it++)
        {
            SCXCoreLib::SCXHandle<InstalledSoftwareInstance> softwareInstance = GetInstance(*it);
            if (0 == softwareInstance)
            {
                try
                {
                    softwareInstance = new InstalledSoftwareInstance(*it, m_deps);
                    AddInstance(softwareInstance);
                }
                catch (const SCXCoreLib::SCXException& e)
                {
                    SCX_LOGWARNING(m_log,
                                   std::wstring(L"Error retrieving information about software with ID: ") + *it + L", " + e.What());
                }
            }
        }

        if (updateInstances)
        {
            for (size_t i = 0; i < this->Size(); i++)
            {
                try
                {
                    this->GetInstance(i)->Update();
                }
                catch (const SCXCoreLib::SCXException& e)
                {
                    SCX_LOGWARNING(m_log,
                                   std::wstring(L"Error storing information about software installation, ") + e.What());
                }
            }
        }
    }

    /*----------------------------------------------------------------------------*/
    /**
    Cleanup

    */
    void InstalledSoftwareEnumeration::CleanUp()
    {
        m_deps->CleanUp();
    }
}

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
