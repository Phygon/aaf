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



#include "CAAFJPEG2000SubDescriptor.h"
#include "ImplAAFJPEG2000SubDescriptor.h"
#include "AAFResult.h"
#include "CAAFEnumValidation.h"

#include "OMAssertions.h"
#include "OMExceptions.h"

#include <assert.h>
#include <string.h>


// CLSID for AAFJPEG2000SubDescriptor 
// {9AFD3B8D-4A20-4a4f-9D52-BCC14D1B7A7B}
EXTERN_C const CLSID CLSID_AAFJPEG2000SubDescriptor = { 0x9AFD3B8D, 0x4A20, 0x4a4f, { 0x9D, 0x52, 0xBC, 0xC1, 0x4D, 0x1B, 0x7A, 0x7B } };





CAAFJPEG2000SubDescriptor::CAAFJPEG2000SubDescriptor (IUnknown * pControllingUnknown, aafBool doInit)
  : CAAFSubDescriptor (pControllingUnknown, kAAFFalse)
{
  if (doInit)
    {
      ImplAAFJPEG2000SubDescriptor * newRep;
      newRep = new ImplAAFJPEG2000SubDescriptor;
      assert (newRep);
      InitRep (newRep);
    }
}


CAAFJPEG2000SubDescriptor::~CAAFJPEG2000SubDescriptor ()
{
}

