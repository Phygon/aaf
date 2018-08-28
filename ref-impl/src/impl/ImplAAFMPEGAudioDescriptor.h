//@doc
//@class    AAFMPEGVideoDescriptor | Implementation class for AAFMPEGVideoDescriptor
#ifndef __ImplAAFMPEGAudioDescriptor_h__
#define __ImplAAFMPEGAudioDescriptor_h__

//=---------------------------------------------------------------------=
//
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



#ifndef __ImplAAFSoundDescriptor_h__
#include "ImplAAFSoundDescriptor.h"
#endif


class ImplAAFMPEGAudioDescriptor : public ImplAAFSoundDescriptor
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFMPEGAudioDescriptor ();

protected:
  virtual ~ImplAAFMPEGAudioDescriptor ();
 
private:

    OMFixedSizeProperty<aafUInt32> _mpegAudioBitRate;
    
    

public:

  //****************
  // Initialize()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Initialize ();

  //****************
  // SetBitRate()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetMPEGAudioBitRate
        // @parm [in] Optional.
        (aafUInt32  bitRate);

  //****************
  // GetBitRate()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetMPEGAudioBitRate
        // @parm [out] Optional.
        (aafUInt32 *  pBitRate);

};

#endif // ! __ImplAAFMPEGAudioDescriptor_h__


