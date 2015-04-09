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

    \brief       Specification of facets needed to make STL internalization behave the
                 same on scx supported platforms

    \date        08-08-05 10:18:00


*/
/*----------------------------------------------------------------------------*/
#ifndef SCXFACETS_H
#define SCXFACETS_H

#include <locale>
#include <wchar.h>
#include <iostream>
#include <vector>
#include <scxcorelib/scxcmn.h>

namespace SCXCoreLib {

#if defined(linux) || defined(macos)
typedef mbstate_t &do_length_mbstateRef;        //!< Declaration on platform
#else
typedef const mbstate_t &do_length_mbstateRef;  //!< Declaration on platform
#endif

//! STL facet to convert between internal wide representation and an external
//! representation acoording to current locale
class SCXDefaultEncodingFacet : public std::codecvt<wchar_t, char, mbstate_t>   {
public:

    virtual bool do_always_noconv() const throw ();
    virtual int do_encoding() const throw ();
    virtual int do_length(do_length_mbstateRef state, const char *begin, const char *end, size_t maxWideCharCount) const;

    virtual std::codecvt_base::result do_in(mbstate_t &state,
               const char *fromBegin, const char *fromEnd, const char *&fromNext,
               wchar_t *toBegin, wchar_t *toEnd, wchar_t *&toNext) const;

    virtual std::codecvt_base::result do_out(mbstate_t &state,
               const wchar_t *fromBegin, const wchar_t *fromEnd, const wchar_t *&fromNext,
               char *toBegin, char *toEnd, char *&toNext) const;

    virtual std::codecvt_base::result do_unshift(mbstate_t &state,
            char *toBegin, char *toEnd, char *&toNext) const;
};


}
#endif /* SCXFACETS_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
