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

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "ModuleTestsCommon.h"
using namespace mtc;

#include "AAF.h"
#include "AAFFileKinds.h"
#include "AAFResult.h"
#include "AAFTypes.h"
#include "AAFPropertyDefs.h"
#include "CAAFBuiltinDefs.h"

#include "AAFWideString.h"

#include <iostream>
using namespace std;


const aafMobID_t        testMobID = { {0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
                                      0x13, 0x00, 0x00, 0x00,
                                      {0x95819726, 0x281d, 0x4d8e, { 0xa7, 0x23, 0x22, 0xa5, 0xc8, 0xe5, 0x81, 0xa8} } };
const aafCharacter      testMobName[] = L"Test Mob";

const char              testAIFCSummary[] = "test summary";
const aafUInt32         testAIFCSummarySize = sizeof(testAIFCSummary);

aafIOBufferDesc_t       testData[] = 
{
    {
        (aafMemPtr_t)(""),
        1
    },
    {
        (aafMemPtr_t)("ABCDEFGH"),
        9
    },
    {
        (aafMemPtr_t)("IJKLEMNOPQRSTUVW"),
        17
    },
    {
        (aafMemPtr_t)("01234"),
        6
    },
    {
        (aafMemPtr_t)("56789"),
        6
    },
    {
        (aafMemPtr_t)("!"),
        2
    }
};

const aafUInt32         testDataCount = sizeof(testData) / sizeof(testData[0]);

// The size  of the stream in the test file.
// It's set when the file is created and checked
// when the file is read
static aafInt64         testStreamSize = 0;



class CustomStreamRawStorage : public IAAFRawStorage,
                               public IAAFRandomRawStorage,
                               public IAAFStreamRawStorage
{
    public:

        // Create an instance of CustomStreamRawStorage
        static CustomStreamRawStorage* Create( const aafWChar* pFileName,
                                               const aafFileExistence_t,
                                               const aafFileAccess_t );


        // Return the number of bytes transferred with StreamXXX() methods
        aafUInt64 StreamBytesWritten() const;
        aafUInt64 StreamBytesRead() const;


        // IUnknown overrides
        virtual HRESULT STDMETHODCALLTYPE   QueryInterface( REFIID iid,
                                                            void** ppIfc );
        virtual aafUInt32 STDMETHODCALLTYPE AddRef();
        virtual aafUInt32 STDMETHODCALLTYPE Release();


        // IAAFRawStorage overrides
        virtual HRESULT STDMETHODCALLTYPE
                IsReadable( aafBoolean_t* pReadable );

        virtual HRESULT STDMETHODCALLTYPE
                Read( aafMemPtr_t   pBuffer,
                      aafUInt32     bufferSize,
                      aafUInt32*    pBytesRead );

        virtual HRESULT STDMETHODCALLTYPE
                IsWriteable( aafBoolean_t* pWriteable );

        virtual HRESULT STDMETHODCALLTYPE
                Write( aafMemConstPtr_t pBuffer,
                       aafUInt32        bufferSize,
                       aafUInt32*       pBytesWritten );

        virtual HRESULT STDMETHODCALLTYPE
                Synchronize();


        // IAAFRandomRawStorage overrides
        virtual HRESULT STDMETHODCALLTYPE
                ReadAt( aafUInt64   position,
                        aafMemPtr_t pBuffer,
                        aafUInt32   bufferSize,
                        aafUInt32*  pBytesRead );

        virtual HRESULT STDMETHODCALLTYPE
                WriteAt( aafUInt64          position,
                         aafMemConstPtr_t   pBuffer,
                         aafUInt32          bufferSize,
                         aafUInt32*         pBytesWritten );

        virtual HRESULT STDMETHODCALLTYPE
                GetSize( aafUInt64* pSize );

        virtual HRESULT STDMETHODCALLTYPE
                IsExtendable( aafBoolean_t* pExtendable );

        virtual HRESULT STDMETHODCALLTYPE
                GetExtent( aafUInt64* pExtent );

        virtual HRESULT STDMETHODCALLTYPE
                SetExtent( aafUInt64 extent );


        // IAAFStreamRawStorage overrides
        virtual HRESULT STDMETHODCALLTYPE
                StreamReadAt( aafUInt64   position,
                              aafMemPtr_t pBuffer,
                              aafUInt32   bufferSize,
                              aafUInt32*  pBytesRead );

        virtual HRESULT STDMETHODCALLTYPE
                StreamWriteAt( aafUInt64          position,
                               aafMemConstPtr_t   pBuffer,
                               aafUInt32          bufferSize,
                               aafUInt32*         pBytesWritten );

        virtual HRESULT STDMETHODCALLTYPE
                StreamReadScatterAt( aafUInt64          position,
                                     aafIOBufferDesc_t* pBuffers,
                                     aafUInt32          bufferCount,
                                     aafUInt32*         pBytesRead );

        virtual HRESULT STDMETHODCALLTYPE
                StreamWriteGatherAt( aafUInt64          position,
                                     aafIOBufferDesc_constptr pBuffers,
                                     aafUInt32          bufferCount,
                                     aafUInt32*         pBytesWritten );


    protected:

        CustomStreamRawStorage( FILE* fp,
                                const aafFileAccess_t access );
        virtual ~CustomStreamRawStorage();

        aafBoolean_t    Readable() const;
        aafBoolean_t    Writeable() const;

    private:

        FILE*                   _file;
        const aafFileAccess_t   _access;
        aafUInt64               _extent;
        aafUInt32               _refCount;
        aafUInt64               _streamBytesWritten;
        aafUInt64               _streamBytesRead;
};



/*static*/ CustomStreamRawStorage* CustomStreamRawStorage::Create(
    const aafWChar* pFileName,
    const aafFileExistence_t existence,
    const aafFileAccess_t access )
{
    assert( pFileName );
    assert( existence == kAAFFileExistence_new ||
            existence == kAAFFileExistence_existing );
    assert( access == kAAFFileAccess_read ||
            access == kAAFFileAccess_write ||
            access == kAAFFileAccess_modify );


    char  mbsFileName[FILENAME_MAX];
    size_t status = wcstombs( mbsFileName, pFileName, FILENAME_MAX );
    assert( status != (size_t)-1 );

    char*  mode = 0;
    if( access == kAAFFileAccess_write )
    {
        mode = "wb";
    }
    else if( access == kAAFFileAccess_read )
    {
        assert( existence == kAAFFileExistence_existing );
        mode = "rb";
    }
    else  // access == kAAFFileAccess_modify
    {
        if( existence == kAAFFileExistence_new )
        {
            mode = "w+b";
        }
        else  // existence == kAAFFileExistence_existing
        {
            mode = "r+b";
        }
    }
    assert( mode );


    FILE*  fp = fopen( mbsFileName, mode );
    assert( fp );


    CustomStreamRawStorage*  p_storage =
        new CustomStreamRawStorage( fp, access );
    assert( p_storage );
    p_storage->AddRef();


    return p_storage;
}



aafUInt64 CustomStreamRawStorage::StreamBytesWritten() const
{
    return _streamBytesWritten;
}



aafUInt64 CustomStreamRawStorage::StreamBytesRead() const
{
    return _streamBytesRead;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::QueryInterface(
    REFIID iid,
    void** ppIfc )
{
    if( !ppIfc )
    {
        return AAFRESULT_NULL_PARAM;
    }

    if( memcmp( &iid, &IID_IUnknown, sizeof(iid) ) == 0 )
    {
        IUnknown* runk = (IAAFRawStorage*)this;
        *ppIfc = (void*)runk;
        AddRef();
        return AAFRESULT_SUCCESS;
    }
    else if( memcmp( &iid, &IID_IAAFRawStorage, sizeof(iid) ) == 0 )
    {
        IAAFRawStorage* rrs = this;
        *ppIfc = (void*) rrs;
        AddRef();
        return AAFRESULT_SUCCESS;
    }
    else if( memcmp( &iid, &IID_IAAFRandomRawStorage, sizeof(iid) ) == 0 )
    {
        IAAFRandomRawStorage* rrrs = this;
        *ppIfc = (void*) rrrs;
        AddRef();
        return AAFRESULT_SUCCESS;
    }
    else if( memcmp( &iid, &IID_IAAFStreamRawStorage, sizeof(iid) ) == 0 )
    {
        IAAFStreamRawStorage* rsrs = this;
        *ppIfc = (void*) rsrs;
        AddRef();
        return AAFRESULT_SUCCESS;
    }
    else
    {
        return E_NOINTERFACE;
    }
}



aafUInt32 STDMETHODCALLTYPE CustomStreamRawStorage::AddRef()
{
    _refCount++;
    return _refCount;
}



aafUInt32 STDMETHODCALLTYPE CustomStreamRawStorage::Release()
{
    const aafUInt32  r = --_refCount;
    if( r == 0 )
    {
        delete this;
    }

    return r;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::IsReadable(
    aafBoolean_t* pResult )
{
    if( !pResult )
    {
        return AAFRESULT_NULL_PARAM;
    }

    *pResult = Readable();

    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::Read(
    aafMemPtr_t pBuffer,
    aafUInt32 bufferSize,
    aafUInt32* pBytesRead )
{
    if( !pBuffer )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !pBytesRead )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !Readable() )
    {
        return AAFRESULT_NOT_READABLE;
    }


    *pBytesRead = fread( pBuffer, 1, bufferSize, _file );


    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::IsWriteable(
    aafBoolean_t* pWriteable )
{
    if( !pWriteable )
    {
        return AAFRESULT_NULL_PARAM;
    }

    *pWriteable = Writeable();

    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::Write(
    aafMemConstPtr_t pBuffer,
    aafUInt32 bufferSize,
    aafUInt32* pBytesWritten )
{
    if( !pBuffer )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !pBytesWritten )
    {
        return AAFRESULT_NULL_PARAM;
    }
    if( !Writeable() )
    {
        return AAFRESULT_NOT_WRITEABLE;
    }


    *pBytesWritten = fwrite( pBuffer, 1, bufferSize, _file );


    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::Synchronize()
{
    AAFRESULT  hr = AAFRESULT_SUCCESS;


    if( Writeable() )
    {
        const int  status = fflush( _file );
        if( status != 0 )
        {
            hr = AAFRESULT_SYNCHRONIZE_FAILURE;
        }
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::ReadAt(
    aafUInt64 position,
    aafMemPtr_t pBuffer,
    aafUInt32 bufferSize,
    aafUInt32* pBytesRead )
{
    AAFRESULT  hr = AAFRESULT_SUCCESS;


    assert( position <= LONG_MAX );
    const long  fseek_to = static_cast<long>(position);
    const int  status = fseek( _file, fseek_to, SEEK_SET );
    if( status != 0 )
    {
        hr = AAFRESULT_READ_FAILURE;
    }
    else
    {
        hr = Read( pBuffer, bufferSize, pBytesRead );
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::WriteAt(
    aafUInt64 position,
    aafMemConstPtr_t pBuffer,
    aafUInt32 bufferSize,
    aafUInt32* pBytesWritten )
{
    AAFRESULT  hr = AAFRESULT_SUCCESS;


    assert( position <= LONG_MAX );
    const long  fseek_to = static_cast<long>(position);
    const int  status = fseek( _file, fseek_to, SEEK_SET );
    if( status != 0 )
    {
        hr = AAFRESULT_WRITE_FAILURE;
    }
    else
    {
        hr = Write( pBuffer, bufferSize, pBytesWritten );
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::GetSize(
    aafUInt64* pSize )
{
    if( !pSize )
    {
        return AAFRESULT_NULL_PARAM;
    }


    AAFRESULT  hr = AAFRESULT_SUCCESS;
    long  size = -1L;


    const long  oldPosition = ftell( _file );
    if( oldPosition == -1L )
    {
        hr = AAFRESULT_GETSIZE_FAILURE;
    }
    else
    {
        int  status = fseek( _file, 0, SEEK_END );
        if( status != 0 )
        {
            hr = AAFRESULT_GETSIZE_FAILURE;
        }
        else
        {
            size = ftell( _file );
            if( size == -1L )
            {
                hr = AAFRESULT_GETSIZE_FAILURE;
            }
        }

        // Restore the old position
        status = fseek( _file, oldPosition, SEEK_SET );
        if( status != 0 )
        {
            hr = AAFRESULT_GETSIZE_FAILURE;
        }
    }


    if( hr == AAFRESULT_SUCCESS )
    {
        assert( size >= 0 );
        *pSize = static_cast<aafUInt64>( size );
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::IsExtendable(
    aafBoolean_t* pExtendable )
{
    if( !pExtendable )
    {
        return AAFRESULT_NULL_PARAM;
    }


    *pExtendable = kAAFTrue;


    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::GetExtent(
    aafUInt64* pExtent )
{
    if( !pExtent )
    {
        return AAFRESULT_NULL_PARAM;
    }


    *pExtent = _extent;


    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::SetExtent(
    aafUInt64 extent )
{
    _extent = extent;
    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::StreamReadAt(
    aafUInt64 position,
    aafMemPtr_t pBuffer,
    aafUInt32 bufferSize,
    aafUInt32* pBytesRead )
{
    const HRESULT hr = ReadAt( position, pBuffer, bufferSize, pBytesRead );

    _streamBytesRead += (*pBytesRead);

    return hr;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::StreamWriteAt(
    aafUInt64 position,
    aafMemConstPtr_t pBuffer,
    aafUInt32 bufferSize,
    aafUInt32* pBytesWritten )
{
    const HRESULT hr = WriteAt( position, pBuffer, bufferSize, pBytesWritten );

    _streamBytesWritten += (*pBytesWritten);

    return hr;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::StreamReadScatterAt(
    aafUInt64 position,
    aafIOBufferDesc_t* pBuffers,
    aafUInt32 bufferCount,
    aafUInt32* pBytesRead )
{
    if( !pBuffers )
    {
        return AAFRESULT_NULL_PARAM;
    }


    AAFRESULT  hr = AAFRESULT_SUCCESS;
    aafUInt64  currentPosition = position;
    for( aafUInt32 i=0; i<bufferCount && hr == AAFRESULT_SUCCESS; i++ )
    {
        aafUInt32  byteRead = 0;
        hr = ReadAt( currentPosition, pBuffers[i].buf, pBuffers[i].bufSize, &byteRead );
        currentPosition += byteRead;
        *pBytesRead += byteRead;
    }


    _streamBytesRead += (*pBytesRead);


    return hr;
}



HRESULT STDMETHODCALLTYPE CustomStreamRawStorage::StreamWriteGatherAt(
    aafUInt64 position,
    aafIOBufferDesc_constptr pBuffers,
    aafUInt32 bufferCount,
    aafUInt32* pBytesWritten )
{
    if( !pBuffers )
    {
        return AAFRESULT_NULL_PARAM;
    }


    AAFRESULT  hr = AAFRESULT_SUCCESS;
    aafUInt64  currentPosition = position;
    for( aafUInt32 i=0; i<bufferCount && hr == AAFRESULT_SUCCESS; i++ )
    {
        aafUInt32  byteWritten = 0;
        hr = WriteAt( currentPosition,
                      pBuffers[i].buf,
                      pBuffers[i].bufSize,
                      &byteWritten );
        currentPosition += byteWritten;
        *pBytesWritten += byteWritten;
    }


    _streamBytesWritten += (*pBytesWritten);


    return hr;
}



CustomStreamRawStorage::CustomStreamRawStorage(
    FILE* fp,
    const aafFileAccess_t access ) :

    _file( fp ),
    _access( access ),
    _extent( 0 ),
    _refCount( 0 ),
    _streamBytesWritten( 0 ),
    _streamBytesRead( 0 )
{
    assert( fp );
}



CustomStreamRawStorage::~CustomStreamRawStorage()
{
    fclose( _file );
    _file = 0;
}



aafBoolean_t CustomStreamRawStorage::Readable() const
{
    return ((_access == kAAFFileAccess_read ||
             _access == kAAFFileAccess_modify) ?
            kAAFTrue : kAAFFalse);
}



aafBoolean_t CustomStreamRawStorage::Writeable() const
{
    return ((_access == kAAFFileAccess_write ||
             _access == kAAFFileAccess_modify) ?
            kAAFTrue : kAAFFalse);
}



aafUInt32 GetBufferDescriptorsDataSize(
    const aafIOBufferDesc_t* pBuffers,
    const aafUInt32 bufferCount )
{
    assert( pBuffers );


    aafUInt32 totalSize = 0;
    for( aafUInt32 i=0; i<bufferCount; i++ )
    {
        totalSize += pBuffers[i].bufSize;
    }

    return totalSize;
}



char* GetBufferDescriptorsData(
    const aafIOBufferDesc_t* pBuffers,
    const aafUInt32 bufferCount )
{
    assert( pBuffers );


    const aafUInt32  buffersDataSize =
        GetBufferDescriptorsDataSize( pBuffers, bufferCount );

    char*  pData = new char[ buffersDataSize ];
    assert( pData );

    char* p = pData;
    for( aafUInt32 i=0; i<bufferCount; i++ )
    {
        memcpy( p, pBuffers[i].buf, pBuffers[i].bufSize );
        p += pBuffers[i].bufSize;
    }

    return pData;
}



static HRESULT CreateAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t /*rawStorageType*/,
    aafProductIdentification_constref productID)
{
    AAFRESULT  hr = AAFRESULT_SUCCESS;
    CustomStreamRawStorage*  pStorage = 0;
    IAAFFile*  pFile = 0;
    IAAFHeader*  pHeader = 0;
    IAAFDictionary*  pDictionary = 0;
    IAAFMob*  pMob = 0;
    IAAFEssenceDescriptor*  pDescriptor = 0;
    IAAFAIFCDescriptor*  pAIFCDescriptor = 0;
    IAAFSourceMob*  pSourceMob = 0;
    IAAFEssenceData*  pEssenceData = 0;
    IAAFEssenceData2*  pEssenceData2 = 0;
    IAAFPlainEssenceData*  pPlainEssenceData = 0;
    IAAFPropertyValue*  pPropValue = 0;
    IAAFTypeDef*  pPropTypeDef = 0;
    IAAFTypeDefStream3*  pTypeDefStream3 = 0;
    IAAFPlainStreamData*  pPlainStreamData = 0;
    IAAFPlainStreamData2*  pTypeDefStream = 0;


    try
    {
        // Remove the previous test file if any.
        ::RemoveTestFile( pFileName );

        // Determine the file encoding to be used.
        aafUID_t effectiveFileKind = EffectiveTestFileEncoding( fileKind );


        // Create raw storage
        const aafFileExistence_t existence = kAAFFileExistence_new;
        const aafFileAccess_t access = kAAFFileAccess_modify;
        pStorage = CustomStreamRawStorage::Create( pFileName,
                                                   existence,
                                                   access );

        // Create file on the raw storage
        CheckResult( AAFCreateAAFFileOnRawStorage( pStorage,
                                                   existence,
                                                   access,
                                                   &effectiveFileKind,
                                                   0,
                                                   &productID,
                                                   &pFile ) );

        // Open the file
        CheckResult( pFile->Open() );

        // The header
        CheckResult( pFile->GetHeader( &pHeader ) );

        // The dictionary
        CheckResult( pHeader->GetDictionary( &pDictionary ) );

        // Built-in defenitions
        CAAFBuiltinDefs  defs( pDictionary );

        // Create a SourceMob
        CheckResult( defs.cdSourceMob()->CreateInstance(
                        IID_IAAFMob, (IUnknown **)&pMob ) );

        CheckResult( pMob->SetMobID( testMobID ) );
        CheckResult( pMob->SetName( testMobName ) );

        // Create an essence descriptor
        CheckResult( defs.cdAIFCDescriptor()->CreateInstance(
                        IID_IAAFEssenceDescriptor,
                        (IUnknown **)&pDescriptor ) );
        CheckResult( pDescriptor->QueryInterface(
                        IID_IAAFAIFCDescriptor, (void **)&pAIFCDescriptor ) );
        CheckResult( pAIFCDescriptor->SetSummary( testAIFCSummarySize,
                                                  (aafDataValue_t)testAIFCSummary ) );

        // Set the descriptor on the source mob
        CheckResult( pMob->QueryInterface( IID_IAAFSourceMob,
                                           (void **)&pSourceMob ) );
        CheckResult( pSourceMob->SetEssenceDescriptor( pDescriptor ) );

        CheckResult( pSourceMob->Initialize() );

        // Add the source mob to the file
        CheckResult( pHeader->AddMob( pMob ) );

        // Create essence data and add it to the file
        CheckResult( defs.cdEssenceData()->CreateInstance(
                        IID_IAAFEssenceData, (IUnknown **)&pEssenceData ) );
        CheckResult( pEssenceData->Initialize( pSourceMob ) );
        CheckResult( pHeader->AddEssenceData( pEssenceData ) );


        // Check the number of bytes transferred with the raw storage
        // stream I/O methods
        CheckExpression( pStorage->StreamBytesWritten() == 0 );
        CheckExpression( pStorage->StreamBytesRead() == 0 );


        // Get the stream property
        CheckResult( GetPropertyValue( pEssenceData,
                                       kAAFPropID_EssenceData_Data,
                                       &pPropValue ) );
        CheckResult( GetPropertyType( pEssenceData,
                                      kAAFPropID_EssenceData_Data,
                                      &pPropTypeDef ) );
        CheckResult( pPropTypeDef->QueryInterface( IID_IAAFTypeDefStream3,
                                                   (void **)&pTypeDefStream3));
        CheckResult( pTypeDefStream3->GetPlainStreamData( 0,
                                                          &pPlainStreamData));
        CheckResult( pPlainStreamData->QueryInterface( IID_IAAFPlainStreamData2,
                                                   (void **)&pTypeDefStream));


        // Total number of bytes written to the EssenceData stream
        // Need to account for the data transferred while skipping
        // KLV key and length.
        aafUInt64  totalStreamBytesWritten = pStorage->StreamBytesWritten();




        // Write stream property using high-level interface
        CheckResult( pEssenceData->QueryInterface( IID_IAAFEssenceData2,
                                                   (void **)&pEssenceData2 ) );
        CheckResult( pEssenceData2->GetPlainEssenceData( 0,
                                                         &pPlainEssenceData ) );
        aafUInt32 i;
        for( i=0; i<testDataCount; i++ )
        {
            aafUInt32  bytesWritten = 0;
            CheckResult(pPlainEssenceData->Write( testData[i].bufSize,
                                                  testData[i].buf,
                                                 &bytesWritten ) );
            CheckExpression( bytesWritten == testData[i].bufSize );

            totalStreamBytesWritten += bytesWritten;
        }


        // Write the stream using property direct interface,
        // single buffer reads
        for( i=0; i<testDataCount; i++ )
        {
            CheckResult( pTypeDefStream->Write( pPropValue,
                                                testData[i].bufSize,
                                                testData[i].buf ) );

            totalStreamBytesWritten += testData[i].bufSize;
        }

        // Write the stream using property direct interface,
        // multiple buffer writes
        {
            aafUInt32  bytesWritten = 0;
            CheckResult( pTypeDefStream->WriteGather( pPropValue,
                                                    testDataCount,
                                                    testData,
                                                    &bytesWritten ) );
            CheckExpression( bytesWritten ==
                GetBufferDescriptorsDataSize( testData, testDataCount ) );

            totalStreamBytesWritten += bytesWritten;
        }


        // Remember the stream size.
        CheckResult( pTypeDefStream->GetSize( pPropValue,
                                              &testStreamSize ) );


        // Save and close the file.
        CheckResult( pFile->Save() );
        CheckResult( pFile->Close() );
    }
    catch( HRESULT& e )
    {
        hr = e;
    }


    if( pTypeDefStream )
    {
        pTypeDefStream->Release();
        pTypeDefStream = 0;
    }
    if( pPlainStreamData )
    {
        pPlainStreamData->Release();
        pPlainStreamData = 0;
    }
    if( pTypeDefStream3 )
    {
        pTypeDefStream3->Release();
        pTypeDefStream3 = 0;
    }
    if( pPropTypeDef )
    {
        pPropTypeDef->Release();
        pPropTypeDef = 0;
    }
    if( pPropValue )
    {
        pPropValue->Release();
        pPropValue = 0;
    }
    if( pEssenceData )
    {
        pEssenceData->Release();
        pEssenceData = 0;
    }
    if( pEssenceData2 )
    {
        pEssenceData2->Release();
        pEssenceData2 = 0;
    }
    if( pPlainEssenceData )
    {
        pPlainEssenceData->Release();
        pPlainEssenceData = 0;
    }
    if( pSourceMob )
    {
        pSourceMob->Release();
        pSourceMob = 0;
    }
    if( pAIFCDescriptor )
    {
        pAIFCDescriptor->Release();
        pAIFCDescriptor = 0;
    }
    if( pDescriptor )
    {
        pDescriptor->Release();
        pDescriptor = 0;
    }
    if( pMob )
    {
        pMob->Release();
        pMob = 0;
    }
    if( pDictionary )
    {
        pDictionary->Release();
        pDictionary = 0;
    }
    if( pHeader )
    {
        pHeader->Release();
        pHeader = 0;
    }
    if( pFile )
    {
        pFile->Close(); // Ignore error if not open
        pFile->Release();
        pFile = 0;
    }
    if( pStorage )
    {
        pStorage->Release();
        pStorage = 0;
    }


    return hr;
}



static HRESULT ReadAAFFile(aafWChar * pFileName)
{
    AAFRESULT  hr = AAFRESULT_SUCCESS;
    CustomStreamRawStorage*  pStorage = 0;
    IAAFFile*  pFile = 0;
    IAAFHeader*  pHeader = 0;
    IEnumAAFMobs*  pMobs = 0;
    IAAFMob*  pMob = 0;
    IAAFSourceMob*  pSourceMob = 0;
    IAAFEssenceData*  pEssenceData = 0;
    IAAFEssenceData2*  pEssenceData2 = 0;
    IAAFPlainEssenceData*  pPlainEssenceData = 0;
    IAAFPropertyValue*  pPropValue = 0;
    IAAFTypeDef*  pPropTypeDef = 0;
    IAAFTypeDefStream3*  pTypeDefStream3 = 0;
    IAAFPlainStreamData*  pPlainStreamData = 0;
    IAAFPlainStreamData2*  pTypeDefStream = 0;


    try
    {
        // Are we reading KLV streams?
        aafUID_t  fileKind;
        aafBool isAAFFile = kAAFFalse;
        CheckResult(AAFFileIsAAFFile(pFileName, &fileKind, &isAAFFile));


        // Create raw storage
        const aafFileExistence_t existence = kAAFFileExistence_existing;
        const aafFileAccess_t access = kAAFFileAccess_read;
        pStorage = CustomStreamRawStorage::Create( pFileName,
                                                   existence,
                                                   access );

        // Create file on the raw storage
        CheckResult( AAFCreateAAFFileOnRawStorage( pStorage,
                                                   existence,
                                                   access,
                                                   0,
                                                   0,
                                                   0,
                                                   &pFile ) );

        // Open the file
        CheckResult( pFile->Open() );

        // The header
        CheckResult( pFile->GetHeader( &pHeader ) );

        // Read and verify the mobs
        CheckResult( pHeader->GetMobs( NULL, &pMobs ) );
        while( pMobs->NextOne( &pMob ) == AAFRESULT_SUCCESS )
        {
            aafMobID_t  mobID;
            CheckResult( pMob->GetMobID( &mobID ) );

            if( memcmp( &mobID, &testMobID, sizeof(aafMobID_t) ) == 0 )
            {
                // Check the mob name
                const aafUInt32 mobNameSize = sizeof(testMobName);
                aafCharacter  mobName[ mobNameSize ] = L"";
                CheckResult( pMob->GetName( mobName, mobNameSize ) );
                CheckExpression( wcscmp( mobName, testMobName ) == 0 );

                // Check if the mob is a source mob
                CheckResult( pMob->QueryInterface( IID_IAAFSourceMob,
                                                   (void **)&pSourceMob ) );
                pSourceMob->Release();
                pSourceMob = 0;
            }

            pMob->Release();
            pMob = 0;
        }


        // The test data expected to be found in the file,
        // as a single buffer
        const aafUInt32  testDataSize =
                            GetBufferDescriptorsDataSize( testData,
                                                          testDataCount );
        char*  pTestData = GetBufferDescriptorsData( testData,
                                                     testDataCount );

        // The buffer into which the data from the file will be read
        aafUInt8*  pBuffer = new aafUInt8[ testDataSize ];

        // The number test data chunks expected to be found in the file
        const size_t  readCount = 3;


        // The EssenceData object
        CheckResult( pHeader->LookupEssenceData( testMobID, &pEssenceData ) );


        // Get the stream property
        CheckResult( GetPropertyValue( pEssenceData,
                                       kAAFPropID_EssenceData_Data,
                                       &pPropValue ) );
        CheckResult( GetPropertyType( pEssenceData,
                                      kAAFPropID_EssenceData_Data,
                                      &pPropTypeDef ) );
        CheckResult( pPropTypeDef->QueryInterface( IID_IAAFTypeDefStream3,
                                                   (void **)&pTypeDefStream3));
        CheckResult( pTypeDefStream3->GetPlainStreamData( 0,
                                                          &pPlainStreamData));
        CheckResult( pPlainStreamData->QueryInterface( IID_IAAFPlainStreamData2,
                                                   (void **)&pTypeDefStream));



        // Check the stream size.
        aafInt64  streamSize = 0;
        CheckResult( pTypeDefStream->GetSize( pPropValue,
                                              &streamSize ) );
#ifdef TEST_CHECK_STREAM_SIZE_ON_RESTORE
        CheckExpression( streamSize == testStreamSize );
#endif


        // Check the number of bytes transferred with the raw storage
        // stream I/O methods
        CheckExpression( pStorage->StreamBytesWritten() == 0 );
//        CheckExpression( pStorage->StreamBytesRead() == 0 );


        // Total number of bytes read from the EssenceData stream.
        // Need to account for the data transferred while skipping
        // KLV key and length.
        aafUInt64  totalStreamBytesRead = pStorage->StreamBytesRead();


        // Read stream property of EssenceData using high-level interface
        CheckResult( pEssenceData->QueryInterface( IID_IAAFEssenceData2,
                                                   (void **)&pEssenceData2 ) );
        CheckResult( pEssenceData2->GetPlainEssenceData( 0,
                                                         &pPlainEssenceData ) );
        CheckResult( pPlainEssenceData->SetPosition( 0 ) );
        aafUInt32 i;
        for( i=0; i<readCount; i++ )
        {
            memset( pBuffer, 0, testDataSize );
            aafUInt32  bytesRead = 0;
            CheckResult(pPlainEssenceData->Read( testDataSize,
                                                 pBuffer,
                                                 &bytesRead ) );
            CheckExpression( bytesRead == testDataSize );
            CheckExpression( memcmp( pBuffer, pTestData, testDataSize ) == 0 );

            totalStreamBytesRead += bytesRead;
        }



        // Read the stream using property direct interface,
        // single buffer reads
        CheckResult( pTypeDefStream->SetPosition( pPropValue, 0 ) );
        for( i=0; i<readCount; i++ )
        {
            memset( pBuffer, 0, testDataSize );
            aafUInt32  bytesRead = 0;
            CheckResult( pTypeDefStream->Read( pPropValue,
                                               testDataSize,
                                               pBuffer,
                                               &bytesRead ) );
            CheckExpression( bytesRead == testDataSize );
            CheckExpression( memcmp( pBuffer, pTestData, testDataSize ) == 0 );

            totalStreamBytesRead += bytesRead;
        }


#if 0   // The behaviour of Read() is questionable. The implementation
        // expects the OMDataStreamProperty::read() to always read
        // zero bytes if the read goes past the end of the stream.

        // Try reading past the end of the stream,
        // single buffer reads
        {
            CheckResult( pTypeDefStream->SetPosition(
                pPropValue, testDataSize * readCount - testDataSize/2 ) );

            memset( pBuffer, 0, testDataSize );
            aafUInt32 bytesRead = 0;
            CheckResult( pTypeDefStream->Read( pPropValue,
                                               testDataSize,
                                               pBuffer,
                                               &bytesRead ) );
            CheckExpression( bytesRead == testDataSize/2 );
            CheckExpression( memcmp( pBuffer,
                                     pTestData + testDataSize-testDataSize/2,
                                     testDataSize/2 ) == 0 );

            totalStreamBytesRead += bytesRead;
        }
#endif

        // Create a vector of I/O buffer descriptors, each pointing to
        // a 1 byte piece in the target buffer.
        const aafUInt32  bufferDescriptorCount = testDataSize;
        aafIOBufferDesc_t*  pBufferDescriptors =
            new aafIOBufferDesc_t[ bufferDescriptorCount ];
        for( i=0; i<testDataSize; i++ )
        {
            assert( i < bufferDescriptorCount );
            pBufferDescriptors[i].bufSize = 1;
            pBufferDescriptors[i].buf = pBuffer + i;
            assert( pBufferDescriptors[i].buf );
        }
        assert( GetBufferDescriptorsDataSize(
                    pBufferDescriptors, bufferDescriptorCount )
                == testDataSize );


        // Read the stream using property direct interface,
        // multiple buffer reads
        CheckResult( pTypeDefStream->SetPosition( pPropValue, 0 ) );
        for( i=0; i<readCount; i++ )
        {
            memset( pBuffer, 0, testDataSize );
            aafUInt32  bytesRead = 0;
            CheckResult( pTypeDefStream->ReadScatter( pPropValue,
                                                      bufferDescriptorCount,
                                                      pBufferDescriptors,
                                                      &bytesRead ) );
            CheckExpression( bytesRead ==
                            GetBufferDescriptorsDataSize(
                                pBufferDescriptors, bufferDescriptorCount ) );
            CheckExpression( memcmp( pBuffer, pTestData, testDataSize ) == 0 );

            totalStreamBytesRead += bytesRead;
        }


        // Try reading past the end of the stream,
        // multiple buffer reads
#ifdef TEST_CHECK_STREAM_SIZE_ON_RESTORE
        {
            CheckResult( pTypeDefStream->SetPosition(
                pPropValue, testDataSize * readCount - testDataSize/2 ) );
            memset( pBuffer, 0, testDataSize );
            aafUInt32 bytesRead = 0;
            CheckResult( pTypeDefStream->ReadScatter( pPropValue,
                                                      bufferDescriptorCount,
                                                      pBufferDescriptors,
                                                      &bytesRead ) );
            CheckExpression( bytesRead == testDataSize/2 );
            CheckExpression( memcmp( pBuffer,
                                     pTestData + testDataSize-testDataSize/2,
                                     testDataSize/2 ) == 0 );

            totalStreamBytesRead += bytesRead;
        }
#endif


        delete[] pBufferDescriptors;
        pBufferDescriptors = 0;


        delete[] pTestData;
        pTestData = 0;
        delete[] pBuffer;
        pBuffer = 0;


        // Close the file.
        CheckResult( pFile->Close() );
    }
    catch( HRESULT& e )
    {
        hr = e;
    }


    if( pTypeDefStream )
    {
        pTypeDefStream->Release();
        pTypeDefStream = 0;
    }
    if( pPlainStreamData )
    {
        pPlainStreamData->Release();
        pPlainStreamData = 0;
    }
    if( pTypeDefStream3 )
    {
        pTypeDefStream3->Release();
        pTypeDefStream3 = 0;
    }
    if( pPropTypeDef )
    {
        pPropTypeDef->Release();
        pPropTypeDef = 0;
    }
    if( pPropValue )
    {
        pPropValue->Release();
        pPropValue = 0;
    }
    if( pPlainEssenceData )
    {
        pPlainEssenceData->Release();
        pPlainEssenceData = 0;
    }
    if( pEssenceData2 )
    {
        pEssenceData2->Release();
        pEssenceData2 = 0;
    }
    if( pEssenceData )
    {
        pEssenceData->Release();
        pEssenceData = 0;
    }
    if( pSourceMob )
    {
        pSourceMob->Release();
        pSourceMob = 0;
    }
    if( pMob )
    {
        pMob->Release();
        pMob = 0;
    }
    if( pMobs )
    {
        pMobs->Release();
        pMobs = 0;
    }
    if( pHeader )
    {
        pHeader->Release();
        pHeader = 0;
    }
    if( pFile )
    {
        pFile->Close(); // Ignore error if not open
        pFile->Release();
        pFile = 0;
    }
    if( pStorage )
    {
        pStorage->Release();
        pStorage = 0;
    }


    return hr;
}

// Required function prototype.
extern "C" HRESULT CAAFStreamRawStorage_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);
extern "C" HRESULT CAAFStreamRawStorage_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID)
{
	HRESULT hr = AAFRESULT_NOT_IMPLEMENTED;
	const size_t fileNameBufLen = 128;
	aafWChar pFileName[ fileNameBufLen ] = L"";
	GenerateTestFileName( productID.productName, fileKind, fileNameBufLen, pFileName );

	try
	{
		if(mode == kAAFUnitTestReadWrite)
			hr = CreateAAFFile(pFileName, fileKind, rawStorageType, productID);
		else
			hr = AAFRESULT_SUCCESS;
		if (SUCCEEDED(hr))
		
			hr = ReadAAFFile(pFileName);
	}
	catch (...)
	{
		cerr << "CAAFStreamRawStorage_test..."
			 << "Caught general C++ exception!" << endl; 
		hr = AAFRESULT_TEST_FAILED;
	}

	return hr;
}
