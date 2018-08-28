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
// The Original Code of this file is Copyright 1998-2004, Licensor of the
// AAF Association.
//
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

#include "ImplAAFTypeDefGenericCharacter.h"

#include "AAFPropertyDefs.h"
#include "AAFPropertyIDs.h"
#include "AAFStoredObjectIDs.h"

#include "OMTypeVisitor.h"

#include <assert.h>


ImplAAFTypeDefGenericCharacter::ImplAAFTypeDefGenericCharacter() :
	_size(PID_TypeDefinitionGenericCharacter_CharacterSize, L"CharacterSize")
{
	_persistentProperties.putDynamicBuiltin(
		*reinterpret_cast<const OMObjectIdentification*>(
			&kAAFPropID_TypeDefinitionGenericCharacter_CharacterSize),
			_size.address());
	_size = 1;
}


ImplAAFTypeDefGenericCharacter::~ImplAAFTypeDefGenericCharacter()
{
}


AAFRESULT STDMETHODCALLTYPE ImplAAFTypeDefGenericCharacter::Initialize(
	const aafUID_t& id,
	aafUInt8 size,
	const aafCharacter* pTypeName,
	const aafCharacter* pTypeDescription)
{
	if (size != 1 && size != 2 && size != 4 && size != 8)
		return AAFRESULT_BAD_SIZE;
	if (!pTypeName)
		return AAFRESULT_NULL_PARAM;
    if(isInitialized())
        return AAFRESULT_ALREADY_INITIALIZED;

	AAFRESULT hr = ImplAAFMetaDefinition::Initialize(id, pTypeName, pTypeDescription);
	if (AAFRESULT_SUCCEEDED(hr))
	{
		_size = size;
		setInitialized();
	}

	return hr;
}


AAFRESULT STDMETHODCALLTYPE ImplAAFTypeDefGenericCharacter::GetTypeCategory(
	eAAFTypeCategory_t* pCategory)
{
	if (!pCategory)
		return AAFRESULT_NULL_PARAM;
	*pCategory = kAAFTypeCatCharacter;
	return AAFRESULT_SUCCESS;
}


const OMUniqueObjectIdentification& ImplAAFTypeDefGenericCharacter::identification() const
{
	return ImplAAFMetaDefinition::identification();
}

const wchar_t* ImplAAFTypeDefGenericCharacter::name() const
{
	return ImplAAFMetaDefinition::name();
}


bool ImplAAFTypeDefGenericCharacter::hasDescription() const
{
	return ImplAAFMetaDefinition::hasDescription();
}


const wchar_t* ImplAAFTypeDefGenericCharacter::description() const
{
	return ImplAAFMetaDefinition::description();
}


bool ImplAAFTypeDefGenericCharacter::isPredefined() const
{
	return ImplAAFMetaDefinition::isPredefined();
}


bool ImplAAFTypeDefGenericCharacter::isFixedSize() const
{
	bool result = false;
	if (IsFixedSize() == kAAFTrue)
	{
		result = true;
	}
	return result;
}


void ImplAAFTypeDefGenericCharacter::reorder(
	OMByte* externalBytes,
	OMUInt32 externalBytesSize) const
{
	TRACE("ImplAAFTypeDefGenericCharacter::reorder");
	PRECONDITION("Valid external bytes", externalBytes != 0);
	PRECONDITION("Valid external bytes size", externalBytesSize > 0);

	if (externalBytesSize > 1)
	{
		reorderInteger(externalBytes, externalBytesSize);
	}
}


OMUInt32 ImplAAFTypeDefGenericCharacter::externalSize(
	const OMByte* ANAME(internalBytes),
	OMUInt32 ANAME(internalBytesSize)) const
{
	TRACE("ImplAAFTypeDefGenericCharacter::externalSize");
	PRECONDITION("Valid internal bytes", internalBytes != 0);
	PRECONDITION("Valid internal bytes size", internalBytesSize > 0);

	return externalSize();
}


