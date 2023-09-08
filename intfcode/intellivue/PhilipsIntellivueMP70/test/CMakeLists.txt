# This file instructs CMake on what build steps to take,
#  what files to operate on, where to install, etc.
# cmake ../cmake -DCMAKE_INSTALL_PREFIX=/opt/DocBoxInc/

# Debug builds can be specified by passing cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 2.8)
project(run_tests)

# Will eventually be determined by an environment variable
set(DOCBOX_PATH /opt/DocBoxInc/)

# This determines where we can locate modules for find_package and include
set(CMAKE_MODULE_PATH ${DOCBOX_PATH}/cmake/modules ${CMAKE_MODULE_PATH})

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

# see modules/FindDicesFramework-Test.cmake
find_package(DicesFramework-Test)

# Set a variable with the location of our source files
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/../src)

# Set a variable with the location of our source files
set(CONFIG_DIR ${PROJECT_SOURCE_DIR}/../config)

# Set a variable with the location of our test config files
set(TEST_CONFIG_DIR ${PROJECT_SOURCE_DIR}/config)

# Set a variable with the location of our testing files
set(TEST_DIR ${CMAKE_SOURCE_DIR}/src)

# Toolbox
set(TOOLBOX_DIR ../../../../Shared/Toolbox)

# Resources
set(RESOURCES_DIR ../../../../Shared/Resources)

# Toolbox Nomenclature
set(TOOLBOX_NOMENCLATURE_DIR ${TOOLBOX_DIR}/Nomenclature)

# Automatically find needed header files in these directories
include_directories(
  ${SOURCE_DIR}
  ${TEST_DIR}
  ${DICESDIM_INCLUDE_DIRS}
  ${RTIDDS_INCLUDE_DIRS}
  ${Log4CPlus_INCLUDE_DIRS}
  ${DBX_FOUND_DIRS}
  ${TOOLBOX_NOMENCLATURE_DIR}
  ${Pqxx_INCLUDE_DIRS}
)

# Create a list of source files
# Notice that we do not explicitly list header files
# CMake automatically finds them in the include directories for us!
set(SOURCES
  ${TEST_DIR}/main.cxx
  ${TEST_DIR}/intellivue_utils_unit_test.cxx
  ${TEST_DIR}/serial_converter_unit_test.cxx
  ${TEST_DIR}/intellivue_association_request_unit_test.cxx
  ${TEST_DIR}/intellivue_association_release_request_unit_test.cxx
  ${TEST_DIR}/intellivue_association_request_unit_test.cxx
  ${TEST_DIR}/intellivue_association_response_unit_test.cxx
  ${TEST_DIR}/dd_philips_intellivue_mp70_unit_test.cxx
  ${TEST_DIR}/ini_association_request_parser_unit_test.cxx
  ${TEST_DIR}/ini_dim_parser_unit_test.cxx
  ${TEST_DIR}/ini_rtsa_priority_list_parser_unit_test.cxx
  ${TEST_DIR}/intellivue_connect_indication_message_unit_test.cxx
  ${SOURCE_DIR}/dd_philips_intellivue_mp70.cxx
  ${SOURCE_DIR}/dd_philips_intellivue_mp70_parser.cxx
  ${SOURCE_DIR}/intellivue_association_request.cxx
  ${SOURCE_DIR}/intellivue_association_release_request.cxx
  ${SOURCE_DIR}/intellivue_association_response.cxx
  ${SOURCE_DIR}/intellivue_set_rtsa_priority_list_request.cxx
  ${SOURCE_DIR}/intellivue_extended_poll_request.cxx
  ${SOURCE_DIR}/intellivue_extended_poll_response.cxx
  ${SOURCE_DIR}/intellivue_single_poll_request.cxx
  ${SOURCE_DIR}/intellivue_single_poll_response.cxx
  ${SOURCE_DIR}/intellivue_connect_indication_message.cxx
  ${SOURCE_DIR}/intellivue_mds_create_event_result.cxx
  ${SOURCE_DIR}/intellivue_mds_create_event_report.cxx
  ${SOURCE_DIR}/intellivue_error_response.cxx
  ${SOURCE_DIR}/intellivue_set_response.cxx
  ${SOURCE_DIR}/intellivue_utils.cxx
  ${SOURCE_DIR}/ini_parser.cxx
  ${SOURCE_DIR}/ini_dim_parser.cxx
  ${SOURCE_DIR}/ini_association_request_parser.cxx
  ${SOURCE_DIR}/ini_rtsa_priority_list_parser.cxx
  ${SOURCE_DIR}/serial_converter.cxx
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
  ${Pqxx_LIBS}
  ${DBX_FOUND_LIBS}
)

# Copy config files to build directory
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
file(REMOVE log4cplus.properties)
file(COPY ${CONFIG_DIR}/log4cplus.properties.debug
  DESTINATION ${CMAKE_BINARY_DIR})
file(RENAME ${CMAKE_BINARY_DIR}/log4cplus.properties.debug
  ${CMAKE_BINARY_DIR}/log4cplus.properties)
else (CMAKE_BUILD_TYPE STREQUAL "Release")
file(REMOVE log4cplus.properties)
file(COPY ${CONFIG_DIR}/log4cplus.properties.release
  DESTINATION ${CMAKE_BINARY_DIR})
file(RENAME ${CMAKE_BINARY_DIR}/log4cplus.properties.release
  ${CMAKE_BINARY_DIR}/log4cplus.properties)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
file(COPY ${CONFIG_DIR}/dd_philips_intellivue_mp70.ini
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${TEST_CONFIG_DIR}/test_association_request_cfg.ini
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${TEST_CONFIG_DIR}/test_dd_philips_intellivue_mp70.ini
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${TEST_CONFIG_DIR}/test_rtsa_priority_list.ini
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CONFIG_DIR}/association_request_cfg.ini
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CONFIG_DIR}/rtsa_priority_list.ini
  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${RESOURCES_DIR}/qos/DicesBaseDriverConfig.xml
  DESTINATION ${CMAKE_BINARY_DIR})

# Configure where application and files get installed
#  Defaults to /usr/local
#  Customize by providing cmake arg -DCMAKE_INSTALL_PREFIX=???
# 'make install'
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/log4cplus.properties
  DESTINATION ${DOCBOX_PATH}/etc/config/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/dd_philips_intellivue_mp70.ini
  DESTINATION ${DOCBOX_PATH}/etc/config/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/association_request_cfg.ini
  DESTINATION ${DOCBOX_PATH}/etc/config/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/rtsa_priority_list.ini
  DESTINATION ${DOCBOX_PATH}/etc/config/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/DicesBaseDriverConfig.xml
  DESTINATION ${DOCBOX_PATH}/etc/config/${CMAKE_PROJECT_NAME})
