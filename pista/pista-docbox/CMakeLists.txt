# This file instructs CMake on what build steps to take,
#  what files to operate on, where to install, etc.
# cmake ../cmake -DCMAKE_INSTALL_PREFIX=/opt/DocBoxInc/

# Debug builds can be specified by passing cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required (VERSION 3.5)
project (infinity-driver)

find_package(DicesIniParser)
find_package(DicesHostIdAndAppId)
find_package(DicesNomenclature)
find_package(RTIDDS)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ProtobufC REQUIRED libprotobuf-c)
pkg_check_modules(libserialport REQUIRED libserialport )

# Set a variable with the location of our source files
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# Automatically find needed header files in these directories
include_directories(
  ${RTIDDS_INCLUDE_DIRS}
  ${DICESNOMENCLATURE_INCLUDES}
  ${DICESINIPARSER_INCLUDES}
  ${DICESHOSTIDANDAPPID_INCLUDES}
  ${SOURCE_DIR}
  ${CMAKE_BINARY_DIR}/src_dds
  ${CMAKE_CURRENT_SOURCE_DIR}/../pista-core/include
)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/src_dds)

# Create a list of source files
# Notice that we do not explicitly list header files
# CMake automatically finds them in the include directories for us!
set(SOURCES ${SOURCE_DIR}/main.cxx )

# RTIDDS package has some definitions we must pass to the compiler
# These would look like -DVARIABLE=X in a gcc call
add_definitions(${RTIDDS_DEFINES} -std=c++11 -gdwarf-2)

add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/src_dds/common.cxx
         ${CMAKE_BINARY_DIR}/src_dds/commonSupport.cxx
         ${CMAKE_BINARY_DIR}/src_dds/commonPlugin.cxx
         ${CMAKE_BINARY_DIR}/src_dds/metric.cxx
         ${CMAKE_BINARY_DIR}/src_dds/metricSupport.cxx
         ${CMAKE_BINARY_DIR}/src_dds/metricPlugin.cxx
         ${CMAKE_BINARY_DIR}/src_dds/numeric.cxx
         ${CMAKE_BINARY_DIR}/src_dds/numericSupport.cxx
         ${CMAKE_BINARY_DIR}/src_dds/numericPlugin.cxx
  COMMAND /opt/DocBoxInc/dices-examples/resource/scripts/rtiddsgen-helper.sh ${CMAKE_BINARY_DIR}/src_dds
)

# CMake will create a binary from the ICE and program sources
add_executable(${CMAKE_PROJECT_NAME}
  ${SOURCES}
  ${CMAKE_BINARY_DIR}/src_dds/common.cxx
  ${CMAKE_BINARY_DIR}/src_dds/commonSupport.cxx
  ${CMAKE_BINARY_DIR}/src_dds/commonPlugin.cxx
  ${CMAKE_BINARY_DIR}/src_dds/metric.cxx
  ${CMAKE_BINARY_DIR}/src_dds/metricSupport.cxx
  ${CMAKE_BINARY_DIR}/src_dds/metricPlugin.cxx
  ${CMAKE_BINARY_DIR}/src_dds/numeric.cxx
  ${CMAKE_BINARY_DIR}/src_dds/numericSupport.cxx
  ${CMAKE_BINARY_DIR}/src_dds/numericPlugin.cxx
)

target_link_libraries(${CMAKE_PROJECT_NAME}
  ${RTIDDS_LIBS}
  ${DICESINIPARSER_LIBS}
  ${DICESHOSTIDANDAPPID_LIBS}
  ${CMAKE_CURRENT_SOURCE_DIR}/../build/x86_64/lib/libpista-core.so
  ${ProtobufC_LIBRARIES}
)

if( ${libserialport_FOUND} )
	target_link_libraries(${CMAKE_PROJECT_NAME} ${libserialport_LDFLAGS})
	# target_link_directories(${CMAKE_PROJECT_NAME} ${libserialport_LIBDIR})
endif()


macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

print_all_variables()

# print_all_variables()
# Configure where application and files get installed
#  Defaults to /usr/local
#  Customize by providing cmake arg -DCMAKE_INSTALL_PREFIX=???
# 'make install'
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_PROJECT_NAME})
