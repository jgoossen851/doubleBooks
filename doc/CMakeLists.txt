cmake_minimum_required(VERSION 3.9)

# Find the Doxygen package
# Require dot, treat the other components as optional
find_package(Doxygen
             REQUIRED dot
             OPTIONAL_COMPONENTS mscgen dia)

# Add Doxygen documentation
# set(DOXYGEN_USE_STAMP_FILE YES) # CMake 3.16
set(DOXYGEN_SOURCE_BROWSER  YES)
set(DOXYGEN_FULL_PATH_NAMES NO)
set(DOXYGEN_CASE_SENSE_NAMES        NO)
set(DOXYGEN_SHOW_GROUPED_MEMB_INC   YES)
set(DOXYGEN_QUIET YES)
set(DOXYGEN_WARN_NO_PARAMDOC YES)
set(DOXYGEN_EXCLUDE_PATTERNS 
    "${PROJECT_SOURCE_DIR}/exogenous/*"
    "${PROJECT_SOURCE_DIR}/examples/*"
    "${PROJECT_SOURCE_DIR}/tools/*"
)
set(DOXYGEN_IMAGE_PATH
    "${PROJECT_SOURCE_DIR}/res/images/"
)
set(DOXYGEN_REFERENCED_BY_RELATION YES)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_PROJECT_LOGO "${PROJECT_SOURCE_DIR}/res/logos/logo.png")

# Attempt to generate as much documentation as possible (for development)
set(DOXYGEN_EXTRACT_ALL     YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN_EXTRACT_PACKAGE YES)
set(DOXYGEN_EXTRACT_STATIC  YES)
set(DOXYGEN_EXTRACT_LOCAL_CLASSES YES)
#set(DOXYGEN_INTERNAL_DOCS YES)

doxygen_add_docs(
    docs
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate documentation"
)
