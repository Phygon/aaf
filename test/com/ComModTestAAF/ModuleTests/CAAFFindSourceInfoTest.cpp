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

#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#include "AAFStoredObjectIDs.h"
#include "AAFResult.h"
#include "ModuleTest.h"
#include "AAFDataDefs.h"
#include "AAFDefUIDs.h"

#include "CAAFBuiltinDefs.h"

#include "AAFSmartPointer.h"
typedef IAAFSmartPointer<IAAFDataDef> IAAFDataDefSP;

#define	MobName			L"MasterMOBTest"
#define	NumMobSlots		4

static const aafWChar *	slotNames[NumMobSlots] = { L"VIDEO SLOT", L"AUDIO SLOT1", L"AUDIO SLOT2", L"AUDIO SLOT3"};
static const aafUID_t *	slotDDefs[NumMobSlots] = {&kAAFDataDef_Picture, &kAAFDataDef_Sound, &kAAFDataDef_Sound, &kAAFDataDef_Sound};
static aafRational_t	slotRates[NumMobSlots] = { {2997,100}, {44100, 1}, {48000, 1}, {48000, 1}};
static const aafWChar* Manufacturer = L"Sony";
static const aafWChar* Model = L"MyModel";
static aafTapeCaseType_t FormFactor = kAAFVHSVideoTape;
static aafVideoSignalType_t VideoSignalType = kAAFPALSignal;
static aafTapeFormatType_t TapeFormat = kAAFVHSFormat;
static aafUInt32 TapeLength = 3200 ;

//static aafMobID_t		NewMobID;
//--cf  This will require some work!!!
static const 	aafMobID_t	TEST1_Master_MobID =
{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
0x13, 0x00, 0x00, 0x00,
{0x8056f1f4, 0x03ff, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}};

static const 	aafMobID_t	TEST1_Source_MobIDs[NumMobSlots] =
{	//start mobid block
	
	//first id
	{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
		0x13, 0x00, 0x00, 0x00,
	{0x9f66346a, 0x03ff, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}},
	
	//second id
	{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
	0x13, 0x00, 0x00, 0x00,
	{0xbc0e582c, 0x03ff, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}},
	
	//third id
	{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
	0x13, 0x00, 0x00, 0x00,
	{0xcaab21c6, 0x03ff, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}},
	
	//fourth id
	{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
	0x13, 0x00, 0x00, 0x00,
	{0x517e182f, 0x03ff, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}}
	
};	//end mobid block


static const aafLength_t	FILE_MOB_LENGTH_ARR[NumMobSlots] = { 90, 80, 70 };


//{060c2b340205110101001000-13-00-00-00-{f9546632-8d6f-11d4-a380-009027dfca6a}}

static const aafMobID_t TAPE_MOB_ID = {

{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00}, 

0x13, 0x00, 0x00, 0x00, 

{0xf9546632, 0x8d6f, 0x11d4, {0xa3, 0x80, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x6a}}};


static const aafPosition_t	TAPE_MOB_OFFSET_ARR[NumMobSlots] = { 15, 25, 35, 45 };
static const aafLength_t	TAPE_MOB_LENGTH_ARR[NumMobSlots] = { 90, 80, 70, 60 };
static aafMobID_t tapeMobID = TAPE_MOB_ID;

#define TAPE_MOB_NAME	L"A Tape Mob"

static const 	aafMobID_t	TEST2_Source_MobID =
{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
0x13, 0x00, 0x00, 0x00,
{0x6f9ec43c, 0x6f6e, 0x4e73, { 0xae, 0xad, 0x5, 0x74, 0x1a, 0x5a, 0x99, 0xba}}};


static const 	aafMobID_t	TEST3_Master_MobID =
{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
0x13, 0x00, 0x00, 0x00,
{0x9b6d1ff4, 0xb9f1, 0x4a0e, {0xbf, 0x8f, 0xbb, 0x51, 0xf3, 0x9d, 0xd4, 0xbb}}};

static const 	aafMobID_t	TEST3_File_MobID =
{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
0x13, 0x00, 0x00, 0x00,
{0xd362747d, 0xdcba, 0x4339, {0x82, 0xd1, 0xa8, 0xc1, 0xd4, 0x53, 0x1a, 0x17}}};

static const 	aafMobID_t	TEST3_Source_MobID =
{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
0x13, 0x00, 0x00, 0x00,
{0xfb439b90, 0x660d, 0x4e82, {0x85, 0x5e, 0x16, 0x55, 0xa3, 0xd7, 0x9d, 0x77}}};

const aafLength_t TEST3_KnownLength = 465;


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

