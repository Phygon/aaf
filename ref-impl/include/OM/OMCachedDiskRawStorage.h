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
// @author Tim Bingham | tjb | Avid Technology, Inc. | OMCachedDiskRawStorage
#ifndef OMCACHEDDISKRAWSTORAGE_H
#define OMCACHEDDISKRAWSTORAGE_H

#include "OMFile.h"
#include "OMCachedRawStorage.h"

class OMCachePageAllocator;
class OMStream;

  // @class Base class supporting access to the raw bytes of disk
  //        files supported by the Object Manager. Disk pages
  //        are cached to improve performance.
  //
  //   @base public | <c OMCachedRawStorage>
  //   @cauthor Tim Bingham | tjb | Avid Technology, Inc.
class OMBaseCachedDiskRawStorage : public OMCachedRawStorage {
public:

  // @access Public members.

    // @cmember Constructor.
  OMBaseCachedDiskRawStorage(OMUInt32 pageSize,
                             OMUInt32 pageCount,
                             OMUInt64 size);

    // @cmember Constructor.
  OMBaseCachedDiskRawStorage(OMUInt32 pageSize,
                             OMUInt32 pageCount,
                             OMUInt64 size,
                             OMCachePageAllocator* allocator);

    // @cmember Destructor.
  virtual ~OMBaseCachedDiskRawStorage(void);

private:
  // @access Private members.

    // @cmember Read bytes without using the cache.
  virtual void rawReadAt(OMUInt64 position,
                         OMUInt32 byteCount,
                         OMByte* destination) = 0;

    // @cmember Write bytes without using the cache.
  virtual void rawWriteAt(OMUInt64 position,
                          OMUInt32 byteCount,
                          const OMByte* source) = 0;

    // @cmember Read a page or partial page without using the cache.
  virtual void readPage(OMUInt64 position,
                        OMUInt32 byteCount,
                        OMByte* destination);

    // @cmember Write a page or partial page without using the cache.
  virtual void writePage(OMUInt64 position,
                         OMUInt32 byteCount,
                         const OMByte* source);

  OMUInt64 _validSize; // maximum valid position for read

};

  // @class Class supporting access to the raw bytes of disk
  //        files supported by the Object Manager. Disk pages
  //        are cached to improve performance.
  //
  //        This is an Object Manager built-in implementation of the
  //        <c OMRawStorage> interface.
  //
  //   @base public | <c OMBaseCachedDiskRawStorage>
  //   @cauthor Tim Bingham | tjb | Avid Technology, Inc.
class OMCachedDiskRawStorage : public OMBaseCachedDiskRawStorage {
public:

  enum {defaultPageSize  = 4096};
  enum {defaultPageCount =   64};

  // @access Static members.

    // @cmember Create an <c OMCachedDiskRawStorage> object by opening
    //          an existing file for read-only access, the file is named
    //          <p fileName>.
    //          The file must already exist.
  static OMCachedDiskRawStorage* openExistingRead(
                                        const wchar_t* fileName,
                                        OMUInt32 pageSize = defaultPageSize,
                                        OMUInt32 pageCount = defaultPageCount);

    // @cmember Create an <c OMCachedDiskRawStorage> object by opening
    //          an existing file for modify access, the file is named
    //          <p fileName>.
    //          The file must already exist.
  static OMCachedDiskRawStorage* openExistingModify(
                                        const wchar_t* fileName,
                                        OMUInt32 pageSize = defaultPageSize,
                                        OMUInt32 pageCount = defaultPageCount);

    // @cmember Create an <c OMCachedDiskRawStorage> object by creating a new
    //          file for modify access, the file is named <p fileName>.
    //          The file must not already exist.
  static OMCachedDiskRawStorage* openNewModify(
                                        const wchar_t* fileName,
                                        OMUInt32 pageSize = defaultPageSize,
                                        OMUInt32 pageCount = defaultPageCount);

    // @cmember Create an <c OMCachedDiskRawStorage> object by creating a new
    //          temporary file for modify access.
  static OMCachedDiskRawStorage* openNewModify(
                                        OMUInt32 pageSize = defaultPageSize,
                                        OMUInt32 pageCount = defaultPageCount);

  // @access Public members.

    // @cmember Destructor.
  virtual ~OMCachedDiskRawStorage(void);

    // @cmember Is it possible to read from this <c OMCachedDiskRawStorage> ?
  virtual bool isReadable(void) const;

