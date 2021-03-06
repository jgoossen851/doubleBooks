# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
# Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com

# Set the header and source files for the library
set(HEADER_FILES
      include/category.h
      include/currency.h
      include/date.h
      include/element.h
)

set(SOURCE_FILES 
      src/category.cpp 
      src/currency.cpp 
      src/date.cpp
)


# Create a new library target
add_library(Datafield STATIC ${SOURCE_FILES}  ${HEADER_FILES})

# Specify external include directories
target_include_directories(Datafield
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Install the library
install(TARGETS Datafield DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_FILES} DESTINATION include)
