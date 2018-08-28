###############################################################################
#
# $Id$ $Name$
#
# The contents of this file are subject to the AAF SDK Public Source
# License Agreement Version 2.0 (the "License"); You may not use this
# file except in compliance with the License.  The License is available
# in AAFSDKPSL.TXT, or you may obtain a copy of the License from the
# Advanced Media Workflow Association, Inc., or its successor.
#
# Software distributed under the License is distributed on an "AS IS"
# basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
# the License for the specific language governing rights and limitations
# under the License.  Refer to Section 3.3 of the License for proper use
# of this Exhibit.
#
# WARNING:  Please contact the Advanced Media Workflow Association,
# Inc., for more information about any additional licenses to
# intellectual property covering the AAF Standard that may be required
# to create and distribute AAF compliant products.
# (http://www.amwa.tv/policies).
#
# Copyright Notices:
# The Original Code of this file is Copyright 1998-2012, licensor of the
# Advanced Media Workflow Association.  All rights reserved.
#
# The Initial Developer of the Original Code of this file and the
# licensor of the Advanced Media Workflow Association is
# Avid Technology.
# All rights reserved.
#
###############################################################################

cmake_minimum_required(VERSION 3.0.2)

if(NOT DEFINED AAFSDK_ROOT)
    message(FATAL_ERROR "'AAFSDK_ROOT' must be set. Run a build from the top-level CMakeLists.txt script.")
endif()

################################################################################
# AAFStandardCodecs
################################################################################
# MSVC: ./AAFWinSDK/<vsXX>/<Win32|x64>/<Debug|Release>/RefImpl/aafext
# Makefile: ./AAFx86_64LinuxSDK/g++/ref-impl/<debug|>
# Makefile: ./AAFx86_64LinuxSDK/g++/bin/<debug|>/aafext
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/RefImpl/aafext")

add_library(AAFStandardCodecs SHARED
    AAFPluginCOM.cpp
    AAFPluginUtils.cpp
    CAAFAIFCCodec.cpp
    CAAFCDCICodec.cpp
    CAAFCDCIDescriptorHelper.cpp
    CAAFDNxHDCodec.cpp
    CAAFEssenceDataStream.cpp
    CAAFEssenceFileContainer.cpp
    CAAFEssenceFileStream.cpp
    CAAFEssenceRIFFWAVEContainer.cpp
    CAAFEssenceRIFFWAVEStream.cpp
    CAAFJPEGCodec.cpp
    CAAFJPEGDescriptorHelper.cpp
    CAAFPCMCodec.cpp
    CAAFVC3Codec.cpp
    CAAFWAVECodec.cpp
    jpegesdatadst.cpp
    jpegesdatasrc.cpp
    ../src/com-api/com-dll/CAAFClassFactory.cpp
    ../src/com-api/com-dll/CAAFInProcServer.cpp
    ../src/com-api/com-dll/CAAFServer.cpp
    ../src/com-api/com-dll/CAAFUnknown.cpp
    ../src/OM/utf8.cpp
)

target_include_directories(AAFStandardCodecs PUBLIC
    .
    ../include/OM
    ../src/com-api
    ../src/com-api/com-dll
    ../src/impl
    ../src/OM
    ../../Utilities/Include
)

target_link_libraries(AAFStandardCodecs PRIVATE
    AAFIID
    AAFLIB
    libjpeg
)

if(MSVC)
    # does not work with cmake 3.0.2
    #target_sources(AAFStandardCodecs PRIVATE "AafPlugincom.def")
    set_target_properties(AAFStandardCodecs PROPERTIES LINK_FLAGS "/DEF:\"${CMAKE_CURRENT_LIST_DIR}/AafPlugincom.def\"")
endif()

set_target_properties(AAFStandardCodecs PROPERTIES
    MACOSX_RPATH ON
    NO_SONAME ON
    SOVERSION ${AAFSDK_VERSION_MAJOR}
    VERSION ${AAFSDK_VERSION_STRING}
)

set_target_properties(AAFStandardCodecs PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${TARGET_DIR}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)

if(MSVC)
    set(TARGET_BINARY_NAME "AAFPGAPI")
else()
    set(TARGET_BINARY_NAME "aafpgapi")
endif()

if(AAFSDK_DLL_VERSIONED)
    set(TARGET_BINARY_NAME "${TARGET_BINARY_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
endif()

set_target_properties(AAFStandardCodecs PROPERTIES
    OUTPUT_NAME ${TARGET_BINARY_NAME}
    OUTPUT_NAME_DEBUG ${TARGET_BINARY_NAME}
    OUTPUT_NAME_RELEASE ${TARGET_BINARY_NAME}
)

################################################################################
# AAFBasicInterpolators
################################################################################
# MSVC: ./AAFWinSDK/<vsXX>/<Win32|x64>/<Debug|Release>/RefImpl/aafext
# Makefile: ./AAFx86_64LinuxSDK/g++/ref-impl/<debug|>
# Makefile: ./AAFx86_64LinuxSDK/g++/bin/<debug|>/aafext
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/RefImpl/aafext")

add_library(AAFBasicInterpolators SHARED
    AAFInterpCOM.cpp
    AAFRational.cpp
    CAAFBasicInterp.cpp
    ../src/com-api/com-dll/CAAFClassFactory.cpp
    ../src/com-api/com-dll/CAAFInProcServer.cpp
    ../src/com-api/com-dll/CAAFServer.cpp
    ../src/com-api/com-dll/CAAFUnknown.cpp
)

target_include_directories(AAFBasicInterpolators PUBLIC
    .
    ../include/OM
    ../src/com-api
    ../src/com-api/com-dll
    ../src/impl
    ../src/OM
    ../../Utilities/Include
)

target_link_libraries(AAFBasicInterpolators
    AAFIID
    AAFLIB
)

if(MSVC)
    # does not work with cmake 3.0.2
    #target_sources(AAFBasicInterpolators PRIVATE "AAFINTP.DEF")
    set_target_properties(AAFBasicInterpolators PROPERTIES LINK_FLAGS "/DEF:\"${CMAKE_CURRENT_LIST_DIR}/AAFINTP.DEF\"")
endif()

set_target_properties(AAFBasicInterpolators PROPERTIES
    MACOSX_RPATH ON
    NO_SONAME ON
    SOVERSION ${AAFSDK_VERSION_MAJOR}
    VERSION ${AAFSDK_VERSION_STRING}
)

set_target_properties(AAFBasicInterpolators PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${TARGET_DIR}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)

if(MSVC)
    set(TARGET_BINARY_NAME "AAFINTP")
else()
    set(TARGET_BINARY_NAME "aafintp")
endif()

if(AAFSDK_DLL_VERSIONED)
    set(TARGET_BINARY_NAME "${TARGET_BINARY_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
endif()

set_target_properties(AAFBasicInterpolators PROPERTIES
    OUTPUT_NAME ${TARGET_BINARY_NAME}
    OUTPUT_NAME_DEBUG ${TARGET_BINARY_NAME}
    OUTPUT_NAME_RELEASE ${TARGET_BINARY_NAME}
)
