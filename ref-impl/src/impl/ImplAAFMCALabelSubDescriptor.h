#ifndef __ImplAAFMCALabelSubDescriptor_h__
#define __ImplAAFMCALabelSubDescriptor_h__

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


#include "ImplAAFSubDescriptor.h"

#include "OMFixedSizeProperty.h"
#include "OMStringProperty.h"
#include "OMWideStringProperty.h"



class ImplAAFMCALabelSubDescriptor : public ImplAAFSubDescriptor
{
public:
  //****************
  // Constructor
  //
  ImplAAFMCALabelSubDescriptor ();

protected:
  //****************
  // Desctructor
  //
  virtual ~ImplAAFMCALabelSubDescriptor ();

public:
  //********************************
  // AAF SDK exported methods start
  //********************************

  //****************
  // Initialize()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Initialize (
        // @param dictionaryID [in] TODO:
        //                  PARAMETER DESCRIPTION.
        aafUID_constref dictionaryID,

		// @param linkID [in] TODO:
        //                  PARAMETER DESCRIPTION.
        aafUID_constref linkID,

		// @param pTagSymbol [in] TODO:
        //                  PARAMETER DESCRIPTION.
        aafCharacter_constptr pTagSymbol);

  //****************
  // SetLabelDictionaryID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetLabelDictionaryID
        // @param dictionaryID [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUID_constref dictionaryID);
  
  //****************
  // GetLabelDictionaryID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetLabelDictionaryID
        // @param pDictionaryID [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUID_t* pDictionaryID);

  //****************
  // SetLinkID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetLinkID
        // @param linkID [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUID_constref linkID);

  //****************
  // GetLinkID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetLinkID
        // @param pLinkID [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUID_t* pLinkID);

  //****************
  // SetTagSymbol()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetTagSymbol
        // @parm [in, string] buffer from which TagSymbol is to be read
        (aafCharacter_constptr pTagSymbol);
  
  //****************
  // GetTagSymbol()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetTagSymbol
        (// @parm [out, string, size_is(bufSize)] buffer into which TagSymbol is to be written
         aafCharacter* pTagSymbol,

         // @parm [in] size of *pTagSymbol buffer in bytes
         aafUInt32 bufSize);
  
  //****************
  // GetTagSymbolBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetTagSymbolBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);
  
  //****************
  // SetTagName()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetTagName
        // @parm [in, string] buffer from which TagName is to be read
        (aafCharacter_constptr pTagName);

  //****************
  // GetTagName()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetTagName
        (// @parm [out, string, size_is(bufSize)] buffer into which TagName is to be written
         aafCharacter* pTagName,

         // @parm [in] size of *pTagName buffer in bytes
         aafUInt32 bufSize);

  //****************
  // GetTagNameBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetTagNameBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);

  //****************
  // SetChannelID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetChannelID
        // @param dictionaryID [in] TODO:
        //                  PARAMETER DESCRIPTION.
        (aafUInt32 channelID);

  //****************
  // GetChannelID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetChannelID
        // @param pChannelID [out] TODO:
        //                      PARAMETER DESCRIPTION.
        (aafUInt32* pChannelID);

  //****************
  // SetRFC5646SpokenLanguage()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetRFC5646SpokenLanguage
        // @parm [in, string] buffer from which RFC5646SpokenLanguage is to be read
        (const char* pRFC5646SpokenLanguage);

  //****************
  // GetRFC5646SpokenLanguage()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetRFC5646SpokenLanguage
        (// @parm [out, string, size_is(bufSize)] buffer into which RFC5646SpokenLanguage is to be written
         char* pRFC5646SpokenLanguage,

         // @parm [in] size of *pRFC5646SpokenLanguage buffer in bytes
         aafUInt32 bufSize);

  //****************
  // GetRFC5646SpokenLanguageBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetRFC5646SpokenLanguageBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);

