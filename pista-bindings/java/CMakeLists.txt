cmake_minimum_required(VERSION 3.11)

project( pista-java )

# Set up swig
find_package(SWIG)
find_package(PythonLibs 3)
find_package(Java)
find_package(JNI)

# find_package(LibWebsockets REQUIRED )  #052319...use installed (distribution) version
find_package(PistaCore REQUIRED )  # FIXME: not found!!!why??

include (UseJava)
include (UseSWIG)

set(CMAKE_SWIG_FLAGS -I../pista-core/include)
set_property(SOURCE pistax.i PROPERTY CPLUSPLUS ON)


if( JNI_FOUND )

	# https://github.com/ptitpoulpe/cmake-swig-java-example/blob/master/CMakeLists.txt
	# https://github.com/ptitpoulpe/cmake-swig-java-example/blob/master/example.i

    find_library(PISTACORE_LIBRARY pista-core HINTS ${CMAKE_SOURCE_DIR}/.. )
    #find_library(PROTOBUF_LIBRARY protobuf HINTS /usr/lib/x86_64-linux-gnu)

    message( STATUS "PISTACORE_LIBRARY=${PISTACORE_LIBRARY}")

	list( APPEND JNI_INCLUDE_DIRS ../pista-core/include )
    list( APPEND JNI_LIBRARIES ${PISTACORE_LIBRARY} )

	message( STATUS "CMAKE_HOME_DIRECTORY=${CMAKE_HOME_DIRECTORY}")
	message( STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
	message( STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")

	option(BUILD_JAVA   "Build Java SWIG module"   ON)
	include_directories( pista-java ${JNI_INCLUDE_DIRS} )

	set(CMAKE_SWIG_OUTDIR java/gen/org/pistax )
	set(CMAKE_SWIG_FLAGS -package org.pistax -features director )  # removed nspace
	swig_add_library(pista-java 
            LANGUAGE java
            OUTPUT_DIR java/gen/org/pistax   # swing -outdir
            OUTFILE_DIR java/gen      # swing -o
	        SOURCES pistax.i
     	)
	swig_link_libraries( pista-java ${JNI_LIBRARIES} )
	set_property(TARGET pista-java PROPERTY SWIG_INCLUDE_DIRECTORIES ${JNI_INCLUDE_DIRS} )
	target_include_directories(pista-java PUBLIC -I../pista-core/include ) 

    set(CMAKE_JAVA_INCLUDE_PATH ${CMAKE_HOME_DIRECTORY}/java/gen)
    add_jar( pistaJNI
        SOURCES 
        ${CMAKE_SWIG_OUTDIR}/PISTAX.java
        ${CMAKE_SWIG_OUTDIR}/PISTAXJNI.java
        VERSION 0.8.0
    )
    add_dependencies( pistaJNI pista-java )
endif( )


# Add subdirectories for each language if desired
option(BUILD_PYTHON "Build Python SWIG module" OFF)

#if(BUILD_JAVA)
#    add_subdirectory(java)
#endif()
#if(BUILD_PYTHON)
#    add_subdirectory(python)
#	swig_add_library(pista-python SHARED
#            LANGUAGE python
#            OUTPUT_DIR python/gen   # swing -outdir
#            OUTFILE_DIR python      # swing -o
#	    SOURCES pistax.i
#     	)
#endif()


# [NO_PROXY]
