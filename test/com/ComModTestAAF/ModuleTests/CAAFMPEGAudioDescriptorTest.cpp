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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>

#include "AAF.h"
#include "AAFResult.h"

#include "CAAFBuiltinDefs.h"
#include "AAFDefUIDs.h"
#include "ModuleTest.h"

using namespace std;


#define kbitRate					1024


static const 	aafMobID_t	TEST_MobID =
{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
0x13, 0x00, 0x00, 0x00,
{0x09273e8e, 0x0406, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}};

// Convenient error handlers.
inline void checkResult(HRESULT r)
{
    if (FAILED(r))
        throw r;
}
inline void checkExpression(bool expression, HRESULT r)
{
    if (!expression)
        throw r;
}



// Required function prototype.
extern "C" HRESULT CAAFMPEGAudioDescriptor_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);

static HRESULT CreateAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_constref productID);

static HRESULT ReadAAFFile(
    aafWChar * pFileName);

static HRESULT Test_IAAFMPEGAudioDescriptor( IAAFMPEGAudioDescriptor*, testMode_t );

static HRESULT Test_IAAFMPEGAudioDescriptor_MPEGAudioBitRate(
    IAAFMPEGAudioDescriptor* pMPEGAudioDesc,
    testMode_t mode );

bool operator ==( const aafUID_t uid1, const aafUID_t uid2 );
bool operator !=( const aafUID_t uid1, const aafUID_t uid2 );




//
// The public entry for this module test,
//
HRESULT CAAFMPEGAudioDescriptor_test(
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
        cerr << "CAAFMPEGAudioDescriptor_test...Caught general C++"
             << " exception!" << endl; 
        hr = AAFRESULT_TEST_FAILED;
    }


    return hr;
}


static HRESULT CreateAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_constref productID)
{
    IAAFFile*               pFile = 0;
    IAAFHeader*             pHeader = 0;
    IAAFDictionary*         pDictionary = 0;
    IAAFSourceMob*          pSourceMob = 0;
    IAAFMob*                pMob = 0;
    IAAFEssenceDescriptor*  pEssDesc = 0;
    IAAFMPEGAudioDescriptor*    pMPEGAudioDesc = 0;

    HRESULT hr = S_OK;

    try
    {
    	    
     	// Remove the previous test file if any.
    	RemoveTestFile(pFileName);


	  	// Create the AAF file
    	checkResult(CreateTestFile( pFileName, fileKind, rawStorageType, productID, &pFile ));

    	// We can't really do anthing in AAF without the header.
    	checkResult(pFile->GetHeader(&pHeader));

    	// Get the AAF Dictionary so that we can create valid AAF objects.
    	checkResult(pHeader->GetDictionary(&pDictionary));
		CAAFBuiltinDefs defs (pDictionary);
 		
	  	// Create a source mob
		checkResult(defs.cdSourceMob()->
					CreateInstance(IID_IAAFSourceMob, 
								   (IUnknown **)&pSourceMob));
		checkResult(pSourceMob->QueryInterface(IID_IAAFMob, (void **)&pMob));

		checkResult(pMob->SetMobID(TEST_MobID));
		checkResult(pMob->SetName(L"MPEGAudioDescriptorTest"));
		checkResult(defs.cdMPEGAudioDescriptor()->
					CreateInstance(IID_IAAFMPEGAudioDescriptor, 
								   (IUnknown **)&pMPEGAudioDesc));		

		Test_IAAFMPEGAudioDescriptor(pMPEGAudioDesc, kAAFUnitTestReadWrite );
		

    	checkResult(pMPEGAudioDesc->QueryInterface(IID_IAAFEssenceDescriptor, (void **)&pEssDesc));
		checkResult(pSourceMob->SetEssenceDescriptor(pEssDesc));

		// Add the MOB to the file
		checkResult(pHeader->AddMob(pMob));
	}
  catch (HRESULT& rResult)
  {
    hr = rResult;
  }


    if (pMPEGAudioDesc) 
    {
        pMPEGAudioDesc->Release();
    }
    if (pEssDesc) 
    {
        pEssDesc->Release();
    }
    if (pMob) 
    {
        pMob->Release();
    }
    if (pSourceMob) 
    {
        pSourceMob->Release();
    }
    if (pDictionary) 
    {
        pDictionary->Release();
    }
    if (pHeader) 
    {
        pHeader->Release();
    }
    if (pFile) 
    {
    	pFile->Save();
        pFile->Close();
        pFile->Release();
    }

    return hr;
}