HRESULT STDMETHODCALLTYPE
    CAAFJPEG2000SubDescriptor::Initialize ()
{
  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
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
    CAAFJPEG2000SubDescriptor::SetRsiz (aafUInt16  rsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetRsiz
       (rsiz);
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
    CAAFJPEG2000SubDescriptor::GetRsiz (aafUInt16 *  pRsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetRsiz
       (pRsiz);
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
    CAAFJPEG2000SubDescriptor::SetXsiz (aafUInt32  xsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetXsiz
       (xsiz);
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
    CAAFJPEG2000SubDescriptor::GetXsiz (aafUInt32 *  pXsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetXsiz
       (pXsiz);
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
    CAAFJPEG2000SubDescriptor::SetYsiz (aafUInt32  ysiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetYsiz
       (ysiz);
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
    CAAFJPEG2000SubDescriptor::GetYsiz (aafUInt32 *  pYsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetYsiz
       (pYsiz);
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
    CAAFJPEG2000SubDescriptor::SetXOsiz (aafUInt32  xosiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetXOsiz
       (xosiz);
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
    CAAFJPEG2000SubDescriptor::GetXOsiz (aafUInt32 *  pXOsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetXOsiz
       (pXOsiz);
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
    CAAFJPEG2000SubDescriptor::SetYOsiz (aafUInt32  yosiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetYOsiz
       (yosiz);
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
    CAAFJPEG2000SubDescriptor::GetYOsiz (aafUInt32 *  pYOsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetYOsiz
       (pYOsiz);
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
    CAAFJPEG2000SubDescriptor::SetXTsiz (aafUInt32  xtsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetXTsiz
       (xtsiz);
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
    CAAFJPEG2000SubDescriptor::GetXTsiz (aafUInt32 *  pXTsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetXTsiz
       (pXTsiz);
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
    CAAFJPEG2000SubDescriptor::SetYTsiz (aafUInt32  ytsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetYTsiz
       (ytsiz);
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
    CAAFJPEG2000SubDescriptor::GetYTsiz (aafUInt32 *  pYTsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetYTsiz
       (pYTsiz);
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
    CAAFJPEG2000SubDescriptor::SetXTOsiz (aafUInt32  xtosiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetXTOsiz
       (xtosiz);
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
    CAAFJPEG2000SubDescriptor::GetXTOsiz (aafUInt32 *  pXTOsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetXTOsiz
       (pXTOsiz);
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
    CAAFJPEG2000SubDescriptor::SetYTOsiz (aafUInt32  ytosiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetYTOsiz
       (ytosiz);
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
    CAAFJPEG2000SubDescriptor::GetYTOsiz (aafUInt32 *  pYTOsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetYTOsiz
       (pYTOsiz);
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
    CAAFJPEG2000SubDescriptor::SetCsiz (aafUInt16  csiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetCsiz
       (csiz);
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
    CAAFJPEG2000SubDescriptor::GetCsiz (aafUInt16 *  pCsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetCsiz
       (pCsiz);
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
    CAAFJPEG2000SubDescriptor::SetComponentSsizAt (aafUInt16  index,
        aafUInt8  ssiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetComponentSsizAt
       (index,
        ssiz);
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
    CAAFJPEG2000SubDescriptor::GetComponentSsizAt (aafUInt16  index,
        aafUInt8 *  pSsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetComponentSsizAt
       (index,
        pSsiz);
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
    CAAFJPEG2000SubDescriptor::SetComponentXRsizAt (aafUInt16  index,
        aafUInt8  ssiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetComponentXRsizAt
       (index,
        ssiz);
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
    CAAFJPEG2000SubDescriptor::GetComponentXRsizAt (aafUInt16  index,
        aafUInt8 *  pXRsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetComponentXRsizAt
       (index,
        pXRsiz);
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
    CAAFJPEG2000SubDescriptor::SetComponentYRsizAt (aafUInt16  index,
        aafUInt8  ssiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetComponentYRsizAt
       (index,
        ssiz);
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
    CAAFJPEG2000SubDescriptor::GetComponentYRsizAt (aafUInt16  index,
        aafUInt8 *  pYRsiz)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetComponentYRsizAt
       (index,
        pYRsiz);
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
    CAAFJPEG2000SubDescriptor::SetCodingStyleDefault (aafUInt32  valueSize,
        aafDataBuffer_t  pValue)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetCodingStyleDefault
       (valueSize,
        pValue);
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
    CAAFJPEG2000SubDescriptor::GetCodingStyleDefaultBufLen (aafUInt32 *  pSizeOfBuffer)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetCodingStyleDefaultBufLen
       (pSizeOfBuffer);
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
    CAAFJPEG2000SubDescriptor::GetCodingStyleDefault (aafUInt32  valueSize,
        aafDataBuffer_t  pValue)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetCodingStyleDefault
       (valueSize,
        pValue);
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
    CAAFJPEG2000SubDescriptor::SetQuantizationDefault (aafUInt32  valueSize,
        aafDataBuffer_t  pValue)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->SetQuantizationDefault
       (valueSize,
        pValue);
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
    CAAFJPEG2000SubDescriptor::GetQuantizationDefaultBufLen (aafUInt32 *  pSizeOfBuffer)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetQuantizationDefaultBufLen
       (pSizeOfBuffer);
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
    CAAFJPEG2000SubDescriptor::GetQuantizationDefault (aafUInt32  valueSize,
        aafDataBuffer_t  pValue)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->GetQuantizationDefault
       (valueSize,
        pValue);
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
    CAAFJPEG2000SubDescriptor::SetJ2CLayout (aafUInt32  numberElements,
        aafRGBAComponent_constptr  pJ2CLayoutArray)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);



  try
    {
      hr = ptr->SetJ2CLayout (numberElements,
    pJ2CLayoutArray);
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
    CAAFJPEG2000SubDescriptor::CountJ2CLayoutElements (aafUInt32 *  pResult)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);


  try
    {
      hr = ptr->CountJ2CLayoutElements (pResult);
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
    CAAFJPEG2000SubDescriptor::GetJ2CLayout (aafUInt32  numberElements,
        aafRGBAComponent_t*  pJ2CLayoutArray)
{
  HRESULT hr;

  ImplAAFJPEG2000SubDescriptor * ptr;
  ImplAAFRoot * pO;
  pO = GetRepObject ();
  assert (pO);
  ptr = static_cast<ImplAAFJPEG2000SubDescriptor*> (pO);
  assert (ptr);



  try
    {
      hr = ptr->GetJ2CLayout (numberElements,
    pJ2CLayoutArray);
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
HRESULT CAAFJPEG2000SubDescriptor::InternalQueryInterface
(
    REFIID riid,
    void **ppvObj)
{
    if (NULL == ppvObj)
        return E_INVALIDARG;

    // We only support the IClassFactory interface 
    if (EQUAL_UID(riid,IID_IAAFJPEG2000SubDescriptor)) 
    { 
        *ppvObj = (IAAFJPEG2000SubDescriptor *)this; 
        ((IUnknown *)*ppvObj)->AddRef();
        return S_OK;
    }

    if (EQUAL_UID(riid,IID_IAAFJPEG2000SubDescriptor2)) 
    { 
        *ppvObj = (IAAFJPEG2000SubDescriptor2 *)this; 
        ((IUnknown *)*ppvObj)->AddRef();
        return S_OK;
    }

    // Always delegate back to base implementation.
    return CAAFSubDescriptor::InternalQueryInterface(riid, ppvObj);
}

//
// Define the contrete object support implementation.
// 
AAF_DEFINE_FACTORY(AAFJPEG2000SubDescriptor)
