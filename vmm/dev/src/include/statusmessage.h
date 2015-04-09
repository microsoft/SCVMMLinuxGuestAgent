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
   \file        statusmessage.h

   \brief       Class provides to read and write actions of osspecialization status file
                
   \date        07-03-2012 09:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#ifndef STATUSMESSAGE_H
#define STATUSMESSAGE_H

#include <scxcorelib/stringaid.h>

#include <util/XElement.h>
#include <util/Unicode.h>

#include <util/LogHandleCache.h>

namespace VMM
{

    namespace GuestAgent
    {

        namespace StatusManager
        {

            class StatusMessage : public SCXCoreLib::SCXSingleton<StatusMessage>
            {

            public:

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Constructor for StatusMessage

                */
                StatusMessage()
                  : m_logHandle(SCX::Util::LogHandleCache::Instance().GetLogHandle(
                                    "scx.vmmguestagent.statusmanager.statusmessage"))
                  , mp_xelementRoot(NULL)
                    
                {
                    SetUp();
                }

                /*----------------------------------------------------------------------------*/
                /**
                   
                   Virtual Destructor for StatusMessage

                */
                virtual ~StatusMessage() 
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   Add Status Element to root

                   \return     None

                */
                bool AddChildToRoot(const SCX::Util::Xml::XElementPtr& element);

                /*----------------------------------------------------------------------------*/
                /**
                   Read element from Root

                   \param   elementName    ElementName being searched
                   
                   \param   elementValue   Value of the element being searched
                   
                   \return  bool           True if element was found. False otherwise

                */
                bool ReadChildOfRoot(const std::string& elementName, 
                                     std::string&       elementValue);
                
            private:
                
                /** Making the class a friend to enable destruction */
                friend class SCXCoreLib::SCXSingleton<StatusMessage>;

                /** Log Handle */
                SCXCoreLib::SCXLogHandle                  m_logHandle;

                /** Pointer to the Root Element */
                SCX::Util::Xml::XElementPtr  mp_xelementRoot;

                /** XML String */
                SCX::Util::Utf8String                   m_xmlString;

                /** Status File */
                std::string                               m_statusFile;

                /*----------------------------------------------------------------------------*/
                /**
                   Helper function to set up directories where status will be persisted

                   \return     None

                */    
                void SetUp();

                /*----------------------------------------------------------------------------*/
                /**
                   Create root element

                   \return     None

                */    
                void AddRoot();

                /*----------------------------------------------------------------------------*/
                /**
                   Helper function to read the file as a string

                   \return     string   File read as a string

                */    
                std::string ReadStatusFileAsString();

                /*----------------------------------------------------------------------------*/
                /**
                   Helper function to persist xml object in memory to file

                   \return     None

                */    
                void Write();
                
            }; // End of OSConfigurationStatus class

        } // End of StatusManager namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* STATUSMESSAGE_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
