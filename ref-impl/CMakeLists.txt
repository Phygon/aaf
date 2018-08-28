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

project(MakeSDK LANGUAGES CXX)

add_subdirectory(aafiid)
add_subdirectory(aaflib)
add_subdirectory(expat)
add_subdirectory(libjpeg)
add_subdirectory(plugins)
add_subdirectory(src/com-api)
add_subdirectory(src/impl)
add_subdirectory(src/OM)

add_custom_target(MakeSDK ALL COMMENT "Building MakeSDK...")

set(INCLUDES
    AAFAudioLabels.h
    AAFClassDefUIDs.h
    AAFCodecDefs.h
    AAFCOMPlatform.h
    AAFCOMPlatformTypes.h
    AAFContainerDefs.h
    AAFDataDefs.h
    AAFDefUIDs.h
    AAFEssenceFormats.h
    AAFExtEnum.h
    AAFFileKinds.h
    AAFFileMode.h
    AAFInterpolatorDefs.h
    AAFMetaDictionary.h
    AAFOperationCategories.h
    AAFOperationDefs.h
    AAFParameterDefs.h
    AAFPlatform.h
    AAFPluginDefs.h
    AAFPropertyDefs.h
    AAFPropertyIDs.h
    AAFResult.h
    AAFSmartPointer.h 
    AAFSmartPointer2.h
    AAFSmartPointerBase.h
    AAFStoredObjectIDs.h
    AAFTypeDefUIDs.h
)

set(REFAPI
    AAF_i.c
    AAF.h
    AAFPlugin_i.c
    AAFPlugin.h
    AAFPluginTypes.h
    AAFTypes.h
)

set(UTILITIES_INCLUDES
    CAAFBuiltinDefs.h
)

target_copy_files(MakeSDK
    "${CMAKE_CURRENT_LIST_DIR}/include"
    "${AAFSDK_SHARED_DIR}/include"
    "${INCLUDES}"
)

target_copy_files(MakeSDK
    "${CMAKE_CURRENT_LIST_DIR}/include/ref-api"
    "${AAFSDK_SHARED_DIR}/include"
    "${REFAPI}"
)

target_copy_files(MakeSDK
    "${AAFSDK_ROOT}/Utilities/Include"
    "${AAFSDK_SHARED_DIR}/include"
    "${UTILITIES_INCLUDES}"
)

add_dependencies(MakeSDK
    AAFBasicInterpolators
    AAFIID
    AAFLIB
    AAFStandardCodecs
    comapi
)
