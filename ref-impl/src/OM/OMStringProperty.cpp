//=---------------------------------------------------------------------=
//
// $Id$ $Name$
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
// The Original Code of this file is Copyright 1998-2004, Licensor of the
// AAF Association.
//
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

// @doc OMEXTERNAL

#include "OMStringProperty.h"

#include "OMUtilities.h"
#include "OMAssertions.h"

  // @mfunc Constructor.
  //   @parm The property id.
  //   @parm The name of this <c OMStringProperty>.
OMStringProperty::OMStringProperty(const OMPropertyId propertyId,
                                   const wchar_t* name)
: OMCharacterStringProperty<char>(propertyId, name)
{
  TRACE("OMStringProperty::OMStringProperty");
}

  // @mfunc Destructor.
OMStringProperty::~OMStringProperty(void)
{
  TRACE("OMStringProperty::~OMStringProperty");
}

  // @mfunc Assignment operator.
  //   @parm The new value for this <c OMStringProperty>.
  //   @rdesc The <c OMStringProperty> resulting from the assignment.
OMStringProperty& OMStringProperty::operator = (const char* value)
{
  TRACE("OMStringProperty::operator =");
  PRECONDITION("Valid string", validString(reinterpret_cast<const char*>(value)));

  assign(value);
  return *this;
}
