HEADERS       = client.h \
                bonjourservicebrowser.h \
                bonjourserviceresolver.h
SOURCES       = client.cpp \
                main.cpp \
                bonjourservicebrowser.cpp \
                bonjourserviceresolver.cpp
QT           += network
QT           += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

!mac:x11:LIBS+=-ldns_sd
win32:LIBS+=-ldnssd
LIBS+=-ldns_sd

LIBPATH=C:/Temp/mDNSResponder-107.6/mDNSWindows/DLL/Debug
INCLUDEPATH += c:/Temp/mDNSResponder-107.6/mDNSShared
