#!/bin/bash

#
# Build libwebsockets static library for Android
#
# requires debian package xutils-dev for makedepend (openssl make depend)
#

# This is based on http://stackoverflow.com/questions/11929773/compiling-the-latest-openssl-for-android/
# via https://github.com/warmcat/libwebsockets/pull/502

# path to NDK
if [ -z ${ANDROID_SDK+x} ]; then 
    echo "ANDROID_SDK is unset"
    export ANDROID_SDK=/opt/Android-Studio
else 
    echo "ANDROID_SDK is set to '${ANDROID_SDK}'"
fi
export NDK=${ANDROID_SDK}/ndk-bundle

export TOOLCHAIN_PATH=${NDK}/prebuilt/${HOST}/bin
export TARGET_ARCH=x86_64
export TARGET_ARCH=armeabi-v7a
export DISTRIB_PATH=`pwd`/../distribution/libs/${TARGET_ARCH}

set -e

# Download packages libz, openssl and libwebsockets

# [ ! -f zlib-1.2.8.tar.gz ] && {
# wget http://prdownloads.sourceforge.net/libpng/zlib-1.2.8.tar.gz
# }

[ ! -f openssl-1.1.1.tar.gz ] && {
wget https://openssl.org/source/openssl-1.1.1.tar.gz
}

# Clean then Unzip

# [ -d zlib-1.2.8 ] && rm -fr zlib-1.2.8
[ -d openssl-1.1.1 ] && rm -fr openssl-1.1.1
# tar xf zlib-1.2.8.tar.gz
tar xf openssl-1.1.1.tar.gz
# tar xf libwebsockets.tar.gz

## configure and build zlib
#[ ! -f ./android-toolchain-arm/lib/libz.a ] && {
#cd zlib-1.2.8
#PATH=$TOOLCHAIN_PATH:$PATH ./configure --static --prefix=$TOOLCHAIN_PATH/..
#PATH=$TOOLCHAIN_PATH:$PATH make
#PATH=$TOOLCHAIN_PATH:$PATH make install
#cd ..
#}
#
# configure and build openssl
[ ! -f ./android-toolchain-arm/lib/libssl.a ] && {
cd openssl-1.1.1
## configure and build libwebsockets
#[ ! -f ./android-toolchain-arm/lib/libwebsockets.a ] && {
# cd libwebsockets
[ ! -d build ] && mkdir build
cd build
#  -H/Users\ccsta\git\pista\pista-core \
#  -B/Users\ccsta\git\pista\.externalNativeBuild\pista-core\android-26\debug\${TARGET_ARCH} \
${ANDROID_SDK}/cmake/3.6.4111459/bin/cmake --verbose \
  -DLWS_WITH_SHARED=OFF \
  -DLWS_WITH_STATIC=ON \
  -DLWS_WITHOUT_DAEMONIZE=ON \
  -DLWS_WITHOUT_TESTAPPS=ON \
  -DLWS_IPV6=OFF \
  -DLWS_WITH_BUNDLED_ZLIB=OFF \
  -DLWS_WITH_SSL=ON  \
  -DLWS_WITH_HTTP2=ON \
  -DLWS_OPENSSL_LIBRARIES="$DISTRIB_PATH/lib/libssl.a;$DISTRIB_PATH/../lib/libcrypto.a" \
  -DLWS_OPENSSL_INCLUDE_DIRS=${DISTRIB_PATH}/include \
  -DCMAKE_BUILD_TYPE=Debug \
  -DANDROID_ABI=${TARGET_ARCH} \
  -DANDROID_PLATFORM=android-26 \
  -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=intermediates/android-26/debug/obj/${TARGET_ARCH} \
  -DANDROID_NDK=${NDK} \
  -DCMAKE_CXX_FLAGS= \
  -DCMAKE_TOOLCHAIN_FILE=${NDK}/build/cmake/android.toolchain.cmake \
  -DCMAKE_MAKE_PROGRAM=${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja \
  "-GAndroid Gradle - Ninja" ../CMakeLists.txt

${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja
cd ..
}
