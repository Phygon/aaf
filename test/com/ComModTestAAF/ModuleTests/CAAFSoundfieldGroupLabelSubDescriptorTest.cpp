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



static const struct CAAFSoundfieldGroupLabelSubDescriptorTestFixture
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



static HRESULT Test_IAAFSoundfieldGroupLabelSubDescriptor_Uninitialized(
    IAAFSoundfieldGroupLabelSubDescriptor* pGroupLabelDesc)
{
    HRESULT  hr = S_OK;


    try
    {
        const aafUID_t  dummy = {0};
        hr = pGroupLabelDesc->AppendGroupOfSoundfieldGroupsLinkID(dummy);
        CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        aafUInt32 count = 2384;
        hr = pGroupLabelDesc->CountGroupOfSoundfieldGroupsLinkIDs(&count);
        CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        CheckExpression(count == 2384);
        aafUID_t v = { 0x6e025119 };
        hr = pGroupLabelDesc->GetGroupOfSoundfieldGroupsLinkIDAt(0, &v);
        CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
        CheckExpression(v.Data1 == 0x6e025119);

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



static HRESULT Test_IAAFSoundfieldGroupLabelSubDescriptor_Initialize(
    IAAFSoundfieldGroupLabelSubDescriptor* pGroupLabelDesc)
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
        hr = pGroupLabelDesc->Initialize(dictionaryLabelID,
                                         linkID,
                                         NULL);
        CheckExpression(hr == AAFRESULT_NULL_PARAM);

        // Initialize SoundfieldGroupLabelSubDescriptor object
        CheckResult(pGroupLabelDesc->Initialize(dictionaryLabelID,
                                                linkID,
                                                pTagSymbol));

        // Double initialize
        hr = pGroupLabelDesc->Initialize(dictionaryLabelID,
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



static HRESULT Test_IAAFSoundfieldGroupLabelSubDescriptor(
    IAAFSoundfieldGroupLabelSubDescriptor* pGroupLabelDesc,
    testMode_t mode)
{
    HRESULT  hr = S_OK;


    try
    {
        const aafUID_t groupsOfGroups[] =
        {
            { 0x1f8274c, 0x7590, 0x4cdb,
              { 0xb5, 0x7e, 0xcf, 0xaa, 0x3b, 0x7b, 0x60, 0xcb } },
            { 0xa78ac05a, 0x5815, 0x4b3b,
              { 0xb7, 0x83, 0xa3, 0xc1, 0x16, 0xd3, 0x0b, 0x9f } },
            { 0xdec3f8aa, 0x899b, 0x4ee6,
              { 0xb7, 0xa3, 0xe, 0x1c, 0x67, 0x69, 0x9d, 0x64 } }
        };
        const aafUInt32 groupsOfGroupsCount =
            sizeof(groupsOfGroups) / sizeof(groupsOfGroups[0]);

        if(mode == kAAFUnitTestReadWrite)
        {
            // Get() calls should fail because the property is optional
            // and not present.
            aafUInt32 count = 82;
            hr = pGroupLabelDesc->CountGroupOfSoundfieldGroupsLinkIDs(&count);
            CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
            // A failed call should not alter the output buffer
            CheckExpression(count == 82);

            aafUID_t dummy = {0x4e087e58};
            hr = pGroupLabelDesc->GetGroupOfSoundfieldGroupsLinkIDAt(0, &dummy);
            CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
            // A failed call should not alter the output buffer
            CheckExpression(dummy.Data1 == 0x4e087e58);

            // Invalid arguments should be rejected regardless of
            // whether a property is present.
            hr = pGroupLabelDesc->CountGroupOfSoundfieldGroupsLinkIDs(NULL);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pGroupLabelDesc->GetGroupOfSoundfieldGroupsLinkIDAt(0, NULL);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);

            for (aafUInt32 i=0; i<groupsOfGroupsCount; i++)
            {
                // SetXXX() should succeed
                CheckResult(pGroupLabelDesc->AppendGroupOfSoundfieldGroupsLinkID(groupsOfGroups[i]));
            }

            // Cannot append duplicates
            for (aafUInt32 i=0; i<groupsOfGroupsCount; i++)
            {
                // SetXXX() should succeed
                hr = pGroupLabelDesc->AppendGroupOfSoundfieldGroupsLinkID(groupsOfGroups[i]);
                CheckExpression(hr == AAFRESULT_INVALID_PARAM);
            }
        }

        if(mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly)
        {
            aafUInt32 count = 562;
            CheckResult(pGroupLabelDesc->CountGroupOfSoundfieldGroupsLinkIDs(&count));
            CheckExpression(count == groupsOfGroupsCount);

            for (aafUInt32 i=0; i<groupsOfGroupsCount; i++)
            {
                // GetXXX() should succeed
                aafUID_t linkID = {0x76e33ac6};
                CheckResult(pGroupLabelDesc->GetGroupOfSoundfieldGroupsLinkIDAt(i, &linkID));
                CheckExpression(linkID == groupsOfGroups[i]);
            }
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


        // Create a SoundfieldGroupLabelSubDescriptor
        IAAFSmartPointer<IAAFSoundfieldGroupLabelSubDescriptor> pGroupLabelDesc;
        CheckResult(defs.cdSoundfieldGroupLabelSubDescriptor()->CreateInstance(
            IID_IAAFSoundfieldGroupLabelSubDescriptor,
            (IUnknown **)&pGroupLabelDesc));

        // Before initialization test if the SoundDescriptor
        // methods return valid error values.
        CheckResult(Test_IAAFSoundfieldGroupLabelSubDescriptor_Uninitialized(pGroupLabelDesc));

        // Initialize
        Test_IAAFSoundfieldGroupLabelSubDescriptor_Initialize(pGroupLabelDesc);

        // Create a SoundDescriptor
        IAAFSmartPointer<IAAFSoundDescriptor> pSoundDesc;
        CheckResult(defs.cdSoundDescriptor()->CreateInstance(
            IID_IAAFSoundDescriptor,
            (IUnknown **)&pSoundDesc));

        // Attach the IAAFSoundfieldGroupLabelSubDescriptor to the SoundDescriptor
        IAAFSmartPointer<IAAFSubDescriptor> pSubDesc;
        CheckResult(pGroupLabelDesc->QueryInterface(IID_IAAFSubDescriptor,
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
        CheckResult(pMob->SetName(L"SoundfieldGroupLabelSubDescriptorTest"));

        // Attach the descriptor to the source mob
        IAAFSmartPointer<IAAFEssenceDescriptor> pSoundDesc_EssenceDesc;
        CheckResult(pSoundDesc->QueryInterface(IID_IAAFEssenceDescriptor,
                                              (void **)&pSoundDesc_EssenceDesc));
        CheckResult(pSourceMob->SetEssenceDescriptor(pSoundDesc_EssenceDesc));

        // Attach the source mob to the file
        CheckResult(pHeader->AddMob(pMob));


        // Test initialized SoundfieldGroupLabelSubDescriptor.
        CheckResult(Test_IAAFSoundfieldGroupLabelSubDescriptor(pGroupLabelDesc,
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

        // Get the SoundfieldGroupLabelSubDescriptor
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
        IAAFSmartPointer<IAAFSoundfieldGroupLabelSubDescriptor> pGroupLabelDesc;
        CheckResult(pSubDesc->QueryInterface(IID_IAAFSoundfieldGroupLabelSubDescriptor,
                                             (void **)&pGroupLabelDesc));


        CheckResult(Test_IAAFSoundfieldGroupLabelSubDescriptor(pGroupLabelDesc,
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
extern "C" HRESULT CAAFSoundfieldGroupLabelSubDescriptor_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);

//
// The public entry for this module test,
//
HRESULT CAAFSoundfieldGroupLabelSubDescriptor_test(
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
        cerr << "CAAFSoundfieldGroupLabelSubDescriptor_test...Caught general C++"
             << " exception!" << endl; 
        hr = AAFRESULT_TEST_FAILED;
    }


    return hr;
}


