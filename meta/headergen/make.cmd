@echo off

:: PATHS
set ENV_PATH=%~dp0.
set BUILD_PATH=%ENV_PATH%\build
set OUTPUT_PATH=%ENV_PATH%\bin
set SOURCE_PATH=%ENV_PATH%

:: CLEANING
if exist %BUILD_PATH% rmdir %BUILD_PATH% /s /q
if exist %OUTPUT_PATH% rmdir %OUTPUT_PATH% /s /q

:: BUILDING
if not exist %BUILD_PATH% mkdir %BUILD_PATH%
if not exist %OUTPUT_PATH% mkdir %OUTPUT_PATH%
pushd %BUILD_PATH%
cmake -G "Visual Studio 12 2013 Win64" %SOURCE_PATH%
cmake --build . --target ALL_BUILD --config Release
popd
