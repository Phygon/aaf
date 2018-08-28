

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 8.00.0603 */
/* at TIMESTAMP REMOVED
 */
/* Compiler settings for ../ref-impl/include/com-api/AAFPlugin.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AAFPlugin_h__
#define __AAFPlugin_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAAFClassExtension_FWD_DEFINED__
#define __IAAFClassExtension_FWD_DEFINED__
typedef interface IAAFClassExtension IAAFClassExtension;

#endif 	/* __IAAFClassExtension_FWD_DEFINED__ */


#ifndef __IAAFDictionaryExtension_FWD_DEFINED__
#define __IAAFDictionaryExtension_FWD_DEFINED__
typedef interface IAAFDictionaryExtension IAAFDictionaryExtension;

#endif 	/* __IAAFDictionaryExtension_FWD_DEFINED__ */


#ifndef __IAAFEssenceCodec_FWD_DEFINED__
#define __IAAFEssenceCodec_FWD_DEFINED__
typedef interface IAAFEssenceCodec IAAFEssenceCodec;

#endif 	/* __IAAFEssenceCodec_FWD_DEFINED__ */


#ifndef __IAAFEssenceCodec2_FWD_DEFINED__
#define __IAAFEssenceCodec2_FWD_DEFINED__
typedef interface IAAFEssenceCodec2 IAAFEssenceCodec2;

#endif 	/* __IAAFEssenceCodec2_FWD_DEFINED__ */


#ifndef __IAAFEssenceCodec3_FWD_DEFINED__
#define __IAAFEssenceCodec3_FWD_DEFINED__
typedef interface IAAFEssenceCodec3 IAAFEssenceCodec3;

#endif 	/* __IAAFEssenceCodec3_FWD_DEFINED__ */


#ifndef __IAAFEssenceContainer_FWD_DEFINED__
#define __IAAFEssenceContainer_FWD_DEFINED__
typedef interface IAAFEssenceContainer IAAFEssenceContainer;

#endif 	/* __IAAFEssenceContainer_FWD_DEFINED__ */


#ifndef __IAAFEssenceDataStream_FWD_DEFINED__
#define __IAAFEssenceDataStream_FWD_DEFINED__
typedef interface IAAFEssenceDataStream IAAFEssenceDataStream;

#endif 	/* __IAAFEssenceDataStream_FWD_DEFINED__ */


#ifndef __IAAFEssenceDataStream2_FWD_DEFINED__
#define __IAAFEssenceDataStream2_FWD_DEFINED__
typedef interface IAAFEssenceDataStream2 IAAFEssenceDataStream2;

#endif 	/* __IAAFEssenceDataStream2_FWD_DEFINED__ */


#ifndef __IAAFEssenceDataStreamEx_FWD_DEFINED__
#define __IAAFEssenceDataStreamEx_FWD_DEFINED__
typedef interface IAAFEssenceDataStreamEx IAAFEssenceDataStreamEx;

#endif 	/* __IAAFEssenceDataStreamEx_FWD_DEFINED__ */


#ifndef __IAAFEssenceStream_FWD_DEFINED__
#define __IAAFEssenceStream_FWD_DEFINED__
typedef interface IAAFEssenceStream IAAFEssenceStream;

#endif 	/* __IAAFEssenceStream_FWD_DEFINED__ */


#ifndef __IAAFInterpolator_FWD_DEFINED__
#define __IAAFInterpolator_FWD_DEFINED__
typedef interface IAAFInterpolator IAAFInterpolator;

#endif 	/* __IAAFInterpolator_FWD_DEFINED__ */


#ifndef __IAAFMultiEssenceCodec_FWD_DEFINED__
#define __IAAFMultiEssenceCodec_FWD_DEFINED__
typedef interface IAAFMultiEssenceCodec IAAFMultiEssenceCodec;

#endif 	/* __IAAFMultiEssenceCodec_FWD_DEFINED__ */


#ifndef __IAAFPlugin_FWD_DEFINED__
#define __IAAFPlugin_FWD_DEFINED__
typedef interface IAAFPlugin IAAFPlugin;

#endif 	/* __IAAFPlugin_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "objidl.h"
#include "AAF.h"
#include "AAFPluginTypes.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_AAFPlugin_0000_0000 */
/* [local] */ 

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
//=--------------------------------------------------------------------------=
// AAF Interfaces.
//=--------------------------------------------------------------------------=
//















extern RPC_IF_HANDLE __MIDL_itf_AAFPlugin_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AAFPlugin_0000_0000_v0_0_s_ifspec;

#ifndef __IAAFClassExtension_INTERFACE_DEFINED__
#define __IAAFClassExtension_INTERFACE_DEFINED__

