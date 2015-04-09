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

   \brief       Defines the dependency interface for ComputerSystem data retrieval. 

   \date        11-04-18 10:00:00

*/
/*----------------------------------------------------------------------------*/
#ifndef COMPUTERSYSTEMDEPENDENCIES_H
#define COMPUTERSYSTEMDEPENDENCIES_H

#include <scxcorelib/scxlog.h>
#include <sys/types.h>
#include <scxcorelib/scxfile.h>
#include <scxcorelib/scxfilepath.h>
#include <vector>

#define FILTERLINUX defined(linux)

#if FILTERLINUX || defined(sun) || defined(hpux) || defined(aix)
#include <utmpx.h>
#endif

#if defined(sun)
/* User info and system run level  */
#include <sys/systeminfo.h>
/* System time  */
#include <time.h>
#endif

using std::vector;

namespace SCXSystemLib
{

#if defined(sun)
    /* Sysinfo value string length  */
    const int cSysinfoValueLength = 257;
    const std::wstring cPowerconfPath = L"/etc/power.conf";
#endif

    /*----------------------------------------------------------------------------*/
    /**
       Class representing all external dependencies from the ComputerSystem PAL.

    */
    class ComputerSystemDependencies
    {
    public:
        /*----------------------------------------------------------------------------*/
        /**
           Constructor
        */
        ComputerSystemDependencies();

        /*----------------------------------------------------------------------------*/
        /**
           Virtual destructor
        */
        virtual ~ComputerSystemDependencies();

        /*----------------------------------------------------------------------------*/
        /**
           Init running context.
        */
        void Init();

        /*----------------------------------------------------------------------------*/
        /**
           Clean up running context.
        */
        void CleanUp();

        public:
#if FILTERLINUX
        /*----------------------------------------------------------------------------*/
        /**
           Get cpu information from system file. 
        */
        virtual const vector<std::wstring>& GetCpuInfo();
#endif

/*----------------------------------------------------------------------------*/
        /**
        Get run-level of system as attr "BootupState"
    
        \param      value - the extracted value if there is one
        Return system run-level.
        */
        virtual bool GetSystemRunLevel(std::wstring &runLevel) const;

#if defined(sun)

        /*----------------------------------------------------------------------------*/
        /**
        Get system information by systeminfo() function
    
        \param      value - the extracted value if there is one
        Return  Greater than 0  mains content is OK. Less than 0 mains value is empty.
        */
        virtual int GetSystemInfo(int contentType, std::wstring &content) const;


        /*----------------------------------------------------------------------------*/
        /**
        Get time zone of system
    
        \param      value - the extracted value if there is one
        Return system daylight value of time zone.
        */
        virtual bool GetSystemTimeZone(bool &dayLightFlag) const;

        /*----------------------------------------------------------------------------*/
        /**
        Get "/etc/power.conf" file content about power management configuration.
    
        \param      value - the extracted value if there is one
        Return system get "/etc/power.conf" content ok or fail.
        */
        virtual bool GetPowerCfg(std::vector<std::wstring>& allLines);
#endif

    private:
        SCXCoreLib::SCXLogHandle m_log;                 //!< log handle
#if FILTERLINUX || defined(aix)
        SCXCoreLib::SCXFilePath m_cpuInfoPath; //!< path to CPU Information file.
        vector<std::wstring> m_cpuInfo;    //!< The content of CPUInfo. 
#endif
    };
}

#endif /* COMPUTERSYSTEMDEPENDENCIES_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
