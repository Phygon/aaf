//=---------------------------------------------------------------------=
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
// The Original Code of this file is Copyright 1998-2018, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
// The Initial Developer of the Original Code of this file and the
// licensor of the Advanced Media Workflow Association is
// Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

#include <iostream>

using namespace std;

#include <assert.h>
#include <string.h>

#include "AAF.h"
#include "AAFFileKinds.h"
#include "AAFResult.h"
#include "AAFPropertyDefs.h"
#include "AAFSmartPointer.h"

#include "CAAFBuiltinDefs.h"
#include "ModuleTestsCommon.h"
using namespace mtc;



static const struct CAAFMCALabelSubDescriptorTestFixture
{
    aafMobID_t      sourceMobID;
    aafUID_t        initialDictLabelID;
    aafUID_t        initialLinkID;
    aafCharacter*   pInitialTagSymbol;

} gTestData = 
{
    // sourceMobID
    { { 0x06, 0x0c, 0x2b, 0x34,
        0x02, 0x05, 0x11, 0x01,
        0x01, 0x00, 0x10, 0x00 },
      0x13, 0x00, 0x00, 0x00,
      { 0x8cc80e07, 0x4348, 0x45d3,
        { 0x9a, 0x6a, 0xbe, 0x3e, 0x12, 0x24, 0x0e, 0xfc } } },

    // initialDictLabelID
    // {03020120-0100-0000-060E-2B340401010d}
    // 06.0e.2b.34.04.01.01.0d.03.02.01.20.01.00.00.00
    { 0x03020120, 0x0100, 0x0000,
      { 0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d } },

    // initialLinkID
    // {2771A1DC-9F99-4b28-BCC5-7DBA040F6366}
    { 0x2771a1dc, 0x9f99, 0x4b28,
      { 0xbc, 0xc5, 0x7d, 0xba, 0x04, 0x0f, 0x63, 0x66 } },

    // pInitialTagSymbol
    L"MrMcTaggyTagSymbol"
};



