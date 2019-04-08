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

# MSVC: ./AAFWinSDK/<vsXX>/ref-impl/Om/<Win32|x64>/<Debug|Release>/
# Makefile: ./AAFx86_64LinuxSDK/g++/OM/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}")

add_library(OM STATIC
    OMArrayType.cpp
    OMAssertions.cpp
    OMBufferedIStream.cpp
    OMBufferedStream.cpp
    OMByteArray.cpp
    OMCachedDiskRawStorage.cpp
    OMCachedRawStorage.cpp
    OMCachePageAllocator.cpp
    OMCharacterType.cpp
    OMClassDefinition.cpp
    OMContainerElement.cpp
    OMContainerProperty.cpp
    OMDataSet.cpp
    OMDataStream.cpp
    OMDataStreamAccess.cpp
    OMDataStreamProperty.cpp
    OMDataStreamPropertyFilter.cpp
    OMDataTypes.cpp
    OMDataVector.cpp
    OMDefinition.cpp
    OMDictionary.cpp
    OMDiskRawStorage.cpp
    OMDynamicLibrary.cpp
    OMEnumeratedType.cpp
    OMExceptions.cpp
    OMExtendibleEnumeratedType.cpp
    OMFile.cpp
    OMGSF_SSStoredObjectFactory.cpp
    OMGSFStructuredStorage.cpp
    OMIndirectType.cpp
    OMIntegerType.cpp
    OMIOStream.cpp
    OMKLVStoredObject.cpp
    OMKLVStoredObjectFactory.cpp
    OMKLVStoredStream.cpp
    OMKLVStoredStreamFilter.cpp
    OMMappedFileRawStorage.cpp
    OMMemoryRawStorage.cpp
    OMMS_SSStoredObjectFactory.cpp
    OMMSStructuredStorage.cpp
    OMMXFStorage.cpp
    OMMXFStorageBase.cpp
    OMObjectManager.cpp
    OMObjectReference.cpp
    OMObjectReferenceType.cpp
    OMOpaqueType.cpp
    OMOStream.cpp
    OMPageCache.cpp
    OMProperty.cpp
    OMPropertyDefinition.cpp
    OMPropertySet.cpp
    OMPropertySetIterator.cpp
    OMPropertyTable.cpp
    OMRawStorageLockBytes.cpp
    OMRecordType.cpp
    OMRefProperty.cpp
    OMRefSetProperty.cpp
    OMRefVectorProperty.cpp
    OMRenamedType.cpp
    OMRootStorable.cpp
    OMSetType.cpp
    OMSS_SSStoredObjectFactory.cpp
    OMSSSStorageRWInputSource.cpp
    OMSSStoredObject.cpp
    OMSSStoredObjectFactory.cpp
    OMSSStoredStream.cpp
    OMSSStructuredStorage.cpp
    OMStackTrace.cpp
    OMStorable.cpp
    OMStoredObject.cpp
    OMStoredObjectFactory.cpp
    OMStoredPropertySetIndex.cpp
    OMStoredSetIndex.cpp
    OMStoredVectorIndex.cpp
    OMStream.cpp
    OMStreamType.cpp
    OMStringProperty.cpp
    OMStringType.cpp
    OMStrongReference.cpp
    OMStrongReferenceSet.cpp
    OMStrongReferenceVector.cpp
    OMSymbolspace.cpp
    OMType.cpp
    OMTypeDefinition.cpp
    OMTypeVisitor.cpp
    OMUniqueObjectIdentType.cpp
    OMUtilities.cpp
    OMWeakReference.cpp
    OMWeakReferenceSet.cpp
    OMWeakReferenceVector.cpp
    OMWideStringProperty.cpp
    OMWrappedRawStorage.cpp
    OMWString.cpp
    OMXMLReader.cpp
    OMXMLStorage.cpp
    OMXMLStoredObject.cpp
    OMXMLStoredObjectFactory.cpp
    OMXMLStoredStream.cpp
    OMXMLUtilities.cpp
    OMXMLWriter.cpp
    utf8.cpp
)

target_include_directories(OM PUBLIC
    ${AAFSDK_ROOT}/ref-impl/include/OM
    ${AAFSDK_ROOT}/ref-impl/src/OM
)

target_include_directories(OM PRIVATE
    ${AAFSDK_ROOT}/ref-impl/include
    ${AAFSDK_ROOT}/ref-impl/include/ref-api
    # Required with OM_USE_SCHEMASOFT_SS
    ${AAFSDK_ROOT}/sss-impl/include
    # AAF-XML stored format support requires the expat library which is bundled with the AAF SDK.
    ${AAFSDK_ROOT}/ref-impl/expat
)

target_compile_definitions(OM PUBLIC
    XML_STATIC
    $<$<CONFIG:Debug>:OM_DEBUG>
    $<$<CONFIG:Debug>:OM_STACK_TRACE_ON_ASSERT>
)

if(NOT AAF_NO_STRUCTURED_STORAGE)
    target_compile_definitions(OM PUBLIC OM_STRUCTURED_STORAGE)
    if(WIN32)
        target_compile_definitions(OM PUBLIC OM_USE_SCHEMASOFT_SS OM_USE_WINDOWS_SS OM_USE_STORAGE_EX)
    else()
        target_compile_definitions(OM PUBLIC OM_USE_SCHEMASOFT_SS)
    endif()
else()
    target_compile_definitions(OM PUBLIC OM_NO_STRUCTURED_STORAGE)
endif()

set_target_properties(OM PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)

if(NOT MSVC)
    set_target_properties(OM PROPERTIES
        OUTPUT_NAME "om"
        OUTPUT_NAME_DEBUG "om"
        OUTPUT_NAME_RELEASE "om"
    )
endif()