static HRESULT ReadAAFFile(
    aafWChar * pFileName )
{
    HRESULT                 	hr = S_OK;
    IAAFFile*               	pFile = 0;
    IAAFHeader*             	pHeader = 0;
    IAAFMob*                	pMob = 0;
    IAAFSourceMob*          	pSourceMob = 0;
    IAAFEssenceDescriptor*  	pEssenceDesc = 0;
    IAAFMPEGAudioDescriptor*    pMPEGAudio = 0;

    try
    {

        // Open the test file
		checkResult(AAFFileOpenExistingRead(pFileName, 0, &pFile));

		// Get the AAF file header.
		checkResult(pFile->GetHeader(&pHeader));
        
        // Get the source mob
        checkResult(pHeader->LookupMob(TEST_MobID, &pMob));
        checkResult(pMob->QueryInterface(IID_IAAFSourceMob,
                                         (void **)&pSourceMob));

        // Get the sound descriptor
        checkResult(pSourceMob->GetEssenceDescriptor(&pEssenceDesc));
        checkResult(pEssenceDesc->QueryInterface(IID_IAAFMPEGAudioDescriptor,
                                                 (void **)&pMPEGAudio));


        checkResult(Test_IAAFMPEGAudioDescriptor(pMPEGAudio,
                                             kAAFUnitTestReadOnly));
    }
    catch (HRESULT& rResult)
    {
        hr = rResult;
    }


    if (pMPEGAudio) 
    {
        pMPEGAudio->Release();
    }
    if (pEssenceDesc) 
    {
        pEssenceDesc->Release();
    }
    if (pSourceMob) 
    {
        pSourceMob->Release();
    }
    if (pMob) 
    {
        pMob->Release();
    }
    if (pHeader) 
    {
        pHeader->Release();
    }
    if (pFile) 
    {
        pFile->Close();
        pFile->Release();
    }


    return hr;
}



static HRESULT Test_IAAFMPEGAudioDescriptor(
    IAAFMPEGAudioDescriptor* pMPEGAudioDesc,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {
        checkResult( Test_IAAFMPEGAudioDescriptor_MPEGAudioBitRate( pMPEGAudioDesc, mode ) );

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


static HRESULT Test_IAAFMPEGAudioDescriptor_MPEGAudioBitRate(
    IAAFMPEGAudioDescriptor* pMPEGAudio,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {
        static const aafUInt32 bogusMPEGAudioBitRate = 21000;


        if( mode == kAAFUnitTestReadWrite )
        {
            // GetMPEGAudioBitRate() should fail if the property not present.
            aafUInt32 bitRate = bogusMPEGAudioBitRate;
            
            hr = pMPEGAudio->GetMPEGAudioBitRate( &bitRate );
            checkExpression( hr == AAFRESULT_PROP_NOT_PRESENT,
                             AAFRESULT_TEST_FAILED );
            checkExpression( bitRate == bogusMPEGAudioBitRate,
                             AAFRESULT_TEST_FAILED );


            // GetMPEGAudioBitRate() should fail if function arguments are invalid.
            bitRate = bogusMPEGAudioBitRate;
            hr = pMPEGAudio->GetMPEGAudioBitRate( NULL );
            checkExpression( hr == AAFRESULT_NULL_PARAM,
                             AAFRESULT_TEST_FAILED );
            checkExpression( bitRate == bogusMPEGAudioBitRate,
                             AAFRESULT_TEST_FAILED );


            // SetMPEGAudioBitRate() should always succeed
            hr = pMPEGAudio->SetMPEGAudioBitRate( kbitRate );
            checkExpression( hr == AAFRESULT_SUCCESS, AAFRESULT_TEST_FAILED );
        }


        if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
        {
            // GetMPEGAudioBitRate() should succeed.
            aafUInt32  bitRate = bogusMPEGAudioBitRate;
            hr = pMPEGAudio->GetMPEGAudioBitRate( &bitRate );
            checkExpression( hr == AAFRESULT_SUCCESS, AAFRESULT_TEST_FAILED );
            checkExpression( bitRate == kbitRate,
                             AAFRESULT_TEST_FAILED );
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
