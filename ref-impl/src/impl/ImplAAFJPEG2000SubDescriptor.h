#ifndef __ImplAAFJPEG2000SubDescriptor_h__
#define __ImplAAFJPEG2000SubDescriptor_h__

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


#include "ImplAAFSubDescriptor.h"

#include "OMArrayProperty.h"
#include "OMFixedSizeProperty.h"
#include "OMVariableSizeProperty.h"



class ImplAAFJPEG2000SubDescriptor : public ImplAAFSubDescriptor
{
public:
  //****************
  // Constructor
  //
  ImplAAFJPEG2000SubDescriptor ();

protected:
  //****************
  // Desctructor
  //
  virtual ~ImplAAFJPEG2000SubDescriptor ();

public:
  //********************************
  // AAF SDK exported methods start
  //********************************

  //****************
  // Initialize()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Initialize ();

  //****************
  // SetRsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetRsiz
        // @param rsiz [in] An enumerated value that defines the JPEG 2000
        //                  decoder capabilities.
        (aafUInt16 rsiz);

  //****************
  // GetRsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetRsiz
        // @param pRsiz [out] An enumerated value that defines the JPEG 2000
        //                    decoder capabilities.
        (aafUInt16 *  pRsiz);


  //***********************************************************
  //
  // SetXsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetXsiz
        // @param xsiz [in] Width of the reference grid
        (aafUInt32  xsiz);


  //***********************************************************
  //
  // GetXsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetXsiz
        // @param pXsiz [out] Width of the reference grid
        (aafUInt32 *  pXsiz);


  //***********************************************************
  //
  // SetYsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetYsiz
        // @param ysiz [in] Height of the reference grid
        (aafUInt32  ysiz);


  //***********************************************************
  //
  // GetYsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetYsiz
              // @param pYsiz [out] Height of the reference grid
        (aafUInt32 *  pYsiz);


  //***********************************************************
  //
  // SetXOsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetXOsiz
        // @param xosiz [in] Horizontal offset from the origin of the
        //                   reference grid to the left side of the image
        //                   area
        (aafUInt32  xosiz);


  //***********************************************************
  //
  // GetXOsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetXOsiz
        // @param pXOsiz [out] Horizontal offset from the origin of the
        //                     reference grid to the left side of the image
        //                     area
        (aafUInt32 *  pXOsiz);


  //***********************************************************
  //
  // SetYOsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetYOsiz
        // @param yosiz [in] Vertical offset from the origin of the reference
        //                   grid to the top side of the image area
        (aafUInt32  yosiz);


  //***********************************************************
  //
  // GetYOsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetYOsiz
        // @param pYOsiz [out] Vertical offset from the origin of the reference
        //                     grid to the top side of the image area
        (aafUInt32 *  pYOsiz);


  //***********************************************************
  //
  // SetXTsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetXTsiz
        // @param xtsiz [in] Width of one reference tile with respect
        //                   to the reference grid
        (aafUInt32  xtsiz);


  //***********************************************************
  //
  // GetXTsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetXTsiz
        // @param pXTsiz [out] Width of one reference tile with respect
        //                     to the reference grid
        (aafUInt32 *  pXTsiz);


  //***********************************************************
  //
  // SetYTsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetYTsiz
        // @param ytsiz [in] Height of one reference tile with respect to
        //                   the reference grid
        (aafUInt32  ytsiz);


  //***********************************************************
  //
  // GetYTsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetYTsiz
        // @param pYTsiz [out] Height of one reference tile with respect to
        //                     the reference grid.
        (aafUInt32 *  pYTsiz);


  //***********************************************************
  //
  // SetXTOsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetXTOsiz
        // @param xtosiz [in] Horizontal offset from the origin of
        //                    the reference grid to the left side of
        //                    the first tile
        (aafUInt32  xtosiz);


  //***********************************************************
  //
  // GetXTOsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetXTOsiz
        // @param pXTOsiz [out] Horizontal offset from the origin of
        //                      the reference grid to the left side of
        //                      the first tile
        (aafUInt32 *  pXTOsiz);


  //***********************************************************
  //
  // SetYTOsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetYTOsiz
        // @param ytosiz [in] Vertical offset from the origin of
        //                    the reference grid to
        (aafUInt32  ytosiz);


  //***********************************************************
  //
  // GetYTOsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetYTOsiz
        // @param pYTOsiz [out] Vertical offset from the origin of
        //                      the reference grid to
        (aafUInt32 *  pYTOsiz);


  //***********************************************************
  //
  // SetCsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetCsiz
        // @param csiz [in] The number of components in the picture.
        (aafUInt16  csiz);


  //***********************************************************
  //
  // GetCsiz()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetCsiz
        // @param pCsiz [out] The number of components in the picture.
        (aafUInt16 *  pCsiz);


  //***********************************************************
  //
  // SetSsizAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetComponentSsizAt
        // @param ssiz [in] The Ssiz parameter of the index-th component.
        (aafUInt16  index,
         aafUInt8  ssiz );


  //***********************************************************
  //
  // GetSsizAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetComponentSsizAt
        // @param pSsiz [out] The Ssiz parameter of the index-th component.
        (aafUInt16  index,
         aafUInt8 *  pSsiz);


