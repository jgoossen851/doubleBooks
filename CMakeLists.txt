# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
# Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com

# Set the CMake version required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project (Budget VERSION 1.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# After a normal build, we can specify the location of various outputs of the
# build. We put executables and static libraries inside the build directory in
# bin/ and lib/, respectively.
# see https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#output-artifacts
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")


# # add the external library subdirectories
# add_subdirectory(exogenous)

# add the library and executable subdirectories
add_subdirectory(src-trees)

# uninstall target (requires root)
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/res/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

# Add documentation
add_subdirectory(doc)


## TESTING ##
include(CTest)

# # does the application run?
# add_test(NAME Runs COMMAND Budget 25)

# # does the usage message work?
# add_test(NAME Usage COMMAND Budget)
# set_tests_properties(Usage
#   PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*name"
# )

include(CPack)
