//@doc
//@class    AAFSequence | Implementation class for AAFSequence
#ifndef __ImplAAFSequence_h__
#define __ImplAAFSequence_h__


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

class ImplAAFTimecode;

class ImplAAFComponent;

class ImplAAFSegment;

class ImplAAFDataDef;

class ImplAAFEvent;

template <class T> 
class ImplAAFEnumerator;
typedef ImplAAFEnumerator<ImplAAFComponent> ImplEnumAAFComponents;

#ifndef __ImplAAFSegment_h__
#include "ImplAAFSegment.h"
#endif

#include "OMStrongRefVectorProperty.h"

class ImplAAFSequence : public ImplAAFSegment
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFSequence ();
  virtual ~ImplAAFSequence ();


  //****************
  // Initialize()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Initialize
		// @parm [in] Data Definition object
        (ImplAAFDataDef * pDataDef);


  //****************
  // AppendComponent()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    AppendComponent
		// @parm [in] Component to append to the sequence
        (ImplAAFComponent * pComponent);


  //****************
  // PrependComponent()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    PrependComponent
		// @parm [in] Component to prepend to the sequence
        (ImplAAFComponent * pComponent);


  //****************
  // InsertComponentAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    InsertComponentAt
		// @parm [in] index to insert component
        (aafUInt32 index,

		 // @parm [in] Component to insert into the sequence
		 ImplAAFComponent * pComponent);


  //****************
  // GetComponentAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetComponentAt
		// @parm [in] index of component to retrieve
        (aafUInt32 index,

		 // @parm [out, retval] retrieved component
		 ImplAAFComponent ** ppComponent);


  //****************
  // RemoveComponentAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    RemoveComponentAt
		// @parm [in] index of component to remove
        (aafUInt32 index);


  //****************
  // RemoveComponent()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    RemoveComponent
		// @parm [in] Component to remove from the sequence
        (ImplAAFComponent * pComponent);


  //****************
  // CountComponents()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    CountComponents
		// @parm [out, retval] Component Enumeration
        (aafUInt32 * pResult);


  //****************
  // GetComponents()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetComponents
		// @parm [out, retval] Component Enumeration
        (ImplEnumAAFComponents ** ppEnum);


  // Override from AAFSegment
  virtual AAFRESULT STDMETHODCALLTYPE
    SegmentOffsetToTC (/*[in]*/ aafPosition_t *  pOffset,
	  /*[out]*/ aafTimecode_t *  pTimecode);

  // Override from AAFSegment
  virtual AAFRESULT STDMETHODCALLTYPE
    SegmentTCToOffset (/*[in]*/ aafTimecode_t *  pTimecode,
	  /*[in]*/ aafRational_t *  pEditRate,
	  /*[out]*/ aafFrameOffset_t *  pOffset);

  // Override from AAFSegement	
  virtual AAFRESULT FindSubSegment( aafPosition_t offset,
									  aafMediaCriteria_t *mediaCrit,
									  aafPosition_t *sequPosPtr,
									  ImplAAFSegment **subseg,
									  aafBool *found);

public:

  // Interfaces visible inside the toolkit, but not exposed through the API
  AAFRESULT GetNthComponent(aafUInt32 index, ImplAAFComponent **ppComponent);

	virtual AAFRESULT GetMinimumBounds(aafPosition_t rootPos, aafLength_t rootLen,
										ImplAAFMob *mob, ImplAAFMobSlot *track,
										aafMediaCriteria_t *mediaCrit,
										aafPosition_t currentObjPos,
										aafOperationChoice_t *effectChoice,
										ImplAAFComponent	*prevObject,
										ImplAAFComponent *nextObject,
										ImplAAFScopeStack *scopeStack,
										aafPosition_t *diffPos, aafLength_t *minLength,
										ImplAAFOperationGroup **groupObject, aafInt32	*nestDepth,
										ImplAAFComponent **found, aafBool *foundTransition);

	virtual AAFRESULT ChangeContainedReferences(aafMobID_constref from,
												aafMobID_constref to);
  AAFRESULT
    SetNthComponent (aafUInt32 index, ImplAAFComponent* pComponent);

	virtual AAFRESULT TraverseToClip( aafLength_t length,
									  ImplAAFSourceClip **sclp,
									  ImplAAFPulldown **pulldownObj,
									  aafInt32 *pulldownPhase,
									  aafLength_t *sclpLen,
									  aafBool *isMask);

	// Visit this component and its sub-components
	// with the specified visitor.
	virtual void Accept(AAFComponentVisitor& visitor);
	
private:

   // Sequences have two distinct forms:
   //   i) a sequence exclusively composed of events,
   //   ii) a sequence of non-event components.
   // The policy that must be enforced in regards to
   // valid component types, ordering, position, and length are different.
   // The component type dependent processing, performed in AppendComponent,
   // is implemented by these polymorphic routines. It is the responsibilty of
   // AppendComponent to attempt the ImplAAFEvent and special case the
   // calls to these routines should the cast succeed.

   AAFRESULT CheckTypeSemantics( ImplAAFEvent* pEvent );
   AAFRESULT CheckPositionSemantics( ImplAAFEvent* pEvent, aafUInt32 index );
   AAFRESULT CheckEventSlotLengthSemantics( ImplAAFEvent* pEvent, aafUInt32 index );

   AAFRESULT CheckTypeSemantics( ImplAAFComponent* pComponent, aafUInt32 index );
   AAFRESULT CheckPositionSemantics( ImplAAFComponent* pComponent );
   AAFRESULT CheckLengthSemantics( ImplAAFComponent* pComponent, aafUInt32 index );

   AAFRESULT CheckTimelineSlotTypeSemantics( ImplAAFEvent* pEvent );
   AAFRESULT CheckTimelineSlotPositionSemantics( ImplAAFEvent* pEvent, aafUInt32 index );
   AAFRESULT CheckTimelineSlotLengthSemantics( ImplAAFEvent* pEvent, aafUInt32 index );

   AAFRESULT CheckTimelineSlotTypeSemantics( ImplAAFComponent* pComponent, aafUInt32 index );

   AAFRESULT CheckStaticSlotPositionSemantics( ImplAAFEvent* pEvent, aafUInt32 index );

   AAFRESULT CheckStaticSlotLengthSemantics( ImplAAFComponent* pComponent );

   AAFRESULT CheckEventSlotTypeSemantics( ImplAAFComponent* pComponent, aafUInt32 index );

   // Update the length of a Sequence for O(n) time
   AAFRESULT UpdateSequenceLength();

   // These routines will update the length of an event, or !event, component.
   // The caller must resolve the type. Both will work correctly if pComponent
   // or pEvent is the first component.
   AAFRESULT UpdateSequenceLengthOnInsert( ImplAAFComponent* pComponent );
   AAFRESULT UpdateSequenceLengthOnInsert( ImplAAFEvent* pEvent, aafUInt32 index);

   ImplAAFComponent* GetLastComponent();
   ImplAAFComponent* GetFirstComponent();
   AAFRESULT GetLastEvent( ImplAAFEvent*& );
   AAFRESULT GetFirstEvent( ImplAAFEvent*& );

   ImplAAFEvent* FindLastEvent() const;
   ImplAAFEvent* FindNextEvent(aafUInt32 index) const;
   ImplAAFEvent* FindPreviousEvent(aafUInt32 index) const;

   bool ContainsEvents() const;
   bool ContainsNonFillers() const;
   bool ContainsNonEvents() const;

private:
	OMStrongReferenceVectorProperty<ImplAAFComponent> _components;
};

#endif // ! __ImplAAFSequence_h__

