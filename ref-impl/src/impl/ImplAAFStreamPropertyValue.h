//@doc
//@class    AAFStreamPropertyValue | Implementation class for AAFPropertyValue
#ifndef __ImplAAFStreamPropertyValue_h__
#define __ImplAAFStreamPropertyValue_h__
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


class ImplAAFRoot;
class ImplAAFTypeDefStream;
class OMDataStreamProperty;
struct IAAFIOCompletion;

#ifndef __ImplAAFPropertyValue_h__
#include "ImplAAFPropertyValue.h"
#endif


class ImplAAFStreamPropertyValue : public ImplAAFPropertyValue
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFStreamPropertyValue ();



  //  
  // All reads/and writes advance the current position 
  // 


  // 
  // Raw byte stream access 
  // 


  // Stream size and positioning 

  //****************
  // GetSize()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetSize
        (// @parm [out] count of bytes in the specified stream property value
         aafInt64 *  pSize);

  //****************
  // SetSize()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetSize
        (// @parm [in] new count of bytes in the specified stream property value
         aafInt64  newSize);

  //****************
  // GetPosition()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPosition
        (// @parm [out] current byte position in the specified stream property value
         aafInt64 *  pPosition);

  //****************
  // SetPosition()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPosition
        (// @parm [in] the new position in the specified stream property value
         aafInt64  newPosition);


  // Sequential access 

  //****************
  // Read()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Read
        (// @parm [in] number of bytes to read
         aafUInt32  dataSize,

         // @parm [out, size_is(dataSize), length_is(*bytesRead)] buffer into which one element from the stream should be written
         aafMemPtr_t  pData,

         // @parm [out,ref] number of bytes actually read (will be either dataSize or 0 if there 
         // is in error)
         aafUInt32 *  bytesRead);

  //****************
  // Write()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Write
        (// @parm [in] number of bytes to write
         aafUInt32  dataSize,

         // @parm [in, ref, size_is(dataSize)] buffer into which should contain one element to be written to the stream
         aafMemPtr_t  pData);


  // Extending the stream 

  //****************
  // Append()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Append
        (// @parm [in] number of bytes to write (must be equal to the element type length)
         aafUInt32  dataSize,

         // @parm [in, ref, size_is(dataSize)] buffer into which should contain one element to be written to the stream
         aafMemPtr_t  pData);


  // Sequential access, multiple buffers

  //****************
  // ReadScatter()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    ReadScatter
        (// @parm [in] number of buffers
         aafUInt32  bufCount,

         // @parm [out, size_is(bufCount)] buffers into which bytes
         // from the stream are written
         aafIOBufferDesc_t *  pBufs,

         // @parm [out,ref] number of bytes actually read (will be
         // either dataSize or 0 if there is an error)
         aafUInt32 *  pBytesRead);

  //****************
  // WriteGather()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    WriteGather
        (// @parm [in] number of buffers
         aafUInt32  bufCount,

         // @parm [in, ref, size_is(bufCount)] buffers containing data
         // to be written to the stream
         aafIOBufferDesc_constptr  pBufs,

         // @parm [out,ref] number of bytes actually written
         aafUInt32 *  pBytesWritten);


  // Asyncrounous sequential access, single buffer

  //****************
  // ReadAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    ReadAsyncAt
        (// @parm [in] stream position at which to start the read
         aafUInt64  position,

         // @parm [in] number of bytes to read
         aafUInt32  dataSize,

         // @parm [out, size_is(dataSize)] buffer into which bytes from
         // the stream are written
         aafMemPtr_t  pData,

         // @parm [in, ref] object implementing the IAAFIOCompletion
         // interface to be called when the read is completed
         IAAFIOCompletion *  pCompletion,

         // @parm [in, ref] client-specific data to be returned to the
         // as a part of the I/O completion routine
         aafMemConstPtr_t  pClientArg);

  //****************
  // WriteAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    WriteAsyncAt
        (// @parm [in] stream position at which to start the write
         aafUInt64  position,

         // @parm [in] number of bytes to write
         aafUInt32  dataSize,

         // @parm [out, size_is(dataSize)] buffer containing data
         // to be written to the stream
         aafMemConstPtr_t  pData,

         // @parm [in, ref] object implementing the IAAFIOCompletion
         // interface to be called when the write is completed
         IAAFIOCompletion *  pCompletion,

         // @parm [in, ref] client-specific data to be returned to the
         // as a part of the I/O completion routine
         aafMemConstPtr_t  pClientArg);


  // Asyncrounous sequential access, multiple buffers

  //****************
  // ReadScatterAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    ReadScatterAsyncAt
        (// @parm [in] stream position at which to start the read
         aafUInt64  position,

         // @parm [in] number of buffers
         aafUInt32  bufCount,

         // @parm [out, size_is(bufCount)] buffers into which bytes
         // from the stream are written
         aafIOBufferDesc_t *  pBufs,

         // @parm [in, ref] object implementing the IAAFIOCompletion
         // interface to be called when the read is completed
         IAAFIOCompletion *  pCompletion,

         // @parm [in, ref] client-specific data to be returned to the
         // as a part of the I/O completion routine
         aafMemConstPtr_t  pClientArg);

  //****************
  // WriteGatherAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    WriteGatherAsyncAt
        (// @parm [in] stream position at which to start the write
        aafUInt64  position,

         // @parm [in] number of buffers
        aafUInt32  bufCount,

         // @parm [in, ref, size_is(bufCount)] buffers containing data
         // to be written to the stream
         aafIOBufferDesc_constptr  pBufs,

         // @parm [in, ref] object implementing the IAAFIOCompletion
         // interface to be called when the write is completed
        IAAFIOCompletion *  pCompletion,

         // @parm [in, ref] client-specific data to be returned to the
         // as a part of the I/O completion routine
        aafMemConstPtr_t  pClientArg);



  // 
  // Access byte order of the stream 
  // 


  //****************
  // HasStoredByteOrder()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    HasStoredByteOrder
        (// @parm [out] kAAFTrue if this stream has a stored byte order
         aafBoolean_t *  pHasByteOrder);

  //****************
  // GetStoredByteOrder()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetStoredByteOrder
        (// @parm [out] Pointer to variable where byte order is to be copied
         eAAFByteOrder_t *  pByteOrder);

  //****************
  // SetStoredByteOrder()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetStoredByteOrder
        (// @parm [in] byte order is to be stored with the stream
         eAAFByteOrder_t  byteOrder);

  //****************
  // ClearStoredByteOrder()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    ClearStoredByteOrder(void);



  // 
  // Access in typed chunks of Elements 
  // 

  //****************
  // ReadElements()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    ReadElements
        (// @parm [in] the type definition of the elements to read
         ImplAAFTypeDef * pElementType,

         // @parm [in] number of bytes to read (must be evenly divisible by the element 
         // type length)
         aafUInt32  dataSize,

         // @parm [out, size_is(dataSize), length_is(*pBytesRead)] buffer into which elements from the stream should be written
         aafMemPtr_t  pData,

         // @parm [out,ref] number of bytes actually read (will be either dataSize or 0 if 
         // there is in error)
         aafUInt32 *  pBytesRead);

  //****************
  // WriteElements()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    WriteElements
        (// @parm [in] the type definition of the elements to read
         ImplAAFTypeDef * pElementType,

         // @parm [in] number of bytes to write (must be evenly divisible by the element type 
         // length)
         aafUInt32  dataSize,

         // @parm [in, ref, size_is(dataSize)] buffer into which elements from the stream should be written
         aafMemPtr_t  pData);


  // Extend in chunks of typed Elements 

  //****************
  // AppendElements()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    AppendElements
        (// @parm [in] the type definition of the elements to read
         ImplAAFTypeDef * pElementType,

         // @parm [in] number of bytes to write (must be evenly divisible by the element type 
         // length)
         aafUInt32  dataSize,

         // @parm [in, ref, size_is(dataSize)] buffer into which elements from the stream should be written
         aafMemPtr_t  pData);


  // Filtered stream size and positioning 

  //****************
  // GetSizeFiltered()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetSizeFiltered
        (// @parm [out] count of bytes in the specified stream property value
         aafInt64 *  pSize);

  //****************
  // SetSizeFiltered()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetSizeFiltered
        (// @parm [in] new count of bytes in the specified stream property value
         aafInt64  newSize);

  //****************
  // GetPositionFiltered()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPositionFiltered
        (// @parm [out] current byte position in the specified stream property value
         aafInt64 *  pPosition);

  //****************
  // SetPositionFiltered()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPositionFiltered
        (// @parm [in] the new position in the specified stream property value
         aafInt64  newPosition);


  // Sequential access 

  //****************
  // ReadFiltered()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    ReadFiltered
        (// @parm [in] number of bytes to read
         aafUInt32  dataSize,

         // @parm [out, size_is(dataSize), length_is(*bytesRead)] buffer into which one element from the stream should be written
         aafMemPtr_t  pData,

         // @parm [out,ref] number of bytes actually read (will be either dataSize or 0 if there 
         // is in error)
         aafUInt32 *  bytesRead);

  //****************
  // WriteFiltered()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    WriteFiltered
        (// @parm [in] number of bytes to write
         aafUInt32  dataSize,

         // @parm [in, ref, size_is(dataSize)] buffer into which should contain one element to be written to the stream
         aafMemPtr_t  pData);


  // Extending the filtered stream 

  //****************
  // AppendFiltered()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    AppendFiltered
        (// @parm [in] number of bytes to write (must be equal to the element type length)
         aafUInt32  dataSize,

         // @parm [in, ref, size_is(dataSize)] buffer into which should contain one element to be written to the stream
         aafMemPtr_t  pData);



  // Sequential access, multiple buffers

  //****************
  // ReadScatter()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    ReadScatterFiltered
        (// @parm [in] number of buffers
         aafUInt32  bufCount,

         // @parm [out, size_is(bufCount)] buffers into which bytes
         // from the stream are written
         aafIOBufferDesc_t *  pBufs,

         // @parm [out,ref] number of bytes actually read (will be
         // either dataSize or 0 if there is an error)
         aafUInt32 *  pBytesRead);

  //****************
  // WriteGather()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    WriteGatherFiltered
        (// @parm [in] number of buffers
         aafUInt32  bufCount,

         // @parm [in, ref, size_is(bufCount)] buffers containing data
         // to be written to the stream
         aafIOBufferDesc_constptr  pBufs,

         // @parm [out,ref] number of bytes actually written
         aafUInt32 *  pBytesWritten);


  // Asyncrounous sequential access, single buffer

  //****************
  // ReadAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    ReadAsyncFilteredAt
        (// @parm [in] stream position at which to start the read
         aafUInt64  position,

         // @parm [in] number of bytes to read
         aafUInt32  dataSize,

         // @parm [out, size_is(dataSize)] buffer into which bytes from
         // the stream are written
         aafMemPtr_t  pData,

         // @parm [in, ref] object implementing the IAAFIOCompletion
         // interface to be called when the read is completed
         IAAFIOCompletion *  pCompletion,

         // @parm [in, ref] client-specific data to be returned to the
         // as a part of the I/O completion routine
         aafMemConstPtr_t  pClientArg);

  //****************
  // WriteAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    WriteAsyncFilteredAt
        (// @parm [in] stream position at which to start the write
         aafUInt64  position,

         // @parm [in] number of bytes to write
         aafUInt32  dataSize,

         // @parm [out, size_is(dataSize)] buffer containing data
         // to be written to the stream
         aafMemConstPtr_t  pData,

         // @parm [in, ref] object implementing the IAAFIOCompletion
         // interface to be called when the write is completed
         IAAFIOCompletion *  pCompletion,

         // @parm [in, ref] client-specific data to be returned to the
         // as a part of the I/O completion routine
         aafMemConstPtr_t  pClientArg);


  // Asyncrounous sequential access, multiple buffers

  //****************
  // ReadScatterAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    ReadScatterAsyncFilteredAt
        (// @parm [in] stream position at which to start the read
         aafUInt64  position,

         // @parm [in] number of buffers
         aafUInt32  bufCount,

         // @parm [out, size_is(bufCount)] buffers into which bytes
         // from the stream are written
         aafIOBufferDesc_t *  pBufs,

         // @parm [in, ref] object implementing the IAAFIOCompletion
         // interface to be called when the read is completed
         IAAFIOCompletion *  pCompletion,

         // @parm [in, ref] client-specific data to be returned to the
         // as a part of the I/O completion routine
         aafMemConstPtr_t  pClientArg);

  //****************
  // WriteGatherAsyncAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    WriteGatherAsyncFilteredAt
        (// @parm [in] stream position at which to start the write
        aafUInt64  position,

         // @parm [in] number of buffers
        aafUInt32  bufCount,

         // @parm [in, ref, size_is(bufCount)] buffers containing data
         // to be written to the stream
         aafIOBufferDesc_constptr  pBufs,

         // @parm [in, ref] object implementing the IAAFIOCompletion
         // interface to be called when the write is completed
        IAAFIOCompletion *  pCompletion,

         // @parm [in, ref] client-specific data to be returned to the
         // as a part of the I/O completion routine
        aafMemConstPtr_t  pClientArg);



  // 
  // Access in typed chunks of Elements in filtered stream
  // 

  //****************
  // ReadElementsFiltered()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    ReadElementsFiltered
        (// @parm [in] the type definition of the elements to read
         ImplAAFTypeDef * pElementType,

         // @parm [in] number of bytes to read (must be evenly divisible by the element 
         // type length)
         aafUInt32  dataSize,

         // @parm [out, size_is(dataSize), length_is(*pBytesRead)] buffer into which elements from the stream should be written
         aafMemPtr_t  pData,

         // @parm [out,ref] number of bytes actually read (will be either dataSize or 0 if 
         // there is in error)
         aafUInt32 *  pBytesRead);

  //****************
  // WriteElementsFiltered()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    WriteElementsFiltered
        (// @parm [in] the type definition of the elements to read
         ImplAAFTypeDef * pElementType,

         // @parm [in] number of bytes to write (must be evenly divisible by the element type 
         // length)
         aafUInt32  dataSize,

         // @parm [in, ref, size_is(dataSize)] buffer into which elements from the stream should be written
         aafMemPtr_t  pData);


  // Extend in chunks of typed Elements 

  //****************
  // AppendElementsFiltered()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    AppendElementsFiltered
        (// @parm [in] the type definition of the elements to read
         ImplAAFTypeDef * pElementType,

         // @parm [in] number of bytes to write (must be evenly divisible by the element type 
         // length)
         aafUInt32  dataSize,

         // @parm [in, ref, size_is(dataSize)] buffer into which elements from the stream should be written
         aafMemPtr_t  pData);




  // non-published method to initialize this object.
  // NOTE: The given property's type must be a stream type.
  AAFRESULT Initialize (const ImplAAFTypeDefStream *streamType,
                        OMProperty *property);

  virtual AAFRESULT STDMETHODCALLTYPE WriteTo(OMProperty* pOmProp);

  void setStreamAccess(OMDataStreamAccess* access);


  //****************
  // GetEssenceElementKey()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetEssenceElementKey
        (// @parm [in] key of the essence elements in this stream
         aafUID_t *  pEssenceElementKey);


  //****************
  // SetEssenceElementKey()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetEssenceElementKey
        (// @parm [in] key of the essence elements in this stream
         aafUID_constref  key);


protected:
  virtual ~ImplAAFStreamPropertyValue ();
  
  // special accessor
  aafUInt32 internalElementSize(void) const;

private:
	OMDataStreamProperty * _streamProperty;
};

//
// smart pointer
//

#ifndef __ImplAAFSmartPointer_h__
#include "ImplAAFSmartPointer.h"
#endif

typedef ImplAAFSmartPointer<ImplAAFStreamPropertyValue> ImplAAFStreamPropertyValueSP;

#endif // ! __ImplAAFStreamPropertyValue_h__
