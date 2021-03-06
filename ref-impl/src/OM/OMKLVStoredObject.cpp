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
// @author Tim Bingham | tjb | Avid Technology, Inc. | OMKLVStoredObject
#include "OMKLVStoredObject.h"

#include "OMMXFStorageBase.h"
#if 0
#include "OMCachedDiskRawStorage.h"
#else
#include "OMMemoryRawStorage.h"
#endif
#include "OMKLVStoredStream.h"
#include "OMProperty.h"
#include "OMPropertySetIterator.h"
#include "OMStrongRefProperty.h"
#include "OMStrongReference.h"
#include "OMStrongReferenceSet.h"
#include "OMStrongReferenceVector.h"
#include "OMObjectReference.h"
#include "OMContainerElement.h"
#include "OMDataStream.h"
#include "OMDataStreamAccess.h"  // !!! tjb
#include "OMIntegerType.h"
#include "OMCharacterType.h"
#include "OMStringType.h"
#include "OMEnumeratedType.h"
#include "OMObjectReferenceType.h"
#include "OMRenamedType.h"
#include "OMStreamType.h"
#include "OMOpaqueType.h"
#include "OMExtendibleEnumeratedType.h"
#include "OMIndirectType.h"
#include "OMUniqueObjectIdentType.h"
#include "OMRootStorable.h"
#include "OMVector.h"
#include "OMVectorIterator.h"
#include "OMWeakReference.h"
#include "OMWeakReferenceVector.h"
#include "OMWeakReferenceSet.h"
#include "OMPropertyTable.h"
#include "OMStrongReferenceSetIter.h"
#include "OMClassDefinition.h"
#include "OMPropertyDefinition.h"
#include "OMDataStreamProperty.h"
#include "OMArrayType.h"
#include "OMSetType.h"
#include "OMDataSet.h"
#include "OMDataVector.h"
#include "OMDataContainer.h"
#include "OMDataContainerIterator.h"
#include "OMExceptions.h"
#include "OMWideStringProperty.h"

#include "OMUtilities.h"

#include "OMRawStorage.h"


#define USETAGTABLE 1
//#define OM_EXTENSIONSONLY 1
// If defined, OM_SAVEOBJECTDIRECTORY causes Object Directory
// to be written to a file.
#define OM_SAVEOBJECTDIRECTORY 1
// If defined, OM_WRITELEGACYROOTCLASSID causes the SMPTE Root class ID
// to be written to a file, otherwise the internal legacy GUID is used.
#define OM_WRITELEGACYROOTCLASSID 1
// If defined, OM_STRICTMXFPARSER turns on stricter standard compliance
// and consitency validation of MXF files during restore.
//#define OM_STRICTMXFPARSER 1

#include "OMTypeVisitor.h"

OMKLVKey metaDictionaryKey =
  {0x8A, 0xE5, 0x95, 0x9D, 0x57, 0xB3, 0xDA, 0x33,
   0x8A, 0x5F, 0xB4, 0x11, 0x4D, 0x66, 0x4B, 0x40};

// {0D010101-0300-0000-060E-2B3402060101}
const OMClassId SMPTERootClassId =
{0x0d010101, 0x0300, 0x0000, {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x06, 0x01, 0x01}};

const OMPropertyId PID_AES3PCMDescriptor_FixedChannelStatusData = 0x3d11;
const OMPropertyId PID_AES3PCMDescriptor_FixedUserData = 0x3d13;

  // @mfunc Open the root <c OMKLVStoredObject> in the raw storage
  //        <p rawStorage> for reading only.
  //   @parm The raw storage in which to open the file.
  //   @rdesc An <c OMKLVStoredObject> representing the root object.
OMKLVStoredObject* OMKLVStoredObject::openRead(OMMXFStorageBase* rawStorage)
{
  TRACE("OMKLVStoredObject::openRead");
  PRECONDITION("Compatible raw storage access mode", rawStorage->isReadable());
  OMKLVStoredObject* result = new OMKLVStoredObject(rawStorage, littleEndian);
  ASSERT("Valid heap pointer", result != 0);
  rawStorage->openRead();
  return result;
}

  // @mfunc Open the root <c OMKLVStoredObject> in the raw storage
  //   @parm The raw storage in which to open the file.
  //   @rdesc An <c OMKLVStoredObject> representing the root object.
  //        <p rawStorage> for modification.
OMKLVStoredObject* OMKLVStoredObject::openModify(OMMXFStorageBase* rawStorage)
{
  TRACE("OMKLVStoredObject::openModify");
  PRECONDITION("Compatible raw storage access mode",
                         rawStorage->isReadable() && rawStorage->isWritable());
  PRECONDITION("Compatible raw storage", rawStorage->isPositionable());
  OMKLVStoredObject* result = new OMKLVStoredObject(rawStorage, littleEndian);
  ASSERT("Valid heap pointer", result != 0);
  rawStorage->openModify();
  return result;
}

  // @mfunc Create a new root <c OMKLVStoredObject> in the raw storage
  //        <p rawStorage>. The byte order of the newly created root
  //        is given by <p byteOrder>.
  //   @parm The raw storage in which to create the file.
  //   @parm The desired byte ordering for the new file.
  //   @rdesc An <c OMKLVStoredObject> representing the root object.
OMKLVStoredObject* OMKLVStoredObject::createWrite(OMMXFStorageBase* rawStorage,
                                                  const OMByteOrder byteOrder)
{
  TRACE("OMKLVStoredObject::createWrite");
  PRECONDITION("Compatible raw storage access mode", rawStorage->isWritable());
  OMKLVStoredObject* result= new OMKLVStoredObject(rawStorage, byteOrder);
  ASSERT("Valid heap pointer", result != 0);
  rawStorage->createWrite();
  return result;
}

  // @mfunc Create a new root <c OMKLVStoredObject> in the raw storage
  //        <p rawStorage>. The byte order of the newly created root
  //        is given by <p byteOrder>.
  //   @parm The raw storage in which to create the file.
  //   @parm The desired byte ordering for the new file.
  //   @rdesc An <c OMKLVStoredObject> representing the root object.
OMKLVStoredObject* OMKLVStoredObject::createModify(OMMXFStorageBase* rawStorage,
                                                   const OMByteOrder byteOrder)
{
  TRACE("OMKLVStoredObject::createModify");
  PRECONDITION("Compatible raw storage access mode",
                         rawStorage->isReadable() && rawStorage->isWritable());
  PRECONDITION("Compatible raw storage", rawStorage->isPositionable());
  OMKLVStoredObject* result= new OMKLVStoredObject(rawStorage, byteOrder);
  ASSERT("Valid heap pointer", result != 0);
  rawStorage->createModify();
  return result;
}

  // @mfunc Does <p rawStorage> contain a recognized file ?
  //        If so, the result is true.
  //   @parm The raw storage.
  //   @rdesc True if the file is recognized, false otherwise.
