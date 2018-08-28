//=---------------------------------------------------------------------=
//
// $Id$ $Name$
//
// The contents of this file are subject to the AAF SDK Public Source
// License Agreement Version 2.0 (the "License"); You may not use this
// file except in compliance with the License.  The License is available
// in AAFSDKPSL.TXT, or you may obtain a copy of the License from the
// Advanced Media Workflow Association, Inc., or its successor.
//
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.  Refer to Section 3.3 of the License for proper use
// of this Exhibit.
//
// WARNING:  Please contact the Advanced Media Workflow Association,
// Inc., for more information about any additional licenses to
// intellectual property covering the AAF Standard that may be required
// to create and distribute AAF compliant products.
// (http://www.amwa.tv/policies).
//
// Copyright Notices:
// The Original Code of this file is Copyright 1998-2009, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
// The Initial Developer of the Original Code of this file and the
// licensor of the Advanced Media Workflow Association is
// Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

#include "AAF.h"
#include "AAFResult.h"
#include "ModuleTest.h"

#include "AAFStoredObjectIDs.h"
#include "AAFTypeDefUIDs.h"
#include "AAFDefUIDs.h"

#include "CAAFBuiltinDefs.h"
#include "AAFSmartPointer.h"
typedef IAAFSmartPointer<IUnknown>                  IUnknownSP;
typedef IAAFSmartPointer<IAAFFile>                  IAAFFileSP;
typedef IAAFSmartPointer<IAAFHeader>                IAAFHeaderSP;
typedef IAAFSmartPointer<IAAFDictionary>            IAAFDictionarySP;
typedef IAAFSmartPointer<IAAFObject>                IAAFObjectSP;
typedef IAAFSmartPointer<IAAFClassDef>              IAAFClassDefSP;
typedef IAAFSmartPointer<IAAFPropertyDef>           IAAFPropertyDefSP;
typedef IAAFSmartPointer<IAAFPropertyValue>         IAAFPropertyValueSP;
typedef IAAFSmartPointer<IAAFTypeDef>               IAAFTypeDefSP;
typedef IAAFSmartPointer<IAAFTypeDefIndirect>       IAAFTypeDefIndirectSP;
typedef IAAFSmartPointer<IAAFTypeDefInt>			IAAFTypeDefIntSP;
typedef IAAFSmartPointer<IAAFTypeDefRename>			IAAFTypeDefRenameSP;
typedef IAAFSmartPointer<IAAFTypeDefString>			IAAFTypeDefStringSP;
typedef IAAFSmartPointer<IAAFTypeDefVariableArray>	IAAFTypeDefVariableArraySP;
typedef IAAFSmartPointer<IAAFMob>                   IAAFMobSP;
typedef IAAFSmartPointer<IAAFTimelineMobSlot>       IAAFTimelineMobSlotSP;
typedef IAAFSmartPointer<IAAFMobSlot>               IAAFMobSlotSP;
typedef IAAFSmartPointer<IAAFSequence>              IAAFSequenceSP;
typedef IAAFSmartPointer<IAAFSegment>               IAAFSegmentSP;
typedef IAAFSmartPointer<IAAFComponent>             IAAFComponentSP;
typedef IAAFSmartPointer<IAAFTypeDefEnum>           IAAFTypeDefEnumSP;
typedef IAAFSmartPointer<IAAFTypeDefRecord>         IAAFTypeDefRecordSP;


#include <iostream>
#include <iomanip>
using namespace std;
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "AAFWideString.h"

// Required function prototypes
extern "C"
{
  // Main test function.
  HRESULT CAAFTypeDefIndirect_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);
}
  // Create the test file.
  void CAAFTypeDefIndirect_create (
     aafCharacter_constptr pFileName,
     aafUID_constref fileKind,
     testRawStorageType_t rawStorageType,
     aafProductIdentification_constref productID); // throw HRESULT

  // Open the test file read only and validate the data.
  void CAAFTypeDefIndirect_read (aafCharacter_constptr pFileName); // throw HRESULT

extern "C" HRESULT CAAFTypeDefIndirect_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID)
{
  HRESULT result = AAFRESULT_SUCCESS;
  const size_t fileNameBufLen = 128;
  aafCharacter wFileName[ fileNameBufLen ] = L"";
  GenerateTestFileName( productID.productName, fileKind, fileNameBufLen, wFileName );

  try
  {
    // Run through a basic set of tests. Create the file, then read it
    // back and validate it.

	if(mode == kAAFUnitTestReadWrite)
   		 CAAFTypeDefIndirect_create (wFileName, fileKind, rawStorageType, productID);
    CAAFTypeDefIndirect_read (wFileName);
  }
  catch (HRESULT &rhr)
  {
    result = rhr;
  }

  return (result);
}


