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
// The Original Code of this file is Copyright 1998-2009, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
// The Initial Developer of the Original Code of this file and the
// licensor of the Advanced Media Workflow Association is
// Avid Technology.
// All rights reserved.
//
// Portions created by British Broadcasting Corporation are
// Copyright 2004, British Broadcasting Corporation.  All rights reserved.
//
//=---------------------------------------------------------------------=


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include the AAF interface declarations.
#include "AAF.h"
#include "AAFTypes.h"
#include "AAFResult.h"
#include "AAFFileKinds.h"
#include "AAFSmartPointer.h"
#include "AAFFileMode.h"
#include "AAFPropertyDefs.h"
#include "AAFTypeDefUIDs.h"
#include "AAFDataDefs.h"
#include "AAFCodecDefs.h"
#include "AAFStoredObjectIDs.h"


IAAFHeader	*gHeader = NULL;

static HRESULT moduleErrorTmp = S_OK;/* note usage in macro */
#define check(a)  \
{  moduleErrorTmp = a; \
  if (!SUCCEEDED(moduleErrorTmp)) \
     FatalErrorCode(moduleErrorTmp, __LINE__, __FILE__);\
}

#define assert(b, msg) \
  if (!(b)) {fprintf(stderr, "ASSERT: %s\n\n", msg); exit(1);}

//*****
// Forward references

static void FatalErrorCode(HRESULT errcode, int line, const char *file);
static void convert(wchar_t* wcName, size_t length, const char* name);
static void convert(char* cName, size_t length, const wchar_t* name);
static void convert(char* cName, size_t length, const char* name);
static void printProductVersion(aafProductVersion_t* pProductVersion);
static void formatGUID(char *cBuffer, size_t length, aafUID_t *pGUID);
static void printDate(aafDateStruct_t *pDate);
static void printTime(aafTimeStruct_t *pTime);
static void printTimeStamp(aafTimeStamp_t *pTimeStamp);
void Int64ToString( aafInt64 in, aafInt16 base, aafInt16 bufSize, char *buf);
static void PrintSlotInfo(IAAFMob *pMob, IAAFMobSlot *pSlot);
static void RegisterRequiredPlugins(void);
static void ReadAAFFile(aafWChar * pFileName);
static void DisplayMobInfo(IAAFMob *pMob);
static void PrintAudioInfo(IAAFFindSourceInfo *result);
static void PrintVideoInfo(IAAFMasterMob *pMMob, aafSlotID_t SlotID, IAAFFindSourceInfo	*result);
AAFRESULT LookupProperty(IAAFHeader *pHeader, aafUID_t classID, aafUID_t propID, IAAFPropertyDef **result);
void LookupTypeDef(IAAFHeader *pHeader, aafUID_t typeID, IAAFTypeDef **result);

//*************************************************************
//*****		Initialization and MAIN function.
//*************************************************************

int main(int argumentCount, char* argumentVector[])
{
	if (argumentCount != 2) {
		fprintf(stderr, "Error : wrong number of arguments\n");
		fprintf(stderr, "Usage : AAFInfo <file>\n");
		return(1);
	}
	
	char* inputFileName = argumentVector[1];
	
	wchar_t wInputFileName[256];
	convert(wInputFileName, 256, inputFileName);
	
	HRESULT hr = AAFLoad(0);
	if (!AAFRESULT_SUCCEEDED(hr))
	{
		fprintf(stderr, "Error : Failed to load the AAF library, ");
		fprintf(stderr, "check environment variables -\n");
		fprintf(stderr, "  Windows    - $PATH\n");
		fprintf(stderr, "  Unix/Linux - $LD_LIBRARY_PATH\n");
		exit(hr);
	}
	
	RegisterRequiredPlugins();
	ReadAAFFile(wInputFileName);
	
	AAFUnload();
	
	return(0);
}



//*************************************************************
//*****		Add-on property functions
//*****		These are the functions required to read integer properties which are
//*****		not in the standard AAF set of properties.
//*************************************************************


