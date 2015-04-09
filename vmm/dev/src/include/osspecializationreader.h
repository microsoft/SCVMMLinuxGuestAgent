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
        \file        osspecializationreader.h

        \brief       Parse specialization file

        \date        01-13-12 11:04:50

*/
/*----------------------------------------------------------------------------*/
#ifndef OSSPECIALIZATIONREADER_H
#define OSSPECIALIZATIONREADER_H

#include <vector>
#include <map>
#include <string>

#include <util/XElement.h>
#include <util/Unicode.h>

namespace VMM
{
    namespace GuestAgent
    {
        namespace SpecializationReader
        {
            typedef std::vector<SCX::Util::Utf8String> stringArray;

            /*----------------------------------------------------------------------------*/
            /**
                wrapper class Optional, used to implement getter which can fail if the value
                is unavailable (indicated by m_isValid = false)
            */
            template <typename T> class Optional
            {
            public:
                /*----------------------------------------------------------------------------*/
                /**
                    Optional class constructor
                */
                Optional()
                {
                    m_isValid = false;
                }

                /*----------------------------------------------------------------------------*/
                /**
                    is the inner value valid
                */
                inline bool& IsValid() { return m_isValid; }

                /*----------------------------------------------------------------------------*/
                /**
                    return inner value if valid
                */
                bool TryGet(T& val) const
                {
                    if (m_isValid)
                    {
                        val = m_val;
                    }

                    return m_isValid;
                }

                /*----------------------------------------------------------------------------*/
                /**
                    reference to inner value
                */
                inline T& inner()
                {
                    return m_val;
                }

                /*----------------------------------------------------------------------------*/
                /**
                    assignment operator
                */
                Optional<T>& operator = (const T& val)
                {
                    m_val = val;
                    m_isValid = true;
                    return *this;
                }

            protected:
                bool m_isValid;
                T m_val;
            };

            typedef Optional<SCX::Util::Utf8String> OptionalString;

            /*----------------------------------------------------------------------------*/
            /**
                class which reads the VMM OS Specialization XML, defining nested 
                classes for each element in the XSD schema
            */
            class OSSpecializationReader : public SCXCoreLib::SCXSingleton<OSSpecializationReader>
            {
                /** Making the class a friend to enable destruction */
                friend class SCXCoreLib::SCXSingleton<OSSpecializationReader>;

                public:

                /*----------------------------------------------------------------------------*/
                /**
                    Load specialization from XML
                */
                virtual void LoadXML(const SCX::Util::Utf8String& xmlString);

                public:
                /*----------------------------------------------------------------------------*/
                /**
                    Gateway class
                */
                class Gateway
                {
                public:
                    /*----------------------------------------------------------------------------*/
                    /**
                        read from node tree
                    */
                    void Read(const SCX::Util::Xml::XElementPtr& ptr);
                    /*----------------------------------------------------------------------------*/
                    /**
                        get gateway address
                    */
                    inline bool GetAddress(SCX::Util::Utf8String& val) const { return m_address.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        get metric (cost?)
                    */
                    inline bool GetMetric(SCX::Util::Utf8String& val) const { return m_metric.TryGet(val); }

                private:
                    OptionalString m_address;
                    OptionalString m_metric;
                };

                /*----------------------------------------------------------------------------*/
                /**
                    NetworkProperties class
                */
                class NetworkProperties
                {
                public:

                    /*----------------------------------------------------------------------------*/
                    /**
                        read from node tree
                    */
                    void Read(const SCX::Util::Xml::XElementPtr& ptr);
                    /*----------------------------------------------------------------------------*/
                    /**
                        return static IP if exists
                    */
                    inline bool GetStaticIP(SCX::Util::Utf8String& val) const { return m_staticIP.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        is address static IP
                    */
                    bool IsStatic() const { return m_isStatic; }

                private:
                    OptionalString m_staticIP;
                    bool m_isStatic;
                };