//
// Constants for new property definitions
//
#define NUM_COMPONENT_ANNOTATION_PROPERTIES 10
static const aafUID_t kComponentAnnotationPIDs[
	NUM_COMPONENT_ANNOTATION_PROPERTIES]=
{
	{0x3feec650, 0xf579, 0x11d3, 
		{ 0x94, 0xed, 0x0, 0x60, 0x97, 0xfe, 0x2b, 0xa5 }},
	{0x3feec651, 0xf579, 0x11d3, 
		{ 0x94, 0xed, 0x0, 0x60, 0x97, 0xfe, 0x2b, 0xa5 }},
	{0xe39670a0, 0x566b, 0x11d4, 
		{ 0x92, 0x29, 0x0, 0x50, 0x4, 0x9c, 0x3b, 0x9d }},
	{0xd1854d0, 0x5675, 0x11d4,  
		{ 0x92, 0x29, 0x0, 0x50, 0x4, 0x9c, 0x3b, 0x9d }},
	{0x1f23b4a0, 0x5675, 0x11d4, 
		{ 0x92, 0x29, 0x0, 0x50, 0x4, 0x9c, 0x3b, 0x9d }},
	{0x3ee82080, 0x5675, 0x11d4, 
		{ 0x92, 0x29, 0x0, 0x50, 0x4, 0x9c, 0x3b, 0x9d }},
	{0x2185fa3e, 0xdb1d, 0x45d4,
		{ 0xaa, 0x77, 0x2f, 0x80, 0x80, 0x68, 0xc6, 0x07 }},
	{0x2a021ead, 0x65ed, 0x43e2,
		{ 0xa1, 0xc2, 0xe7, 0x52, 0x6a, 0x16, 0x1c, 0xc9 }},
	{0x0f3d758b, 0x2e8c, 0x45ea,
		{ 0x9d, 0xe8, 0x38, 0x9b, 0x67, 0x14, 0xed, 0xf7 }},
	{0x218583ac, 0xfd29, 0x45c4,
		{ 0x94, 0xa3, 0x06, 0xcb, 0x28, 0xf5, 0x15, 0x22 }}
};

// AUID of renamed type we will create
static const aafUID_t kAUID_Word = 
{ 0x548be260, 0x566d, 0x11d4, { 0x92, 0x29, 0x0, 0x50, 0x4, 0x9c, 0x3b, 0x9d } };

static aafCharacter_constptr kSequenceAnnotation1 = 
  L"Sequence - Component Annotation 1 - as a unicode string";
static const char kSequenceAnnotation2[] = 
   "Sequence - Component Annotation 2 - as array of UInt8";
static aafUInt16 kSequenceAnnotation3=5;
static const enum CustomEnum {Hot=66, Cold=77} kSequenceAnnotation6=Hot;
static const struct CustomRecord
{
	signed char a;
	unsigned char b;
	bool operator ==(const CustomRecord& x) const {return (a==x.a && b==x.b);}
} kSequenceAnnotation8={-22,33};

// AUID of enum type we will create
static const aafUID_t kAUID_CustomEnum = 
{ 0xbbe9bacd, 0xcdec, 0x47f0, { 0x8a, 0xc6, 0xbe, 0x25, 0x73, 0xc5, 0xe8, 0x5d } };

// AUID of record type we will create
static const aafUID_t kAUID_CustomRecord = 
{ 0x7a375fe9, 0x2667, 0x4b6d, { 0x89, 0x25, 0xe8, 0xdf, 0x4f, 0xab, 0x5b, 0x0d } };

// The test mob id that we added...
static const 	aafMobID_t	sTestMob =
{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
0x13, 0x00, 0x00, 0x00,
{0x37c13606, 0x0405, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}};

#ifndef _DEBUG
// convenient error handlers.
inline void checkResult(HRESULT r)
{
  if (FAILED(r))
    throw r;
}
inline void checkExpression(bool expression, HRESULT r)
{
  if (!expression)
    throw r;
}

#else // #ifndef _DEBUG

// convenient error handlers.
#define checkResult(r)\
do {\
  if (FAILED(r))\
  {\
    cerr << "FILE:" << __FILE__ << " LINE:" << __LINE__ << " Error code = " << hex << r << dec << endl;\
    throw (HRESULT)r;\
  }\
} while (false)

#define checkExpression(expression, r)\
do {\
  if (!(expression))\
  {\
    cerr << "FILE:" << __FILE__ << " LINE:" << __LINE__ << " Expression failed = " << #expression << endl;\
    throw (HRESULT)r;\
  }\
} while (false)

#endif // #else // #ifndef _DEBUG

static void Test_ObjectEquality(IUnknown *obj1, IUnknown *obj2)
{
  // The only way to test object equality in COM is to compare IUnknown
  // interface pointers.
  checkExpression (obj1 && obj2, AAFRESULT_TEST_FAILED);

  IUnknownSP pUnknown1, pUnknown2;
  checkResult (obj1->QueryInterface (IID_IUnknown, (void **)&pUnknown1));
  checkResult (obj2->QueryInterface (IID_IUnknown, (void **)&pUnknown2));
  checkExpression (pUnknown1 == pUnknown2, AAFRESULT_TEST_FAILED);  
}

static void Test_RegisterIndirectComponentAnnotations (
  IAAFDictionary * pDictionary)
{
  //
  // Create an and register the new indirect properties.
  //

  // Get type definition for indirect type and verify that the 
  // type is an indirect type.
  IAAFTypeDefSP pIndirectType;
  IAAFTypeDefIndirectSP pTypeDefIndirect;
  checkResult (pDictionary->LookupTypeDef (kAAFTypeID_Indirect, &pIndirectType));
  checkResult (pIndirectType->QueryInterface (IID_IAAFTypeDefIndirect, (void**)&pTypeDefIndirect));

  // Look up the class definition for components class
  IAAFClassDefSP pComponentClass;
  checkResult (pDictionary->LookupClassDef (AUID_AAFComponent, &pComponentClass));

  // Initialize new properties
  IAAFPropertyDefSP pComponentAnnotationPropertyDef;
  int n;
  for(n=0;n<NUM_COMPONENT_ANNOTATION_PROPERTIES;n++)
	checkResult (pComponentClass->RegisterOptionalPropertyDef (
                                  kComponentAnnotationPIDs[n],
                                  L"Indirect Component Annotation",
                                  pIndirectType,
                                  &pComponentAnnotationPropertyDef));
}

