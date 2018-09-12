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

#include "ImplAAFTimecode.h"
#include "ImplAAFComponent.h"
#include "ImplAAFSegment.h"
#include "ImplAAFDataDef.h"
#include "ImplEnumAAFComponents.h"
#include "ImplAAFFiller.h"
#include "ImplAAFSequence.h"
#include "ImplAAFSourceClip.h"
#include "ImplAAFObjectCreation.h"
#include "ImplAAFDictionary.h"
#include "ImplAAFEvent.h"
#include "ImplAAFTransition.h"
#include "ImplAAFMob.h"

#include "AAFStoredObjectIDs.h"
#include "AAFPropertyIDs.h"

#include "OMAssertions.h"
#include "AAFResult.h"
#include "AAFUtils.h"

#include "ImplAAFSmartPointer.h"
typedef ImplAAFSmartPointer<ImplAAFDataDef>    ImplAAFDataDefSP;
typedef ImplAAFSmartPointer<ImplAAFDictionary> ImplAAFDictionarySP;

#include <typeinfo>

extern "C" const aafClassID_t CLSID_EnumAAFComponents;

ImplAAFSequence::ImplAAFSequence ()
:   _components(			PID_Sequence_Components,		L"Components")
{
	_persistentProperties.put(_components.address());
}

ImplAAFSequence::~ImplAAFSequence ()
{
	aafUInt32 count = _components.count();
	for (aafUInt32 i = 0; i < count; i++) {
		ImplAAFComponent *pComp = _components.clearValueAt(i);

		if (pComp) {
		  pComp->ReleaseReference();
		  pComp = 0;
		}
	}
}

//***********************************************************
//
// Initialize()
//
// This function sets the properties on a newly created sequence
// object with the given property values. The length of the sequence is
// initially set to 0.  When components are appended to the sequence with
// the AppendComponent() call, the length of the appended component is
// added to the length of the sequence.
// 
// Succeeds if all of the following are true:
// - the pDatadef pointer is valid.
// 
// If this method fails no state is changed.
// 
// This method will return the following codes.  If more than one of
// the listed errors is in effect, it will return the first one
// encountered in the order given below:
// 
// AAFRESULT_SUCCESS
//   - succeeded.  (This is the only code indicating success.)
//
// AAFRESULT_NULL_PARAM
//   - pDatadef is null.
// 
AAFRESULT STDMETHODCALLTYPE
    ImplAAFSequence::Initialize (ImplAAFDataDef * pDataDef)
{
  if (! pDataDef)
	return AAFRESULT_NULL_PARAM;

  return (SetDataDef(pDataDef));
}

//***********************************************************
//
// AppendComponent()
//
// This function appends the input component to the given sequence,
// enforcing bottom up creation of mobs.  The length of the sequence
// is incremented by the size of the component, unless the component
// is a transition.  If the component is a transition, it verifies
// that it is not the first object in a transition, and that it is
// not neighboring another transition.  It also verifies that there
// is enough source material on either side of the transition.  The
// function also verifies that the datadefs are compatible.
//
// If the component is successfully appended to the sequence, the
// reference count of the component is incremented.
// 
// Succeeds if all of the following are true:
// - the pComponent pointer is valid.
// 
// If this method fails no state is changed.
// 
// This method will return the following codes.  If more than one of
// the listed errors is in effect, it will return the first one
// encountered in the order given below:
// 
// AAFRESULT_SUCCESS
//   - succeeded.  (This is the only code indicating success.)
//
// AAFRESULT_NULL_PARAM
//   - pComponent is null.
//
// AAFRESULT_INVALID_DATADEF
//   - The data kind of the component is not compatible with the 
//     data kind of the sequence.
//
// AAFRESULT_LEADING_TRAN
//   - Attempted to append a transition as the first component of
//     a sequence.  A sequence can not start with a transition. 
//
// AAFRESULT_ADJACENT_TRAN
//   - Attempted to append a transition next to a transition.  A
//     sequence can not contain back to back transitions.
//
// AAFRESULT_INSUFF_TRAN_MATERIAL
//   - There is not enough source material to add this component.
//
// AAFRESULT_OBJECT_ALREADY_ATTACHED
//   - Attempted to append a component that is already attached to
//     (owned by) another object.
//
// AAFRESULT_EVENT_SEMANTICS
//   - Attempted to append an event to a non-event sequence or vice versa.
//	 - Attempted to append an event but an event type mismatched was found.
//   - Attempted to append an event that did not repect ordering conventions.
//
//
 
