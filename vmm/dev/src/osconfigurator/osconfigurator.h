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
   \file        osconfigurator.h

   \brief       Abstract Base OSConfigurator class
                
   \date        06-24-2012 19:46:03

   \author      Jayashree Singanallur (jayasing)
   
*/
/*----------------------------------------------------------------------------*/

#ifndef OSCONFIGURATOR_H
#define OSCONFIGURATOR_H

#include <osconfiguratorvisitor.h>

namespace VMM
{

    namespace GuestAgent
    {

        namespace OSConfigurator
        {

            class OSConfigurator
            {

            public:


                /*----------------------------------------------------------------------------*/
                /**
                   
                   Virtual Destructor for OSConfigurator

                */
                virtual ~OSConfigurator() 
                {}

                /*----------------------------------------------------------------------------*/
                /**
                   Accept function for the visitor - pure virtual function

                   \param  visitor    Visitor base class
                */
                virtual void Accept(VMM::GuestAgent::OSConfigurator::Visitor& v) = 0;

            }; // End of OSConfigurator class

        } // End of OSConfigurator namespace

    } // End of GuestAgent namespace

} // End of VMM namespace

#endif /* OSCONFIGURATOR_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
