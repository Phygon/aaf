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
#include "AAFPropertyIDs.h"
#include "AAFPropertyDefs.h"

#include "OMType.h"
#include "OMUtilities.h"

#include <assert.h>
#include <wchar.h>



ImplAAFMCALabelSubDescriptor::ImplAAFMCALabelSubDescriptor() :
    _labelDictionaryID(
        PID_MCALabelSubDescriptor_MCALabelDictionaryID,
        L"MCALabelDictionaryID"),
    _linkID(
        PID_MCALabelSubDescriptor_MCALinkID,
        L"MCALinkID"),
    _tagSymbol(
        PID_MCALabelSubDescriptor_MCATagSymbol,
        L"TagSymbol"),
    _tagName(
        PID_MCALabelSubDescriptor_MCATagName,
        L"MCATagName"),
    _channelID(
        PID_MCALabelSubDescriptor_MCAChannelID,
        L"MCAChannelID"),
    _spokenLanguage(
        PID_MCALabelSubDescriptor_RFC5646SpokenLanguage,
        L"RFC5646SpokenLanguage"),
    _title(
        PID_MCALabelSubDescriptor_MCATitle,
        L"MCATitle"),
    _titleVersion(
        PID_MCALabelSubDescriptor_MCATitleVersion,
        L"MCATitleVersion"),
    _titleSubVersion(
        PID_MCALabelSubDescriptor_MCATitleSubVersion,
        L"MCATitleSubVersion"),
    _episode(
        PID_MCALabelSubDescriptor_MCAEpisode,
        L"MCAEpisode"),
    _partitionKind(
        PID_MCALabelSubDescriptor_MCAPartitionKind,
        L"MCAPartitionKind"),
    _partitionNumber(
        PID_MCALabelSubDescriptor_MCAPartitionNumber,
        L"MCAPartitionNumber"),
    _audioContentKind(
        PID_MCALabelSubDescriptor_MCAAudioContentKind,
        L"MCAAudioContentKind"),
    _audioElementKind(
        PID_MCALabelSubDescriptor_MCAAudioElementKind,
        L"MCAAudioElementKind")
{
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCALabelDictionaryID),
        _labelDictionaryID.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCALinkID),
        _linkID.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCATagSymbol),
        _tagSymbol.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCATagName),
        _tagName.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCAChannelID),
        _channelID.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_RFC5646SpokenLanguage),
        _spokenLanguage.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCATitle),
        _title.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCATitleVersion),
        _titleVersion.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCATitleSubVersion),
        _titleSubVersion.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCAEpisode),
        _episode.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCAPartitionKind),
        _partitionKind.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCAPartitionNumber),
        _partitionNumber.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCAAudioContentKind),
        _audioContentKind.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_MCALabelSubDescriptor_MCAAudioElementKind),
        _audioElementKind.address());

    // Initialize Required properties
    const aafUID_t zeroAUID = {0};
    _labelDictionaryID = zeroAUID;
    _linkID = makeUUID(zeroAUID);
    _tagSymbol = L"";
}



