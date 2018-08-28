//=---------------------------------------------------------------------=
//
// $Id$ $Name$
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
// The Original Code of this file is Copyright 1998-2011, Licensor of the
// AAF Association.
//
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

#include "ImplAAFJPEG2000SubDescriptor.h"
#include "AAFPropertyIDs.h"
#include "AAFPropertyDefs.h"



ImplAAFJPEG2000SubDescriptor::ImplAAFJPEG2000SubDescriptor() :
    _Rsiz(PID_JPEG2000SubDescriptor_Rsiz, L"Rsiz"), 
    _Xsiz(PID_JPEG2000SubDescriptor_Xsiz, L"Xsiz"), 
    _Ysiz(PID_JPEG2000SubDescriptor_Ysiz, L"Ysiz"), 
    _XOsiz(PID_JPEG2000SubDescriptor_XOsiz, L"XOsiz"), 
    _YOsiz(PID_JPEG2000SubDescriptor_YOsiz, L"YOsiz"), 
    _XTsiz(PID_JPEG2000SubDescriptor_XTsiz, L"XTsiz"), 
    _YTsiz(PID_JPEG2000SubDescriptor_YTsiz, L"YTsiz"), 
    _XTOsiz(PID_JPEG2000SubDescriptor_XTOsiz, L"XTOsiz"), 
    _YTOsiz(PID_JPEG2000SubDescriptor_YTOsiz, L"YTOsiz"), 
    _Csiz(PID_JPEG2000SubDescriptor_Csiz, L"Csiz"),
    _pictureComponentSizing(PID_JPEG2000SubDescriptor_PictureComponentSizing, L"PictureComponentSizing"),
    _codingStyleDefault(PID_JPEG2000SubDescriptor_CodingStyleDefault, L"CodingStyleDefault"),
    _quantizationDefault(PID_JPEG2000SubDescriptor_QuantizationDefault, L"QuantizationDefault"),
    _j2cLayout(PID_JPEG2000SubDescriptor_J2CLayout, L"J2CLayout")
{
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_Rsiz),
        _Rsiz.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_Xsiz),
        _Xsiz.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_Ysiz),
        _Ysiz.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_XOsiz),
        _XOsiz.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_YOsiz),
        _YOsiz.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_XTsiz),
        _XTsiz.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_YTsiz),
        _YTsiz.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_XTOsiz),
        _XTOsiz.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_YTOsiz),
        _YTOsiz.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_Csiz),
        _Csiz.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_PictureComponentSizing),
        _pictureComponentSizing.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_CodingStyleDefault),
        _codingStyleDefault.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_QuantizationDefault),
        _quantizationDefault.address());
    _persistentProperties.putDynamicBuiltin(
        *reinterpret_cast<const OMObjectIdentification*>(
            &kAAFPropID_JPEG2000SubDescriptor_J2CLayout),
        _j2cLayout.address());

    // Set the required properties to bogus values. The values are
    // deliberately out of the ranges specified in ISO/IEC 15444-1, Table A-9.
    _Rsiz = 0xFFFF;
    _Xsiz = 0;
    _Ysiz = 0;
    _XOsiz = 0xFFFFFFFF;
    _YOsiz = 0xFFFFFFFF;
    _XTsiz = 0;
    _YTsiz = 0;
    _XTOsiz = 0xFFFFFFFF;
    _YTOsiz = 0xFFFFFFFF;
    _Csiz = 0;
    // _pictureComponentSizing is initialized as a zero length array
    // _codingStyleDefault is initialized as a zero length variable value
    // _quantizationDefault is initialized as a zero length variable value
    // _j2cLayout is initialized as a zero length variable value
}



