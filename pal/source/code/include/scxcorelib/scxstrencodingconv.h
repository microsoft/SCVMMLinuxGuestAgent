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
 
    \brief     Defines the public interface for the string encoding conversion PAL.

    \date      07-Jan-2011 09:30 PST
 

*/
/*----------------------------------------------------------------------------*/
#ifndef SCXSTRENCODINGCONV_H
#define SCXSTRENCODINGCONV_H

#include <string>
#include <vector>

namespace SCXCoreLib
{

    bool Utf8ToUtf16( const std::string& inUtf8Str,
                      std::vector< unsigned char >& outUtf16Bytes );
    bool Utf8ToUtf16le( const std::string& inUtf8Str,
                        std::vector< unsigned char >& outUtf16LEBytes );
    bool Utf16ToUtf8( const std::vector< unsigned char >& inUtf16Bytes,
                      std::string& outUtf8Str );
    bool Utf16leToUtf8( const std::vector< unsigned char >& inUtf16LEBytes,
                        std::string& outUtf8Str );

} /* namespace SCXCoreLib */

#endif /* SCXSTRENCODINGCONV_H */
/*------------------E-N-D---O-F---F-I-L-E-------------------------------*/
