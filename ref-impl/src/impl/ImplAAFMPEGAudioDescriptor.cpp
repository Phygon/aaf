//=---------------------------------------------------------------------=
//
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
// The Original Code of this file is Copyright 1998-2005, Licensor of the
// AAF Association.
//
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=










#include "AAFStoredObjectIDs.h"
#include "AAFPropertyIDs.h"
#include "AAFPropertyDefs.h"

#ifndef __ImplAAFMPEGAudioDescriptor_h__
#include "ImplAAFMPEGAudioDescriptor.h"
#endif

#include <string.h>


ImplAAFMPEGAudioDescriptor::ImplAAFMPEGAudioDescriptor ():

	_mpegAudioBitRate(PID_MPEGAudioDescriptor_MPEGAudioBitRate, L"MPEGAudioBitRate")
	
{
    
#define OM_UID(name) \
    *reinterpret_cast<const OMObjectIdentification *>(&kAAFPropID_MPEGAudioDescriptor_##name)
    
	_persistentProperties.putDynamicBuiltin(OM_UID(MPEGAudioBitRate), _mpegAudioBitRate.address());
}


ImplAAFMPEGAudioDescriptor::~ImplAAFMPEGAudioDescriptor ()
{}

AAFRESULT STDMETHODCALLTYPE
    ImplAAFMPEGAudioDescriptor::Initialize ()
{
	return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFMPEGAudioDescriptor::SetMPEGAudioBitRate (
      aafUInt32  bitRate)
{
	_mpegAudioBitRate = bitRate;
	return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFMPEGAudioDescriptor::GetMPEGAudioBitRate (
      aafUInt32 *  pBitRate)
{
	if( pBitRate == NULL )
    {
        return AAFRESULT_NULL_PARAM;
    }
    
	if( !_mpegAudioBitRate.isPresent() )
    {
		return AAFRESULT_PROP_NOT_PRESENT;
    }


    *pBitRate = _mpegAudioBitRate;


    return AAFRESULT_SUCCESS;
}


