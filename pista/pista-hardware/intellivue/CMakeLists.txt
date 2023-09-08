cmake_minimum_required(VERSION 2.8)

PROJECT(IntelliVueStreaming)


# use what QVTK built with
# SET(QT_MOC_EXECUTABLE ${VTK_QT_MOC_EXECUTABLE} CACHE FILEPATH "")
# SET(QT_UIC_EXECUTABLE ${VTK_QT_UIC_EXECUTABLE} CACHE FILEPATH "")
# SET(QT_QMAKE_EXECUTABLE ${VTK_QT_QMAKE_EXECUTABLE} CACHE FILEPATH "")

FIND_PACKAGE(Qt5  COMPONENTS QtGui QtCore QtMultimedia REQUIRED)
find_package(Qt5Widgets)

#INCLUDE(${QT_USE_FILE})

 

# Use the include path and library for Qt that is used by VTK.
INCLUDE_DIRECTORIES(
  ${QT_INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)


# Set your files and resources here  
SET(IntelliVueStreamingUI 
	)
SET(IntelliVueStreamingHeaders 
	
	dataAcquisitionBuffer.h
	timeReference.h
	udpcommunication.h
	UDPStructures.h
	protocolCommands.h
	messageHandler.h
	timeBuffer.h
	igstkRealTimeClock.h

	)
SET(IntelliVueStreamingResources)
SET(IntelliVueStreamingSrcs ${IntelliVueStreamingHeaders}
	main.cpp
	dataAcquisitionBuffer.cpp
	timeReference.cpp
	udpcommunication.cpp
	UDPStructures.cpp
	protocolCommands.cpp
	messageHandler.cpp
	timeBuffer.cpp
	igstkRealTimeClock.cxx
	)


# The rest should just work (sure...)
QT5_WRAP_UI(UISrcs ${IntelliVueStreamingUI})
QT5_WRAP_CPP(MOCSrcs ${IntelliVueStreamingHeaders} )
QT5_ADD_RESOURCES(ResourceSrcs ${IntelliVueStreamingResources})

SOURCE_GROUP("Resources" FILES
  ${IntelliVueStreamingUI}
  ${IntelliVueStreamingResources}
  ${EXE_ICON})


SOURCE_GROUP("Generated" FILES
  ${UISrcs}
  ${MOCSrcs}
  ${ResourceSrcs}
  ${RCS_SOURCES}
)

ADD_DEFINITIONS(-DQT_GUI_LIBS -DQT_CORE_LIB -DQT3_SUPPORT)
SET_SOURCE_FILES_PROPERTIES(${IntelliVueStreamingSrcs} PROPERTIES
                            OBJECT_DEPENDS "${UISrcs}")

# It's nice to have the ui in the windows project file...just double click on it
# and designer comes up on that ui file :)
#IF (${CMAKE_BUILD_TOOL} MATCHES "msdev")
#  SET (IntelliVueStreamingSrcs ${IntelliVueStreamingSrcs} ${IntelliVueStreamingUI})
#ENDIF (${CMAKE_BUILD_TOOL} MATCHES "msdev")
#IF (${CMAKE_BUILD_TOOL} MATCHES "devenv")
#  SET (IntelliVueStreamingSrcs ${IntelliVueStreamingSrcs} ${IntelliVueStreamingUI})
#ENDIF (${CMAKE_BUILD_TOOL} MATCHES "devenv")


ADD_EXECUTABLE( IntelliVueStreaming MACOSX_BUNDLE ${IntelliVueStreamingSrcs} ${UISrcs} ${MOCSrcs} ${ResourceSrcs})

qt5_use_modules (IntelliVueStreaming Widgets Network)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++0x  )
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wno-narrowing )
# -Wno-narrowing                  = Don't warn about type narrowing
set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS}  -Wno-narrowing -Wno-unused-parameter -Wno-unused-variable -Wno-unneeded-internal-declaration -Wno-missing-field-initializers")

TARGET_LINK_LIBRARIES (IntelliVueStreaming
  ${QT_LIBRARIES} ${PCL_LIBRARIES} ${VTK_LIBRARIES})

#TARGET_LINK_LIBRARIES( IntelliVueStreaming
  #Winmm
  #QVTK
#  ${QT_LIBRARIES}
#)
