#ifndef __ImplAAFMPEG4VisualSubDescriptor_h__
#define __ImplAAFMPEG4VisualSubDescriptor_h__

//=---------------------------------------------------------------------=
//
// $Id$ $Name$
//
// The contents of this file are subject to the AAF SDK Public
// Source License Agreement (the "License"); You may not use this file
// except in compliance with the License.  The License is available in
// AAFSDKPSL.TXT, or you may obtain a copy of the License from the AAF
// Association or its successor.
//
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.
//
// The Original Code of this file is Copyright 1998-2011, Licensor of the
// AAF Association.
//
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=


#include "ImplAAFSubDescriptor.h"

#include "OMFixedSizeProperty.h"



class ImplAAFMPEG4VisualSubDescriptor : public ImplAAFSubDescriptor
{
public:
  //****************
  // Constructor
  //
  ImplAAFMPEG4VisualSubDescriptor ();

protected:
  //****************
  // Desctructor
  //
  virtual ~ImplAAFMPEG4VisualSubDescriptor ();

public:
  //********************************
  // AAF SDK exported methods start
  //********************************

  //****************
  // Initialize()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Initialize ();

  //****************
  // SetSingleSequence()
  //
  // Set the flag specifying if all configuration information in
  // the essence stream are identical except vbv_occupancy.
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetSingleSequence
        // @param singleSequence [in] Is all configuration information
        //          the essence stream are identical except vbv_occupancy?
        (aafBoolean_t  singleSequence);


  //****************
  // GetSingleSequence()
  //
  // Get the flag specifying if all configuration information in
  // the essence stream are identical except vbv_occupancy.
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetSingleSequence
        // @param pSingleSequence [out] Is all configuration information
        //          the essence stream are identical except vbv_occupancy?
    (aafBoolean_t *  pSingleSequence);


  //****************
  // SetConstantBVOPs()
  //
  // Set the flag specifying if the number of B-VOPs is always constant.
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetConstantBVOPs
        // @param constantBVOPs [in] Is the number of B-VOPs always constant?
    (aafBoolean_t  constantBVOPs);


  //****************
  // GetConstantBVOPs()
  //
  // Get the flag specifying if the number of B-VOPs is always constant.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    GetConstantBVOPs
        // @param pConstantBVOPs [in] Is the number of B-VOPs always constant?
    (aafBoolean_t *  pConstantBVOPs);


  //****************
  // SetCodedContentType()
  //
  // Set coded content type.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    SetCodedContentType
        // @param codedContentType [in] Coded content type.
    (aafMPEG4VisualCodedContentType_t  codedContentType);


  //****************
  // GetCodedContentType()
  //
  // Get coded content type.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    GetCodedContentType
        // @param pCodedContentType [out] Coded content type.
    (aafMPEG4VisualCodedContentType_t *  pCodedContentType);


  //****************
  // SetLowDelay()
  //
  // Set the flag specifying if the VOL contains no B-VOPs.
  virtual AAFRESULT STDMETHODCALLTYPE
    SetLowDelay
        // @param lowDelay [in] Does the VOL contains no B-VOPs?
    (aafBoolean_t  lowDelay);


  //****************
  // GetLowDelay()
  //
  // Get the flag specifying if the VOL contains no B-VOPs.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    GetLowDelay
        // @param pLowDelay [out] Does the VOL contains no B-VOPs?
    (aafBoolean_t *  pLowDelay);


  //****************
  // SetClosedGOV()
  //
  // Set the flag specifying if closed_gov is set in all GOV headers.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    SetClosedGOV
        // @param closedGOV [out] Is closed_gov set in all GOV headers?
    (aafBoolean_t  closedGOV);


  //****************
  // GetClosedGOV()
  //
  // Get the flag specifying if closed_gov is set in all GOV headers.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    GetClosedGOV
        // @param pClosedGOV [out] Is closed_gov set in all GOV headers?
    (aafBoolean_t *  pClosedGOV);


