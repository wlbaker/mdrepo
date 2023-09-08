#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T11:47:18
#
#-------------------------------------------------

QT       += core gui websockets bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pistacon
TEMPLATE = app

linux:INCLUDEPATH += /usr/local/include /usr/local/include/libpistacxx
android:INCLUDEPATH += ../../platform/android-19/include
android:INCLUDEPATH += /opt/tools/android-19/sysroot/usr/include
android:LIBS += -L/home/bbaker/git/pista/platform/android-19/lib

LIBS += -lm


SOURCES += main.cpp\
        mainwindow.cpp \
    propaqdriver.cpp \
    cJSON_Utils.c \
    cJSON.c

HEADERS  += mainwindow.h \
    propaqdriver.h \
    cJSON_Utils.h \
    cJSON.h

FORMS    += mainwindow.ui

CONFIG += c++11
CONFIG += mobility
MOBILITY =

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    test.json

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../../platform/android-19/lib/libprotobuf-c.so \
        $$PWD/../../platform/android-19/lib/libpista.so
}

#        $$PWD/../../platform/android-19/lib/libprotobuf-lite.so \
#        $$PWD/../../platform/android-19/lib/libprotobuf.so \
#        $$PWD/../../platform/android-19/lib/libpistacxx.so

