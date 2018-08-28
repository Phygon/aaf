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

cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are not allowed!")
endif()

get_filename_component(CURRENT_DIR_ABS "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
set(AAFSDK_ROOT "${CURRENT_DIR_ABS}" CACHE STRING "Path to AAF-SDK root directory" FORCE)
list(APPEND CMAKE_MODULE_PATH "${AAFSDK_ROOT}/build")

set(AAFSDK_VERSION_MAJOR 1 CACHE STRING "Specify the major version of AAF-SDK")
set(AAFSDK_VERSION_MINOR 1 CACHE STRING "Specify the minor version of AAF-SDK")
set(AAFSDK_VERSION_PATCH 6 CACHE STRING "Specify the patch version of AAF-SDK")
set(AAFSDK_VERSION_BUILD 0 CACHE STRING "Specify the build number of AAF-SDK")

set(AAFSDK_VERSION_RELEASE "kAAFVersionBeta" CACHE STRING "Specify the release stage of AAF-SDK")

set(AAFSDK_LEGAL_COMPANY "AAF Association" CACHE STRING "Specify company name")
set(AAFSDK_LEGAL_PRODUCT "AAF-SDK" CACHE STRING "Specify product name")
set(AAFSDK_LEGAL_COPYRIGHT "Copyright © 1998-2018" CACHE STRING "Specify copyright")
set(AAFSDK_LEGAL_TRADEMARKS "" CACHE STRING  "Specify trademarks")
set(AAFSDK_LEGAL_COMMENTS "www.aafassociation.org" CACHE STRING "Specify additional information")

set(AAFSDK_OUT_DIR "${AAFSDK_ROOT}/out" CACHE STRING "Path to AAFSDK output directory")

project(AAF-SDK LANGUAGES CXX)

include(pdefs)
include(cdefs)
include(common)
include(ss)

add_subdirectory(DevUtils)
add_subdirectory(examples)
add_subdirectory(examples2)
add_subdirectory(ref-impl)
add_subdirectory(test)
add_subdirectory(Utilities)

add_custom_target(Everything)
add_dependencies(Everything
    MakeSDK
    MakeSDKExamples
    #MakeSDKExamples2
    MakeSDKTests
    #MakeSDKUtilities
)
