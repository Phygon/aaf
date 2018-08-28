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
// @author Tim Bingham | tjb | Avid Technology, Inc. | OMDataStreamProperty

#include "OMDataStreamProperty.h"

#include "OMAssertions.h"
#include "OMExceptions.h"

#include "OMStoredStream.h"
#include "OMPropertySet.h"
#include "OMStorable.h"
#include "OMStoredObject.h"
#include "OMType.h"
#include "OMUtilities.h"
#include "OMDataStreamAccess.h"
#include "OMDataStreamPropertyFilter.h"

  // Copying.

  // @class Provide deferred copying of <c OMDataStream> properties.
  //        This permits OMStorable::deepCopyTo() to construct objects
  //        "bottom up", and to supply the data for <c OMDataStream>
  //        properties only after copying of the objects is complete.
class OMDeferredStream : public OMDataStreamAccess {
public:
  // @access Public members.

  // @cmember Does <c OMDeferredStream> support deferred copying of
  //          this <c OMDataStream>?
  static bool canCopy(const OMDataStream& stream);

    // @cmember Constructor.
    //          Copy the contents of the <p source> stream property into
    //          memory to be written out later in OMDeferredStream::save().
  OMDeferredStream(const OMDataStream& source, void* context);
  virtual ~OMDeferredStream();

    // @cmember Save data to the given <c OMDataStream> object.
    //          This is a call back function supplied by the client.
    //          The client is passed the opaque context
    //          used to construct this <c OMDataStreamAccess> object.
  virtual void save(OMDataStream& destination, void* context);

private:
  OMUInt32 _size;
  OMUInt8* _bytes;

};

  // @mfunc Does <c OMDeferredStream> support deferred copying of
  //        this <c OMDataStream>?
  //   @parm The <c OMDataStream> to validate.
/*static*/ bool OMDeferredStream::canCopy(const OMDataStream& stream)
{
    const OMUInt32 maxSupportedStreamSize = 1024 * 1024 * 16;
    const bool result = (stream.size() <= maxSupportedStreamSize);
    return result;
}

  // @mfunc Constructor.
  //        Copy the contents of the <p source> stream property into
  //        memory to be written out later in OMDeferredStream::save().
OMDeferredStream::OMDeferredStream(const OMDataStream& source, void* context)
: OMDataStreamAccess(context),
  _size(0),
  _bytes(0)
{
  TRACE("OMDeferredStream::OMDeferredStream");

  // Allocate the buffer to hold stream data
  if (!OMDeferredStream::canCopy(source)) {
    throw OMException("Cannot copy stream property");
  }
  const OMUInt64 source_size = source.size();
  ASSERT("Stream size", source.size() < OMUINT32_MAX);
  _size = static_cast<OMUInt32>(source_size);
  _bytes = new OMUInt8[_size];

  // Save current position of source
  const OMUInt64 savedPosition = source.position();

  // Copy the stream contents into memory
  source.setPosition(0);
  OMUInt32 bytesRead = 0;
  source.read(_bytes, _size, bytesRead);
  ASSERT("Read stream bytes", bytesRead == _size);

  // Restore current position of source
  source.setPosition(savedPosition);
}

OMDeferredStream::~OMDeferredStream()
{
  delete [] _bytes;
  _bytes = 0;
}

  // @mfunc Save data to the given <c OMDataStream> object.
  //        This is a call back function supplied by the client.
  //        The client is passed the opaque context
  //        used to construct this <c OMDataStreamAccess> object.
  //   @parm A pointer to the new <p ReferencedObject>.
void OMDeferredStream::save(OMDataStream& destination, void* /*context*/)
{
  TRACE("OMDeferredStream::save");
  PRECONDITION("Valid source bytes", _bytes);

  OMDataStreamProperty& dest =
    dynamic_cast<OMDataStreamProperty&>(destination);
  ASSERT("Valid destination", dest.hasStreamAccess());

  destination.setPosition(0);

  OMUInt32 bytesWritten = 0;
  destination.write(_bytes, _size, bytesWritten);
  ASSERTU(_size == bytesWritten);

  // Source stream data is copied once.
  delete [] _bytes;
  _bytes = 0;

  dest.clearStreamAccess();
  destination.setPosition(0);
}


