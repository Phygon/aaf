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

#include <stdio.h>
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <string.h>

#include "AAFStoredObjectIDs.h"
#include "AAFResult.h"
#include "ModuleTest.h"
#include "AAFDataDefs.h"
#include "AAFDefUIDs.h"

#include "CAAFBuiltinDefs.h"

#include "AAFSmartPointer.h"
									
typedef IAAFSmartPointer<IAAFDataDef>		IAAFDataDefSP;
typedef IAAFSmartPointer<IAAFFiller>		IAAFFillerSP;
typedef IAAFSmartPointer<IAAFMob>			IAAFMobSP;
typedef IAAFSmartPointer<IAAFMobSlot>		IAAFMobSlotSP;
typedef IAAFSmartPointer<IAAFMobSlot>		IAAFMobSlotSP;
typedef IAAFSmartPointer<IAAFObject>		IAAFObjectSP;
typedef IAAFSmartPointer<IAAFPulldown>		IAAFPulldownSP;
typedef IAAFSmartPointer<IAAFSegment>		IAAFSegmentSP;
typedef IAAFSmartPointer<IAAFSequence>		IAAFSequenceSP;
typedef IAAFSmartPointer<IAAFSourceClip>	IAAFSourceClipSP;
typedef IAAFSmartPointer<IAAFTimecode>		IAAFTimecodeSP;
typedef IAAFSmartPointer<IAAFEdgecode>		IAAFEdgecodeSP;
typedef IAAFSmartPointer<IAAFPulldown>		IAAFPulldownSP;
typedef IAAFSmartPointer<IAAFComponent>		IAAFComponentSP;

static aafUInt8 TEST_AIFC_Summary[] = "TEST";

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

struct SourceMobInfo
{
	const aafMobID_t mobID;
	const int numberOfSlots;

	struct
	{
		aafSlotID_t slotID;
		aafRational_t editRate;
		aafLength_t	length;
		aafTimecode_t timecode;

	} timecodeSlot;

	struct
	{
		aafSlotID_t slotID;
		aafRational_t editRate;
		aafLength_t	length;
		aafEdgecode_t edgecode;

	} edgecodeSlot;

	struct
	{
		aafSlotID_t slotID;
		aafRational_t editRate;
		aafLength_t	length;
		aafUID_t essenceKind;
		aafSourceRef_t sourceRef;
        aafPulldownKind_t  pulldownKind;
        aafPhaseFrame_t  pulldownPhaseFrame;
        aafPulldownDir_t  pulldownDirection;

	} slotWithPulldown;

} mobInfo = 
{
	// mobID
	{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
		0x13, 0x00, 0x00, 0x00,
		{0xb6cb63f0, 0x0404, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}},
	 
	2, // numberOfSlots

	{	// timecodeSlot
		35,					// slotID		
		{30000, 1001},		// editRate
		1L*60L*60L*30L,		// length
		{					// timecode
			108000,				// startFrame
			kAAFTcNonDrop,		// drop
			30,					// fps
		}
	},
	{	// edgecodeSlot
		33,					// slotID
		{1, 1},				// editRate
		44,					// length
		{					// edgecodeSlot
			34,					// startFrame
			kAAFFt35MM,			// filmKind
			kAAFEtEdgenum4,		// codeFormat			
			"AAA"				// header
		}
	},
	{	// slotWithPulldown
		31, // slotID
		{30000, 1001},		// editRate
		34875,				// length
		kAAFDataDef_Sound,	// essenceKind;
		{					// sourceRef
			{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
			 0x13, 0x00, 0x00, 0x00,
			 {0xd2f522dc, 0x871c, 0x4835, {0x9e, 0x6, 0xa2, 0x6a, 0x8a, 0xfb, 0x3a, 0x45}}},
			17,
			674
		},
        kAAFOneToOneNTSC,	// pulldownKind;
        4,					// pulldownPhaseFrame;
        kAAFTapeToFilmSpeed,// pulldownDirection;
	},
};



static void CheckComponentLength(IUnknown* pUnknown, const aafLength_t expectedLength)
{
	IAAFComponentSP pComponent;
	checkResult(pUnknown->QueryInterface(IID_IAAFComponent, (void**)&pComponent));
	aafLength_t length = 0;
	checkResult(pComponent->GetLength(&length));
	checkExpression(expectedLength == length, AAFRESULT_TEST_FAILED);
}



static void CheckTimecode(
	IUnknown* pUnknown,
	const aafLength_t expectedLength,
    const aafTimecode_t& expectedTimecode)
{
	IAAFTimecodeSP pTimecode;
	IAAFSequenceSP pSequence;
	if (AAFRESULT_SUCCEEDED(pUnknown->QueryInterface(IID_IAAFSequence, (void**)&pSequence)))
	{
		IAAFComponentSP pComponent;
		checkResult(pSequence->GetComponentAt(0, &pComponent));
		checkResult(pComponent->QueryInterface(IID_IAAFTimecode, (void**)&pTimecode));
	}
	else
	{
		checkResult(pUnknown->QueryInterface(IID_IAAFTimecode, (void**)&pTimecode));
	}

	CheckComponentLength(pTimecode, expectedLength);

	aafTimecode_t  timecode = {0, 0, 0};
	checkResult(pTimecode->GetTimecode(&timecode));
	checkExpression(expectedTimecode == timecode, AAFRESULT_TEST_FAILED);
}



static void CheckEdgecode(
	IUnknown* pUnknown,
	const aafLength_t expectedLength,
    const aafEdgecode_t& expectedEdgecode)
{
	IAAFEdgecodeSP pEdgecode;
	IAAFSequenceSP pSequence;
	if (AAFRESULT_SUCCEEDED(pUnknown->QueryInterface(IID_IAAFSequence, (void**)&pSequence)))
	{
		IAAFComponentSP pComponent;
		checkResult(pSequence->GetComponentAt(0, &pComponent));
		checkResult(pComponent->QueryInterface(IID_IAAFEdgecode, (void**)&pEdgecode));
	}
	else
	{
		checkResult(pUnknown->QueryInterface(IID_IAAFEdgecode, (void**)&pEdgecode));
	}

	CheckComponentLength(pEdgecode, expectedLength);

	aafEdgecode_t  edgecode = {0, 0, 0, {0}};
	checkResult(pEdgecode->GetEdgecode(&edgecode));
	checkExpression(expectedEdgecode == edgecode, AAFRESULT_TEST_FAILED);
}



