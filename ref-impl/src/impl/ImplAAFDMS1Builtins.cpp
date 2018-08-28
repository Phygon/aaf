#include "AAFResult.h"
#include "AAFStoredObjectIDs.h"
#include "AAFTypeDefUIDs.h"
#include "AAFClassDefUIDs.h"
#include "AAFUtils.h"

#include "ImplAAFDMS1Builtins.h"

#include "OMAssertions.h"

/* ========================== DMS1TypeDefUIDs.h ========================== */

 /* tjb - bogus, probably harmless */
// {2FDE4395-5F54-46b7-AAD9-8526AC58DC56}
const aafUID_t kAAFTypeID_UInt8Array32 =
{0x2fde4395, 0x5f54, 0x46b7, {0xaa, 0xd9, 0x85, 0x26, 0xac, 0x58, 0xdc, 0x56}};

 /* tjb - bogus, probably harmless */
// {48764AC9-6BA0-44b7-9F8B-8D48BB6DC0BB}
const aafUID_t kAAFTypeID_DMS1ProjectStrongReference =
{0x48764ac9, 0x6ba0, 0x44b7, {0x9f, 0x8b, 0x8d, 0x48, 0xbb, 0x6d, 0xc0, 0xbb}};

 /* tjb - bogus, probably harmless */
// {6524B9A8-ECD2-4149-8F91-3A511267638F}
const aafUID_t kAAFTypeID_DMS1PersonStrongReference =
{0x6524b9a8, 0xecd2, 0x4149, {0x8f, 0x91, 0x3a, 0x51, 0x12, 0x67, 0x63, 0x8f}};

 /* tjb - bogus, probably harmless */
 /* tjb - actually represented by a variable array */
// {92F0FEE4-7661-4394-85E0-2D597581244D}
const aafUID_t kAAFTypeID_DMS1PersonWeakReferenceSet =
{0x92f0fee4, 0x7661, 0x4394, {0x85, 0xe0, 0x2d, 0x59, 0x75, 0x81, 0x24, 0x4d}};

 /* tjb - bogus, probably harmless */
 /* tjb - actually represented by a variable array */
// {C0607458-49AD-49b8-9399-DD5976E7F71C}
const aafUID_t kAAFTypeID_DMS1ParticipantStrongReferenceSet =
{0xc0607458, 0x49ad, 0x49b8, {0x93, 0x99, 0xdd, 0x59, 0x76, 0xe7, 0xf7, 0x1c}};

 /* tjb - bogus, probably harmless */
// {0C34AD36-996B-4c6b-8297-B3B915E7E524}
const aafUID_t kAAFTypeID_DMS1ParticipantStrongReference =
{0x0c34ad36, 0x996b, 0x4c6b, {0x82, 0x97, 0xb3, 0xb9, 0x15, 0xe7, 0xe5, 0x24}};

/* ========================== DMS1PropertyDefUIDs.h ====================== */

  // 06.0e.2b.34.01.01.01.01.01.05.06.00.00.00.00.00
  // {01050600-0000-0000-060e-2b3401010101}
const aafUID_t kAAFPropID_DMS1SceneFramework_SceneNumber =
{0x01050600, 0x0000, 0x0000, {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x01}};

  // 06.0e.2b.34.01.01.01.01.01.05.07.00.00.00.00.00
  // {01050700-0000-0000-060e-2b3401010101}
const aafUID_t kAAFPropID_DMS1ClipFramework_TakeNumber =
{0x01050700, 0x0000, 0x0000, {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x01}};

  // 06.0e.2b.34.01.01.01.05.06.01.01.04.02.40.21.00
  // {06010104-0240-2100-060e-2b3401010105}
const aafUID_t kAAFPropID_DMS1ClipFramework_Projects =
{0x06010104,0x0240, 0x2100, {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x05}};

  // 06.0e.2b.34.01.01.01.05.06.01.01.04.05.40.13.00
  // {06010104-0540-1300-060e-2b3401010105}
const aafUID_t kAAFPropID_DMS1ClipFramework_Participants =
{0x06010104, 0x0540, 0x1300, {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x05}};

  // 06.0e.2b.34.01.01.01.02.01.03.01.06.00.00.00.00
  // {01030106-0000-0000-060e-2b3401010102}
