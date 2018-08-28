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

#include "OMStream.h"

#include "OMUtilities.h"
#include "OMRawStorage.h"
#include "OMExceptions.h"

#if defined(OM_OS_WINDOWS)
#define OM_USE_WINDOWS_FILES
#elif defined(OM_OS_MACOSX)
//#define OM_USE_MACOSX_FILES
#define OM_USE_ISO_FILES
#else
#define OM_USE_ISO_FILES
#endif

#if defined(OM_USE_WINDOWS_FILES)

#include <windows.h>

  // @class Wrappers for Windows files.
  //   @cauthor Tim Bingham | tjb | Avid Technology, Inc.
class OMWindowsStream : public OMStream {
public:

  static OMWindowsStream* openExistingRead(const wchar_t* fileName);

  static OMWindowsStream* openExistingModify(const wchar_t* fileName);

  static OMWindowsStream* openNewModify(const wchar_t* fileName);

  static OMWindowsStream* openNewModify(void);

  static bool readable(const wchar_t* fileName);

  static bool modifiable(const wchar_t* fileName);

  static bool creatable(const wchar_t* fileName);

  virtual void read(OMByte* bytes,
                    OMUInt32 byteCount,
                    OMUInt32& bytesRead) const;

  virtual void write(const OMByte* bytes,
                     OMUInt32 byteCount,
                     OMUInt32& bytesWritten);

  virtual OMUInt64 size(void) const;

  virtual void setSize(OMUInt64 newSize);

  virtual OMUInt64 position(void) const;

  virtual void setPosition(OMUInt64 newPosition);

  virtual void synchronize(void);

  virtual ~OMWindowsStream(void);

protected:
  OMWindowsStream(HANDLE file, bool isWritable);

private:
  HANDLE _file;
};

#elif defined(OM_USE_MACOSX_FILES)

#include <CoreServices/CoreServices.h>

  // @class Wrappers for Macintosh OS X files.
  //   @cauthor Tim Bingham | tjb | Avid Technology, Inc.
class OMMacOSXStream : public OMStream {
public:

  static OMMacOSXStream* openExistingRead(const wchar_t* fileName);

  static OMMacOSXStream* openExistingModify(const wchar_t* fileName);

  static OMMacOSXStream* openNewModify(const wchar_t* fileName);

  static OMMacOSXStream* openNewModify(void);

  static bool readable(const wchar_t* fileName);

  static bool modifiable(const wchar_t* fileName);

  static bool creatable(const wchar_t* fileName);

  virtual void read(OMByte* bytes,
                    OMUInt32 byteCount,
                    OMUInt32& bytesRead) const;

  virtual void write(const OMByte* bytes,
                     OMUInt32 byteCount,
                     OMUInt32& bytesWritten);

  virtual OMUInt64 size(void) const;

  virtual void setSize(OMUInt64 newSize);

  virtual OMUInt64 position(void) const;

  virtual void setPosition(OMUInt64 newPosition);

  virtual void synchronize(void);

  virtual ~OMMacOSXStream(void);

protected:
  OMMacOSXStream(SInt16 file, bool isWritable);

private:
  SInt16 _file;
};

#elif defined(OM_USE_ISO_FILES)

#include <limits.h>
#include <errno.h>
#include <sys/types.h>

  // @class Wrappers for ISO FILE*s.
  //   @cauthor Tim Bingham | tjb | Avid Technology, Inc.
class OMISOStream : public OMStream {
public:

  static OMISOStream* openExistingRead(const wchar_t* fileName);

  static OMISOStream* openExistingModify(const wchar_t* fileName);

  static OMISOStream* openNewModify(const wchar_t* fileName);

  static OMISOStream* openNewModify(void);

  static bool readable(const wchar_t* fileName);

  static bool modifiable(const wchar_t* fileName);

  static bool creatable(const wchar_t* fileName);

  virtual void read(OMByte* bytes,
                    OMUInt32 byteCount,
                    OMUInt32& bytesRead) const;

  virtual void write(const OMByte* bytes,
                     OMUInt32 byteCount,
                     OMUInt32& bytesWritten);

  virtual OMUInt64 size(void) const;

  virtual void setSize(OMUInt64 newSize);

  virtual OMUInt64 position(void) const;

  virtual void setPosition(OMUInt64 newPosition);

