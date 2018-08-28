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
#ifndef OMMXFSTORAGEBASE_H
#define OMMXFSTORAGEBASE_H

#include "OMWrappedRawStorage.h"
#include "OMDataTypes.h"
#include "OMIdentitySet.h"
#include "OMIdentitySetIter.h"

class OMDataStream;
class OMDataStreamProperty;
class OMMXFIndexStream;
class OMStorable;


static const OMKLVKey OpenIncompleteHeaderPartitionKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x02, 0x01, 0x00};

static const OMKLVKey IncompleteHeaderPartitionKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x02, 0x02, 0x00};

static const OMKLVKey OpenHeaderPartitionKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x02, 0x03, 0x00};

static const OMKLVKey HeaderPartitionKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x02, 0x04, 0x00};

static const OMKLVKey OpenIncompleteBodyPartitionKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x03, 0x01, 0x00};

static const OMKLVKey IncompleteBodyPartitionKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x03, 0x02, 0x00};

static const OMKLVKey OpenBodyPartitionKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x03, 0x03, 0x00};

static const OMKLVKey BodyPartitionKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x03, 0x04, 0x00};

static const OMKLVKey IncompleteFooterKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x04, 0x02, 0x00};

static const OMKLVKey FooterKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x04, 0x04, 0x00};

static const OMKLVKey primerKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x05, 0x01, 0x00};

static const OMKLVKey fillKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x01,
   0x03, 0x01, 0x02, 0x10, 0x01, 0x00, 0x00, 0x00};

static const OMKLVKey V2FillKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x02,
   0x03, 0x01, 0x02, 0x10, 0x01, 0x00, 0x00, 0x00};

static const OMKLVKey IndexTableSegmentKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x10, 0x01, 0x00};

static const OMKLVKey V10IndexTableSegmentKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x10, 0x00, 0x00};

static const OMKLVKey RandomIndexMetadataKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x11, 0x01, 0x00};

static const OMKLVKey SystemMetadataKey =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01,
   0x0d, 0x01, 0x03, 0x01, 0x04, 0x01, 0x01, 0x00};

static const OMByte EssenceElementPrefix[] =
  {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01};

static const OMByte HeaderPrefix[] =
  {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01,
   0x01, 0x0d, 0x01, 0x02, 0x01, 0x01, 0x02};

static const OMByte OperationalPattern1aPrefix[] =
  {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x01,
   0x0d, 0x01, 0x02, 0x01, 0x01, 0x01};

static const OMUInt32 RunInLimit = 64 * 1024;

// Minimum size of a fill KLV triplet (when L not known a priori)
// K (16 bytes)
// L (1 + 8 bytes BER encoded)
// V (0 fill bytes)
static const OMUInt64 minimumFill = sizeof(OMKLVKey) + 1 + sizeof(OMUInt64);

// Coalesced with preceeding fill of any size.
// (value of fillBufferZoneSize must be > minimumFill)
//
static const OMUInt64 fillBufferZoneSize = 32;

static const OMUInt32 preallocatedMetadataSize = 0x40000;
static const OMUInt64 bodyPartitionOffset = preallocatedMetadataSize +
                                            fillBufferZoneSize;
static const OMUInt64 minimumPostMetadataSpace = 0x8000;

static const OMUInt32 defaultKAGSize = 0x100;

static const OMUInt16 currentMajorVersion = 0x0001;
static const OMUInt16 currentMinorVersion = 0x0002;

// Total size of the fixed-size portions of a partition value
static const OMUInt32 fixedPartitionSize =
  sizeof(OMUInt16) + // Major Version
  sizeof(OMUInt16) + // Minor Version
  sizeof(OMUInt32) + // KAGSize
  sizeof(OMUInt64) + // ThisPartition
  sizeof(OMUInt64) + // PreviousPartition
  sizeof(OMUInt64) + // FooterPartition
  sizeof(OMUInt64) + // HeaderByteCount
  sizeof(OMUInt64) + // IndexByteCount
  sizeof(OMUInt32) + // IndexSID
  sizeof(OMUInt64) + // BodyOffset
  sizeof(OMUInt32) + // BodySID
  sizeof(OMKLVKey) + // Operational Pattern
  sizeof(OMUInt32) + // count of essence container labels
  sizeof(OMUInt32);  // size of each essence container label

