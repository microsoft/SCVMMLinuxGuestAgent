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
   \file        statusmessage.cpp

   \brief       Class provides to read and write actions of osspecialization
                
   \date        07-03-2012 09:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/
#include <statusmessage.h>

#include <fstream>

#include <sys/stat.h>

#include <argumentmanager.h>

using VMM::GuestAgent::StatusManager::StatusMessage;
using SCX::Util::Xml::XElementPtr;
using SCX::Util::Xml::XElement;
using SCX::Util::Xml::XmlException;
using SCX::Util::Xml::XElementList;
using SCX::Util::Utf8String;

const std::string ElementNameOSConfigurationStatusRoot = "OSConfigurationStatus";
const std::string AttributeNameSchemaVersion           = "SchemaVersion";
const std::string SchemaVersion                        = "1.1";

const std::string StatusDir                            = "status";
const std::string StatusMessageXml                     = "statusmessage.xml";

std::string StatusMessage::ReadStatusFileAsString()
{

    SCX_LOGINFO(m_logHandle,
                L"Reading file:" + SCXCoreLib::StrFromMultibyte(m_statusFile));

    //First we need to get our incoming Message
    std::ifstream fileStream(m_statusFile.c_str());
    std::ostringstream strStream;

    if (fileStream.is_open())
    {
        strStream << fileStream.rdbuf();
        fileStream.close();
    }
    else
    {
        SCX_LOGINFO(m_logHandle, "Unable to open the file");
    }

    SCX_LOGINFO(m_logHandle,
                L"File read:" + SCXCoreLib::StrFromMultibyte(strStream.str()));
    return strStream.str();
    
}

bool StatusMessage::AddChildToRoot(const XElementPtr& element)
{

    SCX_LOGTRACE(m_logHandle, "Adding child element to root");

    mp_xelementRoot = NULL;

    std::string xmlString = ReadStatusFileAsString();

    //Let's Load'em up!
    try
    {
        XElement::Load(xmlString,
                       mp_xelementRoot);
    }
    catch (XmlException& x)
    {
        SCX_LOGERROR(m_logHandle, L"XML Exception:" + x.What());
        return false;
    }
    
    mp_xelementRoot->AddChild(element);

    Write();
    
    return true;
}

bool StatusMessage::ReadChildOfRoot(const std::string& elementNameIn, 
                                    std::string&       elementValue)
{

    // Reset root
    mp_xelementRoot = NULL;
    
    std::string xmlString = ReadStatusFileAsString();
    SCX_LOGINFO(m_logHandle, ("File read as:") + (xmlString));

    //Let's Load'em up!
    try
    {
        XElement::Load(xmlString,
                       mp_xelementRoot);
    }
    catch (XmlException& x)
    {
        SCX_LOGERROR(m_logHandle, ("XML Exception:") + SCXCoreLib::StrToMultibyte(x.What()));
        return false;
    }

    XElementPtr xElementPtr(NULL);
    XElementList::const_iterator elementIter;

    // Fetch the children elements from the XML string
    XElementList elementList;
    mp_xelementRoot->GetChildren(elementList);

    // Loop through elements and set class member variables appropriately
    for (elementIter = elementList.begin();
         elementIter != elementList.end();
         elementIter++)
    {

        xElementPtr = *elementIter;

        // Get the current element and its value
        Utf8String elementName = xElementPtr->GetName();
        Utf8String elementContent = xElementPtr->GetContent();
        
        // Check with the xml tags that are expected and store them in appropriate data members
        if (elementName.Str() == elementNameIn)
        {
            elementValue = elementContent.Str();
            return true;
        }
    }
    
    return false;
}

void StatusMessage::AddRoot()
{
    // Create the Root Element
    mp_xelementRoot = new XElement(ElementNameOSConfigurationStatusRoot);

    // Add Root Attributes
    mp_xelementRoot->SetAttributeValue(AttributeNameSchemaVersion,
                                       SchemaVersion);

    Write();
}

void StatusMessage::SetUp()
{
    // Write to file
    std::string installHome = VMM::GuestAgent::Utilities::ArgumentManager::Instance().GetVMMHome();
    
    std::string statusDir = installHome + 
      std::string("/") +
      StatusDir;
    
    // Create status dir, if it doesn't exist
    struct stat statBuff;
    if (stat(statusDir.c_str(), &statBuff) == -1)
    {
        SCX_LOGINFO(m_logHandle, "Creating status dir");

        if (mkdir(statusDir.c_str(), S_IRWXU) != 0)
        {
            SCX_LOGERROR(m_logHandle, "Unable to create status dir");
        }
    }
    else
    {
        SCX_LOGINFO(m_logHandle, "Status dir existed from before");
    }

    m_statusFile = installHome + 
        std::string("/") +  
        StatusDir  + 
        std::string("/") +  
        StatusMessageXml;
    
    // No file exists. So add root node.
    if (stat(m_statusFile.c_str(), &statBuff) == -1)
    {
        SCX_LOGINFO(m_logHandle, "No status xml files. Adding a new one");
        AddRoot();
    }
    else
    {
        SCX_LOGINFO(m_logHandle, "Status XML file exists.");
    }

}

void StatusMessage::Write()
{

    std::ofstream fileStream(m_statusFile.c_str(), 
                             std::ios::out |
                             std::ios::trunc);
    if (fileStream.is_open())
    {

        Utf8String xmlString;
        mp_xelementRoot->ToString(xmlString, false);

        SCX_LOGINFO(m_logHandle,
                    L"Writing following to file:" + 
                    SCXCoreLib::StrFromMultibyte(xmlString.Str()));

        fileStream << xmlString.Str();
    }
    else
    {
        SCX_LOGINFO(m_logHandle, "Unable to open status file");
    }

    fileStream.close();

}