//extern "C" const aafUID_t kAAFPropID_DIDResolutionID =		{ 0xce2aca4d, 0x51ab, 0x11d3, { 0xa0, 0x24, 0x0, 0x60, 0x94, 0xeb, 0x75, 0xcb }};
//extern "C" const aafUID_t kAAFPropID_DIDFirstFrameOffset =	{ 0xce2aca4e, 0x51ab, 0x11d3, { 0xa0, 0x24, 0x0, 0x60, 0x94, 0xeb, 0x75, 0xcb }};
//extern "C" const aafUID_t kAAFPropID_DIDImageSize =			{ 0xce2aca4f, 0x51ab, 0x11d3, { 0xa0, 0x24, 0x0, 0x60, 0x94, 0xeb, 0x75, 0xcb }};
//extern "C" const aafUID_t kAAFPropID_DIDFrameSampleSize =	{ 0xce2aca50, 0x51ab, 0x11d3, { 0xa0, 0x24, 0x0, 0x60, 0x94, 0xeb, 0x75, 0xcb }};
//extern "C" const aafUID_t kAAFPropID_DIDFrameIndexByteOrder = { 0xb57e925d, 0x170d, 0x11d4, { 0xa0, 0x8f, 0x0, 0x60, 0x94, 0xeb, 0x75, 0xcb }};
extern "C" const aafUID_t kAAFPropID_DIDDataOffset =		{ 0xbfde81e4, 0xbcc8, 0x4abd, { 0xa8, 0xe, 0x21, 0x4d, 0xc0, 0xf1, 0x46, 0x84 }};
extern "C" const aafUID_t kAAFPropID_MobAppCode =		{ 0x96c46992, 0x4f62, 0x11d3, { 0xa0, 0x22, 0x0, 0x60, 0x94, 0xeb, 0x75, 0xcb }};

//*****
//Expand this to include more of the provate definitions as they are added.
void CreateMCDefinitions(IAAFHeader *pHeader)
{
	IAAFPropertyDef*	pUnused;
	HRESULT				hr = AAFRESULT_SUCCESS;
	IAAFClassDef*		pClassDef;
	IAAFTypeDef			*pTypeInt32;
	IAAFDictionary		*dict;

	check(pHeader->GetDictionary(&dict));
	check(dict->LookupClassDef(AUID_AAFDigitalImageDescriptor, &pClassDef));
	check(dict->LookupTypeDef(kAAFTypeID_Int32, &pTypeInt32));

	if(pClassDef->LookupPropertyDef(kAAFPropID_DIDDataOffset, &pUnused) != AAFRESULT_SUCCESS)
	{
		hr = pClassDef->RegisterOptionalPropertyDef(kAAFPropID_DIDDataOffset,
											L"DIDDataOffset",
											pTypeInt32,
											&pUnused);

		check(hr);
	}
	pUnused->Release();
	printf("Made MC Definitions\n");
}

//*****
// Register all of the standard codec & interpolator plugins
// ALL of the codecs are shipped as plugins, there's nothing linked in.
static void RegisterRequiredPlugins(void)
{
	IAAFPluginManager	*mgr = NULL;

  // Load the plugin manager 
  check(AAFGetPluginManager(&mgr));

  // Attempt load and register all of the plugins
  // in the shared plugin directory.
  check(mgr->RegisterSharedPlugins());

  // Attempt to register all of the plugin files
  // in the given directorys:
  //check(mgr->RegisterPluginDirectory(directory1));
  //check(mgr->RegisterPluginDirectory(directory2));


  // Attempt to register all of the plugins in any
  // of the given files:
  //check(mgr->RegisterPluginFile(file1));
  //check(mgr->RegisterPluginFile(file2));
  //...
}

//*****
// Given AUIDs for  class, prop, and type, read the integer property
// This may be used to read any property, but it's faster to use the classes (ex IAAFMob)
// to read their own properties, and there's a bit of indirection in reading the fields
// this way.
HRESULT GetIntegerPropFromObject(IAAFHeader *pHeader, IAAFObject* pObj, const aafUID_t & classID, const aafUID_t & propID, const aafUID_t &typeID, aafMemPtr_t pValue, aafUInt32 ValueSize)
{
	IAAFPropertyValue*	pPV = NULL;
	IAAFPropertyDef*	pPD;
	HRESULT				hr;
	IAAFTypeDef			*pTypeDef;
	
	// Get the property value for the target property
	printf("Before lookup prop\n");
	hr = LookupProperty(pHeader, classID, propID, &pPD);
	if(hr != AAFRESULT_SUCCESS)
		return hr;
	printf("Before lookup type\n");
	LookupTypeDef(pHeader, typeID, &pTypeDef);
	//	if (SUCCEEDED(hr))
	{
		aafBool	present = kAAFFalse;
		
		pObj->IsPropertyPresent(pPD, &present);
		if (present == kAAFTrue)
			hr = pObj->GetPropertyValue(pPD, &pPV);
		else
			hr = AAFRESULT_PROP_NOT_PRESENT;
		
		pPD->Release();
	}
	
	printf("After GetPropertyValue\n");
	if (SUCCEEDED(hr))
	{
		IAAFTypeDefInt* pTDInt;
		
		// Get the type def from the dict with which to interpret this
		// property value.
		hr = pTypeDef->QueryInterface(IID_IAAFTypeDefInt, (void**)&pTDInt);
		if (SUCCEEDED(hr))
		{
			hr = pTDInt->GetInteger(pPV, pValue, ValueSize);
			pTDInt->Release();
		}
	}
	
	if (pPV) pPV->Release();
	
	return hr;
}

