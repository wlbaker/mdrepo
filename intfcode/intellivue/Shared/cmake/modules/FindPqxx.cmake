# - Find PostGreSQL C++ library (LIBPQXX)
# Once done this will define
#  Pqxx_FOUND - System has LIBPQXX
#  Pqxx_INCLUDE_DIRS - The LIBPQXX include directories
#  Pqxx_LIBS - The libraries needed to use LIBPQXX

find_path(Pqxx_INCLUDE_DIR pqxx
	HINTS /usr/local/include)

find_library(Pqxx_LIB libpqxx.so
	HINTS /usr/local/lib)

set(Pqxx_INCLUDE_DIRS ${Pqxx_INCLUDE_DIR}/pqxx)
set(Pqxx_LIBS ${Pqxx_LIB})

include(FindPackageHandleStandardArgs)
# handle arguments and set Pqxx_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Pqxx  DEFAULT_MSG
                                  Pqxx_LIBS
                                  Pqxx_INCLUDE_DIRS)



