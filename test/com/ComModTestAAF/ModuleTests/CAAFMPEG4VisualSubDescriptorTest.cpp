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



struct CAAFMPEG4VisualSubDescriptorTestFixture
{
    aafMobID_t              sourceMobID;
};

static const CAAFMPEG4VisualSubDescriptorTestFixture  gTestData = 
{
    // sourceMobID
    { { 0x06, 0x0c, 0x2b, 0x34,
        0x02, 0x05, 0x11, 0x01,
        0x01, 0x00, 0x10, 0x00 },
      0x13, 0x00, 0x00, 0x00,
      { 0x72180083, 0xf225, 0x45ca,
        { 0xb0, 0x60, 0x3a, 0x49,
        0xaf, 0xb0, 0xc0, 0x35 } } }
};



static HRESULT Test_IAAFMPEG4VisualSubDescriptor_Uninitialized(
    IAAFMPEG4VisualSubDescriptor* pMPEG4VisualDesc )
{
    HRESULT  hr = S_OK;


    try
    {
        {
            hr = pMPEG4VisualDesc->SetSingleSequence(kAAFTrue);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafBoolean_t  v = kAAFTrue;
            hr = pMPEG4VisualDesc->GetSingleSequence(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == kAAFTrue);
        }

        {
            hr = pMPEG4VisualDesc->SetConstantBVOPs(kAAFTrue);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafBoolean_t  v = kAAFTrue;
            hr = pMPEG4VisualDesc->GetConstantBVOPs(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == kAAFTrue);
        }

        {
            hr = pMPEG4VisualDesc->SetCodedContentType(kAAFMPEG4VisualCodedContent_Progressive);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafMPEG4VisualCodedContentType_t  v = kAAFMPEG4VisualCodedContent_Mixed;
            hr = pMPEG4VisualDesc->GetCodedContentType(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == kAAFMPEG4VisualCodedContent_Mixed);
        }

        {
            hr = pMPEG4VisualDesc->SetLowDelay(kAAFTrue);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafBoolean_t  v = kAAFTrue;
            hr = pMPEG4VisualDesc->GetLowDelay(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == kAAFTrue);
        }

        {
            hr = pMPEG4VisualDesc->SetClosedGOV(kAAFTrue);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafBoolean_t  v = kAAFTrue;
            hr = pMPEG4VisualDesc->GetClosedGOV(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == kAAFTrue);
        }

        {
            hr = pMPEG4VisualDesc->SetIdenticalGOV(kAAFTrue);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafBoolean_t  v = kAAFTrue;
            hr = pMPEG4VisualDesc->GetIdenticalGOV(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == kAAFTrue);
        }

        {
            hr = pMPEG4VisualDesc->SetMaxGOV(1122);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt16  v = 7766;
            hr = pMPEG4VisualDesc->GetMaxGOV(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 7766);
        }

        {
            hr = pMPEG4VisualDesc->SetBVOPCount(7126);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt16  v = 913;
            hr = pMPEG4VisualDesc->GetBVOPCount(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 913);
        }

        {
            hr = pMPEG4VisualDesc->SetBitRate(9237);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 34234;
            hr = pMPEG4VisualDesc->GetBitRate(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 34234);
        }

        {
            hr = pMPEG4VisualDesc->SetProfileAndLevel(0x11);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 0x32;
            hr = pMPEG4VisualDesc->GetProfileAndLevel(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 0x32);
        }


        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch( HRESULT e )
    {
        hr = e;
    }


    return hr;
}



static HRESULT Test_IAAFMPEG4VisualSubDescriptor(
    IAAFMPEG4VisualSubDescriptor* pMPEG4VisualDesc,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {
        CheckResult(TestSimplePropertyAccess(
            &IAAFMPEG4VisualSubDescriptor::SetSingleSequence,
            &IAAFMPEG4VisualSubDescriptor::GetSingleSequence,
            pMPEG4VisualDesc,
            (aafBoolean_t)kAAFTrue, // will be ignored as it is an optional property
            (aafBoolean_t)kAAFTrue,
            (aafBoolean_t)kAAFFalse,
            false,
            mode));
        CheckResult(TestSimplePropertyAccess(
            &IAAFMPEG4VisualSubDescriptor::SetConstantBVOPs,
            &IAAFMPEG4VisualSubDescriptor::GetConstantBVOPs,
            pMPEG4VisualDesc,
            (aafBoolean_t)kAAFTrue, // will be ignored as it is an optional property
            (aafBoolean_t)kAAFTrue,
            (aafBoolean_t)kAAFFalse,
            false,
            mode));
        CheckResult(TestSimplePropertyAccess(
            &IAAFMPEG4VisualSubDescriptor::SetCodedContentType,
            &IAAFMPEG4VisualSubDescriptor::GetCodedContentType,
            pMPEG4VisualDesc,
            (aafMPEG4VisualCodedContentType_t)kAAFMPEG4VisualCodedContent_Unknown, // will be ignored as it is an optional property
            (aafMPEG4VisualCodedContentType_t)kAAFMPEG4VisualCodedContent_Interlaced,
            (aafMPEG4VisualCodedContentType_t)kAAFMPEG4VisualCodedContent_Mixed,
            false,
            mode));
        CheckResult(TestSimplePropertyAccess(
            &IAAFMPEG4VisualSubDescriptor::SetLowDelay,
            &IAAFMPEG4VisualSubDescriptor::GetLowDelay,
            pMPEG4VisualDesc,
            (aafBoolean_t)kAAFTrue, // will be ignored as it is an optional property
            (aafBoolean_t)kAAFTrue,
            (aafBoolean_t)kAAFFalse,
            false,
            mode));
        CheckResult(TestSimplePropertyAccess(
            &IAAFMPEG4VisualSubDescriptor::SetClosedGOV,
            &IAAFMPEG4VisualSubDescriptor::GetClosedGOV,
            pMPEG4VisualDesc,
            (aafBoolean_t)kAAFTrue, // will be ignored as it is an optional property
            (aafBoolean_t)kAAFTrue,
            (aafBoolean_t)kAAFFalse,
            false,
            mode));
        CheckResult(TestSimplePropertyAccess(
            &IAAFMPEG4VisualSubDescriptor::SetIdenticalGOV,
            &IAAFMPEG4VisualSubDescriptor::GetIdenticalGOV,
            pMPEG4VisualDesc,
            (aafBoolean_t)kAAFTrue, // will be ignored as it is an optional property
            (aafBoolean_t)kAAFTrue,
            (aafBoolean_t)kAAFFalse,
            false,
            mode));
        CheckResult(TestSimplePropertyAccess(
            &IAAFMPEG4VisualSubDescriptor::SetMaxGOV,
            &IAAFMPEG4VisualSubDescriptor::GetMaxGOV,
            pMPEG4VisualDesc,
            (aafUInt16)0, // will be ignored as it is an optional property
            (aafUInt16)22111,
            (aafUInt16)987,
            false,
            mode));
        CheckResult(TestSimplePropertyAccess(
            &IAAFMPEG4VisualSubDescriptor::SetBVOPCount,
            &IAAFMPEG4VisualSubDescriptor::GetBVOPCount,
            pMPEG4VisualDesc,
            (aafUInt16)0, // will be ignored as it is an optional property
            (aafUInt16)11545,
            (aafUInt16)33442,
            false,
            mode));
        CheckResult(TestSimplePropertyAccess(
            &IAAFMPEG4VisualSubDescriptor::SetBitRate,
            &IAAFMPEG4VisualSubDescriptor::GetBitRate,
            pMPEG4VisualDesc,
            (aafUInt32)0, // will be ignored as it is an optional property
            (aafUInt32)222111444,
            (aafUInt32)55675,
            false,
            mode));
        CheckResult(TestSimplePropertyAccess(
            &IAAFMPEG4VisualSubDescriptor::SetProfileAndLevel,
            &IAAFMPEG4VisualSubDescriptor::GetProfileAndLevel,
            pMPEG4VisualDesc,
            (aafUInt8)0, // will be ignored as it is an optional property
            (aafUInt8)0x12,
            (aafUInt8)0x03,
            false,
            mode));

        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch( HRESULT e )
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
        CheckResult(CreateTestFile( pFileName,
                                    fileKind,
                                    rawStorageType,
                                    productID,
                                    &pFile ));


        // Get the AAF Dictionary
        IAAFSmartPointer<IAAFHeader> pHeader;
        CheckResult(pFile->GetHeader(&pHeader));
        IAAFSmartPointer<IAAFDictionary> pDictionary;
        CheckResult(pHeader->GetDictionary(&pDictionary));
        CAAFBuiltinDefs  defs (pDictionary);


        // Create a MPEG4VisualSubDescriptor
        IAAFSmartPointer<IAAFMPEG4VisualSubDescriptor> pMPEG4VisualDesc;
        CheckResult(defs.cdMPEG4VisualSubDescriptor()->CreateInstance(
            IID_IAAFMPEG4VisualSubDescriptor,
            (IUnknown **)&pMPEG4VisualDesc));

        // Before initialization test if the SoundDescriptor
        // methods return valid error values.
        CheckResult(Test_IAAFMPEG4VisualSubDescriptor_Uninitialized(pMPEG4VisualDesc));

        // Initialize MPEG4VisualSubDescriptor object
        CheckResult(pMPEG4VisualDesc->Initialize());

        // Create a CDCIDescriptor
        IAAFSmartPointer<IAAFEssenceDescriptor> pCDCIDesc;
        CheckResult(defs.cdCDCIDescriptor()->CreateInstance(
            IID_IAAFCDCIDescriptor,
            (IUnknown **)&pCDCIDesc));

        // Attach the IAAFMPEG4VisualSubDescriptor to the CDCIDescriptor
        IAAFSmartPointer<IAAFSubDescriptor> pSubDesc;
        CheckResult(pMPEG4VisualDesc->QueryInterface(IID_IAAFSubDescriptor,
                                                  (void **)&pSubDesc));
        IAAFSmartPointer<IAAFEssenceDescriptor2> pCDCIDesc_EssenceDesc2;
        CheckResult(pCDCIDesc->QueryInterface(IID_IAAFEssenceDescriptor2,
                                              (void **)&pCDCIDesc_EssenceDesc2));
        CheckResult(pCDCIDesc_EssenceDesc2->AppendSubDescriptor(pSubDesc));

        // Create a mob, set its ID
        IAAFSmartPointer<IAAFSourceMob> pSourceMob;
        CheckResult(defs.cdSourceMob()->CreateInstance( IID_IAAFSourceMob,
                                                        (IUnknown **)&pSourceMob) );
        IAAFSmartPointer<IAAFMob> pMob;
        CheckResult(pSourceMob->QueryInterface (IID_IAAFMob, (void **)&pMob));
        CheckResult(pMob->SetMobID(gTestData.sourceMobID));
        CheckResult(pMob->SetName(L"MPEG4VisualSubDescriptorTest"));

        // Attach the descriptor to the source mob
        IAAFSmartPointer<IAAFEssenceDescriptor> pCDCIDesc_EssenceDesc;
        CheckResult(pCDCIDesc->QueryInterface(IID_IAAFEssenceDescriptor,
                                              (void **)&pCDCIDesc_EssenceDesc));
        CheckResult(pSourceMob->SetEssenceDescriptor(pCDCIDesc_EssenceDesc));

        // Attach the source mob to the file
        CheckResult(pHeader->AddMob(pMob));


        // Test initialized MPEG4VisualSubDescriptor.
        CheckResult(Test_IAAFMPEG4VisualSubDescriptor(pMPEG4VisualDesc,
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
    aafWChar * pFileName )
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

        // Get the MPEG4VisualSubDescriptor
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
        IAAFSmartPointer<IAAFMPEG4VisualSubDescriptor> pMPEG4VisualDesc;
        CheckResult(pSubDesc->QueryInterface(IID_IAAFMPEG4VisualSubDescriptor,
                                              (void **)&pMPEG4VisualDesc));


        CheckResult(Test_IAAFMPEG4VisualSubDescriptor(pMPEG4VisualDesc,
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
extern "C" HRESULT CAAFMPEG4VisualSubDescriptor_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);

//
// The public entry for this module test,
//
HRESULT CAAFMPEG4VisualSubDescriptor_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID )
{
    HRESULT  hr = AAFRESULT_NOT_IMPLEMENTED;
    const size_t fileNameBufLen = 128;
    aafWChar pFileName[ fileNameBufLen ] = L"";
    GenerateTestFileName( productID.productName, fileKind, fileNameBufLen, pFileName );


    try
    {
        if(mode == kAAFUnitTestReadWrite)
            hr = CreateAAFFile(pFileName, fileKind, rawStorageType, productID);
        else
            hr = AAFRESULT_SUCCESS;
        if(hr == AAFRESULT_SUCCESS)
            hr = ReadAAFFile( pFileName );
    }
    catch (...)
    {
        cerr << "CAAFSoundDescriptor_test...Caught general C++"
             << " exception!" << endl; 
        hr = AAFRESULT_TEST_FAILED;
    }


    return hr;
}

