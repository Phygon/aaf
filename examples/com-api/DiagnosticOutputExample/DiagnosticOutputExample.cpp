//=---------------------------------------------------------------------=
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
// The Original Code of this file is Copyright 1998-2004, Licensor of the
// AAF Association.
// 
// The Initial Developer of the Original Code of this file and the
// Licensor of the AAF Association is Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AAF.h"
#include "AAFResult.h"
#include "AAFFileKinds.h"



// IMyDiagnosticOutput writes the AAF Toolkit diagnostic output
// to a text file
// 
class IMyDiagnosticOutput : public IAAFDiagnosticOutput
{
    public:

        IMyDiagnosticOutput( const char* p_filename );

        virtual HRESULT STDMETHODCALLTYPE PutString( aafCharacter_constptr wcs );

        virtual HRESULT STDMETHODCALLTYPE QueryInterface (REFIID iid, void ** ppIfc);
        virtual aafUInt32 STDMETHODCALLTYPE AddRef();
        virtual aafUInt32 STDMETHODCALLTYPE Release();


    private:

        // The destructor is private. Clients should use Release()
        // do delete instances.
        ~IMyDiagnosticOutput();


    private:

        aafUInt32   _referenceCount;
        FILE*       _fp;
};



IMyDiagnosticOutput::IMyDiagnosticOutput(
    const char* p_filename ) :

    _referenceCount( 1 ),
    _fp( 0 )
{
    assert( p_filename );

    _fp = fopen( p_filename, "wt" );
    assert( _fp );
}



IMyDiagnosticOutput::~IMyDiagnosticOutput()
{
    assert( _referenceCount == 0 );
    assert( _fp );

    fflush( _fp );
    fclose( _fp );
    _fp = 0;
}



HRESULT STDMETHODCALLTYPE IMyDiagnosticOutput::PutString(
    aafCharacter_constptr wcs )
{
    const size_t  string_length = wcslen( wcs );
    char*  mbs = new char[ string_length + 1 ];
    wcstombs( mbs, wcs, string_length + 1 );
    fprintf( _fp, "%s", mbs );
    delete[] mbs;


    return 0;
}



HRESULT STDMETHODCALLTYPE IMyDiagnosticOutput::QueryInterface(
    REFIID iid,
    void ** ppIfc )
{
    if (! ppIfc)
        return AAFRESULT_NULL_PARAM;
    if (iid == IID_IUnknown)
    {
        IUnknown * runk = this;
        *ppIfc = (void*) runk;
        AddRef ();
        return AAFRESULT_SUCCESS;
    }
    else if (iid == IID_IAAFDiagnosticOutput)
    {
        IAAFDiagnosticOutput * ros = this;
        *ppIfc = (void*) ros;
        AddRef ();
        return AAFRESULT_SUCCESS;
    }
    else
    {
        return E_NOINTERFACE;
    }
}



aafUInt32 STDMETHODCALLTYPE IMyDiagnosticOutput::AddRef()
{
    return ++_referenceCount;
}



aafUInt32 STDMETHODCALLTYPE IMyDiagnosticOutput::Release()
{
    aafUInt32 localReferenceCount = --_referenceCount;
    if( localReferenceCount == 0 )
    {
        delete this;
    }
    return localReferenceCount;
}



int main( int argc, char* argv[] )
{
    AAFRESULT  hr = AAFRESULT_SUCCESS;


    if( argc == 2 )
    {
        IMyDiagnosticOutput*  p_output = new IMyDiagnosticOutput( argv[1] );
        hr = AAFSetDiagnosticOutput( p_output );
        p_output->Release();
        p_output = 0;

        if( SUCCEEDED( hr ) )
        {
            printf( "Redirecting diagnostic output from AAF Toolkit to %s\n",
                    argv[1] );
        }
        else
        {
            fprintf( stderr, "ERROR: AAFSetDiagnosticOutput() failed\n" );
        }
    }
    else if( argc == 1 )
    {
        printf( "Using default AAF Toolkit diagnostic output\n" );
    }
    else
    {
            fprintf( stderr, "ERROR: Invalid command line\n" );
            fprintf( stderr, "Usage: %s <log file name>\n", argv[0] );
            hr = AAFRESULT_MAXCODE;
    }


    if( FAILED( hr ) )
    {
        return 1;
    }


    aafProductVersion_t  product_version =
        { 0, 0, 0, 0, kAAFVersionUnknown };

    aafProductIdentification_t  product_id =
        {
            L"Avid Technology",
            L"DiagnosticOutput",
            L"",
            { 0x018541aa, 0x8e18, 0x4a70,
              { 0xbe, 0xd0, 0xea, 0x0d,
                0x49, 0xef, 0x28, 0xd5 } },
            L"",
            &product_version
        };


    IAAFRawStorage* p_storage = 0;
    hr = AAFCreateRawStorageMemory( kAAFFileAccess_modify, &p_storage );
    assert( SUCCEEDED( hr ) );


    IAAFFile*  p_file = 0;
    hr = AAFCreateAAFFileOnRawStorage( p_storage,
                                       kAAFFileExistence_new,
                                       kAAFFileAccess_modify,
                                       &aafFileKindAafSSBinary,
                                       0,
                                       &product_id,
                                       &p_file );
    assert( SUCCEEDED( hr ) );


    // Releasing file before closing it (p_file->Close()) causes
    // an assertion go off inside the AAF toolkit. You can see the
    // assertion message going through IMyDiagnosticOutput::PutString().
    p_file->Release();
    p_file = 0;

    p_storage->Release();
    p_storage = 0;


    return 0;
}
