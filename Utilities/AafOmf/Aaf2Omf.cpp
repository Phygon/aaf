// @doc INTERNAL
// @com This file implements the conversion of OMF files to AAF file format.
/***********************************************************************
 *
 *              Copyright (c) 1998-1999 Avid Technology, Inc.
 *
 * Permission to use, copy and modify this software and accompanying 
 * documentation, and to distribute and sublicense application software
 * incorporating this software for any purpose is hereby granted, 
 * provided that (i) the above copyright notice and this permission
 * notice appear in all copies of the software and related documentation,
 * and (ii) the name Avid Technology, Inc. may not be used in any
 * advertising or publicity relating to the software without the specific,
 *  prior written permission of Avid Technology, Inc.
 *
 * THE SOFTWARE IS PROVIDED AS-IS AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL AVID TECHNOLOGY, INC. BE LIABLE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, PUNITIVE, INDIRECT, ECONOMIC, CONSEQUENTIAL OR
 * OTHER DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE AND
 * ACCOMPANYING DOCUMENTATION, INCLUDING, WITHOUT LIMITATION, DAMAGES
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, AND WHETHER OR NOT
 * ADVISED OF THE POSSIBILITY OF DAMAGE, REGARDLESS OF THE THEORY OF
 * LIABILITY.
 *
 ************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream.h>


namespace OMF2
{
	#include "omPublic.h"
	#include "omMedia.h"
}

// OMF Includes


#include "AafOmf.h"

#include "AAFDomainUtils.h"
#include "OMFDomainUtils.h"
#if AVID_SPECIAL
#include "ConvertAvid.h"
#include "AAFDomainAvidUtils.h"
#include "OMFDomainAvidUtils.h"
#include "AvidEffectTranslate.h"
#else
#include "AAFDomainExtensions.h"
#include "OMFDomainExtensionUtils.h"
#include "EffectTranslate.h"
#endif
#include "Aaf2Omf.h"
#include "aafCodecdefs.h"
#include "aafclassdefuids.h"
#include "AAFException.h"
#include "OMFException.h"
//#include "omcAvJPED.h"

extern AafOmfGlobals* gpGlobals;
// ============================================================================
// Constructor
// ============================================================================
Aaf2Omf::Aaf2Omf() : pFile(NULL), pHeader(NULL), pDictionary(NULL)
{
	pAAF = new AAFDomainExtensionUtils;
	pOMF = new OMFDomainExtensionUtils;
#if AVID_SPECIAL
	pEffectTranslate = new AvidEffectTranslate;
#else
	pEffectTranslate = new EffectTranslate;
#endif
}
// ============================================================================
// Destructor
// ============================================================================
Aaf2Omf::~Aaf2Omf()
{
	if (pHeader)
		pHeader->Release();
	if (pDictionary)
		pDictionary->Release();
	if (pFile)
		pFile->Release();

}
// ============================================================================
// ConvertFile
//			This function provides the control and logic to convert an AAF file
//			by calling all the functions inside this object
//
// ============================================================================
void Aaf2Omf::ConvertFile ()
{
	AAFCheck		rc;

	OpenInputFile();
	OpenOutputFile();
	pAAF->SetDictionary(pDictionary);
	AAFFileRead();

	if (gpGlobals->bOMFFileOpen)
	{
		CloseOutputFile();
		gpGlobals->bOMFFileOpen = kAAFFalse;
	}

	if (gpGlobals->bAAFFileOpen)
	{
		CloseInputFile();
		gpGlobals->bAAFFileOpen = kAAFFalse;
	}
}
// ============================================================================
// ConvertMobIDtoUID
//			This function reduces an MobID into an OMF UID.
//
// ============================================================================
void Aaf2Omf::ConvertMobIDtoUID(aafMobID_constptr pMobID, 
							   OMF2::omfUID_t* pOMFMobID)
{
	struct SMPTELabel		// Change to match GUID to ensure correct byte swapping
	{
		aafUInt32	MobIDMajor;
		aafUInt16	MobIDMinorLow;
		aafUInt16	MobIDMinorHigh;
		aafUInt8	oid;
		aafUInt8	size;
		aafUInt8	ulcode;
		aafUInt8	SMPTE;
		aafUInt8	Registry;
		aafUInt8	unused;
		aafUInt8	MobIDPrefixLow;
		aafUInt8	MobIDPrefixHigh;
	};
	union label
	{
		aafMobID_t			mobID;
		struct SMPTELabel	smpte;
	};

	union label aLabel;
	memcpy((void *)&aLabel.mobID, pMobID, sizeof(aLabel.mobID));

	pOMFMobID->prefix = (aLabel.smpte.MobIDPrefixHigh << 8L) | aLabel.smpte.MobIDPrefixLow;
	pOMFMobID->major = aLabel.smpte.MobIDMajor;
	pOMFMobID->minor = (aLabel.smpte.MobIDMinorHigh << 16L) | aLabel.smpte.MobIDMinorLow;
}
// ============================================================================
// OpenInputFile
//			This function determines an AAF file for read.
//			If the file does not exists or it is not an AAF file an
//			error code will be returned.
//
// ============================================================================
void Aaf2Omf::OpenInputFile ()
{
	AAFCheck					rc;
	aafWChar*					pwFileName = NULL;
	IAAFIdentification*			pIdent = NULL;

	// convert file name to Wide char
	pwFileName = new wchar_t[strlen(gpGlobals->sInFileName)+1];
	mbstowcs(pwFileName, gpGlobals->sInFileName, strlen(gpGlobals->sInFileName)+1);


	if (FAILED(AAFFileOpenExistingRead(pwFileName, 0, &pFile)))
	{
		delete [] pwFileName;
		return;
	}

	if (FAILED(pFile->GetHeader(&pHeader)))
	{
		delete [] pwFileName;
		return;
	}

	if (FAILED(pHeader->GetDictionary(&pDictionary)))
	{
		delete [] pwFileName;
		return;
	}
	if (gpGlobals->bVerboseMode)
	{
		printf("AAF File: %s opened succesfully\n", gpGlobals->sInFileName);
//		printf("          File Revision %s \n", szFileVersion);
	}

	pAAF->RegisterAAFProperties(pDictionary);

	gpGlobals->bAAFFileOpen = kAAFTrue;
	delete [] pwFileName;
}
// ============================================================================
// OpenOutputFile
//			This function creates the output file.
//
// ============================================================================
void Aaf2Omf::OpenOutputFile ()
{
	AAFCheck							rc;
	OMFCheck							OMFError;
	aafBool								bSessionStarted = kAAFFalse;
	
	OMF2::omfProductIdentification_t	OMFProductInfo;
	char*								pszCompanyName = NULL;
	char*								pszProductName = NULL;
    char*								pszProductVersionString = NULL;
    char*								pszPlatform;
	char*								src;
	
	IAAFIdentification*					pIdent = NULL;
	aafWChar*							pwCompanyName = NULL;
	aafWChar*							pwProductName = NULL;
    aafWChar*							pwProductVersionString = NULL;
    aafWChar*							pwPlatform;
	aafUInt32							textSize = 0;
	aafProductVersion_t					productVersion;
	
	try
	{
		if (strlen(gpGlobals->sOutFileName) == 0)
		{
			char*	pExt;
			strcpy(gpGlobals->sOutFileName, gpGlobals->sInFileName);
			pExt= strrchr(gpGlobals->sOutFileName, '.');
			strcpy(pExt,".omf");
		}
		
		if (gpGlobals->bDeleteOutput)
		{
			HRESULT	testRC;
			testRC = deleteFile(gpGlobals->sOutFileName);
			if (testRC == AAFRESULT_SUCCESS)
				printf("Output file: %s will be overwritten\n", gpGlobals->sOutFileName);
			else
				printf("Output file: %s will be created\n", gpGlobals->sOutFileName);
		}
		// Retrieve AAF file's last identification
		rc = pHeader->GetLastIdentification(&pIdent);
		pIdent->GetCompanyNameBufLen(&textSize);
		if (textSize > 0)
		{
			pwCompanyName = (wchar_t *)new wchar_t[textSize];
			pIdent->GetCompanyName(pwCompanyName, textSize);
			pszCompanyName = (char *)new char[textSize/sizeof(wchar_t)];
			wcstombs(pszCompanyName, pwCompanyName, textSize/sizeof(wchar_t));
		}
		else
		{
			src = "<Not Specified>";
			pszCompanyName = (char *)new char[strlen(src)+1];
			strcpy(pszCompanyName, src);
		}
		
		pIdent->GetProductNameBufLen(&textSize);
		if (textSize > 0)
		{
			pwProductName = (wchar_t *)new wchar_t[textSize];
			pIdent->GetProductName(pwProductName, textSize);
			pszProductName = (char *)new char[textSize/sizeof(wchar_t)];
			wcstombs(pszProductName, pwProductName, textSize/sizeof(wchar_t));
		}
		else
		{
			src = "<Not Specified>";
			pszProductName = (char *)new char[strlen(src)+1];
			strcpy(pszProductName, src);
		}
		
		pIdent->GetProductVersionStringBufLen(&textSize);
		if (textSize > 0)
		{
			pwProductVersionString = (wchar_t *)new wchar_t[textSize];
			pIdent->GetProductVersionString(pwProductVersionString, textSize);
			pszProductVersionString = (char *)new char[textSize/sizeof(wchar_t)];
			wcstombs(pszProductVersionString, pwProductVersionString, textSize/sizeof(wchar_t));
		}
		else
		{
			src = "<Not Specified>";
			pszProductVersionString = (char *)new char[strlen(src)+1];
			strcpy(pszProductVersionString, src);
		}
		
		pIdent->GetPlatformBufLen(&textSize);
		if (textSize > 0)
		{
			pwPlatform = (wchar_t *)new wchar_t[textSize/sizeof(wchar_t)];
			pIdent->GetPlatform(pwPlatform, textSize);
			pszPlatform = (char *)new char[textSize/sizeof(wchar_t)];
			wcstombs(pszPlatform, pwPlatform, textSize/sizeof(wchar_t));
		}
		else
		{
			src = "<Not Specified>";
			pszPlatform = (char *)new char[strlen(src)+1];
			strcpy(pszPlatform, src);
		}
		
		
		OMFProductInfo.companyName = pszCompanyName;
		OMFProductInfo.productName = pszProductName;
		OMFProductInfo.productVersionString = pszProductVersionString;
		OMFProductInfo.platform = pszPlatform;
		
		/* rc = !!!*/ pIdent->GetProductVersion(&productVersion);
		OMFProductInfo.productVersion.major = productVersion.major;
		OMFProductInfo.productVersion.minor = productVersion.minor;
		OMFProductInfo.productVersion.tertiary = productVersion.tertiary;
		OMFProductInfo.productVersion.patchLevel = productVersion.patchLevel;
		OMFProductInfo.productID = 42; // Comes from OMF !!!
		OMFProductInfo.productVersion.type = (OMF2::omfProductReleaseType_t)productVersion.type;
		
		if (OMF2::omfsBeginSession(&OMFProductInfo, &OMFSession) != OMF2::OM_ERR_NONE )
		{
			rc = AAFRESULT_BADOPEN;
			goto cleanup;
		}
		
		RegisterCodecProperties(gpGlobals, OMFSession);
		pOMF->RegisterOMFProperties(gpGlobals, OMFSession);
		
		bSessionStarted = kAAFTrue;
		if (OMF2::omfmInit(OMFSession) != OMF2::OM_ERR_NONE )
		{
			OMF2::omfsEndSession(OMFSession);
			rc = AAFRESULT_BAD_SESSION;
			goto cleanup;
		}
		
		
		//	OMFError = omfmRegisterCodec(OMFSession, OMF2::omfCodecAvJPED, OMF2::kOMFRegisterLinked);
		
		if (OMF2::omfsCreateFile((OMF2::fileHandleType)gpGlobals->sOutFileName, OMFSession, OMF2::kOmfRev2x, &OMFFileHdl) != OMF2::OM_ERR_NONE )
		{
			rc = AAFRESULT_BADOPEN;
			goto cleanup;
		}
		
		
		gpGlobals->bOMFFileOpen = kAAFTrue;
		// Clean up and exit 
	}
	catch(...)
	{
		if (pIdent)
			pIdent->Release();
		
		if (pwCompanyName)
			delete [] pwCompanyName;
		
		if (pszCompanyName)
			delete [] pszCompanyName;
		
		if (pwProductName)
			delete [] pwProductName;
		
		if (pszProductName)
			delete [] pszProductName;
		
		if (pwPlatform)
			delete [] pwPlatform;
		
		if (pszPlatform)
			delete [] pszPlatform;
		
		if (pwProductVersionString)
			delete [] pwProductVersionString;
		
		if (pszProductVersionString)
			delete [] pszProductVersionString;
		
		printf("File: %s could NOT be created\n", gpGlobals->sOutFileName);
	}
cleanup:
	if (pIdent)
		pIdent->Release();
	
	if (pwCompanyName)
		delete [] pwCompanyName;
	
	if (pszCompanyName)
		delete [] pszCompanyName;
	
	if (pwProductName)
		delete [] pwProductName;
	
	if (pszProductName)
		delete [] pszProductName;
	
	if (pwPlatform)
		delete [] pwPlatform;
	
	if (pszPlatform)
		delete [] pszPlatform;
	
	if (pwProductVersionString)
		delete [] pwProductVersionString;
	
	if (pszProductVersionString)
		delete [] pszProductVersionString;
	
	if (gpGlobals->bVerboseMode)
	{
		printf("OMF file: %s created succesfully\n", gpGlobals->sOutFileName);
	}
}

// ============================================================================
// CloseOutputFile
//			This function closes the output file.
//
// ============================================================================
void Aaf2Omf::CloseOutputFile()
{
	OMFCheck	OMFError;

	OMFError = OMF2::omfsCloseFile(OMFFileHdl);
	OMFError = OMF2::omfsEndSession(OMFSession);
}

