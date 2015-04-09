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

    \brief       Contains the definition of the log mediator interface.

    \date        2008-07-24 12:10:16

*/
/*----------------------------------------------------------------------------*/
#ifndef SCXLOGMEDIATOR_H
#define SCXLOGMEDIATOR_H

#include <scxcorelib/scxlog.h>

namespace SCXCoreLib
{
    /*----------------------------------------------------------------------------*/
    /**
        A mediator is a log item consumer that enables other log item consumers
        to register themselves to recieve all log items that the mediator gets.
        
        To implement the interface you also need to implement all methods of
        SCXLogItemConsumerIf which this iterface inherits from.
    */
    class SCXLogMediator : public SCXLogItemConsumerIf
    {
    public:
        /*----------------------------------------------------------------------------*/
        /**
            Register an SCXLogItemConsumer as a new receiver of log messages. It will
            recieve all items that were logged through the LogThisItem interface.
            
            \param[in] consumer SCXLogItemConsumerIf to register as consumer.
            \returns False if consumer can't be added.
        */
        virtual bool RegisterConsumer(SCXHandle<SCXLogItemConsumerIf> consumer) = 0;

        /*----------------------------------------------------------------------------*/
        /**
            A registered consumer that is no longer interested in receiving SCXLogItems
            can de-register itself through this interface.
            
            \param[in] consumer SCXLogItemConsumerIf to de-register.
            \returns False if consumer was not previously registered.
        */
        virtual bool DeRegisterConsumer(SCXHandle<SCXLogItemConsumerIf> consumer) = 0;

    };
}

#endif /* SCXLOGMEDIATORSIMPLE_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