ImplAAFJPEG2000SubDescriptor::~ImplAAFJPEG2000SubDescriptor ()
{
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::Initialize()
{
    if( isInitialized() )
    {
        return AAFRESULT_ALREADY_INITIALIZED;
    }

    setInitialized();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetRsiz(
    aafUInt16 rsiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _Rsiz = rsiz;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetRsiz(
    aafUInt16* pRsiz )
{
    if( pRsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }


    *pRsiz = _Rsiz;


    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetXsiz(
    aafUInt32 xsiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _Xsiz = xsiz;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetXsiz(
    aafUInt32* pXsiz )
{
    if( pXsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }


    *pXsiz = _Xsiz;


    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetYsiz(
    aafUInt32 ysiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _Ysiz = ysiz;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetYsiz(
    aafUInt32* pYsiz )
{
    if( pYsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }


    *pYsiz = _Ysiz;


    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetXOsiz(
    aafUInt32 xosiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _XOsiz = xosiz;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetXOsiz(
    aafUInt32* pXOsiz )
{
    if( pXOsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }


    *pXOsiz = _XOsiz;


    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetYOsiz(
    aafUInt32 yosiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _YOsiz = yosiz;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetYOsiz(
    aafUInt32* pYOsiz )
{
    if( pYOsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }


    *pYOsiz = _YOsiz;


    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetXTsiz(
    aafUInt32 xtsiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _XTsiz = xtsiz;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetXTsiz(
    aafUInt32* pXTsiz )
{
    if( pXTsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }


    *pXTsiz = _XTsiz;


    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetYTsiz(
    aafUInt32 ytsiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _YTsiz = ytsiz;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetYTsiz(
    aafUInt32* pYTsiz )
{
    if( pYTsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }


    *pYTsiz = _YTsiz;


    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetXTOsiz(
    aafUInt32 xtosiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _XTOsiz = xtosiz;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetXTOsiz(
    aafUInt32* pXTOsiz )
{
    if( pXTOsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }


    *pXTOsiz = _XTOsiz;


    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetYTOsiz(
    aafUInt32 ytosiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    _YTOsiz = ytosiz;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetYTOsiz(
    aafUInt32* pYTOsiz )
{
    if( pYTOsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }


    *pYTOsiz = _YTOsiz;


    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetCsiz(
    aafUInt16 csiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    const aafUInt32 newPictureComponentSizingArraySize = csiz * 3;
    if( newPictureComponentSizingArraySize > OMPROPERTYSIZE_MAX )
        return AAFRESULT_BAD_SIZE;

    if( newPictureComponentSizingArraySize > _pictureComponentSizing.count() )
    {
        while( _pictureComponentSizing.count() < newPictureComponentSizingArraySize)
        {
            aafUInt8 invalidSsizValue = 0xFF;
            _pictureComponentSizing.append(invalidSsizValue);
        }
    }
    else if( newPictureComponentSizingArraySize < _pictureComponentSizing.count() )
    {
        while( _pictureComponentSizing.count() > newPictureComponentSizingArraySize)
        {
            _pictureComponentSizing.removeLast();
        }
    }

    _Csiz = csiz;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetCsiz(
    aafUInt16* pCsiz )
{
    if( pCsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }


    *pCsiz = _Csiz;


    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetComponentSsizAt(
    aafUInt16  index,
    aafUInt8  ssiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    const aafUInt32 arrayIndex = index * 3;
    if( arrayIndex >= _pictureComponentSizing.count() )
    {
        return AAFRESULT_BADINDEX;
    }

    _pictureComponentSizing.setAt( ssiz, arrayIndex );

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetComponentSsizAt(
    aafUInt16  index,
    aafUInt8* pSsiz )
{
    if( pSsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    const aafUInt32 arrayIndex = index * 3;
    if( arrayIndex >= _pictureComponentSizing.count() )
    {
        return AAFRESULT_BADINDEX;
    }

    *pSsiz = _pictureComponentSizing.getAt( arrayIndex );

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetComponentXRsizAt(
    aafUInt16  index,
    aafUInt8  xrsiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    const aafUInt32 arrayIndex = index * 3 + 1;
    if( arrayIndex >= _pictureComponentSizing.count() )
    {
        return AAFRESULT_BADINDEX;
    }

    _pictureComponentSizing.setAt( xrsiz, arrayIndex );

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetComponentXRsizAt(
    aafUInt16  index,
    aafUInt8* pXRsiz )
{
    if( pXRsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    const aafUInt32 arrayIndex = index * 3 + 1;
    if( arrayIndex >= _pictureComponentSizing.count() )
    {
        return AAFRESULT_BADINDEX;
    }

    *pXRsiz = _pictureComponentSizing.getAt( arrayIndex );

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetComponentYRsizAt(
    aafUInt16  index,
    aafUInt8  yrsiz )
{
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    const aafUInt32 arrayIndex = index * 3 + 2;
    if( arrayIndex >= _pictureComponentSizing.count() )
    {
        return AAFRESULT_BADINDEX;
    }

    _pictureComponentSizing.setAt( yrsiz, arrayIndex );

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetComponentYRsizAt(
    aafUInt16  index,
    aafUInt8* pYRsiz )
{
    if( pYRsiz == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    const aafUInt32 arrayIndex = index * 3 + 2;
    if( arrayIndex >= _pictureComponentSizing.count() )
    {
        return AAFRESULT_BADINDEX;
    }

    *pYRsiz = _pictureComponentSizing.getAt( arrayIndex );

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetCodingStyleDefault(
    aafUInt32  valueSize,
    aafDataBuffer_t  pValue)
{
    if( pValue == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( valueSize < 5 )
        return AAFRESULT_ILLEGAL_VALUE;
    if( valueSize > OMPROPERTYSIZE_MAX )
        return AAFRESULT_BAD_SIZE;
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    const OMPropertySize size = static_cast<OMPropertySize>(valueSize);
    _codingStyleDefault.setValue(pValue, size);

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetCodingStyleDefaultBufLen(
    aafUInt32 *  pSizeOfBuffer)
{
    if( pSizeOfBuffer == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_codingStyleDefault.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pSizeOfBuffer = _codingStyleDefault.size();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetCodingStyleDefault(
    aafUInt32  valueSize,
    aafDataBuffer_t  pValue)
{
    if( pValue == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_codingStyleDefault.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }
    if( valueSize < _codingStyleDefault.size() )
    {
        return AAFRESULT_SMALLBUF;
    }

    _codingStyleDefault.copyToBuffer(pValue, valueSize);

    return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetQuantizationDefault(
    aafUInt32  valueSize,
    aafDataBuffer_t  pValue)
{
    if( pValue == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( valueSize < 2 )
        return AAFRESULT_ILLEGAL_VALUE;
    if( valueSize > OMPROPERTYSIZE_MAX )
        return AAFRESULT_BAD_SIZE;
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    const OMPropertySize size = static_cast<OMPropertySize>(valueSize);
    _quantizationDefault.setValue(pValue, size);

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetQuantizationDefaultBufLen(
    aafUInt32 *  pSizeOfBuffer)
{
    if( pSizeOfBuffer == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_quantizationDefault.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    *pSizeOfBuffer = _quantizationDefault.size();

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetQuantizationDefault(
    aafUInt32  valueSize,
    aafDataBuffer_t  pValue)
{
    if( pValue == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_quantizationDefault.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }
    if( valueSize < _quantizationDefault.size() )
    {
        return AAFRESULT_SMALLBUF;
    }

    _quantizationDefault.copyToBuffer(pValue, valueSize);

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::SetJ2CLayout(
    aafUInt32  numberElements,
    const aafRGBAComponent_t*  pJ2CLayoutArray)
{
    if( pJ2CLayoutArray == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if (numberElements > MAX_NUM_RGBA_COMPS)
    {
        return AAFRESULT_INVALID_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }

    RGBComponentArray layout;
    memcpy(&layout, pJ2CLayoutArray, numberElements*sizeof(aafRGBAComponent_t));
    for(aafUInt32 i = numberElements; i<MAX_NUM_RGBA_COMPS; i++)
    {
        layout.comps[i].Code = kAAFCompNull;
        layout.comps[i].Size = 0;
    }

    _j2cLayout = layout;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::CountJ2CLayoutElements(
    aafUInt32 *  pNumberElements)
{
    if( pNumberElements == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_j2cLayout.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }

    const RGBComponentArray layout = _j2cLayout;
    aafUInt32 count = 0;
    for( count=0; count<MAX_NUM_RGBA_COMPS; count++ )
    {
        if(layout.comps[count].Code == kAAFCompNull)
            break;
    }

    *pNumberElements = count;

    return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE ImplAAFJPEG2000SubDescriptor::GetJ2CLayout(
     aafUInt32  numberElements,
     aafRGBAComponent_t*  pJ2CLayoutArray)
{
    if( pJ2CLayoutArray == 0 )
    {
        return AAFRESULT_NULL_PARAM;
    }
	if (numberElements > MAX_NUM_RGBA_COMPS)
	{
		return AAFRESULT_INVALID_PARAM;
	}
    if( !isInitialized() )
    {
        return AAFRESULT_NOT_INITIALIZED;
    }
    if( !_j2cLayout.isPresent() )
    {
        return AAFRESULT_PROP_NOT_PRESENT;
    }
    aafUInt32 count = 0;
    CountJ2CLayoutElements( &count );
    if( numberElements < count )
    {
        return AAFRESULT_SMALLBUF;
    }

    const RGBComponentArray layout = _j2cLayout;
    memcpy(pJ2CLayoutArray, layout.comps, numberElements * sizeof(aafRGBAComponent_t));

    return AAFRESULT_SUCCESS;
}