OMUInt32 ImplAAFTypeDefGenericCharacter::externalSize() const
{
	return PropValSize();
}


void ImplAAFTypeDefGenericCharacter::externalize(
	const OMByte* internalBytes,
	OMUInt32 internalBytesSize,
	OMByte* externalBytes,
	OMUInt32 externalBytesSize,
	OMByteOrder byteOrder) const
{
	TRACE("ImplAAFTypeDefGenericCharacter::externalize");
	PRECONDITION("Valid internal bytes", internalBytes != 0);
	PRECONDITION("Valid internal bytes size",
				 internalBytesSize == internalSize(externalBytes, externalBytesSize));
	PRECONDITION("Valid external bytes", externalBytes != 0);
	PRECONDITION("Valid external bytes size",
				 externalBytesSize == externalSize(internalBytes, internalBytesSize));

	if (externalBytesSize == internalBytesSize)
	{
		copy(internalBytes, externalBytes, externalBytesSize);
	}
	else
	{
		throw AAFRESULT_INTERNAL_ERROR;
	}
}


OMUInt32 ImplAAFTypeDefGenericCharacter::internalSize(
	const OMByte* ANAME(externalBytes),
	OMUInt32 ANAME(externalSize)) const
{
	return internalSize();
}


OMUInt32 ImplAAFTypeDefGenericCharacter::internalSize() const
{
	return NativeSize();
}


void ImplAAFTypeDefGenericCharacter::internalize(
	const OMByte* externalBytes,
	OMUInt32 externalBytesSize,
	OMByte* internalBytes,
	OMUInt32 internalBytesSize,
	OMByteOrder byteOrder) const
{
	TRACE("ImplAAFTypeDefGenericCharacter::internalize");
	PRECONDITION("Valid internal bytes", internalBytes != 0);
	PRECONDITION("Valid internal bytes size",
				 internalBytesSize == internalSize(externalBytes, externalBytesSize));
	PRECONDITION("Valid external bytes", externalBytes != 0);
	PRECONDITION("Valid external bytes size",
				 externalBytesSize == externalSize(internalBytes, internalBytesSize));
	if (externalBytesSize == internalBytesSize)
	{
		copy(externalBytes, internalBytes, externalBytesSize);
	}
	else
	{
		throw AAFRESULT_INTERNAL_ERROR;
	}
}


void ImplAAFTypeDefGenericCharacter::accept(OMTypeVisitor& visitor) const
{
	visitor.visitCharacterType(this);
}


aafBool ImplAAFTypeDefGenericCharacter::IsFixedSize (void) const
{
	return kAAFTrue;
}


OMUInt32 ImplAAFTypeDefGenericCharacter::PropValSize (void) const
{
	return _size;
}


aafBool ImplAAFTypeDefGenericCharacter::IsRegistered (void) const
{
	// Only depends on registration of basic type.
	return kAAFTrue;
}

OMUInt32 ImplAAFTypeDefGenericCharacter::NativeSize (void) const
{
	return _size;
}


bool ImplAAFTypeDefGenericCharacter::IsAggregatable () const
{
	return true;
}


bool ImplAAFTypeDefGenericCharacter::IsStreamable () const
{
	return true;
}


bool ImplAAFTypeDefGenericCharacter::IsFixedArrayable () const
{
	return true;
}


bool ImplAAFTypeDefGenericCharacter::IsVariableArrayable () const
{
	return true;
}


bool ImplAAFTypeDefGenericCharacter::IsStringable () const
{
	return true;
}


const OMClassId& ImplAAFTypeDefGenericCharacter::classId(void) const
{
  return (*reinterpret_cast<const OMClassId *>(&AUID_AAFTypeDefinitionGenericCharacter));
}


void ImplAAFTypeDefGenericCharacter::onSave(void* clientContext) const
{
  ImplAAFTypeDef::onSave(clientContext);
}


void ImplAAFTypeDefGenericCharacter::onRestore(void* clientContext) const
{
  ImplAAFTypeDef::onRestore(clientContext);
}