static HRESULT CreateTestMobChain1(
    IAAFHeader* pHeader)
{
	IAAFDictionary*  pDictionary = NULL;
	IAAFMob*		pMob = NULL;
	IAAFMasterMob*	pMasterMob = NULL;
	IAAFSourceMob* pSrcMob = NULL;
	IAAFSourceMob* pTapeMob = NULL;
	IAAFEssenceDescriptor*	pDesc = NULL;
	IAAFMob*				pTempMob = NULL;
	HRESULT			hr = S_OK;
	long			test;
	aafSourceRef_t	ref;
	IAAFEssenceDescriptor*		pEssDesc = NULL;
	IAAFTapeDescriptor*			pTapeDesc = NULL;
	
	
	try
	{
		// Get the AAF Dictionary so that we can create valid AAF objects.
		checkResult(pHeader->GetDictionary(&pDictionary));
		
		CAAFBuiltinDefs defs (pDictionary);
		
		// Create a Master Mob
		checkResult(defs.cdMasterMob()->
			CreateInstance(IID_IAAFMob, 
			(IUnknown **)&pMob));
		
		// Set the IAAFMob properties
		checkResult(pMob->SetMobID(TEST1_Master_MobID));
		checkResult(pMob->SetName(MobName));
		
		checkResult(pMob->QueryInterface(IID_IAAFMasterMob, (void **) &pMasterMob));
		
		// Create source mob to associate with our MasterMob.
		checkResult(defs.cdSourceMob()->
			CreateInstance(IID_IAAFSourceMob, 
			(IUnknown **)&pTapeMob));		
		hr = defs.cdTapeDescriptor()->
			CreateInstance(IID_IAAFTapeDescriptor, 
			(IUnknown **)&pTapeDesc);		
		if (AAFRESULT_SUCCESS == hr)
		{
			hr = pTapeDesc->QueryInterface(IID_IAAFEssenceDescriptor, (void **)&pEssDesc);
			if (AAFRESULT_SUCCESS == hr)
			{
				hr = pTapeMob->SetEssenceDescriptor(pEssDesc);
				if (AAFRESULT_SUCCESS == hr)
				{
					hr = pTapeDesc->SetTapeManufacturer( Manufacturer );
					if (AAFRESULT_SUCCESS == hr )
					{
						hr = pTapeDesc->SetTapeModel( Model );
						if (AAFRESULT_SUCCESS == hr )
						{
							hr = pTapeDesc->SetTapeFormFactor( FormFactor );
							if (AAFRESULT_SUCCESS == hr )
							{
								hr = pTapeDesc->SetSignalType( VideoSignalType );
								if (AAFRESULT_SUCCESS == hr )
								{
									hr = pTapeDesc->SetTapeFormat( TapeFormat );
									if (AAFRESULT_SUCCESS == hr )
										hr = pTapeDesc->SetTapeLength( TapeLength );
								}
							}
						}
					}
				}
				pEssDesc->Release();
				pEssDesc = NULL;
			}
			pTapeDesc->Release();
			pTapeDesc = NULL;
		}
		for (test = 0; test < NumMobSlots; test++)
		{
			IAAFDataDefSP pDataDef;
			checkResult (pDictionary->LookupDataDef (*slotDDefs[test], &pDataDef));
			checkResult(pTapeMob->AddNilReference (test, TAPE_MOB_LENGTH_ARR[test], pDataDef, slotRates[test]));
		}
		checkResult(pTapeMob->QueryInterface(IID_IAAFMob, (void **) &pTempMob));
		checkResult(pTempMob->SetName(TAPE_MOB_NAME));
		checkResult(pTempMob->SetMobID(tapeMobID));
		//save the id for future (test) reference
//		TAPE_MOB_ID = tapeMobID;

		checkResult(pHeader->AddMob(pTempMob));
		pTempMob->Release();
		pTempMob = NULL;
		
		// Add some slots
		for (test = 0; test < NumMobSlots; test++)
		{
			// Create source mob to associate with our MasterMob.
			checkResult(defs.cdSourceMob()->
				CreateInstance(IID_IAAFSourceMob, 
				(IUnknown **)&pSrcMob));		
			
			ref.sourceID = tapeMobID;
			ref.sourceSlotID = test;
			ref.startTime = TAPE_MOB_OFFSET_ARR[test];
			IAAFDataDefSP pDDef;
			checkResult(pDictionary->LookupDataDef(*slotDDefs[test], &pDDef));
			checkResult(pSrcMob->AppendPhysSourceRef (slotRates[test],
				test,
				pDDef,
				ref,
				FILE_MOB_LENGTH_ARR[test]));
			
			// Create a concrete subclass of EssenceDescriptor
			checkResult(defs.cdAIFCDescriptor()->
				CreateInstance(IID_IAAFEssenceDescriptor, 
				(IUnknown **)&pDesc));	

			IAAFAIFCDescriptor*			pAIFCDesc = NULL;
			checkResult(pDesc->QueryInterface (IID_IAAFAIFCDescriptor, (void **)&pAIFCDesc));
			checkResult(pAIFCDesc->SetSummary (5, (unsigned char*)"TEST"));
			pAIFCDesc->Release();
			pAIFCDesc = NULL;

			checkResult(pSrcMob->SetEssenceDescriptor(pDesc));
			pDesc->Release();
			pDesc = NULL;
			
			// Append source MOB to header
			checkResult(pSrcMob->QueryInterface(IID_IAAFMob, (void **) &pTempMob));
			checkResult(pTempMob->SetMobID(TEST1_Source_MobIDs[test]));
			checkResult(pTempMob->SetName(L"source mob"));
			
			checkResult(pHeader->AddMob(pTempMob));
			pTempMob->Release();
			pTempMob = NULL;
			
			IAAFDataDefSP pDataDef;
			checkResult (pDictionary->LookupDataDef (*slotDDefs[test], &pDataDef));
			checkResult(pMasterMob->AddMasterSlot(pDataDef, test, pSrcMob, test+1, slotNames[test]));
			
			pSrcMob->Release();
			pSrcMob = NULL;
		}
		
		// Add the master mob to the file and cleanup
		checkResult(pHeader->AddMob(pMob));
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	
	// Cleanup and return
	if (pTempMob)
		pTempMob->Release();
	
	if (pEssDesc)
		pEssDesc->Release();
	
	if (pTapeDesc)
		pTapeDesc->Release();
	
	
	if (pDesc)
		pDesc->Release();
	
	if (pSrcMob)
		pSrcMob->Release();
	
	if (pTapeMob)
		pTapeMob->Release();
	
	if (pMasterMob)
		pMasterMob->Release();
	
	if (pMob)
		pMob->Release();
	
	if (pDictionary)
		pDictionary->Release();
	
	return hr;
}

static HRESULT CreateTestMobChain2(
	IAAFHeader* pHeader)
{
	IAAFSmartPointer<IAAFDictionary>  pDictionary;
	IAAFSmartPointer<IAAFMob>		pMob;
	IAAFSmartPointer<IAAFTimecode>   pTimecode;
	IAAFSmartPointer<IAAFSegment>	pTimecodeSegment;
	IAAFSmartPointer<IAAFPulldown>   pPulldown;
	IAAFSmartPointer<IAAFComponent>  pPulldownComponent;
	IAAFSmartPointer<IAAFSequence>   pSequence;
	IAAFSmartPointer<IAAFSegment>	pSequenceSegment;
	IAAFSmartPointer<IAAFTimelineMobSlot>	pSlot;
	IAAFSmartPointer<IAAFImportDescriptor>	pImportDescriptor;
	IAAFSmartPointer<IAAFSourceMob>  pSourceMob;
	IAAFSmartPointer<IAAFEssenceDescriptor>		   pDescriptor;

	HRESULT			hr = S_OK;
	
	
	try
	{
		checkResult(pHeader->GetDictionary(&pDictionary));
		
		CAAFBuiltinDefs defs (pDictionary);
		
		// Create Mob with Timline Mob Slot containing Pulldown object with
		// Timecode as its input segment, i.e.:
		//
		//	[ TimelineMobSlot ]
		//		[ Sequence ]
		//			[ Pulldown ]
		//				[ Timecode ]
		//

		// Create a Source Mob
		checkResult(defs.cdSourceMob()->
			CreateInstance(IID_IAAFMob, 
			(IUnknown **)&pMob));
		
		checkResult(pMob->SetMobID(TEST2_Source_MobID));
		
		const aafUInt32 slotIndex = 0;

		IAAFDataDefSP pDataDef;
		checkResult(pDictionary->LookupDataDef(kAAFDataDef_Timecode, &pDataDef));

		checkResult(defs.cdTimecode()->
			CreateInstance(IID_IAAFTimecode, 
			(IUnknown **)&pTimecode));
		const aafLength_t timecodeLength = 161;
		aafTimecode_t timecode = {108000, kAAFTcDrop, 30};
		checkResult(pTimecode->Initialize(timecodeLength, &timecode));

		checkResult(defs.cdPulldown()->
			CreateInstance(IID_IAAFPulldown, 
			(IUnknown **)&pPulldown));
		checkResult(pPulldown->QueryInterface(IID_IAAFComponent, (void**)&pPulldownComponent));
		checkResult(pPulldownComponent->SetLength(129));
		checkResult(pPulldownComponent->SetDataDef(pDataDef));
		checkResult(pPulldown->SetPulldownKind(kAAFTwoThreePD));
		checkResult(pPulldown->SetPulldownDirection(kAAFTapeToFilmSpeed));
		checkResult(pPulldown->SetPhaseFrame(0));
		checkResult(pTimecode->QueryInterface(IID_IAAFSegment, (void**)&pTimecodeSegment));
		checkResult(pPulldown->SetInputSegment(pTimecodeSegment));

		checkResult(defs.cdSequence()->
			CreateInstance(IID_IAAFSequence, 
			(IUnknown **)&pSequence));
		checkResult(pSequence->Initialize(pDataDef));
		checkResult(pSequence->AppendComponent(pPulldownComponent));
		checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void**)&pSequenceSegment));

		const aafRational_t slotEditRate = {24000, 1001};
		const aafSlotID_t slotId = 2;
		checkResult(pMob->AppendNewTimelineSlot(slotEditRate, pSequenceSegment, slotId, slotNames[slotIndex], 0, &pSlot));

		checkResult(defs.cdImportDescriptor()->
			CreateInstance(IID_IAAFImportDescriptor, 
			(IUnknown **)&pImportDescriptor));
		checkResult(pImportDescriptor->Initialize());
		checkResult(pImportDescriptor->QueryInterface(IID_IAAFEssenceDescriptor, (void**)&pDescriptor));

		checkResult(pMob->QueryInterface(IID_IAAFSourceMob, (void **) &pSourceMob));
		checkResult(pSourceMob->SetEssenceDescriptor(pDescriptor));
		
		// Add the master mob to the file and cleanup
		checkResult(pHeader->AddMob(pMob));
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	return hr;
}

