
# Changes to FindDoxygen require 3.9.6 or later
cmake_minimum_required( VERSION 3.9.6 )

project( Pista )

# The version number.
set (Pista_VERSION_MAJOR 1)
set (Pista_VERSION_MINOR 0)

cmake_policy( SET CMP0054 NEW)
cmake_policy( SET CMP0057 NEW)

# configure a header file to pass some of the CMake settings
# to the source code

find_package( Doxygen REQUIRED dot )
set( DOXYGEN_GENERATE_HTML YES)
set( DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/doxygen )

doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}/../pista-core
    COMMENT "Generate Developer Docs"
)

message( STATUS "binary dir=${CMAKE_CURRENT_BINARY_DIR}" )
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.doxygen @ONLY)