OMDataStreamProperty::OMDataStreamProperty(const OMPropertyId propertyId,
                                           const wchar_t* name)
: OMDataStream(propertyId, name),
  _stream(0),
  _exists(false),
  _byteOrder(unspecified),
  _streamAccess(0),
  _filter(0)
{
}

OMDataStreamProperty::~OMDataStreamProperty(void)
{
  TRACE("OMDataStreamProperty::~OMDataStreamProperty");

  delete _filter;
  _filter = 0;

  if (_stream != 0) {
    try {
      close();
    } catch (...) {
      _stream = 0;
    }
  }
  POSTCONDITION("Stream closed", _stream == 0);
  delete _streamAccess;
}

void OMDataStreamProperty::detach(void)
{
  if (_stream != 0) {
    try {
      close();
    } catch (...) {
      _stream = 0;
    }
  }

}

  // @mfunc Save this <c OMDataStreamProperty>.
  //   @this const
void OMDataStreamProperty::save(void) const
{
  TRACE("OMDataStreamProperty::save");

  store()->save(*this);

  // The stream has never been written to but we want the stream to
  // exist in the file, create it.
  //
  bool created_here = false;
  OMDataStreamProperty* p = const_cast<OMDataStreamProperty*>(this);
  if (!_exists) {
    p->create();
    created_here = true;
  }
  if (hasStreamAccess()) {
    // Set the current position to the end of the stream
    //
    OMUInt64 lastPosition = size();
    OMUInt64 currentPosition = position();
    if (currentPosition != lastPosition) {
      setPosition(lastPosition);
    }
    // Allow clients to write to the stream
    //
    streamAccess()->save(const_cast<OMDataStreamProperty&>(*this));
  }
  // The following supplements the hack in OMStorable::save(), where
  // an OMStoredObject is closed right after an OMStorable is saved.
  // This causes an OMStoredStream associated with a deferred
  // OMDataStreamProperty (hasStreamAccess() is true) to remain open,
  // after the OMStoredObject associated with the OMStorable containing
  // the stream property is closed. The open OMStoredStream then gets
  // closed when the corresponding OMDataStreamProperty is destroyed.
  // Schemasoft-based implementation of IStorage and IStream interfaces
  // does not support operations on an IStream after its parent IStorage
  // has been closed. Attempting to close an "orphaned" OMStoredStream
  // causes segmentation fault in the Schemasoft Structured Storage library.
  //
  // This hack closes any stream that didn't exist prior to saving the file
  // and that was created during save, after the deferred stream data has
  // been written to the stream. This helps to avoid any issues with trying
  // to access streams whose parent object has already been closed. The hack
  // would potentially affect applications that want to write to stream
  // properties after performing metadata save.
  //
  // The real issue is the Schemasoft-based IStorage and IStream
  // implementation (OMSSIStorage and OMSSIStream), which behaves
  // differently from the Microsoft native implementation. Removing
  // this hack would require an update of OMSSIStorage and OMSSIStream.
  //
  if (created_here)
  {
    p->close();
  }
}

  // @mfunc The number of objects contained within this
  //        <c OMDataStreamProperty> if any.
  //   @rdesc The number of objects.
OMUInt64 OMDataStreamProperty::objectCount(void) const
{
  TRACE("OMDataStreamProperty::objectCount");
  // OMDataStreamProperty doesn't contain objects.
  return 0;
}

  // @mfunc Restore this <c OMDataStreamProperty>, the size of the
  //        <c OMDataStreamProperty> is <p externalSize>.
  //   @parm The size of the <c OMDataStreamProperty>.
void OMDataStreamProperty::restore(OMPropertySize externalSize)
{
  TRACE("OMDataStreamProperty::restore");

  store()->restore(*this, externalSize);
  setPresent();
  _exists = true;
}

  // @mfunc The size, in bytes, of the data in this
  //        <c OMDataStreamProperty>.
  //   @rdesc  The size, in bytes, of the data in this
  //           <c OMDataStreamProperty>.
  //   @this const
OMUInt64 OMDataStreamProperty::size(void) const
{
  TRACE("OMDataStreamProperty::size");

  OMUInt64 result = stream()->size();

  return result;
}

  // @mfunc Set the size, in bytes, of the data in this
  //        <c OMDataStreamProperty>.
  //   @rdesc  The new size, in bytes, of the data in this
  //           <c OMDataStreamProperty>.