static void Test_LookupIndirectComponentAnnotations (
  IAAFDictionary * pDictionary,
  IAAFPropertyDefSP *ppComponentAnnotationPropertyDefs)
{
  // Find the class definition for components class
  IAAFClassDefSP pComponentClass;
  checkResult (pDictionary->LookupClassDef (AUID_AAFComponent, &pComponentClass));

  // Find our property definitions
  int n;
  for(n=0;n<NUM_COMPONENT_ANNOTATION_PROPERTIES;n++)
  {
    checkResult (pComponentClass->LookupPropertyDef(
										kComponentAnnotationPIDs[n],
										&(ppComponentAnnotationPropertyDefs[n])));
    checkExpression(ppComponentAnnotationPropertyDefs[n]!=0,
		AAFRESULT_TEST_FAILED);
  }
}


//
// The type of an indirect property MUST be an indirect type
//
static void Test_GetIndirectTypeFromPropertyDef (
  IAAFPropertyDef * pIndirectPropertyDef,
  IAAFTypeDefIndirect **ppTypeDefIndirect)
{
  IAAFTypeDefSP pIndirectPropertyDefType;
  checkResult (pIndirectPropertyDef->GetTypeDef (&pIndirectPropertyDefType));  
  checkResult (pIndirectPropertyDefType->QueryInterface (IID_IAAFTypeDefIndirect,
                                                         (void**)ppTypeDefIndirect));
}


//
// Test to create and initialize an indirect property with the
// IAAFTypeDefIndirect::CreateValueFromActualData method.
//
static void Test_CreateValueFromActualData (
  IUnknown *pUknownObject,
  IAAFPropertyDef * pIndirectPropertyDef,
  IAAFTypeDef *pActualType,
  aafUInt32 actualDataSize,
  aafDataBuffer_t actualData)
{
  IAAFObjectSP pObject;
  IAAFTypeDefIndirectSP pTypeDefIndirect;
  IAAFPropertyValueSP pIndirectValue;

  
  // Use the direct access interface to set the value.
  checkResult (pUknownObject->QueryInterface (IID_IAAFObject, (void**)&pObject));

  Test_GetIndirectTypeFromPropertyDef (pIndirectPropertyDef, &pTypeDefIndirect);

  // Test the method...
  checkResult (pTypeDefIndirect->CreateValueFromActualData (
                                pActualType,
                                actualData,
                                actualDataSize,
                                &pIndirectValue));

  // Set the value.
  checkResult (pObject->SetPropertyValue (pIndirectPropertyDef, pIndirectValue));
}

static void Test_CreateValueFromActualValue(IAAFDictionary *pDictionary,
											IUnknown *pUnknown,
											IAAFPropertyDef *pPropertyDef,
											IAAFPropertyValue *pActualValue)
{
  CAAFBuiltinDefs defs(pDictionary);

  IAAFPropertyValueSP pIndirectValue;
  IAAFTypeDefIndirectSP pTypeDefIndirect;
  checkResult(defs.tdIndirect()->QueryInterface(IID_IAAFTypeDefIndirect,
	  (void**)&pTypeDefIndirect));
  checkResult(pTypeDefIndirect->CreateValueFromActualValue(
	  pActualValue,&pIndirectValue));
  IAAFObjectSP pObject;
  checkResult(pUnknown->QueryInterface(IID_IAAFObject,(void**)&pObject));
  checkResult(pObject->SetPropertyValue(pPropertyDef,pIndirectValue));
}

//
// Test to create and initialize an indirect property with the
// IAAFTypeDefIndirect::GetActualData method.
//
static aafUInt32 Test_GetActualSize (
  IUnknown *pUknownObject,
  IAAFPropertyDef * pIndirectPropertyDef,
  aafUInt32 /*expectedDataSize*/)
{
  IAAFObjectSP pObject;
  IAAFTypeDefIndirectSP pTypeDefIndirect;
  IAAFPropertyValueSP pIndirectValue;
  aafUInt32 actualDataSize = 0;

  
  // Use the direct access interface to set the value.
  checkResult (pUknownObject->QueryInterface (IID_IAAFObject, (void**)&pObject));

  Test_GetIndirectTypeFromPropertyDef (pIndirectPropertyDef, &pTypeDefIndirect);

  // Set the value.
  checkResult (pObject->GetPropertyValue (pIndirectPropertyDef, &pIndirectValue));

  // Test the method...
  checkResult (pTypeDefIndirect->GetActualSize (
                                pIndirectValue,
                                &actualDataSize));
  checkExpression (actualDataSize == actualDataSize, AAFRESULT_TEST_FAILED);
  
  return (actualDataSize);
}


//
// Test to create and initialize an indirect property with the
// IAAFTypeDefIndirect::GetActualData method.
//
static void Test_GetActualType (
  IUnknown *pUknownObject,
  IAAFPropertyDef * pIndirectPropertyDef,
  IAAFTypeDef ** ppActualType)
{
  IAAFObjectSP pObject;
  IAAFTypeDefIndirectSP pTypeDefIndirect;
  IAAFPropertyValueSP pIndirectValue;

  
  // Use the direct access interface to set the value.
  checkResult (pUknownObject->QueryInterface (IID_IAAFObject, (void**)&pObject));

  Test_GetIndirectTypeFromPropertyDef (pIndirectPropertyDef, &pTypeDefIndirect);

  // Set the value.
  checkResult (pObject->GetPropertyValue (pIndirectPropertyDef, &pIndirectValue));

  // Test the method...
  checkResult (pTypeDefIndirect->GetActualType (
                                pIndirectValue,
                                ppActualType));
}


