cmake_minimum_required(VERSION 3.4.1)

#
# Find the packages we will be using
#
# find_package(Protobufc REQUIRED )

# set(Boost_USE_STATIC_LIBS ON)
# find_package(Boost OPTIONAL_COMPONENTS asio )

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

file(GLOB pista_util_prompt_source          src/c/pista-prompt.c )
file(GLOB pista_util_reproc_source          src/c/reproc.c )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../pista-core/include  )

add_executable( pista-prompt ${pista_util_prompt_source} )
add_executable( reproc ${pista_util_reproc_source} )

target_link_libraries( pista-prompt ${CMAKE_CURRENT_SOURCE_DIR}/../build/x86_64/lib/libpista-core.so )
target_link_libraries( reproc ${CMAKE_CURRENT_SOURCE_DIR}/../build/x86_64/lib/libpista-core.so )

target_link_libraries( pista-prompt ${Boost_LIBRARIES} ${ProtobufC_LIBRARY} "readline" "yajl" "pthread" "dl" "serialport" )
target_link_libraries( reproc ${ProtobufC_LIBRARY} "pthread" "dl" "serialport" )

install(TARGETS pista-prompt RUNTIME DESTINATION bin )

