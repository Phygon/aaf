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

#include "AAF.h"
#include "AAFResult.h"
#include "AAFUtils.h"

#include "OMAssertions.h"

#include "ImplAAFOMRawStorage.h"

#include "OMExceptions.h"

class ChainedIOCompletion : public IAAFIOCompletion {
public:

  static ChainedIOCompletion* Create();

  // IUnknown overrides
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(
    REFIID iid,
    void** ppIfc);
  virtual aafUInt32 STDMETHODCALLTYPE AddRef();
  virtual aafUInt32 STDMETHODCALLTYPE Release();

  // IAAFIOCompletion overrides
  virtual AAFRESULT STDMETHODCALLTYPE Completed(
    HRESULT completionStatus,
    aafUInt32 numTransferred,
    aafMemConstPtr_t pClientData);

  virtual void chainTo(IAAFIOCompletion* pCompletion,
                       aafMemConstPtr_t pClientData);

protected:

  ChainedIOCompletion();
  virtual ~ChainedIOCompletion();

  aafUInt32 _refCount;

  IAAFIOCompletion* _pCompletion;
  aafMemConstPtr_t  _pClientData;
};

ImplAAFOMRawStorage::ImplAAFOMRawStorage (IAAFRawStorage * rep)
  : _rep (rep),
    _randRep (0),
    _streamRep (0),
    _asyncStreamRep (0),
    _copyByteRep (0),
    _pending (0),
    _position(0)
{
  ASSERTU (rep);
  _rep->AddRef ();

  AAFRESULT hr;
  hr = _rep->QueryInterface(IID_IAAFRandomRawStorage, (void **)&_randRep);
  if (AAFRESULT_FAILED (hr))
	_randRep = 0;

  hr = _rep->QueryInterface(IID_IAAFStreamRawStorage, (void **)&_streamRep);
  if (AAFRESULT_FAILED (hr))
	_streamRep = 0;

  hr = _rep->QueryInterface(IID_IAAFAsyncStreamRawStorage, (void **)&_asyncStreamRep);
  if (AAFRESULT_FAILED (hr))
	_asyncStreamRep = 0;

  if (_asyncStreamRep != 0) {
    _pending = ChainedIOCompletion::Create();
  }

  hr = _rep->QueryInterface(IID_IAAFCopyByte, (void **)&_copyByteRep);
  if (AAFRESULT_FAILED (hr))
	_copyByteRep = 0;
}


ImplAAFOMRawStorage::~ImplAAFOMRawStorage ()
{
  ASSERTU (_rep);
  _rep->Release ();
  _rep = 0;

  if (_randRep)
	{
	  _randRep->Release ();
	  _randRep = 0;
	}

  if (_streamRep)
	{
	  _streamRep->Release ();
	  _streamRep = 0;
	}

  if (_asyncStreamRep)
	{
	  _asyncStreamRep->Release ();
	  _asyncStreamRep = 0;
	}

  if (_copyByteRep)
	{
	  _copyByteRep->Release ();
	  _copyByteRep = 0;
	}

  if (_pending)
	{
	  _pending->Release ();
	  _pending = 0;
	}

}


bool ImplAAFOMRawStorage::isReadable(void) const
{
  ASSERTU (_rep);
  aafBoolean_t r;
  AAFRESULT hr;
  hr = _rep->IsReadable (&r);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  return r ? true : false;
}


void ImplAAFOMRawStorage::read(OMByte* bytes,
							   OMUInt32 byteCount,
							   OMUInt32& bytesRead) const
{
  ASSERTU (_rep);
  AAFRESULT hr;

  // If raw storage is positionable (is IAAFRandomRawStorage) read bytes
  // at the position specified by the _position member. Otherwise read
  // at the current storage position which in this case always matches
  // the _position value.
  if (_randRep)
  {
    hr = _randRep->ReadAt (_position, bytes, byteCount, &bytesRead);
  }
  else
  {
    hr = _rep->Read (bytes, byteCount, &bytesRead);
  }
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);

  ImplAAFOMRawStorage* nonConstThis = const_cast<ImplAAFOMRawStorage*>(this);
  nonConstThis->_position += bytesRead;
}