//
// Test to create and initialize an indirect property with the
// IAAFTypeDefIndirect::GetActualData method.
//
static void Test_GetActualData (
  IUnknown *pUknownObject,
  IAAFPropertyDef * pIndirectPropertyDef,
  IAAFTypeDef * /*pActualType*/,
  aafUInt32 actualDataSize,
  aafDataBuffer_t actualData)
{
  IAAFObjectSP pObject;
  IAAFTypeDefIndirectSP pTypeDefIndirect;
  IAAFPropertyValueSP pIndirectValue;

  
  // Use the direct access interface to set the value.
  checkResult (pUknownObject->QueryInterface (IID_IAAFObject, (void**)&pObject));

  Test_GetIndirectTypeFromPropertyDef (pIndirectPropertyDef, &pTypeDefIndirect);

  // Set the value.
  checkResult (pObject->GetPropertyValue (pIndirectPropertyDef, &pIndirectValue));

  // Test the method...
  checkResult (pTypeDefIndirect->GetActualData (
                                pIndirectValue,
                                actualData,
                                actualDataSize));

}

static void Test_GetActualValue(IUnknown *pUnknown,IAAFPropertyDef *pPropertyDef,
								IAAFPropertyValue **ppActualValue)
{
  IAAFObjectSP pObject;
  checkResult(pUnknown->QueryInterface(IID_IAAFObject,(void**)&pObject));
  IAAFPropertyValueSP pIndirectValue;
  checkResult(pObject->GetPropertyValue(pPropertyDef,&pIndirectValue));
  IAAFTypeDefSP pTypeDef;
  checkResult(pIndirectValue->GetType(&pTypeDef));
  IAAFTypeDefIndirectSP pTypeDefIndirect;
  checkResult(pTypeDef->QueryInterface(IID_IAAFTypeDefIndirect,
	  (void**)&pTypeDefIndirect));
  checkResult(pTypeDefIndirect->GetActualValue(pIndirectValue,ppActualValue));
  checkExpression(*ppActualValue!=0,AAFRESULT_TEST_FAILED);
}

static void Test_CreateUInt8ArrayValue (
  IAAFDictionary *pDictionary,
  const aafUInt8* pData,
  const aafUInt32 dataSize,
  IAAFPropertyValue** pValue)
{
  // Create actual property value of UInt8 array type
  IAAFTypeDefSP pTypeDef;
  checkResult(pDictionary->LookupTypeDef(kAAFTypeID_UInt8Array, &pTypeDef));
  IAAFTypeDefVariableArraySP pTypeDefVariableArray;
  checkResult(pTypeDef->QueryInterface(IID_IAAFTypeDefVariableArray,
	  (void**)&pTypeDefVariableArray));
  checkResult(pTypeDefVariableArray->CreateValueFromCArray(
	  (aafMemPtr_t)pData,
          dataSize,
	  pValue));
}

static void ValidatePropertyValue(IAAFDictionary *pDictionary,
	IUnknown *pUnknown,
	IAAFPropertyDef *pIndirectPropertyDef,
	aafUID_t const& kTypeID,
	aafDataBuffer_t pExpectedData,
	aafUInt32 expectedDataSize)
{
  IAAFObjectSP pObject;
  checkResult (pUnknown->QueryInterface(IID_IAAFObject,(void**)&pObject));

  IAAFTypeDefSP pExpectedType;
  checkResult (pDictionary->LookupTypeDef(kTypeID,&pExpectedType));

  Test_GetActualSize (
          pObject,
          pIndirectPropertyDef,
          expectedDataSize);

  IAAFTypeDefSP pActualType;
  Test_GetActualType (
          pObject,
          pIndirectPropertyDef,
          &pActualType);
  Test_ObjectEquality(pActualType,pExpectedType);

  unsigned char *pActualData=new unsigned char[expectedDataSize];
  Test_GetActualData (
          pObject,
          pIndirectPropertyDef,
          pExpectedType,
          expectedDataSize,
          (aafDataBuffer_t)pActualData);
  checkExpression(!memcmp(pActualData,pExpectedData,expectedDataSize),
	  AAFRESULT_TEST_FAILED);
  delete [] pActualData;
}

