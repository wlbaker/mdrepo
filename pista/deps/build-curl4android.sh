#!/bin/bash

# /opt/Android-Studio/ndk-bundle
export NDK=${ANDROID_SDKROOT}/ndk-bundle

# /opt/Android-Studio

export HOST_PLATFORM=`uname`
if [[ ${HOST_PLATFORM} == "Linux" ]]; then
    HOST_PLATFORM="linux"
elif [[ ${HOST_PLATFORM} == "Windows" ]]; then 
    HOST_PLATFORM="windows"
elif [[ ${HOST_PLATFORM} == MING* ]]; then
    HOST_PLATFORM="windows"
fi

export TOOLCHAIN_PATH=${NDK}/prebuilt/${HOST_PLATFORM}-x86_64/bin
export TARGET_ARCH=x86_64
export TARGET_ARCH=armeabi-v7a
export DISTRIB_PATH=`pwd`/../distribution/libs/${TARGET_ARCH}

set -e

# Download packages libz, openssl and libwebsockets

[ ! -f curl-7.61.1.tar.gz ] && {
wget http://curl.haxx.se/download/curl-7.61.1.tar.gz
}

# Clean then Unzip

[ -d curl-7.61.1 ] && rm -fr curl-7.61.1
tar xf curl-7.61.1.tar.gz

## configure and build libwebsockets
[ ! -f ../distribution/libs/curl.a ] && {
cd curl-7.61.1
#  -H/Users\ccsta\git\pista\pista-core \
#  -B/Users\ccsta\git\pista\.externalNativeBuild\pista-core\android-26\debug\${TARGET_ARCH} \
set -x

  # -DLWS_OPENSSL_LIBRARIES="$DISTRIB_PATH/lib/libssl.a;$DISTRIB_PATH/../lib/libcrypto.a" \
  # -DLWS_OPENSSL_INCLUDE_DIRS=${DISTRIB_PATH}/include \
  # -DOPENSSL_ROOT_DIR=`pwd`/../distribution//openssl-1.1.1 \
  # -DOPENSSL_ROOT_DIR=${DISTRIB_PATH} \

${ANDROID_SDKROOT}/cmake/3.6.4111459/bin/cmake --verbose \
  -DOPENSSL_ROOT_DIR=`pwd`/openssl-1.1.1 \
  -DOPENSSL_LIBRARIES="$DISTRIB_PATH/lib/libssl.a;$DISTRIB_PATH/../lib/libcrypto.a" \
  -DOPENSSL_INCLUDE_DIRS=${DISTRIB_PATH}/include \
  -DLWS_WITH_SHARED=OFF \
  -DLWS_WITH_STATIC=ON \
  -DLWS_WITHOUT_DAEMONIZE=ON \
  -DLWS_WITHOUT_TESTAPPS=ON \
  -DLWS_IPV6=OFF \
  -DLWS_WITH_BUNDLED_ZLIB=OFF \
  -DLWS_WITH_SSL=ON  \
  -DLWS_WITH_HTTP2=ON \
  -DCMAKE_BUILD_TYPE=Debug \
  -DANDROID_ABI=${TARGET_ARCH} \
  -DANDROID_PLATFORM=android-26 \
  -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${DISTRIB_PATH} \
  -DANDROID_NDK=${ANDROID_SDKROOT}/ndk-bundle \
  -DCMAKE_CXX_FLAGS=-I${DISTRIB_PATH}/include \
  -DCMAKE_TOOLCHAIN_FILE=${ANDROID_SDKROOT}/ndk-bundle/build/cmake/android.toolchain.cmake \
  -DCMAKE_MAKE_PROGRAM=${ANDROID_SDKROOT}/cmake/3.6.4111459/bin/ninja \
  "-GAndroid Gradle - Ninja" CMakeLists.txt
set +x

${ANDROID_SDKROOT}/cmake/3.6.4111459/bin/ninja
cd ..
}
