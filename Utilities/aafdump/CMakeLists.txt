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

if(NOT WIN32)
    return()
endif()

# MSVC: ./AAFWinSDK/<vsXX>/Utilities/aafdump/<Win32|x64>/<Debug|Release>/
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/Utilities/aafdump")

add_executable(aafdump
    ${AAFSDK_ROOT}/Utilities/aafdump/aafdump.cpp
    ${AAFSDK_ROOT}/Utilities/aafdump/MStructuredStorage.cpp
    ${AAFSDK_ROOT}/Utilities/aafdump/StructuredStorage.cpp
)

target_include_directories(aafdump PRIVATE
    ${AAFSDK_ROOT}/Utilities/aafdump
    ${AAFSDK_ROOT}/ss-impl/ref
)

if(MSVC)
    # file description
    # internal name
    # file name
    target_generate_rc_file(aafdump
        "aafdump"
        "aafdump"
        "aafdump.exe"
    )
endif()

set_target_properties(aafdump PROPERTIES
    VERSION ${AAFSDK_VERSION_STRING}
)

set_target_properties(aafdump PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)
