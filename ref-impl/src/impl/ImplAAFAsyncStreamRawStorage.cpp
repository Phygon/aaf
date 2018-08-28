//=---------------------------------------------------------------------=
//
// $Id$ $Name$
//
// The contents of this file are subject to the AAF SDK Public
// Source License Agreement (the "License"); You may not use this file
// except in compliance with the License.  The License is available in
// AAFSDKPSL.TXT, or you may obtain a copy of the License from the AAF
// Association or its successor.
//
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.
//
// The Original Code of this file is Copyright 1998-2005, Licensor of the
// AAF Association.
//
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

#include "ImplAAFAsyncStreamRawStorage.h"

#include "OMAssertions.h"

#include "AAF.h"
#include "OMRawStorage.h"


ImplAAFAsyncStreamRawStorage::ImplAAFAsyncStreamRawStorage ()
{}


ImplAAFAsyncStreamRawStorage::~ImplAAFAsyncStreamRawStorage ()
{}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFAsyncStreamRawStorage::StreamReadAsyncAt (
      aafUInt64  position,
	  aafMemPtr_t  buf,
	  aafUInt32  bufSize,
	  IAAFIOCompletion *  pCompletion,
	  aafMemConstPtr_t  pClientArg)
{
  if (!GetOMStorage())
	return AAFRESULT_NOT_INITIALIZED;

  if (! buf)
	return AAFRESULT_NULL_PARAM;

  if (! GetOMStorage()->isReadable())
	return AAFRESULT_NOT_READABLE;

  // Creation if ImplAAFAsyncStreamRawStorages in ImplAAFModule.cpp
  // guarantees that this storage is positionable.
  ASSERTU (GetOMStorage()->isPositionable ());


  aafUInt32 bytesRead = 0;
  const AAFRESULT hr = StreamReadAt(position, buf, bufSize, &bytesRead);

  if (pCompletion)
  {
      pCompletion->Completed ( hr, bytesRead, pClientArg);
  }

  return hr;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFAsyncStreamRawStorage::StreamWriteAsyncAt (
      aafUInt64  position,
	  aafMemConstPtr_t  buf,
	  aafUInt32  bufSize,
	  IAAFIOCompletion *  pCompletion,
	  aafMemConstPtr_t  pClientArg)
{
  if (!GetOMStorage())
	return AAFRESULT_NOT_INITIALIZED;

  if (! buf)
	return AAFRESULT_NULL_PARAM;

  if (! GetOMStorage()->isWritable())
	return AAFRESULT_NOT_WRITEABLE;

  // Creation if ImplAAFAsyncStreamRawStorages in ImplAAFModule.cpp
  // guarantees that this storage is positionable.
  ASSERTU (GetOMStorage()->isPositionable ());


  aafUInt32 bytesWritten = 0;
  const AAFRESULT hr = StreamWriteAt (position, buf, bufSize, &bytesWritten);

  if (pCompletion)
  {
      pCompletion->Completed ( hr, bytesWritten, pClientArg);
  }

  return hr;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFAsyncStreamRawStorage::StreamReadScatterAsyncAt (
	  aafUInt64  position,
	  aafIOBufferDesc_t *  pBufs,
	  aafUInt32  bufCount,
	  IAAFIOCompletion *  pCompletion,
	  aafMemConstPtr_t  pClientArg)
{
  if (!GetOMStorage())
	return AAFRESULT_NOT_INITIALIZED;

  if (! pBufs)
	return AAFRESULT_NULL_PARAM;

  if (! GetOMStorage()->isReadable())
	return AAFRESULT_NOT_READABLE;

  // Creation if ImplAAFAsyncStreamRawStorages in ImplAAFModule.cpp
  // guarantees that this storage is positionable.
  ASSERTU (GetOMStorage()->isPositionable ());


  aafUInt32 bytesRead = 0;
  AAFRESULT hr = StreamWriteGatherAt (position,
                                      pBufs,
                                      bufCount,
                                      &bytesRead);


  if (pCompletion)
  {
      pCompletion->Completed ( hr, bytesRead, pClientArg);
  }


  return hr;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFAsyncStreamRawStorage::StreamWriteGatherAsyncAt (
	  aafUInt64  position,
	  aafIOBufferDesc_constptr  pBufs,
	  aafUInt32  bufCount,
	  IAAFIOCompletion *  pCompletion,
	  aafMemConstPtr_t  pClientArg)
{
  if (!GetOMStorage())
	return AAFRESULT_NOT_INITIALIZED;

  if (! pBufs)
	return AAFRESULT_NULL_PARAM;

  if (! GetOMStorage()->isWritable())
	return AAFRESULT_NOT_READABLE;

  // Creation if ImplAAFAsyncStreamRawStorages in ImplAAFModule.cpp
  // guarantees that this storage is positionable.
  ASSERTU (GetOMStorage()->isPositionable ());


  aafUInt32 bytesWritten = 0;
  AAFRESULT hr = StreamWriteGatherAt (position,
                                      pBufs,
                                      bufCount,
                                      &bytesWritten);


  if (pCompletion)
  {
      pCompletion->Completed ( hr, bytesWritten, pClientArg);
  }


  return hr;
}

