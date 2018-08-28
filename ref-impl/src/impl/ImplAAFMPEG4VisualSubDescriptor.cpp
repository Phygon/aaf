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

#include "ImplAAFMPEG4VisualSubDescriptor.h"
#include "AAFPropertyIDs.h"
#include "AAFPropertyDefs.h"



ImplAAFMPEG4VisualSubDescriptor::ImplAAFMPEG4VisualSubDescriptor() :
    _singleSequence(PID_MPEG4VisualSubDescriptor_MPEG4VisualSingleSequence, L"MPEG4VisualSingleSequence"),
    _constantBVOPs(PID_MPEG4VisualSubDescriptor_MPEG4VisualConstantBVOPs, L"MPEG4VisualConstantBVOPs"),
    _codedContentType(PID_MPEG4VisualSubDescriptor_MPEG4VisualCodedContentType, L"MPEG4VisualCodedContentType"),
    _lowDelay(PID_MPEG4VisualSubDescriptor_MPEG4VisualLowDelay, L"MPEG4VisualLowDelay"),
    _closedGOV(PID_MPEG4VisualSubDescriptor_MPEG4VisualClosedGOV, L"MPEG4VisualClosedGOV"),
    _identicalGOV(PID_MPEG4VisualSubDescriptor_MPEG4VisualIdenticalGOV, L"MPEG4VisualIdenticalGOV"),
    _maxGOV(PID_MPEG4VisualSubDescriptor_MPEG4VisualMaxGOV, L"MPEG4VisualMaxGOV"),
    _bvopCount(PID_MPEG4VisualSubDescriptor_MPEG4VisualBVOPCount, L"MPEG4VisualBVOPCount"),
    _bitRate(PID_MPEG4VisualSubDescriptor_MPEG4VisualBitRate, L"MPEG4VisualBitRate"),
    _profileAndLevel(PID_MPEG4VisualSubDescriptor_MPEG4VisualProfileAndLevel, L"MPEG4VisualProfileAndLevel")
{
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MPEG4VisualSubDescriptor_MPEG4VisualSingleSequence),
        _singleSequence.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MPEG4VisualSubDescriptor_MPEG4VisualConstantBVOPs),
        _constantBVOPs.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MPEG4VisualSubDescriptor_MPEG4VisualCodedContentType),
        _codedContentType.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MPEG4VisualSubDescriptor_MPEG4VisualLowDelay),
        _lowDelay.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MPEG4VisualSubDescriptor_MPEG4VisualClosedGOV),
        _closedGOV.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MPEG4VisualSubDescriptor_MPEG4VisualIdenticalGOV),
        _identicalGOV.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MPEG4VisualSubDescriptor_MPEG4VisualMaxGOV),
        _maxGOV.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MPEG4VisualSubDescriptor_MPEG4VisualBVOPCount),
        _bvopCount.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MPEG4VisualSubDescriptor_MPEG4VisualBitRate),
        _bitRate.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MPEG4VisualSubDescriptor_MPEG4VisualProfileAndLevel),
        _profileAndLevel.address());
}



ImplAAFMPEG4VisualSubDescriptor::~ImplAAFMPEG4VisualSubDescriptor ()
{
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::Initialize()
{
    if( isInitialized() )
    {
        return AAFRESULT_ALREADY_INITIALIZED;
    }

    setInitialized();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::SetSingleSequence(
    aafBoolean_t singleSequence )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _singleSequence = singleSequence;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::GetSingleSequence(
    aafBoolean_t* pSingleSequence )
{
    if (pSingleSequence == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_singleSequence.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pSingleSequence = _singleSequence;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::SetConstantBVOPs(
    aafBoolean_t ConstantBVOPs )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _constantBVOPs = ConstantBVOPs;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::GetConstantBVOPs(
    aafBoolean_t* pConstantBVOPs)
{
    if (pConstantBVOPs == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_constantBVOPs.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pConstantBVOPs = _constantBVOPs;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::SetCodedContentType(
    aafBoolean_t CodedContentType )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _codedContentType = CodedContentType;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::GetCodedContentType(
    aafBoolean_t* pCodedContentType)
{
    if (pCodedContentType == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_codedContentType.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pCodedContentType = _codedContentType;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::SetLowDelay(
    aafBoolean_t LowDelay )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _lowDelay = LowDelay;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::GetLowDelay(
    aafBoolean_t* pLowDelay)
{
    if (pLowDelay == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_lowDelay.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pLowDelay = _lowDelay;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::SetClosedGOV(
    aafBoolean_t ClosedGOV )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _closedGOV = ClosedGOV;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::GetClosedGOV(
    aafBoolean_t* pClosedGOV)
{
    if (pClosedGOV == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_closedGOV.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pClosedGOV = _closedGOV;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::SetIdenticalGOV(
    aafBoolean_t IdenticalGOV )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _identicalGOV = IdenticalGOV;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::GetIdenticalGOV(
    aafBoolean_t* pIdenticalGOV)
{
    if (pIdenticalGOV == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_identicalGOV.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pIdenticalGOV = _identicalGOV;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::SetMaxGOV(
    aafUInt16 MaxGOV )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _maxGOV = MaxGOV;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::GetMaxGOV(
    aafUInt16* pMaxGOV)
{
    if (pMaxGOV == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_maxGOV.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pMaxGOV = _maxGOV;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::SetBVOPCount(
    aafUInt16 BVOPCount )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _bvopCount = BVOPCount;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::GetBVOPCount(
    aafUInt16* pBVOPCount)
{
    if (pBVOPCount == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_bvopCount.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pBVOPCount = _bvopCount;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::SetBitRate(
    aafUInt32 BitRate )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _bitRate = BitRate;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::GetBitRate(
    aafUInt32* pBitRate)
{
    if (pBitRate == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_bitRate.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pBitRate = _bitRate;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::SetProfileAndLevel(
    aafUInt8 ProfileAndLevel )
{
    if (!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _profileAndLevel = ProfileAndLevel;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMPEG4VisualSubDescriptor::GetProfileAndLevel(
    aafUInt8* pProfileAndLevel)
{
    if (pProfileAndLevel == 0)
    {
        return AAFRESULT_NULL_PARAM;
    }
    if(!isInitialized())
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_profileAndLevel.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pProfileAndLevel = _profileAndLevel;

    return AAFRESULT_SUCCESS;
}



