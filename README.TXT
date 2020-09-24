
                        AAF SDK version 1.2.0 Release
                         http://aaf.sourceforge.net/

Getting Started
-----------------

The AAF SDK is built and tested using CMake.

Navigate to the AAF SDK root directory and run:

(a) On Windows:
Replace <CONFIG> below with either Debug or Release.
  > mkdir out\build
  > cd out\build
  > cmake -G "Visual Studio 12 2013 Win64" -DPLATFORM=vc12 -DARCH=x64 ..\..
  > cmake --build . --config <CONFIG>
  > ctest -C

(b) On MacOS:
  $ mkdir -p out/build
  $ cd out/build
  $ cmake -G "Xcode" -DPLATFORM=clang7 -DARCH=x86_64 ../..
  $ cmake --build .

(c) On Linux
Replace <CONFIG> below with either Debug or Release.
  $ mkdir -p out/build
  $ cd out/build
  $ cmake -G "Unix Makefiles" -DPLATFORM=gcc48 -DARCH=x86_64 -DCMAKE_BUILD_TYPE=<CONFIG> ../..
  $ cmake --build .
  $ ctest


Examples
----------

To run an example the SDK dynamic library (AAFCOAPI.dll for WIN32,
libcom-api.so for other platforms) must be in your platform's
dynamic library search path.
Under Win32 your PATH must contain AAF/out/target/vc12-x64/Debug/RefImpl
- Create sample AAF files by running ComModAAF.exe
    AAF/out/target/vc12-x64/Debug/Test/ComModTestAAF.exe
- Use the InfoDumper executable to inspect an AAF file
    AAF/out/target/vc12-x64/Debug/Examples/InfoDumper.exe EssenceAccessCDCI_DV.aaf


Documentation
---------------

API documentation and the AAF SDK FAQ are available from the AAF SDK home page
http://aaf.sourceforge.net/
The API documentation can also be built from the SDK source:
  $ cd ref-impl/doc/com-api
  $ make doc
See ref-impl/doc/com-api/README.txt for full details.


Further information
-------------------

If you a have query please use the AAF SDK Forums
http://sourceforge.net/forum/?group_id=24405
