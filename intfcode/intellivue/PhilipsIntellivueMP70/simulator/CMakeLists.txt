# This file instructs CMake on what build steps to take,
#  what files to operate on, where to install, etc.
# cmake ../cmake -DCMAKE_INSTALL_PREFIX=/opt/DocBoxInc/

# Debug builds can be specified by passing cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required (VERSION 2.8)
project (ds-philips-intellivue-mp70)

# Locate libraries and headers for inclusion in our project
# see modules/FindRTIDDS.cmake
find_package(RTIDDS)

# see modules/FindLog4CPlus.cmake
find_package(Log4CPlus)

# see modules/FindDICESDIM.cmake
find_package(DICESDIM)

# see modules/FindDicesFramework-Common.cmake
find_package(DicesFramework-Common)

# see modules/FindDicesFramework-Core.cmake
find_package(DicesFramework-Core)

# see modules/FindDicesFramework-Communication.cmake
find_package(DicesFramework-Communication)

# see modules/FindDicesFramework-Utilities.cmake
find_package(DicesFramework-Utilities)

# see modules/FindDicesFramework-Test.cmake
find_package(DicesFramework-Test)

# Set a variable with the location of our source files
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# Automatically find needed header files in these directories
include_directories(
  ${SOURCE_DIR}
  ${DICESDIM_INCLUDE_DIRS}
  ${RTIDDS_INCLUDE_DIRS}
  ${Log4CPlus_INCLUDE_DIRS}
  ${DBX_FOUND_DIRS}
)

# Create a list of source files
# Notice that we do not explicitly list header files
# CMake automatically finds them in the include directories for us!
set(SOURCES
  ${SOURCE_DIR}/ds_philips_intellivue_mp70.cxx
  ${SOURCE_DIR}/philips_intellivue_mp70_simulator.cxx
  ${SOURCE_DIR}/intellivue_serial.cxx
  ${SOURCE_DIR}/intellivue_utils.cxx
)

# RTIDDS package has some definitions we must pass to the compiler
# These would look like -DVARIABLE=X in a gcc call
add_definitions(${RTIDDS_DEFINES} -std=c++11 -gdwarf-2)

# CMake will create a binary from the ICE and program sources
add_executable(${CMAKE_PROJECT_NAME}
  ${SOURCES}
)

# CMake will link the needed libraries to the executable
target_link_libraries(${CMAKE_PROJECT_NAME}
  ${RTIDDS_LIBS}
  ${DICESDIM_LIBS}
  ${Log4CPlus_LIBS}
  ${DBX_FOUND_LIBS}
)

# Copy config files to build directory
file(COPY ${PROJECT_SOURCE_DIR}/config/log4cplus.properties
  DESTINATION ${CMAKE_BINARY_DIR})

# Configure where application and files get installed
#  Defaults to /usr/local
#  Customize by providing cmake arg -DCMAKE_INSTALL_PREFIX=???
# 'make install'
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/log4cplus.properties 
  DESTINATION ${CMAKE_PROJECT_NAME})

    set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "dicesdim")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://www.docboxinc.com")
set(CPACK_PACKAGE_DESCRIPTION "Intellivue Driver Sim")
set(CPACK_PACKAGE_CONTACT "Jereme Lamothe jlamothe@docboxinc.com")
set(CPACK_DEBIAN_PACKAGE_MANAGER "Jereme Lamothe")
set(CPACK_PACKAGE_VENDOR "DocBox Inc")
set(CPACK_PACKAGE_VERSION_MAJOR "$ENV{VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "$ENV{VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "$ENV{VERSION_BUILD}")
# Absolute paths in CMAKE_INSTALL_PREFIX confuse Debian packaging
# We tell CPack to trust that /opt/DocBoxInc/ isn't a crazy thing
set(CPACK_SET_DESTDIR true)
INCLUDE(CPack)

