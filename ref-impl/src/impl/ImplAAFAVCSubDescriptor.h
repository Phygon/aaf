#ifndef __ImplAAFAVCSubDescriptor_h__
#define __ImplAAFAVCSubDescriptor_h__

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



class ImplAAFAVCSubDescriptor : public ImplAAFSubDescriptor
{
public:
  //****************
  // Constructor
  //
  ImplAAFAVCSubDescriptor ();

protected:
  //****************
  // Desctructor
  //
  virtual ~ImplAAFAVCSubDescriptor ();

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
  // SetDecodingDelay()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetDecodingDelay
        // @param decodingDelay [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt8 decodingDelay);

  //****************
  // GetDecodingDelay()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetDecodingDelay
        // @param pDecodingDelay [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt8 *  pDecodingDelay);

  //****************
  // SetConstantBPictureFlag()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetConstantBPictureFlag
        // @param constantBPictureFlag [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafBoolean_t constantBPictureFlag);

  //****************
  // GetConstantBPictureFlag()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetConstantBPictureFlag
        // @param pConstantBPictureFlag [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafBoolean_t *  pConstantBPictureFlag);

  //****************
  // SetCodedContentKind()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetCodedContentKind
        // @param codedContentKind [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafAVCContentScanningType_t codedContentKind);

  //****************
  // GetCodedContentKind()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetCodedContentKind
        // @param pCodedContentKind [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafAVCContentScanningType_t *  pCodedContentKind);

  //****************
  // SetClosedGOPIndicator()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetClosedGOPIndicator
        // @param closedGOPIndicator [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafBoolean_t closedGOPIndicator);

  //****************
  // GetClosedGOPIndicator()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetClosedGOPIndicator
        // @param pClosedGOPIndicator [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafBoolean_t *  pClosedGOPIndicator);

  //****************
  // SetIdenticalGOPIndicator()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetIdenticalGOPIndicator
        // @param identicalGOPIndicator [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafBoolean_t identicalGOPIndicator);

  //****************
  // GetIdenticalGOPIndicator()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetIdenticalGOPIndicator
        // @param pIdenticalGOPIndicator [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafBoolean_t *  pIdenticalGOPIndicator);

  //****************
  // SetMaximumGOPSize()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetMaximumGOPSize
        // @param maximumGOPSize [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt16 maximumGOPSize);

  //****************
  // GetMaximumGOPSize()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetMaximumGOPSize
        // @param pMaximumGOPSize [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt16 *  pMaximumGOPSize);

  //****************
  // SetMaximumBPictureCount()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetMaximumBPictureCount
        // @param maximumBPictureCount [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt16 maximumBPictureCount);

  //****************
  // GetMaximumBPictureCount()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetMaximumBPictureCount
        // @param pMaximumBPictureCount [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt16 *  pMaximumBPictureCount);

  //****************
  // SetMaximumBitRate()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetMaximumBitRate
        // @param maximumBitRate [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt32 maximumBitRate);

  //****************
  // GetMaximumBitRate()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetMaximumBitRate
        // @param pMaximumBitRate [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt32 *  pMaximumBitRate);

  //****************
  // SetAverageBitRate()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetAverageBitRate
        // @param averageBitRate [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt32 averageBitRate);

  //****************
  // GetAverageBitRate()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetAverageBitRate
        // @param pAverageBitRate [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt32 *  pAverageBitRate);

  //****************
  // SetProfile()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetProfile
        // @param profile [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt8 profile);

  //****************
  // GetProfile()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetProfile
        // @param pProfile [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt8 *  pProfile);

  //****************
  // SetProfileConstraint()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetProfileConstraint
        // @param profileConstraint [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt8 profileConstraint);

  //****************
  // GetProfileConstraint()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetProfileConstraint
        // @param pProfileConstraint [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt8 *  pProfileConstraint);

  //****************
  // SetLevel()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetLevel
        // @param level [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt8 level);

  //****************
  // GetLevel()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetLevel
        // @param pLevel [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt8 *  pLevel);

  //****************
  // SetMaximumRefFrames()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetMaximumRefFrames
        // @param maximumRefFrames [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt8 maximumRefFrames);

  //****************
  // GetMaximumRefFrames()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetMaximumRefFrames
        // @param pMaximumRefFrames [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt8 *  pMaximumRefFrames);

  //****************
  // SetSequenceParameterSetFlag()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetSequenceParameterSetFlag
        // @param sequenceParameterSetFlag [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt8 sequenceParameterSetFlag);

  //****************
  // GetSequenceParameterSetFlag()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetSequenceParameterSetFlag
        // @param pSequenceParameterSetFlag [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt8 *  pSequenceParameterSetFlag);

  //****************
  // SetPictureParameterSetFlag()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPictureParameterSetFlag
        // @param pictureParameterSetFlag [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt8 pictureParameterSetFlag);

  //****************
  // GetPictureParameterSetFlag()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPictureParameterSetFlag
        // @param pPictureParameterSetFlag [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt8 *  pPictureParameterSetFlag);

  //********************************
  // AAF SDK exported methods end
  //********************************

protected:

    OMFixedSizeProperty<aafUInt8>                       _decodingDelay;
    OMFixedSizeProperty<aafBoolean_t>                   _constantBPictureFlag;
    OMFixedSizeProperty<aafAVCContentScanningType_t>    _codedContentKind;
    OMFixedSizeProperty<aafBoolean_t>                   _closedGOPIndicator;
    OMFixedSizeProperty<aafBoolean_t>                   _identicalGOPIndicator;
    OMFixedSizeProperty<aafUInt16>                      _maximumGOPSize;
    OMFixedSizeProperty<aafUInt16>                      _maximumBPictureCount;
    OMFixedSizeProperty<aafUInt32>                      _maximumBitRate;
    OMFixedSizeProperty<aafUInt32>                      _averageBitRate;
    OMFixedSizeProperty<aafUInt8>                       _profile;
    OMFixedSizeProperty<aafUInt8>                       _profileConstraint;
    OMFixedSizeProperty<aafUInt8>                       _level;
    OMFixedSizeProperty<aafUInt8>                       _maximumRefFrames;
    OMFixedSizeProperty<aafUInt8>                       _sequenceParameterSetFlag;
    OMFixedSizeProperty<aafUInt8>                       _pictureParameterSetFlag;
};

#endif // ! __ImplAAFAVCSubDescriptor_h__
