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
   \file        argumentmanager.h

   \brief       Creates and maintains a list of arguments/environemnt variables
   
   \date        07-03-2012 07:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/

#ifndef ARGUMENTMANAGER_H
#define ARGUMENTMANAGER_H


#include <scxcorelib/scxsingleton.h>


namespace SCXCoreLib
{

// forward declaration
class SCXLogHandle;

}

namespace VMM
{
namespace GuestAgent
{
namespace Utilities
{


/// Parses and stores the values from the command line
class ArgumentManager : public SCXCoreLib::SCXSingleton<ArgumentManager>
{
public:
    typedef SCXCoreLib::SCXLogHandle Logger_t;

    /*ctor*/ ArgumentManager();
            
    virtual /*dtor*/ ~ArgumentManager();

    /// Parses the command line
    ///
    /// @param argc number of command line tokens
    /// @param argv the command line tokens
    /// @return EXIT_SUCCESS upon success
    ///         EXIT_FAILURE otherwise
    int LoadArgs(int const argc, char const* const*argv, Logger_t& logger);

    /// @return the path to use
    std::string const& GetVMMHome() const;
    std::string const& GetConfigFilename() const;

private:
    std::string m_vmmHome;
    std::string m_configFilename;
};


inline std::string const&
ArgumentManager::GetVMMHome() const
{
    return m_vmmHome;
}

inline std::string const&
ArgumentManager::GetConfigFilename() const
{
    return m_configFilename;
}


} // namespace Utilities
} // namespace GuestAgent
} // namespace VMM


#endif // ARGUMENTMANAGER_H

