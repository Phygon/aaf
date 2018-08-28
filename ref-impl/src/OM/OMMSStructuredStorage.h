//=---------------------------------------------------------------------=
//
// $Id$ $Name$
//
// The contents of this file are subject to the AAF SDK Public Source
// License Agreement Version 2.0 (the "License"); You may not use this
// file except in compliance with the License.  The License is available
// in AAFSDKPSL.TXT, or you may obtain a copy of the License from the
// Advanced Media Workflow Association, Inc., or its successor.
//
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.  Refer to Section 3.3 of the License for proper use
// of this Exhibit.
//
// WARNING:  Please contact the Advanced Media Workflow Association,
// Inc., for more information about any additional licenses to
// intellectual property covering the AAF Standard that may be required
// to create and distribute AAF compliant products.
// (http://www.amwa.tv/policies).
//
// Copyright Notices:
// The Original Code of this file is Copyright 1998-2009, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
// The Initial Developer of the Original Code of this file and the
// licensor of the Advanced Media Workflow Association is
// Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

// @doc OMEXTERNAL
#ifndef OMMSSTRUCTUREDSTORAGE_H
#define OMMSSTRUCTUREDSTORAGE_H

#ifndef OM_NO_STRUCTURED_STORAGE

#include "OMStructuredStorage.h"

// redefine STGOPTIONS so that it is available on all platforms
typedef struct tagOM_STGOPTIONS
{
  USHORT      usVersion;
  USHORT      reserved;
  ULONG       ulSectorSize;
  const WCHAR *pwcsTemplateFile;
} OM_STGOPTIONS;

// Initialization and finalization.
//
void OMMSSInitialize(void);

void OMMSSFinalize(void);

#if defined(OM_DYNAMIC_SS)
// For dynamic linking to the Structured Storage library redirect
// the following calls to wrapper functions.
//
#define StgCreateDocfile OMStgCreateDocfile
#define StgCreateDocfileOnILockBytes OMStgCreateDocfileOnILockBytes
#define StgOpenStorage OMStgOpenStorage
#define StgOpenStorageOnILockBytes OMStgOpenStorageOnILockBytes
#define StgIsStorageFile OMStgIsStorageFile

#define CoInitialize OMCoInitialize
#define CoUninitialize OMCoUninitialize
#endif

OMInt32 OMStgCreateDocfile(const SSCHAR* pwcsName,
                           OMUInt32 grfMode,
                           OMUInt32 reserved,
                           IStorage** ppstgOpen);

OMInt32 OMStgCreateDocfileOnILockBytes(ILockBytes* plkbyt,
                                       OMUInt32 grfMode,
                                       OMUInt32 reserved,
                                       IStorage** ppstgOpen);

OMInt32 OMStgOpenStorage(SSCHAR* pwcsName,
                         IStorage* pstgPriority,
                         OMUInt32 grfMode,
                         SSCHAR** snbExclude,
                         OMUInt32 reserved,
                         IStorage** ppstgOpen);

OMInt32 OMStgOpenStorageOnILockBytes(ILockBytes* plkbyt,
                                     IStorage* pstgPriority,
                                     OMUInt32 grfMode,
                                     SSCHAR** snbExclude,
                                     OMUInt32 reserved,
                                     IStorage** ppstgOpen);

OMInt32 OMStgIsStorageFile(const SSCHAR* pwcsName);


OMInt32 OMCoInitialize(void* pvReserved);

void OMCoUninitialize(void);



#ifdef OM_USE_STORAGE_EX

// This function does not exist in the current MS Structured Storage library
// but is required to create 4K files through the raw interface.
// Therefore the function is simulated in OMMSStructuredStorage.cpp
// 040109 Ian Baker Metaglue Corp.
OMInt32 StgCreateDocfileOnILockBytesEx (
										ILockBytes* plkbyt,
										DWORD grfMode,
										DWORD stgfmt,
										DWORD grfAttrs,
										OM_STGOPTIONS* pStgOptions,
										void* reserved2,
										REFIID riid,
										void** ppObjectOpen   );


#endif // OM_USE_STORAGE_EX

#endif // !OM_NO_STRUCTURED_STORAGE

#endif // !OMMSSTRUCTUREDSTORAGE_H
