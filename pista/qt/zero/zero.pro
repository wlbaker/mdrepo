#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T12:26:56
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zero
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myglwidget.cpp

HEADERS  += mainwindow.h \
    myglwidget.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