// ============================================================================
// CloseInputFile
//			This function closes the input file.
//
// ============================================================================
void Aaf2Omf::CloseInputFile( )
{
	if (pDictionary)
	{
		pDictionary->Release();
		pDictionary = NULL;
	}

	if (pHeader)
	{
		pHeader->Release();
		pHeader = NULL;
	}

	if (pFile)
	{
		pFile->Close();
		pFile->Release();
		pFile = NULL;
	}
}
// ============================================================================
// AAFFileRead
//
//		Here is where all the real work is done.  
//
// ============================================================================
void Aaf2Omf::AAFFileRead()
{
	AAFCheck				rc;
	OMFCheck				OMFError;

	OMF2::omfMobObj_t		OMFMob = NULL;

	aafNumSlots_t			nAAFNumMobs;
	aafUInt32				numEssenceData = 0;
	IEnumAAFMobs*			pMobIter = NULL;
	IAAFMob*				pMob = NULL;
	IAAFCompositionMob*		pCompMob = NULL;
	IAAFMasterMob*			pMasterMob = NULL;
	IAAFSourceMob*			pSourceMob = NULL;
	IEnumAAFEssenceData*	pEssenceDataIter = NULL;
	IAAFEssenceData*		pEssenceData = NULL;
	aafSearchCrit_t			criteria;

	rc = pHeader->CountMobs(kAAFAllMob, &nAAFNumMobs);
	if (gpGlobals->bVerboseMode)
	{
		printf(" Found: %ld Mobs in the input file\n", nAAFNumMobs);
	}
	criteria.searchTag = kAAFByMobKind;
	criteria.tags.mobKind = kAAFAllMob;
	rc = pHeader->GetMobs(&criteria, &pMobIter);
	while (pMobIter && (pMobIter->NextOne(&pMob) == AAFRESULT_SUCCESS))
	{
		aafUInt32	nameLength = 0;
		aafWChar*	pwMobName = NULL;
		aafMobID_t	MobID;
		char		szMobID[64];
		char*		pszMobName = NULL;

		gpGlobals->nNumAAFMobs++;
		// Get Mob Info
		pMob->GetNameBufLen(&nameLength);
		pwMobName = new wchar_t[nameLength/sizeof(wchar_t)];
		rc = pMob->GetName(pwMobName, nameLength);
		rc = pMob->GetMobID(&MobID);
		pszMobName = new char[nameLength/sizeof(wchar_t)];
		wcstombs(pszMobName, pwMobName, nameLength/sizeof(wchar_t));
		// Is this a composition Mob?
		if (SUCCEEDED(pMob->QueryInterface(IID_IAAFCompositionMob, (void **)&pCompMob)))
		{
			// Composition Mob
			ConvertCompositionMob(pCompMob, &OMFMob, pszMobName, &MobID);
			pCompMob->Release();
			pCompMob = NULL;
		}
		else
		{
			// Is it a Master Mob ?
			if (SUCCEEDED(pMob->QueryInterface(IID_IAAFMasterMob, (void **)&pMasterMob)))
			{
				ConvertMasterMob(pMasterMob, &OMFMob, pszMobName, &MobID);
				pMasterMob->Release();
				pMasterMob = NULL;
			}
			else
			{
				// Is it a Source Mob
				if (SUCCEEDED(pMob->QueryInterface(IID_IAAFSourceMob, (void **)&pSourceMob)))
				{
					ConvertSourceMob(pSourceMob, &OMFMob, pszMobName, &MobID);
					pSourceMob->Release();
					pSourceMob = NULL;
				}
				else
				{
					MobIDtoString(&MobID, szMobID);
					printf("Unrecognized Mob kind encountered ID: %s\n", szMobID);
//					fprintf(stderr,"Unrecognized Mob kind encountered ID: %s\n", szMobID);
				}
			}
		}
		if (OMFMob)
		{
			TraverseMob(pMob, &OMFMob);
			// NOw add user comments 
			aafUInt32	numComments = 0;
			rc = pMob->CountComments(&numComments);
			if (numComments > 0)
			{
				HRESULT	testRC;
				
				IEnumAAFTaggedValues*	pCommentIterator = NULL;
				IAAFTaggedValue*		pMobComment = NULL;
				testRC = pMob->GetComments(&pCommentIterator);
				while ( (SUCCEEDED(testRC)) && (SUCCEEDED(pCommentIterator->NextOne(&pMobComment))))
				{
					char*		pszComment;
					char*		pszCommName;
					aafWChar*	pwcComment;
					aafWChar*	pwcName;
					aafUInt32	textSize;
					aafUInt32	bytesRead;

					pMobComment->GetNameBufLen(&textSize);
					pwcName = new aafWChar [textSize/sizeof(aafWChar)];
					pMobComment->GetName(pwcName, textSize);
					pszCommName =  new char[textSize/sizeof(aafWChar)];
					wcstombs(pszCommName, pwcName, textSize/sizeof(aafWChar));
					pMobComment->GetValueBufLen((aafUInt32 *)&textSize);
					pwcComment = new aafWChar[textSize/sizeof(aafWChar)];
					pMobComment->GetValue((aafUInt32)textSize, (aafDataBuffer_t)pwcComment, &bytesRead);
					pszComment =  new char[textSize/sizeof(aafWChar)];
					wcstombs(pszComment, pwcComment, textSize/sizeof(aafWChar));
					OMFError = OMF2::omfiMobAppendComment(OMFFileHdl, OMFMob, pszCommName, pszComment);
					delete [] pszCommName;
					pszCommName = NULL;
					delete [] pszComment;
					pszComment = NULL;
					delete [] pwcName;
					pwcName = NULL;
					delete [] pwcComment;
					pwcComment = NULL;
					pMobComment->Release();
					pMobComment = NULL;
				}
				pCommentIterator->Release();
			}
		}
		delete [] pwMobName;
		delete [] pszMobName;
		gpGlobals->nNumOMFMobs++;
		pMob->Release();
		pMob = NULL;
	}
	if (pMobIter)
		pMobIter->Release();

	// Now get the media data.
	rc = pHeader->CountEssenceData(&numEssenceData);
	if (numEssenceData > 0)
	{
		if (gpGlobals->bVerboseMode)
		{
			printf(" Found: %ld Essence data objects\n", numEssenceData);
		}
		rc = pHeader->EnumEssenceData(&pEssenceDataIter);
		while (SUCCEEDED(pEssenceDataIter->NextOne(&pEssenceData)))
		{
			ConvertEssenceDataObject(pEssenceData);
		}
		if (pEssenceDataIter)
		{
			pEssenceDataIter->Release();
			pEssenceDataIter = NULL;
		}
		if (pEssenceData)
		{
			pEssenceData->Release();
			pEssenceData = NULL;
		}
	}
	if (pMasterMob)
		pMasterMob->Release();
	if (pSourceMob)
		pSourceMob->Release();
	if (pCompMob)
		pCompMob->Release();
}
// ============================================================================
// ConvertCompositionMob
//
//			This function extracts all the properties of an AAF Composition MOB,
//			Creates an OMF Composition mob object, sets its properties and 
//			appends it to the OMF header. 
//
//			
// Returns: AAFRESULT_SUCCESS if MOB object is converted succesfully
//
// ============================================================================
void Aaf2Omf::ConvertCompositionMob(IAAFCompositionMob* pCompMob,
									   OMF2::omfMobObj_t* pOMFCompMob,
									   char* pMobName,
									   aafMobID_t* pMobID)
{
	AAFCheck				rc;
	OMFCheck				OMFError;
	
	OMF2::omfUID_t			OMFMobID;
	OMF2::omfDefaultFade_t	OMFFade;
	IAAFMob					*pMob = NULL;
	aafDefaultFade_t		DefaultFade;
	
	OMFError = OMF2::omfiCompMobNew(OMFFileHdl, pMobName, (OMF2::omfBool)kAAFFalse, pOMFCompMob);
	
	ConvertMobIDtoUID(pMobID, &OMFMobID);
	OMFError = OMF2::omfiMobSetIdentity(OMFFileHdl, *pOMFCompMob, OMFMobID);
	
	if ((pCompMob->GetDefaultFade(&DefaultFade) == AAFRESULT_SUCCESS) && DefaultFade.valid)
	{
		OMFFade.fadeLength = DefaultFade.fadeLength;
		switch (DefaultFade.fadeType)
		{
		case kAAFFadeNone:
			OMFFade.fadeType = OMF2::kFadeNone;
			break;
		case kAAFFadeLinearAmp:
			OMFFade.fadeType = OMF2::kFadeLinearAmp;
			break;
		case kAAFFadeLinearPower:
			OMFFade.fadeType = OMF2::kFadeLinearPower;
			break;
		}
		OMFFade.fadeEditUnit.numerator = DefaultFade.fadeEditUnit.numerator;
		OMFFade.fadeEditUnit.denominator = DefaultFade.fadeEditUnit.denominator;
		
		OMFError = OMF2::omfiMobSetDefaultFade(OMFFileHdl,
			*pOMFCompMob,
			OMFFade.fadeLength, 
			OMFFade.fadeType ,
			OMFFade.fadeEditUnit);
		
	}
	
	rc = pCompMob->QueryInterface(IID_IAAFMob, (void **)&pMob);
	FinishUpMob(pMob, *pOMFCompMob);
	
	//	if (OMFError != OMF2::OM_ERR_NONE)
	//		rc = AAFRESULT_INTERNAL_ERROR;
}
// ============================================================================
// ConvertMasterMob
//
//			This function extracts all the properties of an AAF Master MOB,
//			Creates an OMF Master mob object, sets its properties and 
//			appends it to the OMF header. 
//
//			
// Returns: AAFRESULT_SUCCESS if MOB object is converted succesfully
//
// ============================================================================
void Aaf2Omf::ConvertMasterMob(IAAFMasterMob* pMasterMob,
								  OMF2::omfMobObj_t* pOMFMasterMob,
								  char* pMobName,
								  aafMobID_t* pMobID)
{
	AAFCheck				rc;
	OMFCheck				OMFError;
	IAAFMob					*pMob = NULL;
	
	OMF2::omfUID_t		OMFMobID;
	
	OMFError = OMF2::omfmMasterMobNew(OMFFileHdl, pMobName, (OMF2::omfBool)kAAFTrue, pOMFMasterMob);
	
	ConvertMobIDtoUID(pMobID, &OMFMobID);
	OMFError = OMF2::omfiMobSetIdentity(OMFFileHdl, *pOMFMasterMob, OMFMobID);
	
	if (gpGlobals->bVerboseMode)
		printf("Converted AAF Master MOB to OMF\n");
	
	rc = pMasterMob->QueryInterface(IID_IAAFMob, (void **)&pMob);
	FinishUpMob(pMob, *pOMFMasterMob);
	
	//	if (OMFError != OMF2::OM_ERR_NONE)
	//		rc = AAFRESULT_INTERNAL_ERROR;
}

