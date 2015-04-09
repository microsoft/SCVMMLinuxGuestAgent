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

   \brief       Enumeration of BIOS 

   \date        11-01-14 15:00:00
*/
/*----------------------------------------------------------------------------*/
#ifndef BIOSENUMERATION_H
#define BIOSENUMERATION_H

#include <scxsystemlib/entityenumeration.h>
#include <scxsystemlib/biosinstance.h>
#include <scxcorelib/scxlog.h>


namespace SCXSystemLib
{

    /*----------------------------------------------------------------------------*/
    /**
       Class that represents a colletion of BIOS

       PAL Holding collection of BIOS

    */
    class BIOSEnumeration : public EntityEnumeration<BIOSInstance>
    {
    public:
        BIOSEnumeration();
        ~BIOSEnumeration();
        virtual void Init();
        virtual void CleanUp();
    private:
        SCXCoreLib::SCXLogHandle m_log;         //!< Log handle.

    };

}

#endif /* BIOSENUMERATION_H*/
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
