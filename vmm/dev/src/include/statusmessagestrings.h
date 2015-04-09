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
   \file        statusmessagestrings.h

   \brief       string values for tags and values used for agent setup status xml file
                
   \date        07-03-2012 09:46:03
   
*/
/*----------------------------------------------------------------------------*/
#ifndef STATUSMESSAGESTRINGS_H
#define STATUSMESSAGESTRINGS_H

namespace VMM
{

    namespace GuestAgent
    {

        namespace StatusManager
        {

            class StatusMessageStrings
            {
            public:
                static const char* SpecializationStatus;
                static const char* SpecializationStarted;
                static const char* SpecializationComplete;
                static const char* SpecializationFailed;
                static const char* InsmodStatus;
                static const char* InsmodCommandComplete;
            };

        } // End of StatusManager namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* STATUSMESSAGESTRINGS_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
