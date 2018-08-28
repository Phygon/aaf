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
# ComPersonnelExtension (Shared)
################################################################################
# MSVC: ./AAFWinSDK/<vsXX>/<Win32|x64>/<Debug|Release>/Examples/Com
# Makefile: ./AAFx86_64LinuxSDK/g++/bin/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/Examples")

add_library(ComPersonnelExtension SHARED
    AAFPersonnelExtension.cpp
    CAAFAdminMob.cpp
    CAAFPersonnelResource.cpp
    ${AAFSDK_ROOT}/examples/com-api/ComExtension/extensionUtils.cpp
    ${AAFSDK_ROOT}/ref-impl/src/com-api/com-dll/CAAFClassFactory.cpp
    ${AAFSDK_ROOT}/ref-impl/src/com-api/com-dll/CAAFServer.cpp
    ${AAFSDK_ROOT}/ref-impl/src/com-api/com-dll/CAAFUnknown.cpp
)

target_include_directories(ComPersonnelExtension PRIVATE
    ${AAFSDK_ROOT}/examples/com-api/ComExtension
    ${AAFSDK_ROOT}/ref-impl/src/com-api/com-dll
    ${AAFSDK_ROOT}/Utilities/Include
)

target_link_libraries(ComPersonnelExtension PRIVATE
    AAFIID
    AAFLIB
)

target_compile_definitions(ComPersonnelExtension PUBLIC
    _USRDLL
    COMPERSONNELEXTENSION_EXPORTS
)

if(MSVC)
    # does not work with cmake 3.0.2
    #target_sources(ComPersonnelExtension PRIVATE "AAFPersonnelExtension.def")
    set_target_properties(ComPersonnelExtension PROPERTIES LINK_FLAGS "/DEF:\"${CMAKE_CURRENT_LIST_DIR}/AAFPersonnelExtension.def\"")
endif()

set_target_properties(ComPersonnelExtension PROPERTIES
    MACOSX_RPATH ON
    NO_SONAME ON
    SOVERSION ${AAFSDK_VERSION_MAJOR}
    VERSION ${AAFSDK_VERSION_STRING}
)

set_target_properties(ComPersonnelExtension PROPERTIES
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

set_target_properties(ComPersonnelExtension PROPERTIES
    OUTPUT_NAME "AAFPersonnelExtension"
    OUTPUT_NAME_DEBUG "AAFPersonnelExtension"
    OUTPUT_NAME_RELEASE "AAFPersonnelExtension"
)

add_dependencies(ComPersonnelExtension
    MakeSDK
)

################################################################################
# ComPersonnelPluginWrite
################################################################################
# MSVC: ./AAFWinSDK/<vsXX>/<Win32|x64>/<Debug|Release>/Examples/Com
# Makefile: ./AAFx86_64LinuxSDK/g++/bin/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/Examples")

add_executable(ComPersonnelPluginWrite
    extensionReadPlugin.cpp
    extensionWritePlugin.cpp
    writePlugin.cpp
    ${AAFSDK_ROOT}/examples/com-api/ComExtension/extensionUtils.cpp
)

target_include_directories(ComPersonnelPluginWrite PRIVATE
    ${AAFSDK_ROOT}/examples/com-api/ComExtension
    ${AAFSDK_ROOT}/Utilities/Include
)

target_link_libraries(ComPersonnelPluginWrite PRIVATE
    AAFIID
    AAFLIB
)

set_target_properties(ComPersonnelPluginWrite PROPERTIES
    VERSION ${AAFSDK_VERSION_STRING}
)

set_target_properties(ComPersonnelPluginWrite PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)

add_dependencies(ComPersonnelPluginWrite
    MakeSDK
)
