#ifndef __ImplAAFSoundfieldGroupLabelSubDescriptor_h__
#define __ImplAAFSoundfieldGroupLabelSubDescriptor_h__

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
// The Original Code of this file is Copyright 1998-2011, Licensor of the
// AAF Association.
//
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=


#include "ImplAAFMCALabelSubDescriptor.h"

#include "AAFUtils.h"

#include "OMArrayProperty.h"



class ImplAAFSoundfieldGroupLabelSubDescriptor : public ImplAAFMCALabelSubDescriptor
{
public:
  //****************
  // Constructor
  //
  ImplAAFSoundfieldGroupLabelSubDescriptor ();

protected:
  //****************
  // Desctructor
  //
  virtual ~ImplAAFSoundfieldGroupLabelSubDescriptor ();

public:
  //********************************
  // AAF SDK exported methods start
  //********************************

  //****************
  // CountGroupOfSoundfieldGroupsLinkIDs()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    CountGroupOfSoundfieldGroupsLinkIDs
        // @param pCount [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt32* pCount);

  //****************
  // GetGroupOfSoundfieldGroupsLinkIDAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetGroupOfSoundfieldGroupsLinkIDAt (
        // @param index [out] TODO:
        //                  PARAMETER DESCRIPTION.
		aafUInt32 index,
        // @param pGroupOfGroupsLinkID [out] TODO:
        //                  PARAMETER DESCRIPTION.
        aafUID_t* pGroupOfGroupsLinkID);

  //****************
  // AppendGroupOfSoundfieldGroupsLinkID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    AppendGroupOfSoundfieldGroupsLinkID
        // @param groupOfGroupsLinkID [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUID_constref groupOfGroupsLinkID);

  //********************************
  // AAF SDK exported methods end
  //********************************


protected:

    bool Contains(aafUID_constref groupOfGroupsLinkID) const;

protected:

    OMArrayProperty<ImplAAFMCALabelSubDescriptor::UUID_t>   _groupLinkIDs;
};

#endif // ! __ImplAAFSoundfieldGroupLabelSubDescriptor_h__