static void CheckPulldown(
	IUnknown* pUnknown,
	const aafLength_t expectedLength,
	const aafSourceRef_t& expectedSourceRef,
    const aafPulldownKind_t expectedPulldownKind,
    const aafPhaseFrame_t expectedPulldownPhaseFrame,
    const aafPulldownDir_t expectedPulldownDirection)
{
	IAAFPulldownSP pPulldown;
	checkResult(pUnknown->QueryInterface(IID_IAAFPulldown, (void**)&pPulldown));

	CheckComponentLength(pUnknown, expectedLength);

    aafPulldownKind_t  pulldownKind;
	checkResult(pPulldown->GetPulldownKind(&pulldownKind));
	checkExpression(expectedPulldownKind == pulldownKind, AAFRESULT_TEST_FAILED);

    aafPhaseFrame_t  pulldownPhaseFrame;
	checkResult(pPulldown->GetPhaseFrame(&pulldownPhaseFrame));
	checkExpression(expectedPulldownPhaseFrame == pulldownPhaseFrame, AAFRESULT_TEST_FAILED);

    aafPulldownDir_t  pulldownDirection;
	checkResult(pPulldown->GetPulldownDirection(&pulldownDirection));
	checkExpression(expectedPulldownDirection == pulldownDirection, AAFRESULT_TEST_FAILED);

	IAAFSegmentSP pInputSegment;
	checkResult(pPulldown->GetInputSegment(&pInputSegment));

	IAAFSourceClipSP pSourceClip;
	checkResult(pInputSegment->QueryInterface(IID_IAAFSourceClip, (void**)&pSourceClip));
	CheckComponentLength(pSourceClip, expectedLength);
	aafSourceRef_t sourceRef = {{0}, 0, 0};
	checkResult(pSourceClip->GetSourceReference(&sourceRef));
	checkExpression(expectedSourceRef == sourceRef, AAFRESULT_TEST_FAILED);
}



// Create a sequence with an optional zero length component
// followed by a non-zero length SourceClip.
static AAFRESULT CreateSequenceWithSourceClip(
	CAAFBuiltinDefs& defs,
	IAAFDataDef* pEssenceKind,
	const aafLength_t length,
	const aafSourceRef_t& sourceRef,
	const bool startWithZeroFiller,
	IAAFSegment** pSegment)
{
	AAFRESULT hr = AAFRESULT_SUCCESS;

	try
	{
		IAAFSequenceSP pSequence;
 		checkResult(defs.cdSequence()->
					CreateInstance(IID_IAAFSequence, 
									(IUnknown **)&pSequence));		
		checkResult(pSequence->Initialize(pEssenceKind));

		if (startWithZeroFiller)
		{
			// Append zero length Filler.
			IAAFFillerSP pFiller;
 			checkResult(defs.cdFiller()->
						CreateInstance(IID_IAAFFiller, 
										(IUnknown **)&pFiller));		
			checkResult(pFiller->Initialize(pEssenceKind, 0));
			{
				IAAFComponentSP pComponent;
				checkResult(pFiller->QueryInterface(IID_IAAFComponent, (void**)&pComponent));
				checkResult(pSequence->AppendComponent(pComponent));
			}
		}

		// Append SourceClip.
		IAAFSourceClipSP pSourceClip;
 		checkResult(defs.cdSourceClip()->
					CreateInstance(IID_IAAFSourceClip, 
									(IUnknown **)&pSourceClip));
		checkResult(pSourceClip->Initialize(pEssenceKind, length, sourceRef));
		{
			IAAFComponentSP pComponent;
			checkResult(pSourceClip->QueryInterface(IID_IAAFComponent, (void**)&pComponent));
			checkResult(pSequence->AppendComponent(pComponent));
		}

		checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void**)pSegment));
	}
	catch (AAFRESULT e)
	{
		hr = e;
	}

	return hr;
}



AAFRESULT RemoveSlot(IUnknown* pUnknown, aafSlotID_t slotID)
{
	AAFRESULT hr = AAFRESULT_SUCCESS;

	try
	{
		IAAFMobSP pMob;
		checkResult(pUnknown->QueryInterface(IID_IAAFMob, (void**)&pMob));

		aafNumSlots_t slotCount = 0;
		checkResult(pMob->CountSlots(&slotCount));
		for (aafUInt32 i=0; i<slotCount; i++)
		{
			IAAFMobSlotSP pSlot;
			checkResult(pMob->GetSlotAt(i, &pSlot));
			aafSlotID_t thisSlotID = 0;
			checkResult(pSlot->GetSlotID(&thisSlotID));
			if (thisSlotID == slotID)
			{
				checkResult(pMob->RemoveSlotAt(i));
				break;
			}
		}
	}
	catch (AAFRESULT e)
	{
		hr = e;
	}

	return hr;
}



// Test IAAFSourceMob::AppendTimecodeSlot() API.
//
// The routine tests supported uses of AddPulldownRef() and correctness of
// data it creates but is not meant to be used to validate persistence of
// data create by AddPulldownRef().
//
static void TestAppendTimecodeSlot(IAAFSourceMob* pSourceMob)
{
	IAAFObjectSP pObject;
	checkResult(pSourceMob->QueryInterface(IID_IAAFObject, (void**)&pObject));
	IAAFDictionarySP pDictionary;
	checkResult(pObject->GetDictionary(&pDictionary));
	CAAFBuiltinDefs defs(pDictionary);

	IAAFMobSP pMob;
	checkResult(pSourceMob->QueryInterface(IID_IAAFMob, (void**)&pMob));

	const aafRational_t editRate = {25, 1};
	const aafSlotID_t slotID = 351;
	aafTimecode_t timecode = {108000, kAAFTcNonDrop, 30};

	// Ensure slot not present
	IAAFMobSlotSP pSlot;
	checkExpression(pMob->LookupSlot(slotID, &pSlot) == AAFRESULT_SLOT_NOT_FOUND, AAFRESULT_TEST_FAILED);

	// Add new slot 
	checkResult(pSourceMob->AppendTimecodeSlot(
		editRate,
		slotID,
		timecode,
		AAF_UNKNOWN_LENGTH));

	// Check the new timecode slot
	checkResult(pMob->LookupSlot(slotID, &pSlot));

	// Check the Timecode with unknown length
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckTimecode(pSegment, AAF_UNKNOWN_LENGTH, timecode);
	}

	// Modify existing timecode slot with unknown length
	timecode.startFrame += 1;
	checkResult(pSourceMob->AppendTimecodeSlot(
		editRate,
		slotID,
		timecode,
		AAF_UNKNOWN_LENGTH));

	// Check the Timecode
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckTimecode(pSegment, AAF_UNKNOWN_LENGTH, timecode);
	}

	// Change existing timecode slot's length from unknown (-1).
	const aafLength_t knownLength = 345934;
	checkResult(pSourceMob->AppendTimecodeSlot(
		editRate,
		slotID,
		timecode,
		knownLength));

	// Check the Timecode
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckTimecode(pSegment, knownLength, timecode);
	}

	// Change existing timecode slot's length back to unknown (-1).
	checkResult(pSourceMob->AppendTimecodeSlot(
		editRate,
		slotID,
		timecode,
		AAF_UNKNOWN_LENGTH));

	// Check the Timecode
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckTimecode(pSegment, AAF_UNKNOWN_LENGTH, timecode);
	}

	// Remove the slot added by this routine.
	checkResult(RemoveSlot(pMob, slotID));
}


