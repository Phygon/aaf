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
//=---------------------------------------------------------------------=


#ifndef __ModuleTestsCommon_h__
#define __ModuleTestsCommon_h__

#include "AAF.h"
#include "AAFResult.h"
#include "AAFSmartPointer.h"

#include "ModuleTest.h"

#include <assert.h>
#include <wchar.h>


// This is a collection of simple functions intended to ease the
// implemenation of module tests and to prevent the spread of
// cut/paste/modified code fragments.
//
// It resides in its own namespace "mtc" to avoid confusion with any
// existing routines that exist, and are repeated, throughout the
// module tests.  For example, mtc::RemoveTestFile() can be called
// rather than cutting and pasting the original RemoveTestFile routine
// that appears in most module test file.
//
// CAAFAuxiliaryDescriptorTest.cpp, CAAFRecordingDescriptorTest.cpp,
// and CAAFDescriptiveMarkerTest.cpp are the first module test
// implementaions that use the mtc functions.  They provide an example
// of how to use these functions.

// mtc  = Module Test Common

namespace mtc {

const	aafMobID_t	TEST_CompositionMobID = 
{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
0x13, 0x00, 0x00, 0x00,
{0x4412fd64, 0x0404, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}};

const	aafMobID_t	TEST_ReferencedMasterMobID = 
{{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
0x13, 0x00, 0x00, 0x00,
{0x4ac5382a, 0x0404, 0x11d4, {0x8e, 0x3d, 0x00, 0x90, 0x27, 0xdf, 0xca, 0x7c}}};

const aafRational_t TEST_EditRate = {30, 1};

// Cross-platform utility to delete a file.
void RemoveTestFile(const wchar_t* pFileName);

// Create an AAF file with a CompositionMob that contains a single
// slot, a referenced master mob.  Both mobs have a single slot with
// with an ID if 1.
// The composition mob id is TEST_CompositionMobID
// The master mob id is Test_ReferencedMasterMobID

// Simple structure to return basic pointers a user of the file will
// always be interested in.
struct SimpleFilePointers {
  IAAFSmartPointer<IAAFFile> pFile;
  IAAFSmartPointer<IAAFHeader> pHeader;
  IAAFSmartPointer<IAAFDictionary> pDictionary;
  IAAFSmartPointer<IAAFMob> pCompositionMob;
  IAAFSmartPointer<IAAFMob> pReferencedMasterMob;
  IAAFSmartPointer<IAAFDataDef> pDataDef;
};

void CreateSimpleAAFFile( aafCharacter* pFileName,
			  aafUID_constref fileKind,
			  const testRawStorageType_t rawStorageType,
			  aafProductIdentification_constref productIdentification,
			  SimpleFilePointers* pFilePointers );

void ReadSimpleAAFFile( aafCharacter* pFileName,
		        SimpleFilePointers* pFilePointers );


IAAFSmartPointer<IAAFMobSlot> GetSlotById( IAAFSmartPointer<IAAFMob>& pMob, aafSlotID_t id );

IAAFSmartPointer<IAAFSourceClip> GetSourceClipFromSlot( IAAFSmartPointer<IAAFMob>& pMob, aafSlotID_t id );

// Chains a source mob on to the source clip attached to slot 1 of the
// master mob in the SimpleFilePointer structure. The caller is
// responsible for adding the required essence descriptor.
IAAFSmartPointer<IAAFSourceMob> AddChainedSourceMob( SimpleFilePointers* pFilePointers );

// convenient error handlers.
void CheckResult(AAFRESULT r);

void CheckExpression(bool expression, AAFRESULT r = AAFRESULT_TEST_FAILED);

// initialValue is the expected value of a required, and therefore
// existing, property, before it gets changed to testValue.
template <typename Interface,
          typename PropertyType,
          typename Setter,
          typename Getter>
HRESULT TestSimplePropertyAccess(
    Setter setter,
    Getter getter,
    Interface* pInterface,
    PropertyType initialValue,
    PropertyType testValue,
    PropertyType anotherValue,
    const bool requiredProperty,
    testMode_t mode)
{
    assert(testValue != anotherValue);
    assert(!requiredProperty || anotherValue != initialValue);
    assert(!requiredProperty || initialValue != testValue);

    HRESULT  hr = S_OK;


    try
    {
        if(mode == kAAFUnitTestReadWrite)
        {
            if(requiredProperty)
            {
                // GetXXX() should succeed because XXX
                // is a required property.
                PropertyType  value = anotherValue;
                CheckResult((pInterface->*getter)(&value));
                CheckExpression(value == initialValue);
            }
            else
            {
                // GetXXX() should fail because XXX is optional and not present.
                PropertyType  value = anotherValue;
                hr = (pInterface->*getter)(&value);
                CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
                CheckExpression(value == anotherValue);
            }

            // GetXXX() should fail if function arguments are invalid.
            hr = (pInterface->*getter)(NULL);
            CheckExpression(hr == AAFRESULT_NULL_PARAM);

            // SetXXX() should always succeed
            CheckResult((pInterface->*setter)(testValue));
        }

        if(mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly)
        {
            // GetXXX() should succeed.
            PropertyType  value = anotherValue;
            CheckResult((pInterface->*getter)(&value));
            CheckExpression(value == testValue);
        }


        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch(HRESULT e)
    {
        hr = e;
    }


    return hr;
}


template <typename Interface,
          typename Setter,
          typename Getter,
          typename Sizer>
HRESULT TestStringPropertyAccess(
    Setter setter,
    Getter getter,
    Sizer sizer,
    Interface* pInterface,
    const aafCharacter* pInitialValue,
    const aafCharacter* pTestValue,
    const bool requiredProperty,
    testMode_t mode)
{
    // Only required properties have an initial value
    assert(requiredProperty || !pInitialValue);

    HRESULT  hr = S_OK;

    try
    {
        if(mode == kAAFUnitTestReadWrite)
        {
            if(requiredProperty)
            {
                // Check the length of the string value of existing required
                // property
                const size_t  expectedBufLen =
                    (wcslen(pInitialValue) + 1) *
                    sizeof(pInitialValue[0]);
                aafUInt32  bufLen = static_cast<aafUInt32>(expectedBufLen) + 7;
                CheckResult((pInterface->*sizer)(&bufLen));
                CheckExpression(bufLen == expectedBufLen);

                // Small output buffer should be rejected when getting
                // value of existing required property
                aafCharacter smallBuffer = L'Q';
                assert(smallBuffer != pInitialValue[0]);
                assert(sizeof(smallBuffer) < bufLen);
                CheckExpression((pInterface->*getter)(
                    &smallBuffer, sizeof(smallBuffer)) == AAFRESULT_SMALLBUF);
                // A failed call should not alter the output buffer
                CheckExpression(smallBuffer == L'Q');

                aafCharacter  buffer[512] = {0};
                assert(bufLen <= sizeof(buffer));
                CheckResult((pInterface->*getter)(buffer, sizeof(buffer)));
                CheckExpression(wcscmp(buffer, pInitialValue) == 0);
            }
            else
            {
                // GetXXXBufLen() should fail because XXX is optional
                // and not present.
                aafUInt32  bufLen = 47;
                hr = (pInterface->*sizer)(&bufLen);
                CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
                // A failed call should not alter the output buffer
                CheckExpression(bufLen == 47);

                // GetXXX() should fail because XXX is optional
                // and not present.
                aafCharacter dummyBuffer = L'Q';
                hr = (pInterface->*getter)(&dummyBuffer, sizeof(dummyBuffer));
                CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
                // A failed call should not alter the output buffer
                CheckExpression(dummyBuffer == L'Q');
            }

            // Invalid arguments should be rejected regardless of
            // whether a property is present.
            CheckExpression((pInterface->*sizer)(NULL) ==
                            AAFRESULT_NULL_PARAM);
            CheckExpression((pInterface->*getter)(NULL, 2048) ==
                            AAFRESULT_NULL_PARAM);

            // Attempt to set the value whose size is larger
            // than UINT16_MAX should fail
            const size_t charSize = 2; // Typical size of stored character
            const size_t largeStringLen =
                aafUInt16(0xffff) / charSize +
                (aafUInt16(0xffff) % charSize ? 1 : 0);
            aafCharacter* pLargeString = new aafCharacter[largeStringLen + 1];
            wmemset(pLargeString, L'z', largeStringLen);
            pLargeString[largeStringLen] = L'\0';
            hr = (pInterface->*setter)(pLargeString);
            delete [] pLargeString;
            pLargeString = NULL;
            CheckExpression(hr == AAFRESULT_BAD_SIZE);

            // SetXXX() should succeed
            CheckResult((pInterface->*setter)(pTestValue));
        }

        if(mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly)
        {
            // Check the length of the string value of existing required
            // property
            const size_t  expectedBufLen =
                (wcslen(pTestValue) + 1) * sizeof(pTestValue[0]);
            aafUInt32  bufLen = static_cast<aafUInt32>(expectedBufLen) + 17;
            CheckResult((pInterface->*sizer)(&bufLen));
            CheckExpression(bufLen == expectedBufLen);

            // GetXXX() should succeed.
            aafCharacter  buffer[512] = {0};
            assert(bufLen <= sizeof(buffer));
            CheckResult((pInterface->*getter)(buffer, sizeof(buffer)));
            CheckExpression(wcscmp(buffer, pTestValue) == 0);
        }


        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch(HRESULT e)
    {
        hr = e;
    }


    return hr;
}


template <typename Interface,
          typename Setter,
          typename Getter,
          typename Sizer>
HRESULT TestStringPropertyAccess(
    Setter setter,
    Getter getter,
    Sizer sizer,
    Interface* pInterface,
    const char* pInitialValue,
    const char* pTestValue,
    const bool requiredProperty,
    testMode_t mode)
{
    // Only required properties have an initial value
    assert(requiredProperty || !pInitialValue);

    HRESULT  hr = S_OK;

    try
    {
        if(mode == kAAFUnitTestReadWrite)
        {
            if(requiredProperty)
            {
                // Check the length of the string value of existing required
                // property
                const size_t  expectedBufLen =
                    (strlen((const char*)pInitialValue) + 1) *
                    sizeof(pInitialValue[0]);
                aafUInt32  bufLen = static_cast<aafUInt32>(expectedBufLen) + 7;
                CheckResult((pInterface->*sizer)(&bufLen));
                CheckExpression(bufLen == expectedBufLen);

                // Small output buffer should be rejected when getting
                // value of existing required property
                char smallBuffer = 'Q';
                assert(smallBuffer != pInitialValue[0]);
                assert(sizeof(smallBuffer) < bufLen);
                CheckExpression((pInterface->*getter)(
                    &smallBuffer, sizeof(smallBuffer)) == AAFRESULT_SMALLBUF);
                // A failed call should not alter the output buffer
                CheckExpression(smallBuffer == 'Q');

                char  buffer[512] = {0};
                assert(bufLen <= sizeof(buffer));
                CheckResult((pInterface->*getter)(buffer, sizeof(buffer)));
                CheckExpression(strcmp((const char*)buffer, (const char*)pInitialValue) == 0);
            }
            else
            {
                // GetXXXBufLen() should fail because XXX is optional
                // and not present.
                aafUInt32  bufLen = 47;
                hr = (pInterface->*sizer)(&bufLen);
                CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
                // A failed call should not alter the output buffer
                CheckExpression(bufLen == 47);

                // GetXXX() should fail because XXX is optional
                // and not present.
                char dummyBuffer = 'Q';
                hr = (pInterface->*getter)(&dummyBuffer, sizeof(dummyBuffer));
                CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
                // A failed call should not alter the output buffer
                CheckExpression(dummyBuffer == 'Q');
            }

            // Invalid arguments should be rejected regardless of
            // whether a property is present.
            CheckExpression((pInterface->*sizer)(NULL) ==
                            AAFRESULT_NULL_PARAM);
            CheckExpression((pInterface->*getter)(NULL, 2048) ==
                            AAFRESULT_NULL_PARAM);

            // SetXXX() should succeed
            CheckResult((pInterface->*setter)(pTestValue));
        }

        if(mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly)
        {
            // Check the length of the string value of existing required
            // property
            const size_t  expectedBufLen =
                (strlen((const char*)pTestValue) + 1) * sizeof(pTestValue[0]);
            aafUInt32  bufLen = static_cast<aafUInt32>(expectedBufLen) + 17;
            CheckResult((pInterface->*sizer)(&bufLen));
            CheckExpression(bufLen == expectedBufLen);

            // GetXXX() should succeed.
            char  buffer[512] = {0};
            assert(bufLen <= sizeof(buffer));
            CheckResult((pInterface->*getter)(buffer, sizeof(buffer)));
            CheckExpression(strcmp((const char*)buffer, (const char*)pTestValue) == 0);
        }


        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch(HRESULT e)
    {
        hr = e;
    }


    return hr;
}


} // end of namespace mtc

#endif
