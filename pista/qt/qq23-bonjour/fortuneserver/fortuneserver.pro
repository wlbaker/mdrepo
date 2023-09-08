HEADERS       = server.h \
                bonjourserviceregister.h
SOURCES       = server.cpp \
                main.cpp \
                bonjourserviceregister.cpp
QT           += network

QT           += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

!mac:x11:LIBS+=-ldns_sd

win32 {
    LIBS+=-ldnssd
    # Add your path to bonjour here.
    LIBPATH=C:/Temp/mDNSResponder-107.6/mDNSWindows/DLL/Debug
    INCLUDEPATH += c:/Temp/mDNSResponder-107.6/mDNSShared
}

LIBS+=-ldns_sd
