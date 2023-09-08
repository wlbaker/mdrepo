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
source ./_shared.sh protobuf-c

set -e

# Download packages libz, openssl and libwebsockets

# [ ! -f zlib-1.2.8.tar.gz ] && {
# wget http://prdownloads.sourceforge.net/libpng/zlib-1.2.8.tar.gz
# }
# [ -d zlib-1.2.8 ] && rm -fr zlib-1.2.8
# tar xf zlib-1.2.8.tar.gz

[ ! -f protobuf-c.tar.gz ] && {
    git clone https://github.com/protobuf-c/protobuf-c.git
    tar caf protobuf-c.tar.gz protobuf-c
}

# Clean then Unzip

configure_make() {
  ARCH=$1; ABI=$2;
  [ -d protobuf-c ] && rm -fr protobuf-c
  tar xf protobuf-c.tar.gz
  echo ARCH=${ARCH}
  echo ABI=${ABI}

  configure $*

  ## configure and build libwebsockets
  pushd protobuf-c
  git checkout v1.3.1
  # patch -p1 -i ../protobuf-c.patch1

  cd build-cmake
  #  -H/Users\ccsta\git\pista\pista-core \
  #  -B/Users\ccsta\git\pista\.externalNativeBuild\pista-core\android-26\debug\${TARGET_ARCH} \
  # -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=intermediates/android-26/debug/obj/${TARGET_ARCH} \
  set -x

  # export Protobuf_LIBRARIES=${DISTRIB_PATH}/${ABI}/lib/libprotobuf.so
  #    :${DISTRIB_PATH}/${ABI}/lib/libprotobuf.so

  ${ANDROID_SDK}/cmake/3.6.4111459/bin/cmake --verbose \
    -DProtobuf_LIBRARIES=${DISTRIB_PATH}/${ABI}/lib/libprotobuf.so \
    -DProtobuf_INCLUDE_DIR=${DISTRIB_PATH}/${ABI}/include \
    -DProtobuf_PROTOC_LIBRARY="${DISTRIB_PATH}/${ABI}/lib/libprotoc.so" \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${DISTRIB_PATH}/${ABI}" \
    -DCMAKE_MODULE_PATH="${DISTRIB_PATH}/${ABI}/lib/pkgconfig" \
    -DANDROID_ABI=${TARGET_ARCH} \
    -DANDROID_PLATFORM=android-${ANDROID_API} \
    -DANDROID_NDK=${ANDROID_NDK} \
    -DCMAKE_CXX_FLAGS= \
    -DCMAKE_CXX_STANDARD_LIBRARIES="${DISTRIB_PATH}/${ABI}/lib/libprotobuf.so" \
    -DCMAKE_TOOLCHAIN_FILE=${ANDROID_SDK}/ndk-bundle/build/cmake/android.toolchain.cmake \
    -DCMAKE_MAKE_PROGRAM=${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja \
    "-GAndroid Gradle - Ninja" CMakeLists.txt

  ${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja

  if [[ $? -eq 0 ]]; then
    echo "Installing Protobuf-C to build directory ..."
    echo `pwd` 
    ${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja install
  else
    echo "ERROR RETURN CODE: $?"
  fi
  set +x
  popd
  [ -d protobuf-c ] && rm -fr protobuf-c
}

for ((i=0; i < ${#ARCHS[@]}; i++))
do
  if [[ $# -eq 0 ]] || [[ "$1" == "${ARCHS[i]}" ]]; then
    [[ ${ANDROID_API} < 21 ]] && ( echo "${ABIS[i]}" | grep 64 > /dev/null ) && continue;
    configure_make "${ARCHS[i]}" "${ABIS[i]}"
  fi
done


