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

#include "ImplAAFFile.h"

#include "OMFile.h"
#include "OMUtilities.h"
#include "OMClassFactory.h"
#include "OMMemoryRawStorage.h"
#include "OMExceptions.h"

#ifndef OM_NO_STRUCTURED_STORAGE
# include "OMSSStoredObjectFactory.h"
# include "OMMS_SSStoredObjectFactory.h"
# ifdef OM_USE_SCHEMASOFT_SS
#  include "OMSS_SSStoredObjectFactory.h"
# endif // OM_USE_SCHEMASOFT_SS
# ifdef OM_USE_GSF_SS
#  include "OMGSF_SSStoredObjectFactory.h"
# endif // OM_USE_GSF_SS
#endif // !OM_NO_STRUCTURED_STORAGE

#include "OMXMLStoredObjectFactory.h"
#include "OMKLVStoredObjectFactory.h"

#include "OMKLVStoredObject.h"
#include "OMMXFStorageBase.h"

#include "ImplAAFDataDef.h"
#include "ImplAAFDictionary.h"
#include "ImplAAFMetaDictionary.h"
#include "ImplAAFHeader.h"
#include "ImplAAFRandomRawStorage.h"
#include "ImplAAFIdentification.h"

#include "AAFStoredObjectIDs.h"
#include "ImplAAFObjectCreation.h"
#include "ImplAAFBuiltinDefs.h"
#include "ImplAAFOMRawStorage.h"

#include "AAFFileMode.h"
#include "AAFFileKinds.h"

#include "ImplAAFSmartPointer.h"
typedef ImplAAFSmartPointer<ImplAAFIdentification>
  ImplAAFIdentificationSP;
typedef ImplAAFSmartPointer<ImplAAFRandomRawStorage>
  ImplAAFRandomRawStorageSP;

#include "OMAssertions.h"

// For IAAFRawStorage
#include "AAF.h"

// If defined RESTORE_MXF_EXTENSIONS causes MXF-specific properies
// to be overwritten or, if they don't exist, created with the values
// returned by Object Manager
#define RESTORE_MXF_EXTENSIONS

extern "C" const aafClassID_t CLSID_AAFRandomRawStorage;

static const aafProductIdentification_t kNullIdent = { 0 };

//
// File Format Version
//
// Update this when incompatible changes are made to AAF file format
// version. 
//
//    kAAFRev1 : Tue Jan 11 17:08:26 EST 2000
//        Initial Release version.
//
//    kAAFRev2 : Wed May 19 19:18:00 EST 2004
//        UInt32Set and AUIDSet types added to built-in model as part
//        of AAF v1.1. This is not compatible with older toolkits.
//
static const aafFileRev_t sCurrentAAFObjectModelVersion = kAAFRev2;


// FileKind from the point of view of the OM.
//
// (Note,this used to be a macro. The macro, however, allows stupid
// erros to go undetected by the compiler. I (jpt) kept the old macro
// name to keep diffs to a minimum.)
OMStoredObjectEncoding ENCODING( const aafUID_t& encodingId )
{
  return *reinterpret_cast<const OMStoredObjectEncoding*>(&encodingId);
}

// local function for simplifying error handling.
inline void checkResult(AAFRESULT r)
{
  if (AAFRESULT_SUCCESS != r)
    throw r;
}

inline void checkExpression(bool test, AAFRESULT r)
{
  if (!test)
    throw r;
}



//
// Returns true if all flags set are defined flags; returns false if
// any flags set are *not* defined.
//
static bool areAllModeFlagsDefined (aafUInt32 modeFlags)
{
  static const aafUInt32 kAllFlags =
	AAF_FILE_MODE_LAZY_LOADING |
	AAF_FILE_MODE_REVERTABLE |
	AAF_FILE_MODE_UNBUFFERED |
	AAF_FILE_MODE_RECLAIMABLE |
	AAF_FILE_MODE_USE_LARGE_SS_SECTORS |
	AAF_FILE_MODE_CLOSE_FAIL_DIRTY |
	AAF_FILE_MODE_DEBUG0_ON |
	AAF_FILE_MODE_DEBUG1_ON;

  if (modeFlags & (~kAllFlags))
	{
	  // at least one flag is not defined
	  return false;
	}
  else
	{
	  return true;
	}
}

//
// Returns true if all flags set are supported flags; returns false if
// any flags set are *not* supported.
//
static bool areAllModeFlagsSupported (aafUInt32 modeFlags)
{
	//NOTE: Lazy loading and large sector support included
  static const aafUInt32 kSupportedFlags =
	AAF_FILE_MODE_USE_LARGE_SS_SECTORS | AAF_FILE_MODE_LAZY_LOADING;

  if (modeFlags & (~kSupportedFlags))
	{
	  // at least one flag is not supported
	  return false;
	}
  else
	{
	  return true;
	}
}

extern "C" const aafClassID_t CLSID_AAFDictionary;

AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::Initialize ()
{
	if (_initialized)
	{
		return AAFRESULT_ALREADY_INITIALIZED;
	}

	// Create the class factory for base classes.
	_factory = ImplAAFDictionary::CreateDictionary();
	if (NULL == _factory)
		return AAFRESULT_NOMEMORY;

	// Create the class factory for meta classes.
	_metafactory = ImplAAFMetaDictionary::CreateMetaDictionary();
	if (NULL == _metafactory)
		return AAFRESULT_NOMEMORY;

	// The following is temporary code. (transdel:2000-APR-11)
	_factory->setMetaDictionary(_metafactory);
	_metafactory->setDataDictionary(_factory);
	
#if 0
	// Experimental: Create and initialize all of the axiomatic definitions.
	// This must be done before another other definitions or data objects
	// can be created.
	AAFRESULT result = _metafactory->InstantiateAxiomaticDefinitions();
	ASSERTU(AAFRESULT_SUCCEEDED(result));
#else
    // Initialize only the non-persistent parts of the meta dictionary
	AAFRESULT result = _metafactory->Initialize();
	ASSERTU(AAFRESULT_SUCCEEDED(result));
#endif

	_initialized = kAAFTrue;

	return result;
}


AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::OpenExistingRead (const aafCharacter * pFileName,
							   aafUInt32 modeFlags)
{
	OMFile::OMLoadMode	loadMode = OMFile::eagerLoad;	// The default behavior
	AAFRESULT stat = AAFRESULT_SUCCESS;

	// Validate parameters and preconditions.
	if (! _initialized)
		return AAFRESULT_NOT_INITIALIZED;

	if (IsOpen())
		return AAFRESULT_ALREADY_OPEN;

	if (_file)
		return AAFRESULT_ALREADY_OPEN;

	if (! pFileName)
		return AAFRESULT_NULL_PARAM;

	if (! areAllModeFlagsDefined (modeFlags))
	  return AAFRESULT_BAD_FLAGS;

	if (! areAllModeFlagsSupported (modeFlags))
	  return AAFRESULT_NOT_IN_CURRENT_VERSION;

    if( modeFlags & AAF_FILE_MODE_LAZY_LOADING)
	{
		  loadMode = OMFile::lazyLoad;
	}

	_modeFlags = modeFlags;

    if (!OMFile::readable(pFileName))
      return AAFRESULT_NOT_READABLE;

	//NOTE: Depending on LARGE sectors flag check encoding 
	if (modeFlags & AAF_FILE_MODE_USE_LARGE_SS_SECTORS)
		return AAFRESULT_BAD_FLAGS;

	OMStoredObjectEncoding encoding;
	if (OMFile::isRecognized(pFileName, encoding)) {
		if (OMFile::isBeingModified(pFileName, encoding))
			return AAFRESULT_FILE_BEING_MODIFIED;
	} else {
		return AAFRESULT_NOT_AAF_FILE;
	}

	try
	{
#if 0 // DICTIONARYLESSFILES
		OMStoredObjectEncoding MXFEncoding = ENCODING(kAAFFileKind_AafKlvBinary);
		if (encoding == MXFEncoding)
		{
		  HRESULT r = _factory->RegisterMetaDictionaries();
		  if (!SUCCEEDED(r)) return r;
		}
#endif
		try {
		  // Ask the OM to open the file.
		  _file = OMFile::openExistingRead(pFileName,
  										 _factory,
  										 0,
										 loadMode,
										 _metafactory);
		} catch (OMException& e) {
			delete _file;
			_file = 0;
			if (e.hasResult()) {
				throw e.result();
			} else {
				throw AAFRESULT_BADOPEN;
			}
		}

		checkExpression(NULL != _file, AAFRESULT_INTERNAL_ERROR);

		// Restore the meta dictionary, it should be the same object
		// as _metafactory
		OMDictionary* mf = _file->dictionary();
		ASSERTU(mf == _metafactory);

		// Make sure all definitions are present in the meta dictionary
		ImplAAFMetaDictionary* d = dynamic_cast<ImplAAFMetaDictionary*>(mf);
		ASSERTU(d);
		checkResult( d->InstantiateAxiomaticDefinitions() );

		// Make sure properties that exist in builtin class
		// definitions but not the file's class definition,
		// are merged to the file's class definition.
		checkResult( d->MergeBuiltinClassDefs() );

		// Get the byte order
		OMByteOrder byteOrder = _file->byteOrder();
		if (byteOrder == littleEndian) {
			_byteOrder = 0x4949; // 'II'
		} else { // bigEndian
			_byteOrder = 0x4d4d; // 'MM'
		}

		// Restore the header.
		bool regWasEnabled = _factory->SetEnableDefRegistration (false);
		OMStorable* head = _file->restore();
		_head = dynamic_cast<ImplAAFHeader *>(head);
		_head->SetFile(this);
		
		// Check for file format version.
		if (_head->IsObjectModelVersionPresent())
		  {
			// If property isn't present, the default version is 0,
			// which is always (supposed to be) legible.  If it is
			// present, find out the version number to determine if
			// the file is legible.
			// If file version is higher than the version understood
			// by this toolkit this file cannot be read.
			checkExpression(_head->GetObjectModelVersion() <=
							static_cast<aafUInt32>(sCurrentAAFObjectModelVersion),
							AAFRESULT_FILEREV_DIFF);
		  }

		// Now that the file is open and the header has been
		// restored, complete the initialization of the
		// dictionary. We obtain the dictionary via the header
		// to give the persistence mechanism a chance to work.
		ImplAAFDictionary* dictionary = 0;
		HRESULT hr = _head->GetDictionary(&dictionary);
		if (hr != AAFRESULT_SUCCESS)
		  return hr;
		_factory->SetEnableDefRegistration (regWasEnabled);
		if (!_factory->IsOMStorableInitialized())
		{
			// Finish initialization of the OMStorable part of the dictionary
			// for files that do not contain an AAF dictionary, such as
			// foreign MXF files.
			// Note the difference from initializing the dictionary object for
			// new files: the call to InitializeOMStorable() is done _after_
			// calling GetDictionary(). This is to ensure that when reading
			// an existing file the dictionary is initialized from the file
			// if the file contains it. And if the file is opened in lazy
			// loading mode the dictionary will not be restored until it is
			// accessed, for example, via GetDictionary().
			_factory->InitializeOMStorable
				  (_factory->GetBuiltinDefs()->cdDictionary());
		}
		dictionary->InitBuiltins();
		dictionary->ReleaseReference();
		dictionary = 0;

#ifdef RESTORE_MXF_EXTENSIONS
		stat = restoreMirroredMetadata();
#endif
	}
	catch (AAFRESULT &r)
	{
		stat = r;

		// Cleanup after failure.
		if (_file)
		{
			_file->close();
		}

		if (NULL != _head)
		{
			_head->ReleaseReference();
			_head = 0;
		}
	}
	
	return stat;
}



AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::OpenExistingModify (const aafCharacter * pFileName,
								 aafUInt32 modeFlags,
								 aafProductIdentification_t * pIdent)
{
	OMFile::OMLoadMode	loadMode = OMFile::eagerLoad;	// The default behavior
	AAFRESULT stat = AAFRESULT_SUCCESS;


	// Validate parameters and preconditions.
	if (! _initialized)
		return AAFRESULT_NOT_INITIALIZED;

	if (IsOpen())
		return AAFRESULT_ALREADY_OPEN;

	if (_file)
		return AAFRESULT_ALREADY_OPEN;

	if (! pFileName)
		return AAFRESULT_NULL_PARAM;

	if (! pIdent)
		return AAFRESULT_NULL_PARAM;

	if (! areAllModeFlagsDefined (modeFlags))
	  return AAFRESULT_BAD_FLAGS;

	if (! areAllModeFlagsSupported (modeFlags))
	  return AAFRESULT_NOT_IN_CURRENT_VERSION;

	if( modeFlags & AAF_FILE_MODE_LAZY_LOADING)
	{
		loadMode = OMFile::lazyLoad;
	}

	_modeFlags = modeFlags;

    if (!OMFile::modifiable(pFileName))
      return AAFRESULT_NOT_MODIFIABLE;

	// JPT REVIEW - What purpose does this serve? None that I can see.
	//NOTE: Depending on LARGE sectors flag set encoding 
	if (modeFlags & AAF_FILE_MODE_USE_LARGE_SS_SECTORS)
	{
	  if (!OMFile::hasFactory( ENCODING(kAAFFileKind_Aaf4KBinary) ))
	    return AAFRESULT_FILEKIND_NOT_REGISTERED;
	}
	else
	{
	  if (!OMFile::hasFactory( ENCODING(kAAFFileKind_Aaf512Binary) ))
	    return AAFRESULT_FILEKIND_NOT_REGISTERED;
	}

	OMStoredObjectEncoding encoding;
	if (!OMFile::isRecognized(pFileName, encoding)) {
		return AAFRESULT_NOT_AAF_FILE;
	}

	if (!OMFile::compatibleStoredFormat(pFileName,
									    OMFile::modifyMode,
									    encoding)) {
		return AAFRESULT_FILEREV_NOT_SUPP;
	}

	if (OMFile::isBeingModified(pFileName, encoding)) {
		return AAFRESULT_FILE_BEING_MODIFIED;
	}

	try 
	{
#if 0 // DICTIONARYLESSFILES
		OMStoredObjectEncoding MXFEncoding = ENCODING(kAAFFileKind_AafKlvBinary);
		if (encoding == MXFEncoding)
		{
		  HRESULT r = _factory->RegisterMetaDictionaries();
		  if (!SUCCEEDED(r)) return r;
		}
#endif
		// Ask the OM to open the file.
		_file = OMFile::openExistingModify(pFileName,
										   _factory,
										   0,
										   loadMode,
										   _metafactory);
		checkExpression(NULL != _file, AAFRESULT_INTERNAL_ERROR);

		// Restore the meta dictionary, it should be the same object
		// as _metafactory
		OMDictionary* mf = _file->dictionary();
		ASSERTU(mf == _metafactory);

		// Make sure all definitions are present in the meta dictionary
		ImplAAFMetaDictionary* d = dynamic_cast<ImplAAFMetaDictionary*>(mf);
		ASSERTU(d);
		checkResult( d->InstantiateAxiomaticDefinitions() );

		// Make sure properties that exist in builtin class
		// definitions but not the file's class definition,
		// are merged to the file's class definition.
		checkResult( d->MergeBuiltinClassDefs() );

		// Get the byte order
		OMByteOrder byteOrder = _file->byteOrder();
		if (byteOrder == littleEndian) {
			_byteOrder = 0x4949; // 'II'
		} else { // bigEndian
			_byteOrder = 0x4d4d; // 'MM'
		}

		// Restore the header.
		bool regWasEnabled = _factory->SetEnableDefRegistration (false);
		OMStorable* head = _file->restore();
		_head = dynamic_cast<ImplAAFHeader *>(head);
		checkExpression(NULL != _head, AAFRESULT_BADHEAD);
		// Check for file format version.
		if (_head->IsObjectModelVersionPresent())
		  {
			// If property isn't present, the default version is 0,
			// which is always (supposed to be) legible.  If it is
			// present, find out the version number to determine if
			// the file is legible.
			// If file version is higher than the version understood
			// by this toolkit this file cannot be read.
			checkExpression(_head->GetObjectModelVersion() <=
							static_cast<aafUInt32>(sCurrentAAFObjectModelVersion),
							AAFRESULT_FILEREV_DIFF);
		  }

		// Update the file format version
		if (sCurrentAAFObjectModelVersion)
		  {
			_head->SetObjectModelVersion(sCurrentAAFObjectModelVersion);
		  }

		// Now that the file is open and the header has been
		// restored, complete the initialization of the
		// dictionary. We obtain the dictionary via the header
		// to give the persistence mechanism a chance to work.
		ImplAAFDictionary* dictionary = 0;
		HRESULT hr = _head->GetDictionary(&dictionary);
		if (hr != AAFRESULT_SUCCESS)
		  return hr;
		_factory->SetEnableDefRegistration (regWasEnabled);
		if (!_factory->IsOMStorableInitialized())
		{
			// Finish initialization of the OMStorable part of the dictionary
			// for files that do not contain an AAF dictionary, such as
			// foreign MXF files.
			// Note the difference from initializing the dictionary object for
			// new files: the call to InitializeOMStorable() is done _after_
			// calling GetDictionary(). This is to ensure that when reading
			// an existing file the dictionary is initialized from the file
			// if the file contains it. And if the file is opened in lazy
			// loading mode the dictionary will not be restored until it is
			// accessed, for example, via GetDictionary().
			_factory->InitializeOMStorable
				  (_factory->GetBuiltinDefs()->cdDictionary());
		}
		dictionary->InitBuiltins();
		dictionary->ReleaseReference();
		dictionary = 0;

		checkResult(_head->SetToolkitRevisionCurrent());
	  
		// NOTE: If modifying an existing file WITHOUT an IDNT object, add a
		// dummy IDNT object to indicate that this program was not the creator.
		//
		aafUInt32	numIdent = 0;
		checkResult(_head->CountIdentifications(&numIdent));
		if(numIdent == 0)
		{
			_head->AddIdentificationObject((aafProductIdentification_t *)NULL);
		}
		// Now, always add the information from THIS application */
		_head->AddIdentificationObject(pIdent);

#ifdef RESTORE_MXF_EXTENSIONS
		stat = restoreMirroredMetadata();
#endif
	}
	catch (AAFRESULT &rc)
	{
		stat = rc;

		// Cleanup after failure.
		if (_file)
		{
			_file->close();
		}

		if (NULL != _head)
		{
			_head->ReleaseReference();
			_head = 0;
		}
	}

	return stat;
}

