//@doc
//@class    AAFTypeDefGenericCharacter | Implementation class for AAFTypeDefGenericCharacter
#ifndef __ImplAAFTypeDefGenericCharacter_h__
#define __ImplAAFTypeDefGenericCharacter_h__


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



class ImplAAFPropertyValue;
class OMTypeVisitor;





#ifndef __ImplAAFTypeDef_h__
#include "ImplAAFTypeDef.h"
#endif

#include "OMCharacterType.h"
#include "OMFixedSizeProperty.h"


class ImplAAFTypeDefGenericCharacter : public ImplAAFTypeDef, public OMCharacterType
{
public:
	ImplAAFTypeDefGenericCharacter();

	AAFRESULT STDMETHODCALLTYPE Initialize(const aafUID_t& id,
										   aafUInt8 size,
										   const aafCharacter* pTypeName,
										   const aafCharacter* pTypeDescription);

protected:
	virtual ~ImplAAFTypeDefGenericCharacter();

	virtual AAFRESULT STDMETHODCALLTYPE GetTypeCategory(eAAFTypeCategory_t* pTid);

	//
	// OMDefinition methods
	//

	virtual const OMUniqueObjectIdentification& identification() const;

	virtual const wchar_t* name() const;

	virtual bool hasDescription() const;

	virtual const wchar_t* description() const;

	virtual bool isPredefined() const;


	//
	// OMType methods
	//

	virtual bool isFixedSize() const;

	virtual void reorder(OMByte* externalBytes,
						OMUInt32 externalBytesSize) const;

	virtual OMUInt32 externalSize(const OMByte* internalBytes,
								OMUInt32 internalBytesSize) const;

	virtual OMUInt32 externalSize() const;

	virtual void externalize(const OMByte* internalBytes,
							OMUInt32 internalBytesSize,
							OMByte* externalBytes,
							OMUInt32 externalBytesSize,
							OMByteOrder byteOrder) const;

	virtual OMUInt32 internalSize(const OMByte* externalBytes,
								OMUInt32 externalSize) const;

	virtual OMUInt32 internalSize() const;

	virtual void internalize(const OMByte* externalBytes,
							OMUInt32 externalBytesSize,
							OMByte* internalBytes,
							OMUInt32 internalBytesSize,
							OMByteOrder byteOrder) const;

	virtual void accept(OMTypeVisitor& visitor) const;

	//
	// ImplAAFTypeDef methods
	//

	virtual aafBool IsFixedSize() const;
	virtual OMUInt32 PropValSize() const;
	virtual aafBool IsRegistered() const;
	virtual OMUInt32 NativeSize() const;

	virtual bool IsAggregatable() const;
	virtual bool IsStreamable() const;
	virtual bool IsFixedArrayable() const;
	virtual bool IsVariableArrayable() const;
	virtual bool IsStringable() const;

	//
	// OMStorable methods
	//

	virtual const OMClassId& classId(void) const;

	virtual void onSave(void* clientContext) const;
	virtual void onRestore(void* clientContext) const;

private:
	OMFixedSizeProperty<aafUInt8> _size;
};

#endif // ! __ImplAAFTypeDefGenericCharacter_h__