static const OMPropertyId PID_InterchangeObject_InstanceUID = 0x3c0a;

// {01011502-0000-0000-060E-2B3401010101}
static const OMObjectIdentification Property_InterchangeObject_InstanceUID =
{0x01011502, 0x0000, 0x0000, {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01}};
// {06010107-1600-0000-060E-2B340101010A}
static const OMObjectIdentification Property_Root_MetaDictionary =
{0x06010107, 0x1600, 0x0000, {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x0A}};
// {06010107-1700-0000-060E-2B340101010A}
static const OMObjectIdentification Property_Root_Header =
{0x06010107, 0x1700, 0x0000, {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x0A}};
// {06010107-1900-0000-060E-2B340101010A}
static const OMObjectIdentification Property_Root_FormatVersion =
{0x06010107, 0x1900, 0x0000, {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x0A}};

static const OMPropertyId PID_Root_ObjectDirectory = 0x0021;
static const OMPropertyId PID_Root_FormatVersion   = 0x0022;
// These legacy PIDs conflict with standard SMPTE-assigned PIDs for
// ClassDefinitions and TypeDefinitions properties.
static const OMPropertyId PID_Legacy_Root_ObjectDirectory = 0x0003;
static const OMPropertyId PID_Legacy_Root_FormatVersion   = 0x0004;

// Incrementing the following value serves to distinguish between
// files with minor but compatible differences.  Incrementing the
// following value does not invalidate files.
//
// History
//
// 0x005 - First forwards and backwards compatible version
// 0x006 - Use closed and complete keys for body and footer
// 0x007 - Fill in index byte count in the footer
// 0x008 - Add InterchangeObject::InstanceUID to primer
static const OMUInt32 formatVersion = 0x008;

static const OMKLVKey objectDirectoryKey =
  {0x96, 0x13, 0xb3, 0x8a, 0x87, 0x34, 0x87, 0x46,
   0xf1, 0x02, 0x96, 0xf0, 0x56, 0xe0, 0x4d, 0x2a};

// Fixup tags
static const OMUInt8 FUT_UNDEFINED       = 0x80;
static const OMUInt8 FUT_RESOLVED        = 0x81;

static const OMUInt8 FUT_OBJECTDIRECTORY = 0xff;

  // @class Class supporting access to the raw bytes of MXF
  //        files supported by the Object Manager.
  //   @base public | <c OMRawStorage>
  //   @cauthor Tim Bingham | tjb | Avid Technology, Inc.
class OMMXFStorageBase : public OMWrappedRawStorage {
public:

    // @cmember Constructor.
  OMMXFStorageBase(OMRawStorage* store) : OMWrappedRawStorage(store)
  {
  }

    // @cmember Destructor.
  virtual ~OMMXFStorageBase(void)
  {
  }

    // @cmember Called when this <c OMMXFStorage> is opened for reading.
  virtual void openRead(void) = 0;

    // @cmember Called when this <c OMMXFStorage> is opened for modification.
  virtual void openModify(void) = 0;

    // @cmember Called when this <c OMMXFStorage> is created for writing.
  virtual void createWrite(void) = 0;

    // @cmember Called when this <c OMMXFStorage> is created for for
    //          modification.
  virtual void createModify(void) = 0;

    // @cmember Open this <c OMMXFStorage>.
  virtual void open(void) = 0;

    // @cmember Close this <c OMMXFStorage>.
  virtual void close(void) = 0;

    // @cmember Called after we Save() this <c OMMXFStorage>.
  virtual void postSave(bool finalize) = 0;

    // @cmember Set the operational pattern to <p pattern>.
  virtual void setOperationalPattern(const OMKLVKey& pattern) = 0;

    // @cmember Get the operational pattern.
  virtual OMKLVKey operationalPattern(void) const = 0;

