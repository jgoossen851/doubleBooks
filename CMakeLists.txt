# Set the CMake version required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project (Budget VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_CXX_EXTENSIONS OFF)

# Set the relative output directory for the compiled binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Add subdirectories for other libraries
add_subdirectory(lib)

# Add the subdirectory containg the main executable target
add_subdirectory(app)

# # Install the application
# install(TARGETS App DESTINATION bin)
# install(FILES "${PROJECT_BINARY_DIR}/${HEADER_FILES}"
#         DESTINATION include)
