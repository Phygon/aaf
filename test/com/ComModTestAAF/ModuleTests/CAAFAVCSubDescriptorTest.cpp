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



struct CAAFAVCSubDescriptorTestFixture
{
    aafMobID_t              sourceMobID;
};

static const CAAFAVCSubDescriptorTestFixture  gTestData = 
{
    { { 0x06, 0x0c, 0x2b, 0x34,
        0x02, 0x05, 0x11, 0x01,
        0x01, 0x00, 0x10, 0x00 },
      0x13, 0x00, 0x00, 0x00,
      { 0xf6d43ded, 0xa5aa, 0x4a05,
        { 0xa2, 0x84, 0x37, 0x8f,
          0x94, 0x16, 0xd0, 0x56 } } } // sourceMobID
};



static HRESULT Test_IAAFAVCSubDescriptor_Uninitialized(
    IAAFAVCSubDescriptor* pAVCDesc )
{
    HRESULT  hr = S_OK;


    try
    {
        {
            hr = pAVCDesc->SetDecodingDelay(201);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 143;
            hr = pAVCDesc->GetDecodingDelay(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 143);
        }
        {
            hr = pAVCDesc->SetConstantBPictureFlag(kAAFTrue);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafBoolean_t  v = kAAFTrue;
            hr = pAVCDesc->GetConstantBPictureFlag(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == kAAFTrue);
        }
        {
            hr = pAVCDesc->SetCodedContentKind(kAAFAVCContentScanning_Interlace_FrameFieldPicture);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafAVCContentScanningType_t  v = kAAFAVCContentScanning_InterlaceFramePicture;
            hr = pAVCDesc->GetCodedContentKind(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == kAAFAVCContentScanning_InterlaceFramePicture);
        }
        {
            hr = pAVCDesc->SetClosedGOPIndicator(kAAFTrue);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafBoolean_t  v = kAAFTrue;
            hr = pAVCDesc->GetClosedGOPIndicator(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == kAAFTrue);
        }
        {
            hr = pAVCDesc->SetIdenticalGOPIndicator(kAAFTrue);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafBoolean_t  v = kAAFTrue;
            hr = pAVCDesc->GetIdenticalGOPIndicator(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == kAAFTrue);
        }
        {
            hr = pAVCDesc->SetMaximumGOPSize(23953);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt16  v = 6915;
            hr = pAVCDesc->GetMaximumGOPSize(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 6915);
        }
        {
            hr = pAVCDesc->SetMaximumBPictureCount(25489);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt16  v = 19432;
            hr = pAVCDesc->GetMaximumBPictureCount(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 19432);
        }
        {
            hr = pAVCDesc->SetMaximumBitRate(14);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 7;
            hr = pAVCDesc->GetMaximumBitRate(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 7);
        }
        {
            hr = pAVCDesc->SetAverageBitRate(2);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 5;
            hr = pAVCDesc->GetAverageBitRate(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 5);
        }
        {
            hr = pAVCDesc->SetProfile(213);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 176;
            hr = pAVCDesc->GetProfile(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 176);
        }
        {
            hr = pAVCDesc->SetProfileConstraint(86);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 153;
            hr = pAVCDesc->GetProfileConstraint(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 153);
        }
        {
            hr = pAVCDesc->SetLevel(242);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 211;
            hr = pAVCDesc->GetLevel(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 211);
        }
        {
            hr = pAVCDesc->SetMaximumRefFrames(77);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 198;
            hr = pAVCDesc->GetMaximumRefFrames(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 198);
        }
        {
            hr = pAVCDesc->SetSequenceParameterSetFlag(242);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 249;
            hr = pAVCDesc->GetSequenceParameterSetFlag(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 249);
        }
        {
            hr = pAVCDesc->SetPictureParameterSetFlag(242);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 249;
            hr = pAVCDesc->GetPictureParameterSetFlag(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 249);
        }
        {
            hr = pAVCDesc->SetPictureParameterSetFlag(242);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 249;
            hr = pAVCDesc->GetPictureParameterSetFlag(&v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 249);
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



template <typename PropertyType>
HRESULT Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
    IAAFAVCSubDescriptor* pAVCDesc,
    HRESULT (STDMETHODCALLTYPE IAAFAVCSubDescriptor::*setter)(PropertyType),
    HRESULT (STDMETHODCALLTYPE IAAFAVCSubDescriptor::*getter)(PropertyType*),
    const PropertyType testValue,
    const bool requiredProperty,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {
        const PropertyType bogusValue = 39;


        if( mode == kAAFUnitTestReadWrite )
        {
            if( requiredProperty )
            {
                // GetXXX() should succeed because XXX
                // is a required property.
                PropertyType  value = bogusValue;
                CheckResult((pAVCDesc->*getter)( &value ));
                CheckExpression(value != bogusValue);
            }
            else
            {
                // GetXXX() should fail because XXX is optional and not present.
                PropertyType  value = bogusValue;
                hr = (pAVCDesc->*getter)( &value );
                CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
            }

            // GetXXX() should fail if function arguments are invalid.
            hr = (pAVCDesc->*getter)( 0 );
            CheckExpression(hr == AAFRESULT_NULL_PARAM);

            // SetXXX() should always succeed
            CheckResult((pAVCDesc->*setter)( testValue ));
        }

        if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
        {
            // GetXXX() should succeed.
            PropertyType  value = bogusValue;
            CheckResult((pAVCDesc->*getter)( &value ));
            CheckExpression(value == testValue);
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



static HRESULT Test_IAAFAVCSubDescriptor(
    IAAFAVCSubDescriptor* pAVCDesc,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetDecodingDelay,
            &IAAFAVCSubDescriptor::GetDecodingDelay,
            (aafUInt8)96,
            true,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetConstantBPictureFlag,
            &IAAFAVCSubDescriptor::GetConstantBPictureFlag,
            (aafBoolean_t)kAAFTrue,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetCodedContentKind,
            &IAAFAVCSubDescriptor::GetCodedContentKind,
            (aafAVCContentScanningType_t)kAAFAVCContentScanning_InterlaceFieldPicture,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetClosedGOPIndicator,
            &IAAFAVCSubDescriptor::GetClosedGOPIndicator,
            (aafBoolean_t)kAAFTrue,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetIdenticalGOPIndicator,
            &IAAFAVCSubDescriptor::GetIdenticalGOPIndicator,
            (aafBoolean_t)kAAFTrue,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetMaximumGOPSize,
            &IAAFAVCSubDescriptor::GetMaximumGOPSize,
            (aafUInt16)96,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetMaximumBPictureCount,
            &IAAFAVCSubDescriptor::GetMaximumBPictureCount,
            (aafUInt16)96,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetMaximumBitRate,
            &IAAFAVCSubDescriptor::GetMaximumBitRate,
            (aafUInt32)96,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetAverageBitRate,
            &IAAFAVCSubDescriptor::GetAverageBitRate,
            (aafUInt32)96,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetProfile,
            &IAAFAVCSubDescriptor::GetProfile,
            (aafUInt8)96,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetProfileConstraint,
            &IAAFAVCSubDescriptor::GetProfileConstraint,
            (aafUInt8)96,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetLevel,
            &IAAFAVCSubDescriptor::GetLevel,
            (aafUInt8)96,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetMaximumRefFrames,
            &IAAFAVCSubDescriptor::GetMaximumRefFrames,
            (aafUInt8)96,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetSequenceParameterSetFlag,
            &IAAFAVCSubDescriptor::GetSequenceParameterSetFlag,
            (aafUInt8)96,
            false,
            mode));
        CheckResult(Test_IAAFAVCSubDescriptor_SimplePropertyAccess(
            pAVCDesc,
            &IAAFAVCSubDescriptor::SetPictureParameterSetFlag,
            &IAAFAVCSubDescriptor::GetPictureParameterSetFlag,
            (aafUInt8)96,
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


        // Create a AVCSubDescriptor
        IAAFSmartPointer<IAAFAVCSubDescriptor> pAVCDesc;
        CheckResult(defs.cdAVCSubDescriptor()->CreateInstance(
            IID_IAAFAVCSubDescriptor,
            (IUnknown **)&pAVCDesc));

        // Before initialization test if the SoundDescriptor
        // methods return valid error values.
        CheckResult(Test_IAAFAVCSubDescriptor_Uninitialized(pAVCDesc));

        // Initialize AVCSubDescriptor object
        CheckResult(pAVCDesc->Initialize());

        // Create a CDCIDescriptor
        IAAFSmartPointer<IAAFEssenceDescriptor> pCDCIDesc;
        CheckResult(defs.cdCDCIDescriptor()->CreateInstance(
            IID_IAAFCDCIDescriptor,
            (IUnknown **)&pCDCIDesc));

        // Attach the IAAFAVCSubDescriptor to the CDCIDescriptor
        IAAFSmartPointer<IAAFSubDescriptor> pSubDesc;
        CheckResult(pAVCDesc->QueryInterface(IID_IAAFSubDescriptor,
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
        CheckResult(pMob->SetName(L"AVCSubDescriptorTest"));

        // Attach the descriptor to the source mob
        IAAFSmartPointer<IAAFEssenceDescriptor> pCDCIDesc_EssenceDesc;
        CheckResult(pCDCIDesc->QueryInterface(IID_IAAFEssenceDescriptor,
                                              (void **)&pCDCIDesc_EssenceDesc));
        CheckResult(pSourceMob->SetEssenceDescriptor(pCDCIDesc_EssenceDesc));

        // Attach the source mob to the file
        CheckResult(pHeader->AddMob(pMob));


        // Test initialized AVCSubDescriptor.
        CheckResult(Test_IAAFAVCSubDescriptor(pAVCDesc,
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

        // Get the AVCSubDescriptor
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
        IAAFSmartPointer<IAAFAVCSubDescriptor> pAVCDesc;
        CheckResult(pSubDesc->QueryInterface(IID_IAAFAVCSubDescriptor,
                                              (void **)&pAVCDesc));


        CheckResult(Test_IAAFAVCSubDescriptor(pAVCDesc,
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
extern "C" HRESULT CAAFAVCSubDescriptor_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);

//
// The public entry for this module test,
//
HRESULT CAAFAVCSubDescriptor_test(
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

