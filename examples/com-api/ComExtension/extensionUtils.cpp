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

#include "extensionUtils.h"
#include "AAF.h"
#include <assert.h>

#if defined(_MAC) || defined(macintosh)
#include <wstring.h>
#endif

#include <iostream.h>



//
// Temporarily (?) only used to print out the role enum.
//
static void sPrintAuid (const aafUID_t auid)
{
  cout << hex
	   << "{ 0x" << auid.Data1
	   << ", 0x" << auid.Data2
	   << ", 0x" << auid.Data3
	   << ", {";
  aafUInt32 i;
  for (i = 0; i < 8; i++)
	{
	  if (i)
		cout << ", ";
	  cout << "0x" << (int) auid.Data4[i];
	}
  cout << "} }";
}


//
// Prints the given string.
//
ostream& operator<< (ostream& s,
					 const aafCharacter * wstring)
{
  assert (wstring);

  const aafUInt32 numChars = wcslen (wstring);

  char * cstring = new char [numChars+1];
  assert (cstring);

  size_t status = wcstombs(cstring, wstring, numChars);
  assert (status != (size_t)-1);
  cstring[numChars] = '\0';

  s << cstring;

  delete[] cstring;

  return s;
}


//
// Returns true if the roles match; returns false otherwise.
//
bool AreRolesEqual (const eRole & roleA, const eRole & roleB)
{
  return (memcmp (&roleA, &roleB, sizeof (eRole)) == 0 ?
		  true : false);
}


//
// Prints the given eRole.
//
void PrintRole (IAAFDictionary * pDict,
				const eRole role)
{
  assert (pDict);
  IAAFTypeDefSP ptd;
  check (pDict->LookupType ((aafUID_t*) &kTypeID_eRole, &ptd));

  IAAFTypeDefExtEnumSP ptde;
  check (ptd->QueryInterface (IID_IAAFTypeDefExtEnum, (void **)&ptde));

  aafUInt32 nameLen = 0;
  check (ptde->GetNameBufLenFromAUID ((aafUID_t*) &role, &nameLen));
  assert (nameLen);

  aafCharacter *buf = 0;
  buf = new aafCharacter[nameLen];
  assert (buf);

  check (ptde->GetNameFromAUID ((aafUID_t*) &role, buf, nameLen));

  cout << buf;

  delete[] buf;
}


//
// Prints the given PersonnelResource.
//
void PrintPersonnelResource (IAAFDictionary * pDict,
							 const PersonnelResource & resource)
{
  assert (pDict);
  assert (resource.name);

  cout << "Name:        " << resource.name << endl;
  cout << "Role:        "; PrintRole (pDict, resource.role); cout << endl;
  if (resource.cid_present)
	cout << "Contract ID: " << dec << resource.cid << endl;
}


//
// Prints all personnel resources in the given PersonnelMob.
//
void PrintPersonnelResources (IAAFDictionary * pDict,
							  IAAFMob * pMob)
{
  // Get an IAAFObject for the mob, then use it to get the class
  // definition describing the PersonnelMob
  IAAFObjectSP pMobObj;
  check (pMob->QueryInterface (IID_IAAFObject, (void **)&pMobObj));
  IAAFClassDefSP cd;
  check (pMobObj->GetDefinition (&cd));

  // Use the class definition to get the definition for the Personnel
  // property.
  IAAFPropertyDefSP pd;
  check (cd->LookupPropertyDef ((aafUID_t*) &kPropID_PersonnelMob_Personnel,
								&pd));

  // Get the property value for the array of personnel objects
  IAAFPropertyValueSP pva;
  check (pMobObj->GetPropertyValue (pd, &pva));

  // Get the type def for arrays
  IAAFTypeDefSP td;
  check (pva->GetType (&td));
  IAAFTypeDefVariableArraySP tda;
  check (td->QueryInterface (IID_IAAFTypeDefVariableArray, (void **)&tda));

  // Use the type def for arrays to get the number of personnel
  // objects in this property value.
  aafUInt32 numPersonnel = 0;
  check (tda->GetCount (pva, &numPersonnel));

  // Get the type def describing elements of the array
  IAAFTypeDefSP basetd;
  check (tda->GetType (&basetd));
  IAAFTypeDefObjectRefSP tdo;
  check (basetd->QueryInterface (IID_IAAFTypeDefObjectRef, (void **)&tdo));

  cout << "There are " << numPersonnel
	   << " personnel record objects." << endl;

  // Print each element in the array.
  aafUInt32 i;
  for (i = 0; i < numPersonnel; i++)
	{
	  // put a newline between each
	  if (i)
		cout << endl;

	  // Get the property value for the indexed record
	  IAAFPropertyValueSP pvr;
	  check (tda->GetElementValue (pva, i, &pvr));

	  // Get the object contained in that property value
	  IAAFObjectSP personObj;
	  check (tdo->GetObject (pvr, &personObj));

	  // Get the resource info from that object
	  PersonnelResource r =
		PersonnelRecordGetInfo (personObj);

	  // print the resource info
	  PrintPersonnelResource (pDict, r);
	}
}