// ============================================================================
// ConvertSourceMob
//
//			This function extracts all the properties of an AAF Source MOB,
//			Creates an OMF Source mob object, sets its properties and 
//			appends it to the OMF header. 
//
//			
// Returns: AAFRESULT_SUCCESS if MOB object is converted succesfully
//
// ============================================================================
void Aaf2Omf::ConvertSourceMob(IAAFSourceMob* pSourceMob,
								  OMF2::omfMobObj_t* pOMFSourceMob,
								  char* pMobName,
								  aafMobID_t* pMobID)
{
	AAFCheck				rc;
	OMFCheck				OMFError;

	OMF2::omfUID_t			OMFMobID;


	IAAFEssenceDescriptor*	pEssenceDesc = NULL;
	IAAFTapeDescriptor*		pTapeDesc = NULL;
	IAAFFileDescriptor*		pFileDesc = NULL;
	IAAFTIFFDescriptor*		pTiffDesc = NULL;
	IAAFWAVEDescriptor*		pWAVEDesc = NULL;
	IAAFAIFCDescriptor*		pAifcDesc = NULL;
	IAAFDigitalImageDescriptor* pDIDDDesc = NULL;
	IAAFCDCIDescriptor*		pCDCIDesc = NULL;
	IAAFObject*				pAAFObject = NULL;
	aafInt32				*lineMap = NULL;
	IAAFMob					*pMob = NULL;

	if (gpGlobals->bVerboseMode)
		printf("Converting AAF Source MOB to OMF\n");

	rc = pSourceMob->GetEssenceDescriptor(&pEssenceDesc);

	IncIndentLevel();

	ConvertMobIDtoUID(pMobID, &OMFMobID);
	if (SUCCEEDED(pEssenceDesc->QueryInterface(IID_IAAFTapeDescriptor,(void **)&pTapeDesc)))
	{
		// This is Tape Descriptor 
		// Therefore the Source Mob is a Tape Mob
		aafWChar*			pwManufacturer = NULL;
		char*				pszManufacturer = NULL;
		aafWChar*			pwModel = NULL;
		char*				pszModel = NULL;
		aafUInt32			textSize;
		aafTapeCaseType_t	formFactor;
		aafTapeFormatType_t	tapeFormat;
		aafLength_t			tapeLength;
		aafVideoSignalType_t videoSignal;
		
		OMFError = OMF2::omfmTapeMobNew(OMFFileHdl, pMobName, pOMFSourceMob);
		
		OMFError = OMF2::omfiMobSetIdentity(OMFFileHdl, *pOMFSourceMob, OMFMobID);
		pTapeDesc->GetTapeFormFactor(&formFactor);
		pTapeDesc->GetSignalType(&videoSignal);
		pTapeDesc->GetTapeFormat(&tapeFormat);
		pTapeDesc->GetTapeLength(&tapeLength);
		pTapeDesc->GetTapeManufacturerBufLen(&textSize);
		if (textSize > 0)
		{
			pwManufacturer = new aafWChar[textSize/sizeof(aafWChar)];
			pTapeDesc->GetTapeManufacturer(pwManufacturer, textSize);
			pszManufacturer = new char[textSize/sizeof(aafWChar)];
			wcstombs(pszManufacturer, pwManufacturer, textSize/sizeof(aafWChar));
		}
		else
			pszManufacturer = NULL;
		pTapeDesc->GetTapeModelBufLen(&textSize);
		if (textSize > 0)
		{
			pwModel = new aafWChar[textSize/sizeof(wchar_t)];
			pTapeDesc->GetTapeModel(pwModel, textSize);
			pszModel = new char[textSize/sizeof(aafWChar)];
			wcstombs(pszModel, pwModel, textSize/sizeof(aafWChar));
		}
		else
			pszModel = NULL;
		
		OMFError = OMF2::omfmTapeMobSetDescriptor(OMFFileHdl,
												*pOMFSourceMob,
												(OMF2::omfTapeCaseType_t *)&formFactor,
												(OMF2::omfVideoSignalType_t *)&videoSignal,
												(OMF2::omfTapeFormatType_t *)&tapeFormat,
												(OMF2::omfLength_t *)&tapeLength,
												pszManufacturer,
												pszModel);
		if (gpGlobals->bVerboseMode)
			printf("%sAdded a Tape Essence Descriptor to a Source MOB\n", gpGlobals->indentLeader);
		if (pwManufacturer)
			delete [] pwManufacturer;
		if (pszManufacturer)
			delete [] pszManufacturer;
		if (pwModel)
			delete [] pwModel;
		if (pszModel)
			delete [] pszModel;
		
		rc = pSourceMob->QueryInterface(IID_IAAFMob, (void **)&pMob);
		FinishUpMob(pMob, *pOMFSourceMob);
		
		goto cleanup;
	}

	if (SUCCEEDED(pEssenceDesc->QueryInterface(IID_IAAFFileDescriptor,(void **)&pFileDesc)))
	{
		// This is File Descriptor
		OMF2::omfRational_t	rate;
		aafRational_t		sampleRate;
		aafLength_t		length;	

		pFileDesc->GetSampleRate(&sampleRate);
		pFileDesc->GetLength(&length);
		rate.numerator = sampleRate.numerator;
		rate.denominator = sampleRate.denominator;
		if (SUCCEEDED(pEssenceDesc->QueryInterface(IID_IAAFTIFFDescriptor, (void **)&pTiffDesc)))
		{
			// It is a TIFF file descriptor
			OMF2::omfDDefObj_t	datakind;
			OMF2::omfObject_t	mediaDescriptor;
			aafInt32			leadingLines, trailingLines;
			aafJPEGTableID_t	JPEGTableID;
			aafDataValue_t		pSummary;
			aafUInt32			summarySize = 0;
			aafBool				IsUniform;
			aafBool				IsContiguous;

			// retrieve TIFF descriptor properties
			rc = pTiffDesc->GetSummaryBufferSize(&summarySize);
			pSummary = new aafUInt8[summarySize];
			rc = pTiffDesc->GetSummary(summarySize, pSummary);
			rc = pTiffDesc->GetTrailingLines(&trailingLines);
			rc = pTiffDesc->GetLeadingLines(&leadingLines);
			rc = pTiffDesc->GetIsUniform(&IsUniform);
			rc = pTiffDesc->GetIsContiguous(&IsContiguous);
			rc = pTiffDesc->GetJPEGTableID(&JPEGTableID);

			// Create a new OMF TIFF File Descriptor
			OMFError = OMF2::omfmFileMobNew(OMFFileHdl, pMobName, rate, CODEC_TIFF_VIDEO, pOMFSourceMob);
			OMFError = OMF2::omfmMobGetMediaDescription(OMFFileHdl, *pOMFSourceMob, &mediaDescriptor);
			OMFError = OMF2::omfiMobSetIdentity(OMFFileHdl, *pOMFSourceMob, OMFMobID);
			OMFError = OMF2::omfsWriteLength(OMFFileHdl, mediaDescriptor, OMF2::OMMDFLLength, (OMF2::omfLength_t)length); 
//!!!			if (OMFError)
//			{
//				char* pErrString = OMF2::omfsGetErrorString(OMFError);
//				fprintf(stderr,"%sAn error occurred while adding TIFF Media descritptor, ERROR = %s\n",gpGlobals->indentLeader, pErrString);
//				goto cleanup;
//			}
			if (gpGlobals->bVerboseMode)
				printf("%sAdded a Tiff Media Descriptor to a Source MOB\n", gpGlobals->indentLeader);

			// Set OMF TIFF File Descriptor properties
			OMF2::omfiDatakindLookup(OMFFileHdl, "omfi:data:Picture", &datakind, (OMF2::omfErr_t *)&rc);
			OMFError = OMF2::omfsWriteBoolean( OMFFileHdl,
										mediaDescriptor,
										OMF2::OMTIFDIsContiguous, 
										(OMF2::omfBool)IsContiguous);
			OMFError = OMF2::omfsWriteBoolean( OMFFileHdl,
										mediaDescriptor,
										OMF2::OMTIFDIsUniform,
										(OMF2::omfBool)IsUniform);
			OMFError = OMF2::omfsWriteDataValue(OMFFileHdl,
										 mediaDescriptor,
										 OMF2::OMTIFDSummary,
										 datakind,
										 (OMF2::omfDataValue_t)pSummary,
										 (OMF2::omfPosition_t)0,
										 summarySize);
			OMFError = OMF2::omfsWriteJPEGTableIDType( OMFFileHdl,
								 				 mediaDescriptor,
												 OMF2::OMTIFDJPEGTableID, 
												 (OMF2::omfJPEGTableID_t)JPEGTableID);
			OMFError = OMF2::omfsWriteInt32(OMFFileHdl,
									 mediaDescriptor,
									 OMF2::OMTIFDLeadingLines, 
									 leadingLines);
			OMFError = OMF2::omfsWriteInt32(OMFFileHdl,
									 mediaDescriptor,
									 OMF2::OMTIFDTrailingLines, 
									 trailingLines);
//			if (OMFError)
//!!!			{
//				char* pErrString = OMF2::omfsGetErrorString(OMFError);
//				fprintf(stderr,"%sAn error occurred while adding TIFF Media descritptor, ERROR = %s\n",gpGlobals->indentLeader, pErrString);
//				goto cleanup;
//			}
			delete [] pSummary;
			rc = pSourceMob->QueryInterface(IID_IAAFMob, (void **)&pMob);
			FinishUpMob(pMob, *pOMFSourceMob);
			goto cleanup;
		}
		if (SUCCEEDED(pEssenceDesc->QueryInterface(IID_IAAFWAVEDescriptor, (void **)&pWAVEDesc)))
		{
			// It is a WAVE file descriptor
			OMF2::omfDDefObj_t	datakind;
			OMF2::omfObject_t	mediaDescriptor;
			aafDataValue_t		pSummary;
			aafUInt32			summarySize = 0;

			// retrieve WAVE descriptor properties
			rc = pWAVEDesc->GetSummaryBufferSize(&summarySize);
			pSummary = new aafUInt8[summarySize];
			rc = pWAVEDesc->GetSummary(summarySize, pSummary);

			//Create a new WAVE File Descriptor
			OMFError = OMF2::omfmFileMobNew(OMFFileHdl, pMobName, rate, CODEC_WAVE_AUDIO, pOMFSourceMob);
			OMFError = OMF2::omfiMobSetIdentity(OMFFileHdl, *pOMFSourceMob, OMFMobID);
			OMFError = OMF2::omfmMobGetMediaDescription(OMFFileHdl, *pOMFSourceMob, &mediaDescriptor);
			OMFError = OMF2::omfsWriteLength(OMFFileHdl, mediaDescriptor, OMF2::OMMDFLLength, (OMF2::omfLength_t)length); 
			OMF2::omfiDatakindLookup(OMFFileHdl, "omfi:data:Sound", &datakind, (OMF2::omfErr_t *)&rc);
			OMFError = OMF2::omfsWriteDataValue(OMFFileHdl,
										 mediaDescriptor,
										 OMF2::OMWAVDSummary,
										 datakind,
										 (OMF2::omfDataValue_t)pSummary,
										 (OMF2::omfPosition_t)0,
										 summarySize);
			if (gpGlobals->bVerboseMode)
				printf("%sAdded a Wave Media Descriptor to a Source MOB\n", gpGlobals->indentLeader);
			rc = pSourceMob->QueryInterface(IID_IAAFMob, (void **)&pMob);
			FinishUpMob(pMob, *pOMFSourceMob);
			goto cleanup;
		}
		if (SUCCEEDED(pEssenceDesc->QueryInterface(IID_IAAFAIFCDescriptor, (void **)&pAifcDesc)))
		{
			// It is a AIFC file descriptor
			OMF2::omfObject_t	mediaDescriptor;
			aafDataValue_t		pSummary;
			aafUInt32			summarySize = 0;

			// retrieve AIFC descriptor properties
			rc = pAifcDesc->GetSummaryBufferSize(&summarySize);
			pSummary = new aafUInt8[summarySize];
			rc = pAifcDesc->GetSummary(summarySize, pSummary);
			
			OMFError = OMF2::omfmFileMobNew(OMFFileHdl, pMobName, rate, CODEC_AIFC_AUDIO, pOMFSourceMob);
			OMFError = OMF2::omfiMobSetIdentity(OMFFileHdl, *pOMFSourceMob, OMFMobID);
			OMFError = OMF2::omfmMobGetMediaDescription(OMFFileHdl, *pOMFSourceMob, &mediaDescriptor);
			OMFError = OMF2::omfsWriteLength(OMFFileHdl, mediaDescriptor, OMF2::OMMDFLLength, (OMF2::omfLength_t)length); 
			if (gpGlobals->bVerboseMode)
				printf("%sAdded an AIFC Media Descriptor to a Source MOB\n", gpGlobals->indentLeader);
			delete [] pSummary;
			rc = pSourceMob->QueryInterface(IID_IAAFMob, (void **)&pMob);
			FinishUpMob(pMob, *pOMFSourceMob);
			goto cleanup;
		}
		if (SUCCEEDED(pEssenceDesc->QueryInterface(IID_IAAFCDCIDescriptor, (void **)&pCDCIDesc)))
		{
			aafUInt32				storedWidth, storedHeight, lineMapSize, n;
			aafUInt32				dispWidth, dispHeight, sampWidth, sampHeight;
			aafInt32				sampX, sampY, dispX, dispY, align;
			aafAlphaTransparency_t	alphaTrans;
			aafFrameLayout_t		layout;
			OMF2::omfObject_t		mediaDescriptor;
			aafRational_t			gamma, aspect;
			OMF2::omfRational_t		OMFGamma, OMFAspect;
			aafUID_t				compressionID;
			char					*omfclassID;
			char					*omfCompression;

			// It is a CDCI file descriptor
			rc = pEssenceDesc->QueryInterface(IID_IAAFDigitalImageDescriptor, (void **)&pDIDDDesc);//!!!
			rc = pDIDDDesc->GetCompression(&compressionID);
			if(memcmp(&compressionID, &CodecJPEG, sizeof(CodecJPEG)) == 0)
			{
				omfclassID = "CDCI";		// For now!!! (Get full toolkit w/all codecs later)
//				omfclassID = "JPED";
				omfCompression = "JFIF";
			}
			else
			{
				omfclassID = "CDCI";
				omfCompression = "";
			}

			OMFError = OMF2::omfmFileMobNew(OMFFileHdl, pMobName, rate, omfclassID, pOMFSourceMob);
			OMFError = OMF2::omfiMobSetIdentity(OMFFileHdl, *pOMFSourceMob, OMFMobID);
			OMFError = OMF2::omfmMobGetMediaDescription(OMFFileHdl, *pOMFSourceMob, &mediaDescriptor);
			OMFError = OMF2::omfsWriteLength(OMFFileHdl, mediaDescriptor, OMF2::OMMDFLLength, (OMF2::omfLength_t)length); 
			
			// Get Digital Image properties and set them
			// Toolkit still expects signed
			pDIDDDesc->GetStoredView(&storedWidth, &storedHeight);
			OMFError = OMF2::omfsWriteInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDStoredHeight, storedHeight);
			OMFError = OMF2::omfsWriteInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDStoredWidth, storedWidth);

			if(pDIDDDesc->GetSampledView(&sampHeight, &sampWidth, &sampX, &sampY) == AAFRESULT_SUCCESS)
			{
				OMFError = OMF2::omfsWriteUInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDSampledHeight, sampHeight);
				OMFError = OMF2::omfsWriteUInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDSampledWidth, sampWidth);
				OMFError = OMF2::omfsWriteInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDSampledXOffset, sampX);
				OMFError = OMF2::omfsWriteInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDSampledYOffset, sampY);
			}

			if(pDIDDDesc->GetDisplayView(&dispHeight, &dispWidth, &dispX, &dispY) == AAFRESULT_SUCCESS)
			{
				OMFError = OMF2::omfsWriteUInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDDisplayHeight, dispHeight);
				OMFError = OMF2::omfsWriteUInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDDisplayWidth, dispWidth);
				OMFError = OMF2::omfsWriteInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDDisplayXOffset, dispX);
				OMFError = OMF2::omfsWriteInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDDisplayYOffset, dispY);
			}
			rc = pDIDDDesc->GetFrameLayout(&layout);
			OMFError = OMF2::omfsWriteLayoutType(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDFrameLayout, (OMF2::omfFrameLayout_t)(layout+1));	// Toolkit used incorrect layout

			if(pDIDDDesc->GetGamma(&gamma) == AAFRESULT_SUCCESS)
			{
				OMFGamma.numerator = gamma.numerator;
				OMFGamma.denominator = gamma.denominator;
				OMFError = OMF2::omfsWriteRational(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDGamma, OMFGamma);
			}

			rc = pDIDDDesc->GetVideoLineMapSize(&lineMapSize);
			lineMap = new aafInt32[lineMapSize];
			rc = pDIDDDesc->GetVideoLineMap(lineMapSize, lineMap);
			// Possibly translate old line map #'s into new ones?!!!
			for(n = 0; n < lineMapSize; n++)
			{
				OMFError = OMF2::OMWriteProp(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDVideoLineMap, 
				n*sizeof(aafInt32), OMF2::OMInt32Array,
				sizeof(aafInt32), lineMap+n);
			}
			delete [] lineMap;
			lineMap = NULL;

			//
			OMFError = OMF2::omfsWriteString(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDCompression, omfCompression);

			//
			if(pDIDDDesc->GetImageAspectRatio(&aspect) == AAFRESULT_SUCCESS)
			{
				OMFAspect.numerator = aspect.numerator;
				OMFAspect.denominator = aspect.denominator;
				OMFError = OMF2::omfsWriteRational(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDImageAspectRatio, OMFAspect);
			}

			//
			if(pDIDDDesc->GetAlphaTransparency(&alphaTrans) == AAFRESULT_SUCCESS)
			{
				OMFError = OMF2::omfsWriteInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDAlphaTransparency, alphaTrans);
			}
			if(pDIDDDesc->GetImageAlignmentFactor(&align) == AAFRESULT_SUCCESS)
			{
				OMFError = OMF2::omfsWriteInt32(OMFFileHdl, mediaDescriptor, OMF2::OMDIDDFieldAlignment, align);
			}
			
			// retrieve CDCI descriptor properties
			aafInt32			componentWidth;
			aafUInt32			horizSubsample;
			aafColorSiting_t	cositing;

			// Find out which are optional & which must fail!!!
			rc = pCDCIDesc->GetComponentWidth(&componentWidth);
			OMFError = OMF2::omfsWriteInt32(OMFFileHdl, mediaDescriptor, gpGlobals->omCDCIComponentWidth, componentWidth); 

			rc = pCDCIDesc->GetHorizontalSubsampling(&horizSubsample);
			OMFError = OMF2::omfsWriteUInt32(OMFFileHdl, mediaDescriptor, gpGlobals->omCDCIHorizontalSubsampling, horizSubsample); 

			rc = pCDCIDesc->GetColorSiting(&cositing);
			OMFError = OMF2::OMWriteProp(OMFFileHdl, mediaDescriptor, gpGlobals->omCDCIColorSiting, 
						  0, OMF2::OMColorSitingType,
						  sizeof(cositing), (void *)&(cositing));

			if (gpGlobals->bVerboseMode)
				printf("%sAdded a CDCI Media Descriptor to a Source MOB\n", gpGlobals->indentLeader);
			rc = pSourceMob->QueryInterface(IID_IAAFMob, (void **)&pMob);
			FinishUpMob(pMob, *pOMFSourceMob);
			goto cleanup;
		}
		if (SUCCEEDED(pEssenceDesc->QueryInterface(IID_IAAFObject, (void **)&pAAFObject)))
		{
			// Media descriptor not implemented or not recognized
			aafUID_t	ObjClass;
			char		szTempUID[64];

			// pAAFObject->GetObjectClass(&ObjClass);
			IAAFClassDef * classDef = 0;
			pAAFObject->GetDefinition(&classDef);
			IAAFDefObject * defObj = 0;
			classDef->QueryInterface(IID_IAAFDefObject, (void **)&defObj);
			defObj->GetAUID (&ObjClass);
			if (defObj)
			  {
				defObj->Release ();
				defObj = 0;
			  }
			if (classDef)
			  {
				classDef->Release ();
				classDef = 0;
			  }

			AUIDtoString(&ObjClass ,szTempUID);
			if (gpGlobals->bVerboseMode)
				printf("%sInvalid essence descripor type found, datadef : %s\n", gpGlobals->indentLeader, szTempUID);
			fprintf(stderr,"%sInvalid essence descriptor type found, datadef : %s\n", gpGlobals->indentLeader, szTempUID);
		}
		rc = pSourceMob->QueryInterface(IID_IAAFMob, (void **)&pMob);
		FinishUpMob(pMob, *pOMFSourceMob);
		goto cleanup;
	}