  typedef OMIdentitySet<OMKLVKey> LabelSet;
  typedef OMIdentitySetIterator<OMKLVKey> LabelSetIterator;

    // @cmember Add <p label> to the set of essence container labels.
  virtual void addEssenceContainerLabel(const OMKLVKey& label) = 0;

    // @cmember Is <p label> present in the set of essence container labels.
  virtual bool containsEssenceContainerLabel(const OMKLVKey& label) const = 0;

    // @cmember Create an iterator over the set of essence container labels.
  virtual LabelSetIterator* essenceContainerLabels(void) const = 0;

    // @cmember Set the file generation.
  virtual void setGeneration(const OMUniqueObjectIdentification& generation)= 0;

    // @cmember Get the file generation.
  virtual OMUniqueObjectIdentification generation(void) const= 0;

    // @cmember findMetadata.
  virtual bool findMetadata(OMUInt64& partitionPosition)= 0;

  static bool findHeader(const OMRawStorage* store, OMUInt64& headerPosition);

  static bool isHeader(const OMKLVKey& k);

  static bool isBody(const OMKLVKey& k);

  static bool isFooter(const OMKLVKey& k);

  static bool isPartition(const OMKLVKey& k);

  static bool isIncomplete(const OMKLVKey& k);

  static bool isClosed(const OMKLVKey& k);

  static bool isIndex(const OMKLVKey& k);

  static bool isEssence(const OMKLVKey& k);

  static bool isFill(const OMKLVKey& k);

    // @cmember Write a fill key, a BER encoded length and
    //          fill between <p from> and <p to>.
  virtual void writeKLVFill(const OMUInt64& from, const OMUInt64& to) = 0;

    // @cmember Write fill so that the next key is page aligned.
  virtual void fillAlignK(const OMUInt64& currentPosition,
                          const OMUInt32& KAGSize) = 0;

    // @cmember Write fill so that the next value is page aligned.
  virtual void fillAlignV(const OMUInt64& currentPosition,
                          const OMUInt32& KAGSize) = 0;

  virtual void write(const OMByte* bytes,
                     OMUInt32 byteCount,
                     OMUInt32& bytesWritten) = 0;
  virtual void write(const OMUInt8& i) = 0;
  virtual void write(const OMUInt16& i, bool reorderBytes) = 0;
  virtual void write(const OMUInt32& i, bool reorderBytes) = 0;
  virtual void write(const OMUInt64& i, bool reorderBytes) = 0;
  virtual void write(const OMUniqueObjectIdentification& id,
                     bool reorderBytes) = 0;
  virtual void write(const OMByte* buffer,
                     const OMUInt32& bufferSize) = 0;

  virtual void writeKLVKey(const OMKLVKey& key) = 0;

  virtual void writeKLVLength(const OMUInt8& length) = 0;
  virtual void writeKLVLength(const OMUInt16& length) = 0;
  virtual void writeKLVLength(const OMUInt32& length) = 0;
  virtual void writeKLVLength(const OMUInt64& length) = 0;

  virtual OMUInt64 reserveKLVLength(void) = 0;
  virtual void fixupKLVLength(const OMUInt64 lengthPosition) = 0;

  virtual OMUInt64 reserve(OMUInt32 size) = 0;
  virtual void fixup(const OMUInt64& patchOffset, const OMUInt8& patchValue) = 0;
  virtual void fixup(const OMUInt64& patchOffset, const OMUInt16& patchValue) = 0;
  virtual void fixup(const OMUInt64& patchOffset, const OMUInt32& patchValue) = 0;
  virtual void fixup(const OMUInt64& patchOffset, const OMUInt64& patchValue) = 0;

    // @cmember The minimum size of <p i> when encoded using <f berEncode>.
    //          The returned size includes the BER length byte.
  static size_t berEncodedSize(const OMUInt64 i);

    // @cmember BER encode <p value> into <p berValueBuffer>.
  static void berEncode(OMByte* berValueBuffer,
                        size_t berValueBufferSize,
                        const OMUInt32& berValueSize,
                        const OMUInt64& value);

