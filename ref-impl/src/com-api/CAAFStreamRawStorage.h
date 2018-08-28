//@doc
//@class    AAFStreamRawStorage | Implementation class for AAFStreamRawStorage
#ifndef __CAAFStreamRawStorage_h__
#define __CAAFStreamRawStorage_h__

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


class CAAFStreamRawStorage
  : public IAAFStreamRawStorage,
    public CAAFRandomRawStorage
{
protected:

  //********
  //
  // Constructor/destructor
  //
  CAAFStreamRawStorage (IUnknown * pControllingUnknown, aafBool doInit = kAAFTrue);
  virtual ~CAAFStreamRawStorage ();

public:


  //***********************************************************
  //
  // StreamReadAt()
  //
  // Attempts to read bufSize stream bytes from this storage.  Places the
  /// data into buf, and puts the actual number of bytes read into
  /// *pNumRead.  If the end of the storage is encountered before
  /// bufSize bytes can be read, the value written into *pNumRead may
  /// be smaller than bufSize.
  ///
  /// This call will advance the current position by *pNumRead bytes.
  ///
  /// Succeeds if:
  /// - The pNumRead pointer is valid.
  /// - This storage is open for read or read/write.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - buf or pNumRead arg is NULL.
  ///
  /// AAFRESULT_NOT_READABLE
  ///   - This storage is not open for read or read/write.
  //
  STDMETHOD (StreamReadAt) (
    // position in this storage from which data is read
    /*[in]*/ aafUInt64  position,

    // Buffer into which data is read
    /*[out, size_is(bufSize), length_is(*pNumRead)]*/ aafMemPtr_t  buf,

    // Size of buf in bytes
    /*[in]*/ aafUInt32  bufSize,

    // Number of bytes read
    /*[out]*/ aafUInt32 *  pNumRead);


  //***********************************************************
  //
  // StreamWriteAt()
  //
  // Writes bufsize stream bytes into this storage.  Obtains the data
  /// from buf.
  ///
  /// This call may fail if the capacity of this storage cannot be
  /// extended sufficiently to complete the request.  The client can
  /// call SetSize() to attempt to reserve capacity for the storage;
  /// if the SetSize() call succeeds, subsequent Write() calls
  /// within requested that capacity are guaranteed to succeed.
  ///
  /// This call will advance the current position by bufSize bytes.
  ///
  /// Succeeds if:
  /// - The pNumWritten pointer is valid.
  /// - This storage is open for write or read/write.
  /// - Sufficient capacity exists in this storage to perform the
  ///   write.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pNumWritten arg is NULL.
  ///
  /// AAFRESULT_NOT_WRITEABLE
  ///   - This storage is not open for write or read/write.
  ///
  /// AAFRESULT_OFFSET_SIZE
  ///   - It is not possible to extend the allocated size of this
  ///     storage.
  //
  STDMETHOD (StreamWriteAt) (
    // position in this storage into which data is written
    /*[in]*/ aafUInt64  position,

    // Buffer from which data is written
    /*[in, size_is(bufSize)]*/ aafMemConstPtr_t  buf,

    // Number of bytes
    /*[in]*/ aafUInt32  bufSize,

    // Number of bytes written
    /*[out]*/ aafUInt32 *  pNumWritten);


  //***********************************************************
  //
  // StreamReadScatterAt()
  //
  // Attempts to read bufsize stream bytes from this storage.  Places the
  /// data into buf, and puts the actual number of bytes read into
  /// *pNumRead.  If the end of the storage is encountered before
  /// bufSize bytes can be read, the value written into *pNumRead may
  /// be smaller than bufSize.
  ///
  /// This call will advance the current position by *pNumRead bytes.
  ///
  /// Succeeds if:
  /// - The pNumRead pointer is valid.
  /// - This storage is open for read or read/write.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - buf or pNumRead arg is NULL.
  ///
  /// AAFRESULT_NOT_READABLE
  ///   - This storage is not open for read or read/write.
  //
  STDMETHOD (StreamReadScatterAt) (
    // position in this storage from which data is read
    /*[in]*/ aafUInt64  position,

    // Buffers into which data is read
    /*[out, size_is(bufCount)]*/ aafIOBufferDesc_t *  pBufs,

    // Number of buffers
    /*[in]*/ aafUInt32  bufCount,

    // Number of bytes read
    /*[out]*/ aafUInt32 *  pNumRead);


  //***********************************************************
  //
  // StreamWriteGatherAt()
  //
  // Writes bufsize stream bytes into this storage.  Obtains the data
  /// from buf.
  ///
  /// This call may fail if the capacity of this storage cannot be
  /// extended sufficiently to complete the request.  The client can
  /// call SetSize() to attempt to reserve capacity for the storage;
  /// if the SetSize() call succeeds, subsequent Write() calls
  /// within requested that capacity are guaranteed to succeed.
  ///
  /// This call will advance the current position by bufSize bytes.
  ///
  /// Succeeds if:
  /// - The pNumWritten pointer is valid.
  /// - This storage is open for write or read/write.
  /// - Sufficient capacity exists in this storage to perform the
  ///   write.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pNumWritten arg is NULL.
  ///
  /// AAFRESULT_NOT_WRITEABLE
  ///   - This storage is not open for write or read/write.
  ///
  /// AAFRESULT_OFFSET_SIZE
  ///   - It is not possible to extend the allocated size of this
  ///     storage.
  //
  STDMETHOD (StreamWriteGatherAt) (
    // position in this storage into which data is written
    /*[in]*/ aafUInt64  position,

    // Buffers from which data is written
    /*[out, size_is(bufCount)]*/ aafIOBufferDesc_constptr  pBufs,

    // Number of buffers
    /*[in]*/ aafUInt32  bufCount,

    // Number of bytes written
    /*[out]*/ aafUInt32 *  pNumWritten);



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

#endif // ! __CAAFStreamRawStorage_h__