cleanup:

	if (pOMFSourceMob)
		ConvertLocator(pEssenceDesc, pOMFSourceMob);
	if (pTapeDesc)
		pTapeDesc->Release();

	if (pFileDesc)
		pFileDesc->Release();

	if (pTiffDesc)
		pTiffDesc->Release();

	if (pWAVEDesc)
		pWAVEDesc->Release();

	if (pAifcDesc)
		pAifcDesc->Release();

	if (pCDCIDesc)
		pCDCIDesc->Release();
	if (pDIDDDesc)
		pDIDDDesc->Release();
	if(lineMap != NULL)
		delete [] lineMap;

	DecIndentLevel();
//	if (OMFError != OMF2::OM_ERR_NONE)
//		rc = AAFRESULT_INTERNAL_ERROR;
}
// ============================================================================
// TraverseMob
//
//			This function inspects the given AAF Mopb for components and recursively
//			visits and convert every component within the MOB. 
//			The objects found are converted to OMF and attached to the OMF object.
//
//			
// Returns: AAFRESULT_SUCCESS if MOB object is converted succesfully
//
// ============================================================================
void Aaf2Omf::TraverseMob(IAAFMob* pMob,
							 OMF2::omfMobObj_t* pOMFMob)
{
	AAFCheck				rc;
	OMFCheck				OMFError;
	
	OMF2::omfMSlotObj_t		OMFNewSlot = NULL;
	OMF2::omfSegObj_t		OMFSegment = NULL;
	OMF2::omfTrackID_t		OMFTrackID;
	OMF2::omfRational_t		OMFeditRate;
	OMF2::omfPosition_t		OMFOrigin;
	char*					pszTrackName = NULL;
	aafWChar*				pwTrackName = NULL;					

	IAAFComponent*			pComponent = NULL;
	IAAFMobSlot*			pSlot = NULL;
	IAAFTimelineMobSlot*	pTimelineMobSlot = NULL;
	IAAFSegment*			pSegment = NULL;
	IEnumAAFMobSlots*		pSlotIter = NULL;
	aafNumSlots_t			numSlots;
//	aafSearchCrit_t			criteria;
	aafUInt32				textSize;

	rc = pMob->CountSlots(&numSlots);

	rc = pMob->GetSlots(&pSlotIter);
	
	IncIndentLevel();
	if (gpGlobals->bVerboseMode)
	{
		printf("%sFound: %ld sub slots\n", gpGlobals->indentLeader, numSlots);
	}

	for (aafUInt32 times = 0; times< numSlots; times++)
	{
		if (AAFRESULT_SUCCESS == pSlotIter->NextOne(&pSlot))
		{
			//	Process Segment data
			pSlot->GetNameBufLen(&textSize);
			pwTrackName = new wchar_t[textSize/sizeof(wchar_t)];
			pSlot->GetName(pwTrackName, textSize);
			pwTrackName = new wchar_t[textSize/sizeof(wchar_t)];
			wcstombs(pszTrackName, pwTrackName, textSize/sizeof(wchar_t));
			pSlot->GetSlotID( (aafSlotID_t *)&OMFTrackID);
			if (SUCCEEDED(pSlot->QueryInterface(IID_IAAFTimelineMobSlot, (void **)&pTimelineMobSlot)))
			{
				pTimelineMobSlot->GetOrigin((aafPosition_t *)&OMFOrigin);
				pTimelineMobSlot->GetEditRate((aafRational_t *)&OMFeditRate);
				pTimelineMobSlot->Release();
				pTimelineMobSlot = NULL;
			}
			if (FAILED(pSlot->GetSegment(&pSegment)))
				break;
			pSegment->QueryInterface(IID_IAAFComponent, (void **)&pComponent);
			ProcessComponent(pComponent, &OMFSegment);

			OMFError = OMF2::omfiMobAppendNewTrack(OMFFileHdl,
											 *pOMFMob,
											 OMFeditRate,
											 OMFSegment,
											 OMFOrigin,
											 OMFTrackID,
											 pszTrackName, 
											 &OMFNewSlot);
			if (gpGlobals->bVerboseMode)
			{
				printf("%sConverted SlotID: %d, Name: %s\n",gpGlobals->indentLeader, (int)OMFTrackID, pszTrackName);
			}
			if (pszTrackName)
			{
				delete [] pszTrackName;
				pszTrackName = NULL;
			}
			if (pwTrackName)
			{
				delete [] pwTrackName;
				pwTrackName = NULL;
			}
			if (pSlot)
			{
				pSlot->Release();
				pSlot = NULL;
			}
			if (pComponent)
			{
				pComponent->Release();
				pComponent = NULL;
			}
			if (pSegment)
			{
				pSegment->Release();
				pSegment = NULL;
			}
		}
	}

	DecIndentLevel();
	pSlotIter->Release();
	pSlotIter = NULL;

//	if (OMFError != OMF2::OM_ERR_NONE)
//		rc = AAFRESULT_INTERNAL_ERROR;
}