// Test IAAFSourceMob::AppendEdgecodeSlot() API.
//
// The routine tests supported uses of AddPulldownRef() and correctness of
// data it creates but is not meant to be used to validate persistence of
// data create by AddPulldownRef().
//
static void TestAppendEdgecodeSlot(IAAFSourceMob* pSourceMob)
{
	IAAFObjectSP pObject;
	checkResult(pSourceMob->QueryInterface(IID_IAAFObject, (void**)&pObject));
	IAAFDictionarySP pDictionary;
	checkResult(pObject->GetDictionary(&pDictionary));
	CAAFBuiltinDefs defs(pDictionary);

	IAAFMobSP pMob;
	checkResult(pSourceMob->QueryInterface(IID_IAAFMob, (void**)&pMob));

	const aafRational_t editRate = {25, 1};
	const aafSlotID_t slotID = 348;
	aafEdgecode_t edgecode =
	{
		0,					// startFrame
		kAAFFt35MM,			// filmKind
		kAAFEtEdgenum4,		// codeFormat			
		"AAA"				// header
	};

	// Ensure slot not present
	IAAFMobSlotSP pSlot;
	checkExpression(pMob->LookupSlot(slotID, &pSlot) == AAFRESULT_SLOT_NOT_FOUND, AAFRESULT_TEST_FAILED);

	// Add new slot 
	checkResult(pSourceMob->AppendEdgecodeSlot(
		editRate,
		slotID,
		edgecode.startFrame,
		AAF_UNKNOWN_LENGTH,
		edgecode.filmKind,
		edgecode.codeFormat,
		edgecode.header));

	// Check the new edgecode slot
	checkResult(pMob->LookupSlot(slotID, &pSlot));

	// Check the Edgecode with unknown length
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckEdgecode(pSegment, AAF_UNKNOWN_LENGTH, edgecode);
	}

	// Modify existing edgecode slot with unknown length
	edgecode.startFrame += 1;
	checkResult(pSourceMob->AppendEdgecodeSlot(
		editRate,
		slotID,
		edgecode.startFrame,
		AAF_UNKNOWN_LENGTH,
		edgecode.filmKind,
		edgecode.codeFormat,
		edgecode.header));

	// Check the Edgecode
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckEdgecode(pSegment, AAF_UNKNOWN_LENGTH, edgecode);
	}

	// Change existing edgecode slot's length from unknown (-1).
	const aafLength_t knownLength = 450934;
	checkResult(pSourceMob->AppendEdgecodeSlot(
		editRate,
		slotID,
		edgecode.startFrame,
		knownLength,
		edgecode.filmKind,
		edgecode.codeFormat,
		edgecode.header));

	// Check the Edgecode
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckEdgecode(pSegment, knownLength, edgecode);
	}

	// Change existing edgecode slot's length back to unknown (-1).
	checkResult(pSourceMob->AppendEdgecodeSlot(
		editRate,
		slotID,
		edgecode.startFrame,
		AAF_UNKNOWN_LENGTH,
		edgecode.filmKind,
		edgecode.codeFormat,
		edgecode.header));

	// Check the Edgecode
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckEdgecode(pSegment, AAF_UNKNOWN_LENGTH, edgecode);
	}

	// Remove the slot added by this routine.
	checkResult(RemoveSlot(pMob, slotID));
}


