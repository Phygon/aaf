//@doc
//@class    AAFMPEGAudioDescriptor | Implementation class for AAFMPEGAudioDescriptor
#ifndef __CAAFMPEGAudioDescriptor_h__
#define __CAAFMPEGAudioDescriptor_h__

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



#ifndef __AAF_h__
#include "AAF.h"
#endif







#ifndef __CAAFSoundDescriptor_h__
#include "CAAFSoundDescriptor.h"
#endif


class CAAFMPEGAudioDescriptor
  : public IAAFMPEGAudioDescriptor,
    public CAAFSoundDescriptor
{
protected:

  //********
  //
  // Constructor/destructor
  //
  CAAFMPEGAudioDescriptor (IUnknown * pControllingUnknown, aafBool doInit = kAAFTrue);
  virtual ~CAAFMPEGAudioDescriptor ();

public:




  //***********************************************************
  //
  // Initialize()
  //
  // Initializes a newly allocated, IAAFMPEGAudioDescriptor-supporting
  /// object. This method must be called after allocation, and before
  /// any other method can be called.
  ///
  /// Succeeds if:
  /// - Initialize() has not yet been called on this object.
  ///
  /// This method will return the following codes.  If more than one of
  /// the listed errors is in effect, it will return the first one
  /// encountered in the order given below:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_ALREADY_INITIALIZED
  ///   - Initialize() has already been called on this object.
  //
  STDMETHOD (Initialize)
     ();



  //***********************************************************
  //
  // SetMPEGAudioBitRate()
  //
  // Sets the MPEGAudioBitRate property. This is an optional property.
  ///
  /// If this method fails, the MPEGAudioBitRate property will not be changed.
  ///
  /// This method will return the following codes:
  ///
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  //
  STDMETHOD (SetMPEGAudioBitRate) (
    // value to assign to the MPEGAudioBitRate property 
    /*[in]*/ aafUInt32  bitRate);


  //***********************************************************
  //
  // GetMPEGAudioBitRate()
  //
  // Gets the MPEGAudioBitRate property.
  ///
  /// Succeeds if all of the following are true:
  /// - pBitRate is a valid pointer
  /// - the property is present.
  ///
  /// If this method fails, pBitRate will not be changed.
  ///
  /// This method will return the following codes:
  ///
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pBitRate is NULL.
  ///
  /// AAFRESULT_PROP_NOT_PRESENT
  ///   - the property is not present.
  //
  STDMETHOD (GetMPEGAudioBitRate) (
    // value of the MPEGAudioBitRate property 
    /*[out]*/ aafUInt32 *  pBitRate);



protected:
  // 
  // Declare the QI that implements for the interfaces
  // for this module. This will be called by CAAFUnknown::QueryInterface().
  // 
  STDMETHOD(InternalQueryInterface)(REFIID riid, void **ppvObjOut);


public:
  //
  // This class as concrete. All AAF objects can be constructed from
  // a CLSID. This will allow subclassing all "base-classes" by
  // aggreggation.
  // 
  AAF_DECLARE_CONCRETE();
  //
  //********
};

#endif // ! __CAAFMPEGAudioDescriptor_h__


