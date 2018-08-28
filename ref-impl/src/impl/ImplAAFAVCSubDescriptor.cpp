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

#include "ImplAAFAVCSubDescriptor.h"
#include "AAFPropertyIDs.h"
#include "AAFPropertyDefs.h"



ImplAAFAVCSubDescriptor::ImplAAFAVCSubDescriptor() :
    _decodingDelay(PID_AVCSubDescriptor_AVCDecodingDelay, L"AVCDecodingDelay"),
    _constantBPictureFlag(PID_AVCSubDescriptor_AVCConstantBPictureFlag, L"AVCConstantBPictureFlag"),
    _codedContentKind(PID_AVCSubDescriptor_AVCCodedContentKind, L"AVCCodedContentKind"),
    _closedGOPIndicator(PID_AVCSubDescriptor_AVCClosedGOPIndicator, L"AVCClosedGOPIndicator"),
    _identicalGOPIndicator(PID_AVCSubDescriptor_AVCIdenticalGOPIndicator, L"AVCIdenticalGOPIndicator"),
    _maximumGOPSize(PID_AVCSubDescriptor_AVCMaximumGOPSize, L"AVCMaximumGOPSize"),
    _maximumBPictureCount(PID_AVCSubDescriptor_AVCMaximumBPictureCount, L"AVCMaximumBPictureCount"),
    _maximumBitRate(PID_AVCSubDescriptor_AVCMaximumBitRate, L"AVCMaximumBitRate"),
    _averageBitRate(PID_AVCSubDescriptor_AVCAverageBitRate, L"AVCAverageBitRate"),
    _profile(PID_AVCSubDescriptor_AVCProfile, L"AVCProfile"),
    _profileConstraint(PID_AVCSubDescriptor_AVCProfileConstraint, L"AVCProfileConstraint"),
    _level(PID_AVCSubDescriptor_AVCLevel, L"AVCLevel"),
    _maximumRefFrames(PID_AVCSubDescriptor_AVCMaximumRefFrames, L"AVCMaximumRefFrames"),
    _sequenceParameterSetFlag(PID_AVCSubDescriptor_AVCSequenceParameterSetFlag, L"AVCSequenceParameterSetFlag"),
    _pictureParameterSetFlag(PID_AVCSubDescriptor_AVCPictureParameterSetFlag, L"AVCPictureParameterSetFlag")
{
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCDecodingDelay),
        _decodingDelay.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCConstantBPictureFlag),
        _constantBPictureFlag.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCCodedContentKind),
        _codedContentKind.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCClosedGOPIndicator),
        _closedGOPIndicator.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCIdenticalGOPIndicator),
        _identicalGOPIndicator.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCMaximumGOPSize),
        _maximumGOPSize.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCMaximumBPictureCount),
        _maximumBPictureCount.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCMaximumBitRate),
        _maximumBitRate.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCAverageBitRate),
        _averageBitRate.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCProfile),
        _profile.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCProfileConstraint),
        _profileConstraint.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCLevel),
        _level.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCMaximumRefFrames),
        _maximumRefFrames.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCSequenceParameterSetFlag),
        _sequenceParameterSetFlag.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AVCSubDescriptor_AVCPictureParameterSetFlag),
        _pictureParameterSetFlag.address());

    // Set the required properties.
    _decodingDelay = 0xFF;  // Default to unknown
}



