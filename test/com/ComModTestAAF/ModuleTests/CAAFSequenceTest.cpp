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
#include <string.h>

#include "AAFStoredObjectIDs.h"
#include "AAFResult.h"
#include "ModuleTest.h"
#include "AAFDataDefs.h"
#include "AAFDefUIDs.h"
#include "AAFSmartPointer.h"

#include "CAAFBuiltinDefs.h"

static const 	aafMobID_t	TEST_MobID =
{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
0x13, 0x00, 0x00, 0x00,
{0x75529074, 0x0404, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}};


// convenient error handlers.
inline void checkResult(HRESULT r)
{
  if (FAILED(r))
    throw r;
}
inline void checkExpression(bool expression, HRESULT r=AAFRESULT_TEST_FAILED)
{
  if (!expression)
    throw r;
}

#define COMPONENT_TEST_LENGTH 10

#define TEST_BYPASS			1
#define TEST_EFFECT_NAME	L"A TestEffect"
#define TEST_EFFECT_DESC	L"A longer description of the TestEffect"
#define TEST_PARAM_NAME		L"A TestEffect parameter"
#define TEST_PARAM_DESC		L"A longer description of the TestEffect parameter"
#define TEST_PARAM_UNITS	L"Furlongs per Fortnight"
#define TEST_EFFECT_LEN		60

const aafUID_t kTestEffectID = { 0xD15E7611, 0xFE40, 0x11d2, { 0x80, 0xA5, 0x00, 0x60, 0x08, 0x14, 0x3E, 0x6F } };

void InstantiateFiller(CAAFBuiltinDefs *defs, 
					   aafLength_t length, 
					   IAAFComponent*& pComponent)
{
	checkResult(defs->cdFiller()->CreateInstance(IID_IAAFComponent, 
		(IUnknown **)&pComponent));
	checkResult(pComponent->SetDataDef(defs->ddkAAFSound()));
	checkResult(pComponent->SetLength(length)); 
}

void InstantiateComponent(CAAFBuiltinDefs *defs, 
						 aafLength_t length, 
						 IAAFComponent*& pComponent)
{
	InstantiateFiller(defs, length, pComponent);
}

void InstantiateComponentWithoutLength(CAAFBuiltinDefs *defs, IAAFComponent*& pComponent)
{
	checkResult(defs->cdFiller()->CreateInstance(IID_IAAFComponent, 
		(IUnknown **)&pComponent));
	checkResult(pComponent->SetDataDef(defs->ddkAAFSound()));
}

void InstantiateNonFillerComponent(CAAFBuiltinDefs *defs, 
								   aafLength_t length, 
								   IAAFComponent*& pComponent)
{
	IAAFSourceClip* pSourceClip = NULL;

	checkResult(defs->cdSourceClip()->CreateInstance(IID_IAAFSourceClip, 
		(IUnknown **)&pSourceClip));
	aafSourceRef_t nullSrcRef;
	memset(&nullSrcRef, 0, sizeof(nullSrcRef));
	checkResult(pSourceClip->Initialize(defs->ddkAAFSound(), length, nullSrcRef));
	checkResult(pSourceClip->QueryInterface(IID_IAAFComponent, (void **)&pComponent));
	pSourceClip->Release();
	pSourceClip = NULL;
}

void InstantiateEvent(CAAFBuiltinDefs *defs,
					  aafPosition_t position,
					  IAAFComponent*& pEventASpComp)
{
	IAAFEvent *pEvent = NULL;

	checkResult(defs->cdCommentMarker()->
		CreateInstance(IID_IAAFEvent, 
			(IUnknown **)&pEvent));
	checkResult(pEvent->SetPosition(position));
	checkResult(pEvent->SetComment(L"A comment"));
	checkResult(pEvent->QueryInterface(IID_IAAFComponent, (void **)&pEventASpComp));
	checkResult(pEventASpComp->SetDataDef(defs->ddkAAFSound()));

	pEvent->Release();
	pEvent = NULL;
}

// Create Event without Position or Length
void InstantiateEvent(CAAFBuiltinDefs *defs,
					  IAAFComponent*& pEventASpComp)
{
	IAAFEvent *pEvent = NULL;

	checkResult(defs->cdCommentMarker()->
		CreateInstance(IID_IAAFEvent, 
			(IUnknown **)&pEvent));
	// AAF specification and AAF Toolkit define Position as required
	// property of Event. It has to be set to something.
	checkResult(pEvent->SetPosition(0));
	checkResult(pEvent->SetComment(L"A comment"));
	checkResult(pEvent->QueryInterface(IID_IAAFComponent, (void **)&pEventASpComp));
	checkResult(pEventASpComp->SetDataDef(defs->ddkAAFSound()));

	pEvent->Release();
	pEvent = NULL;
}

void InstantiateEventWithLength(CAAFBuiltinDefs *defs,
								  aafLength_t length,
								  aafPosition_t position,
								  IAAFComponent*& pEventASpComp)
{
	IAAFEvent *pEvent = NULL;
	InstantiateEvent(defs, position, pEventASpComp);
	checkResult(pEventASpComp->QueryInterface(IID_IAAFEvent, (void **)&pEvent));
	checkResult(pEventASpComp->SetLength(length));
	pEvent->Release();
	pEvent = NULL;
}

void InstantiateEventWithLength(CAAFBuiltinDefs *defs,
								aafLength_t length,
								IAAFComponent*& pEventASpComp)
{
	IAAFEvent *pEvent = NULL;
	InstantiateEvent(defs, pEventASpComp);
	checkResult(pEventASpComp->QueryInterface(IID_IAAFEvent, (void **)&pEvent));
	checkResult(pEventASpComp->SetLength(length));
	pEvent->Release();
	pEvent = NULL;
}

void TestComponentLength(IAAFComponent *pCompLengthCheck,
						 aafLength_t expectedLength)
{
	aafLength_t actualLength = 0;
	checkResult(pCompLengthCheck->GetLength(&actualLength));
	checkExpression(expectedLength == actualLength, AAFRESULT_TEST_FAILED);
}

void InstantiateTransition(CAAFBuiltinDefs *defs,
						   aafLength_t transitionLength,
						   IAAFOperationDef* pOperationDef,
						   IAAFComponent*& pComponent)
{
	IAAFOperationGroup  *pOperationGroup = 0;
	IAAFTransition* pTransition = 0;
	aafPosition_t cutPoint = 0;

	checkResult(defs->cdOperationGroup()->
				CreateInstance(IID_IAAFOperationGroup,
								(IUnknown **)&pOperationGroup));
	checkResult(pOperationGroup->Initialize(defs->ddkAAFSound(), transitionLength, pOperationDef));

	checkResult(defs->cdTransition()->
						CreateInstance(IID_IAAFTransition, 
									(IUnknown **)&pTransition));
	checkResult(pTransition->Initialize (defs->ddkAAFSound(),
												transitionLength,
												cutPoint,
												pOperationGroup));
	checkResult(pTransition->QueryInterface (IID_IAAFComponent,
											(void **)&pComponent));
	
	pTransition->Release();
	pTransition  = NULL;
	pOperationGroup->Release();
	pOperationGroup = NULL;
}

HRESULT TestDefinitions(CAAFBuiltinDefs *defs)
{
	HRESULT			hr = S_OK;

	IAAFSequence*	pSequence = NULL; 
	IAAFComponent*	pComponent = NULL;

	// Add mob slot w/ sequence
 	  checkResult(defs->cdSequence()->
				  CreateInstance(IID_IAAFSequence, 
								 (IUnknown **)&pSequence));		//Instantiate the sequence

	  /*
		This is a charaterization test.
		This test confirms the erroneus behavior that inserting components into an uninitialized sequence succeeds.
		The insert will succeed and leave the sequence uninitialized.
		This behaviour is wrong but legacy code probably depends on it.
		The correct behaviour would be to return AAFRESULT_NOT_INITIALIZED on any attempt to manipulate the sequence before it is initialized.
	  */
	  //Attempt to insert a component before the sequence datadef is set
	  InstantiateComponent(defs, COMPONENT_TEST_LENGTH, pComponent);
	  checkExpression(AAFRESULT_SUCCESS == pSequence->PrependComponent(pComponent), AAFRESULT_TEST_FAILED);
	  pComponent->Release();
	  pComponent = NULL;

	  pSequence->Release();
	  pSequence = 0;

	  return hr;
}


