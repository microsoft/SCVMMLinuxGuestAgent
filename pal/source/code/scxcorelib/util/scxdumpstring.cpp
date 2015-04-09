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

    \brief       Implementation of utilities to implement DumpString methods 
    
    \date        2007-12-04 14:20:00    
*/  
/*----------------------------------------------------------------------------*/
 
#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxdumpstring.h>

 
/*----------------------------------------------------------------------------*/
//! Constructs a DumpStringBuilder for a class
//! \param[in]  classname   Class containing the implemented DumpString     
SCXDumpStringBuilder::SCXDumpStringBuilder(std::string classname) {
    m_stream << classname.c_str() << ":";
}
 
/*----------------------------------------------------------------------------*/
//! Appends a scalar value
//! \param[in]  name    Name (role) of the value
//! \param[in]  value   The value
//! \returns    *this 
SCXDumpStringBuilder &SCXDumpStringBuilder::Text(const std::string &name, const std::wstring &value) {
    m_stream << L" " << name.c_str() << L"='" << value << L"'";
    return *this;
}
  
/*----------------------------------------------------------------------------*/
//! Retrieves the built string
//! \returns    Return value for DumpString
std::wstring SCXDumpStringBuilder::Str() const {
    return m_stream.str();
}

/*----------------------------------------------------------------------------*/
//! Retrieves the built string
//! \returns    Return value for DumpString
SCXDumpStringBuilder::operator std::wstring () const {
    return Str();
}
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
