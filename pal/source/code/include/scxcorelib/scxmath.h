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
 
    \brief     Math helper functions
 
    \date      07-05-28 12:00:00
 

*/
/*----------------------------------------------------------------------------*/
#ifndef SCXMATH_H
#define SCXMATH_H

// Get the system definition of MIN/MAX to avoid future conflicts (only a problem on some HP:s)
#if defined(hpux)
#include <sys/param.h>
#endif /* hpux */

//! Classical mathematical MIN() function returning the smaller of two values
#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

//! Classical mathematical MAX() function returning the larger of two values
#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
   
namespace SCXCoreLib 
{
    scxulong GetPercentage(scxulong old_tic, scxulong new_tic, scxulong old_tot, scxulong new_tot, bool inverse=false);
    scxulong BytesToMegaBytes(scxulong bytes);
    double BytesToMegaBytes(double bytes);
    scxulong KiloBytesToMegaBytes(scxulong kiloBytes);
    double KiloBytesToMegaBytes(double kiloBytes);
    
    double Round(double value);
    scxlong RoundToScxLong(double value);
    signed int RoundToInt(double value);
    unsigned int RoundToUnsignedInt(double value);

    scxulong Abs(scxlong value);
    
    bool IsAscending(int value1, int value2, int value3);
    bool IsStrictlyAscending(int value1, int value2, int value3);
    
    scxlong Pow(scxlong base, scxulong exponent);
    
    signed int ToInt(scxlong value); 
    
    bool Equal(double value1, double value2, double precision);
}

#endif /* SCXMATH_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
