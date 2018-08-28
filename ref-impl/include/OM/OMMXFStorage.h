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
#ifndef OMMXFSTORAGE_H
#define OMMXFSTORAGE_H

#include "OMMXFStorageBase.h"
#include "OMDataTypes.h"
#include "OMIdentitySet.h"
#include "OMDataStream.h"
#include "OMList.h"
#include "OMListIterator.h"
#include "OMSet.h"
#include "OMVector.h"

#define OM_FASTER_STREAM_PARSING
#define OM_NEW_STREAM_WRITING

class OMMXFIndexStream;

class OMStorable;
template <typename Key, typename Element>
class OMSet;
template <typename Key, typename Element>
class OMSetIterator;
template <typename Element>
class OMIdentitySetIterator;

class OMDataStreamProperty; // tjb !!! we shouldn't know about this here

  // @class Class supporting access to the raw bytes of MXF
  //        files supported by the Object Manager.
  //   @base public | <c OMRawStorage>
  //   @cauthor Tim Bingham | tjb | Avid Technology, Inc.
class OMMXFStorage : public OMMXFStorageBase {
public:
  // @access Public members.

    // @cmember Constructor.
  OMMXFStorage(OMRawStorage* store);

    // @cmember Destructor.
  virtual ~OMMXFStorage(void);

    // @cmember Called when this <c OMMXFStorage> is opened for reading.
  virtual void openRead(void);

    // @cmember Called when this <c OMMXFStorage> is opened for modification.
  virtual void openModify(void);

    // @cmember Called when this <c OMMXFStorage> is created for writing.
  virtual void createWrite(void);

    // @cmember Called when this <c OMMXFStorage> is created for for
    //          modification.
  virtual void createModify(void);

    // @cmember Open this <c OMMXFStorage>.
  virtual void open(void);

    // @cmember Close this <c OMMXFStorage>.
  virtual void close(void);

    // @cmember Called after we Save() this <c OMMXFStorage>.
  virtual void postSave(bool finalize);

    // @cmember Set the operational pattern to <p pattern>.
  virtual void setOperationalPattern(const OMKLVKey& pattern);

    // @cmember Get the operational pattern.
  virtual OMKLVKey operationalPattern(void) const;

  typedef OMIdentitySet<OMKLVKey> LabelSet;
  typedef OMIdentitySetIterator<OMKLVKey> LabelSetIterator;

    // @cmember Add <p label> to the set of essence container labels.
  virtual void addEssenceContainerLabel(const OMKLVKey& label);

    // @cmember Is <p label> present in the set of essence container labels.
  virtual bool containsEssenceContainerLabel(const OMKLVKey& label) const;

    // @cmember Create an iterator over the set of essence container labels.
  virtual LabelSetIterator* essenceContainerLabels(void) const;

    // @cmember Set the file generation.
  virtual void setGeneration(const OMUniqueObjectIdentification& generation);

  virtual OMUniqueObjectIdentification generation(void) const;

    // @cmember findMetadata.
  virtual bool findMetadata(OMUInt64& partitionPosition);

  virtual void writeHeaderPartition(OMUInt32 bodySID,
                                    OMUInt32 indexSID,
                                    OMUInt32 KAGSize);
  virtual void writeBodyPartition(OMUInt32 bodySID,
                                  OMUInt32 indexSID,
                                  OMUInt32 KAGSize);
  virtual void writeFooterPartition(OMUInt32 indexSID,
                                    OMUInt32 KAGSize);
  virtual void writePartition(const OMKLVKey& key,
                              OMUInt32 bodySID,
                              OMUInt32 indexSID,
                              OMUInt32 KAGSize);

  virtual void writeRandomIndex(void);

  virtual void readRandomIndex(OMUInt64 length);

  virtual bool findRandomIndex(OMUInt64 fileSize,
                               OMUInt64& indexPosition);

