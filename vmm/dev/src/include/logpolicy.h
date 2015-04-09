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
    \file        logpolicy.h

    \brief       Contains the default implementation of the log policy factory for VMM

    \date        04-03-2012 16:53:16
    
    \author      Jayashree Singanallur (jayasing)

*/
/*----------------------------------------------------------------------------*/
#ifndef LOGPOLICY_H
#define LOGPOLICY_H

#include <iostream>

#include <scxcorelib/scxlogpolicy.h>
#include <scxcorelib/scxfilepath.h>

#include <argumentmanager.h>

class SCXVMMLogPolicy : public SCXCoreLib::SCXLogPolicy
{
    
public:
    
    /*----------------------------------------------------------------------------*/
    /**
       Constructor for SCXVMMLogPolicy file
       
    */
    SCXVMMLogPolicy() 
      : c_VMM_LOG_FILE("scvmm.log"), 
        c_VMM_CONFIG_FILE("scvmm.conf"),
        c_VMM_CONFIG_SUBDIR_ETC("etc"),
        c_DEFAULT_LOG_DIR("/var/opt/microsoft/scvmmguestagent/log")
        {
            
            // Get VMM_HOME from environment
            m_vmmInstallHome = VMM::GuestAgent::Utilities::ArgumentManager::Instance().GetVMMHome();

            if (m_vmmLogHome.empty())
            {
                m_vmmLogHome = c_DEFAULT_LOG_DIR;
            }
    }
    
    /*----------------------------------------------------------------------------*/
    /**
       Get the configuration file
       
    */
    virtual SCXCoreLib::SCXFilePath GetConfigFileName() const
    {
        
        std::wstring configurationFile =
            SCXCoreLib::StrFromMultibyte(m_vmmInstallHome) +
            SCXCoreLib::SCXFilePath::GetFolderSeparator() +
            SCXCoreLib::StrFromMultibyte(c_VMM_CONFIG_SUBDIR_ETC) +
            SCXCoreLib::SCXFilePath::GetFolderSeparator() +
            SCXCoreLib::StrFromMultibyte(c_VMM_CONFIG_FILE);
        
        std::cout << "Logging Configuration File for SC VMM::" 
                  << SCXCoreLib::StrToMultibyte(configurationFile) 
                  << std::endl;
                    
        return SCXCoreLib::SCXFilePath(configurationFile);
    }
    
    /*----------------------------------------------------------------------------*/
    /**
       If no config is specified, then log output will be written to the file specified 
       by this method.
       
       \returns Path to the default log file.
    */
    virtual SCXCoreLib::SCXFilePath GetDefaultLogFileName() const
    {
        
        std::wstring logFile = SCXCoreLib::StrFromMultibyte(m_vmmLogHome) + 
            SCXCoreLib::SCXFilePath::GetFolderSeparator() +
            SCXCoreLib::StrFromMultibyte(c_VMM_LOG_FILE);
        
        std::cout << "Log file location for SC VMM::" 
                  << SCXCoreLib::StrToMultibyte(logFile) 
                  << std::endl;
        
        return SCXCoreLib::SCXFilePath(logFile);
    }
    
    /*----------------------------------------------------------------------------*/
    /**
       Default severity threshold for VMM guest agent
       
       \returns Path to the default log file.
    */
    virtual SCXCoreLib::SCXLogSeverity GetDefaultSeverityThreshold() const                      
    {      
        return SCXCoreLib::eTrace;
    }      
    
private:
    
    // Data Members    

    /** String representing vmm home */
    std::string                  m_vmmInstallHome;
    std::string                  m_vmmLogHome;

    // Const data members
    const std::string c_VMM_LOG_FILE;
    const std::string c_VMM_CONFIG_FILE;
    const std::string c_VMM_CONFIG_SUBDIR_ETC;
    const std::string c_DEFAULT_LOG_DIR;
};

/*----------------------------------------------------------------------------*/
/**
   Log policy factory for SCX VMM
   
   \returns The log policy object.
*/
SCXCoreLib::SCXHandle<SCXCoreLib::SCXLogPolicy> CustomLogPolicyFactory()
{
    return SCXCoreLib::SCXHandle<SCXCoreLib::SCXLogPolicy>(new SCXVMMLogPolicy());
}

#endif /* SCXVMMLOGPOLICY_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
