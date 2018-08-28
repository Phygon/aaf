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
// Portions created by British Broadcasting Corporation are
// Copyright 2004, British Broadcasting Corporation.  All rights reserved.
//
//=---------------------------------------------------------------------=


#include "AAF.h"

#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include "AAFWideString.h"
#include <string.h>
#include <assert.h>

#include "AAFStoredObjectIDs.h"
#include "AAFResult.h"
#include "ModuleTest.h"
#include "AAFDefUIDs.h"
#include "AAFExtEnum.h"
#include "AAFOperationDefs.h"
#include "AAFFileKinds.h"

#include "CAAFBuiltinDefs.h"

typedef IAAFSmartPointer<IAAFComponent>			    IAAFComponentSP;
typedef IAAFSmartPointer<IAAFDictionary>			IAAFDictionarySP;
typedef IAAFSmartPointer<IAAFCompositionMob>		IAAFCompositionMobSP;
typedef IAAFSmartPointer<IAAFCommentMarker>			IAAFCommentMarkerSP;
typedef IAAFSmartPointer<IAAFEssenceData>			IAAFEssenceDataSP;
typedef IAAFSmartPointer<IAAFEssenceData2>			IAAFEssenceData2SP;
typedef IAAFSmartPointer<IAAFEssenceGroup>			IAAFEssenceGroupSP;
typedef IAAFSmartPointer<IAAFEssenceDescriptor>		IAAFEssenceDescriptorSP;
typedef IAAFSmartPointer<IAAFEventMobSlot>			IAAFEventMobSlotSP;
typedef IAAFSmartPointer<IAAFHeader>				IAAFHeaderSP;
typedef IAAFSmartPointer<IAAFMasterMob>				IAAFMasterMobSP;
typedef IAAFSmartPointer<IAAFMob>					IAAFMobSP;
typedef IAAFSmartPointer<IAAFMob2>					IAAFMob2SP;
typedef IAAFSmartPointer<IAAFMob3>					IAAFMob3SP;
typedef IAAFSmartPointer<IAAFMobSlot>				IAAFMobSlotSP;
typedef IAAFSmartPointer<IAAFFile>					IAAFFileSP;
typedef IAAFSmartPointer<IAAFOperationGroup>		IAAFOperationGroupSP;
typedef IAAFSmartPointer<IAAFOperationDef>		    IAAFOperationDefSP;
typedef IAAFSmartPointer<IAAFPlainEssenceData>		IAAFPlainEssenceDataSP;
typedef IAAFSmartPointer<IAAFSegment>		        IAAFSegmentSP;
typedef IAAFSmartPointer<IAAFSequence>		        IAAFSequenceSP;
typedef IAAFSmartPointer<IAAFSoundDescriptor>		IAAFSoundDescriptorSP;
typedef IAAFSmartPointer<IAAFSourceClip>			IAAFSourceClipSP;
typedef IAAFSmartPointer<IAAFSourceReference>		IAAFSourceReferenceSP;
typedef IAAFSmartPointer<IAAFSourceMob>				IAAFSourceMobSP;
typedef IAAFSmartPointer<IAAFTimelineMobSlot>		IAAFTimelineMobSlotSP;



// {E6AB4EE8-33F2-4bea-A5AC-A280B93146E9}
const aafUID_t kClassID_ConcreteEvent = 
{ 0xe6ab4ee8, 0x33f2, 0x4bea, { 0xa5, 0xac, 0xa2, 0x80, 0xb9, 0x31, 0x46, 0xe9 } };


static const aafWChar *slotNames[10] = { L"SLOT1", L"SLOT2", L"SLOT3", L"SLOT4",
                                         L"SLOT5", L"SLOT6", L"SLOT7",  L"SLOTSTATIC" , L"SLOTEVENT"  };

static const aafWChar *mobName = L"MOBTest";

static const aafWChar *pComment[5] = { L"TestComment1", L"TestComment2", 
                                       L"TestComment3", L"TestComment4", L"TestComment5"}; 

static const aafWChar *pCategory[5] = { L"TestCategory1", L"TestCategory2", 
                                        L"TestCategory3", L"TestCategory4", L"TestCategory5"}; 

static const aafTimeStamp_t creationTimeStamp = { {1941, 12, 7}, {5, 31, 12, 1} };
static const aafTimeStamp_t modificationTimeStamp = { {1941, 12, 7}, {5, 31, 12, 2} };

// {21F2083C-B260-11d3-BFFE-00104BC9156D}
static const aafMobID_t MOBTestID = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0x21f2083c, 0xb260, 0x11d3, { 0xbf, 0xfe, 0x0, 0x10, 0x4b, 0xc9, 0x15, 0x6d } } };
// {81831638-EDF4-11d3-A353-009027DFCA6A}
static const aafMobID_t MOBTestID2 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0x81831638, 0xedf4, 0x11d3, { 0xa3, 0x53, 0x0, 0x90, 0x27, 0xdf, 0xca, 0x6a } } };

// {2DFB8BB2-0972-11d4-A357-009027DFCA6A}
static const aafUID_t TEST_KLV = 
{ 0x2dfb8bb2, 0x972, 0x11d4, { 0xa3, 0x57, 0x0, 0x90, 0x27, 0xdf, 0xca, 0x6a } };

// {CC77FBF0-4DFA-11d4-870E-00105A234509}
static const aafMobID_t MOBTestID3 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0xcc77fbf0, 0x4dfa, 0x11d4, { 0x87, 0xe, 0x0, 0x10, 0x5a, 0x23, 0x45, 0x9 } } };

// {CC77FBF1-4DFA-11d4-870E-00105A234509}
static const aafMobID_t MOBTestID4 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0xcc77fbf1, 0x4dfa, 0x11d4, { 0x87, 0xe, 0x0, 0x10, 0x5a, 0x23, 0x45, 0x9 } } };

// {BB496538-B7D2-4560-9C7D-F577DF7D3748}
static const aafMobID_t MOBTestID5 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0xbb496538, 0xb7d2, 0x4560, { 0x9c, 0x7d, 0xf5, 0x77, 0xdf, 0x7d, 0x37, 0x48 } } };

// {E504F8D1-7579-47c7-A3DB-FBE073DE71C8}
static const aafMobID_t MOBTestID6 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
    { 0xe504f8d1, 0x7579, 0x47c7, { 0xa3, 0xdb, 0xfb, 0xe0, 0x73, 0xde, 0x71, 0xc8 } } };

// {5C4D8AD8-4E9D-47f9-9A69-6F7D39EF5EAC}
static const aafMobID_t MOBTestID7 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
    { 0x5c4d8ad8, 0x4e9d, 0x47f9, { 0x9a, 0x69, 0x6f, 0x7d, 0x39, 0xef, 0x5e, 0xac } } };

// {25A6EDFE-5312-48c1-8FF3-099504F4D9F2}
static const aafMobID_t MOBTestID8 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
    { 0x25a6edfe, 0x5312, 0x48c1, { 0x8f, 0xf3, 0x09, 0x95, 0x04, 0xf4, 0xd9, 0xf2 } } };

// {31DFEF88-2E40-4090-A383-338D40FA8F3E}
static const aafMobID_t MOBTestID9 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0x31dfef88, 0x2e40, 0x4090, { 0xa3, 0x83, 0x33, 0x8d, 0x40, 0xfa, 0x8f, 0x3e } } };

// {0CE66544-B034-425A-9156-7089CB29D230}
static const aafMobID_t MOBTestID10 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0x0ce66544, 0xb034, 0x425a, { 0x91, 0x56, 0x70, 0x89, 0xcb, 0x29, 0xd2, 0x30 } } };

// {6C0F6BDE-A5CA-4164-AD98-F6CC4DD50F75}
static const aafMobID_t MOBTestID11 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0x6c0f6bde, 0xa5ca, 0x4164, { 0xad, 0x98, 0xf6, 0xcc, 0x4d, 0xd5, 0x0f, 0x75 } } };

// {8C280D76-BF13-49df-88DA-B6B88AF7ADF7}
static const aafMobID_t MOBTestID12 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0x8c280d76, 0xbf13, 0x49df, { 0x88, 0xda, 0xb6, 0xb8, 0x8a, 0xf7, 0xad, 0xf7 } } };

// {A6ABBC5C-6AAE-4667-8B4D-2EC8B3DE72A9}
static const aafMobID_t MOBTestID13 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0xa6abbc5c, 0x6aae, 0x4667, { 0x8b, 0x4d, 0x2e, 0xc8, 0xb3, 0xde, 0x72, 0xa9 } } };

// {FA121DEF-16F2-4117-8D06-D9B35630D8F1}
static const aafMobID_t MOBTestID14 = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0xfa121def, 0x16f2, 0x4117, { 0x8d, 0x06, 0xd9, 0xb3, 0x56, 0x30, 0xd8, 0xf1 } } };

// {C92063EB-FEA6-4fb3-8EB5-A120CB21E3C4}
static const aafMobID_t MOBTestID_Static = 
{ { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01,
	 0x01, 0x01, 0x04, 0x02 }, 0x13, 0x00, 0x00, 0x00,
	{ 0xcc77fbf1, 0x4dfa, 0x11d4,  { 0x8e, 0xb5, 0xa1, 0x20, 0xcb, 0x21, 0xe3, 0xc4 } } };

static const char KLVsmiley[] =        /* 16x16 smiley face */
  "      ****      "
  "    ********    "
  "   **********   "
  "  ************  "
  " ***  ****  *** "
  " ***  ****  *** "
  "****************"
  "****************"
  "****************"
  "****************"
  " ** ******** ** "
  " *** ****** *** "
  "  ***  **  ***  "
  "   ****  ****   "
  "    ********    "
  "      ****     ";

static const char KLVfrowney[] =        /* 16x16 frowney face */
  "      ****      "
  "    ********    "
  "   **********   "
  "  ************  "
  " ***  ****  *** "
  " ***  ****  *** "
  "****************"
  "****************"
  "*******  *******"
  "*****  **  *****"
  " *** ****** *** "
  " ** ******** ** "
  "  ************  "
  "   **********   "
  "    ********    "
  "      ****     ";



namespace {
const aafCharacter* AttributeNames[]  = { L"Attribute A Name", L"Attribute B Name" };
const aafCharacter* AttributeValues[] = { L"Attribute A Value", L"Attribute B Value" };
}


static aafFrameOffset_t 	TCstartFrame = 108000;	// One hour
static aafDropType_t 		TCdrop = kAAFTcNonDrop;
static aafUInt16		 	TCfps = 30;


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