void ImplAAFOMRawStorage::readAt(OMUInt64 position,
								 OMByte* bytes,
								 OMUInt32 byteCount,
								 OMUInt32& bytesRead) const
{
  ASSERTU (_randRep);
  AAFRESULT hr;
  hr = _randRep->ReadAt (position, bytes, byteCount, &bytesRead);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);

  ImplAAFOMRawStorage* nonConstThis = const_cast<ImplAAFOMRawStorage*>(this);
  nonConstThis->_position = position + bytesRead;
}


bool ImplAAFOMRawStorage::isWritable(void) const
{
  ASSERTU (_rep);
  aafBoolean_t r;
  AAFRESULT hr;
  hr = _rep->IsWriteable (&r);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  return r ? true : false;
}


void ImplAAFOMRawStorage::write(const OMByte* bytes,
								OMUInt32 byteCount,
								OMUInt32& bytesWritten)
{
  ASSERTU (_rep);
  AAFRESULT hr;

  // If raw storage is positionable (is IAAFRandomRawStorage) write bytes
  // at the position specified by the _position member. Otherwise write
  // at the current storage position which in this case always matches
  // the _position value.
  if (_randRep)
  {
    hr = _randRep->WriteAt (_position, bytes, byteCount, &bytesWritten);
  }
  else
  {
    hr = _rep->Write (bytes, byteCount, &bytesWritten);
  }
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  _position += bytesWritten;
}


void ImplAAFOMRawStorage::writeAt(OMUInt64 position,
								  const OMByte* bytes,
								  OMUInt32 byteCount,
								  OMUInt32& bytesWritten)
{
  ASSERTU (_randRep);
  AAFRESULT hr;
  hr = _randRep->WriteAt (position, bytes, byteCount, &bytesWritten);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  _position = position + bytesWritten;
}


void ImplAAFOMRawStorage::writeCopyByteAt(OMUInt64 position,
                                          OMByte theByte,
                                          OMUInt32 byteCount,
                                          OMUInt32& bytesWritten)
{
  ASSERTU (_randRep);
  AAFRESULT hr = AAFRESULT_SUCCESS;
  if (_copyByteRep)
  {
    hr = _copyByteRep->WriteCopyByteAt (position,
                                        theByte,
                                        byteCount,
                                        &bytesWritten);
  }
  else
  {
    bytesWritten = 0;
    OMUInt64 currentPosition = position;
    for (OMUInt32 i=0; i<byteCount && hr == AAFRESULT_SUCCESS; i++)
    {
      OMUInt32  bufferBytesWritten = 0;
      hr = _randRep->WriteAt (currentPosition,
                              &theByte,
                              1,
                              &bufferBytesWritten);
      bytesWritten += bufferBytesWritten;
      currentPosition += bufferBytesWritten;
    }
  }

  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  _position = position + bytesWritten;
}


bool ImplAAFOMRawStorage::isExtendible(void) const
{
  ASSERTU (_rep);

  // If not an AAFRandomRawStorage, it's definitely not extendible.
  if (! _randRep)
	return false;

  AAFRESULT hr;
  aafBoolean_t r;
  hr = _randRep->IsExtendable (&r);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  return r ? true : false;
}


OMUInt64 ImplAAFOMRawStorage::extent(void) const
{
  ASSERTU (_randRep);
  AAFRESULT hr;
  aafUInt64 result;
  hr = _randRep->GetExtent (&result);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  return result;
}


void ImplAAFOMRawStorage::extend(OMUInt64 newSize)
{
  ASSERTU (_randRep);
  AAFRESULT hr;
  hr = _randRep->SetExtent (newSize);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
}


OMUInt64 ImplAAFOMRawStorage::size(void) const
{
  ASSERTU (_randRep);
  AAFRESULT hr;
  OMUInt64 result;
  hr = _randRep->GetSize (&result);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  return result;
}


bool ImplAAFOMRawStorage::isPositionable(void) const
{
  ASSERTU (_rep);
  // If not an AAFRandomRawStorage, it's not positionable.
  if (_randRep)
	return true;
  else
	return false;
}


OMUInt64 ImplAAFOMRawStorage::position(void) const
{
  ASSERTU (_rep);
  return _position;
}


void ImplAAFOMRawStorage::setPosition(OMUInt64 newPosition) const
{
  ASSERTU (_randRep);

  // The _position value is used by read() and write() methods to
  // adjust the storage current position before reading or writing.
  ImplAAFOMRawStorage* nonConstThis = const_cast<ImplAAFOMRawStorage*>(this);
  nonConstThis->_position = newPosition;
}


