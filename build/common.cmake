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

set(AAFSDK_VERSION_STRING "${AAFSDK_VERSION_MAJOR}.${AAFSDK_VERSION_MINOR}.${AAFSDK_VERSION_PATCH}.${AAFSDK_VERSION_BUILD}")

function(target_copy_files target src dst files)
    foreach(file ${files})
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${src}/${file}" "${dst}/${file}"
            DEPENDS "${src}/${file}"
        )
    endforeach()
endfunction()

function(target_generate_rc_file target
    file_description
    internal_name
    file_name
)
    set(AAFSDK_RC_COMMENTS ${AAFSDK_LEGAL_COMMENTS})
    set(AAFSDK_RC_COMPANYNAME ${AAFSDK_LEGAL_COMPANY})
    set(AAFSDK_RC_COPYRIGHT ${AAFSDK_LEGAL_COPYRIGHT})
    set(AAFSDK_RC_FILEDESCRIPTION ${file_description})
    set(AAFSDK_RC_FILENAME ${file_name})
    set(AAFSDK_RC_INTERNALNAME ${internal_name})
    set(AAFSDK_RC_PRODUCTNAME ${AAFSDK_LEGAL_PRODUCT})
    set(AAFSDK_RC_TRADEMARKS ${AAFSDK_LEGAL_TRADEMARKS})
    set(AAFSDK_RC_VERSION_STR ${AAFSDK_VERSION_STRING})
    configure_file("${AAFSDK_ROOT}/build/versioninfo.rc.in" "${CMAKE_CURRENT_BINARY_DIR}/${target}.rc")
    target_sources(${target} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/${target}.rc")
endfunction()