HRESULT TestComponents(CAAFBuiltinDefs *defs, 
					   IAAFDictionary*  pDictionary, 
					   IAAFMob* pMob)
{
	HRESULT			hr = S_OK;

	IAAFSequence*	pSequence = NULL; 
	IAAFComponent *pCompLengthCheck = NULL; //To test sequence length.
	IAAFComponent*	pComponent = NULL;
	aafUInt32		numComponents;
	aafUID_t	   effectID = kTestEffectID;
	IAAFSegment*	pSegment = NULL;
	IAAFTimelineMobSlot*	pMobSlot = NULL;

	// Add mob slot w/ sequence
 	  checkResult(defs->cdSequence()->
				  CreateInstance(IID_IAAFSequence, 
								 (IUnknown **)&pSequence));		
	  checkResult(pSequence->Initialize(defs->ddkAAFSound())); 

	  //Get Component interface to test sequence lenght:
	  checkResult(pSequence->QueryInterface(IID_IAAFComponent, (void **)&pCompLengthCheck));


	  // Set up for transitions testing.
	  // Actual transition testing is further down below.
	  // Here we test behavior specific to empty sequences.
	  aafLength_t					transitionLength=1;
	  IAAFOperationDef*			pOperationDef = NULL;

	  // Create the effect and parameter definitions
	  checkResult(defs->cdOperationDef()->
					CreateInstance(IID_IAAFOperationDef, 
								   (IUnknown **)&pOperationDef));
	  checkResult(pOperationDef->Initialize (effectID, TEST_EFFECT_NAME, TEST_EFFECT_DESC));
	  checkResult(pDictionary->RegisterOperationDef(pOperationDef));
	  checkResult(pOperationDef->SetDataDef (defs->ddkAAFSound()));
	  checkResult(pOperationDef->SetNumberInputs (0));

	  //Create a transition 
	  InstantiateTransition(defs, transitionLength, pOperationDef, pComponent);
	  //Adding the transition to an empty sequence should fail
	  checkExpression(AAFRESULT_LEADING_TRAN == pSequence->InsertComponentAt(0,pComponent), AAFRESULT_TEST_FAILED);
	  pComponent->Release();
	  pComponent = NULL;


	  aafLength_t testLength[4];
	  aafLength_t len;
	  IAAFComponent *pEventASpComp = NULL;
	  aafPosition_t position;
	  
	  int i = 0;
	  // Append two components onto sequence
	  for(i = 0; i < 2; i++)
	  {
		  InstantiateComponent(defs, COMPONENT_TEST_LENGTH+i+2, pComponent);
		  if(i<1)
		  {
			  checkResult(pSequence->PrependComponent(pComponent));
		  }
		  else
		  {
			  checkResult(pSequence->AppendComponent(pComponent));
		  }
		  if(i > 0)
		  {
			  testLength[i] = testLength[i-1]+(COMPONENT_TEST_LENGTH+i+2);
		  }
		  else
		  {
			  testLength[i] = COMPONENT_TEST_LENGTH+i+2;
		  }
		  TestComponentLength(pCompLengthCheck, testLength[i]);
		  pComponent->Release();
		  pComponent = NULL;
	  }
		checkResult(pSequence->CountComponents (&numComponents));
		checkExpression(2 == numComponents, AAFRESULT_TEST_FAILED);
		checkResult(pSequence->RemoveComponentAt(1)); 
		checkResult(pSequence->CountComponents (&numComponents));
		checkExpression(1 == numComponents, AAFRESULT_TEST_FAILED);
		len = 0;//Component at index 1 had length 13, after removing it, the sequence length should be 12.
		checkResult(pCompLengthCheck->GetLength(&len));
		checkExpression((COMPONENT_TEST_LENGTH+2) == len, AAFRESULT_TEST_FAILED);



		// Now prepend a component
		InstantiateComponent(defs, COMPONENT_TEST_LENGTH, pComponent);//10+12 = 22
		checkResult(pSequence->PrependComponent(pComponent));
		pComponent->Release();
		pComponent = NULL;
		TestComponentLength(pCompLengthCheck, (COMPONENT_TEST_LENGTH+2+COMPONENT_TEST_LENGTH));

		
		// Now insert a component in the middle 
		InstantiateComponent(defs, COMPONENT_TEST_LENGTH+1, pComponent);//22+11 = 33 
		checkResult(pSequence->InsertComponentAt(1,pComponent));
		pComponent->Release();
		pComponent = NULL;
		TestComponentLength(pCompLengthCheck, (3*COMPONENT_TEST_LENGTH+3));
		aafLength_t oldLen = (3*COMPONENT_TEST_LENGTH+3);
		// Component count should now be 3
		checkResult(pSequence->CountComponents (&numComponents));
		checkExpression(3 == numComponents, AAFRESULT_TEST_FAILED);


		/////////////////////Trannsition testing/////////////////////////////

		//Create a transition 
		InstantiateTransition(defs, transitionLength, pOperationDef, pComponent);
		//Prepending the transition should fail
		checkExpression(AAFRESULT_LEADING_TRAN == pSequence->InsertComponentAt(0,pComponent), AAFRESULT_TEST_FAILED);
		// now append the transition
		checkResult(pSequence->AppendComponent(pComponent));
		TestComponentLength(pCompLengthCheck, (oldLen-transitionLength));
		// Component count should now be 4
		checkResult(pSequence->CountComponents (&numComponents));
		checkExpression(4 == numComponents, AAFRESULT_TEST_FAILED);
		// Release the component - because we need to reuse the pointer 
		pComponent->Release();
		pComponent = NULL;
		
		//Make a second transition
		InstantiateTransition(defs, transitionLength, pOperationDef, pComponent);
		// now append the second transition and it should fail due to adjecent transitions
		checkExpression(AAFRESULT_ADJACENT_TRAN == pSequence->AppendComponent(pComponent), AAFRESULT_TEST_FAILED);
		// now try inserting the second transition before the first and it should fail due to adjecent transitions
		checkExpression(AAFRESULT_ADJACENT_TRAN == pSequence->InsertComponentAt(numComponents-1, pComponent), AAFRESULT_TEST_FAILED);
		// Component count should now still be 4
		checkResult(pSequence->CountComponents (&numComponents));
		checkExpression(4 == numComponents, AAFRESULT_TEST_FAILED);
		// Release the component - because we need to reuse the pointer later
		pComponent->Release();
		pComponent = NULL;

		pOperationDef->Release();
		pOperationDef = NULL;

		//Remove the transition.
		checkResult(pSequence->RemoveComponentAt(3)); 
		checkResult(pSequence->CountComponents (&numComponents));
		checkExpression(3 == numComponents, AAFRESULT_TEST_FAILED);
		oldLen = (oldLen-transitionLength);
		len = 0;
		checkResult(pCompLengthCheck->GetLength(&len));
		checkExpression((oldLen+transitionLength) == len, AAFRESULT_TEST_FAILED);
		///End Transition testing////////////////////////////////////////////

		checkResult(pSequence->QueryInterface (IID_IAAFSegment, (void **)&pSegment));

		aafRational_t editRate = { 0, 1};
		checkResult(pMob->AppendNewTimelineSlot(editRate,
												pSegment,
												1,
												L"AAF Test Sequence",
												0,
												&pMobSlot));

		pSegment->Release();
    pSegment = NULL;

	pMobSlot->Release();
    pMobSlot = NULL;


		if (pSequence)
			{
				pSequence->Release();
				pSequence = 0;
			}

		if (pComponent)
			pComponent->Release();

		if (pCompLengthCheck)
			pCompLengthCheck->Release();


	return hr;
}

