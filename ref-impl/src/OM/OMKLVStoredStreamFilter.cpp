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
#include "OMKLVStoredStreamFilter.h"

#include "OMAssertions.h"
#include "OMKLVStoredStream.h"
#include "OMMXFStorage.h"
#include "OMUtilities.h"

OMKLVStoredStreamFilter::OMKLVStoredStreamFilter(OMKLVStoredStream* stream)
: _stream(stream),
  _initialized(false),
  _keyWritten(false),
  _dirty(false),
  _position(0),
  _klvLength(0),
  _klvLengthOffset(0),
  _klvValueOffset(0)
{
  TRACE("OMKLVStoredStreamFilter::OMKLVStoredStreamFilter");

  POSTCONDITION("Valid stream", _stream != 0);
}

OMKLVStoredStreamFilter::~OMKLVStoredStreamFilter(void)
{
  TRACE("OMKLVStoredStreamFilter::~OMKLVStoredStreamFilter");

  // We don't own the stream
  _stream = 0;
}

void OMKLVStoredStreamFilter::read(void* ANAME(data), OMUInt32 ANAME(size)) const
{
  TRACE("OMKLVStoredStreamFilter::read");
  PRECONDITION("Valid data buffer", data != 0);
  PRECONDITION("Valid size", size > 0);

  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

void OMKLVStoredStreamFilter::read(OMByte* data,
                             const OMUInt32 bytes,
                             OMUInt32& bytesRead) const
{
  TRACE("OMKLVStoredStreamFilter::read");
  PRECONDITION("Valid data buffer", data != 0);
  PRECONDITION("Valid size", bytes > 0);

  if (!_initialized) {
    initialize();
  }

  const OMUInt64 remainingBytes = _klvLength - _position;
  OMUInt32 bytesToRead;
  if (bytes <= remainingBytes) {
    bytesToRead = bytes;
  } else {
    ASSERT("Supported byte count", remainingBytes < ~(OMUInt32)0);
    bytesToRead = static_cast<OMUInt32>(remainingBytes);
  }
  if (bytesToRead > 0) {
    _stream->setPosition(_klvValueOffset + _position);
    _stream->read(data, bytesToRead, bytesRead);

    OMKLVStoredStreamFilter* non_const_this =
                                    const_cast<OMKLVStoredStreamFilter*>(this);
    non_const_this->_position += bytesRead;
  } else {
    bytesRead = 0;
  }
}

void OMKLVStoredStreamFilter::read(OMIOBufferDescriptor* buffers,
                                   OMUInt32 bufferCount,
                                   OMUInt32& bytesRead) const
{
  TRACE("OMKLVStoredStreamFilter::read");
  PRECONDITION("Valid buffers", buffers != 0);
  PRECONDITION("Valid buffer count", bufferCount > 0);

  if (!_initialized) {
    initialize();
  }

  _stream->setPosition(_klvValueOffset + _position);
  _stream->read(buffers, bufferCount, bytesRead);

  OMKLVStoredStreamFilter* non_const_this =
                                    const_cast<OMKLVStoredStreamFilter*>(this);
  non_const_this->_position += bytesRead;
}

void OMKLVStoredStreamFilter::read(OMUInt64 position,
                                   OMByte* buffer,
                                   const OMUInt32 bytes,
                                   void* /* */ completion,
                                   const void* clientArgument) const
{
  TRACE("OMKLVStoredStreamFilter::read");
  PRECONDITION("Valid data buffer", buffer != 0);
  PRECONDITION("Valid size", bytes > 0);

  if (!_initialized) {
    initialize();
  }

  _stream->read(_klvValueOffset + position,
                buffer,
                bytes,
                completion,
                clientArgument);
}

void OMKLVStoredStreamFilter::read(OMUInt64 position,
                                   OMIOBufferDescriptor* buffers,
                                   OMUInt32 bufferCount,
                                   void* /* */ completion,
                                   const void* clientArgument) const
{
  TRACE("OMKLVStoredStreamFilter::read");
  PRECONDITION("Valid buffers", buffers != 0);
  PRECONDITION("Valid buffer count", bufferCount > 0);

  if (!_initialized) {
    initialize();
  }

  _stream->read(_klvValueOffset + position,
                buffers,
                bufferCount,
                completion,
                clientArgument);
}

void OMKLVStoredStreamFilter::write(void* ANAME(data), OMUInt32 ANAME(size))
{
  TRACE("OMKLVStoredStreamFilter::write");
  PRECONDITION("Valid data", data != 0);
  PRECONDITION("Valid size", size > 0);

  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

void OMKLVStoredStreamFilter::write(const OMByte* data,
                                      const OMUInt32 bytes,
                                      OMUInt32& bytesWritten)
{
  TRACE("OMKLVStoredStreamFilter::write");
  PRECONDITION("Valid data", data != 0);
  PRECONDITION("Valid size", bytes > 0);

  if (!_initialized) {
    initialize();
  }

  if (!_keyWritten)
  {
    writeKey();
  }

  _stream->setPosition(_klvValueOffset + _position);
  _stream->write(data, bytes, bytesWritten);
  _position = _position + bytesWritten;
  if (_position > _klvLength) {
    _klvLength = _position;
    _dirty = true;
  }
}

void OMKLVStoredStreamFilter::write(OMIOBufferDescriptor* buffers,
                                    OMUInt32 bufferCount,
                                    OMUInt32& bytesWritten)
{
  TRACE("OMKLVStoredStreamFilter::write");
  PRECONDITION("Valid buffers", buffers != 0);
  PRECONDITION("Valid buffer count", bufferCount > 0);

  if (!_initialized) {
    initialize();
  }

  if (!_keyWritten)
  {
    writeKey();
  }

  _stream->setPosition(_klvValueOffset + _position);
  _stream->write(buffers,
                 bufferCount,
                 bytesWritten);
  _position = _position + bytesWritten;
  if (_position > _klvLength) {
    _klvLength = _position;
    _dirty = true;
  }
}

void OMKLVStoredStreamFilter::write(OMUInt64 position,
                                    const OMByte* buffer,
                                    const OMUInt32 bytes,
                                    void* /* */ completion,
                                    const void* clientArgument)
{
  TRACE("OMKLVStoredStreamFilter::write");
  PRECONDITION("Valid data", buffer != 0);
  PRECONDITION("Valid size", bytes > 0);

  if (!_initialized) {
    initialize();
  }

  if (!_keyWritten)
  {
    writeKey();
  }

  _stream->write(_klvValueOffset + position,
                 buffer,
                 bytes,
                 completion,
                 clientArgument);
  const OMUInt64 estimatedNewPosition = position + bytes;
  if (estimatedNewPosition > _klvLength) {
    _klvLength = estimatedNewPosition;
    _dirty = true;
  }
}

  // Asynchronous write - multiple buffers
void OMKLVStoredStreamFilter::write(OMUInt64 position,
                                    const OMIOBufferDescriptor* buffers,
                                    OMUInt32 bufferCount,
                                    void* /* */ completion,
                                    const void* clientArgument)
{
  TRACE("OMKLVStoredStreamFilter::write");
  PRECONDITION("Valid buffers", buffers != 0);
  PRECONDITION("Valid buffer count", bufferCount > 0);

  if (!_initialized) {
    initialize();
  }

  if (!_keyWritten)
  {
    writeKey();
  }

  _stream->write(_klvValueOffset + position,
                 buffers,
                 bufferCount,
                 completion,
                 clientArgument);
  const OMUInt64 estimatedNewPosition =
                            position + ioVectorByteCount(buffers, bufferCount);
  if (estimatedNewPosition > _klvLength) {
    _klvLength = estimatedNewPosition;
    _dirty = true;
  }
}

OMUInt64 OMKLVStoredStreamFilter::size(void) const
{
  TRACE("OMKLVStoredStreamFilter::size");

  if (!_initialized) {
    initialize();
  }

  return _klvLength;
}

void OMKLVStoredStreamFilter::setSize(const OMUInt64 newSize)
{
  TRACE("OMKLVStoredStreamFilter::setSize");

  if (!_initialized) {
    initialize();
  }

  OMUInt64 currentPosition = _stream->position();

  _stream->setSize(_klvValueOffset + newSize);
  _klvLength = newSize;

  // Update KLV length
  _stream->setPosition(_klvValueOffset + newSize);
  OMKLVStoredStream::fixupKLVLength(*_stream, _klvLengthOffset);
  _stream->setPosition(currentPosition);
}

OMUInt64 OMKLVStoredStreamFilter::position(void) const
{
  TRACE("OMKLVStoredStreamFilter::position");

  if (!_initialized) {
    initialize();
  }

  return _position;
}

void OMKLVStoredStreamFilter::setPosition(const OMUInt64 newPosition) const
{
  TRACE("OMKLVStoredStreamFilter::setPosition");

  if (!_initialized) {
    initialize();
  }

  _stream->setPosition(_klvValueOffset + newPosition);
  OMKLVStoredStreamFilter* non_const_this =
                                    const_cast<OMKLVStoredStreamFilter*>(this);
  non_const_this->_position = newPosition;
}

void OMKLVStoredStreamFilter::synchronize(void) const
{
  TRACE("OMKLVStoredStreamFilter::synchronize");

  if (_initialized && _dirty) {
    const OMUInt64 savedPosition = _stream->position();
    OMKLVStoredStreamFilter* non_const_this =
                                    const_cast<OMKLVStoredStreamFilter*>(this);

    // Discrepancy between the length maintained by the filter and
    // the actual stream length indicates that the stream has been
    // modified outside this filter.
    if ((_klvValueOffset + _klvLength) < _stream->size()) {
      non_const_this->_klvLength = _stream->size() - _klvValueOffset;
    }

	// Go to the end of the stream
    _stream->setPosition(_klvValueOffset + _klvLength);
    // Update KLV length
    OMKLVStoredStream::fixupKLVLength(*_stream, _klvLengthOffset);
    _stream->setPosition(savedPosition);
    non_const_this->_dirty = false;
  }
}

void OMKLVStoredStreamFilter::close(void)
{
  TRACE("OMKLVStoredStreamFilter::close");

  _stream->close();
}

const OMStoredStream* OMKLVStoredStreamFilter::stream(void) const
{
  TRACE("OMKLVStoredStreamFilter::stream");
  return _stream;
}

OMStoredStream* OMKLVStoredStreamFilter::stream(void)
{
  TRACE("OMKLVStoredStreamFilter::stream");
  return _stream;
}

OMUInt32 OMKLVStoredStreamFilter::streamIdentification(void) const
{
  TRACE("OMKLVStoredStreamFilter::streamIdentification");
  return _stream->streamIdentification();
}

  // @mfunc Set the label to <p label>.
  //   @parm The new label.
void OMKLVStoredStreamFilter::setLabel(const OMKLVKey& label)
{
  TRACE("OMKLVStoredStreamFilter::setLabel");
  _stream->setLabel(label);
}

  // @mfunc Get the label.
  //   @rdesc The label.
OMKLVKey OMKLVStoredStreamFilter::label(void) const
{
  TRACE("OMKLVStoredStreamFilter::label");
  return _stream->label();
}

  // @mfunc Set the block size (alignment) of this essence element.
  //   @parm The block size.
void OMKLVStoredStreamFilter::setBlockSize(OMUInt32 blockSize)
{
  TRACE("OMKLVStoredStreamFilter::setBlockSize");
  _stream->setBlockSize(blockSize);
}

  // @mfunc The block size (alignment) of this essence element.
  //   @rdesc The block size.
OMUInt32 OMKLVStoredStreamFilter::blockSize(void) const
{
  TRACE("OMKLVStoredStreamFilter::blockSize");
  return _stream->blockSize();
}

void OMKLVStoredStreamFilter::initialize(void) const
{
  TRACE("OMKLVStoredStreamFilter::initialize");
  PRECONDITION("Not already initialized", _initialized == false);

  // Remember the current stream position
  const OMUInt64 currentStreamPosition = _stream->position();

  OMUInt64 lengthPosition = 0;
  OMUInt64 length = 0;
  OMUInt64 valuePosition = 0;

  // Attempt to read the key at the beginning of the stream
  bool readKL = false;
  _stream->setPosition(0);
  OMKLVKey key;
  if (OMKLVStoredStream::readKLVKey(*_stream, key)) {
    lengthPosition = _stream->position();

    // Attempt to read the length following the key
    if (OMKLVStoredStream::readKLVLength(*_stream, length)) {
      valuePosition = _stream->position();
      // If this initialize() is called on stream that's being
      // written to it's possible that the stream KLV length in
      // the file is not up-to-date. If the stream size reported
      // by OMStoredStream is larger than the size recorded in the
      // file assume that the latter is expired.
      if (length == 0) {
        if (_stream->size() > valuePosition) {
          length = _stream->size() - valuePosition;
        }
      }
      readKL = true;
    }
  }

  // If failed to read key an length assume the defaults
  if (!readKL) {
    lengthPosition = 16;
    length = 0;
    valuePosition = lengthPosition + 8 + 1;
  }

  OMKLVStoredStreamFilter* non_const_this =
                                    const_cast<OMKLVStoredStreamFilter*>(this);
  non_const_this->_klvLengthOffset = lengthPosition;
  non_const_this->_klvLength = length;
  non_const_this->_klvValueOffset = valuePosition;
  if (currentStreamPosition > _klvValueOffset) {
    ASSERTU(currentStreamPosition >= _klvValueOffset);
    non_const_this->_position = currentStreamPosition - _klvValueOffset;
  } else {
    non_const_this->_position = 0;
  }
  non_const_this->_initialized = true;

  // Restore the current stream position
  _stream->setPosition( currentStreamPosition );
}

void OMKLVStoredStreamFilter::writeKey(void)
{
  TRACE("OMKLVStoredStreamFilter::writeKey");
  PRECONDITION("Key not already written", _keyWritten == false);

  OMKLVKey key = _stream->label();
  if (key == nullOMKLVKey) {
    OMKLVKey defalutKey = {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01,
                           0x0d, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00};
    key = defalutKey;
    _stream->setLabel(key);
  }
  _stream->setPosition(0);
  OMKLVStoredStream::writeKLVKey(*_stream, key);
  _keyWritten = true;

  ARESULT(const OMUInt64 lengthPosition)
                                 OMKLVStoredStream::reserveKLVLength(*_stream);
  POSTCONDITION("Valid KLV length offset", _klvLengthOffset == lengthPosition);
  POSTCONDITION("Valid KLV value offset", _klvValueOffset == _stream->position());
  PRECONDITION("Key written", _keyWritten == true);
}
