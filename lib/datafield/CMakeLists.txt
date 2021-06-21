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

# # Install the library
# install(TARGETS Datafield DESTINATION lib)
# install(FILES ${HEADER_FILES} DESTINATION include)