HRESULT TestEvents(CAAFBuiltinDefs *defs)
{
	HRESULT			hr = S_OK;
	IAAFComponent*	pComponent = NULL;
	IAAFSequence*	pEventsSequence = NULL;
	IAAFComponent *pEventLengthCheck = NULL; //To test events sequence length.

	// Add mob slot w/ events sequence.
 	  checkResult(defs->cdSequence()->
				  CreateInstance(IID_IAAFSequence, 
								 (IUnknown **)&pEventsSequence));		
	  checkResult(pEventsSequence->Initialize(defs->ddkAAFSound()));

	  //Get Component interface to test sequence lenght:
	  checkResult(pEventsSequence->QueryInterface(IID_IAAFComponent, (void **)&pEventLengthCheck));
	  aafLength_t testLength[4];
	  aafLength_t len;

	  IAAFComponent *pEventASpComp = NULL;
	  aafPosition_t position;


		//Create and append a few events with NO lenght property defined
		position = 0;
		InstantiateEvent(defs, position, pEventASpComp);
		//Append event
		checkResult(pEventsSequence->AppendComponent(pEventASpComp));
		pEventASpComp->Release();
		pEventASpComp = NULL;
		//The sequence should also not have length defined because all its elements don't.
		checkExpression(AAFRESULT_PROP_NOT_PRESENT == pEventLengthCheck->GetLength(&len), AAFRESULT_TEST_FAILED);

		position = 1;
		InstantiateEvent(defs, position, pEventASpComp);
		//Append event
		checkResult(pEventsSequence->AppendComponent(pEventASpComp));
		pEventASpComp->Release();
		pEventASpComp = NULL;
		checkExpression(AAFRESULT_PROP_NOT_PRESENT == pEventLengthCheck->GetLength(&len), AAFRESULT_TEST_FAILED);

		//Remove elements
		checkResult(pEventsSequence->RemoveComponentAt(1));
		checkExpression(AAFRESULT_PROP_NOT_PRESENT == pEventLengthCheck->GetLength(&len), AAFRESULT_TEST_FAILED);
		checkResult(pEventsSequence->RemoveComponentAt(0));
		checkExpression(AAFRESULT_PROP_NOT_PRESENT == pEventLengthCheck->GetLength(&len), AAFRESULT_TEST_FAILED);

		int i;
		for(i = 0; i < 3; i++)
		{
			position = 10+i;
			// Create a concrete subclass of event
			InstantiateEventWithLength(defs, (COMPONENT_TEST_LENGTH+i), position, pEventASpComp);
			if(i==0)
			{
				testLength[i] = COMPONENT_TEST_LENGTH+i;
			}
			else
			{
				testLength[i]=(position+COMPONENT_TEST_LENGTH+i)-10;
			}
			// Add the event to the sequence.
			if(i<1)
			{
				checkResult(pEventsSequence->PrependComponent(pEventASpComp));
			}
			else
			{
				checkResult(pEventsSequence->AppendComponent(pEventASpComp));
			}
			TestComponentLength(pEventLengthCheck, testLength[i]);

			if(pEventASpComp)
			{
				pEventASpComp->Release();
				pEventASpComp = NULL;
			}
		}
		//Remove the middle event, the sequence length should not be affected:
		checkResult(pEventsSequence->RemoveComponentAt(1));
		TestComponentLength(pEventLengthCheck, 14);

		//Remove the last element with the farthest end point, sequence length must be recalculated in O(n) time.
		checkResult(pEventsSequence->RemoveComponentAt(1));
		TestComponentLength(pEventLengthCheck, COMPONENT_TEST_LENGTH);

		// Now prepend an event
		position = 0;
		InstantiateEventWithLength(defs, COMPONENT_TEST_LENGTH, position, pEventASpComp);
		checkResult(pEventsSequence->PrependComponent(pEventASpComp));
		pEventASpComp->Release();
		pEventASpComp = NULL;
		TestComponentLength(pEventLengthCheck, (COMPONENT_TEST_LENGTH*2));

		//Remove the end element
		checkResult(pEventsSequence->RemoveComponentAt(1));
		TestComponentLength(pEventLengthCheck, COMPONENT_TEST_LENGTH);

		//Sequence now has length 10 with an elemnent starting at 0 and having lenght 10.
		//Insert an element starting at 5 with length 10 and the sequence should end up with a length of 15.
		position = 5;
		InstantiateEventWithLength(defs, COMPONENT_TEST_LENGTH, position, pEventASpComp);
		//Inserting events out of order (5 > 0) should fail 
		checkExpression(AAFRESULT_EVENT_SEMANTICS == pEventsSequence->PrependComponent(pEventASpComp), AAFRESULT_TEST_FAILED);
		//Append event
		checkResult(pEventsSequence->AppendComponent(pEventASpComp));
		pEventASpComp->Release();
		pEventASpComp = NULL;
		TestComponentLength(pEventLengthCheck, 15);

		//Remove both elements. ( "clear" is part of some super class? )
		checkResult(pEventsSequence->RemoveComponentAt(1));
		TestComponentLength(pEventLengthCheck,COMPONENT_TEST_LENGTH);

		checkResult(pEventsSequence->RemoveComponentAt(0));
		TestComponentLength(pEventLengthCheck,0);

		//Last test with 3 nested events.
		position = 40;
		InstantiateEventWithLength(defs, (4*COMPONENT_TEST_LENGTH), position, pEventASpComp);
		//Inserting at invalid index should fail
		checkExpression(AAFRESULT_BADINDEX == pEventsSequence->InsertComponentAt(3,pEventASpComp), AAFRESULT_TEST_FAILED);
		//Insert first event 
		checkResult(pEventsSequence->InsertComponentAt(0,pEventASpComp));
		pEventASpComp->Release();
		pEventASpComp = NULL;
		TestComponentLength(pEventLengthCheck,4*COMPONENT_TEST_LENGTH);

		//Insert second event, which should not add to the length.
		position = 50;
		InstantiateEventWithLength(defs, (2*COMPONENT_TEST_LENGTH), position, pEventASpComp);
		//Insert second event 
		checkResult(pEventsSequence->InsertComponentAt(1,pEventASpComp));
		pEventASpComp->Release();
		pEventASpComp = NULL;
		TestComponentLength(pEventLengthCheck,4*COMPONENT_TEST_LENGTH);

		//Third event adds to the length
		position = 60;
		InstantiateEventWithLength(defs, (3*COMPONENT_TEST_LENGTH), position, pEventASpComp);
		//Just like append and prepend, insert should not allow out of order events.
		checkExpression(AAFRESULT_EVENT_SEMANTICS == pEventsSequence->InsertComponentAt(1,pEventASpComp), AAFRESULT_TEST_FAILED);
		//Insert third event 
		checkResult(pEventsSequence->InsertComponentAt(2,pEventASpComp));
		pEventASpComp->Release();
		pEventASpComp = NULL;
		TestComponentLength(pEventLengthCheck,5*COMPONENT_TEST_LENGTH);

		//Inset last event with first position at index 0 and length longer then curent sequence length.
		position = 0;
		InstantiateEventWithLength(defs, (10*COMPONENT_TEST_LENGTH), position, pEventASpComp);
		//Insert last event 
		checkResult(pEventsSequence->InsertComponentAt(0,pEventASpComp));
		pEventASpComp->Release();
		pEventASpComp = NULL;
		TestComponentLength(pEventLengthCheck,10*COMPONENT_TEST_LENGTH);

		//In general case inserting a component in an events sequence should succeeed:
		// - Events can be mixed with other components in a sequence referenced from a static mob slot.
		// - Events can be mixed with fillers in a sequence referenced from a timeline mob slot.
		//Since this sequence is not yet referenced by any mob the implementation cannot apply any
		//constraints specific to mob slot type.
		InstantiateComponent(defs, COMPONENT_TEST_LENGTH, pComponent);
		checkResult(pEventsSequence->AppendComponent(pComponent));
		pComponent->Release();
		pComponent = NULL;

		// Insert Event after non-Event
		position = 70;
		InstantiateEventWithLength(defs, (2*COMPONENT_TEST_LENGTH), position, pEventASpComp);
		checkResult(pEventsSequence->AppendComponent(pEventASpComp));
		pEventASpComp->Release();
		pEventASpComp = NULL;

		// Insert non-Event (Filler) after Event
		IAAFComponent*	pFiller = NULL;
		InstantiateFiller(defs, 123, pFiller);
		checkResult(pEventsSequence->AppendComponent(pFiller));
		pFiller->Release();
		pFiller = NULL;

		if(pEventsSequence)
			pEventsSequence->Release();

		if(pEventLengthCheck)
			pEventLengthCheck->Release();

	return hr;
}

