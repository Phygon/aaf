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
# AAFConverterLib
################################################################################
# MSVC: ./AAFWinSDK/<vsXX>/Utilities/AafOmf/<Win32|x64>/<Debug|Release>/
# Makefile: ./AAFx86_64LinuxSDK/g++/bin/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/Utilities/AafOmf")

add_library(AAFConverterLib STATIC
    AafOmf.h
    Aaf2Omf.cpp
    AAFDomainExtensions.cpp
    AAFDomainUtils.cpp
    AAFException.cpp
    AafOmf.cpp
    Assertion.cpp
    EffectTranslate.cpp
    ExceptionBase.cpp
    Extensions.cpp
    LoggerBase.cpp
    Omf2Aaf.cpp
    OMFDomainExtensionUtils.cpp
    OMFDomainUtils.cpp
    OMFException.cpp
    StreamLogger.cpp
)

target_compile_definitions(AAFConverterLib
    -DNO_CONTAINER_EXPORTS
)

target_include_directories(AAFConverterLib PRIVATE
    ${AAFSDK_ROOT}/ref-impl/include
    ${AAFSDK_ROOT}/ref-impl/include/ref-api
    ${AAFSDK_ROOT}/OMF/include
    ${AAFSDK_ROOT}/OMF/portinc
    ${AAFSDK_ROOT}/Utilities/Include
)

set_target_properties(AAFConverterLib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)

################################################################################
# AafOmf
################################################################################
# MSVC: ./AAFWinSDK/<vsXX>/Utilities/AafOmf/<Win32|x64>/<Debug|Release>/
# Makefile: ./AAFx86_64LinuxSDK/g++/bin/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/Utilities/AafOmf")

add_executable(AafOmf
    ${ROOT_DIR}/Utilities/AafOmf/AafOmfMain.cpp
    ${ROOT_DIR}/Utilities/AafOmf/Aaf2Omf.h
    ${ROOT_DIR}/Utilities/AafOmf/AAFDomainExtensions.h
    ${ROOT_DIR}/Utilities/AafOmf/AafOmf.h
    ${ROOT_DIR}/Utilities/AafOmf/EffectTranslate.h
    ${ROOT_DIR}/Utilities/AafOmf/Omf2Aaf.h
    ${ROOT_DIR}/Utilities/AafOmf/OMFDomainUtils.h
)

target_include_directories(AafOmf PRIVATE
    ${ROOT_DIR}/OMF/Include
    ${ROOT_DIR}/OMF/portinc
    ${ROOT_DIR}/Utilities/Include
)

target_link_libraries(AafOmf PRIVATE
    AAFIID
    AAFLIB
    AAFConverterLib
    libbento
    libjpeg
    omfToolkit
)

target_compile_definitions(AAFConverterLib
    -DCOM_NO_WINDOWS_H
    -DNO_CONTAINER_EXPORTS
)

set_target_properties(AafOmf PROPERTIES
    VERSION ${AAFSDK_VERSION_STRING}
)

set_target_properties(AafOmf PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)