PersonnelResource FormatResource (aafCharacter * name,
								  const eRole &  role)
{
  PersonnelResource r;
  assert (name);
  wcscpy (r.name, name);
  r.role = role;
  r.cid_present = false;
  r.cid = 0;

  return r;
}


PersonnelResource FormatResource (aafCharacter * name,
								  const eRole &  role,
								  contractID_t   cid)
{
  PersonnelResource r =
	FormatResource (name, role);
  r.cid_present = true;
  r.cid = cid;
  return r;
}


void PersonnelRecordSetName (IAAFObject * pObj,
							 const aafCharacter * name)
{
  assert (pObj);
  assert (name);

  IAAFClassDefSP cd;
  check (pObj->GetDefinition (&cd));

  IAAFPropertyDefSP pd;
  check (cd->LookupPropertyDef ((aafUID_t*) &kPropID_PersonnelResource_Name,
								&pd));

  IAAFPropertyValueSP pv;
  check (pObj->GetPropertyValue (pd, &pv));
  
  IAAFTypeDefSP td;
  check (pd->GetTypeDef (&td));

  IAAFTypeDefStringSP tds;
  check (td->QueryInterface (IID_IAAFTypeDefString, (void **)&tds));

  check (tds->SetCString (pv,
						  (aafMemPtr_t) name,
						  wcslen (name) * sizeof (aafCharacter)));

  check (pObj->SetPropertyValue (pd, pv));
}


aafUInt32 PersonnelRecordGetNameBufLen (IAAFObject * pObj)
{
  assert (pObj);

  IAAFClassDefSP cd;
  check (pObj->GetDefinition (&cd));

  IAAFPropertyDefSP pd;
  check (cd->LookupPropertyDef ((aafUID_t*) &kPropID_PersonnelResource_Name,
								&pd));

  IAAFPropertyValueSP pv;
  check (pObj->GetPropertyValue (pd, &pv));
  
  IAAFTypeDefSP td;
  check (pd->GetTypeDef (&td));

  IAAFTypeDefStringSP tds;
  check (td->QueryInterface (IID_IAAFTypeDefString, (void **)&tds));

  aafUInt32 numChars = 0;
  check (tds->GetCount (pv, &numChars));

  // Add 1 for null terminator.
  return numChars + 1;
}


void PersonnelRecordGetName (IAAFObject * pObj,
							 aafCharacter * buf,
							 aafUInt32 buflen)
{
  assert (pObj);
  assert (buf);
  aafUInt32 nameLen = PersonnelRecordGetNameBufLen (pObj);
  assert (buflen >= nameLen);

  IAAFClassDefSP cd;
  check (pObj->GetDefinition (&cd));

  IAAFPropertyDefSP pd;
  check (cd->LookupPropertyDef ((aafUID_t*) &kPropID_PersonnelResource_Name,
								&pd));

  IAAFPropertyValueSP pv;
  check (pObj->GetPropertyValue (pd, &pv));
  
  IAAFTypeDefSP td;
  check (pd->GetTypeDef (&td));

  IAAFTypeDefStringSP tds;
  check (td->QueryInterface (IID_IAAFTypeDefString, (void **)&tds));

  check (tds->GetElements (pv, (aafMemPtr_t) buf, buflen));

  // Make sure we're null-terminated.
  buf[nameLen-1] = '\0';
}


