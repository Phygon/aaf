/***********************************************************************
*
*              Copyright (c) 1998-2000 Avid Technology, Inc.
*
* Permission to use, copy and modify this software and accompanying
* documentation, and to distribute and sublicense application software
* incorporating this software for any purpose is hereby granted,
* provided that (i) the above copyright notice and this permission
* notice appear in all copies of the software and related documentation,
* and (ii) the name Avid Technology, Inc. may not be used in any
* advertising or publicity relating to the software without the specific,
* prior written permission of Avid Technology, Inc.
*
* THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
* EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
* WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL AVID TECHNOLOGY, INC. BE LIABLE FOR ANY DIRECT,
* SPECIAL, INCIDENTAL, PUNITIVE, INDIRECT, ECONOMIC, CONSEQUENTIAL OR
* OTHER DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE AND
* ACCOMPANYING DOCUMENTATION, INCLUDING, WITHOUT LIMITATION, DAMAGES
* RESULTING FROM LOSS OF USE, DATA OR PROFITS, AND WHETHER OR NOT
* ADVISED OF THE POSSIBILITY OF DAMAGE, REGARDLESS OF THE THEORY OF
* LIABILITY.
*
************************************************************************/

// @doc OMEXTERNAL
#ifndef OMREFERENCEVECTORITER_H
#define OMREFERENCEVECTORITER_H

#include "OMVectorIterator.h"
#include "OMReferenceContainerIter.h"
#include "OMContainerElement.h"

template <typename ReferencedObject>
class OMReferenceVector;

// @class Iterators over <c OMReferenceVector>s.
//   @tcarg class | ReferencedObject | The type of the contained objects.
template <typename ReferencedObject>
class OMReferenceVectorIterator :
                        public OMReferenceContainerIterator<ReferencedObject> {
public:
  // @access Public members.

    // @cmember Create an <c OMReferenceVectorIterator> over the given
    //          <c OMReferenceVector> <p vector> and
    //          initialize it to the given <p initialPosition>.
    //          If <p initialPosition> is specified as
    //          <e OMIteratorPosition.OMBefore> then this
    //          <c OMReferenceVectorIterator> is made ready to traverse
    //          the associated <c OMReferenceVector> in the
    //          forward direction (increasing indexes).
    //          If <p initialPosition> is specified as
    //          <e OMIteratorPosition.OMAfter> then this
    //          <c OMReferenceVectorIterator> is made ready to traverse
    //          the associated <c OMReferenceVector> in the
    //          reverse direction (decreasing indexes).
  OMReferenceVectorIterator(
                             const OMReferenceVector<ReferencedObject>& vector,
                             OMIteratorPosition initialPosition = OMBefore);

    // @cmember Create a copy of this <c OMReferenceVectorIterator>.
  virtual OMReferenceContainerIterator<ReferencedObject>* copy(void) const;

    // @cmember Destroy this <c OMReferenceVectorIterator>.
  virtual ~OMReferenceVectorIterator(void);

    // @cmember Reset this <c OMReferenceVectorIterator> to the given
    //          <p initialPosition>.
    //          If <p initialPosition> is specified as
    //          <e OMIteratorPosition.OMBefore> then this
    //          <c OMReferenceVectorIterator> is made ready to traverse
    //          the associated <c OMReferenceVector> in the
    //          forward direction (increasing indexes).
    //          If <p initialPosition> is specified as
    //          <e OMIteratorPosition.OMAfter> then this
    //          <c OMReferenceVectorIterator> is made ready to traverse
    //          the associated <c OMReferenceVector> in the
    //          reverse direction (decreasing indexes).
   virtual void reset(OMIteratorPosition initialPosition = OMBefore);

    // @cmember Is this <c OMReferenceVectorIterator> positioned before
    //          the first <p ReferencedObject> ?
   virtual bool before(void) const;

    // @cmember Is this <c OMReferenceVectorIterator> positioned after
    //          the last <p ReferencedObject> ?
   virtual bool after(void) const;

    // @cmember Is this <c OMReferenceVectorIterator> validly
    //          positioned on a <p ReferencedObject> ?
  virtual bool valid(void) const;

    // @cmember The number of <p ReferencedObject>s in the associated
    //          <c OMReferenceVector>.
  virtual size_t count(void) const;

    // @cmember Advance this <c OMReferenceVectorIterator> to the
    //          next <p ReferencedObject>, if any.
    //          If the end of the associated
    //          <c OMReferenceVector> is not reached then the
    //          result is <e bool.true>,
    //          <mf OMReferenceVectorIterator::valid> becomes
    //          <e bool.true> and <mf OMReferenceVectorIterator::after>
    //          becomes <e bool.false>.
    //          If the end of the associated
    //          <c OMReferenceVector> is reached then the result
    //          is <e bool.false>, <mf OMReferenceVectorIterator::valid>
    //          becomes <e bool.false> and
    //          <mf OMReferenceVectorIterator::after> becomes
    //          <e bool.true>. 
   virtual bool operator++();

    // @cmember Retreat this <c OMReferenceVectorIterator> to the
    //          previous <p ReferencedObject>, if any.
    //          If the beginning of the associated
    //          <c OMReferenceVector> is not reached then the
    //          result is <e bool.true>,
    //          <mf OMReferenceVectorIterator::valid> becomes
    //          <e bool.true> and <mf OMReferenceVectorIterator::before>
    //          becomes <e bool.false>.
    //          If the beginning of the associated
    //          <c OMReferenceVector> is reached then the result
    //          is <e bool.false>, <mf OMReferenceVectorIterator::valid>
    //          becomes <e bool.false> and
    //          <mf OMReferenceVectorIterator::before> becomes
    //          <e bool.true>. 
   virtual bool operator--();

    // @cmember Return the <p ReferencedObject> in the associated
    //          <c OMReferenceVector> at the position currently
    //          designated by this <c OMReferenceVectorIterator>.
   virtual ReferencedObject* value(void) const;

    // @cmember Set the <p ReferencedObject> in the associated
    //          <c OMReferenceVector> at the position currently
    //          designated by this <c OMReferenceVectorIterator> to
    //          <p newObject>. The previous <p ReferencedObject>, if any,
    //          is returned.
   virtual ReferencedObject* setValue(const ReferencedObject* newObject);

    // @cmember Return the index of the <p ReferencedObject> in the
    //          associated <c OMReferenceVector> at the position
    //          currently designated by this
    //          <c OMReferenceVectorIterator>.
   virtual size_t index(void) const;

protected:

  typedef OMVectorElement<ReferencedObject> VectorElement;

  typedef OMVectorIterator<VectorElement> VectorIterator;

    // @cmember Create an <c OMReferenceVectorIterator> given
    //          an underlying <c OMVectorIterator>.
  OMReferenceVectorIterator(const VectorIterator& iter);

private:

  VectorIterator _iterator;

};

#include "OMReferenceVectorIterT.h"

#endif