void ImplAAFOMRawStorage::synchronize(void)
{
  ASSERTU (_rep);
  AAFRESULT hr;
  hr = _rep->Synchronize ();
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
}


void ImplAAFOMRawStorage::streamReadAt(OMUInt64 position,
                                       OMByte* bytes,
                                       OMUInt32 byteCount,
                                       OMUInt32& bytesRead) const
{
  ASSERTU (_randRep);
  AAFRESULT hr = AAFRESULT_SUCCESS;
  if (_streamRep)
  {
    hr = _streamRep->StreamReadAt (position, bytes, byteCount, &bytesRead);
  }
  else
  {
    hr = _randRep->ReadAt (position, bytes, byteCount, &bytesRead);
  }

  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  ImplAAFOMRawStorage* nonConstThis = const_cast<ImplAAFOMRawStorage*>(this);
  nonConstThis->_position = position + bytesRead;
}


void ImplAAFOMRawStorage::streamReadAt(OMUInt64 position,
                                       OMIOBufferDescriptor* buffers,
                                       OMUInt32 bufferCount,
                                       OMUInt32& bytesRead) const
{
  ASSERTU (_randRep);
  AAFRESULT hr = AAFRESULT_SUCCESS;
  if (_streamRep)
  {
    aafIOBufferDesc_t*  aafBuffers =
        reinterpret_cast<aafIOBufferDesc_t*>(buffers);
    hr = _streamRep->StreamReadScatterAt (position,
                                          aafBuffers,
                                          bufferCount,
                                          &bytesRead);
  }
  else
  {
    bytesRead = 0;
    OMUInt64 currentPosition = position;
    for (OMUInt32 i=0; i<bufferCount && hr == AAFRESULT_SUCCESS; i++)
    {
      OMUInt32  bufferBytesRead = 0;
      hr = _randRep->ReadAt (currentPosition,
                             buffers[i]._buffer,
                             buffers[i]._bufferSize,
                             &bufferBytesRead);
      bytesRead += bufferBytesRead;
      currentPosition += bufferBytesRead;
    }
  }

  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  ImplAAFOMRawStorage* nonConstThis = const_cast<ImplAAFOMRawStorage*>(this);
  nonConstThis->_position = position + bytesRead;
}


void ImplAAFOMRawStorage::streamReadAt(OMUInt64 position,
                                       OMByte* buffer,
                                       const OMUInt32 bytes,
                                       void* /* */ completion,
                                       const void* clientArgument) const
{
  AAFRESULT hr = AAFRESULT_SUCCESS;

  if (_asyncStreamRep)
  {
    IAAFIOCompletion*  aafCompletion =
        reinterpret_cast<IAAFIOCompletion*>(completion);
    aafMemConstPtr_t  aafClientArgument =
        reinterpret_cast<aafMemConstPtr_t>(clientArgument);
    _pending->chainTo(aafCompletion, aafClientArgument);
    hr = _asyncStreamRep->StreamReadAsyncAt (position,
                                             buffer,
                                             bytes,
                                             _pending,
                                             0);
  }
  else
  {
    // The raw storage does not implement the interface
    // required to implement this call.
    hr = E_NOINTERFACE;
  }

  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
}


void ImplAAFOMRawStorage::streamReadAt(OMUInt64 position,
                                       OMIOBufferDescriptor* buffers,
                                       OMUInt32 bufferCount,
                                       void* /* */ completion,
                                       const void* clientArgument) const
{
  AAFRESULT hr = AAFRESULT_SUCCESS;

  if (_asyncStreamRep)
  {
    aafIOBufferDesc_t*  aafBuffers =
        reinterpret_cast<aafIOBufferDesc_t*>(buffers);
    IAAFIOCompletion*  aafCompletion =
        reinterpret_cast<IAAFIOCompletion*>(completion);
    aafMemConstPtr_t  aafClientArgument =
        reinterpret_cast<aafMemConstPtr_t>(clientArgument);
    _pending->chainTo(aafCompletion, aafClientArgument);
    hr = _asyncStreamRep->StreamReadScatterAsyncAt (position,
                                                    aafBuffers,
                                                    bufferCount,
                                                    _pending,
                                                    0);
  }
  else
  {
    // The raw storage does not implement the interface
    // required to implement this call.
    hr = E_NOINTERFACE;
  }

  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
}