// ============================================================================
// ProcessComponent
//
//			This function will :
//				1. Identify type of AAF Component
//				2. Create the equivalent OMF object
//				3. Convert the AAF datakind to OMF datadef of the object
//				4. Traverse the component (if needed) into its objects
//				5. return the OMF segment 
//
//	INPUTS:		pComponent	Pointer to a AAF Component Interface pointer
//				pOMFSegment	Pointer an OMF object to be created.
//
//	OUTPUTS:	pOMFSegment	new OMF Segment	
//			
// Returns: AAFRESULT_SUCCESS if MOB object is converted succesfully
//
// ============================================================================
void Aaf2Omf::ProcessComponent(IAAFComponent* pComponent, 
								  OMF2::omfObject_t* pOMFSegment)
{
	AAFCheck					rc = AAFRESULT_SUCCESS;
	OMFCheck				OMFError;

	OMF2::omfDDefObj_t		OMFDatakind;

	IAAFSequence*			pSequence = NULL;
	IAAFSourceClip*			pSourceClip = NULL;
	IAAFTimecode*			pTimecode = NULL;
	IAAFEdgecode*			pEdgecode = NULL;
	IAAFFiller*				pFiller = NULL;
	IAAFTransition*			pTransition = NULL;
	IAAFSelector*			pSelector = NULL;
	IAAFOperationGroup*		pEffect = NULL;
	IAAFScopeReference*		pScopeRef = NULL;
	IAAFDataDef*            pDataDef = 0;
	IAAFDefObject*          pDefObj = 0;
	IAAFNestedScope*		pNest = 0;
	aafUID_t				datadef;
	aafLength_t				length;

	IncIndentLevel();
	

	rc = pComponent->GetDataDef(&pDataDef);

	rc = pDataDef->QueryInterface(IID_IAAFDefObject, (void **)&pDefObj);

	pDataDef->Release();
	pDataDef = 0;
	rc = pDefObj->GetAUID(&datadef);

	pDefObj->Release();
	pDefObj = 0;
	
	ConvertAAFDatadef(datadef, &OMFDatakind);

	rc = pComponent->GetLength(&length);
	if (SUCCEEDED(pComponent->QueryInterface(IID_IAAFSequence, (void **)&pSequence)))
	{
		// Component is a sequence
		OMFError = OMF2::omfiSequenceNew(OMFFileHdl, OMFDatakind, pOMFSegment);
		if (gpGlobals->bVerboseMode)
			printf("%sProcessing Sequence\n", gpGlobals->indentLeader);
		TraverseSequence(pSequence, pOMFSegment);
		goto cleanup;
	}

	if (SUCCEEDED(pComponent->QueryInterface(IID_IAAFSourceClip, (void **)&pSourceClip)))
	{
		// component is a source clip
		aafSourceRef_t			ref;
		OMF2::omfSourceRef_t	OMFSourceRef;
		aafFadeType_t			fadeInType, fadeOutType;
		aafLength_t				fadeInLen, fadeOutLen;
		aafBool					fadeInPresent, fadeOutPresent;
		
		if (gpGlobals->bVerboseMode)
		{
			printf("%sProcessing Source Clip of length: %ld\n ", gpGlobals->indentLeader, (int)length);
		}
		// Get Source Clip properties
		pSourceClip->GetSourceReference(&ref);
		pSourceClip->GetFade(&fadeInLen,
			&fadeInType,
			&fadeInPresent,
			&fadeOutLen,
			&fadeOutType,
			&fadeOutPresent);
		ConvertMobIDtoUID(&ref.sourceID, &OMFSourceRef.sourceID);
		OMFSourceRef.sourceTrackID = (OMF2::omfTrackID_t)ref.sourceSlotID;
		OMFSourceRef.startTime = (OMF2::omfPosition_t)ref.startTime;
		// Create OMF Source Clip
		OMFError = OMF2::omfiSourceClipNew(OMFFileHdl,
			OMFDatakind,
			(OMF2::omfLength_t)length,
			OMFSourceRef,
			pOMFSegment);
		if (fadeInPresent || fadeOutPresent)
		{
			// Some 'magic' required to get types to match
			OMF2::omfInt32 fadeInLen32 = (OMF2::omfInt32) fadeInLen;
			OMF2::omfInt32 fadeOutLen32 = (OMF2::omfInt32) fadeOutLen;
			// Check that narrowing of data type didn't throw away
			// data
			if (((aafLength_t) fadeInLen32) != fadeInLen)
			{
				rc = AAFRESULT_INTERNAL_ERROR;
				goto cleanup;
			}
			if (((aafLength_t) fadeOutLen32) != fadeOutLen)
			{
				rc = AAFRESULT_INTERNAL_ERROR;
				goto cleanup;
			}
			OMFError = OMF2::omfiSourceClipSetFade(OMFFileHdl, 
													   *pOMFSegment,
													   fadeInLen32,
													   (OMF2::omfFadeType_t)fadeInType,
													   fadeOutLen32,
													   (OMF2::omfFadeType_t)fadeOutType);
		}
		
		
		goto cleanup;
	}

	if (SUCCEEDED(pComponent->QueryInterface(IID_IAAFTimecode, (void **)&pTimecode)))
	{
		// component is a Timecode
		OMF2::omfTimecode_t	timecode;
		aafTimecode_t		AAFTimecode;

		pTimecode->GetTimecode(&AAFTimecode);

		// Some 'magic' required to get types to match; make sure
		// narrowing of type didn't throw away data
		timecode.startFrame = (OMF2::omfFrameOffset_t) AAFTimecode.startFrame;
		if ((aafFrameOffset_t) timecode.startFrame != AAFTimecode.startFrame)
		{
		  rc = AAFRESULT_INTERNAL_ERROR;
		  goto cleanup;
		}

		timecode.drop = (OMF2::omfDropType_t)AAFTimecode.drop;
		timecode.fps = AAFTimecode.fps;
		if (gpGlobals->bVerboseMode)
		{
			printf("%sProcessing Timecode Clip of length: %ld\n ", gpGlobals->indentLeader, (int)length);
			IncIndentLevel();
			printf("%sstart Frame\t: %ld\n", gpGlobals->indentLeader, timecode.startFrame);
			if (timecode.drop == kAAFTrue)
				printf("%sdrop\t\t: True\n", gpGlobals->indentLeader);
			else
				printf("%sdrop\t\t: False\n", gpGlobals->indentLeader);
			printf("%sFrames/second\t: %ld\n", gpGlobals->indentLeader, timecode.fps);     
			DecIndentLevel();				
		}

		OMFError = OMF2::omfiTimecodeNew(OMFFileHdl, (OMF2::omfLength_t)length, timecode, pOMFSegment);
		goto cleanup;
	}

	if (SUCCEEDED(pComponent->QueryInterface(IID_IAAFEdgecode, (void **)&pEdgecode)))
	{
		// component is an Edgecode
		aafEdgecode_t		edgecode;
		OMF2::omfEdgecode_t	OMFEdgecode;

		pEdgecode->GetEdgecode(&edgecode);

		// Some 'magic' required to get types to match; make sure
		// narrowing of type didn't throw away data
		OMFEdgecode.startFrame = (OMF2::omfFrameOffset_t) edgecode.startFrame;
		if ((aafFrameOffset_t) OMFEdgecode.startFrame != edgecode.startFrame)
		{
		  rc = AAFRESULT_INTERNAL_ERROR;
		  goto cleanup;
		}

		OMFEdgecode.filmKind = (OMF2::omfFilmType_t)edgecode.filmKind;
		OMFEdgecode.codeFormat = (OMF2::omfEdgeType_t)edgecode.codeFormat;
		memcpy(OMFEdgecode.header, edgecode.header, sizeof(edgecode.header));
		if (gpGlobals->bVerboseMode)
		{
			printf("%sProcessing Timecode Clip of length: %ld\n ", gpGlobals->indentLeader, (int)length);
			IncIndentLevel();
			printf("%sstart Frame\t: %ld\n", gpGlobals->indentLeader, edgecode.startFrame);
			DecIndentLevel();				
		}
		OMFError = OMF2::omfiEdgecodeNew(OMFFileHdl, (OMF2::omfLength_t)length, OMFEdgecode, pOMFSegment);		
		goto cleanup;
	}

	if (SUCCEEDED(pComponent->QueryInterface(IID_IAAFFiller, (void **)&pFiller)))
	{
		// component is a filler
		OMFError = OMF2::omfiFillerNew(OMFFileHdl, OMFDatakind, (OMF2::omfLength_t)length, pOMFSegment);
		if (gpGlobals->bVerboseMode)
		{
			printf("%sProcessing Filler of length: %ld\n ", gpGlobals->indentLeader, (int)length);
		}
		goto cleanup;
	}

	if (SUCCEEDED(pComponent->QueryInterface(IID_IAAFOperationGroup, (void **)&pEffect)))
	{
//		//Component is an effect
		OMF2::omfObject_t	nest = NULL;
		OMF2::omfObject_t	effect = NULL;
		IAAFOperationDef	*pEffectDef = NULL;
		IAAFDefObject		*pDefObject = NULL;
		aafUID_t			effectDefAUID;

		if (gpGlobals->bVerboseMode)
		{
			printf("%sProcessing Effect of length: %ld\n ", gpGlobals->indentLeader, (int)length);
		}
		
		// Public effects don't get a surrounding NEST
		rc = pEffect->GetOperationDefinition(&pEffectDef);
		rc = pEffectDef->QueryInterface(IID_IAAFDefObject, (void **) &pDefObject);
		pDefObject->GetAUID(&effectDefAUID);
		pEffectDef->Release();
		pDefObject->Release();

		if(pEffectTranslate->RequiresNestedScope(effectDefAUID))
		{
			OMFError = OMF2::omfiNestedScopeNew(OMFFileHdl, OMFDatakind,
								(OMF2::omfLength_t)length, &nest);
			ConvertEffects(pEffect, nest, &effect);
			OMFError = OMF2::omfiNestedScopeAppendSlot(OMFFileHdl,nest,effect);
			*pOMFSegment = nest;
		}
		else
		{
			ConvertEffects(pEffect, NULL, pOMFSegment);
		}

		goto cleanup;
	}

	if (SUCCEEDED(pComponent->QueryInterface(IID_IAAFTransition, (void **)&pTransition)))
	{
		// component is a Transition
		OMF2::omfEffObj_t	effect;

		aafPosition_t	cutPoint;

		if (gpGlobals->bVerboseMode)
		{
			printf("%sProcessing Transition of length: %ld\n ", gpGlobals->indentLeader, (int)length);
		}
		pTransition->GetCutPoint(&cutPoint);
		rc = pTransition->GetOperationGroup(&pEffect);
		// At this time (4/99) effects are not implemented therefore we 
		// will have to create an Effect from thin air.(hack it !!)
		ConvertEffects(pEffect, NULL, &effect);

		OMFError = OMF2::omfiTransitionNew(OMFFileHdl,
									 OMFDatakind,
									 (OMF2::omfLength_t)length,
									 (OMF2::omfPosition_t)cutPoint,
									 effect,
									 pOMFSegment);
		goto cleanup;
	}

	if (SUCCEEDED(pComponent->QueryInterface(IID_IAAFSelector, (void **)&pSelector)))
	{
		// component is a selector
		IncIndentLevel();
		
		OMFError = OMF2::omfiSelectorNew(OMFFileHdl,
								   OMFDatakind,
								   (OMF2::omfLength_t)length,
								   pOMFSegment);
		ConvertSelector(pSelector, pOMFSegment);
		DecIndentLevel();
		goto cleanup;
	}
	
	if (SUCCEEDED(pComponent->QueryInterface(IID_IAAFNestedScope, (void **)&pNest)))
	{
		// component is a nested scope
		IncIndentLevel();
		
		OMFError = OMF2::omfiNestedScopeNew(OMFFileHdl,
								   OMFDatakind,
								   (OMF2::omfLength_t)length,
								   pOMFSegment);
		ConvertNestedScope(pNest, pOMFSegment);
		DecIndentLevel();
		goto cleanup;
	}

	if (SUCCEEDED(pComponent->QueryInterface(IID_IAAFScopeReference, (void **)&pScopeRef)))
	{
		// component is a source clip
		aafUInt32		relativeScope, relativeSlot;

		if (gpGlobals->bVerboseMode)
		{
			printf("%sProcessing Scope Reference of length: %ld\n ", gpGlobals->indentLeader, (int)length);
		}
		// Get Source Clip properties
        rc = pScopeRef->GetRelativeScope(&relativeScope);
        rc = pScopeRef->GetRelativeSlot(&relativeSlot);
		OMFError = OMF2::omfiScopeRefNew(OMFFileHdl,
									 OMFDatakind,
									 (OMF2::omfLength_t)length,
									 relativeScope,
									 relativeSlot,
									pOMFSegment);

		goto cleanup;
	}

	char szTempUID[64];
	AUIDtoString(&datadef ,szTempUID);
	if (gpGlobals->bVerboseMode)
		printf("%sInvalid component type found, datadef : %s\n", gpGlobals->indentLeader, szTempUID);
	fprintf(stderr,"%sInvalid component type found, datadef : %s\n", gpGlobals->indentLeader, szTempUID);

cleanup:

	if (pScopeRef)
	  {
		pScopeRef->Release();
		pScopeRef = 0;
	  }
	
	if (pNest)
	  {
		pNest->Release();
		pNest = 0;
	  }
	
	if (pSequence)
	  {
		pSequence->Release();
		pSequence = 0;
	  }
	
	if (pSourceClip)
	  {
		pSourceClip->Release();
		pSourceClip = 0;
	  }
	
	if (pTimecode)
	  {
		pTimecode->Release();
		pTimecode = 0;
	  }

	if (pFiller)
	  {
		pFiller->Release();
		pFiller = 0;
	  }
	
	if (pEdgecode)
	  {
		pEdgecode->Release();
		pEdgecode = 0;
	  }

	if (pTransition)
	  {
		pTransition->Release();
		pTransition = 0;
	  }

	if (pSelector)
	  {
		pSelector->Release();
		pSelector = 0;
	  }

	if (pDataDef)
	  {
		pDataDef->Release();
		pDataDef = 0;
	  }

	if (pDefObj)
	  {
		pDefObj->Release();
		pDefObj = 0;
	  }

	DecIndentLevel();
//	if (OMFError != OMF2::OM_ERR_NONE)
//		rc = AAFRESULT_INTERNAL_ERROR;
}
// ============================================================================
// ConvertAAFDatadef
//
//			This function converts an AAF datadef into an OMF datakind. 
//			
// Returns: AAFRESULT_SUCCESS if datakind is converted succesfully
//
// ============================================================================
void Aaf2Omf::ConvertAAFDatadef(aafUID_t Datadef,
								   OMF2::omfDDefObj_t* pDatakind)
{
	AAFCheck				rc;

	OMF2::omfUniqueName_t	datakindName;
	OMF2::omfBool			bFound;
	char					szAUID[64];

	if ( memcmp((char *)&Datadef, (char *)&DDEF_Picture, sizeof(aafUID_t)) == 0 )
	{
		strcpy(datakindName, "omfi:data:Picture");
		bFound = OMF2::omfiDatakindLookup(OMFFileHdl, datakindName, pDatakind, (OMF2::omfErr_t *) &rc);
	}
	else if ( memcmp((char *)&Datadef, (char *)&DDEF_Sound, sizeof(aafUID_t)) == 0 )
	{
		strcpy(datakindName, "omfi:data:Sound");
		bFound = OMF2::omfiDatakindLookup(OMFFileHdl, datakindName, pDatakind, (OMF2::omfErr_t *) &rc);
	}
	else if ( memcmp((char *)&Datadef, (char *)&DDEF_Timecode, sizeof(aafUID_t)) == 0 )
	{
		strcpy(datakindName, "omfi:data:Timecode");
		bFound = OMF2::omfiDatakindLookup(OMFFileHdl, datakindName, pDatakind, (OMF2::omfErr_t *) &rc);
	}
	else if ( memcmp((char *)&Datadef, (char *)&DDEF_Edgecode, sizeof(aafUID_t)) == 0 )
	{
		strcpy(datakindName, "omfi:data:Edgecode");
		bFound = OMF2::omfiDatakindLookup(OMFFileHdl, datakindName, pDatakind, (OMF2::omfErr_t *) &rc);
	}
	else if ( memcmp((char *)&Datadef, (char *)&kAAFEffectPictureWithMate, sizeof(aafUID_t)) == 0 )
	{
		strcpy(datakindName, "omfi:data:PictureWithMatte");
		bFound = OMF2::omfiDatakindLookup(OMFFileHdl, datakindName, pDatakind, (OMF2::omfErr_t *) &rc);
	}
	else
	{
		AUIDtoString(&Datadef, szAUID);
		printf("%sInvalid DataDef Found in sequence AUID : %s\n", gpGlobals->indentLeader, szAUID);
		fprintf(stderr,"%sInvalid DataDef Found in sequence AUID : %s\n", gpGlobals->indentLeader, szAUID);
		rc = AAFRESULT_INVALID_DATADEF;
	}

	if (!bFound)
		rc = AAFRESULT_INVALID_DATADEF;
}

// ============================================================================
// ConvertAAFTypeIDDatakind
//
//			This function converts an AAF type UID into an OMF datakind. 
//			
// Returns: AAFRESULT_SUCCESS if datakind is converted succesfully
//
// ============================================================================
void Aaf2Omf::ConvertAAFTypeIDDatakind(aafUID_t typeID, OMF2::omfDDefObj_t* pDatakind)
{
	AAFCheck				rc;

	OMF2::omfUniqueName_t	datakindName;
	OMF2::omfBool			bFound;
	char					szAUID[64];

	if ( memcmp((char *)&typeID, (char *)&kAAFTypeID_Rational, sizeof(aafUID_t)) == 0 )
	{
		strcpy(datakindName, "omfi:data:Rational");
		bFound = OMF2::omfiDatakindLookup(OMFFileHdl, datakindName, pDatakind, (OMF2::omfErr_t *) &rc);
	}
	else if ( memcmp((char *)&typeID, (char *)&kAAFTypeID_Int32, sizeof(aafUID_t)) == 0 )
	{
		strcpy(datakindName, "omfi:data:Int32");
		bFound = OMF2::omfiDatakindLookup(OMFFileHdl, datakindName, pDatakind, (OMF2::omfErr_t *) &rc);
	}
	else if ( memcmp((char *)&typeID, (char *)&kAAFTypeID_Boolean, sizeof(aafUID_t)) == 0 )
	{
		strcpy(datakindName, "omfi:data:Boolean");
		bFound = OMF2::omfiDatakindLookup(OMFFileHdl, datakindName, pDatakind, (OMF2::omfErr_t *) &rc);
	}
	else
	{
		AUIDtoString(&typeID, szAUID);
		printf("%sInvalid Type Found in sequence AUID : %s\n", gpGlobals->indentLeader, szAUID);
		fprintf(stderr,"%sInvalid Type Found in sequence AUID : %s\n", gpGlobals->indentLeader, szAUID);
		rc = AAFRESULT_INVALID_DATADEF;
	}

	if (!bFound)
		rc = AAFRESULT_INVALID_DATADEF;
}

