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
   \file        isofetcherexception.h

   \brief       Exception class for ISO Fetcher class
   
   \date        05-22-2012 13:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#ifndef ISOFETCHEREXCEPTION_H
#define ISOFETCHEREXCEPTION_H

#include <scxcorelib/scxexception.h>

namespace VMM
{

    namespace GuestAgent
    {

        namespace Fetcher
        {

            class ISOFetcherException : public SCXCoreLib::SCXException
            {

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   Construct a ISOFetcherException object
                   
                   \param [in] message exception message
                */
                ISOFetcherException(const std::wstring& message)
                    : m_message(message) {}

                /*----------------------------------------------------------------------------*/
                /**
                   Implementation of What from SCXException

                   \return The Message string
                */
                std::wstring What() const
                {
                    return m_message;
                }

            private:

                /** Exception message */
                std::wstring m_message;

            }; // End of ISOFetcherException class

        } // End of Fetcher namespace

    } // End of GuestAgent

} // End of VMM

#endif /* ISOFETCHEREXCEPTION_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
