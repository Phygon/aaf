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

# MSVC: ./AAFWinSDK/<vsXX>/ref-impl/Impl/<Win32|x64>/<Debug|Release>/
# Makefile: ./AAFx86_64LinuxSDK/g++/ref-impl/<debug|>
set(TARGET_DIR "${AAFSDK_TARGET_DIR}")

add_library(Impl STATIC
    ${AAFSDK_ROOT}/ref-impl/aaflib/aaflibwin32.cpp
    aafErr.cpp
    AAFObjectModel.cpp
    AAFObjectModelProcs.cpp
    aafTable.cpp
    AAFUtils.cpp
    ImplAAFAES3PCMDescriptor.cpp
    ImplAAFAIFCDescriptor.cpp
    ImplAAFAsyncStreamRawStorage.cpp
    ImplAAFAudioChannelLabelSubDescriptor.cpp
    ImplAAFAuxiliaryDescriptor.cpp
    ImplAAFAVCSubDescriptor.cpp
    ImplAAFTypeDefGenericCharacter.cpp
    ImplAAFBaseClassFactory.cpp
    ImplAAFBuiltinClasses.cpp
    ImplAAFBuiltinTypes.cpp
    ImplAAFBWFImportDescriptor.cpp
    ImplAAFCachePageAllocator.cpp
    ImplAAFCDCIDescriptor.cpp
    ImplAAFClassDef.cpp
    ImplAAFClientDiagnostics.cpp
    ImplAAFCodecDef.cpp
    ImplAAFCommentMarker.cpp
    ImplAAFComponent.cpp
    ImplAAFCompositionMob.cpp
    ImplAAFConstantValue.cpp
    ImplAAFContainerDef.cpp
    ImplAAFContentStorage.cpp
    ImplAAFContext.cpp
    ImplAAFControlPoint.cpp
    ImplAAFDataDef.cpp
    ImplAAFDataEssenceDescriptor.cpp
    ImplAAFDefObject.cpp
    ImplAAFDescriptiveClip.cpp
    ImplAAFDescriptiveFramework.cpp
    ImplAAFDescriptiveMarker.cpp
    ImplAAFDescriptiveObject.cpp
    ImplAAFDictionary.cpp
    ImplAAFDigitalImageDescrip.cpp
    ImplAAFDMS1Builtins.cpp
    ImplAAFEdgecode.cpp
    ImplAAFEssenceAccess.cpp
    ImplAAFEssenceData.cpp
    ImplAAFEssenceDescriptor.cpp
    ImplAAFEssenceFormat.cpp
    ImplAAFEssenceGroup.cpp
    ImplAAFEssencePlugin.cpp
    ImplAAFEvent.cpp
    ImplAAFEventMobSlot.cpp
    ImplAAFFile.cpp
    ImplAAFFileDescriptor.cpp
    ImplAAFFileEncoding.cpp
    ImplAAFFiller.cpp
    ImplAAFFilmDescriptor.cpp
    ImplAAFFindSourceInfo.cpp
    ImplAAFGetFileBits.cpp
    ImplAAFGPITrigger.cpp
    ImplAAFGroupOfSoundfieldGroupsLabelSubDescriptor.cpp
    ImplAAFHeader.cpp
    ImplAAFHTMLClip.cpp
    ImplAAFHTMLDescriptor.cpp
    ImplAAFIdentification.cpp
    ImplAAFImportDescriptor.cpp
    ImplAAFInterpolationDef.cpp
    ImplAAFIOCompletion.cpp
    ImplAAFJPEG2000SubDescriptor.cpp
    ImplAAFKLVData.cpp
    ImplAAFKLVDataDefinition.cpp
    ImplAAFLocator.cpp
    ImplAAFMasterMob.cpp
    ImplAAFMCALabelSubDescriptor.cpp
    ImplAAFMetaDefinition.cpp
    ImplAAFMetaDictionary.cpp
    ImplAAFMob.cpp
    ImplAAFMobSlot.cpp
    ImplAAFModule.cpp
    ImplAAFMPEG4VisualSubDescriptor.cpp
    ImplAAFMPEGAudioDescriptor.cpp
    ImplAAFMPEGVideoDescriptor.cpp
    ImplAAFMultipleDescriptor.cpp
    ImplAAFNestedScope.cpp
    ImplAAFNetworkLocator.cpp
    ImplAAFObject.cpp
    ImplAAFOMCachePageAllocator.cpp
    ImplAAFOMRawStorage.cpp
    ImplAAFOperationDef.cpp
    ImplAAFOperationGroup.cpp
    ImplAAFParameter.cpp
    ImplAAFParameterDef.cpp
    ImplAAFPCMDescriptor.cpp
    ImplAAFPhysicalDescriptor.cpp
    ImplAAFPlainEssenceData.cpp
    ImplAAFPlainStreamData.cpp
    ImplAAFPluginDef.cpp
    ImplAAFPluginFile.cpp
    ImplAAFPluginManager.cpp
    ImplAAFProperty.cpp
    ImplAAFPropertyDef.cpp
    ImplAAFPropertyValue.cpp
    ImplAAFPropValData.cpp
    ImplAAFPulldown.cpp
    ImplAAFRandomFile.cpp
    ImplAAFRandomRawStorage.cpp
    ImplAAFRawStorage.cpp
    ImplAAFRecordingDescriptor.cpp
    ImplAAFRefArrayValue.cpp
    ImplAAFRefContainerValue.cpp
    ImplAAFRefSetValue.cpp
    ImplAAFRefValue.cpp
    ImplAAFRGBADescriptor.cpp
    ImplAAFRIFFChunk.cpp
    ImplAAFRoot.cpp
    ImplAAFScopeReference.cpp
    ImplAAFSegment.cpp
    ImplAAFSelector.cpp
    ImplAAFSequence.cpp
    ImplAAFSetFileBits.cpp
    ImplAAFSoundDescriptor.cpp
    ImplAAFSoundfieldGroupLabelSubDescriptor.cpp
    ImplAAFSourceClip.cpp
    ImplAAFSourceMob.cpp
    ImplAAFSourceReference.cpp
    ImplAAFStaticMobSlot.cpp
    ImplAAFStorable.cpp
    ImplAAFStreamPropertyValue.cpp
    ImplAAFStreamRawStorage.cpp
    ImplAAFStrongRefArrayValue.cpp
    ImplAAFStrongRefSetValue.cpp
    ImplAAFStrongRefValue.cpp
    ImplAAFSubDescriptor.cpp
    ImplAAFTaggedValue.cpp
    ImplAAFTaggedValueDefinition.cpp
    ImplAAFTaggedValueUtil.cpp
    ImplAAFTapeDescriptor.cpp
    ImplAAFTextClip.cpp
    ImplAAFTextLocator.cpp
    ImplAAFTIFFDescriptor.cpp
    ImplAAFTimecode.cpp
    ImplAAFTimecodeStream.cpp
    ImplAAFTimecodeStream12M.cpp
    ImplAAFTimelineMobSlot.cpp
    ImplAAFTransition.cpp
    ImplAAFTypeDef.cpp
    ImplAAFTypeDefArray.cpp
    ImplAAFTypeDefCharacter.cpp
    ImplAAFTypeDefEnum.cpp
    ImplAAFTypeDefExtEnum.cpp
    ImplAAFTypeDefFixedArray.cpp
    ImplAAFTypeDefIndirect.cpp
    ImplAAFTypeDefInt.cpp
    ImplAAFTypeDefObjectRef.cpp
    ImplAAFTypeDefOpaque.cpp
    ImplAAFTypeDefRecord.cpp
    ImplAAFTypeDefRename.cpp
    ImplAAFTypeDefSet.cpp
    ImplAAFTypeDefStream.cpp
    ImplAAFTypeDefString.cpp
    ImplAAFTypeDefStrongObjRef.cpp
    ImplAAFTypeDefVariableArry.cpp
    ImplAAFTypeDefWeakObjRef.cpp
    ImplAAFVaryingValue.cpp
    ImplAAFWAVEDescriptor.cpp
    ImplAAFWeakRefArrayValue.cpp
    ImplAAFWeakRefSetValue.cpp
    ImplAAFWeakRefValue.cpp
    ImplEnumAAFClassDefs.cpp
    ImplEnumAAFCodecDefs.cpp
    ImplEnumAAFCodecFlavours.cpp
    ImplEnumAAFComponents.cpp
    ImplEnumAAFContainerDefs.cpp
    ImplEnumAAFControlPoints.cpp
    ImplEnumAAFDataDefs.cpp
    ImplEnumAAFEssenceData.cpp
    ImplEnumAAFFileEncodings.cpp
    ImplEnumAAFIdentifications.cpp
    ImplEnumAAFInterpolateDefs.cpp
    ImplEnumAAFKLVData.cpp
    ImplEnumAAFKLVDataDefs.cpp
    ImplEnumAAFLoadedPlugins.cpp
    ImplEnumAAFLocators.cpp
    ImplEnumAAFMobs.cpp
    ImplEnumAAFMobSlots.cpp
    ImplEnumAAFOperationDefs.cpp
    ImplEnumAAFParameterDefs.cpp
    ImplEnumAAFParameters.cpp
    ImplEnumAAFPluginDefs.cpp
    ImplEnumAAFPluginLocators.cpp
    ImplEnumAAFProperties.cpp
    ImplEnumAAFPropertyDefs.cpp
    ImplEnumAAFPropertyValues.cpp
    ImplEnumAAFSegments.cpp
    ImplEnumAAFStorablePropVals.cpp
    ImplEnumAAFTaggedValueDefs.cpp
    ImplEnumAAFTaggedValues.cpp
    ImplEnumAAFTypeDefs.cpp
)

