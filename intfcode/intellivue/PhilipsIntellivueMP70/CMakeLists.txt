# This file instructs CMake on what build steps to take,
#  what files to operate on, where to install, etc.

cmake_minimum_required(VERSION 2.8)
project(dd-philips-intellivue-mp70)

# Locate libraries and headers for inclusion in our project
# see modules/FindRTIDDS.cmake
find_package(RTIDDS)

# see modules/FindLog4CPlus.cmake
find_package(Log4CPlus)

# see modules/FindDICESDIM.cmake
find_package(DICESDIM)

# see modules/FindPqxx.cmake
find_package(Pqxx)

# see modules/FindDicesFramework-Common.cmake
find_package(DicesFramework-Common)

# see modules/FindDicesFramework-Core.cmake
find_package(DicesFramework-Core)

# see modules/FindDicesFramework-Communication.cmake
find_package(DicesFramework-Communication)

# see modules/FindDicesFramework-Utilities.cmake
find_package(DicesFramework-Utilities)

# see modules/FindDicesFramework-Deprecated.cmake
find_package(DicesFramework-Deprecated)

# Set a variable with the location of our source files
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# Toolbox
set(TOOLBOX_DIR ../Shared)

# Toolbox Nomenclature
set(TOOLBOX_NOMENCLATURE_DIR ${TOOLBOX_DIR}/Nomenclature)

# Automatically find needed header files in these directories
include_directories(
  ${SOURCE_DIR}
  ${DICESDIM_INCLUDE_DIRS}
  ${RTIDDS_INCLUDE_DIRS}
  ${Log4CPlus_INCLUDE_DIRS}
  ${DBX_FOUND_DIRS}
  ${TOOLBOX_NOMENCLATURE_DIR}
  ${Pqxx_INCLUDE_DIRS}
)

file(GLOB CXX_SRC ${SOURCE_DIR}/*.cxx)

# Create a list of source files
# Notice that we do not explicitly list header files
# CMake automatically finds them in the include directories for us!
set(SOURCES
  ${CXX_SRC}
)

# RTIDDS package has some definitions we must pass to the compiler
# These would look like -DVARIABLE=X in a gcc call
add_definitions(${RTIDDS_DEFINES} -std=c++11 -gdwarf-2 -Wno-deprecated)

# CMake will create a binary from the ICE and program sources
add_executable(${CMAKE_PROJECT_NAME}
  ${SOURCES}
)

# CMake will link the needed libraries to the executable
target_link_libraries(${CMAKE_PROJECT_NAME}
  ${RTIDDS_LIBS}
  ${DICESDIM_LIBS}
  ${Log4CPlus_LIBS}
  ${Pqxx_LIBS}
  ${DBX_FOUND_LIBS}
)

# Copy config files to build directory
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
file(REMOVE log4cplus.properties)
file(COPY ${PROJECT_SOURCE_DIR}/config/log4cplus.properties.debug
  DESTINATION ${CMAKE_BINARY_DIR})
file(RENAME ${CMAKE_BINARY_DIR}/log4cplus.properties.debug
  ${CMAKE_BINARY_DIR}/log4cplus.properties)
else (CMAKE_BUILD_TYPE STREQUAL "Release")
file(REMOVE log4cplus.properties)
file(COPY ${PROJECT_SOURCE_DIR}/config/log4cplus.properties.release
  DESTINATION ${CMAKE_BINARY_DIR})
file(RENAME ${CMAKE_BINARY_DIR}/log4cplus.properties.release
  ${CMAKE_BINARY_DIR}/log4cplus.properties)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

file(COPY ${PROJECT_SOURCE_DIR}/config/dd_philips_intellivue_mp70.ini
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/config/association_request_cfg.ini
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/config/rtsa_priority_list.ini
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/config/QoS.xml
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/config/DicesBaseDriverConfig.xml
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/db/createdb.sh
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/db/MP70db.sql
  DESTINATION ${CMAKE_BINARY_DIR})

# Configure where application and files get installed
#  Defaults to /usr/local
#  Customize by providing cmake arg -DCMAKE_INSTALL_PREFIX=???
# 'make install'
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME
  DESTINATION bin)
install(FILES ${CMAKE_BINARY_DIR}/log4cplus.properties
  DESTINATION etc/config/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/dd_philips_intellivue_mp70.ini
  DESTINATION etc/config/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/association_request_cfg.ini
  DESTINATION etc/config/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/rtsa_priority_list.ini
  DESTINATION etc/config/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/DicesBaseDriverConfig.xml
  DESTINATION etc/config/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/createdb.sh
  DESTINATION etc/db/${CMAKE_PROJECT_NAME}
  PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
install(FILES ${CMAKE_BINARY_DIR}/MP70db.sql
  DESTINATION etc/db/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/QoS.xml
  DESTINATION bin)
