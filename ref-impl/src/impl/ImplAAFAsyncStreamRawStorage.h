#ifndef __ImplAAFAsyncStreamRawStorage_h__
#define __ImplAAFAsyncStreamRawStorage_h__
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


struct IAAFIOCompletion;


class ImplAAFAsyncStreamRawStorage : public ImplAAFStreamRawStorage
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFAsyncStreamRawStorage ();

protected:
  virtual ~ImplAAFAsyncStreamRawStorage ();

public:

  //****************
  // StreamReadAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    StreamReadAsyncAt
        (
		 // position in this storage from which data is read
		 aafUInt64  position,

		 // Buffer into which data is read
		 aafMemPtr_t  buf,

		 // Size of buf in bytes
		 aafUInt32  bufSize,

		 // object implementing the IAAFIOCompletion
		 // interface to be called when the read is completed
		 IAAFIOCompletion *  pCompletion,

		 // client-specific data to be returned to the
		 // as a part of the I/O completion routine
		 aafMemConstPtr_t  pClientArg);


  //****************
  // StreamWriteAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    StreamWriteAsyncAt
        (
		 // position in this storage into which data is written
		 aafUInt64  position,

		 // Buffer from which data is written
		 aafMemConstPtr_t  buf,

		 // Number of bytes requested to write
		 aafUInt32  bufSize,

		 // object implementing the IAAFIOCompletion
		 // interface to be called when the write is completed
		 IAAFIOCompletion *  pCompletion,

		 // client-specific data to be returned to the
		 // as a part of the I/O completion routine
		 aafMemConstPtr_t  pClientArg);


  //****************
  // StreamReadScatterAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    StreamReadScatterAsyncAt
        (
		 // position in this storage from which data is read
		 aafUInt64  position,

		 // Buffers into which data is read
		 aafIOBufferDesc_t *  pBufs,

		 // Number of buffers
		 aafUInt32  bufCount,

		 // object implementing the IAAFIOCompletion
		 // interface to be called when the read is completed
		 IAAFIOCompletion *  pCompletion,

		 // client-specific data to be returned to the
		 // as a part of the I/O completion routine
		 aafMemConstPtr_t  pClientArg);


  //****************
  // StreamWriteGatherAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    StreamWriteGatherAsyncAt
        (
		 // position in this storage into which data is written
		 aafUInt64  position,

		 // Buffers from which data is written
		 aafIOBufferDesc_constptr  pBufs,

		 // Number of buffers
		 aafUInt32  bufCount,

		 // object implementing the IAAFIOCompletion
		 // interface to be called when the write is completed
		 IAAFIOCompletion *  pCompletion,

		 // client-specific data to be returned to the
		 // as a part of the I/O completion routine
		 aafMemConstPtr_t  pClientArg);
};

#endif // ! __ImplAAFAsyncStreamRawStorage_h__