//*****
//Support function for GetIntegerPropFromObject
AAFRESULT LookupProperty(IAAFHeader *pHeader, aafUID_t classID, aafUID_t propID, IAAFPropertyDef **result)
{
	IAAFDictionary	*dict;
	IAAFClassDef	*pClassDef;
	AAFRESULT		hr;

	check(pHeader->GetDictionary(&dict));
	check(dict->LookupClassDef(classID, &pClassDef));
	hr = pClassDef->LookupPropertyDef(propID, result);
	dict->Release();
	pClassDef->Release();

	return hr;
}

//*****
//Support function for GetIntegerPropFromObject
void LookupTypeDef(IAAFHeader *pHeader, aafUID_t typeID, IAAFTypeDef **result)
{
	IAAFDictionary	*dict;
	
	check(pHeader->GetDictionary(&dict));
	check(dict->LookupTypeDef(typeID, result));
	dict->Release();
}

//*************************************************************
//*****		Identification Object
//*****		This object is created every time a file is created or modified, and
//*****		show an audit trail of the applications which touched the data.
//*****		The generationID can be correlated to the generation ID on an object in
//*****		order to tell when an object was modified.
//*************************************************************
static void printIdentification(IAAFIdentification* pIdent)
{
  aafWChar wchName[500];
  char chName[1000];
  char chName2[1000];

  AAFRESULT hr = AAFRESULT_SUCCESS;
    
  aafTimeStamp_t timeStamp;
  check(pIdent->GetDate(&timeStamp));
  printf("    Date             = ");
  printTimeStamp(&timeStamp);
  printf("\n");
   
  check(pIdent->GetCompanyName(wchName, sizeof (wchName)));
  convert(chName, sizeof(chName), wchName);
  check(pIdent->GetProductName(wchName, sizeof (wchName)));
  convert(chName2, sizeof(chName2), wchName);
  printf("    CompanyName      = \"%s\" \"%s\"\n", chName, chName2);

  check(pIdent->GetProductVersionString(wchName, sizeof (wchName)));
  convert(chName, sizeof(chName), wchName);
  printf("    ProductVersionString = \"%s\"\n", chName);

  // optional
  aafProductVersion_t version;
  hr = pIdent->GetProductVersion(&version);
  printf("    ProductVersion   = ");
  if (hr == AAFRESULT_SUCCESS)
  {
	printProductVersion(&version);
	printf("\n");
  }
  else if (hr == AAFRESULT_PROP_NOT_PRESENT)
    printf("    (optional property not present)\n");
  else
    check(hr);

  aafUID_t productID;
  check(pIdent->GetProductID(&productID));
  formatGUID(chName, sizeof(chName), &productID);
  printf("    ProductID            = %s\n", chName);

  // optional
  hr = pIdent->GetRefImplVersion(&version);
  printf("    AAF Toolkit Version  = ");
  if (hr == AAFRESULT_SUCCESS)
  {
    printProductVersion(&version);
    printf("\n");
  }
  else if (hr == AAFRESULT_PROP_NOT_PRESENT)
    printf("    (optional property not present)\n");
  else
	check(hr);

  // optional
  hr = pIdent->GetPlatform(wchName, sizeof (wchName));
  printf("    Platform         = ");
  if (hr == AAFRESULT_SUCCESS)
  {
    convert(chName, sizeof(chName), wchName);
    printf("\"%s\"\n", chName);
  }
  else if (hr == AAFRESULT_PROP_NOT_PRESENT)
    printf("    (optional property not present)\n");
  else
    check(hr);

  aafUID_t generationID;
  check(pIdent->GetGenerationID(&generationID));
  formatGUID(chName, sizeof(chName), &generationID);
  printf("    GenerationID         = %s\n", chName);
}