void ImplAAFOMRawStorage::streamWriteAt(OMUInt64 position,
                                        const OMByte* bytes,
                                        OMUInt32 byteCount,
                                        OMUInt32& bytesWritten)
{
  ASSERTU (_randRep);
  AAFRESULT hr = AAFRESULT_SUCCESS;
  if (_streamRep)
  {
    hr = _streamRep->StreamWriteAt (position, bytes, byteCount, &bytesWritten);
  }
  else
  {
    hr = _randRep->WriteAt (position, bytes, byteCount, &bytesWritten);
  }

  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  _position = position + bytesWritten;
}

void ImplAAFOMRawStorage::streamWriteAt(OMUInt64 position,
                                        OMIOBufferDescriptor* buffers,
                                        OMUInt32 bufferCount,
                                        OMUInt32& bytesWritten)
{
  ASSERTU (_randRep);
  AAFRESULT hr = AAFRESULT_SUCCESS;
  if (_streamRep)
  {
    aafIOBufferDesc_t*  aafBuffers =
        reinterpret_cast<aafIOBufferDesc_t*>(buffers);
    hr = _streamRep->StreamWriteGatherAt (position,
                                          aafBuffers,
                                          bufferCount,
                                          &bytesWritten);
  }
  else
  {
    bytesWritten = 0;
    OMUInt64 currentPosition = position;
    for (OMUInt32 i=0; i<bufferCount && hr == AAFRESULT_SUCCESS; i++)
    {
      OMUInt32  bufferBytesWritten = 0;
      hr = _randRep->WriteAt (currentPosition,
                              buffers[i]._buffer,
                              buffers[i]._bufferSize,
                              &bufferBytesWritten);
      bytesWritten += bufferBytesWritten;
      currentPosition += bufferBytesWritten;
    }
  }

  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  _position = position + bytesWritten;
}

void ImplAAFOMRawStorage::streamWriteAt(OMUInt64 position,
                                        const OMByte* buffer,
                                        const OMUInt32 bytes,
                                        void* /* */ completion,
                                        const void* clientArgument)
{
  AAFRESULT hr = AAFRESULT_SUCCESS;

  if (_asyncStreamRep)
  {
    IAAFIOCompletion*  aafCompletion =
        reinterpret_cast<IAAFIOCompletion*>(completion);
    aafMemConstPtr_t  aafClientArgument =
        reinterpret_cast<aafMemConstPtr_t>(clientArgument);
    _pending->chainTo(aafCompletion, aafClientArgument);
    hr = _asyncStreamRep->StreamWriteAsyncAt (position,
                                              buffer,
                                              bytes,
                                              _pending,
                                              0);
  }
  else
  {
    // The raw storage does not implement the interface
    // required to implement this call.
    hr = E_NOINTERFACE;
  }

  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
}

void ImplAAFOMRawStorage::streamWriteAt(OMUInt64 position,
                                        const OMIOBufferDescriptor* buffers,
                                        OMUInt32 bufferCount,
                                        void* /* */ completion,
                                        const void* clientArgument)
{
  AAFRESULT hr = AAFRESULT_SUCCESS;

  if (_asyncStreamRep)
  {
    const aafIOBufferDesc_t*  aafBuffers =
        reinterpret_cast<const aafIOBufferDesc_t*>(buffers);
    IAAFIOCompletion*  aafCompletion =
        reinterpret_cast<IAAFIOCompletion*>(completion);
    aafMemConstPtr_t  aafClientArgument =
        reinterpret_cast<aafMemConstPtr_t>(clientArgument);
    _pending->chainTo(aafCompletion, aafClientArgument);
    hr = _asyncStreamRep->StreamWriteGatherAsyncAt (position,
                                                    aafBuffers,
                                                    bufferCount,
                                                    _pending,
                                                    0);
  }
  else
  {
    // The raw storage does not implement the interface
    // required to implement this call.
    hr = E_NOINTERFACE;
  }

  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
}

// ImplAAFOMCachedRawStorage methods

ImplAAFOMCachedRawStorage::ImplAAFOMCachedRawStorage(IAAFRandomRawStorage* randRep,
                                                     aafUInt32  pageCount,
                                                     aafUInt32  pageSize,
                                                     OMCachePageAllocator* allocator )