void OMDataStreamProperty::setSize(const OMUInt64 newSize)
{
  TRACE("OMDataStreamProperty::setSize");

  stream()->setSize(newSize);
  setPresent();
  POSTCONDITION("Size properly set", size() == newSize);
}

  // @mfunc The current position for <f read()> and <f write()>, as an
  //        offset in bytes from the begining of the data stream.
  //   @rdesc The current position for <f read()> and <f write()>, as an
  //          offset in bytes from the begining of the data stream.
  //   @this const
OMUInt64 OMDataStreamProperty::position(void) const
{
  TRACE("OMDataStreamProperty::position");

  OMUInt64 result = stream()->position();
  return result;
}

  // @mfunc Set the current position for <f read()> and <f write()>, as an
  //        offset in bytes from the begining of the data stream.
  //   @parm The position to use for subsequent calls to read() and
  //         write() on this stream. The position is specified as an
  //         offset in bytes from the begining of the data stream.
  //   @this const
void OMDataStreamProperty::setPosition(const OMUInt64 offset) const
{
  TRACE("OMDataStreamProperty::setPosition");

  stream()->setPosition(offset);

  POSTCONDITION("Position properly set", position() == offset);
}

OMStoredStream* OMDataStreamProperty::stream(void) const
{
  TRACE("OMDataStreamProperty::stream");
  if (_stream == 0) {
    OMDataStreamProperty* p = const_cast<OMDataStreamProperty*>(this);
    if (_exists) {
      p->open();
    } else {
      p->create();
    }
  }
  ASSERT("Valid stream", _stream != 0);
  return _stream;
}

void OMDataStreamProperty::open(void)
{
  TRACE("OMDataStreamProperty::open");
  PRECONDITION("Stream not already opened", _stream == 0);

  _stream = store()->openStoredStream(*this);
  _exists = true;
  POSTCONDITION("Stream opened", _stream != 0);
}

void OMDataStreamProperty::create(void)
{
  TRACE("OMDataStreamProperty::create");
  PRECONDITION("Stream not already created", _stream == 0);

  _stream = store()->createStoredStream(*this);
  _exists = true;
  POSTCONDITION("Stream opened", _stream != 0);
}

void OMDataStreamProperty::close(void)
{
  TRACE("OMDataStreamProperty::close");

  if (_filter != 0) {
    _filter->synchronize();
    delete _filter;
    _filter = 0;
  }
  // Clear stream access callback before deleting the stream in case
  // the callback's destructor wants to fiddle with the stream
  if (hasStreamAccess()) {
    clearStreamAccess();
  }
  if (_stream != 0) {
    _stream->close();
    delete _stream;
    _stream = 0;
  }
  _exists = false;

  POSTCONDITION("Stream closed", _stream == 0);
}

  // @mfunc Attempt to read the number of bytes given by <p bytes>
  //          from the data stream into the buffer at address
  //          <p buffer>. The actual number of bytes read is returned
  //          in <p bytesRead>.
  //   @parm The address of the buffer into which the bytes should be read.
  //   @parm The number of bytes to read.
  //   @parm The actual number of bytes that were read.
  //   @this const
void OMDataStreamProperty::read(OMByte* buffer,
                                const OMUInt32 bytes,
                                OMUInt32& bytesRead) const
{
  TRACE("OMDataStreamProperty::read");

  PRECONDITION("Optional property is present",
                                           IMPLIES(isOptional(), isPresent()));

  stream()->read(buffer, bytes, bytesRead);
}

  // @mfunc  Attempt to write the number of bytes given by <p bytes>
  //         to the data stream from the buffer at address
  //          <p buffer>. The actual number of bytes written is returned
  //          in <p bytesWritten>.
  //   @parm  The address of the buffer from which the bytes should be written.
  //   @parm The number of bytes to write.
  //   @parm The actual number of bytes that were written.