const aafUID_t kAAFPropID_DMS1Project_Number =
{0x01030106, 0x0000, 0x0000, {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x02}};

  // 06.0e.2b.34.01.01.01.05.01.03.01.08.01.00.00.00
  // {01030108-0100-0000-060e-2b3401010105}
const aafUID_t kAAFPropID_DMS1Project_Name =
{0x01030108, 0x0100, 0x0000, {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x05}};

  // 06.0e.2b.34.01.01.01.03.02.30.06.03.01.01.01.00
  // {02300603-0101-0100-060e-2b3401010103}
const aafUID_t kAAFPropID_DMS1Person_FamilyName = 
{0x02300603, 0x0101, 0x0100, {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x03}};

  // 06.0e.2b.34.01.01.01.03.02.30.06.03.01.02.01.00
  // {02300603-0102-0100-060e-2b3401010103}
const aafUID_t kAAFPropID_DMS1Person_FirstGivenName =
{0x02300603, 0x0102, 0x0100, {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x03}};

  // 06.0e.2b.34.01.01.01.05.06.01.01.04.03.40.14.00
  // {06010104-0340-1400-060e-2b3401010105}
const aafUID_t kAAFPropID_DMS1Participant_People = 
{0x06010104, 0x0340, 0x1400, {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x05}};

/* ========================== DMS1ClassDefUIDs.h ========================= */

// Framework [ == AAFDescriptiveFramework]
//   SceneFramework
//   ProductionClipFrameWork [Abstract]
//     ClipFramework
//
// Set [ == AAFDescriptiveObject ]
//   Project
//   TextLanguage [Abstract]
//     Thesaurus [Abstract]
//       Contact [Abstract]
//         Person
//       Participant
//   ContactsList
//

  // {0D010401-0101-0300-060E-2B3402060101
  // 06.0E.2B.34.02.53.01.01.0D.01.04.01.01.01.03.00
const aafUID_t kAAFClassID_DMS1SceneFramework =
{0x0D010401, 0x0101, 0x0300, {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x06, 0x01, 0x01}};

  // {0D010401-0101-0200-060E-2B3402060101
  // 06.0E.2B.34.02.53.01.01.0D.01.04.01.01.01.02.00
const aafUID_t kAAFClassID_DMS1ClipFramework =
{0x0D010401, 0x0101, 0x0200, {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x06, 0x01, 0x01}};

  // {0D010401-0120-0200-060E-2B3402060101
  // 06.0E.2B.34.02.53.01.01.0D.01.04.01.01.20.02.00
const aafUID_t kAAFClassID_DMS1Project =
{0x0D010401, 0x0120, 0x0200, {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x06, 0x01, 0x01}};

  // {0D010401-011A-0200-060E-2B3402060101
  // 06.0E.2B.34.02.53.01.01.0D.01.04.01.01.1A.02.00
const aafUID_t kAAFClassID_DMS1Person =
{0x0D010401, 0x011A, 0x0200, {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x06, 0x01, 0x01}};

  // {0D010401-0118-0100-060E-2B3402060101
  // 06.0E.2B.34.02.53.01.01.0D.01.04.01.01.18.01.00
const aafUID_t kAAFClassID_DMS1Participant =
{0x0D010401, 0x0118, 0x0100, {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x06, 0x01, 0x01}};

HRESULT AddClass(IAAFDictionary* pDictionary,
                 const aafUID_t&classID,
                 const wchar_t* className,
                 IAAFClassDef* pParentClass)
{
  HRESULT hr;

  IAAFClassDef* pNewClassDefinition = 0;
  hr = pDictionary->CreateMetaInstance(AUID_AAFClassDef,
                                       IID_IAAFClassDef,
                                       (IUnknown**) &pNewClassDefinition);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));

  hr = pNewClassDefinition->Initialize(classID,
	 			       pParentClass,
				       className,
				       kAAFTrue);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));

  hr = pDictionary->RegisterClassDef(pNewClassDefinition);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));

  pNewClassDefinition->Release();

  return AAFRESULT_SUCCESS;
}

