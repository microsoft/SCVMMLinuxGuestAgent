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
        \file        osspecializationreader.cpp

        \brief       Parse specialization file

        \date        01-13-12 11:04:50

*/
/*----------------------------------------------------------------------------*/

#include <osspecializationreader.h>
#include <osspecializationparserexception.h>

#include <util/LogHandleCache.h>


using namespace std;

using SCX::Util::Xml::XElement;
using SCX::Util::Xml::XElementList;
using SCX::Util::Xml::XElementPtr;
using SCX::Util::Xml::XmlException;
using SCX::Util::Utf8String;

using VMM::GuestAgent::SpecializationReader::OSSpecializationReader;
using SCX::Util::LogHandleCache;

const string OSSpecializationReader::sLinuxOSSpecialization   = "LinuxOSSpecialization";
const string OSSpecializationReader::sAgentVersion            = "AgentVersion";
const string OSSpecializationReader::sSchemaVersion           = "SchemaVersion";
const string OSSpecializationReader::sOSConfiguration         = "OSConfiguration";
const string OSSpecializationReader::sHostName                = "HostName";
const string OSSpecializationReader::sDomainName              = "DNSDomainName";
const string OSSpecializationReader::sTimeZone                = "TimeZone";
const string OSSpecializationReader::sVNetAdapters            = "VNetAdapters";
const string OSSpecializationReader::sRunOnceCommands         = "RunOnceCommands";
const string OSSpecializationReader::sRunOnceCommand          = "RunOnceCommand";
const string OSSpecializationReader::sCommandSequence         = "Sequence";
const string OSSpecializationReader::sVNetAdapter             = "VNetAdapter";
const string OSSpecializationReader::sMACAddress              = "MACAddress";
const string OSSpecializationReader::sIPV4Property            = "IPV4Property";
const string OSSpecializationReader::sIPV6Property            = "IPV6Property";
const string OSSpecializationReader::sStaticIP                = "StaticIP";
const string OSSpecializationReader::sAddressType             = "AddressType";
const string OSSpecializationReader::sSTATIC                  = "STATIC";
const string OSSpecializationReader::sDHCP                    = "DHCP";
const string OSSpecializationReader::sGateways                = "Gateways";
const string OSSpecializationReader::sGateway                 = "Gateway";
const string OSSpecializationReader::sAddress                 = "Address";
const string OSSpecializationReader::sMetric                  = "Metric";
const string OSSpecializationReader::sNameServers             = "NameServers";
const string OSSpecializationReader::sNameServer              = "NameServer";
const string OSSpecializationReader::sUsers                   = "Users";
const string OSSpecializationReader::sUser                    = "User";
const string OSSpecializationReader::sRoot                    = "root";
const string OSSpecializationReader::sUserName                = "UserName";
const string OSSpecializationReader::sPassword                = "Password";
const string OSSpecializationReader::sSSHKey                  = "SSHKey";
const string OSSpecializationReader::sUID                     = "UID";
const string OSSpecializationReader::sGroupID                 = "GroupID";
const string OSSpecializationReader::sPrimaryGroup            = "PrimaryGroup";
const string OSSpecializationReader::sDNSSearchSuffixes       = "DNSSearchSuffixes";
const string OSSpecializationReader::sDNSSearchSuffix         = "DNSSearchSuffix";

// log handle at file scope to be visible to nested classes of OSSpecializationReader
SCXCoreLib::SCXLogHandle g_logHandle;

OSSpecializationReader::OSSpecializationReader()
{
    g_logHandle = LogHandleCache::Instance().GetLogHandle("scx.vmmguestagent.osspecializationreader");
}

bool OSSpecializationReader::GetLinuxOSSpecialization(OSSpecializationReader::LinuxOSSpecialization& val)
{
    bool ret = m_specialization.TryGet(val);

    if (ret == false)
    {
        SCX_LOGWARNING(g_logHandle, "GetLinuxOSSpecialization failed: uninitialized LinuxOSSpecialization");
    }

    return ret;
}

void OSSpecializationReader::LoadXML(const Utf8String& xmlString)
{
    SCX_LOGINFO(g_logHandle, "Inside loadXML");

    SCXASSERT(!xmlString.Empty());

    m_xmlString = xmlString;

    try
    {
        XElement::Load(xmlString, m_pXElementRoot);

        SCX_LOGTRACE(g_logHandle, "XML Root element successfully loaded in OSSpecializationReader::LoadXML");
    }
    catch (XmlException& x)
    {
        SCX_LOGERROR(g_logHandle, L"XML Exception: " + x.What());
        return;
    }

    SCX_LOGTRACE(g_logHandle, "Begin Loading OSSpecialization object from XML");

    Load();

    SCX_LOGTRACE(g_logHandle, "Completed Loading OSSpecialization object from XML");
}