: OMBaseCachedDiskRawStorage(pageSize, pageCount, getRawStorageSize(randRep), allocator),
  _rep(0),
  _randRep(randRep)
{
  ASSERTU (randRep);
  _randRep->AddRef ();

  AAFRESULT hr;
  hr = _randRep->QueryInterface(IID_IAAFRawStorage, (void **)&_rep);
  if (AAFRESULT_FAILED (hr))
	_rep = 0;
}

ImplAAFOMCachedRawStorage::~ImplAAFOMCachedRawStorage()
{
  ASSERTU (_rep);
  _rep->Release ();
  _rep = 0;

  if (_randRep)
	{
	  _randRep->Release ();
	  _randRep = 0;
	}
}

bool ImplAAFOMCachedRawStorage::isReadable(void) const
{
  ASSERTU (_rep);
  aafBoolean_t r;
  AAFRESULT hr;
  hr = _rep->IsReadable (&r);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  return r ? true : false;
}

bool ImplAAFOMCachedRawStorage::isWritable(void) const
{
  ASSERTU (_rep);
  aafBoolean_t r;
  AAFRESULT hr;
  hr = _rep->IsWriteable (&r);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  return r ? true : false;
}

bool ImplAAFOMCachedRawStorage::isExtendible(void) const
{
  ASSERTU (_rep);

  // If not an AAFRandomRawStorage, it's definitely not extendible.
  if (! _randRep)
	return false;

  AAFRESULT hr;
  aafBoolean_t r;
  hr = _randRep->IsExtendable (&r);
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
  return r ? true : false;
}

bool ImplAAFOMCachedRawStorage::isPositionable(void) const
{
  ASSERTU (_rep);
  // If not an AAFRandomRawStorage, it's not positionable.
  if (_randRep)
	return true;
  else
	return false;
}

void ImplAAFOMCachedRawStorage::synchronize(void)
{
  if (isWritable()) {
    flush();
  }
  ASSERTU (_rep);
  AAFRESULT hr;
  hr = _rep->Synchronize ();
  if (AAFRESULT_FAILED (hr)) throw OMException(hr);
}

void ImplAAFOMCachedRawStorage::streamReadAt(OMUInt64 /* position */,
                                             OMByte* /* bytes */,
                                             OMUInt32 /* byteCount */,
                                             OMUInt32& /* bytesRead */) const
{
  ASSERTU(false);
}

void ImplAAFOMCachedRawStorage::streamReadAt(
                                           OMUInt64 /* position */,
                                           OMIOBufferDescriptor* /* buffers */,
                                           OMUInt32 /* bufferCount */,
                                           OMUInt32& /* bytesRead */) const
{
  ASSERTU(false);
}

void ImplAAFOMCachedRawStorage::streamReadAt(
                                        OMUInt64 /* position */,
                                        OMByte* /* buffer */,
                                        const OMUInt32 /* bytes */,
                                        void* /* */ /* completion */,
                                        const void* /* clientArgument */) const
{
  ASSERTU(false);
}

void ImplAAFOMCachedRawStorage::streamReadAt(
                                        OMUInt64 /* position */,
                                        OMIOBufferDescriptor* /* buffers */,
                                        OMUInt32 /* bufferCount */,
                                        void* /* */ /* completion */,
                                        const void* /* clientArgument */) const
{
  ASSERTU(false);
}

void ImplAAFOMCachedRawStorage::streamWriteAt(OMUInt64 /* position */,
                                              const OMByte* /* bytes */,
                                              OMUInt32 /* byteCount */,
                                              OMUInt32& /* bytesWritten */)
{
  ASSERTU(false);
}

void ImplAAFOMCachedRawStorage::streamWriteAt(
                                           OMUInt64 /* position */,
                                           OMIOBufferDescriptor* /* buffers */,
                                           OMUInt32 /* bufferCount */,
                                           OMUInt32& /* bytesWritten */)
{
  ASSERTU(false);
}

void ImplAAFOMCachedRawStorage::streamWriteAt(OMUInt64 /* position */,
                                              const OMByte* /* buffer */,
                                              const OMUInt32 /* bytes */,
                                              void* /* */ /* completion */,
                                              const void* /* clientArgument */)
{
  ASSERTU(false);
}

void ImplAAFOMCachedRawStorage::streamWriteAt(
                                     OMUInt64 /* position */,
                                     const OMIOBufferDescriptor* /* buffers */,
                                     OMUInt32 /* bufferCount */,
                                     void* /* */ /* completion */,
                                     const void* /* clientArgument */)
{
  ASSERTU(false);
}

