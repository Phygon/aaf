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

# MSVC: ./AAFWinSDK/<vsXX>/examples2/axLib/<Win32|x64>/<Debug|Release>/
# Makefile: ./AAFx86_64LinuxSDK/g++/axExamples/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/Examples2/axLib")

add_library(axLib STATIC
    AxBaseObj.cpp
    AxBaseObj.h
    AxBaseObjIter.cpp
    AxBaseObjIter.h
    AxComponent.cpp
    AxComponent.h
    AxContentStorage.cpp
    AxContentStorage.h
    AxDefObject.cpp
    AxDefObject.h
    AxDescriptiveFramework.cpp
    AxDescriptiveFramework.h
    AxDictionary.cpp
    AxDictionary.h
    AxEssence.cpp
    AxEssence.h
    AxEx.cpp
    AxEx.h
    AxFile.cpp
    AxFile.h
    AxHeader.cpp
    AxHeader.h
    AxHrMap.cpp
    AxHrMap.h
    AxInit.cpp
    AxInit.h
    AxIterator.cpp
    AxIterator.h
    AxKLVData.cpp
    AxKLVData.h
    AxMetaDef.cpp
    AxMetaDef.h
    AxMob.cpp
    AxMob.h
    AxMobSlot.cpp
    AxMobSlot.h
    AxObject.cpp
    AxObject.h
    AxParameter.cpp
    AxParameter.h
    AxPluginMgr.cpp
    AxPluginMgr.h
    AxProperty.cpp
    AxProperty.h
    AxPropertyValue.cpp
    AxPropertyValue.h
    AxPropertyValueDump.cpp
    AxPropertyValueDump.h
    AxSmartPointer.cpp
    AxSmartPointer.h
    AxStorageErrors.h
    AxTaggedValue.cpp
    AxTaggedValue.h
    AxTypes.cpp
    AxTypes.h
    AxUtil.cpp
    AxUtil.h
)

target_include_directories(axLib
    PUBLIC ${AAFSDK_ROOT}/examples2/axLib
    PRIVATE ${AAFSDK_ROOT}/ref-impl/include
    PRIVATE ${AAFSDK_ROOT}/ref-impl/include/ref-api
)

set_target_properties(axLib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)