  virtual void synchronize(void);

  virtual ~OMISOStream(void);

protected:
  OMISOStream(FILE* file, bool isWritable);

private:
  FILE* _file;
};

#endif

  // @mfunc Create an <c OMStream> object by opening an existing
  //        file for read-only access, the file is named <p fileName>.
  //        The file must already exist.
  //   @parm The file name.
  //   @rdesc The newly created <c OMStream> object.
OMStream*
OMStream::openExistingRead(const wchar_t* fileName)
{
  TRACE("OMStream::openExistingRead");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be read", readable(fileName));

#if defined(OM_USE_WINDOWS_FILES)
  OMStream* result = OMWindowsStream::openExistingRead(fileName);
#elif defined(OM_USE_MACOSX_FILES)
  OMStream* result = OMMacOSXStream::openExistingRead(fileName);
#elif defined(OM_USE_ISO_FILES)
  OMStream* result = OMISOStream::openExistingRead(fileName);
#endif
  return result;
}

  // @mfunc Create an <c OMStream> object by opening an existing
  //        file for modify access, the file is named <p fileName>.
  //        The file must already exist.
  //   @parm The file name.
  //   @rdesc The newly created <c OMStream> object.
OMStream*
OMStream::openExistingModify(const wchar_t* fileName)
{
  TRACE("OMStream::openExistingModify");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be modified", modifiable(fileName));

#if defined(OM_USE_WINDOWS_FILES)
  OMStream* result = OMWindowsStream::openExistingModify(fileName);
#elif defined(OM_USE_MACOSX_FILES)
  OMStream* result = OMMacOSXStream::openExistingModify(fileName);
#elif defined(OM_USE_ISO_FILES)
  OMStream* result = OMISOStream::openExistingModify(fileName);
#endif
  return result;
}

  // @mfunc Create an <c OMStream> object by creating a new
  //        file for modify access, the file is named <p fileName>.
  //        The file must not already exist.
  //   @parm The file name.
  //   @rdesc The newly created <c OMStream> object.
OMStream*
OMStream::openNewModify(const wchar_t* fileName)
{
  TRACE("OMStream::openNewModify");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be created", creatable(fileName));

#if defined(OM_USE_WINDOWS_FILES)
  OMStream* result = OMWindowsStream::openNewModify(fileName);
#elif defined(OM_USE_MACOSX_FILES)
  OMStream* result = OMMacOSXStream::openNewModify(fileName);
#elif defined(OM_USE_ISO_FILES)
  OMStream* result = OMISOStream::openNewModify(fileName);
#endif
  return result;
}

  // @mfunc Create an <c OMStream> object by creating a new
  //        temporary file for modify access.
  //   @rdesc The newly created <c OMStream> object.
OMStream*
OMStream::openNewModify(void)
{
  TRACE("OMStream::openNewModify");

#if defined(OM_USE_WINDOWS_FILES)
  OMStream* result = OMWindowsStream::openNewModify();
#elif defined(OM_USE_MACOSX_FILES)
  OMStream* result = OMMacOSXStream::openNewModify();
#elif defined(OM_USE_ISO_FILES)
  OMStream* result = OMISOStream::openNewModify();
#endif
  return result;
}

  // @mfunc Can an existing file named <p fileName> be opened
  //        for read access ? The file must already exist and be readable.
  //   @parm The name of the file.
  //   @rdesc <e bool.true> if <p fileName> is readable,
  //          <e bool.false> otherwise.
bool OMStream::readable(const wchar_t* fileName)
{
  TRACE("OMStream::readable");
  PRECONDITION("Valid file name", validWideString(fileName));

#if defined(OM_USE_WINDOWS_FILES)
  bool result = OMWindowsStream::readable(fileName);
#elif defined(OM_USE_MACOSX_FILES)
  bool result = OMMacOSXStream::readable(fileName);
#elif defined(OM_USE_ISO_FILES)
  bool result = OMISOStream::readable(fileName);
#endif
  return result;
}

  // @mfunc Can an existing file named <p fileName> be opened
  //        for read/write access ? The file must already exist and be
  //        both readable and writable.
  //   @rdesc <e bool.true> if <p fileName> is modifiable,
  //          <e bool.false> otherwise.
