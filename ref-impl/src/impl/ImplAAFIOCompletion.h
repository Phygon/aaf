#ifndef __ImplAAFIOCompletion_h__
#define __ImplAAFIOCompletion_h__
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
// The Original Code of this file is Copyright 1998-2005, Licensor of the
// AAF Association.
//
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

#ifndef __ImplAAFRoot_h__
#include "ImplAAFRoot.h"
#endif

class ImplAAFIOCompletion : public ImplAAFRoot
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFIOCompletion ();

protected:
  virtual ~ImplAAFIOCompletion ();

public:

  //****************
  // Completed()
  //
  virtual AAFRESULT STDMETHODCALLTYPE Completed (
    HRESULT  completionStatus,
    aafUInt32  numTransferred,
    aafMemConstPtr_t  pClientData);

private:

};

#endif // ! __ImplAAFIOCompletion_h__