// ============================================================================
// TraverseSequence
//
//			This function reads all components the of an AAF Sequence,
//			creates/sets the equivalent OMF objects 
//			
// Returns: AAFRESULT_SUCCESS if MOB object is converted succesfully
//
// ============================================================================
void Aaf2Omf::TraverseSequence(IAAFSequence* pSequence,
								  OMF2::omfObject_t* pOMFSequence )
{
	AAFCheck				rc;
	OMFCheck				OMFError;
	OMF2::omfCpntObj_t		newComponent = NULL;

	IAAFComponent*			pComponent = NULL;
	IEnumAAFComponents*		pCompIter = NULL;
	aafUInt32				numComponents;
	aafUInt32				cpntCount;
	

	rc = pSequence->CountComponents(&numComponents);
	
	rc = pSequence->GetComponents(&pCompIter);
	for (cpntCount = 0; cpntCount < numComponents; cpntCount++)
	{
		rc = pCompIter->NextOne(&pComponent);
		ProcessComponent(pComponent, &newComponent);
		OMFError = OMF2::omfiSequenceAppendCpnt(OMFFileHdl, *pOMFSequence, newComponent);
		pComponent->Release();
		pComponent = NULL;
	}
	pCompIter->Release();
	pCompIter = NULL;
//	if (OMF2::OM_ERR_NONE != OMFError)
//		rc = AAFRESULT_INTERNAL_ERROR;

}
// ============================================================================
// ConvertSelector
//
//			This function converts an AAF Selector object and all the objects it
// contains or references.
//			
// Returns: AAFRESULT_SUCCESS if succesfully
//
// ============================================================================
void Aaf2Omf::ConvertSelector(IAAFSelector* pSelector,
								 OMF2::omfObject_t* pOMFSelector )
{
	AAFCheck				rc;
	OMFCheck				OMFError;
	OMF2::omfSegObj_t		OMFSelected = NULL;
	
	IAAFComponent*			pComponent = NULL;
	IAAFSegment*			pSegment = NULL;
	aafLength_t				length;
	aafInt32				numAlternates;
	
	IncIndentLevel();
	pSelector->QueryInterface(IID_IAAFComponent, (void **)&pComponent);
	pSelector->GetSelectedSegment(&pSegment);
	pSelector->GetNumAlternateSegments(&numAlternates);
	pComponent->GetLength(&length);
	
	if (gpGlobals->bVerboseMode)
		printf("%sProcessing Selector object of length = %ld\n", gpGlobals->indentLeader, length);
	
	pComponent->Release();
	pComponent = NULL;
	pSegment->QueryInterface(IID_IAAFComponent, (void **)&pComponent);
	ProcessComponent(pComponent, &OMFSelected );
	
	OMFError = OMF2::omfiSelectorSetSelected(OMFFileHdl, *pOMFSelector, OMFSelected);
	if (numAlternates > 0)
	{
		OMF2::omfSegObj_t	OMFAltSelected = NULL;
		
		IAAFComponent*		pAltComponent = NULL;
		IEnumAAFSegments*	pEnumAlternates = NULL;
		IAAFSegment*		pAltSegment = NULL;
		
		rc = pSelector->EnumAlternateSegments(&pEnumAlternates);
		for (int i = 0; i< numAlternates;i++)
		{
			pEnumAlternates->NextOne(&pAltSegment);
			pAltSegment->QueryInterface(IID_IAAFComponent, (void **)&pAltComponent);
			ProcessComponent(pAltComponent, &OMFAltSelected);
			OMFError = OMF2::omfiSelectorAddAlt(OMFFileHdl, *pOMFSelector, OMFAltSelected);
			pAltComponent->Release();
			pAltSegment->Release();
		}
		
		pEnumAlternates->Release();
	}
	
	DecIndentLevel();
	if (pSegment)
		pSegment->Release();
	if (pComponent)
		pComponent->Release();
	
//	if (OMF2::OM_ERR_NONE != OMFError)
//		rc = AAFRESULT_INTERNAL_ERROR;
}

// ============================================================================
// ConvertSelector
//
//			This function converts an AAF Selector object and all the objects it
// contains or references.
//			
// Returns: AAFRESULT_SUCCESS if succesfully
//
// ============================================================================
void Aaf2Omf::ConvertNestedScope(IAAFNestedScope* pNest,
								 OMF2::omfObject_t* pOMFNest )
{
	AAFCheck				rc;
	OMFCheck				OMFError;
	OMF2::omfSegObj_t		OMFSegment = NULL;

	IAAFComponent*			pComponent = NULL;
	IAAFSegment*			pSegment = NULL;
	IEnumAAFSegments*		pEnumSegments;
	aafLength_t				length;

	IncIndentLevel();

	pNest->QueryInterface(IID_IAAFComponent, (void **)&pComponent);
	pComponent->GetLength(&length);

	if (gpGlobals->bVerboseMode)
		printf("%sProcessing Nest object of length = %ld\n", gpGlobals->indentLeader, length);

	rc = pNest->GetSegments (&pEnumSegments);
	while(pEnumSegments->NextOne (&pSegment) == AAFRESULT_SUCCESS)
	{
		pSegment->QueryInterface(IID_IAAFComponent, (void **)&pComponent);
		ProcessComponent(pComponent, &OMFSegment);
		OMFError = OMF2::omfiNestedScopeAppendSlot(OMFFileHdl, *pOMFNest, OMFSegment);
		pSegment->Release();
		pSegment = NULL;
		pComponent->Release();
		pComponent = NULL;
	}
	DecIndentLevel();
	if (pSegment)
		pSegment->Release();
	if (pComponent)
		pComponent->Release();

//	if (OMF2::OM_ERR_NONE != OMFError)
//		rc = AAFRESULT_INTERNAL_ERROR;
}

