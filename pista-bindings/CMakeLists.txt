# Set up swig
cmake_minimum_required(VERSION 3.11)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Add subdirectories for each language if desired
option(BUILD_JAVA   "Build Java SWIG module" ON)
option(BUILD_PYTHON "Build Python SWIG module" OFF)
if(BUILD_JAVA)
    add_subdirectory(java)
endif()
if(BUILD_PYTHON)
    add_subdirectory(python)
endif()
