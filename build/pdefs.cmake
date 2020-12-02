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

if(NOT DEFINED AAFSDK_OUT_DIR)
    message(FATAL_ERROR "'AAFSDK_OUT_DIR' must be set.")
endif()

if(NOT PLATFORM)
    message(FATAL_ERROR "'PLATFORM' must be set.")
endif()

if(NOT ARCH)
    message(FATAL_ERROR "'ARCH' must be set.")
endif()

if(APPLE)
    if(${CMAKE_GENERATOR} STREQUAL "Xcode")
        set(CONFIGURATION "${CMAKE_CFG_INTDIR}")
    elseif(${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
        set(CONFIGURATION "${CMAKE_BUILD_TYPE}")
    else()
        message(FATAL_ERROR "CMake generator '${CMAKE_GENERATOR}' is not supported by this platform.")
    endif()
elseif(WIN32)
    string(REGEX REPLACE "Visual Studio ([0-9]+) .*" "\\1" MSVS_VERSION_NUMBER "${CMAKE_GENERATOR}")
    if(NOT ${CMAKE_GENERATOR} STREQUAL "${MSVS_VERSION_NUMBER}")
        set(CONFIGURATION "${CMAKE_CFG_INTDIR}")
    else()
        message(FATAL_ERROR "CMake generator '${CMAKE_GENERATOR}' is not supported by this platform.")
    endif()
elseif(UNIX)
    if(${CMAKE_GENERATOR} STREQUAL "Unix Makefiles" OR ${CMAKE_GENERATOR} STREQUAL "Ninja")
        set(CONFIGURATION "${CMAKE_BUILD_TYPE}")
    else()
        message(FATAL_ERROR "CMake generator '${CMAKE_GENERATOR}' is not supported by this platform.")
    endif()
else()
    message(FATAL_ERROR "This platform is not supported.")
endif()

set(AAFSDK_TARGET_DIR "${AAFSDK_OUT_DIR}/target/${PLATFORM}-${ARCH}/${CONFIGURATION}" CACHE INTERNAL "Path to target directory" FORCE)
set(AAFSDK_SHARED_DIR "${AAFSDK_OUT_DIR}/shared" CACHE INTERNAL "Path to public headers" FORCE)

if(WIN32)
    # This is a workaround to cmake/ctest not substituting the configuration name in the executable path
    # when the cmake generator supports multiple configurations on Windows.
    # The substitution is done manually and test targets will be created explicitly for Debug
    # and Release configurations using the TARGET_DIR_DEBUG/RELEASE and TARGET_COMMAND_DEBUG/RELEASE variables
    macro(SET_WIN32_TEST_VARS target_dir target_file_name)
        string(REPLACE "\$(Configuration)" "Debug" TARGET_DIR_DEBUG ${target_dir})
        set(TARGET_COMMAND_DEBUG ${TARGET_DIR_DEBUG}/${target_file_name})
        string(REPLACE "\$(Configuration)" "Release" TARGET_DIR_RELEASE ${target_dir})
        set(TARGET_COMMAND_RELEASE ${TARGET_DIR_RELEASE}/${target_file_name})
    endmacro(SET_WIN32_TEST_VARS)
endif()