HRESULT AddProperty(IAAFDictionary* pDictionary,
		    const aafUID_t& classDefinitionID,
		    const aafUID_t& propertyDefinitionID,
		    const wchar_t* propertyName,
		    const aafUID_t propertyTypeID)
{
  HRESULT hr;
  IAAFClassDef* pClassDefinition = 0;
  IAAFPropertyDef* pPropertyDefinition = 0;

  hr = pDictionary->LookupClassDef(classDefinitionID,
				   &pClassDefinition);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));

  hr = pClassDefinition->LookupPropertyDef(propertyDefinitionID,
					   &pPropertyDefinition);
  if (AAFRESULT_SUCCEEDED(hr)) {
    pPropertyDefinition->Release();
    pClassDefinition->Release();
  } else {
    IAAFTypeDef* pPropertyType = 0;
    hr = pDictionary->LookupTypeDef(propertyTypeID,
				    &pPropertyType);
    ASSERTU(AAFRESULT_SUCCEEDED(hr));

    hr = pClassDefinition->RegisterOptionalPropertyDef(propertyDefinitionID,
						       propertyName,
						       pPropertyType,
						       &pPropertyDefinition);
    ASSERTU(AAFRESULT_SUCCEEDED(hr));

    pPropertyDefinition->Release();
    pPropertyType->Release();
    pClassDefinition->Release();
  }
  return AAFRESULT_SUCCESS;
}

HRESULT AddVariableArrayType(IAAFDictionary* pDictionary,
                             const aafUID_t& variableArrayTypeID,
                             const wchar_t* variableArrayTypeName,
		             IAAFTypeDef* pElementType)
{
  HRESULT hr;
  IAAFTypeDefVariableArray* pVariableArrayType = 0;
  hr = pDictionary->CreateMetaInstance(AUID_AAFTypeDefVariableArray,
                                       IID_IAAFTypeDefVariableArray,
                                       (IUnknown **) &pVariableArrayType);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));

  hr = pVariableArrayType->Initialize(variableArrayTypeID,
                                      pElementType,
                                      variableArrayTypeName);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));

  IAAFTypeDef* pTypeDef = 0;
  hr = pVariableArrayType->QueryInterface(IID_IAAFTypeDef, (void**)&pTypeDef);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));
  hr = pDictionary->RegisterTypeDef(pTypeDef);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));
  pTypeDef->Release();
  pVariableArrayType->Release();
  return AAFRESULT_SUCCESS;
}

HRESULT AddFixedArrayType(IAAFDictionary* pDictionary,
                          const aafUID_t& fixedArrayTypeID,
                          const wchar_t* fixedArrayTypeName,
		          IAAFTypeDef* pElementType,
                          aafUInt32 elementCount)
{
  HRESULT hr;
  IAAFTypeDefFixedArray* pFixedArrayType = 0;
  hr = pDictionary->CreateMetaInstance(AUID_AAFTypeDefFixedArray,
                                       IID_IAAFTypeDefFixedArray,
                                       (IUnknown **) &pFixedArrayType);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));

  hr = pFixedArrayType->Initialize(fixedArrayTypeID,
                                   pElementType,
                                   elementCount,
                                   fixedArrayTypeName);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));
  IAAFTypeDef* pTypeDef = 0;
  hr = pFixedArrayType->QueryInterface(IID_IAAFTypeDef, (void**)&pTypeDef);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));
  hr = pDictionary->RegisterTypeDef(pTypeDef);
  ASSERTU(AAFRESULT_SUCCEEDED(hr));
  pTypeDef->Release();
  pFixedArrayType->Release();
  return AAFRESULT_SUCCESS;
}