aafVersionType_t theVersion = { 1,2};

AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::OpenNewModify (const aafCharacter * pFileName,
							aafUID_constptr pFileKind,
							aafUInt32 modeFlags,
							aafProductIdentification_t * pIdent)
{
	ImplAAFContentStorage	*pCStore = NULL;
	AAFRESULT stat = AAFRESULT_SUCCESS;

	if (! _initialized)
		return AAFRESULT_NOT_INITIALIZED;

	if (IsOpen())
		return AAFRESULT_ALREADY_OPEN;

	if (_file)
		return AAFRESULT_ALREADY_OPEN;

	if (! pFileName)
		return AAFRESULT_NULL_PARAM;

	if (! pIdent)
		return AAFRESULT_NULL_PARAM;

	if (! areAllModeFlagsDefined (modeFlags))
	  return AAFRESULT_BAD_FLAGS;

	if (! areAllModeFlagsSupported (modeFlags))
	  return AAFRESULT_NOT_IN_CURRENT_VERSION;

    if (!OMFile::creatable(pFileName))
      return AAFRESULT_NOT_CREATABLE;

	if (!OMFile::hasFactory(ENCODING(*pFileKind)))
	  return AAFRESULT_FILEKIND_NOT_REGISTERED;


	try
	{
	  // Create the header for the OM manager to use as the root
	  // for the file. Use the OMClassFactory interface for this 
	  // object because the dictionary has not been associated with
	  // a header yet (Chicken 'n Egg problem).
	  const OMClassId& soid =
		*reinterpret_cast<const OMClassId *>(&AUID_AAFHeader);
	  _head = static_cast<ImplAAFHeader *>(_factory->create(soid));
	  checkExpression(NULL != _head, AAFRESULT_BADHEAD);
		
		// Make sure the header is initialized with our previously created
		// dictionary.
		_head->SetDictionary(_factory);

		// Set the file format version.
		//
		// BobT Fri Jan 21 14:37:43 EST 2000: the default behavior is
		// that if the version isn't present, it's assumed to Version
		// 0.  Therefore if the current version is 0, don't write out
		// the property.  We do this so that hackers examining written
		// files won't know that a mechanism exists to mark future
		// incompatible versions, and so will work harder to make any
		// future changes compatible.
		if (sCurrentAAFObjectModelVersion)
		  {
			_head->SetObjectModelVersion(sCurrentAAFObjectModelVersion);
		  }

		// Add the ident to the header.
		checkResult(_head->AddIdentificationObject(pIdent));
		  
		// Set the byte order
		OMByteOrder byteOrder = hostByteOrder();
		if (byteOrder == littleEndian) {
			_byteOrder = 0x4949; // 'II'
		} else { // bigEndian
			_byteOrder = 0x4d4d; // 'MM'
		}
		_head->SetByteOrder(_byteOrder);
		_head->SetFileRevision (theVersion);

		//JeffB!!! We must decide whether def-only files have a content storage
		checkResult(_head->GetContentStorage(&pCStore));
		pCStore->ReleaseReference(); // need to release this pointer!
		pCStore = 0;

		// Attempt to create the file.
		_file = OMFile::openNewModify(pFileName,
									  _factory,
									  0,
									  byteOrder,
									  _head,
									  ENCODING(*pFileKind),
									  _metafactory);
		checkExpression(NULL != _file, AAFRESULT_INTERNAL_ERROR);

		// Restore the meta dictionary, it should be the same object
		// as _metafactory
		OMDictionary* mf = _file->dictionary();
		ASSERTU(mf == _metafactory);

		// Make sure all definitions are present in the meta dictionary
		ImplAAFMetaDictionary* d = dynamic_cast<ImplAAFMetaDictionary*>(mf);
		ASSERTU(d);
		checkResult( d->InstantiateAxiomaticDefinitions() );

		// Make sure properties that exist in builtin class
		// definitions but not the file's class definition,
		// are merged to the file's class definition.
		checkResult( d->MergeBuiltinClassDefs() );

		// Now that the file is open and the header has been
		// restored, complete the initialization of the
		// dictionary. We obtain the dictionary via the header
		// to give the persistence mechanism a chance to work.
		_factory->InitializeOMStorable
		    (_factory->GetBuiltinDefs()->cdDictionary());
		ImplAAFDictionary* dictionary = 0;
		HRESULT hr = _head->GetDictionary(&dictionary);
		if (hr != AAFRESULT_SUCCESS)
		  return hr;
		dictionary->InitBuiltins();

		dictionary->ReleaseReference();
		dictionary = 0;
		GetRevision(&_setrev);

#ifdef RESTORE_MXF_EXTENSIONS
		stat = restoreMirroredMetadata();
#endif
	}
	catch (AAFRESULT &rc)
	{
		stat = rc;

		// Cleanup after failure.
		if (_file)
		{
			_file->close();
		}

		if (NULL != _head)
		{
			_head->ReleaseReference();
			_head = 0;
		}
	}

	return stat;
}

AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::OpenNewModify (const aafCharacter * pFileName,
							aafUInt32 modeFlags,
							aafProductIdentification_t * pIdent)
{
	const aafUID_t *aafFileEncoding = NULL;
	if (modeFlags & AAF_FILE_MODE_USE_LARGE_SS_SECTORS)
	{
		aafFileEncoding	= &kAAFFileKind_Aaf4KBinary;
	}
	else
	{
		aafFileEncoding	= &kAAFFileKind_Aaf512Binary;
	}

  return OpenNewModify(pFileName, aafFileEncoding, modeFlags, pIdent);
}

AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::OpenTransient (aafProductIdentification_t * pIdent)
{
	if (! _initialized)
		return AAFRESULT_NOT_INITIALIZED;

	if (IsOpen())
		return AAFRESULT_ALREADY_OPEN;

	if (! pIdent)
		return AAFRESULT_NULL_PARAM;

	OMRawStorage * pOMRawStg = 0;

	try {
		//
		// Create a memory backed ImplAAFRawStorage
		//

		pOMRawStg = OMMemoryRawStorage::openNewModify ();
		if (!pOMRawStg) {
			throw AAFRESULT_NOMEMORY;
		}

		//
		// Create a file on top of the memory backed storage. 
		//

		_access = kAAFFileAccess_modify;
		_existence = kAAFFileExistence_new;

		// The following code fragment originated in
		// CreateAAFFileOnRawStorage().  It should probably be
		// factored out and made reusable.  Similar code
		// fragments appear in other ImplAAFFile methods as
		// well.

		// start of CreateAAFFileOnRawStorage fragment

		// Create and init the header;
		const OMClassId& soid =
		  *reinterpret_cast<const OMClassId *>(&AUID_AAFHeader);
		_head = static_cast<ImplAAFHeader *>(_factory->create(soid));
		checkExpression(NULL != _head, AAFRESULT_BADHEAD);
		_head->SetDictionary(_factory);
		if (sCurrentAAFObjectModelVersion) {
		  _head->SetObjectModelVersion(sCurrentAAFObjectModelVersion);
		}
		
		// Set the byte order
		OMByteOrder byteOrder = hostByteOrder();
		if (byteOrder == littleEndian) {
		  _byteOrder = 0x4949; // 'II'
		}
		else { // bigEndian
		  _byteOrder = 0x4d4d; // 'MM'
		}
		_head->SetByteOrder(_byteOrder);
		// FIXME FIXME - Hardcoded version!!!
		_head->SetFileRevision (theVersion);
		
		ImplAAFContentStorage * pCStore = 0;
 	        checkResult(_head->GetContentStorage(&pCStore));
		pCStore->ReleaseReference();
		pCStore = 0;
		
		// Attempt to create the file.
		_file = OMFile::openNewModify (pOMRawStg,
					       _factory,
					       0,
					       byteOrder,
					       _head,
					       ENCODING(kAAFFileKind_Aaf512Binary),
					       _metafactory);

		Open();

		// end of CreateAAFFileOnRawStorage fragment						  

		// Add the ident to the header.
		checkResult( _head->AddIdentificationObject(pIdent) );

	}
	catch ( AAFRESULT& ex ) {
		if ( pOMRawStg ) {
			delete pOMRawStg;
		}

		return ex;
	}
	return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::CreateAAFFileOnRawStorage
  (IAAFRawStorage * pRawStorage,
   aafFileExistence_t existence,
   aafFileAccess_t access,
   aafUID_constptr pFileKind,
   aafUInt32 modeFlags,
   aafProductIdentification_constptr pIdent)
{
	OMFile::OMLoadMode	loadMode = OMFile::eagerLoad;	// The default behavior

  if (! _initialized)
	return AAFRESULT_NOT_INITIALIZED;

  if (! pRawStorage)
	return AAFRESULT_NULL_PARAM;

  if (IsOpen())
	return AAFRESULT_ALREADY_OPEN;

  if (! areAllModeFlagsDefined (modeFlags))
	return AAFRESULT_BAD_FLAGS;

	if (! areAllModeFlagsSupported (modeFlags))
	  return AAFRESULT_NOT_IN_CURRENT_VERSION;

  if (modeFlags & AAF_FILE_MODE_LAZY_LOADING)
      loadMode = OMFile::lazyLoad;

  AAFRESULT hr;
  aafBoolean_t b = kAAFFalse;
  switch (access)
	{
	case kAAFFileAccess_read:
	  if (kAAFFileExistence_new == existence)
		return AAFRESULT_INVALID_PARAM;
	  b = kAAFFalse;
	  hr = pRawStorage->IsReadable (&b);
	  if (kAAFFalse == b)
		return AAFRESULT_NOT_READABLE;
	  break;
	case kAAFFileAccess_write:
	  if (kAAFFileExistence_existing == existence)
		return AAFRESULT_INVALID_PARAM;
	  b = kAAFFalse;
	  hr = pRawStorage->IsWriteable (&b);
	  if (kAAFFalse == b)
		return AAFRESULT_NOT_WRITEABLE;
	  break;
	case kAAFFileAccess_modify:
	  b = kAAFFalse;
	  hr = pRawStorage->IsWriteable (&b);
	  if (kAAFFalse == b)
		return AAFRESULT_NOT_WRITEABLE;
	  b = kAAFFalse;
	  hr = pRawStorage->IsReadable (&b);
	  if (kAAFFalse == b)
		return AAFRESULT_NOT_READABLE;
	  break;
	default:
	  return AAFRESULT_INVALID_PARAM;
	}

  switch (existence)
	{
	case kAAFFileExistence_new:
	  if (! pFileKind)
		return AAFRESULT_NULL_PARAM;

      if (!OMFile::hasFactory(ENCODING(*pFileKind)))
        return AAFRESULT_FILEKIND_NOT_REGISTERED;

	  break;
	case kAAFFileExistence_existing:
		// In this case, pFileKind selects the implementation used to read the existing file.
		// A NULL pFileKind argument was acceptable in previous toolkits when this selection was
		// not available.  Now, treat pFileKind as DontCare.
	  if (! pFileKind)
		  pFileKind = &kAAFFileKind_DontCare;

		// can specify DontCare or a required FileKind on open existing
      if ((*pFileKind) != kAAFFileKind_DontCare && !OMFile::hasFactory(ENCODING(*pFileKind)))
	      return AAFRESULT_FILEKIND_NOT_REGISTERED;

	  break;
	default:
	  return AAFRESULT_INVALID_PARAM;
	}

  _access = access;
  _existence = existence;

  AAFRESULT stat = AAFRESULT_SUCCESS;
  try
	{
	  // Create the OM storage...
	  OMRawStorage * pOMStg =
		new ImplAAFOMRawStorage (pRawStorage);
	  ASSERTU (pOMStg);

	  if (kAAFFileExistence_new == existence) // new
		{
		  if (! pIdent)
			return AAFRESULT_NULL_PARAM;

		  // Create the header for the OM manager to use as the root
		  // for the file. Use the OMClassFactory interface for this
		  // object because the dictionary has not been associated
		  // with a header yet (Chicken 'n Egg problem).
		  const OMClassId& soid =
			*reinterpret_cast<const OMClassId *>(&AUID_AAFHeader);
		  _head = static_cast<ImplAAFHeader *>(_factory->create(soid));
		  checkExpression(NULL != _head, AAFRESULT_BADHEAD);
		
		  // Make sure the header is initialized with our previously
		  // created dictionary.
		  _head->SetDictionary(_factory);

		  // Set the file format version.
		  //
		  // BobT Fri Jan 21 14:37:43 EST 2000: the default behavior
		  // is that if the version isn't present, it's assumed to
		  // Version 0.  Therefore if the current version is 0, don't
		  // write out the property.  We do this so that hackers
		  // examining written files won't know that a mechanism
		  // exists to mark future incompatible versions, and so will
		  // work harder to make any future changes compatible.
		  if (sCurrentAAFObjectModelVersion)
			{
			  _head->SetObjectModelVersion
				(sCurrentAAFObjectModelVersion);
			}

		  // Add the ident to the header.
		  checkResult(_head->AddIdentificationObject(pIdent));
		  
		  // Set the byte order
		  OMByteOrder byteOrder = hostByteOrder();
		  if (byteOrder == littleEndian)
			{
			  _byteOrder = 0x4949; // 'II'
			}
		  else
			{ // bigEndian
			  _byteOrder = 0x4d4d; // 'MM'
			}
		  _head->SetByteOrder(_byteOrder);
		  _head->SetFileRevision (theVersion);

		  //JeffB!!! We must decide whether def-only files have a
		  //content storage
		  ImplAAFContentStorage * pCStore = 0;
		  checkResult(_head->GetContentStorage(&pCStore));
		  pCStore->ReleaseReference(); // need to release this pointer!
		  pCStore = 0;

		  // Attempt to create the file.
		  const OMStoredObjectEncoding aafFileEncoding = ENCODING(*pFileKind);

		  if (kAAFFileAccess_read == access)
			{
			  // Can't open an new file for read only.
			  return AAFRESULT_INVALID_PARAM;
			}
		  if (kAAFFileAccess_modify == access)
			{
			  // NewModify
			  if (! OMFile::compatibleRawStorage (pOMStg,
												  OMFile::modifyMode,
												  aafFileEncoding))
				return AAFRESULT_INVALID_PARAM;
												  
			  _file = OMFile::openNewModify (pOMStg,
											 _factory,
											 0,
											 byteOrder,
											 _head,
											 aafFileEncoding,
											 _metafactory);
			}
		  else // write-only
			{
			  // NewWrite
			  if (! OMFile::compatibleRawStorage (pOMStg,
												  OMFile::writeOnlyMode,
												  aafFileEncoding))
				return AAFRESULT_INVALID_PARAM;
												  
			  _file = OMFile::openNewWrite (pOMStg,
											_factory,
											0,
											byteOrder,
											_head,
											aafFileEncoding,
											_metafactory);
			}
		}
	  else if (kAAFFileExistence_existing == existence) // Existing
		{
		  if (kAAFFileAccess_write == access)
			{
			  // Can't open an existing file for write only.
			  return AAFRESULT_INVALID_PARAM;
			}

		  const OMStoredObjectEncoding aafFileEncoding = ENCODING(*pFileKind);

		  if (kAAFFileAccess_modify == access)
			{
			  // ExistingModify
			  if (! pIdent)
				return AAFRESULT_NULL_PARAM;
			  _preOpenIdent = *pIdent;

			  _file = OMFile::openExistingModify (pOMStg,
												  _factory,
												  0,
												  loadMode,
												  aafFileEncoding,
												  _metafactory);
			}
		  else // read-only
			{
			  // ExistingRead
			  _file = OMFile::openExistingRead (pOMStg,
												_factory,
												0,
												loadMode,
												aafFileEncoding,

												_metafactory);
			}

		} // endif new/existing
	  else
		{
		  return AAFRESULT_INVALID_PARAM;
		}
	}

  catch (AAFRESULT &r)
	{
	  stat = r;
	}
  return stat;
}


AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::Open ()
{
  if (IsOpen() || IsClosed())
	return AAFRESULT_ALREADY_OPEN;

  if (! _file)
	return AAFRESULT_NOT_INITIALIZED;

  if (_existence == kAAFFileExistence_existing) {
    OMStoredObjectEncoding e;
    if (!OMFile::isRecognized(_file->rawStorage(), e))
      return AAFRESULT_NOT_AAF_FILE;

    if (!OMFile::compatibleStoredFormat(_file->rawStorage(),
                                        _file->accessMode(),
                                        e))
      return AAFRESULT_FILEREV_NOT_SUPP;

    if (OMFile::isBeingModified(_file->rawStorage(), e))
      return AAFRESULT_FILE_BEING_MODIFIED;

#if 0 // DICTIONARYLESSFILES
    OMStoredObjectEncoding MXFEncoding = ENCODING(kAAFFileKind_AafKlvBinary);
    if (e == MXFEncoding) {
      HRESULT r = _factory->RegisterMetaDictionaries();
      if (!SUCCEEDED(r)) return r;
    }
#endif
  }

  AAFRESULT stat = AAFRESULT_SUCCESS;

  try {
	  _file->open ();
	  // _isOpen = kAAFTrue;
  } catch (OMException& e) {
    delete _file;
    _file = 0;
    if (e.hasResult()) {
      throw e.result();
    } else {
      throw AAFRESULT_BADOPEN;
    }
  }

  try
	{

	  if (kAAFFileExistence_new == _existence) // new
		{
		  // Restore the meta dictionary, it should be the same object
		  // as _metafactory
		  OMDictionary* mf = _file->dictionary();
		  ASSERTU(mf == _metafactory);

		  // Make sure all definitions are present in the meta dictionary
		  ImplAAFMetaDictionary* d = dynamic_cast<ImplAAFMetaDictionary*>(mf);
		  ASSERTU(d);
		  checkResult( d->InstantiateAxiomaticDefinitions() );

		  // Make sure properties that exist in builtin class
		  // definitions but not the file's class definition,
		  // are merged to the file's class definition.
		  checkResult( d->MergeBuiltinClassDefs() );

		  // Now that the file is open and the header has been
		  // restored, complete the initialization of the
		  // dictionary. We obtain the dictionary via the header
		  // to give the persistence mechanism a chance to work.
		  _factory->InitializeOMStorable
		      (_factory->GetBuiltinDefs()->cdDictionary());
		  ImplAAFDictionary* dictionary = 0;
		  HRESULT hr = _head->GetDictionary(&dictionary);
		  if (hr != AAFRESULT_SUCCESS)
			return hr;
		  dictionary->InitBuiltins();
		  dictionary->ReleaseReference ();
		  dictionary = 0;
		}
	  else if (kAAFFileExistence_existing == _existence) // existing
		{
		// Restore the meta dictionary, it should be the same object
		// as _metafactory
		OMDictionary* mf = _file->dictionary();
		ASSERTU(mf == _metafactory);

		// Make sure all definitions are present in the meta dictionary
		ImplAAFMetaDictionary* d = dynamic_cast<ImplAAFMetaDictionary*>(mf);
		ASSERTU(d);
		checkResult( d->InstantiateAxiomaticDefinitions() );

		// Make sure properties that exist in builtin class
		// definitions but not the file's class definition,
		// are merged to the file's class definition.
		checkResult( d->MergeBuiltinClassDefs() );

		  // Get the byte order
		  OMByteOrder byteOrder = _file->byteOrder();
		  if (byteOrder == littleEndian)
			{
			  _byteOrder = 0x4949; // 'II'
			}
		  else
			{ // bigEndian
			  _byteOrder = 0x4d4d; // 'MM'
			}

		  // Restore the header.
		  bool regWasEnabled = _factory->SetEnableDefRegistration (false);
		  OMStorable* head = _file->restore();
		  _head = dynamic_cast<ImplAAFHeader *>(head);
		  _head->SetFile(this);
		
		  // Check for file format version.
		  if (_head->IsObjectModelVersionPresent())
			{
			  // If property isn't present, the default version is 0,
			  // which is always (supposed to be) legible.  If it is
			  // present, find out the version number to determine if
			  // the file is legible.
			  // If file version is higher than the version understood
			  // by this toolkit this file cannot be read.
			  checkExpression(_head->GetObjectModelVersion() <=
							  static_cast<aafUInt32>(sCurrentAAFObjectModelVersion),
							  AAFRESULT_FILEREV_DIFF);
			}
		  // Now that the file is open and the header has been
		  // restored, complete the initialization of the
		  // dictionary. We obtain the dictionary via the header
		  // to give the persistence mechanism a chance to work.
		  ImplAAFDictionary* dictionary = 0;
		  HRESULT hr = _head->GetDictionary(&dictionary);
		  if (hr != AAFRESULT_SUCCESS)
			return hr;
		  _factory->SetEnableDefRegistration (regWasEnabled);
		  if (!_factory->IsOMStorableInitialized())
		  {
			// Finish initialization of the OMStorable part of the dictionary
			// for files that do not contain an AAF dictionary, such as
			// foreign MXF files.
			// Note the difference from initializing the dictionary object for
			// new files: the call to InitializeOMStorable() is done _after_
			// calling GetDictionary(). This is to ensure that when reading
			// an existing file the dictionary is initialized from the file
			// if the file contains it. And if the file is opened in lazy
			// loading mode the dictionary will not be restored until it is
			// accessed, for example, via GetDictionary().
			_factory->InitializeOMStorable
				  (_factory->GetBuiltinDefs()->cdDictionary());
		  }
		  dictionary->InitBuiltins();
		  dictionary->ReleaseReference ();
		  dictionary = 0;

		  if (IsWriteable())
			{
			  // Update the file format version
			  if (sCurrentAAFObjectModelVersion)
				{
				  _head->SetObjectModelVersion(sCurrentAAFObjectModelVersion);
				}

			  // NOTE: If modifying an existing file WITHOUT an IDNT
			  // object, add a dummy IDNT object to indicate that this
			  // program was not the creator.
			  //
			  aafUInt32	numIdent = 0;
			  checkResult(_head->CountIdentifications(&numIdent));
			  if(numIdent == 0)
				{
				  _head->AddIdentificationObject
					((aafProductIdentification_t *)NULL);
				}
			  // Now, always add the information from THIS application
			  _head->AddIdentificationObject(&_preOpenIdent);
			}
		}
	  else
		{
		  ASSERTU (0);
		}

#ifdef RESTORE_MXF_EXTENSIONS
		stat = restoreMirroredMetadata();
#endif
	}

  catch (AAFRESULT &r)
	{
	  stat = r;
	}
  return stat;
}


AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::Save ()
{
	return Save(true);
}


AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::SaveIntermediate ()
{
	return Save(false);
}


AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::SaveCopyAs (ImplAAFFile * pDestFile)
{
  // Save all objects in this file to pDestFile.  Implemented by
  // cloning the source header's content store and
  // _identificationList.  The source identification objects are
  // appended to pDstFile's existing identification list. The
  // destination header's _byteOrder, _lastModified, _dictionary,
  // _fileRef, and _objectModelVersion are not cloned - they all take
  // care of themselves.  The destination dictionary is updated as a
  // side effect of cloning the content store and ident list.

  if (! pDestFile)
	return AAFRESULT_NULL_PARAM;

  if ( this == pDestFile ) {
    // The call is redundant.  Just save the file.
    return Save();
  }

  try {
    ImplAAFSmartPointer<ImplAAFHeader> spDstHeader;
    checkResult( pDestFile->GetHeader(&spDstHeader) );

    ImplAAFSmartPointer<ImplAAFContentStorage> spDstContentStore;
    checkResult( spDstHeader->GetContentStorage(&spDstContentStore) );

    aafUInt32 numDstMobs = 0;
    checkResult( spDstContentStore->CountMobs(0, &numDstMobs) );

    aafUInt32 numDstEssenceData = 0;
    checkResult( spDstContentStore->CountEssenceData(&numDstEssenceData) );

    if ( numDstMobs || numDstEssenceData ) {
      throw AAFRESULT_OPERATION_NOT_PERMITTED;
    }

    ImplAAFSmartPointer<ImplAAFDictionary> spDstDict;
    checkResult( spDstHeader->GetDictionary(&spDstDict) );

    // Merge the dictionary
    {
      ImplAAFSmartPointer<ImplAAFDictionary> spSrcDict;
      checkResult( GetDictionary(&spSrcDict) );

      checkResult( spSrcDict->MergeTo( spDstDict ) );
    }

    // Clone the content store.
    {
      ImplAAFSmartPointer<ImplAAFContentStorage> spSrcContentStore;
      checkResult( _head->GetContentStorage( &spSrcContentStore ) );

      OMStorable* pNewDstStorable = spSrcContentStore->shallowCopy(static_cast<ImplAAFDictionary*>(spDstDict));
      ImplAAFContentStorage* pNewDstStorage = dynamic_cast<ImplAAFContentStorage*>(pNewDstStorable);
      if ( !pNewDstStorage ) {
		throw AAFRESULT_BAD_TYPE;
      }
      
      spDstHeader->SetContentStorage( pNewDstStorage );

      spSrcContentStore->deepCopyTo( pNewDstStorable, 0 );
      pNewDstStorage->onCopy( 0 );

      // Object created by shallowCopy() is reference counted.
      // Since we already attached it and its container has its
      // own reference to it, we should release our reference.
      pNewDstStorage->ReleaseReference();
      pNewDstStorage = 0;
    }

    // Clone the ident list.
    {
      aafUInt32 numSrcIdents = 0;
      checkResult( _head->CountIdentifications(&numSrcIdents) );
      
      unsigned int i;
      for( i = 0; i < numSrcIdents; ++i ) {

	ImplAAFSmartPointer<ImplAAFIdentification> spSrcIdent;
	checkResult( _head->GetIdentificationAt( i, &spSrcIdent ) );
	
	OMStorable* pNewDstStorable = spSrcIdent->shallowCopy(static_cast<ImplAAFDictionary*>(spDstDict));
	ImplAAFIdentification* pNewDstIdent = dynamic_cast<ImplAAFIdentification*>(pNewDstStorable);
	if ( !pNewDstIdent ) {
	  throw AAFRESULT_BAD_TYPE;
	}
	
	checkResult( spDstHeader->AppendIdentification( pNewDstIdent ) );

	pNewDstIdent->onCopy( 0 );
	spSrcIdent->deepCopyTo( pNewDstIdent, 0 );

	// Object created by shallowCopy() is reference counted.
	// Since we already attached it and its container has its
	// own reference to it, we should release our reference.
	pNewDstIdent->ReleaseReference();
	pNewDstIdent = 0;
      }
    }

  }
  catch( const HRESULT& ex ) {
    return ex;
  }

  return pDestFile->Save();
}


AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::Revert ()
{
	if (! _initialized)
		return AAFRESULT_NOT_INITIALIZED;

	if (!IsOpen())
		return AAFRESULT_NOT_OPEN;

        ASSERTU(_file);
        _file->revert();

	return AAFRESULT_SUCCESS;
}


ImplAAFFile::ImplAAFFile () :
		_cookie(0),
		_file(0),
		_factory(NULL),
		_metafactory(NULL),
		_byteOrder(0),
		// _openType(kOmUndefined),
		_head(NULL),
		_semanticCheckEnable(kAAFFalse),
		_initialized(kAAFFalse),
		// _isOpen(kAAFFalse),
		_existence (0),
		_access (kAAFFileAccess_none),
		_preOpenIdent(kNullIdent)
{
}


ImplAAFFile::~ImplAAFFile ()
{
	// Close() may throw but the destructor shouldn't.
	try
	{
		if (IsOpen())
			Close();
	}
	catch(...)
	{
	}

	InternalReleaseObjects();

	// cleanup the container.
	if (_factory)
	{
		_factory->ReleaseReference();
		_factory = NULL;
	}

	if (_metafactory)
	{
		_metafactory->ReleaseReference();
		_metafactory = NULL;
	}

	// cleanup the OM File.
	if (_file)
	{
		delete _file;
		_file = NULL;
	}
}

void ImplAAFFile::InternalReleaseObjects()
{
}

AAFRESULT ImplAAFFile::saveMirroredMetadata(void)
{
  AAFRESULT hr = AAFRESULT_SUCCESS;

  ASSERTU(_file != 0);
  if (OMKLVStoredObject::hasMxfStorage(_file)) {
    OMMXFStorageBase*  p_storage = OMKLVStoredObject::mxfStorage( _file );
    ASSERTU( p_storage != 0 );

    // Operational pattern
    //
    aafUID_t  operational_pattern;
    hr = _head->GetOperationalPattern( &operational_pattern );
    if( hr == AAFRESULT_SUCCESS )
    {
      OMKLVKey operational_pattern_label;
      convert(operational_pattern_label,
	      *(OMUniqueObjectIdentification*)&operational_pattern );

      p_storage->setOperationalPattern( operational_pattern_label );
    }
    else if( hr == AAFRESULT_PROP_NOT_PRESENT )
    {
      // Ignore the error value
      hr = AAFRESULT_SUCCESS;
      // should set a value meaning unconstrained here
    }

    // Essence containers
    ImplAAFHeader* p_header = _head;

    aafUInt32  essence_container_count = 0;
    hr = p_header->CountEssenceContainers( &essence_container_count );
    if( hr == AAFRESULT_SUCCESS && essence_container_count > 0 )
    {
        aafUID_t* p_essence_containers =
            new aafUID_t[ essence_container_count ];

        hr = p_header->GetEssenceContainers( essence_container_count,
                                                 p_essence_containers );
        if( hr == AAFRESULT_SUCCESS )
        {
            for( aafUInt32 i=0; i<essence_container_count; i++ )
            {
                OMKLVKey essence_container_label;
                convert( essence_container_label,
                         *(OMUniqueObjectIdentification*)(p_essence_containers+i) );

                if( ! p_storage->containsEssenceContainerLabel( essence_container_label ) )
                {
                    p_storage->addEssenceContainerLabel( essence_container_label );
                }
            }
        }
        else if( hr == AAFRESULT_PROP_NOT_PRESENT )
        {
            // Ignore the error value
            hr = AAFRESULT_SUCCESS;
        }

        delete[] p_essence_containers;
        p_essence_containers = 0;
      }
      else if( hr == AAFRESULT_PROP_NOT_PRESENT )
      {
          // Ignore the error value
          hr = AAFRESULT_SUCCESS;
      }
    }

    return hr;
 }

AAFRESULT ImplAAFFile::restoreMirroredMetadata(void)
{
  AAFRESULT hr = AAFRESULT_SUCCESS;

  ASSERTU(_file != 0);
  if (OMKLVStoredObject::hasMxfStorage(_file))
  {
    OMMXFStorageBase*  p_storage = OMKLVStoredObject::mxfStorage( _file );
    ASSERTU( p_storage != 0 );

    ImplAAFHeader* p_header = _head;

	aafUID_t  operational_pattern;
    convert( *(OMUniqueObjectIdentification*)&operational_pattern,
             p_storage->operationalPattern() );

    hr = p_header->SetOperationalPattern( operational_pattern );


    // EssenceContainers
    OMMXFStorageBase::LabelSetIterator*  iter = p_storage->essenceContainerLabels();
    while( ++(*iter) )
    {
        OMKLVKey  essence_container_label = iter->value();

        aafUID_t  essence_container;
        convert( *(OMUniqueObjectIdentification*)&essence_container,
                 essence_container_label );

        aafBoolean_t  present = kAAFFalse;
        p_header->IsEssenceContainerPresent( essence_container,
                                            &present );
        if( !present )
        {
            p_header->AddEssenceContainer( essence_container );
        }
    }

    delete iter;
  }

  return hr;
}

//***********************************************************
// METHOD NAME: Close()
//
// DESCRIPTION:
// @mfunc AAFRESULT | AAFFile | Close |
// Closes an AAF file, saving the result.
// @end
//
//
AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::Close ()
{
	if (! _initialized)
		return AAFRESULT_NOT_INITIALIZED;

	if (!IsOpen())
		return AAFRESULT_NOT_OPEN;


	// Release all of the pointers that we created or copied
	// during the create or open methods.
	InternalReleaseObjects();

	// Close the OM file.
	_file->close();

	// Whenever a file is created or opened a new container is
	// created.  If we don't want to leak the container object
	// and any objects in the associated OMFile object we had
	// better delete the container object here.
	//
	// BobT: Keep this around longer!  We'll need GetBits later...
	// delete _file;
	// _file = 0;
  
	// Release the last reference to the header of the file. 
	// We need to release the header after the file is closed so
	// that the OMFile object within the container can safely
	// use its reference to its root (a.k.a. header).
	if (0 != _head)
	{
		_head->ReleaseReference();
		_head = 0;
	}

	_cookie = 0;
	// _isOpen = kAAFFalse;
	// BobT: don't set this, so we'll remember what open type this
	// file had
	// _openType = kOmUndefined;

	return(AAFRESULT_SUCCESS);
}


//***********************************************************
// METHOD NAME: GetRevision()
//
// DESCRIPTION:
// @mfunc AAFRESULT | AAFFile | GetRevision |
// Get the revision of the current AAF file.
// @end
// 
AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::GetRevision (aafFileRev_t *  rev)
{
	if (! _initialized)
		return AAFRESULT_NOT_INITIALIZED;

	if (! rev)
		return AAFRESULT_NULL_PARAM;

	ImplAAFHeader* header;
	AAFRESULT hr = GetHeader(&header);
	if (hr != AAFRESULT_SUCCESS)
		  return hr;

	aafUInt32 ObjectModelVersion = 0;
	if (header->IsObjectModelVersionPresent())
			ObjectModelVersion = header->GetObjectModelVersion();
	header->ReleaseReference();
	header=0;

	*rev = ObjectModelVersion;

  return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
ImplAAFFile::GetHeader (ImplAAFHeader ** header)
{
  if (! header)
	return AAFRESULT_NULL_PARAM;

  if (!IsOpen())
	return AAFRESULT_NOT_OPEN;

  *header = _head;

  // We are returning a copy of the reference counted object.
  if (_head)
	_head->AcquireReference();

  return(AAFRESULT_SUCCESS);
}

AAFRESULT STDMETHODCALLTYPE
    ImplAAFFile::GetDictionary (ImplAAFDictionary ** ppDictionary) const
{
	if (! ppDictionary)
	{
		return AAFRESULT_NULL_PARAM;
	}

	return(_head->GetDictionary(ppDictionary));
}

OMFile * ImplAAFFile::omFile (void)
{
  ASSERTU (IsOpen());
  ASSERTU (_file);
  return _file;
}

void ImplAAFFile::removeFactories(void)
{
  OMFile::removeAllFactories();
  OMFile::removeAllDefaultEncodings();
}

bool ImplAAFFile::IsReadable () const
{
  ASSERTU (_file);
  return _file->isReadable();
}

bool ImplAAFFile::IsWriteable () const
{
  ASSERTU (_file);
  return _file->isWritable();
}

bool ImplAAFFile::IsOpen () const
{
  if (!_file)
	return false;
  ASSERTU (_file);
  return _file->isOpen();
}

bool ImplAAFFile::IsClosed () const
{
  if (!_file)
	return false;
  ASSERTU (_file);
  return _file->isClosed();
}

OMRawStorage * ImplAAFFile::RawStorage ()
{
  OMRawStorage * r = 0;
  ASSERTU (_file);
  r = _file->rawStorage ();
  ASSERTU (r);
  return r;
}

AAFRESULT ImplAAFFile::Save (bool finalize)
{
	if (! _initialized)
		return AAFRESULT_NOT_INITIALIZED;

	if (!IsOpen())
		return AAFRESULT_NOT_OPEN;

	if (! _file)
		return AAFRESULT_NOT_OPEN;
	if (! _file->isOpen())
		return AAFRESULT_NOT_OPEN;

	// If any new modes are added then the following line will
	// have to be updated.
	if (IsWriteable ()) {
	  // Assure no registration of def objects in dictionary during
	  // save operation
	  ImplAAFDictionarySP dictSP;
	  AAFRESULT hr = _head->GetDictionary(&dictSP);
	  if (AAFRESULT_FAILED (hr))
		return hr;
	  dictSP->AssureClassPropertyTypes ();
	  bool regWasEnabled = dictSP->SetEnableDefRegistration (false);

	  // OMFile::save() allows us to pass a client context to be
	  // regurgitated to the OMStorable::onSave() callback.  We'll use
	  // it to pass the AUID of the latest generation.
	  ImplAAFIdentificationSP pLatestIdent;
	  hr = _head->GetLastIdentification (&pLatestIdent);
	  if (AAFRESULT_FAILED (hr)) return hr;
	  aafUID_t latestGen;
	  hr = pLatestIdent->GetGenerationID (&latestGen);
	  if (AAFRESULT_FAILED (hr)) return hr;

	  hr = saveMirroredMetadata();
	  if (AAFRESULT_FAILED (hr))
		return hr;

	  // Record the fact that this file was modified
	  _head->SetModified();

	  _file->saveFile(finalize, &latestGen);

	  dictSP->SetEnableDefRegistration (regWasEnabled);

	} else {
	  return AAFRESULT_WRONG_OPENMODE;
	}

	return AAFRESULT_SUCCESS;
}


// The default structured storage encodings ids from the point of view
// of the OM.
#define AAF512Encoding ENCODING(kAAFFileKind_Aaf512Binary)
#define AAF4KEncoding  ENCODING(kAAFFileKind_Aaf4KBinary)

// The implementation specific structured storage encoding ids from
// the point of view of the OM.
#define AAFM512Encoding ENCODING(kAAFFileKind_AafM512Binary)
#define AAFS512Encoding ENCODING(kAAFFileKind_AafS512Binary)
#define AAFG512Encoding ENCODING(kAAFFileKind_AafG512Binary)

#define AAFM4KEncoding  ENCODING(kAAFFileKind_AafM4KBinary)
#define AAFS4KEncoding  ENCODING(kAAFFileKind_AafS4KBinary)
#define AAFG4KEncoding  ENCODING(kAAFFileKind_AafG4KBinary)

#define AAFKLVEncoding  ENCODING(kAAFFileKind_AafKlvBinary)

#define AAFXMLEncoding  ENCODING(kAAFFileKind_AafXmlText)

// File signatures from the point of view of the OM.
#define Signature_SSBin_512 ENCODING(kAAFSignature_Aaf512Binary)
#define Signature_SSBin_4K  ENCODING(kAAFSignature_Aaf4KBinary)
#define Signature_XML       ENCODING(kAAFSignature_AafXmlText)


void ImplAAFFile::registerStructuredStorageFactories(void)
{
#ifdef OM_STRUCTURED_STORAGE
  // the signature stored in all AAF SS (512) files
  // note this is not a properly-formed SMPTE label, but this is legacy
  const aafUID_t kAAFSignature_Aaf512Binary = kAAFFileKind_Aaf512Binary;
  
  // the signature stored in all AAF SS (4096) files
  // [060e2b34.0302.0101.0d010201.02000000]
  // This defined in one of the SMPTE specs. Don't change it.
  const aafUID_t kAAFSignature_Aaf4KBinary =
    { 0x0d010201, 0x0200, 0x0000, { 0x06, 0x0e, 0x2b, 0x34, 0x03, 0x02, 0x01, 0x01 } };

  // Choose a default encode based on the priority given to the
  // various implementations in the event more than one is active.
#if defined(OM_USE_SCHEMASOFT_SS)
  const OMStoredObjectEncoding default_Aaf512Binary = AAFS512Encoding;
  const OMStoredObjectEncoding default_Aaf4KBinary  = AAFS4KEncoding;
#elif defined(OM_USE_WINDOWS_SS)
  const OMStoredObjectEncoding default_Aaf512Binary = AAFM512Encoding;
  const OMStoredObjectEncoding default_Aaf4KBinary  = AAFM4KEncoding;
#elif defined(OM_USE_GSF_SS)
  const OMStoredObjectEncoding default_Aaf512Binary = AAFG512Encoding;
  const OMStoredObjectEncoding default_Aaf4KBinary  = AAFG4KEncoding;
#endif

  // First, register the default encoding mappings.
  OMFile::registerDefaultEncoding( AAF512Encoding, default_Aaf512Binary );
  OMFile::registerDefaultEncoding( AAF4KEncoding,  default_Aaf4KBinary );

  // Structured Storage encodings are registered by defining the OM_USE_xxx_SS preprocessor
  // directives and more than one can be registered and available at runtime.
  // The default encoding is set in mapStructuredStorageFileKind_DefaultToActual().

#if defined(OM_USE_WINDOWS_SS)

  OMFile::registerFactory( new OMMS_SSStoredObjectFactory(AAFM512Encoding,
							  Signature_SSBin_512,
							  L"AAF-M",
							  L"AAF Microsoft SS"));
  OMFile::registerFactory( new OMMS_SSStoredObjectFactory(AAFM4KEncoding,
							  Signature_SSBin_4K,
							  L"AAF-M4K",
							  L"AAF Microsoft 4K"));

#endif

#if defined(OM_USE_SCHEMASOFT_SS)
	// The SchemaSoft precompiled library is only available on these platforms:
	// Microsoft, Mac OS X, Irix, Linux, and Solaris
	OMFile::registerFactory( new OMSS_SSStoredObjectFactory(AAFS512Encoding,
								Signature_SSBin_512,
								L"AAF-S",
								L"AAF SchemaSoft SS"));
	OMFile::registerFactory( new OMSS_SSStoredObjectFactory(AAFS4KEncoding,
								Signature_SSBin_4K,
								L"AAF-S4K",
								L"AAF SchemaSoft 4K"));
#endif

#if defined(OM_USE_GSF_SS)

	OMFile::registerFactory( new OMGSF_SSStoredObjectFactory(AAFG512Encoding,
								 Signature_SSBin_512,
								 L"AAF-G",
								 L"AAF GSF SS"));
	OMFile::registerFactory( new OMGSF_SSStoredObjectFactory(AAFG4KEncoding,
								 Signature_SSBin_4K,
								 L"AAF-G4K",
								 L"AAF GSF 4K"));
#endif


#endif // OM_STRUCTURED_STORAGE
}

void ImplAAFFile::registerFactories(void)
{
  // Structured storage has numerous platform dependencies and
  // requires conditional compilation. That is isolated in the
  // following function.
  registerStructuredStorageFactories();

  // JPT REVIEW - Why is this all zeros?
  // no signature is required for AAF-XML 
  const aafUID_t kAAFSignature_AafXmlText =
    { 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };
  
  // The XML and KLV encodings have no platform dependencies and have
  // single implementations, no conditional compilation required.

  OMFile::registerFactory(
                          new OMXMLStoredObjectFactory(AAFXMLEncoding,
                                                       Signature_XML,
                                                       L"XML",
                                                       L"AAF XML"));
  OMFile::registerFactory(
                          new OMKLVStoredObjectFactory(AAFKLVEncoding,
                                                       AAFKLVEncoding,
                                                       L"KLV",
                                                       L"AAF KLV"));

}