  virtual bool isRandomIndex(OMUInt64 fileSize, OMUInt32 ripSize);

    // @cmember Write a fill key, a BER encoded length and
    //          fill between <p from> and <p to>.
  virtual void writeKLVFill(const OMUInt64& from, const OMUInt64& to);

    // @cmember Write a fill key, a BER encoded length and
    //          <p length> bytes of fill.
  virtual void writeKLVFill(const OMUInt64& length);

    // @cmember Write fill so that the next key is page aligned.
  virtual void fillAlignK(const OMUInt64& currentPosition,
                          const OMUInt32& KAGSize);

    // @cmember Write fill so that the next value is page aligned.
  virtual void fillAlignV(const OMUInt64& currentPosition,
                          const OMUInt32& KAGSize);

  virtual void write(const OMByte* bytes,
                     OMUInt32 byteCount,
                     OMUInt32& bytesWritten);
  virtual void write(const OMUInt8& i);
  virtual void write(const OMUInt16& i, bool reorderBytes);
  virtual void write(const OMUInt32& i, bool reorderBytes);
  virtual void write(const OMUInt64& i, bool reorderBytes);
  virtual void write(const OMUniqueObjectIdentification& id,
                     bool reorderBytes);
  virtual void write(const OMByte* buffer,
                     const OMUInt32& bufferSize);

  virtual void writeKLVKey(const OMKLVKey& key);

  virtual void writeKLVLength(const OMUInt8& length);
  virtual void writeKLVLength(const OMUInt16& length);
  virtual void writeKLVLength(const OMUInt32& length);
  virtual void writeKLVLength(const OMUInt64& length);

  virtual OMUInt64 reserveKLVLength(void);
  virtual void fixupKLVLength(const OMUInt64 lengthPosition);

  virtual OMUInt64 reserve(OMUInt32 size);
  virtual void fixup(const OMUInt64& patchOffset, const OMUInt8& patchValue);
  virtual void fixup(const OMUInt64& patchOffset, const OMUInt16& patchValue);
  virtual void fixup(const OMUInt64& patchOffset, const OMUInt32& patchValue);
  virtual void fixup(const OMUInt64& patchOffset, const OMUInt64& patchValue);

  virtual void writeBerLength(OMUInt32 lengthSize, const OMUInt64& length);

  virtual void readPartition(OMUInt64 length,
                             OMUInt32& bodySID,
                             OMUInt32& indexSID,
                             OMUInt32& KAGSize);

  virtual void readPartition(OMUInt64 length,
                             OMUInt32& bodySID,
                             OMUInt32& indexSID,
                             OMUInt32& KAGSize,
                             OMUInt64& previousPartition,
                             OMUInt64& thisPartition,
                             OMUInt64& footerPartition);

  virtual void readHeaderPartition(void);

  virtual void read(OMUInt8& i) const;
  virtual void read(OMInt8& i) const;
  virtual void read(OMUInt16& i, bool reorderBytes) const;
  virtual void read(OMUInt32& i, bool reorderBytes) const;
  virtual void read(OMUInt64& i, bool reorderBytes) const;
  virtual void read(OMInt64& i, bool reorderBytes) const;
  virtual void read(OMUniqueObjectIdentification& id, bool reorderBytes) const;
  virtual void read(OMByte* buffer, const OMUInt32& bufferSize) const;
  virtual void read(OMByte* bytes,
                    OMUInt32 byteCount,
                    OMUInt32& bytesRead) const;

  virtual void readKLVKey(OMKLVKey& key) const;

  virtual bool readOuterKLVKey(OMKLVKey& key) const;

  virtual OMUInt64 readKLVLength(void) const;

  virtual void readKLVFill(void) const;

  virtual void skipLV(void) const;

  virtual void skipV(OMUInt64 length) const;

