/************************************************\
*												*
* Advanced Authoring Format						*
*												*
* Copyright (c) 1998-1999 Avid Technology, Inc. *
* Copyright (c) 1998-1999 Microsoft Corporation *
*												*
\************************************************/
#ifndef __ImplAAFDictionary_h__
#include "ImplAAFDictionary.h"
#endif



#ifndef __ImplAAFClassDef_h__
#include "ImplAAFClassDef.h"
#endif

#ifndef __ImplEnumAAFClassDefs_h__
#include "ImplEnumAAFClassDefs.h"
#endif

#ifndef __ImplAAFTypeDef_h__
#include "ImplAAFTypeDef.h"
#endif

#ifndef __ImplEnumAAFTypeDefs_h__
#include "ImplEnumAAFTypeDefs.h"
#endif

#ifndef __ImplAAFDataDef_h__
#include "ImplAAFDataDef.h"
#endif

#ifndef __ImplEnumAAFDataDefs_h__
#include "ImplEnumAAFDataDefs.h"
#endif

#ifndef __ImplAAFOperationDef_h__
#include "ImplAAFOperationDef.h"
#endif

#ifndef __ImplAAFParameterDef_h__
#include "ImplAAFParameterDef.h"
#endif

#ifndef __ImplEnumAAFOperationDefs_h__
#include "ImplEnumAAFOperationDefs.h"
#endif

#ifndef __ImplEnumAAFCodecDefs_h__
#include "ImplEnumAAFCodecDefs.h"
#endif

#ifndef __ImplEnumAAFContainerDefs_h__
#include "ImplEnumAAFContainerDefs.h"
#endif

#ifndef __ImplEnumAAFInterpolationDefs_h__
#include "ImplEnumAAFInterpolationDefs.h"
#endif


#include "AAFStoredObjectIDs.h"
#include "AAFPropertyIDs.h"

#include "ImplAAFObjectCreation.h"


#ifndef __ImplAAFBaseClassFactory_h__
#include "ImplAAFBaseClassFactory.h"
#endif

#ifndef __ImplAAFBuiltins_h__
#include "ImplAAFBuiltins.h"
#endif



#include "ImplAAFMob.h"

#include <assert.h>
#include <string.h>
#include "aafErr.h"
#include "AAFUtils.h"
#include "AAFDataDefs.h"

extern "C" const aafClassID_t CLSID_EnumAAFDefObjects;
extern "C" const aafClassID_t CLSID_EnumAAFOperationDefs;
extern "C" const aafClassID_t CLSID_EnumAAFParameterDefs;
extern "C" const aafClassID_t CLSID_EnumAAFTypeDefs;
extern "C" const aafClassID_t CLSID_EnumAAFCodecDefs;
extern "C" const aafClassID_t CLSID_EnumAAFContainerDefs;
extern "C" const aafClassID_t CLSID_EnumAAFInterpolationDefs;
extern "C" const aafClassID_t CLSID_EnumAAFDataDefs;

extern aafUID_t gTypeID_AUID;
extern aafUID_t gTypeID_UInt8;
extern aafUID_t gTypeID_UInt16;
extern aafUID_t gTypeID_Int16;
extern aafUID_t gTypeID_UInt32;
extern aafUID_t gTypeID_Int32;
extern aafUID_t gTypeID_Int8;
extern aafUID_t gTypeID_Int64;
extern aafUID_t gTypeID_ObjRef;
extern aafUID_t gTypeID_ObjRefArray;
extern aafUID_t gTypeID_AUIDArray;
extern aafUID_t gTypeID_UInt8Array;
extern aafUID_t gTypeID_UInt8Array8;

extern aafUID_t gClassID_Object;


ImplAAFDictionary::ImplAAFDictionary ()
: _operationDefinitions(PID_Dictionary_OperationDefinitions, "OperationDefinitions"), 
  _parameterDefinitions(PID_Dictionary_ParameterDefinitions, "ParameterDefinitions"),
  _codecDefinitions(PID_Dictionary_CodecDefinitions, "CodecDefinitions"),
  _containerDefinitions(PID_Dictionary_ContainerDefinitions, "ContainerDefinitions"),
  _typeDefinitions      (PID_Dictionary_TypeDefinitions,      "TypeDefinitions"),
  _classDefinitions      (PID_Dictionary_ClassDefinitions,    "ClassDefinitions"),
  _interpolationDefinitions      (PID_Dictionary_InterpolationDefinitions,    "InterpolationDefinitions"),
  _dataDefinitions      (PID_Dictionary_DataDefinitions,    "DataDefinitions"),
  _pBuiltins (0)
{
  _persistentProperties.put (_operationDefinitions.address());
  _persistentProperties.put (_parameterDefinitions.address());
  _persistentProperties.put (_typeDefinitions.address());
  _persistentProperties.put (_classDefinitions.address());
  _persistentProperties.put(_codecDefinitions.address());
  _persistentProperties.put(_containerDefinitions.address());
  _persistentProperties.put(_interpolationDefinitions.address());
  _persistentProperties.put(_dataDefinitions.address());
}