ImplAAFAVCSubDescriptor::~ImplAAFAVCSubDescriptor ()
{
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::Initialize()
{
    if( isInitialized() )
    {
        return AAFRESULT_ALREADY_INITIALIZED;
    }

    setInitialized();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetDecodingDelay(
    aafUInt8 decodingDelay )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _decodingDelay = decodingDelay;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetDecodingDelay(
    aafUInt8* pDecodingDelay )
{
    if (pDecodingDelay == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    *pDecodingDelay = _decodingDelay;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetConstantBPictureFlag(
    aafBoolean_t constantBPictureFlag )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _constantBPictureFlag = constantBPictureFlag;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetConstantBPictureFlag(
    aafBoolean_t* pConstantBPictureFlag )
{
    if (pConstantBPictureFlag == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_constantBPictureFlag.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pConstantBPictureFlag = _constantBPictureFlag;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetCodedContentKind(
    aafAVCContentScanningType_t codedContentKind )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _codedContentKind = codedContentKind;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetCodedContentKind(
    aafAVCContentScanningType_t* pCodedContentKind )
{
    if (pCodedContentKind == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_codedContentKind.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pCodedContentKind = _codedContentKind;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetClosedGOPIndicator(
    aafBoolean_t closedGOPIndicator )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _closedGOPIndicator = closedGOPIndicator;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetClosedGOPIndicator(
    aafBoolean_t* pClosedGOPIndicator )
{
    if (pClosedGOPIndicator == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_closedGOPIndicator.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pClosedGOPIndicator = _closedGOPIndicator;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetIdenticalGOPIndicator(
    aafBoolean_t identicalGOPIndicator )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _identicalGOPIndicator = identicalGOPIndicator;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetIdenticalGOPIndicator(
    aafBoolean_t* pIdenticalGOPIndicator )
{
    if (pIdenticalGOPIndicator == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_identicalGOPIndicator.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pIdenticalGOPIndicator = _identicalGOPIndicator;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetMaximumGOPSize(
    aafUInt16 maximumGOPSize )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _maximumGOPSize = maximumGOPSize;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetMaximumGOPSize(
    aafUInt16* pMaximumGOPSize )
{
    if (pMaximumGOPSize == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_maximumGOPSize.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pMaximumGOPSize = _maximumGOPSize;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetMaximumBPictureCount(
    aafUInt16 maximumBPictureCount )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _maximumBPictureCount = maximumBPictureCount;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetMaximumBPictureCount(
    aafUInt16* pMaximumBPictureCount )
{
    if (pMaximumBPictureCount == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_maximumBPictureCount.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pMaximumBPictureCount = _maximumBPictureCount;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetMaximumBitRate(
    aafUInt32 maximumBitRate )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _maximumBitRate = maximumBitRate;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetMaximumBitRate(
    aafUInt32* pMaximumBitRate )
{
    if (pMaximumBitRate == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_maximumBitRate.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pMaximumBitRate = _maximumBitRate;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetAverageBitRate(
    aafUInt32 averageBitRate )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _averageBitRate = averageBitRate;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetAverageBitRate(
    aafUInt32* pAverageBitRate )
{
    if (pAverageBitRate == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_averageBitRate.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pAverageBitRate = _averageBitRate;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetProfile(
    aafUInt8 profile )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _profile = profile;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetProfile(
    aafUInt8* pProfile )
{
    if (pProfile == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_profile.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pProfile = _profile;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetProfileConstraint(
    aafUInt8 profileConstraint )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _profileConstraint = profileConstraint;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetProfileConstraint(
    aafUInt8* pProfileConstraint )
{
    if (pProfileConstraint == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_profileConstraint.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pProfileConstraint = _profileConstraint;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetLevel(
    aafUInt8 level )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _level = level;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetLevel(
    aafUInt8* pLevel )
{
    if (pLevel == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_level.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pLevel = _level;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetMaximumRefFrames(
    aafUInt8 maximumRefFrames )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _maximumRefFrames = maximumRefFrames;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetMaximumRefFrames(
    aafUInt8* pMaximumRefFrames )
{
    if (pMaximumRefFrames == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_maximumRefFrames.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pMaximumRefFrames = _maximumRefFrames;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetSequenceParameterSetFlag(
    aafUInt8 sequenceParameterSetFlag )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _sequenceParameterSetFlag = sequenceParameterSetFlag;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetSequenceParameterSetFlag(
    aafUInt8* pSequenceParameterSetFlag )
{
    if (pSequenceParameterSetFlag == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_sequenceParameterSetFlag.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pSequenceParameterSetFlag = _sequenceParameterSetFlag;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::SetPictureParameterSetFlag(
    aafUInt8 pictureParameterSetFlag )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _pictureParameterSetFlag = pictureParameterSetFlag;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAVCSubDescriptor::GetPictureParameterSetFlag(
    aafUInt8* pPictureParameterSetFlag )
{
    if (pPictureParameterSetFlag == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_pictureParameterSetFlag.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pPictureParameterSetFlag = _pictureParameterSetFlag;

    return AAFRESULT_SUCCESS;
}

