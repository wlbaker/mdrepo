# - Try to find Log4CPlus libraries
# Once done this will define
#  Log4CPlus_FOUND - System has Log4CPlus
#  Log4CPlus_INCLUDE_DIR - The Log4CPlus include directory
#  Log4CPlus_LIB - The library needed to use Log4CPlus
#  

find_path(Log4CPlus_INCLUDE_DIR log4cplus
        HINTS /usr/local/include)

find_library(Log4CPlus_LIB liblog4cplus.so
        HINTS /usr/local/lib)

set(Log4CPlus_INCLUDE_DIRS ${Log4CPlus_INCLUDE_DIR})
set(Log4CPlus_LIBS ${Log4CPlus_LIB})

include(FindPackageHandleStandardArgs)
# handle arguments and set Log4CPlus_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Log4CPlus  DEFAULT_MSG
                                  Log4CPlus_LIBS 
                                  Log4CPlus_INCLUDE_DIRS)

                                  