void OMDataStreamProperty::write(const OMByte* buffer,
                                 const OMUInt32 bytes,
                                 OMUInt32& bytesWritten)
{
  TRACE("OMDataStreamProperty::write");

  stream()->write(buffer, bytes, bytesWritten);
  setPresent();
}

  // @mfunc Attempt to read the vector of buffers given by <p buffers>
  //        from this <c OMDataStreamProperty>. This is "read scatter". The
  //        <p bufferCount> buffers are read in order until all have
  //        been successfully read or an error is encountered. Once
  //        an error has been encountered on one buffer no additional
  //        buffers are read.
  //        The number of bytes read is returned in <p bytesRead>.
  //   @parm The vector of buffers into which the bytes are to be read.
  //   @parm The count of buffers.
  //   @parm The actual number of bytes that were read.
void OMDataStreamProperty::read(OMIOBufferDescriptor* buffers,
                                OMUInt32 bufferCount,
                                OMUInt32& bytesRead) const
{
  TRACE("OMDataStreamProperty::read");
  stream()->read(buffers, bufferCount, bytesRead);
}

  // @mfunc Attempt to write the vector of buffers given by <p buffers>
  //        to this <c OMDataStreamProperty>. This is "write gather". The
  //        <p bufferCount> buffers are written in order until all have
  //        been successfully written or an error is encountered. Once
  //        an error has been encountered on one buffer no additional
  //        buffers are written.
  //        The number of bytes written is returned in <p bytesWritten>.
  //   @parm The vector of buffers from which the bytes are to be written.
  //   @parm The count of buffers.
  //   @parm The actual number of bytes that were written.
void OMDataStreamProperty::write(const OMIOBufferDescriptor* buffers,
                                 OMUInt32 bufferCount,
                                 OMUInt32& bytesWritten)
{
  TRACE("OMDataStreamProperty::write");
  OMIOBufferDescriptor* b = const_cast<OMIOBufferDescriptor*>(buffers);
  stream()->write(b, bufferCount, bytesWritten);
  setPresent();
}

    // Asynchronous read - single buffer
void OMDataStreamProperty::read(OMUInt64 position,
                                OMByte* buffer,
                                const OMUInt32 bytes,
                                void* /* */ completion,
                                const void* clientArgument)
{
  TRACE("OMDataStreamProperty::read");

  stream()->read(position, buffer, bytes, completion, clientArgument);
}

    // Asynchronous write - single buffer
void OMDataStreamProperty::write(OMUInt64 position,
                                 const OMByte* buffer,
                                 const OMUInt32 bytes,
                                 void* /* */ completion,
                                 const void* clientArgument)
{
  TRACE("OMDataStreamProperty::write");

  stream()->write(position, buffer, bytes, completion, clientArgument);
  setPresent();
}

    // Asynchronous read - multiple buffers
void OMDataStreamProperty::read(OMUInt64 position,
                                OMIOBufferDescriptor* buffers,
                                OMUInt32 bufferCount,
                                void* /* */ completion,
                                const void* clientArgument) const
{
  TRACE("OMDataStreamProperty::read");

  stream()->read(position, buffers, bufferCount, completion, clientArgument);
}

    // Asynchronous write - multiple buffers
void OMDataStreamProperty::write(OMUInt64 position,
                                 const OMIOBufferDescriptor* buffers,
                                 OMUInt32 bufferCount,
                                 void* /* */ completion,
                                 const void* clientArgument)
{
  TRACE("OMDataStreamProperty::write");

  stream()->write(position, buffers, bufferCount, completion, clientArgument);
  setPresent();
}

  // @mfunc Attempt to read the number of elements given by
  //        <p elementCount> and described by <p elementType> and
  //        <p externalElementSize> from the data stream into the buffer
  //        at address <p elements>. The actual number of elements read
  //        is returned in <p elementsRead>.
  //   @parm The element type
  //   @parm The external element size
  //   @parm The address of the buffer into which the elements should be read.
  //   @parm The number of elements to read.
  //   @parm The actual number of elements that were read.
  //   @this const
