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

    \brief     Wql query support related exceptions

    \author    George Yan <georgeya@microsoft.com>

*/
/*----------------------------------------------------------------------------*/

#ifndef SCXWQL_H
#define SCXWQL_H

#include "scxcorelib/scxexception.h"
#include <map>
 

namespace SCXCoreLib
{
    /** Exception for Wql query string parsing failure */
    class SCXParseException : public SCXException {
		public:
			//! Ctor
			SCXParseException(std::wstring reason, 
                                 const SCXCodeLocation& l) : SCXException(l),
                                                             m_Reason(reason)
			{};

			std::wstring What() const { return L"Parsing of the wql query string failed: " + m_Reason;};
		protected:
			//! Description of internal error
			std::wstring   m_Reason;
    };

    /** Exception for Wql query string semantic analysis failure */
    class SCXAnalyzeException : public SCXException {
		public:
			//! Ctor
			SCXAnalyzeException(std::wstring reason, 
                                 const SCXCodeLocation& l) : SCXException(l),
                                                             m_Reason(reason)
			{};

			std::wstring What() const { return L"Semantic analysis of the wql query string failed: " + m_Reason;};
		protected:
			//! Description of internal error
			std::wstring   m_Reason;
    };
}


#endif /* SCXWQL_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
