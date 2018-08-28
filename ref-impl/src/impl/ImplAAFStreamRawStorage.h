#ifndef __ImplAAFStreamRawStorage_h__
#define __ImplAAFStreamRawStorage_h__
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

#include "ImplAAFRandomRawStorage.h"


class ImplAAFStreamRawStorage : public ImplAAFRandomRawStorage
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFStreamRawStorage ();

protected:
  virtual ~ImplAAFStreamRawStorage ();

public:

  //****************
  // StreamReadAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    StreamReadAt
        (
		 // position in this storage from which data is read
		 aafUInt64  position,

		 // Buffer into which data is read
		 aafMemPtr_t  buf,

		 // Size of buf in bytes
		 aafUInt32  bufSize,

		 // Number of bytes read
		 aafUInt32 *  pNumRead);


  //****************
  // StreamWriteAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    StreamWriteAt
        (
		 // position in this storage into which data is written
		 aafUInt64  position,

		 // Buffer from which data is written
		 aafMemConstPtr_t  buf,

		 // Number of bytes requested to write
		 aafUInt32  bufSize,

		 // Number of bytes written
		 aafUInt32 *  pNumWritten);


  //****************
  // StreamReadScatterAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    StreamReadScatterAt
        (
		 // position in this storage from which data is read
		 aafUInt64  position,

		 // Buffers into which data is read
		 aafIOBufferDesc_t *  pBufs,

		 // Number of buffers
		 aafUInt32  bufCount,

		 // Number of bytes read
		 aafUInt32 *  pNumRead);

  //****************
  // StreamWriteGatherAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    StreamWriteGatherAt
        (
		 // position in this storage into which data is written
		 aafUInt64  position,

		 // Buffers from which data is written
		 aafIOBufferDesc_constptr  pBufs,

		 // Number of buffers
		 aafUInt32  bufCount,

		 // Number of bytes written
		 aafUInt32 *  pNumWritten);
};

#endif // ! __ImplAAFStreamRawStorage_h__
