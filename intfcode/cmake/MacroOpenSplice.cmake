##############################################################################
# OpenSplice_IDLGEN(idlfilename)
#
# Macro to generate OpenSplice DDS sources from a given idl file with the 
# data structures.
# You must include the extension .idl in the name of the data file.
#
##############################################################################
# Courtersy of Ivan Galvez Junquera <ivgalvez@gmail.com>
##############################################################################


# Macro to create a list with all the generated source files for a given .idl filename
MACRO (DEFINE_OpenSplice_SOURCES idlfilename)
	SET(outsources)
	GET_FILENAME_COMPONENT(it ${idlfilename} ABSOLUTE)
	GET_FILENAME_COMPONENT(nfile ${idlfilename} NAME_WE)
	SET(outsources ${outsources} ${PROJECT_SOURCE_DIR}/gen/${nfile}.cpp ${PROJECT_SOURCE_DIR}/gen/${nfile}.h)
	SET(outsources ${outsources} ${PROJECT_SOURCE_DIR}/gen/${nfile}Dcps.cpp ${PROJECT_SOURCE_DIR}/gen/${nfile}Dcps.h)
	SET(outsources ${outsources} ${PROJECT_SOURCE_DIR}/gen/${nfile}Dcps_impl.cpp ${PROJECT_SOURCE_DIR}/gen/${nfile}Dcps_impl.h)
	SET(outsources ${outsources} ${PROJECT_SOURCE_DIR}/gen/${nfile}SplDcps.cpp ${PROJECT_SOURCE_DIR}/gen/${nfile}SplDcps.h)
ENDMACRO(DEFINE_OpenSplice_SOURCES)

MACRO (OpenSplice_IDLGEN idlfilename)
	GET_FILENAME_COMPONENT(it ${idlfilename} ABSOLUTE)
	GET_FILENAME_COMPONENT(idlfilename ${idlfilename} NAME)
	DEFINE_OpenSplice_SOURCES(${ARGV})
	ADD_CUSTOM_COMMAND (
		OUTPUT ${outsources}
		COMMAND ${OpenSplice_IDLGEN_BINARY}
		ARGS  -l isocpp -d ${PROJECT_SOURCE_DIR}/gen ${it}
		DEPENDS ${it}
	)
ENDMACRO (OpenSplice_IDLGEN)
