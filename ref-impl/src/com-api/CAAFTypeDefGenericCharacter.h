//@doc
//@class    AAFTypeDefGenericCharacter | Implementation class for AAFTypeDefGenericCharacter
#ifndef __CAAFTypeDefGenericCharacter_h__
#define __CAAFTypeDefGenericCharacter_h__

//=---------------------------------------------------------------------=
//
// This file was GENERATED for the AAF SDK
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
// The Original Code of this file is Copyright 1998-2012, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
// The Initial Developer of the Original Code of this file and the
// licensor of the Advanced Media Workflow Association is
// Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=



#ifndef __AAF_h__
#include "AAF.h"
#endif







#ifndef __CAAFTypeDef_h__
#include "CAAFTypeDef.h"
#endif


class CAAFTypeDefGenericCharacter
  : public IAAFTypeDefGenericCharacter,
    public CAAFTypeDef
{
protected:

  //********
  //
  // Constructor/destructor
  //
  CAAFTypeDefGenericCharacter (IUnknown * pControllingUnknown, aafBool doInit = kAAFTrue);
  virtual ~CAAFTypeDefGenericCharacter ();

public:



  //***********************************************************
  //
  // Initialize()
  //
  // Initializes this type def to be identified by the given AUID, and to
  /// have the given size in bytes.
  ///
  /// The implementation of this method may only allow certain values
  /// for 'size'.  It *will* allow at least 1, 2, 4-byte
  /// characters; some implementations may allow more than that.
  ///
  /// This method must be called after allocation, and before
  /// any other method can be called.
  ///
  /// Succeeds if:
  /// - Initialize() has not yet been called on this object.
  /// - size is a valid value.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_ALREADY_INITIALIZED
  //   - This object has already had Initialize() called on it.
  //
  // AAFRESULT_NULL_PARAM
  //   - pTypeName arg is NULL.
  ///
  /// AAFRESULT_BAD_SIZE
  ///  - size is not a valid value.
  //
  STDMETHOD (Initialize) (
    // AUID to be used to identify this type
    /*[in, ref]*/ aafUID_constref  id,

    // the size of this character type in bytes
    /*[in]*/ aafUInt8  size,

    // name of this type definition
    /*[in, string]*/ aafCharacter_constptr  pTypeName,

    // description of this type definition
    /*[in, string]*/ aafCharacter_constptr  pTypeDescription);





protected:
  // 
  // Declare the QI that implements for the interfaces
  // for this module. This will be called by CAAFUnknown::QueryInterface().
  // 
  STDMETHOD(InternalQueryInterface)(REFIID riid, void **ppvObjOut);


public:
  //
  // This class as concrete. All AAF objects can be constructed from
  // a CLSID. This will allow subclassing all "base-classes" by
  // aggreggation.
  // 
  AAF_DECLARE_CONCRETE();
  //
  //********
};

#endif // ! __CAAFTypeDefGenericCharacter_h__