static void ValidateTestPropertyValues(IAAFDictionary *pDictionary,
									   IAAFSequence *pSequence)
{
  IAAFPropertyDefSP ppComponentAnnotationPropertyDefs[
	  NUM_COMPONENT_ANNOTATION_PROPERTIES];

  Test_LookupIndirectComponentAnnotations (pDictionary,
             ppComponentAnnotationPropertyDefs);

  // Validate property value of type kAAFTypeID_String created via
  // CreateValueFromActualData()
  ValidatePropertyValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[0],kAAFTypeID_String,
	  (aafDataBuffer_t)kSequenceAnnotation1,
	  sizeof(wchar_t)*(wcslen(kSequenceAnnotation1)+1));

  // Validate property value of type kAAFTypeID_UInt8Array created via
  // CreateValueFromActualData()
  ValidatePropertyValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[1],kAAFTypeID_UInt8Array,
	  (aafDataBuffer_t)kSequenceAnnotation2,
	  strlen(kSequenceAnnotation2)+1);

  // Validate property value of renamed type created via 
  // CreateValueFromActualData()
  ValidatePropertyValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[2],kAUID_Word,
	  (aafDataBuffer_t)&kSequenceAnnotation3,sizeof(aafUInt16));

  // Validate property value of type kAAFTypeID_String created via
  // CreateValueFromActualValue()
  ValidatePropertyValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[3],kAAFTypeID_String,
	  (aafDataBuffer_t)kSequenceAnnotation1,
	  sizeof(wchar_t)*(wcslen(kSequenceAnnotation1)+1));

  // Validate property value of type kAAFTypeID_UInt8Array created via
  // CreateValueFromActualValue()
  ValidatePropertyValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[4],kAAFTypeID_UInt8Array,
	  (aafDataBuffer_t)kSequenceAnnotation2,
	  strlen(kSequenceAnnotation2)+1);

  // Validate property value of renamed type created via 
  // CreateValueFromActualValue()
  ValidatePropertyValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[5],kAUID_Word,
	  (aafDataBuffer_t)&kSequenceAnnotation3,sizeof(aafUInt16));

  // Validate property value of enum type created via 
  // CreateValueFromActualData()
  ValidatePropertyValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[6],kAUID_CustomEnum,
	  (aafDataBuffer_t)&kSequenceAnnotation6,sizeof(CustomEnum));

  // Validate property value of enum type created via 
  // CreateValueFromActualValue()
  ValidatePropertyValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[7],kAUID_CustomEnum,
	  (aafDataBuffer_t)&kSequenceAnnotation6,sizeof(CustomEnum));

  // Validate property value of record type created via 
  // CreateValueFromActualData()
  ValidatePropertyValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[8],kAUID_CustomRecord,
	  (aafDataBuffer_t)&kSequenceAnnotation8,sizeof(CustomRecord));

  // Validate property value of record type created via 
  // CreateValueFromActualValue()
  ValidatePropertyValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[9],kAUID_CustomRecord,
	  (aafDataBuffer_t)&kSequenceAnnotation8,sizeof(CustomRecord));

  // Validate string property values via GetActualValue()
  int n;
  IAAFPropertyValueSP pActualValue;
  IAAFTypeDefSP pTypeDef;
  for(n=0;n<2;n++)
  {
	// Property defs 0 and 3 correspond to string properties
	Test_GetActualValue(pSequence,ppComponentAnnotationPropertyDefs[n==0?0:3],
		  &pActualValue);
	checkResult(pActualValue->GetType(&pTypeDef));
	IAAFTypeDefStringSP pTypeDefString;
	checkResult(pTypeDef->QueryInterface(IID_IAAFTypeDefString,
	  (void**)&pTypeDefString));
	aafUInt32 count;
	checkResult(pTypeDefString->GetCount(pActualValue,&count));
	checkExpression(count==wcslen(kSequenceAnnotation1)+1,AAFRESULT_TEST_FAILED);
	aafCharacter *pString=new aafCharacter[count];
	checkResult(pTypeDefString->GetElements(pActualValue,(aafMemPtr_t)pString,
	  count*sizeof(aafCharacter)));
	checkExpression(memcmp(pString,kSequenceAnnotation1,count*sizeof(aafCharacter))
	  ==0,AAFRESULT_TEST_FAILED);
	delete [] pString;
  }

  // Validate UInt8 array property value via GetActualValue()
  for(n=0;n<2;n++)
  {
	// Property defs 1 and 4 correspond to UInt8 array properties
	Test_GetActualValue(pSequence,ppComponentAnnotationPropertyDefs[n==0?1:4],
	  &pActualValue);
	checkResult(pActualValue->GetType(&pTypeDef));
	IAAFTypeDefVariableArraySP pTypeDefVariableArray;
	checkResult(pTypeDef->QueryInterface(IID_IAAFTypeDefVariableArray,
	  (void**)&pTypeDefVariableArray));
	aafUInt32 count;
	checkResult(pTypeDefVariableArray->GetCount(pActualValue,&count));
	checkExpression(count==strlen(kSequenceAnnotation2)+1,AAFRESULT_TEST_FAILED);
	aafUInt8 *pArray=new aafUInt8[count];
	checkResult(pTypeDefVariableArray->GetCArray(pActualValue,(aafMemPtr_t)pArray,
	  count*sizeof(aafUInt8)));
	checkExpression(memcmp(pArray,kSequenceAnnotation2,count*sizeof(aafUInt8))==0,
	  AAFRESULT_TEST_FAILED);
	delete [] pArray;
  }

  // Validate property value of renamed type via GetActualValue()
  for(n=0;n<2;n++)
  {
	// Property defs 2 and 5 correspond to renamed properties
	Test_GetActualValue(pSequence,ppComponentAnnotationPropertyDefs[n==0?2:5],
	  &pActualValue);
	checkResult(pActualValue->GetType(&pTypeDef));
	IAAFTypeDefRenameSP pTypeDefRename;
	checkResult(pTypeDef->QueryInterface(IID_IAAFTypeDefRename,
	  (void**)&pTypeDefRename));
	IAAFPropertyValueSP pBaseValue;
	checkResult(pTypeDefRename->GetBaseValue(pActualValue,&pBaseValue));
	checkResult(pBaseValue->GetType(&pTypeDef));
	IAAFTypeDefIntSP pTypeDefInt;
	checkResult(pTypeDef->QueryInterface(IID_IAAFTypeDefInt,(void**)&pTypeDefInt));
	aafUInt32 size;
	checkResult(pTypeDefInt->GetSize(&size));
	checkExpression(size==sizeof(aafUInt16),AAFRESULT_TEST_FAILED);
	aafUInt16 value;	
	checkResult(pTypeDefInt->GetInteger(pBaseValue,(aafMemPtr_t)&value,
	  sizeof(aafUInt16)));
	checkExpression(value==kSequenceAnnotation3,AAFRESULT_TEST_FAILED);
  }

  // Validate property value of enum type via GetActualValue()
  for(n=0;n<2;n++)
  {
	// Property defs 6 and 7 correspond to enum properties
	Test_GetActualValue(pSequence,ppComponentAnnotationPropertyDefs[n==0?6:7],
	  &pActualValue);
	checkResult(pActualValue->GetType(&pTypeDef));
	IAAFTypeDefEnumSP pTypeDefEnum;
	checkResult(pTypeDef->QueryInterface(IID_IAAFTypeDefEnum,
	  (void**)&pTypeDefEnum));
	aafInt64 value;
	checkResult(pTypeDefEnum->GetIntegerValue(pActualValue, &value));
	checkExpression(static_cast<CustomEnum>(value)==kSequenceAnnotation6,AAFRESULT_TEST_FAILED);
  }

  // Validate property value of record type via GetActualValue()
  for(n=0;n<2;n++)
  {
	// Property defs 8 and 9 correspond to record properties
    Test_GetActualValue(pSequence,ppComponentAnnotationPropertyDefs[n==0?8:9],
	  &pActualValue);
	checkResult(pActualValue->GetType(&pTypeDef));
	IAAFTypeDefRecordSP pTypeDefRecord;
	checkResult(pTypeDef->QueryInterface(IID_IAAFTypeDefRecord,
	  (void**)&pTypeDefRecord));
	CustomRecord value = {0, 0};
	checkResult(pTypeDefRecord->GetStruct(pActualValue, (aafMemPtr_t)&value, sizeof(CustomRecord)));
	checkExpression(value==kSequenceAnnotation8,AAFRESULT_TEST_FAILED);
  }
}

