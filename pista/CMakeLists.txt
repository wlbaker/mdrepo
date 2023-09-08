# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
# // include(CTest)
project( Pista )
 
# The version number.
set (Pista_VERSION "blueberry")
set (Pista_VERSION_MAJOR 1)
set (Pista_VERSION_MINOR 0)
set (Pista_VERSION_PATCH 1)
# set_property(TARGET tgt PROPERTY C_STANDARD 11)
set( CMAKE_C_STANDARD 11)

if( NOT DEFINED CMAKE_INSTALL_DATADIR )
	set(CMAKE_INSTALL_DATADIR "${_CMAKE_INSTALL_DIR}/lib/cmake" )
endif()

set( ABI "x86_64" )
if( ${ANDROID_ABI} )
    set (ABI ${ANDROID_ABI} )
endif()

cmake_policy( SET CMP0054 NEW)
cmake_policy( SET CMP0057 NEW)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/${ABI}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/${ABI}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/${ABI}/bin)
# LIST(APPEND CMAKE_MODULE_PATH "/opt/bernard/lib/cmake/libwebsockets" )

configure_file (
  "${PROJECT_SOURCE_DIR}/pista-core/include/config.h.in"
  "${PROJECT_BINARY_DIR}/pista-core/include/config.h"
  )

macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

# print_all_variables()
#
# Find the packages we will be using
#

# 052319 find_package(ProtobufC REQUIRED )
# 052319 pkg-config package
find_package(PkgConfig REQUIRED)
pkg_check_modules(ProtobufC REQUIRED libprotobuf-c)
pkg_check_modules(libserialport REQUIRED libserialport )
# 052319 find_package(ProtobufC)

# cmake package
find_package(Libwebsockets REQUIRED )  #052319...use installed (distribution) version

# set(Boost_USE_STATIC_LIBS ON)
# find_package(Boost OPTIONAL_COMPONENTS asio )


#
# Build the model definition source files before GLOB-ing the directory
#
## ${PROTOCC} ${PROTOC_OPTIONS} --c_out=../pista-core/src model/ht70.proto
## PROTOC( "--c_out=pista-model/src" pista-hardware/simu/simu.proto )
#PROTOC( --c_out=. pista-hardware/simu/simu.proto )
#PROTOC( --c_out=. pista-hardware/propaqm/propaqm.proto )