bool OMStream::modifiable(const wchar_t* fileName)
{
  TRACE("OMStream::modifiable");
  PRECONDITION("Valid file name", validWideString(fileName));

#if defined(OM_USE_WINDOWS_FILES)
  bool result = OMWindowsStream::readable(fileName);
#elif defined(OM_USE_MACOSX_FILES)
  bool result = OMMacOSXStream::readable(fileName);
#elif defined(OM_USE_ISO_FILES)
  bool result = OMISOStream::readable(fileName);
#endif
  return result;
}

  // @mfunc Can a new file named <p fileName> be created for read access ?
  //        The file must not already exist.
  //   @rdesc <e bool.true> if <p fileName> is creatable,
  //          <e bool.false> otherwise.
bool OMStream::creatable(const wchar_t* fileName)
{
  TRACE("OMStream::creatable");
  PRECONDITION("Valid file name", validWideString(fileName));

#if defined(OM_USE_WINDOWS_FILES)
  bool result = OMWindowsStream::creatable(fileName);
#elif defined(OM_USE_MACOSX_FILES)
  bool result = OMMacOSXStream::creatable(fileName);
#elif defined(OM_USE_ISO_FILES)
  bool result = OMISOStream::creatable(fileName);
#endif
  return result;
}

bool OMStream::isWritable(void) const
{
  TRACE("OMStream::isWritable");
  return _isWritable;
}

OMStream::~OMStream(void)
{
  TRACE("OMStream::~OMStream");
}

OMStream::OMStream(bool isWritable)
: _isWritable(isWritable)
{
  TRACE("OMStream::OMStream");
}

#if defined(OM_USE_WINDOWS_FILES)

#if (_MSC_VER > 1200)
#define OM_INVALID_FILE_ATTRIBUTES INVALID_FILE_ATTRIBUTES
#else
#define OM_INVALID_FILE_ATTRIBUTES 0xffffffff
#endif

