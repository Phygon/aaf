// @doc INTERNAL
// @com This file implements the module test for CAAFDefinitionObject
/******************************************\
*                                          *
* Advanced Authoring Format                *
*                                          *
* Copyright (c) 1998 Avid Technology, Inc. *
* Copyright (c) 1998 Microsoft Corporation *
*                                          *
\******************************************/

#ifndef __CAAFSourceClip_h__
#include "CAAFSourceClip.h"
#endif

#include <iostream.h>
#include <stdio.h>

#include "AAFStoredObjectIDs.h"
#include "AAFResult.h"
#include "AAFDefUIDs.h"
#include "AAFUtils.h"

static aafWChar *slotName = L"SLOT1";
static aafInt32 fadeInLen  = 1000;
static aafInt32 fadeOutLen = 2000;
static aafFadeType_t fadeInType = kFadeLinearAmp;
static aafFadeType_t fadeOutType = kFadeLinearPower;
static aafSourceRef_t sourceRef; 



// Cross-platform utility to delete a file.
static void RemoveTestFile(const wchar_t* pFileName)
{
  const size_t kMaxFileName = 512;
  char cFileName[kMaxFileName];

  size_t status = wcstombs(cFileName, pFileName, kMaxFileName);
  if (status != (size_t)-1)
  { // delete the file.
    remove(cFileName);
  }
}

// convenient error handlers.
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



static HRESULT CreateAAFFile(aafWChar * pFileName)
{
	// IAAFSession*				pSession = NULL;
	IAAFFile*					pFile = NULL;
	IAAFHeader*					pHeader = NULL;
  IAAFDictionary*  pDictionary = NULL;
	IAAFMob*					pMob = NULL;
	IAAFMob*					pReferencedMob = NULL;
	IAAFMobSlot*				newSlot = NULL;
	IAAFSegment*				seg = NULL;
	IAAFSourceClip*				sclp = NULL;
	aafRational_t				audioRate = { 44100, 1 };
	bool bFileOpen = false;
	aafProductIdentification_t	ProductInfo;
	aafUID_t					newMobID, referencedMobID;
	HRESULT						hr = AAFRESULT_SUCCESS;

	ProductInfo.companyName = L"AAF Developers Desk";
	ProductInfo.productName = L"AAFSourceClip Test";
	ProductInfo.productVersion.major = 1;
	ProductInfo.productVersion.minor = 0;
	ProductInfo.productVersion.tertiary = 0;
	ProductInfo.productVersion.patchLevel = 0;
	ProductInfo.productVersion.type = kVersionUnknown;
	ProductInfo.productVersionString = NULL;
	ProductInfo.productID = -1;
	ProductInfo.platform = NULL;

	try
	{
    // Remove the previous test file if any.
    RemoveTestFile(pFileName);

    // Create the file
		checkResult(CoCreateInstance(CLSID_AAFFile,
								 NULL, 
								 CLSCTX_INPROC_SERVER, 
								 IID_IAAFFile, 
								 (void **)&pFile));
		checkResult(pFile->Initialize());
		checkResult(pFile->OpenNewModify(pFileName, 0, &ProductInfo));
		bFileOpen = true;
 
    // We can't really do anthing in AAF without the header.
		checkResult(pFile->GetHeader(&pHeader));

    // Get the AAF Dictionary so that we can create valid AAF objects.
    checkResult(pHeader->GetDictionary(&pDictionary));
 		
		//Make the MOB to be referenced
		checkResult(pDictionary->CreateInstance(&AUID_AAFMasterMob,
								 IID_IAAFMob, 
								 (IUnknown **)&pReferencedMob));
		checkResult(CoCreateGuid((GUID *)&referencedMobID));
		checkResult(pReferencedMob->SetMobID(&referencedMobID));
		checkResult(pReferencedMob->SetName(L"AAFSourceClipTest::ReferencedMob"));

		// Create a Mob
		checkResult(pDictionary->CreateInstance(&AUID_AAFCompositionMob,
								 IID_IAAFMob, 
								 (IUnknown **)&pMob));
		checkResult(CoCreateGuid((GUID *)&newMobID));
		checkResult(pMob->SetMobID(&newMobID));
		checkResult(pMob->SetName(L"AAFSourceClipTest"));

		// Create a SourceClip
		checkResult(pDictionary->CreateInstance(&AUID_AAFSourceClip,
								 IID_IAAFSourceClip, 
								 (IUnknown **)&sclp));
								 		
		// Set the properties for the SourceClip
		checkResult(sclp->SetFade( fadeInLen, fadeInType, fadeOutLen, fadeOutType));
		sourceRef.sourceID = referencedMobID;
		sourceRef.sourceSlotID = 0;
		sourceRef.startTime = 0;
		checkResult(sclp->SetSourceReference(sourceRef));

		checkResult(sclp->QueryInterface (IID_IAAFSegment, (void **)&seg));
		checkResult(pMob->AppendNewSlot (seg, 1, slotName, &newSlot));

		checkResult(pHeader->AppendMob(pMob));
		checkResult(pHeader->AppendMob(pReferencedMob));
	}
  catch (HRESULT& rResult)
  {
    hr = rResult;
  }

  // Cleanup and return
	if (newSlot)
		newSlot->Release();

	if (seg)
		seg->Release();

	if (sclp)
		sclp->Release();

	if (pMob)
		pMob->Release();

	if (pReferencedMob)
		pReferencedMob->Release();

	if (pDictionary)
		pDictionary->Release();

	if (pHeader)
		pHeader->Release();

	if (pFile) 
	{
		if (bFileOpen)
			pFile->Close();
		pFile->Release();
	}


	return hr;
}

