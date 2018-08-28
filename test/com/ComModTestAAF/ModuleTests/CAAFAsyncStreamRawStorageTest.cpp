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

#include "ModuleTestsCommon.h"
using namespace mtc;

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "AAF.h"
#include "AAFPropertyDefs.h"
#include "AAFResult.h"
#include "AAFTypes.h"
#include "CAAFBuiltinDefs.h"

#include <iostream>
using namespace std;


// Define USE_WIN32_IO to use raw storage implemented
// in terms of WIN32 file I/O API.
//#define USE_WIN32_IO

// Define USE_ASYNC_IO to use asynchronous I/O system calls
//#define USE_ASYNC_IO

#ifdef USE_WIN32_IO
#include <windows.h>
#else
#include <stdio.h>
#endif


const aafMobID_t    testMobIDs[] =
{
    {{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
    0x13, 0x00, 0x00, 0x00,
    {0xe41dd2fa, 0x130f, 0x4ecc, {0xad, 0x7f, 0xaf, 0xd4, 0xe8, 0xb6, 0xa5, 0xfe}}},

    {{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
    0x13, 0x00, 0x00, 0x00,
    {0xa18d245b, 0x120d, 0x40ee, {0x93, 0x57, 0x5d, 0x53, 0xea, 0x7f, 0xb1, 0xcd}}},

    {{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
    0x13, 0x00, 0x00, 0x00,
    {0x2edc9739, 0x8ccd, 0x4fdb, {0x9e, 0xf1, 0x35, 0xdb, 0x03, 0xf4, 0x25, 0xfb}}},

    {{0x06, 0x0c, 0x2b, 0x34, 0x02, 0x05, 0x11, 0x01, 0x01, 0x00, 0x10, 0x00},
    0x13, 0x00, 0x00, 0x00,
    {0xca2d0786, 0x0ef5, 0x4613, {0xa0, 0x4a, 0xa0, 0x2d, 0xcd, 0x08, 0xee, 0x91}}}
};
const size_t testMobCount = sizeof(testMobIDs)/sizeof(testMobIDs[0]);

const aafCharacter*  testMobNames[testMobCount] =
{
    L"Test Mob 00",
    L"Test Mob 01",
    L"Test Mob 02",
    L"Test Mob 03"
};



class CustomAsyncStreamRawStorage;
class CustomIOCompletion;


static HRESULT Test_IAAFAsyncStreamRawStorage_WriteAsyncAt(
    IAAFEssenceData*,
    testMode_t );
static HRESULT Test_IAAFAsyncStreamRawStorage_ReadAsyncAt(
    IAAFEssenceData*,
    testMode_t );
static HRESULT Test_IAAFAsyncStreamRawStorage_WriteGatherAsyncAt(
    IAAFEssenceData*,
    testMode_t );
static HRESULT Test_IAAFAsyncStreamRawStorage_ReadScatterAsyncAt(
    IAAFEssenceData*,
    testMode_t );

static HRESULT CreateEssenceData(
    IAAFHeader*,
    const aafMobID_t&,
    const aafCharacter*,
    IAAFEssenceData** );
static HRESULT GetEssenceDataTypeAndValue(
    IAAFEssenceData*,
    IAAFTypeDefStream2**,
    IAAFPropertyValue** );
static aafIOBufferDesc_t* AllocateScatteredBuffers(
    const aafIOBufferDesc_t*,
    const size_t );
static void DeleteScatteredBuffers(
    aafIOBufferDesc_t*,
    const size_t );
static bool CompareScatteredBuffers(
    const aafIOBufferDesc_t*,
    const aafIOBufferDesc_t*,
    const size_t );

static bool AllCompleted(
    CustomIOCompletion**,
    size_t );
static void Wait(
    int );


static CustomAsyncStreamRawStorage* CreateCustomAsyncStreamRawStorageInstance(
    const aafWChar* pFileName,
    const aafFileExistence_t,
    const aafFileAccess_t );



//----------------------------------------------------------------------------
//
//
//----------------------------------------------------------------------------
class CustomAsyncStreamRawStorage : public IAAFRawStorage,
                                    public IAAFRandomRawStorage,
                                    public IAAFAsyncStreamRawStorage
{
    public:

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
                IsWriteable( aafBoolean_t* pWriteable );


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
                IsExtendable( aafBoolean_t* pExtendable );

        virtual HRESULT STDMETHODCALLTYPE
                GetExtent( aafUInt64* pExtent );

        virtual HRESULT STDMETHODCALLTYPE
                SetExtent( aafUInt64 extent );


        // IAAFAsyncStreamRawStorage overrides
        virtual HRESULT STDMETHODCALLTYPE
                StreamReadAsyncAt( aafUInt64        position,
                                   aafMemPtr_t      pBuffer,
                                   aafUInt32        bufferSize,
                                   IAAFIOCompletion* pCompletion,
                                   aafMemConstPtr_t pClientData );

        virtual HRESULT STDMETHODCALLTYPE
                StreamWriteAsyncAt( aafUInt64          position,
                                    aafMemConstPtr_t   pBuffer,
                                    aafUInt32          bufferSize,
                                    IAAFIOCompletion*  pCompletion,
                                    aafMemConstPtr_t   pClientData );

        virtual HRESULT STDMETHODCALLTYPE
                StreamReadScatterAsyncAt( aafUInt64         position,
                                          aafIOBufferDesc_t* pBuffers,
                                          aafUInt32         bufferCount,
                                          IAAFIOCompletion* pCompletion,
                                          aafMemConstPtr_t  pClientData );

        virtual HRESULT STDMETHODCALLTYPE
                StreamWriteGatherAsyncAt( aafUInt64         position,
                                          aafIOBufferDesc_constptr pBuffers,
                                          aafUInt32         bufferCount,
                                          IAAFIOCompletion* pCompletion,
                                          aafMemConstPtr_t  pClientData );


    protected:

        CustomAsyncStreamRawStorage( const aafFileAccess_t access );
        virtual ~CustomAsyncStreamRawStorage();

        aafBoolean_t    Readable() const;
        aafBoolean_t    Writeable() const;

        virtual aafBoolean_t    SetPosition( aafUInt64 position ) = 0;


    private:

        const aafFileAccess_t   _access;
        aafUInt64               _extent;
        aafUInt32               _refCount;
        aafUInt64               _streamBytesWritten;
        aafUInt64               _streamBytesRead;
};



aafUInt64 CustomAsyncStreamRawStorage::StreamBytesWritten() const
{
    return _streamBytesWritten;
}



aafUInt64 CustomAsyncStreamRawStorage::StreamBytesRead() const
{
    return _streamBytesRead;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::QueryInterface(
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
    else if( memcmp( &iid, &IID_IAAFAsyncStreamRawStorage, sizeof(iid) ) == 0 )
    {
        IAAFAsyncStreamRawStorage* rasrs = this;
        *ppIfc = (void*) rasrs;
        AddRef();
        return AAFRESULT_SUCCESS;
    }
    else
    {
        return E_NOINTERFACE;
    }
}



aafUInt32 STDMETHODCALLTYPE CustomAsyncStreamRawStorage::AddRef()
{
    _refCount++;
    return _refCount;
}



aafUInt32 STDMETHODCALLTYPE CustomAsyncStreamRawStorage::Release()
{
    const aafUInt32  r = --_refCount;
    if( r == 0 )
    {
        delete this;
    }

    return r;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::IsReadable(
    aafBoolean_t* pResult )
{
    if( !pResult )
    {
        return AAFRESULT_NULL_PARAM;
    }

    *pResult = Readable();

    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::IsWriteable(
    aafBoolean_t* pWriteable )
{
    if( !pWriteable )
    {
        return AAFRESULT_NULL_PARAM;
    }

    *pWriteable = Writeable();

    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::ReadAt(
    aafUInt64 position,
    aafMemPtr_t pBuffer,
    aafUInt32 bufferSize,
    aafUInt32* pBytesRead )
{
    AAFRESULT  hr = AAFRESULT_SUCCESS;


    if( !SetPosition( position ) )
    {
        hr = AAFRESULT_READ_FAILURE;
    }
    else
    {
        hr = Read( pBuffer, bufferSize, pBytesRead );
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::WriteAt(
    aafUInt64 position,
    aafMemConstPtr_t pBuffer,
    aafUInt32 bufferSize,
    aafUInt32* pBytesWritten )
{
    AAFRESULT  hr = AAFRESULT_SUCCESS;


    if( !SetPosition( position ) )
    {
        hr = AAFRESULT_WRITE_FAILURE;
    }
    else
    {
        hr = Write( pBuffer, bufferSize, pBytesWritten );
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::IsExtendable(
    aafBoolean_t* pExtendable )
{
    if( !pExtendable )
    {
        return AAFRESULT_NULL_PARAM;
    }


    *pExtendable = kAAFTrue;


    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::GetExtent(
    aafUInt64* pExtent )
{
    if( !pExtent )
    {
        return AAFRESULT_NULL_PARAM;
    }


    *pExtent = _extent;


    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::SetExtent(
    aafUInt64 extent )
{
    _extent = extent;
    return AAFRESULT_SUCCESS;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::StreamReadAsyncAt(
    aafUInt64 position,
    aafMemPtr_t pBuffer,
    aafUInt32 bufferSize,
    IAAFIOCompletion* pCompletion,
    aafMemConstPtr_t pClientData )
{
    HRESULT hr = AAFRESULT_SUCCESS;

    aafUInt32  bytesRead = 0;
    hr = ReadAt( position, pBuffer, bufferSize, &bytesRead );

    _streamBytesRead += bytesRead;

    if( pCompletion )
    {
        pCompletion->Completed( hr, bytesRead, pClientData );
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::StreamWriteAsyncAt(
    aafUInt64 position,
    aafMemConstPtr_t pBuffer,
    aafUInt32 bufferSize,
    IAAFIOCompletion* pCompletion,
    aafMemConstPtr_t pClientData )
{
    HRESULT hr = AAFRESULT_SUCCESS;


    aafUInt32  bytesWritten = 0;
    hr = WriteAt( position, pBuffer, bufferSize, &bytesWritten );

    _streamBytesWritten += bytesWritten;

    if( pCompletion )
    {
        pCompletion->Completed( hr, bytesWritten, pClientData );
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::StreamReadScatterAsyncAt(
    aafUInt64 position,
    aafIOBufferDesc_t* pBuffers,
    aafUInt32 bufferCount,
    IAAFIOCompletion* pCompletion,
    aafMemConstPtr_t pClientData )
{
    if( !pBuffers )
    {
        return AAFRESULT_NULL_PARAM;
    }


    AAFRESULT  hr = AAFRESULT_SUCCESS;
    aafUInt64  currentPosition = position;
    aafUInt32  totalBytesRead = 0;
    for( aafUInt32 i=0; i<bufferCount && hr == AAFRESULT_SUCCESS; i++ )
    {
        aafUInt32  byteRead = 0;
        hr = ReadAt( currentPosition, pBuffers[i].buf, pBuffers[i].bufSize, &byteRead );
        currentPosition += byteRead;
        totalBytesRead += byteRead;
    }

    _streamBytesRead += totalBytesRead;

    if( pCompletion )
    {
        pCompletion->Completed( hr, totalBytesRead, pClientData );
    }

    return hr;
}



HRESULT STDMETHODCALLTYPE CustomAsyncStreamRawStorage::StreamWriteGatherAsyncAt(
    aafUInt64 position,
    aafIOBufferDesc_constptr pBuffers,
    aafUInt32 bufferCount,
    IAAFIOCompletion* pCompletion,
    aafMemConstPtr_t pClientData )
{
    if( !pBuffers )
    {
        return AAFRESULT_NULL_PARAM;
    }


    AAFRESULT  hr = AAFRESULT_SUCCESS;
    aafUInt64  currentPosition = position;
    aafUInt32  totalByteWritten = 0;
    for( aafUInt32 i=0; i<bufferCount && hr == AAFRESULT_SUCCESS; i++ )
    {
        aafUInt32  byteWritten = 0;
        hr = WriteAt( currentPosition,
                      pBuffers[i].buf,
                      pBuffers[i].bufSize,
                      &byteWritten );
        currentPosition += byteWritten;
        totalByteWritten += byteWritten;
    }

    _streamBytesWritten += totalByteWritten;

    if( pCompletion )
    {
        pCompletion->Completed( hr, totalByteWritten, pClientData );
    }

    return hr;
}



CustomAsyncStreamRawStorage::CustomAsyncStreamRawStorage(
    const aafFileAccess_t access ) :

    _access( access ),
    _extent( 0 ),
    _refCount( 0 ),
    _streamBytesWritten( 0 ),
    _streamBytesRead( 0 )
{
}



CustomAsyncStreamRawStorage::~CustomAsyncStreamRawStorage()
{
}



aafBoolean_t CustomAsyncStreamRawStorage::Readable() const
{
    return ((_access == kAAFFileAccess_read ||
             _access == kAAFFileAccess_modify) ?
            kAAFTrue : kAAFFalse);
}



aafBoolean_t CustomAsyncStreamRawStorage::Writeable() const
{
    return ((_access == kAAFFileAccess_write ||
             _access == kAAFFileAccess_modify) ?
            kAAFTrue : kAAFFalse);
}



//----------------------------------------------------------------------------
//
//
//----------------------------------------------------------------------------
class StdioAsyncStreamRawStorage : public CustomAsyncStreamRawStorage
{
    public:

        // Create an instance of StdioAsyncStreamRawStorage
        static StdioAsyncStreamRawStorage* Create( const aafWChar* pFileName,
                                                   const aafFileExistence_t,
                                                   const aafFileAccess_t );


        // IAAFRawStorage overrides
        virtual HRESULT STDMETHODCALLTYPE
                Read( aafMemPtr_t   pBuffer,
                      aafUInt32     bufferSize,
                      aafUInt32*    pBytesRead );

        virtual HRESULT STDMETHODCALLTYPE
                Write( aafMemConstPtr_t pBuffer,
                       aafUInt32        bufferSize,
                       aafUInt32*       pBytesWritten );

        virtual HRESULT STDMETHODCALLTYPE
                Synchronize();


        // IAAFRandomRawStorage overrides
        virtual HRESULT STDMETHODCALLTYPE
                GetSize( aafUInt64* pSize );


    protected:

        StdioAsyncStreamRawStorage( FILE* fp,
                                    const aafFileAccess_t access );
        virtual ~StdioAsyncStreamRawStorage();

        virtual aafBoolean_t    SetPosition( aafUInt64 position );


    private:

        FILE*                   _file;
};



/*static*/ StdioAsyncStreamRawStorage* StdioAsyncStreamRawStorage::Create(
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


    StdioAsyncStreamRawStorage*  p_storage =
        new StdioAsyncStreamRawStorage( fp, access );
    assert( p_storage );
    p_storage->AddRef();


    return p_storage;
}



HRESULT STDMETHODCALLTYPE StdioAsyncStreamRawStorage::Read(
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



HRESULT STDMETHODCALLTYPE StdioAsyncStreamRawStorage::Write(
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



HRESULT STDMETHODCALLTYPE StdioAsyncStreamRawStorage::Synchronize()
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



HRESULT STDMETHODCALLTYPE StdioAsyncStreamRawStorage::GetSize(
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



StdioAsyncStreamRawStorage::StdioAsyncStreamRawStorage(
    FILE* fp,
    const aafFileAccess_t access ) :

    CustomAsyncStreamRawStorage( access ),
    _file( fp )
{
    assert( fp );
}



StdioAsyncStreamRawStorage::~StdioAsyncStreamRawStorage()
{
    fclose( _file );
    _file = 0;
}



aafBoolean_t StdioAsyncStreamRawStorage::SetPosition(
    aafUInt64 position )
{
    aafBoolean_t  succeeded = kAAFTrue;


    assert( position <= LONG_MAX );
    const long  fseek_to = static_cast<long>(position);
    const int  status = fseek( _file, fseek_to, SEEK_SET );
    if( status != 0 )
    {
        succeeded = kAAFFalse;
    }


    return succeeded;
}



#ifdef USE_WIN32_IO
//----------------------------------------------------------------------------
//
//
//----------------------------------------------------------------------------
class FileIoOperation
{
    public:

        FileIoOperation( aafUInt64 position,
                         IAAFIOCompletion* completion,
                         aafMemConstPtr_t pClientData );
        virtual ~FileIoOperation();


        IAAFIOCompletion*   Completion() const
        {
            return _completion;
        }
        aafMemConstPtr_t    ClientData() const
        {
            return _clientData;
        }
        OVERLAPPED*         Overlapped() const
        {
            return _overlapped;
        }

    private:

        IAAFIOCompletion*   _completion;
        aafMemConstPtr_t    _clientData;
        OVERLAPPED*         _overlapped;
};



FileIoOperation::FileIoOperation(
    aafUInt64 position,
    IAAFIOCompletion* completion,
    aafMemConstPtr_t clientData ) :

    _completion( completion ),
    _clientData( clientData ),
    _overlapped( new OVERLAPPED )
{
    memset( _overlapped, 0, sizeof(OVERLAPPED) );
    _overlapped->Offset = (LONG)(position & 0x00000000FFFFFFFF);
    _overlapped->OffsetHigh = (LONG)((position & 0xFFFFFFFF00000000) >> 32);
    _overlapped->hEvent = CreateEvent( 0, FALSE, FALSE, 0 );
}



FileIoOperation::~FileIoOperation()
{
    CloseHandle( _overlapped->hEvent );
    delete _overlapped;
    _overlapped = 0;
}



//----------------------------------------------------------------------------
//
//
//----------------------------------------------------------------------------
class FileIoThread
{
    public:

        FileIoThread( HANDLE file );
        virtual ~FileIoThread();

        void        Start();
        void        Finish();

        BOOL        Read( aafUInt64 position,
                          aafMemPtr_t pBuffer,
                          aafUInt32 bufferSize,
                          IAAFIOCompletion* pCompletion,
                          aafMemConstPtr_t pClientData );

        BOOL        Write( aafUInt64 position,
                           aafMemConstPtr_t pBuffer,
                           aafUInt32 bufferSize,
                           IAAFIOCompletion* pCompletion,
                           aafMemConstPtr_t pClientData );

    private:

        int                 UnusedOperationIndex() const;

        static DWORD WINAPI ThreadProc( void *threadPtr );

    private:

        HANDLE              _file;
        const size_t        _operationCount;
        FileIoOperation**   _operations;
        HANDLE              _thread;
        bool                _running;
};



FileIoThread::FileIoThread(
    HANDLE file ) :

    _file( file ),
    _operationCount( 128 ),
    _operations( new FileIoOperation*[_operationCount] ),
    _thread( 0 ),
    _running( false )
{
    memset( _operations, 0, sizeof(FileIoOperation*)*_operationCount );

    DWORD  thread_id = 0;
    _thread = CreateThread(
                    NULL,                       // no security attributes
                    0,                          // use default stack size
                    FileIoThread::ThreadProc,   // thread function
                    this,                       // argument to thread function
                    CREATE_SUSPENDED,           // use default creation flags
                    &thread_id );               // returns the thread identifier

    assert( _thread != NULL );
}



FileIoThread::~FileIoThread()
{
    if( _running )
    {
        Finish();
    }

    for( size_t i=0; i<_operationCount; i++ )
    {
        delete _operations[i];
        _operations[i] = 0;
    }

    delete[] _operations;
    _operations = 0;

    CloseHandle( _thread );
    _thread = 0;
}



void FileIoThread::Start()
{
    assert( !_running );

    DWORD  result = ResumeThread( _thread );
    assert( result != 0xFFFFFFFF );
    _running = true;
}



void FileIoThread::Finish()
{
    assert( _running );

    // Wait for all to complete?
    // ...

    BOOL  succeeded = TerminateThread( _thread, 0 );
    assert( succeeded );
    _running = false;
}



BOOL FileIoThread::Read(
    aafUInt64 position,
    aafMemPtr_t pBuffer,
    aafUInt32 bufferSize,
    IAAFIOCompletion* pCompletion,
    aafMemConstPtr_t pClientData )
{
    BOOL  succeeded = FALSE;


    int  i = UnusedOperationIndex();
    if( i >= 0 )
    {
        _operations[i] = new FileIoOperation( position,
                                              pCompletion,
                                              pClientData );
        succeeded = ReadFile( _file,
                              pBuffer,
                              bufferSize,
                              0,
                              _operations[i]->Overlapped() );

        if( !succeeded )
        {
            const DWORD  e = GetLastError();
            if( e == ERROR_IO_PENDING )
            {
                succeeded = TRUE;
            }
            else
            {
                _operations[i]->Completion()->Completed( e, 0, _operations[i]->ClientData() );
                delete (_operations[i]);
                _operations[i] = 0;
            }
        }
    }


    return succeeded;
}



BOOL FileIoThread::Write(
    aafUInt64 position,
    aafMemConstPtr_t pBuffer,
    aafUInt32 bufferSize,
    IAAFIOCompletion* pCompletion,
    aafMemConstPtr_t pClientData )
{
    BOOL  succeeded = FALSE;


    int  i = UnusedOperationIndex();
    if( i >= 0 )
    {
        _operations[i] = new FileIoOperation( position,
                                              pCompletion,
                                              pClientData );
        succeeded = WriteFile( _file,
                               pBuffer,
                               bufferSize,
                               0,
                               _operations[i]->Overlapped() );

        if( !succeeded )
        {
            const DWORD  e = GetLastError();
            if( e == ERROR_IO_PENDING )
            {
                succeeded = TRUE;
            }
            else
            {
                _operations[i]->Completion()->Completed( e, 0, _operations[i]->ClientData() );
                delete (_operations[i]);
                _operations[i] = 0;
            }
        }
    }


    return succeeded;
}



int FileIoThread::UnusedOperationIndex() const
{
    int  result = -1;
    for( size_t i=0; i<_operationCount; i++ )
    {
        if( _operations[i] == 0 )
        {
            result = i;
            break;
        }
    }


    return result;
}



/*static */ DWORD WINAPI FileIoThread::ThreadProc(
    void *threadPtr )
{
    FileIoThread*  ioThread = reinterpret_cast<FileIoThread*>(threadPtr);
    assert( ioThread != 0 );


    while( true )
    {
        for( size_t i=0; i<ioThread->_operationCount; i++ )
        {
            if( ioThread->_operations[i] )
            {
                DWORD bytesWritten = 0;
                BOOL succeeded =
                    GetOverlappedResult(
                        ioThread->_file,
                        ioThread->_operations[i]->Overlapped(),
                        &bytesWritten,
                        FALSE );
                if( succeeded )
                {
                    ioThread->_operations[i]->Completion()->Completed( S_OK,
                        bytesWritten, ioThread->_operations[i]->ClientData() );
                    delete (ioThread->_operations[i]);
                    ioThread->_operations[i] = 0;
                }
                else
                {
                    const DWORD  e = GetLastError();
                    if( e != ERROR_IO_INCOMPLETE )
                    {
                        ioThread->_operations[i]->Completion()->Completed(
                            e, 0, ioThread->_operations[i]->ClientData() );
                        delete (ioThread->_operations[i]);
                        ioThread->_operations[i] = 0;
                    }
                }
            }
        }

        SleepEx( 10, TRUE );
    }
}



//----------------------------------------------------------------------------
//
//
//----------------------------------------------------------------------------
class Win32AsyncStreamRawStorage : public CustomAsyncStreamRawStorage
{
    public:

        // Create an instance of Win32AsyncStreamRawStorage
        static Win32AsyncStreamRawStorage* Create( const aafWChar* pFileName,
                                                   const aafFileExistence_t,
                                                   const aafFileAccess_t );


        // IAAFRawStorage overrides
        virtual HRESULT STDMETHODCALLTYPE
                Read( aafMemPtr_t   pBuffer,
                      aafUInt32     bufferSize,
                      aafUInt32*    pBytesRead );

        virtual HRESULT STDMETHODCALLTYPE
                Write( aafMemConstPtr_t pBuffer,
                       aafUInt32        bufferSize,
                       aafUInt32*       pBytesWritten );

        virtual HRESULT STDMETHODCALLTYPE
                Synchronize();


        // IAAFRandomRawStorage overrides
        virtual HRESULT STDMETHODCALLTYPE
                GetSize( aafUInt64* pSize );


#ifdef USE_ASYNC_IO
        // IAAFAsyncStreamRawStorage overrides
        virtual HRESULT STDMETHODCALLTYPE
                StreamReadAsyncAt( aafUInt64        position,
                                   aafMemPtr_t      pBuffer,
                                   aafUInt32        bufferSize,
                                   IAAFIOCompletion* pCompletion,
                                   aafMemConstPtr_t pClientData );

        virtual HRESULT STDMETHODCALLTYPE
                StreamWriteAsyncAt( aafUInt64          position,
                                    aafMemConstPtr_t   pBuffer,
                                    aafUInt32          bufferSize,
                                    IAAFIOCompletion*  pCompletion,
                                    aafMemConstPtr_t   pClientData );
#endif


    protected:

        Win32AsyncStreamRawStorage( HANDLE f,
                                    const aafFileAccess_t access );
        virtual ~Win32AsyncStreamRawStorage();

        virtual aafBoolean_t    SetPosition( aafUInt64 position );


    private:

        BOOL GetPosition( LARGE_INTEGER* position ) const;


    private:

        HANDLE                  _file;
        FileIoThread*           _ioThread;
};



/*static*/ Win32AsyncStreamRawStorage* Win32AsyncStreamRawStorage::Create(
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


    DWORD  fileCreationDisposition;
    if( existence == kAAFFileExistence_new )
    {
        fileCreationDisposition = CREATE_NEW;
    }
    else if( existence == kAAFFileExistence_existing )
    {
        fileCreationDisposition = OPEN_EXISTING;
    }
    else
    {
        assert( false );  // Unreachable code
    }


    DWORD  fileAccessMode;
    if( access == kAAFFileAccess_read )
    {
        fileAccessMode = GENERIC_READ;
    }
    else if( access == kAAFFileAccess_write )
    {
        fileAccessMode = GENERIC_WRITE;
    }
    else if( access == kAAFFileAccess_modify )
    {
        fileAccessMode = GENERIC_READ | GENERIC_WRITE;
    }
    else
    {
        assert( false );  // Unreachable code
    }


    const DWORD  fileShareMode = FILE_SHARE_READ;


    DWORD  fileAttributes = FILE_ATTRIBUTE_NORMAL;
#ifdef USE_ASYNC_IO
    fileAttributes |= FILE_FLAG_OVERLAPPED;
#endif


    HANDLE  h_file = CreateFile( pFileName,
                                 fileAccessMode,
                                 fileShareMode,
                                 0, // no security attributes
                                 fileCreationDisposition,
                                 fileAttributes,
                                 0 ); // no template file
    assert( h_file != INVALID_HANDLE_VALUE );


    Win32AsyncStreamRawStorage*  p_storage =
        new Win32AsyncStreamRawStorage( h_file, access );
    assert( p_storage );
    p_storage->AddRef();


    return p_storage;
}



HRESULT STDMETHODCALLTYPE Win32AsyncStreamRawStorage::Read(
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


    HRESULT  hr = AAFRESULT_SUCCESS;


    // Get the current position
    LARGE_INTEGER  position = {0};
    BOOL  succeeded = GetPosition( &position );
    if( succeeded )
    {
        // The OVERLAPPED struct
        OVERLAPPED* overlapped = new OVERLAPPED;
        memset( overlapped, 0, sizeof(OVERLAPPED) );
        overlapped->Offset = position.LowPart;
        overlapped->OffsetHigh = position.HighPart;
        overlapped->hEvent = CreateEvent( 0, FALSE, FALSE, 0 );

        // Read the file
        succeeded = ReadFile( _file,
                              pBuffer,
                              bufferSize,
                              pBytesRead,
                              overlapped );
        if( !succeeded )
        {
            if( GetLastError() == ERROR_IO_PENDING )
            {
                // Wait for completion
                succeeded = GetOverlappedResult( _file,
                                                 overlapped,
                                                 pBytesRead,
                                                 TRUE );
            }
        }

        CloseHandle( overlapped->hEvent );
        delete overlapped;
        overlapped = 0;
    }


    if( succeeded )
    {
        hr = AAFRESULT_SUCCESS;
    }
    else
    {
        hr = AAFRESULT_READ_FAILURE;
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE Win32AsyncStreamRawStorage::Write(
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


    HRESULT  hr = AAFRESULT_SUCCESS;


    // Get the current position
    LARGE_INTEGER  position = {0};
    BOOL  succeeded = GetPosition( &position );
    if( succeeded )
    {
        // The OVERLAPPED struct
        OVERLAPPED* overlapped = new OVERLAPPED;
        memset( overlapped, 0, sizeof(OVERLAPPED) );
        overlapped->Offset = position.LowPart;
        overlapped->OffsetHigh = position.HighPart;
        overlapped->hEvent = CreateEvent( 0, FALSE, FALSE, 0 );

        // Write the file
        succeeded = WriteFile( _file,
                               pBuffer,
                               bufferSize,
                               pBytesWritten,
                               overlapped );
        if( !succeeded )
        {
            if( GetLastError() == ERROR_IO_PENDING )
            {
                // Wait for completion
                succeeded = GetOverlappedResult( _file,
                                                 overlapped,
                                                 pBytesWritten,
                                                 TRUE );
            }
        }

        CloseHandle( overlapped->hEvent );
        delete overlapped;
        overlapped = 0;
    }


    if( succeeded )
    {
        hr = AAFRESULT_SUCCESS;
    }
    else
    {
        hr = AAFRESULT_WRITE_FAILURE;
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE Win32AsyncStreamRawStorage::Synchronize()
{
    AAFRESULT  hr = AAFRESULT_SUCCESS;


    return hr;
}



HRESULT STDMETHODCALLTYPE Win32AsyncStreamRawStorage::GetSize(
    aafUInt64* pSize )
{
    if( !pSize )
    {
        return AAFRESULT_NULL_PARAM;
    }


    AAFRESULT  hr = AAFRESULT_SUCCESS;


    DWORD  size_high = 0;
    const DWORD  size_low = GetFileSize( _file,
                                         &size_high );
    if( size_low == 0xFFFFFFFF )
    {
        if( ::GetLastError() != NO_ERROR )
        {
            hr = AAFRESULT_GETSIZE_FAILURE;
        }
    }

    if( hr == AAFRESULT_SUCCESS )
    {
        *pSize = ((aafUInt64)size_high << 32) | (aafUInt64)size_low;
    }


    return hr;
}



#ifdef USE_ASYNC_IO
HRESULT STDMETHODCALLTYPE Win32AsyncStreamRawStorage::StreamReadAsyncAt(
    aafUInt64 position,
    aafMemPtr_t pBuffer,
    aafUInt32 bufferSize,
    IAAFIOCompletion* pCompletion,
    aafMemConstPtr_t pClientData )
{
    HRESULT hr = AAFRESULT_SUCCESS;


    BOOL  succeeded = _ioThread->Read( position,
                                       pBuffer,
                                       bufferSize,
                                       pCompletion,
                                       pClientData );

    if( succeeded )
    {
        hr = AAFRESULT_SUCCESS;
        //_streamBytesRead += bufferSize;
    }
    else
    {
        DWORD e = GetLastError();
        hr = AAFRESULT_READ_FAILURE;
    }


    return hr;
}



HRESULT STDMETHODCALLTYPE Win32AsyncStreamRawStorage::StreamWriteAsyncAt(
    aafUInt64 position,
    aafMemConstPtr_t pBuffer,
    aafUInt32 bufferSize,
    IAAFIOCompletion* pCompletion,
    aafMemConstPtr_t pClientData )
{
    HRESULT hr = AAFRESULT_SUCCESS;


    BOOL  succeeded = _ioThread->Write( position,
                                        pBuffer,
                                        bufferSize,
                                        pCompletion,
                                        pClientData );

    if( succeeded )
    {
        hr = AAFRESULT_SUCCESS;
        //_streamBytesWritten += bufferSize;
    }
    else
    {
        DWORD e = GetLastError();
        hr = AAFRESULT_WRITE_FAILURE;
    }


    return hr;
}
#endif  // USE_ASYNC_IO



Win32AsyncStreamRawStorage::Win32AsyncStreamRawStorage(
    HANDLE h_file,
    const aafFileAccess_t access ) :

    CustomAsyncStreamRawStorage( access ),
    _file( h_file ),
    _ioThread( new FileIoThread(h_file) )
{
    assert( h_file );
    _ioThread->Start();
}



Win32AsyncStreamRawStorage::~Win32AsyncStreamRawStorage()
{
    _ioThread->Finish();
    delete _ioThread;
    _ioThread = 0;

    CloseHandle( _file );
    _file = 0;
}



aafBoolean_t Win32AsyncStreamRawStorage::SetPosition(
    aafUInt64 position )
{
    aafBoolean_t  succeeded = kAAFTrue;


    const LONG  position_low = (LONG)(position & 0x00000000FFFFFFFF);
    const LONG  position_high = (LONG)((position & 0xFFFFFFFF00000000) >> 32);

    LONG  new_position_low = position_low ;
    LONG  new_position_high = position_high;
    new_position_low = SetFilePointer( _file,
                                       new_position_low,
                                       &new_position_high,
                                       FILE_BEGIN );

    if( new_position_low == 0xFFFFFFFF )
    {
        if( GetLastError() != NO_ERROR )
        {
            succeeded = kAAFFalse;
        }
    }


    return succeeded;
}



BOOL Win32AsyncStreamRawStorage::GetPosition(
    LARGE_INTEGER* pPosition ) const
{
    assert( pPosition );


    BOOL  succeeded = TRUE;


    LONG  new_position_low = 0;
    LONG  new_position_high = 0;
    new_position_low = SetFilePointer( _file,
                                       new_position_low,
                                       &new_position_high,
                                       FILE_CURRENT );

    if( new_position_low == 0xFFFFFFFF )
    {
        if( GetLastError() != NO_ERROR )
        {
            succeeded = FALSE;
        }
    }

    if( succeeded )
    {
        pPosition->LowPart = new_position_low;
        pPosition->HighPart = new_position_high;
    }


    return succeeded;
}


#endif  // USE_WIN32_IO



static CustomAsyncStreamRawStorage* CreateCustomAsyncStreamRawStorageInstance(
    const aafWChar* pFileName,
    const aafFileExistence_t existence,
    const aafFileAccess_t access )
{
#ifdef USE_WIN32_IO
    CustomAsyncStreamRawStorage*  pStorage =
        Win32AsyncStreamRawStorage::Create( pFileName,
                                            existence,
                                            access );
#else
    CustomAsyncStreamRawStorage*  pStorage =
        StdioAsyncStreamRawStorage::Create( pFileName,
                                            existence,
                                            access );
#endif

    return pStorage;
}



class CustomIOCompletion : public IAAFIOCompletion
{
    public:

        // Create an instance of CustomIOCompletion
        static CustomIOCompletion* Create();

        // Check the operation status
        bool IsCompleted() const;
        HRESULT  Status() const;
        aafUInt32  BytesTransferred() const;

        // IUnknown overrides
        virtual HRESULT STDMETHODCALLTYPE
            QueryInterface( REFIID iid,
                            void** ppIfc );
        virtual aafUInt32 STDMETHODCALLTYPE AddRef();
        virtual aafUInt32 STDMETHODCALLTYPE Release();


        // IAAFIOCompletion overrides
        virtual HRESULT STDMETHODCALLTYPE
            Completed( HRESULT completionStatus,
                       aafUInt32 numTransferred,
                       aafMemConstPtr_t pClientData );

    protected:

        CustomIOCompletion();
        virtual ~CustomIOCompletion();

    protected:

        aafUInt32               _refCount;
        bool                    _completed;
        HRESULT                 _status;
        aafUInt32               _bytesTransferred;
};



/*static*/ CustomIOCompletion* CustomIOCompletion::Create()
{
    CustomIOCompletion*  pCompletion = new CustomIOCompletion();
    assert( pCompletion );
    pCompletion->AddRef();


    return pCompletion;
}



bool CustomIOCompletion::IsCompleted() const
{
    return _completed;
}



HRESULT CustomIOCompletion::Status() const
{
    assert( IsCompleted() );
    return _status;
}



aafUInt32 CustomIOCompletion::BytesTransferred() const
{
    assert( IsCompleted() );
    return _bytesTransferred;
}



HRESULT STDMETHODCALLTYPE CustomIOCompletion::QueryInterface(
    REFIID iid,
    void** ppIfc )
{
    if( !ppIfc )
    {
        return AAFRESULT_NULL_PARAM;
    }

    if( memcmp( &iid, &IID_IUnknown, sizeof(iid) ) == 0 )
    {
        IUnknown* runk = (IUnknown*)this;
        *ppIfc = (void*)runk;
        AddRef();
        return AAFRESULT_SUCCESS;
    }
    else if( memcmp( &iid, &IID_IAAFIOCompletion, sizeof(iid) ) == 0 )
    {
        IAAFIOCompletion* rioc = this;
        *ppIfc = (void*) rioc;
        AddRef();
        return AAFRESULT_SUCCESS;
    }
    else
    {
        return E_NOINTERFACE;
    }
}



aafUInt32 STDMETHODCALLTYPE CustomIOCompletion::AddRef()
{
    _refCount++;
    return _refCount;
}



aafUInt32 STDMETHODCALLTYPE CustomIOCompletion::Release()
{
    const aafUInt32  r = --_refCount;
    if( r == 0 )
    {
        delete this;
    }

    return r;
}



HRESULT CustomIOCompletion::Completed(
    HRESULT completionStatus,
    aafUInt32 numTransferred,
    aafMemConstPtr_t /* pClientData */)
{
    assert( !IsCompleted() );

    _completed = true;
    _status = completionStatus;
    _bytesTransferred = numTransferred;

    return AAFRESULT_SUCCESS;
}



CustomIOCompletion::CustomIOCompletion() :
    _refCount( 0 ),
    _completed( false ),
    _status( AAFRESULT_SUCCESS ),
    _bytesTransferred( 0 )
{
}



CustomIOCompletion::~CustomIOCompletion()
{
}



//----------------------------------------------------------------------------
//
//
//----------------------------------------------------------------------------
class AlignedBuffer
{
    public:

        AlignedBuffer( const size_t size, const size_t alignment );
        ~AlignedBuffer();

        template <typename T> operator T()
        {
            return reinterpret_cast<T>(_aligned_buffer);
        }


    private:

        char*         _allocated_buffer;
        char*         _aligned_buffer;
};



AlignedBuffer::AlignedBuffer(
    const size_t size,
    const size_t alignment ) :

    _allocated_buffer( 0 ),
    _aligned_buffer( 0 )
{
    _allocated_buffer = new char[ size + alignment ];
    _aligned_buffer = _allocated_buffer +
                      (alignment - (size_t(_allocated_buffer) % alignment));

    assert( _aligned_buffer >= _allocated_buffer  &&
            (_aligned_buffer + size) <=
                (_allocated_buffer + size + alignment) );
}



AlignedBuffer::~AlignedBuffer()
{
    delete[] _allocated_buffer;
    _allocated_buffer = 0;
    _aligned_buffer = 0;
}



static HRESULT CreateAAFFile(
    aafWChar * pFileName,
    aafUID_constref fileKind,
    testRawStorageType_t /* rawStorageType */,
    aafProductIdentification_constref productID)
{
    HRESULT  hr = AAFRESULT_SUCCESS;
    IAAFRawStorage*  pStorage = 0;
    IAAFFile*  pFile = 0;
    IAAFHeader*  pHeader = 0;
    IAAFEssenceData*  pEssenceData = 0;



    try
    {
        // Remove the previous test file if any.
        ::RemoveTestFile( pFileName );

        // Determine the file encoding to be used.
        aafUID_t effectiveFileKind = EffectiveTestFileEncoding( fileKind );

        // Create raw storage
        const aafFileExistence_t existence = kAAFFileExistence_new;
        const aafFileAccess_t access = kAAFFileAccess_modify;
        pStorage = CreateCustomAsyncStreamRawStorageInstance( pFileName,
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


        CheckResult( CreateEssenceData( pHeader,
                                        testMobIDs[0],
                                        testMobNames[0],
                                        &pEssenceData ) );
        CheckResult( Test_IAAFAsyncStreamRawStorage_WriteAsyncAt(
                        pEssenceData, kAAFUnitTestReadWrite ) );

        pEssenceData->Release();
        pEssenceData = 0;


        CheckResult( CreateEssenceData( pHeader,
                                        testMobIDs[1],
                                        testMobNames[1],
                                        &pEssenceData ) );
        CheckResult( Test_IAAFAsyncStreamRawStorage_ReadAsyncAt(
                        pEssenceData, kAAFUnitTestReadWrite ) );

        pEssenceData->Release();
        pEssenceData = 0;


        CheckResult( CreateEssenceData( pHeader,
                                        testMobIDs[2],
                                        testMobNames[2],
                                        &pEssenceData ) );
        CheckResult( Test_IAAFAsyncStreamRawStorage_WriteGatherAsyncAt(
                        pEssenceData, kAAFUnitTestReadWrite ) );

        pEssenceData->Release();
        pEssenceData = 0;


        CheckResult( CreateEssenceData( pHeader,
                                        testMobIDs[3],
                                        testMobNames[3],
                                        &pEssenceData ) );
        CheckResult( Test_IAAFAsyncStreamRawStorage_ReadScatterAsyncAt(
                        pEssenceData, kAAFUnitTestReadWrite ) );

        pEssenceData->Release();
        pEssenceData = 0;


        // Save the file
        CheckResult( pFile->Save() );
    }
    catch (HRESULT& rResult)
    {
        hr = rResult;
    }


    if( pEssenceData )
    {
        pEssenceData->Release();
        pEssenceData = 0;
    }
    if( pHeader )
    {
        pHeader->Release();
        pHeader = 0;
    }
    if( pFile )
    {
        pFile->Close();
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
    HRESULT  hr = AAFRESULT_SUCCESS;
    IAAFRawStorage*  pStorage = 0;
    IAAFFile*  pFile = 0;
    IAAFHeader*  pHeader = 0;
    IAAFEssenceData*  pEssenceData = 0;


    try
    {
        // Create raw storage
        const aafFileExistence_t existence = kAAFFileExistence_existing;
        const aafFileAccess_t access = kAAFFileAccess_read;
        pStorage = CreateCustomAsyncStreamRawStorageInstance( pFileName,
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


        CheckResult( pHeader->LookupEssenceData( testMobIDs[0], &pEssenceData ) );
        CheckResult( Test_IAAFAsyncStreamRawStorage_WriteAsyncAt(
                        pEssenceData, kAAFUnitTestReadOnly ) );

        pEssenceData->Release();
        pEssenceData = 0;


        CheckResult( pHeader->LookupEssenceData( testMobIDs[1], &pEssenceData ) );
        CheckResult( Test_IAAFAsyncStreamRawStorage_ReadAsyncAt(
                        pEssenceData, kAAFUnitTestReadOnly ) );

        pEssenceData->Release();
        pEssenceData = 0;


        CheckResult( pHeader->LookupEssenceData( testMobIDs[2], &pEssenceData ) );
        CheckResult( Test_IAAFAsyncStreamRawStorage_WriteGatherAsyncAt(
                        pEssenceData, kAAFUnitTestReadOnly ) );

        pEssenceData->Release();
        pEssenceData = 0;


        CheckResult( pHeader->LookupEssenceData( testMobIDs[3], &pEssenceData ) );
        CheckResult( Test_IAAFAsyncStreamRawStorage_ReadScatterAsyncAt(
                        pEssenceData, kAAFUnitTestReadOnly ) );

        pEssenceData->Release();
        pEssenceData = 0;

    }
    catch (HRESULT& rResult)
    {
        hr = rResult;
    }


    if( pEssenceData )
    {
        pEssenceData->Release();
        pEssenceData = 0;
    }
    if( pHeader )
    {
        pHeader->Release();
        pHeader = 0;
    }
    if( pFile )
    {
        pFile->Close();
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



static HRESULT Test_IAAFAsyncStreamRawStorage_WriteAsyncAt(
    IAAFEssenceData* pEssenceData,
    testMode_t mode )
{
    HRESULT  hr = S_OK;
    IAAFPropertyValue*  pPropValue = 0;
    IAAFTypeDefStream2*  pTypeDefStream = 0;


    // The test data
    const size_t  dataBufferCount = 4;
    const size_t  dataBufferSize = 64;
    const size_t  dataSize = dataBufferSize * dataBufferCount;
    char* data = new char[ dataSize ];
    memset( data, 0xAD, dataSize );
    char* p = data;
    for( size_t i=0; i<dataBufferCount; i++ )
    {
        // "WriteAsyncAt-00"
        // "WriteAsyncAt-01"
        // ...
        sprintf( p, "WriteAsyncAt-%02d", i );
        p += dataBufferSize;
    }


    try
    {
        // Get the stream property
        CheckResult( GetEssenceDataTypeAndValue( pEssenceData,
                                                 &pTypeDefStream,
                                                 &pPropValue ) );

        if( mode == kAAFUnitTestReadWrite )
        {
            // The current offset
            aafUInt64 offset = 0;

            // Initiate write operations for the test data,
            // one for each dataBufferSize-byte piece.
            CustomIOCompletion* completion[ dataBufferCount ];
            size_t i;
            for( i=0; i<dataBufferCount; i++ )
            {
                completion[i] = CustomIOCompletion::Create();
                CheckResult( pTypeDefStream->WriteAsyncAt( pPropValue,
                                                           offset,
                                                           dataBufferSize,
                                                           (aafMemConstPtr_t)(data + i*dataBufferSize),
                                                           completion[i],
                                                           0 ) );
                offset += dataBufferSize;
            }

            // Wait for all operations to complete
            while( !AllCompleted( completion, dataBufferCount ) )
            {
                Wait( 10 );
            }

            // Check the completion status
            for( i=0; i<dataBufferCount; i++ )
            {
                CheckExpression( completion[i]->IsCompleted() );
                CheckExpression( completion[i]->Status() == AAFRESULT_SUCCESS );
                CheckExpression( completion[i]->BytesTransferred() == dataBufferSize );
                completion[i]->Release();
                completion[i] = 0;
            }
        }


        if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
        {
            CheckResult( pEssenceData->SetPosition( 0 ) );


             // The current offset
            aafInt64 offset = 0;


            // Streams in KLV-encoded files start with a key and BER encoded length.
            // Skip key and length if present.
            if( true )
            {
#ifdef TEST_NEW_STREAM_WRITING
                CheckResult(SkipKL(pPropValue));
#else
                if( IsKLVStream(pPropValue) )
                    CheckResult(SkipKL(pPropValue));
#endif
            }
            CheckResult(pEssenceData->GetPosition( &offset ) );


            CheckResult( pEssenceData->SetPosition( offset ) );

            unsigned char buffer[ dataSize ];
            memset( buffer, 0, dataSize );
            aafUInt32  bytesRead = 0;
            CheckResult( pEssenceData->Read( dataSize, buffer, &bytesRead ) );
            CheckExpression( bytesRead == dataSize );
            CheckExpression( memcmp( buffer, data, dataSize ) == 0 );


            offset += bytesRead;
        }


    }
    catch( HRESULT e )
    {
        hr = e;
    }


    if( pTypeDefStream )
    {
        pTypeDefStream->Release();
        pTypeDefStream = 0;
    }
    if( pPropValue )
    {
        pPropValue->Release();
        pPropValue = 0;
    }


    return hr;
}



static HRESULT Test_IAAFAsyncStreamRawStorage_ReadAsyncAt(
    IAAFEssenceData* pEssenceData,
    testMode_t mode )
{
    HRESULT  hr = S_OK;
    IAAFPropertyValue*  pPropValue = 0;
    IAAFTypeDefStream2*  pTypeDefStream = 0;


    // The test data
    const size_t  dataBufferCount = 4;
    const size_t  dataBufferSize = 64;
    const size_t  dataSize = dataBufferSize * dataBufferCount;
    char* data = new char[ dataSize ];
    memset( data, 0xAD, dataSize );
    char* p = data;
    for( size_t i=0; i<dataBufferCount; i++ )
    {
        // "ReadAsyncAt-00"
        // "ReadAsyncAt-01"
        // ...
        sprintf( p, "ReadAsyncAt-%02d", i );
        p += dataBufferSize;
    }


    try
    {
        // Get the stream property
        CheckResult( GetEssenceDataTypeAndValue( pEssenceData,
                                                 &pTypeDefStream,
                                                 &pPropValue ) );


        if( mode == kAAFUnitTestReadWrite )
        {
            // The current offset
            aafUInt64 offset = 0;


            CheckResult( pEssenceData->SetPosition( offset ) );

            aafUInt32  bytesWritten = 0;
            CheckResult( pEssenceData->Write( dataSize,
                                              reinterpret_cast<aafDataBuffer_t>(data),
                                              &bytesWritten ) );
            CheckExpression( bytesWritten == dataSize );


            offset += bytesWritten;
        }


        if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
        {
            CheckResult( pTypeDefStream->SetPosition( pPropValue, 0 ) );


            // The current offset
            aafInt64 offset = 0;


            // Streams in KLV-encoded files start with a key and BER encoded length.
            // Skip key and length if present.
            if( true )
            {
#ifdef TEST_NEW_STREAM_WRITING
                CheckResult(SkipKL(pPropValue));
#else
                if( IsKLVStream(pPropValue) )
                    CheckResult(SkipKL(pPropValue));
#endif
            }
            CheckResult(pTypeDefStream->GetPosition( pPropValue,
                                                     &offset ) );


            // Initiate read operations for the test data,
            // one for each dataBufferSize-byte piece.
            unsigned char buffer[ dataSize ];
            memset( buffer, 0, dataSize );
            CustomIOCompletion* completion[ dataBufferCount ];
            size_t i;
            for( i=0; i<dataBufferCount; i++ )
            {
                completion[i] = CustomIOCompletion::Create();
                CheckResult( pTypeDefStream->ReadAsyncAt( pPropValue,
                                                          offset,
                                                          dataBufferSize,
                                                          (aafMemPtr_t)(buffer + i*dataBufferSize),
                                                          completion[i],
                                                          0 ) );
                offset += dataBufferSize;
            }

            // Wait for all operations to complete
            while( !AllCompleted( completion, dataBufferCount ) )
            {
                Wait( 10 );
            }

            // Check the completion status
            for( i=0; i<dataBufferCount; i++ )
            {
                CheckExpression( completion[i]->IsCompleted() );
                CheckExpression( completion[i]->Status() == AAFRESULT_SUCCESS );
                CheckExpression( completion[i]->BytesTransferred() == dataBufferSize );
                completion[i]->Release();
                completion[i] = 0;
            }

            // Check the read data
            CheckExpression( memcmp( buffer, data, dataSize ) == 0 );
        }


    }
    catch( HRESULT e )
    {
        hr = e;
    }


    if( pTypeDefStream )
    {
        pTypeDefStream->Release();
        pTypeDefStream = 0;
    }
    if( pPropValue )
    {
        pPropValue->Release();
        pPropValue = 0;
    }


    return hr;
}



static HRESULT Test_IAAFAsyncStreamRawStorage_WriteGatherAsyncAt(
    IAAFEssenceData* pEssenceData,
    testMode_t mode )
{
    HRESULT  hr = S_OK;
    IAAFPropertyValue*  pPropValue = 0;
    IAAFTypeDefStream2*  pTypeDefStream = 0;


    // The test data
    const unsigned char data[] = "WriteGatherAsyncAt-00";
    const size_t dataSize = sizeof(data);
    const size_t scatteredBuffersCount = 3;
    const size_t scatteredBufferSize = dataSize;
    aafIOBufferDesc_t scatteredData[ scatteredBuffersCount ] =
    {
        {
            (aafMemPtr_t)data,
            scatteredBufferSize
        },
        {
            (aafMemPtr_t)data,
            scatteredBufferSize
        },
        {
            (aafMemPtr_t)data,
            scatteredBufferSize
        }
    };
    const size_t scatteredDataSize = scatteredBufferSize * scatteredBuffersCount;


    try
    {
        // Get the stream property
        CheckResult( GetEssenceDataTypeAndValue( pEssenceData,
                                                 &pTypeDefStream,
                                                 &pPropValue ) );


        if( mode == kAAFUnitTestReadWrite )
        {
            // The current offset
            aafUInt64 offset = 0;
    

            CustomIOCompletion* pCompletion01 = CustomIOCompletion::Create();
            CheckResult( pTypeDefStream->WriteGatherAsyncAt( pPropValue,
                                                             offset,
                                                             scatteredBuffersCount,
                                                             scatteredData,
                                                             pCompletion01,
                                                             0 ) );

            // Wait for completion
            while( !pCompletion01->IsCompleted() )
            {
            }

            CheckExpression( pCompletion01->IsCompleted() );
            CheckExpression( pCompletion01->Status() == AAFRESULT_SUCCESS );
            CheckExpression( pCompletion01->BytesTransferred() == scatteredDataSize );

            offset += pCompletion01->BytesTransferred();

            pCompletion01->Release();
            pCompletion01 = 0;
        }


        if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
        {
            CheckResult( pEssenceData->SetPosition( 0 ) );


             // The current offset
            aafInt64 offset = 0;


            // Streams in KLV-encoded files start with a key and BER encoded length.
            // Skip key and length if present.
            if( true )
            {
#ifdef TEST_NEW_STREAM_WRITING
                CheckResult(SkipKL(pPropValue));
#else
                if( IsKLVStream(pPropValue) )
                    CheckResult(SkipKL(pPropValue));
#endif
            }
            CheckResult(pEssenceData->GetPosition( &offset ) );


            for( size_t i=0; i<scatteredBuffersCount; i++ )
            {
                CheckResult( pEssenceData->SetPosition( offset ) );

                unsigned char* buffer =
                    new unsigned char[ scatteredData[i].bufSize ];
                memset( buffer, 0, scatteredData[i].bufSize );
                aafUInt32  bytesRead = 0;
                CheckResult( pEssenceData->Read( scatteredData[i].bufSize,
                                                 buffer,
                                                 &bytesRead ) );
                CheckExpression( bytesRead == scatteredData[i].bufSize );
                CheckExpression( memcmp( buffer,
                                         scatteredData[i].buf,
                                         scatteredData[i].bufSize ) == 0 );

                offset += bytesRead;

                delete[] buffer;
                buffer = 0;
            }
        }


    }
    catch( HRESULT e )
    {
        hr = e;
    }


    if( pTypeDefStream )
    {
        pTypeDefStream->Release();
        pTypeDefStream = 0;
    }
    if( pPropValue )
    {
        pPropValue->Release();
        pPropValue = 0;
    }


    return hr;
}



static HRESULT Test_IAAFAsyncStreamRawStorage_ReadScatterAsyncAt(
    IAAFEssenceData* pEssenceData,
    testMode_t mode )
{
    HRESULT  hr = S_OK;
    IAAFPropertyValue*  pPropValue = 0;
    IAAFTypeDefStream2*  pTypeDefStream = 0;


    // The test data
    const unsigned char data[] = "ReadScatterAsyncAt-00";
    const size_t dataSize = sizeof(data);
    const size_t scatteredBuffersCount = 3;
    const size_t scatteredBufferSize = dataSize;
    aafIOBufferDesc_t scatteredData[ scatteredBuffersCount ] =
    {
        {
            (aafMemPtr_t)data,
            scatteredBufferSize
        },
        {
            (aafMemPtr_t)data,
            scatteredBufferSize
        },
        {
            (aafMemPtr_t)data,
            scatteredBufferSize
        }
    };
    const size_t scatteredDataSize = scatteredBufferSize * scatteredBuffersCount;


    try
    {
        // Get the stream property
        CheckResult( GetEssenceDataTypeAndValue( pEssenceData,
                                                 &pTypeDefStream,
                                                 &pPropValue ) );


        if( mode == kAAFUnitTestReadWrite )
        {
             // The current offset
            aafUInt64 offset = 0;


            for( size_t i=0; i<scatteredBuffersCount; i++ )
            {
                CheckResult( pEssenceData->SetPosition( offset ) );

                aafUInt32  bytesWritten = 0;
                CheckResult( pEssenceData->Write( scatteredData[i].bufSize,
                                                  scatteredData[i].buf,
                                                  &bytesWritten ) );
                CheckExpression( bytesWritten == scatteredData[i].bufSize );

                offset += bytesWritten;
            }
        }


        if( mode == kAAFUnitTestReadWrite || mode == kAAFUnitTestReadOnly )
        {
            CheckResult( pTypeDefStream->SetPosition( pPropValue, 0 ) );


            // The current offset
            aafInt64 offset = 0;


            // Streams in KLV-encoded files start with a key and BER encoded length.
            // Skip key and length if present.
            if( true )
            {
#ifdef TEST_NEW_STREAM_WRITING
                CheckResult(SkipKL(pPropValue));
#else
                if( IsKLVStream(pPropValue) )
                    CheckResult(SkipKL(pPropValue));
#endif
            }
            CheckResult(pTypeDefStream->GetPosition( pPropValue,
                                                     &offset ) );


            CustomIOCompletion* pCompletion01 = CustomIOCompletion::Create();
            aafIOBufferDesc_t*  scatteredBuffers =
                AllocateScatteredBuffers( scatteredData, scatteredBuffersCount );
            CheckResult( pTypeDefStream->ReadScatterAsyncAt( pPropValue,
                                                             offset,
                                                             scatteredBuffersCount,
                                                             scatteredBuffers,
                                                             pCompletion01,
                                                             0 ) );

            // Wait for completion
            while( !pCompletion01->IsCompleted() )
            {
            }

            CheckExpression( pCompletion01->IsCompleted() );
            CheckExpression( pCompletion01->Status() == AAFRESULT_SUCCESS );
            CheckExpression( pCompletion01->BytesTransferred() == scatteredDataSize );
            CheckExpression( CompareScatteredBuffers( scatteredBuffers,
                                                      scatteredData,
                                                      scatteredBuffersCount ) );

            offset += pCompletion01->BytesTransferred();

            DeleteScatteredBuffers( scatteredBuffers, scatteredBuffersCount );

            pCompletion01->Release();
            pCompletion01 = 0;
        }


    }
    catch( HRESULT e )
    {
        hr = e;
    }


    if( pTypeDefStream )
    {
        pTypeDefStream->Release();
        pTypeDefStream = 0;
    }
    if( pPropValue )
    {
        pPropValue->Release();
        pPropValue = 0;
    }


    return hr;
}



static HRESULT CreateEssenceData(
    IAAFHeader* pHeader,
    const aafMobID_t& mobID,
    const aafCharacter* pMobName,
    IAAFEssenceData** pEssenceData )
{
    HRESULT  hr = S_OK;
    IAAFDictionary*  pDictionary = 0;
    IAAFMob*  pMob = 0;
    IAAFEssenceDescriptor*  pDescriptor = 0;
    IAAFAIFCDescriptor*  pAIFCDescriptor = 0;
    IAAFSourceMob*  pSourceMob = 0;


    try
    {
        // The dictionary
        CheckResult( pHeader->GetDictionary( &pDictionary ) );

        // Built-in defenitions
        CAAFBuiltinDefs  defs( pDictionary );

        // Create a SourceMob
        CheckResult( defs.cdSourceMob()->CreateInstance(
                        IID_IAAFMob, (IUnknown **)&pMob ) );
        CheckResult( pMob->SetMobID( mobID ) );
        CheckResult( pMob->SetName( pMobName ) );

        // Create an essence descriptor
        CheckResult( defs.cdAIFCDescriptor()->CreateInstance(
                        IID_IAAFEssenceDescriptor,
                        (IUnknown **)&pDescriptor ) );
        CheckResult( pDescriptor->QueryInterface(
                        IID_IAAFAIFCDescriptor, (void **)&pAIFCDescriptor ) );

        const char  testAIFCSummary[] = "test summary";
        const aafUInt32  testAIFCSummarySize = sizeof(testAIFCSummary);
        CheckResult( pAIFCDescriptor->SetSummary( testAIFCSummarySize,
                                                  (aafDataValue_t)testAIFCSummary ) );

        // Initialize the source mob
        CheckResult( pMob->QueryInterface( IID_IAAFSourceMob,
                                           (void **)&pSourceMob ) );
        CheckResult( pSourceMob->SetEssenceDescriptor( pDescriptor ) );
        CheckResult( pSourceMob->Initialize() );

        // Add the source mob to the file
        CheckResult( pHeader->AddMob( pMob ) );


        // Create essence data and add it to the file
        CheckResult( defs.cdEssenceData()->CreateInstance(
                        IID_IAAFEssenceData, (IUnknown **)pEssenceData ) );
        CheckResult( (*pEssenceData)->Initialize( pSourceMob ) );
        CheckResult( pHeader->AddEssenceData( *pEssenceData ) );
    }
    catch (HRESULT& rResult)
    {
        hr = rResult;
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


    return hr;
}



static HRESULT GetEssenceDataTypeAndValue(
    IAAFEssenceData* pEssenceData,
    IAAFTypeDefStream2** pPropType,
    IAAFPropertyValue** pPropValue )
{
    HRESULT  hr = S_OK;
    IAAFTypeDef*  pTypeDef = 0;


    try
    {
        CheckResult( GetPropertyValue( pEssenceData,
                                        kAAFPropID_EssenceData_Data,
                                        pPropValue ) );
        CheckResult( GetPropertyType( pEssenceData,
                                        kAAFPropID_EssenceData_Data,
                                        &pTypeDef ) );
        CheckResult( pTypeDef->QueryInterface( IID_IAAFTypeDefStream2,
                                               (void **)pPropType ) );

    }
    catch (HRESULT& rResult)
    {
        hr = rResult;
    }

    if( pTypeDef )
    {
        pTypeDef->Release();
        pTypeDef = 0;
    }


    return hr;
}



static aafIOBufferDesc_t* AllocateScatteredBuffers(
    const aafIOBufferDesc_t* scatteredBuffers,
    const size_t scatteredBuffersCount )
{
    assert( scatteredBuffers );


    aafIOBufferDesc_t*  result = new aafIOBufferDesc_t[ scatteredBuffersCount ];
    for( size_t i=0; i<scatteredBuffersCount; i++ )
    {
        result[i].bufSize = scatteredBuffers[i].bufSize;
        result[i].buf = new unsigned char[ result[i].bufSize ];
        memset( result[i].buf, 0, result[i].bufSize );
    }


    return result;
}



static void DeleteScatteredBuffers(
    aafIOBufferDesc_t* scatteredBuffers,
    const size_t scatteredBuffersCount )
{
    if( scatteredBuffers )
    {
        for( size_t i=0; i<scatteredBuffersCount; i++ )
        {
            delete[] scatteredBuffers[i].buf;
        }
    }


    delete[] scatteredBuffers;
}



static bool CompareScatteredBuffers(
    const aafIOBufferDesc_t* scatteredBuffers01,
    const aafIOBufferDesc_t* scatteredBuffers02,
    const size_t scatteredBuffersCount )
{
    assert( scatteredBuffers01 );
    assert( scatteredBuffers02 );


    bool  result = true;


    for( size_t i=0; i<scatteredBuffersCount && result; i++ )
    {
        if( scatteredBuffers01[i].bufSize == scatteredBuffers02[i].bufSize )
        {
            if( memcmp( scatteredBuffers01[i].buf,
                        scatteredBuffers02[i].buf,
                        scatteredBuffers02[i].bufSize ) != 0 )
            {
                result = false;
            }
        }
        else
        {
            result = false;
        }
    }


    return result;
}



static bool AllCompleted(
    CustomIOCompletion** completion,
    size_t completionCount )
{
    bool allCompleted = true;
    for( size_t i=0; i<completionCount; i++ )
    {
        if( ! completion[i]->IsCompleted() )
        {
            allCompleted = false;
            break;
        }
    }

    return allCompleted;
}


#ifdef OS_WINDOWS
static void Wait(
    int milliseconds )
{
    // Put the thread into alertable state
    // for specified time.
    SleepEx( milliseconds, TRUE );
}
#else
static void Wait(
    int /* milliseconds */)
{
}
#endif


// Required function prototype.
extern "C" HRESULT CAAFAsyncStreamRawStorage_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID);
extern "C" HRESULT CAAFAsyncStreamRawStorage_test(
    testMode_t mode,
    aafUID_t fileKind,
    testRawStorageType_t rawStorageType,
    aafProductIdentification_t productID)
{
	HRESULT hr = AAFRESULT_NOT_IMPLEMENTED;

#ifdef TEST_NEW_STREAM_WRITING
        // not implemented
#else
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
		cerr << "CAAFAsyncStreamRawStorage_test..."
			 << "Caught general C++ exception!" << endl; 
		hr = AAFRESULT_TEST_FAILED;
	}
#endif

	return hr;
}