ImplAAFMCALabelSubDescriptor::~ImplAAFMCALabelSubDescriptor ()
{
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMCALabelSubDescriptor::Initialize(
    aafUID_constref dictionaryID,
    aafUID_constref linkID,
    aafCharacter_constptr pTagSymbol)
{
    if (pTagSymbol == 0)
        return AAFRESULT_NULL_PARAM;
    if( isInitialized() )
        return AAFRESULT_ALREADY_INITIALIZED;

    _labelDictionaryID = dictionaryID;
    _linkID = makeUUID(linkID);
    _tagSymbol = pTagSymbol;

    setInitialized();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMCALabelSubDescriptor::SetLabelDictionaryID(
    aafUID_constref dictionaryID)
{
    if (!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _labelDictionaryID = dictionaryID;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMCALabelSubDescriptor::GetLabelDictionaryID(
    aafUID_t* pDictionaryID)
{
    if (pDictionaryID == 0)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    *pDictionaryID = _labelDictionaryID;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMCALabelSubDescriptor::SetLinkID(
    aafUID_constref linkID)
{
    if (!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _linkID = makeUUID(linkID);

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMCALabelSubDescriptor::GetLinkID(
    aafUID_t* pLinkID)
{
    if (pLinkID == 0)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    *pLinkID = makeAUID(_linkID);

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetTagSymbol (
      aafCharacter_constptr pTagSymbol)
{
    if(pTagSymbol == NULL)
        return AAFRESULT_NULL_PARAM;
    if(wcslen(pTagSymbol)*sizeof(OMCharacter) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _tagSymbol = pTagSymbol;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetTagSymbol (
      aafCharacter* pTagSymbol,
      aafUInt32 bufSize)
{
    if(pTagSymbol == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    if(!_tagSymbol.copyToBuffer(pTagSymbol, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetTagSymbolBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    *pBufSize = _tagSymbol.size();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetTagName (
      aafCharacter_constptr pTagName)
{
    if(pTagName == NULL)
        return AAFRESULT_NULL_PARAM;
    if(wcslen(pTagName)*sizeof(OMCharacter) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _tagName = pTagName;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetTagName (
      aafCharacter* pTagName,
      aafUInt32 bufSize)
{
    if(pTagName == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_tagName.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    if(!_tagName.copyToBuffer(pTagName, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetTagNameBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_tagName.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pBufSize = _tagName.size();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMCALabelSubDescriptor::SetChannelID(
    aafUInt32 channelID)
{
    if (!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _channelID = channelID;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFMCALabelSubDescriptor::GetChannelID(
    aafUInt32* pChannelID)
{
    if (pChannelID == 0)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_channelID.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pChannelID = _channelID;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetRFC5646SpokenLanguage (
      const char*  pSpokenLanguage)
{
    if(pSpokenLanguage == NULL)
        return AAFRESULT_NULL_PARAM;
    if(strlen(reinterpret_cast<const char*>(pSpokenLanguage)) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _spokenLanguage = pSpokenLanguage;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetRFC5646SpokenLanguage (
      char* pSpokenLanguage,
      aafUInt32 bufSize)
{
    if(pSpokenLanguage == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_spokenLanguage.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    if(!_spokenLanguage.copyToBuffer(pSpokenLanguage, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetRFC5646SpokenLanguageBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_spokenLanguage.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

	*pBufSize = _spokenLanguage.size();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetTitle (
      aafCharacter_constptr pTitle)
{
    if(pTitle == NULL)
        return AAFRESULT_NULL_PARAM;
    if(wcslen(pTitle)*sizeof(OMCharacter) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _title = pTitle;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetTitle (
      aafCharacter* pTitle,
      aafUInt32 bufSize)
{
    if(pTitle == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_title.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    if(!_title.copyToBuffer(pTitle, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetTitleBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_title.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pBufSize = _title.size();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetTitleVersion (
      aafCharacter_constptr pTitleVersion)
{
    if(pTitleVersion == NULL)
        return AAFRESULT_NULL_PARAM;
    if(wcslen(pTitleVersion)*sizeof(OMCharacter) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _titleVersion = pTitleVersion;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetTitleVersion (
      aafCharacter* pTitleVersion,
      aafUInt32 bufSize)
{
    if(pTitleVersion == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_titleVersion.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    if(!_titleVersion.copyToBuffer(pTitleVersion, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetTitleVersionBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_titleVersion.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pBufSize = _titleVersion.size();

    return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetTitleSubVersion (
      aafCharacter_constptr pTitleSubVersion)
{
    if(pTitleSubVersion == NULL)
        return AAFRESULT_NULL_PARAM;
    if(wcslen(pTitleSubVersion)*sizeof(OMCharacter) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _titleSubVersion = pTitleSubVersion;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetTitleSubVersion (
      aafCharacter* pTitleSubVersion,
      aafUInt32 bufSize)
{
    if(pTitleSubVersion == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_titleSubVersion.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    if(!_titleSubVersion.copyToBuffer(pTitleSubVersion, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetTitleSubVersionBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_titleSubVersion.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pBufSize = _titleSubVersion.size();

    return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetEpisode (
      aafCharacter_constptr pEpisode)
{
    if(pEpisode == NULL)
        return AAFRESULT_NULL_PARAM;
    if(wcslen(pEpisode)*sizeof(OMCharacter) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _episode = pEpisode;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetEpisode (
      aafCharacter* pEpisode,
      aafUInt32 bufSize)
{
    if(pEpisode == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_episode.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    if(!_episode.copyToBuffer(pEpisode, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetEpisodeBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_episode.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pBufSize = _episode.size();

    return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetPartitionKind (
      aafCharacter_constptr pPartitionKind)
{
    if(pPartitionKind == NULL)
        return AAFRESULT_NULL_PARAM;
    if(wcslen(pPartitionKind)*sizeof(OMCharacter) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _partitionKind = pPartitionKind;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetPartitionKind (
      aafCharacter* pPartitionKind,
      aafUInt32 bufSize)
{
    if(pPartitionKind == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_partitionKind.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    if(!_partitionKind.copyToBuffer(pPartitionKind, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetPartitionKindBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_partitionKind.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pBufSize = _partitionKind.size();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetPartitionNumber (
      aafCharacter_constptr pPartitionNumber)
{
    if(pPartitionNumber == NULL)
        return AAFRESULT_NULL_PARAM;
    if(wcslen(pPartitionNumber)*sizeof(OMCharacter) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _partitionNumber = pPartitionNumber;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetPartitionNumber (
      aafCharacter* pPartitionNumber,
      aafUInt32 bufSize)
{
    if(pPartitionNumber == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_partitionNumber.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    if(!_partitionNumber.copyToBuffer(pPartitionNumber, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetPartitionNumberBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_partitionNumber.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pBufSize = _partitionNumber.size();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetAudioContentKind (
      aafCharacter_constptr pAudioContentKind)
{
    if(pAudioContentKind == NULL)
        return AAFRESULT_NULL_PARAM;
    if(wcslen(pAudioContentKind)*sizeof(OMCharacter) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _audioContentKind = pAudioContentKind;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetAudioContentKind (
      aafCharacter* pAudioContentKind,
      aafUInt32 bufSize)
{
    if(pAudioContentKind == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_audioContentKind.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    if(!_audioContentKind.copyToBuffer(pAudioContentKind, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetAudioContentKindBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_audioContentKind.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pBufSize = _audioContentKind.size();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::SetAudioElementKind (
      aafCharacter_constptr pAudioElementKind)
{
    if(pAudioElementKind == NULL)
        return AAFRESULT_NULL_PARAM;
    if(wcslen(pAudioElementKind)*sizeof(OMCharacter) >= OMPROPERTYSIZE_MAX)
        return AAFRESULT_BAD_SIZE;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;

    _audioElementKind = pAudioElementKind;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetAudioElementKind (
      aafCharacter* pAudioElementKind,
      aafUInt32 bufSize)
{
    if(pAudioElementKind == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_audioElementKind.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    if(!_audioElementKind.copyToBuffer(pAudioElementKind, bufSize))
        return AAFRESULT_SMALLBUF;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFMCALabelSubDescriptor::GetAudioElementKindBufLen (
      aafUInt32* pBufSize)
{
    if(pBufSize == NULL)
        return AAFRESULT_NULL_PARAM;
    if(!isInitialized())
        return AAFRESULT_NOT_INITIALIZED;
    if (!_audioElementKind.isPresent())
        return AAFRESULT_PROP_NOT_PRESENT;

    *pBufSize = _audioElementKind.size();

    return AAFRESULT_SUCCESS;
}



/*static*/
aafUID_t ImplAAFMCALabelSubDescriptor::makeAUID(const UUID_t& uuid)
{
    assert(sizeof(aafUID_t) == sizeof(UUID_t));

    aafUID_t auid = {0};
    memcpy(&auid, &uuid, sizeof(auid));

    if (hostByteOrder() == littleEndian)
    {
        OMType::reorderInteger(reinterpret_cast<OMByte*>(&auid.Data1), sizeof(auid.Data1));
        OMType::reorderInteger(reinterpret_cast<OMByte*>(&auid.Data2), sizeof(auid.Data2));
        OMType::reorderInteger(reinterpret_cast<OMByte*>(&auid.Data3), sizeof(auid.Data3));
    }

    return auid;
}



/*static*/
ImplAAFMCALabelSubDescriptor::UUID_t ImplAAFMCALabelSubDescriptor::makeUUID(const aafUID_t& auid)
{
    UUID_t uuid;
    memcpy(&uuid, &auid, sizeof(uuid));

    if (hostByteOrder() == littleEndian)
    {
        aafUID_t& out = *reinterpret_cast<aafUID_t*>(&uuid);
        OMType::reorderInteger(reinterpret_cast<OMByte*>(&out.Data1), sizeof(out.Data1));
        OMType::reorderInteger(reinterpret_cast<OMByte*>(&out.Data2), sizeof(out.Data2));
        OMType::reorderInteger(reinterpret_cast<OMByte*>(&out.Data3), sizeof(out.Data3));
    }

    return uuid;
}


