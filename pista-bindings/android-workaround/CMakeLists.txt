cmake_minimum_required(VERSION 3.6)

project( pista-java )

find_package(JNI)
include (UseJava)

if( JNI_FOUND )

    find_library(PISTACORE_LIBRARY pista-core HINTS ${CMAKE_SOURCE_DIR}/../.. )

	file(GLOB pista-java ../java/gen/*.cxx )

    message( STATUS "PISTACORE_LIBRARY=${PISTACORE_LIBRARY}")

	list( APPEND JNI_INCLUDE_DIRS ../../pista-core/include )
    list( APPEND JNI_LIBRARIES ${PISTACORE_LIBRARY} )

	message( STATUS "CMAKE_HOME_DIRECTORY=${CMAKE_HOME_DIRECTORY}")
	message( STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
	message( STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")

	include_directories( pista-java ${JNI_INCLUDE_DIRS} )

	target_link_libraries( pista-java ${JNI_LIBRARIES} )
	target_include_directories(pista-java PUBLIC -I../../pista-core/include ) 

    set(CMAKE_JAVA_INCLUDE_PATH ${CMAKE_HOME_DIRECTORY}/../java/gen)
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
