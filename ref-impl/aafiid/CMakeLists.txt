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

# MSVC: ./AAFWinSDK/<vsXX>/<Win32|64>/<Debug|Release>/RefImpl
# Makefile: ./AAFx86_64LinuxSDK/g++/aafiid/<debug|>
# Makefile: ./AAFx86_64LinuxSDK/g++/lib/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/RefImpl")

add_library(AAFIID STATIC aafiid.cpp)

target_include_directories(AAFIID PRIVATE
    ${AAFSDK_ROOT}/ref-impl/include
    ${AAFSDK_ROOT}/ref-impl/include/ref-api
)

set_target_properties(AAFIID PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(AAFIID PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)

if(MSVC)
    set_target_properties(AAFIID PROPERTIES DEBUG_POSTFIX "D")
else()
    set_target_properties(AAFIID PROPERTIES
        OUTPUT_NAME "aafiid"
        OUTPUT_NAME_DEBUG "aafiid"
        OUTPUT_NAME_RELEASE "aafiid"
    )
endif()
