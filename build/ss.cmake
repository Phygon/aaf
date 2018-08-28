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
    message(FATAL_ERROR "'AAFSDK_ROOT' must be set.")
endif()

if(APPLE)
    if(ARCH STREQUAL "universal")
        set(SS_LIB_PATH ${AAFSDK_ROOT}/AAFUniversalDarwinSDK/g++/sss-impl/libSSRW2C.a)
    else()
        set(SS_LIB_PATH ${AAFSDK_ROOT}/AAFx86_64DarwinSDK/clang++/sss-impl/libSSRW2C.a)
    endif()
    #set(SS_LIB_PATH ${AAFSDK_ROOT}/AAFi386DarwinSDK/g++/sss-impl/libSSRW2C.a)
elseif(UNIX)
    set(SS_LIB_PATH ${AAFSDK_ROOT}/AAFx86_64LinuxSDK/g++/sss-impl/libSSRW2C.a)
    #set(SS_LIB_PATH ${AAFSDK_ROOT}/AAFi686LinuxSDK/g++/sss-impl/libSSRW2C.a)
elseif(MSVC)
    unset(SS_LIB_PATH)
    # OM_USE_WINDOWS_SS
endif()

add_library(ss INTERFACE)

if(SS_LIB_PATH)
    target_link_libraries(ss INTERFACE ${SS_LIB_PATH})
endif()
