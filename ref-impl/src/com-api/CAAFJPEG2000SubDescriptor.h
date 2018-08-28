//@doc
//@class    AAFJPEG2000SubDescriptor | Implementation class for AAFJPEG2000SubDescriptor
#ifndef __CAAFJPEG2000SubDescriptor_h__
#define __CAAFJPEG2000SubDescriptor_h__

//=---------------------------------------------------------------------=
//
// This file was GENERATED for the AAF SDK
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
// The Original Code of this file is Copyright 1998-2012, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
// The Initial Developer of the Original Code of this file and the
// licensor of the Advanced Media Workflow Association is
// Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=



#ifndef __AAF_h__
#include "AAF.h"
#endif





#ifndef __CAAFSubDescriptor_h__
#include "CAAFSubDescriptor.h"
#endif


class CAAFJPEG2000SubDescriptor
  : public IAAFJPEG2000SubDescriptor,
    public IAAFJPEG2000SubDescriptor2,
    public CAAFSubDescriptor
{
protected:

  //********
  //
  // Constructor/destructor
  //
  CAAFJPEG2000SubDescriptor (IUnknown * pControllingUnknown, aafBool doInit = kAAFTrue);
  virtual ~CAAFJPEG2000SubDescriptor ();

public:

  //***********************************************************
  //
  // Initialize()
  //
  // Initializes a newly allocated, IAAFJPEG2000SubDescriptor2-supporting
  /// object. This method must be called after allocation, and before
  /// any other method can be called.
  ///
  /// Succeeds if:
  /// - Initialize() has not yet been called on this object.
  ///
  /// This method will return the following codes.  If more than one of
  /// the listed errors is in effect, it will return the first one
  /// encountered in the order given below:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_ALREADY_INITIALIZED
  ///   - Initialize() has already been called on this object.
  //
  STDMETHOD (Initialize)
     ();



  //***********************************************************
  //
  // SetRsiz()
  //
  // Sets the enumerated value that defines the JPEG 2000 decoder capabilities.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the Rsiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetRsiz) (
    // An enumerated value that defines the JPEG 2000 decoder capabilities.
  /// Values are defined in ISO/IEC 15444-1 Annex A.5 Table A-10.
  /// Other values may be defined in amendments to ISO/IEC 15444-1
  /// or in related international standards documents. 
    /*[in]*/ aafUInt16  rsiz);


  //***********************************************************
  //
  // GetRsiz()
  //
  // Gets the enumerated value that defines the JPEG 2000 decoder capabilities.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pRsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pRsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pRsiz arg is NULL.
  //
  STDMETHOD (GetRsiz) (
    // An enumerated value that defines the JPEG 2000 decoder capabilities.
  /// Values are defined in ISO/IEC 15444-1 Annex A.5 Table A-10.
  /// Other values may be defined in amendments to ISO/IEC 15444-1
  /// or in related international standards documents. 
    /*[out]*/ aafUInt16 *  pRsiz);


  //***********************************************************
  //
  // SetXsiz()
  //
  // Sets the width of the reference grid.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the Xsiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetXsiz) (
    // Width of the reference grid, as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[in]*/ aafUInt32  xsiz);


  //***********************************************************
  //
  // GetXsiz()
  //
  // Gets the width of the reference grid.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pXsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pXsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pXsiz arg is NULL.
  //
  STDMETHOD (GetXsiz) (
    // Width of the reference grid, as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[out]*/ aafUInt32 *  pXsiz);


  //***********************************************************
  //
  // SetYsiz()
  //
  // Sets the height of the reference grid.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the Ysiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetYsiz) (
    // Height of the reference grid, as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[in]*/ aafUInt32  ysiz);


  //***********************************************************
  //
  // GetYsiz()
  //
  // Gets the height of the reference grid.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pYsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pYsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pYsiz arg is NULL.
  //
  STDMETHOD (GetYsiz) (
    // Height of the reference grid, as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[out]*/ aafUInt32 *  pYsiz);


  //***********************************************************
  //
  // SetXOsiz()
  //
  // Sets the horizontal offset from the origin of the reference grid
  /// to the left side of the image area.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the XOsiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetXOsiz) (
    // Horizontal offset from the origin of the reference grid to the left
  /// side of the image area, as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[in]*/ aafUInt32  xosiz);


  //***********************************************************
  //
  // GetXOsiz()
  //
  // Gets the horizontal offset from the origin of the reference grid
  /// to the left side of the image area.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pXOsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pXOsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pXOsiz arg is NULL.
  //
  STDMETHOD (GetXOsiz) (
    // Horizontal offset from the origin of the reference grid to the left
  /// side of the image area, as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[out]*/ aafUInt32 *  pXOsiz);


  //***********************************************************
  //
  // SetYOsiz()
  //
  // Gets the vertical offset from the origin of the reference grid
  /// to the top side of the image area.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the YOsiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetYOsiz) (
    // Vertical offset from the origin of the reference grid to the top
  /// side of the image area, as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[in]*/ aafUInt32  yosiz);


  //***********************************************************
  //
  // GetYOsiz()
  //
  // Gets the vertical offset from the origin of the reference grid
  /// to the top side of the image area.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pYOsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pYOsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pYOsiz arg is NULL.
  //
  STDMETHOD (GetYOsiz) (
    // Vertical offset from the origin of the reference grid to the top
  /// side of the image area, as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[out]*/ aafUInt32 *  pYOsiz);


  //***********************************************************
  //
  // SetXTsiz()
  //
  // Gets the width of one reference tile with respect to the reference grid.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the XTsiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetXTsiz) (
    // Width of one reference tile with respect to the reference grid,
  /// as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[in]*/ aafUInt32  xtsiz);


  //***********************************************************
  //
  // GetXTsiz()
  //
  // Sets the width of one reference tile with respect to the reference grid.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pXTsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pXTsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pXTsiz arg is NULL.
  //
  STDMETHOD (GetXTsiz) (
    // Width of one reference tile with respect to the reference grid,
  /// as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[out]*/ aafUInt32 *  pXTsiz);


  //***********************************************************
  //
  // SetYTsiz()
  //
  // Gets the height of one reference tile with respect to the reference grid.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the YTsiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetYTsiz) (
    // Height of one reference tile with respect to the reference grid,
  /// as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[in]*/ aafUInt32  ytsiz);


  //***********************************************************
  //
  // GetYTsiz()
  //
  // Sets the height of one reference tile with respect to the reference grid.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pYTsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pYTsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pYTsiz arg is NULL.
  //
  STDMETHOD (GetYTsiz) (
    // Height of one reference tile with respect to the reference grid,
  /// as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[out]*/ aafUInt32 *  pYTsiz);


  //***********************************************************
  //
  // SetXTOsiz()
  //
  // Gets the horizontal offset from the origin of the reference grid
  /// to the left side of the first tile.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the XTOsiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetXTOsiz) (
    // Horizontal offset from the origin of the reference grid to the left
  /// side of the first tile, as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[in]*/ aafUInt32  xtosiz);


  //***********************************************************
  //
  // GetXTOsiz()
  //
  // Sets the horizontal offset from the origin of the reference grid
  /// to the left side of the first tile.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pXTOsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pXTOsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pXTOsiz arg is NULL.
  //
  STDMETHOD (GetXTOsiz) (
    // Horizontal offset from the origin of the reference grid to the left
  /// side of the first tile, as defined in ISO/IEC 15444-1 Annex A.5.1. 
    /*[out]*/ aafUInt32 *  pXTOsiz);


  //***********************************************************
  //
  // SetYTOsiz()
  //
  // Gets the vertical offset from the origin of the reference grid to
  /// the top side of the first tile.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the YTOsiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetYTOsiz) (
    // Vertical offset from the origin of the reference grid to
  /// the top side of the first tile, as defined in ISO/IEC 15444-1
  /// Annex A.5.1. 
    /*[in]*/ aafUInt32  ytosiz);


  //***********************************************************
  //
  // GetYTOsiz()
  //
  // Gets the vertical offset from the origin of the reference grid to
  /// the top side of the first tile.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pYTOsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pYTOsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pYTOsiz arg is NULL.
  //
  STDMETHOD (GetYTOsiz) (
    // Vertical offset from the origin of the reference grid to
  /// the top side of the first tile, as defined in ISO/IEC 15444-1
  /// Annex A.5.1. 
    /*[out]*/ aafUInt32 *  pYTOsiz);


  //***********************************************************
  //
  // SetCsiz()
  //
  // Sets the number of components in the picture.
  /// If this Sub Descriptor is referenced by the CDCI Descriptor, the order
  /// and kind of components shall be as defined by the Container Format in
  /// the File Descriptor.
  /// If this Sub Descriptor is referenced by the RGBA Descriptor, the order
  /// and kind of components shall be as defined by the Pixel Layout property
  /// of the RGBA Descriptor.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the Csiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetCsiz) (
    // The number of components in the picture,
  /// as defined in ISO/IEC 15444-1 Annex A.5 Table A-10. 
    /*[in]*/ aafUInt16  csiz);


  //***********************************************************
  //
  // GetCsiz()
  //
  // Gets the number of components in the picture.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pCsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pCsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pCsiz arg is NULL.
  //
  STDMETHOD (GetCsiz) (
    // The number of components in the picture,
  /// as defined in ISO/IEC 15444-1 Annex A.5 Table A-10. 
    /*[out]*/ aafUInt16 *  pCsiz);


  //***********************************************************
  //
  // SetComponentSsizAt()
  //
  // Sets the Ssiz parameter of the index-th component.
  /// If this Sub Descriptor is referenced by the CDCI Descriptor, the order
  /// and kind of components shall be as defined by the Container Format in
  /// the File Descriptor.
  /// If this Sub Descriptor is referenced by the RGBA Descriptor, the order
  /// and kind of components shall be as defined by the Pixel Layout property
  /// of the RGBA Descriptor.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the Ssiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetComponentSsizAt) (
    // The index of the component
    /*[in]*/ aafUInt16  index,

    // The Ssiz parameter of the index-th component,
  /// as defined in ISO/IEC 15444-1 Annex A.5.1.
    /*[in]*/ aafUInt8  ssiz);


  //***********************************************************
  //
  // GetComponentSsizAt()
  //
  // Gets the Ssiz parameter of the index-th component.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pSsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pSsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pSsiz arg is NULL.
  //
  STDMETHOD (GetComponentSsizAt) (
    // The index of the component
    /*[in]*/ aafUInt16  index,

    // The Ssiz parameter of the index-th component,
  /// as defined in ISO/IEC 15444-1 Annex A.5.1.
    /*[out]*/ aafUInt8 *  pSsiz);


  //***********************************************************
  //
  // SetComponentXRsizAt()
  //
  // Sets the XRsiz parameter of the index-th component.
  /// If this Sub Descriptor is referenced by the CDCI Descriptor, the order
  /// and kind of components shall be as defined by the Container Format in
  /// the File Descriptor.
  /// If this Sub Descriptor is referenced by the RGBA Descriptor, the order
  /// and kind of components shall be as defined by the Pixel Layout property
  /// of the RGBA Descriptor.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the XRsiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetComponentXRsizAt) (
    // The index of the component
    /*[in]*/ aafUInt16  index,

    // The XRsiz parameter of the index-th component,
  /// as defined in ISO/IEC 15444-1 Annex A.5.1.
    /*[in]*/ aafUInt8  ssiz);


  //***********************************************************
  //
  // GetComponentXRsizAt()
  //
  // Gets the XRsiz parameter of the index-th component.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pXRsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pXRsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pXRsiz arg is NULL.
  //
  STDMETHOD (GetComponentXRsizAt) (
    // The index of the component
    /*[in]*/ aafUInt16  index,

    // The XRsiz parameter of the index-th component,
  /// as defined in ISO/IEC 15444-1 Annex A.5.1.
    /*[out]*/ aafUInt8 *  pXRsiz);


  //***********************************************************
  //
  // SetComponentYRsizAt()
  //
  // Sets the YRsiz parameter of the index-th component.
  /// If this Sub Descriptor is referenced by the CDCI Descriptor, the order
  /// and kind of components shall be as defined by the Container Format in
  /// the File Descriptor.
  /// If this Sub Descriptor is referenced by the RGBA Descriptor, the order
  /// and kind of components shall be as defined by the Pixel Layout property
  /// of the RGBA Descriptor.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// 
  /// If this method fails the YRsiz property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetComponentYRsizAt) (
    // The index of the component
    /*[in]*/ aafUInt16  index,

    // The YRsiz parameter of the index-th component,
  /// as defined in ISO/IEC 15444-1 Annex A.5.1.
    /*[in]*/ aafUInt8  ssiz);


  //***********************************************************
  //
  // GetComponentYRsizAt()
  //
  // Gets the YRsiz parameter of the index-th component.
  /// This property is required.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pYRsiz pointer is valid.
  /// 
  /// If this method fails nothing will be written to *pYRsiz.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pYRsiz arg is NULL.
  //
  STDMETHOD (GetComponentYRsizAt) (
    // The index of the component
    /*[in]*/ aafUInt16  index,

    // The YRsiz parameter of the index-th component,
  /// as defined in ISO/IEC 15444-1 Annex A.5.1.
    /*[out]*/ aafUInt8 *  pYRsiz);


  //***********************************************************
  //
  // SetCodingStyleDefault()
  //
  // Sets the default coding style for all components.
  /// This property is optional.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pValue pointer is valid.
  /// 
  /// If this method fails the CodingStyleDefault property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pValue arg is NULL.
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetCodingStyleDefault) (
    // The number of default coding style bytes
    /*[in]*/ aafUInt32  valueSize,

    // The default coding style bytes.
  /// The data format is as defined in ISO/IEC 15444-1, Annex A.6.1.
    /*[in, size_is(valueSize)]*/ aafDataBuffer_t  pValue);


  //***********************************************************
  //
  // GetCodingStyleDefaultBufLen()
  //
  // Gets the number of bytes in the default coding style sequence.
  /// This property is optional.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pSizeOfBuffer pointer is valid.
  /// - the property is present.
  /// 
  /// If this method fails nothing will be written to *pSizeOfBuffer.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pSizeOfBuffer arg is NULL.
  ///
  /// AAFRESULT_PROP_NOT_PRESENT
  ///   - the property is not present.
  //
  STDMETHOD (GetCodingStyleDefaultBufLen) (
    // The number of bytes in the default coding style sequence 
    /*[out]*/ aafUInt32 *  pSizeOfBuffer);


  //***********************************************************
  //
  // GetCodingStyleDefault()
  //
  // Gets the default coding style bytes.
  /// This property is optional.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pValue pointer is valid.
  /// - the property is present.
  /// 
  /// If this method fails nothing will be written to *pValue.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pValue arg is NULL.
  ///
  /// AAFRESULT_PROP_NOT_PRESENT
  ///   - the property is not present.
  //
  STDMETHOD (GetCodingStyleDefault) (
    // The size of the pValue buffer
    /*[in]*/ aafUInt32  valueSize,

    // The buffer to hold returned default coding style bytes.
  /// The data format is as defined in ISO/IEC 15444-1, Annex A.6.1.
    /*[in, size_is(valueSize)]*/ aafDataBuffer_t  pValue);


  //***********************************************************
  //
  // SetQuantizationDefault()
  //
  // Sets the default quantization style for all components.
  /// This property is optional.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pValue pointer is valid.
  /// 
  /// If this method fails the QuantizationDefault property will not be
  /// changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pValue arg is NULL.
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  //
  STDMETHOD (SetQuantizationDefault) (
    // The number of default quantization style bytes
    /*[in]*/ aafUInt32  valueSize,

    // The default quantization style bytes.
  /// The data format is as defined in ISO/IEC 15444-1, Annex A.6.4.
    /*[in, size_is(valueSize)]*/ aafDataBuffer_t  pValue);


  //***********************************************************
  //
  // GetQuantizationDefaultBufLen()
  //
  // Gets the number of bytes in the default quantization style sequence.
  /// This property is optional.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pSizeOfBuffer pointer is valid.
  /// - the property is present.
  /// 
  /// If this method fails nothing will be written to *pSizeOfBuffer.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pSizeOfBuffer arg is NULL.
  ///
  /// AAFRESULT_PROP_NOT_PRESENT
  ///   - the property is not present.
  //
  STDMETHOD (GetQuantizationDefaultBufLen) (
    // The number of bytes in the default quantization style sequence 
    /*[out]*/ aafUInt32 *  pSizeOfBuffer);


  //***********************************************************
  //
  // GetQuantizationDefault()
  //
  // Gets the default quantization style bytes.
  /// This property is optional.
  /// 
  /// Succeeds if all of the following are true:
  /// - the object is initialized.
  /// - the pValue pointer is valid.
  /// - the property is present.
  /// 
  /// If this method fails nothing will be written to *pValue.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pValue arg is NULL.
  ///
  /// AAFRESULT_PROP_NOT_PRESENT
  ///   - the property is not present.
  //
  STDMETHOD (GetQuantizationDefault) (
    // The size of the pValue buffer
    /*[in]*/ aafUInt32  valueSize,

    // The buffer to hold returned default quantization style bytes.
  /// The data format is as defined in ISO/IEC 15444-1, Annex A.6.4.
    /*[in, size_is(valueSize)]*/ aafDataBuffer_t  pValue);


  //***********************************************************
  // METHOD NAME: SetJ2CLayout()
  //
  // DESCRIPTION:
  // @mfunc AAFRESULT | AAFJPEG2000SubDescriptor2 | SetJ2CLayout |
  // Sets the order, type and size of the image components in the compressed J2C codestream.
  ///
  /// The layout array is an Array of 8 aafRGBAComponent_t.
  /// If you set less than 8 entries, the remaining entries will be padded with kAAFCompNull and a size of zero.
  /// If this method fails, the J2CLayout property will not be changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pJ2CLayoutArray is null.
  ///
  /// AAFRESULT_INVALID_PARAM
  ///   - numberElements indicates that the array is larger than allowed by
  ///     the property type.
  // @end
  // 
  STDMETHOD (SetJ2CLayout)
   (
    // @parm [in] aafUInt32 | numberElements | The number of elements in pJ2CLayoutArray
    aafUInt32  numberElements,

    // @parm [in] aafRGBAComponent_constptr | pJ2CLayoutArray | Array of up to 8 aafRGBAComponent_t indicating component order, type and size.
    aafRGBAComponent_constptr  pJ2CLayoutArray
  );

  //***********************************************************
  // METHOD NAME: CountJ2CLayoutElements()
  //
  // DESCRIPTION:
  // @mfunc AAFRESULT | AAFJPEG2000SubDescriptor2 | CountJ2CLayoutElements |
  // Returns the number of components in a pixel in the compressed J2C codestream.
  /// 
  /// Succeeds if all of the following are true:
  /// - this object has already been initialized.
  /// - the pResult pointer is valid.
  /// 
  /// If this method fails no state is changed.
  /// 
  /// This method will return the following codes.  If more than one of
  /// the listed errors is in effect, it will return the first one
  /// encountered in the order given below:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pResult is null.
  // @end
  // 
  STDMETHOD (CountJ2CLayoutElements)
   (
    // @parm [out] aafUInt32 * | pResult | Number of components
    aafUInt32 *  pResult
  );

  //***********************************************************
  // METHOD NAME: GetJ2CLayout()
  //
  // DESCRIPTION:
  // @mfunc AAFRESULT | AAFJPEG2000SubDescriptor2 | GetJ2CLayout |
  // Gets the order, type and size of the image components in the compressed J2C codestream.
  ///
  /// The layout array is an Array of 8 aafRGBAComponent_t.
  /// 
  /// If you Get more entries than were set, the extra entries will be padded with kAAFCompNull and a size of zero.
  ///
  /// If this method fails, J2CLayout property will not be changed.
  /// 
  /// This method will return the following codes:
  /// 
  /// AAFRESULT_SUCCESS
  ///   - succeeded.  (This is the only code indicating success.)
  ///
  /// AAFRESULT_NOT_INITIALIZED
  ///   - the object is not initialized.
  ///
  /// AAFRESULT_NULL_PARAM
  ///   - pJ2CLayoutArray is NULL.
  ///
  /// AAFRESULT_INVALID_PARAM
  ///   - numberElements indicates that the array is larger than allowed by
  ///     the property type.
  ///
  /// AAFRESULT_SMALLBUF
  ///   - numberElements indicates that the array is too small to hold
  ///     the data.
  // @end
  // 
  STDMETHOD (GetJ2CLayout)
   (
    // @parm [in] aafUInt32 | numberElements | The number of elements in the array
    aafUInt32  numberElements,

    // @parm [out, size_is(numberElements)] aafRGBAComponent_t* | pJ2CLayoutArray | Array of up to 8 aafRGBAComponent_t indicating component order, type and size.
    aafRGBAComponent_t*  pJ2CLayoutArray
  );



protected:
  // 
  // Declare the QI that implements for the interfaces
  // for this module. This will be called by CAAFUnknown::QueryInterface().
  // 
  STDMETHOD(InternalQueryInterface)(REFIID riid, void **ppvObjOut);


public:
  //
  // This class as concrete. All AAF objects can be constructed from
  // a CLSID. This will allow subclassing all "base-classes" by
  // aggreggation.
  // 
  AAF_DECLARE_CONCRETE();
  //
  //********
};

#endif // ! __CAAFJPEG2000SubDescriptor_h__

