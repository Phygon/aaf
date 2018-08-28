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

#include "ImplAAFSoundfieldGroupLabelSubDescriptor.h"
#include "AAFPropertyIDs.h"
#include "AAFPropertyDefs.h"
#include "AAFUtils.h"

#include "OMArrayPropertyIterator.h"



ImplAAFSoundfieldGroupLabelSubDescriptor::ImplAAFSoundfieldGroupLabelSubDescriptor() :
    _groupLinkIDs(
        PID_SoundfieldGroupLabelSubDescriptor_GroupOfSoundfieldGroupsLinkID,
        L"GroupOfSoundfieldGroupsLinkID")
{
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_SoundfieldGroupLabelSubDescriptor_GroupOfSoundfieldGroupsLinkID),
        _groupLinkIDs.address());
}



ImplAAFSoundfieldGroupLabelSubDescriptor::~ImplAAFSoundfieldGroupLabelSubDescriptor ()
{
}



AAFRESULT STDMETHODCALLTYPE ImplAAFSoundfieldGroupLabelSubDescriptor::CountGroupOfSoundfieldGroupsLinkIDs(
    aafUInt32* pCount)
{
    if (pCount == 0)
        return AAFRESULT_NULL_PARAM;
    if (!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_groupLinkIDs.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pCount = _groupLinkIDs.count();

	return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFSoundfieldGroupLabelSubDescriptor::GetGroupOfSoundfieldGroupsLinkIDAt(
	aafUInt32 index,
    aafUID_t* pGroupOfGroupsLinkID)
{
	//TODO: Return AAFRESULT_BADINDEX for bad index
    if (pGroupOfGroupsLinkID == 0)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_groupLinkIDs.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;
	if (index >= _groupLinkIDs.count())
	  return AAFRESULT_BADINDEX;

    *pGroupOfGroupsLinkID = makeAUID(_groupLinkIDs.getAt(index));

	return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFSoundfieldGroupLabelSubDescriptor::AppendGroupOfSoundfieldGroupsLinkID(
    aafUID_constref groupOfGroupsLinkID)
{
    if (!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (this->Contains(groupOfGroupsLinkID))
        return AAFRESULT_INVALID_PARAM;
    // TODO: Validate against OMPROPERTYSIZE_MAX

    _groupLinkIDs.append(makeUUID(groupOfGroupsLinkID));

	return AAFRESULT_SUCCESS;
}



bool ImplAAFSoundfieldGroupLabelSubDescriptor::Contains(
    aafUID_constref groupOfGroupsLinkID) const
{
    OMArrayPropertyIterator<UUID_t>* iter =
        dynamic_cast<OMArrayPropertyIterator<UUID_t>*>(_groupLinkIDs.createIterator());
    if (!iter)
        return false;

    const UUID_t targetUUID = makeUUID(groupOfGroupsLinkID);

    bool found = false;
    while (!found && (iter->before() || iter->valid()))
    {
        if (++(*iter))
        {
            const UUID_t id = iter->value();
            if (id == targetUUID)
            {
                found = true;
            }
        }
    }

    delete iter;
    iter = NULL;;
    
    return found;
}

