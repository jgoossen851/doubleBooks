# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
# Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com

# Set the CMake version required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project (Budget VERSION 1.0.1)

# Set platform independent compiler/linker flags
#   C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#   PIC does not depend on absolute address.
#   True by default for SHARED and MODULE library targets, otherwise False
set(CMAKE_POSITION_INDEPENDENT_CODE True)

# Set platform dependent compiler/linker flags
if (MSVC)
    # Warning level 4
    add_compile_options(/W4)
    # All warnings as errors
    #add_compile_options(/WX)
else()
    # Lots of warnings
    add_compile_options(-Wall -Wextra -pedantic)
    # All warnings as errors
    #add_compile_options(-Werror)
endif()

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

# Add icon from resources
add_subdirectory(res)


## TESTING ##
include(CTest)

# # does the application run?
# add_test(NAME Runs COMMAND Budget 25)

# # does the usage message work?
# add_test(NAME Usage COMMAND Budget)
# set_tests_properties(Usage
#   PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*name"
# )


## PACKAGING ##
# Create Package Installation Rules
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# Set the default files to exclude from the source distribution
set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\\\.svn/;/\\\\.bzr/;/\\\\.hg/;/\\\\.git/;\\\\.swp\$;\\\\.#;/#")
# Attempt to read regexes to ignore from the .gitignore
# Files are predominately ignored as desired
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/.gitignore" REGEX_OUT REGEX "^[^#]")
# Escape characters "." and "-"
string(REGEX REPLACE "([\\.\\-])" "\\\\\\\\\\1"
  REGEX_OUT "${REGEX_OUT}"
)
# Replace pattern "*" with ".*"
string(REGEX REPLACE "\\*" ".*"
  REGEX_OUT "${REGEX_OUT}"
)
list(APPEND CPACK_SOURCE_IGNORE_FILES "${REGEX_OUT}")

include(CPack)
