#!/bin/bash

# source deps/_shared.sh

export NINJA=`which ninja`
export CMAKE=`which cmake`
export SUDO=

set -u
set -e

if [[ -z "${DISTRIB_PATH}" ]]; then
	export DISTRIB_PATH=/usr
fi


# Download packages libz, openssl and libserialport
unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*) 
	    SUDO=sudo
	    ;;
    Darwin*)    machine=Mac;;
    CYGWIN*) ;;
    MINGW*)     
	    ;;
    *)          machine="UNKNOWN:${unameOut}"
esac
echo "Distribution path: ${DISTRIB_PATH}"

configure_make() {

  rm -f CMakeCache.txt

  # configure $*

  # echo "Configuring Protobuf ... with ARCH=${ARCH} and ABI=${ABI}"
  # set -x

    # -DProtobuf_LIBRARY=${DISTRIB_PATH}/${ABI}/lib/libprotobuf.so \
    # -DProtobuf_PROTOC_LIBRARY="${DISTRIB_PATH}/${ABI}/lib/libprotoc.so" \
    # -DANDROID_API=${ANDROID_API}
    # -DCMAKE_TOOLCHAIN_FILE=${ANDROID_SDK}/ndk-bundle/build/cmake/android.toolchain.cmake \

  ${CMAKE} --verbose \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX="${DISTRIB_PATH}" \
    -DCMAKE_MODULE_PATH="macros;/opt/DocBoxInc/cmake/modules" \
    -DCMAKE_PREFIX_PATH="${DISTRIB_PATH}" \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_C_COMPILER=gcc \
    -DCMAKE_CXX_COMPILER=g++ \
    -DCMAKE_CXX_FLAGS= \
    -DCMAKE_MAKE_PROGRAM=${NINJA} \
    "-GNinja" CMakeLists.txt

  set +x
  ${NINJA}

  if [[ $? -eq 0 ]]; then
    echo "Installing PISTA to distribution directory ..."
    ${SUDO} ${NINJA} install
  else
    echo "ERROR RETURN CODE: $?"
  fi
}

configure_make