  virtual void readHeaderPartition(void) = 0;

  static bool read(const OMRawStorage* store, OMUInt8& i);
  static bool read(const OMRawStorage* store, OMUInt16& i, bool reorderBytes);
  static bool read(const OMRawStorage* store, OMUInt32& i, bool reorderBytes);
  static bool read(const OMRawStorage* store, OMUInt64& i, bool reorderBytes);
  static bool read(const OMRawStorage* store, OMKLVKey& key);
  static bool readKLVLength(const OMRawStorage* store, OMUInt64& length);
  static bool skipBytes(const OMRawStorage* store, OMUInt64 length);

  virtual void read(OMUInt8& i) const = 0;
  virtual void read(OMInt8& i) const = 0;
  virtual void read(OMUInt16& i, bool reorderBytes) const = 0;
  virtual void read(OMUInt32& i, bool reorderBytes) const = 0;
  virtual void read(OMUInt64& i, bool reorderBytes) const = 0;
  virtual void read(OMInt64& i, bool reorderBytes) const = 0;
  virtual void read(OMUniqueObjectIdentification& id, bool reorderBytes) const = 0;
  virtual void read(OMByte* buffer, const OMUInt32& bufferSize) const = 0;
  virtual void read(OMByte* bytes,
                    OMUInt32 byteCount,
                    OMUInt32& bytesRead) const = 0;

  virtual void readKLVKey(OMKLVKey& key) const = 0;

  virtual bool readOuterKLVKey(OMKLVKey& key) const = 0;

  virtual OMUInt64 readKLVLength(void) const = 0;

  virtual void readKLVFill(void) const = 0;

  virtual void skipLV(void) const = 0;

  virtual void skipV(OMUInt64 length) const = 0;

  static OMUInt64 readBerLength(const OMRawStorage* store);

  // A weak reference in MXF file is stored as 16-byte InstanceUID of the
  // referenced object (see SMPTE 377M, Section 5.7.)
  // InstanceUID isn't currently part of the object model and cannot be
  // stored in OMReferenceProperty but it has to be preserved to resolve
  // (i.e. find the referenced object) the references once all the objects
  // were read from the file.
  // The following methods are used to save and access InstanceUID of the
  // referenced object for each restored weak reference property.
  //
    // @cmember Given pointer to a weak reference property return
    //          the InstanceUID of the referenced object.
  virtual bool findReferencedInstanceId(const void* reference,
                                        OMUniqueObjectIdentification* id) = 0;
    // @cmember Remember the InstanceUID of the object referenced
    //          by the specified weak reference property.
  virtual void associate(const void* reference,
                         const OMUniqueObjectIdentification& referencedInstanceId) = 0;


    // Object -> instanceId
  virtual OMUniqueObjectIdentification instanceId(OMStorable* object) = 0;

    // instanceId -> object
  virtual OMStorable* object(const OMUniqueObjectIdentification& instanceId) = 0;

    // object <-> instanceId
  virtual void associate(OMStorable* object,
                         const OMUniqueObjectIdentification& instanceId) = 0;

    // enter object into object directory
  virtual void enterObject(OMStorable& object, OMUInt64 position) = 0;

  virtual void removeObject(OMStorable& object) = 0;

  virtual bool containsObject(const OMUniqueObjectIdentification& instanceId) = 0;

  virtual void resolve(const OMUniqueObjectIdentification& instanceId) = 0;

  virtual OMUInt64 primerOffset(void) = 0;

  virtual void clearObjectDirectory(void) = 0;

  virtual void saveObjectDirectory(void) = 0;

  virtual void restoreObjectDirectory(OMUInt64 headerOffset) = 0;

  virtual void setObjectDirectoryOffset(OMUInt64 objectDirectoryOffset) = 0;

  virtual OMUInt64 objectDirectoryOffset(void) const = 0;

  virtual bool streamExists(OMUInt32 sid) = 0;

