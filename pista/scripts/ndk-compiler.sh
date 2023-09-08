# export CXX=arm-linux-androideabi-g++
# export CC=arm-linux-androideabi-gcc


export NDK_PATH=/opt/tools/Android/Sdk/ndk-bundle

# dest install directory
export PLATFORM_PREFIX=/opt/tools/android-19

# dreate stand-alone android compiler
# if [ -ndef PLATFORM_PREFIX ] ;
# export NDK_ROOT=/opt/tools/Android/Sdk/ndk-bundle
# kitkat 4.4
export NDK_PLATFORM=android-19
# lollipop 5.1
# export NDK_PLATFORM=android-22

mkdir ${PLATFORM_PREFIX}
${NDK_PATH}/build/tools/make-standalone-toolchain.sh --platform=${NDK_PLATFORM} --install-dir=${PLATFORM_PREFIX} --system=linux-x86_64 --arch=arm

# export PATH=${PATH}:${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin
# fi

export PATH=${PLATFORM_PREFIX}/bin:${PATH}
## build protobuf
#cd /opt/tools
#LDFLAGS="-L${PLATFORM_PREFIX}/lib" CXXFLAGS="-I ${PLATFORM_PREFIX}/include" ./configure --build=x86_64-redhat-linux --host=arm-linux-androideabi --prefix=/home/bbaker/git/pista/platform/android-19 --with-protoc=/usr/bin/protoc
## build proto-c
#LDFLAGS="-L${PLATFORM_PREFIX}/lib" CXXFLAGS="-I ${PLATFORM_PREFIX}/include" ./configure -v --build=x86_64-redhat-linux --host=arm-linux-androideabi --prefix=/home/bbaker/git/pista/platform/android-19 --disable-protoc
## build pista
#LDFLAGS="-L${PLATFORM_PREFIX}/lib" CFLAGS="-I ${PLATFORM_PREFIX}/include" CXXFLAGS="-I ${PLATFORM_PREFIX}/include" ./configure --build=x86_64-redhat-linux --host=arm-linux-androideabi --prefix=/opt/tools/android-19 --disable-libserialport

#
# build pista
# --> NOTE: no LDFLAGS passed to this configure
#
export INST_PATH=/home/bbaker/git/pista/platform/android-19
CFLAGS="-I ${INST_PATH}/include" CXXFLAGS="-I ${INST_PATH}/include" ./configure --build=x86_64-redhat-linux --host=arm-linux-androideabi --prefix=/home/bbaker/git/pista/platform/android-19/ --disable-libserialport --disable-python --disable-java