ImplAAFDictionary::~ImplAAFDictionary ()
{
  size_t i;
  // Release the _codecDefinitions
  size_t size = _codecDefinitions.getSize();
  for (i = 0; i < size; i++)
	{
		ImplAAFCodecDef *pPlug = _codecDefinitions.setValueAt(0, i);
		if (pPlug)
		{
		  pPlug->ReleaseReference();
		}
	}

	size_t containerDefSize = _containerDefinitions.getSize();
	for (i = 0; i < containerDefSize; i++)
	{
		ImplAAFContainerDef *pPlug = _containerDefinitions.setValueAt(0, i);
		if (pPlug)
		{
		  pPlug->ReleaseReference();
		}
	}

	size_t typeDefSize = _typeDefinitions.getSize();
	for (i = 0; i < typeDefSize; i++)
	{
		ImplAAFTypeDef *pPlug = _typeDefinitions.setValueAt(0, i);
		if (pPlug)
		{
		  pPlug->ReleaseReference();
		}
	}

  size_t classDefSize = _classDefinitions.getSize();
  for (i = 0; i < classDefSize; i++)
	{
	  ImplAAFClassDef *pClass = _classDefinitions.setValueAt(0, i);
	  if (pClass)
		{
		  pClass->ReleaseReference();
		}
	}
  size_t opsDefSize = _operationDefinitions.getSize();
  for (i = 0; i < opsDefSize; i++)
	{
	  ImplAAFOperationDef *pOps = _operationDefinitions.setValueAt(0, i);
	  if (pOps)
		{
		  pOps->ReleaseReference();
		}
	}
  size_t parmDefSize = _parameterDefinitions.getSize();
  for (i = 0; i < parmDefSize; i++)
	{
	  ImplAAFParameterDef *pParm = _parameterDefinitions.setValueAt(0, i);
	  if (pParm)
		{
		  pParm->ReleaseReference();
		}
	}
  size_t interpDefSize = _interpolationDefinitions.getSize();
  for (i = 0; i < interpDefSize; i++)
	{
	  ImplAAFInterpolationDef *pInterp = _interpolationDefinitions.setValueAt(0, i);
	  if (pInterp)
		{
		  pInterp->ReleaseReference();
		}
	}

  size_t dataDefSize = _dataDefinitions.getSize();
  for (i = 0; i < dataDefSize; i++)
	{
	  ImplAAFDataDef *pDDef = _dataDefinitions.setValueAt(0, i);
	  if (pDDef)
		{
		  pDDef->ReleaseReference();
		}
	}

  if (_pBuiltins)
	{
	  delete _pBuiltins;
	  _pBuiltins = 0;
	}
}



//
// Factory function for all built-in classes.
//
static ImplAAFObject* CreateBaseClassInstance(const aafUID_t* pAUID) 
{

  // Lookup the code class id for the given stored object id.
  const aafClassID_t* id = ImplAAFBaseClassFactory::LookupClassID(pAUID);
  if (NULL == id)
    return NULL;
  
  // Attempt to create the corresponding storable object.
  ImplAAFRoot *impl = ::CreateImpl(*id);
  if (NULL == impl)
  { // This is a serious programming error. A stored object id was found in the file
	  // with a known base class id but no base object could be created.
    assert(NULL != impl);
    return NULL;
  }

  // Make sure that the object we created was actually one of our
  // ImplAAFObject derived classes.
  ImplAAFObject* object = dynamic_cast<ImplAAFObject*>(impl);
  if (NULL == object)
  { // Not a valid object. Release the pointer so we don't leak memory.
    impl->ReleaseReference();
    impl = 0;
    assert(NULL != object);
	  return NULL;
  }

  return object;
}


// Factory method for creating a Dictionary.
ImplAAFDictionary *ImplAAFDictionary::CreateDictionary(void)
{
  // Create a dictionary.
  ImplAAFDictionary * pDictionary = NULL;
  
  
  pDictionary = static_cast<ImplAAFDictionary *>(::CreateBaseClassInstance(&AUID_AAFDictionary));
  assert(NULL != pDictionary);
  if (NULL != pDictionary)
  {
    // If we created a dictionary then give it a reference to a factory
    // (dictionary) to satisfy the OMStorable class invariant: Every OMStorabe
    // must have a reference to a factory. Since the dictionary is not created
    // by the OMClassFactory interface we just set the factory to "itself".
    //
    pDictionary->setClassFactory(pDictionary);
  }
  
  return pDictionary;
}


