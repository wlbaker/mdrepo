# - Try to find DICESDIM
# Once done this will define
#  DICESDIM_FOUND - System has DICESDIM
#  DICESDIM_INCLUDE_DIRS - The DICESDIM include directories
#  DICESDIM_LIBS - The libraries needed to use DICESDIM

find_path(DICESDIM_INCLUDE_DIR alarm.h
  HINTS /usr/local/include/dicesdim)

find_library(DICESDIM_LIB dicesdim
	HINTS /usr/local/lib)

set(DICESDIM_INCLUDE_DIRS ${DICESDIM_INCLUDE_DIR})
set(DICESDIM_LIBS ${DICESDIM_LIB})

include(FindPackageHandleStandardArgs)
# handle arguments and set DICESDIM_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(DICESDIM  DEFAULT_MSG
                                  DICESDIM_LIB 
                                  DICESDIM_INCLUDE_DIRS)
                                  