static HRESULT ReadAAFFile(aafWChar * pFileName)
{
	// IAAFSession *				pSession = NULL;
	IAAFFile *					pFile = NULL;
	IAAFHeader *				pHeader = NULL;
	IEnumAAFMobs*				pMobIter = NULL;
	IAAFMob*					pMob = NULL;
	IAAFMob*					pReferencedMob = NULL;
	IEnumAAFMobSlots*			pSlotIter = NULL;
	IAAFMobSlot*				pSlot = NULL;
	IAAFSegment*				pSegment = NULL;
	IAAFSourceClip*				pSourceClip = NULL;
	bool bFileOpen = false;
	aafProductIdentification_t	ProductInfo;
	aafSearchCrit_t				criteria;
	aafNumSlots_t				numMobs, numSlots;
	aafInt32					rFadeInLen;
	aafInt32					rFadeOutLen;
	aafFadeType_t				rFadeInType;
	aafFadeType_t				rFadeOutType;
	aafSourceRef_t				rSourceRef; 
	aafBool						fadeInPresent;
	aafBool						fadeOutPresent;
	HRESULT						hr = AAFRESULT_SUCCESS;
	aafUID_t					rReferencedMobID;

	ProductInfo.companyName = L"AAF Developers Desk. NOT!";
	ProductInfo.productName = L"MaAAFSourceClip Test. NOT!";
	ProductInfo.productVersion.major = 1;
	ProductInfo.productVersion.minor = 0;
	ProductInfo.productVersion.tertiary = 0;
	ProductInfo.productVersion.patchLevel = 0;
	ProductInfo.productVersion.type = kVersionUnknown;
	ProductInfo.productVersionString = NULL;
	ProductInfo.productID = -1;
	ProductInfo.platform = NULL;

	try
	{ 
    // Open the file
		checkResult(CoCreateInstance(CLSID_AAFFile,
								 NULL, 
								 CLSCTX_INPROC_SERVER, 
								 IID_IAAFFile, 
								 (void **)&pFile));
		checkResult(pFile->Initialize());
		checkResult(pFile->OpenExistingRead(pFileName, 0));
		bFileOpen = true;
 
    // We can't really do anthing in AAF without the header.
		checkResult(pFile->GetHeader(&pHeader));

		// Get the number of mobs in the file (should be one)
		checkResult(pHeader->GetNumMobs(kAllMob, &numMobs));
		checkExpression(2 == numMobs, AAFRESULT_TEST_FAILED);

		// Enumerate over all Composition Mobs
		criteria.searchTag = kByMobKind;
		criteria.tags.mobKind = kCompMob;
		checkResult(pHeader->EnumAAFAllMobs(&criteria, &pMobIter));
		while (AAFRESULT_SUCCESS == pMobIter->NextOne(&pMob))
		{
			checkResult(pMob->GetNumSlots(&numSlots));
			checkExpression(1 == numSlots, AAFRESULT_TEST_FAILED);

			checkResult(pMob->EnumAAFAllMobSlots(&pSlotIter));
			while (AAFRESULT_SUCCESS == pSlotIter->NextOne(&pSlot))
			{
				// The segment should be a source clip...
				checkResult(pSlot->GetSegment(&pSegment));
				checkResult(pSegment->QueryInterface(IID_IAAFSourceClip, (void **) &pSourceClip));

				checkResult(pSourceClip->GetFade( &rFadeInLen, &rFadeInType, &fadeInPresent, 
									&rFadeOutLen, &rFadeOutType, &fadeOutPresent ));
				checkResult(pSourceClip->GetSourceReference( &rSourceRef)); 
				// verify that we read exactly the same thing as we wrote to the file !!
				checkExpression(AAFTrue == fadeInPresent, AAFRESULT_TEST_FAILED);
				checkExpression(rFadeInLen == fadeInLen && rFadeInType == fadeInType,
				                AAFRESULT_TEST_FAILED);
				checkExpression(AAFTrue == fadeOutPresent, AAFRESULT_TEST_FAILED);
				checkExpression(rFadeOutLen == fadeOutLen && rFadeOutType == fadeOutType, 
				                AAFRESULT_TEST_FAILED);
				checkExpression(memcmp(&(rSourceRef.sourceID), &(sourceRef.sourceID), sizeof(sourceRef.sourceID)) == 0, 
				                AAFRESULT_TEST_FAILED);
				checkExpression(rSourceRef.sourceSlotID == sourceRef.sourceSlotID &&
				                rSourceRef.startTime == sourceRef.startTime, 
				                AAFRESULT_TEST_FAILED);

				checkResult(pSourceClip->ResolveRef(&pReferencedMob));
				checkResult(pReferencedMob->GetMobID(&rReferencedMobID));
				checkExpression(0 != EqualAUID(&rReferencedMobID, &sourceRef.sourceID), 
				                AAFRESULT_TEST_FAILED);

				pSlot->Release();
				pSlot = NULL;
			}

			pMob->Release();
			pMob = NULL;
		}

	}
  catch (HRESULT& rResult)
  {
    hr = rResult;
  }

	// Cleanup and return
	if (pReferencedMob)
		pReferencedMob->Release();

	if (pSourceClip)
		pSourceClip->Release();

	if (pSegment)
		pSegment->Release();

	if (pSlot)
		pSlot->Release();

	if (pSlotIter)
		pSlotIter->Release();

	if (pMob)
		pMob->Release();

	if (pMobIter)
		pMobIter->Release();

	if (pHeader)
		pHeader->Release();

	if (pFile) 
	{
		if (bFileOpen)
			pFile->Close();
		pFile->Release();
	}

	return hr;
}
 


HRESULT CAAFSourceClip::test()
{
	HRESULT hr = AAFRESULT_NOT_IMPLEMENTED;
 	aafWChar * pFileName = L"SourceClipTest.aaf";

	try
	{
		hr = CreateAAFFile(	pFileName );
		if(hr == AAFRESULT_SUCCESS)
			hr = ReadAAFFile( pFileName );
	}
	catch (...)
	{
	  cerr << "CAAFSourceClip::test...Caught general C++"
		" exception!" << endl; 
	  hr = AAFRESULT_TEST_FAILED;
	}


	return hr;
}






