static aafMobID_t nilMobID()
{
	static aafMobID_t mobID;
	memset(&mobID, 0, sizeof(mobID));
	return mobID;
}

HRESULT AppendSourceReference(
	IUnknown* pMobUnknown,
	aafRational_t  editRate,
    aafSlotID_t  slotID,
    IAAFDataDef* pDataDef,
    aafSourceRef_t  ref,
    aafLength_t  refLength)
{
	HRESULT			hr = S_OK;

	try
	{
		// Dictionary
		IAAFSmartPointer<IAAFObject> pObject;
		checkResult(pMobUnknown->QueryInterface(IID_IAAFObject, (void**)&pObject));
		IAAFSmartPointer<IAAFDictionary> pDict;
		checkResult(pObject->GetDictionary(&pDict));
		CAAFBuiltinDefs defs(pDict);

		IAAFSmartPointer<IAAFMob> pMob;
		checkResult(pMobUnknown->QueryInterface(IID_IAAFMob, (void**)&pMob));

		IAAFSmartPointer<IAAFSequence>	pSequence;
		IAAFSmartPointer<IAAFMobSlot> pSlot;
		if (pMob->LookupSlot(slotID, &pSlot) == S_OK)
		{
			// Slot exists, get the slot segment, it should be a sequence.
			IAAFSmartPointer<IAAFSegment> pSegment;
			checkResult(pSlot->GetSegment(&pSegment));
			checkResult(pSegment->QueryInterface(IID_IAAFSequence, (void**)&pSequence));
		}
		else
		{
			// Slot doesn't exist, create a new slot with an empty sequence.
			checkResult(defs.cdSequence()->CreateInstance(IID_IAAFSequence, (IUnknown **)&pSequence));
			checkResult(pSequence->Initialize(pDataDef));
			IAAFSmartPointer<IAAFSegment> pSegment;
			checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void**)&pSegment));
			IAAFSmartPointer<IAAFTimelineMobSlot> pTLSlot;
			checkResult(pMob->AppendNewTimelineSlot(editRate, pSegment, slotID, L"test456734", 0, &pTLSlot));
		}

		// Append a new source clip to the sequence
		IAAFSmartPointer<IAAFSourceClip> pSourceClip;
		checkResult(defs.cdSourceClip()->CreateInstance(IID_IAAFSourceClip, (IUnknown **)&pSourceClip));
		checkResult(pSourceClip->Initialize(pDataDef, refLength, ref));

		IAAFSmartPointer<IAAFComponent>	pSequenceComponent;
		checkResult(pSourceClip->QueryInterface(IID_IAAFComponent, (void**)&pSequenceComponent));
		checkResult(pSequence->AppendComponent(pSequenceComponent));
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	return hr;
}

