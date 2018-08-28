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



#include "CAAFAVCSubDescriptor.h"
#include "ImplAAFAVCSubDescriptor.h"
#include "AAFResult.h"
#include "CAAFEnumValidation.h"

#include "OMAssertions.h"
#include "OMExceptions.h"

#include <assert.h>
#include <string.h>


// CLSID for AAFAVCSubDescriptor 
// {70B8009A-DCCE-499B-B08A-3FA387304E5D}
EXTERN_C const CLSID CLSID_AAFAVCSubDescriptor = { 0x70B8009A, 0xDCCE, 0x499B, { 0xB0, 0x8A, 0x3F, 0xA3, 0x87, 0x30, 0x4E, 0x5D } };





CAAFAVCSubDescriptor::CAAFAVCSubDescriptor (IUnknown * pControllingUnknown, aafBool doInit)
  : CAAFSubDescriptor (pControllingUnknown, kAAFFalse)
{
  if (doInit)
    {
      ImplAAFAVCSubDescriptor * newRep;
      newRep = new ImplAAFAVCSubDescriptor;
      assert (newRep);
      InitRep (newRep);
    }
}


CAAFAVCSubDescriptor::~CAAFAVCSubDescriptor ()
{
}


HRESULT STDMETHODCALLTYPE
    CAAFAVCSubDescriptor::Initialize ()
{
  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);
  HRESULT hr;

  try
    {
      hr = ptr->Initialize();
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
    CAAFAVCSubDescriptor::SetDecodingDelay (aafUInt8  decodingDelay)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetDecodingDelay
       (decodingDelay);
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
    CAAFAVCSubDescriptor::GetDecodingDelay (aafUInt8 *  pDecodingDelay)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetDecodingDelay
       (pDecodingDelay);
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
    CAAFAVCSubDescriptor::SetConstantBPictureFlag (aafBoolean_t  constantBPictureFlag)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetConstantBPictureFlag
       (constantBPictureFlag);
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
    CAAFAVCSubDescriptor::GetConstantBPictureFlag (aafBoolean_t *  pConstantBPictureFlag)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetConstantBPictureFlag
       (pConstantBPictureFlag);
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
    CAAFAVCSubDescriptor::SetCodedContentKind (aafAVCContentScanningType_t  codedContentKind)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetCodedContentKind
       (codedContentKind);
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
    CAAFAVCSubDescriptor::GetCodedContentKind (aafAVCContentScanningType_t *  pCodedContentKind)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetCodedContentKind
       (pCodedContentKind);
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
    CAAFAVCSubDescriptor::SetClosedGOPIndicator (aafBoolean_t  closedGOPIndicator)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetClosedGOPIndicator
       (closedGOPIndicator);
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
    CAAFAVCSubDescriptor::GetClosedGOPIndicator (aafBoolean_t *  pClosedGOPIndicator)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetClosedGOPIndicator
       (pClosedGOPIndicator);
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
    CAAFAVCSubDescriptor::SetIdenticalGOPIndicator (aafBoolean_t  identicalGOPIndicator)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetIdenticalGOPIndicator
       (identicalGOPIndicator);
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
    CAAFAVCSubDescriptor::GetIdenticalGOPIndicator (aafBoolean_t *  pIdenticalGOPIndicator)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetIdenticalGOPIndicator
       (pIdenticalGOPIndicator);
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
    CAAFAVCSubDescriptor::SetMaximumGOPSize (aafUInt16  maximumGOPSize)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetMaximumGOPSize
       (maximumGOPSize);
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
    CAAFAVCSubDescriptor::GetMaximumGOPSize (aafUInt16 *  pMaximumGOPSize)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetMaximumGOPSize
       (pMaximumGOPSize);
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
    CAAFAVCSubDescriptor::SetMaximumBPictureCount (aafUInt16  maximumBPictureCount)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetMaximumBPictureCount
       (maximumBPictureCount);
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
    CAAFAVCSubDescriptor::GetMaximumBPictureCount (aafUInt16 *  pMaximumBPictureCount)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetMaximumBPictureCount
       (pMaximumBPictureCount);
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
    CAAFAVCSubDescriptor::SetMaximumBitRate (aafUInt32  maximumBitRate)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetMaximumBitRate
       (maximumBitRate);
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
    CAAFAVCSubDescriptor::GetMaximumBitRate (aafUInt32 *  pMaximumBitRate)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetMaximumBitRate
       (pMaximumBitRate);
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
    CAAFAVCSubDescriptor::SetAverageBitRate (aafUInt32  averageBitRate)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetAverageBitRate
       (averageBitRate);
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
    CAAFAVCSubDescriptor::GetAverageBitRate (aafUInt32 *  pAverageBitRate)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetAverageBitRate
       (pAverageBitRate);
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
    CAAFAVCSubDescriptor::SetProfile (aafUInt8  profile)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetProfile
       (profile);
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
    CAAFAVCSubDescriptor::GetProfile (aafUInt8 *  pProfile)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetProfile
       (pProfile);
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
    CAAFAVCSubDescriptor::SetProfileConstraint (aafUInt8  profileConstraint)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetProfileConstraint
       (profileConstraint);
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
    CAAFAVCSubDescriptor::GetProfileConstraint (aafUInt8 *  pProfileConstraint)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetProfileConstraint
       (pProfileConstraint);
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
    CAAFAVCSubDescriptor::SetLevel (aafUInt8  level)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetLevel
       (level);
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
    CAAFAVCSubDescriptor::GetLevel (aafUInt8 *  pLevel)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetLevel
       (pLevel);
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
    CAAFAVCSubDescriptor::SetMaximumRefFrames (aafUInt8  maximumRefFrames)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetMaximumRefFrames
       (maximumRefFrames);
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
    CAAFAVCSubDescriptor::GetMaximumRefFrames (aafUInt8 *  pMaximumRefFrames)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetMaximumRefFrames
       (pMaximumRefFrames);
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
    CAAFAVCSubDescriptor::SetSequenceParameterSetFlag (aafUInt8  sequenceParameterSetFlag)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetSequenceParameterSetFlag
       (sequenceParameterSetFlag);
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
    CAAFAVCSubDescriptor::GetSequenceParameterSetFlag (aafUInt8 *  pSequenceParameterSetFlag)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetSequenceParameterSetFlag
       (pSequenceParameterSetFlag);
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
    CAAFAVCSubDescriptor::SetPictureParameterSetFlag (aafUInt8  pictureParameterSetFlag)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetPictureParameterSetFlag
       (pictureParameterSetFlag);
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
    CAAFAVCSubDescriptor::GetPictureParameterSetFlag (aafUInt8 *  pPictureParameterSetFlag)
{
  HRESULT hr;

  ImplAAFAVCSubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFAVCSubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetPictureParameterSetFlag
       (pPictureParameterSetFlag);
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
HRESULT CAAFAVCSubDescriptor::InternalQueryInterface
(
    REFIID riid,
    void **ppvObj)
{
    if (NULL == ppvObj)
        return E_INVALIDARG;

    // We only support the IClassFactory interface 
    if (EQUAL_UID(riid,IID_IAAFAVCSubDescriptor)) 
    { 
        *ppvObj = (IAAFAVCSubDescriptor *)this; 
        ((IUnknown *)*ppvObj)->AddRef();
        return S_OK;
    }

    // Always delegate back to base implementation.
    return CAAFSubDescriptor::InternalQueryInterface(riid, ppvObj);
}

//
// Define the contrete object support implementation.
// 
AAF_DEFINE_FACTORY(AAFAVCSubDescriptor)