HRESULT AddObjectReferenceType(IAAFDictionary* pDictionary,
			       const aafUID_t& objectReferenceTypeID,
			       const wchar_t* objectReferenceTypeName,
			       const aafUID_t& referencedObjectID)
{
  HRESULT hr;
  IAAFTypeDef* pTypeDef = 0;

  hr = pDictionary->LookupTypeDef(objectReferenceTypeID, &pTypeDef);
  if (AAFRESULT_SUCCEEDED(hr)) {
    pTypeDef->Release();
  } else {
    IAAFTypeDefStrongObjRef* pTypeDefStrongObjRef = 0;
    hr = pDictionary->CreateMetaInstance(AUID_AAFTypeDefStrongObjRef,
					 IID_IAAFTypeDefStrongObjRef,
					 (IUnknown**) &pTypeDefStrongObjRef);
    ASSERTU(AAFRESULT_SUCCEEDED(hr));

    IAAFClassDef* pClassDefinition;
    hr = pDictionary->LookupClassDef(referencedObjectID,
				     &pClassDefinition);
    ASSERTU(AAFRESULT_SUCCEEDED(hr));

    hr = pTypeDefStrongObjRef->Initialize(objectReferenceTypeID,
					  pClassDefinition,
					  objectReferenceTypeName);
    ASSERTU(AAFRESULT_SUCCEEDED(hr));

    hr = pTypeDefStrongObjRef->QueryInterface(IID_IAAFTypeDef,
					      (void **)&pTypeDef);
    ASSERTU(AAFRESULT_SUCCEEDED(hr));

    hr = pDictionary->RegisterTypeDef(pTypeDef);
    ASSERTU(AAFRESULT_SUCCEEDED(hr));

    pClassDefinition->Release();
    pTypeDefStrongObjRef->Release();
    pTypeDef->Release();
  }
  return AAFRESULT_SUCCESS;
}