static void TestInvalidInputs (
	IAAFDictionary *pDictionary,
	IAAFSequence *pSequence)
{
  AAFRESULT hr = AAFRESULT_SUCCESS;
  IAAFTypeDefSP pTmpTypeDef;
  IAAFTypeDefIndirectSP pIndirectType;
  IAAFTypeDefSP pOversizeActualType;
  IAAFPropertyValueSP pIndirectValue;
  IAAFPropertyValueSP pActualValue;


  // Get indirect type definition
  checkResult (pDictionary->LookupTypeDef (kAAFTypeID_Indirect, &pTmpTypeDef));  
  checkResult (pTmpTypeDef->QueryInterface (IID_IAAFTypeDefIndirect, (void**)&pIndirectType));

  // Get the type definition of actual data
  checkResult (pDictionary->LookupTypeDef (kAAFTypeID_UInt8Array, &pOversizeActualType));

  // The maximum allowed property size is 64K
  const aafUInt32 maxSimplePropertySize = 64 * 1024;

  // Generate dummy annotation
  aafUInt32 oversizeActualDataSize = maxSimplePropertySize + 1024;
  aafUInt8* pOversizeActualData = new aafUInt8[ oversizeActualDataSize ];
  memset(pOversizeActualData, 'A', oversizeActualDataSize);

  // Try setting value whose size is larger than the supported
  // maximum simple property size.
  hr = pIndirectType->CreateValueFromActualData (
                                    pOversizeActualType,
                                    pOversizeActualData,
                                    oversizeActualDataSize,
                                    &pIndirectValue);
  checkExpression(hr == AAFRESULT_BAD_SIZE, AAFRESULT_TEST_FAILED);

  // Try setting value whose size is equal to the supported
  // maximum simple property size. Normally such size would
  // be valid but for indirect properties it is not because
  // a few bytes of an indirect property value are used to
  // maintain type-specific data slightly reducing the space
  // available for actual value data.
  hr = pIndirectType->CreateValueFromActualData (
                                    pOversizeActualType,
                                    pOversizeActualData,
                                    maxSimplePropertySize,
                                    &pIndirectValue);
  checkExpression(hr == AAFRESULT_BAD_SIZE, AAFRESULT_TEST_FAILED);

  // Try setting value whose size is equal to the supported
  // maximum simple property size. Normally such size would
  // be valid but for indirect properties it is not because
  // a few bytes of an indirect property value are used to
  // maintain type-specific data slightly reducing the space
  // available for actual value data.
  Test_CreateUInt8ArrayValue (pDictionary,
                              pOversizeActualData,
                              maxSimplePropertySize,
                              &pActualValue);
  hr = pIndirectType->CreateValueFromActualValue(
                                    pActualValue,
                                    &pIndirectValue);
  checkExpression(hr == AAFRESULT_BAD_SIZE, AAFRESULT_TEST_FAILED);

  delete [] pOversizeActualData;
  pOversizeActualData = NULL;

}

// This routine passes platform-specific type information
// to AAF enum and record type definitions. It should be
// called after the type definitions are created or restored and
// before thay are used to access proprty values.
static void DescribeInternalTypeLayout(IAAFDictionary* pDictionary)
{
  IAAFTypeDefSP pTypeDef;
  checkResult(pDictionary->LookupTypeDef(kAUID_CustomEnum, &pTypeDef));
  IAAFTypeDefEnumSP pTypeDefEnum;
  checkResult(pTypeDef->QueryInterface(IID_IAAFTypeDefEnum, (void**)&pTypeDefEnum));
  pTypeDefEnum->RegisterSize(sizeof(CustomEnum));

  checkResult(pDictionary->LookupTypeDef(kAUID_CustomRecord, &pTypeDef));
  IAAFTypeDefRecordSP pTypeDefRecord;
  checkResult(pTypeDef->QueryInterface(IID_IAAFTypeDefRecord, (void**)&pTypeDefRecord));
  aafUInt32 offsets[] = {offsetof(CustomRecord, a), offsetof(CustomRecord, b)};
  checkResult (pTypeDefRecord->RegisterMembers (offsets, 2, sizeof (CustomRecord)));
}


