//@doc
//@class    AAFEssenceStream | Implementation class for AAFEssenceStream
#ifndef __CAAFEssenceDataStream_h__
#define __CAAFEssenceDataStream_h__

/******************************************\
*                                          *
* Advanced Authoring Format                *
*                                          *
* Copyright (c) 1998 Avid Technology, Inc. *
*                                          *
\******************************************/

#ifndef __AAFPlugin_h__
#include "AAFPlugin.h"
#endif


#ifndef __CAAFUnknown_h__
#include "CAAFUnknown.h"
#endif

// forward declaration
interface IAAFEssenceData;


EXTERN_C const CLSID CLSID_AAFEssenceDataStream;

class CAAFEssenceDataStream
  : public IAAFEssenceDataStream,
    public IAAFEssenceStream,
    public CAAFUnknown
{
protected:

  //********
  //
  // Constructor/destructor
  //
  CAAFEssenceDataStream (IUnknown * pControllingUnknown);
  virtual ~CAAFEssenceDataStream ();

public:
  //
  // IAAFEssenceDataStream methods.
  //

  // Initialize this instance with an IAAFEssenceData interface pointer
  // ba calling QueryInterface on the given IUnknown pointer.
  STDMETHOD (Init)
            (/* [in] */ IUnknown *essenceData);

  
  //
  // IAAFEssenceStream methods.
  //

  // Write some number of bytes to the stream exactly and with no formatting or compression.
  STDMETHOD (Write)
    (/*[in,size_is(buflen)]*/ aafDataBuffer_t  buffer, // to a buffer
     /*[in]*/ aafInt32  buflen); // of this size 

  // Read some number of bytes from the stream exactly and with no formatting or compression.
  STDMETHOD (Read)
    (/*[in]*/ aafUInt32  buflen, // to a buffer of this size
     /*[out, size_is(buflen), length_is(*bytesRead)]*/ aafDataBuffer_t  buffer, // here is the buffer
     /*[out,ref]*/ aafUInt32 *  bytesRead); // Return bytes actually read 

  // Seek to the absolute byte offset into the stream.
  STDMETHOD (Seek)
    (/*[in]*/ aafInt64  byteOffset); // The absolute byte offset into the stream. 

  // Seek forward or backward the given byte count.
  STDMETHOD (SeekRelative)
    (/*[in]*/ aafInt32  byteOffset); // The relative byte offset into the stream. 

  // Returns AAFTrue if the byte offset is within the stream.
  STDMETHOD (IsPosValid)
    (/*[in]*/ aafInt64  byteOffset, // The absolute byte offset into the stream.
     /*[out]*/ aafBool *  isValid); // The result. 

  // Returns the position within the stream.
  STDMETHOD (GetPosition)
    (/*[out]*/ aafInt64 *  position); // The position within the stream. 

  // Returns the length of the stream.
  STDMETHOD (GetLength)
    (/*[out]*/ aafInt64 *  position); // The length of the stream. 

  // Ensure that all bits are written.
  STDMETHOD (FlushCache)
     ();


  // Sets the size of the cache buffer used for further operations.
			// Destroys the current contents of the cache.
  STDMETHOD (SetCacheSize)
    (/*[in]*/ aafInt32  itsSize); // The size of the cache buffer. 


  
  //
  // IUnknown methods. (Macro defined in CAAFUnknown.h)
  //

  AAF_DECLARE_STANDARD_UNKNOWN()

protected:
  // 
  // Declare the QI that implements for the interfaces
  // for this module. This will be called by CAAFUnknown::QueryInterface().
  // 
  virtual HRESULT InternalQueryInterface(REFIID riid, void **ppvObjOut);


public:
  //
  // This class as concrete. All objects can be constructed from
  // a CLSID. This will allow subclassing all "base-classes" by
  // aggreggation.
  // 
  AAF_DECLARE_FACTORY();
  //


private:
	IAAFEssenceData		*_data;
};

#endif // ! __CAAFEssenceDataStream_h__


