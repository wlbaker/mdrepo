#!/usr/bin/env bash

export NDK_ROOT=/opt/tools/Android/Sdk/ndk-bundle
export ANDROID_NDK=${NDK_ROOT}
export ANDROID_NDK_ROOT=${NDK_ROOT}
export CXXSTL=$NDK_ROOT/sources/cxx-stl/gnu-libstdc++

source ./_shared.sh

echo "ARCHS=${ARCHS}"

LIB_VER=3.6.1
# LIB_VER=3.5.0
# 3.5.0: requires patch
# 3.6.1: clean compile 
LIB_NAME="protobuf-all-${LIB_VER}.zip"
[ -f "${LIB_NAME}" ] || wget https://github.com/protocolbuffers/protobuf/releases/download/v${LIB_VER}/${LIB_NAME};

configure_make() {
  ARCH=$1; ABI=$2;
  rm -rf protobuf-$LIB_VER
  unzip ${LIB_NAME}
  pushd protobuf-$LIB_VER
  mkdir build-${ARCH}
  cd build-${ARCH}

  configure $*

  echo "Configuring Protobuf ... with ARCH=${ARCH} and ABI=${ABI} TARGET_ARCH=${TARGET_ARCH}"

  #
  # For info on -Dprotobuf_BUILD_PROTOC_BINARIES
  # https://github.com/protocolbuffers/protobuf/pull/3878
  # 

  set -x
  ${ANDROID_SDK}/cmake/3.6.4111459/bin/cmake --verbose \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${DISTRIB_PATH}/${ABI} \
    -DANDROID_ABI=${TARGET_ARCH} \
    -DANDROID_PLATFORM=android-26 \
    -DANDROID_NDK=${ANDROID_SDK}/ndk-bundle \
    -DCMAKE_TOOLCHAIN_FILE=${ANDROID_SDK}/ndk-bundle/build/cmake/android.toolchain.cmake \
    -DCMAKE_MAKE_PROGRAM=${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja \
    -Dprotobuf_BUILD_SHARED_LIBS=ON \
    -Dprotobuf_BUILD_PROTOC_BINARIES=ON \
    -Dprotobuf_BUILD_EXAMPLES=off \
    -Dprotobuf_BUILD_TESTS=off \
    -DANDROID_CPP_FEATURES="rtti exceptions" \
    -DANDROID_LINKER_FLAGS="-landroid -llog" \
    "-GAndroid Gradle - Ninja" ../cmake/CMakeLists.txt
  set +x

  ${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja -C ../cmake

  if [[ $? -eq 0 ]]; then
    echo "Installing Protobuf to build directory ..."
    ${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja -C ../cmake install
  else
    echo "ERROR RETURN CODE: $?"
  fi
  popd
}

for ((i=0; i < ${#ARCHS[@]}; i++))
do
    echo "Preparing $#==0 and ${ARCHS[i]}...ANDROID_API=${ANDROID_API}"
  if [[ $# -eq 0 ]] || [[ "$1" == "${ARCHS[i]}" ]]; then
    # Do not build 64 bit arch if ANDROID_API is less than 21 which is
    # the minimum supported API level for 64 bit.
    [[ ${ANDROID_API} < 21 ]] && ( echo "${ABIS[i]}" | grep 64 > /dev/null ) && continue;
    configure_make "${ARCHS[i]}" "${ABIS[i]}"
  fi
done