HRESULT TestTimelineMobSlotNonEventSemantics(CAAFBuiltinDefs* defs,
											 IAAFMob* pMob)
{
	HRESULT			hr = S_OK;

	IAAFSequence*	pSequence = NULL;
	IAAFComponent*	pFiller = NULL;
	IAAFComponent*	pComponent = NULL;
	IAAFComponent*	pEvent = NULL;
	IAAFSegment*	pSegment = NULL;
	IAAFTimelineMobSlot*	pMobSlot = NULL;
	aafUInt32	expectedComponentCount = 0;

	checkResult(defs->cdSequence()->
				CreateInstance(IID_IAAFSequence,
								(IUnknown**)&pSequence));		
	checkResult(pSequence->Initialize(defs->ddkAAFSound()));
	checkResult(pSequence->QueryInterface (IID_IAAFSegment, (void **)&pSegment));

	const aafRational_t editRate = {0, 1};
	const aafSlotID_t slotID = 1;
	checkResult(pMob->AppendNewTimelineSlot(editRate,
											pSegment,
											slotID,
											L"AAF Test Sequence",
											0,
											&pMobSlot));

	/* TODO: Test adding non-Filler to Sequences of only Fillers:

	InstantiateFiller(defs, 123, pFiller);
	checkResult(pSequence->AppendComponent(pFiller));
	pFiller->Release();
	pFiller = NULL;

	InstantiateNonFillerComponent(defs, 123, pComponent);
	checkResult(pSequence->AppendComponent(pComponent));
	pComponent->Release();
	pComponent = NULL;
	*/

	// Sequence with a single non-Filler (SourceClip)
	InstantiateNonFillerComponent(defs, 123, pComponent);
	checkResult(pSequence->AppendComponent(pComponent));
	expectedComponentCount++;
	pComponent->Release();
	pComponent = NULL;

	// Cannot add Event to a Sequence in TimelineMobSlot that contains
	// components that are not Events or Fillers
	InstantiateEvent(defs, pEvent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(0, pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(1, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	// Sequence of Filler, non-Filler (SourceClip) and Filler.
	InstantiateFiller(defs, 123, pFiller);
	checkResult(pSequence->PrependComponent(pFiller));
	expectedComponentCount++;
	pFiller->Release();
	pFiller = NULL;
	InstantiateFiller(defs, 123, pFiller);
	checkResult(pSequence->AppendComponent(pFiller));
	expectedComponentCount++;
	pFiller->Release();
	pFiller = NULL;

	// Cannot add Event to a Sequence in TimelineMobSlot that contains
	// components that are not Events or Fillers
	InstantiateEvent(defs, pEvent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(0, pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(1, pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(2, pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(3, pEvent), AAFRESULT_TEST_FAILED);

	aafUInt32 componentCount = 0;
	checkResult(pSequence->CountComponents(&componentCount));
	checkExpression(expectedComponentCount == componentCount, AAFRESULT_TEST_FAILED);

	if (pSequence)
	{
		pSequence->Release();
		pSequence = NULL;
	}
	if (pFiller)
	{
		pFiller->Release();
		pFiller = NULL;
	}
	if (pComponent)
	{
		pComponent->Release();
		pComponent = NULL;
	}
	if (pEvent)
	{
		pEvent->Release();
		pEvent = NULL;
	}
	if (pSegment)
	{
		pSegment->Release();
		pSegment = NULL;
	}
	if (pMobSlot)
	{
		pMobSlot->Release();
		pMobSlot = NULL;
	}

	return hr;
}

HRESULT TestTimelineMobSlotInvalidSemantics(CAAFBuiltinDefs* defs,
											IAAFSequence*	pSequence)
{
	HRESULT			hr = S_OK;

	IAAFComponent*	pEvent = NULL;
	IAAFComponent*	pComponent = NULL;

	// Cannot add Event without Length to a Sequence in TimelineMobSlot
	InstantiateEvent(defs, pEvent);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->InsertComponentAt(0, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	// Cannot add Event with Position to a Sequence in TimelineMobSlot
	InstantiateEventWithLength(defs, 123, 19, pEvent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(0, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	// Cannot add non-Event without Length to a Sequence in TimelineMobSlot
	InstantiateComponentWithoutLength(defs, pComponent);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->AppendComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->PrependComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->InsertComponentAt(0, pComponent), AAFRESULT_TEST_FAILED);
	pComponent->Release();
	pComponent = NULL;

	if (pEvent)
	{
		pEvent->Release();
		pEvent = NULL;
	}
	if (pComponent)
	{
		pComponent->Release();
		pComponent = NULL;
	}

	return hr;
}

HRESULT TestTimelineMobSlotWithEventsInvalidSemantics(CAAFBuiltinDefs* defs,
													  IAAFSequence*	pSequence)
{
	HRESULT			hr = S_OK;

	IAAFComponent*	pComponent = NULL;

	// Cannot add component that is not Filler or Event to a Sequence in
	// TimelineMobSlot that contains Events.
	InstantiateNonFillerComponent(defs, 123, pComponent);
	checkExpression(AAFRESULT_OBJECT_SEMANTIC == pSequence->AppendComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_OBJECT_SEMANTIC == pSequence->PrependComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_OBJECT_SEMANTIC == pSequence->InsertComponentAt(0, pComponent), AAFRESULT_TEST_FAILED);
	pComponent->Release();
	pComponent = NULL;

	if (pComponent)
	{
		pComponent->Release();
		pComponent = NULL;
	}

	return hr;
}

HRESULT TestTimelineMobSlotEventSemantics(CAAFBuiltinDefs* defs,
										  IAAFMob* pMob)
{
	HRESULT			hr = S_OK;

	aafUInt32	expectedComponentCount = 0;

	//-----------------------------------------------------
	// Empty Sequence attached to TimelineMobSlot
	//-----------------------------------------------------
	IAAFSmartPointer<IAAFSequence> pSequence;
	IAAFSmartPointer<IAAFSegment> pSegmentSequence;
	IAAFSmartPointer<IAAFComponent> pComponentSequence;
	checkResult(defs->cdSequence()->CreateInstance(IID_IAAFSequence, (IUnknown**)&pSequence));
	checkResult(pSequence->Initialize(defs->ddkAAFSound()));
	checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void **)&pSegmentSequence));
	checkResult(pSequence->QueryInterface(IID_IAAFComponent, (void **)&pComponentSequence));

	const aafRational_t editRate = {0, 1};
	const aafSlotID_t slotID = 1;
	IAAFSmartPointer<IAAFTimelineMobSlot> pMobSlot;
	checkResult(pMob->AppendNewTimelineSlot(editRate,
											pSegmentSequence,
											slotID,
											L"AAF Test Sequence",
											0,
											&pMobSlot));


	// Test invalid semantics with empty Sequence
	TestTimelineMobSlotInvalidSemantics(defs, pSequence);

	//-----------------------------------------------------
	// Sequence with a single Event
	//-----------------------------------------------------
	IAAFSmartPointer<IAAFComponent> pEvent;
	InstantiateEventWithLength(defs, 123, *&pEvent);
	checkResult(pSequence->AppendComponent(pEvent));
	expectedComponentCount++;

	// Test invalid semantics with only Events
	TestTimelineMobSlotInvalidSemantics(defs, pSequence);
	TestTimelineMobSlotWithEventsInvalidSemantics(defs, pSequence);

	//-----------------------------------------------------
	// Sequence of Filler, Event and Filler.
	//-----------------------------------------------------
	// Can add Fillers to a Sequence with Events
	IAAFSmartPointer<IAAFComponent> pFiller;
	InstantiateFiller(defs, 123, *&pFiller);
	checkResult(pSequence->PrependComponent(pFiller));
	expectedComponentCount++;
	InstantiateFiller(defs, 123, *&pFiller);
	checkResult(pSequence->AppendComponent(pFiller));
	expectedComponentCount++;

	// Test invalid semantics with Events and Fillers
	TestTimelineMobSlotInvalidSemantics(defs, pSequence);
	TestTimelineMobSlotWithEventsInvalidSemantics(defs, pSequence);

	//-----------------------------------------------------
	// Sequence of Event, Filler, Event, Event, Filler and
	// Event.
	//-----------------------------------------------------
	// Can add Events to a Sequence with Events and Fillers
	InstantiateEventWithLength(defs, 123, *&pEvent);
	checkResult(pSequence->InsertComponentAt(expectedComponentCount-1, pEvent));
	expectedComponentCount++;
	InstantiateEventWithLength(defs, 123, *&pEvent);
	checkResult(pSequence->AppendComponent(pEvent));
	expectedComponentCount++;
	InstantiateEventWithLength(defs, 123, *&pEvent);
	checkResult(pSequence->PrependComponent(pEvent));
	expectedComponentCount++;

	// Test invalid semantics with Events and Fillers
	TestTimelineMobSlotInvalidSemantics(defs, pSequence);
	TestTimelineMobSlotWithEventsInvalidSemantics(defs, pSequence);

	aafUInt32 componentCount = 0;
	checkResult(pSequence->CountComponents(&componentCount));
	checkExpression(expectedComponentCount == componentCount, AAFRESULT_TEST_FAILED);

	return hr;
}

HRESULT TestStaticMobSlotInvalidSemantics(CAAFBuiltinDefs* defs,
										  IAAFSequence*	pSequence)
{
	HRESULT			hr = S_OK;

	IAAFComponent*	pEvent = NULL;
	IAAFComponent*	pComponent = NULL;

	// Cannot add Event with Length to a Sequence in StaticMobSlot
	InstantiateEventWithLength(defs, 123, pEvent);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->InsertComponentAt(0, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	// Cannot add Event with unknown length (-1) to a Sequence in StaticMobSlot
	InstantiateEventWithLength(defs, AAF_UNKNOWN_LENGTH, pEvent);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->InsertComponentAt(0, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	// Cannot add Event with Position to a Sequence in StaticMobSlot
	InstantiateEvent(defs, 19, pEvent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(0, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	// Cannot add Event with Length and Position to a Sequence in StaticMobSlot
	InstantiateEventWithLength(defs, 123, 19, pEvent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(0, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	// Cannot add non-Event with Length to a Sequence in StaticMobSlot
	InstantiateComponent(defs, 123, pComponent);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->AppendComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->PrependComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->InsertComponentAt(0, pComponent), AAFRESULT_TEST_FAILED);
	pComponent->Release();
	pComponent = NULL;

	// Cannot add non-Event with unknown length (-1) to a Sequence in StaticMobSlot
	InstantiateComponent(defs, AAF_UNKNOWN_LENGTH, pComponent);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->AppendComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->PrependComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_BAD_LENGTH == pSequence->InsertComponentAt(0, pComponent), AAFRESULT_TEST_FAILED);
	pComponent->Release();
	pComponent = NULL;

	if (pComponent)
	{
		pComponent->Release();
		pComponent = NULL;
	}
	if (pEvent)
	{
		pEvent->Release();
		pEvent = NULL;
	}

	return hr;
}

HRESULT TestTimelineMobSlotEventSemanticsUnkLen(CAAFBuiltinDefs* defs, IAAFMob* pMob)
{
	HRESULT hr = S_OK;

	IAAFSmartPointer<IAAFComponent> pFiller;
	IAAFSmartPointer<IAAFComponent> pEvent;

	aafUInt32 componentCount = 0;
	aafUInt32 expectedComponentCount = 0;
	aafLength_t sequenceLength = 0;

	// Sequence
	IAAFSmartPointer<IAAFSequence> pSequence;
	IAAFSmartPointer<IAAFSegment> pSegmentSequence;
	IAAFSmartPointer<IAAFComponent> pComponentSequence;
	checkResult(defs->cdSequence()->CreateInstance(IID_IAAFSequence, (IUnknown**)&pSequence));
	checkResult(pSequence->Initialize(defs->ddkAAFSound()));
	checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void **)&pSegmentSequence));
	checkResult(pSequence->QueryInterface(IID_IAAFComponent, (void **)&pComponentSequence));

	// TimelineMobSlot
	const aafSlotID_t slotID = 1;
	const aafRational_t editRate = { 0, 1 };
	IAAFSmartPointer<IAAFTimelineMobSlot> pMobSlot;
	checkResult(pMob->AppendNewTimelineSlot(editRate,
		pSegmentSequence,
		slotID,
		L"AAF Test Sequence",
		0,
		&pMobSlot));

	// append Filler
	InstantiateFiller(defs, 43, *&pFiller);
	checkResult(pSequence->AppendComponent(pFiller));
	expectedComponentCount++;

	// append Event
	InstantiateEventWithLength(defs, 57, *&pEvent);
	checkResult(pSequence->AppendComponent(pEvent));
	expectedComponentCount++;

	// append Filler with unknown length
	InstantiateFiller(defs, AAF_UNKNOWN_LENGTH, *&pFiller);
	// Sequence Components other than the last Component shall not have a Length property set to AAF_UNKNOWN_LENGTH.
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->PrependComponent(pFiller), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->InsertComponentAt(0, pFiller), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->InsertComponentAt(1, pFiller), AAFRESULT_TEST_FAILED);
	// the last Component of a Sequence may have a Length property set to AAF_UNKNOWN_LENGTH.
	checkResult(pSequence->AppendComponent(pFiller));
	expectedComponentCount++;

	// a Sequence that contains a Component with Length of -1 shall have a Length property set to -1
	checkResult(pSequence->CountComponents(&componentCount));
	checkExpression(componentCount == expectedComponentCount, AAFRESULT_TEST_FAILED);
	checkResult(pComponentSequence->GetLength(&sequenceLength));
	checkExpression(sequenceLength == AAF_UNKNOWN_LENGTH, AAFRESULT_TEST_FAILED);

	// cannot append another component with unknown length
	InstantiateEventWithLength(defs, AAF_UNKNOWN_LENGTH, *&pEvent);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);

	// cannot append any component after Componet with unknown length
	InstantiateEventWithLength(defs, 77, *&pEvent);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);

	// insert Component into Sequence with unknown length
	InstantiateEventWithLength(defs, 33, *&pEvent);
	checkResult(pSequence->InsertComponentAt(2, pEvent));
	expectedComponentCount++;

	// remove Component with length
	checkResult(pSequence->RemoveComponentAt(2));
	expectedComponentCount--;

	// but Sequence still has an unknown length
	checkResult(pSequence->CountComponents(&componentCount));
	checkExpression(componentCount == expectedComponentCount, AAFRESULT_TEST_FAILED);
	checkResult(pComponentSequence->GetLength(&sequenceLength));
	checkExpression(sequenceLength == AAF_UNKNOWN_LENGTH, AAFRESULT_TEST_FAILED);

	// a Sequence that doesn't contains Components with Length of -1 shall not have a Length property set to -1
	checkResult(pSequence->RemoveComponentAt(expectedComponentCount - 1));
	expectedComponentCount--;
	checkResult(pSequence->CountComponents(&componentCount));
	checkExpression(componentCount == expectedComponentCount, AAFRESULT_TEST_FAILED);
	checkResult(pComponentSequence->GetLength(&sequenceLength));
	checkExpression(sequenceLength == 100, AAFRESULT_TEST_FAILED);

	return hr;
}

HRESULT TestTimelineMobSlotNonEventSemanticsUnkLen(CAAFBuiltinDefs* defs,	IAAFMob* pMob)
{
	HRESULT	hr = S_OK;

	IAAFSmartPointer<IAAFComponent> pFiller;
	IAAFSmartPointer<IAAFComponent> pSourceClip;
	
	aafUInt32 componentCount = 0;
	aafUInt32 expectedComponentCount = 0;
	aafLength_t sequenceLength = 0;

	// Sequence
	IAAFSmartPointer<IAAFSequence> pSequence;
	IAAFSmartPointer<IAAFSegment> pSegmentSequence;
	IAAFSmartPointer<IAAFComponent> pComponentSequence;
	checkResult(defs->cdSequence()->CreateInstance(IID_IAAFSequence, (IUnknown**)&pSequence));
	checkResult(pSequence->Initialize(defs->ddkAAFSound()));
	checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void **)&pSegmentSequence));
	checkResult(pSequence->QueryInterface(IID_IAAFComponent, (void **)&pComponentSequence));

	// TimelineMobSlot
	const aafSlotID_t slotID = 1;
	const aafRational_t editRate = { 0, 1 };
	IAAFSmartPointer<IAAFTimelineMobSlot> pMobSlot;
	checkResult(pMob->AppendNewTimelineSlot(editRate, pSegmentSequence,	slotID,	L"AAF Test Sequence", 0, &pMobSlot));

	// append Filler
	InstantiateFiller(defs, 43, *&pFiller);
	checkResult(pSequence->AppendComponent(pFiller));
	expectedComponentCount++;

	// append SourceClip
	InstantiateNonFillerComponent(defs, 57, *&pSourceClip);
	checkResult(pSequence->AppendComponent(pSourceClip));
	expectedComponentCount++;

	// append Filler with unknown length
	InstantiateFiller(defs, AAF_UNKNOWN_LENGTH, *&pFiller);
	// Sequence Components other than the last Component shall not have a Length property set to AAF_UNKNOWN_LENGTH.
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->PrependComponent(pFiller), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->InsertComponentAt(0, pFiller), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->InsertComponentAt(1, pFiller), AAFRESULT_TEST_FAILED);
	// the last Component of a Sequence may have a Length property set to AAF_UNKNOWN_LENGTH.
	checkResult(pSequence->AppendComponent(pFiller));
	expectedComponentCount++;

	// a Sequence that contains a Component with Length of -1 shall have a Length property set to -1
	checkResult(pSequence->CountComponents(&componentCount));
	checkExpression(componentCount == expectedComponentCount, AAFRESULT_TEST_FAILED);
	checkResult(pComponentSequence->GetLength(&sequenceLength));
	checkExpression(sequenceLength == AAF_UNKNOWN_LENGTH, AAFRESULT_TEST_FAILED);

	// cannot append another component with unknown length
	InstantiateNonFillerComponent(defs, AAF_UNKNOWN_LENGTH, *&pSourceClip);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->AppendComponent(pSourceClip), AAFRESULT_TEST_FAILED);

	// cannot append any component after Componet with unknown length
	InstantiateNonFillerComponent(defs, 77, *&pSourceClip);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->AppendComponent(pSourceClip), AAFRESULT_TEST_FAILED);

	// insert Component into Sequence with unknown length
	InstantiateNonFillerComponent(defs, 33, *&pSourceClip);
	checkResult(pSequence->InsertComponentAt(2, pSourceClip));
	expectedComponentCount++;

	// remove Component with length
	checkResult(pSequence->RemoveComponentAt(2));
	expectedComponentCount--;

	// but Sequence still has an unknown length
	checkResult(pSequence->CountComponents(&componentCount));
	checkExpression(componentCount == expectedComponentCount, AAFRESULT_TEST_FAILED);
	checkResult(pComponentSequence->GetLength(&sequenceLength));
	checkExpression(sequenceLength == AAF_UNKNOWN_LENGTH, AAFRESULT_TEST_FAILED);

	// a Sequence that doesn't contains Components with Length of -1 shall not have a Length property set to -1
	checkResult(pSequence->RemoveComponentAt(expectedComponentCount - 1));
	expectedComponentCount--;
	checkResult(pSequence->CountComponents(&componentCount));
	checkExpression(componentCount == expectedComponentCount, AAFRESULT_TEST_FAILED);
	checkResult(pComponentSequence->GetLength(&sequenceLength));
	checkExpression(sequenceLength == 100, AAFRESULT_TEST_FAILED);

	return hr;
}

