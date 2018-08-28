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



static const struct CAAFAudioChannelLabelSubDescriptorTestFixture
{
    aafMobID_t      sourceMobID;

} gTestData = 
{
    // sourceMobID
    { { 0x06, 0x0c, 0x2b, 0x34,
        0x02, 0x05, 0x11, 0x01,
        0x01, 0x00, 0x10, 0x00 },
      0x13, 0x00, 0x00, 0x00,
      { 0x72547144, 0x58aa, 0x4ba8,
        { 0x8b, 0x92, 0x50, 0xdb, 0x04, 0xb8, 0xad, 0xe3 } } },
};



static HRESULT Test_IAAFAudioChannelLabelSubDescriptor_Uninitialized(
    IAAFAudioChannelLabelSubDescriptor* pChannelLabelDesc)
{
    HRESULT  hr = S_OK;


    try
    {
        const aafUID_t  dummy = {0};
        hr = pChannelLabelDesc->SetSoundfieldGroupLinkID(dummy);
        CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

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



static HRESULT Test_IAAFAudioChannelLabelSubDescriptor_Initialize(
    IAAFAudioChannelLabelSubDescriptor* pChannelLabelDesc)
{
    HRESULT  hr = S_OK;


    try
    {
        const aafUID_t dictionaryLabelID = 
            { 0x03020120, 0x0100, 0x0000,
              { 0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d } };
        const aafUID_t linkID =
            { 0xe36200fa, 0x978b, 0x416a,
              { 0xa7, 0xc1, 0x43, 0xf8, 0xcb, 0x70, 0x16, 0x17 } };
        const aafCharacter* pTagSymbol = L"TestTagSymbol135";

        // Initialize with invalid arguments
        hr = pChannelLabelDesc->Initialize(dictionaryLabelID,
                                           linkID,
                                           NULL);
        CheckExpression(hr == AAFRESULT_NULL_PARAM);

        // Initialize AudioChannelLabelSubDescriptor object
        CheckResult(pChannelLabelDesc->Initialize(dictionaryLabelID,
                                                  linkID,
                                                  pTagSymbol));

        // Double initialize
        hr = pChannelLabelDesc->Initialize(dictionaryLabelID,
                                           linkID,
                                           pTagSymbol);
        CheckExpression(hr == AAFRESULT_ALREADY_INITIALIZED);

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



static HRESULT Test_IAAFAudioChannelLabelSubDescriptor(
    IAAFAudioChannelLabelSubDescriptor* pChannelLabelDesc,
    testMode_t mode)
{
    HRESULT  hr = S_OK;


    try
    {
        const aafUID_t initialGroupID = {0}; // unused
        const aafUID_t testGroupID =
            { 0x1f8274c, 0x7590, 0x4cdb,
              { 0xb5, 0x7e, 0xcf, 0xaa, 0x3b, 0x7b, 0x60, 0xcb } };
        const aafUID_t anotherGroupID =
            { 0xed38f1d4, 0x572d, 0x42d5,
              { 0x8f, 0x33, 0xa5, 0xe7, 0x3b, 0x0b, 0xf1, 0xf4 } };

		CheckResult(TestSimplePropertyAccess(
            &IAAFAudioChannelLabelSubDescriptor::SetSoundfieldGroupLinkID,
            &IAAFAudioChannelLabelSubDescriptor::GetSoundfieldGroupLinkID,
            pChannelLabelDesc,
            initialGroupID,
            testGroupID,
            anotherGroupID,
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


        // Create a AudioChannelLabelSubDescriptor
        IAAFSmartPointer<IAAFAudioChannelLabelSubDescriptor> pChannelLabelDesc;
        CheckResult(defs.cdAudioChannelLabelSubDescriptor()->CreateInstance(
            IID_IAAFAudioChannelLabelSubDescriptor,
            (IUnknown **)&pChannelLabelDesc));

        // Before initialization test if the SoundDescriptor
        // methods return valid error values.
        CheckResult(Test_IAAFAudioChannelLabelSubDescriptor_Uninitialized(pChannelLabelDesc));

        // Initialize
        Test_IAAFAudioChannelLabelSubDescriptor_Initialize(pChannelLabelDesc);

        // Create a SoundDescriptor
        IAAFSmartPointer<IAAFSoundDescriptor> pSoundDesc;
        CheckResult(defs.cdSoundDescriptor()->CreateInstance(
            IID_IAAFSoundDescriptor,
            (IUnknown **)&pSoundDesc));

        // Attach the IAAFAudioChannelLabelSubDescriptor to the SoundDescriptor
        IAAFSmartPointer<IAAFSubDescriptor> pSubDesc;
        CheckResult(pChannelLabelDesc->QueryInterface(IID_IAAFSubDescriptor,
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
        CheckResult(pMob->SetName(L"AudioChannelLabelSubDescriptorTest"));

        // Attach the descriptor to the source mob
        IAAFSmartPointer<IAAFEssenceDescriptor> pSoundDesc_EssenceDesc;
        CheckResult(pSoundDesc->QueryInterface(IID_IAAFEssenceDescriptor,
                                              (void **)&pSoundDesc_EssenceDesc));
        CheckResult(pSourceMob->SetEssenceDescriptor(pSoundDesc_EssenceDesc));

        // Attach the source mob to the file
        CheckResult(pHeader->AddMob(pMob));


        // Test initialized AudioChannelLabelSubDescriptor.
        CheckResult(Test_IAAFAudioChannelLabelSubDescriptor(pChannelLabelDesc,
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

        // Get the AudioChannelLabelSubDescriptor
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
        IAAFSmartPointer<IAAFAudioChannelLabelSubDescriptor> pChannelLabelDesc;
        CheckResult(pSubDesc->QueryInterface(IID_IAAFAudioChannelLabelSubDescriptor,
                                             (void **)&pChannelLabelDesc));


        CheckResult(Test_IAAFAudioChannelLabelSubDescriptor(pChannelLabelDesc,
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
extern "C" HRESULT CAAFAudioChannelLabelSubDescriptor_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);

//
// The public entry for this module test,
//
HRESULT CAAFAudioChannelLabelSubDescriptor_test(
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
        cerr << "CAAFAudioChannelLabelSubDescriptor_test...Caught general C++"
             << " exception!" << endl; 
        hr = AAFRESULT_TEST_FAILED;
    }


    return hr;
}