// ============================================================================
// ConvertLocator
//
//			This function converts an AAF Filed descriptor to OMF
//			
// Returns: AAFRESULT_SUCCESS if succesfully
//
// ============================================================================
void Aaf2Omf::ConvertLocator(IAAFEssenceDescriptor* pEssenceDesc,
								OMF2::omfMobObj_t*	pOMFSourceMob )
{
	AAFCheck				rc;
	OMFCheck				OMFError;
	// OMF2::omfClassID_t		locType;

	char*					pszLocatorPath = NULL;
	char*					pszName = NULL;

	IAAFLocator*			pLocator = NULL;
	IAAFTextLocator*		pTextLocator = NULL;
	IEnumAAFLocators*		pLocatorIter = NULL;		
	aafUInt32				numLocators = 0;
    aafWChar*				pwLocatorPath = NULL;
	aafWChar*				pwName = NULL;

	aafUInt32				pathSize = 0;
	aafUInt32				textSize = 0;

	rc = pEssenceDesc->CountLocators(&numLocators);
	if(numLocators > 0)
	{
		rc = pEssenceDesc->GetLocators(&pLocatorIter);
		while (SUCCEEDED(pLocatorIter->NextOne(&pLocator)))
		{
			if (SUCCEEDED(pLocator->QueryInterface(IID_IAAFTextLocator, (void **)&pTextLocator)))
			{
				rc = pTextLocator->GetNameBufLen(&textSize);
				pwName = new wchar_t[textSize/sizeof(wchar_t)];
				rc = pTextLocator->GetName(pwName, textSize);

				pszName = new char[textSize/sizeof(wchar_t)];
				wcstombs(pszName, pwName, textSize/sizeof(wchar_t));
				OMFError = OMF2::omfmMobAddTextLocator(OMFFileHdl, *pOMFSourceMob, pszName);
				if (pwName)
					delete [] pwName;
				if (pszName)
					delete [] pszName;
			}
			else
			{
				pLocator->GetPathBufLen(&pathSize);
				pwLocatorPath = new wchar_t[pathSize/sizeof(wchar_t)];
				pLocator->GetPath(pwLocatorPath, pathSize);
				pszLocatorPath = new char[pathSize/sizeof(wchar_t)];
				wcstombs(pszLocatorPath, pwLocatorPath, pathSize/sizeof(wchar_t));
				OMFError = OMF2::omfmMobAddNetworkLocator(OMFFileHdl, *pOMFSourceMob, OMF2::kOmfiMedia, pszLocatorPath);
				if (pwLocatorPath)
				{
					delete [] pwLocatorPath;
					pwLocatorPath = NULL;
				}
				if (pszLocatorPath)
				{
					delete [] pszLocatorPath;
					pszLocatorPath = NULL;
				}
			}
		}
	}
	if (pTextLocator)
		pTextLocator->Release();
	if (pLocator)
		pLocator->Release();
	if (pLocatorIter)
		pLocatorIter->Release();
	if (pwLocatorPath)
		delete [] pwLocatorPath;
	if (pszLocatorPath)
		delete [] pszLocatorPath;

//	if (OMFError != OMF2::OM_ERR_NONE)
//		rc = AAFRESULT_INTERNAL_ERROR;
}
// ============================================================================
// ConvertEssenceDataObject
//
//			This function is called by the AAFFILERead module for each 
//			media data object found in the header
//			
// Returns: AAFRESULT_SUCCESS if Header object is converted succesfully
//
// ============================================================================
void Aaf2Omf::ConvertEssenceDataObject( IAAFEssenceData* pEssenceData)
{
	AAFCheck				rc;
	OMFCheck				OMFError;
	
	OMF2::omfObject_t		OMFSourceMob = NULL;
	OMF2::omfObject_t		OMFHeader = NULL;
	OMF2::omfObject_t		mediaData = NULL;
	OMF2::omfUID_t			mediaID;
	OMF2::omfProperty_t		idProperty;
	OMF2::omfDDefObj_t		datakind;
	char					id[5];
	
	IAAFEssenceData*			pTIFFData = NULL;
	IAAFEssenceData*			pAIFCData = NULL;
	IAAFEssenceData*			pWAVEData = NULL;
	IAAFEssenceData*			pJPEGData = NULL;
	IAAFTIFFDescriptor*			pTIFFDesc = NULL;
	IAAFAIFCDescriptor*			pAIFCDesc = NULL;
	IAAFWAVEDescriptor*			pWAVEDesc = NULL;
	IAAFCDCIDescriptor*			pJPEGDesc = NULL;
	IAAFEssenceDescriptor		*pEssenceDesc = NULL;
	IAAFMob*				pMob = NULL;
	IAAFSourceMob*			pSourceMob = NULL;
	IAAFObject*				pAAFObject = NULL;
	aafMobID_t				mobID;
	aafBool					bConvertMedia = kAAFFalse;
	
	// get the file mob id
	rc = pEssenceData->GetFileMobID(&mobID);

	// make sure it is a Source mob
	rc = pEssenceData->GetFileMob(&pSourceMob);
	
	if (FAILED(pSourceMob->GetEssenceDescriptor(&pEssenceDesc)))
	{
		pSourceMob->Release();
		return;
	}
	
	ConvertMobIDtoUID(&mobID, &mediaID);
	if (OMF2::omfsFindSourceMobByID(OMFFileHdl, mediaID, &OMFSourceMob) != OMF2::OM_ERR_NONE)
	{
		rc = AAFRESULT_INVALID_OBJ;
		pSourceMob->Release();
		return;
	}
	OMFError = OMF2::omfsGetHeadObject( OMFFileHdl, &OMFHeader );
	
	// !!! Tomas, there is only one kind of essence data now, so this code will
	// need to find the EssenceDescriptor of the associated file mob (lookup he
	// dataID in the MOB index on the dictionary) and do a QI on the result
	// The code is something like:
	//
	if (SUCCEEDED(pEssenceDesc->QueryInterface(IID_IAAFTIFFDescriptor, (void **)&pTIFFDesc)))
	{
		//Convert TIFF Essence data
		idProperty = OMF2::OMTIFFData;
		OMF2::omfiDatakindLookup(OMFFileHdl, "omfi:data:Picture", &datakind, (OMF2::omfErr_t *)&rc);
		strcpy(id, "TIFF");
		OMFError = OMF2::omfsObjectNew(OMFFileHdl, id, &mediaData);

		OMFError = OMF2::omfsWriteUID(OMFFileHdl, mediaData, OMF2::OMMDATMobID, mediaID);
//		if (OMFError != OMF2::OM_ERR_NONE)
//		{
//			char* pErrString = OMF2::omfsGetErrorString(OMFError);
//			goto cleanup;
//		}
		OMFError = OMF2::omfsAppendObjRefArray(OMFFileHdl, OMFHeader, OMF2::OMHEADMediaData, mediaData);
//		if (OMFError != OMF2::OM_ERR_NONE)
//		{
//			char* pErrString = OMF2::omfsGetErrorString(OMFError);
//			goto cleanup;
//		}
//		else
			goto CopyMedia;
	}
	
	if (SUCCEEDED(pEssenceDesc->QueryInterface(IID_IAAFAIFCDescriptor, (void **)&pAIFCDesc)))
	{
		//Convert AIFC Essence data
		idProperty = OMF2::OMAIFCData;
		OMF2::omfiDatakindLookup(OMFFileHdl, "omfi:data:Sound", &datakind, (OMF2::omfErr_t *)&rc);
		strcpy(id, "AIFC");
		OMFError = OMF2::omfsObjectNew(OMFFileHdl, id, &mediaData);
//		if (OMFError != OMF2::OM_ERR_NONE)
//			goto cleanup;
		OMFError = OMF2::omfsWriteUID(OMFFileHdl, mediaData, OMF2::OMMDATMobID, mediaID);
//		if (OMFError != OMF2::OM_ERR_NONE)
//		{
//			char* pErrString = OMF2::omfsGetErrorString(OMFError);
//			goto cleanup;
//		}
		OMFError = OMF2::omfsAppendObjRefArray(OMFFileHdl, OMFHeader, OMF2::OMHEADMediaData, mediaData);
//		if (OMFError != OMF2::OM_ERR_NONE)
//			goto cleanup;
//		else
			goto CopyMedia;
	}
	
	if (SUCCEEDED(pEssenceData->QueryInterface(IID_IAAFWAVEDescriptor, (void **)&pWAVEDesc)))
	{
		//Convert WAVE Essence data
		idProperty = OMF2::OMWAVEData;
		OMF2::omfiDatakindLookup(OMFFileHdl, "omfi:data:Sound", &datakind, (OMF2::omfErr_t *)&rc);
		strcpy(id, "WAVE");
		OMFError = OMF2::omfsObjectNew(OMFFileHdl, id, &mediaData);
//		if (OMFError != OMF2::OM_ERR_NONE)
//			goto cleanup;
		OMFError = OMF2::omfsWriteUID(OMFFileHdl, mediaData, OMF2::OMMDATMobID, mediaID);
//		if (OMFError != OMF2::OM_ERR_NONE)
//		{
//			char* pErrString = OMF2::omfsGetErrorString(OMFError);
//			goto cleanup;
//		}
		OMFError = OMF2::omfsAppendObjRefArray(OMFFileHdl, OMFHeader, OMF2::OMHEADMediaData, mediaData);
//		if (OMFError != OMF2::OM_ERR_NONE)
//			goto cleanup;
//		else
			goto CopyMedia;
	}
	
	//!!!Need to check "compression" flag to determine if really JPEG
	if (SUCCEEDED(pEssenceData->QueryInterface(IID_IAAFCDCIDescriptor, (void **)&pJPEGDesc)))
	{
		//Convert JPEG Essence data
		idProperty = OMF2::OMIDATImageData;
		OMF2::omfiDatakindLookup(OMFFileHdl, "omfi:data:Picture", &datakind, (OMF2::omfErr_t *)&rc);
		strcpy(id, "JPEG");
		OMFError = OMF2::omfsObjectNew(OMFFileHdl, id, &mediaData);
//		if (OMFError != OMF2::OM_ERR_NONE)
//			goto cleanup;
		OMFError = OMF2::omfsWriteUID(OMFFileHdl, mediaData, OMF2::OMMDATMobID, mediaID);
//		if (OMFError != OMF2::OM_ERR_NONE)
//		{
//			char* pErrString = OMF2::omfsGetErrorString(OMFError);
//			goto cleanup;
//		}
		OMFError = OMF2::omfsAppendObjRefArray(OMFFileHdl, OMFHeader, OMF2::OMHEADMediaData, mediaData);
//		if (OMFError != OMF2::OM_ERR_NONE)
//			goto cleanup;
//		else
			goto CopyMedia;
	}
	
	// Media type not supported or invalid
	rc = pEssenceData->QueryInterface(IID_IAAFObject, (void **)&pAAFObject);
	
	{
		aafUID_t	ObjClass;
		char		szTempUID[64];
		
		// pAAFObject->GetObjectClass(&ObjClass);
		IAAFClassDef * classDef = 0;
		pAAFObject->GetDefinition(&classDef);
		IAAFDefObject * defObj = 0;
		pEssenceDesc->QueryInterface(IID_IAAFDefObject, (void **)&defObj);
		defObj->GetAUID (&ObjClass);
		if (defObj)
		{
			defObj->Release ();
			defObj = 0;
		}
		if (classDef)
		{
			classDef->Release ();
			classDef = 0;
		}
		
		AUIDtoString(&ObjClass ,szTempUID);
		if (gpGlobals->bVerboseMode)
			printf("%sInvalid essence data type found, datadef : %s\n", gpGlobals->indentLeader, szTempUID);
		fprintf(stderr,"%sInvalid essence data type found, datadef : %s\n", gpGlobals->indentLeader, szTempUID);
	}
	goto cleanup;
	
CopyMedia:
	if (mediaData)
	{
		void*			pBuffer = NULL;
		aafPosition_t	AAFOffset;
		
		aafLength_t		numBytes;
		aafUInt32		nBlockSize;
		aafUInt32		numBytesRead;
		aafBool			bMore = kAAFFalse;
		
		rc = pEssenceData->GetSize(&numBytes);
		if (numBytes > 0)
		{
			if (numBytes > (2 * 1048576))
			{
				nBlockSize = 2 * 1048576;	// only allocate 2 Meg
				bMore = kAAFTrue;			// you going to need more than one read/write
			}
			else
			{
				// Some 'magic' required to get types to match; make sure
				// narrowing of type didn't throw away data
				nBlockSize = (aafUInt32) numBytes;
				if ((aafLength_t) nBlockSize != numBytes)
				{
					rc = AAFRESULT_INTERNAL_ERROR;
					goto cleanup;
				}
			}
			pBuffer = new char[nBlockSize];
			AAFOffset = 0;
			do 
			{
				rc = pEssenceData->SetPosition( AAFOffset );
				rc = pEssenceData->Read( nBlockSize, (unsigned char *)pBuffer, &numBytesRead);
				
				// write the media
				OMFError = OMF2::omfsWriteDataValue(OMFFileHdl, 
					mediaData,
					idProperty,
					datakind, 
					(OMF2::omfDataValue_t)pBuffer,
					(OMF2::omfPosition_t)AAFOffset,
					numBytesRead);
				// calculate next offset
				AAFOffset += numBytesRead;
			}while (numBytes > AAFOffset );
			// Free the allocated buffer 
			delete [] pBuffer;
		}
	}
cleanup:
	if (pSourceMob)
		pSourceMob->Release();
	if (pEssenceDesc)
		pEssenceDesc->Release();
	
	if (pTIFFData)
		pTIFFData->Release();
	
	if (pAIFCData)
		pAIFCData->Release();
	
	if (pWAVEData)
		pWAVEData->Release();
	
	if (pJPEGData)
		pJPEGData->Release();
	
//	if (OMFError != OMF2::OM_ERR_NONE)
//		rc = AAFRESULT_INTERNAL_ERROR;
}
// ============================================================================
// ConvertEffects
//
//			This function reads an OMF effect object, converts its properties
//			to AAF, updates the AAF Effect object and, if necessary creates the 
//			effect definition by Calling ConvertOMFEffectDefinition. 
//			
// Returns: AAFRESULT_SUCCESS if object is converted.
//
// ============================================================================
void Aaf2Omf::ConvertEffects(IAAFOperationGroup* pEffect,
								OMF2::omfObject_t	 nest,
								OMF2::omfEffObj_t*	pOMFEffect)
{
	AAFCheck				rc;
	OMFCheck				omStat;
	OMF2::omfDDefObj_t		effectDatakind;
	// OMF2::omfLength_t		effectLength;
	OMF2::omfEDefObj_t		effectDef;
	// OMF2::omfDDefObj_t		OMFdatakind;
	OMF2::omfUniqueName_t	effectID;
	OMF2::omfUniqueName_t	MCEffectID;
	OMF2::omfErr_t			testErr;
	OMFCheck				OMFError;
	OMF2::omfBool			bDefExists;
	OMF2::omfObject_t		pOMFSegment, pOMFEffectSlot, pScopeReference;
	
	IAAFOperationDef*		pEffectDef = NULL;
	IAAFParameterDef*		pParameterDef = NULL;
	IAAFParameter*			pParameter = NULL;
	IAAFDefObject*			pDefObject = NULL;
	IAAFSegment*			pSegment = NULL;
	IAAFSourceReference*		pSourceRef= NULL;
	IAAFFiller*				pFiller = NULL;
	IAAFComponent*			pComponent = NULL;
	IAAFSourceClip*			pSourceClip = NULL;
	IAAFDataDef*			pDataDef = 0;
	IAAFDefObject* 			pDefObj = 0;
	IAAFConstantValue*		pConstantValue = NULL;
	
	aafUID_t				effectAUID;
	aafUID_t				effectDefAUID;
	aafLength_t				length;
	aafUInt32				byPass, bypassOverride, *byPassPtr;
	aafUInt32				textSize;
	aafBool					isATimeWarp;
	aafInt32				n, numSources;
	aafInt32				numParameters;
	aafWChar*				pwDesc = NULL;
	aafWChar*				pwName = NULL;
	
	char*					pszName = NULL;
	char*					pszDesc = NULL;
	char*					stdName = NULL;
	
	IncIndentLevel();
	
	rc = pEffect->QueryInterface(IID_IAAFComponent, (void **)&pComponent);
	
	pComponent->GetLength(&length);
	rc = pComponent->GetDataDef(&pDataDef);
	rc = pDataDef->QueryInterface(IID_IAAFDefObject, (void **)&pDefObj);
	pDataDef->Release ();
	pDataDef = 0;
	rc = pDefObj->GetAUID(&effectAUID);
	pDefObj->Release ();
	pDefObj = 0;
	ConvertAAFDatadef(effectAUID, &effectDatakind);
	pEffect->IsATimeWarp(&isATimeWarp);
	pEffect->CountSourceSegments(&numSources);
	pEffect->CountParameters(&numParameters);
	rc = pEffect->GetOperationDefinition(&pEffectDef);
	// pEffectDef->GetDataDefinitionID(&datadefAUID);
	rc = pEffectDef->QueryInterface(IID_IAAFDefObject, (void **) &pDefObject);
	pDefObject->GetAUID(&effectDefAUID);
	pDefObject->GetNameBufLen(&textSize);
	pwName = new wchar_t[textSize/sizeof(wchar_t)];
	pDefObject->GetName(pwName, textSize);
	pszName = new char[textSize/sizeof(wchar_t)];
	wcstombs(pszName, pwName, textSize/sizeof(wchar_t));
	
	pDefObject->GetDescriptionBufLen(&textSize);
	pwDesc = new wchar_t[textSize/sizeof(wchar_t)];
	pDefObject->GetDescription(pwDesc, textSize);
	pszDesc = new char[textSize/sizeof(wchar_t)];
	wcstombs(pszDesc, pwDesc, textSize/sizeof(wchar_t));
	
	if(pEffectDef->GetBypass(&byPass) == AAFRESULT_SUCCESS)
		byPassPtr = &byPass;
	else
		byPassPtr = NULL;
	
	pEffectTranslate->GetEffectIDs(pEffect, effectID, MCEffectID);
	
	// At some point we should try to reconstruct the AVX private effect ID
	// from the AAF File
#if AVID_SPECIAL
	if(strcmp(MCEffectID, AVX_PLACEHOLDER_EFFECT) == 0)
	{
		strcpy(MCEffectID, "UnknownAVX Effect");
		strcpy(effectID, "omfi:effect:Unknown");
		
		if(pEffect->LookupParameter(kAAFParamID_AvidEffectID, &pParameter) == AAFRESULT_SUCCESS)
			rc = pParameter->QueryInterface(IID_IAAFConstantValue, (void **)&pConstantValue);

		aafUInt32			srcValueLen, lenRead;
		rc = pConstantValue->GetValueBufLen(&srcValueLen);
		//				Assert(srcValueLen <= sizeof(MCEffectID));
		rc = pConstantValue->GetValue(srcValueLen, (unsigned char*)MCEffectID, &lenRead);
		pConstantValue->Release();
		pConstantValue = NULL;
		pParameter->Release();
		pParameter = NULL;
	}
#endif
	
	bDefExists = OMF2::omfiEffectDefLookup(OMFFileHdl, effectID, &effectDef, &testErr);
	if (testErr == OMF2::OM_ERR_NONE && !bDefExists)
	{
		rc = OMF2::omfiEffectDefNew(OMFFileHdl,
			effectID,
			pszName,
			pszDesc,
			(OMF2::omfArgIDType_t *)byPassPtr,
			(OMF2::omfBool)isATimeWarp,
			&effectDef);
	}
	
	omStat = OMF2::omfiEffectNew(OMFFileHdl,
		effectDatakind,
		(OMF2::omfLength_t)length,
		effectDef,
		pOMFEffect);
	
	
	if(MCEffectID[0] != '\0')
	{
		omStat = OMF2::omfsWriteString(OMFFileHdl, (*pOMFEffect), gpGlobals->pvtEffectIDProp,
			MCEffectID);
	}
	
	if(SUCCEEDED(pEffect->GetRender(&pSourceRef)))
	{
		rc = pSourceRef->QueryInterface(IID_IAAFSourceClip, (void **) &pSourceClip);
		rc = pSourceRef->QueryInterface(IID_IAAFComponent, (void **) &pComponent);
		ProcessComponent(pComponent,&pOMFSegment);
		omStat = OMF2::omfiEffectSetFinalRender(OMFFileHdl,(*pOMFEffect), pOMFSegment);
		pSourceClip->Release();
		pSourceClip = NULL;
		pComponent->Release();
		pComponent = NULL;
	}
	
	if(SUCCEEDED(pEffectDef->GetBypass(&bypassOverride)))
	{
		omStat = OMF2::omfiEffectSetBypassOverride(OMFFileHdl,(*pOMFEffect),
			bypassOverride);	//!!! 1-1 mapping?
	}
	
	rc = pEffect->CountSourceSegments(&numSources);
	for(n = 0; n < numSources; n++)
	{
		rc = pEffect->GetInputSegmentAt(n, &pSegment);
		rc = pSegment->QueryInterface(IID_IAAFComponent,
												(void **) &pComponent);
		
		if(pComponent != NULL)
		{
			ProcessComponent(pComponent,&pOMFSegment);
			if(nest != NULL)
			{
				omStat = OMF2::omfiNestedScopeAppendSlot(OMFFileHdl,nest, pOMFSegment);
				omStat = OMF2::omfiScopeRefNew(OMFFileHdl,
					effectDatakind,
					(OMF2::omfLength_t)length,
					0,
					1,		// This may not be a constant
					&pScopeReference);
				omStat = OMF2::omfiEffectAddNewSlot(OMFFileHdl,(*pOMFEffect),
					-1*(n+1), pScopeReference, &pOMFEffectSlot);
			}
			else
			{
				omStat = OMF2::omfiEffectAddNewSlot(OMFFileHdl,(*pOMFEffect),
					-1*(n+1), pOMFSegment, &pOMFEffectSlot);
			}
			pComponent->Release();
			pComponent = NULL;
		}
		//!!! Else error
		
		pSegment->Release();
	}
	
	// If the effect ID is known, map to a apecific OMF effect ID
	if(pEffect->LookupParameter(kAAFParameterDefLevel, &pParameter) == AAFRESULT_SUCCESS)
	{
		aafInt32	levelSlot;
#if AVID_SPECIAL
		if(pEffectTranslate->isPrivateEffect(effectDefAUID))
			levelSlot = OMF2_EFFE_ALLOTHERS_LEVEL_SLOT;
		else
#endif
			levelSlot = -3;
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect), levelSlot,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParameterDefSMPTEWipeNumber, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  1,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParameterDefSMPTEReverse, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  2,
			(OMF2::omfLength_t)length);
	}
