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
#ifndef OMKLVSTOREDSTREAMFILTER_H
#define OMKLVSTOREDSTREAMFILTER_H

#include "OMStoredStreamFilter.h"

class OMKLVStoredStream;

  // @class Implementation of <c OMStoredStreamFilter> for
  //        SMPTE (Society of Motion Picture and Television Engineers)
  //        Key Length Value (KLV) binary files.
  //   @base public | <c OMStoredStreamFilter>
class OMKLVStoredStreamFilter : public OMStoredStreamFilter {
public:
  // @access Public members.

    // @cmember Constructor.
  OMKLVStoredStreamFilter(OMKLVStoredStream* stream);

    // @cmember Destructor.
  ~OMKLVStoredStreamFilter(void);

    // @cmember Read <p size> bytes from this <c OMKLVStoredStreamFilter>
    //          into the buffer at address <p data>.
  virtual void read(void* data, OMUInt32 size) const;

    // @cmember Attempt to read <p bytes> bytes from this
    //          <c OMKLVStoredStreamFilter> into the buffer at address <p data>.
    //          The actual number of bytes read is returned in <p bytesRead>.
  virtual void read(OMByte* data,
                    const OMUInt32 bytes,
                    OMUInt32& bytesRead) const;

    // @cmember Attempt to read the vector of buffers given by <p buffers>
    //          from this <c OMKLVStoredStreamFilter>. This is "read scatter". The
    //          <p bufferCount> buffers are read in order until all have
    //          been successfully read or an error is encountered. Once
    //          an error has been encountered on one buffer no additional
    //          buffers are read.
    //          The number of bytes read is returned in <p bytesRead>.
  virtual void read(OMIOBufferDescriptor* buffers,
                    OMUInt32 bufferCount,
                    OMUInt32& bytesRead) const;

    // Asynchronous read - single buffer
  virtual void read(OMUInt64 position,
                    OMByte* buffer,
                    const OMUInt32 bytes,
                    void* /* */ completion,
                    const void* clientArgument) const;

    // Asynchronous read - multiple buffers
  virtual void read(OMUInt64 position,
                    OMIOBufferDescriptor* buffers,
                    OMUInt32 bufferCount,
                    void* /* */ completion,
                    const void* clientArgument) const;

    // @cmember Write <p size> bytes from the buffer at address
    //          <p data> to this <c OMKLVStoredStreamFilter>.
  virtual void write(void* data, OMUInt32 size);

    // @cmember Attempt to write <p bytes> bytes from the buffer at
    //          address <p data> to this <c OMKLVStoredStreamFilter>. The actual
    //          number of bytes written is returned in <p bytesWritten>.
  virtual void write(const OMByte* data,
                     const OMUInt32 bytes,
                     OMUInt32& bytesWritten);

    // @cmember Attempt to write the vector of buffers given by <p buffers>
    //          to this <c OMKLVStoredStreamFilter>. This is "write gather". The
    //          <p bufferCount> buffers are written in order until all have
    //          been successfully written or an error is encountered. Once
    //          an error has been encountered on one buffer no additional
    //          buffers are written.
    //          The number of bytes written is returned in <p bytesWritten>.
  virtual void write(OMIOBufferDescriptor* buffers,
                     OMUInt32 bufferCount,
                     OMUInt32& bytesWritten);

    // Asynchronous write - single buffer
  virtual void write(OMUInt64 position,
                     const OMByte* buffer,
                     const OMUInt32 bytes,
                     void* /* */ completion,
                     const void* clientArgument);

    // Asynchronous write - multiple buffers
  virtual void write(OMUInt64 position,
                     const OMIOBufferDescriptor* buffers,
                     OMUInt32 bufferCount,
                     void* /* */ completion,
                     const void* clientArgument);

    // @cmember The size of this <c OMKLVStoredStreamFilter> in bytes.
  virtual OMUInt64 size(void) const;

    // @cmember Set the size of this <c OMKLVStoredStreamFilter> to <p bytes>.
  virtual void setSize(const OMUInt64 newSize);

    // @cmember The current position for <f read()> and
    //          <f write()>, as an offset in bytes from the
    //          begining of this <c OMKLVStoredStreamFilter>.
  virtual OMUInt64 position(void) const;

    // @cmember Set the current position for <f read()> and
    //          <f write()>, as an offset in bytes from the
    //          begining of this <c OMKLVStoredStreamFilter>.
  virtual void setPosition(const OMUInt64 offset) const;

    // @cmember Synchronize this <c OMKLVStoredStreamFilter> with
    //          the underlying <c OMKLVStoredStream>.
    //          Calling this method brings the encoding-specific
    //          represenation of <c OMKLVStoredStream> into a valid state.
  virtual void synchronize(void) const;

    // @cmember Close this <c OMStoredStream>.
  virtual void close(void);

    // @cmember Get unfiltered <c OMStoredStream>.
  virtual const OMStoredStream* stream() const;

    // @cmember Get unfiltered <c OMStoredStream>.
  virtual OMStoredStream* stream();

  // Get rid of the following 5

  virtual OMUInt32 streamIdentification(void) const;

    // @cmember Set the label to <p label>.
  virtual void setLabel(const OMKLVKey& label);

    // @cmember Get the label.
  virtual OMKLVKey label(void) const;

    // @cmember Set the block size (alignment) of this essence element.
  virtual void setBlockSize(OMUInt32 blockSize);

    // @cmember The block size (alignment) of this essence element.
  virtual OMUInt32 blockSize(void) const;

private:
  // @access Private members.

  void initialize(void) const;
  void writeKey(void);

  OMKLVStoredStream* _stream;
  bool _initialized;
  bool _keyWritten;
  bool _dirty;
  OMUInt64 _position;
  OMUInt64 _klvLength;
  OMUInt64 _klvLengthOffset;
  OMUInt64 _klvValueOffset;
};

#endif
