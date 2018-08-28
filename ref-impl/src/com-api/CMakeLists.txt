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

# MSVC: ./AAFWinSDK/<vsXX>/<Win32|x64>/<Debug|Release>/RefImpl
# Makefile: ./AAFx86_64LinuxSDK/g++/com-api/<debug|>
# Makefile: ./AAFx86_64LinuxSDK/g++/bin/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}/RefImpl")

add_library(comapi SHARED
    CAAFAES3PCMDescriptor.cpp
    CAAFAIFCDescriptor.cpp
    CAAFAsyncStreamRawStorage.cpp
    CAAFAudioChannelLabelSubDescriptor.cpp
    CAAFAuxiliaryDescriptor.cpp
    CAAFAVCSubDescriptor.cpp
    CAAFTypeDefGenericCharacter.cpp
    CAAFBWFImportDescriptor.cpp
    CAAFCachePageAllocator.cpp
    CAAFCDCIDescriptor.cpp
    CAAFClassDef.cpp
    CAAFCodecDef.cpp
    CAAFCommentMarker.cpp
    CAAFComponent.cpp
    CAAFCompositionMob.cpp
    CAAFConstantValue.cpp
    CAAFContainerDef.cpp
    CAAFContentStorage.cpp
    CAAFControlPoint.cpp
    CAAFDataDef.cpp
    CAAFDataEssenceDescriptor.cpp
    CAAFDefObject.cpp
    CAAFDescriptiveClip.cpp
    CAAFDescriptiveFramework.cpp
    CAAFDescriptiveMarker.cpp
    CAAFDescriptiveObject.cpp
    CAAFDictionary.cpp
    CAAFDigitalImageDescriptor.cpp
    CAAFEdgecode.cpp
    CAAFEnumValidation.cpp
    CAAFEssenceAccess.cpp
    CAAFEssenceData.cpp
    CAAFEssenceDescriptor.cpp
    CAAFEssenceFormat.cpp
    CAAFEssenceGroup.cpp
    CAAFEvent.cpp
    CAAFEventMobSlot.cpp
    CAAFFile.cpp
    CAAFFileDescriptor.cpp
    CAAFFileEncoding.cpp
    CAAFFiller.cpp
    CAAFFilmDescriptor.cpp
    CAAFFindSourceInfo.cpp
    CAAFGetFileBits.cpp
    CAAFGPITrigger.cpp
    CAAFGroupOfSoundfieldGroupsLabelSubDescriptor.cpp
    CAAFHeader.cpp
    CAAFHTMLClip.cpp
    CAAFHTMLDescriptor.cpp
    CAAFIdentification.cpp
    CAAFImportDescriptor.cpp
    CAAFInterpolationDef.cpp
    CAAFIOCompletion.cpp
    CAAFJPEG2000SubDescriptor.cpp
    CAAFKLVData.cpp
    CAAFKLVDataDefinition.cpp
    CAAFLocator.cpp
    CAAFMasterMob.cpp
    CAAFMCALabelSubDescriptor.cpp
    CAAFMetaDefinition.cpp
    CAAFMetaDictionary.cpp
    CAAFMob.cpp
    CAAFMobSlot.cpp
    CAAFModule.cpp
    CAAFMPEG4VisualSubDescriptor.cpp
    CAAFMPEGAudioDescriptor.cpp
    CAAFMPEGVideoDescriptor.cpp
    CAAFMultipleDescriptor.cpp
    CAAFNestedScope.cpp
    CAAFNetworkLocator.cpp
    CAAFObject.cpp
    CAAFOperationDef.cpp
    CAAFOperationGroup.cpp
    CAAFParameter.cpp
    CAAFParameterDef.cpp
    CAAFPCMDescriptor.cpp
    CAAFPhysicalDescriptor.cpp
    CAAFPlainEssenceData.cpp
    CAAFPlainStreamData.cpp
    CAAFPluginDef.cpp
    CAAFPluginManager.cpp
    CAAFProperty.cpp
    CAAFPropertyDef.cpp
    CAAFPropertyValue.cpp
    CAAFPropValData.cpp
    CAAFPulldown.cpp
    CAAFRandomFile.cpp
    CAAFRandomRawStorage.cpp
    CAAFRawStorage.cpp
    CAAFRecordingDescriptor.cpp
    CAAFRGBADescriptor.cpp
    CAAFRIFFChunk.cpp
    CAAFRoot.cpp
    CAAFScopeReference.cpp
    CAAFSegment.cpp
    CAAFSelector.cpp
    CAAFSequence.cpp
    CAAFSetFileBits.cpp
    CAAFSoundDescriptor.cpp
    CAAFSoundfieldGroupLabelSubDescriptor.cpp
    CAAFSourceClip.cpp
    CAAFSourceMob.cpp
    CAAFSourceReference.cpp
    CAAFStaticMobSlot.cpp
    CAAFStreamPropertyValue.cpp
    CAAFStreamRawStorage.cpp
    CAAFStrongRefArrayValue.cpp
    CAAFStrongRefSetValue.cpp
    CAAFStrongRefValue.cpp
    CAAFSubDescriptor.cpp
    CAAFTaggedValue.cpp
    CAAFTaggedValueDefinition.cpp
    CAAFTapeDescriptor.cpp
    CAAFTextClip.cpp
    CAAFTextLocator.cpp
    CAAFTIFFDescriptor.cpp
    CAAFTimecode.cpp
    CAAFTimecodeStream.cpp
    CAAFTimecodeStream12M.cpp
    CAAFTimelineMobSlot.cpp
    CAAFTransition.cpp
    CAAFTypeDef.cpp
    CAAFTypeDefCharacter.cpp
    CAAFTypeDefEnum.cpp
    CAAFTypeDefExtEnum.cpp
    CAAFTypeDefFixedArray.cpp
    CAAFTypeDefIndirect.cpp
    CAAFTypeDefInt.cpp
    CAAFTypeDefObjectRef.cpp
    CAAFTypeDefOpaque.cpp
    CAAFTypeDefRecord.cpp
    CAAFTypeDefRename.cpp
    CAAFTypeDefSet.cpp
    CAAFTypeDefStream.cpp
    CAAFTypeDefString.cpp
    CAAFTypeDefStrongObjRef.cpp
    CAAFTypeDefVariableArray.cpp
    CAAFTypeDefWeakObjRef.cpp
    CAAFVaryingValue.cpp
    CAAFWAVEDescriptor.cpp
    CAAFWeakRefArrayValue.cpp
    CAAFWeakRefSetValue.cpp
    CAAFWeakRefValue.cpp
    CEnumAAFClassDefs.cpp
    CEnumAAFCodecDefs.cpp
    CEnumAAFCodecFlavours.cpp
    CEnumAAFComponents.cpp
    CEnumAAFContainerDefs.cpp
    CEnumAAFControlPoints.cpp
    CEnumAAFDataDefs.cpp
    CEnumAAFEssenceData.cpp
    CEnumAAFFileDescriptors.cpp
    CEnumAAFFileEncodings.cpp
    CEnumAAFIdentifications.cpp
    CEnumAAFInterpolationDefs.cpp
    CEnumAAFKLVData.cpp
    CEnumAAFKLVDataDefs.cpp
    CEnumAAFLoadedPlugins.cpp
    CEnumAAFLocators.cpp
    CEnumAAFMobs.cpp
    CEnumAAFMobSlots.cpp
    CEnumAAFOperationDefs.cpp
    CEnumAAFParameterDefs.cpp
    CEnumAAFParameters.cpp
    CEnumAAFPluginDefs.cpp
    CEnumAAFPluginLocators.cpp
    CEnumAAFProperties.cpp
    CEnumAAFPropertyDefs.cpp
    CEnumAAFPropertyValues.cpp
    CEnumAAFRIFFChunks.cpp
    CEnumAAFSegments.cpp
    CEnumAAFStorablePropVals.cpp
    CEnumAAFSubDescriptors.cpp
    CEnumAAFTaggedValueDefs.cpp
    CEnumAAFTaggedValues.cpp
    CEnumAAFTypeDefs.cpp
    com-dll/AAFCOM.cpp
    com-dll/AAFObjectCreation.cpp
    com-dll/CAAFClassFactory.cpp
    com-dll/CAAFInProcServer.cpp
    com-dll/CAAFServer.cpp
    com-dll/CAAFUnknown.cpp
)

