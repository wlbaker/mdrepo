cmake_minimum_required(VERSION 3.11)

# Include python
find_package(PythonLibs REQUIRED)
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
include_directories(${PYTHON_INCLUDE_PATH})


set(CMAKE_SWIG_FLAGS "")
set_source_files_properties(../pistax.i PROPERTIES CPLUSPLUS ON)
include_directories(../../pista-core/include)

# Add swig module
# DEPRECATED swig_add_module( pypista python ../pistax.i)
swig_add_library(pypista TYPE MODULE LANGUAGE python SOURCES ../pistax.i )
swig_link_libraries(pypista pista-core x-support ${PYTHON_LIBRARIES})

message(STATUS "PYTHON_INCLUDE_PATH=${PYTHON_INCLUDE_PATH}")
message(STATUS "PYTHON_LIBRARIES=${PYTHON_LIBRARIES}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")

# Files to install with Python
set(PYTHON_INSTALL_FILES
        ${CMAKE_CURRENT_BINARY_DIR}/swig_example.py
        ${CMAKE_CURRENT_BINARY_DIR}/_swig_example.so)

# Configure setup.py and copy to output directory
set(SETUP_PY_IN ${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in)
set(SETUP_PY_OUT ${CMAKE_CURRENT_BINARY_DIR}/setup.py)
configure_file(${SETUP_PY_IN} ${SETUP_PY_OUT})

# Declare install target for python
#install(TARGETS swig_example
#        COMMAND "${PYTHON_EXECUTABLE} setup.py"
#        COMPONENT swig-python)

# Install target to call setup.py
#add_custom_target(install-python
#	DEPENDS _swig_example
#	COMMAND python ${SETUP_PY_OUT} install)
