//=---------------------------------------------------------------------=
//
// This file was GENERATED for the AAF SDK
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
// The Original Code of this file is Copyright 1998-2012, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
// The Initial Developer of the Original Code of this file and the
// licensor of the Advanced Media Workflow Association is
// Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=



#include "CAAFAsyncStreamRawStorage.h"
#include "ImplAAFAsyncStreamRawStorage.h"
#include "AAFResult.h"
#include "CAAFEnumValidation.h"

#include "OMAssertions.h"
#include "OMExceptions.h"

#include <assert.h>
#include <string.h>


// CLSID for AAFAsyncStreamRawStorage 
// {91BEC86C-2C46-432F-BB9D-755EA4FE2347}
EXTERN_C const CLSID CLSID_AAFAsyncStreamRawStorage = { 0x91BEC86C, 0x2C46, 0x432F, { 0xBB, 0x9D, 0x75, 0x5E, 0xA4, 0xFE, 0x23, 0x47 } };






CAAFAsyncStreamRawStorage::CAAFAsyncStreamRawStorage (IUnknown * pControllingUnknown, aafBool doInit)
  : CAAFRandomRawStorage (pControllingUnknown, kAAFFalse)
{
  if (doInit)
    {
      ImplAAFAsyncStreamRawStorage * newRep;
      newRep = new ImplAAFAsyncStreamRawStorage;
      assert (newRep);
      InitRep (newRep);
    }
}


CAAFAsyncStreamRawStorage::~CAAFAsyncStreamRawStorage ()
{
}


HRESULT STDMETHODCALLTYPE
    CAAFAsyncStreamRawStorage::StreamReadAsyncAt (aafUInt64  position,
        aafMemPtr_t  buf,
        aafUInt32  bufSize,
        IAAFIOCompletion *  pCompletion,
        aafMemConstPtr_t  pClientArg)
{
  HRESULT hr;

  ImplAAFAsyncStreamRawStorage * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAsyncStreamRawStorage*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->StreamReadAsyncAt
       (position,
        buf,
        bufSize,
        pCompletion,
        pClientArg);
    }
  catch (OMException& e)
    {
      // OMExceptions should be handled by the impl code. However, if an
      // unhandled OMException occurs, control reaches here. We must not
      // allow the unhandled exception to reach the client code, so we
      // turn it into a failure status code.
      //
      // If the OMException contains an HRESULT, it is returned to the
      // client, if not, AAFRESULT_UHANDLED_EXCEPTION is returned.
      //
      hr = OMExceptionToResult(e, AAFRESULT_UNHANDLED_EXCEPTION);
    }
  catch (OMAssertionViolation &)
    {
      // Control reaches here if there is a programming error in the
      // impl code that was detected by an assertion violation.
      // We must not allow the assertion to reach the client code so
      // here we turn it into a failure status code.
      //
      hr = AAFRESULT_ASSERTION_VIOLATION;
    }
  catch (...)
    {
      // We CANNOT throw an exception out of a COM interface method!
      // Return a reasonable exception code.
      //
      hr = AAFRESULT_UNEXPECTED_EXCEPTION;
    }

  return hr;
}



HRESULT STDMETHODCALLTYPE
    CAAFAsyncStreamRawStorage::StreamWriteAsyncAt (aafUInt64  position,
        aafMemConstPtr_t  buf,
        aafUInt32  bufSize,
        IAAFIOCompletion *  pCompletion,
        aafMemConstPtr_t  pClientArg)
{
  HRESULT hr;

  ImplAAFAsyncStreamRawStorage * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAsyncStreamRawStorage*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->StreamWriteAsyncAt
       (position,
        buf,
        bufSize,
        pCompletion,
        pClientArg);
    }
  catch (OMException& e)
    {
      // OMExceptions should be handled by the impl code. However, if an
      // unhandled OMException occurs, control reaches here. We must not
      // allow the unhandled exception to reach the client code, so we
      // turn it into a failure status code.
      //
      // If the OMException contains an HRESULT, it is returned to the
      // client, if not, AAFRESULT_UHANDLED_EXCEPTION is returned.
      //
      hr = OMExceptionToResult(e, AAFRESULT_UNHANDLED_EXCEPTION);
    }
  catch (OMAssertionViolation &)
    {
      // Control reaches here if there is a programming error in the
      // impl code that was detected by an assertion violation.
      // We must not allow the assertion to reach the client code so
      // here we turn it into a failure status code.
      //
      hr = AAFRESULT_ASSERTION_VIOLATION;
    }
  catch (...)
    {
      // We CANNOT throw an exception out of a COM interface method!
      // Return a reasonable exception code.
      //
      hr = AAFRESULT_UNEXPECTED_EXCEPTION;
    }

  return hr;
}



