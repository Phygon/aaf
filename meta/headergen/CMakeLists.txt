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

cmake_minimum_required (VERSION 3.0.2 FATAL_ERROR)

project(HeaderGen)

get_filename_component(CURRENT_DIR_ABS "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
list(APPEND CMAKE_MODULE_PATH "${AAFSDK_ROOT}/build")

set(OUT_BINARIES_DIR ${CURRENT_DIR_ABS}/bin)
set(OUT_HEADERS_DIR ${CURRENT_DIR_ABS}/include)
set(INSTALL_HEADERS_DIR ${CURRENT_DIR_ABS}/../../ref-impl/include)

# path to generated/modified AAFMetaDictionary.h file to use
set(AAFMETADICT_PATH ${INSTALL_HEADERS_DIR}/AAFMetaDictionary.h)

include_directories(
    ${CURRENT_DIR_ABS}
    ${INSTALL_HEADERS_DIR}
)

add_library(headerGenUtils OBJECT headerGenUtils.cpp headerGenUtils.h)

# classDefUid
set(TARGETNAME classDefUid)
set(OUTPUTNAME AAFClassDefUIDs.h)
add_executable(${TARGETNAME} $<TARGET_OBJECTS:headerGenUtils> classDefUid.cpp headerGenUtils.h ${AAFMETADICT_PATH})
set_target_properties(${TARGETNAME} PROPERTIES OUTPUT_NAME "${TARGETNAME}")
set_target_properties(${TARGETNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_BINARIES_DIR})
add_custom_command(TARGET ${TARGETNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_HEADERS_DIR}/
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} AAFClassDefUIDs > ${OUT_HEADERS_DIR}/${OUTPUTNAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/${OUTPUTNAME} ${INSTALL_HEADERS_DIR}/${OUTPUTNAME}
    COMMENT "Generating ${OUTPUTNAME}..."
)

# extEnumUid
set(TARGETNAME extEnumUid)
set(OUTPUTNAME AAFExtEnum.h)
add_executable(${TARGETNAME} $<TARGET_OBJECTS:headerGenUtils> extEnumUid.cpp headerGenUtils.h ${AAFMETADICT_PATH})
set_target_properties(${TARGETNAME} PROPERTIES OUTPUT_NAME "${TARGETNAME}")
set_target_properties(${TARGETNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_BINARIES_DIR})
add_custom_command(TARGET ${TARGETNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_HEADERS_DIR}/
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} AAFExtEnum > ${OUT_HEADERS_DIR}/${OUTPUTNAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/${OUTPUTNAME} ${INSTALL_HEADERS_DIR}/${OUTPUTNAME}
    COMMENT "Generating ${OUTPUTNAME}..."
)

# propertyDefUid
set(TARGETNAME propertyDefUid)
set(OUTPUTNAME AAFPropertyDefs.h)
add_executable(${TARGETNAME} $<TARGET_OBJECTS:headerGenUtils> propertyDefUid.cpp headerGenUtils.h ${AAFMETADICT_PATH})
set_target_properties(${TARGETNAME} PROPERTIES OUTPUT_NAME "${TARGETNAME}")
set_target_properties(${TARGETNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_BINARIES_DIR})
add_custom_command(TARGET ${TARGETNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_HEADERS_DIR}/
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} AAFPropertyDefs > ${OUT_HEADERS_DIR}/${OUTPUTNAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/${OUTPUTNAME} ${INSTALL_HEADERS_DIR}/${OUTPUTNAME}
    COMMENT "Generating ${OUTPUTNAME}..."
)

# propertyId
set(TARGETNAME propertyId)
set(OUTPUTNAME AAFPropertyIDs.h)
add_executable(${TARGETNAME} $<TARGET_OBJECTS:headerGenUtils> propertyId.cpp headerGenUtils.h ${AAFMETADICT_PATH})
set_target_properties(${TARGETNAME} PROPERTIES OUTPUT_NAME "${TARGETNAME}")
set_target_properties(${TARGETNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_BINARIES_DIR})
add_custom_command(TARGET ${TARGETNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_HEADERS_DIR}/
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} AAFPropertyIDs > ${OUT_HEADERS_DIR}/${OUTPUTNAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/${OUTPUTNAME} ${INSTALL_HEADERS_DIR}/${OUTPUTNAME}
    COMMENT "Generating ${OUTPUTNAME}..."
)

# storedObjectUid
set(TARGETNAME storedObjectUid)
set(OUTPUTNAME AAFStoredObjectIDs.h)
add_executable(${TARGETNAME} $<TARGET_OBJECTS:headerGenUtils> storedObjectUid.cpp headerGenUtils.h ${AAFMETADICT_PATH})
set_target_properties(${TARGETNAME} PROPERTIES OUTPUT_NAME "${TARGETNAME}")
set_target_properties(${TARGETNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_BINARIES_DIR})
add_custom_command(TARGET ${TARGETNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_HEADERS_DIR}/
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} AAFStoredObjectIDs > ${OUT_HEADERS_DIR}/${OUTPUTNAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/${OUTPUTNAME} ${INSTALL_HEADERS_DIR}/${OUTPUTNAME}
    COMMENT "Generating ${OUTPUTNAME}..."
)

# typeDefUid
set(TARGETNAME typeDefUid)
set(OUTPUTNAME AAFTypeDefUIDs.h)
add_executable(${TARGETNAME} $<TARGET_OBJECTS:headerGenUtils> typeDefUid.cpp headerGenUtils.h ${AAFMETADICT_PATH})
set_target_properties(${TARGETNAME} PROPERTIES OUTPUT_NAME "${TARGETNAME}")
set_target_properties(${TARGETNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_BINARIES_DIR})
add_custom_command(TARGET ${TARGETNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_HEADERS_DIR}/
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} AAFTypeDefUIDs > ${OUT_HEADERS_DIR}/${OUTPUTNAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/${OUTPUTNAME} ${INSTALL_HEADERS_DIR}/${OUTPUTNAME}
    COMMENT "Generating ${OUTPUTNAME}..."
)

# genDefInstances
set(TARGETNAME genDefInstances)
add_executable(${TARGETNAME} $<TARGET_OBJECTS:headerGenUtils> genDefInstances.cpp headerGenUtils.h ${AAFMETADICT_PATH})
set_target_properties(${TARGETNAME} PROPERTIES OUTPUT_NAME "${TARGETNAME}")
set_target_properties(${TARGETNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_BINARIES_DIR})
add_custom_command(TARGET ${TARGETNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_HEADERS_DIR}/
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} OperationDefinition kAAF > ${OUT_HEADERS_DIR}/AAFOperationDefs.h
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} ParameterDefinition kAAF > ${OUT_HEADERS_DIR}/AAFParameterDefs.h
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} DataDefinition kAAF > ${OUT_HEADERS_DIR}/AAFDataDefs.h
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} ContainerDefinition kAAF > ${OUT_HEADERS_DIR}/AAFContainerDefs.h
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} InterpolationDefinition kAAF > ${OUT_HEADERS_DIR}/AAFInterpolatorDefs.h
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} OPDefinition kAAF > ${OUT_HEADERS_DIR}/AAFOPDefs.h
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} KLVDataDefinition kAAF > ${OUT_HEADERS_DIR}/AAFKLVDataDefs.h
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} TaggedValueDefinition kAAF > ${OUT_HEADERS_DIR}/AAFTaggedValueDefs.h
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} PluginDefinition kAAF > ${OUT_HEADERS_DIR}/AAFPluginDefs.h
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} CodecDefinition kAAF > ${OUT_HEADERS_DIR}/AAFCodecDefs.h
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} CompressionDefinition kAAF > ${OUT_HEADERS_DIR}/AAFCompressionDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFOperationDefs.h ${INSTALL_HEADERS_DIR}/AAFOperationDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFParameterDefs.h ${INSTALL_HEADERS_DIR}/AAFParameterDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFDataDefs.h ${INSTALL_HEADERS_DIR}/AAFDataDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFContainerDefs.h ${INSTALL_HEADERS_DIR}/AAFContainerDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFInterpolatorDefs.h ${INSTALL_HEADERS_DIR}/AAFInterpolatorDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFOPDefs.h ${INSTALL_HEADERS_DIR}/AAFOPDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFKLVDataDefs.h ${INSTALL_HEADERS_DIR}/AAFKLVDataDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFTaggedValueDefs.h ${INSTALL_HEADERS_DIR}/AAFTaggedValueDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFPluginDefs.h ${INSTALL_HEADERS_DIR}/AAFPluginDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFCodecDefs.h ${INSTALL_HEADERS_DIR}/AAFCodecDefs.h
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/AAFCompressionDefs.h ${INSTALL_HEADERS_DIR}/AAFCompressionDefs.h
    COMMENT "Generating definition headers..."
)

# result
set(TARGETNAME result)
set(OUTPUTNAME AAFResult.h)
add_executable(${TARGETNAME} $<TARGET_OBJECTS:headerGenUtils> result.cpp headerGenUtils.h ../../ref-impl/include/AAFMetaResult.h)
set_target_properties(${TARGETNAME} PROPERTIES OUTPUT_NAME "${TARGETNAME}")
set_target_properties(${TARGETNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_BINARIES_DIR})
add_custom_command(TARGET ${TARGETNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_HEADERS_DIR}/
    COMMAND ${OUT_BINARIES_DIR}/${TARGETNAME} AAFResult > ${OUT_HEADERS_DIR}/${OUTPUTNAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${OUT_HEADERS_DIR}/${OUTPUTNAME} ${INSTALL_HEADERS_DIR}/${OUTPUTNAME}
    COMMENT "Generating ${OUTPUTNAME}..."
)
