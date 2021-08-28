# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
# Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com

# Set other headers and sources not contained in libraries
set(HEADER_FILES
                ../include/ansi.h
                ../include/csv.h
                ../include/database.h
                ../include/format.h
                ../include/strings.h
                ../include/table.h
                ../include/transaction.h
)
set(SOURCE_FILES 
                ${PROJECT_SOURCE_DIR}/src/ansi.cpp
                ${PROJECT_SOURCE_DIR}/src/csv.cpp
                ${PROJECT_SOURCE_DIR}/src/database.cpp
                ${PROJECT_SOURCE_DIR}/src/strings.cpp
                ${PROJECT_SOURCE_DIR}/src/table.cpp
                ${PROJECT_SOURCE_DIR}/src/transaction.cpp
)


# Create the executable target with the project name
add_executable(${PROJECT_NAME} main.cpp ${HEADER_FILES} ${SOURCE_FILES})
# Set the output name of the binary executable
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "budget")

# Link the application to applicable libraries
target_link_libraries(${PROJECT_NAME} PUBLIC Datafield)

# Specify additional include directores
target_include_directories(${PROJECT_NAME} PUBLIC 
                              ../include
                              )

# Install the application
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/../${HEADER_FILES}
        DESTINATION include)
