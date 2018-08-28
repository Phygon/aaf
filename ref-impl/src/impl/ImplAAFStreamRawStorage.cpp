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

#include "ImplAAFStreamRawStorage.h"

#include "OMAssertions.h"

#include "OMRawStorage.h"


ImplAAFStreamRawStorage::ImplAAFStreamRawStorage ()
{}


ImplAAFStreamRawStorage::~ImplAAFStreamRawStorage ()
{}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFStreamRawStorage::StreamReadAt (
      aafUInt64  position,
	  aafMemPtr_t  buf,
	  aafUInt32  bufSize,
	  aafUInt32 *  pNumRead)
{
  if (!GetOMStorage())
	return AAFRESULT_NOT_INITIALIZED;

  if (! buf)
	return AAFRESULT_NULL_PARAM;

  if (! pNumRead)
	return AAFRESULT_NULL_PARAM;

  if (! GetOMStorage()->isReadable())
	return AAFRESULT_NOT_READABLE;

  // Creation if ImplAAFStreamRawStorages in ImplAAFModule.cpp
  // guarantees that this storage is positionable.
  ASSERTU (GetOMStorage()->isPositionable ());


  return ReadAt(position, buf, bufSize, pNumRead);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFStreamRawStorage::StreamWriteAt (
      aafUInt64  position,
	  aafMemConstPtr_t  buf,
	  aafUInt32  bufSize,
	  aafUInt32 *  pNumWritten)
{
  if (!GetOMStorage())
	return AAFRESULT_NOT_INITIALIZED;

  if (! buf)
	return AAFRESULT_NULL_PARAM;

  if (! pNumWritten)
	return AAFRESULT_NULL_PARAM;

  if (! GetOMStorage()->isWritable())
	return AAFRESULT_NOT_WRITEABLE;

  // Creation if ImplAAFStreamRawStorages in ImplAAFModule.cpp
  // guarantees that this storage is positionable.
  ASSERTU (GetOMStorage()->isPositionable ());


  return WriteAt (position, buf, bufSize, pNumWritten);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFStreamRawStorage::StreamReadScatterAt (
	  aafUInt64  position,
	  aafIOBufferDesc_t *  pBufs,
	  aafUInt32  bufCount,
	  aafUInt32 *  pNumRead)
{
  if (!GetOMStorage())
	return AAFRESULT_NOT_INITIALIZED;

  if (! pBufs)
	return AAFRESULT_NULL_PARAM;

  if (! pNumRead)
	return AAFRESULT_NULL_PARAM;

  if (! GetOMStorage()->isReadable())
	return AAFRESULT_NOT_READABLE;

  // Creation if ImplAAFStreamRawStorages in ImplAAFModule.cpp
  // guarantees that this storage is positionable.
  ASSERTU (GetOMStorage()->isPositionable ());


  AAFRESULT hr = AAFRESULT_SUCCESS;
  aafUInt64 currentPosition = position;
  for (aafUInt32 i=0; i<bufCount && hr == AAFRESULT_SUCCESS; i++)
  {
    aafUInt32  bytesRead = 0;
    hr = StreamReadAt (currentPosition,
                       pBufs[i].buf,
                       pBufs[i].bufSize,
                       &bytesRead);
    (*pNumRead) += bytesRead;
    currentPosition += bytesRead;
  }


  return hr;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFStreamRawStorage::StreamWriteGatherAt (
	  aafUInt64  position,
	  aafIOBufferDesc_constptr  pBufs,
	  aafUInt32  bufCount,
	  aafUInt32 *  pNumWritten)
{
  if (!GetOMStorage())
	return AAFRESULT_NOT_INITIALIZED;

  if (! pBufs)
	return AAFRESULT_NULL_PARAM;

  if (! pNumWritten)
	return AAFRESULT_NULL_PARAM;

  if (! GetOMStorage()->isWritable())
	return AAFRESULT_NOT_READABLE;

  // Creation if ImplAAFStreamRawStorages in ImplAAFModule.cpp
  // guarantees that this storage is positionable.
  ASSERTU (GetOMStorage()->isPositionable ());


  AAFRESULT hr = AAFRESULT_SUCCESS;
  aafUInt64 currentPosition = position;
  for (aafUInt32 i=0; i<bufCount && hr == AAFRESULT_SUCCESS; i++)
  {
    aafUInt32  bytesWritten = 0;
    hr = StreamWriteAt (currentPosition,
                        pBufs[i].buf,
                        pBufs[i].bufSize,
                        &bytesWritten);
    (*pNumWritten) += bytesWritten;
    currentPosition += bytesWritten;
  }


  return hr;
}