HRESULT TestStaticMobSlotSemantics(CAAFBuiltinDefs* defs,
									  IAAFMob* pMob)
{
	HRESULT			hr = S_OK;

	IAAFSequence*	pSequence = NULL;
	IAAFComponent*	pComponent = NULL;
	IAAFComponent*	pEvent = NULL;
	IAAFSegment*	pSegment = NULL;
	IAAFMobSlot*	pMobSlot = NULL;
	aafUInt32	expectedComponentCount = 0;

	//-----------------------------------------------------
	// Empty Sequence attached to StaticMobSlot
	//-----------------------------------------------------
	checkResult(defs->cdSequence()->
				CreateInstance(IID_IAAFSequence,
								(IUnknown**)&pSequence));		
	checkResult(pSequence->Initialize(defs->ddkAAFSound()));
	checkResult(pSequence->QueryInterface (IID_IAAFSegment, (void **)&pSegment));

	checkResult(defs->cdStaticMobSlot()->
				CreateInstance(IID_IAAFMobSlot,
								(IUnknown**)&pMobSlot));		
	checkResult(pMobSlot->SetSlotID(1));
	checkResult(pMobSlot->SetSegment(pSegment));

	checkResult(pMob->AppendSlot(pMobSlot));

	// Test invalid semantics with the empty Seqeunce
	TestStaticMobSlotInvalidSemantics(defs, pSequence);

	InstantiateEvent(defs, pEvent);
	checkResult(pSequence->AppendComponent(pEvent));
	expectedComponentCount++;
	pEvent->Release();
	pEvent = NULL;

	InstantiateEvent(defs, pEvent);
	checkResult(pSequence->PrependComponent(pEvent));
	expectedComponentCount++;
	pEvent->Release();
	pEvent = NULL;

	InstantiateEvent(defs, pEvent);
	checkResult(pSequence->InsertComponentAt(1, pEvent));
	expectedComponentCount++;
	pEvent->Release();
	pEvent = NULL;

	InstantiateComponentWithoutLength(defs, pComponent);
	checkResult(pSequence->AppendComponent(pComponent));
	expectedComponentCount++;
	pComponent->Release();
	pComponent = NULL;

	InstantiateComponentWithoutLength(defs, pComponent);
	checkResult(pSequence->PrependComponent(pComponent));
	expectedComponentCount++;
	pComponent->Release();
	pComponent = NULL;

	InstantiateComponentWithoutLength(defs, pComponent);
	checkResult(pSequence->InsertComponentAt(1, pComponent));
	expectedComponentCount++;
	pComponent->Release();
	pComponent = NULL;

	// Test invalid semantics with the non-empty Seqeunce
	TestStaticMobSlotInvalidSemantics(defs, pSequence);

	aafUInt32 componentCount = 0;
	checkResult(pSequence->CountComponents(&componentCount));
	checkExpression(expectedComponentCount == componentCount, AAFRESULT_TEST_FAILED);

	if (pSequence)
	{
		pSequence->Release();
		pSequence = NULL;
	}
	if (pComponent)
	{
		pComponent->Release();
		pComponent = NULL;
	}
	if (pEvent)
	{
		pEvent->Release();
		pEvent = NULL;
	}
	if (pSegment)
	{
		pSegment->Release();
		pSegment = NULL;
	}
	if (pMobSlot)
	{
		pMobSlot->Release();
		pMobSlot = NULL;
	}

	return hr;
}

