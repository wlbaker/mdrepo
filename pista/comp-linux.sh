#!/bin/bash

# source deps/_shared.sh

export DISTRIB_PATH=/mingw64
export NINJA=`which ninja`
export CMAKE=`which cmake`
export SUDO=

set -u
set -e

# Download packages libz, openssl and libserialport
unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*) 
	    DISTRIB_PATH=/usr/local
	    DISTRIB_PATH=/opt/bernard
	    SUDO=sudo
	    ;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    DISTRIB_PATH=/usr/local;;
    MINGW*)     
	    DISTRIB_PATH=/mingw64
	    ;;
    *)          machine="UNKNOWN:${unameOut}"
esac
echo "Distribution path: ${DISTRIB_PATH}"

export LOCAL_PROTOBUF_C_LIB=${DISTRIB_PATH}/lib/libprotobuf-c.so
export LOCAL_WEBSOCKETS_LIB=${DISTRIB_PATH}/lib/libwebsockets.so

configure_make() {
  # ARCH=$1; ABI=$2;

  rm -f CMakeCache.txt

  # configure $*

  # echo "Configuring Protobuf ... with ARCH=${ARCH} and ABI=${ABI}"
  # set -x

    # -DProtobuf_LIBRARY=${DISTRIB_PATH}/${ABI}/lib/libprotobuf.so \
    # -DProtobuf_PROTOC_LIBRARY="${DISTRIB_PATH}/${ABI}/lib/libprotoc.so" \
    # -DANDROID_API=${ANDROID_API}
    # -DCMAKE_TOOLCHAIN_FILE=${ANDROID_SDK}/ndk-bundle/build/cmake/android.toolchain.cmake \

    # -DWebsockets_LIBRARY=${LOCAL_WEBSOCKETS_LIB} \
    # -DProtobufC_LIBRARY=${LOCAL_PROTOBUF_C_LIB} \
  ${CMAKE} \
    -DLWS_WITH_SHARED=ON \
    -DLWS_WITH_STATIC=ON \
	-DLWS_STATIC_PIC=ON \
    -DLWS_WITHOUT_DAEMONIZE=ON \
    -DLWS_WITHOUT_TESTAPPS=ON \
    -DLWS_IPV6=OFF \
    -DLWS_WITH_BUNDLED_ZLIB=OFF \
    -DLWS_WITH_SSL=ON  \
    -DLWS_WITH_HTTP2=ON \
    -DProtobuf_INCLUDE_DIR=${DISTRIB_PATH}/include \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX="${DISTRIB_PATH}" \
    -DCMAKE_MODULE_PATH="macros;${DISTRIB_PATH}/lib/cmake/libwebsockets" \
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

configure_make linux x86_64 