static HRESULT CreateTestMobChain3(
	IAAFHeader* pHeader)
{
	IAAFSmartPointer<IAAFDictionary>  pDictionary;
	IAAFSmartPointer<IAAFMob>		pSMob;
	IAAFSmartPointer<IAAFSourceMob>		pSourceMob;
	IAAFSmartPointer<IAAFMob>		pFMob;
	IAAFSmartPointer<IAAFSourceMob>		pFileMob;
	IAAFSmartPointer<IAAFMob>		pMMob;
	IAAFSmartPointer<IAAFMasterMob>		pMasterMob;
	IAAFSmartPointer<IAAFSourceClip>   pSourceClip;
	IAAFSmartPointer<IAAFSegment>	pSegment;
	IAAFSmartPointer<IAAFSegment>	pSequenceSegment;
	IAAFSmartPointer<IAAFTimelineMobSlot>	pSlot;
	IAAFSmartPointer<IAAFImportDescriptor>	pImportDescriptor;
	IAAFSmartPointer<IAAFAIFCDescriptor>	pAIFCDescriptor;
	IAAFSmartPointer<IAAFEssenceDescriptor>		   pDescriptor;

	HRESULT			hr = S_OK;
	
	
	try
	{
		checkResult(pHeader->GetDictionary(&pDictionary));
		
		CAAFBuiltinDefs defs (pDictionary);
		
		// Create a Physical Source Mob
		checkResult(defs.cdSourceMob()->
			CreateInstance(IID_IAAFMob, 
			(IUnknown **)&pSMob));
		checkResult(pSMob->SetMobID(TEST3_Source_MobID));
		checkResult(pSMob->QueryInterface(IID_IAAFSourceMob, (void**)&pSourceMob));

		checkResult(defs.cdImportDescriptor()->
			CreateInstance(IID_IAAFImportDescriptor, 
			(IUnknown **)&pImportDescriptor));
		checkResult(pImportDescriptor->Initialize());
		checkResult(pImportDescriptor->QueryInterface(IID_IAAFEssenceDescriptor, (void**)&pDescriptor));
		checkResult(pSourceMob->SetEssenceDescriptor(pDescriptor));

		// Create a File Source Mob
		checkResult(defs.cdSourceMob()->
			CreateInstance(IID_IAAFMob, 
			(IUnknown **)&pFMob));
		checkResult(pFMob->SetMobID(TEST3_File_MobID));
		checkResult(pFMob->QueryInterface(IID_IAAFSourceMob, (void**)&pFileMob));

		checkResult(defs.cdAIFCDescriptor()->
			CreateInstance(IID_IAAFAIFCDescriptor, 
			(IUnknown **)&pAIFCDescriptor));	
		checkResult(pAIFCDescriptor->SetSummary(5, (unsigned char*)"TEST"));
		checkResult(pAIFCDescriptor->QueryInterface(IID_IAAFEssenceDescriptor, (void**)&pDescriptor));
		checkResult(pFileMob->SetEssenceDescriptor(pDescriptor));

		// Create a Master Mob
		checkResult(defs.cdMasterMob()->
			CreateInstance(IID_IAAFMob, 
			(IUnknown **)&pMMob));
		checkResult(pMMob->SetMobID(TEST3_Master_MobID));
		checkResult(pMMob->QueryInterface(IID_IAAFMasterMob, (void**)&pMasterMob));
		
		const aafRational_t editRate = {48000, 1};
		aafSlotID_t slotID = 0;

		// Slot 1: Physical Source Mob's SourceClip with unknown (-1) length, others' lengths are known.
		slotID++;

		{
			// Add Physical Source Mob Slot
			checkResult(pSourceMob->AddNilReference(slotID, AAF_UNKNOWN_LENGTH, defs.ddPicture(), editRate));
			// Add File Source Mob Slot
			const aafSourceRef_t physicalSourceRef = {TEST3_Source_MobID, slotID, 0};
			checkResult(pFileMob->NewPhysSourceRef(editRate, slotID, defs.ddSound(), physicalSourceRef, TEST3_KnownLength));
			// Add Master Source Mob Slot
			const aafSourceRef_t sourceRef = {TEST3_File_MobID, slotID, 0};
			checkResult(pMasterMob->NewPhysSourceRef(editRate, slotID, defs.ddPicture(), sourceRef, TEST3_KnownLength));
		}

		// Slot 2: File Source Mob's SourceClip with unknown (-1) length, others' lengths are known.
		slotID++;

		{
			// Add Physical Source Mob Slot
			checkResult(pSourceMob->AddNilReference(slotID, TEST3_KnownLength, defs.ddPicture(), editRate));
			// Add File Source Mob Slot
			const aafSourceRef_t physicalSourceRef = {TEST3_Source_MobID, slotID, 0};
			checkResult(pFileMob->NewPhysSourceRef(editRate, slotID, defs.ddSound(), physicalSourceRef, AAF_UNKNOWN_LENGTH));
			// Add Master Source Mob Slot
			const aafSourceRef_t sourceRef = {TEST3_File_MobID, slotID, 0};
			checkResult(pMasterMob->NewPhysSourceRef(editRate, slotID, defs.ddPicture(), sourceRef, TEST3_KnownLength));
		}

		// Slot 3: Master Source Mob's SourceClip with unknown (-1) length, others' lengths are known.
		slotID++;
		{
			// Add Physical Source Mob Slot
			checkResult(pSourceMob->AddNilReference(slotID, TEST3_KnownLength, defs.ddPicture(), editRate));
			// Add File Source Mob Slot
			const aafSourceRef_t physicalSourceRef = {TEST3_Source_MobID, slotID, 0};
			checkResult(pFileMob->NewPhysSourceRef(editRate, slotID, defs.ddSound(), physicalSourceRef, TEST3_KnownLength));
			// Add Master Source Mob Slot
			const aafSourceRef_t sourceRef = {TEST3_File_MobID, slotID, 0};
			checkResult(pMasterMob->NewPhysSourceRef(editRate, slotID, defs.ddPicture(), sourceRef, AAF_UNKNOWN_LENGTH));
		}

		// Slot 4: Master and File Source Mobs' SourceClip are with unknown (-1) length, others' lengths are known.
		slotID++;
		{
			// Add Physical Source Mob Slot
			checkResult(pSourceMob->AddNilReference(slotID, TEST3_KnownLength, defs.ddPicture(), editRate));
			// Add File Source Mob Slot
			const aafSourceRef_t physicalSourceRef = {TEST3_Source_MobID, slotID, 0};
			checkResult(pFileMob->NewPhysSourceRef(editRate, slotID, defs.ddSound(), physicalSourceRef, AAF_UNKNOWN_LENGTH));
			// Add Master Source Mob Slot
			const aafSourceRef_t sourceRef = {TEST3_File_MobID, slotID, 0};
			checkResult(pMasterMob->NewPhysSourceRef(editRate, slotID, defs.ddPicture(), sourceRef, AAF_UNKNOWN_LENGTH));
		}

		// Slot 5: All Mobs' SourceClip are with unknown (-1) length, others' lengths are known.
		slotID++;
		{
			// Add Physical Source Mob Slot
			checkResult(pSourceMob->AddNilReference(slotID, AAF_UNKNOWN_LENGTH, defs.ddPicture(), editRate));
			// Add File Source Mob Slot
			const aafSourceRef_t physicalSourceRef = {TEST3_Source_MobID, slotID, 0};
			checkResult(pFileMob->NewPhysSourceRef(editRate, slotID, defs.ddSound(), physicalSourceRef, AAF_UNKNOWN_LENGTH));
			// Add Master Source Mob Slot
			const aafSourceRef_t sourceRef = {TEST3_File_MobID, slotID, 0};
			checkResult(pMasterMob->NewPhysSourceRef(editRate, slotID, defs.ddPicture(), sourceRef, AAF_UNKNOWN_LENGTH));
		}

		// Slot 6: 
		slotID++;
		{
			// Add Physical Source Mob Slot
			checkResult(pSourceMob->AddNilReference(slotID, AAF_UNKNOWN_LENGTH, defs.ddPicture(), editRate));
			// Add File Source Mob Slot
			const aafSourceRef_t physicalSourceRef1 = {TEST3_Source_MobID, slotID, 0};
			checkResult(AppendSourceReference(pFileMob, editRate, slotID, defs.ddSound(), physicalSourceRef1, TEST3_KnownLength));
			const aafSourceRef_t physicalSourceRef2 = {TEST3_Source_MobID, slotID, TEST3_KnownLength};
			checkResult(AppendSourceReference(pFileMob, editRate, slotID, defs.ddSound(), physicalSourceRef2, TEST3_KnownLength));
			// Add Master Source Mob Slot
			const aafSourceRef_t sourceRef1 = {TEST3_File_MobID, slotID, 0};
			checkResult(AppendSourceReference(pMasterMob, editRate, slotID, defs.ddSound(), sourceRef1, TEST3_KnownLength));
			const aafSourceRef_t sourceRef2 = {TEST3_File_MobID, slotID, TEST3_KnownLength};
			checkResult(AppendSourceReference(pMasterMob, editRate, slotID, defs.ddSound(), sourceRef2, TEST3_KnownLength));
		}

		// Slot 7: 
		slotID++;
		{
			// Add Physical Source Mob Slot
			checkResult(pSourceMob->AddNilReference(slotID, TEST3_KnownLength * 2, defs.ddPicture(), editRate));
			// Add File Source Mob Slot
			const aafSourceRef_t physicalSourceRef1 = {TEST3_Source_MobID, slotID, 0};
			checkResult(AppendSourceReference(pFileMob, editRate, slotID, defs.ddSound(), physicalSourceRef1, TEST3_KnownLength));
			const aafSourceRef_t physicalSourceRef2 = {TEST3_Source_MobID, slotID, TEST3_KnownLength};
			checkResult(AppendSourceReference(pFileMob, editRate, slotID, defs.ddSound(), physicalSourceRef2, AAF_UNKNOWN_LENGTH));
			// Add Master Source Mob Slot
			const aafSourceRef_t sourceRef1 = {TEST3_File_MobID, slotID, 0};
			checkResult(AppendSourceReference(pMasterMob, editRate, slotID, defs.ddSound(), sourceRef1, TEST3_KnownLength));
			const aafSourceRef_t sourceRef2 = {TEST3_File_MobID, slotID, TEST3_KnownLength};
			checkResult(AppendSourceReference(pMasterMob, editRate, slotID, defs.ddSound(), sourceRef2, TEST3_KnownLength));
		}

		// Slot 8: 
		slotID++;
		{
			// Add Physical Source Mob Slot
			checkResult(pSourceMob->AddNilReference(slotID, TEST3_KnownLength * 2, defs.ddPicture(), editRate));
			// Add File Source Mob Slot
			const aafSourceRef_t physicalSourceRef1 = {TEST3_Source_MobID, slotID, 0};
			checkResult(AppendSourceReference(pFileMob, editRate, slotID, defs.ddSound(), physicalSourceRef1, TEST3_KnownLength));
			const aafSourceRef_t physicalSourceRef2 = {TEST3_Source_MobID, slotID, TEST3_KnownLength};
			checkResult(AppendSourceReference(pFileMob, editRate, slotID, defs.ddSound(), physicalSourceRef2, TEST3_KnownLength));
			// Add Master Source Mob Slot
			const aafSourceRef_t sourceRef1 = {TEST3_File_MobID, slotID, 0};
			checkResult(AppendSourceReference(pMasterMob, editRate, slotID, defs.ddSound(), sourceRef1, TEST3_KnownLength));
			const aafSourceRef_t sourceRef2 = {TEST3_File_MobID, slotID, TEST3_KnownLength};
			checkResult(AppendSourceReference(pMasterMob, editRate, slotID, defs.ddSound(), sourceRef2, AAF_UNKNOWN_LENGTH));
		}

		// Slot 9: 
		slotID++;
		{
			// Add Physical Source Mob Slot
			checkResult(pSourceMob->AddNilReference(slotID, TEST3_KnownLength * 2, defs.ddPicture(), editRate));
			// Add File Source Mob Slot
			const aafSourceRef_t physicalSourceRef1 = {TEST3_Source_MobID, slotID, 0};
			checkResult(AppendSourceReference(pFileMob, editRate, slotID, defs.ddSound(), physicalSourceRef1, TEST3_KnownLength));
			const aafSourceRef_t physicalSourceRef2 = {TEST3_Source_MobID, slotID, TEST3_KnownLength};
			checkResult(AppendSourceReference(pFileMob, editRate, slotID, defs.ddSound(), physicalSourceRef2, AAF_UNKNOWN_LENGTH));
			// Add Master Source Mob Slot
			const aafSourceRef_t sourceRef1 = {TEST3_File_MobID, slotID, 0};
			checkResult(AppendSourceReference(pMasterMob, editRate, slotID, defs.ddSound(), sourceRef1, TEST3_KnownLength));
			const aafSourceRef_t sourceRef2 = {TEST3_File_MobID, slotID, TEST3_KnownLength};
			checkResult(AppendSourceReference(pMasterMob, editRate, slotID, defs.ddSound(), sourceRef2, AAF_UNKNOWN_LENGTH));
		}

		// Slot 10: 
		slotID++;
		{
			// Add Physical Source Mob Slot
			checkResult(pSourceMob->AddNilReference(slotID, AAF_UNKNOWN_LENGTH, defs.ddPicture(), editRate));
			// Add File Source Mob Slot
			const aafSourceRef_t physicalSourceRef1 = {TEST3_Source_MobID, slotID, 0};
			checkResult(AppendSourceReference(pFileMob, editRate, slotID, defs.ddSound(), physicalSourceRef1, TEST3_KnownLength));
			const aafSourceRef_t physicalSourceRef2 = {TEST3_Source_MobID, slotID, TEST3_KnownLength};
			checkResult(AppendSourceReference(pFileMob, editRate, slotID, defs.ddSound(), physicalSourceRef2, AAF_UNKNOWN_LENGTH));
			// Add Master Source Mob Slot
			const aafSourceRef_t sourceRef1 = {TEST3_File_MobID, slotID, 0};
			checkResult(AppendSourceReference(pMasterMob, editRate, slotID, defs.ddSound(), sourceRef1, TEST3_KnownLength));
			const aafSourceRef_t sourceRef2 = {TEST3_File_MobID, slotID, TEST3_KnownLength};
			checkResult(AppendSourceReference(pMasterMob, editRate, slotID, defs.ddSound(), sourceRef2, AAF_UNKNOWN_LENGTH));
		}

		checkResult(pHeader->AddMob(pSMob));
		checkResult(pHeader->AddMob(pFMob));
		checkResult(pHeader->AddMob(pMMob));
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	return hr;
}

static HRESULT CreateAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_constref productID)
{
	IAAFFile*		pFile = NULL;
	bool bFileOpen = false;
	IAAFHeader *        pHeader = NULL;
	HRESULT			hr = S_OK;
	
	
	try
	{
		// Remove the previous test file if any.
		RemoveTestFile(pFileName);
		
		
		// Create the AAF file
		checkResult(CreateTestFile( pFileName, fileKind, rawStorageType, productID, &pFile ));
		bFileOpen = true;
		
		// Get the AAF file header.
		checkResult(pFile->GetHeader(&pHeader));

		checkResult(CreateTestMobChain1(pHeader));
		checkResult(CreateTestMobChain2(pHeader));
		checkResult(CreateTestMobChain3(pHeader));
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	
	if (pHeader)
		pHeader->Release();
	
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

static HRESULT ValidateTestMobChain1(IAAFHeader* pHeader)
{
	IEnumAAFMobs*	pMobIter = NULL;
	IAAFMob*		pMob = NULL;
	IAAFMasterMob*		pMasterMob = NULL;
	IEnumAAFMobSlots*	pSlotIter = NULL;
	IAAFMobSlot*		pSlot = NULL;
	aafNumSlots_t	numMobs;
	aafSearchCrit_t	criteria;
	IAAFSearchSource*  pSearchSource = NULL;
	IAAFFindSourceInfo*  pSourceInfo = NULL;
	IAAFFindSourceInfo2*  pSourceInfo2 = NULL;
	IAAFMob* si_mob = NULL;  //mob used by SourceInfo intf.

	HRESULT			hr = S_OK;
	
	try
	{
		// Validate that there is on one master mob in the test file.
		checkResult(pHeader->CountMobs(kAAFMasterMob, &numMobs));
		checkExpression(1 == numMobs || 2 == numMobs, AAFRESULT_TEST_FAILED);
		
		// Enumerate over Master MOBs
		criteria.searchTag = kAAFByMobKind;
		criteria.tags.mobKind = kAAFMasterMob;
		checkResult(pHeader->GetMobs(&criteria, &pMobIter));
		while (pMobIter && pMobIter->NextOne(&pMob) == AAFRESULT_SUCCESS)
		{
			aafWChar			name[500];
			aafNumSlots_t		numSlots = 0;
			aafMobID_t				mobID;
			
			// TODO: Test Master MOB specific methods here
			checkResult(pMob->QueryInterface(IID_IAAFMasterMob, (void **) &pMasterMob));
			
			checkResult(pMob->GetName(name, sizeof(name)));
			checkExpression(wcscmp(name, MobName) == 0, AAFRESULT_TEST_FAILED);
			
			checkResult(pMob->GetMobID(&mobID));
			checkExpression(0 == memcmp(&mobID, &TEST1_Master_MobID, sizeof(mobID)), AAFRESULT_TEST_FAILED);
			
			checkResult(pMob->CountSlots(&numSlots));
			checkExpression(NumMobSlots == numSlots, AAFRESULT_TEST_FAILED);
			
			//AAFRESULT STDMETHODCALLTYPE
			//   ImplAAFMasterMob::GetTapeNameBufLen (0,
			//										 aafInt32*  pLen)
			unsigned long	s = 0;
			
			// Enumerate over all MOB slots for this MOB
			checkResult(pMob->GetSlots(&pSlotIter));
			while (pSlotIter && pSlotIter->NextOne(&pSlot) == AAFRESULT_SUCCESS)
			{
				aafWChar			slotName[500];
				aafSlotID_t			slotID;
				//aafUInt32			bufSize = 0;
				
				// Validate the slot name
				checkResult(pSlot->GetName(slotName, sizeof(slotName)));
				checkExpression(wcscmp(slotName, slotNames[s]) == 0, AAFRESULT_TEST_FAILED);
				
				// Validate the slot id.
				checkResult(pSlot->GetSlotID(&slotID));
				checkExpression(slotID == s+1, AAFRESULT_TEST_FAILED);

				//Now, do a search source  ...............

				//Get a search source intf.
				checkResult( pMasterMob->QueryInterface(IID_IAAFSearchSource, (void**)&pSearchSource) );

				//From the searchsource inft, get a FindSourceINfo intf.
				checkResult ( pSearchSource->SearchSource(
					slotID,
					0,
					kAAFTapeMob,
					NULL, //don't care about Media Criteria
					NULL, //don't care about operation choice
					&pSourceInfo));

				//This is an important milestone! At this point, we were successful - about getting a pSourceInfo intf.
				//  so, release the search source intf.
				if (pSearchSource)
				{
					pSearchSource->Release();
					pSearchSource=NULL;
				}

				checkResult( pSourceInfo->QueryInterface(IID_IAAFFindSourceInfo2, (void**)&pSourceInfo2) );

				//NOw, simply test the methods on the (final) SourceInfo intf.
				aafRational_t si_editRate = {-1};
				aafLength_t  si_length = {-1};
				aafSourceRef_t  si_sourceRef = {{{0,0,0,0,0,0,0,0,0,0,0,0},0,0,0,0,{0,0,0,{0,0,0,0,0,0,0,0}}},0,0};
				aafMobID_t  si_MobID = {{0,0,0,0,0,0,0,0,0,0,0,0},0,0,0,0,
						{0,0,0,{0,0,0,0,0,0,0,0}}};
				
				aafBoolean_t si_HasChannelIDs = kAAFFalse;
				aafUInt32    si_ChannelID = 0;
				
				//Call the methods
				pSourceInfo->GetEditRate( &si_editRate);
				pSourceInfo->GetLength(&si_length);
				pSourceInfo->GetMob(&si_mob);
				pSourceInfo->GetSourceReference(&si_sourceRef);

				//Check the values returned by the methods
				//edit rate
				checkExpression(si_editRate.numerator == slotRates[s].numerator, AAFRESULT_TEST_FAILED);
				checkExpression(si_editRate.denominator == slotRates[s].denominator, AAFRESULT_TEST_FAILED);
				//Length
				checkExpression(si_length == FILE_MOB_LENGTH_ARR[s], AAFRESULT_TEST_FAILED);
				//Mob
				checkExpression(si_mob!=NULL, AAFRESULT_TEST_FAILED); 
				si_mob->GetMobID(&si_MobID);
				checkExpression(memcmp(&si_MobID, &tapeMobID, sizeof(aafMobID_t))==0,
										AAFRESULT_TEST_FAILED);
				//Source Reference
				checkExpression(si_sourceRef.sourceSlotID == s,					AAFRESULT_TEST_FAILED);
				checkExpression(si_sourceRef.startTime == TAPE_MOB_OFFSET_ARR[s], AAFRESULT_TEST_FAILED);

				pSourceInfo2->GetMultichannelSourceReference(&si_sourceRef, &si_HasChannelIDs, &si_ChannelID);

				checkExpression(si_HasChannelIDs == kAAFFalse, AAFRESULT_TEST_FAILED);
				checkExpression(si_ChannelID == 0, AAFRESULT_TEST_FAILED);

				//Done with tests .. release the FindSourceInfo intf .. 
				if (pSourceInfo)
				{
					pSourceInfo->Release();
					pSourceInfo=NULL;
				}
				if (pSourceInfo2)
				{
					pSourceInfo2->Release();
					pSourceInfo2=NULL;
				}

				//Also don't forget to release the si_mob intf.
				if (si_mob)
				{
					si_mob->Release();
					si_mob=NULL;
				}
				
				pSlot->Release();
				pSlot = NULL;
				s++;
			}
			
			pSlotIter->Release();
			pSlotIter = NULL;
			pMob->Release();
			pMob = NULL;
			pMasterMob->Release();
			pMasterMob = NULL;
		}
		
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	
	// Cleanup and return

	if (pSearchSource)
		pSearchSource->Release();
	
	if (pSourceInfo)
		pSourceInfo->Release();
	
	if (si_mob)
		si_mob->Release();
				
	
	if (pSlot)
		pSlot->Release();
	
	if (pMasterMob)
		pMasterMob->Release();
	
	if (pMob)
		pMob->Release();
	
	if (pMobIter)
		pMobIter->Release();
	
	return hr;
}

static HRESULT ValidateTestMobChain2(IAAFHeader* pHeader)
{
	IAAFSmartPointer<IEnumAAFMobs>	pMobIter;
	IAAFSmartPointer<IAAFMob>		pMob;
	IAAFSmartPointer<IAAFMasterMob>		pMasterMob;
	IAAFSmartPointer<IEnumAAFMobSlots>	pSlotIter;
	IAAFSmartPointer<IAAFMobSlot>		pSlot;
	IAAFSmartPointer<IAAFSearchSource>  pSearchSource;
	IAAFSmartPointer<IAAFFindSourceInfo>  pSourceInfo;
	IAAFSmartPointer<IAAFFindSourceInfo2>  pSourceInfo2;
	IAAFSmartPointer<IAAFMob> si_mob;  //mob used by SourceInfo intf.

	HRESULT			hr = S_OK;
	
	try
	{
		// Do not fail the test if the mob not found. It most likely means
		// that the file being validated comes from an earlier versin of
		// the test. Even if there's an issue with getting a mob it is not
		// the purpose of this test to detect such issues.
		if (AAFRESULT_SUCCEEDED(pHeader->LookupMob(TEST2_Source_MobID, &pMob)))
		{
			checkResult(pMob->GetSlots(&pSlotIter));
			checkResult(pSlotIter->NextOne(&pSlot));
			aafSlotID_t slotID = 0;
			checkResult(pSlot->GetSlotID(&slotID));

			checkResult( pMob->QueryInterface(IID_IAAFSearchSource, (void**)&pSearchSource) );

			checkExpression(
				AAFRESULT_TRAVERSAL_NOT_POSS ==
				pSearchSource->SearchSource(
					slotID,
					0,
					kAAFFileMob,
					NULL, //don't care about Media Criteria
					NULL, //don't care about operation choice
					&pSourceInfo),
				AAFRESULT_TEST_FAILED);
		}
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	return hr;
}

static HRESULT ValidateTestMobChain3(IAAFHeader* pHeader)
{
	IAAFSmartPointer<IEnumAAFMobs>	pMobIter;
	IAAFSmartPointer<IAAFMob>		pMob;
	IAAFSmartPointer<IAAFMasterMob>		pMasterMob;
	IAAFSmartPointer<IEnumAAFMobSlots>	pSlotIter;
	IAAFSmartPointer<IAAFMobSlot>		pSlot;
	IAAFSmartPointer<IAAFSearchSource>  pSearchSource;
	IAAFSmartPointer<IAAFFindSourceInfo>  pSourceInfo;
	struct
	{
		aafPosition_t offset;
		AAFRESULT status;
		aafPosition_t start;
		aafLength_t length;
	} expectedResults[][2] = {
		// Slot 1
		{
			{0,						S_OK,							0,						TEST3_KnownLength},
			{TEST3_KnownLength+100,	AAFRESULT_TRAVERSAL_NOT_POSS,	0,						TEST3_KnownLength},
		},
		// Slot 2
		{
			{0,						S_OK,							0,						TEST3_KnownLength},
			{TEST3_KnownLength+100,	AAFRESULT_TRAVERSAL_NOT_POSS,	0,						TEST3_KnownLength},
		},
		// Slot 3
		{
			{0,						S_OK,							0,						TEST3_KnownLength},
			{TEST3_KnownLength+100,	AAFRESULT_TRAVERSAL_NOT_POSS,	0,						TEST3_KnownLength},
		},
		// Slot 4
		{
			{0,						S_OK,							0,						TEST3_KnownLength},
			{TEST3_KnownLength+100,	AAFRESULT_TRAVERSAL_NOT_POSS,	0,						0},
		},
		// Slot 5
		{
			{0,						S_OK,							0,						AAF_UNKNOWN_LENGTH},
			{TEST3_KnownLength+100,	S_OK,							TEST3_KnownLength+100,	AAF_UNKNOWN_LENGTH},
		},
		// Slot 6
		{
			{0,						S_OK,							0,						TEST3_KnownLength},
			{TEST3_KnownLength+100,	S_OK,							TEST3_KnownLength+100,	TEST3_KnownLength},
		},
		// Slot 7
		{
			{0,						S_OK,							0,						TEST3_KnownLength},
			{TEST3_KnownLength+100,	S_OK,							TEST3_KnownLength+100,	TEST3_KnownLength},
		},
		// Slot 8
		{
			{0,						S_OK,							0,						TEST3_KnownLength},
			{TEST3_KnownLength+100,	S_OK,							TEST3_KnownLength+100,	TEST3_KnownLength},
		},
		// Slot 9
		{
			{0,						S_OK,							0,						TEST3_KnownLength},
			{TEST3_KnownLength+100,	S_OK,							TEST3_KnownLength+100,	TEST3_KnownLength * 2},
		},
		// Slot 10
		{
			{0,						S_OK,							0,						TEST3_KnownLength},
			{TEST3_KnownLength+100,	S_OK,							TEST3_KnownLength+100,	AAF_UNKNOWN_LENGTH},
		},
	};

	HRESULT			hr = S_OK;
	
	try
	{
		// Do not fail the test if the mob not found. It most likely means
		// that the file being validated comes from an earlier versin of
		// the test. Even if there's an issue with getting a mob it is not
		// the purpose of this test to detect such issues.
		if (AAFRESULT_SUCCEEDED(pHeader->LookupMob(TEST3_Master_MobID, &pMob)))
		{
			const size_t expectedSlotCount = sizeof(expectedResults) / sizeof(expectedResults[0]);

			checkResult( pMob->QueryInterface(IID_IAAFSearchSource, (void**)&pSearchSource) );
			checkResult(pMob->GetSlots(&pSlotIter));
			while (AAFRESULT_SUCCEEDED(pSlotIter->NextOne(&pSlot)))
			{
				aafSlotID_t slotID = 0;
				checkResult(pSlot->GetSlotID(&slotID));
				if (slotID-1 > expectedSlotCount)
				{
					// Slot from the future
					continue;
				}

				const size_t count = sizeof(expectedResults[0]) / sizeof(expectedResults[0][0]);
				for (size_t i=0; i<count; i++)
				{
					const aafPosition_t offset = expectedResults[slotID-1][i].offset;
					const HRESULT expectedStatus = expectedResults[slotID-1][i].status;
					const aafLength_t expectedStart = expectedResults[slotID-1][i].start;
					const aafLength_t expectedLength = expectedResults[slotID-1][i].length;
					HRESULT status = pSearchSource->SearchSource(
						slotID,
						offset,
						kAAFPhysicalMob,
						NULL, //don't care about Media Criteria
						NULL, //don't care about operation choice
						&pSourceInfo);
					checkExpression(status == expectedStatus, AAFRESULT_TEST_FAILED);
					if (expectedStatus == S_OK)
					{
						aafSourceRef_t sourceRef;
						checkResult(pSourceInfo->GetSourceReference(&sourceRef));
						checkExpression(sourceRef.sourceID == TEST3_Source_MobID, AAFRESULT_TEST_FAILED);
						checkExpression(sourceRef.sourceSlotID == slotID, AAFRESULT_TEST_FAILED);
						checkExpression(sourceRef.startTime == expectedStart, AAFRESULT_TEST_FAILED);
						aafLength_t length = -233;
						checkResult(pSourceInfo->GetLength(&length));
						checkExpression(length == expectedLength, AAFRESULT_TEST_FAILED);
					}
				}
			}
		}
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	return hr;
}

static HRESULT ReadAAFFile(aafWChar* pFileName)
{
	IAAFFile*		pFile = NULL;
	bool bFileOpen = false;
	IAAFHeader*		pHeader = NULL;

	HRESULT			hr = S_OK;
	
	try
	{
		// Open the AAF file
		checkResult(AAFFileOpenExistingRead(pFileName, 0, &pFile));
		bFileOpen = true;

		// Get the AAF file header.
		checkResult(pFile->GetHeader(&pHeader));

        //checkResult(ValidateTestMobChain1(pHeader));
        checkResult(ValidateTestMobChain2(pHeader));
        checkResult(ValidateTestMobChain3(pHeader));
	}
	catch (HRESULT& rResult)
	{
		hr = rResult;
	}
	
	
	// Cleanup and return

	if (pHeader)
		pHeader->Release();
	
	if (pFile)
	{  // Close file
		if (bFileOpen)
			pFile->Close();
		pFile->Release();
	}
	
	return hr;
}


extern "C" HRESULT CAAFFindSourceInfo_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);
extern "C" HRESULT CAAFFindSourceInfo_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID)
{
	HRESULT hr = AAFRESULT_NOT_IMPLEMENTED;
	const size_t fileNameBufLen = 128;
	aafWChar pFileName[ fileNameBufLen ] = L"";
	GenerateTestFileName( productID.productName, fileKind, fileNameBufLen, pFileName );
	
	try
	{
		if(mode == kAAFUnitTestReadWrite)
			hr = CreateAAFFile(pFileName, fileKind, rawStorageType, productID);
		else
			hr = AAFRESULT_SUCCESS;
		if (SUCCEEDED(hr))
			hr = ReadAAFFile(pFileName);
	}
	catch (...)
	{
	  cerr << "CAAFFindSourceInfo_test..."
		   << "Caught general C++ exception!" << endl; 
	  hr = AAFRESULT_TEST_FAILED;
	}
	
	if (SUCCEEDED(hr))
	{
		hr = AAFRESULT_SUCCESS;
	}
	
	return hr;
}




