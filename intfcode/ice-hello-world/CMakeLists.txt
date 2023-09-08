# This file instructs CMake on what build steps to take,
#  what files to operate on, where to install, etc.

# Call CMake as follows to build the project
# cmake -DCMAKE_MODULE_PATH=.

cmake_minimum_required (VERSION 3.5)
project (helloworld)

# Locate libraries and headers for inclusion in our project
# see modules/FindRTIDDS.cmake
find_package(RTIDDS)

# Set a variable with the location of our source files
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(IDL_DIR ${PROJECT_SOURCE_DIR}/idl)
set(IDL_SOURCE_DIR ${CMAKE_BINARY_DIR}/src_dds)
file(MAKE_DIRECTORY ${IDL_SOURCE_DIR})

file(GLOB SOURCES ${SOURCE_DIR}/*.cxx)
file(GLOB IDL_FILES ${IDL_DIR}/*.idl)

foreach(idl_file ${IDL_FILES})
  get_filename_component(idl ${idl_file} NAME_WE)
  set(sources
    ${IDL_SOURCE_DIR}/${idl}.cxx
    ${IDL_SOURCE_DIR}/${idl}Plugin.cxx
    ${IDL_SOURCE_DIR}/${idl}Support.cxx
  )

  add_custom_command(OUTPUT ${sources}
    COMMAND $ENV{NDDSHOME}/bin/rtiddsgen -I ${IDL_DIR} -namespace -language C++ -replace -d ${IDL_SOURCE_DIR} ${idl_file}
    WORKING_DIRECTORY ${CURRENT_BINARY_DIR}
    DEPENDS ${idl_file}
    COMMENT "Compiling ${idl_file}" VERBATIM
  )
  set(IDL_SOURCES ${IDL_SOURCES} ${sources})
endforeach(idl_file)

set_source_files_properties(${IDL_SOURCES} PROPERTIES GENERATED TRUE)

include_directories(
  ${RTIDDS_INCLUDE_DIRS}
  ${SOURCE_DIR}
  ${IDL_SOURCE_DIR}
)

# RTIDDS package has some definitions we must pass to the compiler
# These would look like -DVARIABLE=X in a gcc call
# Enable C++11 features for gcc
# Silence warnings, this is demo code!
add_definitions(
  ${RTIDDS_DEFINES}
  -std=c++11
  -Wno-write-strings
)

# CMake will create a binary from the program sources
add_executable(${CMAKE_PROJECT_NAME}
  ${SOURCES}
  ${IDL_SOURCES}
)

# CMake will link the needed libraries to the executable
target_link_libraries(${CMAKE_PROJECT_NAME}
  ${RTIDDS_LIBS}
)