HRESULT STDMETHODCALLTYPE
    CAAFAsyncStreamRawStorage::StreamReadScatterAsyncAt (aafUInt64  position,
        aafIOBufferDesc_t *  pBufs,
        aafUInt32  bufCount,
        IAAFIOCompletion *  pCompletion,
        aafMemConstPtr_t  pClientArg)
{
  HRESULT hr;

  ImplAAFAsyncStreamRawStorage * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAsyncStreamRawStorage*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->StreamReadScatterAsyncAt
       (position,
        pBufs,
        bufCount,
        pCompletion,
        pClientArg);
    }
  catch (OMException& e)
    {
      // OMExceptions should be handled by the impl code. However, if an
      // unhandled OMException occurs, control reaches here. We must not
      // allow the unhandled exception to reach the client code, so we
      // turn it into a failure status code.
      //
      // If the OMException contains an HRESULT, it is returned to the
      // client, if not, AAFRESULT_UHANDLED_EXCEPTION is returned.
      //
      hr = OMExceptionToResult(e, AAFRESULT_UNHANDLED_EXCEPTION);
    }
  catch (OMAssertionViolation &)
    {
      // Control reaches here if there is a programming error in the
      // impl code that was detected by an assertion violation.
      // We must not allow the assertion to reach the client code so
      // here we turn it into a failure status code.
      //
      hr = AAFRESULT_ASSERTION_VIOLATION;
    }
  catch (...)
    {
      // We CANNOT throw an exception out of a COM interface method!
      // Return a reasonable exception code.
      //
      hr = AAFRESULT_UNEXPECTED_EXCEPTION;
    }

  return hr;
}



HRESULT STDMETHODCALLTYPE
    CAAFAsyncStreamRawStorage::StreamWriteGatherAsyncAt (aafUInt64  position,
        aafIOBufferDesc_constptr  pBufs,
        aafUInt32  bufCount,
        IAAFIOCompletion *  pCompletion,
        aafMemConstPtr_t  pClientArg)
{
  HRESULT hr;

  ImplAAFAsyncStreamRawStorage * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAsyncStreamRawStorage*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->StreamWriteGatherAsyncAt
       (position,
        pBufs,
        bufCount,
        pCompletion,
        pClientArg);
    }
  catch (OMException& e)
    {
      // OMExceptions should be handled by the impl code. However, if an
      // unhandled OMException occurs, control reaches here. We must not
      // allow the unhandled exception to reach the client code, so we
      // turn it into a failure status code.
      //
      // If the OMException contains an HRESULT, it is returned to the
      // client, if not, AAFRESULT_UHANDLED_EXCEPTION is returned.
      //
      hr = OMExceptionToResult(e, AAFRESULT_UNHANDLED_EXCEPTION);
    }
  catch (OMAssertionViolation &)
    {
      // Control reaches here if there is a programming error in the
      // impl code that was detected by an assertion violation.
      // We must not allow the assertion to reach the client code so
      // here we turn it into a failure status code.
      //
      hr = AAFRESULT_ASSERTION_VIOLATION;
    }
  catch (...)
    {
      // We CANNOT throw an exception out of a COM interface method!
      // Return a reasonable exception code.
      //
      hr = AAFRESULT_UNEXPECTED_EXCEPTION;
    }

  return hr;
}



//
// 
// 
inline int EQUAL_UID(const GUID & a, const GUID & b)
{
  return (0 == memcmp((&a), (&b), sizeof (aafUID_t)));
}
HRESULT CAAFAsyncStreamRawStorage::InternalQueryInterface
(
    REFIID riid,
    void **ppvObj)
{
    if (NULL == ppvObj)
        return E_INVALIDARG;

    // We only support the IClassFactory interface 
    if (EQUAL_UID(riid,IID_IAAFAsyncStreamRawStorage)) 
    { 
        *ppvObj = (IAAFAsyncStreamRawStorage *)this; 
        ((IUnknown *)*ppvObj)->AddRef();
        return S_OK;
    }

    // Always delegate back to base implementation.
    return CAAFRandomRawStorage::InternalQueryInterface(riid, ppvObj);
}

//
// Define the contrete object support implementation.
// 
AAF_DEFINE_FACTORY(AAFAsyncStreamRawStorage)

