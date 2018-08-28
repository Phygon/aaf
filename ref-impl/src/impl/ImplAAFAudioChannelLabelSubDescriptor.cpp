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

#include "ImplAAFAudioChannelLabelSubDescriptor.h"
#include "AAFPropertyIDs.h"
#include "AAFPropertyDefs.h"



ImplAAFAudioChannelLabelSubDescriptor::ImplAAFAudioChannelLabelSubDescriptor() :
    _groupLinkID(
        PID_AudioChannelLabelSubDescriptor_SoundfieldGroupLinkID,
        L"SoundfieldGroupLinkID")
{
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_AudioChannelLabelSubDescriptor_SoundfieldGroupLinkID),
        _groupLinkID.address());
}



ImplAAFAudioChannelLabelSubDescriptor::~ImplAAFAudioChannelLabelSubDescriptor ()
{
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAudioChannelLabelSubDescriptor::SetSoundfieldGroupLinkID(
    aafUID_constref groupLinkID)
{
    if (!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _groupLinkID = makeUUID(groupLinkID);

	return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFAudioChannelLabelSubDescriptor::GetSoundfieldGroupLinkID(
    aafUID_t* pGroupLinkID)
{
    if (pGroupLinkID == 0)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_groupLinkID.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;
 
    *pGroupLinkID = makeAUID(_groupLinkID);

	return AAFRESULT_SUCCESS;
}



