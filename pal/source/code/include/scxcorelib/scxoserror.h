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

    \brief        Operating system error handling         
    
    \date        07-09-27 17:56:00

    Operating system calls normally return error codes instead of throwing 
    exceptions. Here are some utilities to map the C-style of error handling 
    into the C++ style, that is, exceptions.
     
    
*/
/*----------------------------------------------------------------------------*/
#ifndef OSERROR_H
#define OSERROR_H

#include <string>
 
namespace SCXCoreLib {
    std::wstring TextOfWindowsLastError(unsigned int lastError);
    std::wstring UnexpectedWindowsError(const std::wstring &problem, 
            unsigned int lastError);
     
    std::wstring UnexpectedErrno(const std::wstring &problem, int errnoValue);
}

#endif /* OSERROR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