void OSSpecializationReader::Load()
{
    if (m_pXElementRoot == NULL)
    {
        SCX_LOGERROR(g_logHandle, "OSSpecializationReader::ParseChildNodes, null m_pXElementRoot"); 
        throw OSSpecializationParserException("null m_pXElementRoot");
    }

    if (m_pXElementRoot->GetName().Str() != sLinuxOSSpecialization)
    {
        SCX_LOGERROR(g_logHandle, "Unrecognized XML Root element: " + m_pXElementRoot->GetName().Str());
        throw OSSpecializationParserException("Unrecognized root element" + sLinuxOSSpecialization);
    }

    m_specialization.IsValid() = true;
    m_specialization.inner().Read(m_pXElementRoot);
}

void OSSpecializationReader::LinuxOSSpecialization::Read(const XElementPtr& osSpecElementPtr)
{
    XElementList xElementList;
    osSpecElementPtr->GetChildren(xElementList);

    for (XElementList::const_iterator xElementListIter = xElementList.begin();
        xElementListIter != xElementList.end();
        xElementListIter++)
    {
        XElementPtr xElementPtr = *xElementListIter;
        Utf8String elementName = xElementPtr->GetName();

        if (elementName == sAgentVersion)
        {
            m_agentVersion = xElementPtr->GetContent();

            SCX_LOGTRACE(g_logHandle, "Agent Version read as: " + xElementPtr->GetContent().Str());
        }
        else if (elementName == sSchemaVersion)
        {
            m_schemaVersion = xElementPtr->GetContent();

            SCX_LOGTRACE(g_logHandle, "Schema Version read as: " + xElementPtr->GetContent().Str());
        }
        else if (elementName == sOSConfiguration)
        {
            m_osConfiguration.IsValid() = true;
            m_osConfiguration.inner().Read(xElementPtr);

            SCX_LOGTRACE(g_logHandle, "Read of OS Configuration complete.");
        }
        else
        {
            SCX_LOGERROR(g_logHandle, "Unexpected tag encountered in LinuxOSSpecialization :" + elementName.Str());
            throw OSSpecializationParserException("unexpected tag encountered: " + elementName.Str());
        }
    }
}

void OSSpecializationReader::OSConfiguration::Read(const XElementPtr& osConfigElementPtr)
{
    XElementList xElementList;
    osConfigElementPtr->GetChildren(xElementList);

    for (XElementList::const_iterator xElementListIter = xElementList.begin();
        xElementListIter != xElementList.end();
        xElementListIter++)
    {
        XElementPtr xElementPtr = *xElementListIter;
        Utf8String elementName = xElementPtr->GetName();

        if (elementName == sHostName)
        {
            m_hostName = xElementPtr->GetContent();

            SCX_LOGTRACE(g_logHandle, "Host Name read as: " + xElementPtr->GetContent().Str());
        }
        else if (elementName == sDomainName)
        {
            m_domainName = xElementPtr->GetContent();

            //SCX_LOGTRACE(g_logHandle, "Domain Name read as: " + xElementPtr->GetContent());
        }
        else if (elementName == sTimeZone)
        {
            int val;
            istringstream ( xElementPtr->GetContent().Str() ) >> val;
            m_timeZone = val;

            SCX_LOGTRACE(g_logHandle, "Time Zone read as: " + xElementPtr->GetContent().Str());
        }
        else if (elementName == sVNetAdapters)
        {
            ReadVNetAdapters(xElementPtr);

            SCX_LOGTRACE(g_logHandle, "Read of VNet Adapters complete.");
        }
        else if (elementName == sRunOnceCommands)
        {
            ReadRunOnceCommands(xElementPtr);

            SCX_LOGTRACE(g_logHandle, "Read of Run Once Commands complete.");
        }
        else if (elementName == sUsers)
        {
            ReadRootUser(xElementPtr);

            SCX_LOGTRACE(g_logHandle, "Read of Root User complete.");
        }
        else
        {
            SCX_LOGERROR(g_logHandle, "Unexpected tag encountered in OSConfiguration :" + elementName.Str());
            throw OSSpecializationParserException("unexpected tag encountered: " + elementName.Str());
        }
    }
}