void PersonnelRecordSetRole (IAAFObject * pObj,
							 eRole role)
{
  assert (pObj);

  IAAFClassDefSP cd;
  check (pObj->GetDefinition (&cd));

  IAAFPropertyDefSP pd;
  check (cd->LookupPropertyDef ((aafUID_t*) &kPropID_PersonnelResource_Role,
								&pd));

  IAAFPropertyValueSP pv;
  check (pObj->GetPropertyValue (pd, &pv));
  
  IAAFTypeDefSP td;
  check (pd->GetTypeDef (&td));

  IAAFTypeDefExtEnumSP tde;
  check (td->QueryInterface (IID_IAAFTypeDefExtEnum, (void **)&tde));

  check (tde->SetAUIDValue (pv, &role));
  check (pObj->SetPropertyValue (pd, pv));
}


eRole PersonnelRecordGetRole (IAAFObject * pObj)
{
  eRole r;
  assert (pObj);

  IAAFClassDefSP cd;
  check (pObj->GetDefinition (&cd));

  IAAFPropertyDefSP pd;
  check (cd->LookupPropertyDef ((aafUID_t*) &kPropID_PersonnelResource_Role,
								&pd));

  IAAFPropertyValueSP pv;
  check (pObj->GetPropertyValue (pd, &pv));
  
  IAAFTypeDefSP td;
  check (pd->GetTypeDef (&td));

  IAAFTypeDefExtEnumSP tde;
  check (td->QueryInterface (IID_IAAFTypeDefExtEnum, (void **)&tde));

  check (tde->GetAUIDValue (pv, &r));
  return r;
}


void PersonnelRecordSetContractID (IAAFObject * pObj,
								   contractID_t cid)
{
  assert (pObj);

  IAAFClassDefSP cd;
  check (pObj->GetDefinition (&cd));

  IAAFPropertyDefSP pd;
  check (cd->LookupPropertyDef ((aafUID_t*) &kPropID_PersonnelResource_ContractID,
								&pd));

  IAAFTypeDefSP td;
  check (pd->GetTypeDef (&td));

  IAAFTypeDefIntSP tdi;
  check (td->QueryInterface (IID_IAAFTypeDefInt, (void **)&tdi));

  IAAFPropertyValueSP pv;
  check (tdi->CreateValue ((aafMemPtr_t) &cid, sizeof (cid), &pv));

  check (pObj->SetPropertyValue (pd, pv));
}


bool PersonnelRecordContractIDIsPresent (IAAFObject * pObj)
{
  aafBool r;
  assert (pObj);

  IAAFClassDefSP cd;
  check (pObj->GetDefinition (&cd));

  IAAFPropertyDefSP pd;
  check (cd->LookupPropertyDef ((aafUID_t*) &kPropID_PersonnelResource_ContractID,
								&pd));

  check (pObj->IsPropertyPresent (pd, &r));
  return r ? true : false;
}


contractID_t PersonnelRecordGetContractID (IAAFObject * pObj)
{
  assert (pObj);
  assert (PersonnelRecordContractIDIsPresent (pObj));

  contractID_t r;

  IAAFClassDefSP cd;
  check (pObj->GetDefinition (&cd));

  IAAFPropertyDefSP pd;
  check (cd->LookupPropertyDef ((aafUID_t*) &kPropID_PersonnelResource_ContractID,
								&pd));

  IAAFPropertyValueSP pv;
  check (pObj->GetPropertyValue (pd, &pv));
  
  IAAFTypeDefSP td;
  check (pd->GetTypeDef (&td));

  IAAFTypeDefIntSP tdi;
  check (td->QueryInterface (IID_IAAFTypeDefInt, (void **)&tdi));

  check (tdi->GetInteger (pv, (aafMemPtr_t) &r, sizeof (r)));
  return r;
}


void PersonnelRecordSetInfo (IAAFObject * pObj,
							 const PersonnelResource & info)
{
  assert (info.name);
  PersonnelRecordSetName (pObj, info.name);
  PersonnelRecordSetRole (pObj, info.role);
  if (info.cid_present)
	PersonnelRecordSetContractID (pObj, info.cid);
}


PersonnelResource PersonnelRecordGetInfo (IAAFObject * pObj)
{
  PersonnelResource r;

  PersonnelRecordGetName (pObj, r.name, sizeof (r.name));
  r.role = PersonnelRecordGetRole (pObj);
  if (PersonnelRecordContractIDIsPresent (pObj))
	{
	  r.cid = PersonnelRecordGetContractID (pObj);
	  r.cid_present = true;
	}
  else
	{
	  r.cid_present = false;
	}
  return r;
}
