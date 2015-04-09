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
    \file        argumentmanager.cpp

    \brief       Contains all the arguments loaded as environment variables

    \date        07-03-2012 12:53:16

    \author      Jayashree Singanallur (jayasing)

*/
/*----------------------------------------------------------------------------*/
#include <argumentmanager.h>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <scxcorelib/scxlog.h>

using VMM::GuestAgent::Utilities::ArgumentManager;


namespace
{

char const VMM_HOME_ENV_VAR[] = "SCVMM_HOME";
char const VMM_HOME_DEFAULT[] = "/opt/microsoft/scvmmguestagent/";
char const CLI_CONFIG_FILENAME[] = "mntpath=";
char const USAGE[] = "scvmmguestagent [mntpath=<PATH>]";

}


/*ctor*/
ArgumentManager::ArgumentManager()
  : m_vmmHome(VMM_HOME_DEFAULT)
  , m_configFilename()
{
    // empty
}

/*dtor*/
ArgumentManager::~ArgumentManager()
{
    // empty
}

int
ArgumentManager::LoadArgs(
    int const argc,
    char const* const* argv,
    Logger_t& logger)
{
    int result = 1 == argc ? EXIT_SUCCESS : EXIT_FAILURE;

    char const* const vmmHomeEnv = getenv(VMM_HOME_ENV_VAR);
    if (NULL != vmmHomeEnv)
    {
        m_vmmHome = vmmHomeEnv;
    }

    if (2 == argc &&
        0 == strncmp (CLI_CONFIG_FILENAME, argv[1],
                      strlen(CLI_CONFIG_FILENAME)))
    {
        m_configFilename = argv[1] + strlen(CLI_CONFIG_FILENAME);
        result = EXIT_SUCCESS;
    }

    if (EXIT_FAILURE == result)
    {
        std::ostringstream strm;
        strm << "Error parsing commandline: ";
        if (2 == argc &&
            0 != strncmp(CLI_CONFIG_FILENAME, argv[1],
                         strlen(CLI_CONFIG_FILENAME)))
        {
            strm << "encountered unknown command \"" << argv[1];
        }
        else
        {
            strm << "invalid args.";
        }
        strm << std::endl << USAGE;
        SCX_LOGERROR(logger, strm.str ());
    }
    return result;
}