void OSSpecializationReader::OSConfiguration::ReadVNetAdapters(const XElementPtr& vNetAdaptersElementPtr)
{
    XElementList vNetAdaptersElementList;
    vNetAdaptersElementPtr->GetChildren(vNetAdaptersElementList);
    VNetAdapters.clear();

    for (XElementList::const_iterator vNetAdaptersElementIter = vNetAdaptersElementList.begin();
         vNetAdaptersElementIter != vNetAdaptersElementList.end();
         vNetAdaptersElementIter++)
    {
        XElementPtr xElementPtr = *vNetAdaptersElementIter;

        Utf8String elementName = xElementPtr->GetName();

        if (elementName == sVNetAdapter)
        {
            VNetAdapter val;
            val.Read(xElementPtr);
            VNetAdapters.push_back(val);

            SCX_LOGTRACE(g_logHandle, "Read of VNet Adapter complete.");
        }
        else
        {
            SCX_LOGERROR(g_logHandle, "invalid tag encountered in ReadVNetAdapters: " + elementName.Str());
            throw OSSpecializationParserException("unexpected tag encountered: " + elementName.Str());
        }
    }
}

void OSSpecializationReader::OSConfiguration::ReadRunOnceCommands(const XElementPtr& runOnceCommandsElementPtr)
{
    XElementList runOnceCommandsElementList;
    runOnceCommandsElementPtr->GetChildren(runOnceCommandsElementList);

    for (XElementList::const_iterator runOnceCommandsElementIter = runOnceCommandsElementList.begin();
         runOnceCommandsElementIter != runOnceCommandsElementList.end();
         runOnceCommandsElementIter++)
    {
        XElementPtr xElementPtr = *runOnceCommandsElementIter;

        Utf8String elementName = xElementPtr->GetName();

        if (elementName == sRunOnceCommand)
        {
            Utf8String sSequenceVal;

            if (xElementPtr->GetAttributeValue(sCommandSequence, sSequenceVal))
            {
                int sequenceVal;
                istringstream ( sSequenceVal.Str() ) >> sequenceVal;

                if (RunOnceCommands.find(sequenceVal) == RunOnceCommands.end())
                {
                    RunOnceCommands[sequenceVal] = xElementPtr->GetContent();

                    SCX_LOGTRACE(g_logHandle, "Run Once Command read as: " + xElementPtr->GetContent().Str());
                }
                else
                {
                    SCX_LOGERROR(g_logHandle, "duplicate Sequence attribute encountered in ReadRunOnceCommands: " + elementName.Str());
                }
            }
            else
            {
                SCX_LOGERROR(g_logHandle, "required Sequence attribute missing in ReadRunOnceCommands: " + elementName.Str());
            }
        }
        else
        {
            SCX_LOGERROR(g_logHandle, "invalid tag encountered in ReadRunOnceCommands: " + elementName.Str());
            throw OSSpecializationParserException("unexpected tag encountered: " + elementName.Str());
        }
    }
}

void OSSpecializationReader::OSConfiguration::ReadRootUser(const XElementPtr& xElementPtr)
{
    XElementList usersElementList;
    xElementPtr->GetChildren(usersElementList);
    m_root.IsValid() = false;

	for (XElementList::const_iterator usersElementIter = usersElementList.begin();
		usersElementIter != usersElementList.end();
		usersElementIter++)
	{
		XElementPtr userNameElement;
		XElementPtr xElementPtr = *usersElementIter;

        if (xElementPtr->GetName().Str() != sUser)
        {
            SCX_LOGERROR(g_logHandle, "Expecting tag value \"User\", got: " + xElementPtr->GetName().Str());
            throw OSSpecializationParserException("unexpected tag encountered: " + xElementPtr->GetName().Str());
        }

		if (xElementPtr->GetChild(sUserName, userNameElement))
		{
			if (userNameElement->GetContent() == sRoot)
			{
				m_root.IsValid() = true;
				m_root.inner().Read(xElementPtr);
			}
		}
        else
        {
            SCX_LOGERROR(
                g_logHandle,
                L"unexpected tag encountered when looking for value \"Name\"");
            throw OSSpecializationParserException("unexpected tag encountered when looking for value \"Name\"");
        }
	}
}

