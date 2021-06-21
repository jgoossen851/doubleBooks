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
                ../src/ansi.cpp
                ../src/csv.cpp
                ../src/database.cpp
                ../src/strings.cpp
                ../src/table.cpp
                ../src/transaction.cpp
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
