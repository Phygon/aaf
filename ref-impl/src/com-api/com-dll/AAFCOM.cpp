////////////////////////////////////////////////////////////////////////////////
// @doc
//
// @module AAFCOM.CPP - AAF COM InProc Server DLL |
//
// Implementation of DLL Exports
// 
// @end
//
// Tom Ransdell, Avid AAF Development Team
//
////////////////////////////////////////////////////////////////////////////////

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
* THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
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

// Prototypes that must be implemented but NOT exported.
extern "C" const char * AAFGetLibraryDirectory();
extern "C" const char * AAFGetLibraryPath();


#include "CAAFInProcServer.h"
#include "ImplAAFContext.h"

CAAFInProcServer g_AAFInProcServer;
CAAFServer* g_pAAFServer = &g_AAFInProcServer;


// Include the table the associates all of the CLSID's with class names and factory methods.
#include "AAFObjectTable_i.cpp"

// Include the definitions for all of the interface IID's.
#include "AAF_i.c"
#include "AAFPrivate_i.c"


#if defined(_MAC)

// Make sure we have defined IID_IUnknown and IID_IClassFactory.
#include <initguid.h>
#include <coguid.h>	


// Define struc
typedef struct
{
	CFragInitBlock		InitBlock;	// CFM init Block
	Boolean				Inited;		// True if we've been inited
	short				ResRefNum;	// ResRefNum of the dll
	UInt32				DLLVersion; // holds DLL's version number from resource
}
dlldata;

static dlldata	DllData;




enum 
{
	uppDllInitRoutineProcInfo = kPascalStackBased
		 | RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		 | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(CFragInitBlockPtr)))
};

ProcInfoType __procinfo = uppDllInitRoutineProcInfo;


extern "C" 
{
OSErr pascal __initialize(CFragInitBlockPtr initBlkPtr);
OSErr pascal DllInitializationRoutine(CFragInitBlockPtr initBlkPtr);
OSErr pascal DllExecutionRoutine();
void pascal __terminate();
void pascal DllTerminationRoutine();
}

#include "MetroNubUtils.h"


#pragma export on
#endif // #if defined(_MAC)



#if defined(WIN32) || defined(_WIN32)
// Include the entry point for the windows dll.
/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{	
		// Initialize the inproc server object.
		g_AAFInProcServer.Init(AAFObjectMap, hInstance);

    // Attempt to intialize the global AAF context singleton.
    // This is a thread safe because this initialization
    // is only called when the dll is first loaded by the 
    // main thread of the current process. 
    // NOTE:This object is not reference counted!
    if (NULL == ImplAAFContext::GetInstance ())
    {
      // Return the most liked error code.
      return E_OUTOFMEMORY;
    }

    // We don't need to be notified everytime a thread is created
    // or destroyed.
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		g_AAFInProcServer.Term();
	}
	return TRUE;    // ok
}

#endif


/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	return g_AAFInProcServer.CanUnloadNow();
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return g_AAFInProcServer.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	// registers objects, typelib and all interfaces in typelib
	return g_AAFInProcServer.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	// Unregisters all objects.
	return g_AAFInProcServer.UnregisterServer();
}



#if defined(_MAC)
//
//  DllGetVersion
//
//  gets the controls version
//

STDAPI
DllGetVersion(UInt32* pVersion)
{
	Handle	hResource = NULL;
	HRESULT	Error = E_FAIL;
	
	if (!DllData.Inited && DllData.InitBlock.fragLocator.where == kDataForkCFragLocator)
	{
		short	InResFile = ::CurResFile();
		short	ResRefNum;

		//	open up the resource fork of the dll and save it off
		ResRefNum = ::FSpOpenResFile(DllData.InitBlock.fragLocator.u.onDisk.fileSpec, fsRdPerm);

		hResource = Get1Resource('vers', 1);
		
		if (hResource && GetHandleSize(hResource) > sizeof(UInt32))
		{
			//  Extract the version number from the resource, stripping off
			//  the release stage byte.
			DllData.DLLVersion = *pVersion = (*((LPDWORD)(*hResource))) & 0xFFFF00FF;
			Error = S_OK;
		}
		if(hResource)
			ReleaseResource(hResource);
		
		::UseResFile(InResFile);
		CloseResFile(ResRefNum);
	}
	else
		*pVersion = DllData.DLLVersion;

	return Error;
}

//
//  DllInitializationRoutine
//
//  Initialization routine called by COM
//

OSErr pascal
DllInitializationRoutine(CFragInitBlockPtr initBlkPtr)
{
	DllData.InitBlock = *initBlkPtr;
	DllData.Inited = false;
	DllData.ResRefNum = -1;


	__initialize(initBlkPtr);

	// Initialize the inproc server object with a copy of the contents of the initBlkPtr.
	g_AAFInProcServer.Init(AAFObjectMap, (HINSTANCE)&DllData.InitBlock);


  // Attempt to intialize the global AAF context singleton.
  // This is a thread safe because this initialization
  // is only called when the dll is first loaded by the 
  // main thread of the current process. 
  // NOTE:This object is not reference counted!
  if (NULL == ImplAAFContext::GetInstance ())
  {
    // Return the most liked error code.
    return memFullErr;
  }


	if (!DllData.Inited && DllData.InitBlock.fragLocator.where == kDataForkCFragLocator)
	{
		short	InResFile = ::CurResFile();
		Handle	hResource = NULL;

		DllData.Inited = true;
		//	open up the resource fork of the dll and save it off
		DllData.ResRefNum = ::FSpOpenResFile(DllData.InitBlock.fragLocator.u.onDisk.fileSpec, fsRdPerm);

		hResource = Get1Resource('vers', 1);
		
		if (hResource && GetHandleSize(hResource) > sizeof(UInt32))
		{
			//  Extract the version number from the resource, stripping off
			//  the release stage byte.
			DllData.DLLVersion = (*((LPDWORD)(*hResource))) & 0xFFFF00FF;
		}
		if (hResource)
			ReleaseResource(hResource);

		::UseResFile(InResFile);
	}



    return noErr;
}


//
//  DllExecutionRoutine
//
//  Execution routine called by COM
//

OSErr pascal
DllExecutionRoutine()
{
	//	this routine isn't getting called by anybody
    return noErr;
}


//
//  DllTerminationRoutine
//
//  Termination routine called by COM
//

void pascal
DllTerminationRoutine()
{
	// Terminate the inproc server object.
	g_AAFInProcServer.Term();
	g_pAAFServer	= NULL;

	if (DllData.Inited)
	{
		if (DllData.ResRefNum != -1)
		{
			CloseResFile(DllData.ResRefNum);
			DllData.ResRefNum = -1;
		}
		
		DllData.Inited = false;
	}
	
	__terminate();
}


#pragma export off
#endif // #if defined(_MAC)


//
// Platform dependent file system information needed by the reference
// implementation to load AAF plugins "relative" to this shared library/dll.
//
const char * AAFGetLibraryDirectory()
{
	return g_AAFInProcServer.GetServerDirectory();
}

const char * AAFGetLibraryPath()
{
	return g_AAFInProcServer.GetServerPath();
}