//*************************************************************
//*****		Top level function to read all of the contents of one file.
//*****		Currently, only looks for ident object, composition mobs and master mobs.
//*****		
//*****		Note that I'm using CountMobs only to handle the special "nothing there"
//*****		case of a display utility.
//*****		
//*****		When following a mob reference, it's better to use IAAFSourceClip::ResolveRef()
//*****		or IAAFHeader::LookupMob().
//*************************************************************
static void ReadAAFFile(aafWChar * pFileName)
{
	HRESULT		hr = S_OK;
	IAAFFile	* pFile = NULL;
	aafUInt32	usageCode;
	IAAFObject	*pObj;

  hr = AAFFileOpenExistingRead (pFileName, AAF_FILE_MODE_LAZY_LOADING, &pFile);
  if (SUCCEEDED(hr))
  {
    IAAFHeader * pHeader = NULL;

    hr = pFile->GetHeader(&pHeader);
    check(hr); // display error message
	gHeader = pHeader;

	if (SUCCEEDED(hr))
    {
      IAAFIdentification *    pIdent = NULL;

	  CreateMCDefinitions(pHeader);

      hr = pHeader->GetLastIdentification(&pIdent);
      check(hr); // display error message
      if (SUCCEEDED(hr))
      {
		printf("File edited by:\n");
        printIdentification(pIdent);

        pIdent->Release();
        pIdent = NULL;

		aafSearchCrit_t	criteria;
		IEnumAAFMobs	*mobs;
		IAAFMob			*pMob;
		long			numShown;

			aafNumSlots_t numMobs;
	    /* Get Composition Mobs */
	    printf("\nCompositions\n");
	    printf(  "------------\n");
		numShown = 0;
		criteria.searchTag = kAAFByMobKind;
		criteria.tags.mobKind = kAAFCompMob;
		check(pHeader->GetMobs(&criteria, &mobs));
		while(mobs->NextOne(&pMob) == AAFRESULT_SUCCESS)
		{
			printf("Mob\n");
			check(pMob->QueryInterface(IID_IAAFObject, (void**)&pObj));
			
			usageCode = 0;
			hr = GetIntegerPropFromObject(pHeader, pObj, AUID_AAFMob, kAAFPropID_MobAppCode, kAAFTypeID_Int32, (unsigned char*)&usageCode, sizeof(usageCode));
			printf("hr = %ld\n", hr);
			if ((hr == AAFRESULT_SUCCESS) && usageCode != 0)
				continue;

			printf("Mob2\n");
			DisplayMobInfo(pMob);
			printf("\n");
			numShown++;
			pMob->Release();
			pMob  = NULL;
		}
	    if (numShown == 0)
	      printf("No Compositions or subclips found.\n");

	    /* Get subclip Mobs */
	    printf("\nSub Clips\n");
	    printf(  "------------\n");
		numShown = 0;
		criteria.searchTag = kAAFByMobKind;
		criteria.tags.mobKind = kAAFCompMob;
		check(pHeader->GetMobs(&criteria, &mobs));
		while(mobs->NextOne(&pMob) == AAFRESULT_SUCCESS)
		{
			check(pMob->QueryInterface(IID_IAAFObject, (void**)&pObj));
			
			usageCode = 0;
			hr = GetIntegerPropFromObject(pHeader, pObj, AUID_AAFMob, kAAFPropID_MobAppCode, kAAFTypeID_Int32, (unsigned char*)&usageCode, sizeof(usageCode));
			if ((hr != AAFRESULT_SUCCESS) || usageCode != 2)
				continue;

			DisplayMobInfo(pMob);
			printf("\n");
			numShown++;
			pMob->Release();
			pMob  = NULL;
		}
	    if (numShown == 0)
	      printf("No Subclips found.\n");

		printf("\n\nMedia Data\n");
	    printf("----------\n");
	    /* Get to the media data via master mobs */
        check(pHeader->CountMobs(kAAFMasterMob, &numMobs));
	    if (numMobs == 0)
	      printf("No Media Data found.\n");
		else
		{
			criteria.searchTag = kAAFByMobKind;
			criteria.tags.mobKind = kAAFMasterMob;
			check(pHeader->GetMobs(&criteria, &mobs));
			while(mobs->NextOne(&pMob) == AAFRESULT_SUCCESS)
			{
				DisplayMobInfo(pMob);
				pMob->Release();
				pMob  = NULL;
				printf("\n");
			}
			mobs->Release();
			mobs = NULL;
		}
	  }
      pHeader->Release();
      pHeader = NULL;
    }

	gHeader = NULL;
	hr = pFile->Close();
    check(hr);

    pFile->Release();
    pFile = NULL;
  }
  else
  {
    fprintf(stderr, "Error : Failed to open file (result = %0x).\n", hr);
    exit(1);
  }
}

//*************************************************************
//*****		Extracts information about a single MOB
//*****		
//*****		AAF mobIDs are generated by the OMF algorithm, and then sliced up to
//*****		fit into the AAF UMID.  Look in AAFUtils.cpp for the function aafMobIDNew()
//*****		for an example of the mapping.
//*************************************************************

