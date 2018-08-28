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



#include "CAAFAudioChannelLabelSubDescriptor.h"
#include "ImplAAFAudioChannelLabelSubDescriptor.h"
#include "AAFResult.h"
#include "CAAFEnumValidation.h"

#include "OMAssertions.h"
#include "OMExceptions.h"

#include <assert.h>
#include <string.h>


// CLSID for AAFAudioChannelLabelSubDescriptor 
// {9A0906EC-32DE-4384-9242-1775D3D389CF}
EXTERN_C const CLSID CLSID_AAFAudioChannelLabelSubDescriptor = { 0x9A0906EC, 0x32DE, 0x4384, { 0x92, 0x42, 0x17, 0x75, 0xD3, 0xD3, 0x89, 0xCF } };





CAAFAudioChannelLabelSubDescriptor::CAAFAudioChannelLabelSubDescriptor (IUnknown * pControllingUnknown, aafBool doInit)
  : CAAFMCALabelSubDescriptor (pControllingUnknown, kAAFFalse)
{
  if (doInit)
    {
      ImplAAFAudioChannelLabelSubDescriptor * newRep;
      newRep = new ImplAAFAudioChannelLabelSubDescriptor;
      assert (newRep);
      InitRep (newRep);
    }
}


CAAFAudioChannelLabelSubDescriptor::~CAAFAudioChannelLabelSubDescriptor ()
{
}


HRESULT STDMETHODCALLTYPE
    CAAFAudioChannelLabelSubDescriptor::Initialize (aafUID_constref  dictionaryID,
        aafUID_constref  linkID,
        aafCharacter_constptr  pTagSymbol)
{
  HRESULT hr;

  ImplAAFAudioChannelLabelSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAudioChannelLabelSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->Initialize
       (dictionaryID,
        linkID,
        pTagSymbol);
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
    CAAFAudioChannelLabelSubDescriptor::SetSoundfieldGroupLinkID (aafUID_constref  linkID)
{
  HRESULT hr;

  ImplAAFAudioChannelLabelSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAudioChannelLabelSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetSoundfieldGroupLinkID
       (linkID);
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
    CAAFAudioChannelLabelSubDescriptor::GetSoundfieldGroupLinkID (aafUID_t *  pLinkID)
{
  HRESULT hr;

  ImplAAFAudioChannelLabelSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAudioChannelLabelSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetSoundfieldGroupLinkID
       (pLinkID);
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
HRESULT CAAFAudioChannelLabelSubDescriptor::InternalQueryInterface
(
    REFIID riid,
    void **ppvObj)
{
    if (NULL == ppvObj)
        return E_INVALIDARG;

    // We only support the IClassFactory interface 
    if (EQUAL_UID(riid,IID_IAAFAudioChannelLabelSubDescriptor)) 
    { 
        *ppvObj = (IAAFAudioChannelLabelSubDescriptor *)this; 
        ((IUnknown *)*ppvObj)->AddRef();
        return S_OK;
    }

    // Always delegate back to base implementation.
    return CAAFMCALabelSubDescriptor::InternalQueryInterface(riid, ppvObj);
}

//
// Define the contrete object support implementation.
// 
AAF_DEFINE_FACTORY(AAFAudioChannelLabelSubDescriptor)

