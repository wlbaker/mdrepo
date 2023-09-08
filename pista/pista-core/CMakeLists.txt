cmake_minimum_required( VERSION 2.6 )
project( Pista )

# The version number.
set (Pista_VERSION "bluebonnet-0" )
set (Pista_VERSION_MAJOR 1)
set (Pista_VERSION_MINOR 0)
set (Pista_VERSION_PATCH 1)

cmake_policy( SET CMP0054 NEW)
cmake_policy( SET CMP0057 NEW)

find_package( Doxygen REQUIRED )
set( DOXYGEN_GENERATE_HTML YES)
set( DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../doc/doxygen )

doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate Developer Docs"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# does this system provide the log and exp functions?
include (CheckFunctionExists)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/include/config.h.in"
  "${PROJECT_BINARY_DIR}/include/config.h"
  )

