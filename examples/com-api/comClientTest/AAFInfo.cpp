//=---------------------------------------------------------------------=
//
// The contents of this file are subject to the AAF SDK Public
// Source License Agreement (the "License"); You may not use this file
// except in compliance with the License.  The License is available in
// AAFSDKPSL.TXT, or you may obtain a copy of the License from the AAF
// Association or its successor.
// 
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.
// 
// The Original Code of this file is Copyright 1998-2001, Licensor of the
// AAF Association.
// 
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include the AAF interface declarations.
#include "AAF.h"
#include "AAFTypes.h"
#include "AAFResult.h"

#if defined( OS_MACOS )
#include "DataInput.h"
#endif

static void     FatalErrorCode(HRESULT errcode, int line, char *file)
{
  printf("Error '%0x' returned at line %d in %s\n", errcode, line, file);
  // we don't need to exit on failure
  //exit(1); 
}

static HRESULT moduleErrorTmp = S_OK;/* note usage in macro */
#define check(a)  \
{  moduleErrorTmp = a; \
  if (!SUCCEEDED(moduleErrorTmp)) \
     FatalErrorCode(moduleErrorTmp, __LINE__, __FILE__);\
}

#define assert(b, msg) \
  if (!(b)) {fprintf(stderr, "ASSERT: %s\n\n", msg); exit(1);}


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

static void convert(wchar_t* wName, size_t length, const wchar_t* name)
{
  assert((name /* && *name */), "Valid input name");
  assert(wName != 0, "Valid output buffer");
  assert(length > 0, "Valid output buffer size");

  size_t sourceLength = 0;
  while (*name)
    ++sourceLength;
  if (sourceLength < length - 1) {
    // Copy the string if there is enough room in the destinition buffer.
    while (*wName++ = *name++)
      ;
  } else {
    fprintf(stderr, "Error : Failed to copy '%s'.\n\n", name);
    exit(1);  
  }
}

#if defined( OS_UNIX )

static const unsigned char guidMap[] =
{ 3, 2, 1, 0, '-', 5, 4, '-', 7, 6, '-', 8, 9, '-', 10, 11, 12, 13, 14, 15 }; 
static const wchar_t digits[] = L"0123456789ABCDEF"; 

#define GUIDSTRMAX 38 

typedef OLECHAR OMCHAR;

int StringFromGUID2(const GUID& guid, OMCHAR* buffer, int bufferSize) 
{
  const unsigned char* ip = (const unsigned char*) &guid; // input pointer
  OMCHAR* op = buffer;                                    // output pointer

  *op++ = L'{'; 
 
  for (size_t i = 0; i < sizeof(guidMap); i++) { 

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

static void printIdentification(IAAFIdentification* pIdent)
{
  aafWChar wchName[500];
  char chName[1000];
    
    
  check(pIdent->GetCompanyName(wchName, sizeof (wchName)));
  convert(chName, sizeof(chName), wchName);
  printf("CompanyName          = \"%s\"\n", chName);

  check(pIdent->GetProductName(wchName, sizeof (wchName)));
  convert(chName, sizeof(chName), wchName);
  printf("ProductName          = \"%s\"\n", chName);

  check(pIdent->GetProductVersionString(wchName, sizeof (wchName)));
  convert(chName, sizeof(chName), wchName);
  printf("ProductVersionString = \"%s\"\n", chName);

  aafProductVersion_t version;
  check(pIdent->GetProductVersion(&version));
  convert(chName, sizeof(chName), wchName);
  printf("ProductVersion.major      = %d\n", version.major);
  printf("ProductVersion.minor      = %d\n", version.minor);
  printf("ProductVersion.tertiary   = %d\n", version.tertiary);
  printf("ProductVersion.patchLevel = %d\n", version.patchLevel);
  char* releaseType;
  switch (version.type) {
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
  printf("ProductVersion.type       = \"%s\"\n", releaseType);

  aafUID_t productID;
  check(pIdent->GetProductID(&productID));
  formatGUID(chName, sizeof(chName), &productID);
  printf("ProductID            = %s\n", chName);

  check(pIdent->GetPlatform(wchName, sizeof (wchName)));
  convert(chName, sizeof(chName), wchName);
  printf("Platform             = \"%s\"\n", chName);
}

static void ReadAAFFile(aafWChar * pFileName)
{
  HRESULT hr = S_OK;
  IAAFFile * pFile = NULL;


  hr = AAFFileOpenExistingRead (pFileName, 0, &pFile);
  if (SUCCEEDED(hr))
  {
    IAAFHeader * pHeader = NULL;

    hr = pFile->GetHeader(&pHeader);
    check(hr); // display error message
    if (SUCCEEDED(hr))
    {
      IAAFIdentification *    pIdent = NULL;

      hr = pHeader->GetLastIdentification(&pIdent);
      check(hr); // display error message
      if (SUCCEEDED(hr))
      {
        fprintf(stdout, "LastIdentification\n");
        printIdentification(pIdent);

        pIdent->Release();
        pIdent = NULL;

        aafNumSlots_t n;
        hr = pHeader->CountMobs(kAAFAllMob, &n);
        check(hr);
        printf("Number of Mobs       = %d\n", n);
      }
      pHeader->Release();
      pHeader = NULL;
    }

    hr = pFile->Close();
    check(hr);

    pFile->Release();
    pFile = NULL;
  }
  else
  {
    fprintf(stderr, "Error : Failed to open file (result = %0x).\n", hr);
  }
}

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

  printf("Attempting to load the AAF dll...\n");
  HRESULT hr = AAFLoad(0);
  if (!AAFRESULT_SUCCEEDED(hr))
  {
    fprintf(stderr, "Failed to load the AAF DLL.\n");
    fprintf(stderr, "Is the $PATH environment variable set correctly ?\n");
    exit(1);
  }
  printf("DONE\n");

  ReadAAFFile(wInputFileName);

  fprintf(stdout, "Done\n");

  AAFUnload();

  return(0);
}