OMWindowsStream*
OMWindowsStream::openExistingRead(const wchar_t* fileName)
{
  TRACE("OMWindowsStream::openExistingRead");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be read", readable(fileName));

  OMWindowsStream* result = 0;
  HANDLE file = CreateFile(fileName,
                           GENERIC_READ,
                           FILE_SHARE_READ | FILE_SHARE_WRITE,
                           0,
                           OPEN_EXISTING,
                           0,
                           0);
  if (file != INVALID_HANDLE_VALUE) {
    result = new OMWindowsStream(file, false);
    ASSERT("Valid heap pointer", result != 0);
  } else {
    throw OMException("CreateFile() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
  return result;
}

OMWindowsStream*
OMWindowsStream::openExistingModify(const wchar_t* fileName)
{
  TRACE("OMWindowsStream::openExistingModify");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be modified", modifiable(fileName));

  OMWindowsStream* result = 0;
  HANDLE file = CreateFile(fileName,
                           GENERIC_WRITE | GENERIC_READ,
                           FILE_SHARE_READ,
                           0,
                           OPEN_EXISTING,
                           0,
                           0);
  if (file != INVALID_HANDLE_VALUE) {
    result = new OMWindowsStream(file, true);
    ASSERT("Valid heap pointer", result != 0);
  } else {
    throw OMException("CreateFile() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
  return result;
}

OMWindowsStream*
OMWindowsStream::openNewModify(const wchar_t* fileName)
{
  TRACE("OMWindowsStream::openNewModify");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be created", creatable(fileName));

  OMWindowsStream* result = 0;
  HANDLE file = CreateFile(fileName,
                           GENERIC_WRITE | GENERIC_READ,
                           FILE_SHARE_READ,
                           0,
                           CREATE_NEW,
                           0,
                           0);
  if (file != INVALID_HANDLE_VALUE) {
    result = new OMWindowsStream(file, true);
    ASSERT("Valid heap pointer", result != 0);
  } else {
    throw OMException("CreateFile() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
  return result;
}

OMWindowsStream*
OMWindowsStream::openNewModify(void)
{
  TRACE("OMWindowsStream::openNewModify");

  wchar_t tempPath[MAX_PATH];
  DWORD length = GetTempPath(MAX_PATH, tempPath);
  if ((length == 0) || (length > MAX_PATH)) {
    throw OMException("GetTempPath() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
  wchar_t fileName[MAX_PATH];
  UINT status = GetTempFileName(tempPath, L"xxx", 0, fileName);
  if (status == 0) {
    throw OMException("GetTempFileName() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
  OMWindowsStream* result = 0;
  HANDLE file = CreateFile(fileName,
                           GENERIC_WRITE | GENERIC_READ,
                           FILE_SHARE_READ,
                           0,
                           CREATE_ALWAYS,
                           0,
                           0);
  if (file != INVALID_HANDLE_VALUE) {
    result = new OMWindowsStream(file, true);
    ASSERT("Valid heap pointer", result != 0);
  } else {
    throw OMException("CreateFile() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
  return result;
}

bool OMWindowsStream::readable(const wchar_t* fileName)
{
  TRACE("OMWindowsStream::readable");
  PRECONDITION("Valid file name", validWideString(fileName));

  bool result;
  DWORD attributes = GetFileAttributes(fileName);
  if (attributes != OM_INVALID_FILE_ATTRIBUTES) {
    result = true; // File exists (and is readable)
  } else {
    result = false; // File does not exist
  }
  return result;
}

bool OMWindowsStream::modifiable(const wchar_t* fileName)
{
  TRACE("OMWindowsStream::modifiable");
  PRECONDITION("Valid file name", validWideString(fileName));

  bool result;
  DWORD attributes = GetFileAttributes(fileName);
  if (attributes != OM_INVALID_FILE_ATTRIBUTES) {
    if (attributes & FILE_ATTRIBUTE_READONLY) {
      result = false; // File exists (and may not be written)
    } else {
      result = true; // File exists (and may be written)
    }
  } else {
    result = false; // File does not exist
  }
  return result;
}

bool OMWindowsStream::creatable(const wchar_t* fileName)
{
  TRACE("OMWindowsStream::creatable");
  PRECONDITION("Valid file name", validWideString(fileName));

  bool result;
  DWORD attributes = GetFileAttributes(fileName);
  if (attributes != OM_INVALID_FILE_ATTRIBUTES) {
    result = false; // File exists
  } else {
    result = true; // File does not exist
  }
  return result;
}

void OMWindowsStream::read(OMByte* bytes,
                           OMUInt32 byteCount,
                           OMUInt32& bytesRead) const
{
  TRACE("OMWindowsStream::read");

  DWORD readBytes;
  BOOL result = ReadFile(_file, bytes, byteCount, &readBytes, 0);
  if (!result) {
    throw OMException("ReadFile() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
  bytesRead = readBytes;
}

void OMWindowsStream::write(const OMByte* bytes,
                            OMUInt32 byteCount,
                            OMUInt32& bytesWritten)
{
  TRACE("OMWindowsStream::write");
  PRECONDITION("Stream is writable", isWritable());

  DWORD writtenBytes;
  BOOL result = WriteFile(_file, bytes, byteCount, &writtenBytes, 0);
  if (!result) {
    throw OMException("WriteFile() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
  bytesWritten = writtenBytes;
}

OMUInt64 OMWindowsStream::size(void) const
{
  TRACE("OMWindowsStream::size");

  OMUInt64 result;
  ULARGE_INTEGER li;
  li.LowPart = GetFileSize(_file, &li.HighPart);
  if ((li.LowPart == -1) && GetLastError() != NO_ERROR) {
    throw OMException("GetFileSize() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
  result = li.QuadPart;
  return result;
}

void OMWindowsStream::setSize(OMUInt64 newSize)
{
  TRACE("OMWindowsStream::setSize");
  PRECONDITION("Stream is writable", isWritable());

  OMUInt64 savedPosition = position();
  setPosition(newSize);
  BOOL result = SetEndOfFile(_file);
  if (!result) {
    setPosition(savedPosition);
    throw OMException("SetEndOfFile() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
  setPosition(savedPosition);
}

OMUInt64 OMWindowsStream::position(void) const
{
  TRACE("OMWindowsStream::position");

  OMUInt64 result;
  LARGE_INTEGER li;
  li.QuadPart = 0;
  li.LowPart = SetFilePointer(_file, li.LowPart, &li.HighPart, FILE_CURRENT);
  if ((li.LowPart == -1) && GetLastError() != NO_ERROR) {
    throw OMException("SetFilePointer() failed", HRESULT_FROM_WIN32(GetLastError()));
  }
  result = li.QuadPart;
  return result;
}

void OMWindowsStream::setPosition(OMUInt64 newPosition)
{
  TRACE("OMWindowsStream::setPosition");

  LARGE_INTEGER li;
  li.QuadPart = newPosition;
  li.LowPart = SetFilePointer(_file, li.LowPart, &li.HighPart, FILE_BEGIN);
  if ((li.LowPart == -1) && GetLastError() != NO_ERROR) {
    throw OMException("SetFilePointer() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
}

void OMWindowsStream::synchronize(void)
{
  TRACE("OMWindowsStream::synchronize");
  PRECONDITION("Stream is writable", isWritable());

  BOOL result = FlushFileBuffers(_file);
  if (!result) {
    throw OMException("FlushFileBuffers() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
}

OMWindowsStream::~OMWindowsStream(void)
{
  TRACE("OMWindowsStream::~OMWindowsStream");

  if (isWritable()) {
    synchronize();
  }
  BOOL result = CloseHandle(_file);
  if (!result) {
    throw OMException("CloseHandle() failed.", HRESULT_FROM_WIN32(GetLastError()));
  }
}

OMWindowsStream::OMWindowsStream(HANDLE file, bool isWritable)
: OMStream(isWritable),
  _file(file)
{
  TRACE("OMWindowsStream::OMWindowsStream");
}

#elif defined(OM_USE_MACOSX_FILES)

OMMacOSXStream*
OMMacOSXStream::openExistingRead(const wchar_t* fileName)
{
  TRACE("OMMacOSXStream::openExistingRead");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be read", readable(fileName));

  OMMacOSXStream* result = 0;
  ASSERT("Unimplemented code not reached", false);
  return result;
}

OMMacOSXStream*
OMMacOSXStream::openExistingModify(const wchar_t* fileName)
{
  TRACE("OMMacOSXStream::openExistingModify");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be modified", modifiable(fileName));

  OMMacOSXStream* result = 0;
  ASSERT("Unimplemented code not reached", false);
  return result;
}

OMMacOSXStream*
OMMacOSXStream::openNewModify(const wchar_t* fileName)
{
  TRACE("OMMacOSXStream::openNewModify");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be created", creatable(fileName));

  OMMacOSXStream* result = 0;
  ASSERT("Unimplemented code not reached", false);
  return result;
}

OMMacOSXStream*
OMMacOSXStream::openNewModify(void)
{
  TRACE("OMMacOSXStream::openNewModify");

  OMMacOSXStream* result = 0;
  ASSERT("Unimplemented code not reached", false);
  return result;
}

bool OMMacOSXStream::readable(const wchar_t* fileName)
{
  TRACE("OMMacOSXStream::readable");
  PRECONDITION("Valid file name", validWideString(fileName));

  bool result = false;
  ASSERT("Unimplemented code not reached", false);
  return result;
}

bool OMMacOSXStream::modifiable(const wchar_t* fileName)
{
  TRACE("OMMacOSXStream::modifiable");
  PRECONDITION("Valid file name", validWideString(fileName));

  bool result = false;
  ASSERT("Unimplemented code not reached", false);
  return result;
}

bool OMMacOSXStream::creatable(const wchar_t* fileName)
{
  TRACE("OMMacOSXStream::creatable");
  PRECONDITION("Valid file name", validWideString(fileName));

  bool result = false;
  ASSERT("Unimplemented code not reached", false);
  return result;
}

void OMMacOSXStream::read(OMByte* /* bytes */,
                          OMUInt32 /* byteCount */,
                          OMUInt32& /* bytesRead */) const
{
  TRACE("OMMacOSXStream::read");

  ASSERT("Unimplemented code not reached", false);
}

void OMMacOSXStream::write(const OMByte* /* bytes */,
                           OMUInt32 /* byteCount */,
                           OMUInt32& /* bytesWritten */)
{
  TRACE("OMMacOSXStream::write");
  PRECONDITION("Stream is writable", isWritable());

  ASSERT("Unimplemented code not reached", false);
}

OMUInt64 OMMacOSXStream::size(void) const
{
  TRACE("OMMacOSXStream::size");

  OMUInt64 result = 0;
  ASSERT("Unimplemented code not reached", false);
  return result;
}

void OMMacOSXStream::setSize(OMUInt64 /* newSize */)
{
  TRACE("OMMacOSXStream::setSize");
  PRECONDITION("Stream is writable", isWritable());

  ASSERT("Unimplemented code not reached", false);
}

OMUInt64 OMMacOSXStream::position(void) const
{
  TRACE("OMMacOSXStream::position");

  OMUInt64 result = 0;
  ASSERT("Unimplemented code not reached", false);
  return result;
}

void OMMacOSXStream::setPosition(OMUInt64 /* newPosition */)
{
  TRACE("OMMacOSXStream::setPosition");

  ASSERT("Unimplemented code not reached", false);
}

void OMMacOSXStream::synchronize(void)
{
  TRACE("OMMacOSXStream::synchronize");
  PRECONDITION("Stream is writable", isWritable());

  ASSERT("Unimplemented code not reached", false);
}

OMMacOSXStream::~OMMacOSXStream(void)
{
  TRACE("OMMacOSXStream::~OMMacOSXStream");

  ASSERT("Unimplemented code not reached", false);
}

OMMacOSXStream::OMMacOSXStream(SInt16 file, bool isWritable)
: OMStream(isWritable),
  _file(file)
{
  TRACE("OMMacOSXStream::OMMacOSXStream");
  ASSERT("Unimplemented code not reached", false);
}

#elif defined(OM_USE_ISO_FILES)

OMISOStream*
OMISOStream::openExistingRead(const wchar_t* fileName)
{
  TRACE("OMISOStream::openExistingRead");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be read", readable(fileName));

  FILE* file = wfopen(fileName, L"rb");
  ASSERT("File successfully opened", file != 0); // tjb - error

  OMISOStream* result = new OMISOStream(file, false);
  ASSERT("Valid heap pointer", result != 0);

  return result;
}

OMISOStream*
OMISOStream::openExistingModify(const wchar_t* fileName)
{
  TRACE("OMISOStream::openExistingModify");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be modified", modifiable(fileName));

  FILE* file = wfopen(fileName, L"r+b");
  ASSERT("File successfully opened", file != 0); // tjb - error

  OMISOStream* result = new OMISOStream(file, true);
  ASSERT("Valid heap pointer", result != 0);

  return result;
}

OMISOStream*
OMISOStream::openNewModify(const wchar_t* fileName)
{
  TRACE("OMISOStream::openNewModify");

  PRECONDITION("Valid file name", validWideString(fileName));
  PRECONDITION("File can be created", creatable(fileName));

  FILE* file = wfopen(fileName, L"w+b");
  ASSERT("File successfully opened", file != 0); // tjb - error

  OMISOStream* result = new OMISOStream(file, true);
  ASSERT("Valid heap pointer", result != 0);

  return result;
}

OMISOStream*
OMISOStream::openNewModify(void)
{
  TRACE("OMISOStream::openNewModify");

  FILE* file = tmpfile();
  ASSERT("File successfully opened", file != 0); // tjb - error

  OMISOStream* result = new OMISOStream(file, true);
  ASSERT("Valid heap pointer", result != 0);

  return result;
}

bool OMISOStream::readable(const wchar_t* fileName)
{
  TRACE("OMISOStream::readable");
  PRECONDITION("Valid file name", validWideString(fileName));

  bool result;
  FILE* f = wfopen(fileName, L"rb");
  if (f != 0) {
    result = true;
    fclose(f);
  } else {
    result = false;
  }
  return result;
}

bool OMISOStream::modifiable(const wchar_t* fileName)
{
  TRACE("OMISOStream::modifiable");
  PRECONDITION("Valid file name", validWideString(fileName));

  bool result;
  FILE* f = wfopen(fileName, L"r+b");
  if (f != 0) {
    result = true;
    fclose(f);
  } else {
    result = false;
  }
  return result;
}

bool OMISOStream::creatable(const wchar_t* fileName)
{
  TRACE("OMISOStream::creatable");
  PRECONDITION("Valid file name", validWideString(fileName));

  // Check that the file doesn't already exist.
  // This is the ISO way to do it.
  //
  bool result;
  FILE* f = wfopen(fileName, L"r");
  if (f != 0) {
    result = false;
    fclose(f);
  } else {
    result = true;
  }
  return result;
}

void OMISOStream::read(OMByte* bytes,
                       OMUInt32 byteCount,
                       OMUInt32& bytesRead) const
{
  TRACE("OMISOStream::read");
  PRECONDITION("No error on stream", ferror(_file) == 0);

  size_t actualByteCount = fread(bytes, 1, byteCount, _file);
  ASSERT("Successful read", ferror(_file) == 0);

  bytesRead = static_cast<OMUInt32>(actualByteCount);
}

void OMISOStream::write(const OMByte* bytes,
                        OMUInt32 byteCount,
                        OMUInt32& bytesWritten)
{
  TRACE("OMISOStream::write");
  PRECONDITION("Stream is writable", isWritable());
  PRECONDITION("No error on stream", ferror(_file) == 0);

  size_t actualByteCount = fwrite(bytes, 1, byteCount, _file);
  ASSERT("Successful write", ferror(_file) == 0);

  bytesWritten = static_cast<OMUInt32>(actualByteCount);
}

OMUInt64 OMISOStream::size(void) const
{
  TRACE("OMISOStream::size");
  PRECONDITION("No error on stream", ferror(_file) == 0);

  errno = 0;
  off_t oldPosition = ftello(_file);
  ASSERT("Successful tell", IMPLIES(oldPosition == static_cast<off_t>(-1), errno == 0));

  long int status = fseeko(_file, 0, SEEK_END);
  ASSERT("Successful seek", status == 0); // tjb - error

  errno = 0;
  off_t position = ftello(_file);
  ASSERT("Successful tell", IMPLIES(position == static_cast<off_t>(-1), errno == 0));

  status = fseeko(_file, oldPosition, SEEK_SET);
  ASSERT("Successful seek", status == 0); // tjb - error

  OMUInt64 result = position;
  return result;
}

void OMISOStream::setSize(OMUInt64 newSize)
{
  TRACE("OMISOStream::setSize");
  PRECONDITION("Stream is writable", isWritable());

  OMUInt64 currentSize = size();

  if (newSize > currentSize) {

    // Extend by writing a single byte.
    //
    OMUInt64 oldPosition = position(); // Save position
    OMByte nullByte = 0;

    setPosition(newSize - 1);
    OMUInt32 bw;
    write(&nullByte, 1, bw);

    ASSERT("Size properly changed", size() == newSize);
    setPosition(oldPosition); // Restore position
  }
  // else no ISO way to truncate the file in place
}

OMUInt64 OMISOStream::position(void) const
{
  TRACE("OMISOStream::position");
  PRECONDITION("No error on stream", ferror(_file) == 0);

  errno = 0;
  const off_t position = ftello(_file);
  ASSERT("Successful tell", IMPLIES(position == static_cast<off_t>(-1), errno == 0));

  OMUInt64 result = position;
  return result;
}

void OMISOStream::setPosition(OMUInt64 newPosition)
{
  TRACE("OMISOStream::setPosition");

#define OMOFF_MAX (sizeof(off_t) == sizeof(OMInt64) ? OMINT64_MAX : OMINT32_MAX)
  ASSERT("Supported position", newPosition <= OMOFF_MAX); // tjb - limit

  ASSERT("No error on stream", ferror(_file) == 0);
  off_t osNewPosition = static_cast<off_t>(newPosition);
#if defined(OM_DEBUG)
  int status = fseeko(_file, osNewPosition, SEEK_SET);
  ASSERT("Successful seek", status == 0); // tjb - error
#else
  fseeko(_file, osNewPosition, SEEK_SET);
#endif
}

void OMISOStream::synchronize(void)
{
  TRACE("OMISOStream::synchronize");
  PRECONDITION("Stream is writable", isWritable());
  PRECONDITION("No error on stream", ferror(_file) == 0);

#if defined(OM_DEBUG)
  int status = fflush(_file);
  ASSERT("Successful flush", status == 0); // tjb - error
#else
  fflush(_file);
#endif
}

OMISOStream::~OMISOStream(void)
{
  TRACE("OMISOStream::~OMISOStream");

  if (isWritable()) {
    synchronize();
  }
  ASSERT("No error on stream", ferror(_file) == 0);
#if defined(OM_DEBUG)
  int status = fclose(_file);
  ASSERT("Successful close", status == 0); // tjb - error
#else
  fclose(_file);
#endif
  _file = 0;
}

OMISOStream::OMISOStream(FILE* file, bool isWritable)
: OMStream(isWritable),
  _file(file)
{
  TRACE("OMISOStream::OMISOStream");
}

#endif
