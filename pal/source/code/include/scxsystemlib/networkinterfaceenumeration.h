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

    \brief       Specification of the network interface enumeration PAL
    
    \date        08-03-03 11:23:02   
    
*/
/*----------------------------------------------------------------------------*/
#ifndef NETWORKINTERFACEENUMERATION_H
#define NETWORKINTERFACEENUMERATION_H

#include <scxsystemlib/networkinterfaceinstance.h>
#include <scxsystemlib/entityenumeration.h>
#include <scxsystemlib/cpuinstance.h>
#include <scxcorelib/scxlog.h>
#include <scxcorelib/scxhandle.h>
#include <unistd.h>

namespace SCXSystemLib
{
    class NetworkInterfaceDependencies;
    
    /*----------------------------------------------------------------------------*/
    /**
        Represents a collection of network interfaces
    */
    class NetworkInterfaceEnumeration : public EntityEnumeration<NetworkInterfaceInstance>
    {
    public:
        NetworkInterfaceEnumeration(bool includeNonRunning = false);
        NetworkInterfaceEnumeration(SCXCoreLib::SCXHandle<NetworkInterfaceDependencies>, bool includeNonRunning = false);
        virtual ~NetworkInterfaceEnumeration();
        virtual void Init();
        virtual void Update(bool updateInstances=true);
    protected:
        virtual void UpdateInstances();
        virtual void UpdateEnumeration();
    private:
        SCXCoreLib::SCXLogHandle m_log;         //!< Log handle.
        SCXCoreLib::SCXHandle<NetworkInterfaceDependencies> m_deps; //!< Dependencies to rely on
        bool m_includeNonRunning; //!< Return all interfaces (rather than UP and/or RUNNING interfaces only)
    };
}


#endif /* NETWORKINTERFACEENUMERATION_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
