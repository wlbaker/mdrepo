# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )

file(GLOB pista_core_sources ../../pista-core/src/c/*.c )
file(GLOB pista_hardware_sources ../../pista-core/src/hardware/imp731/*.c )
file(GLOB pista_bind_cxx ../../pista-core/src/cxx/*.cpp )
# file(GLOB pista_bind_java ../../pista-core/bindings/java/*.cxx )
SET( pista_source ${pista_core_sources} ${pista_hardware_sources} ${pista_bind_cxx} )
# ${pista_bind_java} )

add_library( pista-core
             SHARED
             ${pista_source} )

include_directories( ${PROTOBUF_INCLUDE_DIR} )

target_include_directories(pista-core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../pista-core/include>
#  $<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )

# set_target_properties(pista-core PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries( pista-core ${libserialport_LIBRARIES} ${PROTOBUF_LIBRARY} )
endif()

add_subdirectory( deps/libwebsockets )
include_directories( deps/libwebsockets/include )
include_directories( ${PROTOBUF_INCLUDE_DIR} )