//
// Create an instance of the appropriate derived class, given the class id.
//  This method implements the OMClassFactory interface.
//
OMStorable* ImplAAFDictionary::create(const OMClassId& classId) const
{
  const aafUID_t* pAUID  = reinterpret_cast<const aafUID_t*>(&classId);
  OMStorable *result = 0;

  // Is this a request to create the dictionary?
  if (memcmp(pAUID, &AUID_AAFDictionary, sizeof(aafUID_t)) == 0)
  { // The result is just this instance.
    result = const_cast<ImplAAFDictionary*>(this);
    // Bump the reference count.
    AcquireReference();
  } 
  else
  { // Create an instance of the class corresponsing to the given
    // stored object id.

    // Try the built-in dictionary first.
    //
    result = ::CreateBaseClassInstance(pAUID);
    if (result == 0)
    {
      // Not in the built-in dictionary, try the current dictionary.
      // TBD
      //
    }
  }

  // If we created an object then give it a reference to the factory
  // (dictionary) that was used to created it.
  //
  if (NULL != result && ((ImplAAFDictionary *)result != this))
  {
    result->setClassFactory(this);
  }

  return result;
}


// Creates a single uninitialized AAF object of the class associated 
  // with a specified stored object id.
AAFRESULT STDMETHODCALLTYPE 
  ImplAAFDictionary::CreateInstance (
    // Class identifier (AUID) of the stored object. This is the
    // corresponding SMPTE identifier (as a GUID) for all predefined
    // built-in classes.
    aafUID_t * pAUID,

    // Address of output variable that receives the 
    // object pointer requested in pAUID
    ImplAAFObject ** ppvObject)
{
  if (NULL == pAUID || NULL == ppvObject)
    return AAFRESULT_NULL_PARAM;
  
  // Initialize the out parameter.
	*ppvObject = NULL;

  const OMClassId* classId  = reinterpret_cast<const OMClassId*>(pAUID);
  *ppvObject = static_cast<ImplAAFObject *>(create(*classId));

  if (NULL == *ppvObject)
    return AAFRESULT_INVALID_CLASS_ID;
  else
    return AAFRESULT_SUCCESS;
}