static HRESULT Test_IAAFMCALabelSubDescriptor_Uninitialized(
    IAAFMCALabelSubDescriptor* pMCADesc)
{
    HRESULT  hr = S_OK;


    try
    {
		{
            const aafUID_t  dummy = {0};
            hr = pMCADesc->SetLabelDictionaryID(dummy);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUID_t  v = { 0x89abcdef };
            hr = pMCADesc->GetLabelDictionaryID(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v.Data1 == 0x89abcdef);
        }
		{
            const aafUID_t  dummy = {0};
            hr = pMCADesc->SetLinkID(dummy);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUID_t  v = {0x89abcdef};
            hr = pMCADesc->GetLinkID(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v.Data1 == 0x89abcdef);
        }
		{
            hr = pMCADesc->SetTagSymbol(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetTagSymbol(L"xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetTagSymbolBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetTagSymbolBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetTagSymbol(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }
		{
            hr = pMCADesc->SetTagName(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetTagName(L"xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetTagNameBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetTagNameBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetTagName(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }
        {
            hr = pMCADesc->SetChannelID(348756);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 3255;
            hr = pMCADesc->GetChannelID(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 3255);
        }
        {
            hr = pMCADesc->SetRFC5646SpokenLanguage(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetRFC5646SpokenLanguage("xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetTitleBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetTitleBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetTitle(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }
		{
            hr = pMCADesc->SetTitle(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetTitle(L"xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetTitleBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetTitleBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetTitle(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }
		{
            hr = pMCADesc->SetTitleVersion(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetTitleVersion(L"xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetTitleVersionBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetTitleVersionBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetTitleVersion(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }
		{
            hr = pMCADesc->SetTitleSubVersion(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetTitleSubVersion(L"xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetTitleSubVersionBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetTitleSubVersionBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetTitleSubVersion(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }
		{
            hr = pMCADesc->SetEpisode(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetEpisode(L"xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetEpisodeBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetEpisodeBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetEpisode(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }
		{
            hr = pMCADesc->SetPartitionKind(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetPartitionKind(L"xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetPartitionKindBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetPartitionKindBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetPartitionKind(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }
		{
            hr = pMCADesc->SetPartitionNumber(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetPartitionNumber(L"xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetPartitionNumberBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetPartitionNumberBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetPartitionNumber(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }
		{
            hr = pMCADesc->SetAudioContentKind(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetAudioContentKind(L"xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetAudioContentKindBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetAudioContentKindBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetAudioContentKind(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }
		{
            hr = pMCADesc->SetAudioElementKind(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pMCADesc->SetAudioElementKind(L"xyz");
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            hr = pMCADesc->GetAudioElementKindBufLen(0);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            aafUInt32  size = 98;
            hr = pMCADesc->GetAudioElementKindBufLen(&size);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            CheckExpression(size == 98);
            aafCharacter  v[] = {0};
            hr = pMCADesc->GetAudioElementKind(v, sizeof(v));
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        }

        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch(HRESULT e)
    {
        hr = e;
    }


    return hr;
}



static HRESULT Test_IAAFMCALabelSubDescriptor(
    IAAFMCALabelSubDescriptor* pMCADesc,
    testMode_t mode)
{
    HRESULT  hr = S_OK;


    try
    {
        {
            const aafUID_t testDictLabelID =
                { 0x03020120, 0x0200, 0x0000,
                  { 0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d } };
            const aafUID_t anotherDictLabelID =
                { 0x03020120, 0x0300, 0x0000,
                  { 0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d } };
		    CheckResult(TestSimplePropertyAccess(
                &IAAFMCALabelSubDescriptor::SetLabelDictionaryID,
                &IAAFMCALabelSubDescriptor::GetLabelDictionaryID,
                pMCADesc,
                gTestData.initialDictLabelID,
                testDictLabelID,
                anotherDictLabelID,
                true,
                mode));
        }

        {
            const aafUID_t testLinkID =
                { 0x63c2dc7b, 0x204a, 0x4479,
                  { 0x8a, 0xe9, 0x7b, 0x71, 0x79, 0xd8, 0x3, 0x41 } };
            const aafUID_t anotherLinkID =
                { 0xbd666a5a, 0x6a7c, 0x43b0,
                  { 0xab, 0x23, 0x93, 0x18, 0x4f, 0x57, 0xb2, 0x7b } };
		    CheckResult(TestSimplePropertyAccess(
                &IAAFMCALabelSubDescriptor::SetLinkID,
                &IAAFMCALabelSubDescriptor::GetLinkID,
                pMCADesc,
                gTestData.initialLinkID,
                testLinkID,
                anotherLinkID,
                true,
                mode));
        }

		CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetTagSymbol,
            &IAAFMCALabelSubDescriptor::GetTagSymbol,
            &IAAFMCALabelSubDescriptor::GetTagSymbolBufLen,
            pMCADesc,
            gTestData.pInitialTagSymbol,
            L"TestTagSymbol-3824",
            true,
            mode));

        CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetTagName,
            &IAAFMCALabelSubDescriptor::GetTagName,
            &IAAFMCALabelSubDescriptor::GetTagNameBufLen,
            pMCADesc,
            NULL,
            L"TestTagName-4347",
            false,
            mode));

		CheckResult(TestSimplePropertyAccess(
            &IAAFMCALabelSubDescriptor::SetChannelID,
            &IAAFMCALabelSubDescriptor::GetChannelID,
            pMCADesc,
            (aafUInt32)0, // will be ignored
            (aafUInt32)44,
            (aafUInt32)9,
            false,
            mode));

        CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetTitle,
            &IAAFMCALabelSubDescriptor::GetTitle,
            &IAAFMCALabelSubDescriptor::GetTitleBufLen,
            pMCADesc,
            NULL,
            L"TestTitle-1470",
            false,
            mode));

        CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetRFC5646SpokenLanguage,
            &IAAFMCALabelSubDescriptor::GetRFC5646SpokenLanguage,
            &IAAFMCALabelSubDescriptor::GetRFC5646SpokenLanguageBufLen,
            pMCADesc,
            NULL,
            "TestRFC5646SpokenLanguage-4398",
            false,
            mode));

        CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetTitleVersion,
            &IAAFMCALabelSubDescriptor::GetTitleVersion,
            &IAAFMCALabelSubDescriptor::GetTitleVersionBufLen,
            pMCADesc,
            NULL,
            L"TestTitleVersion-2304",
            false,
            mode));

        CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetTitleSubVersion,
            &IAAFMCALabelSubDescriptor::GetTitleSubVersion,
            &IAAFMCALabelSubDescriptor::GetTitleSubVersionBufLen,
            pMCADesc,
            NULL,
            L"TestTitleSubVersion-6523",
            false,
            mode));

        CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetEpisode,
            &IAAFMCALabelSubDescriptor::GetEpisode,
            &IAAFMCALabelSubDescriptor::GetEpisodeBufLen,
            pMCADesc,
            NULL,
            L"TestEpisode-1547",
            false,
            mode));

        CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetPartitionKind,
            &IAAFMCALabelSubDescriptor::GetPartitionKind,
            &IAAFMCALabelSubDescriptor::GetPartitionKindBufLen,
            pMCADesc,
            NULL,
            L"TestPartitionKind-2375",
            false,
            mode));

        CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetPartitionNumber,
            &IAAFMCALabelSubDescriptor::GetPartitionNumber,
            &IAAFMCALabelSubDescriptor::GetPartitionNumberBufLen,
            pMCADesc,
            NULL,
            L"TestPartitionNumber-9234",
            false,
            mode));

        CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetAudioContentKind,
            &IAAFMCALabelSubDescriptor::GetAudioContentKind,
            &IAAFMCALabelSubDescriptor::GetAudioContentKindBufLen,
            pMCADesc,
            NULL,
            L"TestAudioContentKind-5674",
            false,
            mode));

        CheckResult(TestStringPropertyAccess(
            &IAAFMCALabelSubDescriptor::SetAudioElementKind,
            &IAAFMCALabelSubDescriptor::GetAudioElementKind,
            &IAAFMCALabelSubDescriptor::GetAudioElementKindBufLen,
            pMCADesc,
            NULL,
            L"TestAudioElementKind-4595",
            false,
            mode));

        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch(HRESULT e)
    {
        hr = e;
    }


    return hr;
}



static HRESULT CreateAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_constref productID)
{
    HRESULT hr = S_OK;

    try
    {
        // Remove the previous test file if any.
        ::RemoveTestFile(pFileName);


        // Create the test file
        IAAFSmartPointer<IAAFFile> pFile;
        CheckResult(CreateTestFile(pFileName,
                                    fileKind,
                                    rawStorageType,
                                    productID,
                                    &pFile));


        // Get the AAF Dictionary
        IAAFSmartPointer<IAAFHeader> pHeader;
        CheckResult(pFile->GetHeader(&pHeader));
        IAAFSmartPointer<IAAFDictionary> pDictionary;
        CheckResult(pHeader->GetDictionary(&pDictionary));
        CAAFBuiltinDefs  defs (pDictionary);


        // Create a MCALabelSubDescriptor
        IAAFSmartPointer<IAAFMCALabelSubDescriptor> pMCADesc;
        CheckResult(defs.cdGroupOfSoundfieldGroupsLabelSubDescriptor()->CreateInstance(
            IID_IAAFMCALabelSubDescriptor,
            (IUnknown **)&pMCADesc));
        IAAFSmartPointer<IAAFGroupOfSoundfieldGroupsLabelSubDescriptor> pGroupsLabelSubDesc;
        CheckResult(pMCADesc->QueryInterface(IID_IAAFGroupOfSoundfieldGroupsLabelSubDescriptor,
                                                  (void **)&pGroupsLabelSubDesc));

        // Before initialization test if the IAAFMCALabelSubDescriptor
        // methods return valid error values.
        CheckResult(Test_IAAFMCALabelSubDescriptor_Uninitialized(pMCADesc));

        // Initialize IAAFGroupOfSoundfieldGroupsLabelSubDescriptor instance 
        CheckResult(pGroupsLabelSubDesc->Initialize(gTestData.initialDictLabelID,
                                                    gTestData.initialLinkID,
                                                    gTestData.pInitialTagSymbol));

        // Create a SoundDescriptor
        IAAFSmartPointer<IAAFSoundDescriptor> pSoundDesc;
        CheckResult(defs.cdSoundDescriptor()->CreateInstance(
            IID_IAAFSoundDescriptor,
            (IUnknown **)&pSoundDesc));

        // Attach the IAAFMCALabelSubDescriptor to the SoundDescriptor
        IAAFSmartPointer<IAAFSubDescriptor> pSubDesc;
        CheckResult(pMCADesc->QueryInterface(IID_IAAFSubDescriptor,
                                                  (void **)&pSubDesc));
        IAAFSmartPointer<IAAFEssenceDescriptor2> pSoundDesc_EssenceDesc2;
        CheckResult(pSoundDesc->QueryInterface(IID_IAAFEssenceDescriptor2,
                                              (void **)&pSoundDesc_EssenceDesc2));
        CheckResult(pSoundDesc_EssenceDesc2->AppendSubDescriptor(pSubDesc));

        // Create a mob, set its ID
        IAAFSmartPointer<IAAFSourceMob> pSourceMob;
        CheckResult(defs.cdSourceMob()->CreateInstance(IID_IAAFSourceMob,
                                                        (IUnknown **)&pSourceMob));
        IAAFSmartPointer<IAAFMob> pMob;
        CheckResult(pSourceMob->QueryInterface (IID_IAAFMob, (void **)&pMob));
        CheckResult(pMob->SetMobID(gTestData.sourceMobID));
        CheckResult(pMob->SetName(L"MCALabelSubDescriptorTest"));

        // Attach the descriptor to the source mob
        IAAFSmartPointer<IAAFEssenceDescriptor> pSoundDesc_EssenceDesc;
        CheckResult(pSoundDesc->QueryInterface(IID_IAAFEssenceDescriptor,
                                              (void **)&pSoundDesc_EssenceDesc));
        CheckResult(pSourceMob->SetEssenceDescriptor(pSoundDesc_EssenceDesc));

        // Attach the source mob to the file
        CheckResult(pHeader->AddMob(pMob));


        // Test initialized MCALabelSubDescriptor.
        CheckResult(Test_IAAFMCALabelSubDescriptor(pMCADesc,
                                                   kAAFUnitTestReadWrite));


        // Save and close the file
        CheckResult(pFile->Save());
        CheckResult(pFile->Close());
    }
    catch (HRESULT& rResult)
    {
        hr = rResult;
    }

    return hr;
}



static HRESULT ReadAAFFile(
    aafWChar * pFileName)
{
    HRESULT                 hr = S_OK;

    try
    {
        // Open the test file
        IAAFSmartPointer<IAAFFile> pFile;
        CheckResult(AAFFileOpenExistingRead(pFileName, 0, &pFile));
        IAAFSmartPointer<IAAFHeader> pHeader;
        CheckResult(pFile->GetHeader(&pHeader));

        // Get the source mob
        IAAFSmartPointer<IAAFMob> pMob;
        CheckResult(pHeader->LookupMob(gTestData.sourceMobID, &pMob));
        IAAFSmartPointer<IAAFSourceMob> pSourceMob;
        CheckResult(pMob->QueryInterface(IID_IAAFSourceMob,
                                         (void **)&pSourceMob));

        // Get the MCALabelSubDescriptor
        IAAFSmartPointer<IAAFEssenceDescriptor> pEssenceDesc;
        CheckResult(pSourceMob->GetEssenceDescriptor(&pEssenceDesc));
        IAAFSmartPointer<IAAFEssenceDescriptor2> pEssenceDesc2;
        CheckResult(pEssenceDesc->QueryInterface(IID_IAAFEssenceDescriptor2,
                                                 (void **)&pEssenceDesc2));
        aafUInt32 subdescriptorCount = 0;
        CheckResult(pEssenceDesc2->CountSubDescriptors(&subdescriptorCount));
        CheckExpression(subdescriptorCount == 1);
        IAAFSmartPointer<IAAFSubDescriptor> pSubDesc;
        CheckResult(pEssenceDesc2->GetSubDescriptorAt(0 , &pSubDesc));
        IAAFSmartPointer<IAAFMCALabelSubDescriptor> pMCADesc;
        CheckResult(pSubDesc->QueryInterface(IID_IAAFMCALabelSubDescriptor,
                                              (void **)&pMCADesc));


        CheckResult(Test_IAAFMCALabelSubDescriptor(pMCADesc,
                                                   kAAFUnitTestReadOnly));

        CheckResult(pFile->Close());
    }
    catch (HRESULT& rResult)
    {
        hr = rResult;
    }


    return hr;
}



// Required function prototype.
extern "C" HRESULT CAAFMCALabelSubDescriptor_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);

//
// The public entry for this module test,
//
HRESULT CAAFMCALabelSubDescriptor_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID)
{
    HRESULT  hr = AAFRESULT_NOT_IMPLEMENTED;
    const size_t fileNameBufLen = 128;
    aafWChar pFileName[ fileNameBufLen ] = L"";
    GenerateTestFileName(productID.productName, fileKind, fileNameBufLen, pFileName);


    try
    {
        if(mode == kAAFUnitTestReadWrite)
            hr = CreateAAFFile(pFileName, fileKind, rawStorageType, productID);
        else
            hr = AAFRESULT_SUCCESS;
        if(hr == AAFRESULT_SUCCESS)
            hr = ReadAAFFile(pFileName);
    }
    catch (...)
    {
        cerr << "CAAFMCALabelSubDescriptor_test...Caught general C++"
             << " exception!" << endl; 
        hr = AAFRESULT_TEST_FAILED;
    }


    return hr;
}