AAFRESULT STDMETHODCALLTYPE
    ImplAAFSequence::AppendComponent (ImplAAFComponent* pComponent)
{
	aafUInt32 count=0;
	AAFRESULT ar = AAFRESULT_SUCCESS;
	ar = CountComponents (&count);
	if (AAFRESULT_FAILED (ar)) 
	{
		return ar;
	}
	return InsertComponentAt(count, pComponent);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFSequence::PrependComponent (ImplAAFComponent* pComponent)
{
	if(!pComponent)
		return(AAFRESULT_NULL_PARAM);

	if (pComponent->attached())
			return AAFRESULT_OBJECT_ALREADY_ATTACHED;

	return  InsertComponentAt(0, pComponent);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFSequence::InsertComponentAt (aafUInt32 index,
										ImplAAFComponent* pComponent)
{
  if (!pComponent) 
    return AAFRESULT_NULL_PARAM;

  aafUInt32 count=0;
  AAFRESULT ar = AAFRESULT_SUCCESS;
  ar = CountComponents (&count);
  if (AAFRESULT_FAILED (ar)) 
  {
	  return ar;
  }

  if (index > count)
  {
	return AAFRESULT_BADINDEX;
  }

  if (pComponent->attached())
    return AAFRESULT_OBJECT_ALREADY_ATTACHED;

  ImplAAFDataDefSP sequDataDef, cpntDataDef;
  aafBool			willConvert = kAAFFalse;

  XPROTECT()
  {
    // Verify that component's datadef converts to sequence's datadef
	if(GetDataDef(&sequDataDef) == AAFRESULT_SUCCESS)
	{
		pComponent->GetDataDef(&cpntDataDef);
		CHECK(cpntDataDef->DoesDataDefConvertTo(sequDataDef, &willConvert));
	
		if (willConvert == kAAFFalse)
			RAISE(AAFRESULT_INVALID_DATADEF);
	}
	else
		SetDataDef(cpntDataDef); //This should never execute because the sequence the datadef must be set before manipulating the sequence.

	ImplAAFEvent* pEvent = dynamic_cast<ImplAAFEvent*>( pComponent );

	//index > count means an index = 0 and a count = 0, i.e. insert into an epmty list at index 0 is allowed.
	if (GetMobSlotType() == ImplAAFComponent::MobSlotType_Timeline)
	{
		if(pEvent)
		{
			CHECK( CheckTimelineSlotTypeSemantics( pEvent ) ); 
			CHECK( CheckTimelineSlotPositionSemantics( pEvent, index ) ); 
			CHECK( CheckTimelineSlotLengthSemantics( pEvent, index) ); 
			CHECK( UpdateSequenceLengthOnInsert( pEvent) ); // Treat as Component without Position!
		}
		else
		{
			CHECK( CheckTimelineSlotTypeSemantics( pComponent, index) );
			CHECK( CheckPositionSemantics( pComponent ) );
			CHECK( CheckLengthSemantics( pComponent, index) );
			CHECK( UpdateSequenceLengthOnInsert( pComponent ) );
		}
	}
	else if (GetMobSlotType() == ImplAAFComponent::MobSlotType_Static)
	{
		if(pEvent)
		{
			CHECK( CheckTypeSemantics( pEvent ) ); 
			CHECK( CheckStaticSlotPositionSemantics( pEvent, index ) ); 
			CHECK( CheckStaticSlotLengthSemantics( pEvent ) ); 
			CHECK( UpdateSequenceLengthOnInsert( pEvent, index ) ); 
		}
		else
		{
			CHECK( CheckTypeSemantics( pComponent, index) );
			CHECK( CheckPositionSemantics( pComponent ) );
			CHECK( CheckStaticSlotLengthSemantics( pComponent ) );
			CHECK( UpdateSequenceLengthOnInsert( pComponent ) );
		}
	}
	else if (GetMobSlotType() == ImplAAFComponent::MobSlotType_Event)
	{
		if(pEvent)
		{
			CHECK( CheckTypeSemantics( pEvent ) ); 
			CHECK( CheckPositionSemantics( pEvent, index ) ); 
			CHECK( CheckEventSlotLengthSemantics( pEvent, index ) ); 
			CHECK( UpdateSequenceLengthOnInsert( pEvent, index ) ); 
		}
		else
		{
			CHECK( CheckEventSlotTypeSemantics( pComponent, index ) );
			CHECK( CheckPositionSemantics( pComponent ) );
			CHECK( CheckLengthSemantics( pComponent, index ) );
			CHECK( UpdateSequenceLengthOnInsert( pComponent ) );
		}
	}
	else
	{
		if(pEvent)
		{
			CHECK( CheckTypeSemantics( pEvent ) ); 
			CHECK( CheckPositionSemantics( pEvent, index ) ); 
			CHECK( CheckEventSlotLengthSemantics( pEvent, index ) );
			CHECK( UpdateSequenceLengthOnInsert( pEvent, index ) ); 
		}
		else
		{
			CHECK( CheckTypeSemantics( pComponent, index) );
			CHECK( CheckPositionSemantics( pComponent ) );
			CHECK( CheckLengthSemantics( pComponent, index ) );
			CHECK( UpdateSequenceLengthOnInsert( pComponent ) );
		}
	}

	_components.insertAt(pComponent,index);
	pComponent->AcquireReference();
  }
  XEXCEPT
  {
  }
  XEND;

  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFSequence::GetComponentAt (aafUInt32 index,
									 ImplAAFComponent ** ppComponent)
{
  if (!ppComponent) 
    return AAFRESULT_NULL_PARAM;

  aafUInt32 count;
  AAFRESULT ar;
  ar = CountComponents (&count);
  if (AAFRESULT_FAILED (ar)) return ar;
  if (index >= count)
	return AAFRESULT_BADINDEX;

  ImplAAFComponent *pComponent = NULL;
  _components.getValueAt(pComponent,index);

  if (pComponent)
  {
	  pComponent->AcquireReference();
  }
  else
  {
	  return AAFRESULT_OBJECT_NOT_IN_FILE ;
  }

  (*ppComponent)=pComponent;

  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFSequence::RemoveComponentAt (aafUInt32 index)
{
  aafUInt32 count = 0;
  AAFRESULT hr = AAFRESULT_SUCCESS;
  hr = CountComponents (&count);
  if (AAFRESULT_FAILED (hr)) return hr;
  if (index >= count)
	return AAFRESULT_BADINDEX;

	ImplAAFComponent *pComp = NULL;
	pComp = 	_components.removeAt(index);
	ImplAAFEvent* pEvent = 0;
	pEvent = dynamic_cast<ImplAAFEvent*>( pComp );

	if (pComp)
	{
		if(count == 1)
		{
			//If count was 1 and we successfully removed an item, the list is now empty.
			aafLength_t dummy;
			//In order eveluation of and will not call GetLength when pEvent is 0.
			if (pEvent != 0 && 
				AAFRESULT_PROP_NOT_PRESENT == pEvent->GetLength(&dummy) )
 		    {
				//If the event didn't have length defined, do noting with the sequence length.
				//If the sequence had a component with length, which was previously removed,
				//and then a component without length is removed and there are no components
				//left in the sequence, should its length be 0 or undefined?
			}
			else hr = SetLength( 0 );
		}
		else
		{
			XPROTECT()
			{
				CHECK(UpdateSequenceLength());
			}
			XEXCEPT
			{
			}
			XEND;
		}
		// We have removed an element from a "stong reference container" so we must
		// decrement the objects reference count. This will not delete the object
		// since the caller must have alread acquired a reference. (transdel 2000-MAR-10)
		pComp->ReleaseReference ();
	}

	return hr;
}


//***********************************************************
//
// RemoveComponent()
//
// This function removes the input component from the given
// sequence, deleting it from any associated AAF file.  The length
// of the sequence is decremented by the size of the component.
// 
// Succeeds if all of the following are true:
// - the -pComponent pointer is valid.
// 
// If this method fails no state is changed.
// 
// This method will return the following codes.  If more than one of
// the listed errors is in effect, it will return the first one
// encountered in the order given below:
// 
// AAFRESULT_SUCCESS
//   - succeeded.  (This is the only code indicating success.)
//
// AAFRESULT_NULL_PARAM
//   - pComponent is null.
// 
AAFRESULT STDMETHODCALLTYPE
    ImplAAFSequence::RemoveComponent (ImplAAFComponent* pComponent)
{
	AAFRESULT status;

	if (!_components.containsValue(pComponent))
	  return AAFRESULT_BADINDEX;

	if (!pComponent->attached())
	  return AAFRESULT_OBJECT_NOT_ATTACHED;

	OMUInt32 index; 
	if(_components.findIndex(pComponent, index))
	{
		status = RemoveComponentAt(index);
	}
	else 
	{
		status = AAFRESULT_PARAMETER_NOT_FOUND;
	}

	return status;
}

//***********************************************************
//
// CountComponents()
//
// This function returns the number of components in the sequence.
// 
// Succeeds if all of the following are true:
// - the pNumCpnts pointer is valid.
// 
// If this method fails no state is changed.
// 
// This method will return the following codes.  If more than one of
// the listed errors is in effect, it will return the first one
// encountered in the order given below:
// 
// AAFRESULT_SUCCESS
//   - succeeded.  (This is the only code indicating success.)
//
// AAFRESULT_NULL_PARAM
//   - pNumCpnts is null.
// 
AAFRESULT STDMETHODCALLTYPE
    ImplAAFSequence::CountComponents (aafUInt32 * pNumCpnts)
{
  if (! pNumCpnts) return AAFRESULT_NULL_PARAM;

	aafUInt32 numCpnts = _components.count();
	*pNumCpnts = numCpnts;

	return AAFRESULT_SUCCESS;
}

//***********************************************************
//
// GetComponents()
//
// Places an IEnumAAFComponents enumerator for the components contained in the sequence
// into the *ppEnum argument.
// 
// Succeeds if all of the following are true:
// - the ppEnum pointer is valid.
// 
// If this method fails nothing will be written to *ppEnum.
// 
// This method will return the following codes.  If more than one of
// the listed errors is in effect, it will return the first one
// encountered in the order given below:
// 
// AAFRESULT_SUCCESS
//   - succeeded.  (This is the only code indicating success.)
//
// AAFRESULT_NULL_PARAM
//   - ppEnum is null.
//
// E_FAIL
//   - Failed to create the enumerator.
//
// 
AAFRESULT STDMETHODCALLTYPE
    ImplAAFSequence::GetComponents (ImplEnumAAFComponents ** ppEnum)
{
  if (NULL == ppEnum)
	return AAFRESULT_NULL_PARAM;
  *ppEnum = 0;
	
  ImplEnumAAFComponents *theEnum = (ImplEnumAAFComponents *)CreateImpl (CLSID_EnumAAFComponents);
	
  XPROTECT()
	{
		OMStrongReferenceVectorIterator<ImplAAFComponent>* iter = 
			new OMStrongReferenceVectorIterator<ImplAAFComponent>(_components);
		if(iter == 0)
			RAISE(AAFRESULT_NOMEMORY);
		CHECK(theEnum->Initialize(&CLSID_EnumAAFComponents, this, iter));
	  *ppEnum = theEnum;
	}
  XEXCEPT
	{
	  if (theEnum)
		{
		  theEnum->ReleaseReference();
		  theEnum = 0;
		}
	}
  XEND;

	return(AAFRESULT_SUCCESS);
}


//***********************************************************
//
// SegmentOffsetToTC()
//
// Converts the given Segment offset to timecode.
// 
// Succeeds if all of the following are true:
// - the pOffset pointer is valid.
// - the pTimeCode pointer is valid.
// 
// If this method fails the value of pTimecode is left unchanged.
// 
// This method will return the following codes.  If more than one of
// the listed errors is in effect, it will return the first one
// encountered in the order given below:
// 
// AAFRESULT_SUCCESS
//   - succeeded.  (This is the only code indicating success.)
//
// AAFRESULT_NULL_PARAM
//   - any arg is NULL.
// 
// Override from AAFSegment
AAFRESULT STDMETHODCALLTYPE
ImplAAFSequence::SegmentOffsetToTC (aafPosition_t*  pOffset,
									aafTimecode_t*  pTimecode)
{
	ImplAAFTimecode*	pTC = NULL;
	aafPosition_t		sequPos;
	HRESULT				hr = AAFRESULT_SUCCESS;

	if (pOffset == NULL || pTimecode == NULL)
		return AAFRESULT_NULL_PARAM;

	hr = OffsetToTimecodeClip(*pOffset, &pTC, &sequPos);
	if(SUCCEEDED(hr))
	{
		aafTimecode_t timecode;

 		hr = pTC->GetTimecode(&timecode);
		if (SUCCEEDED(hr))
		{
			aafPosition_t	offset = *pOffset;

			offset -= sequPos;
			timecode.startFrame += offset;

			*pTimecode = timecode;
		}
		pTC->ReleaseReference();
		pTC = 0;
	}

	return hr;
}

//***********************************************************
//
// SegmentTCToOffset()
//
// Converts the given Timecode to an Offset.
// 
// Succeeds if all of the following are true:
// - the pTimeCode pointer is valid.
// - the pEditRate pointer is valid
// - the pFrameOffset pointer is valid.
// 
// If this method fails the value of pOffset is left unchanged.
// 
// This method will return the following codes.  If more than one of
// the listed errors is in effect, it will return the first one
// encountered in the order given below:
// 
// AAFRESULT_SUCCESS
//   - succeeded.  (This is the only code indicating success.)
//
// AAFRESULT_NULL_PARAM
//   - any arg is NULL.
// 
// Override from AAFSegment
AAFRESULT STDMETHODCALLTYPE
ImplAAFSequence::SegmentTCToOffset (aafTimecode_t*		pTimecode,
									aafRational_t*		pEditRate,
									aafFrameOffset_t*	pOffset)
{
	aafTimecode_t		startTC;
	ImplAAFComponent*	pComponent;
	ImplAAFSegment*		pSegment;
	HRESULT				hr = AAFRESULT_SUCCESS;
	aafLength_t			segLen, tcLen;
	ImplAAFTimecode*	pTC;
	aafFrameOffset_t	begPos, endPos;
	aafPosition_t		sequPos, segStart;
	aafBool				found = kAAFFalse;
	aafLength_t			junk;

	if (pOffset == NULL || pTimecode == NULL || pEditRate == NULL)
		return AAFRESULT_NULL_PARAM;

	segStart = 0;
	junk = 0;

	aafUInt32 numCpnts = _components.count();
	for (aafUInt32 index=0; index < numCpnts; index++)
	{
		ImplAAFSourceClip*	pSubSegment;
		aafBool			isMask;
		implCompType_t	type;

		_components.getValueAt(pComponent, index);

		pComponent->GetComponentType(&type);
		if (type == kTransition)
			continue;

		pSegment = static_cast<ImplAAFSegment*> (pComponent);

		/// !!!Jeff B - this needs some work for FILM
		hr = pSegment->TraverseToClip(junk, &pSubSegment, NULL, NULL, &junk, &isMask);
		if (SUCCEEDED(hr))
		{
			hr = pSubSegment->GetLength(&segLen);
			if (SUCCEEDED(hr))
			{
				if (segLen == 0)
					continue;		// Skip zero-length clips, sometimes found in MC files
				if (segLen == AAF_UNKNOWN_LENGTH)
					continue;		// Skip unknown-length clips

	 			pTC = (ImplAAFTimecode *)pSubSegment;
	 			pTC->GetTimecode(&startTC);
				begPos = startTC.startFrame;
				endPos = startTC.startFrame + segLen;
				if ((pTimecode->startFrame < endPos) && (begPos <= pTimecode->startFrame))
				{
					pComponent->AccumulateLength(&sequPos);
  					segStart = sequPos;
					pTC->GetLength(&tcLen);
					found = kAAFTrue;
					break;
				}
			}
			pSubSegment->ReleaseReference();
			pSubSegment = 0;
		}
	}
	
	if (found)
	{
		aafPosition_t	newStart, oldStart;

		// Assume found at this point, so finish generating result
		oldStart = (pTimecode->startFrame - startTC.startFrame) + segStart;
		hr = AAFConvertEditRate(*pEditRate, oldStart, *pEditRate, kRoundFloor, &newStart);
		*pOffset = newStart - sequPos;

		// check for out of bound timecode
		if (pTimecode->startFrame < startTC.startFrame) 
		{
			// out of left bound 
			hr = AAFRESULT_BADSAMPLEOFFSET;
		}
		else
		{
			if (pTimecode->startFrame > (startTC.startFrame + tcLen))
			{
				// out of right bound
				 hr = AAFRESULT_BADSAMPLEOFFSET;
			}
		}
	}
	else
		hr = AAFRESULT_TIMECODE_NOT_FOUND;

	return hr;
}

//***************************************************************
//
// FindSubSeqment
//
// Gets a segment on the sequence. 
//
//
//
AAFRESULT ImplAAFSequence::FindSubSegment(aafPosition_t offset, 
										 aafMediaCriteria_t * /*mediaCrit*/,
										 aafPosition_t *sequPosPtr,
										 ImplAAFSegment **subseg,
										 aafBool *found)
{
	aafLength_t	segLen;
	aafPosition_t begPos, endPos, zero;
	aafUInt32 n = 0;
	ImplAAFSegment* seg = NULL;

	XPROTECT( )
	{
		CHECK(GetOptionalLength(this, &segLen));
		begPos = 0;
		zero = 0;
		if (segLen != AAF_UNKNOWN_LENGTH)
		{
			endPos = begPos;
			endPos += segLen;
			if (begPos <= offset &&
				offset < endPos)
			{
				*found = kAAFFalse;
				*subseg = NULL;
				*sequPosPtr = 0;
				begPos = 0;
				endPos = begPos;
				CHECK(CountComponents(&n));
				for (aafUInt32 i = 0 ; *found != kAAFTrue && i < n ; i++) 
				{
					CHECK(GetComponentAt(i, (ImplAAFComponent**)&seg));
					CHECK(GetOptionalLength(seg, &segLen));
					endPos += segLen;
					if (begPos <= offset &&
						offset < endPos)
					{
						*found = kAAFTrue;
						*subseg = seg;
						// We are returning a reference to this object so bump the ref count
						seg->AcquireReference();
						*sequPosPtr = begPos;
					} 
					else 
					{
						begPos = endPos;
					}
					seg->ReleaseReference();
					seg = NULL;
				}
			}
			else if ((begPos == endPos) && (offset == zero)) 	//JeffB: Handle zero-length sourceClips
			{
				*found = kAAFFalse;
				*subseg = NULL;
				*sequPosPtr = 0;
				CHECK(CountComponents(&n));
				if (n > 0)
				{
					CHECK(GetComponentAt(0, (ImplAAFComponent**)&seg));
					CHECK(GetOptionalLength(seg, &segLen));
					if (segLen == 0)
					{
						*found = kAAFTrue;
						*subseg = seg;
						seg->AcquireReference();
						*sequPosPtr = 0;
					}
					seg->ReleaseReference();
					seg = NULL;
				}
			}
			else
			{
				*found = kAAFFalse;
				*subseg = NULL;
				*sequPosPtr = 0;
			}
		}
		else
		{
			if (begPos <= offset)
			{
				*found = kAAFFalse;
				*subseg = NULL;
				*sequPosPtr = 0;
				begPos = 0;
				endPos = begPos;
				CHECK(CountComponents(&n));
				for (aafUInt32 i = 0 ; *found != kAAFTrue && i < n ; i++) 
				{
					CHECK(GetComponentAt(i, (ImplAAFComponent**)&seg));
					CHECK(GetOptionalLength(seg, &segLen));
					if (segLen != AAF_UNKNOWN_LENGTH)
					{
						endPos += segLen;
						if (begPos <= offset &&
							offset < endPos)
						{
							*found = kAAFTrue;
							*subseg = seg;
							// We are returning a reference to this object so bump the ref count
							seg->AcquireReference();
							*sequPosPtr = begPos;
						} 

						begPos = endPos;
					}
					else
					{
						if (begPos <= offset)
						{
							*found = kAAFTrue;
							*subseg = seg;
							// We are returning a reference to this object so bump the ref count
							seg->AcquireReference();
							*sequPosPtr = begPos;
						}
					}
					seg->ReleaseReference();
					seg = NULL;
				}
			}
			else
			{
				*found = kAAFFalse;
				*subseg = NULL;
				*sequPosPtr = 0;
			}
		}
	} /* XPROTECT */
	XEXCEPT
	{
		if (seg) {
			seg->ReleaseReference();
			seg = NULL;
		}
	}
	XEND;

	return(AAFRESULT_SUCCESS);
}

//***********************************************************
//
// GetNthComponent()
//
// Get the component at the position specified by index from
// the components vector.  This is used by the ImplEnumAAFComponents
// to retrieve the components from the sequence.
//
// NOTES:
//
//    - The vector is 0-based.
//    - AddRef the object being returned.
// 
AAFRESULT
    ImplAAFSequence::GetNthComponent (aafUInt32 index, ImplAAFComponent** ppComponent)
{
	ImplAAFComponent*	obj;
	HRESULT				hr;

	size_t numCpnts = _components.count();
	if (index < numCpnts)
	{
		_components.getValueAt(obj, index);
		obj->AcquireReference();
		*ppComponent = obj;
		hr =  AAFRESULT_SUCCESS;
	}
	else
		hr = AAFRESULT_NO_MORE_OBJECTS;

	return hr;
}

AAFRESULT ImplAAFSequence::ChangeContainedReferences(aafMobID_constref from,
													 aafMobID_constref to)
{
	aafUInt32			n, count;
	ImplAAFComponent	*comp = NULL;
	
	XPROTECT()
	{
		CHECK(CountComponents (&count));
		for(n = 0; n < count; n++)
		{
			CHECK(GetNthComponent (n, &comp));
			CHECK(comp->ChangeContainedReferences(from, to));
			comp->ReleaseReference();
			comp = NULL;
		}
	}
	XEXCEPT
	{
		if(comp != NULL)
		  comp->ReleaseReference();
		comp = 0;
	}
	XEND;

	return AAFRESULT_SUCCESS;
}

AAFRESULT ImplAAFSequence::GetMinimumBounds(aafPosition_t rootPos, aafLength_t rootLen,
											ImplAAFMob *mob, ImplAAFMobSlot *track,
											aafMediaCriteria_t *mediaCrit,
											aafPosition_t currentObjPos,
											aafOperationChoice_t *effectChoice,
											ImplAAFComponent	*prevObject,
											ImplAAFComponent *nextObject,
											ImplAAFScopeStack *scopeStack,
											aafPosition_t *diffPos, aafLength_t *minLength,
											ImplAAFOperationGroup **effeObject, aafInt32	*nestDepth,
											ImplAAFComponent **foundObj, aafBool *foundTransition)
{
	aafUInt32			count = 0;
	ImplAAFSegment		*seg = NULL;
	ImplAAFComponent	*tmpFound = NULL;
	aafLength_t			tmpMinLen = 0;

	aafPosition_t		sequOffset = 0;
	ImplAAFSegment		*subseg = NULL;
	aafBool				found = kAAFFalse;
	aafLength_t			subsegLen = 0;

	XPROTECT()
	{
		CHECK(FindSubSegment(rootPos, mediaCrit,
							&sequOffset, &subseg,
							&found));
		if (found)
		{
			CHECK(GetOptionalLength(subseg, &subsegLen));

			// TODO:
			// The existing implementations of GetMinimumBounds() in ImplAAFComponent,
			// ImplAAFSelector, and ImplAAFEssenceGroup call MobFindLeaf() to traverse
			// the sub-component. But all MobFindLeaf() does is call sub-component's
			// GetMinimumBounds(). It seems that it would be more appropriare to call
			// GetMinimumBounds() directly, right here. This would also allow to remove
			// a dependency on ImplAAFMob.h.
			CHECK(mob->MobFindLeaf(track, mediaCrit, effectChoice,
									subseg, sequOffset, subsegLen,
									prevObject, nextObject, 
									scopeStack, 
									currentObjPos, &tmpFound, &tmpMinLen, foundTransition,
									effeObject, nestDepth, diffPos));
		}

		if(diffPos != NULL)
		{
			*diffPos = rootPos - sequOffset;
		}	
		if (tmpFound)
		{
			*foundObj = tmpFound;
			if (rootLen != AAF_UNKNOWN_LENGTH && tmpMinLen != AAF_UNKNOWN_LENGTH)
			{
				if (tmpMinLen < rootLen)
					*minLength = tmpMinLen;
				else
					*minLength = rootLen;
			}
			else
			{
				// One if the legths is unknown (-1)
				if (tmpMinLen != AAF_UNKNOWN_LENGTH)
				{
					XASSERT(rootLen == AAF_UNKNOWN_LENGTH, AAFRESULT_INTERNAL_ERROR);
					*minLength = tmpMinLen;
				}
				else
				{
					XASSERT(tmpMinLen == AAF_UNKNOWN_LENGTH, AAFRESULT_INTERNAL_ERROR);
					*minLength = rootLen;
				}
			}
		}
		else
		{
			RAISE(AAFRESULT_TRAVERSAL_NOT_POSS);
		}
	}
	XEXCEPT
	{
	}
	XEND;

	if( subseg != NULL )
		subseg->ReleaseReference();
	if( seg != NULL )
		seg->ReleaseReference();
	
	return(AAFRESULT_SUCCESS);
}

//SDK Internal
AAFRESULT
    ImplAAFSequence::SetNthComponent (aafUInt32 index, ImplAAFComponent* pComponent)
{
	HRESULT				hr;


	if( pComponent == NULL )
		return AAFRESULT_NULL_PARAM;

	size_t numCpnts = _components.count();
	if (index < numCpnts)
	{
		// Retreive the old component
		// If it's the same as one we are setting just return success.
		//
		ImplAAFComponent	*pOldComponent = NULL;
		_components.getValueAt( pOldComponent, index );
		ASSERTU(pOldComponent);
		if( pOldComponent != NULL && pOldComponent == pComponent )
			return AAFRESULT_SUCCESS;

		// Make sure the new component is not already in use.
		if (pComponent->attached())
			return AAFRESULT_OBJECT_ALREADY_ATTACHED;

		if( pOldComponent != NULL )
		    pOldComponent->ReleaseReference();

		_components.setValueAt(pComponent, index);
		pComponent->AcquireReference();
		hr =  AAFRESULT_SUCCESS;
	}
	else
		hr = AAFRESULT_NO_MORE_OBJECTS;

	return hr;
}

AAFRESULT ImplAAFSequence::TraverseToClip(aafLength_t length,
											ImplAAFSourceClip **sclp,
											ImplAAFPulldown ** /*pulldownObj*/,
											aafInt32 * /*pulldownPhase*/,
											aafLength_t *sclpLen,
											aafBool * /*isMask*/)
{
	XPROTECT()
	{
		aafUInt32	count = 0;
		CHECK(CountComponents( &count ));
		if( count != 1 )
		    return(AAFRESULT_TRAVERSAL_NOT_POSS);

		ImplAAFComponent *p_component = NULL;
		CHECK(GetComponentAt( 0, &p_component ));

		ImplAAFSourceClip *p_src_clip = dynamic_cast<ImplAAFSourceClip*>( p_component );
		if( !p_src_clip )
		{
		    p_component->ReleaseReference();
		    p_component = NULL;
		    return(AAFRESULT_TRAVERSAL_NOT_POSS);
		}

		*sclp = p_src_clip;

		CHECK(GetOptionalLength((*sclp), sclpLen));
		if (length != AAF_UNKNOWN_LENGTH && *sclpLen != AAF_UNKNOWN_LENGTH)
		{
			if (length < *sclpLen)
			{
				*sclpLen = length;
			}
		}
		else
		{
			if (length != AAF_UNKNOWN_LENGTH)
			{
				XASSERT(*sclpLen == AAF_UNKNOWN_LENGTH, AAFRESULT_INTERNAL_ERROR);
				*sclpLen = length;
			}
		}
	} /* XPROTECT */
	
	XEXCEPT
	{
	}
	XEND;
	
	return(AAFRESULT_SUCCESS);
}

//***********************************************************
//

ImplAAFComponent* ImplAAFSequence::GetLastComponent()
{
	ImplAAFComponent* pComponent = 0;

	_components.getValueAt(pComponent, _components.count()-1 );	

	return pComponent;
}

ImplAAFComponent* ImplAAFSequence::GetFirstComponent()
{
	ImplAAFComponent* pComponent = 0;

	_components.getValueAt(pComponent, 0 );

	return pComponent;
}

AAFRESULT ImplAAFSequence::GetLastEvent(ImplAAFEvent*& pLastEvent )
{
	AAFRESULT status = AAFRESULT_SUCCESS;

	ImplAAFEvent* pEvent = dynamic_cast<ImplAAFEvent*>( GetLastComponent() );
	if ( pEvent ) {
		pLastEvent = pEvent;
	}
	else {
		status = AAFRESULT_EVENT_SEMANTICS;
	}

	return status;
}

AAFRESULT ImplAAFSequence::GetFirstEvent(ImplAAFEvent*& pFirstEvent )
{
	AAFRESULT status = AAFRESULT_SUCCESS;

	ImplAAFEvent* pEvent = dynamic_cast<ImplAAFEvent*>( GetFirstComponent() );
	if ( pEvent ) {
		pFirstEvent = pEvent;
	}
	else {
		status = AAFRESULT_EVENT_SEMANTICS;
	}
	
	return status;
}
                           
ImplAAFEvent* ImplAAFSequence::FindLastEvent() const
{
	ImplAAFEvent* pEvent = NULL;

	const aafUInt32 count = _components.count();
	for (aafUInt32 i = count; i > 0; i--) {
		ImplAAFComponent *pComp = NULL;
		_components.getValueAt(pComp, i-1);
		pEvent = dynamic_cast<ImplAAFEvent*>(pComp);
		if (pEvent) {
			break;
		}
	}

	return pEvent;
}

ImplAAFEvent* ImplAAFSequence::FindNextEvent(aafUInt32 index) const
{
	ImplAAFEvent* pEvent = NULL;

	for (aafUInt32 i = index; i < _components.count(); i++) {
		ImplAAFComponent *pComp = NULL;
		_components.getValueAt(pComp, i);
		pEvent = dynamic_cast<ImplAAFEvent*>(pComp);
		if (pEvent) {
			break;
		}
	}

	return pEvent;
}

ImplAAFEvent* ImplAAFSequence::FindPreviousEvent(aafUInt32 index) const
{
	ImplAAFEvent* pEvent = NULL;

	if (index > _components.count()) {
		index = _components.count();
	}

	for (aafUInt32 i = index; i > 0; i--) {
		ImplAAFComponent *pComp = NULL;
		_components.getValueAt(pComp, i-1);
		pEvent = dynamic_cast<ImplAAFEvent*>(pComp);
		if (pEvent) {
			break;
		}
	}

	return pEvent;
}

bool ImplAAFSequence::ContainsEvents() const
{
	bool foundEvent = false;

	const aafUInt32 count = _components.count();
	for (aafUInt32 i = 0; i < count; i++) {
		ImplAAFComponent *pComp = NULL;
		_components.getValueAt(pComp, i);
		if (dynamic_cast<ImplAAFEvent*>(pComp)) {
			foundEvent = true;
			break;
		}
	}

	return foundEvent;
}

bool ImplAAFSequence::ContainsNonFillers() const
{
	bool foundNonFiller = false;

	const aafUInt32 count = _components.count();
	for (aafUInt32 i = 0; i < count; i++) {
		ImplAAFComponent *pComp = NULL;
		_components.getValueAt(pComp, i);
		if (!dynamic_cast<ImplAAFFiller*>(pComp) &&
			!dynamic_cast<ImplAAFEvent*>(pComp)) {
			foundNonFiller = true;
			break;
		}
	}

	return foundNonFiller;
}

bool ImplAAFSequence::ContainsNonEvents() const
{
	bool foundNonEvent = false;

	const aafUInt32 count = _components.count();
	for (aafUInt32 i = 0; i < count; i++) {
		ImplAAFComponent *pComp = NULL;
		_components.getValueAt(pComp, i);
		if (!dynamic_cast<ImplAAFEvent*>(pComp)) {
			foundNonEvent = true;
			break;
		}
	}

	return foundNonEvent;
}

// ImplAAFSequence private - Event sematics

AAFRESULT ImplAAFSequence::CheckTypeSemantics( ImplAAFEvent* pEvent )
{
	// In most general case (StaticMobSlot) a Sequence can mix Events and
	// non-Events.

	// No restrictions for a first sequence component.
	if (_components.count() == 0) {
		return AAFRESULT_SUCCESS;
	}

	// If Sequence contains Events they must be of the same type
	ImplAAFEvent* pLastEvent = FindLastEvent();
	if (pLastEvent)
	{
		// Haven't seen any rules against use of typeid(), and there
		// are already dynamic_casts all over the place... so let's
		// get with times here and use type_info equality to verify
		// concrete type identity.

// Ugly workaround for x86 optimisation bug in gcc-3.3.x
// The bug is not present in gcc-3.2.x or gcc-3.4.x
#if defined(__i386__) && __GNUC__ == 3 && __GNUC_MINOR__ == 3
		const char *comp_name = typeid(*pLastEvent).name();
		const char *event_name = typeid(*pEvent).name();
		if ( strcmp(comp_name, event_name) != 0 ) {
			return AAFRESULT_EVENT_SEMANTICS;
		}
#else
		if ( typeid( *pLastEvent ) != typeid( *pEvent) ) {
			return AAFRESULT_EVENT_SEMANTICS;
		}
#endif
	}

	return AAFRESULT_SUCCESS;
}

AAFRESULT ImplAAFSequence::CheckPositionSemantics( ImplAAFEvent* pEvent, aafUInt32 index )
{
	//Events must be in order by position.

	AAFRESULT status;

	ImplAAFEvent* pEventPrior = FindPreviousEvent(index);
	ImplAAFEvent* pEventNext = FindNextEvent(index);

	aafPosition_t posNew;
	status = pEvent->GetPosition( &posNew );
	if ( AAFRESULT_SUCCESS != status ) {
		return status;
	}

	if(pEventPrior != 0)
	{
		aafPosition_t posPrior;
		status = pEventPrior->GetPosition( &posPrior );
		if ( AAFRESULT_SUCCESS != status ) return status;

		if ( posPrior > posNew ) return AAFRESULT_EVENT_SEMANTICS;
	}

	if(pEventNext != 0)
	{
		aafPosition_t posNext;
		status = pEventNext->GetPosition( &posNext );
		if ( AAFRESULT_SUCCESS != status ) return status;

		if ( posNext < posNew ) return AAFRESULT_EVENT_SEMANTICS;
	}

	return AAFRESULT_SUCCESS;
}


AAFRESULT ImplAAFSequence::CheckEventSlotLengthSemantics( ImplAAFEvent* pEvent, aafUInt32 index )
{
	// The length property is optional on events.
	// If it is specified, overlap may occur. Hence, nothing to verify.

	// No restrictions for a first sequence component.
	if (_components.count() == 0)
	{
		return AAFRESULT_SUCCESS;
	}

	AAFRESULT hr = AAFRESULT_SUCCESS;

	ImplAAFComponent* pEventLast = GetLastComponent();

	// The length property is optional on events.
	aafLength_t lengthLast = 0;
	hr = pEventLast->GetLength(&lengthLast);
	if (hr == AAFRESULT_SUCCESS)
	{
		// cannot append anything after a last component with unknown length
		if (lengthLast == AAF_UNKNOWN_LENGTH && index == _components.count())
		{
			return AAFRESULT_INVALID_PARAM;
		}
	}
	else if (hr == AAFRESULT_PROP_NOT_PRESENT)
	{
		// Nothing to check here.
	}
	else
	{
		return AAFRESULT_BAD_LENGTH;
	}

	// The length property is optional on events.
	aafLength_t length = 0;
	hr = pEvent->GetLength(&length);
	if (hr == AAFRESULT_SUCCESS)
	{
		// component with unknown length can be only added to the end
		if (length == AAF_UNKNOWN_LENGTH && index != _components.count())
		{
			return AAFRESULT_INVALID_PARAM;
		}
	}
	else if (hr == AAFRESULT_PROP_NOT_PRESENT)
	{
		// Nothing to check here.
	}
	else
	{
		return AAFRESULT_BAD_LENGTH;
	}

	return AAFRESULT_SUCCESS;
}

AAFRESULT ImplAAFSequence::UpdateSequenceLength()
{
	AAFRESULT status;

	aafLength_t dummy = 0;
	status = GetLength(&dummy);
	if (status != AAFRESULT_SUCCESS && status != AAFRESULT_PROP_NOT_PRESENT)
		return status;

	aafLength_t sequenceLength = 0;
	bool sequenceLengthPresent = status != AAFRESULT_PROP_NOT_PRESENT;

	bool nonEventsSemantics = true;
	if (GetMobSlotType() == ImplAAFComponent::MobSlotType_Timeline)
	{
		// treat Events as Component without Position!
		nonEventsSemantics = true;
		sequenceLengthPresent = true;
	}
	else if (GetMobSlotType() == ImplAAFComponent::MobSlotType_Static)
	{
		// if a	Component is in a StaticMobSlot then it shall not have a Length property set
		return AAFRESULT_SUCCESS;
	}
	else if (GetMobSlotType() == ImplAAFComponent::MobSlotType_Event)
	{
		nonEventsSemantics = false;
	}
	else
	{
		// ignore position of Events if the sequence contains non-Events.
		nonEventsSemantics = ContainsNonEvents();
	}

	aafLength_t lastLength = 0;
	status = GetOptionalLength(GetLastComponent(), &lastLength);
	if (status != AAFRESULT_SUCCESS)
		return status;

	if (_components.count() == 0)
	{
		sequenceLength = 0;
	}
	else if (lastLength == AAF_UNKNOWN_LENGTH)
	{
		// only last Component in a Sequence is allowed to be of Unknown Length (-1)
		// when this is the case then a Sequence length is also of Unknown Length (-1)
		sequenceLength = AAF_UNKNOWN_LENGTH;
		sequenceLengthPresent = true;
	}
	else
	{
		// The length of the Sequence shall be equal to
		// the sum of the length of all Segments directly owned by the Sequence
		// minus the sum of the lengths of all Transitions directly owned by the Sequence.
		for (aafUInt32 index = 0; index < _components.count(); index++)
		{
			ImplAAFComponent* pComponent = NULL;
			_components.getValueAt(pComponent, index);

			aafLength_t compLength = 0;
			status = pComponent->GetLength(&compLength);
			if (status != AAFRESULT_SUCCESS && status != AAFRESULT_PROP_NOT_PRESENT)
				return status;

			if (status != AAFRESULT_PROP_NOT_PRESENT)
				sequenceLengthPresent = true;

			if (nonEventsSemantics)
			{
				if (dynamic_cast<ImplAAFTransition*>(pComponent))
					sequenceLength -= compLength;
				else
					sequenceLength += compLength;
			}
			else
			{
				static aafPosition_t posFirst = 0;
				static aafPosition_t posLast = 0;

				ImplAAFEvent* pEvent = dynamic_cast<ImplAAFEvent*>(pComponent);

				if (!pEvent)
					return AAFRESULT_EVENT_SEMANTICS;

				aafPosition_t compPosition;
				status = pEvent->GetPosition(&compPosition);
				if (AAFRESULT_SUCCESS != status)
					return status;

				if (index == 0)
				{
					posFirst = compPosition;
					sequenceLength = compLength;
				}
				else
				{
					aafLength_t eventLength = compPosition + compLength;
					if (eventLength > sequenceLength)
						posLast = eventLength;

					if (index == (_components.count() - 1))
					{
						sequenceLength = posLast - posFirst;
					}
				}
			}
		}
	}

	if (sequenceLengthPresent)
	{
		status = SetLength(sequenceLength);
		if (AAFRESULT_SUCCESS != status)
			return status;
	}

	return AAFRESULT_SUCCESS;
}

AAFRESULT ImplAAFSequence::UpdateSequenceLengthOnInsert( ImplAAFEvent* pEvent, aafUInt32 index)
{
	aafLength_t newEndPoint = 0;

	aafLength_t dummy;
	if ( AAFRESULT_PROP_NOT_PRESENT == GetLength(&dummy) &&
 		 AAFRESULT_PROP_NOT_PRESENT == pEvent->GetLength(&dummy) ) {
		return AAFRESULT_SUCCESS;
	}


    AAFRESULT status;

	aafPosition_t posNext;
	status = pEvent->GetPosition( &posNext );
	if ( AAFRESULT_SUCCESS != status ) {
		return status;
	}

	aafLength_t lengthNext;
	status = GetOptionalLength( pEvent, &lengthNext );
	if ( AAFRESULT_SUCCESS != status ) {
		return status;
	}

	if ( _components.count() == 0 ) {

		status = SetLength( lengthNext );
		if ( AAFRESULT_SUCCESS != status ) {
			return status;
		}

	}
	else if ( this->ContainsNonEvents() ) {
		// Ignore position of Events if the sequence contains non-Events.
		ImplAAFComponent* pComponent = pEvent;
		UpdateSequenceLengthOnInsert( pComponent );
	}
	else {
		ImplAAFEvent* pFirstEvent;
		status = GetFirstEvent( pFirstEvent );
		if ( AAFRESULT_SUCCESS != status ) {
			return status;
		}

		aafPosition_t posFirst;
		status = pFirstEvent->GetPosition( &posFirst );
		if ( AAFRESULT_SUCCESS != status ) {
			return status;
		}

		aafLength_t seqLength;
		status = GetOptionalLength( this, &seqLength );
		if ( AAFRESULT_SUCCESS != status ) {
			return status;
		}

		if (lengthNext == AAF_UNKNOWN_LENGTH || seqLength == AAF_UNKNOWN_LENGTH)
		{
			seqLength = AAF_UNKNOWN_LENGTH;
		}
		else
		{
			aafLength_t endPoint = (lengthNext + posNext) - posFirst;
			if (endPoint > seqLength)
			{
				newEndPoint = endPoint;
			}
			else
			{
				newEndPoint = seqLength;
			}

			if (index == 0)
			{
				if (posNext > posFirst)
					seqLength = newEndPoint;
				else
					seqLength = newEndPoint + (posFirst - posNext);
			}
			else
			{
				seqLength = newEndPoint;
			}
		}

		status = SetLength(seqLength);
		if (AAFRESULT_SUCCESS != status)
		{
			return status;
		}
	}

	return status;
}


AAFRESULT ImplAAFSequence::CheckTypeSemantics( ImplAAFComponent* pComponent, aafUInt32 index) 
{
	ImplAAFTransition* pTransition = dynamic_cast<ImplAAFTransition*>(pComponent);

	if (pTransition) 
	{ 
		// The first component in a sequence must *not* be of type Transition.
		if (index == 0)
		{
			return AAFRESULT_LEADING_TRAN;
		}

		// Reject adjacent transitions
		if (index > 0)
		{
			ImplAAFComponent* pComponentPrior = 0;
			_components.getValueAt(pComponentPrior, index - 1);
			if (dynamic_cast<ImplAAFTransition*>(pComponentPrior))
			{
				return AAFRESULT_ADJACENT_TRAN;
			}
		}

		// Reject adjacent transitions
		if (_components.count() > index)
		{
			ImplAAFComponent* pComponentNext = 0;
			// Existing values in this <c OMVector> at <p index> and higher are shifted up one index position on insert.
			_components.getValueAt(pComponentNext, index);
			if (dynamic_cast<ImplAAFTransition*>(pComponentNext))
			{
				return AAFRESULT_ADJACENT_TRAN;
			}
		}
	}

	return AAFRESULT_SUCCESS;
}

AAFRESULT ImplAAFSequence::CheckPositionSemantics( ImplAAFComponent* /*pComponent*/ )
{
	// There is nothing to check for a non-event.

	// One could check that the cut point is valid.

	return AAFRESULT_SUCCESS;
}

AAFRESULT ImplAAFSequence::CheckLengthSemantics( ImplAAFComponent* pComponentNext, aafUInt32 index )
{
	// Length properties are not optional for components and transitions.
	aafLength_t lengthNext = 0;
	if (pComponentNext->GetLength(&lengthNext) == AAFRESULT_PROP_NOT_PRESENT)
	{
		return AAFRESULT_BAD_LENGTH;
	}

	// No restrictions for a first sequence component.
	if (_components.count() == 0) {
		return AAFRESULT_SUCCESS;
	}

	// component with unknown length can be only added to the end
	if (lengthNext == AAF_UNKNOWN_LENGTH && index != _components.count())
	{
		return AAFRESULT_INVALID_PARAM;
	}

	ImplAAFComponent* pComponentLast = GetLastComponent();

	// Length properties are not optional for components and transitions.
	aafLength_t lengthLast = 0;
	if (pComponentLast->GetLength(&lengthLast) == AAFRESULT_PROP_NOT_PRESENT)
	{
		return AAFRESULT_BAD_LENGTH;
	}

	// cannot append anything after a last component with unknown length
	if (lengthLast == AAF_UNKNOWN_LENGTH && index == _components.count())
	{
		return AAFRESULT_INVALID_PARAM;
	}

	// If either the new component, or the last component in the sequence, is a transition,
	// then verify they fully overlap.
	ImplAAFTransition* pTransitionNext = dynamic_cast<ImplAAFTransition*>(pComponentNext);
	ImplAAFTransition* pTransitionLast = dynamic_cast<ImplAAFTransition*>(pComponentLast);
	bool overstepNext = pTransitionNext && (lengthNext == AAF_UNKNOWN_LENGTH || lengthLast < lengthNext);
	bool overstepLast = pTransitionLast && (lengthLast == AAF_UNKNOWN_LENGTH || lengthNext < lengthLast);
	if (overstepNext || overstepLast)
	{
		return AAFRESULT_INSUFF_TRAN_MATERIAL;
	}
	
	return AAFRESULT_SUCCESS;
}

AAFRESULT ImplAAFSequence::CheckTimelineSlotTypeSemantics( ImplAAFEvent* pEvent )
{
	AAFRESULT status = AAFRESULT_SUCCESS;

	if (_components.count() > 0)
	{
		if (this->ContainsNonFillers())
		{
			status = AAFRESULT_EVENT_SEMANTICS;
		}
	}

	if (AAFRESULT_SUCCEEDED(status))
	{
		status = CheckTypeSemantics(pEvent);
	}

	return status;
}

AAFRESULT ImplAAFSequence::CheckTimelineSlotPositionSemantics( ImplAAFEvent* pEvent, aafUInt32 /*index*/ )
{
	aafPosition_t position = 0;
	AAFRESULT status = pEvent->GetPosition(&position);

	// Treat Position property with zero value as not present
	if (AAFRESULT_SUCCEEDED(status) && position == 0)
		status = AAFRESULT_PROP_NOT_PRESENT;

	if (status == AAFRESULT_PROP_NOT_PRESENT)
		return AAFRESULT_SUCCESS;

	return AAFRESULT_EVENT_SEMANTICS;
}

AAFRESULT ImplAAFSequence::CheckTimelineSlotLengthSemantics( ImplAAFEvent* pEvent, aafUInt32 index )
{
	// Event in a TimlineMobSlot is required to have Length property
	aafLength_t lengthNext = 0;
	if (pEvent->GetLength(&lengthNext) == AAFRESULT_PROP_NOT_PRESENT)
	{
		return AAFRESULT_BAD_LENGTH;
	}

	// No restrictions for a first sequence component.
	if (_components.count() == 0)
	{
		return AAFRESULT_SUCCESS;
	}

	// component with unknown length can be only added to the end
	if (lengthNext == AAF_UNKNOWN_LENGTH && index != _components.count())
	{
		return AAFRESULT_INVALID_PARAM;
	}

	ImplAAFComponent* pComponentLast = GetLastComponent();

	// Length properties are not optional for components and transitions.
	aafLength_t lengthLast = 0;
	if (pComponentLast->GetLength(&lengthLast) == AAFRESULT_PROP_NOT_PRESENT)
	{
		return AAFRESULT_BAD_LENGTH;
	}

	// cannot append anything after a last component with unknown length
	if (lengthLast == AAF_UNKNOWN_LENGTH && index == _components.count())
	{
		return AAFRESULT_INVALID_PARAM;
	}

	return AAFRESULT_SUCCESS;
}

AAFRESULT ImplAAFSequence::CheckTimelineSlotTypeSemantics( ImplAAFComponent* pComponent, aafUInt32 index )
{
	// This method doesn't supports Events
	if (dynamic_cast<ImplAAFEvent*>(pComponent))
	{
		return AAFRESULT_INTERNAL_ERROR;
	}

	AAFRESULT status = AAFRESULT_SUCCESS;

	// Events are not allowed in Sequences with non-Events and non-Fillers
	if (_components.count() > 0)
	{
		if (!dynamic_cast<ImplAAFFiller*>(pComponent) &&
			this->ContainsEvents())
		{
			status = AAFRESULT_OBJECT_SEMANTIC;
		}
	}

	if (AAFRESULT_SUCCEEDED(status))
	{
		// Check generic (non-TimelineMobSlot) semantics.
		status = CheckTypeSemantics(pComponent, index);
	}

	return status;
}

AAFRESULT ImplAAFSequence::CheckStaticSlotPositionSemantics( ImplAAFEvent* pEvent, aafUInt32 /*index*/ )
{
	aafPosition_t position = 0;
	AAFRESULT status = pEvent->GetPosition(&position);

	// Treat Position property with zero value as not present
	if (AAFRESULT_SUCCEEDED(status) && position == 0)
		status = AAFRESULT_PROP_NOT_PRESENT;

	if (status == AAFRESULT_PROP_NOT_PRESENT)
		return AAFRESULT_SUCCESS;

	return AAFRESULT_EVENT_SEMANTICS;
}

AAFRESULT ImplAAFSequence::CheckStaticSlotLengthSemantics( ImplAAFComponent* pComponent )
{
	// Length properties are not allowed in Components of StaticMobSlots
	aafLength_t length = 0;
	if( pComponent->GetLength(&length) != AAFRESULT_PROP_NOT_PRESENT ) {
		return AAFRESULT_BAD_LENGTH;
	}

	return AAFRESULT_SUCCESS;
}

AAFRESULT ImplAAFSequence::CheckEventSlotTypeSemantics( ImplAAFComponent* pComponent, aafUInt32 index ) 
{
	// This method doesn't supports Events
	if (dynamic_cast<ImplAAFEvent*>(pComponent))
	{
		return AAFRESULT_INTERNAL_ERROR;
	}

	// Non-Events are not allowed in EventMobSlots
	AAFRESULT status = AAFRESULT_EVENT_SEMANTICS;

	if (AAFRESULT_SUCCEEDED(status))
	{
		// Check generic (non-EventMobSlot) semantics.
		// This code is currently unreachable but left here
		// in case anything above changes.
		status = CheckTypeSemantics(pComponent, index);
	}

	return status;
}

AAFRESULT ImplAAFSequence::UpdateSequenceLengthOnInsert( ImplAAFComponent* pComponent )
{
	// First get the length of pComponent. If it does not have a length property
	// (AAFRESULT_PROP_NOT_PRESENT) leave the sequence length unchanged.
	// 
	// Now, assuming pComponent has a length:
	//
	// If this sequence has no length property (as is the case when the first
	// component is added, use a default sequence length of zero, and update the
	// sequence length.
	//
	// If this sequence has a length,  then update this sequence's length.
	//
	// If the component is a transition subtract its length, else, add its length.
	//
	// When pComponent has unknown length (-1):
	//
	// Sequence will have unknown length (-1).
	
	AAFRESULT status;

	aafLength_t compLength = 0;
	status = pComponent->GetLength( &compLength );
	if ( AAFRESULT_SUCCESS != status ) {
		return AAFRESULT_SUCCESS;
	}


	aafLength_t seqLength = 0;
	status = GetLength( &seqLength );
	if ( !(AAFRESULT_PROP_NOT_PRESENT == status  ||  AAFRESULT_SUCCESS == status) ) {
		return status;
	}

	if (compLength == AAF_UNKNOWN_LENGTH || seqLength == AAF_UNKNOWN_LENGTH)
	{
		seqLength = AAF_UNKNOWN_LENGTH;
	}
	else
	{
		// The length of the Sequence shall be equal to the sum of the length of all Segments directly owned 
		// by the Sequence minus the sum of the lengths of all Transitions directly owned by the Sequence.
		if (dynamic_cast<ImplAAFTransition*>(pComponent))
			seqLength -= compLength;
		else
			seqLength += compLength;
	}	

	status = SetLength( seqLength );
	if ( AAFRESULT_SUCCESS != status ) {
		return status;
	}

	return AAFRESULT_SUCCESS;
}

void ImplAAFSequence::Accept(AAFComponentVisitor& visitor)
{
	aafUInt32 count = 0;
	CountComponents(&count);
	for(aafUInt32 i=0; i<count; i++)
	{
		ImplAAFComponent* pComponent = 0;
		GetNthComponent(i, &pComponent);

       	        pComponent->Accept(visitor);

		pComponent->ReleaseReference();
		pComponent = NULL;
	}

	// TODO
	// visitor.VisitSequence(this);
}