static void DisplayMobInfo(IAAFMob *pMob)
{
	aafUInt32		wnameLen, nameLen;
	aafCharacter	*wname;
	char			*name;
	aafNumSlots_t	numSlots;
	aafUInt32		numComments, n;
	IEnumAAFMobSlots *slotIter;
	IAAFMobSlot		*pSlot;
	
	// Generally, it's get buffer length, allocate, read.  Note that we've been generous
	// on the char buffer size, to handle true multi-byte.
	check(pMob->GetNameBufLen(&wnameLen));
	nameLen = 2*wnameLen;
	wname = new aafCharacter[nameLen];
	check(pMob->GetName(wname, nameLen));
	name = new char[nameLen];
	convert(name, nameLen, wname);
	
	printf("Name: \"%s\"\n", name);
	
	delete [] wname;
	delete [] name;
	
	check(pMob->CountComments(&numComments));
	printf("NumComments: %ld\n", numComments);
	//        virtual HRESULT STDMETHODCALLTYPE GetComments( 
	//           /* [out] */ IEnumAAFTaggedValues __RPC_FAR *__RPC_FAR *ppEnum) = 0;
	
	check(pMob->CountSlots(&numSlots));
	printf("NumSlots: %ld\n", numSlots);
	check(pMob->GetSlots(&slotIter));
	n = 1;
	while(slotIter->NextOne(&pSlot) == AAFRESULT_SUCCESS)
	{
		PrintSlotInfo(pMob, pSlot);
		pSlot->Release();
		pSlot = NULL;
	}
	slotIter->Release();
	slotIter = NULL;
}

static void PrintSlotInfo(IAAFMob *pMob, IAAFMobSlot *pSlot)
{
	IAAFDataDef	*dataDef;
	aafUInt32		physSlotNum;
	aafSlotID_t		SlotID;
	IAAFMasterMob	*pMMob;
	aafUInt32		wnameLen, nameLen;
	aafCharacter	*wname;
	char			*name;
	
	check(pSlot->GetSlotID(&SlotID));
	check(pSlot->GetDataDef(&dataDef));
	if(pSlot->GetPhysicalNum(&physSlotNum) == AAFRESULT_SUCCESS)
	{
		IAAFDefObject	*def;
		
		check(dataDef->QueryInterface(IID_IAAFDefObject, (void**)&def));
		check(def->GetNameBufLen(&wnameLen));
		nameLen = 2*wnameLen;
		wname = new aafCharacter[nameLen];
		check(def->GetName(wname, nameLen));
		name = new char[nameLen];
		convert(name, nameLen, wname);
		
		printf("    %s %ld -- ID %ld\n", name, physSlotNum, SlotID);
		delete [] wname;
		delete [] name;

		def->Release();
		def = NULL;
	}
	else
	{
		printf("    ID %ld [no physical track]\n", 
			SlotID);
	}
	
	if(pMob->QueryInterface(IID_IAAFMasterMob, (void**)&pMMob) == AAFRESULT_SUCCESS)
	{
		IAAFSearchSource	*pSearch;
		IAAFFindSourceInfo	*result;
		aafBoolean_t		isPicture, isSound;
		
		check(dataDef->IsPictureKind(&isPicture));
		check(dataDef->IsSoundKind(&isSound));
		
		check(pMob->QueryInterface(IID_IAAFSearchSource, (void**)&pSearch));
		check(pSearch->SearchSource(SlotID, 0, kAAFFileMob, NULL, NULL, &result));
		if(isSound)
		{
			
			//       virtual HRESULT STDMETHODCALLTYPE GetSourceReference( 
			//           /* [out] */ aafSourceRef_t __RPC_FAR *pSourceRef) = 0;
			
			PrintAudioInfo(result);
		}
		if(isPicture)
		{
			PrintVideoInfo(pMMob, SlotID, result);
		}
		
		
		//       virtual HRESULT STDMETHODCALLTYPE CountSamples( 
		//           /* [in] */ IAAFDataDef __RPC_FAR *pDataDef,
		//           /* [out] */ aafLength_t __RPC_FAR *result) = 0;

		pMMob->Release();
		pMMob = NULL;
	}
}

//*************************************************************
//*****		Prints descriptor information for audio mobs using the low-level
//*****		interfaces.  This is useful when you need to read MC specific properties
//*****		like the absolute offset to the media data.
//*****		A version of this function using
//*****		the high-level media functions is in the works.
//*************************************************************
static void PrintAudioInfo(IAAFFindSourceInfo	*result)
{
	IAAFMob					*mob;
	IAAFSourceMob			*sourceMob;
	IAAFEssenceDescriptor	*desc;
	IAAFFileDescriptor		*fileDesc;
	//  omfInt32 sampleSize;
	//  omfInt32 numChannels;
	
	//  char codecName[NAMESIZE];
	aafLength_t numSamples;
	char prtBuf[64];
	aafRational_t editRate;
	
	check(result->GetMob(&mob)); 
	check(mob->QueryInterface(IID_IAAFSourceMob, (void**)&sourceMob));
    check(sourceMob->GetEssenceDescriptor(&desc));
	if(desc->QueryInterface(IID_IAAFAIFCDescriptor, (void**)&sourceMob) == AAFRESULT_SUCCESS)
	{
		printf("        Format: AIFC\n");
		sourceMob->Release();
		sourceMob = NULL;
	}
	else if(desc->QueryInterface(IID_IAAFWAVEDescriptor, (void**)&sourceMob) == AAFRESULT_SUCCESS)
	{
		printf("        Format: WAVE\n");
		sourceMob->Release();
		sourceMob = NULL;
	}
	
	check(result->GetEditRate(&editRate));
	printf("        Edit Rate: %ld/%ld\n", editRate.numerator,
		editRate.denominator);
	
	check(desc->QueryInterface(IID_IAAFFileDescriptor, (void**)&fileDesc));
	check(fileDesc->GetLength(&numSamples));
	Int64ToString(numSamples, 10, sizeof(prtBuf), prtBuf);
	printf("            No. Samples   %s\n", prtBuf);
	
	fileDesc->Release();
	fileDesc = NULL;
	mob->Release();
	mob = NULL;
	desc->Release();
	desc = NULL;
}