// Test IAAFSourceMob::AddPulldownRef() API.
//
// The routine tests supported uses of AddPulldownRef() and correctness of
// data it creates but is not meant to be used to validate persistence of
// data create by AddPulldownRef().
//
static void TestAddPulldownRef(IAAFSourceMob* pSourceMob)
{
	IAAFObjectSP pObject;
	checkResult(pSourceMob->QueryInterface(IID_IAAFObject, (void**)&pObject));
	IAAFDictionarySP pDictionary;
	checkResult(pObject->GetDictionary(&pDictionary));
	CAAFBuiltinDefs defs(pDictionary);

	IAAFMobSP pMob;
	checkResult(pSourceMob->QueryInterface(IID_IAAFMob, (void**)&pMob));

	IAAFDataDef* pEssenceKind = defs.ddkAAFSound();
	const aafRational_t editRate = {25, 1};
	const aafSlotID_t slotID = 721;
	const aafLength_t pulldownLength = 164;
    const aafPulldownKind_t  pulldownKind = kAAFOneToOneNTSC;
    const aafPhaseFrame_t  pulldownPhaseFrame = 4;
    const aafPulldownDir_t  pulldownDirection = kAAFTapeToFilmSpeed;

	const aafSourceRef_t pulldownSourceRef_1 =
	{
		{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
		 0x13, 0x00, 0x00, 0x00,
		 {0x9ecbe671, 0xa584, 0x46cd, {0x94, 0xa6, 0xe9, 0x54, 0xa6, 0x90, 0x54, 0xd8}}},
		17,
		342
	};
	const aafSourceRef_t pulldownSourceRef_2 =
	{
		{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
		 0x13, 0x00, 0x00, 0x00,
		 {0xb01d0cca, 0x1659, 0x4b9b, {0xb3, 0x73, 0x14, 0x3b, 0x3, 0xed, 0xdf, 0xad}}},
		6757,
		573
	};

	const aafSourceRef_t sourceClipRef =
	{
		{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
		 0x13, 0x00, 0x00, 0x00,
		 {0xb7649a5f, 0x2637, 0x43f8, {0xb0, 0x95, 0x1, 0x66, 0xf5, 0x21, 0xb2, 0xc4}}},
		677,
		426
	};

	// kAAFVideoTapNTSC is not allowed
	checkExpression(pSourceMob->AddPulldownRef(
						kAAFAppend, // This gets ignored by the implementation.
						editRate,
						slotID,
						pEssenceKind,
						pulldownSourceRef_1,
						pulldownLength,
						kAAFVideoTapNTSC,
						pulldownPhaseFrame,
						pulldownDirection) == AAFRESULT_PULLDOWN_KIND,
					AAFRESULT_TEST_FAILED);

	// Ensure slot not present
	IAAFMobSlotSP pSlot;
	checkExpression(pMob->LookupSlot(slotID, &pSlot) == AAFRESULT_SLOT_NOT_FOUND, AAFRESULT_TEST_FAILED);


	//
	// 1. Create new slot with Pulldown.
	//

	// Add timeline slot with Pulldown.
	checkResult(pSourceMob->AddPulldownRef(
		kAAFAppend, // This gets ignored by the implementation.
		editRate,
		slotID,
		pEssenceKind,
		pulldownSourceRef_2,
		pulldownLength,
		pulldownKind,
		pulldownPhaseFrame,
		pulldownDirection));

	// Check the new slot with Pulldown
	checkResult(pMob->LookupSlot(slotID, &pSlot));

	// Check the Pulldown
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckPulldown(
			pSegment,
			pulldownLength,
			pulldownSourceRef_2,
			pulldownKind,
			pulldownPhaseFrame,
			pulldownDirection);
	}

	// Cannot add Pulldown over Segment that is not a SourceClip
	// (at this point we have a Pulldown instance as the Segment).
	checkExpression(pSourceMob->AddPulldownRef(
						kAAFAppend, // This gets ignored by the implementation.
						editRate,
						slotID,
						pEssenceKind,
						pulldownSourceRef_1,
						pulldownLength,
						pulldownKind,
						pulldownPhaseFrame,
						pulldownDirection) == AAFRESULT_NOT_SOURCE_CLIP,
					AAFRESULT_TEST_FAILED);


	//
	// 2. Replace non-zero length SourceClip with a Pulldown.
	//

	// Set the slot segment to non-zero length SourceClip
	{
		IAAFSourceClipSP pSourceClip;
 		checkResult(defs.cdSourceClip()->
			CreateInstance(IID_IAAFSourceClip, (IUnknown **)&pSourceClip));
		aafSourceRef_t sourceRef = {{0}, 0, 0};
		checkResult(pSourceClip->Initialize(pEssenceKind, pulldownLength*3, sourceClipRef));
		IAAFSegmentSP pSegment;
		checkResult(pSourceClip->QueryInterface(IID_IAAFSegment, (void**)&pSegment));
		checkResult(pSlot->SetSegment(pSegment));
	}

	// AddPulldownRef() replaces an existing SourceClip with a Pulldown
	// with same SourceClip reference but adjusted length.
	checkResult(pSourceMob->AddPulldownRef(
		kAAFAppend, // This gets ignored by the implementation.
		editRate,
		slotID,
		pEssenceKind,
		pulldownSourceRef_1,
		pulldownLength,
		pulldownKind,
		pulldownPhaseFrame,
		pulldownDirection));

	// Check the Pulldown
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckPulldown(
			pSegment,
			pulldownLength,
			pulldownSourceRef_1,
			pulldownKind,
			pulldownPhaseFrame,
			pulldownDirection);
	}


	//
	// 3. Add Pulldown to an empty Sequence.
	//

	// Set the slot segment to empty Sequence
	{
		IAAFSequenceSP pSequence;
 		checkResult(defs.cdSequence()->
				  CreateInstance(IID_IAAFSequence, 
								 (IUnknown **)&pSequence));		
		checkResult(pSequence->Initialize(pEssenceKind));
		IAAFSegmentSP pSegment;
		checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void**)&pSegment));
		IAAFMobSlotSP pSlot;
		checkResult(pMob->LookupSlot(slotID, &pSlot));
		checkResult(pSlot->SetSegment(pSegment));
	}

	// AddPulldownRef() adds a new Pulldown component to an empty Sequence.
	checkResult(pSourceMob->AddPulldownRef(
		kAAFAppend, // This gets ignored by the implementation.
		editRate,
		slotID,
		pEssenceKind,
		pulldownSourceRef_2,
		pulldownLength,
		pulldownKind,
		pulldownPhaseFrame,
		pulldownDirection));

	// Check Sequence with a single Pulldown
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		IAAFSequenceSP pSequence;
		checkResult(pSegment->QueryInterface(IID_IAAFSequence, (void**)&pSequence));

		// Expect one and only Sequence component
		aafUInt32 componentCount = 0;
		checkResult(pSequence->CountComponents(&componentCount));
		checkExpression(componentCount == 1, AAFRESULT_TEST_FAILED);

		// Expect a Pulldown as the the Sequence component
		IAAFComponentSP pComponent;
		checkResult(pSequence->GetComponentAt(0, &pComponent));
		CheckPulldown(
			pComponent,
			pulldownLength,
			pulldownSourceRef_2,
			pulldownKind,
			pulldownPhaseFrame,
			pulldownDirection);
	}

	// Cannot add Pulldown over Segment that is not a SourceClip
	// (at this point we have a Sequence with a single Pulldown as
	// the Segment).
	checkExpression(pSourceMob->AddPulldownRef(
						kAAFAppend, // This gets ignored by the implementation.
						editRate,
						slotID,
						pEssenceKind,
						pulldownSourceRef_1,
						pulldownLength,
						pulldownKind,
						pulldownPhaseFrame,
						pulldownDirection) == AAFRESULT_NOT_SOURCE_CLIP,
					AAFRESULT_TEST_FAILED);


	//
	// 4. In a Sequence replace non-zero length SourceClip with with a Pulldown.
	//

	// Set the slot segment to a sequence with a zero length component
	// followed by a non-zero length SourceClip.
	{
		IAAFSegmentSP pSegment;
		checkResult(CreateSequenceWithSourceClip(
			defs,
			pEssenceKind,
			pulldownLength*2,
			sourceClipRef,
			true,
			&pSegment));
		checkResult(pSlot->SetSegment(pSegment));
	}

	// AddPulldownRef() find first non-zero length SourceClip in a Sequence
	// and replaces it with a Pulldown with same SourceClip reference but
	// adjusted length.
	checkResult(pSourceMob->AddPulldownRef(
		kAAFAppend, // This gets ignored by the implementation.
		editRate,
		slotID,
		pEssenceKind,
		pulldownSourceRef_1,
		pulldownLength,
		pulldownKind,
		pulldownPhaseFrame,
		pulldownDirection));

	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		IAAFSequenceSP pSequence;
		checkResult(pSegment->QueryInterface(IID_IAAFSequence, (void**)&pSequence));
		// The first component is zero-length Filler.
		IAAFComponentSP pComponent;
		checkResult(pSequence->GetComponentAt(0, &pComponent));
		IAAFFillerSP pFiller;
		checkResult(pComponent->QueryInterface(IID_IAAFFiller, (void**)&pFiller));
		// The second component is a Pulldown
		checkResult(pSequence->GetComponentAt(1, &pComponent));
		CheckPulldown(
			pComponent,
			pulldownLength,
			pulldownSourceRef_1,
			pulldownKind,
			pulldownPhaseFrame,
			pulldownDirection);
	}

	// Cannot add Pulldown over Segment that is not a SourceClip
	// (at this point we have a Sequence with a zero length Filler
	// and a single Pulldown as the Segment).
	checkExpression(pSourceMob->AddPulldownRef(
						kAAFAppend, // This gets ignored by the implementation.
						editRate,
						slotID,
						pEssenceKind,
						pulldownSourceRef_1,
						pulldownLength,
						pulldownKind,
						pulldownPhaseFrame,
						pulldownDirection) == AAFRESULT_NOT_SOURCE_CLIP,
					AAFRESULT_TEST_FAILED);

	// Remove the slot added by this routine.
	RemoveSlot(pMob, slotID);
}