void OSSpecializationReader::VNetAdapter::Read(const XElementPtr& vNetAdapterElementPtr)
{
    XElementList xElementList;
    vNetAdapterElementPtr->GetChildren(xElementList);

    for (XElementList::const_iterator xElementListIter = xElementList.begin();
        xElementListIter != xElementList.end();
        xElementListIter++)
    {
        XElementPtr xElementPtr = *xElementListIter;
        Utf8String elementName = xElementPtr->GetName();

        if (elementName == sMACAddress)
        {
            m_macAddress = xElementPtr->GetContent();

            SCX_LOGTRACE(g_logHandle, "MAC Address read as: " + xElementPtr->GetContent().Str());
        }
        else if (elementName == sIPV4Property)
        {
            m_ipV4.IsValid() = true;
            m_ipV4.inner().Read(xElementPtr);

            SCX_LOGTRACE(g_logHandle, "Read of IP V4 address complete.");
        }
        else if (elementName == sIPV6Property)
        {
            m_ipV6.IsValid() = true;
            m_ipV6.inner().Read(xElementPtr);

            SCX_LOGTRACE(g_logHandle, "Read of IP V6 address complete.");
        }
        else if (elementName == sGateways)
        {
            ReadGateways(xElementPtr);

            SCX_LOGTRACE(g_logHandle, "Read of Gateways complete.");
        }
        else if (elementName == sNameServers)
        {
            XElementList nameServerElementList;
            xElementPtr->GetChildren(nameServerElementList);
            NameServers.clear();

            for (XElementList::const_iterator nameServerElementIter = nameServerElementList.begin();
                 nameServerElementIter != nameServerElementList.end();
                 nameServerElementIter++)
            {
                xElementPtr = *nameServerElementIter;

                Utf8String elementName = xElementPtr->GetName();

                if (elementName == sNameServer)
                {
                    NameServers.push_back(xElementPtr->GetContent());

                    SCX_LOGTRACE(g_logHandle, "Name Server read as: " + xElementPtr->GetContent().Str());
                }
                else
                {
                    SCX_LOGERROR(g_logHandle, "invalid tag encountered while reading NameServers: " + elementName.Str());
                    throw OSSpecializationParserException("unexpected tag encountered: " + elementName.Str());
                }
            }
        }
        else if (elementName == sDNSSearchSuffixes)
        {
            XElementList dnsSearchSuffixElementList;
            xElementPtr->GetChildren(dnsSearchSuffixElementList);
            DNSSearchSuffixes.clear();

            for (XElementList::const_iterator dnsSearchSuffixElementIter = dnsSearchSuffixElementList.begin();
                 dnsSearchSuffixElementIter != dnsSearchSuffixElementList.end();
                 dnsSearchSuffixElementIter++)
            {
                xElementPtr = *dnsSearchSuffixElementIter;

                Utf8String elementName = xElementPtr->GetName();

                if (elementName == sDNSSearchSuffix)
                {
                    DNSSearchSuffixes.push_back(xElementPtr->GetContent());

                    SCX_LOGTRACE(g_logHandle, "DNS Search Suffix read as: " + xElementPtr->GetContent().Str());
                }
                else
                {
                    SCX_LOGERROR(g_logHandle, "invalid tag encountered while reading DNSSearchSuffixes: " + elementName.Str());
                    throw OSSpecializationParserException("unexpected tag encountered: " + elementName.Str());
                }
            }
        }
        else
        {
            SCX_LOGERROR(g_logHandle, "invalid tag encountered in ReadRunOnceCommands: " + elementName.Str());
            throw OSSpecializationParserException("unexpected tag encountered: " + elementName.Str());
        }
    }
}

void OSSpecializationReader::VNetAdapter::ReadGateways(const XElementPtr& gatewaysElementPtr)
{
    XElementList gatewaysElementList;
    gatewaysElementPtr->GetChildren(gatewaysElementList);
    Gateways.clear();

    for (XElementList::const_iterator gatewaysElementIter = gatewaysElementList.begin();
         gatewaysElementIter != gatewaysElementList.end();
         gatewaysElementIter++)
    {
        XElementPtr xElementPtr = *gatewaysElementIter;

        Utf8String elementName = xElementPtr->GetName();

        if (elementName == sGateway)
        {
            Gateway val;
            val.Read(xElementPtr);
            Gateways.push_back(val);

            SCX_LOGTRACE(g_logHandle, "Read of Gateway complete.");
        }
        else
        {
            SCX_LOGERROR(g_logHandle, "invalid tag encountered within ReadGateways: " + elementName.Str());
            throw OSSpecializationParserException("unexpected tag encountered: " + elementName.Str());
        }
    }
}