//*************************************************************
//*****		Prints descriptor information for video mobs.
//*****		interfaces.  This is useful when you need to read MC specific properties
//*****		like the absolute offset to the media data.
//*****		A version of this function using
//*****		the high-level media functions is in the works.
//*************************************************************
static void PrintVideoInfo(IAAFMasterMob *pMMob, aafSlotID_t SlotID, IAAFFindSourceInfo	*result)
{
	char layoutString[128];

	aafUInt32				height, width;
	aafInt32				xOffset, yOffset;
	aafLength_t				numSamples;
	char					prtBuf[64];
	IAAFMob					*mob;
	IAAFSourceMob			*sourceMob;
	IAAFEssenceDescriptor	*desc;
	IAAFFileDescriptor		*fileDesc;
	IAAFDigitalImageDescriptor	*didd;
	IAAFTIFFDescriptor		*tiff;
	IAAFCodecDef			*codecDef;
	IAAFDefObject			*def;
	aafUID_t				auid;
	aafFrameLayout_t		layout;
	aafInt32				componentWidth, dataOffset;
	aafInt16				pad;
	aafUInt32				horizontalSub, verticalSub;
	IAAFObject				*pObj;
	
	check(result->GetMob(&mob)); 
	check(mob->QueryInterface(IID_IAAFSourceMob, (void**)&sourceMob));
    check(sourceMob->GetEssenceDescriptor(&desc));
	check(desc->QueryInterface(IID_IAAFFileDescriptor, (void**)&fileDesc));
	
	check(desc->QueryInterface(IID_IAAFObject, (void**)&pObj));


	check(fileDesc->GetCodecDef(&codecDef));
	check(codecDef->QueryInterface(IID_IAAFDefObject, (void**)&def));
	check(def->GetAUID(&auid));
	if(memcmp(&auid, &kAAFCodecJPEG, sizeof(auid)) == 0)
	{
		IAAFCDCIDescriptor		*cdci;
		printf("        Format:      JPEG\n");
		check(desc->QueryInterface(IID_IAAFCDCIDescriptor, (void**)&cdci));
		check(cdci->GetComponentWidth(&componentWidth));
		printf("        ComponentSize: %ld\n", componentWidth);
		check(cdci->GetPaddingBits(&pad));
		printf("        Pad Bits:    %d\n", pad);
		check(cdci->GetHorizontalSubsampling(&horizontalSub));
		printf("        HSubsample:  %ld\n", horizontalSub);
		check(cdci->GetVerticalSubsampling(&verticalSub));
		printf("        VSubsample:  %ld\n", verticalSub);
		cdci->Release();
		cdci = NULL;
	}
	else if(memcmp(&auid, &kAAFCodecCDCI, sizeof(auid)) == 0)
	{
		IAAFCDCIDescriptor		*cdci;
		printf("        Format:      CDCI (Uncompressed)\n");
		check(desc->QueryInterface(IID_IAAFCDCIDescriptor, (void**)&cdci));
		check(cdci->GetComponentWidth(&componentWidth));
		printf("        ComponentSize: %ld\n", componentWidth);
		check(cdci->GetPaddingBits(&pad));
		printf("        Pad Bits:    %d\n", pad);
		check(cdci->GetHorizontalSubsampling(&horizontalSub));
		printf("        HSubsample:  %ld\n", horizontalSub);
		check(cdci->GetVerticalSubsampling(&verticalSub));
		printf("        VSubsample:  %ld\n", verticalSub);

		cdci->Release();
		cdci = NULL;
	}
	else if(memcmp(&auid, &kAAFCodecRGBA, sizeof(auid)) == 0)
	{
		IAAFRGBADescriptor		*rgba;
		printf("        Format:      RGBA\n");
		check(desc->QueryInterface(IID_IAAFRGBADescriptor, (void**)&rgba));

		rgba->Release();
		rgba = NULL;
	}
	else if(desc->QueryInterface(IID_IAAFTIFFDescriptor, (void**)&tiff) == AAFRESULT_SUCCESS)
	{
		printf("        Format:      TIFF\n");
		tiff->Release();
		tiff = NULL;
	}

	if(desc->QueryInterface(IID_IAAFDigitalImageDescriptor, (void**)&didd) == AAFRESULT_SUCCESS)
	{
		check(didd->GetStoredView(&height, &width));
		printf("        Stored Size: %ldx%ld\n", width, height);
		check(didd->GetSampledView(&height, &width, &xOffset, &yOffset));
		printf("        Sampled:     (%ld, %ld) %ldx%ld\n", xOffset, yOffset, width, height);
		check(didd->GetDisplayView(&height, &width, &xOffset, &yOffset));
 		printf("        Display:     (%ld, %ld) %ldx%ld\n", xOffset, yOffset, width, height);

		check(didd->GetFrameLayout(&layout));
		switch (layout)
		{
		case kAAFFullFrame:
			strcpy(layoutString, "Full Frame");
			break;
		case kAAFSeparateFields:
			strcpy(layoutString, "Separate Fields");
			break;
		case kAAFOneField:
			strcpy(layoutString, "One Field");
			break;
		case kAAFMixedFields:
			strcpy(layoutString, "Mixed Fields");
			break;
		default:
			strcpy(layoutString, "Null Layout");
			break;
		}
		printf("        Layout;      %s\n", layoutString);

		didd->Release();
		didd = NULL;
	}
	check(fileDesc->GetLength(&numSamples));
	Int64ToString(numSamples, 10, sizeof(prtBuf), prtBuf);
	printf("        # Samples:   %s\n", prtBuf);
	if(GetIntegerPropFromObject(gHeader, pObj, AUID_AAFDigitalImageDescriptor,
						kAAFPropID_DIDDataOffset, kAAFTypeID_Int32,
						(aafMemPtr_t)&dataOffset, sizeof(dataOffset)) == 0)
	{
		printf("        Data Offset: 0x%0lx\n", dataOffset);
	}
	else
	{
		printf("        Data Offset: not specified\n");
	}
	pObj->Release();
	mob->Release();
	mob = NULL;
	sourceMob->Release();
	sourceMob = NULL;
	desc->Release();
	desc = NULL;
	fileDesc->Release();
	fileDesc = NULL;
}



