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
        \file        osspecializationparserexception.h

        \brief       exception for specialization parser

        \date        01-13-12 11:04:50

*/
/*----------------------------------------------------------------------------*/
#ifndef OSSPECIALIZATIONPARSEREXCEPTION_H
#define OSSPECIALIZATIONPARSEREXCEPTION_H

#include <string>


namespace VMM
{
    namespace GuestAgent
    {
        namespace SpecializationReader
        {
                /*----------------------------------------------------------------------------*/
                /**
                    Exception class for OSSpecialization parser
                */
                class OSSpecializationParserException
                {
                public:
                    /*----------------------------------------------------------------------------*/
                    /**
                        OSSpecializationParserException constructor
                    */
                    OSSpecializationParserException(const std::string& message) : m_message(message) {}
                
                    /*----------------------------------------------------------------------------*/
                    /**
                        Exception message
                    */
                    std::string What() const
                    {
                        return m_message;
                    }
                
                private:
                    std::string m_message;
                
                }; // End of OSSpecializationParserException class

         } // namespace SpecializationReader
    } // namespace GuestAgent
} // namespace VMM

#endif // OSSPECIALIZATIONPARSEREXCEPTION_H