target_include_directories(comapi PRIVATE
    ${AAFSDK_ROOT}/ref-impl/include
    ${AAFSDK_ROOT}/ref-impl/include/ref-api
    ${AAFSDK_ROOT}/ref-impl/plugins
    ${AAFSDK_ROOT}/ref-impl/src/com-api
    ${AAFSDK_ROOT}/ref-impl/src/com-api/com-dll
    ${AAFSDK_ROOT}/ref-impl/src/impl
)

target_link_libraries(comapi PRIVATE
    Impl
    OM
    expat
    ss
)

target_compile_definitions(comapi PUBLIC -DAAFCOAPI)

if(MSVC)
    # does not work with cmake 3.0.2
    #target_sources(comapi PRIVATE "com-dll/AAFCOM.DEF")
    set_target_properties(comapi PROPERTIES LINK_FLAGS "/DEF:\"${CMAKE_CURRENT_LIST_DIR}/com-dll\\AAFCOM.DEF\"")
endif()

if(MSVC)
    # file description
    # internal name
    # file name
    target_generate_rc_file(comapi
        "Advanced Authoring Format API"
        "AAFCOAPI"
        "AAFCOAPI.dll"
    )
endif()

set_target_properties(comapi PROPERTIES
    MACOSX_RPATH ON
    NO_SONAME ON
    SOVERSION ${AAFSDK_VERSION_MAJOR}
    VERSION ${AAFSDK_VERSION_STRING}
)

set_target_properties(comapi PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${TARGET_DIR}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)

if(MSVC)
    set(TARGET_BINARY_NAME "AAFCOAPI")
else()
    set(TARGET_BINARY_NAME "com-api")
endif()

if(AAFSDK_DLL_VERSIONED)
    set(TARGET_BINARY_NAME "${TARGET_BINARY_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
endif()

set_target_properties(comapi PROPERTIES
    OUTPUT_NAME ${TARGET_BINARY_NAME}
    OUTPUT_NAME_DEBUG ${TARGET_BINARY_NAME}
    OUTPUT_NAME_RELEASE ${TARGET_BINARY_NAME}
)
