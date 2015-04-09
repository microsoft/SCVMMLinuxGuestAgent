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

    \date     07-06-05 00:23:50
    
*/
/*----------------------------------------------------------------------------*/
#ifndef SCX_WIDEN_STRING_H
#define SCX_WIDEN_STRING_H

/** Widen a constant string to wstring */
#define SCXSTRINGTOWSTRING2(x) L ## x
/** Widen a constant string to wstring */
#define SCXSTRINGTOWSTRING(x) SCXSTRINGTOWSTRING2(x)


/**
  __SCXWFILE__ is a std::wstring correspondance to __FILE__ 
  Useful mostly in unit tests, otherwise the SCXSRCLOCATION macro should be used.
*/
#define __SCXWFILE__ SCXSTRINGTOWSTRING(__FILE__)

#endif /* SCX_WIDEN_STRING_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
