//@doc
//@class    AAFAVCSubDescriptor | Implementation class for AAFAVCSubDescriptor
#ifndef __CAAFAVCSubDescriptor_h__
#define __CAAFAVCSubDescriptor_h__

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


class CAAFAVCSubDescriptor
  : public IAAFAVCSubDescriptor,
    public CAAFSubDescriptor
{
protected:

  //********
  //
  // Constructor/destructor
  //
  CAAFAVCSubDescriptor (IUnknown * pControllingUnknown, aafBool doInit = kAAFTrue);
  virtual ~CAAFAVCSubDescriptor ();

public:


  //***********************************************************
  //
  // Initialize()
  //
  // Initializes a newly allocated, IAAFAVCSubDescriptor-supporting
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
  // SetDecodingDelay()
  //
  // Set the delay required for decoded pictures in number of access units.
  /// The value is given by the presentation time of the first presented
  /// picture in a GOP minus the decoding time of the first decoded picture
  /// in the GOP.
  /// The value shall be set to zero if there are no B Pictures in the essence
  /// stream.
  /// The value shall be set to FFh if the delay is unknown.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCDecodingDelay property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetDecodingDelay) (
    // The delay required for decoded pictures in number of access units. 
    /*[in]*/ aafUInt8  decodingDelay);


  //***********************************************************
  //
  // GetDecodingDelay()
  //
  // Get the delay required for decoded pictures in number of access units.
  /// The value is the presentation time of the first presented picture in
  /// a GOP minus the decoding time of the first decoded picture in the GOP.
  /// The value is zero if there are no B Pictures in the essence stream.
  /// The value is FFh if the delay is unknown.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pDecodingDelay pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pDecodingDelay.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pDecodingDelay arg is NULL.
  //
  STDMETHOD (GetDecodingDelay) (
    // The delay required for decoded pictures in number of access units. 
    /*[out]*/ aafUInt8 *  pDecodingDelay);



  //***********************************************************
  //
  // SetConstantBPictureFlag()
  //
  // Set the flag specifying if the number of the consecutive B Pictures
  /// is always constant.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCConstantBPictureFlag property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetConstantBPictureFlag) (
    // True if the number of the consecutive B Pictures is always constant; false if it is not constant or is unknown. 
    /*[in]*/ aafBoolean_t  constantBPictureFlag);


  //***********************************************************
  //
  // GetConstantBPictureFlag()
  //
  // Get the flag specifying if the number of the consecutive B Pictures
  /// is always constant.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pConstantBPictureFlag pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pConstantBPictureFlag.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pConstantBPictureFlag arg is NULL.
  //
  STDMETHOD (GetConstantBPictureFlag) (
    // True if the number of the consecutive B Pictures is always constant; false if it is not constant or is unknown. 
    /*[out]*/ aafBoolean_t *  pConstantBPictureFlag);



  //***********************************************************
  //
  // SetCodedContentKind()
  //
  // Set coded content kind.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCCodedContentKind property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetCodedContentKind) (
    // coded content kind. 
    /*[in]*/ aafAVCContentScanningType_t  codedContentKind);


  //***********************************************************
  //
  // GetCodedContentKind()
  //
  // Get coded content kind.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pCodedContentKind pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pCodedContentKind.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pCodedContentKind arg is NULL.
  //
  STDMETHOD (GetCodedContentKind) (
    // coded content kind. 
    /*[out]*/ aafAVCContentScanningType_t *  pCodedContentKind);



  //***********************************************************
  //
  // SetClosedGOPIndicator()
  //
  // Set the closed GOP indicator.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCClosedGOPIndicator property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetClosedGOPIndicator) (
    // True if all GOPs are started with an IDR Picture; false otherwise or if the information is not available. 
    /*[in]*/ aafBoolean_t  closedGOPIndicator);


  //***********************************************************
  //
  // GetClosedGOPIndicator()
  //
  // Set the closed GOP indicator.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pClosedGOPIndicator pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pClosedGOPIndicator.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pClosedGOPIndicator arg is NULL.
  //
  STDMETHOD (GetClosedGOPIndicator) (
    // True if all GOPs are started with an IDR Picture; false otherwise or if the information is not available. 
    /*[out]*/ aafBoolean_t *  pClosedGOPIndicator);



  //***********************************************************
  //
  // SetIdenticalGOPIndicator()
  //
  // Set identical GOP indicator.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCIdenticalGOPIndicator property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetIdenticalGOPIndicator) (
    // True if every GOP in has the same number of pictures and the same types of pictures in the same order; false otherwise or if the information is not available. 
    /*[in]*/ aafBoolean_t  identicalGOPIndicator);


  //***********************************************************
  //
  // GetIdenticalGOPIndicator()
  //
  // Get identical GOP indicator.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pIdenticalGOPIndicator pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pIdenticalGOPIndicator.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pIdenticalGOPIndicator arg is NULL.
  //
  STDMETHOD (GetIdenticalGOPIndicator) (
    // True if every GOP in has the same number of pictures and the same types of pictures in the same order; false otherwise or if the information is not available. 
    /*[out]*/ aafBoolean_t *  pIdenticalGOPIndicator);



  //***********************************************************
  //
  // SetMaximumGOPSize()
  //
  // Set the maximum occurring spacing between I Pictures.
  /// A value of 0 or the absence of this property indicates either there
  /// is no limit to the maximum GOP or the maximum GOP is unknown.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCMaximumGOPSize property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetMaximumGOPSize) (
    // maximum GOP size. 
    /*[in]*/ aafUInt16  maximumGOPSize);


  //***********************************************************
  //
  // GetMaximumGOPSize()
  //
  // Get the maximum occurring spacing between I Pictures.
  /// A value of 0 or the absence of this property indicates either there
  /// is no limit to the maximum GOP or the maximum GOP is unknown.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pMaximumGOPSize pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pMaximumGOPSize.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pMaximumGOPSize arg is NULL.
  //
  STDMETHOD (GetMaximumGOPSize) (
    // maximum GOP size. 
    /*[out]*/ aafUInt16 *  pMaximumGOPSize);



  //***********************************************************
  //
  // SetMaximumBPictureCount()
  //
  // Set the maximum number of B Pictures between P or I Pictures.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCMaximumBPictureCount property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetMaximumBPictureCount) (
    // maximum B Picture count. 
    /*[in]*/ aafUInt16  maximumBPictureCount);


  //***********************************************************
  //
  // GetMaximumBPictureCount()
  //
  // Get the maximum number of B Pictures between P or I Pictures.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pMaximumBPictureCount pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pMaximumBPictureCount.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pMaximumBPictureCount arg is NULL.
  //
  STDMETHOD (GetMaximumBPictureCount) (
    // maximum B Picture count. 
    /*[out]*/ aafUInt16 *  pMaximumBPictureCount);



  //***********************************************************
  //
  // SetMaximumBitRate()
  //
  // Set the maximum bit rate of the AVC stream in bit/s is given by
  /// bit_rate_scale and bit_rate_value_minus1 in the HRD parameters
  /// in the Sequence Parameter Set. The equivalent value is assigned
  /// for this property of the stream even if the stream does not
  /// include the HRD parameters.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCMaximumBitRate property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetMaximumBitRate) (
    // maximum bit rate. 
    /*[in]*/ aafUInt32  maximumBitRate);


  //***********************************************************
  //
  // GetMaximumBitRate()
  //
  // Get the maximum bit rate of the AVC stream in bit/s.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pMaximumBitRate pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pMaximumBitRate.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pMaximumBitRate arg is NULL.
  //
  STDMETHOD (GetMaximumBitRate) (
    // maximum bit rate. 
    /*[out]*/ aafUInt32 *  pMaximumBitRate);



  //***********************************************************
  //
  // SetAverageBitRate()
  //
  // Set the average bitrate of the AVC stream in bit/s over the entire
  /// AVC bitstream.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCAverageBitRate property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetAverageBitRate) (
    // Average bit rate. 
    /*[in]*/ aafUInt32  averageBitRate);


  //***********************************************************
  //
  // GetAverageBitRate()
  //
  // Get the average bitrate of the AVC stream in bit/s over the entire
  /// AVC bitstream.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pAverageBitRate pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pAverageBitRate.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pAverageBitRate arg is NULL.
  //
  STDMETHOD (GetAverageBitRate) (
    // Average bit rate. 
    /*[out]*/ aafUInt32 *  pAverageBitRate);



  //***********************************************************
  //
  // SetProfile()
  //
  // Set the AVC video profile.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCProfile property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetProfile) (
    // AVC video profile. 
    /*[in]*/ aafUInt8  profile);


  //***********************************************************
  //
  // GetProfile()
  //
  // Get the AVC video profile.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pProfile pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pProfile.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pProfile arg is NULL.
  //
  STDMETHOD (GetProfile) (
    // AVC video profile. 
    /*[out]*/ aafUInt8 *  pProfile);



  //***********************************************************
  //
  // SetProfileConstraint()
  //
  // Set the AVC video profile constraint flags.
  /// The value of bit [7..2] is taken from constraint_set0_flag through
  /// constraint_set5_flag in the sequence parameter set. The value of
  /// bit [1..0] shall be set to zero.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCProfileConstraint property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetProfileConstraint) (
    // AVC video profile constraint flags. 
    /*[in]*/ aafUInt8  profileConstraint);


  //***********************************************************
  //
  // GetProfileConstraint()
  //
  // Get the AVC video profile constraint flags.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pProfileConstraint pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pProfileConstraint.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pProfileConstraint arg is NULL.
  //
  STDMETHOD (GetProfileConstraint) (
    // AVC video profile constraint flags. 
    /*[out]*/ aafUInt8 *  pProfileConstraint);



  //***********************************************************
  //
  // SetLevel()
  //
  // Set the AVC level.
  /// The value is taken from level_idc in the sequence parameter set.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCLevel property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetLevel) (
    // AVC level. 
    /*[in]*/ aafUInt8  level);


  //***********************************************************
  //
  // GetLevel()
  //
  // Get the AVC level.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pLevel pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pLevel.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pLevel arg is NULL.
  //
  STDMETHOD (GetLevel) (
    // AVC level. 
    /*[out]*/ aafUInt8 *  pLevel);



  //***********************************************************
  //
  // SetMaximumRefFrames()
  //
  // Set the maximum number of reference frames.
  /// The value is the maximum value of max_num_ref_frames within all
  /// sequence parameter sets.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCMaximumRefFrames property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetMaximumRefFrames) (
    // maximum number of reference frames. 
    /*[in]*/ aafUInt8  maximumRefFrames);


  //***********************************************************
  //
  // GetMaximumRefFrames()
  //
  // Get the maximum number of reference frames.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pMaximumRefFrames pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pMaximumRefFrames.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pMaximumRefFrames arg is NULL.
  //
  STDMETHOD (GetMaximumRefFrames) (
    // maximum number of reference frames. 
    /*[out]*/ aafUInt8 *  pMaximumRefFrames);



  //***********************************************************
  //
  // SetSequenceParameterSetFlag()
  //
  // Set the flag specifying location and the constancy of sequence
  /// parameter sets.
  /// For the meaning of values of the flag see SMPTE ST 381-3:2013, Table 7.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCSequenceParameterSetFlag property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetSequenceParameterSetFlag) (
    // sequence parameter set flag. 
    /*[in]*/ aafUInt8  sequenceParameterSetFlag);


  //***********************************************************
  //
  // GetSequenceParameterSetFlag()
  //
  // Get the flag specifying location and the constancy of sequence
  /// parameter sets.
  /// For the meaning of values of the flag see SMPTE ST 381-3:2013, Table 7.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pSequenceParameterSetFlag pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pSequenceParameterSetFlag.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pSequenceParameterSetFlag arg is NULL.
  //
  STDMETHOD (GetSequenceParameterSetFlag) (
    // sequence parameter set flag. 
    /*[out]*/ aafUInt8 *  pSequenceParameterSetFlag);



  //***********************************************************
  //
  // SetPictureParameterSetFlag()
  //
  // Set the flag specifying the location and the constancy of picture
  /// parameter sets.
  /// For the meaning of values of the flag see SMPTE ST 381-3:2013, Table 8.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the AVCPictureParameterSetFlag property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetPictureParameterSetFlag) (
    // picture parameter set flag. 
    /*[in]*/ aafUInt8  pictureParameterSetFlag);


  //***********************************************************
  //
  // GetPictureParameterSetFlag()
  //
  // Get the flag specifying the location and the constancy of picture
  /// parameter sets.
  /// For the meaning of values of the flag see SMPTE ST 381-3:2013, Table 8.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pPictureParameterSetFlag pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pPictureParameterSetFlag.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pPictureParameterSetFlag arg is NULL.
  //
  STDMETHOD (GetPictureParameterSetFlag) (
    // picture parameter set flag. 
    /*[out]*/ aafUInt8 *  pPictureParameterSetFlag);



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

#endif // ! __CAAFAVCSubDescriptor_h__