// Test IAAFSourceMob::AddPulldownRef() handling of unknown (-1) length.
//
// The routine tests supported uses of AddPulldownRef() and correctness of
// data it creates but is not meant to be used to validate persistence of
// data create by AddPulldownRef().
//
static void TestAddPulldownRefWithUnknownLength(IAAFSourceMob* pSourceMob)
{
	IAAFObjectSP pObject;
	checkResult(pSourceMob->QueryInterface(IID_IAAFObject, (void**)&pObject));
	IAAFDictionarySP pDictionary;
	checkResult(pObject->GetDictionary(&pDictionary));
	CAAFBuiltinDefs defs(pDictionary);

	IAAFMobSP pMob;
	checkResult(pSourceMob->QueryInterface(IID_IAAFMob, (void**)&pMob));

	IAAFDataDef* pEssenceKind = defs.ddkAAFSound();
	const aafRational_t editRate = {25, 1};
	const aafSlotID_t slotID = 401;
	const aafLength_t pulldownLength = 532;
    const aafPulldownKind_t  pulldownKind = kAAFOneToOneNTSC;
    const aafPhaseFrame_t  pulldownPhaseFrame = 4;
    const aafPulldownDir_t  pulldownDirection = kAAFTapeToFilmSpeed;

	const aafSourceRef_t pulldownSourceRef_1 =
	{
		{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
		 0x13, 0x00, 0x00, 0x00,
		 {0x9ecbe671, 0xa584, 0x46cd, {0x94, 0xa6, 0xe9, 0x54, 0xa6, 0x90, 0x54, 0xd8}}},
		17,
		342
	};
	const aafSourceRef_t pulldownSourceRef_2 =
	{
		{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
		 0x13, 0x00, 0x00, 0x00,
		 {0xb01d0cca, 0x1659, 0x4b9b, {0xb3, 0x73, 0x14, 0x3b, 0x3, 0xed, 0xdf, 0xad}}},
		6757,
		573
	};

	const aafSourceRef_t sourceClipRef =
	{
		{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
		 0x13, 0x00, 0x00, 0x00,
		 {0xb7649a5f, 0x2637, 0x43f8, {0xb0, 0x95, 0x1, 0x66, 0xf5, 0x21, 0xb2, 0xc4}}},
		677,
		426
	};

	// Ensure slot not present
	IAAFMobSlotSP pSlot;
	checkExpression(pMob->LookupSlot(slotID, &pSlot) == AAFRESULT_SLOT_NOT_FOUND, AAFRESULT_TEST_FAILED);

	//
	// 1. Create new slot with Pulldown of unknown (-1) length.
	//

	// Add timeline slot with Pulldown of unknown (-1) length.
	checkResult(pSourceMob->AddPulldownRef(
		kAAFAppend, // This gets ignored by the implementation.
		editRate,
		slotID,
		pEssenceKind,
		pulldownSourceRef_1,
		AAF_UNKNOWN_LENGTH,
		pulldownKind,
		pulldownPhaseFrame,
		pulldownDirection));

	// Check the new slot with Pulldown
	checkResult(pMob->LookupSlot(slotID, &pSlot));

	// Check the Pulldown
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckPulldown(
			pSegment,
			AAF_UNKNOWN_LENGTH,
			pulldownSourceRef_1,
			pulldownKind,
			pulldownPhaseFrame,
			pulldownDirection);
	}


	//
	// 2. Replace non-zero length SourceClip with Pulldown of unknown (-1) length.
	//

	// Set the slot segment to non-zero length SourceClip
	{
		IAAFSourceClipSP pSourceClip;
 		checkResult(defs.cdSourceClip()->
			CreateInstance(IID_IAAFSourceClip, (IUnknown **)&pSourceClip));
		aafSourceRef_t sourceRef = {{0}, 0, 0};
		checkResult(pSourceClip->Initialize(pEssenceKind, 1999, sourceClipRef));
		IAAFSegmentSP pSegment;
		checkResult(pSourceClip->QueryInterface(IID_IAAFSegment, (void**)&pSegment));
		checkResult(pSlot->SetSegment(pSegment));
	}

	// AddPulldownRef() replaces an existing SourceClip with a Pulldown
	// with same SourceClip reference but adjusted length.
	checkResult(pSourceMob->AddPulldownRef(
		kAAFAppend, // This gets ignored by the implementation.
		editRate,
		slotID,
		pEssenceKind,
		pulldownSourceRef_2,
		AAF_UNKNOWN_LENGTH,
		pulldownKind,
		pulldownPhaseFrame,
		pulldownDirection));

	// Check the Pulldown
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckPulldown(
			pSegment,
			AAF_UNKNOWN_LENGTH,
			pulldownSourceRef_2,
			pulldownKind,
			pulldownPhaseFrame,
			pulldownDirection);
	}


	//
	// 3. Replace SourceClip of unknown (-1) length with non-zero length Pulldown.
	//

	// Set the slot segment to SourceClip of unknown (-1) length 
	{
		IAAFSourceClipSP pSourceClip;
 		checkResult(defs.cdSourceClip()->
			CreateInstance(IID_IAAFSourceClip, (IUnknown **)&pSourceClip));
		aafSourceRef_t sourceRef = {{0}, 0, 0};
		checkResult(pSourceClip->Initialize(pEssenceKind, AAF_UNKNOWN_LENGTH, sourceClipRef));
		IAAFSegmentSP pSegment;
		checkResult(pSourceClip->QueryInterface(IID_IAAFSegment, (void**)&pSegment));
		checkResult(pSlot->SetSegment(pSegment));
	}

	// AddPulldownRef() replaces an existing SourceClip of unknown (-1)
	// length with a Pulldown with same SourceClip reference and non-zero
	// length.
	checkResult(pSourceMob->AddPulldownRef(
		kAAFAppend, // This gets ignored by the implementation.
		editRate,
		slotID,
		pEssenceKind,
		pulldownSourceRef_1,
		pulldownLength,
		pulldownKind,
		pulldownPhaseFrame,
		pulldownDirection));

	// Check the Pulldown
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		CheckPulldown(
			pSegment,
			pulldownLength,
			pulldownSourceRef_1,
			pulldownKind,
			pulldownPhaseFrame,
			pulldownDirection);
	}


	//
	// 4. Add Pulldown of unknown (-1) length to an empty Sequence.
	//

	// Set the slot segment to empty Sequence
	{
		IAAFSequenceSP pSequence;
 		checkResult(defs.cdSequence()->
				  CreateInstance(IID_IAAFSequence, 
								 (IUnknown **)&pSequence));		
		checkResult(pSequence->Initialize(pEssenceKind));
		IAAFSegmentSP pSegment;
		checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void**)&pSegment));
		IAAFMobSlotSP pSlot;
		checkResult(pMob->LookupSlot(slotID, &pSlot));
		checkResult(pSlot->SetSegment(pSegment));
	}

	// AddPulldownRef() adds a new Pulldown component of unknown (-1) length
	// to an empty Sequence.
	checkResult(pSourceMob->AddPulldownRef(
		kAAFAppend, // This gets ignored by the implementation.
		editRate,
		slotID,
		pEssenceKind,
		pulldownSourceRef_2,
		AAF_UNKNOWN_LENGTH,
		pulldownKind,
		pulldownPhaseFrame,
		pulldownDirection));

	// Check Sequence with a single Pulldown
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		IAAFSequenceSP pSequence;
		checkResult(pSegment->QueryInterface(IID_IAAFSequence, (void**)&pSequence));

		// Expect one and only Sequence component
		aafUInt32 componentCount = 0;
		checkResult(pSequence->CountComponents(&componentCount));
		checkExpression(componentCount == 1, AAFRESULT_TEST_FAILED);

		// Expect a Pulldown as the the Sequence component
		IAAFComponentSP pComponent;
		checkResult(pSequence->GetComponentAt(0, &pComponent));
		CheckPulldown(
			pComponent,
			AAF_UNKNOWN_LENGTH,
			pulldownSourceRef_2,
			pulldownKind,
			pulldownPhaseFrame,
			pulldownDirection);
	}


	//
	// 5. In a Sequence replace non-zero length SourceClip with with Pulldown of unknown (-1) length.
	//

	// Set the slot segment to a sequence with a zero length component
	// followed by a non-zero length SourceClip.
	{
		IAAFSegmentSP pSegment;
		checkResult(CreateSequenceWithSourceClip(
			defs,
			pEssenceKind,
			pulldownLength*2,
			sourceClipRef,
			true,
			&pSegment));
		checkResult(pSlot->SetSegment(pSegment));
	}

	// AddPulldownRef() finds first non-zero length - including unknown (-1)
	// length - SourceClip in a Sequence and replaces it with a Pulldown with
	// same SourceClip reference but adjusted length.
	checkResult(pSourceMob->AddPulldownRef(
		kAAFAppend, // This gets ignored by the implementation.
		editRate,
		slotID,
		pEssenceKind,
		pulldownSourceRef_1,
		AAF_UNKNOWN_LENGTH,
		pulldownKind,
		pulldownPhaseFrame,
		pulldownDirection));

	// Check Sequence with Filler and Pulldown
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		IAAFSequenceSP pSequence;
		checkResult(pSegment->QueryInterface(IID_IAAFSequence, (void**)&pSequence));
		// The first component is zero-length Filler.
		IAAFComponentSP pComponent;
		checkResult(pSequence->GetComponentAt(0, &pComponent));
		IAAFFillerSP pFiller;
		checkResult(pComponent->QueryInterface(IID_IAAFFiller, (void**)&pFiller));
		// The second component is a Pulldown of unknown (-1) length.
		checkResult(pSequence->GetComponentAt(1, &pComponent));
		CheckPulldown(
			pComponent,
			AAF_UNKNOWN_LENGTH,
			pulldownSourceRef_1,
			pulldownKind,
			pulldownPhaseFrame,
			pulldownDirection);
	}


	//
	// 6. In a Sequence replace SourceClip of unknown (-1) length with non-zero length Pulldown.
	//

	// Set the slot segment to a sequence with a zero length component
	// followed by a SourceClip of unknown (-1) length.
	{
		IAAFSegmentSP pSegment;
		checkResult(CreateSequenceWithSourceClip(
			defs,
			pEssenceKind,
			AAF_UNKNOWN_LENGTH,
			sourceClipRef,
			true,
			&pSegment));
		checkResult(pSlot->SetSegment(pSegment));
	}

	// AddPulldownRef() finds first non-zero length - including unknown (-1)
	// length - SourceClip in a Sequence and replaces it with a Pulldown with
	// same SourceClip reference but adjusted length.
	checkResult(pSourceMob->AddPulldownRef(
		kAAFAppend, // This gets ignored by the implementation.
		editRate,
		slotID,
		pEssenceKind,
		pulldownSourceRef_2,
		pulldownLength,
		pulldownKind,
		pulldownPhaseFrame,
		pulldownDirection));

	// Check Sequence with Filler and Pulldown
	{
		IAAFSegmentSP pSegment;
		checkResult(pSlot->GetSegment(&pSegment));
		IAAFSequenceSP pSequence;
		checkResult(pSegment->QueryInterface(IID_IAAFSequence, (void**)&pSequence));
		// The first component is zero-length Filler.
		IAAFComponentSP pComponent;
		checkResult(pSequence->GetComponentAt(0, &pComponent));
		IAAFFillerSP pFiller;
		checkResult(pComponent->QueryInterface(IID_IAAFFiller, (void**)&pFiller));
		// The second component is a Pulldown of non-zero length.
		checkResult(pSequence->GetComponentAt(1, &pComponent));
		CheckPulldown(
			pComponent,
			pulldownLength,
			pulldownSourceRef_2,
			pulldownKind,
			pulldownPhaseFrame,
			pulldownDirection);
	}

	// Remove the slot added by this routine.
	RemoveSlot(pMob, slotID);
}


