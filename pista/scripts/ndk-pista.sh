CXX=arm-linux-androideabi-g++
CC=arm-linux-androideabi-gcc


NDK_PATH=/opt/tools/Android/Sdk/ndk-bundle
PLATFORM_PREFIX=/opt/tools/android-19
NDK_PLATFORM=android-19

PATH=${PLATFORM_PREFIX}/bin:${PATH}

#
# build pista
# --> NOTE: no LDFLAGS passed to this configure
#
INST_PATH=/home/bbaker/git/pista/platform/android-19
CFLAGS="-I ${INST_PATH}/include" CXXFLAGS="-I ${INST_PATH}/include" ./configure --build=x86_64-redhat-linux --host=arm-linux-androideabi --prefix=/home/bbaker/git/pista/platform/android-19/ --disable-libserialport --disable-python --disable-java

