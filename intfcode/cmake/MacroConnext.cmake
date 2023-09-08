##############################################################################
# Connext_IDLGEN(idlfilename)
#
# Macro to generate Connext DDS sources from a given idl file with the 
# data structures.
# You must include the extension .idl in the name of the data file.
#
##############################################################################
# Courtersy of Ivan Galvez Junquera <ivgalvez@gmail.com>
##############################################################################


# Macro to create a list with all the generated source files for a given .idl filename
MACRO (DEFINE_Connext_SOURCES idlfilename)
	SET(outsources)
	GET_FILENAME_COMPONENT(it ${idlfilename} ABSOLUTE)
	GET_FILENAME_COMPONENT(nfile ${idlfilename} NAME_WE)
	SET(outsources ${outsources} ${PROJECT_SOURCE_DIR}/gen/${nfile}.cxx ${PROJECT_SOURCE_DIR}/gen/${nfile}.hpp)
	SET(outsources ${outsources} ${PROJECT_SOURCE_DIR}/gen/${nfile}Impl.cxx ${PROJECT_SOURCE_DIR}/gen/${nfile}Impl.h)
	SET(outsources ${outsources} ${PROJECT_SOURCE_DIR}/gen/${nfile}ImplPlugin.cxx ${PROJECT_SOURCE_DIR}/gen/${nfile}ImplPlugin.h)
	SET(outsources ${outsources} ${PROJECT_SOURCE_DIR}/gen/${nfile}ImplSupport.cxx ${PROJECT_SOURCE_DIR}/gen/${nfile}ImplSupport.h)
ENDMACRO(DEFINE_Connext_SOURCES)

MACRO (Connext_IDLGEN idlfilename)
	GET_FILENAME_COMPONENT(it ${idlfilename} ABSOLUTE)
	GET_FILENAME_COMPONENT(idlfilename ${idlfilename} NAME)
	DEFINE_Connext_SOURCES(${ARGV})
	ADD_CUSTOM_COMMAND (
		OUTPUT ${outsources}
		COMMAND ${Connext_IDLGEN_BINARY}
		ARGS  -d ${PROJECT_SOURCE_DIR}/gen -replace -language C++11 ${it}
		DEPENDS ${it}
	)
ENDMACRO (Connext_IDLGEN)