// Test IAAFSourceMob::AddNilReference() handling of unknown (-1) length.
//
// The routine tests supported uses of AddNilReference() and correctness of
// data it creates but is not meant to be used to validate persistence of
// data create by AddPulldownRef().
//
static void TestAddNilReferenceWithUnknownLength(IAAFSourceMob* pSourceMob)
{
	IAAFObjectSP pObject;
	checkResult(pSourceMob->QueryInterface(IID_IAAFObject, (void**)&pObject));
	IAAFDictionarySP pDictionary;
	checkResult(pObject->GetDictionary(&pDictionary));
	CAAFBuiltinDefs defs(pDictionary);

	const aafSlotID_t slotID = 87;
	const aafRational_t editRate = {24, 1};
	checkResult(pSourceMob->AddNilReference(
		slotID,
		AAF_UNKNOWN_LENGTH,
		defs.ddkAAFSound(),
		editRate));

	// Check the new slot with Pulldown
	IAAFMobSP pMob;
	checkResult(pSourceMob->QueryInterface(IID_IAAFMob, (void**)&pMob));
	IAAFMobSlotSP pSlot;
	checkResult(pMob->LookupSlot(slotID, &pSlot));

	IAAFSegmentSP pSegment;
	checkResult(pSlot->GetSegment(&pSegment));
	IAAFSourceClipSP pSourceClip;
	checkResult(pSegment->QueryInterface(IID_IAAFSourceClip, (void**)&pSourceClip));
	CheckComponentLength(pSourceClip, AAF_UNKNOWN_LENGTH);

	RemoveSlot(pSourceMob, slotID);
}



