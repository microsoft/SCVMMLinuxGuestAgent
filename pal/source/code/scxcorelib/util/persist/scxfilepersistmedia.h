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

    \brief       File based implementation of the SCXPersistMedia interface
    
    \date        2008-08-21 16:23:44

*/
/*----------------------------------------------------------------------------*/
#ifndef SCXFILEPERSISTMEDIA_H
#define SCXFILEPERSISTMEDIA_H


#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxpersistence.h>
#include <scxcorelib/scxfilepath.h>

namespace SCXCoreLib
{
    /*----------------------------------------------------------------------------*/
    /**
        Simple file based implementation of SCXPersistMedia interface.
    */
    class SCXFilePersistMedia : public SCXPersistMedia
    {
    public:
        SCXFilePersistMedia();
        virtual ~SCXFilePersistMedia();
        virtual SCXHandle<SCXPersistDataReader> CreateReader(const std::wstring& name);
        virtual SCXHandle<SCXPersistDataWriter> CreateWriter(const std::wstring& name, unsigned int version = 0);
        virtual void UnPersist(const std::wstring& name);
        SCXFilePath NameToFilePath(const std::wstring& name) const;
        void SetBasePath(const SCXFilePath& path);
    private:
        void AddUserNameToBasePath();
        SCXFilePath m_BasePath; //!< Folder where persistence files are stored.
    };
}

#endif /* SCXFILEPERSISTMEDIA_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
