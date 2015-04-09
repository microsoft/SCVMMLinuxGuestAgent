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

    \brief       File based implementation of the SCXPersistDataWriter interface
    
    \date        2008-08-21 14:50:08

*/
/*----------------------------------------------------------------------------*/
#ifndef SCXFILEPERSISTDATAWRITER_H
#define SCXFILEPERSISTDATAWRITER_H

#include <scxcorelib/scxpersistence.h>
#include <scxcorelib/scxfilepath.h>
#include <list>

namespace SCXCoreLib
{

    /*----------------------------------------------------------------------------*/
    /**
        File based implementation of the SCXPersistDataWriter interface.
    */
    class SCXFilePersistDataWriter : public SCXPersistDataWriter
    {
    public:
        SCXFilePersistDataWriter(const SCXFilePath& path, unsigned int version);
        virtual ~SCXFilePersistDataWriter();
        virtual void WriteStartGroup(const std::wstring& name);
        virtual void WriteEndGroup();
        virtual void WriteValue(const std::wstring& name, const std::wstring& value);
        virtual void DoneWriting();
    private:
        SCXHandle<std::fstream> m_Stream; //!< Stream for writing to file.
        std::list<std::wstring> m_StartedGroups; //!< Current open groups.
        std::wstring m_Indentation; //!< Contains spaces for indentation.
        std::wstring EncodeString(const std::wstring& in) const;
    };
}

#endif /* SCXFILEPERSISTDATAWRITER_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