  //****************
  // SetIdenticalGOV()
  //
  // Set the flag specifying if every GOV in the sequence is constructed the same.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    SetIdenticalGOV
        // @param identicalGOV [in] Is every GOV in the sequence is
        //          constructed the same?
    (aafBoolean_t  identicalGOV);


  //****************
  // GetIdenticalGOV()
  //
  // Get the flag specifying if every GOV in the sequence is constructed the same.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    GetIdenticalGOV
        // @param pIdenticalGOV [out] Is every GOV in the sequence is
        //          constructed the same?
    (aafBoolean_t *  pIdenticalGOV);


  //****************
  // SetMaxGOV()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetMaxGOV
        // @param maxGOV [in] The maximum occurring spacing between I frames.
    (aafUInt16  maxGOV);


  //****************
  // GetMaxGOV()
  //
  // Get the maximum occurring spacing between I frames.
  // A value of 0 or the absence of this property implies no limit to
  // the maximum GOV or the maximum GOV is unknown.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    GetMaxGOV
        // @param pMaxGOV [out] The maximum occurring spacing between I frames.
    (aafUInt16 *  pMaxGOV);


  //****************
  // SetBVOPCount()
  //
  // Set the maximum occurring spacing between I frames.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    SetBVOPCount
        // @param maxGOV [in] The maximum number of B-VOPs between P or
        //          I-VOPs.
    (aafUInt16  bvopCount);


  //****************
  // GetBVOPCount()
  //
  // Get the maximum occurring spacing between I frames.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    GetBVOPCount
        // @param pBVOPCount [out] The maximum number of B-VOPs between P or
        //          I-VOPs.
    (aafUInt16 *  pBVOPCount);


  //****************
  // SetBitRate()
  //
  // Set the maximum bit rate of the MPEG-4 Visual stream in bits per second.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    SetBitRate
        // @param bitRate [in] The maximum bit rate of the MPEG-4 Visual
        //          stream.
    (aafUInt32  bitRate);


  //****************
  // GetBitRate()
  //
  // Get the maximum bit rate of the MPEG-4 Visual stream in bits per second.
  // 
  virtual AAFRESULT STDMETHODCALLTYPE
    GetBitRate
        // @param pBitRate [out] The maximum bit rate of the MPEG-4 Visual
        //          stream.
    (aafUInt32 *  pBitRate);


  //****************
  // SetProfileAndLevel()
  //
  // Set the MPEG-4 visual profile and level.
  // The meaning of the bits is given in Table G.1 of ISO/IEC 14496-2.
  virtual AAFRESULT STDMETHODCALLTYPE
    SetProfileAndLevel
        // @param profileAndLevel [in] The MPEG-4 visual profile and level.
    (aafUInt8  profileAndLevel);


  //****************
  // GetProfileAndLevel()
  //
  // Get the MPEG-4 visual profile and level.
  // The meaning of the bits is given in Table G.1 of ISO/IEC 14496-2.
  virtual AAFRESULT STDMETHODCALLTYPE
    GetProfileAndLevel
        // @param pProfileAndLevel [out] The MPEG-4 visual profile and level.
    (aafUInt8 *  pProfileAndLevel);

  //********************************
  // AAF SDK exported methods end
  //********************************

protected:

    OMFixedSizeProperty<aafBoolean_t>                       _singleSequence;
    OMFixedSizeProperty<aafBoolean_t>                       _constantBVOPs;
    OMFixedSizeProperty<aafMPEG4VisualCodedContentType_t>   _codedContentType;
    OMFixedSizeProperty<aafBoolean_t>                       _lowDelay;
    OMFixedSizeProperty<aafBoolean_t>                       _closedGOV;
    OMFixedSizeProperty<aafBoolean_t>                       _identicalGOV;
    OMFixedSizeProperty<aafUInt16>                          _maxGOV;
    OMFixedSizeProperty<aafUInt16>                          _bvopCount;
    OMFixedSizeProperty<aafUInt32>                          _bitRate;
    OMFixedSizeProperty<aafUInt8>                           _profileAndLevel;
};

#endif // ! __ImplAAFMPEG4VisualSubDescriptor_h__