// Create the test file.
void CAAFTypeDefIndirect_create (
    aafCharacter_constptr pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_constref productID)
{
  IAAFFileSP pFile;
  IAAFHeaderSP pHeader;
  IAAFDictionarySP pDictionary;
  IAAFPropertyDefSP ppComponentAnnotationPropertyDefs[
	  NUM_COMPONENT_ANNOTATION_PROPERTIES];
  IAAFMobSP pMob;
  IAAFTimelineMobSlotSP pTimelineMobSlot;
  IAAFMobSlotSP pMobSlot;
  IAAFSequenceSP pSequence;
  IAAFSegmentSP pSequenceSegment;
  IAAFComponentSP pSequenceComponent;


  // Remove the previous test file is one exists
  RemoveTestFile (pFileName);

  // Create the file.
  checkResult (CreateTestFile( pFileName, fileKind, rawStorageType, productID, &pFile ));
  checkResult (pFile->GetHeader (&pHeader));
  checkResult (pHeader->GetDictionary (&pDictionary));
  
  Test_RegisterIndirectComponentAnnotations (pDictionary);

  Test_LookupIndirectComponentAnnotations (pDictionary,
	  ppComponentAnnotationPropertyDefs);

  // Create and composition mob and a sequence with several components.
  // each component will have a different indirect annotion type.
  CAAFBuiltinDefs defs (pDictionary);

  checkResult (defs.cdCompositionMob()->CreateInstance(IID_IAAFMob, (IUnknown **)&pMob));
  checkResult (pMob->SetName(L"AAFIndirectTypeTest-Mob"));
  // Save the new mob id so that we can just look it up...
  checkResult (pMob->SetMobID (sTestMob));
  

  checkResult (defs.cdTimelineMobSlot()->CreateInstance(IID_IAAFTimelineMobSlot, (IUnknown**)&pTimelineMobSlot));
  checkResult (pTimelineMobSlot->Initialize ());
  aafRational_t editRate = { 30000, 1001 };
  checkResult (pTimelineMobSlot->SetEditRate (editRate));
  checkResult (pTimelineMobSlot->SetOrigin (0));
  checkResult (pTimelineMobSlot->QueryInterface (IID_IAAFMobSlot, (void**)&pMobSlot));
  checkResult (pMobSlot->SetSlotID (0));
  checkResult (pMobSlot->SetName (L"AAFIndirectTypeTest-MobSlot"));

  checkResult (defs.cdSequence()->CreateInstance(IID_IAAFSequence, (IUnknown **)&pSequence));
  checkResult (pSequence->Initialize(defs.ddkAAFPicture()));


  // Test kAAFTypeID_String
  // 
  // Set a string value into the component annotation property of the new sequence.
  //
  aafUInt32 sequenceAnnotation1Size = sizeof(wchar_t) * (wcslen (kSequenceAnnotation1) + 1);
  Test_CreateValueFromActualData (
          pSequence,
          ppComponentAnnotationPropertyDefs[0],
          defs.tdString (),
          sequenceAnnotation1Size,
          (aafDataBuffer_t)kSequenceAnnotation1);
  
  // Test kAAFTypeID_UInt8Array
  // 
  // Set an ascii string as an array of unsigned bytes into the 2nd component annotation 
  // property of the new sequence.
  //
  IAAFTypeDefSP annotation2Type;
  checkResult (pDictionary->LookupTypeDef (kAAFTypeID_UInt8Array, &annotation2Type));
  aafUInt32 sequenceAnnotation2Size = strlen (kSequenceAnnotation2) + 1;
  Test_CreateValueFromActualData (
          pSequence,
          ppComponentAnnotationPropertyDefs[1],
          annotation2Type,
          sequenceAnnotation2Size,
          (aafDataBuffer_t)kSequenceAnnotation2);

  // Register a renamed type ("word") of UInt16.
  IAAFTypeDefRenameSP pTypeDefRenameWord;
  checkResult(pDictionary->CreateMetaInstance(AUID_AAFTypeDefRename,
    IID_IAAFTypeDefRename,(IUnknown **)&pTypeDefRenameWord));
  checkResult(pTypeDefRenameWord->Initialize(kAUID_Word,
											defs.tdUInt16(),
											L"Word"));
  IAAFTypeDefSP pTypeDef;
  checkResult(pTypeDefRenameWord->QueryInterface(IID_IAAFTypeDef,
    (void**)&pTypeDef));
  checkResult(pDictionary->RegisterTypeDef(pTypeDef));
  IAAFTypeDefSP pRegisteredTypeDefRename;
  checkResult(pDictionary->LookupTypeDef(kAUID_Word,&pRegisteredTypeDefRename));
  
  Test_CreateValueFromActualData(
	  pSequence,
	  ppComponentAnnotationPropertyDefs[2],
	  pRegisteredTypeDefRename,
	  sizeof(aafUInt16),
	  (aafDataBuffer_t)&kSequenceAnnotation3);

  // Now use CreateValueFromActualValue() to create indirect property values
  // of various types.

  // Create actual property value of string type
  IAAFPropertyValueSP pActualStringValue;
  IAAFTypeDefStringSP pTypeDefString;
  checkResult(defs.tdString()->QueryInterface(IID_IAAFTypeDefString,
	  (void**)&pTypeDefString));
  checkResult(pTypeDefString->CreateValueFromCString(
	  (aafMemPtr_t)kSequenceAnnotation1,sequenceAnnotation1Size,
	  &pActualStringValue));

  Test_CreateValueFromActualValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[3],pActualStringValue);

  // Create actual property value of UInt8 array type
  IAAFPropertyValueSP pActualUInt8ArrayValue;
  aafUInt32 dataSize=(strlen(kSequenceAnnotation2)+1)*sizeof(char);
  Test_CreateUInt8ArrayValue (
	  pDictionary,
	  (aafMemPtr_t)kSequenceAnnotation2,dataSize,
	  &pActualUInt8ArrayValue);

  Test_CreateValueFromActualValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[4],pActualUInt8ArrayValue);

  // Create actual property value of renamed type
  IAAFTypeDefRenameSP pTypeDefRename;
  checkResult(pRegisteredTypeDefRename->QueryInterface(IID_IAAFTypeDefRename,
	  (void**)&pTypeDefRename));
  IAAFTypeDefIntSP pTypeDefInt;
  checkResult(defs.tdUInt16()->QueryInterface(IID_IAAFTypeDefInt,
	  (void**)&pTypeDefInt));
  IAAFPropertyValueSP pBaseValue;
  checkResult(pTypeDefInt->CreateValue((aafMemPtr_t)&kSequenceAnnotation3,
	  sizeof(aafUInt16),&pBaseValue));
  IAAFPropertyValueSP pActualRenameValue;
  checkResult(pTypeDefRename->CreateValue(pBaseValue,&pActualRenameValue));

  Test_CreateValueFromActualValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[5],pActualRenameValue);


  // Test additional types

  // Register a enum type
  IAAFTypeDefEnumSP pTypeDefEnum;
  checkResult(pDictionary->CreateMetaInstance(AUID_AAFTypeDefEnum,
    IID_IAAFTypeDefEnum,(IUnknown **)&pTypeDefEnum));
  aafInt64 enumValues[] = {Hot, Cold};
  aafString_t enumNames[] = {L"Hot", L"Cold"};
  checkResult(pTypeDefEnum->Initialize(kAUID_CustomEnum,
										defs.tdUInt8(),
										enumValues,
										enumNames,
										2,
										L"CustomEnum"));
  checkResult(pTypeDefEnum->RegisterSize(sizeof(CustomEnum)));
  IAAFTypeDefSP pTypeDefEnum_TypeDef;
  checkResult(pTypeDefEnum->QueryInterface(IID_IAAFTypeDef,
    (void**)&pTypeDefEnum_TypeDef));
  checkResult(pDictionary->RegisterTypeDef(pTypeDefEnum_TypeDef));

  // Test creating a enum using CreateValueFromActualData()
  Test_CreateValueFromActualData(
	  pSequence,
	  ppComponentAnnotationPropertyDefs[6],
	  pTypeDefEnum_TypeDef,
	  sizeof(CustomEnum),
	  (aafDataBuffer_t)&kSequenceAnnotation6);

  // Test creating a enum using CreateValueFromActualValue()
  IAAFPropertyValueSP pCustomEnumValue;
  checkResult(pTypeDefEnum->CreateValueFromName(L"Hot", &pCustomEnumValue));
  Test_CreateValueFromActualValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[7],pCustomEnumValue);



  // Register a record type
  IAAFTypeDefRecordSP pTypeDefRecord;
  checkResult(pDictionary->CreateMetaInstance(AUID_AAFTypeDefRecord,
  IID_IAAFTypeDefRecord,(IUnknown **)&pTypeDefRecord));
  IAAFTypeDef* memberTypes[] = {defs.tdInt8(), defs.tdUInt8()};
  aafString_t memberNames[] = {L"Numerator", L"Denominator"};
  checkResult (pTypeDefRecord->Initialize (kAUID_CustomRecord,
											memberTypes,
											memberNames,
											2,
											L"CustomRecord"));
  aafUInt32 offsets[] = {offsetof(CustomRecord, a), offsetof(CustomRecord, b)};
  checkResult (pTypeDefRecord->RegisterMembers (offsets,
												2,
												sizeof (CustomRecord)));
  IAAFTypeDefSP pTypeDefRecord_TypeDef;
  checkResult(pTypeDefRecord->QueryInterface(IID_IAAFTypeDef,
    (void**)&pTypeDefRecord_TypeDef));
  checkResult(pDictionary->RegisterTypeDef(pTypeDefRecord_TypeDef));

  // Test creating a record using CreateValueFromActualData()
  Test_CreateValueFromActualData(
	  pSequence,
	  ppComponentAnnotationPropertyDefs[8],
	  pTypeDefRecord_TypeDef,
	  sizeof(kSequenceAnnotation8),
	  (aafDataBuffer_t)&kSequenceAnnotation8);

  // Test creating a record using CreateValueFromActualValue()
  IAAFPropertyValueSP pCustomRecordValue;
  checkResult(pTypeDefRecord->CreateValueFromStruct((aafMemPtr_t)&kSequenceAnnotation8,
	  sizeof(CustomRecord), &pCustomRecordValue));
  Test_CreateValueFromActualValue(pDictionary,pSequence,
	  ppComponentAnnotationPropertyDefs[9],pCustomRecordValue);


  TestInvalidInputs (pDictionary, pSequence);

  ValidateTestPropertyValues(pDictionary,pSequence);

  checkResult (pSequence->QueryInterface (IID_IAAFSegment,
	  (void**)&pSequenceSegment));
  checkResult (pMobSlot->SetSegment (pSequenceSegment));
  checkResult (pMob->AppendSlot (pMobSlot));
  checkResult (pHeader->AddMob (pMob));

  checkResult (pFile->Save ());
  checkResult (pFile->Close ());
}

// Open the test file read only and validate the data.
void CAAFTypeDefIndirect_read (aafCharacter_constptr pFileName)
{
  IAAFFileSP pFile;
  IAAFHeaderSP pHeader;
  IAAFDictionarySP pDictionary;
  IAAFMobSP pMob;
  IAAFMobSlotSP pMobSlot;
  IAAFSequenceSP pSequence;
  IAAFSegmentSP pSequenceSegment;

  checkResult (AAFFileOpenExistingRead (pFileName, 0, &pFile));
  checkResult (pFile->GetHeader (&pHeader));
  checkResult (pHeader->GetDictionary (&pDictionary));

  CAAFBuiltinDefs defs (pDictionary);

  // Find the mob that we added in the create.
  checkResult (pHeader->LookupMob (sTestMob, &pMob));
  checkResult (pMob->GetSlotAt (0, &pMobSlot));
  checkResult (pMobSlot->GetSegment (&pSequenceSegment));
  checkResult (pSequenceSegment->QueryInterface (IID_IAAFSegment, (void**)&pSequence));

  DescribeInternalTypeLayout(pDictionary);

  ValidateTestPropertyValues(pDictionary,pSequence);

  checkResult (pFile->Close ());
}