  //***********************************************************
  //
  // SetXRsizAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetComponentXRsizAt
        // @param xrsiz [in] The XRsiz parameter of the index-th component.
        (aafUInt16  index,
         aafUInt8  xrsiz );


  //***********************************************************
  //
  // GetXRsizAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetComponentXRsizAt
        // @param pXRsiz [out] The XRsiz parameter of the index-th component.
        (aafUInt16  index,
         aafUInt8 *  pXRsiz);


  //***********************************************************
  //
  // SetYRsizAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetComponentYRsizAt
        // @param ssiz [in] The YRsiz parameter of the index-th component.
        (aafUInt16  index,
         aafUInt8  yrsiz );


  //***********************************************************
  //
  // GetYRsizAt()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetComponentYRsizAt
        // @param pYRsiz [out] The YRsiz parameter of the index-th component.
        (aafUInt16  index,
         aafUInt8 *  pYRsiz);


  //***********************************************************
  //
  // SetCodingStyleDefault()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetCodingStyleDefault
         // @parm [in] The number of default coding style bytes
        (aafUInt32  valueSize,
         // @parm [in, size_is(valueSize)] The number of default coding style bytes
         aafDataBuffer_t  pValue);


  //****************
  // GetCodingStyleDefaultBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetCodingStyleDefaultBufLen
         //@parm [out] Number of bytes in Coding Style Default.
        (aafUInt32 *  pSizeOfBuffer); 


  //***********************************************************
  //
  // GetSetCodingStyleDefault()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetCodingStyleDefault
         // @parm [in] The size of the pValue buffer
        (aafUInt32  valueSize,
         // @parm [out, size_is(valueSize)] The buffer to hold returned default coding style bytes.
         aafDataBuffer_t  pValue);


  //***********************************************************
  //
  // SetQuantizationDefault()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetQuantizationDefault
         // @parm [in] The number of default quantization style bytes
        (aafUInt32  valueSize,
         // @parm [in, size_is(valueSize)] The number of default quantization style bytes
         aafDataBuffer_t  pValue);


  //****************
  // GetQuantizationDefaultBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetQuantizationDefaultBufLen
         //@parm [out] Number of bytes in Quantization Default.
        (aafUInt32 *  pSizeOfBuffer); 


  //***********************************************************
  //
  // GetSetQuantizationDefault()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetQuantizationDefault
         // @parm [in] The size of the pValue buffer
        (aafUInt32  valueSize,
         // @parm [out, size_is(valueSize)] The buffer to hold returned default quantization style bytes.
         aafDataBuffer_t  pValue);


  virtual AAFRESULT STDMETHODCALLTYPE
    SetJ2CLayout
         // @parm [in] aafUInt32 | numberElements | The number of elements in pJ2CLayoutArray
        (aafUInt32  numberElements,
         // @parm [in] aafRGBAComponent_t* | pJ2CLayoutArray | Array of up to 8 aafRGBAComponent_t indicating component order, type and size.
         const aafRGBAComponent_t*  pJ2CLayoutArray);


  virtual AAFRESULT STDMETHODCALLTYPE
    CountJ2CLayoutElements
         // @parm [out] aafUInt32 * | pResult | Number of components
        (aafUInt32 *  pNumberElements);


  virtual AAFRESULT STDMETHODCALLTYPE
    GetJ2CLayout
         // @parm [in] aafUInt32 | numberElements | The number of elements in the array
        (
         aafUInt32  numberElements,
         // @parm [out, size_is(numberElements)] aafRGBAComponent_t* | pJ2CLayoutArray | Array of up to 8 aafRGBAComponent_t indicating component order, type and size.
         aafRGBAComponent_t*  pJ2CLayoutArray);


  //********************************
  // AAF SDK exported methods end
  //********************************

protected:

    typedef struct
    {
        aafRGBAComponent_t comps[MAX_NUM_RGBA_COMPS];
    } RGBComponentArray;

    OMFixedSizeProperty<aafUInt16>              _Rsiz;
    OMFixedSizeProperty<aafUInt32>              _Xsiz;
    OMFixedSizeProperty<aafUInt32>              _Ysiz;
    OMFixedSizeProperty<aafUInt32>              _XOsiz;
    OMFixedSizeProperty<aafUInt32>              _YOsiz;
    OMFixedSizeProperty<aafUInt32>              _XTsiz;
    OMFixedSizeProperty<aafUInt32>              _YTsiz;
    OMFixedSizeProperty<aafUInt32>              _XTOsiz;
    OMFixedSizeProperty<aafUInt32>              _YTOsiz;
    OMFixedSizeProperty<aafUInt16>              _Csiz;
    OMArrayProperty<aafUInt8>                   _pictureComponentSizing;
    OMVariableSizeProperty<aafUInt8>            _codingStyleDefault;
    OMVariableSizeProperty<aafUInt8>            _quantizationDefault;
    OMFixedSizeProperty<RGBComponentArray>      _j2cLayout;
};

#endif // ! __ImplAAFJPEG2000SubDescriptor_h__