  /*
  static OMUInt64 readBerLength(const OMRawStorage* store);
  */


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
                                        OMUniqueObjectIdentification* id);
    // @cmember Remember the InstanceUID of the object referenced
    //          by the specified weak reference property.
  virtual void associate(const void* reference,
                         const OMUniqueObjectIdentification& referencedInstanceId);


    // Object -> instanceId
  virtual OMUniqueObjectIdentification instanceId(OMStorable* object);

    // instanceId -> object
  virtual OMStorable* object(const OMUniqueObjectIdentification& instanceId);

    // object <-> instanceId
  virtual void associate(OMStorable* object,
                         const OMUniqueObjectIdentification& instanceId);

    // enter object into object directory
  virtual void enterObject(OMStorable& object, OMUInt64 position);

  virtual void removeObject(OMStorable& object);

  virtual bool containsObject(const OMUniqueObjectIdentification& instanceId);

  virtual void resolve(const OMUniqueObjectIdentification& instanceId);

  virtual OMUInt64 primerOffset(void);

  virtual void clearObjectDirectory(void);

  virtual void saveObjectDirectory(void);

  virtual void fixupReference(OMUInt64 patchOffset, OMUInt64 patchValue);

  virtual void restoreObjectDirectory(OMUInt64 headerOffset);

  virtual void setObjectDirectoryOffset(OMUInt64 objectDirectoryOffset);

  virtual OMUInt64 objectDirectoryOffset(void) const;

  virtual bool streamExists(OMUInt32 sid);

  virtual void createStreamAndAddSegment(OMUInt32 sid,
                            const OMKLVKey& label,
                            OMUInt32 blockSize,
                            OMUInt32 allocationSize,
                            bool alignV);

  virtual OMUInt32 addStream(OMDataStream* stream);

  virtual OMUInt32 streamIdentification(OMDataStream* stream);

  virtual OMDataStream* stream(OMUInt32 sid);

  virtual void associate(OMDataStream* stream, OMUInt32 sid);

  virtual bool containsStream(OMUInt32 sid);

  virtual bool containsStream(OMDataStream* stream);

  virtual OMUInt64 streamSize(OMUInt32 sid);

  virtual void streamSetSize(OMUInt32 sid, OMUInt64 newSize);

  virtual void streamRawWrite(OMUInt32 sid,
                              OMUInt64 rawPosition,
                              const OMByte* rawBytes,
                              OMUInt32 rawByteCount);

  virtual void streamFragment(OMUInt32 sid,
                              OMUInt64 position,
                              OMUInt32 byteCount,
                              OMUInt64& rawPosition,
                              OMUInt32& rawByteCount);

  virtual void streamWriteFragment(OMUInt32 sid,
                                   OMUInt64 position,
                                   const OMByte* bytes,
                                   OMUInt32 byteCount,
                                   OMUInt32& bytesWritten);

  virtual void writeStreamAt(OMUInt32 sid,
                             OMUInt64 position,
                             const OMByte* bytes,
                             OMUInt32 byteCount,
                             OMUInt32& bytesWritten);

  virtual void writeStreamAt(OMUInt32 sid,
                             OMUInt64 position,
                             OMIOBufferDescriptor* buffers,
                             OMUInt32 bufferCount,
                             OMUInt32& bytesWritten);

  virtual void writeStreamAt(OMUInt32 sid,
                             OMUInt64 position,
                             const OMByte* buffer,
                             const OMUInt32 bytes,
                             void* /* */ completion,
                             const void* clientArgument);

  virtual void writeStreamAt(OMUInt32 sid,
                             OMUInt64 position,
                             const OMIOBufferDescriptor* buffers,
                             OMUInt32 bufferCount,
                             void* /* */ completion,
                             const void* clientArgument);

  virtual void streamRawRead(OMUInt32 sid,
                             OMUInt64 rawPosition,
                             OMByte* rawBytes,
                             OMUInt32 rawByteCount);

  virtual void streamReadFragment(OMUInt32 sid,
                                  OMUInt64 position,
                                  OMByte* bytes,
                                  OMUInt32 byteCount,
                                  OMUInt32& bytesRead);

  virtual void readStreamAt(OMUInt32 sid,
                            OMUInt64 position,
                            OMByte* bytes,
                            OMUInt32 byteCount,
                            OMUInt32& bytesRead);

  virtual void readStreamAt(OMUInt32 sid,
                            OMUInt64 position,
                            OMIOBufferDescriptor* buffers,
                            OMUInt32 bufferCount,
                            OMUInt32& bytesRead);

  virtual void readStreamAt(OMUInt32 sid,
                            OMUInt64 position,
                            OMByte* buffer,
                            const OMUInt32 bytes,
                            void* /* */ completion,
                            const void* clientArgument);

  virtual void readStreamAt(OMUInt32 sid,
                            OMUInt64 position,
                            OMIOBufferDescriptor* buffers,
                            OMUInt32 bufferCount,
                            void* /* */ completion,
                            const void* clientArgument);

  virtual void streamRestoreSegment(OMUInt32 sid,
                                    OMUInt64 start,
                                    OMUInt64 allocatedSize,
                                    OMUInt64 occupiedSize,
                                    OMKLVKey label,
                                    OMUInt32 gridSize);

  virtual void streamGrow(OMUInt32 sid, OMUInt64 growBytes);

  virtual void saveStreams(void);
  virtual void restoreStreams(void);

  virtual const OMMXFIndexStream* indexStream(const OMUInt32 streamId) const;

  virtual void checkStreams(void);

  struct Stream;
  struct Segment {
    OMUInt64 _start;   // Stream position of this Segment
    OMUInt64 _size;    // Size of this Segment in bytes
    OMUInt64 _origin;  // File position of this Segment
    Stream* _stream;   // Stream to which this segment belongs
  };
  typedef OMList<Segment*> SegmentList;
  typedef OMListIterator<Segment*> SegmentListIterator;

  struct Stream {
    SegmentList* _segments;
    OMUInt64 _size;
    OMKLVKey _label;
    OMUInt32 _gridSize;
    OMUInt32 _sid;
  };

  virtual bool findStream(OMUInt32 sid, Stream*& stream);

  virtual SegmentListIterator* streamSegments(OMUInt32 sid) const;

    // @cmember Record a reference to <p tag> at <p address>.
  virtual void reference(OMUInt64 address, OMUInt8 tag);

    // @cmember Provide a definition for <p tag> of <p value>.
  virtual void definition(OMUInt64 value, OMUInt8 tag);

    // @cmember Apply <c Fixup>s for <p tag>.
  virtual void fixup(OMUInt8 tag);

    // @cmember Apply all <c Fixup>s.
  virtual void fixup(void);

    // @cmember Destroy all <c Fixup>s.
  virtual void destroyFixups(void);

  // Deferred streams
  virtual void addDeferredStream(OMDataStreamProperty* stream);

  virtual void performDeferredIO(void);

  virtual void postMetadataSavePosition(void);
  void postMetadataFill(void);

