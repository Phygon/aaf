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
 * prior written permission of Avid Technology, Inc.
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

#include "AAFStoredObjectIDs.h"
#include "AAFPropertyIDs.h"
#include "ImplAAFObjectCreation.h"

#ifndef __ImplAAFDataDef_h__
#include "ImplAAFDataDef.h"
#endif


 

#ifndef __ImplAAFParameter_h__
#include "ImplAAFParameter.h"
#endif

#include <assert.h>
#include <string.h>
#include "AAFResult.h"
#include "aafErr.h"
#include "ImplAAFDictionary.h"
#include "ImplAAFTypeDef.h"
#include "ImplAAFParameterDef.h"
#include "ImplAAFTypeDef.h"

ImplAAFParameter::ImplAAFParameter ()
: _parmDef(			PID_Parameter_Definition,	"Definition")
{
	_persistentProperties.put(_parmDef.address());
}


ImplAAFParameter::~ImplAAFParameter ()
{
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFParameter::SetParameterDefinition (
      ImplAAFParameterDef *pParmDef)
{
	aafUID_t			newUID;
	ImplAAFDictionary	*dict = NULL;

	if(pParmDef == NULL)
		return AAFRESULT_NULL_PARAM;

	XPROTECT()
	{
		CHECK(pParmDef->GetAUID(&newUID));
		CHECK(GetDictionary(&dict));
// This is a weak reference, not yet counted
//		if(dict->LookupParameterDef(&newUID, &def) == AAFRESULT_SUCCESS)
//			def->ReleaseReference();

		_parmDef = newUID;
//		pParmDef->AcquireReference();
		dict->ReleaseReference();
		dict = NULL;
	}
	XEXCEPT
	{
		if(dict)
		  dict->ReleaseReference();
		dict = 0;
	}
	XEND

	return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFParameter::GetParameterDefinition (
      ImplAAFParameterDef **ppParmDef)
{
	ImplAAFDictionary	*dict = NULL;

	if(ppParmDef == NULL)
		return AAFRESULT_NULL_PARAM;

	XPROTECT()
	{
	  CHECK(GetDictionary(&dict));
		CHECK(dict->LookupParameterDef(_parmDef, ppParmDef));
//		(*ppParmDef)->AcquireReference();
		dict->ReleaseReference();
		dict = NULL;
	}
	XEXCEPT
	{
		if(dict)
		  dict->ReleaseReference();
		dict = 0;
	}
	XEND;

	return AAFRESULT_SUCCESS;
}

	



AAFRESULT STDMETHODCALLTYPE
    ImplAAFParameter::GetTypeDefinition (
      ImplAAFTypeDef **ppTypeDef)
{
	ImplAAFParameterDef	*pParameterDef = NULL;

	if(ppTypeDef == NULL)
		return AAFRESULT_NULL_PARAM;

	XPROTECT()
	{
	  CHECK(GetParameterDefinition(&pParameterDef));
		CHECK(pParameterDef->GetTypeDefinition (ppTypeDef));
		pParameterDef->ReleaseReference();
		pParameterDef = NULL;
	}
	XEXCEPT
	{
		if(pParameterDef)
		  pParameterDef->ReleaseReference();
		pParameterDef = 0;
	}
	XEND;

	return AAFRESULT_SUCCESS;
}

const OMUniqueObjectIdentification&
  ImplAAFParameter::identification(void) const
{
  return *reinterpret_cast<const OMUniqueObjectIdentification*>(&_parmDef.reference());
}






