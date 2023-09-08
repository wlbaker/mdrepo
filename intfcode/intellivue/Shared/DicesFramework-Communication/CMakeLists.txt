cmake_minimum_required(VERSION 2.8)

project(DicesFramework-Communication)

## PACKAGE
# Locate libraries and headers for inclusion in our project
# > modules/FindDicesFramework-Common.cmake
find_package(DicesFramework-Common)

find_package(Log4CPlus)

## DIRECTORY/FILE SETTINGS
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/code)

set(INSTALL_HEADER_DIR ${SOURCE_DIR}/)
set(INSTALL_HEADER_DEST include/${CMAKE_PROJECT_NAME}/Communication)

set(INSTALL_LIB_TARGET ${CMAKE_PROJECT_NAME})
set(INSTALL_LIB_DEST lib)

file(GLOB_RECURSE SOURCES
  ${SOURCE_DIR}/*.cxx
)

file(GLOB_RECURSE HEADERS
  ${SOURCE_DIR}/*.h
)

set(SOURCES_HEADERS
  ${SOURCES}
  ${HEADERS}
)

set(INCLUDE_DIRS "")
foreach(F ${HEADERS})
  get_filename_component(PATH ${F} DIRECTORY)
  list(APPEND INCLUDE_DIRS ${PATH})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

include_directories(
  ${INCLUDE_DIRS}
  ${DBX_FOUND_DIRS}
  ${Log4CPlus_INCLUDE_DIRS}
)

## OUTPUT
# Configure
set(CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS} -Wno-deprecated")

add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCES_HEADERS})

# Link
target_link_libraries(${CMAKE_PROJECT_NAME}
  ${DBX_FOUND_LIBS}
  ${Log4CPlus_LIBS}
)

## INSTALL
# Header
install(
  DIRECTORY ${INSTALL_HEADER_DIR}
  DESTINATION ${INSTALL_HEADER_DEST}
  COMPONENT headers
  PATTERN "src" EXCLUDE
)

# Library
install(TARGETS ${INSTALL_LIB_TARGET}
  LIBRARY DESTINATION ${INSTALL_LIB_DEST}
  COMPONENT library)