//****************
  // SetTitle()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetTitle
        // @parm [in, string] buffer from which Title is to be read
        (aafCharacter_constptr pTitle);

  //****************
  // GetTitle()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetTitle
        (// @parm [out, string, size_is(bufSize)] buffer into which Title is to be written
         aafCharacter* pTitle,

         // @parm [in] size of *pTitle buffer in bytes
         aafUInt32 bufSize);

  //****************
  // GetTitleBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetTitleBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);

  //****************
  // SetTitleVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetTitleVersion
        // @parm [in, string] buffer from which TitleVersion is to be read
        (aafCharacter_constptr pTitleVersion);

  //****************
  // GetTitleVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetTitleVersion
        (// @parm [out, string, size_is(bufSize)] buffer into which TitleVersion is to be written
         aafCharacter* pTitleVersion,

         // @parm [in] size of *pTitleVersion buffer in bytes
         aafUInt32 bufSize);

  //****************
  // GetTitleVersionBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetTitleVersionBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);

  //****************
  // SetTitleSubVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetTitleSubVersion
        // @parm [in, string] buffer from which TitleSubVersion is to be read
        (aafCharacter_constptr pTitleSubVersion);

  //****************
  // GetTitleSubVersion()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetTitleSubVersion
        (// @parm [out, string, size_is(bufSize)] buffer into which TitleSubVersion is to be written
         aafCharacter* pTitleSubVersion,

         // @parm [in] size of *pTitleSubVersion buffer in bytes
         aafUInt32 bufSize);

  //****************
  // GetTitleSubVersionBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetTitleSubVersionBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);

  //****************
  // SetEpisode()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetEpisode
        // @parm [in, string] buffer from which Episode is to be read
        (aafCharacter_constptr pEpisode);

  //****************
  // GetEpisode()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetEpisode
        (// @parm [out, string, size_is(bufSize)] buffer into which Episode is to be written
         aafCharacter* pEpisode,

         // @parm [in] size of *pEpisode buffer in bytes
         aafUInt32 bufSize);

  //****************
  // GetEpisodeBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetEpisodeBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);

  //****************
  // SetPartitionKind()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPartitionKind
        // @parm [in, string] buffer from which PartitionKind is to be read
        (aafCharacter_constptr pPartitionKind);

  //****************
  // GetPartitionKind()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPartitionKind
        (// @parm [out, string, size_is(bufSize)] buffer into which PartitionKind is to be written
         aafCharacter* pPartitionKind,

         // @parm [in] size of *pPartitionKind buffer in bytes
         aafUInt32 bufSize);

  //****************
  // GetPartitionKindBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPartitionKindBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);

  //****************
  // SetPartitionNumber()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetPartitionNumber
        // @parm [in, string] buffer from which PartitionNumber is to be read
        (aafCharacter_constptr pPartitionNumber);

  //****************
  // GetPartitionNumber()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPartitionNumber
        (// @parm [out, string, size_is(bufSize)] buffer into which PartitionNumber is to be written
         aafCharacter* pPartitionNumber,

         // @parm [in] size of *pPartitionNumber buffer in bytes
         aafUInt32 bufSize);

  //****************
  // GetPartitionNumberBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetPartitionNumberBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);


  //****************
  // SetAudioContentKind()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetAudioContentKind
        // @parm [in, string] buffer from which AudioContentKind is to be read
        (aafCharacter_constptr pAudioContentKind);

  //****************
  // GetAudioContentKind()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetAudioContentKind
        (// @parm [out, string, size_is(bufSize)] buffer into which AudioContentKind is to be written
         aafCharacter* pAudioContentKind,

         // @parm [in] size of *pAudioContentKind buffer in bytes
         aafUInt32 bufSize);

  //****************
  // GetAudioContentKindBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetAudioContentKindBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);

  //****************
  // SetAudioElementKind()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetAudioElementKind
        // @parm [in, string] buffer from which AudioElementKind is to be read
        (aafCharacter_constptr pAudioElementKind);

  //****************
  // GetAudioElementKind()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetAudioElementKind
        (// @parm [out, string, size_is(bufSize)] buffer into which AudioElementKind is to be written
         aafCharacter* pAudioElementKind,

         // @parm [in] size of *pAudioElementKind buffer in bytes
         aafUInt32 bufSize);

  //****************
  // GetAudioElementKindBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetAudioElementKindBufLen
        // @parm [out] size of required buffer, in bytes
        (aafUInt32* pBufSize);

  //********************************
  // AAF SDK exported methods end
  //********************************

protected:

    //
    // SMPTE UUID as array of bytes.
    //
    // The main property of this type, compared to the AUID type represented
    // by aafUID_t in AAF Toolkit, is its storage format in MXF files. While
    // the AUID type is defined as integer typed fields Data1, Data2, Data3
    // and Data4, the UUID type is defined as a seqeuence of bytes.
    // 
    // Given UUID:
    //      0772262e-7655-436f-8ff3-8ac51b771e02
    // if treated as AUID it is stored using little endian byte order as:
    //      8f f3 8a c5 1b 77 1e 02 07 72 26 2e 76 55 43 6f
    // and if treated as UUID it is stored, independent of the storage byte
    // order as:
    //      07 72 26 2e 76 55 43 6f 8f f3 8a c5 1b 77 1e 02 
    //
    // The type declaration is not in any public scope because the type is
    // currently only used for internal in-memory representation of SMPTE
    // UUID in MCALabelSubDescriptor and its subclasses. If this type is
    // needed outside the current scope it can be redefined as necessary,
    // with only requirement to maintain the stored fored format for all
    // the supported encodings.
    //
    struct UUID_t
    {
        aafUInt8 bytes[16];

        bool operator==(const UUID_t& uuid) const
        {
            return (memcmp(bytes, uuid.bytes, sizeof(bytes)) == 0 ? true : false);
        }
    };

    static aafUID_t makeAUID(const UUID_t& uuid);
    static UUID_t   makeUUID(const aafUID_t& auid);


protected:

    OMFixedSizeProperty<aafUID_t>   _labelDictionaryID;
    OMFixedSizeProperty<UUID_t>     _linkID;
    OMWideStringProperty            _tagSymbol;
    OMWideStringProperty            _tagName;
    OMFixedSizeProperty<aafUInt32>  _channelID;
    OMStringProperty                _spokenLanguage;
    OMWideStringProperty            _title;
    OMWideStringProperty            _titleVersion;
    OMWideStringProperty            _titleSubVersion;
    OMWideStringProperty            _episode;
    OMWideStringProperty            _partitionKind;
    OMWideStringProperty            _partitionNumber;
    OMWideStringProperty            _audioContentKind;
    OMWideStringProperty            _audioElementKind;
};

#endif // ! __ImplAAFMCALabelSubDescriptor_h__
