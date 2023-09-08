# NOTE: Search for Dices Framework: Deprecated
#  Upon completion...
#    - ..._FOUND 	- Module found
#    - ..._INCLUDE_DIRS - Module include directories
#    - ..._LIBS		- Module libraries


## CONFIGURATION
set(PACKAGE_PREFIX DICESFRAMEWORK_DEPRECATED)

set(INCLUDE_HINT Deprecated/)
set(INCLUDE_HINT_PATH /usr/local/include/DicesFramework-Deprecated)
set(LIB_HINT DicesFramework-Deprecated)
set(LIB_HINT_PATH /usr/local/lib)

##
## DO NOT MODIFY BELOW; AUTOMATED BY ABOVE VARIABLES
##
include(FindPackageHandleStandardArgs)

find_path(${PACKAGE_PREFIX}_SOURCE_DIR ${INCLUDE_HINT}
  HINTS ${INCLUDE_HINT_PATH})

file(GLOB_RECURSE ${PACKAGE_PREFIX}_HEADERS ${${PACKAGE_PREFIX}_SOURCE_DIR}/*.h)

set(PACKAGE_INCLUDE_DIRS "")
foreach(F ${${PACKAGE_PREFIX}_HEADERS})
  get_filename_component(PATH ${F} DIRECTORY)
  list(APPEND PACKAGE_INCLUDE_DIRS ${PATH})
endforeach()
list(REMOVE_DUPLICATES PACKAGE_INCLUDE_DIRS)

set(${PACKAGE_PREFIX}_INCLUDE_DIRS ${${PACKAGE_PREFIX}_SOURCE_DIR} ${PACKAGE_INCLUDE_DIRS})

find_library(${PACKAGE_PREFIX}_LIB ${LIB_HINT}
  HINTS ${LIB_HINT_PATH})

set(${PACKAGE_PREFIX}_LIBS ${${PACKAGE_PREFIX}_LIB})

# Handle arguments and set ..._FOUND to TRUE when arguments are TRUE
find_package_handle_standard_args(
  ${PACKAGE_PREFIX} DEFAULT_MSG
  ${PACKAGE_PREFIX}_LIBS
  ${PACKAGE_PREFIX}_INCLUDE_DIRS)

if(${${PACKAGE_PREFIX}_FOUND})
  if(NOT DEFINED DBX_FOUND_DIRS)
    set(DBX_FOUND_DIRS "")
  endif()
  list(APPEND DBX_FOUND_DIRS ${${PACKAGE_PREFIX}_INCLUDE_DIRS})
  list(REMOVE_DUPLICATES DBX_FOUND_DIRS)

  if(NOT DEFINED DBX_FOUND_LIBS)
    set(DBX_FOUND_LIBS "")
  endif()
  list(APPEND DBX_FOUND_LIBS ${${PACKAGE_PREFIX}_LIBS})
  list(REMOVE_DUPLICATES DBX_FOUND_LIBS)
endif()