void OMDataStreamProperty::readTypedElements(const OMType* elementType,
                                             OMUInt32 externalElementSize,
                                             OMByte* elements,
                                             OMUInt32 elementCount,
                                             OMUInt32& elementsRead) const
{
  TRACE("OMDataStreamProperty::readTypedElements");

  PRECONDITION("Optional property is present",
                                           IMPLIES(isOptional(), isPresent()));
  PRECONDITION("Valid element type", elementType != 0);
  PRECONDITION("Valid element size", externalElementSize!= 0);
  PRECONDITION("Valid buffer", elements != 0);
  PRECONDITION("Valid element count", elementCount > 0);
  PRECONDITION("Stream byte order is known", hasByteOrder());

  OMUInt64 currentPosition = position();
  OMUInt64 streamSize = size();

  OMUInt32 readCount = 0;
  if (currentPosition < streamSize) {
    OMUInt64 remaining = (streamSize - currentPosition) / externalElementSize;
    if (remaining < elementCount) {
      readCount = static_cast<OMUInt32>(remaining);
    } else {
      readCount = elementCount;
    }
  }
  if (readCount > 0) {

    bool reorder = false;
    if (byteOrder() != hostByteOrder()) {
      reorder = true;
    }

    // Allocate buffer for one element
    OMByte* buffer = new OMByte[externalElementSize];

    for (OMUInt32 i = 0; i < readCount; i++) {

      // Read an element of the property value
      OMUInt32 actualByteCount;
      read(buffer, externalElementSize, actualByteCount);
      ASSERT("All bytes read", actualByteCount == externalElementSize);

      // Reorder an element of the property value
      if (reorder) {
        elementType->reorder(buffer, externalElementSize);
      }

      // Internalize an element of the property value
      OMUInt32 requiredBytesSize = elementType->internalSize(
                                                          buffer,
                                                          externalElementSize);

      elementType->internalize(buffer,
                             externalElementSize,
                             &elements[i * requiredBytesSize],
                             requiredBytesSize,
                             hostByteOrder());
    }
    delete [] buffer;
  }
  elementsRead = readCount;
}


  // @mfunc Attempt to write the number of elements given by
  //        <p elementCount> and described by <p elementType> and
  //        <p internalElementSize> to the data stream from the buffer
  //        at address <p elements>. The actual number of elements written
  //        is returned in <p elementsWritten>.
  //   @parm The element type
  //   @parm The internal element size
  //   @parm The address of the buffer from which the elements should
  //         be written.
  //   @parm The number of elements to write.
  //   @parm The actual number of elements that were written.
void OMDataStreamProperty::writeTypedElements(const OMType* elementType,
                                              OMUInt32 internalElementSize,
                                              const OMByte* elements,
                                              OMUInt32 elementCount,
                                              OMUInt32& elementsWritten)
{
  TRACE("OMDataStreamProperty::writeTypedElements");

  PRECONDITION("Valid element type", elementType != 0);
  PRECONDITION("Valid element size", internalElementSize!= 0);
  PRECONDITION("Valid buffer", elements != 0);
  PRECONDITION("Valid element count", elementCount > 0);
  PRECONDITION("Stream byte order is known", hasByteOrder());

  bool reorder = false;
  if (byteOrder() != hostByteOrder()) {
    reorder = true;
  }

  // Allocate buffer for one element
  OMUInt32 externalBytesSize = elementType->externalSize(
                                                 const_cast<OMByte*>(elements),
                                                 internalElementSize);

  OMByte* buffer = new OMByte[externalBytesSize];

  for (OMUInt32 i = 0; i < elementCount; i++) {

    // Externalize an element of the property value
    elementType->externalize(
                       const_cast<OMByte*>(&elements[i * internalElementSize]),
                       internalElementSize,
                       buffer,
                       externalBytesSize,
                       hostByteOrder());

    // Reorder an element of the property value
    if (reorder) {
      elementType->reorder(buffer, externalBytesSize);
    }

    // Write an element of the property value
    OMUInt32 actualByteCount;
    write(buffer, externalBytesSize, actualByteCount);
    ASSERT("All bytes written", actualByteCount == externalBytesSize);
  }
  delete [] buffer;
  elementsWritten = elementCount;
  setPresent();
}

  // @mfunc The size of the raw bits of this
  //        <c OMDataStreamProperty>. The size is given in bytes.
  //   @rdesc The size of the raw bits of this
  //          <c OMDataStreamProperty> in bytes.
  //   @this const