set( BUILD_SHARED_LIBS ON )
message( STATUS "To build shared libs, set BUILD_SHARED_LIBS to ON" )
message( STATUS "Building Shared Libs: ${BUILD_SHARED_LIBS}" )

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# file(GLOB pista_core_c_sources   LIST_DIRECTORIES false          pista-core/src/c/*.c )
file(GLOB pista_core_c_sources   RELATIVE ${PROJECT_SOURCE_DIR}          pista-core/src/c/*.c )

# FIXME...(only) if libserialport lookup fails, then remove the corresponding source code
# list(REMOVE_ITEM pista_core_c_sources 	     "pista-core/src/c/pista_lspIO.c")

file(GLOB pista_core_c_serialport_sources    pista-core/src/c/serial/*.c )
file(GLOB pista_core_cxx_sources             pista-core/src/cxx/*.cpp )
file(GLOB pista_core_cxx_boost_sources       pista-core/src/cxx/boost/*.cpp )
file(GLOB pista_core_cxx_serialport_sources  pista-core/src/cxx/serial/*.cpp )

file(GLOB x_support_sources             pista-hardware/support/*.c )
file(GLOB pista_hw_bmp180_sources       pista-hardware/bmp180/*.c )
file(GLOB pista_hw_imp731_sources       pista-hardware/imp731/*.c )
file(GLOB pista_hw_ht70_sources         pista-hardware/ht70/*.c )
file(GLOB pista_hw_infinity_sources     pista-hardware/infinity/*.c )
file(GLOB pista_hw_simu_sources         pista-hardware/simu/*.c )
file(GLOB pista_hw_propaqm_sources      pista-hardware/propaqm/*.c )
file(GLOB pista_hw_medsys3_sources      pista-hardware/medsys3/*.c )

file(GLOB pista_bind_jni                pista-bindings/java/*.cxx )


SET( pista_source ${pista_core_c_sources} ${pista_core_cxx_sources} )
# SET( pista_source ${pista_source} ${pista_hw_propaqm_sources} )


if( ${Boost_ASIO_FOUND} )
	include_directories( ${Boost_INCLUDE_DIRS}  )
	ADD( pista_source ${pista_core_cxx_boost_sources}  )
    target_link_libraries( pista-core ${Boost_LIBRARIES} ${PROTOBUF_LIBRARY} )
endif()
if( ${libserialport_FOUND} )
	include_directories( ${libserialport_INCLUDE_DIRS}  )
	ADD( pista_source ${pista_core_c_serialport_sources }  )
	ADD( pista_source ${pista_core_cxx_serialport_sources }  )
    target_link_libraries( pista-core ${libserialport_LIBRARIES} ${PROTOBUF_LIBRARY} )
endif()

include_directories( ${Protobuf_INCLUDE_DIR} )
include_directories( ${LibWebsockets_INCLUDE_DIR} )

# 052319 add_subdirectory( deps/libwebsockets )
# 052319 include_directories( deps/libwebsockets/include )

# add_subdirectory( deps/yajl )

message( STATUS "Static LIBWEBSOCKETS libraries: ${LIBWEBSOCKETS_LIBRARIES_STATIC}" )
message( STATUS "Shared LIBWEBSOCKETS libraries: ${LIBWEBSOCKETS_LIBRARIES_SHARED}" )

message( STATUS "Static PROTOBUF-C libraries: ${ProtobufC_LIBRARIES}" )
# message( STATUS "Shared PROTOBUF-C libraries: ${ProtobufC_LIBRARIES_SHARED}" )

# print_all_variables()

#

add_library( x-support ${x_support_sources} )
add_library( pista-core ${pista_source} )
add_library( pista-simu ${pista_hw_simu_sources} )
add_library( pista-imp731 ${pista_hw_imp731_sources} )
add_library( pista-ht70 ${pista_hw_ht70_sources} )
#FIXME MINGW64: add_library( pista-propaqm ${pista_hw_propaqm_sources} )
add_library( pista-medsys3 ${pista_hw_medsys3_sources} )

# add_library( pista-simu
#             SHARED
#             ${pista_hw_simu_sources} )

include_directories( 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/pista-core/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# set_target_properties(pista-core PROPERTIES LINKER_LANGUAGE CXX)
# target_link_libraries( pista-core LINK_PUBLIC ${YAJL_LIBRARIES} ${LIBWEBSOCKETS_LIBRARIES} ${ProtobufC_LIBRARIES} )
target_link_libraries( pista-core LINK_PUBLIC ${ProtobufC_LIBRARIES} x-support ${libserialport_LIBRARIES} dl )
target_link_libraries( pista-simu LINK_PUBLIC ${ProtobufC_LIBRARIES} x-support )
target_link_libraries( pista-imp731 LINK_PUBLIC ${ProtobufC_LIBRARIES} yajl x-support ${libserialport_LIBRARIES} )
target_link_libraries( pista-ht70 LINK_PUBLIC ${ProtobufC_LIBRARIES} expat x-support )
#FIXME MINGW64: target_link_libraries( pista-propaqm LINK_PUBLIC ${ProtobufC_LIBRARIES} ${LIBWEBSOCKETS_LIBRARIES_STATIC} ssl crypto yajl x-support )
target_link_libraries( pista-medsys3 LINK_PUBLIC ${ProtobufC_LIBRARIES} ${LIBWEBSOCKETS_LIBRARIES_STATIC} ssl crypto yajl x-support )

if (UNIX)
    add_library( pista-bmp180 ${pista_hw_bmp180_sources} )
    # add_library( pista-infinity ${pista_hw_infinity_sources} )

    #target_include_directories(pista-bmp180 PUBLIC
    #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/pista-core/include>
    #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    #)

    target_link_libraries( pista-bmp180 LINK_PUBLIC ${ProtobufC_LIBRARIES} x-support pista-core )
    # target_link_libraries( pista-infinity LINK_PUBLIC ${ProtobufC_LIBRARIES} expat x-support )
    install(TARGETS pista-bmp180 RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
    # install(TARGETS pista-infinity RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
endif (UNIX)

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/pista-util )

install(TARGETS pista-core EXPORT PistaCoreConfig RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(TARGETS x-support EXPORT PistaCoreConfig RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(TARGETS pista-simu RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(TARGETS pista-imp731 RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib )
install(TARGETS pista-ht70 RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
#FIXME MINGW64: install(TARGETS pista-propaqm RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(TARGETS pista-medsys3 RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/pista-core/include/pista.h DESTINATION include )

configure_file( pista-core/pista.pc.in pista-core/pista.pc @ONLY )

# IF(CMAKE_HOST_UNIX)
# INSTALL(CODE "EXECUTE_PROCESS (COMMAND ln -sf protoc-gen-c protoc-c WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)")
# ENDIF()

export( TARGETS
	pista-core x-support
	NAMESPACE PistaCore::
	FILE "${CMAKE_CURRENT_BINARY_DIR}/PistaCoreConfig.cmake"
)

install( EXPORT
	PistaCoreConfig
	DESTINATION "${CMAKE_INSTALL_DATADIR}/PistaCore/cmake"
	NAMESPACE PistaCore::
)

# build a CPack driven installer package
# include (InstallRequiredSystemLibraries)
# set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
# set (CPACK_PACKAGE_VERSION_MAJOR "${Pista_VERSION_MAJOR}")
# set (CPACK_PACKAGE_VERSION_MINOR "${Pista_VERSION_MINOR}")
# include (CPack)


message(STATUS " ")
message(STATUS " ")
message(STATUS "AFTER BUILD: consider building pista-util")
message(STATUS "AFTER BUILD: consider building pista-bindings")
message(STATUS " ")
message(STATUS " ")
