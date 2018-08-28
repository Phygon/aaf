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
// The Original Code of this file is Copyright 1998-2018, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
// The Initial Developer of the Original Code of this file and the
// licensor of the Advanced Media Workflow Association is
// Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

#include <iostream>

using namespace std;

#include <assert.h>
#include <string.h>

#include "AAF.h"
#include "AAFFileKinds.h"
#include "AAFResult.h"
#include "AAFPropertyDefs.h"
#include "AAFSmartPointer.h"

#include "CAAFBuiltinDefs.h"
#include "ModuleTestsCommon.h"
using namespace mtc;



struct CAAFJPEG2000SubDescriptorTestFixture
{
    aafMobID_t              sourceMobID;
};

static const CAAFJPEG2000SubDescriptorTestFixture  gTestData = 
{
    { { 0x06, 0x0c, 0x2b, 0x34,
        0x02, 0x05, 0x11, 0x01,
        0x01, 0x00, 0x10, 0x00 },
      0x13, 0x00, 0x00, 0x00,
      { 0xf6d43ded, 0xa5aa, 0x4a05,
        { 0xa2, 0x84, 0x37, 0x8f,
          0x94, 0x16, 0xd0, 0x56 } } } // sourceMobID
};



static HRESULT Test_IAAFJPEG2000SubDescriptor_Uninitialized(
    IAAFJPEG2000SubDescriptor* pJPEG2000Desc )
{
    HRESULT  hr = S_OK;


    try
    {
        {
            hr = pJPEG2000Desc->SetRsiz( 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt16  v = 88;
            hr = pJPEG2000Desc->GetRsiz( &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetXsiz( 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 88;
            hr = pJPEG2000Desc->GetXsiz( &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetYsiz( 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 88;
            hr = pJPEG2000Desc->GetYsiz( &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetXOsiz( 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 88;
            hr = pJPEG2000Desc->GetXOsiz( &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetYOsiz( 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 88;
            hr = pJPEG2000Desc->GetYOsiz( &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetXTsiz( 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 88;
            hr = pJPEG2000Desc->GetXTsiz( &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetYTsiz( 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 88;
            hr = pJPEG2000Desc->GetYTsiz( &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }

        {
            hr = pJPEG2000Desc->SetXTOsiz( 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 88;
            hr = pJPEG2000Desc->GetXTOsiz( &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetYTOsiz( 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt32  v = 88;
            hr = pJPEG2000Desc->GetYTOsiz( &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetCsiz( 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt16  v = 88;
            hr = pJPEG2000Desc->GetCsiz( &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetComponentSsizAt( 0, 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 88;
            hr = pJPEG2000Desc->GetComponentSsizAt( 0, &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetComponentXRsizAt( 0, 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 88;
            hr = pJPEG2000Desc->GetComponentXRsizAt( 0, &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            hr = pJPEG2000Desc->SetComponentYRsizAt( 0, 17 );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            aafUInt8  v = 88;
            hr = pJPEG2000Desc->GetComponentYRsizAt( 0, &v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(v == 88 );
        }
        {
            aafUInt8  dummy[] = {0x99, 0x22, 0x77, 0x33, 0x11};
            hr = pJPEG2000Desc->SetCodingStyleDefault( 5, dummy );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            const aafUInt8 init[] = {0x44, 0x55, 0x66, 0x88, 0xAA};
            aafUInt8  v[]         = {0x44, 0x55, 0x66, 0x88, 0xAA};
            hr = pJPEG2000Desc->GetCodingStyleDefault( 5, v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(memcmp(v, init, 5) == 0);
        }
        {
            aafUInt8  dummy[] = {0x44, 0x88};
            hr = pJPEG2000Desc->SetQuantizationDefault( 2, dummy );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            const aafUInt8 init[] = {0x55, 0xCC};
            aafUInt8  v[]         = {0x55, 0xCC};
            hr = pJPEG2000Desc->GetQuantizationDefault( 2, v );
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(memcmp(v, init, 2) == 0);
        }
        {
            IAAFSmartPointer<IAAFJPEG2000SubDescriptor2> pJPEG2000Desc2;
            CheckResult(pJPEG2000Desc->QueryInterface(IID_IAAFJPEG2000SubDescriptor2,
                                                      (void **)&pJPEG2000Desc2));

            aafRGBAComponent_t dummy[] = {{kAAFCompAlpha, 16}, {kAAFCompNull, 0}};
            hr = pJPEG2000Desc2->SetJ2CLayout(2, dummy);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);

            aafUInt32 elementCount = 93;
            hr = pJPEG2000Desc2->CountJ2CLayoutElements(&elementCount);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
            CheckExpression(elementCount == 93);

            const aafRGBAComponent_t init[] = {{kAAFCompPalette, 13}, {kAAFCompPalette, 7}};
            aafRGBAComponent_t v[]          = {{kAAFCompPalette, 13}, {kAAFCompPalette, 7}};
            hr = pJPEG2000Desc2->GetJ2CLayout(2, v);
            CheckExpression(hr == AAFRESULT_NOT_INITIALIZED);
			for (size_t i=0; i<2; i++)
			{
				CheckExpression(v[i].Code == init[i].Code);
				CheckExpression(v[i].Size == init[i].Size);
			}
        }

        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch( HRESULT e )
    {
        hr = e;
    }


    return hr;
}



template <typename PropertyType>
HRESULT Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
    IAAFJPEG2000SubDescriptor* pJPEG2000Desc,
    HRESULT (STDMETHODCALLTYPE IAAFJPEG2000SubDescriptor::*setter)(PropertyType),
    HRESULT (STDMETHODCALLTYPE IAAFJPEG2000SubDescriptor::*getter)(PropertyType*),
    const PropertyType testValue,
    const bool requiredProperty,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {
        const PropertyType bogusValue = 39;


        if( mode == kAAFUnitTestReadWrite )
        {
            if( requiredProperty )
            {
                // GetXXX() should succeed because XXX
                // is a required property.
                PropertyType  value = bogusValue;
                CheckResult((pJPEG2000Desc->*getter)( &value ));
                CheckExpression(value != bogusValue);
            }

            // GetXXX() should fail if function arguments are invalid.
            hr = (pJPEG2000Desc->*getter)( 0 );
            CheckExpression(hr == AAFRESULT_NULL_PARAM);

            // SetXXX() should always succeed
            CheckResult((pJPEG2000Desc->*setter)( testValue ));
        }

        if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
        {
            // GetXXX() should succeed.
            PropertyType  value = bogusValue;
            CheckResult((pJPEG2000Desc->*getter)( &value ));
            CheckExpression(value == testValue);
        }


        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch( HRESULT e )
    {
        hr = e;
    }


    return hr;
}



static HRESULT Test_IAAFJPEG2000SubDescriptor_PictureComponentSizing(
    IAAFJPEG2000SubDescriptor* pJPEG2000Desc,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {
        // Get the component count (Csiz) that should be set in one of
        // the previous tests.
        aafUInt16 componentCount = 0;
        CheckResult(pJPEG2000Desc->GetCsiz( &componentCount ));
        // Make sure the desciptor's component count is sufficiently
        // large in order to test the PictureComponentSizing methods.
        assert( componentCount > 3 );

        for( int index=componentCount; index>0; index--)
        {
            // Base the Ssiz, XRsiz and YRsiz values on th eindex
            const aafUInt8 theSsiz = index;
            const aafUInt8 theXRsiz = 33 + index;
            const aafUInt8 theYRsiz = 66 + index;
            assert( theSsiz > 0 && theXRsiz > 0 && theYRsiz > 0 );

            if( mode == kAAFUnitTestReadWrite )
            {
                CheckResult(pJPEG2000Desc->SetComponentYRsizAt( index-1, theYRsiz ));
                CheckResult(pJPEG2000Desc->SetComponentXRsizAt( index-1, theXRsiz ));
                CheckResult(pJPEG2000Desc->SetComponentSsizAt( index-1, theSsiz ));
            }
            if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
            {
                aafUInt8 v = 0;
                CheckResult(pJPEG2000Desc->GetComponentSsizAt( index-1, &v ));
                CheckExpression(v == theSsiz);
                v = 0;
                CheckResult(pJPEG2000Desc->GetComponentXRsizAt( index-1, &v ));
                CheckExpression(v == theXRsiz);
                v = 0;
                CheckResult(pJPEG2000Desc->GetComponentYRsizAt( index-1, &v ));
                CheckExpression(v == theYRsiz);
            }
        }

        if( mode == kAAFUnitTestReadWrite )
        {
            // Attempt to specify too many components
            const aafUInt16 tooManyComponents = 21845 + 1;
            hr = pJPEG2000Desc->SetCsiz( tooManyComponents );
            CheckExpression(hr == AAFRESULT_BAD_SIZE);

            // Attempt to set at out-of-range index
            hr = pJPEG2000Desc->SetComponentSsizAt( componentCount, 35 );
            hr = pJPEG2000Desc->SetComponentXRsizAt( componentCount, 75 );
            hr = pJPEG2000Desc->SetComponentYRsizAt( componentCount, 95 );
            CheckExpression(hr == AAFRESULT_BADINDEX);

            // Make sure SetComponentSsizAt() doesn't somehow change
            // the component count
            aafUInt16 anotherComponentCount = 0;
            CheckResult(pJPEG2000Desc->GetCsiz( &anotherComponentCount ));
            CheckExpression(componentCount == anotherComponentCount);

            // Grow the component count by 2
            CheckResult(pJPEG2000Desc->SetCsiz( componentCount + 2 ));
            anotherComponentCount = 0;
            CheckResult(pJPEG2000Desc->GetCsiz( &anotherComponentCount ));
            CheckExpression(componentCount + 2 == anotherComponentCount);

            // Set Ssiz for the 2nd new component
            CheckResult(pJPEG2000Desc->SetComponentSsizAt( componentCount+1, 35 ));
            // Getting Ssiz for the 1nd new component should succeed however
            // the returned value is undefined because it wasn't set.
            aafUInt8 ssiz1 = 0;
            CheckResult(pJPEG2000Desc->GetComponentSsizAt( componentCount, &ssiz1 ));
            // Get Ssiz for the 2nd new component
            aafUInt8 ssiz2 = 0;
            CheckResult(pJPEG2000Desc->GetComponentSsizAt( componentCount+1, &ssiz2 ));
            CheckExpression(ssiz2 == 35);

            // Set XRsiz for the 2nd new component
            CheckResult(pJPEG2000Desc->SetComponentXRsizAt( componentCount+1, 75 ));
            // Getting XRsiz for the 1nd new component should succeed however
            // the returned value is undefined because it wasn't set.
            aafUInt8 xrsiz1 = 0;
            CheckResult(pJPEG2000Desc->GetComponentXRsizAt( componentCount, &xrsiz1 ));
            // Get XRsiz for the 2nd new component
            aafUInt8 xrsiz2 = 0;
            CheckResult(pJPEG2000Desc->GetComponentXRsizAt( componentCount+1, &xrsiz2 ));
            CheckExpression(xrsiz2 == 75);

            // Set YRsiz for the 2nd new component
            CheckResult(pJPEG2000Desc->SetComponentYRsizAt( componentCount+1, 95 ));
            // Getting YRsiz for the 1nd new component should succeed however
            // the returned value is undefined because it wasn't set.
            aafUInt8 yrsiz1 = 0;
            CheckResult(pJPEG2000Desc->GetComponentYRsizAt( componentCount, &yrsiz1 ));
            // Get YRsiz for the 2nd new component
            aafUInt8 yrsiz2 = 0;
            CheckResult(pJPEG2000Desc->GetComponentYRsizAt( componentCount+1, &yrsiz2 ));
            CheckExpression(yrsiz2 == 95);

            // Truncate the component count by 2
            CheckResult(pJPEG2000Desc->SetCsiz( componentCount ));
            anotherComponentCount = 0;
            CheckResult(pJPEG2000Desc->GetCsiz( &anotherComponentCount ));
            CheckExpression(componentCount == anotherComponentCount);
            aafUInt8 ssiz3 = 0;
            hr = pJPEG2000Desc->GetComponentSsizAt( componentCount, &ssiz3 );
            CheckExpression(hr == AAFRESULT_BADINDEX);
            aafUInt8 xrsiz3 = 0;
            hr = pJPEG2000Desc->GetComponentXRsizAt( componentCount, &xrsiz3 );
            CheckExpression(hr == AAFRESULT_BADINDEX);
            aafUInt8 yrsiz3 = 0;
            hr = pJPEG2000Desc->GetComponentYRsizAt( componentCount, &yrsiz3 );
            CheckExpression(hr == AAFRESULT_BADINDEX);
        }

        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch( HRESULT e )
    {
        hr = e;
    }


    return hr;
}



// TODO: Need single routine that could test both
// CodingStyleDefault and QuantizationDefault.
static HRESULT Test_IAAFJPEG2000SubDescriptor_CodingStyleDefault(
    IAAFJPEG2000SubDescriptor* pJPEG2000Desc,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {
        const aafUInt32 minSize = 5; // per standard

        static aafUInt8  testCodingStyle[] =
            {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
        static const aafUInt32 testCodingStyleSize =
            sizeof(testCodingStyle) / sizeof(testCodingStyle[0]);
        assert(testCodingStyleSize >= minSize);

        static aafUInt8  bogusCodingStyle[] =
            {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9};
        static const aafUInt32 bogusCodingStyleSize =
            sizeof(bogusCodingStyle) / sizeof(bogusCodingStyle[0]);
        assert(bogusCodingStyleSize >= minSize);

        if( mode == kAAFUnitTestReadWrite )
        {
            // GetCodingStyleDefaultBufLen() should fail if the property not present.
            aafUInt32  dummySize = 98;
            hr = pJPEG2000Desc->GetCodingStyleDefaultBufLen( &dummySize );
            CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
            CheckExpression(dummySize == 98);

            // GetCodingStyleDefaultBufLen() should fail if function arguments are invalid.
            hr = pJPEG2000Desc->GetCodingStyleDefaultBufLen( NULL );
            CheckExpression( hr == AAFRESULT_NULL_PARAM);

            // GetCodingStyleDefault() should fail if the property not present.
            aafUInt8  codingStyleDefault[minSize];
            memcpy(codingStyleDefault, bogusCodingStyle, minSize);
            hr = pJPEG2000Desc->GetCodingStyleDefault( minSize, codingStyleDefault );
            CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
            CheckExpression(memcmp(codingStyleDefault, bogusCodingStyle, minSize) == 0);

            // GetCodingStyleDefault() should fail if function arguments are invalid.
            memcpy(codingStyleDefault, bogusCodingStyle, minSize);
            hr = pJPEG2000Desc->GetCodingStyleDefault( minSize, NULL );
            CheckExpression(hr == AAFRESULT_NULL_PARAM);

            // SetCodingStyleDefault() should always succeed
            CheckResult(pJPEG2000Desc->SetCodingStyleDefault(
                testCodingStyleSize,
                testCodingStyle ));

            // Attempt to pass fewer bytes than the required minimum to
            // SetCodingStyleDefault().
            // That the property value remains intact will be tested later
            // when the property is read back.
            assert(bogusCodingStyleSize >= (minSize-1));
            hr = pJPEG2000Desc->SetCodingStyleDefault(
                minSize-1,
                bogusCodingStyle );
            CheckExpression(hr == AAFRESULT_ILLEGAL_VALUE);

            // Attempt to pass fewer than 65535 bytes to SetCodingStyleDefault().
            // That the property value remains intact will be tested later
            // when the property is read back.
            hr = pJPEG2000Desc->SetCodingStyleDefault(
                65535+1,
                bogusCodingStyle );
            CheckExpression(hr == AAFRESULT_BAD_SIZE);
        }


        if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
        {
            // GetCodingStyleDefault() should succeed.
            aafUInt8  codingStyleDefault[testCodingStyleSize];
            memcpy(codingStyleDefault,
                   bogusCodingStyle,
                   testCodingStyleSize);
            hr = pJPEG2000Desc->GetCodingStyleDefault( testCodingStyleSize-1, codingStyleDefault );
            CheckExpression(hr == AAFRESULT_SMALLBUF);
            CheckExpression(memcmp(codingStyleDefault, bogusCodingStyle, testCodingStyleSize) == 0);

            aafUInt32 codingStyleDefaultSize = 0;
            CheckResult(pJPEG2000Desc->GetCodingStyleDefaultBufLen(&codingStyleDefaultSize));
            CheckExpression(codingStyleDefaultSize == testCodingStyleSize);

            CheckResult(pJPEG2000Desc->GetCodingStyleDefault(testCodingStyleSize, codingStyleDefault));
            CheckExpression(memcmp(codingStyleDefault, testCodingStyle, testCodingStyleSize) == 0);
        }


        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch( HRESULT e )
    {
        hr = e;
    }


    return hr;
}



// TODO: Need single routine that could test both
// CodingStyleDefault and QuantizationDefault.
static HRESULT Test_IAAFJPEG2000SubDescriptor_QuantizationDefault(
    IAAFJPEG2000SubDescriptor* pJPEG2000Desc,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {
        const aafUInt32 minSize = 2; // per standard

        static aafUInt8  testQuantizationStyle[] =
            {0x44, 0x55, 0x66, 0x77};
        static const aafUInt32 testQuantizationStyleSize =
            sizeof(testQuantizationStyle) / sizeof(testQuantizationStyle[0]);
        assert(testQuantizationStyleSize >= minSize);

        static aafUInt8  bogusQuantizationStyle[] =
            {0xFC, 0xFB, 0xFA, 0xF9};
        static const aafUInt32 bogusQuantizationStyleSize =
            sizeof(bogusQuantizationStyle) / sizeof(bogusQuantizationStyle[0]);
        assert(bogusQuantizationStyleSize >= minSize);

        if( mode == kAAFUnitTestReadWrite )
        {
            // GetQuantizationDefaultBufLen() should fail if the property not present.
            aafUInt32  dummySize = 98;
            hr = pJPEG2000Desc->GetQuantizationDefaultBufLen( &dummySize );
            CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
            CheckExpression(dummySize == 98);

            // GetQuantizationDefaultBufLen() should fail if function arguments are invalid.
            hr = pJPEG2000Desc->GetQuantizationDefaultBufLen( NULL );
            CheckExpression( hr == AAFRESULT_NULL_PARAM);

            // GetQuantizationDefault() should fail if the property not present.
            aafUInt8  quantizationStyleDefault[minSize];
            memcpy(quantizationStyleDefault, bogusQuantizationStyle, minSize);
            hr = pJPEG2000Desc->GetQuantizationDefault( minSize, quantizationStyleDefault );
            CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
            CheckExpression(memcmp(quantizationStyleDefault, bogusQuantizationStyle, minSize) == 0);

            // GetQuantizationDefault() should fail if function arguments are invalid.
            memcpy(quantizationStyleDefault, bogusQuantizationStyle, minSize);
            hr = pJPEG2000Desc->GetQuantizationDefault( minSize, NULL );
            CheckExpression(hr == AAFRESULT_NULL_PARAM);

            // SetQuantizationDefault() should always succeed
            CheckResult(pJPEG2000Desc->SetQuantizationDefault(
                testQuantizationStyleSize,
                testQuantizationStyle ));

            // Attempt to pass fewer bytes than the required minimum to
            // SetQuantizationDefault().
            // That the property value remains intact will be tested later
            // when the property is read back.
            assert(bogusQuantizationStyleSize >= (minSize-1));
            hr = pJPEG2000Desc->SetQuantizationDefault(
                minSize-1,
                bogusQuantizationStyle );
            CheckExpression(hr == AAFRESULT_ILLEGAL_VALUE);

            // Attempt to pass fewer than 65535 bytes to SetQuantizationDefault().
            // That the property value remains intact will be tested later
            // when the property is read back.
            hr = pJPEG2000Desc->SetQuantizationDefault(
                65535+1,
                bogusQuantizationStyle );
            CheckExpression(hr == AAFRESULT_BAD_SIZE);
        }


        if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
        {
            // GetQuantizationDefault() should succeed.
            aafUInt8  quantizationStyleDefault[testQuantizationStyleSize];
            memcpy(quantizationStyleDefault,
                   bogusQuantizationStyle,
                   testQuantizationStyleSize);
            hr = pJPEG2000Desc->GetQuantizationDefault( testQuantizationStyleSize-1, quantizationStyleDefault );
            CheckExpression(hr == AAFRESULT_SMALLBUF);
            CheckExpression(memcmp(quantizationStyleDefault, bogusQuantizationStyle, testQuantizationStyleSize) == 0);

            aafUInt32 quantizationStyleDefaultSize = 0;
            CheckResult(pJPEG2000Desc->GetQuantizationDefaultBufLen(&quantizationStyleDefaultSize));
            CheckExpression(quantizationStyleDefaultSize == testQuantizationStyleSize);

            CheckResult(pJPEG2000Desc->GetQuantizationDefault(testQuantizationStyleSize, quantizationStyleDefault));
            CheckExpression(memcmp(quantizationStyleDefault, testQuantizationStyle, testQuantizationStyleSize) == 0);
        }


        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch( HRESULT e )
    {
        hr = e;
    }


    return hr;
}



static HRESULT Test_IAAFJPEG2000SubDescriptor_J2CLayout(
    IAAFJPEG2000SubDescriptor* pSubDesc,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {

        IAAFSmartPointer<IAAFJPEG2000SubDescriptor2> pJPEG2000Desc2;
        CheckResult(pSubDesc->QueryInterface(IID_IAAFJPEG2000SubDescriptor2,
                                                    (void **)&pJPEG2000Desc2));

		const aafRGBAComponent_t testJ2CLayout[] = {{kAAFCompAlpha, 8}, {kAAFCompBlue, 8}, {kAAFCompGreen, 8}, {kAAFCompRed, 8}, {kAAFCompFill, 8} };
        const aafUInt32 testJ2CLayoutElementCount = sizeof(testJ2CLayout) / sizeof(testJ2CLayout[0]);

        const aafUInt32  bogusJ2CLayoutElementCount = 8;
        const aafRGBAComponent_t bogusJ2CLayout[bogusJ2CLayoutElementCount] =
            {{kAAFCompPalette, 13}, {kAAFCompPalette, 13}, {kAAFCompPalette, 13}, {kAAFCompPalette, 13},
                {kAAFCompPalette, 13}, {kAAFCompPalette, 13}, {kAAFCompPalette, 13}, {kAAFCompPalette, 13}};

		if( mode == kAAFUnitTestReadWrite )
        {
            // CountJ2CLayoutElements() should fail if the property not present.
            aafUInt32  dummyCount = 74;
            hr = pJPEG2000Desc2->CountJ2CLayoutElements( &dummyCount );
            CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
            CheckExpression(dummyCount == 74);

            // CountJ2CLayoutElements() should fail if function arguments are invalid.
            hr = pJPEG2000Desc2->CountJ2CLayoutElements( NULL );
            CheckExpression( hr == AAFRESULT_NULL_PARAM);

			aafRGBAComponent_t  j2cLayout[MAX_NUM_RGBA_COMPS];
            memcpy(j2cLayout, bogusJ2CLayout, sizeof(aafRGBAComponent_t)*MAX_NUM_RGBA_COMPS);

			// GetJ2CLayout() should fail if the property not present.
            hr = pJPEG2000Desc2->GetJ2CLayout( bogusJ2CLayoutElementCount, j2cLayout );
            CheckExpression(hr == AAFRESULT_PROP_NOT_PRESENT);
			for (size_t i=0; i<bogusJ2CLayoutElementCount; i++)
			{
				CheckExpression(j2cLayout[i].Code == bogusJ2CLayout[i].Code);
				CheckExpression(j2cLayout[i].Size == bogusJ2CLayout[i].Size);
			}

            // GetJ2CLayout() should fail if function arguments are invalid.
            hr = pJPEG2000Desc2->GetJ2CLayout( 2, NULL );
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pJPEG2000Desc2->GetJ2CLayout( MAX_NUM_RGBA_COMPS+1, j2cLayout );
            CheckExpression(hr == AAFRESULT_INVALID_PARAM);
			for (size_t i=0; i<bogusJ2CLayoutElementCount; i++)
			{
				CheckExpression(j2cLayout[i].Code == bogusJ2CLayout[i].Code);
				CheckExpression(j2cLayout[i].Size == bogusJ2CLayout[i].Size);
			}


            // SetJ2CLayout() should fail if function arguments are invalid.
            hr = pJPEG2000Desc2->SetJ2CLayout( 2, NULL );
            CheckExpression(hr == AAFRESULT_NULL_PARAM);
            hr = pJPEG2000Desc2->SetJ2CLayout( MAX_NUM_RGBA_COMPS+1, bogusJ2CLayout );
            CheckExpression(hr == AAFRESULT_INVALID_PARAM);


			// SetJ2CLayout() should pad supplied layout array up to MAX_NUM_RGBA_COMPS elements with {0,0} terminator.
            const aafRGBAComponent_t shortJ2CLayout[] = {{kAAFCompBlue, 16}, {kAAFCompGreen, 16}};
            const aafUInt32 shortJ2CLayoutElementCount = sizeof(shortJ2CLayout) / sizeof(shortJ2CLayout[0]);
            CheckResult(pJPEG2000Desc2->SetJ2CLayout( shortJ2CLayoutElementCount, shortJ2CLayout ));

			aafUInt32 j2cLayoutElementCount = 0;
			CheckResult(pJPEG2000Desc2->CountJ2CLayoutElements( &j2cLayoutElementCount ));
            CheckExpression(j2cLayoutElementCount == shortJ2CLayoutElementCount);

            CheckResult(pJPEG2000Desc2->GetJ2CLayout( MAX_NUM_RGBA_COMPS, j2cLayout ));
            for (size_t i=0; i<MAX_NUM_RGBA_COMPS; i++)
            {
                if (i<shortJ2CLayoutElementCount)
                {
                    CheckExpression(j2cLayout[i].Code == shortJ2CLayout[i].Code);
                    CheckExpression(j2cLayout[i].Size == shortJ2CLayout[i].Size);
                }
                else
                {
                    CheckExpression(j2cLayout[i].Code == kAAFCompNull);
                    CheckExpression(j2cLayout[i].Size == 0);
                }
            }


			// CountJ2CLayoutElements() should ignore layout elements following {0,0} terminator.
			const aafRGBAComponent_t invalidJ2CLayout[] = {{kAAFCompRed, 10}, {kAAFCompNull, 0}, {kAAFCompAlpha, 10} };
            const aafUInt32 invalidJ2CLayoutElementCount = sizeof(invalidJ2CLayout) / sizeof(invalidJ2CLayout[0]);
            CheckResult(pJPEG2000Desc2->SetJ2CLayout( invalidJ2CLayoutElementCount, invalidJ2CLayout ));

			j2cLayoutElementCount = 0;
			CheckResult(pJPEG2000Desc2->CountJ2CLayoutElements( &j2cLayoutElementCount ));
            CheckExpression(j2cLayoutElementCount == 1);

            memcpy(j2cLayout, bogusJ2CLayout, sizeof(aafRGBAComponent_t)*MAX_NUM_RGBA_COMPS);
            CheckResult(pJPEG2000Desc2->GetJ2CLayout( MAX_NUM_RGBA_COMPS, j2cLayout ));
            for (size_t i=0; i<MAX_NUM_RGBA_COMPS; i++)
            {
                if (i<invalidJ2CLayoutElementCount)
                {
                    CheckExpression(j2cLayout[i].Code == invalidJ2CLayout[i].Code);
                    CheckExpression(j2cLayout[i].Size == invalidJ2CLayout[i].Size);
                }
                else
                {
                    CheckExpression(j2cLayout[i].Code == kAAFCompNull);
                    CheckExpression(j2cLayout[i].Size == 0);
                }
            }


			// Use SetJ2CLayout() to set the final layout to be stored in the file.
            CheckResult(pJPEG2000Desc2->SetJ2CLayout( testJ2CLayoutElementCount, testJ2CLayout ));
		}

		if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
		{
			aafUInt32 j2cLayoutElementCount = 0;
			CheckResult(pJPEG2000Desc2->CountJ2CLayoutElements( &j2cLayoutElementCount ));
            CheckExpression(j2cLayoutElementCount == testJ2CLayoutElementCount);

			aafRGBAComponent_t  j2cLayout[MAX_NUM_RGBA_COMPS];
            memcpy(j2cLayout, bogusJ2CLayout, sizeof(aafRGBAComponent_t)*MAX_NUM_RGBA_COMPS);

            // GetJ2CLayout() should fail if function arguments are invalid (specified output buffer cannot fit all available data).
            hr = pJPEG2000Desc2->GetJ2CLayout( j2cLayoutElementCount-1, j2cLayout );
			CheckExpression(hr == AAFRESULT_SMALLBUF);

			CheckResult(pJPEG2000Desc2->GetJ2CLayout( MAX_NUM_RGBA_COMPS, j2cLayout ));
            for (size_t i=0; i<MAX_NUM_RGBA_COMPS; i++)
            {
                if (i<testJ2CLayoutElementCount)
                {
                    CheckExpression(j2cLayout[i].Code == testJ2CLayout[i].Code);
                    CheckExpression(j2cLayout[i].Size == testJ2CLayout[i].Size);
                }
                else
                {
                    CheckExpression(j2cLayout[i].Code == kAAFCompNull);
                    CheckExpression(j2cLayout[i].Size == 0);
                }
            }
		}

        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch( HRESULT e )
    {
        hr = e;
    }


    return hr;
}



static HRESULT Test_IAAFJPEG2000SubDescriptor(
    IAAFJPEG2000SubDescriptor* pJPEG2000Desc,
    testMode_t mode )
{
    HRESULT  hr = S_OK;


    try
    {
        Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
            pJPEG2000Desc,
            &IAAFJPEG2000SubDescriptor::SetRsiz,
            &IAAFJPEG2000SubDescriptor::GetRsiz,
            (aafUInt16)17,
            true,
            mode );
        Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
            pJPEG2000Desc,
            &IAAFJPEG2000SubDescriptor::SetXsiz,
            &IAAFJPEG2000SubDescriptor::GetXsiz,
            (aafUInt32)17,
            true,
            mode );
        Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
            pJPEG2000Desc,
            &IAAFJPEG2000SubDescriptor::SetYsiz,
            &IAAFJPEG2000SubDescriptor::GetYsiz,
            (aafUInt32)17,
            true,
            mode );
        Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
            pJPEG2000Desc,
            &IAAFJPEG2000SubDescriptor::SetXOsiz,
            &IAAFJPEG2000SubDescriptor::GetXOsiz,
            (aafUInt32)17,
            true,
            mode );
        Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
            pJPEG2000Desc,
            &IAAFJPEG2000SubDescriptor::SetYOsiz,
            &IAAFJPEG2000SubDescriptor::GetYOsiz,
            (aafUInt32)17,
            true,
            mode );
        Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
            pJPEG2000Desc,
            &IAAFJPEG2000SubDescriptor::SetXTsiz,
            &IAAFJPEG2000SubDescriptor::GetXTsiz,
            (aafUInt32)17,
            true,
            mode );
        Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
            pJPEG2000Desc,
            &IAAFJPEG2000SubDescriptor::SetYTsiz,
            &IAAFJPEG2000SubDescriptor::GetYTsiz,
            (aafUInt32)17,
            true,
            mode );

        Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
            pJPEG2000Desc,
            &IAAFJPEG2000SubDescriptor::SetXTOsiz,
            &IAAFJPEG2000SubDescriptor::GetXTOsiz,
            (aafUInt32)17,
            true,
            mode );
        Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
            pJPEG2000Desc,
            &IAAFJPEG2000SubDescriptor::SetYTOsiz,
            &IAAFJPEG2000SubDescriptor::GetYTOsiz,
            (aafUInt32)17,
            true,
            mode );
        Test_IAAFJPEG2000SubDescriptor_SimplePropertyAccess(
            pJPEG2000Desc,
            &IAAFJPEG2000SubDescriptor::SetCsiz,
            &IAAFJPEG2000SubDescriptor::GetCsiz,
            (aafUInt16)17,
            true,
            mode );

        Test_IAAFJPEG2000SubDescriptor_PictureComponentSizing(
            pJPEG2000Desc,
            mode);

        Test_IAAFJPEG2000SubDescriptor_CodingStyleDefault(
            pJPEG2000Desc,
            mode);

        Test_IAAFJPEG2000SubDescriptor_QuantizationDefault(
            pJPEG2000Desc,
            mode);

		CheckResult(Test_IAAFJPEG2000SubDescriptor_J2CLayout(
            pJPEG2000Desc,
            mode));

        // If we got to this point none of the tests above
        // failed and the status can be set to 'success'.
        hr = S_OK;
    }
    catch( HRESULT e )
    {
        hr = e;
    }


    return hr;
}



static HRESULT CreateAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_constref productID)
{
    HRESULT hr = S_OK;

    try
    {
        // Remove the previous test file if any.
        ::RemoveTestFile(pFileName);


        // Create the test file
        IAAFSmartPointer<IAAFFile> pFile;
        CheckResult(CreateTestFile( pFileName,
                                    fileKind,
                                    rawStorageType,
                                    productID,
                                    &pFile ));


        // Get the AAF Dictionary
        IAAFSmartPointer<IAAFHeader> pHeader;
        CheckResult(pFile->GetHeader(&pHeader));
        IAAFSmartPointer<IAAFDictionary> pDictionary;
        CheckResult(pHeader->GetDictionary(&pDictionary));
        CAAFBuiltinDefs  defs (pDictionary);


        // Create a JPEG2000SubDescriptor
        IAAFSmartPointer<IAAFJPEG2000SubDescriptor> pJPEG2000Desc;
        CheckResult(defs.cdJPEG2000SubDescriptor()->CreateInstance(
            IID_IAAFJPEG2000SubDescriptor,
            (IUnknown **)&pJPEG2000Desc));

        // Before initialization test if the SoundDescriptor
        // methods return valid error values.
        CheckResult(Test_IAAFJPEG2000SubDescriptor_Uninitialized(pJPEG2000Desc));

        // Initialize JPEG2000SubDescriptor object
        CheckResult(pJPEG2000Desc->Initialize());

        // Create a CDCIDescriptor
        IAAFSmartPointer<IAAFEssenceDescriptor> pCDCIDesc;
        CheckResult(defs.cdCDCIDescriptor()->CreateInstance(
            IID_IAAFCDCIDescriptor,
            (IUnknown **)&pCDCIDesc));

        // Attach the IAAFJPEG2000SubDescriptor to the CDCIDescriptor
        IAAFSmartPointer<IAAFSubDescriptor> pSubDesc;
        CheckResult(pJPEG2000Desc->QueryInterface(IID_IAAFSubDescriptor,
                                                  (void **)&pSubDesc));
        IAAFSmartPointer<IAAFEssenceDescriptor2> pCDCIDesc_EssenceDesc2;
        CheckResult(pCDCIDesc->QueryInterface(IID_IAAFEssenceDescriptor2,
                                              (void **)&pCDCIDesc_EssenceDesc2));
        CheckResult(pCDCIDesc_EssenceDesc2->AppendSubDescriptor(pSubDesc));

        // Create a mob, set its ID
        IAAFSmartPointer<IAAFSourceMob> pSourceMob;
        CheckResult(defs.cdSourceMob()->CreateInstance( IID_IAAFSourceMob,
                                                        (IUnknown **)&pSourceMob) );
        IAAFSmartPointer<IAAFMob> pMob;
        CheckResult(pSourceMob->QueryInterface (IID_IAAFMob, (void **)&pMob));
        CheckResult(pMob->SetMobID(gTestData.sourceMobID));
        CheckResult(pMob->SetName(L"JPEG2000SubDescriptorTest"));

        // Attach the descriptor to the source mob
        IAAFSmartPointer<IAAFEssenceDescriptor> pCDCIDesc_EssenceDesc;
        CheckResult(pCDCIDesc->QueryInterface(IID_IAAFEssenceDescriptor,
                                              (void **)&pCDCIDesc_EssenceDesc));
        CheckResult(pSourceMob->SetEssenceDescriptor(pCDCIDesc_EssenceDesc));

        // Attach the source mob to the file
        CheckResult(pHeader->AddMob(pMob));


        // Test initialized JPEG2000SubDescriptor.
        CheckResult(Test_IAAFJPEG2000SubDescriptor(pJPEG2000Desc,
                                                   kAAFUnitTestReadWrite));


        // Save and close the file
        CheckResult(pFile->Save());
        CheckResult(pFile->Close());
    }
    catch (HRESULT& rResult)
    {
        hr = rResult;
    }

    return hr;
}



static HRESULT ReadAAFFile(
    aafWChar * pFileName )
{
    HRESULT                 hr = S_OK;

    try
    {
        // Open the test file
        IAAFSmartPointer<IAAFFile> pFile;
        CheckResult(AAFFileOpenExistingRead(pFileName, 0, &pFile));
        IAAFSmartPointer<IAAFHeader> pHeader;
        CheckResult(pFile->GetHeader(&pHeader));

        // Get the source mob
        IAAFSmartPointer<IAAFMob> pMob;
        CheckResult(pHeader->LookupMob(gTestData.sourceMobID, &pMob));
        IAAFSmartPointer<IAAFSourceMob> pSourceMob;
        CheckResult(pMob->QueryInterface(IID_IAAFSourceMob,
                                         (void **)&pSourceMob));

        // Get the JPEG2000SubDescriptor
        IAAFSmartPointer<IAAFEssenceDescriptor> pEssenceDesc;
        CheckResult(pSourceMob->GetEssenceDescriptor(&pEssenceDesc));
        IAAFSmartPointer<IAAFEssenceDescriptor2> pEssenceDesc2;
        CheckResult(pEssenceDesc->QueryInterface(IID_IAAFEssenceDescriptor2,
                                                 (void **)&pEssenceDesc2));
        aafUInt32 subdescriptorCount = 0;
        CheckResult(pEssenceDesc2->CountSubDescriptors(&subdescriptorCount));
        CheckExpression(subdescriptorCount == 1);
        IAAFSmartPointer<IAAFSubDescriptor> pSubDesc;
        CheckResult(pEssenceDesc2->GetSubDescriptorAt(0 , &pSubDesc));
        IAAFSmartPointer<IAAFJPEG2000SubDescriptor> pJPEG2000Desc;
        CheckResult(pSubDesc->QueryInterface(IID_IAAFJPEG2000SubDescriptor,
                                              (void **)&pJPEG2000Desc));


        CheckResult(Test_IAAFJPEG2000SubDescriptor(pJPEG2000Desc,
                                                   kAAFUnitTestReadOnly));

        CheckResult(pFile->Close());
    }
    catch (HRESULT& rResult)
    {
        hr = rResult;
    }


    return hr;
}



// Required function prototype.
extern "C" HRESULT CAAFJPEG2000SubDescriptor_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);

//
// The public entry for this module test,
//
HRESULT CAAFJPEG2000SubDescriptor_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID )
{
    HRESULT  hr = AAFRESULT_NOT_IMPLEMENTED;
    const size_t fileNameBufLen = 128;
    aafWChar pFileName[ fileNameBufLen ] = L"";
    GenerateTestFileName( productID.productName, fileKind, fileNameBufLen, pFileName );


    try
    {
        if(mode == kAAFUnitTestReadWrite)
            hr = CreateAAFFile(pFileName, fileKind, rawStorageType, productID);
        else
            hr = AAFRESULT_SUCCESS;
        if(hr == AAFRESULT_SUCCESS)
            hr = ReadAAFFile( pFileName );
    }
    catch (...)
    {
        cerr << "CAAFSoundDescriptor_test...Caught general C++"
             << " exception!" << endl; 
        hr = AAFRESULT_TEST_FAILED;
    }


    return hr;
}

