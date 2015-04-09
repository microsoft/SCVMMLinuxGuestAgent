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

    \brief      Implements the default implementation for BIOS dependencies.

    \date       2011-03-28 14:56:20

*/
/*----------------------------------------------------------------------------*/
#include <scxcorelib/scxcmn.h>
#include <stdio.h>
#include <vector>

namespace SCXSystemLib
{
    class BiosDependencies
    {
    public:
        BiosDependencies();
        virtual ~BiosDependencies();

#if defined(sun) && defined(sparc)
        /*----------------------------------------------------------------------------*/
        /**
        Get sparc prom version
        \param version : returned prom version value.
        */
        virtual void GetPromVersion(std::wstring& version);

        /*----------------------------------------------------------------------------*/
        /**
        Get sparc prom manufacturer
        \param manufacturer : returned prom manufacturer value.
        */
        virtual void GetPromManufacturer(std::wstring& manufacturer);

    private:
        /*----------------------------------------------------------------------------*/
        /**
        Get sparc prom property value
        \param propName : property name.
        \param retValue : returned property value.
        \throws SCXInternalErrorException if querying prom proptery value failed
        */
        void GetPromPropertyValue(const std::wstring& propName,std::wstring& retValue);

#endif
    };
}
