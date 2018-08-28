//@doc
//@class    AAFAsyncStreamRawStorage | Implementation class for AAFAsyncStreamRawStorage
#ifndef __CAAFAsyncStreamRawStorage_h__
#define __CAAFAsyncStreamRawStorage_h__

//=---------------------------------------------------------------------=
//
// This file was GENERATED for the AAF SDK
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
// The Original Code of this file is Copyright 1998-2012, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
// The Initial Developer of the Original Code of this file and the
// licensor of the Advanced Media Workflow Association is
// Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=



#ifndef __AAF_h__
#include "AAF.h"
#endif






#ifndef __CAAFRandomRawStorage_h__
#include "CAAFRandomRawStorage.h"
#endif


class CAAFAsyncStreamRawStorage
  : public IAAFAsyncStreamRawStorage,
    public CAAFRandomRawStorage
{
protected:

  //********
  //
  // Constructor/destructor
  //
  CAAFAsyncStreamRawStorage (IUnknown * pControllingUnknown, aafBool doInit = kAAFTrue);
  virtual ~CAAFAsyncStreamRawStorage ();

public:


  //***********************************************************
  //
  // StreamReadAsyncAt()
  //
  // Attempts to read bufSize stream bytes from this storage.
  //
  // Succeeds if:
  // - This storage is open for read or read/write.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - buf arg is NULL.
  //
  // AAFRESULT_NOT_READABLE
  //   - This storage is not open for read or read/write.
  //
  STDMETHOD (StreamReadAsyncAt) (
    // position in this storage from which data is read
    /*[in]*/ aafUInt64  position,

    // Buffer into which data is read
    /*[out, size_is(bufSize)]*/ aafMemPtr_t  buf,

    // Size of buf in bytes
    /*[in]*/ aafUInt32  bufSize,

    // object implementing the IAAFIOCompletion interface to be called when the read is completed
    /*[in]*/ IAAFIOCompletion *  pCompletion,

    // client-specific data to be returned to the as a part of the I/O completion routine
    /*[in]*/ aafMemConstPtr_t  pClientArg);


  //***********************************************************
  //
  // StreamWriteAsyncAt()
  //
  // Writes bufsize stream bytes into this storage.  Obtains the data
  // from buf.
  //
  // Succeeds if:
  // - The buf pointer is valid.
  // - This storage is open for write or read/write.
  // - Sufficient capacity exists in this storage to perform the
  //   write.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - buf arg is NULL.
  //
  // AAFRESULT_NOT_WRITEABLE
  //   - This storage is not open for write or read/write.
  //
  // AAFRESULT_OFFSET_SIZE
  //   - It is not possible to extend the allocated size of this
  //     storage.
  //
  STDMETHOD (StreamWriteAsyncAt) (
    // position in this storage into which data is written
    /*[in]*/ aafUInt64  position,

    // Buffer from which data is written
    /*[in, size_is(bufSize)]*/ aafMemConstPtr_t  buf,

    // Number of bytes
    /*[in]*/ aafUInt32  bufSize,

    // object implementing the IAAFIOCompletion interface to be called when the read is completed
    /*[in]*/ IAAFIOCompletion *  pCompletion,

    // client-specific data to be returned to the as a part of the I/O completion routine
    /*[in]*/ aafMemConstPtr_t  pClientArg);


  //***********************************************************
  //
  // StreamReadScatterAsyncAt()
  //
  // Attempts to read bufsize stream bytes from this storage.
  //
  // Succeeds if:
  // - The buf pointer is valid.
  // - This storage is open for read or read/write.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - buf arg is NULL.
  //
  // AAFRESULT_NOT_READABLE
  //   - This storage is not open for read or read/write.
  //
  STDMETHOD (StreamReadScatterAsyncAt) (
    // position in this storage from which data is read
    /*[in]*/ aafUInt64  position,

    // Buffers into which data is read
    /*[out, size_is(bufCount)]*/ aafIOBufferDesc_t *  pBufs,

    // Number of buffers
    /*[in]*/ aafUInt32  bufCount,

    // object implementing the IAAFIOCompletion interface to be called when the read is completed
    /*[in]*/ IAAFIOCompletion *  pCompletion,

    // client-specific data to be returned to the as a part of the I/O completion routine
    /*[in]*/ aafMemConstPtr_t  pClientArg);


  //***********************************************************
  //
  // StreamWriteGatherAsyncAt()
  //
  // Writes bufsize stream bytes into this storage.  Obtains the data
  // from buf.
  //
  // Succeeds if:
  // - The pNumWritten pointer is valid.
  // - This storage is open for write or read/write.
  // - Sufficient capacity exists in this storage to perform the
  //   write.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - buf arg is NULL.
  //
  // AAFRESULT_NOT_WRITEABLE
  //   - This storage is not open for write or read/write.
  //
  // AAFRESULT_OFFSET_SIZE
  //   - It is not possible to extend the allocated size of this
  //     storage.
  //
  STDMETHOD (StreamWriteGatherAsyncAt) (
    // position in this storage into which data is written
    /*[in]*/ aafUInt64  position,

    // Buffers from which data is written
    /*[out, size_is(bufCount)]*/ aafIOBufferDesc_constptr  pBufs,

    // Number of buffers
    /*[in]*/ aafUInt32  bufCount,

    // object implementing the IAAFIOCompletion interface to be called when the read is completed
    /*[in]*/ IAAFIOCompletion *  pCompletion,

    // client-specific data to be returned to the as a part of the I/O completion routine
    /*[in]*/ aafMemConstPtr_t  pClientArg);



protected:
  // 
  // Declare the QI that implements for the interfaces
  // for this module. This will be called by CAAFUnknown::QueryInterface().
  // 
  STDMETHOD(InternalQueryInterface)(REFIID riid, void **ppvObjOut);


public:
  //
  // This class as concrete. All AAF objects can be constructed from
  // a CLSID. This will allow subclassing all "base-classes" by
  // aggreggation.
  // 
  AAF_DECLARE_CONCRETE();
  //
  //********
};

#endif // ! __CAAFAsyncStreamRawStorage_h__


