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

   \brief     No-op helper (primarily for Solaris 11 platforms)

   \date      2012-01-19 14:40:00


*/
/*----------------------------------------------------------------------------*/

/*
 * The Solaris 11 linker has an issue (at least for Solaris Studio 12.2) where
 * it doesn't allow a link line with no input files at all.
 *
 * Normally, we link libscxcoreprovidermodule.so with no input files (but lots
 * of -l libraries that resolve to our lib*.a files).  The Solaris 11 compiler
 * doesn't care for this.
 *
 * Two ways to solve this:
 *   1. For Solaris 11, rather than use -l for inclusion of our .a files,
 *      include them as input files (ifdef in Makefile.components), or
 *   2. Include a dummy input file (a noop file, if you will), that contains
 *      no executable code, but exists solely to pacify Solaris 11.
 *
 * We decided to solve the issue using #2.  This is the noop file.  It contains
 * no executable code.
 */
