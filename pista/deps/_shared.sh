#!/bin/bash

export DISTRIB_PATH=`dirname "$0"`/../distribution/libs
echo "DISTRIB_PATH=${DISTRIB_PATH}"
pushd .
export DISTRIB_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
export DISTRIB_PATH="${DISTRIB_PATH}/../distribution/libs"
echo "REVISED DISTRIB_PATH=${DISTRIB_PATH}"
echo "REVISED PWD=`pwd`"
popd

TOOLS_ROOT=`pwd`
ARCH=`uname -m`
HOST='linux-x86_64'
GCC_TOOLS='NOT_SET_WLB'

#wlb -- default value?
export TOOL="arm-linux-androideabi"

export ANDROID_API=26
#
# Warning !!! Android Build !!!
#
# Default to API 21 for it is the minimum requirement for 64 bit archs.
# IF you need to build for min api level 16, you need to modify it to 14 and will not build for 64 bit archs.
# api level 16 build is better because api level 21 and higher may have problem like
#
#     https://github.com/openssl/openssl/issues/988
#     http://stackoverflow.com/questions/37122126/whats-the-exact-significance-of-android-ndk-platform-version-compared-to-api-le
#
# So if you not need 64 bit arch api level 16 is better
#
# But but but cURL could not build by android-20 and earlier :-(
# So you can build openssl with android-16 then build cURL with android-21
#
if [ "${1}" == "cURL" ]; then
    ANDROID_API=${ANDROID_API:-21}
fi
ANDROID_API=${ANDROID_API:-26}
echo "API=${ANDROID_API}"

# ARCHS=("android" "android-armeabi" "android64-aarch64" "android-x86" "android64" "android-mips" "android-mips64")
# ABIS=("armeabi" "armeabi-v7a" "arm64-v8a" "x86" "x86_64" "mips" "mips64")

ARCHS=("android64-aarch64" "android-armeabi" "android-x86_64" )
ABIS=("arm64-v8a" "armeabi-v7a" "x86_64" )

# ARCHS=("android-x86_64" )
# ABIS=("x86_64" )

# ARCHS=("android-armeabi" )
# ABIS=("armeabi-v7a" )

NDK=${ANDROID_NDK}

