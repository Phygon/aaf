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

# MSVC: ./AAFWinSDK/<vsXX>/<Win32|x64>/<Debug|Release>/Test
# Makefile: ./AAFx86_64LinuxSDK/g++/bin/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/Test")

add_executable(ComFileKindTest ComFileKindTest.cpp)

target_include_directories(ComFileKindTest PRIVATE
    ${AAFSDK_ROOT}/Utilities/Include
)

if(WIN32)
    target_link_libraries(ComFileKindTest PRIVATE
        AAFIID
        AAFLIB
        winmm.lib
    )
else()
    target_link_libraries(ComFileKindTest PRIVATE
        AAFIID
        AAFLIB
    )
endif()

set_target_properties(ComFileKindTest PROPERTIES
    VERSION ${AAFSDK_VERSION_STRING}
)

set_target_properties(ComFileKindTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)

add_dependencies(ComFileKindTest
    MakeSDK
)

if(WIN32)
    SET_WIN32_TEST_VARS(${TARGET_DIR} $<TARGET_FILE_NAME:ComFileKindTest>)

    add_test(NAME ComFileKindTest_Debug
             CONFIGURATIONS Debug
             WORKING_DIRECTORY ${TARGET_DIR_DEBUG}
             COMMAND ${TARGET_COMMAND_DEBUG} -d)

    add_test(NAME ComFileKindTest_Release
             CONFIGURATIONS Release
             WORKING_DIRECTORY ${TARGET_DIR_RELEASE}
             COMMAND ${TARGET_COMMAND_RELEASE} -d)
else()
    add_test(NAME ComFileKindTest
             WORKING_DIRECTORY ${TARGET_DIR}
             COMMAND ComFileKindTest -d)
    set_property(TEST ComFileKindTest PROPERTY ENVIRONMENT "LD_LIBRARY_PATH=${AAFSDK_TARGET_DIR}/RefImpl:$ENV{LD_LIBRARY_PATH}")
endif()