void OSSpecializationReader::User::Read(const XElementPtr& userElementPtr)
{
    XElementList xElementList;
    userElementPtr->GetChildren(xElementList);

    for (XElementList::const_iterator xElementListIter = xElementList.begin();
        xElementListIter != xElementList.end();
        xElementListIter++)
    {
        XElementPtr xElementPtr = *xElementListIter;
        Utf8String elementName = xElementPtr->GetName();

        if (elementName == sUserName)
        {
            m_userName = xElementPtr->GetContent();

            SCX_LOGTRACE(g_logHandle, "User Name read as: " + xElementPtr->GetContent().Str());
        }
        else if (elementName == sPassword)
        {
            m_password = xElementPtr->GetContent();

            SCX_LOGTRACE(g_logHandle, "Password read.");
        }
        else if (elementName == sSSHKey)
        {
            m_sshKey = xElementPtr->GetContent();

            SCX_LOGTRACE(g_logHandle, "SSH Key read.");
        }
	    else if (elementName == sUID)
	    {
		    m_UID = xElementPtr->GetContent();

		    SCX_LOGTRACE(g_logHandle, "UID read as: " + xElementPtr->GetContent().Str());
	    }
	    else if (elementName == sGroupID)
	    {
		    m_groupID = xElementPtr->GetContent();

		    SCX_LOGTRACE(g_logHandle, "Group ID read as: " + xElementPtr->GetContent().Str());
	    }
	    else if (elementName == sPrimaryGroup)
	    {
		    m_primaryGroup = xElementPtr->GetContent();

		    SCX_LOGTRACE(g_logHandle, "Primary Group read as: " + xElementPtr->GetContent().Str());
	    }
        else
        {
            SCX_LOGERROR(g_logHandle, "invalid tag encountered within User::Read: " + elementName.Str());
            throw OSSpecializationParserException("unexpected tag encountered: " + elementName.Str());
        }
    }
}

void OSSpecializationReader::Gateway::Read(const XElementPtr& gatewayPtr)
{
    XElementList xElementList;
    gatewayPtr->GetChildren(xElementList);

    for (XElementList::const_iterator xElementListIter = xElementList.begin();
        xElementListIter != xElementList.end();
        xElementListIter++)
    {
        XElementPtr xElementPtr = *xElementListIter;
        Utf8String elementName = xElementPtr->GetName();

        if (elementName == sAddress)
        {
            m_address = xElementPtr->GetContent();

            SCX_LOGTRACE(g_logHandle, "Gateway Address read as: " + xElementPtr->GetContent().Str());
        }
        else if (elementName == sMetric)
        {
            m_metric = xElementPtr->GetContent();

            SCX_LOGTRACE(g_logHandle, "Gateway Metric read as: " + xElementPtr->GetContent().Str());
        }
        else
        {
            SCX_LOGERROR(g_logHandle, "invalid tag encountered within Gateway::Read: " + elementName.Str());
            throw OSSpecializationParserException("unexpected tag encountered: " + elementName.Str());
        }
    }
}

void OSSpecializationReader::NetworkProperties::Read(const XElementPtr& netPropElementPtr)
{    
    Utf8String addressType;
    if (netPropElementPtr->GetAttributeValue(sAddressType, addressType))
    {
        if (addressType == sSTATIC)
        {
            m_isStatic = true;

            SCX_LOGTRACE(g_logHandle, "IP Address is STATIC");

            XElementPtr xElementPtr;
            if (netPropElementPtr->GetChild(sStaticIP, xElementPtr))
            {
                XElementPtr val;
                if (xElementPtr->GetChild(sAddress, val))
                {
                    m_staticIP = val->GetContent();

                    SCX_LOGTRACE(g_logHandle, "Static IP address read as: " + val->GetContent().Str());
                }
            }
        }
        else if (addressType == sDHCP)
        {
            m_isStatic = false;

            SCX_LOGTRACE(g_logHandle, "IP Address is DHCP");
        }
        else
        {
            SCX_LOGERROR(g_logHandle, "invalid address type value within NetworkProperties::Read :" + addressType.Str());
            throw OSSpecializationParserException("unexpected attribute value encountered: " + addressType.Str());
        }
    }
}
