# We need NDDSHOME set to know the location of the RTI Connext DDS installation
if (NOT DEFINED NDDSHOME)
  if (DEFINED ENV{NDDSHOME})
    set(NDDSHOME $ENV{NDDSHOME})
  else()
    message(FATAL_ERROR "$NDDSHOME not specified. Please set -DNDDSHOME= to your RTI Connext DDS installation directory")
  endif()
endif()

# We need to know the RTI Connext DDS libraries to compile against
if (NOT DEFINED ARCHITECTURE)
  message(FATAL_ERROR "$ARCHITECTURE not specified. Please set -DARCHITECTURE= to your RTI Connext DDS architecture")
endif()

# Connext DDS Definitions
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
  set(Connext_DEFINITIONS
     "-DRTI_UNIX -DRTI_LINUX"
  )
  set(nddscore_libname libnddscorez.a)
  set(nddsc_libname libnddscz.a)
  set(nddscpp_libname libnddscppz.a)
  set(nddscpp2_libname libnddscpp2z.a)
  set(external_libs "-ldl -lm -lpthread -lrt")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
  set(Connext_DEFINITIONS
    "-DWIN32_LEAN_AND_MEAN -DWIN32 -D_WINDOWS -DRTI_WIN32 -D_BIND_TO_CURRENT_MFC_VERSION=1 -D_BIND_TO_CURRENT_CRT_VERSION=1 -D_CRT_SECURE_NO_WARNING")
  set(nddscore_libname nddscorez.lib)
  set(nddsc_libname nddscz.lib)
  set(nddscpp_libname nddscppz.lib)
  set(nddscpp2_libname nddscpp2z.lib)
  set(external_libs ws2_32 netapi32 version)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  # Build for Mac
  set(Connext_DEFINITIONS  "-DRTI_UNIX -DRTI_DARWIN -DRTI_DARWIN10 -DRTI_64BIT")
  set(nddscore_libname libnddscorez.a)
  set(nddsc_libname libnddscz.a)
  set(nddscpp_libname libnddscppz.a)
  set(nddscpp2_libname libnddscpp2z.a)
endif()


# Find ndds_c.h header file
find_path(Connext_INCLUDE_DIRS_NDDS
  NAMES ndds_cpp.h
  PATHS ${NDDSHOME}/include/ndds
  )
find_path(Connext_INCLUDE_DIRS_DDS
  NAMES dds/dds.hpp
  PATHS ${NDDSHOME}/include/hpp
  )
# We need to include both include and include/ndds directories
set(Connext_INCLUDE_DIRS
  ${NDDSHOME}/include
  ${NDDSHOME}/include/hpp/rtiboost
  ${Connext_INCLUDE_DIRS_NDDS}
  ${Connext_INCLUDE_DIRS_DDS}
  )

# Add Core, C, and C++ libraries for the given architecture
find_library(nddscore_lib
  NAMES ${nddscore_libname}
  PATHS ${NDDSHOME}/lib/${ARCHITECTURE}
  )

find_library(nddsc_lib
  NAMES ${nddsc_libname}
  PATHS ${NDDSHOME}/lib/${ARCHITECTURE}
  )

find_library(nddscpp_lib
  NAMES ${nddscpp_libname}
  PATHS ${NDDSHOME}/lib/${ARCHITECTURE}
  )

find_library(nddscpp2_lib
  NAMES ${nddscpp2_libname}
  PATHS ${NDDSHOME}/lib/${ARCHITECTURE}
  )

set(Connext_LIBRARIES
  ${nddscpp2_lib}
  ${nddscpp_lib}
  ${nddsc_lib}
  ${nddscore_lib}
  ${CMAKE_DL_LIBS}
  ${external_libs}
  )


# Binary for the IDL compiler 
SET (Connext_IDLGEN_BINARY ${NDDSHOME}/scripts/rtiddsgen)

IF (Connext_INCLUDE_DIRS AND Connext_LIBRARIES)
	SET(Connext_FOUND TRUE)
ENDIF (Connext_INCLUDE_DIRS AND Connext_LIBRARIES)

IF (Connext_FOUND)
	MESSAGE(STATUS "Found Connext DDS libraries: ${Connext_LIBRARIES}")
ELSE (Connext_FOUND)
	IF (Connext_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find Connext DDS")
	ENDIF (Connext_FIND_REQUIRED)
ENDIF (Connext_FOUND)

MARK_AS_ADVANCED(Connext_INCLUDE_DIRS Connext_LIBRARIES Connext_IDLGEN_BINARY)
INCLUDE (MacroConnext)