/* interface IAAFClassExtension */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFClassExtension;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("65C07344-DF36-11d3-8008-00104bc9156d")
    IAAFClassExtension : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterDefinitions( 
            /* [in] */ IAAFDictionary *pDictionary) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFClassExtensionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFClassExtension * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFClassExtension * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFClassExtension * This);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterDefinitions )( 
            IAAFClassExtension * This,
            /* [in] */ IAAFDictionary *pDictionary);
        
        END_INTERFACE
    } IAAFClassExtensionVtbl;

    interface IAAFClassExtension
    {
        CONST_VTBL struct IAAFClassExtensionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFClassExtension_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFClassExtension_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFClassExtension_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFClassExtension_RegisterDefinitions(This,pDictionary)	\
    ( (This)->lpVtbl -> RegisterDefinitions(This,pDictionary) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFClassExtension_INTERFACE_DEFINED__ */


#ifndef __IAAFDictionaryExtension_INTERFACE_DEFINED__
#define __IAAFDictionaryExtension_INTERFACE_DEFINED__

/* interface IAAFDictionaryExtension */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFDictionaryExtension;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9a51e9f7-f80e-4ef1-96fd-469cd498271e")
    IAAFDictionaryExtension : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterExtensionDefinitions( 
            /* [in] */ IAAFDictionary *pDictionary) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFDictionaryExtensionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFDictionaryExtension * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFDictionaryExtension * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFDictionaryExtension * This);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterExtensionDefinitions )( 
            IAAFDictionaryExtension * This,
            /* [in] */ IAAFDictionary *pDictionary);
        
        END_INTERFACE
    } IAAFDictionaryExtensionVtbl;

    interface IAAFDictionaryExtension
    {
        CONST_VTBL struct IAAFDictionaryExtensionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFDictionaryExtension_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFDictionaryExtension_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFDictionaryExtension_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFDictionaryExtension_RegisterExtensionDefinitions(This,pDictionary)	\
    ( (This)->lpVtbl -> RegisterExtensionDefinitions(This,pDictionary) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFDictionaryExtension_INTERFACE_DEFINED__ */


#ifndef __IAAFEssenceCodec_INTERFACE_DEFINED__
#define __IAAFEssenceCodec_INTERFACE_DEFINED__

/* interface IAAFEssenceCodec */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFEssenceCodec;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3631F7A2-9121-11d2-8088-006008143e6f")
    IAAFEssenceCodec : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetEssenceAccess( 
            /* [in] */ IAAFEssenceAccess *pEssenceAccess) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountFlavours( 
            /* [out] */ aafUInt32 *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedFlavourID( 
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pVariant) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountDataDefinitions( 
            /* [out] */ aafUInt32 *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedDataDefinition( 
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pDataDefID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxCodecDisplayNameLength( 
            /* [out] */ aafUInt32 *pBufSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCodecDisplayName( 
            /* [ref][in] */ aafUID_constref flavour,
            /* [size_is][string][out] */ aafCharacter *pName,
            /* [in] */ aafUInt32 bufSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountChannels( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafUInt16 *pNumChannels) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectInfo( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafSelectInfo_t *pSelectInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ValidateEssence( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCheckVerbose_t verbose,
            /* [in] */ aafCheckWarnings_t outputWarnings,
            /* [in] */ aafUInt32 bufSize,
            /* [length_is][size_is][out] */ aafCharacter *pErrorText,
            /* [out] */ aafUInt32 *pBytesRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref flavour,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [ref][in] */ aafRational_constref sampleRate,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ aafMediaOpenMode_t openMode,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountSamples( 
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [out] */ aafLength_t *pNumSamples) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteSamples( 
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [size_is][in] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesWritten,
            /* [ref][out] */ aafUInt32 *bytesWritten) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadSamples( 
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [length_is][size_is][out] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesRead,
            /* [ref][out] */ aafUInt32 *bytesRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Seek( 
            /* [in] */ aafPosition_t sampleFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CompleteWrite( 
            /* [in] */ IAAFSourceMob *pFileMob) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateDescriptorFromStream( 
            /* [in] */ IAAFEssenceStream *pStream,
            /* [in] */ IAAFSourceMob *pSourceMob) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentEssenceStream( 
            /* [out] */ IAAFEssenceStream **ppStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutEssenceFormat( 
            /* [in] */ IAAFEssenceFormat *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceFormat( 
            /* [in] */ IAAFEssenceFormat *pFormatTemplate,
            /* [out] */ IAAFEssenceFormat **ppNewFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultEssenceFormat( 
            /* [out] */ IAAFEssenceFormat **ppNewFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceDescriptorID( 
            /* [out] */ aafUID_t *pDescriptorID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceDataID( 
            /* [out] */ aafUID_t *pEssenceDataID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedSampleSize( 
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [in] */ aafPosition_t sampleOffset,
            /* [out] */ aafLength_t *pLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLargestSampleSize( 
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [out] */ aafLength_t *pLength) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFEssenceCodecVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFEssenceCodec * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFEssenceCodec * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFEssenceCodec * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetEssenceAccess )( 
            IAAFEssenceCodec * This,
            /* [in] */ IAAFEssenceAccess *pEssenceAccess);
        
        HRESULT ( STDMETHODCALLTYPE *CountFlavours )( 
            IAAFEssenceCodec * This,
            /* [out] */ aafUInt32 *pCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedFlavourID )( 
            IAAFEssenceCodec * This,
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pVariant);
        
        HRESULT ( STDMETHODCALLTYPE *CountDataDefinitions )( 
            IAAFEssenceCodec * This,
            /* [out] */ aafUInt32 *pCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedDataDefinition )( 
            IAAFEssenceCodec * This,
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pDataDefID);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxCodecDisplayNameLength )( 
            IAAFEssenceCodec * This,
            /* [out] */ aafUInt32 *pBufSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetCodecDisplayName )( 
            IAAFEssenceCodec * This,
            /* [ref][in] */ aafUID_constref flavour,
            /* [size_is][string][out] */ aafCharacter *pName,
            /* [in] */ aafUInt32 bufSize);
        
        HRESULT ( STDMETHODCALLTYPE *CountChannels )( 
            IAAFEssenceCodec * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafUInt16 *pNumChannels);
        
        HRESULT ( STDMETHODCALLTYPE *GetSelectInfo )( 
            IAAFEssenceCodec * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafSelectInfo_t *pSelectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *ValidateEssence )( 
            IAAFEssenceCodec * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCheckVerbose_t verbose,
            /* [in] */ aafCheckWarnings_t outputWarnings,
            /* [in] */ aafUInt32 bufSize,
            /* [length_is][size_is][out] */ aafCharacter *pErrorText,
            /* [out] */ aafUInt32 *pBytesRead);
        
        HRESULT ( STDMETHODCALLTYPE *Create )( 
            IAAFEssenceCodec * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref flavour,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [ref][in] */ aafRational_constref sampleRate,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable);
        
        HRESULT ( STDMETHODCALLTYPE *Open )( 
            IAAFEssenceCodec * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ aafMediaOpenMode_t openMode,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable);
        
        HRESULT ( STDMETHODCALLTYPE *CountSamples )( 
            IAAFEssenceCodec * This,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [out] */ aafLength_t *pNumSamples);
        
        HRESULT ( STDMETHODCALLTYPE *WriteSamples )( 
            IAAFEssenceCodec * This,
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [size_is][in] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesWritten,
            /* [ref][out] */ aafUInt32 *bytesWritten);
        
        HRESULT ( STDMETHODCALLTYPE *ReadSamples )( 
            IAAFEssenceCodec * This,
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [length_is][size_is][out] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesRead,
            /* [ref][out] */ aafUInt32 *bytesRead);
        
        HRESULT ( STDMETHODCALLTYPE *Seek )( 
            IAAFEssenceCodec * This,
            /* [in] */ aafPosition_t sampleFrame);
        
        HRESULT ( STDMETHODCALLTYPE *CompleteWrite )( 
            IAAFEssenceCodec * This,
            /* [in] */ IAAFSourceMob *pFileMob);
        
        HRESULT ( STDMETHODCALLTYPE *CreateDescriptorFromStream )( 
            IAAFEssenceCodec * This,
            /* [in] */ IAAFEssenceStream *pStream,
            /* [in] */ IAAFSourceMob *pSourceMob);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentEssenceStream )( 
            IAAFEssenceCodec * This,
            /* [out] */ IAAFEssenceStream **ppStream);
        
        HRESULT ( STDMETHODCALLTYPE *PutEssenceFormat )( 
            IAAFEssenceCodec * This,
            /* [in] */ IAAFEssenceFormat *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceFormat )( 
            IAAFEssenceCodec * This,
            /* [in] */ IAAFEssenceFormat *pFormatTemplate,
            /* [out] */ IAAFEssenceFormat **ppNewFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultEssenceFormat )( 
            IAAFEssenceCodec * This,
            /* [out] */ IAAFEssenceFormat **ppNewFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceDescriptorID )( 
            IAAFEssenceCodec * This,
            /* [out] */ aafUID_t *pDescriptorID);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceDataID )( 
            IAAFEssenceCodec * This,
            /* [out] */ aafUID_t *pEssenceDataID);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedSampleSize )( 
            IAAFEssenceCodec * This,
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [in] */ aafPosition_t sampleOffset,
            /* [out] */ aafLength_t *pLength);
        
        HRESULT ( STDMETHODCALLTYPE *GetLargestSampleSize )( 
            IAAFEssenceCodec * This,
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [out] */ aafLength_t *pLength);
        
        END_INTERFACE
    } IAAFEssenceCodecVtbl;

    interface IAAFEssenceCodec
    {
        CONST_VTBL struct IAAFEssenceCodecVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFEssenceCodec_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFEssenceCodec_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFEssenceCodec_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFEssenceCodec_SetEssenceAccess(This,pEssenceAccess)	\
    ( (This)->lpVtbl -> SetEssenceAccess(This,pEssenceAccess) ) 

#define IAAFEssenceCodec_CountFlavours(This,pCount)	\
    ( (This)->lpVtbl -> CountFlavours(This,pCount) ) 

#define IAAFEssenceCodec_GetIndexedFlavourID(This,index,pVariant)	\
    ( (This)->lpVtbl -> GetIndexedFlavourID(This,index,pVariant) ) 

#define IAAFEssenceCodec_CountDataDefinitions(This,pCount)	\
    ( (This)->lpVtbl -> CountDataDefinitions(This,pCount) ) 

#define IAAFEssenceCodec_GetIndexedDataDefinition(This,index,pDataDefID)	\
    ( (This)->lpVtbl -> GetIndexedDataDefinition(This,index,pDataDefID) ) 

#define IAAFEssenceCodec_GetMaxCodecDisplayNameLength(This,pBufSize)	\
    ( (This)->lpVtbl -> GetMaxCodecDisplayNameLength(This,pBufSize) ) 

#define IAAFEssenceCodec_GetCodecDisplayName(This,flavour,pName,bufSize)	\
    ( (This)->lpVtbl -> GetCodecDisplayName(This,flavour,pName,bufSize) ) 

#define IAAFEssenceCodec_CountChannels(This,fileMob,essenceKind,stream,pNumChannels)	\
    ( (This)->lpVtbl -> CountChannels(This,fileMob,essenceKind,stream,pNumChannels) ) 

#define IAAFEssenceCodec_GetSelectInfo(This,fileMob,stream,pSelectInfo)	\
    ( (This)->lpVtbl -> GetSelectInfo(This,fileMob,stream,pSelectInfo) ) 

#define IAAFEssenceCodec_ValidateEssence(This,fileMob,stream,verbose,outputWarnings,bufSize,pErrorText,pBytesRead)	\
    ( (This)->lpVtbl -> ValidateEssence(This,fileMob,stream,verbose,outputWarnings,bufSize,pErrorText,pBytesRead) ) 

#define IAAFEssenceCodec_Create(This,fileMob,flavour,essenceKind,sampleRate,stream,compEnable)	\
    ( (This)->lpVtbl -> Create(This,fileMob,flavour,essenceKind,sampleRate,stream,compEnable) ) 

#define IAAFEssenceCodec_Open(This,fileMob,openMode,stream,compEnable)	\
    ( (This)->lpVtbl -> Open(This,fileMob,openMode,stream,compEnable) ) 

#define IAAFEssenceCodec_CountSamples(This,essenceKind,pNumSamples)	\
    ( (This)->lpVtbl -> CountSamples(This,essenceKind,pNumSamples) ) 

#define IAAFEssenceCodec_WriteSamples(This,nSamples,buflen,buffer,samplesWritten,bytesWritten)	\
    ( (This)->lpVtbl -> WriteSamples(This,nSamples,buflen,buffer,samplesWritten,bytesWritten) ) 

#define IAAFEssenceCodec_ReadSamples(This,nSamples,buflen,buffer,samplesRead,bytesRead)	\
    ( (This)->lpVtbl -> ReadSamples(This,nSamples,buflen,buffer,samplesRead,bytesRead) ) 

#define IAAFEssenceCodec_Seek(This,sampleFrame)	\
    ( (This)->lpVtbl -> Seek(This,sampleFrame) ) 

#define IAAFEssenceCodec_CompleteWrite(This,pFileMob)	\
    ( (This)->lpVtbl -> CompleteWrite(This,pFileMob) ) 

#define IAAFEssenceCodec_CreateDescriptorFromStream(This,pStream,pSourceMob)	\
    ( (This)->lpVtbl -> CreateDescriptorFromStream(This,pStream,pSourceMob) ) 

#define IAAFEssenceCodec_GetCurrentEssenceStream(This,ppStream)	\
    ( (This)->lpVtbl -> GetCurrentEssenceStream(This,ppStream) ) 

#define IAAFEssenceCodec_PutEssenceFormat(This,pFormat)	\
    ( (This)->lpVtbl -> PutEssenceFormat(This,pFormat) ) 

#define IAAFEssenceCodec_GetEssenceFormat(This,pFormatTemplate,ppNewFormat)	\
    ( (This)->lpVtbl -> GetEssenceFormat(This,pFormatTemplate,ppNewFormat) ) 

#define IAAFEssenceCodec_GetDefaultEssenceFormat(This,ppNewFormat)	\
    ( (This)->lpVtbl -> GetDefaultEssenceFormat(This,ppNewFormat) ) 

#define IAAFEssenceCodec_GetEssenceDescriptorID(This,pDescriptorID)	\
    ( (This)->lpVtbl -> GetEssenceDescriptorID(This,pDescriptorID) ) 

#define IAAFEssenceCodec_GetEssenceDataID(This,pEssenceDataID)	\
    ( (This)->lpVtbl -> GetEssenceDataID(This,pEssenceDataID) ) 

#define IAAFEssenceCodec_GetIndexedSampleSize(This,essenceDefID,sampleOffset,pLength)	\
    ( (This)->lpVtbl -> GetIndexedSampleSize(This,essenceDefID,sampleOffset,pLength) ) 

#define IAAFEssenceCodec_GetLargestSampleSize(This,essenceDefID,pLength)	\
    ( (This)->lpVtbl -> GetLargestSampleSize(This,essenceDefID,pLength) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFEssenceCodec_INTERFACE_DEFINED__ */


#ifndef __IAAFEssenceCodec2_INTERFACE_DEFINED__
#define __IAAFEssenceCodec2_INTERFACE_DEFINED__

/* interface IAAFEssenceCodec2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFEssenceCodec2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8888F7A2-9121-11d2-8088-006008143e6f")
    IAAFEssenceCodec2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetEssenceAccess( 
            /* [in] */ IAAFEssenceAccess *pEssenceAccess) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountFlavours( 
            /* [out] */ aafUInt32 *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedFlavourID( 
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pVariant) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountDataDefinitions( 
            /* [out] */ aafUInt32 *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedDataDefinition( 
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pDataDefID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxCodecDisplayNameLength( 
            /* [out] */ aafUInt32 *pBufSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCodecDisplayName( 
            /* [ref][in] */ aafUID_constref flavour,
            /* [size_is][string][out] */ aafCharacter *pName,
            /* [in] */ aafUInt32 bufSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountChannels( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafUInt16 *pNumChannels) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectInfo( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafSelectInfo_t *pSelectInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ValidateEssence( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCheckVerbose_t verbose,
            /* [in] */ aafCheckWarnings_t outputWarnings,
            /* [in] */ aafUInt32 bufSize,
            /* [length_is][size_is][out] */ aafCharacter *pErrorText,
            /* [out] */ aafUInt32 *pBytesRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref flavour,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [ref][in] */ aafRational_constref sampleRate,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ aafMediaOpenMode_t openMode,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountSamples( 
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [out] */ aafLength_t *pNumSamples) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteSamples( 
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [size_is][in] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesWritten,
            /* [ref][out] */ aafUInt32 *bytesWritten) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadSamples( 
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [length_is][size_is][out] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesRead,
            /* [ref][out] */ aafUInt32 *bytesRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Seek( 
            /* [in] */ aafPosition_t sampleFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CompleteWrite( 
            /* [in] */ IAAFSourceMob *pFileMob) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateDescriptorFromStream( 
            /* [in] */ IAAFEssenceStream *pStream,
            /* [in] */ IAAFSourceMob *pSourceMob) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentEssenceStream( 
            /* [out] */ IAAFEssenceStream **ppStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutEssenceFormat( 
            /* [in] */ IAAFEssenceFormat *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceFormat( 
            /* [in] */ IAAFEssenceFormat *pFormatTemplate,
            /* [out] */ IAAFEssenceFormat **ppNewFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultEssenceFormat( 
            /* [out] */ IAAFEssenceFormat **ppNewFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceDescriptorID( 
            /* [out] */ aafUID_t *pDescriptorID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceDataID( 
            /* [out] */ aafUID_t *pEssenceDataID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedSampleSize( 
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [in] */ aafPosition_t sampleOffset,
            /* [out] */ aafLength_t *pLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLargestSampleSize( 
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [out] */ aafLength_t *pLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFlavour( 
            /* [ref][in] */ aafUID_constref flavour) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFEssenceCodec2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFEssenceCodec2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFEssenceCodec2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetEssenceAccess )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ IAAFEssenceAccess *pEssenceAccess);
        
        HRESULT ( STDMETHODCALLTYPE *CountFlavours )( 
            IAAFEssenceCodec2 * This,
            /* [out] */ aafUInt32 *pCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedFlavourID )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pVariant);
        
        HRESULT ( STDMETHODCALLTYPE *CountDataDefinitions )( 
            IAAFEssenceCodec2 * This,
            /* [out] */ aafUInt32 *pCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedDataDefinition )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pDataDefID);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxCodecDisplayNameLength )( 
            IAAFEssenceCodec2 * This,
            /* [out] */ aafUInt32 *pBufSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetCodecDisplayName )( 
            IAAFEssenceCodec2 * This,
            /* [ref][in] */ aafUID_constref flavour,
            /* [size_is][string][out] */ aafCharacter *pName,
            /* [in] */ aafUInt32 bufSize);
        
        HRESULT ( STDMETHODCALLTYPE *CountChannels )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafUInt16 *pNumChannels);
        
        HRESULT ( STDMETHODCALLTYPE *GetSelectInfo )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafSelectInfo_t *pSelectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *ValidateEssence )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCheckVerbose_t verbose,
            /* [in] */ aafCheckWarnings_t outputWarnings,
            /* [in] */ aafUInt32 bufSize,
            /* [length_is][size_is][out] */ aafCharacter *pErrorText,
            /* [out] */ aafUInt32 *pBytesRead);
        
        HRESULT ( STDMETHODCALLTYPE *Create )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref flavour,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [ref][in] */ aafRational_constref sampleRate,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable);
        
        HRESULT ( STDMETHODCALLTYPE *Open )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ aafMediaOpenMode_t openMode,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable);
        
        HRESULT ( STDMETHODCALLTYPE *CountSamples )( 
            IAAFEssenceCodec2 * This,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [out] */ aafLength_t *pNumSamples);
        
        HRESULT ( STDMETHODCALLTYPE *WriteSamples )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [size_is][in] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesWritten,
            /* [ref][out] */ aafUInt32 *bytesWritten);
        
        HRESULT ( STDMETHODCALLTYPE *ReadSamples )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [length_is][size_is][out] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesRead,
            /* [ref][out] */ aafUInt32 *bytesRead);
        
        HRESULT ( STDMETHODCALLTYPE *Seek )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ aafPosition_t sampleFrame);
        
        HRESULT ( STDMETHODCALLTYPE *CompleteWrite )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ IAAFSourceMob *pFileMob);
        
        HRESULT ( STDMETHODCALLTYPE *CreateDescriptorFromStream )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ IAAFEssenceStream *pStream,
            /* [in] */ IAAFSourceMob *pSourceMob);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentEssenceStream )( 
            IAAFEssenceCodec2 * This,
            /* [out] */ IAAFEssenceStream **ppStream);
        
        HRESULT ( STDMETHODCALLTYPE *PutEssenceFormat )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ IAAFEssenceFormat *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceFormat )( 
            IAAFEssenceCodec2 * This,
            /* [in] */ IAAFEssenceFormat *pFormatTemplate,
            /* [out] */ IAAFEssenceFormat **ppNewFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultEssenceFormat )( 
            IAAFEssenceCodec2 * This,
            /* [out] */ IAAFEssenceFormat **ppNewFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceDescriptorID )( 
            IAAFEssenceCodec2 * This,
            /* [out] */ aafUID_t *pDescriptorID);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceDataID )( 
            IAAFEssenceCodec2 * This,
            /* [out] */ aafUID_t *pEssenceDataID);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedSampleSize )( 
            IAAFEssenceCodec2 * This,
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [in] */ aafPosition_t sampleOffset,
            /* [out] */ aafLength_t *pLength);
        
        HRESULT ( STDMETHODCALLTYPE *GetLargestSampleSize )( 
            IAAFEssenceCodec2 * This,
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [out] */ aafLength_t *pLength);
        
        HRESULT ( STDMETHODCALLTYPE *SetFlavour )( 
            IAAFEssenceCodec2 * This,
            /* [ref][in] */ aafUID_constref flavour);
        
        END_INTERFACE
    } IAAFEssenceCodec2Vtbl;

    interface IAAFEssenceCodec2
    {
        CONST_VTBL struct IAAFEssenceCodec2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFEssenceCodec2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFEssenceCodec2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFEssenceCodec2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFEssenceCodec2_SetEssenceAccess(This,pEssenceAccess)	\
    ( (This)->lpVtbl -> SetEssenceAccess(This,pEssenceAccess) ) 

#define IAAFEssenceCodec2_CountFlavours(This,pCount)	\
    ( (This)->lpVtbl -> CountFlavours(This,pCount) ) 

#define IAAFEssenceCodec2_GetIndexedFlavourID(This,index,pVariant)	\
    ( (This)->lpVtbl -> GetIndexedFlavourID(This,index,pVariant) ) 

#define IAAFEssenceCodec2_CountDataDefinitions(This,pCount)	\
    ( (This)->lpVtbl -> CountDataDefinitions(This,pCount) ) 

#define IAAFEssenceCodec2_GetIndexedDataDefinition(This,index,pDataDefID)	\
    ( (This)->lpVtbl -> GetIndexedDataDefinition(This,index,pDataDefID) ) 

#define IAAFEssenceCodec2_GetMaxCodecDisplayNameLength(This,pBufSize)	\
    ( (This)->lpVtbl -> GetMaxCodecDisplayNameLength(This,pBufSize) ) 

#define IAAFEssenceCodec2_GetCodecDisplayName(This,flavour,pName,bufSize)	\
    ( (This)->lpVtbl -> GetCodecDisplayName(This,flavour,pName,bufSize) ) 

#define IAAFEssenceCodec2_CountChannels(This,fileMob,essenceKind,stream,pNumChannels)	\
    ( (This)->lpVtbl -> CountChannels(This,fileMob,essenceKind,stream,pNumChannels) ) 

#define IAAFEssenceCodec2_GetSelectInfo(This,fileMob,stream,pSelectInfo)	\
    ( (This)->lpVtbl -> GetSelectInfo(This,fileMob,stream,pSelectInfo) ) 

#define IAAFEssenceCodec2_ValidateEssence(This,fileMob,stream,verbose,outputWarnings,bufSize,pErrorText,pBytesRead)	\
    ( (This)->lpVtbl -> ValidateEssence(This,fileMob,stream,verbose,outputWarnings,bufSize,pErrorText,pBytesRead) ) 

#define IAAFEssenceCodec2_Create(This,fileMob,flavour,essenceKind,sampleRate,stream,compEnable)	\
    ( (This)->lpVtbl -> Create(This,fileMob,flavour,essenceKind,sampleRate,stream,compEnable) ) 

#define IAAFEssenceCodec2_Open(This,fileMob,openMode,stream,compEnable)	\
    ( (This)->lpVtbl -> Open(This,fileMob,openMode,stream,compEnable) ) 

#define IAAFEssenceCodec2_CountSamples(This,essenceKind,pNumSamples)	\
    ( (This)->lpVtbl -> CountSamples(This,essenceKind,pNumSamples) ) 

#define IAAFEssenceCodec2_WriteSamples(This,nSamples,buflen,buffer,samplesWritten,bytesWritten)	\
    ( (This)->lpVtbl -> WriteSamples(This,nSamples,buflen,buffer,samplesWritten,bytesWritten) ) 

#define IAAFEssenceCodec2_ReadSamples(This,nSamples,buflen,buffer,samplesRead,bytesRead)	\
    ( (This)->lpVtbl -> ReadSamples(This,nSamples,buflen,buffer,samplesRead,bytesRead) ) 

#define IAAFEssenceCodec2_Seek(This,sampleFrame)	\
    ( (This)->lpVtbl -> Seek(This,sampleFrame) ) 

#define IAAFEssenceCodec2_CompleteWrite(This,pFileMob)	\
    ( (This)->lpVtbl -> CompleteWrite(This,pFileMob) ) 

#define IAAFEssenceCodec2_CreateDescriptorFromStream(This,pStream,pSourceMob)	\
    ( (This)->lpVtbl -> CreateDescriptorFromStream(This,pStream,pSourceMob) ) 

#define IAAFEssenceCodec2_GetCurrentEssenceStream(This,ppStream)	\
    ( (This)->lpVtbl -> GetCurrentEssenceStream(This,ppStream) ) 

#define IAAFEssenceCodec2_PutEssenceFormat(This,pFormat)	\
    ( (This)->lpVtbl -> PutEssenceFormat(This,pFormat) ) 

#define IAAFEssenceCodec2_GetEssenceFormat(This,pFormatTemplate,ppNewFormat)	\
    ( (This)->lpVtbl -> GetEssenceFormat(This,pFormatTemplate,ppNewFormat) ) 

#define IAAFEssenceCodec2_GetDefaultEssenceFormat(This,ppNewFormat)	\
    ( (This)->lpVtbl -> GetDefaultEssenceFormat(This,ppNewFormat) ) 

#define IAAFEssenceCodec2_GetEssenceDescriptorID(This,pDescriptorID)	\
    ( (This)->lpVtbl -> GetEssenceDescriptorID(This,pDescriptorID) ) 

#define IAAFEssenceCodec2_GetEssenceDataID(This,pEssenceDataID)	\
    ( (This)->lpVtbl -> GetEssenceDataID(This,pEssenceDataID) ) 

#define IAAFEssenceCodec2_GetIndexedSampleSize(This,essenceDefID,sampleOffset,pLength)	\
    ( (This)->lpVtbl -> GetIndexedSampleSize(This,essenceDefID,sampleOffset,pLength) ) 

#define IAAFEssenceCodec2_GetLargestSampleSize(This,essenceDefID,pLength)	\
    ( (This)->lpVtbl -> GetLargestSampleSize(This,essenceDefID,pLength) ) 

#define IAAFEssenceCodec2_SetFlavour(This,flavour)	\
    ( (This)->lpVtbl -> SetFlavour(This,flavour) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFEssenceCodec2_INTERFACE_DEFINED__ */


#ifndef __IAAFEssenceCodec3_INTERFACE_DEFINED__
#define __IAAFEssenceCodec3_INTERFACE_DEFINED__

/* interface IAAFEssenceCodec3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFEssenceCodec3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F375A58F-EB6A-49C7-90A2-7937329AE0E4")
    IAAFEssenceCodec3 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetEssenceAccess( 
            /* [in] */ IAAFEssenceAccess *pEssenceAccess) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountFlavours( 
            /* [out] */ aafUInt32 *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedFlavourID( 
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pVariant) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountDataDefinitions( 
            /* [out] */ aafUInt32 *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedDataDefinition( 
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pDataDefID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxCodecDisplayNameLength( 
            /* [out] */ aafUInt32 *pBufSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCodecDisplayName( 
            /* [ref][in] */ aafUID_constref flavour,
            /* [size_is][string][out] */ aafCharacter *pName,
            /* [in] */ aafUInt32 bufSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountChannels( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafUInt16 *pNumChannels) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectInfo( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafSelectInfo_t *pSelectInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ValidateEssence( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCheckVerbose_t verbose,
            /* [in] */ aafCheckWarnings_t outputWarnings,
            /* [in] */ aafUInt32 bufSize,
            /* [length_is][size_is][out] */ aafCharacter *pErrorText,
            /* [out] */ aafUInt32 *pBytesRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref flavour,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [ref][in] */ aafRational_constref sampleRate,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ aafMediaOpenMode_t openMode,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountSamples( 
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [out] */ aafLength_t *pNumSamples) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteSamples( 
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [size_is][in] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesWritten,
            /* [ref][out] */ aafUInt32 *bytesWritten) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadSamples( 
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [length_is][size_is][out] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesRead,
            /* [ref][out] */ aafUInt32 *bytesRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Seek( 
            /* [in] */ aafPosition_t sampleFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CompleteWrite( 
            /* [in] */ IAAFSourceMob *pFileMob) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateDescriptorFromStream( 
            /* [in] */ IAAFEssenceStream *pStream,
            /* [in] */ IAAFSourceMob *pSourceMob) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentEssenceStream( 
            /* [out] */ IAAFEssenceStream **ppStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutEssenceFormat( 
            /* [in] */ IAAFEssenceFormat *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceFormat( 
            /* [in] */ IAAFEssenceFormat *pFormatTemplate,
            /* [out] */ IAAFEssenceFormat **ppNewFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultEssenceFormat( 
            /* [out] */ IAAFEssenceFormat **ppNewFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceDescriptorID( 
            /* [out] */ aafUID_t *pDescriptorID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceDataID( 
            /* [out] */ aafUID_t *pEssenceDataID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedSampleSize( 
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [in] */ aafPosition_t sampleOffset,
            /* [out] */ aafLength_t *pLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLargestSampleSize( 
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [out] */ aafLength_t *pLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFlavour( 
            /* [ref][in] */ aafUID_constref flavour) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsCompressionSupported( 
            /* [in] */ aafUID_constref compression,
            /* [retval][out] */ aafBoolean_t *pIsSupported) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFEssenceCodec3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFEssenceCodec3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFEssenceCodec3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetEssenceAccess )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ IAAFEssenceAccess *pEssenceAccess);
        
        HRESULT ( STDMETHODCALLTYPE *CountFlavours )( 
            IAAFEssenceCodec3 * This,
            /* [out] */ aafUInt32 *pCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedFlavourID )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pVariant);
        
        HRESULT ( STDMETHODCALLTYPE *CountDataDefinitions )( 
            IAAFEssenceCodec3 * This,
            /* [out] */ aafUInt32 *pCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedDataDefinition )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pDataDefID);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxCodecDisplayNameLength )( 
            IAAFEssenceCodec3 * This,
            /* [out] */ aafUInt32 *pBufSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetCodecDisplayName )( 
            IAAFEssenceCodec3 * This,
            /* [ref][in] */ aafUID_constref flavour,
            /* [size_is][string][out] */ aafCharacter *pName,
            /* [in] */ aafUInt32 bufSize);
        
        HRESULT ( STDMETHODCALLTYPE *CountChannels )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafUInt16 *pNumChannels);
        
        HRESULT ( STDMETHODCALLTYPE *GetSelectInfo )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [out] */ aafSelectInfo_t *pSelectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *ValidateEssence )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCheckVerbose_t verbose,
            /* [in] */ aafCheckWarnings_t outputWarnings,
            /* [in] */ aafUInt32 bufSize,
            /* [length_is][size_is][out] */ aafCharacter *pErrorText,
            /* [out] */ aafUInt32 *pBytesRead);
        
        HRESULT ( STDMETHODCALLTYPE *Create )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref flavour,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [ref][in] */ aafRational_constref sampleRate,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable);
        
        HRESULT ( STDMETHODCALLTYPE *Open )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ aafMediaOpenMode_t openMode,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable);
        
        HRESULT ( STDMETHODCALLTYPE *CountSamples )( 
            IAAFEssenceCodec3 * This,
            /* [ref][in] */ aafUID_constref essenceKind,
            /* [out] */ aafLength_t *pNumSamples);
        
        HRESULT ( STDMETHODCALLTYPE *WriteSamples )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [size_is][in] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesWritten,
            /* [ref][out] */ aafUInt32 *bytesWritten);
        
        HRESULT ( STDMETHODCALLTYPE *ReadSamples )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ aafUInt32 nSamples,
            /* [in] */ aafUInt32 buflen,
            /* [length_is][size_is][out] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *samplesRead,
            /* [ref][out] */ aafUInt32 *bytesRead);
        
        HRESULT ( STDMETHODCALLTYPE *Seek )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ aafPosition_t sampleFrame);
        
        HRESULT ( STDMETHODCALLTYPE *CompleteWrite )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ IAAFSourceMob *pFileMob);
        
        HRESULT ( STDMETHODCALLTYPE *CreateDescriptorFromStream )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ IAAFEssenceStream *pStream,
            /* [in] */ IAAFSourceMob *pSourceMob);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentEssenceStream )( 
            IAAFEssenceCodec3 * This,
            /* [out] */ IAAFEssenceStream **ppStream);
        
        HRESULT ( STDMETHODCALLTYPE *PutEssenceFormat )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ IAAFEssenceFormat *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceFormat )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ IAAFEssenceFormat *pFormatTemplate,
            /* [out] */ IAAFEssenceFormat **ppNewFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultEssenceFormat )( 
            IAAFEssenceCodec3 * This,
            /* [out] */ IAAFEssenceFormat **ppNewFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceDescriptorID )( 
            IAAFEssenceCodec3 * This,
            /* [out] */ aafUID_t *pDescriptorID);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceDataID )( 
            IAAFEssenceCodec3 * This,
            /* [out] */ aafUID_t *pEssenceDataID);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedSampleSize )( 
            IAAFEssenceCodec3 * This,
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [in] */ aafPosition_t sampleOffset,
            /* [out] */ aafLength_t *pLength);
        
        HRESULT ( STDMETHODCALLTYPE *GetLargestSampleSize )( 
            IAAFEssenceCodec3 * This,
            /* [ref][in] */ aafUID_constref essenceDefID,
            /* [out] */ aafLength_t *pLength);
        
        HRESULT ( STDMETHODCALLTYPE *SetFlavour )( 
            IAAFEssenceCodec3 * This,
            /* [ref][in] */ aafUID_constref flavour);
        
        HRESULT ( STDMETHODCALLTYPE *IsCompressionSupported )( 
            IAAFEssenceCodec3 * This,
            /* [in] */ aafUID_constref compression,
            /* [retval][out] */ aafBoolean_t *pIsSupported);
        
        END_INTERFACE
    } IAAFEssenceCodec3Vtbl;

    interface IAAFEssenceCodec3
    {
        CONST_VTBL struct IAAFEssenceCodec3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFEssenceCodec3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFEssenceCodec3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFEssenceCodec3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFEssenceCodec3_SetEssenceAccess(This,pEssenceAccess)	\
    ( (This)->lpVtbl -> SetEssenceAccess(This,pEssenceAccess) ) 

#define IAAFEssenceCodec3_CountFlavours(This,pCount)	\
    ( (This)->lpVtbl -> CountFlavours(This,pCount) ) 

#define IAAFEssenceCodec3_GetIndexedFlavourID(This,index,pVariant)	\
    ( (This)->lpVtbl -> GetIndexedFlavourID(This,index,pVariant) ) 

#define IAAFEssenceCodec3_CountDataDefinitions(This,pCount)	\
    ( (This)->lpVtbl -> CountDataDefinitions(This,pCount) ) 

#define IAAFEssenceCodec3_GetIndexedDataDefinition(This,index,pDataDefID)	\
    ( (This)->lpVtbl -> GetIndexedDataDefinition(This,index,pDataDefID) ) 

#define IAAFEssenceCodec3_GetMaxCodecDisplayNameLength(This,pBufSize)	\
    ( (This)->lpVtbl -> GetMaxCodecDisplayNameLength(This,pBufSize) ) 

#define IAAFEssenceCodec3_GetCodecDisplayName(This,flavour,pName,bufSize)	\
    ( (This)->lpVtbl -> GetCodecDisplayName(This,flavour,pName,bufSize) ) 

#define IAAFEssenceCodec3_CountChannels(This,fileMob,essenceKind,stream,pNumChannels)	\
    ( (This)->lpVtbl -> CountChannels(This,fileMob,essenceKind,stream,pNumChannels) ) 

#define IAAFEssenceCodec3_GetSelectInfo(This,fileMob,stream,pSelectInfo)	\
    ( (This)->lpVtbl -> GetSelectInfo(This,fileMob,stream,pSelectInfo) ) 

#define IAAFEssenceCodec3_ValidateEssence(This,fileMob,stream,verbose,outputWarnings,bufSize,pErrorText,pBytesRead)	\
    ( (This)->lpVtbl -> ValidateEssence(This,fileMob,stream,verbose,outputWarnings,bufSize,pErrorText,pBytesRead) ) 

#define IAAFEssenceCodec3_Create(This,fileMob,flavour,essenceKind,sampleRate,stream,compEnable)	\
    ( (This)->lpVtbl -> Create(This,fileMob,flavour,essenceKind,sampleRate,stream,compEnable) ) 

#define IAAFEssenceCodec3_Open(This,fileMob,openMode,stream,compEnable)	\
    ( (This)->lpVtbl -> Open(This,fileMob,openMode,stream,compEnable) ) 

#define IAAFEssenceCodec3_CountSamples(This,essenceKind,pNumSamples)	\
    ( (This)->lpVtbl -> CountSamples(This,essenceKind,pNumSamples) ) 

#define IAAFEssenceCodec3_WriteSamples(This,nSamples,buflen,buffer,samplesWritten,bytesWritten)	\
    ( (This)->lpVtbl -> WriteSamples(This,nSamples,buflen,buffer,samplesWritten,bytesWritten) ) 

#define IAAFEssenceCodec3_ReadSamples(This,nSamples,buflen,buffer,samplesRead,bytesRead)	\
    ( (This)->lpVtbl -> ReadSamples(This,nSamples,buflen,buffer,samplesRead,bytesRead) ) 

#define IAAFEssenceCodec3_Seek(This,sampleFrame)	\
    ( (This)->lpVtbl -> Seek(This,sampleFrame) ) 

#define IAAFEssenceCodec3_CompleteWrite(This,pFileMob)	\
    ( (This)->lpVtbl -> CompleteWrite(This,pFileMob) ) 

#define IAAFEssenceCodec3_CreateDescriptorFromStream(This,pStream,pSourceMob)	\
    ( (This)->lpVtbl -> CreateDescriptorFromStream(This,pStream,pSourceMob) ) 

#define IAAFEssenceCodec3_GetCurrentEssenceStream(This,ppStream)	\
    ( (This)->lpVtbl -> GetCurrentEssenceStream(This,ppStream) ) 

#define IAAFEssenceCodec3_PutEssenceFormat(This,pFormat)	\
    ( (This)->lpVtbl -> PutEssenceFormat(This,pFormat) ) 

#define IAAFEssenceCodec3_GetEssenceFormat(This,pFormatTemplate,ppNewFormat)	\
    ( (This)->lpVtbl -> GetEssenceFormat(This,pFormatTemplate,ppNewFormat) ) 

#define IAAFEssenceCodec3_GetDefaultEssenceFormat(This,ppNewFormat)	\
    ( (This)->lpVtbl -> GetDefaultEssenceFormat(This,ppNewFormat) ) 

#define IAAFEssenceCodec3_GetEssenceDescriptorID(This,pDescriptorID)	\
    ( (This)->lpVtbl -> GetEssenceDescriptorID(This,pDescriptorID) ) 

#define IAAFEssenceCodec3_GetEssenceDataID(This,pEssenceDataID)	\
    ( (This)->lpVtbl -> GetEssenceDataID(This,pEssenceDataID) ) 

#define IAAFEssenceCodec3_GetIndexedSampleSize(This,essenceDefID,sampleOffset,pLength)	\
    ( (This)->lpVtbl -> GetIndexedSampleSize(This,essenceDefID,sampleOffset,pLength) ) 

#define IAAFEssenceCodec3_GetLargestSampleSize(This,essenceDefID,pLength)	\
    ( (This)->lpVtbl -> GetLargestSampleSize(This,essenceDefID,pLength) ) 

#define IAAFEssenceCodec3_SetFlavour(This,flavour)	\
    ( (This)->lpVtbl -> SetFlavour(This,flavour) ) 

#define IAAFEssenceCodec3_IsCompressionSupported(This,compression,pIsSupported)	\
    ( (This)->lpVtbl -> IsCompressionSupported(This,compression,pIsSupported) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFEssenceCodec3_INTERFACE_DEFINED__ */


#ifndef __IAAFEssenceContainer_INTERFACE_DEFINED__
#define __IAAFEssenceContainer_INTERFACE_DEFINED__

/* interface IAAFEssenceContainer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFEssenceContainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a7337031-c103-11d2-808a-006008143e6f")
    IAAFEssenceContainer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateEssenceStream( 
            /* [string][in] */ aafCharacter_constptr pName,
            /* [in] */ aafMobID_constptr pMobID,
            /* [retval][out] */ IAAFEssenceStream **ppEssenceStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateEssenceStreamWriteOnly( 
            /* [string][in] */ aafCharacter_constptr pPath,
            /* [in] */ aafMobID_constptr pMobID,
            /* [retval][out] */ IAAFEssenceStream **ppEssenceStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenEssenceStreamReadOnly( 
            /* [string][in] */ aafCharacter_constptr pFilePath,
            /* [in] */ aafMobID_constptr pMobID,
            /* [retval][out] */ IAAFEssenceStream **ppEssenceStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenEssenceStreamAppend( 
            /* [string][in] */ aafCharacter_constptr pFilePath,
            /* [in] */ aafMobID_constptr pMobID,
            /* [retval][out] */ IAAFEssenceStream **ppEssenceStream) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFEssenceContainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFEssenceContainer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFEssenceContainer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFEssenceContainer * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateEssenceStream )( 
            IAAFEssenceContainer * This,
            /* [string][in] */ aafCharacter_constptr pName,
            /* [in] */ aafMobID_constptr pMobID,
            /* [retval][out] */ IAAFEssenceStream **ppEssenceStream);
        
        HRESULT ( STDMETHODCALLTYPE *CreateEssenceStreamWriteOnly )( 
            IAAFEssenceContainer * This,
            /* [string][in] */ aafCharacter_constptr pPath,
            /* [in] */ aafMobID_constptr pMobID,
            /* [retval][out] */ IAAFEssenceStream **ppEssenceStream);
        
        HRESULT ( STDMETHODCALLTYPE *OpenEssenceStreamReadOnly )( 
            IAAFEssenceContainer * This,
            /* [string][in] */ aafCharacter_constptr pFilePath,
            /* [in] */ aafMobID_constptr pMobID,
            /* [retval][out] */ IAAFEssenceStream **ppEssenceStream);
        
        HRESULT ( STDMETHODCALLTYPE *OpenEssenceStreamAppend )( 
            IAAFEssenceContainer * This,
            /* [string][in] */ aafCharacter_constptr pFilePath,
            /* [in] */ aafMobID_constptr pMobID,
            /* [retval][out] */ IAAFEssenceStream **ppEssenceStream);
        
        END_INTERFACE
    } IAAFEssenceContainerVtbl;

    interface IAAFEssenceContainer
    {
        CONST_VTBL struct IAAFEssenceContainerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFEssenceContainer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFEssenceContainer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFEssenceContainer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFEssenceContainer_CreateEssenceStream(This,pName,pMobID,ppEssenceStream)	\
    ( (This)->lpVtbl -> CreateEssenceStream(This,pName,pMobID,ppEssenceStream) ) 

#define IAAFEssenceContainer_CreateEssenceStreamWriteOnly(This,pPath,pMobID,ppEssenceStream)	\
    ( (This)->lpVtbl -> CreateEssenceStreamWriteOnly(This,pPath,pMobID,ppEssenceStream) ) 

#define IAAFEssenceContainer_OpenEssenceStreamReadOnly(This,pFilePath,pMobID,ppEssenceStream)	\
    ( (This)->lpVtbl -> OpenEssenceStreamReadOnly(This,pFilePath,pMobID,ppEssenceStream) ) 

#define IAAFEssenceContainer_OpenEssenceStreamAppend(This,pFilePath,pMobID,ppEssenceStream)	\
    ( (This)->lpVtbl -> OpenEssenceStreamAppend(This,pFilePath,pMobID,ppEssenceStream) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFEssenceContainer_INTERFACE_DEFINED__ */


#ifndef __IAAFEssenceDataStream_INTERFACE_DEFINED__
#define __IAAFEssenceDataStream_INTERFACE_DEFINED__

/* interface IAAFEssenceDataStream */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFEssenceDataStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDDB6AB1-98DC-11d2-808a-006008143e6f")
    IAAFEssenceDataStream : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IUnknown *essenceData) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFEssenceDataStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFEssenceDataStream * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFEssenceDataStream * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFEssenceDataStream * This);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IAAFEssenceDataStream * This,
            /* [in] */ IUnknown *essenceData);
        
        END_INTERFACE
    } IAAFEssenceDataStreamVtbl;

    interface IAAFEssenceDataStream
    {
        CONST_VTBL struct IAAFEssenceDataStreamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFEssenceDataStream_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFEssenceDataStream_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFEssenceDataStream_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFEssenceDataStream_Init(This,essenceData)	\
    ( (This)->lpVtbl -> Init(This,essenceData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFEssenceDataStream_INTERFACE_DEFINED__ */


#ifndef __IAAFEssenceDataStream2_INTERFACE_DEFINED__
#define __IAAFEssenceDataStream2_INTERFACE_DEFINED__

/* interface IAAFEssenceDataStream2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFEssenceDataStream2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F8C9C2A1-DD6B-4e10-884F-012AF43550BC")
    IAAFEssenceDataStream2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IUnknown *essenceData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceData( 
            /* [retval][out] */ IAAFEssenceData **ppEssenceData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEssenceElementKey( 
            /* [ref][in] */ aafUID_constref eek,
            /* [in] */ aafUInt8 eeKind,
            /* [in] */ aafUInt8 eeCount,
            /* [in] */ aafUInt8 eeType,
            /* [in] */ aafUInt8 eeIndex,
            /* [in] */ aafSlotID_t sourceSlotID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEssenceElementKey( 
            /* [out] */ aafUID_t *pEssenceElementKey) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFEssenceDataStream2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFEssenceDataStream2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFEssenceDataStream2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFEssenceDataStream2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IAAFEssenceDataStream2 * This,
            /* [in] */ IUnknown *essenceData);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceData )( 
            IAAFEssenceDataStream2 * This,
            /* [retval][out] */ IAAFEssenceData **ppEssenceData);
        
        HRESULT ( STDMETHODCALLTYPE *SetEssenceElementKey )( 
            IAAFEssenceDataStream2 * This,
            /* [ref][in] */ aafUID_constref eek,
            /* [in] */ aafUInt8 eeKind,
            /* [in] */ aafUInt8 eeCount,
            /* [in] */ aafUInt8 eeType,
            /* [in] */ aafUInt8 eeIndex,
            /* [in] */ aafSlotID_t sourceSlotID);
        
        HRESULT ( STDMETHODCALLTYPE *GetEssenceElementKey )( 
            IAAFEssenceDataStream2 * This,
            /* [out] */ aafUID_t *pEssenceElementKey);
        
        END_INTERFACE
    } IAAFEssenceDataStream2Vtbl;

    interface IAAFEssenceDataStream2
    {
        CONST_VTBL struct IAAFEssenceDataStream2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFEssenceDataStream2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFEssenceDataStream2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFEssenceDataStream2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFEssenceDataStream2_Init(This,essenceData)	\
    ( (This)->lpVtbl -> Init(This,essenceData) ) 

#define IAAFEssenceDataStream2_GetEssenceData(This,ppEssenceData)	\
    ( (This)->lpVtbl -> GetEssenceData(This,ppEssenceData) ) 

#define IAAFEssenceDataStream2_SetEssenceElementKey(This,eek,eeKind,eeCount,eeType,eeIndex,sourceSlotID)	\
    ( (This)->lpVtbl -> SetEssenceElementKey(This,eek,eeKind,eeCount,eeType,eeIndex,sourceSlotID) ) 

#define IAAFEssenceDataStream2_GetEssenceElementKey(This,pEssenceElementKey)	\
    ( (This)->lpVtbl -> GetEssenceElementKey(This,pEssenceElementKey) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFEssenceDataStream2_INTERFACE_DEFINED__ */


#ifndef __IAAFEssenceDataStreamEx_INTERFACE_DEFINED__
#define __IAAFEssenceDataStreamEx_INTERFACE_DEFINED__

/* interface IAAFEssenceDataStreamEx */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFEssenceDataStreamEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("bc0f561a-7834-408f-b97e-813997a55c5b")
    IAAFEssenceDataStreamEx : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IUnknown *essenceData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteSampleIndex( 
            /* [in] */ aafUInt32 bytes,
            /* [size_is][out] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *bytesWritten) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadSampleIndex( 
            /* [in] */ aafUInt32 buflen,
            /* [length_is][size_is][out] */ aafDataBuffer_t pBuffer,
            /* [ref][out] */ aafUInt32 *pBytesRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SeekSampleIndex( 
            /* [in] */ aafPosition_t byteOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSampleIndexPosition( 
            /* [out] */ aafPosition_t *pPosition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSampleIndexLength( 
            /* [out] */ aafLength_t *pLength) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFEssenceDataStreamExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFEssenceDataStreamEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFEssenceDataStreamEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFEssenceDataStreamEx * This);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IAAFEssenceDataStreamEx * This,
            /* [in] */ IUnknown *essenceData);
        
        HRESULT ( STDMETHODCALLTYPE *WriteSampleIndex )( 
            IAAFEssenceDataStreamEx * This,
            /* [in] */ aafUInt32 bytes,
            /* [size_is][out] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *bytesWritten);
        
        HRESULT ( STDMETHODCALLTYPE *ReadSampleIndex )( 
            IAAFEssenceDataStreamEx * This,
            /* [in] */ aafUInt32 buflen,
            /* [length_is][size_is][out] */ aafDataBuffer_t pBuffer,
            /* [ref][out] */ aafUInt32 *pBytesRead);
        
        HRESULT ( STDMETHODCALLTYPE *SeekSampleIndex )( 
            IAAFEssenceDataStreamEx * This,
            /* [in] */ aafPosition_t byteOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSampleIndexPosition )( 
            IAAFEssenceDataStreamEx * This,
            /* [out] */ aafPosition_t *pPosition);
        
        HRESULT ( STDMETHODCALLTYPE *GetSampleIndexLength )( 
            IAAFEssenceDataStreamEx * This,
            /* [out] */ aafLength_t *pLength);
        
        END_INTERFACE
    } IAAFEssenceDataStreamExVtbl;

    interface IAAFEssenceDataStreamEx
    {
        CONST_VTBL struct IAAFEssenceDataStreamExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFEssenceDataStreamEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFEssenceDataStreamEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFEssenceDataStreamEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFEssenceDataStreamEx_Init(This,essenceData)	\
    ( (This)->lpVtbl -> Init(This,essenceData) ) 

#define IAAFEssenceDataStreamEx_WriteSampleIndex(This,bytes,buffer,bytesWritten)	\
    ( (This)->lpVtbl -> WriteSampleIndex(This,bytes,buffer,bytesWritten) ) 

#define IAAFEssenceDataStreamEx_ReadSampleIndex(This,buflen,pBuffer,pBytesRead)	\
    ( (This)->lpVtbl -> ReadSampleIndex(This,buflen,pBuffer,pBytesRead) ) 

#define IAAFEssenceDataStreamEx_SeekSampleIndex(This,byteOffset)	\
    ( (This)->lpVtbl -> SeekSampleIndex(This,byteOffset) ) 

#define IAAFEssenceDataStreamEx_GetSampleIndexPosition(This,pPosition)	\
    ( (This)->lpVtbl -> GetSampleIndexPosition(This,pPosition) ) 

#define IAAFEssenceDataStreamEx_GetSampleIndexLength(This,pLength)	\
    ( (This)->lpVtbl -> GetSampleIndexLength(This,pLength) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFEssenceDataStreamEx_INTERFACE_DEFINED__ */


#ifndef __IAAFEssenceStream_INTERFACE_DEFINED__
#define __IAAFEssenceStream_INTERFACE_DEFINED__

/* interface IAAFEssenceStream */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFEssenceStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("83402902-9146-11d2-8088-006008143e6f")
    IAAFEssenceStream : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ aafUInt32 bytes,
            /* [size_is][out] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *bytesWritten) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Read( 
            /* [in] */ aafUInt32 buflen,
            /* [length_is][size_is][out] */ aafDataBuffer_t pBuffer,
            /* [ref][out] */ aafUInt32 *pBytesRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Seek( 
            /* [in] */ aafPosition_t byteOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SeekRelative( 
            /* [in] */ aafInt32 byteOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [out] */ aafPosition_t *pPosition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLength( 
            /* [out] */ aafLength_t *pLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FlushCache( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCacheSize( 
            /* [in] */ aafUInt32 itsSize) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFEssenceStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFEssenceStream * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFEssenceStream * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFEssenceStream * This);
        
        HRESULT ( STDMETHODCALLTYPE *Write )( 
            IAAFEssenceStream * This,
            /* [in] */ aafUInt32 bytes,
            /* [size_is][out] */ aafDataBuffer_t buffer,
            /* [ref][out] */ aafUInt32 *bytesWritten);
        
        HRESULT ( STDMETHODCALLTYPE *Read )( 
            IAAFEssenceStream * This,
            /* [in] */ aafUInt32 buflen,
            /* [length_is][size_is][out] */ aafDataBuffer_t pBuffer,
            /* [ref][out] */ aafUInt32 *pBytesRead);
        
        HRESULT ( STDMETHODCALLTYPE *Seek )( 
            IAAFEssenceStream * This,
            /* [in] */ aafPosition_t byteOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SeekRelative )( 
            IAAFEssenceStream * This,
            /* [in] */ aafInt32 byteOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            IAAFEssenceStream * This,
            /* [out] */ aafPosition_t *pPosition);
        
        HRESULT ( STDMETHODCALLTYPE *GetLength )( 
            IAAFEssenceStream * This,
            /* [out] */ aafLength_t *pLength);
        
        HRESULT ( STDMETHODCALLTYPE *FlushCache )( 
            IAAFEssenceStream * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetCacheSize )( 
            IAAFEssenceStream * This,
            /* [in] */ aafUInt32 itsSize);
        
        END_INTERFACE
    } IAAFEssenceStreamVtbl;

    interface IAAFEssenceStream
    {
        CONST_VTBL struct IAAFEssenceStreamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFEssenceStream_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFEssenceStream_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFEssenceStream_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFEssenceStream_Write(This,bytes,buffer,bytesWritten)	\
    ( (This)->lpVtbl -> Write(This,bytes,buffer,bytesWritten) ) 

#define IAAFEssenceStream_Read(This,buflen,pBuffer,pBytesRead)	\
    ( (This)->lpVtbl -> Read(This,buflen,pBuffer,pBytesRead) ) 

#define IAAFEssenceStream_Seek(This,byteOffset)	\
    ( (This)->lpVtbl -> Seek(This,byteOffset) ) 

#define IAAFEssenceStream_SeekRelative(This,byteOffset)	\
    ( (This)->lpVtbl -> SeekRelative(This,byteOffset) ) 

#define IAAFEssenceStream_GetPosition(This,pPosition)	\
    ( (This)->lpVtbl -> GetPosition(This,pPosition) ) 

#define IAAFEssenceStream_GetLength(This,pLength)	\
    ( (This)->lpVtbl -> GetLength(This,pLength) ) 

#define IAAFEssenceStream_FlushCache(This)	\
    ( (This)->lpVtbl -> FlushCache(This) ) 

#define IAAFEssenceStream_SetCacheSize(This,itsSize)	\
    ( (This)->lpVtbl -> SetCacheSize(This,itsSize) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFEssenceStream_INTERFACE_DEFINED__ */


#ifndef __IAAFInterpolator_INTERFACE_DEFINED__
#define __IAAFInterpolator_INTERFACE_DEFINED__

/* interface IAAFInterpolator */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFInterpolator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("75C6CDF2-0D67-11d3-80A9-006008143e6f")
    IAAFInterpolator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetNumTypesSupported( 
            /* [out] */ aafUInt32 *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedSupportedType( 
            /* [in] */ aafUInt32 index,
            /* [out] */ IAAFTypeDef **ppType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTypeDefinition( 
            /* [out] */ IAAFTypeDef **ppTypeDef) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTypeDefinition( 
            /* [in] */ IAAFTypeDef *pTypeDef) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParameter( 
            /* [out] */ IAAFParameter **ppParameter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParameter( 
            /* [in] */ IAAFParameter *pParameter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InterpolateOne( 
            /* [in] */ aafRational_t *pInputValue,
            /* [in] */ aafUInt32 valueSize,
            /* [length_is][size_is][out] */ aafDataBuffer_t pValue,
            /* [out] */ aafUInt32 *bytesRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InterpolateMany( 
            /* [in] */ aafRational_t *pStartInputValue,
            /* [in] */ aafRational_t *pInputStep,
            /* [in] */ aafUInt32 generateCount,
            /* [out] */ aafMemPtr_t pOutputValue,
            /* [out] */ aafUInt32 *pResultCount) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFInterpolatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFInterpolator * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFInterpolator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFInterpolator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumTypesSupported )( 
            IAAFInterpolator * This,
            /* [out] */ aafUInt32 *pCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedSupportedType )( 
            IAAFInterpolator * This,
            /* [in] */ aafUInt32 index,
            /* [out] */ IAAFTypeDef **ppType);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeDefinition )( 
            IAAFInterpolator * This,
            /* [out] */ IAAFTypeDef **ppTypeDef);
        
        HRESULT ( STDMETHODCALLTYPE *SetTypeDefinition )( 
            IAAFInterpolator * This,
            /* [in] */ IAAFTypeDef *pTypeDef);
        
        HRESULT ( STDMETHODCALLTYPE *GetParameter )( 
            IAAFInterpolator * This,
            /* [out] */ IAAFParameter **ppParameter);
        
        HRESULT ( STDMETHODCALLTYPE *SetParameter )( 
            IAAFInterpolator * This,
            /* [in] */ IAAFParameter *pParameter);
        
        HRESULT ( STDMETHODCALLTYPE *InterpolateOne )( 
            IAAFInterpolator * This,
            /* [in] */ aafRational_t *pInputValue,
            /* [in] */ aafUInt32 valueSize,
            /* [length_is][size_is][out] */ aafDataBuffer_t pValue,
            /* [out] */ aafUInt32 *bytesRead);
        
        HRESULT ( STDMETHODCALLTYPE *InterpolateMany )( 
            IAAFInterpolator * This,
            /* [in] */ aafRational_t *pStartInputValue,
            /* [in] */ aafRational_t *pInputStep,
            /* [in] */ aafUInt32 generateCount,
            /* [out] */ aafMemPtr_t pOutputValue,
            /* [out] */ aafUInt32 *pResultCount);
        
        END_INTERFACE
    } IAAFInterpolatorVtbl;

    interface IAAFInterpolator
    {
        CONST_VTBL struct IAAFInterpolatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFInterpolator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFInterpolator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFInterpolator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFInterpolator_GetNumTypesSupported(This,pCount)	\
    ( (This)->lpVtbl -> GetNumTypesSupported(This,pCount) ) 

#define IAAFInterpolator_GetIndexedSupportedType(This,index,ppType)	\
    ( (This)->lpVtbl -> GetIndexedSupportedType(This,index,ppType) ) 

#define IAAFInterpolator_GetTypeDefinition(This,ppTypeDef)	\
    ( (This)->lpVtbl -> GetTypeDefinition(This,ppTypeDef) ) 

#define IAAFInterpolator_SetTypeDefinition(This,pTypeDef)	\
    ( (This)->lpVtbl -> SetTypeDefinition(This,pTypeDef) ) 

#define IAAFInterpolator_GetParameter(This,ppParameter)	\
    ( (This)->lpVtbl -> GetParameter(This,ppParameter) ) 

#define IAAFInterpolator_SetParameter(This,pParameter)	\
    ( (This)->lpVtbl -> SetParameter(This,pParameter) ) 

#define IAAFInterpolator_InterpolateOne(This,pInputValue,valueSize,pValue,bytesRead)	\
    ( (This)->lpVtbl -> InterpolateOne(This,pInputValue,valueSize,pValue,bytesRead) ) 

#define IAAFInterpolator_InterpolateMany(This,pStartInputValue,pInputStep,generateCount,pOutputValue,pResultCount)	\
    ( (This)->lpVtbl -> InterpolateMany(This,pStartInputValue,pInputStep,generateCount,pOutputValue,pResultCount) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFInterpolator_INTERFACE_DEFINED__ */


#ifndef __IAAFMultiEssenceCodec_INTERFACE_DEFINED__
#define __IAAFMultiEssenceCodec_INTERFACE_DEFINED__

/* interface IAAFMultiEssenceCodec */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFMultiEssenceCodec;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7F93992D-DDA3-11d3-8008-00104bc9156d")
    IAAFMultiEssenceCodec : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE MultiCreate( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref flavour,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable,
            /* [in] */ aafUInt32 numParms,
            /* [size_is][in] */ aafmMultiCreate_t *createParms) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MultiOpen( 
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ aafMediaOpenMode_t openMode,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteBlocks( 
            /* [in] */ aafDeinterleave_t inter,
            /* [in] */ aafUInt16 xferBlockCount,
            /* [size_is][in] */ aafmMultiXfer_t *pTransferParm,
            /* [size_is][out] */ aafmMultiResult_t *pResultParm) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadBlocks( 
            /* [in] */ aafDeinterleave_t inter,
            /* [in] */ aafUInt16 xferBlockCount,
            /* [size_is][out] */ aafmMultiXfer_t *pTransferParm,
            /* [size_is][out] */ aafmMultiResult_t *pResultParm) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFMultiEssenceCodecVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFMultiEssenceCodec * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFMultiEssenceCodec * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFMultiEssenceCodec * This);
        
        HRESULT ( STDMETHODCALLTYPE *MultiCreate )( 
            IAAFMultiEssenceCodec * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [ref][in] */ aafUID_constref flavour,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable,
            /* [in] */ aafUInt32 numParms,
            /* [size_is][in] */ aafmMultiCreate_t *createParms);
        
        HRESULT ( STDMETHODCALLTYPE *MultiOpen )( 
            IAAFMultiEssenceCodec * This,
            /* [in] */ IAAFSourceMob *fileMob,
            /* [in] */ aafMediaOpenMode_t openMode,
            /* [in] */ IAAFEssenceStream *stream,
            /* [in] */ aafCompressEnable_t compEnable);
        
        HRESULT ( STDMETHODCALLTYPE *WriteBlocks )( 
            IAAFMultiEssenceCodec * This,
            /* [in] */ aafDeinterleave_t inter,
            /* [in] */ aafUInt16 xferBlockCount,
            /* [size_is][in] */ aafmMultiXfer_t *pTransferParm,
            /* [size_is][out] */ aafmMultiResult_t *pResultParm);
        
        HRESULT ( STDMETHODCALLTYPE *ReadBlocks )( 
            IAAFMultiEssenceCodec * This,
            /* [in] */ aafDeinterleave_t inter,
            /* [in] */ aafUInt16 xferBlockCount,
            /* [size_is][out] */ aafmMultiXfer_t *pTransferParm,
            /* [size_is][out] */ aafmMultiResult_t *pResultParm);
        
        END_INTERFACE
    } IAAFMultiEssenceCodecVtbl;

    interface IAAFMultiEssenceCodec
    {
        CONST_VTBL struct IAAFMultiEssenceCodecVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFMultiEssenceCodec_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFMultiEssenceCodec_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFMultiEssenceCodec_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFMultiEssenceCodec_MultiCreate(This,fileMob,flavour,stream,compEnable,numParms,createParms)	\
    ( (This)->lpVtbl -> MultiCreate(This,fileMob,flavour,stream,compEnable,numParms,createParms) ) 

#define IAAFMultiEssenceCodec_MultiOpen(This,fileMob,openMode,stream,compEnable)	\
    ( (This)->lpVtbl -> MultiOpen(This,fileMob,openMode,stream,compEnable) ) 

#define IAAFMultiEssenceCodec_WriteBlocks(This,inter,xferBlockCount,pTransferParm,pResultParm)	\
    ( (This)->lpVtbl -> WriteBlocks(This,inter,xferBlockCount,pTransferParm,pResultParm) ) 

#define IAAFMultiEssenceCodec_ReadBlocks(This,inter,xferBlockCount,pTransferParm,pResultParm)	\
    ( (This)->lpVtbl -> ReadBlocks(This,inter,xferBlockCount,pTransferParm,pResultParm) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFMultiEssenceCodec_INTERFACE_DEFINED__ */


#ifndef __IAAFPlugin_INTERFACE_DEFINED__
#define __IAAFPlugin_INTERFACE_DEFINED__

/* interface IAAFPlugin */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAAFPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3631F7A4-9121-11d2-8088-006008143e6f")
    IAAFPlugin : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CountDefinitions( 
            /* [out] */ aafUInt32 *pDefCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedDefinitionID( 
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pPluginID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPluginDescriptorID( 
            /* [out] */ aafUID_t *pPluginID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedDefinitionObject( 
            /* [in] */ aafUInt32 index,
            /* [in] */ IAAFDictionary *pDictionary,
            /* [out] */ IAAFDefObject **pDefObject) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateDescriptor( 
            /* [in] */ IAAFDictionary *pDictionary,
            /* [out] */ IAAFPluginDef **pPluginDef) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAAFPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAAFPlugin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAAFPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAAFPlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *CountDefinitions )( 
            IAAFPlugin * This,
            /* [out] */ aafUInt32 *pDefCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedDefinitionID )( 
            IAAFPlugin * This,
            /* [in] */ aafUInt32 index,
            /* [out] */ aafUID_t *pPluginID);
        
        HRESULT ( STDMETHODCALLTYPE *GetPluginDescriptorID )( 
            IAAFPlugin * This,
            /* [out] */ aafUID_t *pPluginID);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexedDefinitionObject )( 
            IAAFPlugin * This,
            /* [in] */ aafUInt32 index,
            /* [in] */ IAAFDictionary *pDictionary,
            /* [out] */ IAAFDefObject **pDefObject);
        
        HRESULT ( STDMETHODCALLTYPE *CreateDescriptor )( 
            IAAFPlugin * This,
            /* [in] */ IAAFDictionary *pDictionary,
            /* [out] */ IAAFPluginDef **pPluginDef);
        
        END_INTERFACE
    } IAAFPluginVtbl;

    interface IAAFPlugin
    {
        CONST_VTBL struct IAAFPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAAFPlugin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAAFPlugin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAAFPlugin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAAFPlugin_CountDefinitions(This,pDefCount)	\
    ( (This)->lpVtbl -> CountDefinitions(This,pDefCount) ) 

#define IAAFPlugin_GetIndexedDefinitionID(This,index,pPluginID)	\
    ( (This)->lpVtbl -> GetIndexedDefinitionID(This,index,pPluginID) ) 

#define IAAFPlugin_GetPluginDescriptorID(This,pPluginID)	\
    ( (This)->lpVtbl -> GetPluginDescriptorID(This,pPluginID) ) 

#define IAAFPlugin_GetIndexedDefinitionObject(This,index,pDictionary,pDefObject)	\
    ( (This)->lpVtbl -> GetIndexedDefinitionObject(This,index,pDictionary,pDefObject) ) 

#define IAAFPlugin_CreateDescriptor(This,pDictionary,pPluginDef)	\
    ( (This)->lpVtbl -> CreateDescriptor(This,pDictionary,pPluginDef) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAAFPlugin_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


