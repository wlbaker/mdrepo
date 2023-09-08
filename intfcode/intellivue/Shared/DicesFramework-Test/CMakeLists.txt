cmake_minimum_required(VERSION 2.8)

project(DicesFramework-Test)

# Locate libraries and headers for inclusion in our project
# see modules/FindRTIDDS.cmake
find_package(RTIDDS)

# see modules/FindDICESDIM.cmake
find_package(DICESDIM)

# see modules/FindPqxx.cmake
find_package(Pqxx)

# see modules/FindLog4CPlus.cmake
find_package(Log4CPlus)

# see modules/FindDicesFramework-Common.cmake
find_package(DicesFramework-Common)

# see modules/FindDicesFramework-Core.cmake
find_package(DicesFramework-Core)

# see modules/FindDicesFramework-Communication.cmake
find_package(DicesFramework-Communication)

# see modules/FindDicesFramework-Utilities.cmake
find_package(DicesFramework-Utilities)

# DIRECTORY SETTINGS
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/code)

file(GLOB_RECURSE SOURCES
  ${SOURCE_DIR}/*.cxx
)

file(GLOB_RECURSE HEADERS
  ${SOURCE_DIR}/*.h
)

set(PROJECTS "")
foreach(F ${HEADERS})
  get_filename_component(PATH ${F} DIRECTORY)
  list(APPEND PROJECTS ${PATH})
endforeach()
list(REMOVE_DUPLICATES PROJECTS)

set(SOURCES_HEADERS
  ${SOURCES}
  ${HEADERS}
)

include_directories(
  ${RTIDDS_INCLUDE_DIRS}
  ${DICESDIM_INCLUDE_DIRS}
  ${Pqxx_INCLUDE_DIRS}
  ${DICESFRAMEWORK_COMMON_INCLUDE_DIRS}
  ${DICESFRAMEWORK_CORE_INCLUDE_DIRS}
  ${DICESFRAMEWORK_COMMUNICATION_INCLUDE_DIRS}
  ${DICESFRAMEWORK_UTILITIES_INCLUDE_DIRS}
  ${PROJECTS}
  ${Log4CPlus_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS} -Wno-deprecated")

# RTIDDS package has some definitions we must pass to the compiler
# These would look like -DVARIABLE=X in a gcc call
add_definitions(${RTIDDS_DEFINES})

# DECLARE OUTPUT TYPE
add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCES_HEADERS})

target_link_libraries(${CMAKE_PROJECT_NAME}
  ${RTIDDS_LIBS}
  ${DICESDIM_LIBS}
  ${Pqxx_LIBS}
  ${DICESFRAMEWORK_COMMON_LIBS}
  ${DICESFRAMEWORK_CORE_LIBS}
  ${DICESFRAMEWORK_COMMUNICATION_LIBS}
  ${DICESFRAMEWORK_UTILITES_LIBS}
  ${Log4CPlus_LIBS}
)

# INSTALL
install(
  DIRECTORY "${SOURCE_DIR}/"
  DESTINATION include/${CMAKE_PROJECT_NAME}/Test
  COMPONENT headers
  PATTERN "src" EXCLUDE
)

install(TARGETS ${CMAKE_PROJECT_NAME}
  LIBRARY DESTINATION lib
  COMPONENT library)
