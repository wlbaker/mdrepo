#!/bin/bash

if [[ -z "${DISTRIB_PATH}" ]]; then
	export DISTRIB_PATH=/usr
fi

set -u

# Download packages libz, openssl and libwebsockets

[ ! -f protobuf-c.tar.gz ] && {
    git clone https://github.com/protobuf-c/protobuf-c.git
    tar caf protobuf-c.tar.gz protobuf-c
}

# Clean then Unzip

configure_make() {
  [ -d protobuf-c ] && rm -fr protobuf-c
  tar xf protobuf-c.tar.gz

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

    # -DProtobuf_LIBRARIES=${DISTRIB_PATH}/${ABI}/lib/libprotobuf.so \
    # -DProtobuf_INCLUDE_DIR=${DISTRIB_PATH}/${ABI}/include \
    # -DProtobuf_PROTOC_LIBRARY="${DISTRIB_PATH}/${ABI}/lib/libprotoc.so" \
    

    # 110519 WLB: -lprotobuf is already included
    # -DCMAKE_CXX_STANDARD_LIBRARIES="/usr/lib64/libprotobuf.so" \
    # ...it would be different on UBUNTU anyway.../usr/lib/x86_64-linux-gnu/libprotobuf.so
  /usr/bin/cmake --verbose \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_C_COMPILER=gcc \
    -DCMAKE_CXX_COMPILER=g++ \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${DISTRIB_PATH}" \
    -DCMAKE_MODULE_PATH="${DISTRIB_PATH}/lib/pkgconfig" \
    -DCMAKE_CXX_FLAGS= \
    -DCMAKE_MAKE_PROGRAM=`which ninja` \
    "-GNinja" CMakeLists.txt

  /usr/bin/ninja

  if [[ $? -eq 0 ]]; then
    echo "Installing Protobuf-C to build directory ..."
    echo `pwd` 
    sudo /usr/bin/ninja install
  else
    echo "ERROR RETURN CODE: $?"
  fi
  set +x
  popd
}

configure_make "linux" "x86_64"


