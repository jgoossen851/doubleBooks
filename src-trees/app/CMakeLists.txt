# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
# Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com

cmake_minimum_required(VERSION 3.5.1)

# Set the CMake target name and files for this subdirectory
set(TARGET_NAME ${PROJECT_NAME})

set(SOURCE_FILES
    src/main.cpp
)

configure_file(include/version.h.in ${PROJECT_BINARY_DIR}/include/version.h)

set(INCLUDE_FILES
    ${PROJECT_BINARY_DIR}/include/version.h
)

# Create a new target with the source and header files as dependencies
add_executable("${TARGET_NAME}" ${SOURCE_FILES} ${INCLUDE_FILES})

# Set the output name of the binary executable
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "doublebooks")

# The keywords PUBLIC, PRIVATE, and INTERFACE are used for both Include
# Directories and Link Libraries.
# * PUBLIC means that other libraries including or linking thistarget should
#   also include or link the listed directory.
# * PRIVATE means that this target must include or link the directory while
#   other libraries including or linking this target do not.
# * INTERFACE means that other libraries including or linking this target
#   should include or link the listed directory while this target does not.

# Specify include directories to use when compiling the given target
target_include_directories("${TARGET_NAME}"
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_BINARY_DIR}/include
)

# Specify libraries or flags to use when linking a given target and/or its dependents
target_link_libraries("${TARGET_NAME}"
    PRIVATE Datafield Ansi Misc
)

# If install target is built, create a local installation of target
install(TARGETS "${TARGET_NAME}" DESTINATION bin)
# install(FILES ${PATH_TO_INCLUDE_FILES}
#         DESTINATION include)