                /*----------------------------------------------------------------------------*/
                /**
                    VNetAdapter class
                */
                class VNetAdapter
                {
                public:
                    /*----------------------------------------------------------------------------*/
                    /**
                        read from node tree
                    */
                    void Read(const SCX::Util::Xml::XElementPtr& ptr);
                    /*----------------------------------------------------------------------------*/
                    /**
                        return MAC Address if exists
                    */
                    inline bool GetMACAddress(SCX::Util::Utf8String& val) const { return m_macAddress.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return IP v4 address if exists
                    */
                    inline bool GetIPV4(NetworkProperties& val) const { return m_ipV4.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return IP v6 address if exists
                    */
                    inline bool GetIPV6(NetworkProperties& val) const { return m_ipV6.TryGet(val); }

                    /*----------------------------------------------------------------------------*/
                    /**
                        list of Gateways
                    */
                    std::vector<Gateway>                 Gateways;
                    /*----------------------------------------------------------------------------*/
                    /**
                        list of Name Servers
                    */
                    std::vector<SCX::Util::Utf8String> NameServers;
                    /*----------------------------------------------------------------------------*/
                    /**
                        list of DNS Search Suffixes
                    */
                    std::vector<SCX::Util::Utf8String> DNSSearchSuffixes;

                private:
                    void ReadGateways(const SCX::Util::Xml::XElementPtr& ptr);

                    OptionalString                m_macAddress;
                    Optional<NetworkProperties>   m_ipV4;
                    Optional<NetworkProperties>   m_ipV6;
                };

                /*----------------------------------------------------------------------------*/
                /**
                    User class
                */
                class User
                {
                public:
                    /*----------------------------------------------------------------------------*/
                    /**
                        read from node tree
                    */
                    void Read(const SCX::Util::Xml::XElementPtr& xElementPtr);
                    /*----------------------------------------------------------------------------*/
                    /**
                        return user name if exists
                    */
                    inline bool GetUserName(SCX::Util::Utf8String& val) const { return m_userName.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return Password if exists
                    */
                    inline bool GetPassword(SCX::Util::Utf8String& val) const { return m_password.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return SSH Key if exists
                    */
                    inline bool GetSSHKey(SCX::Util::Utf8String& val) const { return m_sshKey.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return UID if exists
                    */
                    inline bool GetUID(SCX::Util::Utf8String& val) const { return m_UID.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return Group ID if exists
                    */
                    inline bool GetGroupID(SCX::Util::Utf8String& val) const { return m_groupID.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return Primary Group if exists
                    */
                    inline bool GetPrimaryGroup(SCX::Util::Utf8String& val) const { return m_primaryGroup.TryGet(val); }

                private:
                    OptionalString m_userName;
                    OptionalString m_password;
                    OptionalString m_sshKey;
                    OptionalString m_UID;
                    OptionalString m_groupID;
                    OptionalString m_primaryGroup;
                };

                /*----------------------------------------------------------------------------*/
                /**
                    OSConfiguration class
                */
                class OSConfiguration
                {
                public:
                    /*----------------------------------------------------------------------------*/
                    /**
                        read from node tree
                    */
                    void Read(const SCX::Util::Xml::XElementPtr& xElementPtr);

                    /*----------------------------------------------------------------------------*/
                    /**
                        return Host Name if exists
                    */
                    inline bool GetHostName(SCX::Util::Utf8String& val) const { return m_hostName.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return Domain Name if exists
                    */
                    inline bool GetDomainName(SCX::Util::Utf8String& val) const { return m_domainName.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return Time Zone if exists
                    */
                    inline bool GetTimeZone(int& val) const { return m_timeZone.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return Root user if exists
                    */
                    inline bool GetRoot(User& val) const { return m_root.TryGet(val); }

                    /*----------------------------------------------------------------------------*/
                    /**
                        list of Run Once commands
                    */
                    std::map<int, SCX::Util::Utf8String> RunOnceCommands;
                    /*----------------------------------------------------------------------------*/
                    /**
                        list of VNet adapters
                    */
                    std::vector<VNetAdapter> VNetAdapters;
                private:
                    void ReadVNetAdapters(const SCX::Util::Xml::XElementPtr& vNetAdaptersElementPtr);
                    void ReadRunOnceCommands(const SCX::Util::Xml::XElementPtr& vNetAdaptersElementPtr);
                    void ReadRootUser(const SCX::Util::Xml::XElementPtr& vNetAdaptersElementPtr);

                    OptionalString    m_hostName;
                    OptionalString    m_domainName;
                    Optional<int>     m_timeZone;
                    Optional<User>    m_root;
                };

                /*----------------------------------------------------------------------------*/
                /**
                    LinuxOSSpecialization class
                */
                class LinuxOSSpecialization
                {
                public:
                    /*----------------------------------------------------------------------------*/
                    /**
                        read from node tree
                    */
                    void Read(const SCX::Util::Xml::XElementPtr& xElementPtr);
                    /*----------------------------------------------------------------------------*/
                    /**
                        return OS Configuration if exists
                    */
                    inline bool GetOSConfiguration(OSConfiguration& val) const { return m_osConfiguration.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return Schema Version if exists
                    */
                    inline bool GetSchemaVersion(SCX::Util::Utf8String& val) const { return m_schemaVersion.TryGet(val); }
                    /*----------------------------------------------------------------------------*/
                    /**
                        return Agent Version if exists
                    */
                    inline bool GetAgentVersion(SCX::Util::Utf8String& val) const { return m_agentVersion.TryGet(val); }

                private:
                    Optional<OSConfiguration>    m_osConfiguration;
                    OptionalString               m_schemaVersion;
                    OptionalString               m_agentVersion;
                };

                /*----------------------------------------------------------------------------*/
                /**
                    return LinuxOSSpecialization if exists
                */
                bool GetLinuxOSSpecialization(LinuxOSSpecialization& val);

                protected:
                SCX::Util::Xml::XElementPtr  m_pXElementRoot;

                private:

                /*----------------------------------------------------------------------------*/
                /**
                    OSSpecializationReader constructor
                */
                OSSpecializationReader();

                /*----------------------------------------------------------------------------*/
                /**
                    load LinuxOSSpecialization object from xml root element 
                */
                void Load();

                SCX::Util::Utf8String         m_xmlString;
                Optional<LinuxOSSpecialization> m_specialization;

                /*----------------------------------------------------------------------------*/
                /**
                    xsd schema tag values
                */
                static const std::string sLinuxOSSpecialization;
                static const std::string sAgentVersion;
                static const std::string sSchemaVersion;
                static const std::string sOSConfiguration;
                static const std::string sHostName;
                static const std::string sDomainName;
                static const std::string sTimeZone;
                static const std::string sVNetAdapters;
                static const std::string sRunOnceCommands;
                static const std::string sRunOnceCommand;
                static const std::string sCommandSequence;
                static const std::string sVNetAdapter;
                static const std::string sMACAddress;
                static const std::string sAddressType;
                static const std::string sGateways;
                static const std::string sGateway;
                static const std::string sAddress;
                static const std::string sSTATIC;
                static const std::string sDHCP;
                static const std::string sIPV4Property;
                static const std::string sIPV6Property;
                static const std::string sStaticIP;
                static const std::string sMetric;
                static const std::string sNameServers;
                static const std::string sNameServer;
                static const std::string sUsers;
                static const std::string sUser;
                static const std::string sRoot;
                static const std::string sUserName;
                static const std::string sPassword;
                static const std::string sSSHKey;
                static const std::string sUID;
                static const std::string sGroupID;
                static const std::string sPrimaryGroup;
                static const std::string sDNSSearchSuffixes;
                static const std::string sDNSSearchSuffix;

			public:
				virtual /*dtor*/ ~OSSpecializationReader () {}
             }; // class OSSpecializationReader
         } // namespace SpecializationReader
    } // namespace GuestAgent
} // namespace VMM

#endif // OSSPECIALIZATIONREADER_H
