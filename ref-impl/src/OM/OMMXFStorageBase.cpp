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

#include "OMMXFStorageBase.h"
#include "OMAssertions.h"
#include "OMType.h"

bool OMMXFStorageBase::findHeader(const OMRawStorage* store,
                              OMUInt64& headerPosition)
{
  OMUInt64 startPosition = 0;
  store->setPosition(startPosition);
  return findPattern(store,
                     startPosition,
                     headerPosition,
                     HeaderPrefix,
                     sizeof(HeaderPrefix),
                     RunInLimit);
}

bool OMMXFStorageBase::isHeader(const OMKLVKey& k)
{
  bool result;
  if (memcmp(&OpenIncompleteHeaderPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&IncompleteHeaderPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&OpenHeaderPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&HeaderPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::isBody(const OMKLVKey& k)
{
  bool result;
  if (memcmp(&OpenIncompleteBodyPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&IncompleteBodyPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&OpenBodyPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&BodyPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::isFooter(const OMKLVKey& k)
{
  bool result;
  if (memcmp(&IncompleteFooterKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&FooterKey, &k, sizeof(k)) == 0) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::isPartition(const OMKLVKey& k)
{
  TRACE("OMMXFStorageBase::isPartition");
  bool result;
  if (isHeader(k)) {
    result = true;
  } else if (isBody(k)) {
    result = true;
  } else if (isFooter(k)) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::isIncomplete(const OMKLVKey& k)
{
  TRACE("OMMXFStorageBase::isIncomplete");
  bool result;
  if (memcmp(&OpenIncompleteHeaderPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&IncompleteHeaderPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&OpenIncompleteBodyPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&IncompleteBodyPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&IncompleteFooterKey, &k, sizeof(k)) == 0) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::isClosed(const OMKLVKey& k)
{
  TRACE("OMMXFStorageBase::isClosed");
  bool result;
  if (memcmp(&IncompleteHeaderPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&HeaderPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&IncompleteBodyPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&BodyPartitionKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&IncompleteFooterKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&FooterKey, &k, sizeof(k)) == 0) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::isIndex(const OMKLVKey& k)
{
  TRACE("OMMXFStorageBase::isIndex");
  bool result;
  if (memcmp(&IndexTableSegmentKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&V10IndexTableSegmentKey, &k, sizeof(k)) == 0) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::isEssence(const OMKLVKey& k)
{
  TRACE("OMMXFStorageBase::isEssence");
  bool result;
  if (memcmp(&EssenceElementPrefix, &k, sizeof(EssenceElementPrefix)) == 0) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::isFill(const OMKLVKey& k)
{
  TRACE("OMMXFStorageBase::isFill");
  bool result;
  if (memcmp(&fillKey, &k, sizeof(k)) == 0) {
    result = true;
  } else if (memcmp(&V2FillKey, &k, sizeof(k)) == 0) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

  // @mfunc The minimum size of <p i> when encoded using <f berEncode>.
  //        The returned size includes the BER length byte.
  //   @parm The value to encode.
  //   @rdesc The encoded size.
size_t OMMXFStorageBase::berEncodedSize(const OMUInt64 i)
{
  TRACE("OMMXFStorageBase::berEncodedSize");

  const OMUInt64 mask = ((OMUInt64)0xff << 56);
  size_t result;
  if (i != 0) {
    result = sizeof(i);
    OMUInt64 v = i;
    while (((v & mask) >> 56) == 0) {
      v = v << 8;
      result = result - 1;
    }
  } else {
    result = 1;
  }
  result = result + 1; // account for length byte
  return result;
}

  // @mfunc BER encode <p value> into <p berValueBuffer>.
  //   @parm OMByte* | berValueBuffer | The buffer in which to place the BER
  //         encoded value.
  //   @parm size_t | berValueBufferSize | The size of the buffer.
  //   @parm const OMUInt32& | berValueSize | The desired encoding size 1-8
  //         (does not include the BER length byte). e.g for a value that fits
  //         in an OMUInt32, 4 is sufficient.
  //   @parm const OMUInt64& | value | The value to encode.
void OMMXFStorageBase::berEncode(OMByte* berValueBuffer,
                                 size_t ANAME(berValueBufferSize),
                                 const OMUInt32& berValueSize,
                                 const OMUInt64& value)
{
  TRACE("OMMXFStorageBase::berEncode");
  PRECONDITION("Valid output buffer", berValueBuffer != 0);
  PRECONDITION("Valid output buffer size",
                              berValueBufferSize >= berEncodedSize(value));
  PRECONDITION("Valid size", berValueSize <= sizeof(OMUInt64));
  PRECONDITION("Valid size", berValueSize > 0);
  PRECONDITION("Valid size", berValueSize >= (berEncodedSize(value) - 1));

  OMByte* p = berValueBuffer;
  OMByte b = 0x80 | (OMByte)berValueSize;
  *p++ = b;
  size_t skip = sizeof(OMUInt64) - berValueSize;
  size_t i;
  OMUInt64 v = value;
  for (i = 0; i < skip; i++) {
    v = v << 8;
  }
  const OMUInt64 mask = ((OMUInt64)0xff << 56);
  for (i = i; i < sizeof(OMUInt64); i++) {
    b = (OMByte)((v & mask) >> 56);
    *p++ = b;
    v = v << 8;
  }
}

bool OMMXFStorageBase::read(const OMRawStorage* store,
                        OMUInt8& i)
{
  TRACE("OMMXFStorageBase::read");
  bool result;
  OMUInt32 bytesRead;
  OMByte* dest = reinterpret_cast<OMByte*>(&i);
  store->read(dest, sizeof(OMUInt8), bytesRead);
  if (bytesRead == sizeof(OMUInt8)) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::read(const OMRawStorage* store,
                        OMUInt16& i,
                        bool reorderBytes)
{
  TRACE("OMMXFStorageBase::read");
  bool result;
  OMUInt32 bytesRead;
  OMByte* dest = reinterpret_cast<OMByte*>(&i);
  store->read(dest, sizeof(OMUInt16), bytesRead);
  if (bytesRead == sizeof(OMUInt16)) {
    if (reorderBytes) {
      OMType::reorderInteger(dest, sizeof(OMUInt16));
    }
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::read(const OMRawStorage* store,
                        OMUInt32& i,
                        bool reorderBytes)
{
  TRACE("OMMXFStorageBase::read");
  bool result;
  OMUInt32 bytesRead;
  OMByte* dest = reinterpret_cast<OMByte*>(&i);
  store->read(dest, sizeof(OMUInt32), bytesRead);
  if (bytesRead == sizeof(OMUInt32)) {
    if (reorderBytes) {
      OMType::reorderInteger(dest, sizeof(OMUInt32));
    }
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::read(const OMRawStorage* store,
                        OMUInt64& i,
                        bool reorderBytes)
{
  TRACE("OMMXFStorageBase::read");
  bool result;
  OMUInt32 bytesRead;
  OMByte* dest = reinterpret_cast<OMByte*>(&i);
  store->read(dest, sizeof(OMUInt64), bytesRead);
  if (bytesRead == sizeof(OMUInt64)) {
    if (reorderBytes) {
      OMType::reorderInteger(dest, sizeof(OMUInt64));
    }
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::read(const OMRawStorage* store, OMKLVKey& key)
{
  TRACE("OMMXFStorageBase::read");
  bool result;
  OMUInt32 bytesRead;
  OMByte* dest = reinterpret_cast<OMByte*>(&key);
  store->read(dest, sizeof(OMKLVKey), bytesRead);
  if (bytesRead == sizeof(OMKLVKey)) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool OMMXFStorageBase::readKLVLength(const OMRawStorage* store, OMUInt64& length)
{
  TRACE("OMMXFStorageBase::readKLVLength");
  length = readBerLength(store);
  return true; // tjb
}

bool OMMXFStorageBase::skipBytes(const OMRawStorage* store, OMUInt64 length)
{
  TRACE("OMMXFStorageBase::skipBytes");
  OMUInt64 pos = store->position();
  OMUInt64 newPosition = pos + length;
  store->setPosition(newPosition);
  return true; // tjb
}

OMUInt64 OMMXFStorageBase::readBerLength(const OMRawStorage* store)
{
  TRACE("OMMXFStorageBase::readBerLength");

  OMUInt64 result;
  OMUInt8 b;
  read(store, b);
  if (b == 0x80) {
    // unknown length
    result = 0;
  } else if ((b & 0x80) != 0x80) {
    // short form
    result = b;
  } else {
    // long form
    int length = b & 0x7f;
    result = 0;
    for (int k = 0; k < length; k++) {
      read(store, b);
      result = result << 8;
      result = result + b;
    }
  }
  return result;
}

bool OMMXFStorageBase::endsMetadata(const OMKLVKey& k)
{
  TRACE("OMMXFStorageBase::endsMetadata");

  bool result = false;
  if (isPartition(k)) {
    result = true;
  } else if (k == RandomIndexMetadataKey) {
    result = true;
  } else if (isEssence(k) || k == SystemMetadataKey) {
    result = true;
  } else if (isIndex(k)) {
    result = true;
  }
  return result;
}

bool OMMXFStorageBase::findPattern(const OMRawStorage* store,
                                   OMUInt64 currentPosition,
                                   OMUInt64& patternPosition,
                                   const OMByte* pattern,
                                   OMUInt64 patternSize,
                                   OMUInt32 limit)
{
  bool found = false;
  OMUInt64 pos = currentPosition;
  OMUInt32 c = 0;
  size_t i = 0;
  do {
    OMByte b;
    store->read(&b, 1, c);
    if (c == 1) {
      if (b != pattern[i]) {
        pos = pos + i + 1;
        i = 0;
      } else {
        if (i < patternSize - 1) {
          i = i + 1;
        } else {
          patternPosition = pos;
          found = true;
        }
      }
    }
  } while ((!found) && (pos < limit) && (c == 1));
  return found;
}