void ImplAAFOMCachedRawStorage::rawReadAt(OMUInt64 position,
                                          OMUInt32 byteCount,
                                          OMByte* destination)
{
  ASSERTU(_randRep);
  ASSERTU(byteCount != 0);

  OMUInt32 bytesRead = 0;
  AAFRESULT hr = _randRep->ReadAt(position, destination, byteCount, &bytesRead);
  if (AAFRESULT_FAILED(hr) || (bytesRead != byteCount)) {
    throw OMException(hr);
  }
}


void ImplAAFOMCachedRawStorage::rawWriteAt(OMUInt64 position,
                                           OMUInt32 byteCount,
                                           const OMByte* source)
{
  ASSERTU(_randRep);
  ASSERTU(byteCount != 0);

  OMUInt32 bytesWritten = 0;
  AAFRESULT hr = _randRep->WriteAt(position, source, byteCount, &bytesWritten);
  if (AAFRESULT_FAILED(hr) || (bytesWritten != byteCount)) {
    throw OMException(hr);
  }
}


/*static*/ aafUInt64 ImplAAFOMCachedRawStorage::getRawStorageSize(
    IAAFRandomRawStorage* pRandomRawStorage )
{
  ASSERTU (pRandomRawStorage);

  aafUInt64 rawStorageSize = 0;

  pRandomRawStorage->GetSize(&rawStorageSize);

  return rawStorageSize;
}

ChainedIOCompletion* ChainedIOCompletion::Create()
{
  ChainedIOCompletion* result = new ChainedIOCompletion();
  ASSERTU(result);
  result->AddRef();
  return result;
}

HRESULT STDMETHODCALLTYPE ChainedIOCompletion::QueryInterface(
  REFIID iid,
  void** ppIfc)
{
    if( !ppIfc )
    {
        return AAFRESULT_NULL_PARAM;
    }

    if( aafIsEqualIID( iid, IID_IUnknown ) )
    {
        IUnknown* runk = (IUnknown*)this;
        *ppIfc = (void*)runk;
        AddRef();
        return AAFRESULT_SUCCESS;
    }
    else if( aafIsEqualIID( iid, IID_IAAFIOCompletion ) )
    {
        IAAFIOCompletion* rioc = this;
        *ppIfc = (void*) rioc;
        AddRef();
        return AAFRESULT_SUCCESS;
    }
    else
    {
        return E_NOINTERFACE;
    }
}

aafUInt32 STDMETHODCALLTYPE ChainedIOCompletion::AddRef()
{
    _refCount++;
    return _refCount;
}

aafUInt32 STDMETHODCALLTYPE ChainedIOCompletion::Release()
{
    const aafUInt32  r = --_refCount;
    if( r == 0 )
    {
        delete this;
    }

    return r;
}

AAFRESULT STDMETHODCALLTYPE ChainedIOCompletion::Completed(
    HRESULT  completionStatus,
    aafUInt32  numTransferred,
    aafMemConstPtr_t  ANAME(pClientData))
{
    TRACE("ChainedIOCompletion::Completed");
    PRECONDITION("Chained", _pCompletion != 0);
    PRECONDITION("Recognized client data", pClientData == 0);

    HRESULT hr = _pCompletion->Completed(completionStatus,
                                         numTransferred,
                                         _pClientData);
    _pCompletion->Release();
 
    _pCompletion = 0;
    _pClientData = 0;
    POSTCONDITION("Not chained", _pCompletion == 0);
    return hr;
}

void ChainedIOCompletion::chainTo(
    IAAFIOCompletion* pCompletion,
    aafMemConstPtr_t pClientData)
{
    TRACE("ChainedIOCompletion::chainTo");
    PRECONDITION("Not chained", _pCompletion == 0);
    _pCompletion = pCompletion;
    _pCompletion->AddRef();
    _pClientData = pClientData;
    POSTCONDITION("Chained", _pCompletion != 0);
}

ChainedIOCompletion::ChainedIOCompletion()
: _refCount(0),
  _pCompletion(0),
  _pClientData(0)
{
}

ChainedIOCompletion::~ChainedIOCompletion()
{
    TRACE("ChainedIOCompletion::~ChainedIOCompletion");
    PRECONDITION("Not chained", _pCompletion == 0);
}
