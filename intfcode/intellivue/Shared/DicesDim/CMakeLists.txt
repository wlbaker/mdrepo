# This file instructs CMake on what build steps to take,
#  what files to operate on, where to install, etc.

cmake_minimum_required (VERSION 2.8)
project (dicesdim)

# Locate libraries and headers for inclusion in our project
# see cmake/FindRTIDDS.cmake
find_package(RTIDDS)

set (DICES_DIM_DIR ${PROJECT_SOURCE_DIR}/idl)

file(GLOB DICES_DIM_IDL ${DICES_DIM_DIR}/*.idl)

set (SOURCE_DIR ${CMAKE_BINARY_DIR}/src_dds)
file(MAKE_DIRECTORY ${SOURCE_DIR})

macro(rtiddsgen)
  foreach(_idl_file ${ARGN})
    get_filename_component(_idl ${_idl_file} NAME_WE)
    set(_sources
      ${SOURCE_DIR}/${_idl}.cxx
      ${SOURCE_DIR}/${_idl}Plugin.cxx
      ${SOURCE_DIR}/${_idl}Support.cxx
    )
    set(_headers
    ${SOURCE_DIR}/${_idl}.h
    ${SOURCE_DIR}/${_idl}Plugin.h
    ${SOURCE_DIR}/${_idl}Support.h)

    add_custom_command(OUTPUT ${_sources}
      COMMAND rtiddsgen -I ${DICES_DIM_DIR} -namespace -language C++ -replace -d ${SOURCE_DIR} ${_idl_file}
      WORKING_DIRECTORY ${CURRENT_BINARY_DIR}
      DEPENDS ${_idl_file}
      COMMENT "Compiling ${_idl_file}" VERBATIM)
    set(SOURCES ${SOURCES} ${_sources})
    set(HEADERS ${HEADERS} ${_headers})
  endforeach(_idl_file)
endmacro(rtiddsgen)

rtiddsgen(${DICES_DIM_IDL})

# Automatically find needed header files in these directories
# SYSTEM headers won't produce compiler warnings
include_directories(SYSTEM
  ${RTIDDS_INCLUDE_DIRS}
)

include_directories(
  ${SOURCE_DIR}
)

# RTIDDS package has some definitions we must pass to the compiler
# These would look like -DVARIABLE=X in a gcc call
# Enable C++11 features for gcc 4.6.3
# Enable warnings of all types
# Supress unused var/param, because OF COURSE these variables are unused!
add_definitions(${RTIDDS_DEFINES} -std=c++11 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-deprecated)

# CMake will create a library
add_library(${CMAKE_PROJECT_NAME} SHARED
  ${SOURCES}
)

# CMake will link the needed libraries to the executable
target_link_libraries(${CMAKE_PROJECT_NAME} 
  ${RTIDDS_LIBS}
)

# Configure where application and files get installed
#  Defaults to /usr/local
#  Customize by providing cmake -DCMAKE_INSTALL_PREFIX=???
# 'make install'
install(TARGETS ${CMAKE_PROJECT_NAME}
  LIBRARY DESTINATION lib
  COMPONENT library)
install(FILES ${HEADERS} 
  DESTINATION include/${CMAKE_PROJECT_NAME}
  COMPONENT headers)