HRESULT TestStaticMobSlotLengths(CAAFBuiltinDefs* defs,
								 IAAFMob* pMob)
{
	HRESULT			hr = S_OK;

	IAAFSequence*	pSequence = NULL;
	IAAFComponent*	pComponent = NULL;
	IAAFComponent*	pEvent = NULL;
	IAAFSegment*	pSegment = NULL;
	IAAFMobSlot*	pMobSlot = NULL;

	//-----------------------------------------------------
	// Create empty Sequence attached to StaticMobSlot
	//-----------------------------------------------------
	checkResult(defs->cdSequence()->
				CreateInstance(IID_IAAFSequence,
								(IUnknown**)&pSequence));		
	checkResult(pSequence->Initialize(defs->ddkAAFSound()));
	checkResult(pSequence->QueryInterface (IID_IAAFSegment, (void **)&pSegment));

	checkResult(defs->cdStaticMobSlot()->
				CreateInstance(IID_IAAFMobSlot,
								(IUnknown**)&pMobSlot));		
	checkResult(pMobSlot->SetSlotID(1));
	checkResult(pMobSlot->SetSegment(pSegment));

	checkResult(pMob->AppendSlot(pMobSlot));

	//-----------------------------------------------------
	// Add Events and non-Events without length to
	// the Sequence.
	//-----------------------------------------------------
	InstantiateEvent(defs, pEvent);
	checkResult(pSequence->AppendComponent(pEvent));
	pEvent->Release();
	pEvent = NULL;

	InstantiateEvent(defs, pEvent);
	checkResult(pSequence->PrependComponent(pEvent));
	pEvent->Release();
	pEvent = NULL;

	InstantiateEvent(defs, pEvent);
	checkResult(pSequence->InsertComponentAt(1, pEvent));
	pEvent->Release();
	pEvent = NULL;

	InstantiateComponentWithoutLength(defs, pComponent);
	checkResult(pSequence->AppendComponent(pComponent));
	pComponent->Release();
	pComponent = NULL;

	InstantiateComponentWithoutLength(defs, pComponent);
	checkResult(pSequence->PrependComponent(pComponent));
	pComponent->Release();
	pComponent = NULL;

	InstantiateComponentWithoutLength(defs, pComponent);
	checkResult(pSequence->InsertComponentAt(1, pComponent));
	pComponent->Release();
	pComponent = NULL;

	// Sequence with components without Length
	checkResult(pSequence->QueryInterface(IID_IAAFComponent, (void**)&pComponent));
	aafLength_t length = 0;
	checkExpression(AAFRESULT_PROP_NOT_PRESENT == pComponent->GetLength(&length), AAFRESULT_TEST_FAILED);
	pComponent->Release();
	pComponent = NULL;

	if (pSequence)
	{
		pSequence->Release();
		pSequence = NULL;
	}
	if (pComponent)
	{
		pComponent->Release();
		pComponent = NULL;
	}
	if (pEvent)
	{
		pEvent->Release();
		pEvent = NULL;
	}
	if (pSegment)
	{
		pSegment->Release();
		pSegment = NULL;
	}
	if (pMobSlot)
	{
		pMobSlot->Release();
		pMobSlot = NULL;
	}

	return hr;
}