static HRESULT CreateAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_constref productID)
{
	IAAFFile *					pFile = NULL;
	bool bFileOpen = false;
	IAAFHeader *				pHeader = NULL;
	IAAFDictionary*  pDictionary = NULL;
	IAAFSourceMob	*pSourceMob = NULL;
	IAAFMob			*pMob = NULL;
	IAAFEssenceDescriptor *edesc = NULL;

	HRESULT						hr = S_OK;

  try
  {
      // Remove the previous test file if any.
      RemoveTestFile(pFileName);


	  // Create the file
	  checkResult(CreateTestFile( pFileName, fileKind, rawStorageType, productID, &pFile ));
	  bFileOpen = true;
 
	  // We can't really do anthing in AAF without the header.
	  checkResult(pFile->GetHeader(&pHeader));

	  // Get the AAF Dictionary so that we can create valid AAF objects.
	  checkResult(pHeader->GetDictionary(&pDictionary));
	  CAAFBuiltinDefs defs (pDictionary);
	 		
	  //Make the first mob
	  long			test;

	  aafRational_t	audioRate = { 44100, 1 };

	  // Create a Mob
	  checkResult(defs.cdSourceMob()->
				  CreateInstance(IID_IAAFSourceMob, 
								 (IUnknown **)&pSourceMob));

	  checkResult(pSourceMob->QueryInterface (IID_IAAFMob, (void **)&pMob));

	  checkResult(pMob->SetMobID(mobInfo.mobID));
	  checkResult(pMob->SetName(L"SourceMOBTest"));
	  
  	  TestAddNilReferenceWithUnknownLength(pSourceMob);

	  // Add some slots
	  for(test = 0; test < mobInfo.numberOfSlots; test++)
	  {
		  checkResult(pSourceMob->AddNilReference (test+1, 0, defs.ddkAAFSound(), audioRate));
	  }

	  TestAppendEdgecodeSlot(pSourceMob);

	  //Add new edgecode slot
	  checkResult(pSourceMob->AppendEdgecodeSlot(
		  mobInfo.edgecodeSlot.editRate,
		  mobInfo.edgecodeSlot.slotID,
		  mobInfo.edgecodeSlot.edgecode.startFrame,
		  mobInfo.edgecodeSlot.length,
		  mobInfo.edgecodeSlot.edgecode.filmKind,
		  mobInfo.edgecodeSlot.edgecode.codeFormat,
		  mobInfo.edgecodeSlot.edgecode.header));
	  mobInfo.edgecodeSlot.edgecode.startFrame += 1;
	  //Modify existing edgecode slot
	  checkResult(pSourceMob->AppendEdgecodeSlot(
		  mobInfo.edgecodeSlot.editRate,
		  mobInfo.edgecodeSlot.slotID,
		  mobInfo.edgecodeSlot.edgecode.startFrame,
		  mobInfo.edgecodeSlot.length,
		  mobInfo.edgecodeSlot.edgecode.filmKind,
		  mobInfo.edgecodeSlot.edgecode.codeFormat,
		  mobInfo.edgecodeSlot.edgecode.header));

	  TestAppendTimecodeSlot(pSourceMob);

	  //Add timecode slot
	  checkResult(pSourceMob->AppendTimecodeSlot(
		  mobInfo.timecodeSlot.editRate,
		  mobInfo.timecodeSlot.slotID,
		  mobInfo.timecodeSlot.timecode,
		  mobInfo.timecodeSlot.length));
	  mobInfo.timecodeSlot.timecode.startFrame += 1;
	  //Modify existing timecode slot
	  checkResult(pSourceMob->AppendTimecodeSlot(
		  mobInfo.timecodeSlot.editRate,
		  mobInfo.timecodeSlot.slotID,
		  mobInfo.timecodeSlot.timecode,
		  mobInfo.timecodeSlot.length));

	  TestAddPulldownRef(pSourceMob);
	  TestAddPulldownRefWithUnknownLength(pSourceMob);

	  // Add timeline slot with Pulldown to the file.
	  checkResult(pSourceMob->AddPulldownRef(
		  kAAFAppend, // This gets ignored by the implementation.
		  mobInfo.slotWithPulldown.editRate,
		  mobInfo.slotWithPulldown.slotID,
		  defs.ddkAAFSound(),
		  mobInfo.slotWithPulldown.sourceRef,
		  mobInfo.slotWithPulldown.length,
		  mobInfo.slotWithPulldown.pulldownKind,
		  mobInfo.slotWithPulldown.pulldownPhaseFrame,
		  mobInfo.slotWithPulldown.pulldownDirection));

	  // Create a concrete subclass of EssenceDescriptor
 	  checkResult(defs.cdAIFCDescriptor()->
				  CreateInstance(IID_IAAFEssenceDescriptor, 
								 (IUnknown **)&edesc));		

		IAAFAIFCDescriptor*			pAIFCDesc = NULL;
		checkResult(edesc->QueryInterface (IID_IAAFAIFCDescriptor, (void **)&pAIFCDesc));
		checkResult(pAIFCDesc->SetSummary (sizeof(TEST_AIFC_Summary), TEST_AIFC_Summary));
		pAIFCDesc->Release();
		pAIFCDesc = NULL;

 	  checkResult(pSourceMob->SetEssenceDescriptor (edesc));

	  checkResult(pHeader->AddMob(pMob));

  }
  catch (HRESULT& rResult)
  {
    hr = rResult;
  }
	
  if (edesc)
	  edesc->Release();

  if (pMob)
    pMob->Release();

  if (pSourceMob)
    pSourceMob->Release();

	if (pDictionary)
		pDictionary->Release();

	if (pHeader)
		pHeader->Release();

	if (pFile) 
	{
		if (bFileOpen)
		  {
			pFile->Save();
			pFile->Close();
		  }
		pFile->Release();
	}

	return hr;
}