private:
  // @access Private members.

  void markMetadataStart(OMUInt64 primerKeyPosition);
  void markMetadataEnd(OMUInt64 endKeyPosition);

  void markIndexStart(OMKLVKey key,
                      OMUInt32 sid,
                      OMUInt32 gridSize,
                      OMUInt64 indexKeyPosition);
  void markIndexEnd(OMUInt64 endKeyPosition);

  void markEssenceSegmentStart(OMKLVKey key,
                               OMUInt32 sid,
                               OMUInt32 gridSize,
                               OMUInt64 essenceKeyPosition);
  void markEssenceSegmentEnd(OMUInt64 endKeyPosition);

  void markFill(OMUInt64 fillKeyPosition, OMUInt64 fillEndPosition);

  OMUInt32 _gridSize;

  OMUInt64 _primerPosition;
  OMUInt64 _headerByteCount;

  bool _inIndex;
  OMUInt32 _indexSID;
  OMKLVKey _indexKey;
  OMUInt64 _indexPosition;

  bool _inEssence;
  OMUInt32 _essenceSID;
  OMKLVKey _essenceKey;
  OMUInt64 _essencePosition;

  OMUInt64 _fillStart;
  OMUInt64 _fillEnd;

  struct ObjectDirectoryEntry {
    OMStorable* _object;
    OMUInt64 _offset;
    OMUInt8 _flags;
  };

  typedef OMSet<OMUniqueObjectIdentification,
                ObjectDirectoryEntry> ObjectDirectory;
  typedef OMSetIterator<OMUniqueObjectIdentification,
                        ObjectDirectoryEntry> ObjectDirectoryIterator;
  typedef OMSet<OMStorable*, OMUniqueObjectIdentification> ObjectSet;

  ObjectDirectory* instanceIdToObject(void);

  ObjectSet* objectToInstanceId(void);

  OMSet<OMDataStream*, OMUInt32>* streamToSid(void);
  OMSet<OMUInt32, OMDataStream*>* sidToStream(void);

  struct Fixup;
  typedef OMList<Fixup*> FixupList;
  typedef OMListIterator<Fixup*> FixupListIterator;

  struct Fixup {
    OMUInt64 _address; // File address
    OMUInt64 _value;   // Value to write to address
    OMUInt8  _tag;     // Identifies the reference
  };

  FixupList _fixups;

  bool _reorderBytes;
  OMKLVKey _operationalPattern;
  LabelSet _essenceContainerLabels;
  OMUniqueObjectIdentification _generation;
  OMSet<const void*, OMUniqueObjectIdentification>* _referenceToInstanceId;
  OMUInt64 _objectDirectoryOffset;    // offset of object directory
  ObjectDirectory* _instanceIdToObject;
  ObjectSet* _objectToInstanceId;
  OMSet<OMDataStream*, OMUInt32>* _streamToSid;
  OMSet<OMUInt32, OMDataStream*>* _sidToStream;
  OMUInt32 _maxSid;

  virtual Stream* createStream(OMUInt32 sid,
                               OMUInt64 size,
                               OMKLVKey label,
                               OMUInt32 allocationSize);
  virtual Segment* addSegment(Stream* s,
                              OMUInt64 start,
                              OMUInt64 size,
                              OMUInt64 origin);
  virtual Segment* findSegment(Stream* s, OMUInt64 position);
  virtual Segment* findLastSegment(Stream* s);
  virtual OMUInt64 allocatedSize(Stream* s);
  virtual Segment* streamSegment(OMUInt32 sid, OMUInt64 position);
  virtual OMUInt64 validSize(const Segment* segment);

    // debugging
  void printPartitions(void);
  void printStreams(void);

  typedef OMSet<OMUInt32, Stream*> SegmentMap;
  typedef OMSetIterator<OMUInt32, Stream*> SegmentMapIterator;
  virtual SegmentMap* segmentMap(void);
  void destroySegmentMap(void);
  SegmentMap* _segmentMap;
  SegmentList* _segments;
  OMUInt64 _fileSize;

  struct Partition {
    OMUInt64 _address;
    OMUInt32 _bodySID;
    OMUInt64 _previous;
    OMUInt32 _indexSID;
  };
  void destroyPartitions(void);
  bool findPartition(OMUInt64 address, OMUInt32& index) const;
  void addPartition(OMUInt64 address,  OMUInt32 bodySID, OMUInt32 index);
  OMVector<Partition*> _partitions;
  OMUInt64 _primerOffset;
  OMUInt64 _metadataEnd;
  typedef OMList<OMDataStreamProperty*> StreamList;
  typedef OMListIterator<OMDataStreamProperty*> StreamListIterator;
  StreamList _deferredStreams;

};

#endif
