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

    \brief       Contains the definition of the Singleton Template.

    \date        2007-06-19 08:50:28

*/
/*----------------------------------------------------------------------------*/
#ifndef SCXSINGLETON_H
#define SCXSINGLETON_H

#include <scxcorelib/scxexception.h>
#include <scxcorelib/scxthreadlock.h>
#include <scxcorelib/scxhandle.h>

namespace SCXCoreLib
{
    /*----------------------------------------------------------------------------*/
    /**
        Provides singleton functionality.
    
        \date        <2007-06-19 08:50:28>
        
        Use this class when a singleton is needed.

        To make class A a singleton, let it inherit from SCXSingleton<A>.
        Make Singleton<A> a friend of A, and make the constructors private.

        \ex
        \code
        class A : public SCXSingleton<A>
        {
            friend class SCXSingleton<A>;
                public:
                    std::wstring DumpString() const;
        private:
            A();
        };
        \endcode
    */
    template<class T> class SCXSingleton
    {
    public:
        /*----------------------------------------------------------------------------*/
        /**
            Returns a reference to the singleton instance.
           
            If the instance is not yet created, it first creates it.
           
        */
        static T& Instance()
        {
            if (0 == s_lockHandle.GetData())
            {
                throw SCXInternalErrorException(L"Tried to get a singleton instance before static initialization was completed.", SCXSRCLOCATION);
            }

            SCXThreadLock lock(*s_lockHandle, true);
            
            if (0 == s_instance.GetData())
            {
                s_instance = new T();
            }

            return *s_instance;
        }

    protected:
        /** Only instantiated by subclassing. */
        SCXSingleton() {}
        /** Only instantiated by subclassing. */
        SCXSingleton(const SCXSingleton&) {}
        /** Only copied by subclassing. */
        SCXSingleton& operator=(const SCXSingleton&) { return *this; }

    private:
        static SCXCoreLib::SCXHandle<T> s_instance; //!< Handle to the singleton instance.
        static SCXCoreLib::SCXHandle< SCXThreadLockHandle > s_lockHandle; //!< Used for locking at creation time.
    };

    template<class T> SCXCoreLib::SCXHandle<T> SCXSingleton<T>::s_instance(0);
    template<class T> SCXCoreLib::SCXHandle<SCXThreadLockHandle> SCXSingleton<T>::s_lockHandle( new SCXThreadLockHandle(ThreadLockHandleGet()));
}

#endif /* SCXSINGLETON_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