static HRESULT ReadAAFFile(aafWChar * pFileName)
{
	// IAAFSession *				pSession = NULL;
	IAAFFile *					pFile = NULL;
	bool bFileOpen = false;
	IAAFHeader *				pHeader = NULL;
	IEnumAAFMobs *mobIter = NULL;
	IAAFEssenceDescriptor		*pEdesc = NULL;
	IAAFSourceMob				*pSourceMob = NULL;
	IAAFMob			*aMob = NULL;
	IEnumAAFMobSlots	*slotIter = NULL;
	IAAFMobSlot		*slot = NULL;
	aafNumSlots_t	numMobs, n, s;
	HRESULT						hr = S_OK;

	try
	{ 
    // Open the file
		checkResult(AAFFileOpenExistingRead(pFileName, 0, &pFile));
		bFileOpen = true;
 
    // We can't really do anthing in AAF without the header.
		checkResult(pFile->GetHeader(&pHeader));

		// Get the number of mobs in the file (should be one)
		checkResult(pHeader->CountMobs(kAAFAllMob, &numMobs));
		checkExpression(1 == numMobs, AAFRESULT_TEST_FAILED);


		



    checkResult(pHeader->GetMobs (NULL, &mobIter));
	  for(n = 0; n < numMobs; n++)
	  {
		  aafWChar		name[500];
		  aafNumSlots_t	numSlots;
		  aafMobID_t		mobID;
		  aafSlotID_t		trackID;

		  checkResult(mobIter->NextOne (&aMob));
		  checkResult(aMob->GetName (name, sizeof(name)));
		  checkResult(aMob->GetMobID (&mobID));

		  checkResult(aMob->CountSlots (&numSlots));
		  if (mobInfo.numberOfSlots+3 != numSlots)
			  return AAFRESULT_TEST_FAILED;
		  if(numSlots != 0)
		  {
			  checkResult(aMob->GetSlots(&slotIter));

			  for(s = 0; s < numSlots; s++)
			  {
				checkResult(slotIter->NextOne (&slot));
				checkResult(slot->GetSlotID(&trackID));

				if(trackID == mobInfo.timecodeSlot.slotID ||
					trackID == mobInfo.edgecodeSlot.slotID)
				{
					IAAFSegmentSP pSegment;
					IAAFSequenceSP pSequence;
					checkResult(slot->GetSegment(&pSegment));
					checkResult(pSegment->QueryInterface(IID_IAAFSequence, (void **) &pSequence));

					if(trackID == mobInfo.timecodeSlot.slotID)
					{
						IAAFTimecodeSP timeCode;
						IAAFComponentSP compTimeCodeSP;
						checkResult(pSequence->GetComponentAt(0, &compTimeCodeSP));
						checkResult(compTimeCodeSP->QueryInterface(IID_IAAFTimecode, (void**)&timeCode));
						aafTimecode_t tc;
						checkResult(timeCode->GetTimecode(&tc));
						checkExpression(tc.startFrame == mobInfo.timecodeSlot.timecode.startFrame, AAFRESULT_TEST_FAILED);
					}
					else if (trackID == mobInfo.edgecodeSlot.slotID)
					{
						IAAFEdgecodeSP edgeCode;
						IAAFComponentSP compEdgeCodeSP;
						checkResult(pSequence->GetComponentAt(0, &compEdgeCodeSP));
						checkResult(compEdgeCodeSP->QueryInterface(IID_IAAFEdgecode, (void**)&edgeCode));
						aafEdgecode_t  edgecode; 
						checkResult(edgeCode->GetEdgecode(&edgecode));
						checkExpression(edgecode.startFrame == mobInfo.edgecodeSlot.edgecode.startFrame, AAFRESULT_TEST_FAILED);
						checkExpression(memcmp(edgecode.header, mobInfo.edgecodeSlot.edgecode.header, 3)==0, AAFRESULT_TEST_FAILED);
						checkExpression(edgecode.filmKind == mobInfo.edgecodeSlot.edgecode.filmKind, AAFRESULT_TEST_FAILED);
						checkExpression(edgecode.codeFormat == mobInfo.edgecodeSlot.edgecode.codeFormat, AAFRESULT_TEST_FAILED);
					}
				}
				else if (trackID == mobInfo.slotWithPulldown.slotID)
				{
					IAAFSegmentSP pSegment;
					checkResult(slot->GetSegment(&pSegment));
					CheckPulldown(
						pSegment,
						mobInfo.slotWithPulldown.length,
						mobInfo.slotWithPulldown.sourceRef,
						mobInfo.slotWithPulldown.pulldownKind,
						mobInfo.slotWithPulldown.pulldownPhaseFrame,
						mobInfo.slotWithPulldown.pulldownDirection);
				}
				slot->Release();
				slot = NULL;
			  }
		  }
		  checkResult(aMob->QueryInterface (IID_IAAFSourceMob, (void **)&pSourceMob));
		  checkResult(pSourceMob->GetEssenceDescriptor (&pEdesc));

		  aafUInt8 summary[5];
		  IAAFAIFCDescriptor* pAIFCDesc = NULL;
		  checkResult(pEdesc->QueryInterface (IID_IAAFAIFCDescriptor, (void **)&pAIFCDesc));
		  checkResult(pAIFCDesc->GetSummary (sizeof(summary), summary));
		  checkExpression(memcmp(summary, TEST_AIFC_Summary, sizeof(TEST_AIFC_Summary)) == 0, AAFRESULT_TEST_FAILED);
		  pAIFCDesc->Release();
		  pAIFCDesc = NULL;

		  pEdesc->Release();
		  pEdesc = NULL;

		  pSourceMob->Release();
		  pSourceMob = NULL;

		  aMob->Release();
		  aMob = NULL;
    }
	}
  catch (HRESULT& rResult)
  {
    hr = rResult;
  }

  
  // Cleanup and return
  if (slot)
    slot->Release();

  if (slotIter)
    slotIter->Release();

  if (pEdesc)
    pEdesc->Release();

  if (pSourceMob)
    pSourceMob->Release();

  if (aMob)
    aMob->Release();

	if(mobIter)
		mobIter->Release();

	if (pHeader)
    pHeader->Release();

	if (pFile) 
	{
		if (bFileOpen)
			pFile->Close();
		pFile->Release();
	}

	return hr;
}
 
extern "C" HRESULT CAAFSourceMob_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);
extern "C" HRESULT CAAFSourceMob_test(
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
		if(hr == AAFRESULT_SUCCESS)
			hr = ReadAAFFile( pFileName );
	}
  catch (...)
	{
	  cerr << "CAAFSourceMob_test...Caught general C++"
		   << " exception!" << endl; 
	  hr = AAFRESULT_TEST_FAILED;
	}


	// When all of the functionality of this class is tested, we can return success.
	// When a method and its unit test have been implemented, remove it from the list.
	if (SUCCEEDED(hr))
	{
		cout << "The following AAFSourceMob methods have not been implemented:" << endl; 
		cout << "     Initialize" << endl; 
		cout << "     AppendPhysSourceRef - needs unit test" << endl; 
		cout << "     SpecifyValidCodeRange" << endl; 
		cout << "     NewPhysSourceRef" << endl;
		hr = AAFRESULT_TEST_PARTIAL_SUCCESS;
	}
	  
	return hr;
}
