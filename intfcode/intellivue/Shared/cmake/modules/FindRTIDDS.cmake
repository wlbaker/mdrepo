# - Try to find RTIDDS
# Once done this will define
#  RTIDDS_FOUND - System has RTIDDS
#  RTIDDS_INCLUDE_DIRS - The RTIDDS include directories
#  RTIDDS_LIBS - The libraries needed to use RTIDDS
#  RTIDDS_DEFINES - Compiler switches required for using RTIDDS
# The following CMake variables impact which library we link
#  CMAKE_BUILD_TYPE

find_path(RTIDDS_INCLUDE_DIR include
	HINTS $ENV{NDDSHOME})
find_path(RTIDDS_LIB_DIR lib
	HINTS $ENV{NDDSHOME})

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    set(LIBSUFFIX d)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

find_library(RTIDDS_C_LIB nddsc${LIBSUFFIX}
	HINTS ${RTIDDS_LIB_DIR}/lib/x64Linux3gcc5.4.0)
find_library(RTIDDS_CPP_LIB nddscpp${LIBSUFFIX}
	HINTS ${RTIDDS_LIB_DIR}/lib/x64Linux3gcc5.4.0)
find_library(RTIDDS_CORE_LIB nddscore${LIBSUFFIX}
	HINTS ${RTIDDS_LIB_DIR}/lib/x64Linux3gcc5.4.0)

set(RTIDDS_INCLUDE_DIRS 
	${RTIDDS_INCLUDE_DIR}/include
	${RTIDDS_INCLUDE_DIR}/include/ndds)
set(RTIDDS_LIBS 
	${RTIDDS_C_LIB}
	${RTIDDS_CPP_LIB}
	${RTIDDS_CORE_LIB}
	dl nsl m pthread rt )
set(RTIDDS_DEFINES -DRTI_UNIX -DRTI_LINUX -DRTI_64BIT)

include(FindPackageHandleStandardArgs)
# handle arguments and set RTIDDS_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(RTIDDS  DEFAULT_MSG
                                  RTIDDS_C_LIB 
                                  RTIDDS_CPP_LIB
                                  RTIDDS_CORE_LIB
                                  RTIDDS_INCLUDE_DIR)
                                  
