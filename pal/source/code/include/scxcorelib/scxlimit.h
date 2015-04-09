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
    \file        scxlimit.h

    \brief       Define limits used in SCX-project.
    
    \date        07-10-11 15:14:13

*/
/*----------------------------------------------------------------------------*/
#ifndef SCXLIMIT_H
#define SCXLIMIT_H

/** scxlong is always 64 bits. This is the largest signed 64 bit value SCXCore can handle. */
const scxlong cMaxScxLong = (static_cast<scxlong>(0x7FFFFFFF)) << 32 |  0xFFFFFFFF;

/** scxlong is always 64 bits. This is the smallest signed 64 bit value SCXCore can handle. */
const scxlong cMinScxLong = -cMaxScxLong - 1;

#endif /* SCXLIMIT_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
