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

# MSVC: ./AAFWinSDK/<vsXX>/<Win32|x64>/<Debug|Release>/RefImpl
# Makefile: ./AAFx86_64LinuxSDK/g++/aaflib/<debug|>
# Makefile: ./AAFx86_64LinuxSDK/g++/lib/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/RefImpl")

add_library(AAFLIB STATIC
    aaflib.h
    aafrdli.h
    aaflib.cpp
    aaflibwin32.cpp
    aaflibsgi.cpp
    #aaflibMacX.cpp
)

target_include_directories(AAFLIB PUBLIC
    ${AAFSDK_ROOT}/ref-impl/include
    ${AAFSDK_ROOT}/ref-impl/include/ref-api
)

target_include_directories(AAFLIB PRIVATE
    ${AAFSDK_ROOT}/ref-impl/aaflib
    ${AAFSDK_ROOT}/ref-impl/plugins
    ${AAFSDK_ROOT}/ref-impl/src/com-api
    ${AAFSDK_ROOT}/ref-impl/src/com-api/com-dll
    ${AAFSDK_ROOT}/ref-impl/src/impl
    ${AAFSDK_ROOT}/ref-impl/include/OM
    ${AAFSDK_ROOT}/ref-impl/src/OM
)

target_compile_definitions(AAFLIB PRIVATE
    AAFSDK_VERSION_MAJOR=${AAFSDK_VERSION_MAJOR}
    AAFSDK_VERSION_MINOR=${AAFSDK_VERSION_MINOR}
    AAFSDK_VERSION_PATCH=${AAFSDK_VERSION_PATCH}
    AAFSDK_VERSION_BUILD=${AAFSDK_VERSION_BUILD}
    AAFSDK_VERSION_RELEASE=${AAFSDK_VERSION_RELEASE}
)

if(UNIX AND NOT APPLE)
    target_link_libraries(AAFLIB dl uuid)
endif()

# TODO: find a way to get the actual 'comapi' target output binary name
if(AAFSDK_DLL_VERSIONED)
    set(AAFCOAPI_DLL_NAME "com-api-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
    if(APPLE)
        target_compile_definitions(AAFLIB PRIVATE DEFAULT_AAFDLL_NAME=\"lib${AAFCOAPI_DLL_NAME}.dylib\")
    elseif(UNIX)
        target_compile_definitions(AAFLIB PRIVATE DEFAULT_AAFDLL_NAME=\"lib${AAFCOAPI_DLL_NAME}.so\")
    endif()
endif()

set_target_properties(AAFLIB PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)

if(MSVC)
    set_target_properties(AAFLIB PROPERTIES
        OUTPUT_NAME "AAF"
        OUTPUT_NAME_DEBUG "AAF"
        OUTPUT_NAME_RELEASE "AAF"
        DEBUG_POSTFIX "D"
    )
else()
    set_target_properties(AAFLIB PROPERTIES
        OUTPUT_NAME "aaflib"
        OUTPUT_NAME_DEBUG "aaflib"
        OUTPUT_NAME_RELEASE "aaflib"
    )
endif()
