HEADERS       = glwidget.h \
                mainwindow.h \
    instrumentdisplay.h \
    firstform.h \
    settingsform.h \
    bluetoothmgmtform.h \
    patientform.h \
    flowlayout.h \
    ../guitester/qtwaveformbuffer.h \
    ../guitester/glinstrumentdisplay.h \
    ../guitester/bandrenderer.h \
    dataform.h \
    shortcuticonarea.h \
    wifimgmtform.h

SOURCES       = glwidget.cpp \
                main.cpp \
                mainwindow.cpp \
    instrumentdisplay.cpp \
    firstform.cpp \
    settingsform.cpp \
    bluetoothmgmtform.cpp \
    patientform.cpp \
    flowlayout.cpp \
    ../guitester/qtwaveformbuffer.cpp \
    ../guitester/glinstrumentdisplay.cpp \
    ../guitester/bandrenderer.cpp \
    dataform.cpp \
    shortcuticonarea.cpp \
    wifimgmtform.cpp

RESOURCES     = qdarkstyle/style.qrc \
    rc/app.qrc
win32:RC_ICONS += rc/meddev.ico

INCLUDEPATH += ../guitester

android:INCLUDEPATH += ../../platform/android-19/include
android:INCLUDEPATH += /opt/tools/android-19/sysroot/usr/include
android:LIBS += -L/home/bbaker/git/pista/platform/android-19/lib

linux:INCLUDEPATH += /usr/local/include /usr/local/include/libpistacxx
linux:LIBS += -L/usr/local/lib

LIBS += -lpistacxx -lpista -lprotobuf-c -lwebsockets -lserialport -lavahi-common -lavahi-client -lyajl

# LIBS += -L/home/bbaker/git/pista/pista-core/bindings/cxx/.libs  -L/home/bbaker/git/pista/pista-core/.libs -lpistacxx -lpista -lprotobuf-c

# didnt work...debug output is not going to console
# OUTPUT += Console

CONFIG += c++11

TARGET = Bernard

qtHaveModule(serialport) {
        DEFINES += QT_SERIALPORT_SUPPORT
        QT += serialport
}
QT  += widgets opengl bluetooth  network

# install
target.path = $$[HOME]/.local/Bernard
INSTALLS += target

DISTFILES += \
    README \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

FORMS += \
    firstform.ui \
    settingsform.ui \
    bluetoothmgmtform.ui \
    patientform.ui \
    dataform.ui \
    wifimgmtform.ui

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../../platform/android-19/lib/libprotobuf-c.so \
        $$PWD/../../platform/android-19/lib/libpistacxx.so \
        $$PWD/../../platform/android-19/lib/libpista.so
}
