#-------------------------------------------------
#
# Project created by QtCreator 2016-01-19T15:31:32
#
#-------------------------------------------------

CONFIG += c++11

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zerodotzero
TEMPLATE = app

linux:INCLUDEPATH += /usr/local/include /usr/local/include/libpistacxx
android:INCLUDEPATH += ../../platform/android-19/include
android:INCLUDEPATH += /opt/tools/android-19/sysroot/usr/include
android:LIBS += -L/home/bbaker/git/pista/platform/android-19/lib


SOURCES += main.cpp\
    glinstrumentdisplay.cpp \
    qtwaveformbuffer.cpp \
    demowindow.cpp \
    helper.cpp \
    bandrenderer.cpp

HEADERS  += \
    glinstrumentdisplay.h \
    qtwaveformbuffer.h \
    demowindow.h \
    helper.h \
    bandrenderer.h

FORMS    += \
    demowindow.ui

LIBS += -lpistacxx -lprotobuf-c
# LIBS += -lserialport


linux64 {
#    LIBSSL= $$OPENSSLPATH/linux64/lib/libssl.a
#    !exists($$LIBSSL): error ("Not existing $$LIBSSL)
#    LIBS+= $$LIBSSL
#    LIBCRYPTO= $$OPENSSLPATH/linux64/lib/libcrypto.a
#    !exists($$LIBCRYPTO): error ("Not existing $$LIBCRYPTO)
#    LIBS+= $$LIBCRYPTO
}

message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(Binary files (executables): $$[QT_INSTALL_BINS])
message(Plugins: $$[QT_INSTALL_PLUGINS])
message(Examples: $$[QT_INSTALL_EXAMPLES])

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = /home/bbaker/git/pista/qt/guitester/../../platform/android-19/lib/libprotobuf-c.so /home/bbaker/git/pista/qt/guitester/../../platform/android-19/lib/libpistacxx.so /home/bbaker/git/pista/qt/guitester/../../platform/android-19/lib/libpista.so
}
