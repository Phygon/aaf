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

#ifndef OMSTRUCTUREDSTORAGE_H
#define OMSTRUCTUREDSTORAGE_H

#ifndef OM_NO_STRUCTURED_STORAGE

#include <time.h>
#include "OMDataTypes.h"

// Use the standard implementation on MS Windows platforms (ole32.dll).
//
// The Microsoft reference implementation is broken and will not be
// fixed, so no Microsoft implementation is available for other platforms.
// However, the definitions in the reference implementation are still
// needed by the OM.

// Each Microsoft supplied Structured Storage implementation requires
// us to include different header files.
//
#if defined(OM_USE_WINDOWS_SS)
# include <objbase.h>
#elif defined(OM_USE_REFERENCE_SS)
#  include "h/storage.h"
#elif defined(OM_USE_SCHEMASOFT_SS) || defined(OM_USE_GSF_SS)
/* XXX: need to get this out of here.  SchemaSoft and libgsf stuff should not include
 *      this header
 */
// HACK ALERT -- SChemaSoft and Reference SS conflict with typedef for CHAR
//            -- redefine Reference typedef
#  define CHAR REFERENCE_CHAR
#  include "h/storage.h"
#  undef REFERENCE_CHAR
#else
#error "Don't know which structured storage implementation to use."
#endif

#include "OMRawStorage.h"
#include "OMFile.h"

// Determine whether or not UNICODE versions of the APIs are in use.
//
#if defined(OM_OS_WINDOWS) && defined(UNICODE)
# define OM_UNICODE_APIS
#endif

// SSCHAR is used in client code for all character (string) arguments
// to functions whose prototype changes when UNICODE is defined.
//
#if defined(OM_UNICODE_APIS)
typedef wchar_t SSCHAR;
#else
typedef char SSCHAR;
#endif

#if !defined(OM_USE_WINDOWS_SS)

// The Macintosh and reference implementation declarations
// for LARGE_INTEGER and ULARGE_INTEGER don't have a QuadPart.
// On Macintosh this is probably because the HighPart and LowPart
// components on that platform are not in the natural platform order.
// Here we hide these differences behind a couple of functions.

static inline OMUInt64 toOMUInt64(const ULARGE_INTEGER &x)
{
  OMUInt64 result = (((OMUInt64)x.HighPart) << 32) + (x.LowPart);
  return result;
}

static inline ULARGE_INTEGER fromOMUInt64(const OMUInt64& x)
{
  ULARGE_INTEGER result;
  result.HighPart = (OMUInt32)(((OMUInt64)x) >> 32);
  result.LowPart  = (OMUInt32) (0x00000000FFFFFFFF & (OMUInt64)x);
  return result;
}

#else

static inline OMUInt64 toOMUInt64(const ULARGE_INTEGER &x)
{
  OMUInt64 result;
  result = x.QuadPart;
  return result;
}


static inline ULARGE_INTEGER fromOMUInt64(const OMUInt64& x)
{
  ULARGE_INTEGER result;
  result.QuadPart = x;
  return result;
}

#endif

/*
 * Formula from From Microsoft FAQ Q167296
 * Under UNIX platforms, file times are maintained in the form of a ANSI C
 * runtime arithmetic type named 'time_t', which represents seconds since
 * midnight January 1, 1970 UTC (coordinated universal time).
 *
 * Under Win32 platforms, file times are maintained primarily in the form of a
 * 64-bit FILETIME structure, which represents the number of 100-nanosecond
 * intervals since January 1, 1601 UTC (coordinate universal time).
 *
 */

#ifndef _MSC_VER
// Provide a replacement Int32x32To64() for non-MSVC compilers
static inline OMInt64 Int32x32To64 (unsigned int multiplier, unsigned int multiplicand)
{
	return (OMInt64)multiplier * (OMInt64)multiplicand;
}
#endif

const OMInt64 SECS_TO_100NS = 10000000;

#if defined(_MSC_VER) && (_MSC_VER < 1310)
const OMInt64 NS100_BETWEEN_EPOCHS = 116444736000000000;
#else
const OMInt64 NS100_BETWEEN_EPOCHS = 116444736000000000LL;
#endif

static inline void convertUnixTimeToFileTime (time_t ut, FILETIME *ft)
{
	OMInt64 ll = Int32x32To64(ut, SECS_TO_100NS) + NS100_BETWEEN_EPOCHS;
	ft->dwLowDateTime = (DWORD)ll;
	ft->dwHighDateTime = (DWORD)(ll >> 32);
}

static inline void convertFileTimeToUnixTime (const FILETIME *ft, time_t *ut)
{
	// first convert filetime to long long in 100ns
	OMInt64 ll = ((OMInt64)ft->dwHighDateTime << 32) + ft->dwLowDateTime;


	// then convert to seconds in units of 100ns since unix epocs
	ll -= NS100_BETWEEN_EPOCHS;

	// convert it to seconds from Win Epoch
	ll /= SECS_TO_100NS;
	*ut = (time_t)ll;
}

#endif // !OM_NO_STRUCTURED_STORAGE

#endif // !OMSTRUCTUREDSTORAGE_H
