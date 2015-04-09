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

    \brief       Contains the definition of a simple log mediator class.

    \date        2008-07-18 11:44:22

*/
/*----------------------------------------------------------------------------*/
#ifndef SCXLOGMEDIATORSIMPLE_H
#define SCXLOGMEDIATORSIMPLE_H

#include "scxlogmediator.h"
#include "scxlogbackend.h"
#include <scxcorelib/scxhandle.h>
#include <set>

namespace SCXCoreLib
{
    /*----------------------------------------------------------------------------*/
    /**
        Simple implementation of the log mediator interface.
        This class implements a synchronous solution causing the calling thread
        to wait for logging to complete.
    */
    class SCXLogMediatorSimple : public SCXLogMediator
    {
    private:
        /*----------------------------------------------------------------------------*/
        /**
            A strict ordering is needed by the set template.
        */
        struct HandleCompare
        {
            /*----------------------------------------------------------------------------*/
            /**
                Compares two scxhandles.
                It actually compares the addresses of the data that is pointed to by the
                handles. This is of course random, but the exact order is not important in
                this implementation. Only that there _is_ a strict order.
                \param[in] h1 First handle to compare.
                \param[in] h2 Second handle to compare.
                \returns true if h1 is less than h2.
            */
            bool operator()(const SCXHandle<SCXLogItemConsumerIf> h1, const SCXHandle<SCXLogItemConsumerIf> h2) const
            {
                return h1.GetData() < h2.GetData();
            }
        };

        typedef std::set<SCXHandle<SCXLogItemConsumerIf>, HandleCompare> ConsumerSet; //!< Defines a set of consumers.

    public:
        SCXLogMediatorSimple();
        explicit SCXLogMediatorSimple(const SCXThreadLockHandle& lock);

        virtual void LogThisItem(const SCXLogItem& item);
        virtual SCXLogSeverity GetEffectiveSeverity(const std::wstring& module) const;
        virtual bool RegisterConsumer(SCXHandle<SCXLogItemConsumerIf> consumer);
        virtual bool DeRegisterConsumer(SCXHandle<SCXLogItemConsumerIf> consumer);
        virtual void HandleLogRotate();

        const std::wstring DumpString() const;
    private:
        SCXThreadLockHandle m_lock; //!< Thread lock synchronizing access to internal data.
        ConsumerSet m_Consumers; //!< Set of currently subscribed consumers.
    };
}

#endif /* SCXLOGMEDIATORSIMPLE_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
