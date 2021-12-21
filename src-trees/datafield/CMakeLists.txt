# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
# Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com

cmake_minimum_required(VERSION 3.5.1)

# Set the CMake target name and files for this subdirectory
set(TARGET_NAME Datafield)

set(SOURCE_FILES
    src/account.cpp
    src/category.cpp 
    src/currency.cpp 
    src/date.cpp
)

set(INCLUDE_FILES
    include/account.h
    include/category.h
    include/currency.h
    include/date.h
    include/element.h
)

# Create a new target with the source and header files as dependencies
add_library("${TARGET_NAME}" STATIC "${SOURCE_FILES}" "${INCLUDE_FILES}")

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
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Specify libraries or flags to use when linking a given target and/or its dependents
target_link_libraries("${TARGET_NAME}"
)

# # Install the library
# install(TARGETS "${TARGET_NAME}" DESTINATION lib)
# install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_FILES} DESTINATION include)


## TESTING ##
set(TEST_TARGET_NAME "${TARGET_NAME}.test")

set(TEST_FILES
    test/datafield.test.cpp
)

# Create a new target with the source and header files as dependencies
add_executable("${TEST_TARGET_NAME}" ${TEST_FILES} ${SOURCE_FILES} ${INCLUDE_FILES})

# Specify include directories to use when compiling the given target
target_include_directories("${TEST_TARGET_NAME}"
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Specify libraries or flags to use when linking a given target and/or its dependents
target_link_libraries("${TEST_TARGET_NAME}"
    PUBLIC Ansi Csv
)

# Add build-in self test (BIST) to test list
add_test(NAME "${TARGET_NAME}-BIST" COMMAND Datafield.test)