  virtual void createStreamAndAddSegment(OMUInt32 sid,
                            const OMKLVKey& label,
                            OMUInt32 blockSize,
                            OMUInt32 allocationSize,
                            bool alignV) = 0;

  virtual OMUInt32 addStream(OMDataStream* stream) = 0;

  virtual OMUInt32 streamIdentification(OMDataStream* stream) = 0;

  virtual OMDataStream* stream(OMUInt32 sid) = 0;

  virtual void associate(OMDataStream* stream, OMUInt32 sid) = 0;

  virtual bool containsStream(OMUInt32 sid) = 0;

  virtual bool containsStream(OMDataStream* stream) = 0;

  virtual OMUInt64 streamSize(OMUInt32 sid) = 0;

  virtual void streamSetSize(OMUInt32 sid, OMUInt64 newSize) = 0;

  virtual void writeStreamAt(OMUInt32 sid,
                             OMUInt64 position,
                             const OMByte* bytes,
                             OMUInt32 byteCount,
                             OMUInt32& bytesWritten) = 0;

  virtual void writeStreamAt(OMUInt32 sid,
                             OMUInt64 position,
                             OMIOBufferDescriptor* buffers,
                             OMUInt32 bufferCount,
                             OMUInt32& bytesWritten) = 0;

  virtual void writeStreamAt(OMUInt32 sid,
                             OMUInt64 position,
                             const OMByte* buffer,
                             const OMUInt32 bytes,
                             void* /* */ completion,
                             const void* clientArgument) = 0;

  virtual void writeStreamAt(OMUInt32 sid,
                             OMUInt64 position,
                             const OMIOBufferDescriptor* buffers,
                             OMUInt32 bufferCount,
                             void* /* */ completion,
                             const void* clientArgument) = 0;

  virtual void readStreamAt(OMUInt32 sid,
                            OMUInt64 position,
                            OMByte* bytes,
                            OMUInt32 byteCount,
                            OMUInt32& bytesRead) = 0;

  virtual void readStreamAt(OMUInt32 sid,
                            OMUInt64 position,
                            OMIOBufferDescriptor* buffers,
                            OMUInt32 bufferCount,
                            OMUInt32& bytesRead) = 0;

  virtual void readStreamAt(OMUInt32 sid,
                            OMUInt64 position,
                            OMByte* buffer,
                            const OMUInt32 bytes,
                            void* /* */ completion,
                            const void* clientArgument) = 0;

  virtual void readStreamAt(OMUInt32 sid,
                            OMUInt64 position,
                            OMIOBufferDescriptor* buffers,
                            OMUInt32 bufferCount,
                            void* /* */ completion,
                            const void* clientArgument) = 0;

  virtual void saveStreams(void) = 0;
  virtual void restoreStreams(void) = 0;

  virtual const OMMXFIndexStream* indexStream(const OMUInt32 streamId) const = 0;

  virtual void checkStreams(void) = 0;

    // @cmember Record a reference to <p tag> at <p address>.
  virtual void reference(OMUInt64 address, OMUInt8 tag)= 0;

    // @cmember Provide a definition for <p tag> of <p value>.
  virtual void definition(OMUInt64 value, OMUInt8 tag)= 0;

    // @cmember Apply <c Fixup>s for <p tag>.
  virtual void fixup(OMUInt8 tag)= 0;

    // @cmember Apply all <c Fixup>s.
  virtual void fixup(void)= 0;

    // @cmember Destroy all <c Fixup>s.
  virtual void destroyFixups(void)= 0;

  // Deferred streams
  virtual void addDeferredStream(OMDataStreamProperty* stream) = 0;

  virtual void performDeferredIO(void) = 0;

  static bool endsMetadata(const OMKLVKey& k);
  virtual void postMetadataSavePosition(void) = 0;

private:
  // @access Private members.

  static bool findPattern(const OMRawStorage* store,
                          OMUInt64 currentPosition,
                          OMUInt64& patternPosition,
                          const OMByte* pattern,
                          OMUInt64 patternSize,
                          OMUInt32 limit);

};

#endif
