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
// The Original Code of this file is Copyright 1998-2003, Licensor of the
// AAF Association.
//
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

// @doc OMINTERNAL
// @author Tim Bingham | tjb | Avid Technology, Inc. | OMMXFStorage

#include "OMMXFStorage.h"

#include "OMRawStorage.h"
#include "OMAssertions.h"
#include "OMExceptions.h"
#include "OMUtilities.h"
#include "OMSet.h"

  // @mfunc Constructor.
OMMXFStorage::OMMXFStorage(OMRawStorage* store)
: OMWrappedRawStorage(store),
  _instanceIdToObject(0),
  _objectToInstanceId(0)
{
  TRACE("OMMXFStorage::OMMXFStorage");
}

  // @mfunc Destructor.
OMMXFStorage::~OMMXFStorage(void)
{
  TRACE("OMMXFStorage::~OMMXFStorage");

  if (_instanceIdToObject != 0) {
    _instanceIdToObject->clear();
    delete _instanceIdToObject;
    _instanceIdToObject = 0;
  }

  if (_objectToInstanceId != 0) {
    _objectToInstanceId->clear();
    delete _objectToInstanceId;
    _objectToInstanceId = 0;
  }
}

OMMXFStorage::ObjectDirectory* OMMXFStorage::instanceIdToObject(void)
{
  TRACE("OMMXFStorage::instanceIdToObject");
  if (_instanceIdToObject == 0) {
    _instanceIdToObject = new ObjectDirectory();
    ASSERT("Valid heap pointer", _instanceIdToObject != 0);
  }
  return _instanceIdToObject;
}

OMMXFStorage::ObjectSet* OMMXFStorage::objectToInstanceId(void)
{
  TRACE("OMMXFStorage::objectToInstanceId");

  if (_objectToInstanceId == 0) {
    _objectToInstanceId = new ObjectSet();
    ASSERT("Valid heap pointer", _objectToInstanceId != 0);
  }
  return _objectToInstanceId;
}
