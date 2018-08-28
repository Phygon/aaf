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

// @doc OMINTERNAL
// @author Tim Bingham | tjb | Avid Technology, Inc. | OMSSStoredStream

#ifndef OM_NO_STRUCTURED_STORAGE

#include "OMStructuredStorage.h"

#include "OMSSStoredStream.h"
#include "OMAssertions.h"
#include "OMExceptions.h"
#include "OMTransparentStoredStreamFilter.h"

static void checkStatus(HRESULT status);

OMSSStoredStream::OMSSStoredStream(IStream* stream)
: _stream(stream)
{
  TRACE("OMSSStoredStream::OMSSStoredStream");
  PRECONDITION("Valid stream", _stream != 0);
}

OMSSStoredStream::~OMSSStoredStream(void)
{
  TRACE("OMSSStoredStream::~OMSSStoredStream");
  PRECONDITION("Stream not open", _stream == 0);
}

void OMSSStoredStream::read(void* data, OMUInt32 size) const
{
  TRACE("OMSSStoredStream::read");
  PRECONDITION("Valid stream", _stream != 0);
  PRECONDITION("Valid data buffer", data != 0);
  PRECONDITION("Valid size", size > 0);

  ULONG bytesRead;
  HRESULT result = _stream->Read(data, size, &bytesRead);
  checkStatus(result);
  ASSERT("Succeeded", SUCCEEDED(result));

  ASSERT("Successful read", bytesRead == size);
}

void OMSSStoredStream::read(OMByte* data,
                             const OMUInt32 bytes,
                             OMUInt32& bytesRead) const
{
  TRACE("OMSSStoredStream::read");
  PRECONDITION("Valid stream", _stream != 0);
  PRECONDITION("Valid data buffer", data != 0);
  PRECONDITION("Valid size", bytes > 0);

  // HACK ALERT for GCC/Linux - Accomodate any variety of int and long incompatibility
  ULONG tempLong=static_cast<ULONG>(bytesRead);
  HRESULT result = _stream->Read(data, bytes, &tempLong);
  bytesRead=static_cast<OMUInt32>(tempLong);
  checkStatus(result);
  ASSERT("Succeeded", SUCCEEDED(result));
}

  // @mfunc Attempt to read the vector of buffers given by <p buffers>
  //        from this <c OMSSStoredStream>. This is "read scatter". The
  //        <p bufferCount> buffers are read in order until all have
  //        been successfully read or an error is encountered. Once
  //        an error has been encountered on one buffer no additional
  //        buffers are read.
  //        The number of bytes read is returned in <p bytesRead>.
  //   @parm The vector of buffers into which the bytes are to be read.
  //   @parm The count of buffers.
  //   @parm The actual number of bytes that were read.
void OMSSStoredStream::read(OMIOBufferDescriptor* buffers,
                             OMUInt32 bufferCount,
                             OMUInt32& bytesRead) const
{
  TRACE("OMSSStoredStream::read");

  OMUInt32 totalBytesRead = 0;
  for (OMUInt32 i = 0; i < bufferCount; i++) {
    OMUInt32 readCount;
    read(buffers[i]._buffer, buffers[i]._bufferSize, readCount);
    totalBytesRead = totalBytesRead + readCount;
    if (readCount != buffers[i]._bufferSize) {
      break;
    }
  }
  bytesRead = totalBytesRead;
}

  // Asynchronous read - single buffer
void OMSSStoredStream::read(OMUInt64 /* position */,
                             OMByte* /* buffer */,
                             const OMUInt32 /* bytes */,
                             void* /* */ /* completion */,
                             const void* /* clientArgument */)
{
  TRACE("OMSSStoredStream::read");
  ASSERT("Unimplemented code not reached", false);
}

  // Asynchronous read - multiple buffers
void OMSSStoredStream::read(OMUInt64 /* position */,
                             OMIOBufferDescriptor* /* buffers */,
                             OMUInt32 /* bufferCount */,
                             void* /* */ /* completion */,
                             const void* /* clientArgument */) const
{
  TRACE("OMSSStoredStream::read");
  ASSERT("Unimplemented code not reached", false);
}

void OMSSStoredStream::probe(OMUInt64 /* position */,
                              OMUInt32 /* bytesRequired */,
                              OMUInt32& /* bytesAvailable */) const
{
  TRACE("OMSSStoredStream::probe");
  ASSERT("Unimplemented code not reached", false);
}

void OMSSStoredStream::write(void* data, OMUInt32 size)
{
  TRACE("OMSSStoredStream::write");
  PRECONDITION("Valid stream", _stream != 0);
  PRECONDITION("Valid data", data != 0);
  PRECONDITION("Valid size", size > 0);

  ULONG bytesWritten;
  HRESULT resultCode = _stream->Write(data, size, &bytesWritten);
  checkStatus(resultCode);
  ASSERT("Succeeded", SUCCEEDED(resultCode));

  ASSERT("Successful write", bytesWritten == size);
}

void OMSSStoredStream::write(const OMByte* data,
                              const OMUInt32 bytes,
                              OMUInt32& bytesWritten)
{
  TRACE("OMSSStoredStream::write");
  PRECONDITION("Valid stream", _stream != 0);
  PRECONDITION("Valid data", data != 0);
  PRECONDITION("Valid size", bytes > 0);

  // HACK ALERT for GCC/Linux - Accomodate any variety of int and long incompatibility
  ULONG tempLong=static_cast<ULONG>(bytesWritten);
  HRESULT resultCode = _stream->Write(data, bytes, &tempLong);
  bytesWritten=static_cast<OMUInt32>(tempLong);
  checkStatus(resultCode);
  ASSERT("Succeeded", SUCCEEDED(resultCode));
}

  // @cmember Attempt to write the vector of buffers given by <p buffers>
  //          to this <c OMSSStoredStream>. This is "write gather". The
  //          <p bufferCount> buffers are written in order until all have
  //          been successfully written or an error is encountered. Once
  //          an error has been encountered on one buffer no additional
  //          buffers are written.
  //          The number of bytes written is returned in <p bytesWritten>.
  //   @parm The vector of buffers from which the bytes are to be written.
  //   @parm The count of buffers.
  //   @parm The actual number of bytes that were written.