target_include_directories(Impl PUBLIC
    ${AAFSDK_ROOT}/ref-impl/include
    ${AAFSDK_ROOT}/ref-impl/include/ref-api
)

target_include_directories(Impl PRIVATE
    ${AAFSDK_ROOT}/ref-impl/aaflib
    ${AAFSDK_ROOT}/ref-impl/src/Impl
    ${AAFSDK_ROOT}/ref-impl/include/OM
    ${AAFSDK_ROOT}/ref-impl/src/OM
)

target_link_libraries(Impl PRIVATE
    OM
    AAFLIB
)

target_compile_definitions(Impl PRIVATE
    XML_STATIC
    $<$<CONFIG:Debug>:OM_STACK_TRACE_ON_ASSERT>
    $<$<CONFIG:Debug>:OM_DEBUG>
    AAFSDK_VERSION_MAJOR=${AAFSDK_VERSION_MAJOR}
    AAFSDK_VERSION_MINOR=${AAFSDK_VERSION_MINOR}
    AAFSDK_VERSION_PATCH=${AAFSDK_VERSION_PATCH}
    AAFSDK_VERSION_BUILD=${AAFSDK_VERSION_BUILD}
    AAFSDK_VERSION_RELEASE=${AAFSDK_VERSION_RELEASE}
)

if(NOT AAF_NO_STRUCTURED_STORAGE)
    target_compile_definitions(Impl PRIVATE OM_STRUCTURED_STORAGE)
    if(WIN32)
        target_compile_definitions(Impl PRIVATE OM_USE_WINDOWS_SS OM_USE_STORAGE_EX)
    else()
        target_compile_definitions(Impl PRIVATE OM_USE_SCHEMASOFT_SS)
    endif()
else()
    target_compile_definitions(Impl PRIVATE OM_NO_STRUCTURED_STORAGE)
endif()

set_target_properties(Impl PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_DIR}
)

set_target_properties(Impl PROPERTIES
    OUTPUT_NAME "impl"
    OUTPUT_NAME_DEBUG "impl"
    OUTPUT_NAME_RELEASE "impl"
)
