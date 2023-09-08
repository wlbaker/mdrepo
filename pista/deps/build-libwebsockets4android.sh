#!/bin/bash

#
# Build libwebsockets static library for Android
#
# This is based on http://stackoverflow.com/questions/11929773/compiling-the-latest-openssl-for-android/
# via https://github.com/warmcat/libwebsockets/pull/502

# path to NDK
export NDK=${ANDROID_SDK}/ndk-bundle
export SDK=${ANDROID_SDK}
export TOOLCHAIN_PATH=${NDK}/prebuilt/windows-x86_64/bin
export TARGET_ARCH=x86_64
export TARGET_ARCH=armeabi-v7a
export ABI=armeabi-v7a
export DISTRIB_PATH=`pwd`/../distribution/libs

set -u
source ./_shared.sh cURL

set -e

# Download packages libz, openssl and libwebsockets

# [ ! -f zlib-1.2.8.tar.gz ] && {
# wget http://prdownloads.sourceforge.net/libpng/zlib-1.2.8.tar.gz
# }
# [ -d zlib-1.2.8 ] && rm -fr zlib-1.2.8
# tar xf zlib-1.2.8.tar.gz

[ ! -f libwebsockets.tar.gz ] && {
    git clone https://github.com/warmcat/libwebsockets.git
    tar caf libwebsockets.tar.gz libwebsockets
}

# Clean then Unzip

configure_make() {
  ARCH=$1; ABI=$2;
  [ -d libwebsockets ] && rm -fr libwebsockets
  tar xf libwebsockets.tar.gz
  echo ARCH=${ARCH}
  echo ABI=${ABI}

  ## configure and build libwebsockets
  cd libwebsockets
  git checkout v3.0.1
  #[ ! -d build ] && mkdir build
  #cd build
  #  -H/Users\ccsta\git\pista\pista-core \
  #  -B/Users\ccsta\git\pista\.externalNativeBuild\pista-core\android-26\debug\${TARGET_ARCH} \
  set -x
  ${SDK}/cmake/3.6.4111459/bin/cmake --verbose \
    -DLWS_WITH_SHARED=OFF \
    -DLWS_WITH_STATIC=ON \
    -DLWS_WITHOUT_DAEMONIZE=ON \
    -DLWS_WITHOUT_TESTAPPS=ON \
    -DLWS_IPV6=OFF \
    -DLWS_WITH_BUNDLED_ZLIB=OFF \
    -DLWS_WITH_SSL=ON  \
    -DLWS_WITH_HTTP2=ON \
    -DLWS_OPENSSL_LIBRARIES="$DISTRIB_PATH/${ABI}/lib/libssl.a;$DISTRIB_PATH/${ABI}/lib/libcrypto.a" \
    -DLWS_OPENSSL_INCLUDE_DIRS=${DISTRIB_PATH}/${ABI}/include \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX="${DISTRIB_PATH}/${ABI}" \
    -DANDROID_ABI=${TARGET_ARCH} \
    -DANDROID_PLATFORM=android-26 \
    -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=intermediates/android-26/debug/obj/${TARGET_ARCH} \
    -DANDROID_NDK=${NDK} \
    -DCMAKE_CXX_FLAGS= \
    -DCMAKE_TOOLCHAIN_FILE=${NDK}/build/cmake/android.toolchain.cmake \
    -DCMAKE_MAKE_PROGRAM=${SDK}/cmake/3.6.4111459/bin/ninja \
    "-GAndroid Gradle - Ninja" CMakeLists.txt

  ${SDK}/cmake/3.6.4111459/bin/ninja install
  set +x
  cd ..
}

for ((i=0; i < ${#ARCHS[@]}; i++))
do
  if [[ $# -eq 0 ]] || [[ "$1" == "${ARCHS[i]}" ]]; then
    [[ ${ANDROID_API} < 21 ]] && ( echo "${ABIS[i]}" | grep 64 > /dev/null ) && continue;
    configure_make "${ARCHS[i]}" "${ABIS[i]}"
  fi
done


