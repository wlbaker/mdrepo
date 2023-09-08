#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T14:24:07
#
#-------------------------------------------------

QT       += core network gui


TARGET = qtintellivuestreaming
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11
CONFIG   += warn_off


QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++
QMAKE_CXXFLAGS += -Wno-narrowing -Wno-unused-parameter -Wno-unused-variable -Wno-unneeded-internal-declaration -Wno-missing-field-initializers


TEMPLATE = app


SOURCES += main.cpp \
    DatagramToStruct.cpp \
    dataAcquisitionBuffer.cpp \
    igstkRealTimeClock.cxx \
    messageHandler.cpp \
    protocolCommands.cpp \
    timeBuffer.cpp \
    timeReference.cpp \
    udpcommunication.cpp \
    UDPStructures.cpp \
    writeToDatagram.cpp \
    InfluxDBAccessor.cpp


DISTFILES += \
    CMakeLists.txt.user \
    CMakeLists.txt

HEADERS += \
    dataAcquisitionBuffer.h \
    igstkRealTimeClock.h \
    messageHandler.h \
    protocolCommands.h \
    timeBuffer.h \
    timeReference.h \
    udpcommunication.h \
    UDPStructures.h \
    InfluxDBAccessor.h
