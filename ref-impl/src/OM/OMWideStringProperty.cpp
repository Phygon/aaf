//=---------------------------------------------------------------------=
//
// The contents of this file are subject to the AAF SDK Public
// Source License Agreement (the "License"); You may not use this file
// except in compliance with the License.  The License is available in
// AAFSDKPSL.TXT, or you may obtain a copy of the License from the AAF
// Association or its successor.
// 
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.
// 
// The Original Code of this file is Copyright 1998-2001, Licensor of the
// AAF Association.
// 
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

// @doc OMEXTERNAL
// @author Tim Bingham | tjb | Avid Technology, Inc. | OMWideStringProperty

#include "OMWideStringProperty.h"

#include "OMAssertions.h"

  // @mfunc Constructor.
  //   @parm The property id.
  //   @parm The name of this <c OMWideStringProperty>.
OMWideStringProperty::OMWideStringProperty(const OMPropertyId propertyId,
                                           const wchar_t* name)
: OMCharacterStringProperty<wchar_t>(propertyId, name)
{
  TRACE("OMWideStringProperty::OMWideStringProperty");
}

  // @mfunc Destructor.
OMWideStringProperty::~OMWideStringProperty(void)
{
  TRACE("OMWideStringProperty::~OMWideStringProperty");
}

  // @mfunc Assignment operator.
  //   @parm The new value for this <c OMWideStringProperty>.
  //   @rdesc The <c OMWideStringProperty> resulting from the assignment.
OMWideStringProperty& OMWideStringProperty::operator = (const wchar_t* value)
{
  TRACE("OMWideStringProperty::operator =");
  PRECONDITION("Valid string", validWideString(value));

  assign(value);
  return *this;
}
