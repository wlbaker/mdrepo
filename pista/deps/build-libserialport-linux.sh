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
    # git clone https://github.com/scottmudge/libserialport-cmake.git
    # mv libserialport-cmake libserialport

    git clone https://github.com/sigrokproject/libserialport.git

    tar caf libserialport.tar.gz libserialport
}

# Clean then Unzip

configure_make() {
  [ -d libserialport ] && rm -fr libserialport
  tar xf libserialport.tar.gz

  ## configure and build libserialport
  pushd libserialport
  set -x
  ./autogen.sh
  ./configure --prefix=${DISTRIB_PATH}
  make

  if [[ $? -eq 0 ]]; then
    echo "Installing LIBSERIALPORT to distribution directory ..."
    echo `pwd` 
    ${SUDO} make install
  else
    echo "ERROR RETURN CODE: $?"
  fi
  set +x
  popd
}

configure_make


