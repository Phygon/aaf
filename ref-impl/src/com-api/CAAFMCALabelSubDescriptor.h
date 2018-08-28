//@doc
//@class    AAFMCALabelSubDescriptor | Implementation class for AAFMCALabelSubDescriptor
#ifndef __CAAFMCALabelSubDescriptor_h__
#define __CAAFMCALabelSubDescriptor_h__

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





#ifndef __CAAFSubDescriptor_h__
#include "CAAFSubDescriptor.h"
#endif


class CAAFMCALabelSubDescriptor
  : public IAAFMCALabelSubDescriptor,
    public CAAFSubDescriptor
{
protected:

  //********
  //
  // Constructor/destructor
  //
  CAAFMCALabelSubDescriptor (IUnknown * pControllingUnknown, aafBool doInit = kAAFTrue);
  virtual ~CAAFMCALabelSubDescriptor ();

public:


  //***********************************************************
  //
  // SetLabelDictionaryID()
  //
  // Set the globally registered SMPTE UL that defines the meaning
  /// of this MCALabelSubDescriptor instance.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MCALabelDictionaryID property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetLabelDictionaryID) (
    // Label dictionary ID. 
    /*[in]*/ aafUID_constref  dictionaryID);


  //***********************************************************
  //
  // GetLabelDictionaryID()
  //
  // Get the globally registered SMPTE UL that defines the meaning
  /// of this MCALabelSubDescriptor instance.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pDictionaryID pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pDictionaryID.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pDictionaryID arg is NULL.
  //
  STDMETHOD (GetLabelDictionaryID) (
    // Label dictionary ID. 
    /*[out]*/ aafUID_t *  pDictionaryID);


  //***********************************************************
  //
  // SetLinkID()
  //
  // Set UUID that uniquely identifies this MCALabelSubDescriptor
  /// instance and is used to link to it.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MCALinkID property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetLinkID) (
    // Link ID. 
    /*[in]*/ aafUID_constref  linkID);


  //***********************************************************
  //
  // GetLinkID()
  //
  // Get UUID that uniquely identifies this MCALabelSubDescriptor
  /// instance and is used to link to it.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pLinkID pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pLinkID.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pLinkID arg is NULL.
  //
  STDMETHOD (GetLinkID) (
    // Link ID. 
    /*[out]*/ aafUID_t *  pLinkID);


  //***********************************************************
  //
  // SetTagSymbol()
  //
  // Sets Symbol identifying this MCALabelSubDescriptor.
  ///
  /// Set the TagSymbol property to the value specified in
  /// pTagSymbol.  A copy is made of the data so the caller
  /// retains ownership of the *pTagSymbol buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pTagSymbol pointer is valid.
  /// 
  /// If this method fails the TagSymbol property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pTagSymbol arg is NULL.
  //
  STDMETHOD (SetTagSymbol) (
    // buffer from which TagSymbol is to be read 
    /*[in, string]*/ aafCharacter_constptr  pTagSymbol);


  //***********************************************************
  //
  // GetTagSymbol()
  //
  // Gets Symbol identifying this MCALabelSubDescriptor.
  /// 
  /// Writes the TagSymbol property, with a trailing null
  /// character, into the pTagSymbol buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the TagSymbol property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetTagSymbolBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pTagSymbol.
  /// 
  /// Succeeds if:
  /// - The pTagSymbol pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   TagSymbol.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pTagSymbol arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold TagSymbol.
  //
  STDMETHOD (GetTagSymbol) (
    // buffer into which TagSymbol is to be written
    /*[out, string, size_is(bufSize)]*/ aafCharacter *  pTagSymbol,

    // size of *pTagSymbol buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetTagSymbolBufLen()
  //
  // Returns size of buffer (in bytes) required for GetTagSymbol().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetTagSymbolBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);


  //***********************************************************
  //
  // SetTagName()
  //
  // Sets Name.
  ///
  /// Set the TagName property to the value specified in
  /// pTagName.  A copy is made of the data so the caller
  /// retains ownership of the *pTagName buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pTagName pointer is valid.
  /// 
  /// If this method fails the TagName property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pTagName arg is NULL.
  //
  STDMETHOD (SetTagName) (
    // buffer from which TagName is to be read 
    /*[in, string]*/ aafCharacter_constptr  pTagName);


  //***********************************************************
  //
  // GetTagName()
  //
  // Gets Name.
  /// 
  /// Writes the TagName property, with a trailing null
  /// character, into the pTagName buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the TagName property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetTagNameBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pTagName.
  /// 
  /// Succeeds if:
  /// - The pTagName pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   TagName.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pTagName arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold TagName.
  //
  STDMETHOD (GetTagName) (
    // buffer into which TagName is to be written
    /*[out, string, size_is(bufSize)]*/ aafCharacter *  pTagName,

    // size of *pTagName buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetTagNameBufLen()
  //
  // Returns size of buffer (in bytes) required for GetTagName().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetTagNameBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);


  //***********************************************************
  //
  // SetChannelID()
  //
  // Set the numerical channel identifier within the essence
  /// described by this MCALabelSubDescriptor.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the MCAChannelID property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetChannelID) (
    // Channel ID. 
    /*[in]*/ aafUInt32  channelID);


  //***********************************************************
  //
  // GetChannelID()
  //
  // Get the numerical channel identifier within the essence
  /// described by this MCALabelSubDescriptor.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pChannelID pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pChannelID.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pChannelID arg is NULL.
  //
  STDMETHOD (GetChannelID) (
    // Channel ID. 
    /*[out]*/ aafUInt32 *  pChannelID);


  //***********************************************************
  //
  // SetTitle()
  //
  // Sets Program title.
  ///
  /// Set the Title property to the value specified in
  /// pTitle.  A copy is made of the data so the caller
  /// retains ownership of the *pTitle buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pTitle pointer is valid.
  /// 
  /// If this method fails the Title property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pTitle arg is NULL.
  //
  STDMETHOD (SetTitle) (
    // buffer from which Title is to be read 
    /*[in, string]*/ aafCharacter_constptr  pTitle);


  //***********************************************************
  //
  // GetTitle()
  //
  // Gets Program title.
  /// 
  /// Writes the Title property, with a trailing null
  /// character, into the pTitle buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the Title property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetTitleBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pTitle.
  /// 
  /// Succeeds if:
  /// - The pTitle pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   Title.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pTitle arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold Title.
  //
  STDMETHOD (GetTitle) (
    // buffer into which Title is to be written
    /*[out, string, size_is(bufSize)]*/ aafCharacter *  pTitle,

    // size of *pTitle buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetTitleBufLen()
  //
  // Returns size of buffer (in bytes) required for GetTitle().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetTitleBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);


  //***********************************************************
  //
  // SetRFC5646SpokenLanguage()
  //
  // Sets RFC 5646 Spoken Language.
  ///
  /// Set the RFC5646SpokenLanguage property to the value specified in
  /// pRFC5646SpokenLanguage.  A copy is made of the data so the caller
  /// retains ownership of the *pRFC5646SpokenLanguage buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pRFC5646SpokenLanguage pointer is valid.
  /// 
  /// If this method fails the RFC5646SpokenLanguage property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pRFC5646SpokenLanguage arg is NULL.
  //
  STDMETHOD (SetRFC5646SpokenLanguage) (
    // NULL-terminated US-ASCII string specifying RFC 5646 compliant language tag. 
    /*[in, string]*/ const char *  pRFC5646SpokenLanguage);


  //***********************************************************
  //
  // GetRFC5646SpokenLanguage()
  //
  // Gets RFC 5646 Spoken Language.
  /// 
  /// Writes the RFC5646SpokenLanguage property, with a trailing null
  /// character, into the pRFC5646SpokenLanguage buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the RFC5646SpokenLanguage property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetRFC5646SpokenLanguageBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pRFC5646SpokenLanguage.
  /// 
  /// Succeeds if:
  /// - The pRFC5646SpokenLanguage pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   RFC5646SpokenLanguage.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pRFC5646SpokenLanguage arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold RFC5646SpokenLanguage.
  //
  STDMETHOD (GetRFC5646SpokenLanguage) (
    // buffer into which RFC5646SpokenLanguage is to be written
    /*[out, string, size_is(bufSize)]*/ char *  pRFC5646SpokenLanguage,

    // size of *pRFC5646SpokenLanguage buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetRFC5646SpokenLanguageBufLen()
  //
  // Returns size of buffer (in bytes) required for GetRFC5646SpokenLanguage().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetRFC5646SpokenLanguageBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);


  //***********************************************************
  //
  // SetTitleVersion()
  //
  // Sets Program version.
  ///
  /// Set the TitleVersion property to the value specified in
  /// pTitleVersion.  A copy is made of the data so the caller
  /// retains ownership of the *pTitleVersion buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pTitleVersion pointer is valid.
  /// 
  /// If this method fails the TitleVersion property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pTitleVersion arg is NULL.
  //
  STDMETHOD (SetTitleVersion) (
    // buffer from which TitleVersion is to be read 
    /*[in, string]*/ aafCharacter_constptr  pTitleVersion);


  //***********************************************************
  //
  // GetTitleVersion()
  //
  // Gets Program version.
  /// 
  /// Writes the TitleVersion property, with a trailing null
  /// character, into the pTitleVersion buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the TitleVersion property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetTitleVersionBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pTitleVersion.
  /// 
  /// Succeeds if:
  /// - The pTitleVersion pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   TitleVersion.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pTitleVersion arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold TitleVersion.
  //
  STDMETHOD (GetTitleVersion) (
    // buffer into which TitleVersion is to be written
    /*[out, string, size_is(bufSize)]*/ aafCharacter *  pTitleVersion,

    // size of *pTitleVersion buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetTitleVersionBufLen()
  //
  // Returns size of buffer (in bytes) required for GetTitleVersion().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetTitleVersionBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);


  //***********************************************************
  //
  // SetTitleSubVersion()
  //
  // Sets Program sub-version.
  ///
  /// Set the TitleSubVersion property to the value specified in
  /// pTitleSubVersion.  A copy is made of the data so the caller
  /// retains ownership of the *pTitleSubVersion buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pTitleSubVersion pointer is valid.
  /// 
  /// If this method fails the TitleSubVersion property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pTitleSubVersion arg is NULL.
  //
  STDMETHOD (SetTitleSubVersion) (
    // buffer from which TitleSubVersion is to be read 
    /*[in, string]*/ aafCharacter_constptr  pTitleSubVersion);


  //***********************************************************
  //
  // GetTitleSubVersion()
  //
  // Gets Program sub-version.
  /// 
  /// Writes the TitleSubVersion property, with a trailing null
  /// character, into the pTitleSubVersion buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the TitleSubVersion property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetTitleSubVersionBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pTitleSubVersion.
  /// 
  /// Succeeds if:
  /// - The pTitleSubVersion pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   TitleSubVersion.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pTitleSubVersion arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold TitleSubVersion.
  //
  STDMETHOD (GetTitleSubVersion) (
    // buffer into which TitleSubVersion is to be written
    /*[out, string, size_is(bufSize)]*/ aafCharacter *  pTitleSubVersion,

    // size of *pTitleSubVersion buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetTitleSubVersionBufLen()
  //
  // Returns size of buffer (in bytes) required for GetTitleSubVersion().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetTitleSubVersionBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);


  //***********************************************************
  //
  // SetEpisode()
  //
  // Sets Program episode.
  ///
  /// Set the Episode property to the value specified in
  /// pEpisode.  A copy is made of the data so the caller
  /// retains ownership of the *pEpisode buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pEpisode pointer is valid.
  /// 
  /// If this method fails the Episode property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pEpisode arg is NULL.
  //
  STDMETHOD (SetEpisode) (
    // buffer from which Episode is to be read 
    /*[in, string]*/ aafCharacter_constptr  pEpisode);


  //***********************************************************
  //
  // GetEpisode()
  //
  // Gets Program episode.
  /// 
  /// Writes the Episode property, with a trailing null
  /// character, into the pEpisode buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the Episode property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetEpisodeBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pEpisode.
  /// 
  /// Succeeds if:
  /// - The pEpisode pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   Episode.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pEpisode arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold Episode.
  //
  STDMETHOD (GetEpisode) (
    // buffer into which Episode is to be written
    /*[out, string, size_is(bufSize)]*/ aafCharacter *  pEpisode,

    // size of *pEpisode buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetEpisodeBufLen()
  //
  // Returns size of buffer (in bytes) required for GetEpisode().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetEpisodeBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);


  //***********************************************************
  //
  // SetPartitionKind()
  //
  // Sets Program partition kind.
  ///
  /// Set the PartitionKind property to the value specified in
  /// pPartitionKind.  A copy is made of the data so the caller
  /// retains ownership of the *pPartitionKind buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pPartitionKind pointer is valid.
  /// 
  /// If this method fails the PartitionKind property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pPartitionKind arg is NULL.
  //
  STDMETHOD (SetPartitionKind) (
    // buffer from which PartitionKind is to be read 
    /*[in, string]*/ aafCharacter_constptr  pPartitionKind);


  //***********************************************************
  //
  // GetPartitionKind()
  //
  // Gets Program partition kind.
  /// 
  /// Writes the PartitionKind property, with a trailing null
  /// character, into the pPartitionKind buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the PartitionKind property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetPartitionKindBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pPartitionKind.
  /// 
  /// Succeeds if:
  /// - The pPartitionKind pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   PartitionKind.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pPartitionKind arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold PartitionKind.
  //
  STDMETHOD (GetPartitionKind) (
    // buffer into which PartitionKind is to be written
    /*[out, string, size_is(bufSize)]*/ aafCharacter *  pPartitionKind,

    // size of *pPartitionKind buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetPartitionKindBufLen()
  //
  // Returns size of buffer (in bytes) required for GetPartitionKind().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetPartitionKindBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);


  //***********************************************************
  //
  // SetPartitionNumber()
  //
  // Sets Program partition number.
  ///
  /// Set the PartitionNumber property to the value specified in
  /// pPartitionNumber.  A copy is made of the data so the caller
  /// retains ownership of the *pPartitionNumber buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pPartitionNumber pointer is valid.
  /// 
  /// If this method fails the PartitionNumber property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pPartitionNumber arg is NULL.
  //
  STDMETHOD (SetPartitionNumber) (
    // buffer from which PartitionNumber is to be read 
    /*[in, string]*/ aafCharacter_constptr  pPartitionNumber);


  //***********************************************************
  //
  // GetPartitionNumber()
  //
  // Gets Program partition number.
  /// 
  /// Writes the PartitionNumber property, with a trailing null
  /// character, into the pPartitionNumber buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the PartitionNumber property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetPartitionNumberBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pPartitionNumber.
  /// 
  /// Succeeds if:
  /// - The pPartitionNumber pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   PartitionNumber.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pPartitionNumber arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold PartitionNumber.
  //
  STDMETHOD (GetPartitionNumber) (
    // buffer into which PartitionNumber is to be written
    /*[out, string, size_is(bufSize)]*/ aafCharacter *  pPartitionNumber,

    // size of *pPartitionNumber buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetPartitionNumberBufLen()
  //
  // Returns size of buffer (in bytes) required for GetPartitionNumber().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetPartitionNumberBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);


  //***********************************************************
  //
  // SetAudioContentKind()
  //
  // Sets Description of the audio content.
  ///
  /// Set the AudioContentKind property to the value specified in
  /// pAudioContentKind.  A copy is made of the data so the caller
  /// retains ownership of the *pAudioContentKind buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pAudioContentKind pointer is valid.
  /// 
  /// If this method fails the AudioContentKind property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pAudioContentKind arg is NULL.
  //
  STDMETHOD (SetAudioContentKind) (
    // buffer from which AudioContentKind is to be read 
    /*[in, string]*/ aafCharacter_constptr  pAudioContentKind);


  //***********************************************************
  //
  // GetAudioContentKind()
  //
  // Gets Description of the audio content.
  /// 
  /// Writes the AudioContentKind property, with a trailing null
  /// character, into the pAudioContentKind buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the AudioContentKind property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetAudioContentKindBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pAudioContentKind.
  /// 
  /// Succeeds if:
  /// - The pAudioContentKind pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   AudioContentKind.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pAudioContentKind arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold AudioContentKind.
  //
  STDMETHOD (GetAudioContentKind) (
    // buffer into which AudioContentKind is to be written
    /*[out, string, size_is(bufSize)]*/ aafCharacter *  pAudioContentKind,

    // size of *pAudioContentKind buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetAudioContentKindBufLen()
  //
  // Returns size of buffer (in bytes) required for GetAudioContentKind().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetAudioContentKindBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);


  //***********************************************************
  //
  // SetAudioElementKind()
  //
  // Sets Description of the audio element.
  ///
  /// Set the AudioElementKind property to the value specified in
  /// pAudioElementKind.  A copy is made of the data so the caller
  /// retains ownership of the *pAudioElementKind buffer and is
  /// responsible for de-allocating it.  There is no pre-set limit to
  /// the length of the name, other than available system memory or
  /// disk space.
  /// 
  /// Succeeds if all of the following are true:
  /// - the pAudioElementKind pointer is valid.
  /// 
  /// If this method fails the AudioElementKind property will not be
  /// changed.
  /// 
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pAudioElementKind arg is NULL.
  //
  STDMETHOD (SetAudioElementKind) (
    // buffer from which AudioElementKind is to be read 
    /*[in, string]*/ aafCharacter_constptr  pAudioElementKind);


  //***********************************************************
  //
  // GetAudioElementKind()
  //
  // Gets Description of the audio element.
  /// 
  /// Writes the AudioElementKind property, with a trailing null
  /// character, into the pAudioElementKind buffer.  The
  /// buffer is allocated by the caller.  The size of the buffer is
  /// given by bufSize.  If the AudioElementKind property has not yet
  /// been set, a zero-length string will be written (that is,
  /// only the trailing null character). 
  /// 
  /// Caller may call GetAudioElementKindBufLen() to determine the
  /// required buffer size.
  /// 
  /// If this method fails nothing will be written to
  /// *pAudioElementKind.
  /// 
  /// Succeeds if:
  /// - The pAudioElementKind pointer is valid.
  /// - bufSize indicates that the buffer is large enough to hold
  ///   AudioElementKind.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pAudioElementKind arg is NULL.
  ///
  /// AAFRESULT_SMALL_BUF
  ///   - bufSize indicates that the allocated buffer is not large
  ///     enough to hold AudioElementKind.
  //
  STDMETHOD (GetAudioElementKind) (
    // buffer into which AudioElementKind is to be written
    /*[out, string, size_is(bufSize)]*/ aafCharacter *  pAudioElementKind,

    // size of *pAudioElementKind buffer in bytes
    /*[in]*/ aafUInt32  bufSize);


  //***********************************************************
  //
  // GetAudioElementKindBufLen()
  //
  // Returns size of buffer (in bytes) required for GetAudioElementKind().
  /// 
  /// Succeeds if:
  /// - The pBufSize pointer is valid.
  //
  // This method will return the following codes.  If more than one of
  // the listed errors is in effect, it will return the first one
  // encountered in the order given below:
  // 
  // AAFRESULT_SUCCESS
  //   - succeeded.  (This is the only code indicating success.)
  //
  // AAFRESULT_NULL_PARAM
  //   - pBufSize arg is NULL.
  //
  STDMETHOD (GetAudioElementKindBufLen) (
    // size of required buffer, in bytes 
    /*[out]*/ aafUInt32 *  pBufSize);



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

#endif // ! __CAAFMCALabelSubDescriptor_h__