void OMSSStoredStream::write(OMIOBufferDescriptor* buffers,
                              OMUInt32 bufferCount,
                              OMUInt32& bytesWritten)
{
  TRACE("OMSSStoredStream::write");

  OMUInt32 totalBytesWritten = 0;
  for (OMUInt32 i = 0; i < bufferCount; i++) {
    OMUInt32 writeCount;
    write(buffers[i]._buffer, buffers[i]._bufferSize, writeCount);
    totalBytesWritten = totalBytesWritten + writeCount;
    if (writeCount != buffers[i]._bufferSize) {
      break;
    }
  }
  bytesWritten = totalBytesWritten;
}

  // Asynchronous write - single buffer
void OMSSStoredStream::write(OMUInt64 /* position */,
                              const OMByte* /* buffer */,
                              const OMUInt32 /* bytes */,
                              void* /* */ /* completion */,
                              const void* /* clientArgument */)
{
  TRACE("OMSSStoredStream::write");
  ASSERT("Unimplemented code not reached", false);
}

  // Asynchronous write - multiple buffers
void OMSSStoredStream::write(OMUInt64 /* position */,
                              const OMIOBufferDescriptor* /* buffers */,
                              OMUInt32 /* bufferCount */,
                              void* /* */ /* completion */,
                              const void* /* clientArgument */)
{
  TRACE("OMSSStoredStream::write");
  ASSERT("Unimplemented code not reached", false);
}

OMUInt64 OMSSStoredStream::size(void) const
{
  TRACE("OMSSStoredStream::size");
  PRECONDITION("Valid stream", _stream != 0);

  STATSTG statstg;
  HRESULT status = _stream->Stat(&statstg, STATFLAG_NONAME);
  checkStatus(status);
  ASSERT("Succeeded", SUCCEEDED(status));

  OMUInt64 result = toOMUInt64(statstg.cbSize);
  return result;
}

void OMSSStoredStream::setSize(const OMUInt64 newSize)
{
  TRACE("OMSSStoredStream::setSize");

  ULARGE_INTEGER newStreamSize = fromOMUInt64(newSize);
  HRESULT status = _stream->SetSize(newStreamSize);
  checkStatus(status);
  ASSERT("Succeeded", SUCCEEDED(status));
}

OMUInt64 OMSSStoredStream::position(void) const
{
  TRACE("OMSSStoredStream::position");
  PRECONDITION("Valid stream", _stream != 0);

  OMUInt64 result;
  LARGE_INTEGER zero = {0, 0};
  ULARGE_INTEGER position;
  HRESULT status = _stream->Seek(zero, STREAM_SEEK_CUR, &position);
  checkStatus(status);
  ASSERT("Succeeded", SUCCEEDED(status));

  result = toOMUInt64(position);
  return result;
}

void OMSSStoredStream::setPosition(const OMUInt64 offset) const
{
  TRACE("OMSSStoredStream::setPosition");
  PRECONDITION("Valid stream", _stream != 0);

  ULARGE_INTEGER newPosition = fromOMUInt64(offset);
  ULARGE_INTEGER oldPosition;
  LARGE_INTEGER position;
  memcpy(&position, &newPosition, sizeof(LARGE_INTEGER));
  HRESULT status = _stream->Seek(position, STREAM_SEEK_SET, &oldPosition);
  checkStatus(status);
  ASSERT("Succeeded", SUCCEEDED(status));
}

void OMSSStoredStream::close(void)
{
  TRACE("OMSSStoredStream::close");
  PRECONDITION("Valid stream", _stream != 0);

#if defined(OM_DEBUG)
  HRESULT status = _stream->Release();
  ASSERT("Reference count is 0.", status == 0);
#else
  _stream->Release();
#endif
  _stream = 0;
}

  // @mfunc Does this <c OMStoredStream> know about essence element keys?
  //   @rdesc True if this supports essence element keys, false otherwise.
  //   @this const
bool OMSSStoredStream::hasEssenceElementKey(void) const
{
  TRACE("OMSSStoredStream::hasEssenceElementKey");

  return false;
}

  // @mfunc The essence element key associated with this <c OMStoredStream>.
  //   @rdesc The essence element key.
  //   @this const
OMKLVKey OMSSStoredStream::essenceElementKey(void) const
{
  TRACE("OMSSStoredStream::essenceElementKey");
  PRECONDITION("Stream supports essence element keys", false);

  // Shouldn't be here
  return nullOMKLVKey;
}

  // @mfunc Specify the essence element key for this <c OMStoredStream>.
  //   @parm The essence element key.
void OMSSStoredStream::setEssenceElementKey(const OMKLVKey& /*key*/)
{
  TRACE("OMSSStoredStream::setEssenceElementKey");
  PRECONDITION("Stream supports essence element keys", false);
  // Shouldn't be here
}

OMStoredStreamFilter* OMSSStoredStream::createFilter(void)
{
  TRACE("OMKLVStoredStream::createFilter");

  OMStoredStreamFilter* result = new OMTransparentStoredStreamFilter(this);
  ASSERT("Valid heap pointer", result != 0);
  return result;
}

static void checkStatus(HRESULT status)
{
  TRACE("checkStatus");

  if (FAILED(status)) {
    throw OMException(status);
  }
}

#endif // !OM_NO_STRUCTURED_STORAGE