#if AVID_SPECIAL
	if(pEffect->LookupParameter(kAAFParamID_AvidUserParam, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  0,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParamID_AvidBounds, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  0,
			(OMF2::omfLength_t)length);
	}
#endif
#if 0
	if(pEffect->LookupParameter(kAAFParameterDefAmplitude, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParameterDefPan, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	//		kAAFParameterDefSMPTEReverse
	//		kAAFParameterDefSMPTESoft
	//		kAAFParameterDefSMPTEBorder
	//		kAAFParameterDefSMPTEPosition
	//		kAAFParameterDefSMPTEModulator
	//		kAAFParameterDefSMPTEShadow
	//		kAAFParameterDefSMPTETumble
	//		kAAFParameterDefSMPTESpotlight
	//		kAAFParameterDefSMPTEReplicationH
	//		kAAFParameterDefSMPTEReplicationV
	//		kAAFParameterDefSMPTECheckerboard
	if(pEffect->LookupParameter(kAAFParameterDefPhaseOffset, &pParameter) == AAFRESULT_SUCCESS)
	{
		convertParameter(pParameter, effectDefAUID, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParameterDefSpeedRatio, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParamID_AvidBorderWidth, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParamID_AvidBorderSoft, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParamID_AvidXPos, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParamID_AvidYPos, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParamID_AvidCrop, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, effectDefAUID, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParamID_AvidScale, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParamID_AvidSpillSupress, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
	if(pEffect->LookupParameter(kAAFParamID_AvidColor, &pParameter) == AAFRESULT_SUCCESS)
	{
		ConvertParameter(pParameter, (*pOMFEffect),  xxx,
			(OMF2::omfLength_t)length);
	}
#endif
	
	DecIndentLevel();
	if (pwName)
	{
		delete [] pwName;
		pwName = 0;
	}
	
	if (pwDesc)
	{
		delete [] pwDesc;
		pwDesc = 0;
	}
	
	if (pszName)
	{
		delete [] pszName;
		pszName = 0;
	}
	
	if (pszDesc)
	{
		delete [] pszDesc;
		pszDesc = 0;
	}
	
	if (pEffectDef)
	{
		pEffectDef->Release();
		pEffectDef = 0;
	}
	
	if (pParameterDef)
	{
		pParameterDef->Release();
		pParameterDef = 0;
	}
	
	if (pParameter)
	{
		pParameter->Release();
		pParameter = 0;
	}
	
	if (pDefObject)
	{
		pDefObject->Release();
		pDefObject = 0;
	}
	
	//	if (pSegment)
	//	{
	//	  pSegment->Release();
	//	  pSegment = 0;
	//	}
	
	if (pSourceRef)
	{
		pSourceRef->Release();
		pSourceRef = 0;
	}
	
	if (pFiller)
	{
		pFiller->Release();
		pFiller = 0;
	}
	
	if (pComponent)
	{
		pComponent->Release();
		pComponent = 0;
	}
	
	if (pSourceClip)
	{
		pSourceClip->Release();
		pSourceClip = 0;
	}
	
	if (pDataDef)
	{
		pDataDef->Release ();
		pDataDef = 0;
	}
	
	if (pDefObj)
	{
		pDefObj->Release ();
		pDefObj = 0;
	}
}

void Aaf2Omf::ConvertParameter(	IAAFParameter*		pParm,
									aafUID_t			&effectDefID,
								  OMF2::omfSegObj_t		pOMFEffect,
									OMF2::omfInt32		slotNum,
									OMF2::omfLength_t	effectLen)
{
	IAAFConstantValue	*pConstantValue = NULL;
	IAAFVaryingValue	*pVaryingValue = NULL;
	IAAFTypeDef			*pTypeDef = NULL;
	IAAFDefObject		*pDef = NULL;
	IAAFInterpolationDef	*pInterpDef = NULL;
	IAAFParameterDef	*pParmDef = NULL;
	IAAFControlPoint	*pPoint = NULL;
	IEnumAAFControlPoints *pointEnum;
	aafUID_t			typeDefID, interpDefID, paramDefID;
	AAFCheck			rc;
	OMFCheck			omStat;
	aafUInt32			srcValueLen, destValueLen, lenRead;
	aafDataBuffer_t		srcValue = NULL, destValue = NULL;
	OMF2::omfInterpKind_t interpKind;
	OMF2::omfObject_t	vval, kfVVAL = NULL;
	aafRational_t		aafTime;
	OMF2::omfRational_t	omfTime;
	aafEditHint_t		aafEditHint;
	OMF2::omfEditHint_t	omfEditHint;
	OMF2::omfSegObj_t	omfSeg;
	OMF2::omfObject_t	pOMFEffectSlot;
	OMF2::omfObject_t	pOMFDatakind;
	bool				didNew;

    rc = pParm->GetTypeDefinition(&pTypeDef);
	rc = pTypeDef->QueryInterface(IID_IAAFDefObject, (void **)&pDef);
    rc = pDef->GetAUID(&typeDefID);
	pDef->Release();
	pDef = NULL;
	//
    rc = pParm->GetParameterDefinition(&pParmDef);
	rc = pParmDef->QueryInterface(IID_IAAFDefObject, (void **)&pDef);
    rc = pDef->GetAUID(&paramDefID);
	pParmDef->Release();
	pParmDef = NULL;
	pDef->Release();
	pDef = NULL;

	//!!! This one parameter ID has no OMF equivilent.  make a routine which
	// knows the valid ones to let through.
#if AVID_SPECIAL
	if(memcmp(&paramDefID, &kAAFParamID_AvidSelected, sizeof(paramDefID)) != 0 &&
	   memcmp(&paramDefID, &kAAFParamID_AvidUserParam, sizeof(paramDefID)) != 0)
#endif
	{
		ConvertAAFTypeIDDatakind(typeDefID, &pOMFDatakind);
		
		if (SUCCEEDED(pParm->QueryInterface(IID_IAAFConstantValue, (void **)&pConstantValue)))
		{
			rc = pConstantValue->GetValueBufLen(&srcValueLen);
			srcValue = new unsigned char[srcValueLen];
			rc = pConstantValue->GetValue(srcValueLen, srcValue, &lenRead);
			ConvertValueBuf(typeDefID, srcValue, lenRead, &destValue, &destValueLen, &didNew);
			omStat = OMF2::omfiConstValueNew(OMFFileHdl, pOMFDatakind, effectLen,
				destValueLen, destValue, &omfSeg);
			if(didNew)
				delete [] destValue;
			delete [] srcValue;
			destValue = NULL;
			srcValue = NULL;
			omStat = OMF2::omfiEffectAddNewSlot(OMFFileHdl,pOMFEffect,
				slotNum, omfSeg, &pOMFEffectSlot);
		}
		else
		{
			rc = pParm->QueryInterface(IID_IAAFVaryingValue, (void **)&pVaryingValue);

			rc = pVaryingValue->GetInterpolationDefinition(&pInterpDef);
			rc = pInterpDef->QueryInterface(IID_IAAFDefObject, (void **)&pDef);
			pInterpDef->Release();
			pInterpDef = NULL;
			rc = pDef->GetAUID(&interpDefID);
			pDef->Release();
			pDef = NULL;
			if(memcmp(&interpDefID, &LinearInterpolator, sizeof(interpDefID)) == 0)
			{
				interpKind = OMF2::kLinearInterp;
			}
			else if(memcmp(&interpDefID, &ConstantInterpolator, sizeof(interpDefID)) == 0)
			{
				interpKind = OMF2::kConstInterp;
			}
			// else error!!!
				
			omStat = OMF2::omfiVaryValueNew(OMFFileHdl, pOMFDatakind, effectLen,
				interpKind, &vval);
			omfSeg = vval;
				
			rc = pVaryingValue->GetControlPoints(&pointEnum);
			while(pointEnum->NextOne(&pPoint) == AAFRESULT_SUCCESS)
			{
				HRESULT	testRC;
				rc = pPoint->GetTime(&aafTime);
				omfTime.numerator = aafTime.numerator;
				omfTime.denominator = aafTime.denominator;
				testRC = pPoint->GetEditHint(&aafEditHint);
				if(testRC == AAFRESULT_PROP_NOT_PRESENT)
					aafEditHint = kAAFNoEditHint;
				else
					rc = testRC;
				switch(aafEditHint)
				{
				case kAAFNoEditHint:
					omfEditHint = OMF2::kNoEditHint;
					break;
				case kAAFProportional:
					omfEditHint = OMF2::kProportional;
					break;
				case kAAFRelativeLeft:
					omfEditHint = OMF2::kRelativeLeft;
					break;
				case kAAFRelativeRight:
					omfEditHint = OMF2::kRelativeRight;
					break;
				case kAAFRelativeFixed:
					omfEditHint = OMF2::kRelativeFixed;
					break;
					//!!!Handle default case
				}
				
				rc = pPoint->GetValueBufLen(&srcValueLen);
				srcValue = new unsigned char[srcValueLen];
				rc = pPoint->GetValue(srcValueLen, srcValue, &lenRead);
				ConvertValueBuf(typeDefID, srcValue, lenRead, &destValue, &destValueLen, &didNew);
				omStat = OMF2::omfiVaryValueAddPoint(OMFFileHdl, vval, omfTime, omfEditHint, pOMFDatakind,
					destValueLen, destValue);
				if(didNew)
					delete [] destValue;
				delete [] srcValue;
				destValue = NULL;
				srcValue = NULL;
			}
			omStat = OMF2::omfiEffectAddNewSlot(OMFFileHdl,pOMFEffect,
				slotNum, omfSeg, &pOMFEffectSlot);
		}
	}
	if(pConstantValue != NULL)
	{
		pConstantValue->Release();
		pConstantValue = NULL;
	}
	if(pInterpDef != NULL)
	{
		pInterpDef->Release();
		pInterpDef = NULL;
	}
	if(pPoint != NULL)
	{
		pPoint->Release();
		pPoint = NULL;
	}
	if((srcValue != NULL) && (srcValue != destValue))
	{
		delete [] srcValue;
		srcValue = NULL;
	}
	if(destValue != NULL)
	{
		delete [] destValue;
		destValue = NULL;
	}
}


OMF2::omfObject_t Aaf2Omf::LocateSlot(OMF2::omfEffObj_t pOMFEffect, aafInt32 kfSlotNum)
{
	OMF2::omfNumSlots_t	numSlots, slotID;
	OMF2::omfIterHdl_t	slotIter;
	OMF2::omfESlotObj_t	effectSlot;
	OMF2::omfObject_t	segment, result = NULL;
	OMFCheck	OMFError;

	OMFError = OMF2::omfiEffectGetNumSlots(OMFFileHdl, pOMFEffect, &numSlots);
	OMFError = OMF2::omfiIteratorAlloc(OMFFileHdl, &slotIter);
	while(OMF2::omfiEffectGetNextSlot(slotIter, pOMFEffect, NULL, &effectSlot) == OMF2::OM_ERR_NONE)
	{
		OMFError = OMF2::omfiEffectSlotGetInfo(OMFFileHdl, effectSlot, &slotID, &segment);
		if(slotID == kfSlotNum)
		{
			result = segment;
		}
	}
	OMFError = OMF2::omfiIteratorDispose(OMFFileHdl, slotIter);

	return(result);
}

void Aaf2Omf::ConvertValueBuf(aafUID_t &typeDefID,
								aafDataBuffer_t srcValue, aafUInt32 srcValueLen,
								 aafDataBuffer_t *destValue, aafUInt32 *destValueLen,
								 bool *didAllocateNew)
{
	*didAllocateNew = false;
	if(memcmp(&typeDefID, &kAAFTypeID_Rational, sizeof(typeDefID)) == 0)
	{
		*destValue = srcValue;
		*destValueLen = srcValueLen;
	}
	else if(memcmp(&typeDefID, &kAAFTypeID_Int32, sizeof(typeDefID)) == 0)
	{
		*destValue = srcValue;
		*destValueLen = srcValueLen;
	}
	else if(memcmp(&typeDefID, &kAAFTypeID_Boolean, sizeof(typeDefID)) == 0)
	{
		*destValue = srcValue;
		*destValueLen = srcValueLen;
	}
	else // Error!!!
	{
		*destValue = srcValue;
		*destValueLen = srcValueLen;
	}
}
// OTher idea: Upon hitting ANY of the Avid private params (or level) find a VVAL
// and assume that all VVALs containing AvidPrivate have identical times
void Aaf2Omf::ConvertObjectProps(IAAFObject* pObj, OMF2::omfObject_t	pOMFObject)
{
}