OMUInt32 OMDataStreamProperty::bitsSize(void) const
{
  TRACE("OMDataStreamProperty::bitsSize");

  return sizeof(OMStoredStream*); // tjb !
}

  // @mfunc Get the raw bits of this <c OMDataStreamProperty>.
  //        The raw bits are copied to the buffer at address <p bits> which
  //        is <p size> bytes in size.
  //   @parm The address of the buffer into which the raw bits are copied.
  //   @parm OMUInt32 | size | The size of the buffer.
  //   @this const
void OMDataStreamProperty::getBits(OMByte* bits, OMUInt32 ANAME(size)) const
{
  TRACE("OMDataStreamProperty::getBits");
  PRECONDITION("Valid bits", bits != 0);
  PRECONDITION("Valid size", size >= bitsSize());

  memcpy(bits, &_stream, bitsSize());
}

  // @mfunc Set the raw bits of this <c OMDataStreamProperty>. The raw
  //         bits are copied from the buffer at address <p bits> which
  //         is <p size> bytes in size.
  //   @parm const OMByte* | bits | The address of the buffer from which the
  //         raw bits are copied.
  //   @parm OMUInt32 | size | The size of the buffer.
void OMDataStreamProperty::setBits(const OMByte* ANAME(bits),
                                   OMUInt32 ANAME(size))
{
  TRACE("OMDataStreamProperty::setBits");
  PRECONDITION("Valid bits", bits != 0);
  PRECONDITION("Valid size", size >= bitsSize());

  ASSERT("Unimplemented code not reached", false);
}

  // @mfunc Is a byte order specifed for this stream ?