//*************************************************************
//*****		Utility Functions
//*************************************************************

static void     FatalErrorCode(HRESULT errcode, int line, const char *file)
{
  printf("Error '%0x' returned at line %d in %s\n", errcode, line, file);
  exit(1); 
}

static void convert(wchar_t* wcName, size_t length, const char* name)
{
  assert((name /* && *name */), "Valid input name");
  assert(wcName != 0, "Valid output buffer");
  assert(length > 0, "Valid output buffer size");
  
  size_t status = mbstowcs(wcName, name, length);
  if (status == (size_t)-1) {
    fprintf(stderr, "Error : Failed to convert'%s' to a wide character string.\n\n", name);
    exit(1);  
  }
}

static void convert(char* cName, size_t length, const wchar_t* name)
{
  assert((name /* && *name */), "Valid input name");
  assert(cName != 0, "Valid output buffer");
  assert(length > 0, "Valid output buffer size");

  size_t status = wcstombs(cName, name, length);
  if (status == (size_t)-1) {
    fprintf(stderr, ": Error : Conversion failed.\n\n");
    exit(1);  
  }
}

static void convert(char* cName, size_t length, const char* name)
{
  assert((name /* && *name */), "Valid input name");
  assert(cName != 0, "Valid output buffer");
  assert(length > 0, "Valid output buffer size");

  size_t sourceLength = strlen(name);
  if (sourceLength < length - 1) {
    strncpy(cName, name, length);
  } else {
    fprintf(stderr, "Error : Failed to copy '%s'.\n\n", name);
    exit(1);  
  }
}

static void printProductVersion(aafProductVersion_t* pProductVersion)
{
  printf("%d.%d.%d-%d", pProductVersion->major,
                        pProductVersion->minor,
                        pProductVersion->tertiary,
                        pProductVersion->patchLevel);
  const char* releaseType;
  switch (pProductVersion->type) {
    case kAAFVersionUnknown:
      releaseType = "Unknown";
      break;
    case kAAFVersionReleased:
      releaseType = "Released";
      break;
    case kAAFVersionDebug:
      releaseType = "Debug";
      break;
    case kAAFVersionPatched:
      releaseType = "Patched";
      break;
    case kAAFVersionBeta:
      releaseType = "Beta";
      break;
    case kAAFVersionPrivateBuild:
      releaseType = "PrivateBuild";
      break;
    default:
      releaseType = "Not Recognized";
      break;
  }
  printf(" (%s)", releaseType);
}