// internal utility factory method to create an ImplAAFObject given an auid.
// This method was created to make it simpler to replace calls to "Deprecated"
// call to CreateImpl which should only be used for instanciating transient
// non-ImplAAFObject classes such as an enumerator.
ImplAAFObject *ImplAAFDictionary::CreateImplObject(const aafUID_t& auid)
{
  ImplAAFObject *pObject = NULL;
  AAFRESULT result = AAFRESULT_SUCCESS;
  
  result = CreateInstance(const_cast<aafUID_t *>(&auid), &pObject);
  assert(AAFRESULT_SUCCEEDED(result));
  return pObject;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::LookupClass (
      aafUID_t * pClassID,
      ImplAAFClassDef ** ppClassDef)
{
  if (!pClassID) return AAFRESULT_NULL_PARAM;
  if (!ppClassDef) return AAFRESULT_NULL_PARAM;

  // BobT hack! we don't have class defs fully impl'd yet, so return
  // the only class def we know (for AAFObject)
  ImplAAFClassDef *pcd = NULL;
  AAFRESULT hr =_pBuiltins->ClassDefObject(&pcd);
  if (AAFRESULT_FAILED(hr)) return hr;
  assert (ppClassDef);
  *ppClassDef = pcd;
  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::RegisterClass (
      ImplAAFClassDef * pClassDef)
{
  if (NULL == pClassDef)
	return AAFRESULT_NULL_PARAM;
	
  _classDefinitions.appendValue(pClassDef);
  pClassDef->AcquireReference();
	
  pClassDef->SetDict(this);

  return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::GetClassDefinitions (
      ImplEnumAAFClassDefs ** /*ppEnum*/)
{
  return AAFRESULT_NOT_IMPLEMENTED;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::RegisterType (
      ImplAAFTypeDef * pTypeDef)
{
  if (NULL == pTypeDef)
	return AAFRESULT_NULL_PARAM;
	
  // Get the AUID of the new type to register.
  aafUID_t newAUID;
  HRESULT hr = pTypeDef->GetAUID(&newAUID);
  if (hr != AAFRESULT_SUCCESS)
    return hr;

  // Is this type already registered ?
  ImplAAFTypeDef * pExistingTypeDef = NULL;
  hr = LookupType(&newAUID, &pExistingTypeDef);

  if (hr != AAFRESULT_SUCCESS) {
    // This type is not yet registered, add it to the dictionary.
    _typeDefinitions.appendValue(pTypeDef);
    pTypeDef->AcquireReference();
    // Set up the (non-persistent) dictionary pointer.
    pTypeDef->SetDict(this);
  } else {
    // This type is already registered, probably because it was
    // already in the persisted dictionary.
    // Set up the (non-persistent) dictionary pointer.
    pExistingTypeDef->SetDict(this);
    pExistingTypeDef->ReleaseReference();
  }

  return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::LookupType (
      aafUID_t *  pTypeID,
      ImplAAFTypeDef ** ppTypeDef)
{
	ImplEnumAAFTypeDefs		*typeEnum = NULL;
	ImplAAFTypeDef			*typeDef = NULL;
	aafBool						defFound;
	AAFRESULT					status;
	aafUID_t					testAUID;

	XPROTECT()
	{
		CHECK(GetTypeDefinitions (&typeEnum));
		status = typeEnum->NextOne (&typeDef);
		defFound = AAFFalse;
		while(status == AAFRESULT_SUCCESS && !defFound)
		{
			CHECK(typeDef->GetAUID (&testAUID));
			if(EqualAUID(pTypeID, &testAUID))
			{
				defFound = AAFTrue;
				*ppTypeDef = typeDef;
				typeDef->AcquireReference();
				break;
			}
			typeDef->ReleaseReference();
			typeDef = NULL;
			status = typeEnum->NextOne (&typeDef);
		}
		if(typeDef != NULL)
		{
			typeDef->ReleaseReference();
			typeDef = NULL;
		}
		typeEnum->ReleaseReference();
		typeEnum = NULL;
		if(!defFound)
			 RAISE(AAFRESULT_NO_MORE_OBJECTS);
	}
	XEXCEPT
	{
		if(typeEnum != NULL)
			typeEnum->ReleaseReference();
		if(typeDef != NULL)
			typeDef->ReleaseReference();
	}
	XEND
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::GetTypeDefinitions (
      ImplEnumAAFTypeDefs ** ppEnum)
{
	if (NULL == ppEnum)
		return AAFRESULT_NULL_PARAM;
	*ppEnum = 0;
	
	ImplEnumAAFTypeDefs *theEnum = (ImplEnumAAFTypeDefs *)CreateImpl (CLSID_EnumAAFTypeDefs);
	
	XPROTECT()
	{
		CHECK(theEnum->SetEnumStrongProperty(this, &_typeDefinitions));
		*ppEnum = theEnum;
	}
	XEXCEPT
	{
		if (theEnum)
			theEnum->ReleaseReference();
		return(XCODE());
	}
	XEND;
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::RegisterDataDefintion (
      ImplAAFDataDef *pDataDef)
{
  if (NULL == pDataDef)
	return AAFRESULT_NULL_PARAM;
	
  // Get the AUID of the new type to register.
  aafUID_t newAUID;
  HRESULT hr = pDataDef->GetAUID(&newAUID);
  if (hr != AAFRESULT_SUCCESS)
    return hr;

  // Is this type already registered ?
  ImplAAFDataDef * pExistingDataDef = NULL;
  hr = LookupDataDefintion(&newAUID, &pExistingDataDef);

  if (hr != AAFRESULT_SUCCESS) {
    // This type is not yet registered, add it to the dictionary.
    _dataDefinitions.appendValue(pDataDef);
    pDataDef->AcquireReference();
    // Set up the (non-persistent) dictionary pointer.
    pDataDef->SetDict(this);
  } else {
    // This type is already registered, probably because it was
    // already in the persisted dictionary.
    // Set up the (non-persistent) dictionary pointer.
    pExistingDataDef->SetDict(this);
    pExistingDataDef->ReleaseReference();
  }

  return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::LookupDataDefintion (
      aafUID_t *pDataDefintionID,
      ImplAAFDataDef **ppDataDef)
{
	ImplEnumAAFDataDefs		*dataEnum = NULL;
	ImplAAFDataDef			*dataDef = NULL;
	aafBool						defFound;
	AAFRESULT					status;
	aafUID_t					testAUID;

	XPROTECT()
	{
		CHECK(GetDataDefinitions (&dataEnum));
		status = dataEnum->NextOne (&dataDef);
		defFound = AAFFalse;
		while(status == AAFRESULT_SUCCESS && !defFound)
		{
			CHECK(dataDef->GetAUID (&testAUID));
			if(EqualAUID(pDataDefintionID, &testAUID))
			{
				defFound = AAFTrue;
				*ppDataDef = dataDef;
				dataDef->AcquireReference();
				break;
			}
			dataDef->ReleaseReference();
			dataDef = NULL;
			status = dataEnum->NextOne (&dataDef);
		}
		if(dataDef != NULL)
		{
			dataDef->ReleaseReference();
			dataDef = NULL;
		}
		dataEnum->ReleaseReference();
		dataEnum = NULL;
		if(!defFound)
			 RAISE(AAFRESULT_NO_MORE_OBJECTS);
	}
	XEXCEPT
	{
		if(dataEnum != NULL)
			dataEnum->ReleaseReference();
		if(dataDef != NULL)
			dataDef->ReleaseReference();
	}
	XEND
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::GetDataDefinitions (
      ImplEnumAAFDataDefs **ppEnum)
{
	if (NULL == ppEnum)
		return AAFRESULT_NULL_PARAM;
	*ppEnum = 0;
	
	ImplEnumAAFDataDefs *theEnum = (ImplEnumAAFDataDefs *)CreateImpl (CLSID_EnumAAFDataDefs);
	
	XPROTECT()
	{
		CHECK(theEnum->SetEnumStrongProperty(this, &_dataDefinitions));
		*ppEnum = theEnum;
	}
	XEXCEPT
	{
		if (theEnum)
			theEnum->ReleaseReference();
		return(XCODE());
	}
	XEND;
	
	return(AAFRESULT_SUCCESS);
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::RegisterOperationDefinition (
      ImplAAFOperationDef *pOperationDef)
{
	if (NULL == pOperationDef)
		return AAFRESULT_NULL_PARAM;
	
	_operationDefinitions.appendValue(pOperationDef);
	// trr - We are saving a copy of pointer in _pluginDefinitions
	// so we need to bump its reference count.
	pOperationDef->AcquireReference();
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::LookupOperationDefinition (
      aafUID_t *effectID,
      ImplAAFOperationDef **ppOperationDef)
{
	ImplEnumAAFOperationDefs	*effectEnum = NULL;
	ImplAAFOperationDef			*effectDef = NULL;
	aafBool						defFound;
	AAFRESULT					status;
	aafUID_t					testAUID;

	XPROTECT()
	{
		CHECK(GetOperationDefinitions (&effectEnum));
		status = effectEnum->NextOne (&effectDef);
		defFound = AAFFalse;
		while(status == AAFRESULT_SUCCESS && !defFound)
		{
			CHECK(effectDef->GetAUID (&testAUID));
			if(EqualAUID(effectID, &testAUID))
			{
				defFound = AAFTrue;
				*ppOperationDef = effectDef;
				effectDef->AcquireReference();
				break;
			}
			effectDef->ReleaseReference();
			effectDef = NULL;
			status = effectEnum->NextOne (&effectDef);
		}
		if(effectDef != NULL)
		{
			effectDef->ReleaseReference();
			effectDef = NULL;
		}
		effectEnum->ReleaseReference();
		effectEnum = NULL;
		if(!defFound)
			 RAISE(AAFRESULT_NO_MORE_OBJECTS);
	}
	XEXCEPT
	{
		if(effectEnum != NULL)
			effectEnum->ReleaseReference();
		if(effectDef != NULL)
			effectDef->ReleaseReference();
	}
	XEND
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::GetOperationDefinitions (
      ImplEnumAAFOperationDefs **ppEnum)
{
	if (NULL == ppEnum)
		return AAFRESULT_NULL_PARAM;
	*ppEnum = 0;
	
	ImplEnumAAFOperationDefs *theEnum = (ImplEnumAAFOperationDefs *)CreateImpl (CLSID_EnumAAFOperationDefs);
	
	XPROTECT()
	{
		CHECK(theEnum->SetEnumStrongProperty(this, &_operationDefinitions));
		*ppEnum = theEnum;
	}
	XEXCEPT
	{
		if (theEnum)
			theEnum->ReleaseReference();
		return(XCODE());
	}
	XEND;
	
	return(AAFRESULT_SUCCESS);
}

AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::RegisterParameterDefinition (
      ImplAAFParameterDef *pParameterDef)
{
	if (NULL == pParameterDef)
		return AAFRESULT_NULL_PARAM;
	
	_parameterDefinitions.appendValue(pParameterDef);
	// trr - We are saving a copy of pointer in _pluginDefinitions
	// so we need to bump its reference count.
	pParameterDef->AcquireReference();
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::LookupParameterDefinition (
      aafUID_t *pParameterID,
      ImplAAFParameterDef **ppParameterDef)
{
	ImplEnumAAFParameterDefs		*parameterEnum = NULL;
	ImplAAFParameterDef			*parameterDef = NULL;
	aafBool						defFound;
	AAFRESULT					status;
	aafUID_t					testAUID;

	XPROTECT()
	{
		CHECK(GetParameterDefinitions (&parameterEnum));
		status = parameterEnum->NextOne (&parameterDef);
		defFound = AAFFalse;
		while(status == AAFRESULT_SUCCESS && !defFound)
		{
			CHECK(parameterDef->GetAUID (&testAUID));
			if(EqualAUID(pParameterID, &testAUID))
			{
				defFound = AAFTrue;
				*ppParameterDef = parameterDef;
				parameterDef->AcquireReference();
				break;
			}
			parameterDef->ReleaseReference();
			parameterDef = NULL;
			status = parameterEnum->NextOne (&parameterDef);
		}
		if(parameterDef != NULL)
		{
			parameterDef->ReleaseReference();
			parameterDef = NULL;
		}
		parameterEnum->ReleaseReference();
		parameterEnum = NULL;
		if(!defFound)
			 RAISE(AAFRESULT_NO_MORE_OBJECTS);
	}
	XEXCEPT
	{
		if(parameterEnum != NULL)
			parameterEnum->ReleaseReference();
		if(parameterDef != NULL)
			parameterDef->ReleaseReference();
	}
	XEND
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::GetParameterDefinitions (
      ImplEnumAAFParameterDefs **ppEnum)
{
	if (NULL == ppEnum)
		return AAFRESULT_NULL_PARAM;
	*ppEnum = 0;
	
	ImplEnumAAFParameterDefs *theEnum = (ImplEnumAAFParameterDefs *)CreateImpl (CLSID_EnumAAFParameterDefs);
	
	XPROTECT()
	{
		CHECK(theEnum->SetEnumStrongProperty(this, &_parameterDefinitions));
		*ppEnum = theEnum;
	}
	XEXCEPT
	{
		if (theEnum)
			theEnum->ReleaseReference();
		return(XCODE());
	}
	XEND;
	
	return(AAFRESULT_SUCCESS);
}

AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::RegisterCodecDefinition (
      ImplAAFCodecDef *pPlugDef)
{
	if (NULL == pPlugDef)
		return AAFRESULT_NULL_PARAM;
	
	_codecDefinitions.appendValue(pPlugDef);
	// trr - We are saving a copy of pointer in _pluginDefinitions
	// so we need to bump its reference count.
	pPlugDef->AcquireReference();
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT
    ImplAAFDictionary::GetNumCodecDefs(aafUInt32 *  pNumCodecDefs)
{
  size_t siz;

  if(pNumCodecDefs == NULL)
    return AAFRESULT_NULL_PARAM;
  
  _codecDefinitions.getSize(siz);
  
  *pNumCodecDefs = siz;
  return AAFRESULT_SUCCESS;
}

AAFRESULT
    ImplAAFDictionary::GetNthCodecDef (aafInt32 index, ImplAAFCodecDef **ppPluggableDefs)
{
  if (NULL == ppPluggableDefs)
    return AAFRESULT_NULL_PARAM;

  ImplAAFCodecDef *obj = NULL;
  _codecDefinitions.getValueAt(obj, index);
  *ppPluggableDefs = obj;
	
  // trr - We are returning a copy of pointer stored in _mobs so we need
  // to bump its reference count.
  if (obj)
    obj->AcquireReference();
  else
    return AAFRESULT_NO_MORE_OBJECTS;

  return AAFRESULT_SUCCESS;
}

AAFRESULT ImplAAFDictionary::LookupCodecDefinition(aafUID_t *defID, ImplAAFCodecDef **result)
{
	ImplAAFCodecDef				*codec = NULL;
	aafBool						defFound;
	aafUID_t					testAUID;
	aafUInt32					n, numCodecs;

	XPROTECT()
	{
		*result = NULL;
		CHECK(GetNumCodecDefs(&numCodecs));
		defFound = AAFFalse;
		for(n = 0; n < numCodecs && !defFound; n++)
		{
			CHECK(GetNthCodecDef (n, &codec));
			CHECK(codec->GetAUID (&testAUID));
			if(EqualAUID(defID, &testAUID))
			{
				defFound = AAFTrue;
				*result = codec;
				codec->AcquireReference();
				break;
			}
			codec->ReleaseReference();
			codec = NULL;
		}
		if(codec != NULL)
		{
			codec->ReleaseReference();
			codec = NULL;
		}
		if(!defFound)
			 RAISE(AAFRESULT_NO_MORE_OBJECTS);
	}
	XEXCEPT
	{
		if(codec != NULL)
			codec->ReleaseReference();
	}
	XEND
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::GetCodecDefinitions (
      ImplEnumAAFCodecDefs **ppEnum)
{
	if (NULL == ppEnum)
		return AAFRESULT_NULL_PARAM;
	*ppEnum = 0;
	
	ImplEnumAAFCodecDefs *theEnum = (ImplEnumAAFCodecDefs *)CreateImpl (CLSID_EnumAAFCodecDefs);
	
	XPROTECT()
	{
		CHECK(theEnum->SetEnumStrongProperty(this, &_codecDefinitions));
		*ppEnum = theEnum;
	}
	XEXCEPT
	{
		if (theEnum)
			theEnum->ReleaseReference();
		return(XCODE());
	}
	XEND;
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::RegisterContainerDefinition (
      ImplAAFContainerDef *pPlugDef)
{
	if (NULL == pPlugDef)
		return AAFRESULT_NULL_PARAM;
	
	_containerDefinitions.appendValue(pPlugDef);
	// trr - We are saving a copy of pointer in _pluginDefinitions
	// so we need to bump its reference count.
	pPlugDef->AcquireReference();
	
	return(AAFRESULT_SUCCESS);
}

AAFRESULT ImplAAFDictionary::LookupContainerDefinition(aafUID_t *defID, ImplAAFContainerDef **result)
{
	ImplAAFContainerDef			*container = NULL;
	aafBool						defFound;
	aafUID_t					testAUID;
	aafUInt32					n, numContainers;

	XPROTECT()
	{
		*result = NULL;
		CHECK(GetNumContainerDefs(&numContainers));
		defFound = AAFFalse;
		for(n = 0; n < numContainers && !defFound; n++)
		{
			CHECK(GetNthContainerDef (n, &container));
			CHECK(container->GetAUID (&testAUID));
			if(EqualAUID(defID, &testAUID))
			{
				defFound = AAFTrue;
				*result = container;
				container->AcquireReference();
				break;
			}
			container->ReleaseReference();
			container = NULL;
		}
		if(container != NULL)
		{
			container->ReleaseReference();
			container = NULL;
		}
		if(!defFound)
			 RAISE(AAFRESULT_NO_MORE_OBJECTS);
	}
	XEXCEPT
	{
		if(container != NULL)
			container->ReleaseReference();
	}
	XEND
	
	return(AAFRESULT_SUCCESS);
}

AAFRESULT
    ImplAAFDictionary::GetNumContainerDefs(aafUInt32 *  pNumContainerDefs)
{
  size_t siz;

  if(pNumContainerDefs == NULL)
    return AAFRESULT_NULL_PARAM;
  
  _containerDefinitions.getSize(siz);
  
  *pNumContainerDefs = siz;
  return AAFRESULT_SUCCESS;
}

AAFRESULT
    ImplAAFDictionary::GetNthContainerDef (aafInt32 index, ImplAAFContainerDef **ppPluggableDefs)
{
  if (NULL == ppPluggableDefs)
    return AAFRESULT_NULL_PARAM;

  ImplAAFContainerDef *obj = NULL;
  _containerDefinitions.getValueAt(obj, index);
  *ppPluggableDefs = obj;
	
  // trr - We are returning a copy of pointer stored in _mobs so we need
  // to bump its reference count.
  if (obj)
    obj->AcquireReference();
  else
    return AAFRESULT_NO_MORE_OBJECTS;

  return AAFRESULT_SUCCESS;
}

AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::GetContainerDefinitions (
      ImplEnumAAFContainerDefs **ppEnum)
{
	if (NULL == ppEnum)
		return AAFRESULT_NULL_PARAM;
	*ppEnum = 0;
	
	ImplEnumAAFContainerDefs *theEnum = (ImplEnumAAFContainerDefs *)CreateImpl (CLSID_EnumAAFContainerDefs);
	
	XPROTECT()
	{
		CHECK(theEnum->SetEnumStrongProperty(this, &_containerDefinitions));
		*ppEnum = theEnum;
	}
	XEXCEPT
	{
		if (theEnum)
			theEnum->ReleaseReference();
		return(XCODE());
	}
	XEND;
	
	return(AAFRESULT_SUCCESS);
}

#define REGISTER_TYPE_BUILTIN(func) \
{ \
  ImplAAFTypeDef * pTD = 0; \
  AAFRESULT hr = func (&pTD); \
  assert (AAFRESULT_SUCCEEDED(hr)); \
  assert (pTD); \
  RegisterType (pTD); \
  pTD->ReleaseReference(); \
}


#define REGISTER_CLASS_BUILTIN(func) \
{ \
  ImplAAFClassDef * pCD = 0; \
  AAFRESULT hr = func (&pCD); \
  assert (AAFRESULT_SUCCEEDED(hr)); \
  assert (pCD); \
  RegisterClass (pCD); \
  pCD->ReleaseReference(); \
}


void ImplAAFDictionary::InitBuiltins()
{
  if (_pBuiltins) return;

  _pBuiltins = new ImplAAFBuiltins(this);
  assert (_pBuiltins);

  // Put built-in types into dictionary.
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefUInt8);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefUInt16);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefInt16);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefUInt32);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefInt32);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefInt64);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefObjRef);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefObjRefArray);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefUInt8Array);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefUInt8Array8);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefAUID);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefAUIDArray);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefWCharString);
  REGISTER_TYPE_BUILTIN(_pBuiltins->TypeDefFadeType);

  REGISTER_CLASS_BUILTIN(_pBuiltins->ClassDefObject);

  ImplAAFDataDef	*dataDef = NULL;
	AAFRESULT		hr;
	aafUID_t		uid;
	hr = CreateInstance (&AUID_AAFDataDef,
							(ImplAAFObject **)&dataDef);
	uid = DDEF_Picture;
	hr = dataDef->Init (&uid, L"Picture", L"Picture data");
    hr = RegisterDataDefintion (dataDef);
	dataDef->ReleaseReference();
	dataDef = NULL;
	/***!!!*/
	hr = CreateInstance (&AUID_AAFDataDef,
							(ImplAAFObject **)&dataDef);
	uid = DDEF_Sound;
	hr = dataDef->Init (&uid, L"Sound", L"Sound data");
    hr = RegisterDataDefintion (dataDef);
	dataDef->ReleaseReference();
	dataDef = NULL;
	/***!!!*/
	hr = CreateInstance (&AUID_AAFDataDef,
							(ImplAAFObject **)&dataDef);
	uid = DDEF_Timecode;
	hr = dataDef->Init (&uid, L"Timecode", L"Timecode data");
    hr = RegisterDataDefintion (dataDef);
	dataDef->ReleaseReference();
	dataDef = NULL;
	/***!!!*/
	hr = CreateInstance (&AUID_AAFDataDef,
							(ImplAAFObject **)&dataDef);
	uid = DDEF_Edgecode;
	hr = dataDef->Init (&uid, L"Edgecode", L"Edgecode data");
    hr = RegisterDataDefintion (dataDef);
	dataDef->ReleaseReference();
	dataDef = NULL;
	/***!!!*/
	hr = CreateInstance (&AUID_AAFDataDef,
							(ImplAAFObject **)&dataDef);
	uid = DDEF_Matte;
	hr = dataDef->Init (&uid, L"Matte", L"Matte data");
    hr = RegisterDataDefintion (dataDef);
	dataDef->ReleaseReference();
	dataDef = NULL;
	/***!!!*/
	hr = CreateInstance (&AUID_AAFDataDef,
							(ImplAAFObject **)&dataDef);
	uid = DDEF_PictureWithMatte;
	hr = dataDef->Init (&uid, L"PictureWithMatte", L"PictureWithMatte data");
    hr = RegisterDataDefintion (dataDef);
	dataDef->ReleaseReference();
	dataDef = NULL;
}

AAFRESULT
ImplAAFDictionary::LookupPropDef (OMPropertyId opid,
								  ImplAAFPropertyDef ** ppd)
{
  InitBuiltins ();
  assert (_pBuiltins);
  return _pBuiltins->LookupPropDef (opid, ppd);
}

AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::RegisterInterpolationDefinition (
      ImplAAFInterpolationDef *pInterpolationDef)
{
	if (NULL == pInterpolationDef)
		return AAFRESULT_NULL_PARAM;
	
	_interpolationDefinitions.appendValue(pInterpolationDef);
	// trr - We are saving a copy of pointer in _pluginDefinitions
	// so we need to bump its reference count.
	pInterpolationDef->AcquireReference();
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::LookupInterpolationDefinition (
      aafUID_t *pInterpolationID,
      ImplAAFInterpolationDef **ppInterpolationDef)
{
	ImplEnumAAFInterpolationDefs		*InterpolationEnum = NULL;
	ImplAAFInterpolationDef			*InterpolationDef = NULL;
	aafBool						defFound;
	AAFRESULT					status;
	aafUID_t					testAUID;

	XPROTECT()
	{
		CHECK(GetInterpolationDefinitions (&InterpolationEnum));
		status = InterpolationEnum->NextOne (&InterpolationDef);
		defFound = AAFFalse;
		while(status == AAFRESULT_SUCCESS && !defFound)
		{
			CHECK(InterpolationDef->GetAUID (&testAUID));
			if(EqualAUID(pInterpolationID, &testAUID))
			{
				defFound = AAFTrue;
				*ppInterpolationDef = InterpolationDef;
				InterpolationDef->AcquireReference();
				break;
			}
			InterpolationDef->ReleaseReference();
			InterpolationDef = NULL;
			status = InterpolationEnum->NextOne (&InterpolationDef);
		}
		if(InterpolationDef != NULL)
		{
			InterpolationDef->ReleaseReference();
			InterpolationDef = NULL;
		}
		InterpolationEnum->ReleaseReference();
		InterpolationEnum = NULL;
		if(!defFound)
			 RAISE(AAFRESULT_NO_MORE_OBJECTS);
	}
	XEXCEPT
	{
		if(InterpolationEnum != NULL)
			InterpolationEnum->ReleaseReference();
		if(InterpolationDef != NULL)
			InterpolationDef->ReleaseReference();
	}
	XEND
	
	return(AAFRESULT_SUCCESS);
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFDictionary::GetInterpolationDefinitions (
      ImplEnumAAFInterpolationDefs **ppEnum)
{
	if (NULL == ppEnum)
		return AAFRESULT_NULL_PARAM;
	*ppEnum = 0;
	
	ImplEnumAAFInterpolationDefs *theEnum = (ImplEnumAAFInterpolationDefs *)CreateImpl (CLSID_EnumAAFInterpolationDefs);
	
	XPROTECT()
	{
		CHECK(theEnum->SetEnumStrongProperty(this, &_interpolationDefinitions));
		*ppEnum = theEnum;
	}
	XEXCEPT
	{
		if (theEnum)
			theEnum->ReleaseReference();
		return(XCODE());
	}
	XEND;
	
	return(AAFRESULT_SUCCESS);
}

OMDEFINE_STORABLE(ImplAAFDictionary, AUID_AAFDictionary);