AAFRESULT DMS1RegisterDefinitions(IAAFDictionary* pDictionary)
{
  HRESULT hr;

// DMS1 attachment points in the AAF object model

  IAAFClassDef* pInterchangeObject = 0;
  hr = pDictionary->LookupClassDef(kAAFClassID_InterchangeObject,
                                   &pInterchangeObject);

  // AAFDescriptiveObject
  hr = AddClass(pDictionary,
                kAAFClassID_DescriptiveObject,
                L"DescriptiveObject",
                pInterchangeObject);

  IAAFClassDef* pDescriptiveObject = 0;
  hr = pDictionary->LookupClassDef(kAAFClassID_DescriptiveObject,
                                   &pDescriptiveObject);
// Classes

  // Project
  hr = AddClass(pDictionary,
                kAAFClassID_DMS1Project,
                L"DMS1Project",
                pDescriptiveObject);


  IAAFTypeDef* pElementType = 0;
  hr = pDictionary->LookupTypeDef(kAAFTypeID_UInt8, &pElementType);
  hr = AddFixedArrayType(pDictionary,
                         kAAFTypeID_UInt8Array32,
                         L"UInt8Array32",
		         pElementType,
                         32);
  pElementType->Release();
  pElementType = 0;

  hr = AddProperty(pDictionary,
                   kAAFClassID_DMS1Project,
                   kAAFPropID_DMS1Project_Number,
                   L"Number",
                   kAAFTypeID_UInt8Array32);

  hr = AddProperty(pDictionary,
                   kAAFClassID_DMS1Project,
                   kAAFPropID_DMS1Project_Name,
                   L"Name",
                   kAAFTypeID_String);

  IAAFClassDef* pDescriptiveFramework = 0;
  hr = pDictionary->LookupClassDef(kAAFClassID_DescriptiveFramework,
                                   &pDescriptiveFramework);
  // SceneFramework
  hr = AddClass(pDictionary,
                kAAFClassID_DMS1SceneFramework,
                L"DMS1SceneFramework",
                pDescriptiveFramework);

  hr = AddProperty(pDictionary,
                   kAAFClassID_DMS1SceneFramework,
                   kAAFPropID_DMS1SceneFramework_SceneNumber,
                   L"SceneNumber",
                   kAAFTypeID_UInt8Array32);
  //Person
  hr = AddClass(pDictionary,
                kAAFClassID_DMS1Person,
                L"DMS1Person",
                pDescriptiveObject);


  hr = AddProperty(pDictionary,
                   kAAFClassID_DMS1Person,
                   kAAFPropID_DMS1Person_FirstGivenName,
                   L"FirstGivenName",
                   kAAFTypeID_String);

  hr = AddProperty(pDictionary,
                   kAAFClassID_DMS1Person,
                   kAAFPropID_DMS1Person_FamilyName,
                   L"FamilyName",
                   kAAFTypeID_String);
//Participant
  hr = AddClass(pDictionary,
                kAAFClassID_DMS1Participant,
                L"DMS1Participant",
                pDescriptiveObject);

  hr = AddObjectReferenceType(pDictionary,
			      kAAFTypeID_DMS1PersonStrongReference,
			      L"StrongReference<Project>",
		              kAAFClassID_DMS1Person);

  IAAFTypeDef* pSetElementType = 0;
  hr = pDictionary->LookupTypeDef(kAAFTypeID_DMS1PersonStrongReference,
                                  &pSetElementType);
  hr = AddVariableArrayType(pDictionary,
			    kAAFTypeID_DMS1PersonWeakReferenceSet,
			    L"WeakReferenceSet<DMS1Person>",
			    pSetElementType);
  pSetElementType->Release();
  pSetElementType = 0;

  hr = AddProperty(pDictionary,
                   kAAFClassID_DMS1Participant,
                   kAAFPropID_DMS1Participant_People,
                   L"People",
                   kAAFTypeID_DMS1PersonWeakReferenceSet);
  //ClipFramework
  hr = AddClass(pDictionary,
                kAAFClassID_DMS1ClipFramework,
                L"DMS1ClipFramework",
                pDescriptiveFramework);

  hr = AddProperty(pDictionary,
                   kAAFClassID_DMS1ClipFramework,
                   kAAFPropID_DMS1ClipFramework_TakeNumber,
                   L"TakeNumber",
                   kAAFTypeID_UInt16);

  hr = AddObjectReferenceType(pDictionary,
			      kAAFTypeID_DMS1ProjectStrongReference,
			      L"StrongReference<DMS1Project>",
		              kAAFClassID_DMS1Project);

  hr = AddProperty(pDictionary,
                   kAAFClassID_DMS1ClipFramework,
                   kAAFPropID_DMS1ClipFramework_Projects,
                   L"Projects",
                   kAAFTypeID_DMS1ProjectStrongReference);
  hr = AddObjectReferenceType(pDictionary,
			      kAAFTypeID_DMS1ParticipantStrongReference,
			      L"StrongReference<Participant>",
		              kAAFClassID_DMS1Participant);
  hr = pDictionary->LookupTypeDef(kAAFTypeID_DMS1ParticipantStrongReference,
                                  &pSetElementType);
  hr = AddVariableArrayType(pDictionary,
			    kAAFTypeID_DMS1ParticipantStrongReferenceSet,
			    L"StrongReferenceSet<DMS1Participant>",
			    pSetElementType);
  pSetElementType->Release();
  pSetElementType = 0;

  hr = AddProperty(pDictionary,
                   kAAFClassID_DMS1ClipFramework,
                   kAAFPropID_DMS1ClipFramework_Participants,
                   L"Participants",
                   kAAFTypeID_DMS1ParticipantStrongReferenceSet);

  pDescriptiveFramework->Release();
  pDescriptiveObject->Release();
  pInterchangeObject->Release();
  return AAFRESULT_SUCCESS;
}

bool IsDMS1ClassDefinition(const aafUID_t& classID)
{
  bool result = false;

  if( classID == kAAFClassID_DMS1SceneFramework ||
      classID == kAAFClassID_DMS1ClipFramework ||
      classID == kAAFClassID_DescriptiveObject ||
      classID == kAAFClassID_DMS1Project ||
      classID == kAAFClassID_DMS1Person ||
      classID == kAAFClassID_DMS1Participant )
  {
    result = true;
  }

  return result;
}

bool IsDMS1TypeDefinition(const aafUID_t& typeID)
{
  bool result = false;

  if (typeID == kAAFTypeID_UInt8Array32 ||
      typeID == kAAFTypeID_DMS1ProjectStrongReference ||
      typeID == kAAFTypeID_DMS1PersonStrongReference ||
      typeID == kAAFTypeID_DMS1PersonWeakReferenceSet ||
      typeID == kAAFTypeID_DMS1ParticipantStrongReferenceSet ||
      typeID == kAAFTypeID_DMS1ParticipantStrongReference)
  {
    result = true;
  }

  return result;
}
