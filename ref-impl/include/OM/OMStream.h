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
// @author Tim Bingham | tjb | Avid Technology, Inc. | OMStream
#ifndef OMSTREAM_H
#define OMSTREAM_H

#include <stdio.h>
#include "OMFile.h"
#include "OMDataTypes.h"

  // @class Wrapper for file system.
  //        Additionally supporting wchar_t file names and 64-bit positions.
  //   @cauthor Tim Bingham | tjb | Avid Technology, Inc.
class OMStream {
public:

    // @cmember Create an <c OMStream> object by opening an existing
    //          file for read-only access, the file is named <p fileName>.
    //          The file must already exist.
    //   @precondition <f readable()>
  static OMStream* openExistingRead(const wchar_t* fileName);

    // @cmember Create an <c OMStream> object by opening an existing
    //          file for modify access, the file is named <p fileName>.
    //          The file must already exist.
    //   @precondition <f modifiable()>
  static OMStream* openExistingModify(const wchar_t* fileName);

    // @cmember Create an <c OMStream> object by creating a new
    //          file for modify access, the file is named <p fileName>.
    //          The file must not already exist.
    //   @precondition <f creatable()>
  static OMStream* openNewModify(const wchar_t* fileName);

    // @cmember Create an <c OMStream> object by creating a new
    //          file temporary for modify access.
  static OMStream* openNewModify(void);

    // @cmember Can an existing file named <p fileName> be opened
    //          for read access ? The file must already exist and be readable.
  static bool readable(const wchar_t* fileName);

    // @cmember Can an existing file named <p fileName> be opened
    //          for read/write access ? The file must already exist and be
    //          both readable and writable.
  static bool modifiable(const wchar_t* fileName);

    // @cmember Can a new file named <p fileName> be created for read access ?
    //          The file must not already exist.
  static bool creatable(const wchar_t* fileName);

    // @cmember Attempt to read the number of bytes given by <p byteCount>
    //          from the current position in this <c OMStream>
    //          into the buffer at address <p bytes>.
    //          The actual number of bytes read is returned in <p bytesRead>.
  virtual void read(OMByte* bytes,
                    OMUInt32 byteCount,
                    OMUInt32& bytesRead) const = 0;

    // @cmember Attempt to write the number of bytes given by <p byteCount>
    //          to the current position in this <c OMStream>
    //          from the buffer at address <p bytes>.
    //          The actual number of bytes written is returned in
    //          <p bytesWritten>.
  virtual void write(const OMByte* bytes,
                     OMUInt32 byteCount,
                     OMUInt32& bytesWritten) = 0;

  virtual OMUInt64 size(void) const = 0;

  virtual void setSize(OMUInt64 newSize) = 0;

  virtual OMUInt64 position(void) const = 0;

  virtual void setPosition(OMUInt64 newPosition) = 0;

  virtual void synchronize(void) = 0;

  bool isWritable(void) const;

  virtual ~OMStream(void);

protected:
  OMStream(bool isWritable);

private:
  bool _isWritable;
};

#endif