#if defined( OS_UNIX )

aafUInt8 HostByteOrder(void)
{
  aafUInt16 word = 0x1234;
  aafUInt8 byte = *((aafUInt8*)&word);
  aafUInt8 result;

  if (byte == 0x12) {
    result = 'B';
  } else {
    result = 'L';
  }
  return result;
}

static const unsigned char idMapLittle[] =
{ 3, 2, 1, 0, '-', 5, 4, '-', 7, 6, '-', 8, 9, '-', 10, 11, 12, 13, 14, 15 }; 
static const unsigned char idMapBig[] =
{ 0, 1, 2, 3, '-', 4, 5, '-', 6, 7, '-', 8, 9, '-', 10, 11, 12, 13, 14, 15 }; 
static const unsigned char* guidMap;
static const wchar_t digits[] = L"0123456789ABCDEF"; 

#define GUIDSTRMAX 38 

int StringFromGUID2(const GUID& guid, OLECHAR* buffer, int bufferSize) 
{
  if (HostByteOrder() == 'L') {
    guidMap = &idMapLittle[0];
  } else {
    guidMap = &idMapBig[0];
  }
  const unsigned char* ip = (const unsigned char*) &guid; // input pointer
  OLECHAR* op = buffer;                                    // output pointer

  *op++ = L'{'; 
 
  for (size_t i = 0; i < sizeof(idMapLittle); i++) { 

    if (guidMap[i] == '-') { 
      *op++ = L'-'; 
    } else { 
      *op++ = digits[ (ip[guidMap[i]] & 0xF0) >> 4 ]; 
      *op++ = digits[ (ip[guidMap[i]] & 0x0F) ]; 
    } 
  } 
  *op++ = L'}'; 
  *op = L'\0'; 
 
  return GUIDSTRMAX; 
} 

#endif

// The maximum number of characters in the formated GUID.
// (as returned by StringFromGUID2).
const size_t MAX_GUID_BUFFER = 40;

static void formatGUID(char *cBuffer, size_t length, aafUID_t *pGUID)
{
  assert(pGUID, "Valid input GUID");
  assert(cBuffer != 0, "Valid output buffer");
  assert(length > 0, "Valid output buffer size");

  int bytesCopied = 0;
  OLECHAR wGUID[MAX_GUID_BUFFER];

  bytesCopied = StringFromGUID2(*((GUID*)pGUID), wGUID, MAX_GUID_BUFFER);
  if (0 < bytesCopied) {
    convert(cBuffer, length, wGUID);
  } else {
    fprintf(stderr, "\nError : formatGUID failed.\n\n");
    exit(1);  
  }
}

static void printDate(aafDateStruct_t *pDate)
{
  printf("%04d-%02d-%02d", pDate->year, pDate->month, pDate->day);
}

static void printTime(aafTimeStruct_t *pTime)
{
  printf("%02d:%02d:%02d.%02d", pTime->hour, pTime->minute, pTime->second, pTime->fraction);
}

static void printTimeStamp(aafTimeStamp_t *pTimeStamp)
{
  printDate(&pTimeStamp->date);
  printf(" ");
  printTime(&pTimeStamp->time);
}

void Int64ToString(
			aafInt64	in,			/* IN - Print this number */
			aafInt16	base,		/* IN - in this numerical base */
			aafInt16	bufSize,	/* IN - into a buffer of this length */
			char 		*buf)		/* IN/OUT - here is the buffer. */
{
	aafInt64		workval;
	char			tmpBuf[64];
	aafInt32		numDigits, remainder, src, dest;
	aafBool			negative = FALSE;
	
		numDigits = 0;
		workval = in;
		if(workval == 0)
		{
			buf[0] = '0';
			buf[1] = '\0';
		}
		else
		{
			if(workval < 0)
			{
				workval = -workval;
				negative = TRUE;
			}
			while(workval > 0)
			{
				remainder = (long)(workval % base);
				workval = workval / base;
				tmpBuf[numDigits++] = (char)remainder + '0';
			}
			if(negative)
				tmpBuf[numDigits++] = '-';
			if(numDigits < bufSize)		/* Allow one byte for '\0' */
			{
				for(src = numDigits-1, dest = 0; src >= 0; src--, dest++)
					buf[dest] = tmpBuf[src];
				buf[numDigits] = '\0';
			}
			else
			{
				strncpy(buf, "*err*", bufSize-1);
				buf[bufSize-1] = '\0';
			}
		}
}