bool OMDataStreamProperty::hasByteOrder(void) const
{
  TRACE("OMDataStreamProperty::hasByteOrder");

  bool result;
  if ((_byteOrder == littleEndian) || (_byteOrder == bigEndian)) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

  // @mfunc Specify a byte order for this stream.
void OMDataStreamProperty::setByteOrder(OMByteOrder byteOrder)
{
  TRACE("OMDataStreamProperty::setByteOrder");

  PRECONDITION("Valid byte order",
                      (byteOrder == littleEndian) || (byteOrder == bigEndian));
  PRECONDITION("No existing byte order", !hasByteOrder());
  PRECONDITION("Stream is empty", size() == 0);

  _byteOrder = byteOrder;

  POSTCONDITION("Byte order properly set", hasByteOrder());
}

  // @mfunc The byte order of this stream.
OMByteOrder OMDataStreamProperty::byteOrder(void) const
{
  TRACE("OMDataStreamProperty::byteOrder");

  PRECONDITION("Byte order set", hasByteOrder());

  return _byteOrder;
}

  // @mfunc Clear the byte order of this stream
void OMDataStreamProperty::clearByteOrder(void)
{
  TRACE("OMDataStreamProperty::clearByteOrder");

  PRECONDITION("Byte order set", hasByteOrder());

  _byteOrder = unspecified;

  POSTCONDITION("Byte order properly cleared", !hasByteOrder());
}

OMByteOrder OMDataStreamProperty::storedByteOrder(void) const
{
  TRACE("OMDataStreamProperty::storedByteOrder");

  return _byteOrder;
}

void OMDataStreamProperty::setStoredByteOrder(OMByteOrder byteOrder)
{
  TRACE("OMDataStreamProperty::setStoredByteOrder");

  _byteOrder = byteOrder;
}

void OMDataStreamProperty::shallowCopyTo(OMProperty* /* destination */) const
{
  TRACE("OMDataStreamProperty::shallowCopyTo");
  // Nothing to do - this is a shallow copy
}

void OMDataStreamProperty::deepCopyTo(OMProperty* destination,
                                      void* /* clientContext */,
                                      bool deferStreamData) const
{
  TRACE("OMDataStreamProperty::deepCopyTo");
  PRECONDITION("Valid destination", destination != 0);

  typedef OMDataStreamProperty Property;
  Property* dest = dynamic_cast<Property*>(destination);
  ASSERT("Destination is correct type", dest != 0);
  ASSERT("Valid destination", dest != this);

  ASSERT("Destination stream is empty", dest->size() == 0);
  if (hasByteOrder()) {
    dest->setByteOrder(byteOrder());
  }

  if (deferStreamData) {
    OMDeferredStream* deferredCopy = new OMDeferredStream(*this, 0);
    dest->setStreamAccess(deferredCopy);
  } else {
    // Save current position of source
    OMUInt64 savedPosition = position();
  
    // Copy the stream contents
    setPosition(0);
    dest->setPosition(0);
    OMUInt32 bytesRead;
    OMUInt32 bytesWritten;
    OMUInt64 bytesToCopy = size();
    OMByte buffer[1024];
    while (bytesToCopy != 0) {
      read(buffer, sizeof(buffer), bytesRead);
      dest->write(buffer, bytesRead, bytesWritten);
      bytesToCopy = bytesToCopy - bytesWritten;
    }
  
    // Restore current position of source
    setPosition(savedPosition);
    dest->setPosition(0);

    // Close the destination stream if the source was empty  
    // Most data stream functions, used directly or in ASSERTs, have the side-effect of 
    // creating the data stream. This was an issue for the XML stored format because an empty
    // source data stream resulted in an destination data stream file which was not closed 
    // when the AAF file is closed because dest->isPresent() is false - an optional and empty 
    // source data stream results in a "not present" destination data stream. Subsequent attempts 
    // to open the same data stream file resulted in an exception.
    if (dest->isOptional() && !dest->isPresent())
    {
        dest->close();
    }
  }
}

void OMDataStreamProperty::setStreamAccess(OMDataStreamAccess* streamAccess)
{
  TRACE("OMDataStreamProperty::setStreamAccess");
  PRECONDITION("No existing stream access", !hasStreamAccess());
  _streamAccess = streamAccess;
  setPresent();
  POSTCONDITION("Has stream access", hasStreamAccess());
}

void OMDataStreamProperty::clearStreamAccess(void)
{
  TRACE("OMDataStreamProperty::clearStreamAccess");
  PRECONDITION("Existing stream access", hasStreamAccess());
  delete _streamAccess;
  _streamAccess = 0;
  POSTCONDITION("No stream access", !hasStreamAccess());
}

bool OMDataStreamProperty::hasStreamAccess(void) const
{
  TRACE("OMDataStreamProperty::hasStreamAccess");
  bool result;
  if (_streamAccess != 0) {
    result = true;
  } else {
    result = false;
  }
  POSTCONDITION("Consistent result", IMPLIES(_streamAccess == 0, !result));
  POSTCONDITION("Consistent result", IMPLIES(_streamAccess != 0,  result));
  return result;
}

OMDataStreamAccess* OMDataStreamProperty::streamAccess(void) const
{
  TRACE("OMDataStreamProperty::streamAccess");
  PRECONDITION("Has stream access", hasStreamAccess());
  OMDataStreamAccess* result = _streamAccess;
  POSTCONDITION("Valid result", result != 0);
  return result;
}

  // @mfunc Does this stream know about essence element keys?
  //   @rdesc True if this supports essence element keys, false otherwise.
  //   @this const
bool OMDataStreamProperty::hasEssenceElementKey(void) const
{
  TRACE("OMDataStreamProperty::hasEssenceElementKey");

  bool result = stream()->hasEssenceElementKey();
  return result;
}

  // @mfunc The essence element key associated with this stream.
  //   @rdesc The essence element key.
  //   @this const
OMKLVKey OMDataStreamProperty::essenceElementKey(void) const
{
  TRACE("OMDataStreamProperty::essenceElementKey");
  PRECONDITION("Stream supports essence element keys", hasEssenceElementKey());

  OMKLVKey result = stream()->essenceElementKey();
  return result;
}

  // @mfunc Specify the essence element key for this stream.
  //   @parm The essence element key.
void OMDataStreamProperty::setEssenceElementKey(const OMKLVKey& key)
{
  TRACE("OMDataStreamProperty::setEssenceElementKey");
  PRECONDITION("Stream supports essence element keys", hasEssenceElementKey());

  stream()->setEssenceElementKey(key);

  POSTCONDITION("Essence element key set", essenceElementKey() == key);
}

  // @mfunc The encoding-specific stream filter.
  //   @rdesc The stram filter.
OMDataStreamPropertyFilter* OMDataStreamProperty::filter(void)
{
  TRACE("OMDataStreamProperty::filter");

  if (_filter == 0) {
    _filter = new OMDataStreamPropertyFilter(this);
  }

  POSTCONDITION("Valid filter", _filter != 0);
  return _filter;
}
