#!/bin/bash

#
# Build libserialport static library for Android
#
# This is based on http://stackoverflow.com/questions/11929773/compiling-the-latest-openssl-for-android/
# via https://github.com/warmcat/libserialport/pull/502

set -u
set -e

if [[ -z "${DISTRIB_PATH}" ]]; then
	export DISTRIB_PATH=/usr
fi

NINJA=`which ninja`
SUDO=

# Download packages libz, openssl and libserialport
unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*) 
	    SUDO=sudo
	    ;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    ;;
    MINGW*)     ;;
    *)          machine="UNKNOWN:${unameOut}"
esac
echo "Distribution path: ${DISTRIB_PATH}"

[ ! -f libserialport.tar.gz ] && {
    # git clone git://sigrok.org/libserialport.git

    # use scott mudge's fork since it has cmake
    git clone https://github.com/scottmudge/libserialport-cmake.git
    mv libserialport-cmake libserialport

    tar caf libserialport.tar.gz libserialport
}

# Clean then Unzip

configure_make() {
  ARCH=$1; ABI=$2;
  [ -d libserialport ] && rm -fr libserialport
  tar xf libserialport.tar.gz
  echo ARCH=${ARCH}
  echo ABI=${ABI}

  ## configure and build libserialport
  pushd libserialport
  # git checkout libserialport-0.1.1
  #[ ! -d build ] && mkdir build
  #cd build
  #  -H/Users\ccsta\git\pista\pista-core \
  #  -B/Users\ccsta\git\pista\.externalNativeBuild\pista-core\android-26\debug\${TARGET_ARCH} \
  # -DLWS_OPENSSL_LIBRARIES="$DISTRIB_PATH/${ABI}/lib/libssl.a;$DISTRIB_PATH/${ABI}/lib/libcrypto.a" \
  # -DLWS_OPENSSL_INCLUDE_DIRS=${DISTRIB_PATH}/${ABI}/include \
  set -x
  cmake --verbose \
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
    echo "Installing LIBSERIALPORT to distribution directory ..."
    echo `pwd` 
    ${SUDO} ${NINJA} install
  else
    echo "ERROR RETURN CODE: $?"
  fi
  set +x
  popd
}

configure_make "mingw64" "x86_64"