HRESULT TestEventMobSlotInvalidSemantics(CAAFBuiltinDefs* defs,
										 IAAFSequence* pSequence,
										 aafPosition_t existingPosition)
{
	// The following tests assume that pSequence is attached to
	// an EventMobSlot.

	IAAFComponent*	pComponent = NULL;
	IAAFComponent*	pEvent = NULL;

	//-----------------------------------------------------
	// Sequence with Event at 'existingPosition'
	//-----------------------------------------------------

	// Cannot add non-Event (with Length) to a Sequence in EventMobSlot
	InstantiateComponent(defs, 123, pComponent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->AppendComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->PrependComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(0, pComponent), AAFRESULT_TEST_FAILED);
	pComponent->Release();
	pComponent = NULL;

	// Cannot add non-Event (without Length) to a Sequence in EventMobSlot
	InstantiateComponentWithoutLength(defs, pComponent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->AppendComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->PrependComponent(pComponent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(0, pComponent), AAFRESULT_TEST_FAILED);
	pComponent->Release();
	pComponent = NULL;

	// Note that adding Event without position cannot be tested because
	// Event's Position property is required in AAF Toolkit, and therefore
	// is always present.
	//
	// [ ... ]

	// Cannot add Event (without Length) after Event with larger position.
	InstantiateEvent(defs, existingPosition-10, pEvent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(1, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	// Cannot add Event (without Length) before Event with smaller position.
	InstantiateEvent(defs, existingPosition+10, pEvent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(0, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	// Cannot add Event (with Length) after Event with larger position.
	InstantiateEventWithLength(defs, 123, existingPosition-10, pEvent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(1, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	// Cannot add Event (with Length) before Event with smaller position.
	InstantiateEventWithLength(defs, 123, existingPosition+10, pEvent);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	checkExpression(AAFRESULT_EVENT_SEMANTICS == pSequence->InsertComponentAt(0, pEvent), AAFRESULT_TEST_FAILED);
	pEvent->Release();
	pEvent = NULL;

	if (pComponent)
	{
		pComponent->Release();
		pComponent = NULL;
	}
	if (pEvent)
	{
		pEvent->Release();
		pEvent = NULL;
	}

	return S_OK;
}

HRESULT TestEventMobSlotSemantics(CAAFBuiltinDefs* defs,
									  IAAFMob* pMob)
{
	HRESULT			hr = S_OK;

	IAAFSequence*	pSequence = NULL;
	IAAFComponent*	pFiller = NULL;
	IAAFComponent*	pComponent = NULL;
	IAAFComponent*	pEvent = NULL;
	IAAFSegment*	pSegment = NULL;
	IAAFMobSlot*	pMobSlot = NULL;

	//-----------------------------------------------------
	// Create empty(*) Sequence attached to EventMobSlot
	//-----------------------------------------------------
	checkResult(defs->cdSequence()->
				CreateInstance(IID_IAAFSequence,
								(IUnknown**)&pSequence));		
	checkResult(pSequence->Initialize(defs->ddkAAFSound()));
	checkResult(pSequence->QueryInterface (IID_IAAFSegment, (void **)&pSegment));

	checkResult(defs->cdEventMobSlot()->
				CreateInstance(IID_IAAFMobSlot,
								(IUnknown**)&pMobSlot));		
	checkResult(pMobSlot->SetSlotID(1));

	// (*) Actually, the sequence is not empty.
	// EventMobSlot's SetSegment() has a bizzare requirement for
	// an input Sequence to be non-empty. This is a whim of the API
	// which is not supported by the data model.
	const aafPosition_t position = 100;
	InstantiateEvent(defs, position, pEvent);
	checkResult(pSequence->AppendComponent(pEvent));
	pEvent->Release();
	pEvent = NULL;

	checkResult(pMobSlot->SetSegment(pSegment));
	checkResult(pMob->AppendSlot(pMobSlot));

	//-----------------------------------------------------
	// Test adding invalid components to sequence with one
	// Event at 'position'
	//-----------------------------------------------------
	TestEventMobSlotInvalidSemantics(defs, pSequence, position);

	//-----------------------------------------------------
	// Add Events with unique Positions to Sequence with
	// one Event: [0]: 100
	//-----------------------------------------------------

	// [0]: 100, [1]: 120 
	//            ^
	InstantiateEvent(defs, position+10+10, pEvent);
	checkResult(pSequence->AppendComponent(pEvent));
	pEvent->Release();
	pEvent = NULL;

	// [0]: 100, [1]: 110, [2]: 120 
	//            ^
	InstantiateEvent(defs, position+10, pEvent);
	checkResult(pSequence->InsertComponentAt(1, pEvent));
	pEvent->Release();
	pEvent = NULL;

	// [0]: 80, [1]: 100, [2]: 110, [3]: 120 
	//  ^
	InstantiateEvent(defs, position-10-10, pEvent);
	checkResult(pSequence->PrependComponent(pEvent));
	pEvent->Release();
	pEvent = NULL;

	// [0]: 80, [1]: 90, [2]: 100, [3]: 110, [4]: 120 
	//           ^
	InstantiateEvent(defs, position-10, pEvent);
	checkResult(pSequence->InsertComponentAt(1, pEvent));
	pEvent->Release();
	pEvent = NULL;

	//-----------------------------------------------------
	// Add Events with duplicate Positions to Sequence with
	// Events:
	// [0]: 80, [1]: 90, [2]: 100, [3]: 110, [4]: 120
	//-----------------------------------------------------

	// [0]: 80, [1]: 90, [2]: 100, [3]: 110, [4]: 120, [5]: 120
	//                                                  ^
	InstantiateEvent(defs, position+10+10, pEvent);
	checkResult(pSequence->AppendComponent(pEvent));
	pEvent->Release();
	pEvent = NULL;

	// [0]: 80, [1]: 90, [2]: 100, [3]: 100, [4]: 110, [5]: 120, [6]: 120
	//                    ^
	InstantiateEvent(defs, position, pEvent);
	checkResult(pSequence->InsertComponentAt(2, pEvent));
	pEvent->Release();
	pEvent = NULL;

	// [0]: 80, [1]: 80, [2]: 90, [3]: 100, [4]: 100, [5]: 110, [6]: 120, [7]: 120
	//  ^
	InstantiateEvent(defs, position-10-10, pEvent);
	checkResult(pSequence->PrependComponent(pEvent));
	pEvent->Release();
	pEvent = NULL;

	//-----------------------------------------------------
	// Validate Sequence Events and their Positions
	//-----------------------------------------------------
	const aafPosition_t expectedPositions[] = {80, 80, 90, 100, 100, 110, 120, 120};
	const size_t expectedCount = sizeof(expectedPositions) / sizeof(expectedPositions[0]);
	for (size_t i=0; i<expectedCount; i++)
	{
		IAAFComponent* pComponent = NULL;
		checkResult(pSequence->GetComponentAt(i, &pComponent));
		IAAFEvent* pEvent = NULL;
		checkResult(pComponent->QueryInterface(IID_IAAFEvent, (void**)&pEvent));
		aafPosition_t position = 0;
		checkResult(pEvent->GetPosition(&position));
		checkExpression(expectedPositions[i] == position, AAFRESULT_TEST_FAILED);
		pComponent->Release();
		pEvent->Release();
	}

	aafUInt32 componentCount = 0;
	checkResult(pSequence->CountComponents(&componentCount));
	checkExpression(expectedCount == componentCount, AAFRESULT_TEST_FAILED);

	//-----------------------------------------------------
	// Test adding invalid components to sequence with one
	// Event at 'position'
	//-----------------------------------------------------
	TestEventMobSlotInvalidSemantics(defs, pSequence, position);

	if (pSequence)
	{
		pSequence->Release();
		pSequence = NULL;
	}
	if (pFiller)
	{
		pFiller->Release();
		pFiller = NULL;
	}
	if (pComponent)
	{
		pComponent->Release();
		pComponent = NULL;
	}
	if (pEvent)
	{
		pEvent->Release();
		pEvent = NULL;
	}
	if (pSegment)
	{
		pSegment->Release();
		pSegment = NULL;
	}
	if (pMobSlot)
	{
		pMobSlot->Release();
		pMobSlot = NULL;
	}

	return hr;
}

HRESULT TestEventMobSlotSemanticsUnkLen(CAAFBuiltinDefs* defs, IAAFMob* pMob)
{
	HRESULT			hr = S_OK;

	IAAFSmartPointer<IAAFComponent> pEvent;

	aafLength_t seqLength = 0;

	//-----------------------------------------------------
	// Create empty(*) Sequence attached to EventMobSlot
	//-----------------------------------------------------
	IAAFSmartPointer<IAAFSequence> pSequence;
	IAAFSmartPointer<IAAFSegment> pSegmentSequence;
	IAAFSmartPointer<IAAFComponent> pComponentSequence;
	checkResult(defs->cdSequence()->CreateInstance(IID_IAAFSequence, (IUnknown**)&pSequence));
	checkResult(pSequence->Initialize(defs->ddkAAFSound()));
	checkResult(pSequence->QueryInterface(IID_IAAFSegment, (void **)&pSegmentSequence));
	checkResult(pSequence->QueryInterface(IID_IAAFComponent, (void **)&pComponentSequence));

	IAAFSmartPointer<IAAFMobSlot> pMobSlot;
	checkResult(defs->cdEventMobSlot()->CreateInstance(IID_IAAFMobSlot, (IUnknown**)&pMobSlot));
	checkResult(pMobSlot->SetSlotID(1));

	// (*) Actually, the sequence is not empty.
	// EventMobSlot's SetSegment() has a bizzare requirement for
	// an input Sequence to be non-empty. This is a whim of the API
	// which is not supported by the data model.
	InstantiateEvent(defs, 100, *&pEvent);
	checkResult(pSequence->AppendComponent(pEvent));

	checkResult(pMobSlot->SetSegment(pSegmentSequence));
	checkResult(pMob->AppendSlot(pMobSlot));

	InstantiateEvent(defs, 120, *&pEvent);
	checkResult(pSequence->AppendComponent(pEvent));

	// pSequence: [(pos:100; len:null), (pos:120; len:null)], len:null

	// expect no length is set
	checkExpression(AAFRESULT_PROP_NOT_PRESENT == pComponentSequence->GetLength(&seqLength), AAFRESULT_TEST_FAILED);

	// append Component with unknown length (-1)
	// Sequence Components other than the last Component shall not have a Length property set to AAF_UNKNOWN_LENGTH.
	InstantiateEventWithLength(defs, AAF_UNKNOWN_LENGTH, 10, *&pEvent);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->PrependComponent(pEvent), AAFRESULT_TEST_FAILED);
	// the last Component of a Sequence may have a Length property set to AAF_UNKNOWN_LENGTH.
	InstantiateEventWithLength(defs, AAF_UNKNOWN_LENGTH, 180, *&pEvent);
	checkResult(pSequence->AppendComponent(pEvent));

	// pSequence: [(pos:100, len:null), (pos:120, len:null), (pos:180, len:-1)], len:-1

	// a Sequence that contains a Component with Length of -1 shall have a Length property set to -1
	checkResult(pComponentSequence->GetLength(&seqLength));
	checkExpression(seqLength == AAF_UNKNOWN_LENGTH, AAFRESULT_TEST_FAILED);

	// cannot append another component with unknown length
	InstantiateEventWithLength(defs, AAF_UNKNOWN_LENGTH, 200, *&pEvent);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);

	// cannot append any component after Componet with unknown length
	InstantiateEvent(defs, 200, *&pEvent);
	checkExpression(AAFRESULT_INVALID_PARAM == pSequence->AppendComponent(pEvent), AAFRESULT_TEST_FAILED);

	// insert Component into Sequence of unknown length
	InstantiateEventWithLength(defs, 60, 140, *&pEvent);
	checkResult(pSequence->InsertComponentAt(2, pEvent));

	// pSequence: [(pos:100, len:null), (pos:120, len:null), (pos:140, len:60), (pos:180, len:-1)], len:-1

	// but Sequence still has an unknown length
	checkResult(pComponentSequence->GetLength(&seqLength));
	checkExpression(seqLength == AAF_UNKNOWN_LENGTH, AAFRESULT_TEST_FAILED);

	// remove Component with length
	checkResult(pSequence->RemoveComponentAt(2));

	// pSequence: [(pos:100, len:null), (pos:120, len:null), (pos:180, len:-1)], len:-1

	// but Sequence still has an unknown length
	checkResult(pComponentSequence->GetLength(&seqLength));
	checkExpression(seqLength == AAF_UNKNOWN_LENGTH, AAFRESULT_TEST_FAILED);

	// remove the last Component of unknown length
	checkResult(pSequence->RemoveComponentAt(2));

	// pSequence: [(pos:100, len:null), (pos:120, len:null)], len:null

	// a Sequence that doesn't contains Components with Length of -1 shall not have a Length property set to -1
	checkResult(pComponentSequence->GetLength(&seqLength));
	checkExpression(AAFRESULT_PROP_NOT_PRESENT != seqLength, AAFRESULT_TEST_FAILED);

	return hr;
}

static HRESULT CreateAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_constref productID)
{
	IAAFFile*		pFile = NULL;
	IAAFHeader*		pHeader = NULL;
	IAAFDictionary*  pDictionary = NULL;
	IAAFMob*		pMob = NULL;
	IAAFMob*		pTransientMob = NULL;

	HRESULT			hr = S_OK;
	


  try
  {  
      // Remove the previous test file if any.
      RemoveTestFile(pFileName);


	  // Create the AAF file
	  checkResult(CreateTestFile( pFileName, fileKind, rawStorageType, productID, &pFile ));

	  // Get the AAF file header.
	  checkResult(pFile->GetHeader(&pHeader));

	  // Get the AAF Dictionary so that we can create valid AAF objects.
	  checkResult(pHeader->GetDictionary(&pDictionary));
	  CAAFBuiltinDefs defs (pDictionary);
 		
	  // Create a Composition Mob
	  checkResult(defs.cdCompositionMob()->
				  CreateInstance(IID_IAAFMob, 
								 (IUnknown **)&pMob));

	  checkResult(pMob->SetMobID(TEST_MobID));
	  checkResult(pMob->SetName(L"AAFSequenceTest"));

	  TestDefinitions(&defs);
	  TestEvents(&defs);
	  TestComponents(&defs,pDictionary, pMob);
	  
		// Add the master mob to the file and cleanup
		pHeader->AddMob(pMob);

	  checkResult(defs.cdSourceMob()->
				  CreateInstance(IID_IAAFMob, 
								 (IUnknown **)&pTransientMob));
	  TestTimelineMobSlotNonEventSemantics(&defs, pTransientMob);
	  TestTimelineMobSlotNonEventSemanticsUnkLen(&defs, pTransientMob);
	  TestTimelineMobSlotEventSemantics(&defs, pTransientMob);
	  TestTimelineMobSlotEventSemanticsUnkLen(&defs, pTransientMob);
	  TestStaticMobSlotSemantics(&defs, pTransientMob);
	  TestStaticMobSlotLengths(&defs, pTransientMob);
	  TestEventMobSlotSemantics(&defs, pTransientMob);
	  TestEventMobSlotSemanticsUnkLen(&defs, pTransientMob);
  }
  catch (HRESULT& rResult)
  {
    hr = rResult;
  }


	if (pMob)
    pMob->Release();

	if (pTransientMob)
		pTransientMob->Release();

	if (pDictionary)
    pDictionary->Release();

	if (pHeader)
    pHeader->Release();

	if (pFile)
	{
		pFile->Save();
		pFile->Close();
		pFile->Release();
	}
 
	return hr;
}

static HRESULT ReadAAFFile(aafWChar* pFileName)
{
	IAAFFile*		pFile = NULL;
	IAAFHeader*		pHeader = NULL;
	IEnumAAFMobs*	pMobIter = NULL;
	IAAFMob*		pMob = NULL;
	IEnumAAFMobSlots*	pSlotIter = NULL;
	IAAFMobSlot*		pSlot = NULL;
	IAAFComponent*		pComp = NULL;
	IAAFSegment*		pSegment = NULL;
	IAAFSequence*		pSequence = NULL;
	IEnumAAFComponents*	pCompIter = NULL;
	IAAFDataDef*        pDataDef = 0;
	IAAFDefObject*      pDefObj = 0;
	aafNumSlots_t	numMobs;
	aafSearchCrit_t	criteria;
	HRESULT			hr = S_OK;


  try
  {
	  // Open the AAF file
	  checkResult(AAFFileOpenExistingRead(pFileName, 0, &pFile));

	  // Get the AAF file header.
	  checkResult(pFile->GetHeader(&pHeader));

    // Validate that there is only one composition mob.
	  checkResult(pHeader->CountMobs(kAAFCompMob, &numMobs));
	  checkExpression(1 == numMobs, AAFRESULT_TEST_FAILED);

	  // Enumerate over Composition MOBs
	  criteria.searchTag = kAAFByMobKind;
	  criteria.tags.mobKind = kAAFCompMob;
    checkResult(pHeader->GetMobs(&criteria, &pMobIter));
	  while (pMobIter && pMobIter->NextOne(&pMob) == AAFRESULT_SUCCESS)
	  {
		  aafNumSlots_t		numSlots = 0;

		  checkResult(pMob->CountSlots(&numSlots));
		  checkExpression(1 == numSlots, AAFRESULT_TEST_FAILED);

      // Enumerate over all MOB slots for this MOB
			checkResult(pMob->GetSlots(&pSlotIter));
			while (pSlotIter && pSlotIter->NextOne(&pSlot) == AAFRESULT_SUCCESS)
			{
				aafUInt32			numCpnts;

				checkResult(pSlot->GetSegment(&pSegment));
				checkResult(pSegment->QueryInterface(IID_IAAFSequence, (void **) &pSequence));

				checkResult(pSequence->CountComponents(&numCpnts));
				checkExpression(numCpnts == 3, AAFRESULT_TEST_FAILED);

				// Verify components using enumerator
			    checkResult(pSequence->GetComponents(&pCompIter));
				numCpnts = 0;
				aafLength_t	len;
				aafUID_t	dataDef;
				while (pCompIter && pCompIter->NextOne(&pComp) == AAFRESULT_SUCCESS)
				{
					numCpnts++;

					checkResult(pComp->GetDataDef(&pDataDef));
					checkResult(pDataDef->QueryInterface(IID_IAAFDefObject, (void **) &pDefObj));
					pDataDef->Release();
					pDataDef = 0;
					checkResult(pDefObj->GetAUID(&dataDef));
					pDefObj->Release();
					pDefObj = 0;
					checkExpression(memcmp(&kAAFDataDef_Sound, &dataDef, sizeof(aafUID_t)) == 0,
					                AAFRESULT_TEST_FAILED);

					checkResult(pComp->GetLength(&len));
					checkExpression(len == COMPONENT_TEST_LENGTH+numCpnts-1);

					pComp->Release();
					pComp = NULL;
				}
				checkExpression(numCpnts == 3);

				// Verify components using GetComponentAt()
				for(aafUInt32 n=0;n<3;n++)
				{
					checkResult(pSequence->GetComponentAt(n,&pComp));
					checkResult(pComp->GetDataDef(&pDataDef));
					checkResult(pDataDef->QueryInterface(IID_IAAFDefObject, (void **) &pDefObj));
					pDataDef->Release();
					pDataDef = 0;
					checkResult(pDefObj->GetAUID(&dataDef));
					pDefObj->Release();
					pDefObj = 0;
					checkExpression(memcmp(&kAAFDataDef_Sound, &dataDef, sizeof(aafUID_t)) == 0,
					                AAFRESULT_TEST_FAILED);

					checkResult(pComp->GetLength(&len));
					checkExpression(len == COMPONENT_TEST_LENGTH+n);

					pComp->Release();
					pComp = NULL;
				}

				pCompIter->Release();
				pCompIter = NULL;

				pSequence->Release();
				pSequence = NULL;

						pSegment->Release();
				pSegment = NULL;

				pSlot->Release();
				pSlot = NULL;
			}

			pSlotIter->Release();
      pSlotIter = NULL;

		  pMob->Release();
      pMob = NULL;
		}


	}
	catch (HRESULT& rResult)
	{
	  hr = rResult;
	}

	// Cleanup object references
	if (pComp)
	  {
		pComp->Release();
		pComp = 0;
	  }

	if (pCompIter)
	  {
		pCompIter->Release();
		pCompIter = 0;
	  }

	

	if (pSegment)
	  {
		pSegment->Release();
		pSegment = 0;
	  }

	if (pSlot)
	  {
		pSlot->Release();
		pSlot = 0;
	  }

	if (pSlotIter)
	  {
		pSlotIter->Release();
		pSlotIter = 0;
	  }

	if (pMob)
	  {
		pMob->Release();
		pMob = 0;
	  }

	if (pMobIter)
	  {
		pMobIter->Release();
		pMobIter = 0;
	  }

	if (pHeader)
	  {
		pHeader->Release();
		pHeader = 0;
	  }

	if (pDataDef)
	  {
		pDataDef->Release();
		pDataDef = 0;
	  }

	if (pDefObj)
	  {
		pDefObj->Release();
		pDefObj = 0;
	  }

	if (pFile)
	  {
		pFile->Close();
		pFile->Release();
		pFile = 0;
	  }

	return 	hr;
}

extern "C" HRESULT CAAFSequence_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);
extern "C" HRESULT CAAFSequence_test(
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
		cerr << "CAAFSequence_test..."
			 << "Caught general C++ exception!" << endl; 
		hr = AAFRESULT_TEST_FAILED;
	}

	return hr;
}



















