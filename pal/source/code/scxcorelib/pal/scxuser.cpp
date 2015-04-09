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

    \brief       Implemet the user PAL.
    
    \date        2008-03-25 11:22:33
    
*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxuser.h>
#include <scxcorelib/scxdumpstring.h>
#include <scxcorelib/stringaid.h>

#if defined(SCX_UNIX)
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#else
#error "Platform not supported"
#endif


namespace SCXCoreLib
{
/*----------------------------------------------------------------------------*/
/**
    Default constructor, represents current user.
*/
    SCXUser::SCXUser() : m_uid(geteuid())
    {
        SetName();
    }

/*----------------------------------------------------------------------------*/
/**
    Constructor for specific user ID.

    /param uid User ID of user to represent.
*/
    SCXUser::SCXUser(SCXUserID uid) : m_uid(uid)
    {
        SetName();
    }
    
/*----------------------------------------------------------------------------*/
/**
    Virtual destructor.
*/
    SCXUser::~SCXUser()
    {

    }

/*----------------------------------------------------------------------------*/
/**
   Printable representation of object.
   \returns a string suitable for printing in logs describing the object.
*/
    const std::wstring SCXUser::DumpString() const {
        return SCXDumpStringBuilder("SCXUser")
            .Scalar("uid", m_uid);
    }

/*----------------------------------------------------------------------------*/
/**
    Get user ID.

    \returns user ID of the represented user.
*/
    SCXUserID SCXUser::GetUID()
    {
        return m_uid;
    }

/*----------------------------------------------------------------------------*/
/**
    Get user name.

    \returns user name of the represented user.
*/
    std::wstring SCXUser::GetName()
    {
        return m_name;
    }

/*----------------------------------------------------------------------------*/
/**
    Set user name
*/
    void SCXUser::SetName()
    {
        struct passwd pwd;
        struct passwd *ppwd = NULL;
        long bufSize = sysconf(_SC_GETPW_R_SIZE_MAX);

        // Sanity check - all platforms have this, but never hurts to be certain

        if (bufSize < 1024)
        {
            bufSize = 1024;
        }

        std::vector<char> buf(bufSize);

        // Use reentrant form of getpwuid (it's reentrant, and it pacifies purify)
#if !defined(sun)
		int rc = getpwuid_r (m_uid, &pwd, &buf[0], buf.size (), &ppwd);
		if (rc != 0)
		{
			ppwd = NULL;
		}
#else
        ppwd = getpwuid_r(m_uid, &pwd, &buf[0], buf.size());
#endif

        if (ppwd)
        {
            m_name = StrFromMultibyte(ppwd->pw_name);
        }
        else
        {
            m_name = StrFrom(m_uid);
        }
    }
    
/*----------------------------------------------------------------------------*/
/**
    Check if user is the root user.

    \returns True if the user is the root user.
*/
    bool SCXUser::IsRoot()
    {
        return m_uid == 0;
    }
} /* namespace SCXCoreLib */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
