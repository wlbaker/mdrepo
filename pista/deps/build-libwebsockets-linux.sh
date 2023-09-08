#!/bin/bash

#
# Build libwebsockets static library for Android
#
# This is based on http://stackoverflow.com/questions/11929773/compiling-the-latest-openssl-for-android/
# via https://github.com/warmcat/libwebsockets/pull/502

# path to NDK
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

# Download packages libz, openssl and libwebsockets

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
  pushd libwebsockets
  git checkout v3.1-stable
  #[ ! -d build ] && mkdir build
  #cd build
  #  -H/Users\ccsta\git\pista\pista-core \
  #  -B/Users\ccsta\git\pista\.externalNativeBuild\pista-core\android-26\debug\${TARGET_ARCH} \
  # -DLWS_OPENSSL_LIBRARIES="$DISTRIB_PATH/${ABI}/lib/libssl.a;$DISTRIB_PATH/${ABI}/lib/libcrypto.a" \
  # -DLWS_OPENSSL_INCLUDE_DIRS=${DISTRIB_PATH}/${ABI}/include \
  # -DCMAKE_C_FLAGS="-Wpointer-sign" \
  # -DCMAKE_CXX_FLAGS="-Wpointer-sign" \
  #  -DCMAKE_CXX_STANDARD_LIBRARIES="/usr/lib64/libprotobuf.so" \
  set -x
  ${CMAKE} --verbose \
    -DLWS_WITH_SHARED=ON \
    -DLWS_WITH_STATIC=ON \
	-DLWS_STATIC_PIC=ON \
    -DLWS_WITHOUT_DAEMONIZE=ON \
    -DLWS_WITHOUT_TESTAPPS=ON \
    -DLWS_IPV6=OFF \
    -DLWS_WITH_BUNDLED_ZLIB=OFF \
    -DLWS_WITH_SSL=ON  \
    -DLWS_WITH_HTTP2=ON \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_C_COMPILER=gcc \
    -DCMAKE_CXX_COMPILER=g++ \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${DISTRIB_PATH}" \
    -DCMAKE_MODULE_PATH="${DISTRIB_PATH}/lib/pkgconfig" \
    -DCMAKE_MAKE_PROGRAM=${NINJA} \
    "-GNinja" CMakeLists.txt

  ${NINJA}
  if [[ $? -eq 0 ]]; then
    echo "Installing LIBWEBSOCKETS to DISTRIB directory ..."
    echo `pwd` 
    ${SUDO} ${NINJA} install
  else
    echo "ERROR RETURN CODE: $?"
  fi
  set +x
  popd
}

configure_make "linux" "x86_64"