configure() {
  ARCH=$1; OUT=$2; CLANG=${3:-""};

  echo "WLB: ARCH in _shared: ${ARCH}"
  export TARGET_ARCH=moo

  if [ "$ARCH" == "android" ]; then
    export ARCH_FLAGS="-mthumb"
    export ARCH_LINK=""
    export TOOL="arm-linux-androideabi"
    export GCC_TOOLS="arm-linux-androideabi"
    NDK_FLAGS="--arch=arm"
  elif [ "$ARCH" == "android-armeabi" ]; then
    export ARCH_FLAGS="-march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb -mfpu=neon"
    export ARCH_LINK="-march=armv7-a -Wl,--fix-cortex-a8"
    export TOOL="arm-linux-androideabi"
    export GCC_TOOLS="arm-linux-androideabi"
    export TARGET_ARCH="armeabi-v7a"
    NDK_FLAGS="--arch=arm"
  elif [ "$ARCH" == "android64-aarch64" ]; then
    export ARCH_FLAGS=""
    export ARCH_LINK=""
    export TOOL="aarch64-linux-android"
    export TARGET_ARCH="arm64-v8a"
    export GCC_TOOLS="aarch64-linux-android"
    NDK_FLAGS="--arch=arm64"
  elif [ "$ARCH" == "android-x86" ]; then
    export ARCH_FLAGS="-march=i686 -mtune=intel -msse3 -mfpmath=sse -m32"
    export ARCH_LINK=""
    export TOOL="i686-linux-android"
    export GCC_TOOLS="i686-linux-android"
    NDK_FLAGS="--arch=x86"
  elif [ "$ARCH" == "android-x86_64" ]; then
      echo "Building for $ARCH..."
    export ARCH_FLAGS="-march=x86-64 -msse4.2 -mpopcnt -m64 -mtune=intel"
    export ARCH_LINK=""
    export TOOL="x86_64"
    export GCC_TOOLS="x86_64-linux-android"
    export TARGET_ARCH="x86_64"
    NDK_FLAGS="--arch=x86_64"
  elif [ "$ARCH" == "android64" ]; then
    export ARCH_FLAGS="-march=x86-64 -msse4.2 -mpopcnt -m64 -mtune=intel"
    export ARCH_LINK=""
    export TOOL="x86_64-linux-android"
    export TARGET_ARCH="x86_64"
    export GCC_TOOLS="x86_64-linux-android"
    NDK_FLAGS="--arch=x86_64"
  elif [ "$ARCH" == "android-mips" ]; then
    export ARCH_FLAGS=""
    export ARCH_LINK=""
    export TOOL="mipsel-linux-android"
    NDK_FLAGS="--arch=mips"
  elif [ "$ARCH" == "android-mips64" ]; then
    export ARCH="linux64-mips64"
    export ARCH_FLAGS=""
    export ARCH_LINK=""
    export TOOL="mips64el-linux-android"
    NDK_FLAGS="--arch=mips64"
  else
      echo "Unknown ARCH in _shared: ${ARCH}"
      exit 0
  fi;

  echo "WLB: TOOL in _shared: ${TOOL}"
  echo "WLB: GCC_TOOLS in _shared: ${GCC_TOOLS}"
  TOOLCHAIN_ROOT=${NDK_ROOT}/toolchains/llvm/prebuilt/${HOST}

  export TOOLCHAIN_PATH=${TOOLCHAIN_ROOT}/bin
  export NDK_TOOLCHAIN_BASENAME=${NDK_ROOT}/toolchains/${TOOL}-4.9/prebuilt/${HOST}/${GCC_TOOLS}/bin
  #wlb export SYSROOT=${TOOLCHAIN_ROOT}/sysroot
  export SYSROOT=${NDK}/sysroot/usr/lib/${GCC_TOOLS}
	# aarch64-linux-android/
	# arm-linux-androideabi/
	# i686-linux-android/
	# x86_64-linux-android/
  
  # see openssl-1.1.1/NOTES.ANDROID
  # export CROSS_SYSROOT=$SYSROOT

  #if [ -z "${CLANG}" ]; then
    #export CC=${NDK_TOOLCHAIN_BASENAME}-gcc
    #export CXX=${NDK_TOOLCHAIN_BASENAME}-g++
  #else
    export CC=${TOOLCHAIN_PATH}/clang
    export CXX=${TOOLCHAIN_PATH}/clang++
  #fi;
  export LINK=${CXX}
  export LD=${NDK_TOOLCHAIN_BASENAME}/ld
  export AR=${NDK_TOOLCHAIN_BASENAME}/ar
  export RANLIB=${NDK_TOOLCHAIN_BASENAME}/ranlib
  export STRIP=${NDK_TOOLCHAIN_BASENAME}/strip
  export CPPFLAGS=${CPPFLAGS:-""}
  export LIBS=${LIBS:-""}
  export CFLAGS="${ARCH_FLAGS} -fpic -ffunction-sections -funwind-tables -fstack-protector -fno-strict-aliasing -finline-limit=64"
  export CXXFLAGS="${CFLAGS} -std=c++11 -frtti -fexceptions"
  export LDFLAGS="${ARCH_LINK}"
  export TOOL="${TOOL}"
  echo "**********************************************"
  echo "use ANDROID_API=${ANDROID_API}"
  echo "use NDK=${NDK}"
  echo "export ARCH=${ARCH}"
  echo "export NDK_TOOLCHAIN_BASENAME=${NDK_TOOLCHAIN_BASENAME}"
  echo "export SYSROOT=${SYSROOT}"
  echo "export CC=${CC}"
  echo "export CXX=${CXX}"
  echo "export LINK=${LINK}"
  echo "export LD=${LD}"
  echo "export AR=${AR}"
  echo "export RANLIB=${RANLIB}"
  echo "export STRIP=${STRIP}"
  echo "export CPPFLAGS=${CPPFLAGS}"
  echo "export CFLAGS=${CFLAGS}"
  echo "export CXXFLAGS=${CXXFLAGS}"
  echo "export LDFLAGS=${LDFLAGS}"
  echo "export LIBS=${LIBS}"
  echo "export TOOL=${TOOL}"
  echo "**********************************************"
}
