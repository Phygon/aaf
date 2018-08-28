#ifndef __ImplAAFAudioChannelLabelSubDescriptor_h__
#define __ImplAAFAudioChannelLabelSubDescriptor_h__

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

#include "OMFixedSizeProperty.h"



class ImplAAFAudioChannelLabelSubDescriptor : public ImplAAFMCALabelSubDescriptor
{
public:
  //****************
  // Constructor
  //
  ImplAAFAudioChannelLabelSubDescriptor ();

protected:
  //****************
  // Desctructor
  //
  virtual ~ImplAAFAudioChannelLabelSubDescriptor ();

public:
  //********************************
  // AAF SDK exported methods start
  //********************************

  //****************
  // SetSoundfieldGroupLinkID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetSoundfieldGroupLinkID
        // @param groupLinkID [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUID_constref groupLinkID);

  //****************
  // GetSoundfieldGroupLinkID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetSoundfieldGroupLinkID
        // @param pGroupLinkID [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUID_t* pGroupLinkID);

  //********************************
  // AAF SDK exported methods end
  //********************************

protected:

    OMFixedSizeProperty<ImplAAFMCALabelSubDescriptor::UUID_t>  _groupLinkID;
};

#endif // ! __ImplAAFAudioChannelLabelSubDescriptor_h__
