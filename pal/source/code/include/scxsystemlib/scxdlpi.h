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

#include <sys/types.h>
#include <sys/stropts.h>

#undef DLPI_DEV

#define BUFSIZE 4000
static u_long controlInfo[BUFSIZE];
static u_long dataInfo[BUFSIZE];
static struct strbuf control = {BUFSIZE, 0, (char *)controlInfo};
static struct strbuf data = {BUFSIZE, 0, (char *)dataInfo};

class dlpi
{
public:
    
    /**
        Get a message from a stream; return type of message

        \param      fd - file descriptor
        \returns    0 if OK, -1 otherwise
    */
    static int getMessage(int fd);
    
    /**
        Verify that dl_primitive in controlInfo = prim

        \param      prim - DLPI primitive (DL_INFO_REQ, DL_INFO_ACK ... etc.)
        \returns    0 if OK, -1 otherwise
    */
    static int testControlPrimitive(int prim);
    
    /**
        Put a control message on a stream

        \param      fd - DLPI device file descriptor
        \param      len - length of control message
        \param      pri - message type
        \returns    0 if OK, -1 otherwise
    */
    static int putControlMessage(int fd, int len, int pri);
    
    /**
        Put a control + data message on a stream

        \param      fd - DLPI device file descriptor
        \param      clen - length of control message
        \param      dlen - length of data message
        \param      pri - message type
        \returns    0 if OK, -1 otherwise
    */
    static int putControlAndData(int fd, int clen, int dlen, int pri);
    
    /**
        Open file descriptor and attach

        \param      dev - DLPI device name
        \param      ppa - Physical Point of Attachment
        \param      fd - DLPI device file descriptor
        \returns    0 if OK, -1 otherwise
    */
    static int openDLPI(const char *dev, int ppa, int *fd);
    
    /**
        Send DL_BIND_REQ

        \param      fd - File Descriptor
        \param      sap - Service Access Point
        \param      addr - Bind address
        \returns    0 if OK, -1 otherwise
    */
    static int bindDLPI(int fd, int sap, u_char *addr);
    
    /**
        Get the mac address of the "first" interface

        \param       addr - an array of six bytes, has to be allocated by the caller
        \returns     0 if OK, -1 if the address could not be determined
    */
    static long getMacAddress ( u_char  *addr);
};
