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

    \brief       Assert implementation to allow handling asserts in other ways than default.

    \date        2007-05-16 16:26:00

*/
/*----------------------------------------------------------------------*/
#ifndef SCXASSERT_H
#define SCXASSERT_H

#include <scxcorelib/scxcmn.h>

#ifdef NDEBUG
/** Default assertion macro */
#define SCXASSERT(cond) 
/** Assertion macro with message parameter */
#define SCXASSERTFAIL(message)
#else
/** Default assertion macro */
#define SCXASSERT(cond) (cond)?static_cast<void>(0):SCXCoreLib::scx_assert_failed(#cond,__FILE__,__LINE__)
/** Assertion macro with message parameter */
#define SCXASSERTFAIL(message) SCXCoreLib::scx_assert_failed("",__FILE__,__LINE__,message)
#endif


namespace SCXCoreLib
{
    extern "C" void scx_assert_failed(const char* c, const char* f, const unsigned int l, const wchar_t* m = 0);
} /* namespace SCXCoreLib */

#endif /* SCXASSERT_H */