static HRESULT CreateEssenceData(
	IAAFHeader* pHeader,
	const aafMobID_t sourceMobID,
	aafDataBuffer_t data,
	aafUInt32 dataSize)
{
	HRESULT hr = S_OK;

	try
	{
		IAAFDictionarySP pDictionary;
		checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs(pDictionary);

		// Create SoundDescriptor
		IAAFSoundDescriptorSP pSoundDesc;
		checkResult(defs.cdSoundDescriptor()->CreateInstance(IID_IAAFSoundDescriptor, (IUnknown **)&pSoundDesc));
		const aafRational_t audioSamplingRate = {48000, 1};
		checkResult(pSoundDesc->SetAudioSamplingRate(audioSamplingRate));
		checkResult(pSoundDesc->SetChannelCount(1));
		checkResult(pSoundDesc->SetQuantizationBits(16));

		// Create SourceMob and set its descriptor
		IAAFSourceMobSP pSourceMob;
		checkResult(defs.cdSourceMob()->CreateInstance(IID_IAAFSourceMob, (IUnknown **)&pSourceMob));
		IAAFEssenceDescriptorSP pEssenceDesc;
		checkResult(pSoundDesc->QueryInterface(IID_IAAFEssenceDescriptor, (void**)&pEssenceDesc));
		checkResult(pSourceMob->SetEssenceDescriptor(pEssenceDesc));

		// Add the SourceMob to the Header
		IAAFMobSP pMob;
		checkResult(pSourceMob->QueryInterface(IID_IAAFMob, (void**)&pMob));
		checkResult(pMob->SetMobID(sourceMobID));
		checkResult(pHeader->AddMob(pMob));

		// Create EssenceData
		IAAFEssenceDataSP pEssenceData;
		checkResult(defs.cdEssenceData()->CreateInstance(IID_IAAFEssenceData, (IUnknown **)&pEssenceData));
		checkResult(pEssenceData->Initialize(pSourceMob));
		checkResult(pHeader->AddEssenceData(pEssenceData));
		IAAFEssenceData2SP pEssenceData2;
		checkResult(pEssenceData->QueryInterface(IID_IAAFEssenceData2, (void**)&pEssenceData2));
		IAAFPlainEssenceDataSP pPlainEssenceData;
		checkResult(pEssenceData2->GetPlainEssenceData(0, &pPlainEssenceData));
		aafUInt32 bytesWritten = 0;
		checkResult(pPlainEssenceData->Write(dataSize, data, &bytesWritten));
		checkExpression(bytesWritten == dataSize, AAFRESULT_TEST_FAILED);
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	return hr;
}

// Get object's Data Definition property
static HRESULT GetDataDef(
	IUnknown* pUnknownWithDataDef,
	IAAFDataDef** pDataDef)
{
	HRESULT hr = S_OK;

	IAAFComponentSP pComponent;
	IAAFMobSlotSP pMobSlot;
	if (pUnknownWithDataDef->QueryInterface(IID_IAAFComponent, (void**)&pComponent) == S_OK)
	{
		hr = pComponent->GetDataDef(pDataDef);
	}
	else if (pUnknownWithDataDef->QueryInterface(IID_IAAFMobSlot, (void**)&pMobSlot) == S_OK)
	{
		IAAFSegmentSP pSegment;
		checkResult(pMobSlot->GetSegment(&pSegment));
		hr = GetDataDef(pSegment, pDataDef);
	}
	else
	{
		hr = AAFRESULT_TEST_FAILED;
	}

	return hr;
}

// Get object's Length property
static HRESULT GetLength(
	IUnknown* pUnknownWithDataDef,
	aafLength_t* pLength)
{
	HRESULT hr = S_OK;

	IAAFComponentSP pComponent;
	IAAFMobSlotSP pMobSlot;
	if (pUnknownWithDataDef->QueryInterface(IID_IAAFComponent, (void**)&pComponent) == S_OK)
	{
		hr = pComponent->GetLength(pLength);
	}
	else if (pUnknownWithDataDef->QueryInterface(IID_IAAFMobSlot, (void**)&pMobSlot) == S_OK)
	{
		IAAFSegmentSP pSegment;
		checkResult(pMobSlot->GetSegment(&pSegment));
		hr = GetLength(pSegment, pLength);
	}
	else
	{
		hr = AAFRESULT_TEST_FAILED;
	}

	return hr;
}

// Create a Source Clip object referencing full length of a 1st Slot of the specified mob
static HRESULT CreateSourceClip(
	IAAFHeader* pHeader,
	const aafMobID_t& referencedMobID,
	IAAFSourceClip** pSourceClip)
{
	HRESULT hr = S_OK;

	try
	{
		IAAFDictionarySP pDictionary;
		checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs(pDictionary);

		// Obtain information needed to buld a referecen to a specified Mob
		aafSourceRef_t reference = {referencedMobID, 1, 0};
		aafLength_t referenceLength = 0;
		IAAFDataDefSP pReferenceDataDef(defs.ddkAAFPicture());

		IAAFMobSP pReferencedMob;
		if AAFRESULT_SUCCEEDED(pHeader->LookupMob(referencedMobID, &pReferencedMob))
		{
			IAAFMobSlotSP pReferencedSlot;
			if (AAFRESULT_SUCCEEDED(pReferencedMob->GetSlotAt(0, &pReferencedSlot)))
			{
				checkResult(pReferencedSlot->GetSlotID(&(reference.sourceSlotID)));
				checkResult(GetDataDef(pReferencedSlot, &pReferenceDataDef));
				checkResult(GetLength(pReferencedSlot, &referenceLength));
			}
		}

		// Create a Source Clip with a reference to a specified Mob
		IAAFSourceClipSP pResult;
		checkResult(defs.cdSourceClip()->CreateInstance(IID_IAAFSourceClip, (IUnknown **)&pResult));
		checkResult(pResult->Initialize(pReferenceDataDef, referenceLength, reference));

		*pSourceClip = pResult;
		(*pSourceClip)->AddRef();
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	return hr;
}

static HRESULT CreateSequence(
	IAAFHeader* pHeader,
	IUnknown* pUnknownComponent,
	IAAFSequence** pSequence)
{
	HRESULT hr = S_OK;

	try
	{
		IAAFDictionarySP pDictionary;
		checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs(pDictionary);

		IAAFDataDefSP pDataDef;
		checkResult(GetDataDef(pUnknownComponent, &pDataDef));

		IAAFSequenceSP pResult;
		checkResult(defs.cdSequence()->CreateInstance(IID_IAAFSequence, (IUnknown **)&pResult));
		checkResult(pResult->Initialize(pDataDef));

		IAAFComponentSP pComponent;
		checkResult(pUnknownComponent->QueryInterface(IID_IAAFComponent, (void**)&pComponent));
		checkResult(pResult->AppendComponent(pComponent));

		*pSequence = pResult;
		(*pSequence)->AddRef();
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	return hr;
}

static HRESULT RegisterOperationDef(
	IAAFHeader* pHeader,
	const aafUID_t& operationDefID)
{
	HRESULT hr = S_OK;

	try
	{
		IAAFDictionarySP pDictionary;
		checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs(pDictionary);

		IAAFOperationDefSP pOperationDef;
		checkResult(defs.cdOperationDef()->CreateInstance(IID_IAAFOperationDef, (IUnknown **)&pOperationDef));
		if (operationDefID == kAAFEffectSMPTEVideoWipe)
		{
			checkResult(pOperationDef->Initialize(kAAFEffectSMPTEVideoWipe, L"SmpteWipeDummy", L"SmpteWipeDummy"));
			checkResult(pDictionary->RegisterOperationDef(pOperationDef));
			checkResult(pOperationDef->SetDataDef (defs.ddkAAFPicture()));
			checkResult(pOperationDef->SetNumberInputs(1));
			checkResult(pOperationDef->SetBypass(1));
		}
		else
		{
			hr = AAFRESULT_TEST_FAILED;
		}
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	return hr;
}

static HRESULT CreateOperationGroup(
	IAAFHeader* pHeader,
	const aafUID_t& operationDefID,
	const aafMobID_t& inputMobID,
	const aafMobID_t& renderMobID,
	IAAFOperationGroup** pOperationGroup)
{
	HRESULT hr = S_OK;

	try
	{
		IAAFDictionarySP pDictionary;
		checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs(pDictionary);

		checkResult(RegisterOperationDef(pHeader,operationDefID));

		// Create an Input Segment for the Operation Group first -
		// it is convinient for determining the length of the Opearion Group.
		IAAFSourceClipSP pSourceClip;
		checkResult(CreateSourceClip(pHeader, inputMobID, &pSourceClip));
		IAAFSequenceSP pSequence;
		checkResult(CreateSequence(pHeader, pSourceClip, &pSequence));
		IAAFSegmentSP pInputSegment;
		checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void **)&pInputSegment));

		// Create an Operation Group
		IAAFOperationDefSP pOperationDef;
		checkResult(pDictionary->LookupOperationDef(operationDefID, &pOperationDef));
		IAAFDataDefSP pDataDef;
		checkResult(pOperationDef->GetDataDef(&pDataDef));
		aafLength_t length = 0;
		checkResult(GetLength(pInputSegment, &length));

		IAAFOperationGroupSP pResult;
		checkResult(defs.cdOperationGroup()->CreateInstance(IID_IAAFOperationGroup, (IUnknown **)&pResult));
		checkResult(pResult->Initialize(pDataDef, length, pOperationDef));

		// Add an Input Segment to the  Operation Group
		checkResult(pResult->AppendInputSegment(pInputSegment));

		// Create Operation Group's Render
		checkResult(CreateEssenceData(pHeader, renderMobID, (aafDataBuffer_t)KLVfrowney, sizeof(KLVfrowney)));
		IAAFSourceClipSP pRenderSourceClip;
		checkResult(CreateSourceClip(pHeader, renderMobID, &pRenderSourceClip));
		IAAFSourceReferenceSP pRenderSourceReference;
		checkResult(pRenderSourceClip->QueryInterface(IID_IAAFSourceReference, (void **)&pRenderSourceReference));
		checkResult(pResult->SetRender(pRenderSourceReference));

		*pOperationGroup = pResult;
		(*pOperationGroup)->AddRef();

	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	return hr;
}

static HRESULT CreateCommentMarker(
	IAAFHeader* pHeader,
	const aafMobID_t& annotationMobID,
	IAAFCommentMarker** pCommentMarker)
{
	HRESULT hr = S_OK;

	try
	{
		IAAFDictionarySP pDictionary;
		checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs(pDictionary);

		// Create CommentMarker
		IAAFCommentMarkerSP pResult;
		checkResult(defs.cdCommentMarker()->CreateInstance(IID_IAAFCommentMarker, (IUnknown **)&pResult));

		IAAFComponentSP pComponent;
		checkResult(pResult->QueryInterface(IID_IAAFComponent, (void**)&pComponent));
		checkResult(pComponent->SetDataDef(defs.ddkAAFDescriptiveMetadata()));

		IAAFSourceClipSP pAnnotation;
		checkResult(CreateSourceClip(pHeader, annotationMobID, &pAnnotation));
		IAAFSourceReferenceSP pAnnotationSourceReference;
		checkResult(pAnnotation->QueryInterface(IID_IAAFSourceReference, (void**)&pAnnotationSourceReference));
		checkResult(pResult->SetAnnotation(pAnnotationSourceReference));

		*pCommentMarker = pResult;
		(*pCommentMarker)->AddRef();
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	return hr;
}

// Create a Composition Mob
static HRESULT CreateComposition(
	IAAFHeader* pHeader,
	const aafMobID_t& compositionMobID,
	const aafMobID_t& masterMobID,
	const aafMobID_t& compositionEffectRenderMobID,
	const aafMobID_t& commentMarkerAnnotationMobID)
{
	HRESULT hr = S_OK;

	try
	{
		IAAFDictionarySP pDictionary;
		checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs(pDictionary);

		// Create CompositionMob
		IAAFCompositionMobSP pCompositionMob;
		checkResult(defs.cdCompositionMob()->CreateInstance(IID_IAAFCompositionMob, (IUnknown **)&pCompositionMob));

		// Add the CompositionMob to the Header
		IAAFMobSP pMob;
		checkResult(pCompositionMob->QueryInterface(IID_IAAFMob, (void**)&pMob));
		checkResult(pMob->SetMobID(compositionMobID));

		// Create Operation Group
		IAAFOperationGroupSP pOperationGroup;
		checkResult(CreateOperationGroup(pHeader, kAAFEffectSMPTEVideoWipe, masterMobID, compositionEffectRenderMobID, &pOperationGroup));

		// A Sequence with the Operation Group
		IAAFSequenceSP pSequence;
		checkResult(CreateSequence(pHeader, pOperationGroup, &pSequence));
		IAAFSegmentSP pSegment;
		checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void **)&pSegment));

		const aafRational_t editRate = {25, 1};
		IAAFTimelineMobSlotSP pTimelineMobSlot;
		checkResult(pMob->AppendNewTimelineSlot(editRate, pSegment, 1, L"Planetary", 0, &pTimelineMobSlot));

		// Create Comment Marker
		IAAFCommentMarkerSP pCommentMarker;
		checkResult(CreateCommentMarker(pHeader, commentMarkerAnnotationMobID, &pCommentMarker));
		checkResult(pCommentMarker->QueryInterface(IID_IAAFSegment, (void **)&pSegment));

		// Add Comment Marker to the Composition Mob (just for variaty don't wrap it in a Sequence).
		IAAFMob2SP pMob2;
		checkResult(pCompositionMob->QueryInterface(IID_IAAFMob2, (void**)&pMob2));
		IAAFEventMobSlotSP pEventMobSlot;
		checkResult(pMob2->AppendNewEventSlot(editRate, pSegment, 2, L"Plot", 0, &pEventMobSlot));

		checkResult(pHeader->AddMob(pMob));
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	return hr;
}

// Create a Master Mob with an Essence Group
static HRESULT CreateEssenceGroup(
	IAAFHeader* pHeader,
	const aafMobID_t& masterMobID,
	const aafMobID_t& choiceMobID,
	const aafMobID_t& stillMobID)
{
	HRESULT hr = S_OK;

	try
	{
		IAAFDictionarySP pDictionary;
		checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs(pDictionary);

		// Create file mobs to serve as the 'choice' and 'still frame' for Essence Group
		checkResult(CreateEssenceData(pHeader, choiceMobID, (aafDataBuffer_t)KLVfrowney, sizeof(KLVfrowney)));
		checkResult(CreateEssenceData(pHeader, stillMobID, (aafDataBuffer_t)KLVsmiley, sizeof(KLVsmiley)));

		// Create Source Clip referencing the file mob that will serve as
		// the 'choice' for Essence Group
		IAAFSourceClipSP pChoiceSourceClip;
		checkResult(CreateSourceClip(pHeader, choiceMobID, &pChoiceSourceClip));

		IAAFDataDefSP pDataDef;
		checkResult(GetDataDef(pChoiceSourceClip, &pDataDef));
		aafLength_t length = 0;
		checkResult(GetLength(pChoiceSourceClip, &length));

		// Create Essence Group
		IAAFEssenceGroupSP pEssenceGroup;
		checkResult(defs.cdEssenceGroup()->CreateInstance(IID_IAAFEssenceGroup, (IUnknown **)&pEssenceGroup));
		IAAFComponentSP pComponent;
		checkResult(pEssenceGroup->QueryInterface(IID_IAAFComponent, (void**)&pComponent));
		checkResult(pComponent->SetDataDef(pDataDef));
		checkResult(pComponent->SetLength(length));

		// Add the 'choice' and the 'still frame' to the Essence Group
		IAAFSegmentSP pChoiceSegment;
		checkResult(pChoiceSourceClip->QueryInterface(IID_IAAFSegment, (void**)&pChoiceSegment));
		checkResult(pEssenceGroup->AppendChoice(pChoiceSegment));

		// Set a 'still frame' on the Essence Group
		IAAFSourceClipSP pStillSourceClip;
		checkResult(CreateSourceClip(pHeader, stillMobID, &pStillSourceClip));
		// Still has to have length of 1
		IAAFComponentSP pStillComponent;
		checkResult(pStillSourceClip->QueryInterface(IID_IAAFComponent, (void**)&pStillComponent));
		checkResult(pStillComponent->SetLength(1));
		checkResult(pEssenceGroup->SetStillFrame(pStillSourceClip));

		// Create MasterMob to hold the Essence Group
		IAAFMasterMobSP pMasterMob;
		checkResult(defs.cdMasterMob()->CreateInstance(IID_IAAFMasterMob, (IUnknown **)&pMasterMob));

		IAAFMobSP pMob;
		checkResult(pMasterMob->QueryInterface(IID_IAAFMob, (void**)&pMob));
		checkResult(pMob->SetMobID(masterMobID));

		IAAFSegmentSP pEssenceGroupSegment;
		checkResult(pEssenceGroup->QueryInterface(IID_IAAFSegment, (void**)&pEssenceGroupSegment));
		const aafRational_t editRate = {25, 1};
		IAAFTimelineMobSlotSP pTimelineMobSlot;
		checkResult(pMob->AppendNewTimelineSlot(editRate, pEssenceGroupSegment, 1, L"Neptune Seven", 0, &pTimelineMobSlot));

		checkResult(pHeader->AddMob(pMob));

	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	return hr;
}

// Create Master Mob without Mob Slots
static HRESULT CreateEmptyClip(
	IAAFHeader* pHeader,
	const aafMobID_t& masterMobID)
{
	HRESULT hr = S_OK;

	try
	{
		IAAFDictionarySP pDictionary;
		checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs(pDictionary);

		// Create MasterMob to hold the Essence Group
		IAAFMasterMobSP pMasterMob;
		checkResult(defs.cdMasterMob()->CreateInstance(IID_IAAFMasterMob, (IUnknown **)&pMasterMob));

		IAAFMobSP pMob;
		checkResult(pMasterMob->QueryInterface(IID_IAAFMob, (void**)&pMob));
		checkResult(pMob->SetMobID(masterMobID));

		checkResult(pHeader->AddMob(pMob));

	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	return hr;
}

static HRESULT CreateClonedAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_constref productID)
{
	HRESULT hr = S_OK;
	IAAFFileSP pDestFile;

	try
	{
		// Create the desctination file that will receive "cloned" metadata
		RemoveTestFile(pFileName);
		checkResult(CreateTestFile( pFileName, fileKind, rawStorageType, productID, &pDestFile));

		// TODO: kAAFFileKind_AafKlvBinary MXF writer implementation
		// fails to write KLV key and length for essence streams created
		// by CloneExternal(). Remove this once fixed.
		const bool encodingSupportsEssenceCloning = (fileKind != kAAFFileKind_AafKlvBinary);

		//
		// Clone from a file with potentially different encoding.
		//
		if (AAFRESULT_SUCCEEDED(hr) && encodingSupportsEssenceCloning)
		{
			IAAFFileSP pSrcFile;
			try
			{
				// Create the source file to clone metadata from
				checkResult(AAFFileOpenTransient(const_cast<aafProductIdentification_t*>(&productID), &pSrcFile));
				IAAFHeaderSP pHeader;
				checkResult(pSrcFile->GetHeader(&pHeader));
				checkResult(CreateEssenceData(pHeader, MOBTestID5, (aafDataBuffer_t)KLVfrowney, sizeof(KLVfrowney)));
				IAAFMobSP pMob;
				checkResult(pHeader->LookupMob(MOBTestID5, &pMob));

				IAAFMobSP pClonedMob;
				checkResult(pMob->CloneExternal(kAAFNoFollowDepend, kAAFIncludeMedia, pDestFile, &pClonedMob));
				checkResult(pDestFile->Save());

				checkResult(pSrcFile->Close());
			}
			catch (HRESULT& rResult)
			{
				pSrcFile->Close();
				hr = rResult;
			}
		}

		//
		// Clone from a file with the same encoding.
		//
		if (AAFRESULT_SUCCEEDED(hr))
		{
			IAAFFileSP pSrcFile;
			try
			{
				// Create the source file to clone metadata from
				aafCharacter src_filename[128];
				wcscpy(src_filename, pFileName);
				wcscat(src_filename, L"_source");
				RemoveTestFile(src_filename);
				checkResult(CreateTestFile( src_filename, fileKind, rawStorageType, productID, &pSrcFile));
				IAAFHeaderSP pHeader;
				checkResult(pSrcFile->GetHeader(&pHeader));

				//
				// Clone from saved but not closed file.
				//
				checkResult(CreateEssenceData(pHeader, MOBTestID6, (aafDataBuffer_t)KLVfrowney, sizeof(KLVfrowney)));
				checkResult(pSrcFile->Save());
				{
					IAAFMobSP pMob;
					checkResult(pHeader->LookupMob(MOBTestID6, &pMob));
					IAAFMobSP pClonedMob;
					checkResult(pMob->CloneExternal(kAAFNoFollowDepend, kAAFIncludeMedia, pDestFile, &pClonedMob));
					checkResult(pDestFile->Save());
				}

				//
				// Clone from saved and closed file.
				//
				checkResult(CreateEssenceData(pHeader, MOBTestID7, (aafDataBuffer_t)KLVsmiley, sizeof(KLVsmiley)));
				checkResult(CreateEssenceData(pHeader, MOBTestID8, (aafDataBuffer_t)KLVfrowney, sizeof(KLVfrowney)));
				checkResult(CreateEssenceGroup(pHeader, MOBTestID10, MOBTestID9, MOBTestID11));
				checkResult(CreateEmptyClip(pHeader, MOBTestID14));
				checkResult(CreateComposition(pHeader, MOBTestID12, MOBTestID10, MOBTestID13, MOBTestID14));
				checkResult(pSrcFile->Save());
				checkResult(pSrcFile->Close());
				// Reopen the closed source file
				checkResult(AAFFileOpenExistingRead(src_filename, 0, &pSrcFile));

				// Clone from saved and closed file.
				checkResult(pSrcFile->GetHeader(&pHeader));
				{
					IAAFMobSP pMob;
					checkResult(pHeader->LookupMob(MOBTestID7, &pMob));
					IAAFMobSP pClonedMob;
					checkResult(pMob->CloneExternal(kAAFNoFollowDepend, kAAFIncludeMedia, pDestFile, &pClonedMob));
					checkResult(pDestFile->Save());
				}
				{
					// Clone comples Composition Mob and its dependencies
					IAAFMobSP pMob;
					checkResult(pHeader->LookupMob(MOBTestID12, &pMob));
					IAAFMobSP pClonedMob;
					checkResult(pMob->CloneExternal(kAAFFollowDepend, kAAFNoIncludeMedia, pDestFile, &pClonedMob));
					checkResult(pDestFile->Save());
				}

				// Clone from saved and closed file while deferring copying of stream contents.
				{
					IAAFMobSP pMob;
					checkResult(pHeader->LookupMob(MOBTestID8, &pMob));
					// TODO: Fix CloneExternalAdvanced() to support deferred
					// copying of the media.
					//
					// TODO: Add a test case for CloneExternalAdvanced() to
					// test deferred copying of stream properties other than
					// essence and index stream properties.
					//
					// This call is disabled because it currently doesn't
					// support cloning with media when deferred stream copying
					// is enabled.
#if 0				
					IAAFMob3SP pMob3;
					if (AAFRESULT_SUCCEEDED(pMob->QueryInterface(IID_IAAFMob3, (void**)&pMob3)))
					{
						IAAFMobSP pClonedMob;
						checkResult(pMob3->CloneExternalAdvanced(kAAFNoFollowDepend, kAAFIncludeMedia, kAAFTrue, pDestFile, &pClonedMob));
					}
					else
#endif
					{
						// Fall back to the original method if the toolkit version doesn't implement IAAFMob3
						IAAFMobSP pClonedMob;
						checkResult(pMob->CloneExternal(kAAFNoFollowDepend, kAAFIncludeMedia, pDestFile, &pClonedMob));
					}
					checkResult(pDestFile->Save());
				}

				checkResult(pSrcFile->Close());
			}
			catch (HRESULT& rResult)
			{
				pSrcFile->Close();
				hr = rResult;
			}
		}

		checkResult(pDestFile->Close());
	}
	catch (HRESULT& rResult)
	{
		pDestFile->Close();
		hr = rResult;
	}

	return hr;
}

static HRESULT ReadEssenceData(IAAFHeader* pHeader, const aafMobID_t sourceMobID, aafDataBuffer_t buffer, aafUInt32 bufferSize, aafUInt32* pBytesRead)
{
	HRESULT hr = S_OK;

	try
	{
		IAAFEssenceDataSP pEssenceData;
		checkResult(pHeader->LookupEssenceData(sourceMobID, &pEssenceData));
		IAAFEssenceData2SP pEssenceData2;
		checkResult(pEssenceData->QueryInterface(IID_IAAFEssenceData2, (void**)&pEssenceData2));
		IAAFPlainEssenceDataSP pPlainEssenceData;
		checkResult(pEssenceData2->GetPlainEssenceData(0, &pPlainEssenceData));
		checkResult(pPlainEssenceData->Read(bufferSize, buffer, pBytesRead));
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	return hr;
}

static bool MobExists(IAAFHeader* pHeader, const aafMobID_t& mobID)
{
	IAAFMobSP pMob;
	return  (pHeader->LookupMob(mobID, &pMob) == S_OK);
}

static HRESULT ReadClonedAAFFile(aafWChar * pFileName)
{
	HRESULT hr = S_OK;

	IAAFFileSP pFile;

	try
	{
		// Open the file
		checkResult(AAFFileOpenExistingRead(pFileName, 0, &pFile));
		IAAFHeaderSP pHeader;
		checkResult(pFile->GetHeader(&pHeader));

		aafUInt8 buffer[500];
		aafUInt32 bytesRead = 0;

		memset(buffer, 0, sizeof(buffer));
		bytesRead = 0;
		checkResult(ReadEssenceData(pHeader, MOBTestID7, buffer, sizeof(buffer), &bytesRead));
		checkExpression(bytesRead == sizeof(KLVsmiley), AAFRESULT_TEST_FAILED);
		checkExpression(memcmp(buffer, KLVsmiley, bytesRead) == 0, AAFRESULT_TEST_FAILED);

		memset(buffer, 0, sizeof(buffer));
		bytesRead = 0;
		checkResult(ReadEssenceData(pHeader, MOBTestID8, buffer, sizeof(buffer), &bytesRead));
		checkExpression(bytesRead == sizeof(KLVfrowney), AAFRESULT_TEST_FAILED);
		checkExpression(memcmp(buffer, KLVfrowney, bytesRead) == 0, AAFRESULT_TEST_FAILED);

		checkExpression(MobExists(pHeader, MOBTestID9), AAFRESULT_TEST_FAILED);
		checkExpression(MobExists(pHeader, MOBTestID10), AAFRESULT_TEST_FAILED);
		checkExpression(MobExists(pHeader, MOBTestID11), AAFRESULT_TEST_FAILED);
		checkExpression(MobExists(pHeader, MOBTestID12), AAFRESULT_TEST_FAILED);
		checkExpression(MobExists(pHeader, MOBTestID13), AAFRESULT_TEST_FAILED);
		checkExpression(MobExists(pHeader, MOBTestID14), AAFRESULT_TEST_FAILED);

		// The following 2 tests currently fail due to known bugs.
		// For test cases see CreateClonedAAFFile() and how streams
		// associated with these mobs were created

		memset(buffer, 0, sizeof(buffer));
		bytesRead = 0;
		checkExpression(ReadEssenceData(pHeader, MOBTestID5, buffer, sizeof(buffer), &bytesRead) == S_OK, AAFRESULT_TEST_PARTIAL_SUCCESS);
		checkExpression(bytesRead == sizeof(KLVfrowney), AAFRESULT_TEST_PARTIAL_SUCCESS);
		checkExpression(memcmp(buffer, KLVfrowney, bytesRead) == 0, AAFRESULT_TEST_PARTIAL_SUCCESS);

		memset(buffer, 0, sizeof(buffer));
		bytesRead = 0;
		checkResult(ReadEssenceData(pHeader, MOBTestID6, buffer, sizeof(buffer), &bytesRead));
		checkExpression(bytesRead == sizeof(KLVfrowney), AAFRESULT_TEST_PARTIAL_SUCCESS);
		checkExpression(memcmp(buffer, KLVfrowney, bytesRead) == 0, AAFRESULT_TEST_PARTIAL_SUCCESS);
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}

	if (pFile)
	{
		pFile->Close();
	}

	return hr;
}

static HRESULT CreateAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_constref productID)
{
  IAAFFile *					pFile = NULL;
  bool 							bFileOpen = false;
  IAAFHeader *        			pHeader = NULL;
  IAAFDictionary*  				pDictionary = NULL;
  IAAFMob						*pMob = NULL;
  IAAFMob						*pMob2 = NULL;
  IAAFMob2                      *pMobInterface2 = NULL;
  IAAFTimelineMobSlot 			*newSlot = NULL;
  IAAFStaticMobSlot 			*newStaticSlot=NULL;
  IAAFEventMobSlot 				*newEventSlot=NULL;
  IAAFSegment					*seg = NULL;
  IAAFSourceClip				*sclp = NULL;
  IAAFEvent						*event=NULL;
  IAAFComponent*				pComponent = NULL;
  IAAFClassDef					*pcdEventMeta=NULL;
  IAAFClassDef					*pcdEvent=NULL;
  IAAFClassDef					*pcdEventConcrete=NULL;
  HRESULT						hr = S_OK;
  aafNumSlots_t					numMobs;
  aafUInt32 					bufLen = 0;
  aafUInt32 					bytesRead = 0;
  aafUInt32 					numComments = 0;
  aafUInt32						numFound = 0;
  aafWChar						name[500];
  aafWChar						value[500];
  IEnumAAFTaggedValues 			*enumTaggedVal = NULL;
  IAAFTaggedValue				*taggedVal = NULL;
  IAAFMobSlot 					*mSlot = NULL;
  IAAFFiller 					*filler = NULL;
  IAAFKLVData					*pKLVData = NULL;
  IAAFTypeDef*					pBaseType = NULL;
  IAAFSourceReference 			*pSourceRef = NULL;
  IAAFTimecode					*pTimecode = NULL;
  aafTimecode_t					timecode;
  int 							i;


  try
	{
	  // Remove the previous test file if any.
	  RemoveTestFile(pFileName);

	  // Create the file.
	  checkResult(CreateTestFile( pFileName, fileKind, rawStorageType, productID, &pFile ));
	  bFileOpen = true;
 
	  // We can't really do anthing in AAF without the header.
	  checkResult(pFile->GetHeader(&pHeader));

	  // Get the AAF Dictionary so that we can create valid AAF objects.
	  checkResult(pHeader->GetDictionary(&pDictionary));
 		
	  CAAFBuiltinDefs defs (pDictionary);

	  //Make the first mob
	  long	test;

	  // Create a concrete subclass of Mob
	  checkResult(defs.cdMasterMob()->
				  CreateInstance(IID_IAAFMob, 
								 (IUnknown **)&pMob));
	  checkResult( pMob->QueryInterface(IID_IAAFMob2,(void**)&pMobInterface2));

	  checkResult(pMob->SetMobID(MOBTestID));
      checkExpression(pMob->GetNameBufLen(&bufLen) == AAFRESULT_PROP_NOT_PRESENT, AAFRESULT_TEST_FAILED);
      checkExpression(pMob->GetName(name, 0) == AAFRESULT_PROP_NOT_PRESENT, AAFRESULT_TEST_FAILED);
	  checkExpression(pMob->SetName(NULL) == AAFRESULT_NULL_PARAM, AAFRESULT_TEST_FAILED);
	  checkResult(pMob->SetName(mobName));
	  
	  checkResult(pMob->SetCreateTime(creationTimeStamp));
	  checkResult(pMob->SetModTime(modificationTimeStamp));

	  // Add some slots
	  for(test = 1; test < 6; test++)
		{
		  checkResult(defs.cdSourceClip()->
					  CreateInstance(IID_IAAFSourceClip, 
									 (IUnknown **)&sclp));		
		  checkResult(sclp->QueryInterface(IID_IAAFSourceReference, (void **)&pSourceRef));
		  checkResult(pSourceRef->SetSourceID(MOBTestID3));

		  checkResult(sclp->QueryInterface(IID_IAAFComponent, (void **)&pComponent));
		  checkResult(pComponent->SetDataDef(defs.ddkAAFPicture()));

		  checkResult(sclp->QueryInterface (IID_IAAFSegment, (void **)&seg));

		  aafRational_t editRate = { 0, 1};
		  checkResult(pMob->AppendNewTimelineSlot (editRate,
												   seg,
												   test+1,
												   slotNames[test],
												   0,
												   &newSlot));

		

		  if(test == 5)
		  {
			  checkExpression(pMob->AppendNewTimelineSlot (editRate,
										   NULL,
										   test+1,
										   slotNames[test],
										   0,
										   &newSlot) == AAFRESULT_NULL_PARAM, 
										   AAFRESULT_TEST_FAILED);

			  checkExpression(pMob->AppendNewTimelineSlot (editRate,
										   seg,
										   test+1,
										   NULL,
										   0,
										   &newSlot) == AAFRESULT_NULL_PARAM, 
										   AAFRESULT_TEST_FAILED);

			  checkExpression(pMob->AppendNewTimelineSlot (editRate,
										   seg,
										   test+1,
										   slotNames[test],
										   0,
										   NULL) == AAFRESULT_NULL_PARAM, 
										   AAFRESULT_TEST_FAILED);

			  pMob->RemoveSlotAt(4);
			  checkExpression(pMob->RemoveSlotAt(test+1) == AAFRESULT_BADINDEX,
			  							   AAFRESULT_TEST_FAILED);
		  }

		  newSlot->Release();
		  newSlot = NULL;

		  if(newStaticSlot)
			newStaticSlot->Release();
		  newStaticSlot = NULL;

		  seg->Release();
		  seg = NULL;

		  sclp->Release();
		  sclp = NULL;
		  
		  pComponent->Release();
		  pComponent = NULL;
		  
		  pSourceRef->Release();
		  pSourceRef = NULL;
		}



		// PrependSlot
 		checkResult(defs.cdStaticMobSlot()->
					  CreateInstance(IID_IAAFMobSlot, 
									 (IUnknown **)&mSlot));		
 		checkResult(defs.cdFiller()->
					  CreateInstance(IID_IAAFFiller, 
									 (IUnknown **)&filler));		

		checkResult(filler->Initialize(defs.ddkAAFSound(), 10));
		checkResult(filler->QueryInterface (IID_IAAFSegment, (void **)&seg));

		checkResult(mSlot->SetName(slotNames[0]));
		checkResult(mSlot->SetPhysicalNum(1));
		checkResult(mSlot->SetSlotID(1));
		checkResult(mSlot->SetSegment(seg));

		checkResult(pMob->PrependSlot(mSlot));
		checkExpression(pMob->PrependSlot(mSlot) == AAFRESULT_OBJECT_ALREADY_ATTACHED,
															AAFRESULT_TEST_FAILED);			
		checkExpression(pMob->PrependSlot(NULL) == AAFRESULT_NULL_PARAM, 
												  AAFRESULT_TEST_FAILED);
		mSlot->Release();
		mSlot = NULL;
		
		seg->Release();
		seg = NULL;
		
		filler->Release();
		filler = NULL;

		// AppendSlot
 		checkResult(defs.cdStaticMobSlot()->
					  CreateInstance(IID_IAAFMobSlot, 
									 (IUnknown **)&mSlot));		
 		checkResult(defs.cdFiller()->
					  CreateInstance(IID_IAAFFiller, 
									 (IUnknown **)&filler));		

		checkResult(filler->Initialize(defs.ddkAAFSound(), 10));
		checkResult(filler->QueryInterface (IID_IAAFSegment, (void **)&seg));

		checkResult(mSlot->SetName(slotNames[6]));
		checkResult(mSlot->SetPhysicalNum(1));
		checkResult(mSlot->SetSlotID(7));
		checkResult(mSlot->SetSegment(seg));

		checkResult(pMob->AppendSlot(mSlot));
		checkExpression(pMob->AppendSlot(mSlot) == AAFRESULT_OBJECT_ALREADY_ATTACHED,
															AAFRESULT_TEST_FAILED);			
		checkExpression(pMob->AppendSlot(NULL) == AAFRESULT_NULL_PARAM, 
												  AAFRESULT_TEST_FAILED);
		mSlot->Release();
		mSlot = NULL;
		
		seg->Release();
		seg = NULL;

		filler->Release();
		filler = NULL;

 		// InsertSlotAt -- insert a timecode object for OffsetToMobTimecode() testing
		timecode.startFrame = TCstartFrame;	// One hour
		timecode.drop = TCdrop;
		timecode.fps = TCfps;

		checkResult(defs.cdTimecode()->
					  CreateInstance(IID_IAAFTimecode, 
									 (IUnknown **)&pTimecode));
		checkResult(pTimecode->Initialize(100, &timecode));		
		checkResult(pTimecode->QueryInterface (IID_IAAFSegment, (void **)&seg));
		
		assert(pComponent == NULL);
		checkResult(pTimecode->QueryInterface(IID_IAAFComponent,(void **)&pComponent));
		checkResult(pComponent->SetDataDef(defs.ddkAAFTimecode()));
		pComponent->Release();
		pComponent = NULL;

 		checkResult(defs.cdStaticMobSlot()->
					  CreateInstance(IID_IAAFMobSlot, 
									 (IUnknown **)&mSlot));		

		checkResult(mSlot->SetName(slotNames[5]));
		checkResult(mSlot->SetPhysicalNum(1));
		checkResult(mSlot->SetSlotID(6));
		checkResult(mSlot->SetSegment(seg));

		checkExpression(pMob->InsertSlotAt(8, mSlot) == AAFRESULT_BADINDEX, 
												  AAFRESULT_TEST_FAILED);
		checkResult(pMob->InsertSlotAt(5, mSlot));

		checkExpression(pMob->InsertSlotAt(4, mSlot) == AAFRESULT_OBJECT_ALREADY_ATTACHED,
															AAFRESULT_TEST_FAILED);			
		checkExpression(pMob->InsertSlotAt(1, NULL) == AAFRESULT_NULL_PARAM, 
												  AAFRESULT_TEST_FAILED);
		mSlot->Release();
		mSlot = NULL;

		seg->Release();
		seg = NULL;
		
		pTimecode->Release();
		pTimecode = NULL;


		//now test AppendNewStaticSlot
		checkResult(defs.cdSourceClip()->
			CreateInstance(IID_IAAFSourceClip, 
			(IUnknown **)&sclp));		
		checkResult(sclp->QueryInterface(IID_IAAFSourceReference, (void **)&pSourceRef));
		checkResult(pSourceRef->SetSourceID(MOBTestID_Static));

		checkResult(sclp->QueryInterface(IID_IAAFComponent, (void **)&pComponent));
		checkResult(pComponent->SetDataDef(defs.ddkAAFPicture()));

		checkResult(sclp->QueryInterface (IID_IAAFSegment, (void **)&seg));

		checkResult(pMobInterface2->AppendNewStaticSlot (  seg,
			8,
			slotNames[7],
			&newStaticSlot));

		if(newStaticSlot)
			newStaticSlot->Release();
		newStaticSlot = NULL;


		seg->Release();
		seg = NULL;

		pSourceRef->Release();
		pSourceRef = NULL;

		sclp->Release();
		sclp = NULL;

		pComponent->Release();
		pComponent = NULL;



		//now test AppendNewEventSlot

		//Create a concrete version of IAAFEvent
		checkResult (pDictionary->CreateMetaInstance (AUID_AAFClassDef, IID_IAAFClassDef, (IUnknown**) &pcdEventMeta));
		checkResult (pDictionary->LookupClassDef (AUID_AAFEvent, &pcdEvent));
		checkResult (pcdEventMeta->Initialize (kClassID_ConcreteEvent, pcdEvent, L"COncreteEvent", kAAFTrue));
		checkResult (pDictionary->RegisterClassDef (pcdEventMeta));

		//Now instantiate it
		checkResult(pDictionary->LookupClassDef(kClassID_ConcreteEvent, &pcdEventConcrete));
		checkResult(pcdEventConcrete->CreateInstance(IID_IAAFEvent, (IUnknown **)&event));
		
		//and initialize reqruied properties
		checkResult(event->QueryInterface(IID_IAAFComponent, (void **)&pComponent));
		checkResult(pComponent->SetDataDef(defs.ddkAAFPicture()));
		event->SetPosition(1);

		aafRational_t EventeditRate = { 0, 1};

		//get the segment
		checkResult(event->QueryInterface (IID_IAAFSegment, (void **)&seg));
		checkResult(pMobInterface2->AppendNewEventSlot (  EventeditRate,
															seg,
															9,
															slotNames[8],
															0,
															&newEventSlot));

		if(newEventSlot)
			newEventSlot->Release();
		newEventSlot = NULL;

		seg->Release();
		seg = NULL;

		pComponent->Release();
		pComponent = NULL;

		event->Release();
		event = NULL;

		pcdEventConcrete->Release();
		pcdEventConcrete = NULL;

		pcdEvent->Release();
		pcdEvent = NULL;

		pcdEventMeta->Release();
		pcdEventMeta = NULL;


		// Try CountKLVData before any have been attached
		numFound = 1;
		checkResult(pMob->CountKLVData(&numFound));
		checkExpression(numFound == 0, AAFRESULT_TEST_FAILED);
		checkExpression(pMob->CountKLVData(NULL) == AAFRESULT_NULL_PARAM,
			AAFRESULT_TEST_FAILED);		  
		// AppendKLVData - attach some objects
		checkResult(pDictionary->LookupTypeDef (kAAFTypeID_UInt8Array, &pBaseType));
		checkResult(pDictionary->RegisterKLVDataKey(TEST_KLV, pBaseType));
		pBaseType->Release();
		pBaseType = NULL;

		checkExpression(pMob->AppendKLVData(NULL) == AAFRESULT_NULL_PARAM,
		  												AAFRESULT_TEST_FAILED);	
 		checkResult(defs.cdKLVData()->
					  CreateInstance(IID_IAAFKLVData, 
									 (IUnknown **)&pKLVData));									 		
		checkResult(pKLVData->Initialize(TEST_KLV, sizeof(KLVfrowney), 
		  													(unsigned char *)KLVfrowney));
		checkResult(pMob->AppendKLVData(pKLVData));		  
		pKLVData->Release();
		pKLVData = NULL;
		  
 		checkResult(defs.cdKLVData()->
					  CreateInstance(IID_IAAFKLVData, 
									 (IUnknown **)&pKLVData));
		checkResult(pKLVData->Initialize(TEST_KLV, sizeof(KLVfrowney), 
		  													(unsigned char *)KLVfrowney));
		checkResult(pMob->AppendKLVData(pKLVData));		  
		checkExpression(pMob->AppendKLVData(pKLVData) == AAFRESULT_OBJECT_ALREADY_ATTACHED,
		  														AAFRESULT_TEST_FAILED);		  
		  												
		// RemoveKLVData - remove object #2
		checkExpression(pMob->RemoveKLVData(NULL) == AAFRESULT_NULL_PARAM,
		  												AAFRESULT_TEST_FAILED);		  
 		checkResult(pMob->CountKLVData(&numFound));
		checkExpression(numFound == 2, AAFRESULT_TEST_FAILED);
 		checkResult(pMob->RemoveKLVData(pKLVData));
 		checkResult(pMob->CountKLVData(&numFound));
		checkExpression(numFound == 1, AAFRESULT_TEST_FAILED);
		pKLVData->Release();
		pKLVData = NULL;
 		  
		// Try removing an object that is not attached
 		checkResult(defs.cdKLVData()->
					  CreateInstance(IID_IAAFKLVData, 
									 (IUnknown **)&pKLVData));
		checkResult(pKLVData->Initialize(TEST_KLV, sizeof(KLVsmiley), 
		  													(unsigned char *)KLVsmiley));
		checkExpression(pMob->RemoveKLVData(pKLVData) == AAFRESULT_OBJECT_NOT_ATTACHED, 
		  												AAFRESULT_TEST_FAILED);
		// Attach it to replace the one removed												
		checkResult(pMob->AppendKLVData(pKLVData));

		pKLVData->Release();
		pKLVData = NULL;

		// Comments
		checkExpression(pMob->GetComments(&enumTaggedVal) == AAFRESULT_PROP_NOT_PRESENT,
													AAFRESULT_TEST_FAILED);
		// Check CountComments()
		checkExpression(pMob->CountComments(NULL) == AAFRESULT_NULL_PARAM,
															AAFRESULT_TEST_FAILED);
		numComments = 1;
		checkResult(pMob->CountComments(&numComments));
		checkExpression(numComments == 0, AAFRESULT_TEST_FAILED);
		
		// Check AppendComments()
		checkExpression(pMob->AppendComment(NULL, pComment[0]) == AAFRESULT_NULL_PARAM,
																	AAFRESULT_TEST_FAILED);
		checkExpression(pMob->AppendComment(const_cast<aafWChar*>(pCategory[0]), NULL) == AAFRESULT_NULL_PARAM,
																	AAFRESULT_TEST_FAILED);
		for (i = 0; i < 5; ++i)
		{
		checkResult(pMob->AppendComment(const_cast<aafWChar*>(pCategory[i]), pComment[i]));
		}

		checkResult(pMob->CountComments(&numComments));
		checkExpression(numComments == 5, AAFRESULT_TEST_FAILED);

		// Check GetComments()
		checkExpression(pMob->GetComments(NULL) == AAFRESULT_NULL_PARAM,
													AAFRESULT_TEST_FAILED);
		checkResult(pMob->GetComments(&enumTaggedVal));
		for (i = 0; i < 5; ++i)
		{						
			checkResult(enumTaggedVal->NextOne(&taggedVal));
			
			checkResult(taggedVal->GetNameBufLen(&bufLen));
			checkResult(taggedVal->GetName(name, bufLen));
			checkExpression(wcscmp(name, pCategory[i]) == 0, AAFRESULT_TEST_FAILED);
			
			checkResult(taggedVal->GetValueBufLen(&bufLen));
			checkResult(taggedVal->GetValue(bufLen, (aafDataBuffer_t)value, &bytesRead));
			checkExpression(wcscmp(value, pComment[i]) == 0, AAFRESULT_TEST_FAILED);

			taggedVal->Release();
			taggedVal = NULL;
		}		

		
 		checkResult(defs.cdTaggedValue()->
					  CreateInstance(IID_IAAFTaggedValue, 
									 (IUnknown **)&taggedVal));		
						
		checkExpression(pMob->RemoveComment(taggedVal) == AAFRESULT_OBJECT_NOT_ATTACHED, 
													AAFRESULT_TEST_FAILED);
		taggedVal->Release();
		taggedVal = NULL;

		enumTaggedVal->Reset();
		enumTaggedVal->Skip(2);
		checkResult(enumTaggedVal->NextOne(&taggedVal));
		checkExpression(pMob->RemoveComment(NULL) == AAFRESULT_NULL_PARAM, 
													AAFRESULT_TEST_FAILED);
		checkResult(pMob->RemoveComment(taggedVal));
		taggedVal->Release();
		taggedVal = NULL;
			
		enumTaggedVal->Reset();
		for (i = 0; i < 5; ++i)
		{
 			if (i==2)
 				continue;
 										
			checkResult(enumTaggedVal->NextOne(&taggedVal));
			
			checkResult(taggedVal->GetNameBufLen(&bufLen));
			checkResult(taggedVal->GetName(name, bufLen));
			checkExpression(wcscmp(name, pCategory[i]) == 0, AAFRESULT_TEST_FAILED);
			
			checkResult(taggedVal->GetValueBufLen(&bufLen));
			checkResult(taggedVal->GetValue(bufLen, (aafDataBuffer_t)value, &bytesRead));
			checkExpression(wcscmp(value, pComment[i]) == 0, AAFRESULT_TEST_FAILED);

			taggedVal->Release();
			taggedVal = NULL;
		}		

		enumTaggedVal->Release();
		enumTaggedVal = NULL;
		

  	  // Check the Mob2 attribute and usage code implementations.
 	  // Need IAAFMob2 for that;
	 checkResult( pMobInterface2->AppendAttribute( AttributeNames[0], AttributeValues[0] ) );
	 checkResult( pMobInterface2->AppendAttribute( AttributeNames[1], AttributeValues[1] ) );
	 checkResult( pMobInterface2->SetUsageCode( kAAFUsage_SubClip ) );

	  // Add the mob to the file.
	  checkResult(pHeader->AddMob(pMob));

	  // Test changing the mob id after the mob is attached to the
	  // content store.  Change it, then reset to the original id.
	  checkResult(pMob->SetMobID(MOBTestID2));
	  checkResult(pMob->SetMobID(MOBTestID));
	  
	  // Create another Mob, check mob count, then delete and recheck count
	  checkResult(defs.cdMasterMob()->
				  CreateInstance(IID_IAAFMob, 
								 (IUnknown **)&pMob2));

	  checkResult(pMob2->SetMobID(MOBTestID2));
	  checkResult(pMob2->SetName(mobName));
	  
	  checkResult(pMob2->SetCreateTime(creationTimeStamp));
	  checkResult(pMob2->SetModTime(modificationTimeStamp));
	  // Add the mob to the file.
	  checkResult(pHeader->AddMob(pMob2));
	  checkResult(pHeader->CountMobs(kAAFAllMob, &numMobs));
	  checkExpression(numMobs == 2, AAFRESULT_TEST_FAILED);
	  checkResult(pHeader->RemoveMob(pMob2));
	  checkResult(pHeader->CountMobs(kAAFAllMob, &numMobs));
	  checkExpression(numMobs == 1, AAFRESULT_TEST_FAILED);

	  //try Copy()
	  const aafCharacter *copy_name = L"Name of Copied Mob";
	  IAAFMobSP spCopiedMob;
	  checkResult(pMob->Copy(copy_name, &spCopiedMob));
	  checkResult(pHeader->CountMobs(kAAFAllMob, &numMobs));
	  checkExpression(numMobs == 2, AAFRESULT_TEST_FAILED);
	  checkResult(pHeader->RemoveMob(spCopiedMob));
	  checkResult(pHeader->CountMobs(kAAFAllMob, &numMobs));
	  checkExpression(numMobs == 1, AAFRESULT_TEST_FAILED);

	  //try CloneExternal
	  IAAFMobSP spClonedMob;
	  IAAFFileSP spDestFile;
	  aafCharacter dest_filename[128];
	  wcscpy(dest_filename, pFileName);
	  wcscat(dest_filename, L"_clone");


	  // Remove the previous test file if any.
	  RemoveTestFile(dest_filename);
	  try
	  {
		checkResult(CreateTestFile( dest_filename, fileKind, rawStorageType, productID, &spDestFile ));
		hr = pMob->CloneExternal(kAAFNoFollowDepend, kAAFNoIncludeMedia, spDestFile, &spClonedMob);
		checkExpression(hr == AAFRESULT_SUCCESS || hr == AAFRESULT_NOT_IMPLEMENTED || hr == AAFRESULT_NOT_IN_CURRENT_VERSION,
						AAFRESULT_TEST_FAILED);
	  }
	  catch (HRESULT& rResult)
	  {
		hr = rResult;
	  }

	  if (spDestFile)
	  {
		spDestFile->Save();
		spDestFile->Close();
	  }
	}
  catch (HRESULT& rResult)
	{
	  hr = rResult;
	}


  // Cleanup and return
  if (enumTaggedVal)
    enumTaggedVal->Release();

  if (newSlot)
    newSlot->Release();

  if (newStaticSlot)
	newStaticSlot->Release();
		 

  if (seg)
    seg->Release();

  if (pComponent)
    pComponent->Release();

  if (sclp)
    sclp->Release();

  if (pMob)
    pMob->Release();

  if (pMob2)
    pMob2->Release();

  if (pMobInterface2)
    pMobInterface2->Release();

  if (pDictionary)
    pDictionary->Release();

  if (pHeader)
    pHeader->Release();

 if(pcdEventMeta)
	  pcdEventMeta->Release();

 if(pcdEvent)
	  pcdEvent->Release();

  if(pcdEventConcrete)
	  pcdEventConcrete->Release();
 

      
  if (pFile)
	{  // Close file
	  if (bFileOpen)
		{
		  pFile->Save();
		  pFile->Close();
		}
	  pFile->Release();
	}

  return hr;
}

static void checkTimeStampsAreEqual(aafTimeStamp_constref ts1, aafTimeStamp_constref ts2)
{
  // Check the time stamp: should be 7 December, 1941 at 05:13:12.01
  checkExpression (ts1.date.year == ts2.date.year, AAFRESULT_TEST_FAILED);
  checkExpression (ts1.date.month == ts2.date.month, AAFRESULT_TEST_FAILED);
  checkExpression (ts1.date.day == ts2.date.day, AAFRESULT_TEST_FAILED);
  checkExpression (ts1.time.hour == ts2.time.hour, AAFRESULT_TEST_FAILED);
  checkExpression (ts1.time.minute == ts2.time.minute, AAFRESULT_TEST_FAILED);
  checkExpression (ts1.time.second == ts2.time.second, AAFRESULT_TEST_FAILED);
  checkExpression (ts1.time.fraction == ts2.time.fraction, AAFRESULT_TEST_FAILED);
}

static HRESULT ReadAAFFile(aafWChar * pFileName)
{
  IAAFDictionary		*pDictionary = NULL;
  IAAFFile 				*pFile = NULL;
  bool 					bFileOpen = false;
  IAAFHeader 			*pHeader = NULL;
  IEnumAAFMobs 			*mobIter = NULL;
  IAAFMob				*aMob = NULL;
  IEnumAAFMobSlots		*slotIter = NULL;
  IAAFMobSlot			*slot = NULL;
  aafNumSlots_t			numMobs, n, s;
  HRESULT				hr = S_OK;
  aafUInt32 			bufLen = 0;
  aafUInt32 			bytesRead = 0;
  aafUInt32				numFound = 0;
  aafWChar				value[500];
  IEnumAAFTaggedValues 	*enumTaggedVal = NULL;
  IAAFTaggedValue		*taggedVal = NULL;
  aafUID_t				testKey;
  IEnumAAFKLVData		*klvEnum = NULL;
  IAAFKLVData			*pKLVData = NULL;
  IAAFTypeDef*			pBaseType = NULL;
  IAAFSourceClip		*pSourceClip = NULL;
  IAAFSourceReference	*pSourceRef = NULL;
  IAAFSegment			*pSegment = NULL;
  aafMobID_t			sourceID;
  int 					i;


  try
	{
	  // Open the file
	  checkResult(AAFFileOpenExistingRead(pFileName, 0, &pFile));
	  bFileOpen = true;

	  // We can't really do anthing in AAF without the header.
	  checkResult(pFile->GetHeader(&pHeader));
	  checkResult(pHeader->GetDictionary(&pDictionary));
 	  CAAFBuiltinDefs defs (pDictionary);


	  checkResult(pHeader->CountMobs(kAAFAllMob, &numMobs));
	  checkExpression(1 == numMobs, AAFRESULT_TEST_FAILED);


	  aafSearchCrit_t		criteria;
	  criteria.searchTag = kAAFNoSearch;
	  checkResult(pHeader->GetMobs (&criteria, &mobIter));

	  for(n = 0; n < numMobs; n++)
		{
		  aafWChar		name[500], slotName[500];
		  aafNumSlots_t	numSlots;
		  aafMobID_t		mobID;
		  aafSlotID_t		trackID;
		  aafUInt32 nameBufLen = 0;

		  checkResult(mobIter->NextOne (&aMob));
      
	      // Check GetNameBufLen and GetName
	      checkExpression(aMob->GetNameBufLen(NULL) == AAFRESULT_NULL_PARAM, AAFRESULT_TEST_FAILED);
	      checkResult(aMob->GetNameBufLen(&nameBufLen));
	      checkExpression(((wcslen(mobName) + 1) * sizeof(aafCharacter)) == nameBufLen, AAFRESULT_TEST_FAILED);
		  checkExpression(aMob->GetName (NULL, nameBufLen) == AAFRESULT_NULL_PARAM, AAFRESULT_TEST_FAILED);
		  checkExpression(aMob->GetName (name, 4) == AAFRESULT_SMALLBUF, AAFRESULT_TEST_FAILED);
		  checkResult(aMob->GetName (name, nameBufLen));
		  checkExpression (wcscmp(mobName, name) == 0, AAFRESULT_TEST_FAILED);

	      // Check GetMobID
		  checkExpression(aMob->GetMobID (NULL) == AAFRESULT_NULL_PARAM, AAFRESULT_TEST_FAILED);
		  checkResult(aMob->GetMobID (&mobID));
		  checkExpression(memcmp(&MOBTestID, &mobID, sizeof(mobID)) == 0, AAFRESULT_TEST_FAILED);

		  // Check the time stamps
		  aafTimeStamp_t created = { {0,0,0}, {0,0,0,0} };
		  checkExpression(aMob->GetCreateTime(NULL) == AAFRESULT_NULL_PARAM, AAFRESULT_TEST_FAILED);
		  checkResult(aMob->GetCreateTime(&created));
		  checkTimeStampsAreEqual(creationTimeStamp, created);
		  aafTimeStamp_t modified = { {0,0,0}, {0,0,0,0} };
		  checkExpression(aMob->GetModTime(NULL) == AAFRESULT_NULL_PARAM, AAFRESULT_TEST_FAILED);
		  checkResult(aMob->GetModTime(&modified));
		  checkTimeStampsAreEqual(modificationTimeStamp, modified);

	      // Check the GetMobInfo data.
	      memset(&created, 0, sizeof(created));
	      memset(&modified, 0, sizeof(modified));
	      checkExpression(aMob->GetMobInfo(NULL, &created, 
      								   name, sizeof(name)) == AAFRESULT_NULL_PARAM,
      														  AAFRESULT_TEST_FAILED);
	      checkExpression(aMob->GetMobInfo(&modified, NULL, 
      								   name, sizeof(name)) == AAFRESULT_NULL_PARAM,
      														  AAFRESULT_TEST_FAILED);
	      checkExpression(aMob->GetMobInfo(&modified, &created, 
      								   NULL, sizeof(name)) == AAFRESULT_NULL_PARAM,
      														  AAFRESULT_TEST_FAILED);
		  checkExpression(aMob->GetMobInfo(&modified, &created, 
      								   name, 1) == AAFRESULT_SMALLBUF,
      												AAFRESULT_TEST_FAILED);
	      checkResult(aMob->GetMobInfo(&modified, &created, name, sizeof(name)));
		  checkTimeStampsAreEqual(creationTimeStamp, created);
		  checkTimeStampsAreEqual(modificationTimeStamp, modified);
		  checkExpression (wcscmp(mobName, name) == 0, AAFRESULT_TEST_FAILED);

		  checkExpression(aMob->CountSlots (NULL) == AAFRESULT_NULL_PARAM, AAFRESULT_TEST_FAILED);
		  checkResult(aMob->CountSlots (&numSlots));

		  //seven slots made by IAAFMob and  one static slot and event slot made throught IAAFMOb2
		  checkExpression((7+1+1) == numSlots, AAFRESULT_TEST_FAILED);

		  checkExpression(aMob->GetSlots(NULL) == AAFRESULT_NULL_PARAM, AAFRESULT_TEST_FAILED);
		  checkResult(aMob->GetSlots(&slotIter));

		  for(s = 0; s < numSlots; s++)
			{
			  checkResult(slotIter->NextOne (&slot));
			  checkResult(slot->GetNameBufLen(&bufLen));
			  checkResult(slot->GetName (slotName, bufLen));
			  checkResult(slot->GetSlotID(&trackID));
			  checkExpression (wcscmp(slotName, slotNames[s]) == 0, AAFRESULT_TEST_FAILED);
			  checkExpression(trackID == (s+1), AAFRESULT_TEST_FAILED);

			  slot->Release();
			  slot = NULL;
			  bufLen = 0;
			  trackID = 0;
			}
			slotIter->Release();
			slotIter = NULL;
			
			// GetSlotAt
			checkExpression(aMob->GetSlotAt(1, NULL) == AAFRESULT_NULL_PARAM,
														AAFRESULT_TEST_FAILED);
			checkExpression(aMob->GetSlotAt(9, &slot) == AAFRESULT_BADINDEX,
														AAFRESULT_TEST_FAILED);
			for (s = 0; s < numSlots; ++s)
			{
				checkResult(aMob->GetSlotAt(s, &slot));
				checkResult(slot->GetNameBufLen(&bufLen));
				checkResult(slot->GetName(slotName, bufLen));
				checkResult(slot->GetSlotID(&trackID));
				checkExpression(wcscmp(slotName, slotNames[s]) == 0, AAFRESULT_TEST_FAILED);
				checkExpression(trackID == (s+1), AAFRESULT_TEST_FAILED);	

				if ( 0 < s && s < 5 ) // These are the SourceClips
				{
					checkResult(slot->GetSegment(&pSegment));
			  		checkResult(pSegment->QueryInterface (IID_IAAFSourceClip, (void **)&pSourceClip));
				  	checkResult(pSourceClip->QueryInterface (IID_IAAFSourceReference, (void **)&pSourceRef));
				    checkResult(pSourceRef->GetSourceID(&sourceID));
				    checkExpression(memcmp(&sourceID, &MOBTestID3, sizeof(aafMobID_t)) == 0,
				    													 AAFRESULT_TEST_FAILED);
			  		pSourceRef->Release();
			  		pSourceRef = NULL;
			  		pSourceClip->Release();
            pSourceClip = NULL;
			  		pSegment->Release();
            pSegment = NULL;
				}
				
				slot->Release();
				slot = NULL;
				bufLen = 0;
				trackID = 0;
			}			

		  // ChangeRef
		  checkResult(aMob->ChangeRef(MOBTestID3, MOBTestID4));

		  for (s = 1; s < 5; ++s) // These are the SourceClips
		  {
				checkResult(aMob->GetSlotAt(s, &slot));
				checkResult(slot->GetSegment(&pSegment));
  		  		checkResult(pSegment->QueryInterface (IID_IAAFSourceClip, (void **)&pSourceClip));
	  	  		checkResult(pSourceClip->QueryInterface (IID_IAAFSourceReference, (void **)&pSourceRef));
	      		checkResult(pSourceRef->GetSourceID(&sourceID));
	      		checkExpression(memcmp(&sourceID, &MOBTestID4, sizeof(aafMobID_t)) == 0,
		   													 AAFRESULT_TEST_FAILED);
			  	pSourceRef->Release();
			  	pSourceRef = NULL;
			  	pSourceClip->Release();
			  	pSourceClip = NULL;
			  	pSegment->Release();
			  	pSegment = NULL;
		  		slot->Release();
			  	slot = NULL;
		  }

		  // try it again with a MobID it won't find.  Make sure nothing changes
		  checkResult(aMob->ChangeRef(MOBTestID3, MOBTestID2));

		  for (s = 1; s < 5; ++s) // These are the SourceClips
		  {
				checkResult(aMob->GetSlotAt(s, &slot));
				checkResult(slot->GetSegment(&pSegment));
  		  		checkResult(pSegment->QueryInterface (IID_IAAFSourceClip, (void **)&pSourceClip));
	  	  		checkResult(pSourceClip->QueryInterface (IID_IAAFSourceReference, (void **)&pSourceRef));
	      		checkResult(pSourceRef->GetSourceID(&sourceID));
	      		checkExpression(memcmp(&sourceID, &MOBTestID4, sizeof(aafMobID_t)) == 0,
		   													 AAFRESULT_TEST_FAILED);
			  	pSourceRef->Release();
			  	pSourceRef = NULL;
			  	pSourceClip->Release();
			  	pSourceClip = NULL;
			  	pSegment->Release();
			  	pSegment = NULL;
		  		slot->Release();
			  	slot = NULL;
		  }

		  // LookUpSlot
		  checkResult(aMob->LookupSlot(4, &slot));
		  checkResult(slot->GetSegment(&pSegment));
		  checkResult(pSegment->QueryInterface (IID_IAAFSourceClip, (void **)&pSourceClip));
		  checkResult(pSourceClip->QueryInterface (IID_IAAFSourceReference, (void **)&pSourceRef));
		  checkResult(pSourceRef->GetSourceID(&sourceID));

		  checkResult(slot->GetNameBufLen(&bufLen));
		  checkResult(slot->GetName(slotName, bufLen));
		  checkResult(slot->GetSlotID(&trackID));
		  checkExpression(wcscmp(slotName, slotNames[3]) == 0, AAFRESULT_TEST_FAILED);
		  checkExpression(trackID == (4), AAFRESULT_TEST_FAILED);	

		  pSourceRef->Release();
		  pSourceRef = NULL;		
		  pSourceClip->Release();
		  pSourceClip = NULL;		
		  pSegment->Release();
		  pSegment = NULL;		
		  slot->Release();
		  slot = NULL;		

      
      checkExpression(aMob->LookupSlot(10, &slot) == AAFRESULT_SLOT_NOT_FOUND,
													AAFRESULT_TEST_FAILED);

		  checkExpression(aMob->LookupSlot(0, NULL) == AAFRESULT_NULL_PARAM,
													AAFRESULT_TEST_FAILED);
					  												
		  // OffsetToMobTimecode
		  // 7/5/00  - this method is broken so the tests that will 
		  // make it fail have been commented out.  This module test 
		  // will still report Partial Success until implementation has been fixed
		  aafPosition_t		offset = 1;
		  aafTimecode_t		timecode;
		  // initialize timecode values
		  timecode.startFrame = 0;
		  timecode.drop = kAAFTcDrop;
		  timecode.fps = 24;

		  checkResult(aMob->LookupSlot(6, &slot));
		  checkResult(slot->GetSegment(&pSegment));

		  checkResult(aMob->OffsetToMobTimecode(pSegment, &offset, &timecode));
		  checkExpression(timecode.startFrame == (TCstartFrame + offset), AAFRESULT_TEST_FAILED);
		  checkExpression(timecode.drop == TCdrop, AAFRESULT_TEST_FAILED);
		  checkExpression(timecode.fps == TCfps, AAFRESULT_TEST_FAILED);

		  checkExpression(aMob->OffsetToMobTimecode(pSegment, NULL, &timecode) == AAFRESULT_NULL_PARAM,
															AAFRESULT_TEST_FAILED);
		  checkExpression(aMob->OffsetToMobTimecode(pSegment, &offset, NULL) == AAFRESULT_NULL_PARAM,
															AAFRESULT_TEST_FAILED);
															
		  // reinitialize values
		  timecode.startFrame = 0;
		  timecode.drop = kAAFTcDrop;
		  timecode.fps = 24;

		  // According to IDL this should search for the slot containing the timecode segment
		  checkResult(aMob->OffsetToMobTimecode(NULL, &offset, &timecode));
		  checkExpression(timecode.startFrame == (TCstartFrame + offset), AAFRESULT_TEST_FAILED);
		  checkExpression(timecode.drop == TCdrop, AAFRESULT_TEST_FAILED);
		  checkExpression(timecode.fps == TCfps, AAFRESULT_TEST_FAILED);
															
		  pSegment->Release();
		  pSegment = NULL;
		  slot->Release();
		  slot = NULL;
		  
		  // Pass in a segment that is not a timecode and make sure it returns correct hr
		  checkResult(aMob->LookupSlot(1, &slot));
		  checkResult(slot->GetSegment(&pSegment));
		  checkExpression(aMob->OffsetToMobTimecode(pSegment, &offset, &timecode) == AAFRESULT_TIMECODE_NOT_FOUND,
															AAFRESULT_TEST_FAILED);
		  pSegment->Release();
		  pSegment = NULL;
		  slot->Release();
		  slot = NULL;

		  // GetKLVData
		  checkResult(pDictionary->LookupTypeDef (kAAFTypeID_UInt8Array, &pBaseType));
		  checkResult(pDictionary->RegisterKLVDataKey(TEST_KLV, pBaseType));
		  pBaseType->Release();
		  pBaseType = NULL;

		  checkResult(aMob->CountKLVData(&numFound));
		  checkExpression(numFound == 2, AAFRESULT_TEST_FAILED);
		  checkResult(aMob->GetKLVData(&klvEnum));
		  
		  checkResult(klvEnum->NextOne(&pKLVData));
		  checkResult(pKLVData->GetValueBufLen(&bufLen));
		  checkExpression(sizeof(KLVfrowney) == bufLen, AAFRESULT_TEST_FAILED);
		  checkResult(pKLVData->GetValue( sizeof(value), (unsigned char *)value, &bytesRead));
		  checkExpression(memcmp(value, KLVfrowney, sizeof(KLVfrowney)) == 0, AAFRESULT_TEST_FAILED);
		  checkResult(pKLVData->GetKey(&testKey));
		  checkExpression(memcmp(&testKey, &TEST_KLV, sizeof(aafUID_t)) == 0, AAFRESULT_TEST_FAILED);
		  pKLVData->Release();
		  pKLVData = NULL;

		  checkResult(klvEnum->NextOne(&pKLVData));
		  checkResult(pKLVData->GetValueBufLen(&bufLen));
		  checkExpression(sizeof(KLVsmiley) == bufLen, AAFRESULT_TEST_FAILED);
		  checkResult(pKLVData->GetValue( sizeof(value), (unsigned char *)value, &bytesRead));
		  checkExpression(memcmp(value, KLVsmiley, sizeof(KLVsmiley)) == 0, AAFRESULT_TEST_FAILED);
		  checkResult(pKLVData->GetKey(&testKey));
		  checkExpression(memcmp(&testKey, &TEST_KLV, sizeof(aafUID_t)) == 0, AAFRESULT_TEST_FAILED);
		  pKLVData->Release();
		  pKLVData = NULL;

		  klvEnum->Release();
		  klvEnum = NULL;

		  checkExpression(aMob->GetKLVData(NULL) == AAFRESULT_NULL_PARAM,
		  												AAFRESULT_TEST_FAILED);	  


		  // Check the comments 
		  checkResult(aMob->GetComments(&enumTaggedVal));
		  for (i = 0; i < 5; ++i)
		  {
 			if (i==2)
 				continue;
 										
			checkResult(enumTaggedVal->NextOne(&taggedVal));
			
			checkResult(taggedVal->GetNameBufLen(&bufLen));
			checkResult(taggedVal->GetName(name, bufLen));
			checkExpression(wcscmp(name, pCategory[i]) == 0, AAFRESULT_TEST_FAILED);
			
			checkResult(taggedVal->GetValueBufLen(&bufLen));
			checkResult(taggedVal->GetValue(bufLen, (aafDataBuffer_t)value, &bytesRead));
			checkExpression(wcscmp(value, pComment[i]) == 0, AAFRESULT_TEST_FAILED);

			taggedVal->Release();
			taggedVal = NULL;
		  }		



		  // Check attributes and usage code.
		  // Need IAAFMob2 for that;
		  IAAFMob2* aMobInterface2 = 0;
		  checkResult( aMob->QueryInterface( IID_IAAFMob2, reinterpret_cast<void**>(&aMobInterface2) ) );
		  
		  IEnumAAFTaggedValues* pAttributesEnum = 0;
		  checkResult( aMobInterface2->GetAttributes( &pAttributesEnum ) );

		  int attributeCount = 0;
		  HRESULT atthr = AAFRESULT_SUCCESS;
		  IAAFTaggedValue* pAttribute = 0;
		  for( atthr = pAttributesEnum->NextOne( &pAttribute );
		       atthr == AAFRESULT_SUCCESS;
		       atthr = pAttributesEnum->NextOne( &pAttribute ) ) {

		    aafUInt32 bufLen = 0;
		    checkResult( pAttribute->GetNameBufLen(&bufLen) );

		    // "name" is 500 chars long... sized more than
		    // large enough for a simple test.
		    checkExpression( attributeCount < 2, AAFRESULT_TEST_FAILED );
		    checkResult( pAttribute->GetName( name, bufLen ) );
		    checkExpression( wcscmp(name, AttributeNames[attributeCount] ) == 0, AAFRESULT_TEST_FAILED );


		    // check the value

		    IAAFTypeDef* pAttributeTypeDef = NULL;
		    checkResult( pAttribute->GetTypeDefinition( &pAttributeTypeDef ) );
		    // It should be a string.
		    IAAFTypeDefString* pTDString = NULL;
		    checkResult( pAttributeTypeDef->QueryInterface( IID_IAAFTypeDefString, reinterpret_cast<void**>(&pTDString) ) );
		    checkResult( pAttribute->GetValue( sizeof(name),
		    			       reinterpret_cast<aafDataBuffer_t>(name), &bufLen ) );
		    checkExpression( wcscmp( AttributeValues[attributeCount], name ) == 0, AAFRESULT_TEST_FAILED );
		    

		    pAttributeTypeDef->Release();
		    pAttributeTypeDef = NULL;

		    pTDString->Release();
		    pTDString = NULL;

		    pAttribute->Release();
		    pAttribute = NULL;


		    attributeCount++;
		  }

		  checkExpression( 2 == attributeCount && atthr == AAFRESULT_NO_MORE_OBJECTS,
				   AAFRESULT_TEST_FAILED );

		  aafUID_t code;
		  checkResult( aMobInterface2->GetUsageCode( &code ) );
		  checkExpression( memcmp( &code, &kAAFUsage_SubClip, sizeof(code) ) == 0, AAFRESULT_TEST_FAILED );



		  pAttributesEnum->Release();
		  pAttributesEnum = NULL;
		    
		  enumTaggedVal->Release();
		  enumTaggedVal = NULL;
			
		  aMobInterface2->Release();
		  aMobInterface2 = NULL;
		  aMob->Release();
		  aMob = NULL;
		}




	}
  catch (HRESULT& rResult)
	{
	  hr = rResult;
	}

  // Cleanup object references
  if (slot)
    slot->Release();

  if (slotIter)
    slotIter->Release();

  if (aMob)
    aMob->Release();

  if (mobIter)
    mobIter->Release();

  if (pHeader)
    pHeader->Release();

  if (pDictionary)
    pDictionary->Release();
      
  if (pFile)
	{  // Close file
	  if (bFileOpen)
		pFile->Close();
	  pFile->Release();
	}

  return hr;
}
 

extern "C" HRESULT CAAFMob_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);
extern "C" HRESULT CAAFMob_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID)
{
	HRESULT hr = AAFRESULT_SUCCESS;
	const size_t fileNameBufLen = 128;
	aafWChar pFileName[ fileNameBufLen ] = L"";
	GenerateTestFileName( productID.productName, fileKind, fileNameBufLen, pFileName );

	try
	{
		if(mode == kAAFUnitTestReadWrite)
		{
			hr = CreateAAFFile(pFileName, fileKind, rawStorageType, productID);
		}
		else
			hr = AAFRESULT_SUCCESS;
		if(hr == AAFRESULT_SUCCESS)
		{
			hr = ReadAAFFile( pFileName );
		}

		if(hr == AAFRESULT_SUCCESS)
		{
			aafCharacter pClonedFileName[ fileNameBufLen ];
			wcscpy(pClonedFileName, pFileName);
			wcscat(pClonedFileName, L"_cloned");

			if(mode == kAAFUnitTestReadWrite)
			{
				hr = CreateClonedAAFFile(pClonedFileName, fileKind, rawStorageType, productID);
			}

			if(hr == AAFRESULT_SUCCESS)
			{
				hr = ReadClonedAAFFile(pClonedFileName);
			}
		}
	}
	catch (...)
	{
	  cerr << "CAAFMob_test...Caught general C++"
		   << " exception!" << endl; 
	  hr = AAFRESULT_TEST_FAILED;
	}

  // Cleanup our object if it exists.

  return hr;
}