    // @cmember Is it possible to write to this <c OMCachedDiskRawStorage> ?
  virtual bool isWritable(void) const;

    // @cmember May this <c OMCachedDiskRawStorage> be changed in size ?
  virtual bool isExtendible(void) const;

    // @cmember May the current position, for <f read()> and <f write()>,
    //          of this <c OMCachedDiskRawStorage> be changed ?
  virtual bool isPositionable(void) const;

    // @cmember Synchronize this <c OMCachedDiskRawStorage> with its external
    //          representation.
  virtual void synchronize(void);

  // Functions for accessing stream data within this <c OMCachedDiskRawStorage>

    // @cmember Attempt to read the number of stream data bytes given by
    //          <p byteCount> from offset <p position> in this
    //          <c OMCachedDiskRawStorage> into the buffer at
    //          address <p bytes>.
    //          The actual number of bytes read is returned in <p bytesRead>.
  virtual void streamReadAt(OMUInt64 position,
                            OMByte* bytes,
                            OMUInt32 byteCount,
                            OMUInt32& bytesRead) const;

    // @cmember Attempt to fill the vector of buffers given by <p buffers>
    //          with stream data read from offset <p position> in
    //          this <c OMCachedDiskRawStorage>. This is "read scatter".
    //          The <p bufferCount> buffers are read in order until all have
    //          been successfully read or an error is encountered. Once
    //          an error has been encountered on one buffer no additional
    //          buffers are read.
    //          The number of bytes read is returned in <p bytesRead>.
  virtual void streamReadAt(OMUInt64 position,
                            OMIOBufferDescriptor* buffers,
                            OMUInt32 bufferCount,
                            OMUInt32& bytesRead) const;

    // Asynchronous read - single buffer
  virtual void streamReadAt(OMUInt64 position,
                            OMByte* buffer,
                            const OMUInt32 bytes,
                            void* /* */ completion,
                            const void* clientArgument) const;

    // Asynchronous read - multiple buffers
  virtual void streamReadAt(OMUInt64 position,
                            OMIOBufferDescriptor* buffers,
                            OMUInt32 bufferCount,
                            void* /* */ completion,
                            const void* clientArgument) const;

    // @cmember Attempt to write the number of stream data bytes given by
    //          <p byteCount> to offset  <p position> in this
    //          <c OMCachedDiskRawStorage>
    //          from the buffer at address <p bytes>.
    //          The actual number of bytes written is returned in
    //          <p bytesWritten>.
  virtual void streamWriteAt(OMUInt64 position,
                             const OMByte* bytes,
                             OMUInt32 byteCount,
                             OMUInt32& bytesWritten);

    // @cmember Attempt to write the vector of buffers given by <p buffers>
    //          to this <c OMCachedDiskRawStorage>. Stream data bytes
    //          are written starting at offset <p position> in this
    //          <c OMCachedDiskRawStorage>.
    //          This is "write gather".
    //          The <p bufferCount> buffers are written in order until all have
    //          been successfully written or an error is encountered. Once
    //          an error has been encountered on one buffer no additional
    //          buffers are written.
    //          The number of bytes written is returned in <p bytesWritten>.
  virtual void streamWriteAt(OMUInt64 position,
                             OMIOBufferDescriptor* buffers,
                             OMUInt32 bufferCount,
                             OMUInt32& bytesWritten);

    // Asynchronous write - single buffer
  virtual void streamWriteAt(OMUInt64 position,
                             const OMByte* buffer,
                             const OMUInt32 bytes,
                             void* /* */ completion,
                             const void* clientArgument);

    // Asynchronous write - multiple buffers
  virtual void streamWriteAt(OMUInt64 position,
                             const OMIOBufferDescriptor* buffers,
                             OMUInt32 bufferCount,
                             void* /* */ completion,
                             const void* clientArgument);

private:
  // @access Private members.

    // @cmember Read bytes without using the cache.
  virtual void rawReadAt(OMUInt64 position,
                         OMUInt32 byteCount,
                         OMByte* destination);

    // @cmember Write bytes without using the cache.
  virtual void rawWriteAt(OMUInt64 position,
                          OMUInt32 byteCount,
                          const OMByte* source);

    // @cmember Constructor.
  OMCachedDiskRawStorage(OMStream* file,
                         OMFile::OMAccessMode accessMode,
                         OMUInt32 pageSize,
                         OMUInt32 pageCount);

  OMStream* _file;            // The underlying disk file
  OMFile::OMAccessMode _mode; // Disk file is open in this mode

};

#endif
