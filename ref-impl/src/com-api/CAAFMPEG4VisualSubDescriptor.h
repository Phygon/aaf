//@doc
//@class    AAFMPEG4VisualSubDescriptor | Implementation class for AAFMPEG4VisualSubDescriptor
#ifndef __CAAFMPEG4VisualSubDescriptor_h__
#define __CAAFMPEG4VisualSubDescriptor_h__

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





#ifndef __CAAFSubDescriptor_h__
#include "CAAFSubDescriptor.h"
#endif


class CAAFMPEG4VisualSubDescriptor
  : public IAAFMPEG4VisualSubDescriptor,
    public CAAFSubDescriptor
{
protected:

  //********
  //
  // Constructor/destructor
  //
  CAAFMPEG4VisualSubDescriptor (IUnknown * pControllingUnknown, aafBool doInit = kAAFTrue);
  virtual ~CAAFMPEG4VisualSubDescriptor ();

public:


  //***********************************************************
  //
  // Initialize()
  //
  // Initializes a newly allocated, IAAFMPEG4VisualSubDescriptor-supporting
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
  // SetSingleSequence()
  //
  // Set the flag specifying if all configuration information in the essence stream
  /// are identical except vbv_occupancy.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MPEG4VisualSingleSequence property will not be
  /// changed.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  STDMETHOD (SetSingleSequence) (
    // True if all configuration information in the essence stream are identical except vbv_occupancy. False if there are differences among configuration information within the Essence stream except vbv_occupancy. 
    /*[in]*/ aafBoolean_t  singleSequence);


  //***********************************************************
  //
  // GetSingleSequence()
  //
  // Get the flag specifying if all configuration information in the essence stream
  /// are identical except vbv_occupancy.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pSingleSequence pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pSingleSequence.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - If pSingleSequence arg is NULL.
  //
  STDMETHOD (GetSingleSequence) (
    // True if all configuration information in the essence stream are identical except vbv_occupancy. False if there are differences among configuration information within the Essence stream except vbv_occupancy. 
    /*[out]*/ aafBoolean_t *  pSingleSequence);


  //***********************************************************
  //
  // SetConstantBVOPs()
  //
  // Set the flag specifying if the number of B-VOPs is always constant.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MPEG4VisualConstantBVOPs property will not be
  /// changed.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  STDMETHOD (SetConstantBVOPs) (
    // True if the number of B-VOPs is always constant. 
    /*[in]*/ aafBoolean_t  constantBVOPs);


  //***********************************************************
  //
  // GetConstantBVOPs()
  //
  // Get the flag specifying if the number of B-VOPs is always constant.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pConstantBVOPs pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pConstantBVOPs.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - If pConstantBVOPs arg is NULL.
  //
  STDMETHOD (GetConstantBVOPs) (
    // True if the number of B-VOPs is always constant. 
    /*[out]*/ aafBoolean_t *  pConstantBVOPs);


  //***********************************************************
  //
  // SetCodedContentType()
  //
  // Set coded content kind.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MPEG4VisualCodedContentType property will not be
  /// changed.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  STDMETHOD (SetCodedContentType) (
    // coded content kind. 
    /*[in]*/ aafMPEG4VisualCodedContentType_t  codedContentType);


  //***********************************************************
  //
  // GetCodedContentType()
  //
  // Get coded content kind.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pCodedContentType pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pCodedContentType.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - If pCodedContentType arg is NULL.
  //
  STDMETHOD (GetCodedContentType) (
    // coded content kind. 
    /*[out]*/ aafMPEG4VisualCodedContentType_t *  pCodedContentType);


  //***********************************************************
  //
  // SetLowDelay()
  //
  // Set the flag specifying if the VOL contains no B-VOPs.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MPEG4VisualLowDelay property will not be
  /// changed.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  STDMETHOD (SetLowDelay) (
    // True if the VOL contains no B-VOPs. 
    /*[in]*/ aafBoolean_t  lowDelay);


  //***********************************************************
  //
  // GetLowDelay()
  //
  // Get the flag specifying if the VOL contains no B-VOPs.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pLowDelay pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pLowDelay.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - If pLowDelay arg is NULL.
  //
  STDMETHOD (GetLowDelay) (
    // True if the VOL contains no B-VOPs. 
    /*[out]*/ aafBoolean_t *  pLowDelay);


  //***********************************************************
  //
  // SetClosedGOV()
  //
  // Set the flag specifying if closed_gov is set in all GOV headers.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MPEG4VisualClosedGOV property will not be
  /// changed.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  STDMETHOD (SetClosedGOV) (
    // True if closed_gov is set in all GOV headers. 
    /*[in]*/ aafBoolean_t  closedGOV);


  //***********************************************************
  //
  // GetClosedGOV()
  //
  // Get the flag specifying if closed_gov is set in all GOV headers.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pClosedGOV pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pClosedGOV.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - If pClosedGOV arg is NULL.
  //
  STDMETHOD (GetClosedGOV) (
    // True if closed_gov is set in all GOV headers. 
    /*[out]*/ aafBoolean_t *  pClosedGOV);


  //***********************************************************
  //
  // SetIdenticalGOV()
  //
  // Set the flag specifying if every GOV in the sequence is constructed the same.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MPEG4VisualIdenticalGOV property will not be
  /// changed.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  STDMETHOD (SetIdenticalGOV) (
    // True if every GOV in the sequence is constructed the same. 
    /*[in]*/ aafBoolean_t  identicalGOV);


  //***********************************************************
  //
  // GetIdenticalGOV()
  //
  // Get the flag specifying if every GOV in the sequence is constructed the same.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pIdenticalGOV pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pIdenticalGOV.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - If pIdenticalGOV arg is NULL.
  //
  STDMETHOD (GetIdenticalGOV) (
    // True if every GOV in the sequence is constructed the same. 
    /*[out]*/ aafBoolean_t *  pIdenticalGOV);


  //***********************************************************
  //
  // SetMaxGOV()
  //
  // Set the maximum occurring spacing between I frames.
  /// A value of 0 or the absence of this property implies no limit to
  // the maximum GOV or the maximum GOV is unknown.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MPEG4VisualMaxGOV property will not be
  /// changed.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  STDMETHOD (SetMaxGOV) (
    // The maximum occurring spacing between I frames. 
    /*[in]*/ aafUInt16  maxGOV);


  //***********************************************************
  //
  // GetMaxGOV()
  //
  // Get the maximum occurring spacing between I frames.
  /// A value of 0 or the absence of this property implies no limit to
  // the maximum GOV or the maximum GOV is unknown.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pMaxGOV pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pMaxGOV.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - If pMaxGOV arg is NULL.
  //
  STDMETHOD (GetMaxGOV) (
    // The maximum occurring spacing between I frames. 
    /*[out]*/ aafUInt16 *  pMaxGOV);


  //***********************************************************
  //
  // SetBVOPCount()
  //
  // Set the maximum occurring spacing between I frames.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MPEG4VisualBVOPCount property will not be
  /// changed.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  STDMETHOD (SetBVOPCount) (
    // The maximum number of B-VOPs between P or I-VOPs. 
    /*[in]*/ aafUInt16  bvopCount);


  //***********************************************************
  //
  // GetBVOPCount()
  //
  // Get the maximum occurring spacing between I frames.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pBVOPCount pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pBVOPCount.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - If pBVOPCount arg is NULL.
  //
  STDMETHOD (GetBVOPCount) (
    // The maximum number of B-VOPs between P or I-VOPs. 
    /*[out]*/ aafUInt16 *  pBVOPCount);


  //***********************************************************
  //
  // SetBitRate()
  //
  // Set the maximum bit rate of the MPEG-4 Visual stream in bits per second.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MPEG4VisualBitRate property will not be
  /// changed.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  STDMETHOD (SetBitRate) (
    // The maximum bit rate of the MPEG-4 Visual stream. 
    /*[in]*/ aafUInt32  bitRate);


  //***********************************************************
  //
  // GetBitRate()
  //
  // Get the maximum bit rate of the MPEG-4 Visual stream in bits per second.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pBitRate pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pBitRate.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - If pBitRate arg is NULL.
  //
  STDMETHOD (GetBitRate) (
    // The maximum bit rate of the MPEG-4 Visual stream. 
    /*[out]*/ aafUInt32 *  pBitRate);


  //***********************************************************
  //
  // SetProfileAndLevel()
  //
  // Set the MPEG-4 visual profile and level.
  /// The meaning of the bits is given in Table G.1 of ISO/IEC 14496-2.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MPEG4VisualProfileAndLevel property will not be
  /// changed.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  STDMETHOD (SetProfileAndLevel) (
    // The MPEG-4 visual profile and level. 
    /*[in]*/ aafUInt8  profileAndLevel);


  //***********************************************************
  //
  // GetProfileAndLevel()
  //
  // Get the MPEG-4 visual profile and level.
  /// The meaning of the bits is given in Table G.1 of ISO/IEC 14496-2.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pProfileAndLevel pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pProfileAndLevel.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NOT_INITIALIZED
  //   - This object has not yet had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - If pProfileAndLevel arg is NULL.
  //
  STDMETHOD (GetProfileAndLevel) (
    // The MPEG-4 visual profile and level. 
    /*[out]*/ aafUInt8 *  pProfileAndLevel);



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

#endif // ! __CAAFMPEG4VisualSubDescriptor_h__


