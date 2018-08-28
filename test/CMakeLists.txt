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

project(MakeSDKTests LANGUAGES CXX)

add_subdirectory(com)

add_custom_target(MakeSDKTests ALL COMMENT "Building MakeSDKTests...")
add_dependencies(MakeSDKTests
    MakeSDK
    ComFileKindTest
    ComModTestAAF
    CreateSequence
    EssenceAccess
    MakeSDK
    #MetaModelVerification
    MultiGenTest
    OpenExistingModify
    ResultToTextTest
    ScaleTest
    UTF8FileNameTest
    XMLStoredFormat
)

if(WIN32)
    set(TEST_TARGET_DIR "${AAFSDK_TARGET_DIR}/Test")
    target_copy_files(MakeSDKTests "${AAFSDK_TARGET_DIR}/RefImpl" "${TEST_TARGET_DIR}" "AAFCOAPI.dll;AAFCOAPI.pdb")
    target_copy_files(MakeSDKTests "${AAFSDK_TARGET_DIR}/RefImpl/aafext" "${TEST_TARGET_DIR}/aafext" "AAFPGAPI.dll;AAFPGAPI.pdb")
    target_copy_files(MakeSDKTests "${AAFSDK_TARGET_DIR}/RefImpl/aafext" "${TEST_TARGET_DIR}/aafext" "AAFINTP.dll;AAFINTP.pdb")
endif()