bool
OMKLVStoredObject::isRecognized(OMRawStorage* rawStorage)
{
  TRACE("OMKLVStoredObject::isRecognized");
  PRECONDITION("Valid raw storage", rawStorage != 0);
  PRECONDITION("Positionable raw storage", rawStorage->isPositionable());

  bool reorderBytes;
  if (hostByteOrder() == bigEndian) {
    reorderBytes = false;
  } else {
    reorderBytes = true;
  }
  bool result = false;
  OMUInt64 headerPosition;
  bool foundHeader = OMMXFStorageBase::findHeader(rawStorage, headerPosition);
  if (foundHeader) {
    rawStorage->setPosition(headerPosition);
    OMKLVKey k;
    if (OMMXFStorageBase::read(rawStorage, k)) {
      if (OMMXFStorageBase::isHeader(k)) {
        OMUInt64 length;
        if (OMMXFStorageBase::readKLVLength(rawStorage, length)) {
          OMUInt16 majorVersion;
          if (OMMXFStorageBase::read(rawStorage, majorVersion, reorderBytes)) {
            if (majorVersion == currentMajorVersion) {
              OMUInt16 minorVersion;
              if (OMMXFStorageBase::read(rawStorage, minorVersion, reorderBytes)) {
                if (minorVersion == currentMinorVersion ||
                    minorVersion == 0x0003) {
                  // Skip up to count of essence container labels.
                  OMUInt64 skip = fixedPartitionSize -
                                  (2 * sizeof(OMUInt16)) - // major/minor
                                  (2 * sizeof(OMUInt32));  // ecl count/size
                  OMMXFStorageBase::skipBytes(rawStorage, skip);
                  // Read essence container label count and size.
                  OMUInt32 elementCount;
                  OMMXFStorageBase::read(rawStorage, elementCount, reorderBytes);
                  OMUInt32 elementSize;
                  OMMXFStorageBase::read(rawStorage, elementSize, reorderBytes);
                  // Check for consistency between partition length and essence
                  // container label count and size.
                  OMUInt64 expectedLength = fixedPartitionSize +
                                            (elementCount * elementSize);
                  if (length == expectedLength) {
                    result = true;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  rawStorage->setPosition(0);
  return result;
}

  // @mfunc Can the contents of a file on the given <c OMRawStorage>
  //          be successfully modified ?
  //   @parm The raw storage.
  //   @rdesc True if the file contents can be modified, false otherwise.
bool OMKLVStoredObject::modifiableStoredFormat(const OMRawStorage* rawStorage)
{
  TRACE("OMKLVStoredObject::isRecognized");
  PRECONDITION("Valid raw storage", rawStorage != 0);
  PRECONDITION("Positionable raw storage", rawStorage->isPositionable());

  bool reorderBytes;
  if (hostByteOrder() == bigEndian) {
    reorderBytes = false;
  } else {
    reorderBytes = true;
  }

  // Read version numbers of the MXF byte-level format from
  // the Header Partition. Allow modifying only files whose
  // format version matches the current version supported
  // by AAF SDK.
  // In MXF the byte-level format version can be used to
  // identify the version of the Object Specification and
  // the version of the objects storage format.
  bool result = false;
  OMUInt64 headerPosition;
  bool foundHeader = OMMXFStorageBase::findHeader(rawStorage, headerPosition);
  if (foundHeader) {
    rawStorage->setPosition(headerPosition);
    OMKLVKey k;
    if (OMMXFStorageBase::read(rawStorage, k)) {
      OMUInt64 length;
      if (OMMXFStorageBase::readKLVLength(rawStorage, length)) {
        OMUInt16 majorVersion;
        if (OMMXFStorageBase::read(rawStorage, majorVersion, reorderBytes)) {
            OMUInt16 minorVersion;
          if (OMMXFStorageBase::read(rawStorage, minorVersion, reorderBytes)) {
            if (majorVersion == currentMajorVersion &&
                minorVersion == currentMinorVersion) {
              result = true;
            }
          }
        }
      }
    }
  }
  rawStorage->setPosition(0);
  return result;
}

  // @mfunc Does <p file> have an <c OMMXFStorageBase>.
  //   @parm The <c OMFile>
  //   @rdesc <e bool.true> if the given <c OMFile> has an
  //          <c OMMXFStorageBase>, <e bool.false> otherwise.
bool OMKLVStoredObject::hasMxfStorage(const OMFile* file)
{
  TRACE("OMKLVStoredObject::hasMxfStorage");
  PRECONDITION("Valid file", file != 0);

  bool result = false;
  OMKLVStoredObject* r = root(file);
  if (r != 0) {
    result = true;
  }
  return result;
}

  // @mfunc The <c OMMXFStorageBase> associated with <p file>.
  //   @parm The <c OMFile>
  //   @rdesc The <c OMMXFStorageBase>
OMMXFStorageBase* OMKLVStoredObject::mxfStorage(const OMFile* file)
{
  TRACE("OMKLVStoredObject::mxfStorage");
  PRECONDITION("Valid file", file != 0);
  PRECONDITION("File has MXF storage", hasMxfStorage(file));

  OMKLVStoredObject* r = root(file);
  OMMXFStorageBase* result = r->_storage;

  return result;
}

  // @mfunc The root storage of <p file>.
  //   @parm The <c OMFile>
  //   @rdesc The root <c OMKLVStoredObject> if <p file> is KLV encoded,
  //          0 otherwise.
OMKLVStoredObject* OMKLVStoredObject::root(const OMFile* file)
{
  TRACE("OMKLVStoredObject::root");
  OMKLVStoredObject* result = 0;
  OMStoredObject* r = const_cast<OMFile*>(file)->rootStore();
  if (r != 0) {
    result = dynamic_cast<OMKLVStoredObject*>(r);
  }
  return result;
}

  // @mfunc Does <p stream> represent MXF essence ?
  //   @parm The <c OMDataStreamProperty>
  //   @rdesc <e bool.true> if the given <c OMDataStreamProperty> has an
  //          <c OMMXFStorageBase>, <e bool.false> otherwise.
bool OMKLVStoredObject::isMxfEssence(const OMDataStreamProperty* stream)
{
  TRACE("OMKLVStoredObject::isMxfEssence");
  PRECONDITION("Valid stream", stream != 0);
  bool result = false;
  OMKLVStoredStream* s = mxfStream(stream);
  if (s != 0) {
    result = true;
  }
  return result;
}

  // @mfunc The <c OMKLVStoredStream> associated with <p stream>.
  //   @parm The <c OMDataStreamProperty>
  //   @rdesc The <c OMKLVStoredStream>
OMKLVStoredStream*
OMKLVStoredObject::mxfEssence(const OMDataStreamProperty* stream)
{
  TRACE("OMKLVStoredObject::mxfEssence");
  PRECONDITION("Valid stream", stream != 0);
  PRECONDITION("MXF essence", isMxfEssence(stream));
  OMKLVStoredStream* result = mxfStream(stream);
  return result;
}

  // @mfunc The <c OMKLVStoredStream> associated with <p stream>
  //   @parm The <c OMDataStreamProperty>
  //   @rdesc The <c OMKLVStoredStream> if <p stream> is KLV encoded,
  //          0 otherwise.
OMKLVStoredStream*
OMKLVStoredObject::mxfStream(const OMDataStreamProperty* stream)
{
  TRACE("OMKLVStoredObject::mxfStream");
  PRECONDITION("Valid stream", stream != 0);
  OMStoredStream* s = stream->stream();
  OMKLVStoredStream* result = dynamic_cast<OMKLVStoredStream*>(s);
  return result;
}

bool OMKLVStoredObject::isEnforcingST377(const OMFile* file)
{
  TRACE("OMKLVStoredObject::isEnforcingST377");
  // Experimental: Enable to enforce ST 377M constraints.
  // The result may not be readable by the current version.
  return false;
}

  // @mfunc Are bits in <p externalValue> a SMPTE UL representation of
  //        an extendible enumumeration value of type <p type>?
  //        See comments in the implementation regarding reliabity of
  //        this routine.
  //   @parm Buffer with external/stored value if a property.
  //   @parm Size of <p externalValue>.
  //   @parm Type of the property with value <p externalValue>.
/*static*/ bool OMKLVStoredObject::isExtendibleEnumStoredAsSMPTEUL(
    const OMByte* externalValue,
    const OMUInt32 externalSize,
    const OMType* type)
{
  TRACE("OMKLVStoredObject::isExtendibleEnumStoredAsSMPTEUL()");
  PRECONDITION("Valid value buffer", externalValue != 0);
  PRECONDITION("Valid type", type != 0);

  bool result = false;
  if (type->tag() == OMType::OMTTExtendibleEnumerated) {
    static const OMByte smpteULPrefix[] = {0x06, 0x0e, 0x2b, 0x34};
    if (externalSize == 16 && memcmp(externalValue, smpteULPrefix, 4) == 0) {
      // Value is a SMPTE UL
      result = true;
    } else {
      // Check if the value is a UID stored as SMPTE UL: assuming that the
      // value is stored as SMPTE UL convert it into UID and check if the
      // property type definition contains the UID. If it does then the
      // value is formated as SMPTE UL.
      // Note that this approach relies on the extendible enumumeration type
      // definition being complete, i.e. containing definitions for all the
      // possible values of this type. A file where extendible enumumeration
      // types miss value definitions is considered invalid. Such files do
      // exist due to earlier versions of the SDK failure to enforce the
      // value definition requirement. For such files at this level it is
      // impossible to determine if extendible enumumeration value that's
      // a UID is stored as a SMPTE UL. On the other hand, same earlier
      // versions of the SDK did not store extendible enumumeration values
      // as ULs so the results produces by this routine should be sufficiently
      // reliable.
      const OMKLVKey* key = reinterpret_cast<const OMKLVKey*>(externalValue);
      OMUniqueObjectIdentification id;
      convert(id, *key);
      const OMExtendibleEnumeratedType* extendibleEnumType =
                         dynamic_cast<const OMExtendibleEnumeratedType*>(type);
      ASSERT("Valid extendible enumeration type", extendibleEnumType != 0);
      for (OMUInt32 i = 0; i < extendibleEnumType->elementCount(); i++) {
        if (extendibleEnumType->elementValue(i) == id) {
          result = true;
          break;
        }
      }
    }
  }
  return result;
}

  // @mfunc Destructor.
OMKLVStoredObject::~OMKLVStoredObject(void)
{
  TRACE("OMKLVStoredObject::~OMKLVStoredObject");
}

  // @mfunc Create a new <c OMKLVStoredObject>, named <p name>,
  //        contained by this <c OMKLVStoredObject>.
  //   @parm The name to be used for the new <c OMKLVStoredObject>.
  //   @rdesc A new <c OMKLVStoredObject> contained by this
  //          <c OMKLVStoredObject>.
OMStoredObject* OMKLVStoredObject::create(const wchar_t* /* name */)
{
  TRACE("OMKLVStoredObject::create");
  OMStoredObject* result = new OMKLVStoredObject(_storage, _byteOrder);
  ASSERT("Valid heap pointer", result != 0);
  return result;
}

  // @mfunc Create a new <c OMKLVStoredObject>, contained by this
  //        <c OMKLVStoredObject>. The new <c OMKLVStoredObject> is
  //        a stored representatin of an <c OMStorable> referenced by
  //        <p containingProperty>.
  //   @parm The property that references the new <c OMKLVStoredObject>.
  //   @rdesc A new <c OMKLVStoredObject> contained by this
  //          <c OMKLVStoredObject>.
OMStoredObject* OMKLVStoredObject::create(const OMProperty* /*containingProperty*/)
{
  TRACE("OMKLVStoredObject::create");
  return create(static_cast<const wchar_t*>(0));
}

  // @mfunc Create a new <c OMKLVStoredObject>, contained by this
  //        <c OMKLVStoredObject>. The new <c OMKLVStoredObject> is
  //        a stored representatin of an <c OMStorable> referenced by
  //        an element <p localKey> of <p containingProperty>.
  //   @parm The vector/set property that references the new
  //         <c OMKLVStoredObject>.
  //   @parm The local key of the element of the vector/set property that
  //         references the new <c OMKLVStoredObject>.
  //   @rdesc A new <c OMKLVStoredObject> contained by this
  //          <c OMKLVStoredObject>.
OMStoredObject* OMKLVStoredObject::create(const OMProperty* containingProperty,
                                          OMUInt32 /*localKey*/)
{
  TRACE("OMKLVStoredObject::create");
  return create(containingProperty);
}

  // @mfunc Open an existing <c OMKLVStoredObject>, named <p name>,
  //        contained by this <c OMKLVStoredObject>.
  //   @parm The name of the existing <c OMKLVStoredObject>.
  //   @rdesc The existing <c OMKLVStoredObject> contained by this
  //          <c OMKLVStoredObject>.
OMStoredObject* OMKLVStoredObject::open(const wchar_t* /* name */)
{
  TRACE("OMKLVStoredObject::open");
  OMStoredObject* result = new OMKLVStoredObject(_storage, _byteOrder);
  ASSERT("Valid heap pointer", result != 0);
  return result;
}

  // @mfunc Open an existing <c OMKLVStoredObject>, contained by this
  //        <c OMKLVStoredObject>. The existing <c OMKLVStoredObject> is
  //        a stored representatin of an <c OMStorable> referenced by
  //        <p containingProperty>.
  //   @parm The property that references the existing <c OMKLVStoredObject>.
  //   @rdesc The existing <c OMKLVStoredObject> contained by this
  //          <c OMKLVStoredObject>.
OMStoredObject* OMKLVStoredObject::open(const OMProperty* /*containingProperty*/)
{
  TRACE("OMKLVStoredObject::open");
  return open(static_cast<const wchar_t*>(0));
}

  // @mfunc Open an existing <c OMKLVStoredObject>, contained by this
  //        <c OMKLVStoredObject>. The existing <c OMKLVStoredObject> is
  //        a stored representatin of an <c OMStorable> referenced by
  //        an element <p localKey> of <p containingProperty>.
  //   @parm The vector/set property that references the existing
  //         <c OMKLVStoredObject>.
  //   @parm The local key of the element of the vector/set property that
  //         references the existing <c OMKLVStoredObject>.
  //   @rdesc The existing <c OMKLVStoredObject> contained by this
  //          <c OMKLVStoredObject>.
OMStoredObject* OMKLVStoredObject::open(const OMProperty* containingProperty,
                                        OMUInt32 /*localKey*/)
{
  TRACE("OMKLVStoredObject::open");
  return open(containingProperty);
}

  // @mfunc Close this <c OMKLVStoredObject>.
void OMKLVStoredObject::close(void)
{
  TRACE("OMKLVStoredObject::close");
}

  // @mfunc The byte order of this <c OMKLVStoredObject>.
  //   @rdesc The byte order.
  //   @this const
OMByteOrder OMKLVStoredObject::byteOrder(void) const
{
  TRACE("OMKLVStoredObject::byteOrder");

  return _byteOrder;
}

#if defined(USETAGTABLE)
static struct {
  OMPropertyTag _tag;
  OMUInt16 _pids[4];
  const wchar_t* _path;
} map [] = {
  {0xffff,
   {0x0001, 0x0003},         L"/MetaDictionary/ClassDefinitions"},
  {0xffff,
   {0x0001, 0x0004},         L"/MetaDictionary/TypeDefinitions"},
  {0xffff,
   {0x0002, 0x3b04, 0x2605}, L"/Header/Dictionary/DataDefinitions"},
  {0xffff,
   {0x0002, 0x3b04, 0x2608}, L"/Header/Dictionary/ContainerDefinitions"},
  {0xffff,
   {0x0002, 0x3b04, 0x2607}, L"/Header/Dictionary/CodecDefinitions"},
  {0xffff,
   {0x0002, 0x3b04, 0x2603}, L"/Header/Dictionary/OperationDefinitions"},
  {0xffff,
   {0x0002, 0x3b04, 0x2609}, L"/Header/Dictionary/InterpolationDefinitions"},
  {0xffff,
   {0x0002, 0x3b04, 0x2604}, L"/Header/Dictionary/ParameterDefinitions"},
};

static size_t mapSize = sizeof(map)  / sizeof(map[0]);

static void initializeMap(OMFile& file)
{
  for (size_t i = 0; i < mapSize; i++) {
    OMPropertyTag tag = file.referencedProperties()->insert(map[i]._pids);
    map[i]._tag = tag;
  }
}

static OMPropertyTag findTag(const wchar_t* path)
{
  TRACE("findTag");
  OMPropertyTag result =  nullOMPropertyTag;
  for (size_t i = 0; i < mapSize; i++) {
    if (compareWideString(path, map[i]._path) == 0) {
      result = map[i]._tag;
      break;
    }
  }
  POSTCONDITION("", result != nullOMPropertyTag);
  return result;
}
#endif

void OMKLVStoredObject::save(OMFile& file)
{
  TRACE("OMKLVStoredObject::save(OMFile)");

  save(file, true);
}

void OMKLVStoredObject::save(OMFile& file, bool finalize)
{
  TRACE("OMKLVStoredObject::save(OMFile&, bool)");

  _storage->open();

  OMUInt64 pos = _storage->primerOffset();
  _storage->setPosition(pos);
  // Write the primer
  writePrimerPack(file.dictionary());
  _storage->fillAlignK(_storage->position(), defaultKAGSize);

  // Save the rest of the file
#if defined(OM_EXTENSIONSONLY)
  // Get the (hidden) root object
  OMStorable* root = file.root();

  // Get the meta-dictionary and save it
  OMProperty* mdp = root->propertySet()->get(PID_Root_MetaDictionary);
  OMStrongReference* mdsr = dynamic_cast<OMStrongReference*>(mdp);
  ASSERT("Valid type", mdsr != 0);
  OMStrongObjectReference& mdr = mdsr->reference();
  OMStorable* mdo = mdr.getValue();
  ASSERT("Valid object", mdo != 0);
  OMDictionary* dictionary = dynamic_cast<OMDictionary*>(mdo);
  ASSERT("Valid dictionary", dictionary != 0);

  writeMetaDictionary(dictionary);

  // Get the client root and save it
  OMStorable* cr = file.clientRoot();
  cr->save();

#if defined(OM_SAVEOBJECTDIRECTORY)
  if (!isEnforcingST377(&file)) {
    // Save the meta object directory
    _storage->saveObjectDirectory();
  }
#endif
#else
  if (!file.dictionary()->isRequired(file.encoding())) {
    // Get only the client root and save it
    file.clientRoot()->save();
  } else {
    // Save everything including the metadictionary
    file.root()->save();

#if defined(OM_SAVEOBJECTDIRECTORY)
    if (!isEnforcingST377(&file)) {
      // Save the meta object directory
      _storage->saveObjectDirectory();
    }
#endif
  }
#endif

  _storage->postMetadataSavePosition();
  _storage->performDeferredIO();

  // Save streams
  //
  _storage->saveStreams();

  _storage->postSave(finalize);
  _storage->close();
}

void OMKLVStoredObject::save(OMStorable& object)
{
  TRACE("OMKLVStoredObject::save(OMStorable)");

  OMUInt64 position = _storage->position();
  _storage->enterObject(object, position);

  OMClassId classId = object.classId();
#if !defined (OM_WRITELEGACYROOTCLASSID)
  if (classId == OMRootStorable::_rootClassId) {
    classId = SMPTERootClassId;
  }
#else
  if (classId == OMRootStorable::_rootClassId &&
      isEnforcingST377(object.file())) {
    classId = SMPTERootClassId;
  }
#endif
  save(classId);
  save(*object.propertySet());
}

  // @mfunc Save the <c OMStoredObjectIdentification> <p id>
  //        in this <c OMKLVStoredObject>.
  //   @parm The <t OMStoredObjectIdentification> to save.
void OMKLVStoredObject::save(const OMStoredObjectIdentification& id)
{
  TRACE("OMKLVStoredObject::save(OMStoredObjectIdentification)");

  OMKLVKey k;
  convert(k, id);
  _storage->writeKLVKey(k);
}

  // @mfunc Save the <c OMPropertySet> <p properties> in this
  //        <c OMKLVStoredObject>.
  //   @parm The <c OMPropertySet> to save.
void OMKLVStoredObject::save(const OMPropertySet& properties)
{
  TRACE("OMKLVStoredObject::save(OMPropertySet)");

  // Length
  OMUInt64 lengthPosition = _storage->reserveKLVLength();

  // Flat properties
  flatSave(properties);

  // patch length
  _storage->fixupKLVLength(lengthPosition);

  // Deep properties
  deepSave(properties);
}

  // @mfunc Save the <c OMSimpleProperty> <p property> in this
  //        <c OMKLVStoredObject>.
  //   @parm The <c OMSimpleProperty> to save.
void OMKLVStoredObject::save(const OMSimpleProperty& property)
{
  TRACE("OMKLVStoredObject::save(OMSimpleProperty)");

  OMUInt32 bs = property.bitsSize();
  ASSERT("Property value not too big", bs <= OMPROPERTYSIZE_MAX);
  OMPropertySize size = static_cast<OMPropertySize>(bs);
  OMByte* bits = property.bits();
  const OMType* propertyType = property.type();
  ASSERT("Valid property type", propertyType != 0);

  // Allocate buffer for property value
  OMUInt32 sz = propertyType->externalSize(bits, size);
  ASSERT("Property not too big", sz <= OMPROPERTYSIZE_MAX);
  OMPropertySize externalBytesSize = static_cast<OMPropertySize>(sz);
  OMByte* buffer = new OMByte[externalBytesSize];
  ASSERT("Valid heap pointer", buffer != 0);

  if ((propertyType->identification() == Type_UniqueObjectIdentification) ||
      (propertyType->identification() == Type_TransferCharacteristic)) {
    // UniqueObjectIdentification properties are stored
    // as SMPTE universal labels in KLV-encoded files
    const OMUniqueObjectIdentification& id =
        *(OMUniqueObjectIdentification*)bits;
    convert(*(OMKLVKey*)buffer, id);
  } else if (propertyType->tag() == OMType::OMTTExtendibleEnumerated &&
             isEnforcingST377(property.container()->file())) {
    // Extendible enumeration properties are UniqueObjectIdentifications and
    // are stored as SMPTE universal labels in SMPTE-compliant MXF files.
    const OMUniqueObjectIdentification& id =
                  *reinterpret_cast<const OMUniqueObjectIdentification*>(bits);
    convert(*(OMKLVKey*)buffer, id);
  } else if (propertyType->identification() == Type_ProductVersion &&
             isEnforcingST377(property.container()->file())) {
    // ProductVersion properties are stored as 10 byte values in
    // SMPTE-compliant MXF files, as opposed to 9 bytes for other
    // encodings. The culprit is the last member ProductVersion::type
    // which is traditionally stored as UInt8 but is required to be
    // serialized as UInt16 by the MXF specification.
    const OMRecordType* recordType =
                               dynamic_cast<const OMRecordType*>(propertyType);
    ASSERT("Valid record type", recordType != 0);
    ASSERT("Valid record type", recordType->memberCount() == 5);
    const OMType* memberType = recordType->memberType(4);
    const OMPropertySize memberDefaultExternalSize =
                       static_cast<OMPropertySize>(memberType->externalSize());
    const OMPropertySize memberAdjustedExternalSize = sizeof(OMUInt16);
    const OMPropertySize adjustedExternalSize = externalBytesSize -
                                                memberDefaultExternalSize + 
                                                memberAdjustedExternalSize;
    // Re-allocate the external bits buffer to accommodate the adjusted
    // external size.
    delete [] buffer;
    buffer = new OMByte[adjustedExternalSize];
    ASSERT("Valid heap pointer", buffer != 0);

    // Externalize property value using default
    // external size for all record members.
    propertyType->externalize(bits,
                              size,
                              buffer,
                              externalBytesSize,
                              hostByteOrder());

    if (_reorderBytes) {
      propertyType->reorder(buffer, externalBytesSize);
    }

    // Re-externalize the last record property value member,
    // this time using MXF-compliant external size.
    const OMUInt32 memberInternalSize = memberType->internalSize();
    const OMByte* memberInternalBits = bits +
                                       propertyType->internalSize() -
                                       memberInternalSize;
    OMByte* memberExternalBits =  buffer +
                                  externalBytesSize -
                                  memberDefaultExternalSize;
    ASSERT("Expected size", memberInternalSize > memberAdjustedExternalSize);
    OMType::contract(memberInternalBits,
                     memberInternalSize,
                     memberExternalBits,
                     memberAdjustedExternalSize,
                     hostByteOrder());
    if (_reorderBytes) {
        OMType::reorderInteger(memberExternalBits, memberAdjustedExternalSize);
    }

    externalBytesSize = adjustedExternalSize;
  } else {
    // Externalize property value
    propertyType->externalize(bits,
                              size,
                              buffer,
                              externalBytesSize,
                              hostByteOrder());

    // Reorder property value
    if (_reorderBytes) {
      propertyType->reorder(buffer, externalBytesSize);
    }
  }

  // size
  _storage->write(externalBytesSize, _reorderBytes);
  // value
  _storage->write(buffer, externalBytesSize);

  delete [] buffer;
}

void OMKLVStoredObject::save(const OMDataVector& property)
{
  TRACE("OMKLVStoredObject::save(OMDataVector)");

  const OMType* propertyType = property.type();
  ASSERT("Valid property type", propertyType != 0);
  const OMArrayType* at = dynamic_cast<const OMArrayType*>(propertyType);
  ASSERT("Correct type", at != 0);
  OMType* elementType = at->elementType();
  ASSERT("Fixed size elements", elementType->isFixedSize());
  OMUInt32 elementSize = elementType->internalSize();
  OMUInt32 externalElementSize = elementType->externalSize();
  OMUInt32 elementCount = property.count();

  // Standard-compliant serialization of arrays of ProductVersion elements
  // is not implemented. At this time failing to save such properties
  // shouldn't have any practical impact as no standard properties of this
  // type exist and it's unlikely that applicaions are creating custom
  // properties of this type.
  if (elementType->identification() == Type_ProductVersion &&
      isEnforcingST377(property.container()->file())) {
    throw OMException("ST377-compliant serialization of arrays of "
                      "ProductVersion values is not implemented.");
  }

    // Allocate buffer for one element
  OMByte* buffer = new OMByte[externalElementSize];
  ASSERT("Valid heap pointer", buffer != 0);

  // size
  // Doh! 32-bit size and count but 16-bit property size
  OMUInt64 size = externalElementSize * elementCount;
  ASSERT("Property not too big",
           (size + sizeof(OMUInt32) + sizeof(OMUInt32)) <= OMPROPERTYSIZE_MAX);
  OMPropertySize propertySize = static_cast<OMPropertySize>(size);
  propertySize = propertySize + sizeof(OMUInt32) + sizeof(OMUInt32);
  _storage->write(propertySize, _reorderBytes);

  if (property.propertyId() == PID_AES3PCMDescriptor_FixedChannelStatusData ||
      property.propertyId() == PID_AES3PCMDescriptor_FixedUserData) {

    // SMPTE Elements Register defines the type of FixedChannelStatusData
    // and FixedUserData properties as UInt8Array. But SMPTE 382M-2007
    // mapping standard defines the stored format of these properties in
    // MXF as an array of 24-byte elements. The following code ignores
    // the Register-supplied element size and writes 24-byte size, and
    // corresponding element count, required by the MXF mapping standard.
    // Restoring these properties doesn't require any special handling because
    // the parser ignores the stored array format and relies only on the
    // dictionary definitions to find the array element size and count.
    ASSERT("Expected element size", elementSize == 1);
    ASSERT("Expected element count", (elementCount % 24) == 0);
    const OMUInt32 externalElementSize = 24;
    const OMUInt32 externalElementCount = elementCount / externalElementSize;
    // element count
    _storage->write(externalElementCount, _reorderBytes);
    // element size
    _storage->write(externalElementSize, _reorderBytes);
  } else {
    // element count
    _storage->write(elementCount, _reorderBytes);

    // element size
    _storage->write(externalElementSize, _reorderBytes);
  }

  OMDataContainerIterator* it = property.createIterator();
  while (++(*it)) {

    // Get a pointer to the element
    const OMByte* bits = it->currentElement();

    if ((elementType->identification() == Type_UniqueObjectIdentification) ||
        (elementType->identification() == Type_TransferCharacteristic)) {
      // UniqueObjectIdentification properties are stored
      // as SMPTE universal labels in KLV-encoded files
      const OMUniqueObjectIdentification& id =
          *(OMUniqueObjectIdentification*)bits;
      convert(*(OMKLVKey*)buffer, id);
    } else if (elementType->tag() == OMType::OMTTExtendibleEnumerated &&
               isEnforcingST377(property.container()->file())) {
      // Extendible enumeration properties are UniqueObjectIdentifications and
      // are stored as SMPTE universal labels in SMPTE-compliant MXF files.
      const OMUniqueObjectIdentification& id =
                  *reinterpret_cast<const OMUniqueObjectIdentification*>(bits);
      convert(*(OMKLVKey*)buffer, id);
    } else {
      // Externalize element
      elementType->externalize(bits,
                               elementSize,
                               buffer,
                               externalElementSize,
                               hostByteOrder());

      // Reorder element
      if (_reorderBytes) {
        elementType->reorder(buffer, externalElementSize);
      }
    }

    // value
    _storage->write(buffer, externalElementSize);

  }
  delete it;
  delete [] buffer;
}

void OMKLVStoredObject::save(const OMDataSet& property)
{
  TRACE("OMKLVStoredObject::save(OMDataSet)");

  const OMType* propertyType = property.type();
  ASSERT("Valid property type", propertyType != 0);
  const OMSetType* st = dynamic_cast<const OMSetType*>(propertyType);
  ASSERT("Correct type", st != 0);
  OMType* elementType = st->elementType();
  ASSERT("Fixed size elements", elementType->isFixedSize());
  OMUInt32 elementSize = elementType->internalSize();
  OMUInt32 externalElementSize = elementType->externalSize();
  OMUInt32 elementCount = property.count();

  // Standard-compliant serialization of sets of ProductVersion elements
  // is not implemented. At this time failing to save such properties
  // shouldn't have any practical impact as no standard properties of this
  // type exist and it's unlikely that applicaions are creating custom
  // properties of this type.
  if (elementType->identification() == Type_ProductVersion &&
      isEnforcingST377(property.container()->file())) {
    throw OMException("ST377-compliant serialization of sets of "
                      "ProductVersion values is not implemented.");
  }

    // Allocate buffer for one element
  OMByte* buffer = new OMByte[externalElementSize];
  ASSERT("Valid heap pointer", buffer != 0);

  // size
  // Doh! 32-bit size and count but 16-bit property size
  OMUInt64 size = externalElementSize * elementCount;
  ASSERT("Property not too big",
           (size + sizeof(OMUInt32) + sizeof(OMUInt32)) <= OMPROPERTYSIZE_MAX);
  OMPropertySize propertySize = static_cast<OMPropertySize>(size);
  propertySize = propertySize + sizeof(OMUInt32) + sizeof(OMUInt32);
  _storage->write(propertySize, _reorderBytes);

  // element count
  _storage->write(elementCount, _reorderBytes);

  // element size
  _storage->write(externalElementSize, _reorderBytes);

  OMDataContainerIterator* it = property.createIterator();
  while (++(*it)) {

    // Get a pointer to the element
    const OMByte* bits = it->currentElement();


    if ((elementType->identification() == Type_UniqueObjectIdentification) ||
        (elementType->identification() == Type_TransferCharacteristic)) {
      // UniqueObjectIdentification properties are stored
      // as SMPTE universal labels in KLV-encoded files
      const OMUniqueObjectIdentification& id =
          *(OMUniqueObjectIdentification*)bits;
      convert(*(OMKLVKey*)buffer, id);
    } else if (elementType->tag() == OMType::OMTTExtendibleEnumerated &&
               isEnforcingST377(property.container()->file())) {
      // Extendible enumeration properties are UniqueObjectIdentifications and
      // are stored as SMPTE universal labels in SMPTE-compliant MXF files.
      const OMUniqueObjectIdentification& id =
                  *reinterpret_cast<const OMUniqueObjectIdentification*>(bits);
      convert(*(OMKLVKey*)buffer, id);
    } else {
      // Externalize element
      elementType->externalize(bits,
                               elementSize,
                               buffer,
                               externalElementSize,
                               hostByteOrder());

      // Reorder element
      if (_reorderBytes) {
        elementType->reorder(buffer, externalElementSize);
      }
    }

    // value
    _storage->write(buffer, externalElementSize);

  }
  delete it;
  delete [] buffer;
}

  // @mfunc Save the <c OMStrongReference> <p singleton> in this
  //        <c OMKLVStoredObject>.
  //   @parm The <c OMStrongReference> to save.
void OMKLVStoredObject::save(const OMStrongReference& singleton)
{
  TRACE("OMKLVStoredObject::save(OMStrongReference)");
  singleton.reference().save();
}

  // @mfunc Save the <c OMStrongReferenceVector> <p vector> in this
  //        <c OMKLVStoredObject>.
  //   @parm The <c OMStrongReferenceVector> to save.
void OMKLVStoredObject::save(const OMStrongReferenceVector& vector)
{
  TRACE("OMKLVStoredObject::save(OMStrongReferenceVector)");

  OMContainerIterator<OMStrongReferenceVectorElement>& iterator =
                                                            *vector.iterator();
  while (++iterator) {

    OMStrongReferenceVectorElement& element = iterator.value();

    // save the object
    //
    element.save();

  }
  delete &iterator;
}

  // @mfunc Save the <c OMStrongReferenceSet> <p set> in this
  //        <c OMKLVStoredObject>.
  //   @parm The <c OMStrongReference> to save.
void OMKLVStoredObject::save(const OMStrongReferenceSet& set)
{
  TRACE("OMKLVStoredObject::save(OMStrongReferenceSet)");

#ifdef HACK_SKIP_PRIMARY_MOB_DEF
  bool skipPrimaryMob = !isPrimaryMobPresent(set.container()->file());
#endif

  OMContainerIterator<OMStrongReferenceSetElement>& iterator = *set.iterator();
  while (++iterator) {
    OMStrongReferenceSetElement& element = iterator.value();

#ifdef HACK_SKIP_PRIMARY_MOB_DEF
    if (skipPrimaryMob && elementHasPrimaryMobDefinition(set, element)) {
      continue;
    }
#endif

    // Save elements that are sticky or that are referenced.
    if (element.isSticky() || element.referenceCount() > 0) {

      // object
      element.save();
    }
  }
  delete &iterator;
}

  // @mfunc Save the <c OMWeakReference> <p singleton> in this
  //        <c OMKLVStoredObject>.
  //   @parm The <c OMWeakReference> to save.
void OMKLVStoredObject::save(const OMWeakReference& /* singleton */)
{
  TRACE("OMKLVStoredObject::save(OMWeakReference)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Save the <c OMWeakReferenceVector> <p vector> in this
  //        <c OMKLVStoredObject>.
  //   @parm The <c OMWeakReferenceVector> to save.
void OMKLVStoredObject::save(const OMWeakReferenceVector& /* vector */)
{
  TRACE("OMKLVStoredObject::save(OMWeakReferenceVector)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Save the <c OMWeakReferenceSet> <p set> in this
  //        <c OMKLVStoredObject>.
  //   @parm The <c OMWeakReferenceSet> to save.
void OMKLVStoredObject::save(const OMWeakReferenceSet& /* set */)
{
  TRACE("OMKLVStoredObject::save(OMWeakReferenceSet)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Save the <c OMPropertyTable> <p table> in this
  //        <c OMKLVStoredObject>.
  //   @parm The <c OMPropertyTable> to save.
void OMKLVStoredObject::save(const OMPropertyTable* /* table */)
{
  TRACE("OMKLVStoredObject::save(OMPropertyTable)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Save the <c OMDataStream> <p stream> in this
  //        <c OMKLVStoredObject>.
  //   @parm The <c OMDataStream> to save.
void OMKLVStoredObject::save(const OMDataStream& /* stream */)
{
  TRACE("OMKLVStoredObject::save(OMDataStream)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

OMRootStorable* OMKLVStoredObject::restore(OMFile& file)
{
  TRACE("OMKLVStoredObject::restore(OMFile)");

#if defined(USETAGTABLE)
  initializeMap(file);
#endif

  OMUInt64 headerPosition;
  if (!_storage->findMetadata(headerPosition)) {
    throw OMException("Failed to find valid metadata.");
  }
  _storage->setPosition(headerPosition);

  OMKLVKey k;
  _storage->readKLVKey(k);
  if (OMMXFStorageBase::isPartition(k)) {
    // Read the header partition
    _storage->readHeaderPartition();
    _storage->readKLVKey(k);
  }
  if (OMMXFStorageBase::isFill(k)) {
    _storage->readKLVFill();
    _storage->readKLVKey(k);
  }

#if 1 // DMS1SUPPORT
  // Read the primer, remember its position
  OMUInt64 primerPosition = 0;
  if (k == primerKey) {
    primerPosition = _storage->position();
    readPrimerPack(file.dictionary());
    _storage->readKLVKey(k);
  }
#else
  // Read the primer
  if (k == primerKey) {
    readPrimerPack(file.dictionary());
    _storage->readKLVKey(k);
  }
#endif

  file.setLoadMode(OMFile::lazyLoad);

  if (OMMXFStorageBase::isFill(k)) {
    _storage->readKLVFill();
    _storage->readKLVKey(k);
  }

  // For restoring meta objects
  OMDictionary* metaDictionary = file.dictionary();
  // For restoring objects
  const OMClassFactory* dictionary = file.classFactory();

  // restore the root
  //
  OMClassId cid;
  convert(cid, k);
  OMRootStorable* root = new OMRootStorable();
  ASSERT("Valid heap pointer", root != 0);
  root->attach(&file);
  root->setStore(file.rootStore());
  root->setClassFactory(metaDictionary);
  // HACK4MEIP2
  if (cid == OMRootStorable::_rootClassId ||
      cid == SMPTERootClassId) {
    flatRestore(*root->propertySet());
    _storage->removeObject(*root);
    // restore the meta object directory
    //
    if (_storage->objectDirectoryOffset() != 0) {
      _storage->restoreObjectDirectory(headerPosition);
    }
    _storage->readKLVKey(k);
    convert(cid, k);
  } else {
    // tjb - what ?
  }

  // restore the meta dictionary
  //

  while (metaDictionary->isMeta(cid)) {
    OMStorable* object = metaDictionary->create(cid);
    ASSERT("Registered class id", object != 0);
    ASSERT("Valid class factory", metaDictionary == object->classFactory());
#if !defined(OM_NO_VALIDATE_DEFINITIONS)
    ASSERT("Valid class definition", object->definition() != 0);
#endif
    flatRestore(*object->propertySet());

    // Attach the object.
    // tjb !!! object->attach(containingObject, name);
    // tjb !!! object->setStore(this);
    object->onRestore(file.clientOnSaveContext());

    _storage->readKLVKey(k);
    convert(cid, k);
  }
  OMProperty* mdp = root->propertySet()->get(PID_Root_MetaDictionary);
  OMStrongReference* mdsr = dynamic_cast<OMStrongReference*>(mdp);
  ASSERT("Valid type", mdsr != 0);
  OMStrongObjectReference& mdr = mdsr->reference();
  OMStorable* mdo = mdr.getValue();
  // HACK4MEIP2
  if (mdo != 0) {
    ASSERT("Valid object", mdo != 0);
    deepRestore(*mdo->propertySet());
  } else {
    // tjb - what ?
  }

#if 1 // DMS1SUPPORT
  // Register extended definitions with the restored dictionary and
  // re-read the primer to update the extended definitions with
  // information from the primer.
  if (file.accessMode() == OMFile::readOnlyMode) {
    metaDictionary->extend();

    OMUInt64 p = _storage->position();
    _storage->setPosition(primerPosition);
    readPrimerPack(file.dictionary());
    _storage->setPosition(p);
  }
#endif

  // restore the client root
  //
  OMStorable* r = 0;
  root->setClassFactory(dictionary);
  convert(cid, k);
  while (!OMMXFStorageBase::endsMetadata(k)) {
    if (dictionary->isRegistered(cid)) {
      OMStorable* object = dictionary->create(cid);
      ASSERT("Registered class id", object != 0);
      ASSERT("Valid class factory", dictionary == object->classFactory());
#if !defined(OM_NO_VALIDATE_DEFINITIONS)
      ASSERT("Valid class definition", object->definition() != 0);
#endif
      if (r == 0) {
        r = object; // HACK4MEIP2 - First object is root
      }

      flatRestore(*object->propertySet());

	  // Attach the object.
      // tjb !!! object->attach(containingObject, name);
      // tjb !!! object->setStore(this);
      object->onRestore(file.clientOnSaveContext());
    } else {
      //  Dark meta data
      _storage->skipLV();
    }

    bool b = _storage->readOuterKLVKey(k);
    if (!b) {
      throw OMException("Failed to read key while parsing metadata.");
    }
    convert(cid, k);
  }
  ASSERT("Root object found", r != 0);
  OMProperty* hp = root->propertySet()->get(PID_Root_Header);
  OMStrongReference* hsr = dynamic_cast<OMStrongReference*>(hp);
  ASSERT("Valid type", hsr != 0);
  OMStrongObjectReference& hr = hsr->reference();
  OMStorable* ho = hr.getValue();
  // HACK4MEIP2
  if (ho != 0) {
    ASSERT("Valid object", ho != 0);
    deepRestore(*ho->propertySet());
  } else {
    hr.setValue(r);
    deepRestore(*r->propertySet());
    _storage->removeObject(*r);
  }

  _storage->skipLV(); // This V is fill

  _storage->restoreStreams();

  _storage->clearObjectDirectory();

  return root;
}

OMStorable*
OMKLVStoredObject::restoreObject(const OMStrongObjectReference& reference)
{
  TRACE("OMKLVStoredObject::restoreObject");
  const OMUniqueObjectIdentification id = reference.identification();
  OMStorable* result = _storage->object(id);
  if (result != 0) {
    _storage->resolve(id);
      // Attach the object.
    OMProperty* property = reference.property();
    result->attach(property, reference);
    result->setStore(this);
  }
  return result;
}

  // @mfunc Restore the <c OMStoredObjectIdentification>
  //        of this <c OMKLVStoredObject> into <p id>.
  //   @parm The newly restored <t OMStoredObjectIdentification>.
void OMKLVStoredObject::restore(OMStoredObjectIdentification& /* id */)
{
  TRACE("OMKLVStoredObject::restore(OMStoredObjectIdentification)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Restore the <c OMPropertySet> <p properties> into
  //        this <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMPropertySet>.
void OMKLVStoredObject::restore(OMPropertySet& /* properties */)
{
  TRACE("OMKLVStoredObject::restore(OMPropertySet)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Restore the <c OMSimpleProperty> <p property> into this
  //        <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMSimpleProperty>
  //   @parm The external size.
void OMKLVStoredObject::restore(OMSimpleProperty& property,
                                OMPropertySize externalSize)
{
  TRACE("OMKLVStoredObject::restore(OMSimpleProperty)");

  const OMType* propertyType = property.type();
  ASSERT("Valid property type", propertyType != 0);

  // Allocate buffer for property value
  OMByte* buffer = new OMByte[externalSize];
  ASSERT("Valid heap pointer", buffer != 0);

  if (externalSize)
    _storage->read(buffer, externalSize);

  if ((propertyType->identification() == Type_UniqueObjectIdentification) ||
      (propertyType->identification() == Type_TransferCharacteristic) ||
      (isExtendibleEnumStoredAsSMPTEUL(buffer, externalSize, propertyType))) {
    // UniqueObjectIdentification properties are stored
    // as SMPTE universal labels in KLV-encoded files.
    const OMKLVKey* key = (OMKLVKey*)buffer;
    OMUniqueObjectIdentification* id =
                                (OMUniqueObjectIdentification*)property.bits();

    const size_t internalSize = sizeof(OMUniqueObjectIdentification);
    property.setSize(internalSize);
    ASSERT("Property value buffer large enough",
                                              property.size() >= internalSize);
    convert(*id, *key);

  } else if (externalSize == 0 && dynamic_cast<OMWideStringProperty*>(&property)) {
    // Allow zero-size string properties through.
  } else {
    // Reorder property value
    if (_reorderBytes) {
      propertyType->reorder(buffer, externalSize);
    }

    // Internalize property value
    OMUInt32 sz = propertyType->internalSize(buffer, externalSize);
    ASSERT("Property not too big", sz <= OMPROPERTYSIZE_MAX);
    OMPropertySize requiredBytesSize = static_cast<OMPropertySize>(sz);
    property.setSize(requiredBytesSize);
    ASSERT("Property value buffer large enough",
                                         property.size() >= requiredBytesSize);
    OMByte* bits = property.bits();
    propertyType->internalize(buffer,
                              externalSize,
                              bits,
                              requiredBytesSize,
                              hostByteOrder());
  }

  delete [] buffer;
}

  // @mfunc Restore the <c OMDataVector> <p property> into this
  //        <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMDataVector>
  //   @parm The external size.
void OMKLVStoredObject::restore(OMDataVector& property,
                                OMPropertySize externalSize)
{
  TRACE("OMKLVStoredObject::restore(OMDataVector)");

  const OMType* propertyType = property.type();
  ASSERT("Valid property type", propertyType != 0);
  const OMArrayType* at = dynamic_cast<const OMArrayType*>(propertyType);
  ASSERT("Correct type", at != 0);
  OMType* elementType = at->elementType();
  ASSERT("Fixed size elements", elementType->isFixedSize());
  OMUInt32 externalElementSize = elementType->externalSize();
  OMUInt32 elementSize = elementType->internalSize();

  // Allocate buffer for one element
  OMByte* buffer = new OMByte[externalElementSize];
  ASSERT("Valid heap pointer", buffer != 0);
  OMByte* value = new OMByte[elementSize];
  ASSERT("Valid heap pointer", value != 0);

  property.clear();
  OMUInt32 elementCount = externalSize / externalElementSize;

  for (OMUInt32 i = 0; i < elementCount; i++) {

    // Read one element
    _storage->read(buffer, externalElementSize);

    if ((elementType->identification() == Type_UniqueObjectIdentification) ||
        (elementType->identification() == Type_TransferCharacteristic) ||
        (isExtendibleEnumStoredAsSMPTEUL(buffer, externalElementSize, propertyType))) {
      // UniqueObjectIdentification properties are stored
      // as SMPTE universal labels in KLV-encoded files.
      const OMKLVKey* key = (OMKLVKey*)buffer;
      OMUniqueObjectIdentification* id = (OMUniqueObjectIdentification*)value;
      convert(*id, *key);

    } else {
      // Reorder element
      if (_reorderBytes) {
        elementType->reorder(buffer, externalElementSize);
      }

      // Internalize element
      elementType->internalize(buffer,
                               externalElementSize,
                               value,
                               elementSize,
                               hostByteOrder());
    }

    property.appendValue(value);
  }
  delete [] buffer;
  delete [] value;
}

void OMKLVStoredObject::restore(OMDataSet& property,
                                OMPropertySize externalSize)
{
  TRACE("OMKLVStoredObject::restore(OMDataSet)");

  const OMType* propertyType = property.type();
  ASSERT("Valid property type", propertyType != 0);
  const OMSetType* st = dynamic_cast<const OMSetType*>(propertyType);
  ASSERT("Correct type", st != 0);
  OMType* elementType = st->elementType();
  ASSERT("Fixed size elements", elementType->isFixedSize());
  OMUInt32 externalElementSize = elementType->externalSize();
  OMUInt32 elementSize = elementType->internalSize();

  // Allocate buffer for one element
  OMByte* buffer = new OMByte[externalElementSize];
  ASSERT("Valid heap pointer", buffer != 0);
  OMByte* value = new OMByte[elementSize];
  ASSERT("Valid heap pointer", value != 0);

  property.clear();
  OMUInt32 elementCount = externalSize / externalElementSize;

  for (OMUInt32 i = 0; i < elementCount; i++) {

    // Read one element
    _storage->read(buffer, externalElementSize);

    if ((elementType->identification() == Type_UniqueObjectIdentification) ||
        (elementType->identification() == Type_TransferCharacteristic) ||
        (isExtendibleEnumStoredAsSMPTEUL(buffer, externalElementSize, propertyType))) {
      // UniqueObjectIdentification properties are stored
      // as SMPTE universal labels in KLV-encoded files.
      const OMKLVKey* key = (OMKLVKey*)buffer;
      OMUniqueObjectIdentification* id = (OMUniqueObjectIdentification*)value;
      convert(*id, *key);

    } else {
      // Reorder element
      if (_reorderBytes) {
        elementType->reorder(buffer, externalElementSize);
      }

      // Internalize element
      elementType->internalize(buffer,
                               externalElementSize,
                               value,
                               elementSize,
                               hostByteOrder());
    }
    property.insert(value);
  }
  delete [] buffer;
  delete [] value;
}

  // @mfunc Restore the <c OMStrongReference> <p singleton> into this
  //        <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMStrongReference>.
  //   @parm The external size.
void OMKLVStoredObject::restore(OMStrongReference& singleton ,
                                OMPropertySize ANAME(externalSize))
{
  TRACE("OMKLVStoredObject::restore(OMStrongReference)");

  ASSERT("Valid size", externalSize == sizeof(OMUniqueObjectIdentification));
  OMUniqueObjectIdentification id;
  _storage->read(id, _reorderBytes);

  OMStrongObjectReference newReference(&singleton, id, false);
  singleton.reference() = newReference;
}

  // @mfunc Restore the <c OMStrongReferenceVector> <p vector> into this
  //        <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMStrongReferenceVector>.
  //   @parm The external size.
void OMKLVStoredObject::restore(OMStrongReferenceVector& /* vector */,
                                OMPropertySize /* externalSize */)
{
  TRACE("OMKLVStoredObject::restore(OMStrongReferenceVector)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Restore the <c OMStrongReferenceSet> <p set> into this
  //        <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMStrongReferenceSet>.
  //   @parm The external size.
void OMKLVStoredObject::restore(OMStrongReferenceSet& /* set */,
                                OMPropertySize /* externalSize */)
{
  TRACE("OMKLVStoredObject::restore(OMStrongReferenceSet)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Restore the <c OMWeakReference> <p singleton> into this
  //        <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMWeakReference>.
  //   @parm The external size.
void OMKLVStoredObject::restore(OMWeakReference& singleton,
                                OMPropertySize ANAME(externalSize))
{
  TRACE("OMKLVStoredObject::restore(OMWeakReference)");

  ASSERT("Valid size", externalSize == sizeof(OMUniqueObjectIdentification));
  OMUniqueObjectIdentification id;
  _storage->read(id, _reorderBytes);

  // Remember the InstanceUID of the object referenced by
  // this OMWeakReference.
  _storage->associate(&singleton, id);
}

  // @mfunc Restore the <c OMWeakReferenceVector> <p vector> into this
  //        <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMWeakReferenceVector>.
  //   @parm The external size.
void OMKLVStoredObject::restore(OMWeakReferenceVector& /* vector */,
                                OMPropertySize /* externalSize */)
{
  TRACE("OMKLVStoredObject::restore(OMWeakReferenceVector)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Restore the <c OMWeakReferenceSet> <p set> into this
  //        <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMWeakReferenceSet>.
  //   @parm The external size.
void OMKLVStoredObject::restore(OMWeakReferenceSet& /* set */,
                                OMPropertySize /* externalSize */)
{
  TRACE("OMKLVStoredObject::restore(OMWeakReferenceSet)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Restore the <c OMPropertyTable> in this <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMPropertyTable>.
void OMKLVStoredObject::restore(OMPropertyTable*& /* table */)
{
  TRACE("OMKLVStoredObject::restore(OMPropertyTable)");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
}

  // @mfunc Restore the <c OMDataStream> <p stream> into this
  //        <c OMKLVStoredObject>.
  //   @parm The newly restored <c OMDataStream>.
  //   @parm The external size.
void OMKLVStoredObject::restore(OMDataStream& /* stream */,
                                OMPropertySize /* externalSize */)
{
  TRACE("OMKLVStoredObject::restore(OMDataStream)");

  ASSERT("NYI", false);
}

void OMKLVStoredObject::reorderString(OMCharacter* string,
                                      size_t characterCount)
{
  TRACE("OMKLVStoredObject::reorderString");

  for (size_t i = 0; i < characterCount; i++) {
    OMByte* src = reinterpret_cast<OMByte*>(&string[i]);
    OMType::reorderInteger(src, sizeof(OMUInt16));
  }
}

void OMKLVStoredObject::externalizeString(const wchar_t* internalString,
                                          OMCharacter* externalString,
                                          size_t characterCount)
{
  TRACE("OMKLVStoredObject::externalizeString");

  for (size_t i = 0; i < characterCount; i++) {
    externalString[i] = internalString[i];
  }
}

void OMKLVStoredObject::internalizeString(const OMCharacter* externalString,
                                          wchar_t* internalString,
                                          size_t characterCount)
{
  TRACE("OMKLVStoredObject::internalizeString");

  for (size_t i = 0; i < characterCount; i++) {
    internalString[i] = externalString[i];
  }
}

void OMKLVStoredObject::write(const wchar_t* string)
{
  TRACE("OMKLVStoredObject::write");

  PRECONDITION("Valid string", string != 0); // L"" is OK

  // include terminating null
  size_t count = lengthOfWideString(string) + 1;
  ASSERT("String not too long", count <= OMUINT16_MAX);
  OMUInt16 characterCount = static_cast<OMUInt16>(count);
  OMPropertySize externalBytesSize = characterCount * 2;
  _storage->write(characterCount, _reorderBytes);

  OMCharacter* buffer = new OMCharacter[characterCount];
  ASSERT("Valid heap pointer", buffer != 0);

  externalizeString(string, buffer, characterCount);

  if (_reorderBytes) {
    reorderString(buffer, characterCount);
  }
  _storage->write(reinterpret_cast<OMByte*>(buffer), externalBytesSize);
  delete [] buffer;
}

void OMKLVStoredObject::write(bool b)
{
  TRACE("OMKLVStoredObject::write");

  OMByte byte;
  if (b) {
    byte = 0xff; // true
  } else {
    byte = 0x00; // false
  }
  _storage->write(byte);
}

void OMKLVStoredObject::read(const wchar_t* string, OMUInt16 characterCount)
{
  TRACE("OMKLVStoredObject::read");

  PRECONDITION("Valid buffer", string != 0);
  PRECONDITION("Valid count", characterCount != 0);

  OMCharacter* buffer = new OMCharacter[characterCount];
  ASSERT("Valid heap pointer", buffer != 0);
  OMPropertySize externalBytesSize = characterCount * 2;
  _storage->read(reinterpret_cast<OMByte*>(buffer), externalBytesSize);

  if (_reorderBytes) {
    reorderString(buffer, characterCount);
  }

  internalizeString(buffer, const_cast<wchar_t*>(string), characterCount);
}

void OMKLVStoredObject::read(bool& b)
{
  TRACE("OMKLVStoredObject::read");

  OMByte byte;
  _storage->read(byte);
  ASSERT("Valid bool", (byte == 0x00) || (byte == 0xff)); // tjb - error

  if (byte == 0x00) {
    b = false;
  } else {
    b = true;
  }
}

void OMKLVStoredObject::writeProperty(OMPropertyId pid, const OMUInt32& value)
{
  TRACE("OMKLVStoredObject::writeProperty");

  // pid
  _storage->write(pid, _reorderBytes);
  // size
  OMPropertySize size = sizeof(value);
  _storage->write(size, _reorderBytes);
  // value
  _storage->write(value, _reorderBytes);
}

void OMKLVStoredObject::readProperty(const OMPropertyId& ANAME(pid),
                                     OMUInt32& value)
{
  TRACE("OMKLVStoredObject::readProperty");

  // pid
  OMPropertyId p;
  _storage->read(p, _reorderBytes);
  ASSERT("Expected pid", p == pid);
  // size
  OMPropertySize size;
  _storage->read(size, _reorderBytes);
  ASSERT("Expected size", size == sizeof(value));
  // value
  _storage->read(value, _reorderBytes);
}

  // @mfunc Open the <c OMStoredStream> representing the property
  //        <p stream> contained within this <c OMKLVStoredObject>.
  //   @parm The <c OMDataStream> to be opened.
  //   @rdesc The newly created <c OMStoredStream>.
OMStoredStream* OMKLVStoredObject::openStoredStream(
                                            const OMDataStream& /* property */)
{
  TRACE("OMKLVStoredObject::openStoredStream");
  ASSERT("Unimplemented code not reached", false); // tjb TBS
  return 0;
}

  // @mfunc Create an <c OMStoredStream> representing the property
  //        <p stream> contained within this <c OMKLVStoredObject>.
  //   @parm The <c OMDataStream> to be created.
  //   @rdesc The newly created <c OMStoredStream>.
OMStoredStream* OMKLVStoredObject::createStoredStream(
                                                  const OMDataStream& property)
{
  TRACE("OMKLVStoredObject::createStoredStream");

  OMUInt32 sid = _storage->addStream(const_cast<OMDataStream*>(&property));
  OMKLVStoredStream* result = new OMKLVStoredStream(_storage, sid);
  ASSERT("Valid heap pointer", result != 0);
  return result;
}

void OMKLVStoredObject::flatSave(const OMPropertySet& properties) const
{
  TRACE("OMKLVStoredObject::flatSave");

  referenceSave(properties.container(), PID_InterchangeObject_InstanceUID);

  if (properties.container()->classId() == Class_Root) {
    OMKLVStoredObject* This = const_cast<OMKLVStoredObject*>(this);

    const OMFile* file = properties.container()->file();
    const bool forceST377 = isEnforcingST377(file);

#if defined(OM_SAVEOBJECTDIRECTORY)
    if (!forceST377) {
      OMUniqueObjectIdentification id = _storage->generation();
      This->saveObjectDirectoryReference(id);
    }
#endif

    OMPropertyId pid = forceST377 ? PID_Root_FormatVersion :
                                    PID_Legacy_Root_FormatVersion;
    OMUInt32 version = formatVersion;
    This->writeProperty(pid, version);
  }

  OMPropertySetIterator iterator(properties, OMBefore);
  while (++iterator) {
    OMProperty* p = iterator.property();
    ASSERT("Valid property", p != 0);
    ASSERT("Property has a definition", p->definition() != 0);
    if (!p->isOptional() || p->isPresent()) {
      OMPropertyId id = p->propertyId();
      if (id == 0x3b04) { // the AAF dictionary which we shouldn't know about
        OMFile* file = properties.container()->file();
        OMDictionary* dictionary = file->dictionary();
        if (!dictionary->isRequired(file->encoding())) {
          continue;
        }
      }
      OMDictionary::mapToKLV(id);
      switch (p->storedForm()) {
      case SF_DATA: {
        _storage->write(id, _reorderBytes);
        p->save();
        break;
      }
      case SF_DATA_VECTOR: {
        _storage->write(id, _reorderBytes);
        p->save();
        break;
      }
      case SF_DATA_SET: {
        _storage->write(id, _reorderBytes);
        p->save();
        break;
      }
      case SF_STRONG_OBJECT_REFERENCE: {
        OMStrongReference* sr = dynamic_cast<OMStrongReference*>(p);
        ASSERT("Valid type", sr != 0);
        OMStrongObjectReference& r = sr->reference();
        OMStorable* object = r.getValue();
        ASSERT("Valid object", object != 0);
        referenceSave(object, id);
        break;
      }
      case SF_STRONG_OBJECT_REFERENCE_VECTOR: {
        _storage->write(id, _reorderBytes);
        OMStrongReferenceVector* v = dynamic_cast<OMStrongReferenceVector*>(p);
        ASSERT("Valid type", v != 0);
        OMUInt32 elementCount = v->count();
        OMUInt32 elementSize = sizeof(OMUniqueObjectIdentification);
        ASSERT("Property not too big",
           (sizeof(OMUInt32) + sizeof(OMUInt32) + (elementCount * elementSize))
           <= OMPROPERTYSIZE_MAX);
        OMPropertySize size = static_cast<OMPropertySize>(
                                sizeof(OMUInt32) + sizeof(OMUInt32)
                                + (elementCount * elementSize));
        _storage->write(size, _reorderBytes);
        _storage->write(elementCount, _reorderBytes);
        _storage->write(elementSize, _reorderBytes);
        OMContainerIterator<OMStrongReferenceVectorElement>& iterator =
                                                                *v->iterator();
        while (++iterator) {
          OMStrongReferenceVectorElement& element = iterator.value();
          OMStrongObjectReference& r = element.reference();
          OMStorable* object = r.getValue();
          ASSERT("Valid object", object != 0);
          OMUniqueObjectIdentification id = _storage->instanceId(object);
          _storage->write(id, _reorderBytes);
        }
        delete &iterator;
        break;
      }
      case SF_STRONG_OBJECT_REFERENCE_SET: {
        _storage->write(id, _reorderBytes);
        OMStrongReferenceSet* s = dynamic_cast<OMStrongReferenceSet*>(p);
        ASSERT("Valid type", s != 0);
        OMUInt32 elementCount = s->count();
#ifdef HACK_SKIP_PRIMARY_MOB_DEF
        if (elementCount > 0 && setHasPrimaryMobDefinition(*s)) {
          elementCount = elementCount - 1;
        }
#endif
        OMUInt32 elementSize = sizeof(OMUniqueObjectIdentification);
        ASSERT("Property not too big",
           (sizeof(OMUInt32) + sizeof(OMUInt32) + (elementCount * elementSize))
           <= OMPROPERTYSIZE_MAX);
        OMPropertySize size = static_cast<OMPropertySize>(
                                sizeof(OMUInt32) + sizeof(OMUInt32)
                                + (elementCount * elementSize));
        _storage->write(size, _reorderBytes);
        _storage->write(elementCount, _reorderBytes);
        _storage->write(elementSize, _reorderBytes);
        OMContainerIterator<OMStrongReferenceSetElement>& iterator =
                                                                *s->iterator();
        while (++iterator) {
          OMStrongReferenceSetElement& element = iterator.value();
#ifdef HACK_SKIP_PRIMARY_MOB_DEF
          if (elementHasPrimaryMobDefinition(*s, element)) {
            continue;
          }
#endif
          OMStrongObjectReference& r = element.reference();
          OMStorable* object = r.getValue();
          ASSERT("Valid object", object != 0);
          OMUniqueObjectIdentification id = _storage->instanceId(object);
          _storage->write(id, _reorderBytes);
        }
        delete &iterator;
        break;
      }
      case SF_WEAK_OBJECT_REFERENCE: {
        OMWeakReference* wr = dynamic_cast<OMWeakReference*>(p);
        ASSERT("Valid type", wr != 0);
        OMStorable* object = dynamic_cast<OMStorable*>(wr->getObject());
        ASSERT("Valid object", object != 0);
#if 1 // HACK
        // In AAF the properties with the following ids are historically and
        // currently weak references, in MXF they are simply labels so
        // persist them as such. In AAF they'll eventually become a new kind
        // of reference. tjb 11/14/05
        //
        if ((id == 0x0201) || (id == 0x3004) || (id == 0x3005) || (id == 0x0b01) || (id == 0x4e01)){
          ASSERT("Valid identification size",
                        wr->keySize() == sizeof(OMUniqueObjectIdentification));
          const OMUniqueObjectIdentification k =
            *reinterpret_cast<const OMUniqueObjectIdentification*>(
                                                     wr->identificationBits());
          _storage->write(id, _reorderBytes);
          OMPropertySize s = sizeof(OMKLVKey);
          _storage->write(s, _reorderBytes);
          OMKLVKey k2; // 8,166m
          convert(k2, k);
          _storage->writeKLVKey(k2);
        } else {
          referenceSave(object, id);
        }
#else
        referenceSave(object, id);
#endif
        break;
      }
      case SF_WEAK_OBJECT_REFERENCE_VECTOR: {
        _storage->write(id, _reorderBytes);
        OMWeakReferenceVector* v = dynamic_cast<OMWeakReferenceVector*>(p);
        ASSERT("Valid type", v != 0);
        OMUInt32 elementCount = v->count();
        OMUInt32 elementSize = sizeof(OMUniqueObjectIdentification);
        ASSERT("Property not too big",
           (sizeof(OMUInt32) + sizeof(OMUInt32) + (elementCount * elementSize))
           <= OMPROPERTYSIZE_MAX);
        OMPropertySize size = static_cast<OMPropertySize>(
                                sizeof(OMUInt32) + sizeof(OMUInt32)
                                + (elementCount * elementSize));
        _storage->write(size, _reorderBytes);
        _storage->write(elementCount, _reorderBytes);
        _storage->write(elementSize, _reorderBytes);
        OMContainerIterator<OMWeakReferenceVectorElement>& iterator =
                                                                *v->iterator();
        while (++iterator) {
          OMWeakReferenceVectorElement& element = iterator.value();
          OMWeakObjectReference& r = element.reference();
          OMStorable* object = r.getValue();
          ASSERT("Valid object", object != 0);
          OMUniqueObjectIdentification id = _storage->instanceId(object);
          _storage->write(id, _reorderBytes);
        }
        delete &iterator;
        break;
      }
      case SF_WEAK_OBJECT_REFERENCE_SET: {
        _storage->write(id, _reorderBytes);
        OMWeakReferenceSet* s = dynamic_cast<OMWeakReferenceSet*>(p);
        ASSERT("Valid type", s != 0);
        OMUInt32 elementCount = s->count();
        OMUInt32 elementSize = sizeof(OMUniqueObjectIdentification);
        ASSERT("Property not too big",
           (sizeof(OMUInt32) + sizeof(OMUInt32) + (elementCount * elementSize))
           <= OMPROPERTYSIZE_MAX);
        OMPropertySize size = static_cast<OMPropertySize>(
                                sizeof(OMUInt32) + sizeof(OMUInt32)
                                + (elementCount * elementSize));
        _storage->write(size, _reorderBytes);
        _storage->write(elementCount, _reorderBytes);
        _storage->write(elementSize, _reorderBytes);
        OMContainerIterator<OMWeakReferenceSetElement>& iterator =
                                                                *s->iterator();
        while (++iterator) {
          OMWeakReferenceSetElement& element = iterator.value();
          OMWeakObjectReference& r = element.reference();
          OMStorable* object = r.getValue();
          ASSERT("Valid object", object != 0);
          OMUniqueObjectIdentification id = _storage->instanceId(object);
          _storage->write(id, _reorderBytes);
        }
        delete &iterator;
        break;
      }
      case SF_DATA_STREAM: {
        OMDataStreamProperty* stream = dynamic_cast<OMDataStreamProperty*>(p);
        ASSERT("Valid type", stream != 0);
        _storage->write(id, _reorderBytes);
        OMPropertySize s = sizeof(OMUInt32);
        _storage->write(s, _reorderBytes);
        OMStoredStream* ss = stream->stream();
        ASSERT("Valid stream", ss != 0);
        OMKLVStoredStream* kss = dynamic_cast<OMKLVStoredStream*>(ss);
        ASSERT("Valid type", kss != 0);
        OMUInt32 sid = kss->streamIdentification();
        _storage->write(sid, _reorderBytes);
        // There's no place in the file to put the stored byte order
        // until we have metadata streams.
        ASSERT("Supported stream byte order",
                                  (stream->storedByteOrder() == unspecified) ||
                                  (stream->storedByteOrder() == bigEndian));
        // !!! tjb bug fix repeated code from OMDataStreamProperty::save()
        if (stream->hasStreamAccess()) {
          _storage->addDeferredStream(stream);
        }
        // !!! tjb
        break;
      }
      default:
        break;
      }
    }
  }
}

void OMKLVStoredObject::deepSave(const OMPropertySet& properties) const
{
  TRACE("OMKLVStoredObject::deepSave");

  OMPropertySetIterator iterator(properties, OMBefore);
  while (++iterator) {
    OMProperty* p = iterator.property();
    ASSERT("Valid property", p != 0);
    ASSERT("Property has a definition", p->definition() != 0);
    if (!p->isOptional() || p->isPresent()) {
      OMPropertyId id = p->propertyId();
      if (id == 0x3b04) { // the AAF dictionary which we shouldn't know about
        OMFile* file = properties.container()->file();
        OMDictionary* dictionary = file->dictionary();
        if (!dictionary->isRequired(file->encoding())) {
          continue;
        }
      }
      switch (p->storedForm()) {
      case SF_STRONG_OBJECT_REFERENCE:
      case SF_STRONG_OBJECT_REFERENCE_VECTOR:
      case SF_STRONG_OBJECT_REFERENCE_SET: {
        p->save();
        break;
      }
      default:
        break;
      }
    }
  }
}

void OMKLVStoredObject::referenceSave(OMStorable* object,
                                      OMPropertyId pid) const
{
  TRACE("OMKLVStoredObject::referenceSave");
  PRECONDITION("Valid object", object != 0);

  OMUniqueObjectIdentification oid = _storage->instanceId(object);
  _storage->write(pid, _reorderBytes);
  OMPropertySize s = sizeof(OMUniqueObjectIdentification);
  _storage->write(s, _reorderBytes);
  _storage->write(oid, _reorderBytes);
}

void OMKLVStoredObject::flatRestore(const OMPropertySet& properties)
{
  TRACE("OMKLVStoredObject::flatRestore");

  OMUInt64 setLength = _storage->readKLVLength();

  const OMUInt16 overhead = sizeof(OMPropertyId) + sizeof(OMPropertySize);

  while (setLength > 0) {
    OMPropertyId pid;
    _storage->read(pid, _reorderBytes);
    OMDictionary::mapFromKLV(pid);
    OMPropertySize length;
    _storage->read(length, _reorderBytes);

    if (pid == PID_InterchangeObject_InstanceUID) {
      // The UID of this object
      referenceRestore(properties.container(), pid);
    } else if ((pid == PID_Root_ObjectDirectory ||
                pid == PID_Legacy_Root_ObjectDirectory) &&
               (properties.container()->classId() == Class_Root)) {
      OMUniqueObjectIdentification id; // Not yet used
      _storage->read(id, _reorderBytes);
      OMUInt64 offset;
      _storage->read(offset, _reorderBytes);
      _storage->setObjectDirectoryOffset(offset);
    } else if ((pid == PID_Root_FormatVersion ||
                pid == PID_Legacy_Root_FormatVersion) &&
               (properties.container()->classId() == Class_Root)) {
      OMUInt32 version; // Not yet used
      _storage->read(version, _reorderBytes);
#if defined(OM_STRICTMXFPARSER)
    } else if ((!properties.isAllowed(pid)) && (pid >= 0x8000)) { // HACK4MEIP2
      // Dark extension
      _storage->skipV(length);  // discard value !! tjb
#else
    } else if ((!properties.isAllowed(pid))) {
      // Discard properties that do not belong to the object containing this
      // property set. These include both dark extension properties (pid >=
      // 0x8000) and standard properties. (This is to accept invalid MXF files
      // that put properties of one class in instances of another class.)
      _storage->skipV(length);
#endif
#if 1 // DMS1SUPPORT || DICTIONARYLESSFILES
#else
    } else if (pid == 0x6101) {
      // HACK4MEIP2
      // Temporary hack - ignore this property - we don't yet have
      // compiled-in knowlege of its 'type' - the DMS-1 object model
      _storage->skipV(length);  // DMSegment::DMFrameWork
#endif
    } else {
    // Ensure p is not NULL
    if (!properties.isPresent(pid)) {
      throw OMException("Property does not belong to property set.");
    }
    OMProperty* p = properties.get(pid);
    ASSERT("Valid property", p != 0);

    switch (p->storedForm()) {
    case SF_DATA: {
      // p->restore(length);
      OMSimpleProperty* sp = fast_dynamic_cast<OMSimpleProperty*>(p);
      ASSERT("Correct type", sp != 0);
      restore(*sp, length);
      p->setPresent();
      break;
    }
    case SF_DATA_VECTOR: {
      // p->restore(length);
      OMDataVector* dv = fast_dynamic_cast<OMDataVector*>(p);
      ASSERT("Correct type", dv != 0);
      OMUInt32 entryCount;
      _storage->read(entryCount, _reorderBytes);
      OMUInt32 entrySize;
      _storage->read(entrySize, _reorderBytes);
      OMPropertySize externalSize = length -
                                    (sizeof(OMUInt32) + sizeof(OMUInt32));
      ASSERT("Consistent size", externalSize == entryCount * entrySize);
      restore(*dv, externalSize);
      p->setPresent();
      break;
    }
    case SF_DATA_SET: {
      // p->restore(length);
      OMDataSet* ds = fast_dynamic_cast<OMDataSet*>(p);
      ASSERT("Correct type", ds != 0);
      OMUInt32 entryCount;
      _storage->read(entryCount, _reorderBytes);
      OMUInt32 entrySize;
      _storage->read(entrySize, _reorderBytes);
      OMPropertySize externalSize = length -
                                    (sizeof(OMUInt32) + sizeof(OMUInt32));
      ASSERT("Consistent size", externalSize == entryCount * entrySize);
      restore(*ds, externalSize);
      p->setPresent();
      break;
    }
    case SF_STRONG_OBJECT_REFERENCE: {
      // p->restore(length);
      OMStrongReference* sr = fast_dynamic_cast<OMStrongReference*>(p);
      ASSERT("Valid type", sr != 0);
      restore(*sr, length);
      p->setPresent();
      break;
    }
    case SF_STRONG_OBJECT_REFERENCE_VECTOR: {
      OMUInt32 elementCount;
      OMUInt32 elementSize;
      _storage->read(elementCount, _reorderBytes);
      _storage->read(elementSize, _reorderBytes);
      OMStrongReferenceVector* v = fast_dynamic_cast<OMStrongReferenceVector*>(p);
      if (elementCount > 0) {
        v->grow(elementCount);
        for (OMUInt32 i = 0; i < elementCount; i++) {
          OMUniqueObjectIdentification id;
          _storage->read(id, _reorderBytes);

          OMStrongObjectReference newReference(v, id, false);
          OMStrongReferenceVectorElement element(v, id, i);
          element.reference() = newReference;
          v->insert(i, element);
        }
      }
      p->setPresent();
      OMUInt64 actualLength = (elementCount * elementSize) + sizeof(elementCount) + sizeof(elementSize);
      if (actualLength > OMUINT16_MAX) {
        // Local set is borked !
        setLength = setLength + length - actualLength;
      }
      break;
    }
    case SF_STRONG_OBJECT_REFERENCE_SET: {
      OMUInt32 elementCount;
      OMUInt32 elementSize;
      _storage->read(elementCount, _reorderBytes);
      _storage->read(elementSize, _reorderBytes);
      OMStrongReferenceSet* s = fast_dynamic_cast<OMStrongReferenceSet*>(p);
      OMKeySize keySize = s->keySize();
      OMByte* key = new OMByte[keySize];
      ASSERT("Valid heap pointer", key != 0);
      OMUInt32* keyI = (OMUInt32*)key;
      memset(key, 0, keySize);

      for (OMUInt32 i = 0; i < elementCount; i++) {
        *keyI = i + 1; // Temporary unique key 1..N
        OMUniqueObjectIdentification id;
        _storage->read(id, _reorderBytes);

        OMStrongObjectReference newReference(s, id, false);
        OMStrongReferenceSetElement element(s, id, i, key, keySize);
        element.reference() = newReference;
        s->insert(key, element);
      }
      delete [] key;
      p->setPresent();
      OMUInt64 actualLength = (elementCount * elementSize) + sizeof(elementCount) + sizeof(elementSize);
      if (actualLength > OMUINT16_MAX) {
        // Local set is borked !
        setLength = setLength + length - actualLength;
      }
      break;
    }
    case SF_WEAK_OBJECT_REFERENCE: {
      OMWeakReference* wr = fast_dynamic_cast<OMWeakReference*>(p);
      ASSERT("Valid type", wr != 0);
      restore(*wr, length);
      p->setPresent();
      break;
    }
    case SF_WEAK_OBJECT_REFERENCE_VECTOR: {
      OMUInt32 elementCount;
      OMUInt32 elementSize;
      _storage->read(elementCount, _reorderBytes);
      _storage->read(elementSize, _reorderBytes);
      OMWeakReferenceVector* v = fast_dynamic_cast<OMWeakReferenceVector*>(p);
      if (elementCount > 0) {
        v->grow(elementCount);
        for (OMUInt32 i = 0; i < elementCount; i++) {
          OMUniqueObjectIdentification id;
          _storage->read(id, _reorderBytes);

          OMWeakReferenceVectorElement element(
                                          v,
                                          &id,
                                          sizeof(OMUniqueObjectIdentification),
                                          nullOMPropertyTag);
          v->insert(i, element);
        }
      }
      p->setPresent();
      break;
    }
    case SF_WEAK_OBJECT_REFERENCE_SET: {
      OMUInt32 elementCount;
      OMUInt32 elementSize;
      _storage->read(elementCount, _reorderBytes);
      _storage->read(elementSize, _reorderBytes);
      OMWeakReferenceSet* s = fast_dynamic_cast<OMWeakReferenceSet*>(p);
      if (elementCount > 0) {
        for (OMUInt32 i = 0; i < elementCount; i++) {
          OMUniqueObjectIdentification id;
          _storage->read(id, _reorderBytes);

          OMWeakReferenceSetElement element(
                                          s,
                                          &id,
                                          sizeof(OMUniqueObjectIdentification),
                                          nullOMPropertyTag);
          s->insert(&id, element);
        }
      }
      p->setPresent();
      break;
    }
    case SF_DATA_STREAM: {
      OMDataStream* stream = fast_dynamic_cast<OMDataStream*>(p);
      ASSERT("Valid type", stream != 0);
      OMUInt32 sid;
      _storage->read(sid, _reorderBytes);
      // Do not restore optional stream properties that have zero stream ID
      // (SID). Specifically, this is indended to handle the case of zero
      // IndexSID property.
      // In the AAF model, to indicate that there's no index table present
      // in the essence container, the IndexSID property would be omitted
      // from theEssence Container Data object. MXF allows to leave the
      // optional IndexSID in and use a special value (zero) to specify
      // the lack of index. Here an optional stream property with zero SID
      // is skipped as if it wasn't present at all.
      if (sid != 0 || !p->isOptional()) {
        // There's no place in the file from which to get the stored byte order
        // until we have metadata streams.
        stream->setStoredByteOrder(bigEndian);
        p->setPresent();
        _storage->associate(stream, sid);
      }
      break;
    }
    default:
      break;
    }
    }
    setLength = setLength - (overhead + length);
  }
}

void OMKLVStoredObject::deepRestore(const OMPropertySet& properties)
{
  TRACE("OMKLVStoredObject::deepRestore");

  OMPropertySetIterator iterator(properties, OMBefore);
  while (++iterator) {
    OMProperty* p = iterator.property();
    ASSERT("Valid property", p != 0);
#if 0 // HACK4MEIP2
    ASSERT("Property has a definition", p->definition() != 0);
#endif
    if (!p->isOptional() || p->isPresent()) {
      switch (p->storedForm()) {
      case SF_STRONG_OBJECT_REFERENCE: {
        OMStrongReference* sr = fast_dynamic_cast<OMStrongReference*>(p);
        ASSERT("Valid type", sr != 0);
        OMStrongObjectReference& r = sr->reference();
        OMStorable* object = r.getValue();
        // HACK4MEIP2
        if (object != 0) {
          ASSERT("Valid object", object != 0);
          deepRestore(*object->propertySet());
        } else {
          // tjb - what ?
        }
        break;
      }
      case SF_STRONG_OBJECT_REFERENCE_SET: {
        OMStrongReferenceSet* s = fast_dynamic_cast<OMStrongReferenceSet*>(p);
        ASSERT("Valid type", s != 0);
        OMUInt32 count = s->count();
        if (count > 0) {
          OMContainerIterator<OMStrongReferenceSetElement>& iterator =
                                                                *s->iterator();
          OMKeySize keySize = s->keySize();
          OMPropertyId keyPid = s->keyPropertyId();
          if (p->propertyId() == 0x0b03) {
            keyPid = 0x4c01;
          }
          OMByte* key = new OMByte[keySize];
          ASSERT("Valid heap pointer", key != 0);
          OMVector<OMUniqueObjectIdentification> objects;
          OMVector<OMByte*> keys;
          objects.grow(count);
          keys.grow(count);

          while (++iterator) {
            OMStrongReferenceSetElement& element = iterator.value();
            OMStrongObjectReference& r = element.reference();
            OMUniqueObjectIdentification id = r.identification();
            // Remember an unresolved reference
            if (r.pointer() == 0) {
              if (_storage->containsObject(id)) {
                objects.insert(id);
              }

              OMByte* k = new OMByte[keySize];
              memcpy(k, element.identification(), keySize);
              keys.insert(k);
            }
          }

          OMVectorIterator<OMByte*> kiter(keys, OMBefore);
          while (++kiter) {
            OMByte* k = kiter.value();
            s->remove(k);
            delete [] k;
          }

          OMUInt32 localKey = 0;
          OMVectorIterator<OMUniqueObjectIdentification> viter(objects,
                                                               OMBefore);
          while (++viter) {
            OMUniqueObjectIdentification id = viter.value();
            OMStorable* obj = _storage->object(id);
            ASSERT("Valid object", obj != 0);
            OMProperty* kp = obj->propertySet()->get(keyPid);
            ASSERT("Valid property", kp != 0);
            ASSERT("Consistent sizes", keySize == kp->bitsSize());
            kp->getBits(key, keySize);

            if (!s->contains(key)) {
              OMStrongReferenceSetElement element(s,
                                                  id,
                                                  localKey,
                                                  key,
                                                  keySize);
              element.setValue(key, obj);
              s->insert(key, element);
              _storage->resolve(id);
            } // else key already present
            localKey = localKey + 1;
          }
          delete [] key;
          delete &iterator;

          OMContainerIterator<OMStrongReferenceSetElement>& iter =
                                                                *s->iterator();
          while (++iter) {
            OMStrongReferenceSetElement& element = iter.value();
            OMStrongObjectReference& r = element.reference();
            OMStorable* object = r.getValue();
            ASSERT("Valid object", object != 0);
            deepRestore(*object->propertySet());
          }
          delete &iter;

        }
        break;
      }
      case SF_WEAK_OBJECT_REFERENCE: {
        OMWeakReference* wr = fast_dynamic_cast<OMWeakReference*>(p);
        ASSERT("Valid type", wr != 0);

        // Find the InstanceUID of the object referenced by
        // this weak reference property and then find an
        // object with this InstanceUID.
        OMStorable* obj = 0;
        OMUniqueObjectIdentification id;
        if (_storage->findReferencedInstanceId(wr, &id)) {
          obj = _storage->object(id);
        }
#if defined(USETAGTABLE)
        if (obj != 0) {
#endif
        ASSERT("Valid object", obj != 0);
        // get key property from object
        OMPropertyId keyPid = wr->keyPropertyId();
        // build new reference from key and object
        OMProperty* kp = obj->propertySet()->get(keyPid);
        ASSERT("Valid property", kp != 0);

        const OMKeySize keySize = wr->keySize();
        ASSERT("Consistent sizes", kp->bitsSize() == keySize);
        OMByte* keyBits = new OMByte[keySize];
        kp->getBits(keyBits, keySize);
#if defined(USETAGTABLE)
        /*
        // Setting the target tag on the weak reference property
        // marks the reference as resolvable (see IsResolvable())
        // even before the file's OMRootStorable is set up for
        // referenced properties search. This violates a precondition
        // in OMFile::findProperty().
        //
        OMPropertyTag tag = findTag(wr->targetName());
        wr->setTargetTag(tag);
        */
        wr->setIdentificationBits(keyBits, keySize);
#else
        wr->setIdentificationBits(keyBits, keySize);
        wr->setValue(obj);

#endif
        delete [] keyBits;
        keyBits = 0;

#if defined(USETAGTABLE)
        } else {
          OMPropertyTag tag = findTag(wr->targetName());
          wr->setTargetTag(tag);

          // HACK4MEIP2
          // We failed to find the reference object by its InstanceUID,
          // save the ID to try it again later as a universal label.
          ASSERT("Referenced object ID can be a label",
                        wr->keySize() == sizeof(OMUniqueObjectIdentification));
          wr->setIdentificationBits(&id, sizeof(id));
        }
#endif
        break;
      }
      case SF_STRONG_OBJECT_REFERENCE_VECTOR: {
        OMStrongReferenceVector* v = fast_dynamic_cast<OMStrongReferenceVector*>(p);
        ASSERT("Valid type", v != 0);
        OMContainerIterator<OMStrongReferenceVectorElement>& iterator =
                                                                *v->iterator();
        while (++iterator) {
          OMStrongReferenceVectorElement& element = iterator.value();
          OMStrongObjectReference& r = element.reference();
          OMStorable* object = r.getValue();
          
          // The only case in which this doesn't succeed is when strong reference is incorrect
          // This shall never happen, but in case it happens (incorrect AAF), proceed without crashing
          if (object != 0) {
            deepRestore(*object->propertySet());
          }
        }
        delete &iterator;
        break;
      }
      case SF_WEAK_OBJECT_REFERENCE_VECTOR: {
        OMWeakReferenceVector* v = fast_dynamic_cast<OMWeakReferenceVector*>(p);
        ASSERT("Valid type", v != 0);
        OMPropertyId keyPid = v->keyPropertyId();
        const OMKeySize keySize = v->keySize();
        OMByte* key = new OMByte[keySize];
        ASSERT("Valid heap pointer", key != 0);
        OMContainerIterator<OMWeakReferenceVectorElement>& iterator =
                                                                *v->iterator();
        while (++iterator) {
          OMWeakReferenceVectorElement& element = iterator.value();
          OMWeakObjectReference& r = element.reference();
          const OMUniqueObjectIdentification id =
              *reinterpret_cast<const OMUniqueObjectIdentification*>(
                                                     element.identification());
          OMStorable* obj = _storage->object(id);
#if defined(USETAGTABLE)
        if (obj != 0) {
#endif
          ASSERT("Valid object", obj != 0);
          OMProperty* kp = obj->propertySet()->get(keyPid);
          ASSERT("Valid property", kp != 0);
          ASSERT("Consistent sizes", kp->bitsSize() == keySize);
          memset(key, 0, keySize);
          kp->getBits(key, keySize);
#if defined(USETAGTABLE)
          OMPropertyTag tag = findTag(v->targetName());
          OMWeakObjectReference newReference(v,
                                             key,
                                             keySize,
                                             tag);
          r = newReference;
#else
          r.setValue(key, obj);
#endif
#if defined(USETAGTABLE)
        } else {
          OMPropertyTag tag = findTag(v->targetName());
          r.setTargetTag(tag);
        }
#endif
        }
        delete &iterator;
        delete [] key;
        key = 0;
        break;
      }
      case SF_WEAK_OBJECT_REFERENCE_SET: {
        OMWeakReferenceSet* s = fast_dynamic_cast<OMWeakReferenceSet*>(p);
        ASSERT("Valid type", s != 0);
        OMUInt32 count = s->count();
        if (count > 0) {
          OMContainerIterator<OMWeakReferenceSetElement>& iterator =
                                                                *s->iterator();
          OMPropertyId keyPid = s->keyPropertyId();
          const OMKeySize keySize = s->keySize();
          OMByte* key = new OMByte[keySize];
          ASSERT("Valid heap pointer", key != 0);
          OMVector<OMUniqueObjectIdentification> objects;

          objects.grow(count);
          while (++iterator) {
            OMWeakReferenceSetElement& element = iterator.value();
            //OMWeakObjectReference& r = element.reference();
            const OMUniqueObjectIdentification id =
                *reinterpret_cast<const OMUniqueObjectIdentification*>(
                                                     element.identification());
            objects.insert(id);
          }
          s->removeAllObjects();
          OMVectorIterator<OMUniqueObjectIdentification> viter(objects,
                                                               OMBefore);
          while (++viter) {
            OMUniqueObjectIdentification id = viter.value();
            OMStorable* obj = _storage->object(id);
#if defined(USETAGTABLE)
            if (obj != 0) {
#endif
            ASSERT("Valid object", obj != 0);
            OMProperty* kp = obj->propertySet()->get(keyPid);
            ASSERT("Valid property", kp != 0);
            ASSERT("Consistent sizes", kp->bitsSize() == keySize);
            memset(key, 0, keySize);
            kp->getBits(key, keySize);

            OMWeakReferenceSetElement element(s, key, keySize, nullOMPropertyTag);
#if defined(USETAGTABLE)
            OMPropertyTag tag = findTag(s->targetName());
            OMWeakObjectReference newReference(s,
                                               key,
                                               keySize,
                                               tag);
            element.reference() = newReference;
#else
            element.setValue(key, obj);
#endif
            s->insert(key, element);
#if defined(USETAGTABLE)
            } else {
              /* OMPropertyTag tag = */ findTag(s->targetName());
              //element.reference().setTargetTag(tag);
            }
#endif
          }
          delete &iterator;
          delete [] key;
          key = 0;
        }
        break;
      }
      case SF_DATA:
      case SF_DATA_STREAM:
        // tjb -- NYI
        break;
      default:
        break;
      }
    }
  }
}

void OMKLVStoredObject::referenceRestore(OMStorable* object,
                                         OMPropertyId ANAME(pid))
{
  TRACE("OMKLVStoredObject::referenceRestore");

  ASSERT("Property is reference/instance UID",
         pid == PID_InterchangeObject_InstanceUID);
  OMUniqueObjectIdentification iid;
  _storage->read(iid, _reorderBytes);
  _storage->associate(object, iid);
}

void OMKLVStoredObject::writePrimerPack(const OMDictionary* dictionary)
{
  TRACE("OMKLVStoredObject::writePrimerPack");

  OMUInt32 elementCount = 0;
  OMUInt32 elementSize = sizeof(OMPropertyId) +
                         sizeof(OMUniqueObjectIdentification);
  _storage->writeKLVKey(primerKey);
  OMUInt64 lengthPosition = _storage->reserveKLVLength();
  OMUInt64 elementCountPosition = _storage->reserve(sizeof(elementCount));
  _storage->write(elementSize, _reorderBytes);

  // Instance UID
  _storage->write(PID_InterchangeObject_InstanceUID, _reorderBytes);
  OMKLVKey iuidk;
  convert(iuidk, Property_InterchangeObject_InstanceUID);
  _storage->writeKLVKey(iuidk);
  elementCount = elementCount + 1;

  if (dictionary->isRequired(dictionary->file()->encoding())) {
    // Meta Dictionary
    _storage->write(PID_Root_MetaDictionary, _reorderBytes);
    convert(iuidk, Property_Root_MetaDictionary);
    _storage->writeKLVKey(iuidk);
    elementCount = elementCount + 1;

    // Header
    _storage->write(PID_Root_Header, _reorderBytes);
    convert(iuidk, Property_Root_Header);
    _storage->writeKLVKey(iuidk);
    elementCount = elementCount + 1;

    // Format Version
    // Add Format Version to the Primer only if using valid standard PID
    // because legacy invalid PID would conflict with the TypeDefinitions
    // PID. This makes the Primer incomplete but this is an old error.
    if (isEnforcingST377(dictionary->file())) {
      _storage->write(PID_Root_FormatVersion, _reorderBytes);
      convert(iuidk, Property_Root_FormatVersion);
      _storage->writeKLVKey(iuidk);
      elementCount = elementCount + 1;
    }

    // Object Directory
    // Omit Object Directory because its legacy invalid PID would conflict
    // with the ClassDefinitions PID.
  }

  ClassDefinitionsIterator* classes = dictionary->classDefinitions();
  while (++(*classes)) {
    OMObject* obj = classes->currentObject();
    OMClassDefinition* classDefinition = dynamic_cast<OMClassDefinition*>(obj);
    ASSERT("Object is correct type", classDefinition != 0);
    PropertyDefinitionsIterator*
                           properties = classDefinition->propertyDefinitions();
    while (++(*properties)) {
      elementCount = elementCount + 1;
      OMObject* obj = properties->currentObject();
      OMPropertyDefinition* propertyDefinition =
                                      dynamic_cast<OMPropertyDefinition*>(obj);
      ASSERT("Object is correct type", propertyDefinition != 0);
      OMPropertyId pid = propertyDefinition->localIdentification();
      OMDictionary::mapToKLV(pid);
      _storage->write(pid, _reorderBytes);
      OMUniqueObjectIdentification id = propertyDefinition->identification();
      OMDictionary::mapToKLV(id);
      OMKLVKey k;
      convert(k, id);
      _storage->writeKLVKey(k);
    }
    delete properties;
  }
  delete classes;

  // patch length and elementCount
  _storage->fixupKLVLength(lengthPosition);
  _storage->fixup(elementCountPosition, elementCount);
}

void OMKLVStoredObject::readPrimerPack(OMDictionary* dictionary)
{
  TRACE("OMKLVStoredObject::readPrimerPack");

  _storage->readKLVLength();
  OMUInt32 elementCount;
  _storage->read(elementCount, _reorderBytes);
  OMUInt32 elementSize;
  _storage->read(elementSize, _reorderBytes);
  ASSERT("Valid element size",
                       elementSize == sizeof(OMKLVKey) + sizeof(OMPropertyId));
  for (OMUInt32 i = 0; i < elementCount; i++) {
    OMPropertyId pid;
    _storage->read(pid, _reorderBytes);
    OMDictionary::mapFromKLV(pid);
    OMKLVKey x;
    _storage->readKLVKey(x);
    OMUniqueObjectIdentification id;
    convert(id, x);
    OMDictionary::mapFromKLV(id);
    if (id != Property_InterchangeObject_InstanceUID) {
      dictionary->associate(id, pid);
    }
  }
}

void OMKLVStoredObject::saveObjectDirectoryReference(
                                        const OMUniqueObjectIdentification& id)
{
  OMPropertySize size = sizeof(OMUniqueObjectIdentification) +
                        sizeof(OMUInt64);
  // pid
  OMPropertyId pid = PID_Legacy_Root_ObjectDirectory;
  _storage->write(pid, _reorderBytes);
  // size
  _storage->write(size, _reorderBytes);
  // id
  _storage->write(id, _reorderBytes);
  // offset (not yet known, will patch later)
  OMUInt64 offset = 0;
  _storage->reference(_storage->position(), FUT_OBJECTDIRECTORY);
  _storage->write(offset, _reorderBytes);
}

OMUInt64
OMKLVStoredObject::restoreObjectDirectoryReference(
                                              OMUniqueObjectIdentification& id)
{
  TRACE("OMKLVStoredObject::restoreObjectDirectoryReference");

  // pid
  OMPropertyId pid;
  _storage->read(pid, _reorderBytes);
  ASSERT("Expected pid", pid == PID_Root_ObjectDirectory ||
                         pid == PID_Legacy_Root_ObjectDirectory);
  // size
  OMPropertySize size;
  _storage->read(size, _reorderBytes);
  ASSERT("Expected size",
            size == (sizeof(OMUniqueObjectIdentification) + sizeof(OMUInt64)));
  // id
  _storage->read(id, _reorderBytes);
  // offset
  OMUInt64 offset;
  _storage->read(offset, _reorderBytes);
  return offset;
}

void OMKLVStoredObject::writeMetaDictionary(const OMDictionary* dictionary)
{
  TRACE("OMKLVStoredObject::writeMetaDictionary");

  OMSet<OMUniqueObjectIdentification,
        const OMClassDefinition*> extensionClasses;
  OMSet<OMUniqueObjectIdentification,
        const OMPropertyDefinition*> extensionProperties;
  OMSet<OMUniqueObjectIdentification,
        const OMType*> extensionTypes;
  ClassDefinitionsIterator* classes = dictionary->classDefinitions();
  while (++(*classes)) {
    OMObject* cdef = classes->currentObject();
    OMClassDefinition* classDefinition = dynamic_cast<OMClassDefinition*>(cdef);
    ASSERT("Object is correct type", classDefinition != 0);
    if (!classDefinition->isPredefined()) {
      // Add classDefinition to output set
      extensionClasses.insert(classDefinition->identification(),
                              classDefinition);
    }
    PropertyDefinitionsIterator*
                           properties = classDefinition->propertyDefinitions();
    while (++(*properties)) {
      OMObject* pdef = properties->currentObject();
      ASSERT("Valid object", pdef != 0);
      OMPropertyDefinition* propertyDefinition = dynamic_cast<OMPropertyDefinition*>(pdef);
      ASSERT("Object is correct type", propertyDefinition != 0);
      if (!propertyDefinition->isPredefined()) {
        OMUniqueObjectIdentification id = propertyDefinition->identification();
        ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
        if (!extensionProperties.contains(id)) {
          // Add propertyDefinition to output set
          extensionProperties.insert(propertyDefinition->identification(),
                                     propertyDefinition);

          const OMType* typeDefinition = propertyDefinition->type();
          ASSERT("Valid type", typeDefinition != 0);
          if (!typeDefinition->isPredefined()) {
            if (!extensionTypes.contains(typeDefinition->identification())) {
              //  Add type Definition to output set
              extensionTypes.insert(typeDefinition->identification(),
                                    typeDefinition);

              // Process (recursively) dependendant types
              //
              TypeCollector tc(extensionTypes);
              typeDefinition->accept(tc);
            }
          }
        }
      }
    }
    delete properties;
  }
  delete classes;

  // Output extension definitions
  OMSetIterator<OMUniqueObjectIdentification,
                const OMClassDefinition*> extcl(extensionClasses, OMBefore);
  OMSetIterator<OMUniqueObjectIdentification,
                const OMPropertyDefinition*> extprop(extensionProperties,
                                                     OMBefore);
  OMSetIterator<OMUniqueObjectIdentification,
                const OMType*> exttype(extensionTypes, OMBefore);

  size_t total = extcl.count() + extprop.count() + exttype.count();
  if (total != 0) {

    // Output KL for meta dictionary
    _storage->writeKLVKey(metaDictionaryKey);
    OMUInt64 lengthPosition = _storage->reserveKLVLength();

    // Output set of extension classes
    while (++extcl) {
      const OMClassDefinition* cd = extcl.value();
      writeClassDefinition(cd);
    }

    // Output set of extension properties
    while (++extprop) {
      const OMPropertyDefinition* pd = extprop.value();
      writePropertyDefinition(pd);
    }

    // Output set of extension types
    while (++exttype) {
      const OMType* td = exttype.value();
      writeTypeDefinition(td);
    }

    // fixup length of KLV packet
    _storage->fixupKLVLength(lengthPosition);

  } // else no extensions - no dictionary
}

void OMKLVStoredObject::writeDefinition(const OMDefinition* d)
{
  TRACE("OMKLVStoredObject::writeDefinition");

  // identification (key)
  OMUniqueObjectIdentification id = d->identification();
  ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
  OMKLVKey k;
  convert(k, id);
  _storage->writeKLVKey(k);

  // name (string)
  const wchar_t* name = d->name();
  write(name);

  // description (string) [optional]
  if (d->hasDescription()) {
    // Present
    const wchar_t* description = d->description();
    ASSERT("Valid description", description != 0);
    write(description);
  } else {
    // Not present
    OMUInt16 len = 0;
    _storage->write(len, _reorderBytes);
  }
}

void OMKLVStoredObject::writeClassDefinition(const OMClassDefinition* cd)
{
  TRACE(" OMKLVStoredObject::writeClassDefinition");

  ASSERT("Valid class definition", cd != 0);

  // length
  OMUInt64 p = _storage->reserve(sizeof(OMUInt16));

  // tag
  OMByte classTag = 0x10;
  _storage->write(classTag);

  // definition [key, name, description]
  writeDefinition(cd);

  // parent (key)
  // An extension cannot be a root
  ASSERT("Class is not a root", cd->hasParent());
  const OMClassDefinition* pc = cd->parent();
  ASSERT("Valid parent class definition", pc != 0);
  OMUniqueObjectIdentification id = pc->identification();
  ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
  OMKLVKey k;
  convert(k, id);
  _storage->writeKLVKey(k);

  // properties [not in this flat dictionary]

  // isConcrete (boolean)
  write(cd->isConcrete());

  // fixup length
  _storage->fixup(p, (OMUInt16)(_storage->position() - p - sizeof(OMUInt16)));
}

void OMKLVStoredObject::writePropertyDefinition(const OMPropertyDefinition* pd)
{
  TRACE("OMKLVStoredObject::writePropertyDefinition");

  ASSERT("Valid property definition", pd != 0);

  // length
  OMUInt64 p = _storage->reserve(sizeof(OMUInt16));

  // tag
  OMByte propertyTag = 0x20;
  _storage->write(propertyTag);

  // definition [key, name, description]
  writeDefinition(pd);

  // type (key)
  const OMType* t = pd->type();
  ASSERT("Valid type", t != 0);
  OMUniqueObjectIdentification id = t->identification();
  ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
  OMKLVKey k;
  convert(k, id);
  _storage->writeKLVKey(k);

  // isRequired (boolean)
  write(!pd->isOptional());

  // localIdentification (UInt16) [not here - already in primer]

  // member of (key) [not in other (unflattened) dictionaries]
  OMClassDefinition* cd = pd->containingClass();
  ASSERT("Valid class definition", cd != 0);
  id = cd->identification();
  ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
  convert(k, id);
  _storage->writeKLVKey(k);

  // fixup length
  _storage->fixup(p, (OMUInt16)(_storage->position() - p - sizeof(OMUInt16)));
}

void OMKLVStoredObject::writeTypeDefinition(const OMType* td)
{
  TRACE("OMKLVStoredObject::writeTypeDefinition");

  ASSERT("Valid type definition", td != 0);

  // length
  OMUInt64 p = _storage->reserve(sizeof(OMUInt16));

  // tag
  OMByte typeTag = td->tag();
  _storage->write(typeTag + 0x30);

  // definition [key, name, description]
  writeDefinition(td);

  switch(typeTag) {
  case OMType::OMTTInteger: {
    const OMIntegerType* it = fast_dynamic_cast<const OMIntegerType*>(td);
    ASSERT("Correct type", it != 0);
    // Size
    OMUInt8 sz = it->size();
    _storage->write(sz);
    // IsSigned
    bool sign = it->isSigned();
    write(sign);
    break;
    }
  case OMType::OMTTCharacter: {
    ARESULT(const OMCharacterType* ct)
    dynamic_cast<const OMCharacterType*>(td);
    ASSERT("Correct type", ct != 0);
    // No additional attributes
    break;
    }
  case OMType::OMTTStrongObjectReference: {
    const OMStrongObjectReferenceType* rt = fast_dynamic_cast<const OMStrongObjectReferenceType*>(td);
    ASSERT("Correct type", rt != 0);
    // ReferencedType
    OMUniqueObjectIdentification id = rt->referencedType();
    ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
    OMKLVKey k;
    convert(k, id);
    _storage->writeKLVKey(k);
    break;
    }
  case OMType::OMTTWeakObjectReference: {
    const OMWeakObjectReferenceType* rt = fast_dynamic_cast<const OMWeakObjectReferenceType*>(td);
    ASSERT("Correct type", rt != 0);
    // ReferencedType
    OMUniqueObjectIdentification id = rt->referencedType();
    ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
    OMKLVKey k;
    convert(k, id);
    _storage->writeKLVKey(k);
    // TargetPathElementCount
    OMUInt32 count = rt->targetPathElementCount();
    _storage->write(count, _reorderBytes);
    // TargetPath
    for (OMUInt32 i = 0; i < count; i++) {
      const OMUniqueObjectIdentification& element = rt->targetPathElement(i);
      ASSERT("Valid identification",
                                  element != nullOMUniqueObjectIdentification);
      convert(k, element);
      _storage->writeKLVKey(k);
    }
    break;
    }
  case OMType::OMTTRename: {
    const OMRenamedType* rt = fast_dynamic_cast<const OMRenamedType*>(td);
    ASSERT("Correct type", rt != 0);
    // RenamedType
    OMType* renType = rt->renamedType();
    ASSERT("Valid renamed type", renType != 0);
    OMUniqueObjectIdentification id = renType->identification();
    ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
    OMKLVKey k;
    convert(k, id);
    _storage->writeKLVKey(k);
    break;
    }
  case OMType::OMTTEnumerated: {
    const OMEnumeratedType* et = fast_dynamic_cast<const OMEnumeratedType*>(td);
    ASSERT("Correct type", et != 0);
    // ElementType
    OMType* elType = et->elementType();
    ASSERT("Valid element type", elType != 0);
    OMUniqueObjectIdentification id = elType->identification();
    ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
    OMKLVKey k;
    convert(k, id);
    _storage->writeKLVKey(k);
    // ElementCount
    OMUInt32 count = et->elementCount();
    _storage->write(count, _reorderBytes);
    for (OMUInt32 i = 0; i < count; i++) {
      // ElementName
      const wchar_t* eName = et->elementName(i);
      write(eName);
      // ElementValue
      OMUInt64 eValue = et->elementValue(i);
      _storage->write(eValue, _reorderBytes);
    }
    break;
    }
  case OMType::OMTTFixedArray: {
    const OMFixedArrayType* at = fast_dynamic_cast<const OMFixedArrayType*>(td);
    ASSERT("Correct type", at != 0);
    // ElementType
    OMType* elType = at->elementType();
    ASSERT("Valid element type", elType != 0);
    OMUniqueObjectIdentification id = elType->identification();
    ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
    OMKLVKey k;
    convert(k, id);
    _storage->writeKLVKey(k);
    // ElementCount
    OMUInt32 count = at->elementCount();
    _storage->write(count, _reorderBytes);
    break;
    }
  case OMType::OMTTVaryingArray: {
    const OMVaryingArrayType* at = fast_dynamic_cast<const OMVaryingArrayType*>(td);
    ASSERT("Correct type", at != 0);
    // ElementType
    OMType* elType = at->elementType();
    ASSERT("Valid element type", elType != 0);
    OMUniqueObjectIdentification id = elType->identification();
    ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
    OMKLVKey k;
    convert(k, id);
    _storage->writeKLVKey(k);
    break;
    }
  case OMType::OMTTSet: {
    const OMSetType* st = fast_dynamic_cast<const OMSetType*>(td);
    ASSERT("Correct type", st != 0);
    // ElementType
    OMType* elType = st->elementType();
    ASSERT("Valid element type", elType != 0);
    OMUniqueObjectIdentification id = elType->identification();
    ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
    OMKLVKey k;
    convert(k, id);
    _storage->writeKLVKey(k);
    break;
    }
  case OMType::OMTTRecord: {
    const OMRecordType* rt = fast_dynamic_cast<const OMRecordType*>(td);
    ASSERT("Correct type", rt != 0);
    // MemberCount
    OMUInt32 count = rt->memberCount();
    _storage->write(count, _reorderBytes);
    for (OMUInt32 i = 0; i < count; i++) {
      // MemberType
      const OMType* mType = rt->memberType(i);
      OMUniqueObjectIdentification id = mType->identification();
      ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
      OMKLVKey k;
      convert(k, id);
      _storage->writeKLVKey(k);
      // MemberName
      const wchar_t* mName = rt->memberName(i);
      write(mName);
    }
    break;
    }
  case OMType::OMTTStream: {
    ARESULT(const OMStreamType* st)
    dynamic_cast<const OMStreamType*>(td);
    ASSERT("Correct type", st != 0);
    // No additional attributes
    break;
    }
  case OMType::OMTTString: {
    const OMStringType* st = fast_dynamic_cast<const OMStringType*>(td);
    ASSERT("Correct type", st != 0);
    // ElementType
    OMType* elType = st->elementType();
    ASSERT("Valid element type", elType != 0);
    OMUniqueObjectIdentification id = elType->identification();
    ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
    OMKLVKey k;
    convert(k, id);
    _storage->writeKLVKey(k);
    break;
    }
  case OMType::OMTTExtendibleEnumerated: {
    const OMExtendibleEnumeratedType* ot = fast_dynamic_cast<const OMExtendibleEnumeratedType*>(td);
    ASSERT("Correct type", ot != 0);
    // ElementCount
    OMUInt32 count = ot->elementCount();
    _storage->write(count, _reorderBytes);
    for (OMUInt32 i = 0; i < count; i++) {
      // ElementName
      const wchar_t* eName = ot->elementName(i);
      write(eName);
      // ElementValue
      OMUniqueObjectIdentification id = ot->elementValue(i);
      ASSERT("Valid identification", id != nullOMUniqueObjectIdentification);
      OMKLVKey k;
      convert(k, id);
      _storage->writeKLVKey(k);
    }
    break;
    }
  case OMType::OMTTIndirect: {
    ARESULT(const OMIndirectType* ot)
    dynamic_cast<const OMIndirectType*>(td);
    ASSERT("Correct type", ot != 0);
    // No additional attributes
    break;
    }
  case OMType::OMTTOpaque: {
    ARESULT(const OMOpaqueType* ot)
    dynamic_cast<const OMOpaqueType*>(td);
    ASSERT("Correct type", ot != 0);
    // No additional attributes
    break;
    }
  default:
    ASSERT("All cases handled", false);
    break;
  }
  // fixup length
  _storage->fixup(p, (OMUInt16)(_storage->position() - p - sizeof(OMUInt16)));
}

void OMKLVStoredObject::readMetaDictionary(OMDictionary* dictionary)
{
  TRACE("OMKLVStoredObject::readMetaDictionary");
  PRECONDITION("Valid dictionary", dictionary != 0);

  OMUInt64 len = _storage->readKLVLength();
  OMUInt64 remaining = len;
  while (remaining > 0) {
    OMUInt16 length;
    _storage->read(length, _reorderBytes);
    remaining = remaining - sizeof(OMUInt16);
    OMByte tag;
    _storage->read(tag);
    switch (tag) {
    case 0x10: {
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      OMUniqueObjectIdentification parent;
      bool isConcrete;
      readClassDefinition(id, &name, &description, parent, isConcrete);
      dictionary->newClass(id, name, description, parent, isConcrete);
      }
      break;
    case 0x20: {
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      OMUniqueObjectIdentification type;
      bool isRequired;
      OMUniqueObjectIdentification cont;
      readPropertyDefinition(id, &name, &description, type, isRequired, cont);
      dictionary->newProperty(id, name, description, type, isRequired, cont);
      }
      break;
    case 0x31: { // Integer
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // Size
      OMUInt8 sz;
      _storage->read(sz);

      // IsSigned
      bool isSigned;
      read(isSigned);

      dictionary->newIntegerType(id, name, description, sz, isSigned);
      }
      break;
    case 0x32: { // Character
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // No additional attributes
      dictionary->newCharacterType(id, name, description);
      }
      break;
    case 0x33: { // StrongObjectReference
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // ReferencedType
      OMKLVKey k;
      _storage->readKLVKey(k);
      OMUniqueObjectIdentification refType;
      convert(refType, k);

      dictionary->newStrongReferenceType(id, name, description, refType);
      }
      break;
    case 0x34: { // WeakObjectReference
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // ReferencedType
      OMKLVKey k;
      _storage->readKLVKey(k);
      OMUniqueObjectIdentification refType;
      convert(refType, k);

      // TargetPathElementCount
      OMUInt32 count;
      _storage->read(count, _reorderBytes);

      OMObjectIdentification* path = new OMObjectIdentification[count];
      ASSERT("Valid heap pointer", path != 0);
      // TargetPath
      for (OMUInt32 i = 0; i < count; i++) {
        _storage->readKLVKey(k);
        convert(path[i], k);
      }

      dictionary->newWeakReferenceType(id,
                                       name,
                                       description,
                                       refType,
                                       path,
                                       count);
      delete [] path;
      }
      break;
    case 0x35: { // Rename
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // RenamedType
      OMKLVKey k;
      _storage->readKLVKey(k);
      OMUniqueObjectIdentification renamedType;
      convert(renamedType, k);

      dictionary->newRenamedType(id, name, description, renamedType);
      }
      break;
    case 0x36: { // Enumerated
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // ElementType
      OMKLVKey k;
      _storage->readKLVKey(k);
      OMUniqueObjectIdentification type;
      convert(id, k);

      // ElementCount
      OMUInt32 count;
      _storage->read(count, _reorderBytes);

      const wchar_t** names = new const wchar_t*[count];
      ASSERT("Valid heap pointer", names != 0);
      OMInt64* values = new OMInt64[count];
      ASSERT("Valid heap pointer", values != 0);
      for (OMUInt32 i = 0; i < count; i++) {
        // ElementName
        OMUInt16 nameSize;
        _storage->read(nameSize, _reorderBytes);
        ASSERT("Valid size", nameSize > 0);
        names[i] = new wchar_t[nameSize];
        ASSERT("Valid heap pointer", names[i] != 0);
        read(names[i], nameSize);

        // ElementValue
        OMUInt64 eValue;
        _storage->read(eValue, _reorderBytes);
        values[i] = eValue;
      }
      dictionary->newEnumeratedType(id,
                                    name,
                                    description,
                                    type,
                                    names,
                                    values,
                                    count);
      delete [] names;
      delete [] values;
      }
      break;
    case 0x37: { // FixedArray
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // ElementType
      OMKLVKey k;
      _storage->readKLVKey(k);
      OMUniqueObjectIdentification elType;
      convert(elType, k);

      // ElementCount
      OMUInt32 count;
      _storage->read(count, _reorderBytes);

      dictionary->newFixedArrayType(id, name, description, elType, count);
      }
      break;
    case 0x38: { // VaryingArray
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // ElementType
      OMKLVKey k;
      _storage->readKLVKey(k);
      OMUniqueObjectIdentification elType;
      convert(elType, k);

      dictionary->newVaryingArrayType(id, name, description, elType);
      }
      break;
    case 0x39: { // Set
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // ElementType
      OMKLVKey k;
      _storage->readKLVKey(k);
      OMUniqueObjectIdentification elType;
      convert(elType, k);

      dictionary->newSetType(id, name, description, elType);
      }
      break;
    case 0x3a: { // Record
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // MemberCount
      OMUInt32 count;
      _storage->read(count, _reorderBytes);

      OMObjectIdentification* memberTypes = new OMObjectIdentification[count];
      ASSERT("Valid heap pointer", memberTypes != 0);
      const wchar_t** memberNames = new const wchar_t*[count];
      ASSERT("Valid heap pointer", memberNames != 0);
      for (OMUInt32 i = 0; i < count; i++) {
        // MemberType
        OMKLVKey k;
        _storage->readKLVKey(k);
        convert(memberTypes[i], k);

        // MemberName
        OMUInt16 nameSize;
        _storage->read(nameSize, _reorderBytes);
        ASSERT("Valid size", nameSize > 0);
        memberNames[i] = new wchar_t[nameSize];
        ASSERT("Valid heap pointer", memberNames[i] != 0);
        read(memberNames[i], nameSize);

      }
      dictionary->newRecordType(id,
                                name,
                                description,
                                memberTypes,
                                memberNames,
                                count);
      }
      break;
    case 0x3b: { // Stream
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // No additional attributes
      dictionary->newStreamType(id, name, description);
      }
      break;
    case 0x3c: { // String
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // ElementType
      OMKLVKey k;
      _storage->readKLVKey(k);
      OMUniqueObjectIdentification elType;
      convert(elType, k);

      dictionary->newStringType(id, name, description, elType);
      }
      break;
    case 0x3d: { // ExtendibleEnumerated
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // ElementCount
      OMUInt32 count;
      _storage->read(count, _reorderBytes);

      const wchar_t** names = new const wchar_t*[count];
      ASSERT("Valid heap pointer", names != 0);
      OMObjectIdentification* values = new OMObjectIdentification[count];
      ASSERT("Valid heap pointer", values != 0);
      for (OMUInt32 i = 0; i < count; i++) {
        // ElementName
        OMUInt16 nameSize;
        _storage->read(nameSize, _reorderBytes);
        ASSERT("Valid size", nameSize > 0);
        names[i] = new wchar_t[nameSize];
        ASSERT("Valid heap pointer", names[i] != 0);
        read(names[i], nameSize);

        // ElementValue
        OMKLVKey k;
        _storage->readKLVKey(k);
        convert(values[i], k);
      }
      dictionary->newExtendibleEnumeratedType(id,
                                              name,
                                              description,
                                              names,
                                              values,
                                              count);
      delete [] names;
      delete [] values;
      }
      break;
    case 0x3e: { // Indirect
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // No additional attributes
      dictionary->newIndirectType(id, name, description);
      }
      break;
    case 0x3f: { // Opaque
      // definition [key, name, description]
      OMUniqueObjectIdentification id;
      const wchar_t* name;
      const wchar_t* description;
      readDefinition(id, &name, &description);

      // No additional attributes
      dictionary->newOpaqueType(id, name, description);
      }
      break;
    default:
      //mxfError("Invalid definition tag (%"MXFPRIx08").\n", tag);
      //skipBytes(length - 1, infile);
      ASSERT("Valid tag", false);
      break;
    }
    //fprintf(stdout, "\n");
    remaining = remaining - length;
  }
  dictionary->resolve();
}

void OMKLVStoredObject::readDefinition(OMUniqueObjectIdentification& id,
                                       const wchar_t** name,
                                       const wchar_t** description)
{
  TRACE("OMKLVStoredObject::readDefinition");

  // identification (label)
  OMKLVKey k;
  _storage->readKLVKey(k);
  convert(id, k);

  // name (string)
  OMUInt16 nameSize;
  _storage->read(nameSize, _reorderBytes);
  ASSERT("Valid size", nameSize > 0);
  *name = new wchar_t[nameSize];
  ASSERT("Valid heap pointer", *name != 0);
  read(*name, nameSize);

  // description (string - optional)
  OMUInt16 descSize;
  _storage->read(descSize, _reorderBytes);
  if (descSize > 0) {
    *description = new wchar_t[descSize];
    ASSERT("Valid heap pointer", *description != 0);
    read(*description, descSize);
  } else {
    *description = 0;
  }
}

void
OMKLVStoredObject::readClassDefinition(OMUniqueObjectIdentification& id,
                                       const wchar_t** name,
                                       const wchar_t** description,
                                       OMUniqueObjectIdentification& parent,
                                       bool& isConcrete)
{
  TRACE("OMKLVStoredObject::readPropertyDefinition");

  // definition [key, name, description]
  readDefinition(id, name, description);

  // parent class (label)
  OMKLVKey k;
  _storage->readKLVKey(k);
  convert(parent, k);

  // concrete/abstract (bool)
  read(isConcrete);
}

void OMKLVStoredObject::readPropertyDefinition(
                                        OMUniqueObjectIdentification& id,
                                        const wchar_t** name,
                                        const wchar_t** description,
                                        OMUniqueObjectIdentification& type,
                                        bool& isRequired,
                                        OMUniqueObjectIdentification& memberOf)
{
  TRACE("OMKLVStoredObject::readPropertyDefinition");

  // definition [key, name, description]
  readDefinition(id, name, description);

  // type (key)
  OMKLVKey k;
  _storage->readKLVKey(k);
  convert(type, k);

  // isRequired (boolean)
  read(isRequired);

  // localIdentification (UInt16) [not here - already in primer]

  // member of (key) [not in other (unflattened) dictionaries]
  _storage->readKLVKey(k);
  convert(memberOf, k);
}

void OMKLVStoredObject::readTypeDefinition(OMDictionary* /* dictionary */)
{
  TRACE("OMKLVStoredObject::readTypeDefinition");
}

  // @mfunc Constructor.
  //   @parm The <c OMRawStorage> on which this <c OMKLVStoredObject> resides.
  //   @parm TBS
OMKLVStoredObject::OMKLVStoredObject(OMMXFStorageBase* s, OMByteOrder byteOrder)
: _storage(s),
  _byteOrder(byteOrder),
  _reorderBytes(false)
{
  TRACE("OMKLVStoredObject::OMKLVStoredObject");

  if (hostByteOrder() == bigEndian) {
    _reorderBytes = false;
  } else {
    _reorderBytes = true;
  }
}
