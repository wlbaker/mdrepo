#!/usr/bin/env bash

export NDK_ROOT=/opt/tools/Android/Sdk/ndk-bundle
export ANDROID_NDK=${NDK_ROOT}
export ANDROID_NDK_ROOT=${NDK_ROOT}
export CXXSTL=$NDK_ROOT/sources/cxx-stl/gnu-libstdc++
export ARCH="arm64-v8a"  
export ARCH="armeabl-v7a"
#export CFLAGS="-DANDROID -fpermissive -Wno-format -fPIC -fPIE -pie -g -O2 -I../protobuf/arm64build/include"
#export LDFLAGS="-Wl,--allow-shlib-undefined -fPIC -fPIE -pie -L$CXXSTL/libs/arm64-v8a/include -static-libstdc++ -L../protobuf/arm64build/lib"
#export CXXFLAGS="-std=c++03 -Wno-c++11-long-long -Wno-c++11-extensions -I$CXXSTL/include $CFLAGS"
#export CC="aarch64-linux-android-clang"
#export CXX="aarch64-linux-android-clang++"
#export AR="aarch64-linux-android-ar"  
#export RANLIB="aarch64-linux-android-ranlib"
#export STRIP="aarch64-linux-android-strip --strip-unneeded"  
#export READELF="aarch64-linux-android-readelf"  
#export MAKE="make -j4 CROSS_COMPILE_TARGET=yes"

source ./_shared.sh
configure_make() {
  ARCH=$1; ABI=$2;
  pushd protobuf-c

  configure $*

  rm -rf build/
  rm Makefile.in
  rm config.in
  make clean

  echo "Configuring protobuf-c ... with CC=${CC}"

  ./autogen.sh

  set -x
  # /opt/tools/Android/Sdk/ndk-bundle/prebuilt/linux-x86_64/bin/
  PATH=/opt/tools/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/bin:/opt/tools/Android/Sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin:${PATH} ./configure --host=arm-linux-android --target=arm-linux-android --build=x86_64-fedora-linux \
            --prefix=$(pwd)/build \
            CFLAGS="$CFLAGS" \
            LDFAGS="$LDFLAGS" \
            CXXFLAGS="$CXXFLAGS" \
            protobuf_CXXFLAGS="$CXXFLAGS" \
            protobuf_CFLAGS="$CFLAGS" \
            protobuf_LIBS="$LDFLAGS" \
            ac_cv_c_bigendian=no
  set +x

  echo "Making protobuf-c ..."
  $MAKE

  if [[ $# -eq 0 ]]; then
    echo "Installing protobuf-c to build directory ..."
    make install
    popd
  fi
}

for ((i=0; i < ${#ARCHS[@]}; i++))
do
  if [[ $# -eq 0 ]] || [[ "$1" == "${ARCHS[i]}" ]]; then
    # Do not build 64 bit arch if ANDROID_API is less than 21 which is
    # the minimum supported API level for 64 bit.
    [[ ${ANDROID_API} < 21 ]] && ( echo "${ABIS[i]}" | grep 64 > /dev/null ) && continue;
    configure_make "${ARCHS[i]}" "${ABIS[i]}"
  fi
done
