#!/bin/sh

# source deps/_shared.sh

export DISTRIB_PATH=/usr/local
export NINJA=`which ninja`
export CMAKE=`which cmake`
export SUDO=
export LOcAL_PROTOBuF_C_LIB=${DISTRIB_PATH}/lib/libprotobuf-c.so

# Download packages libz, openssl and libserialport
unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*) 
	    DISTRIB_PATH=/usr/local
	    SUDO=sudo
	    ;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    DISTRIB_PATH=/usr/local;;
    MINGW*)     
	    DISTRIB_PATH=/mingw64
	    LOCAL_PROTOBUF_C_LIB=/mingw64/lib/libprotobuf-c.dll.a
	    LOCAL_WEBSOCKETS_LIB=/mingw64/lib/libwebsockets.dll.a
	    ;;
    *)          machine="UNKNOWN:${unameOut}"
esac
echo "Distribution path: ${DISTRIB_PATH}"

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

  ${CMAKE} --verbose \
    -DProtobufC_LIBRARY=${LOCAL_PROTOBUF_C_LIB} \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX="${DISTRIB_PATH}" \
    -DCMAKE_MODULE_PATH="${DISTRIB_PATH}/lib/pkgconfig" \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_C_COMPILER=gcc \
    -DCMAKE_C_FLAGS= -I${DISTRIB_PATH}/include \
    -DCMAKE_MAKE_PROGRAM=${NINJA} \
    "-GNinja" CMakeLists.txt

  set +x
  ${NINJA}

  if [[ $? -eq 0 ]]; then
    echo "Installing PISTA to distribution directory ..."
    ${SUDO} ${NINJA} install
    # sudo /usr/bin/ninja install
  else
    echo "ERROR RETURN CODE: $?"
  fi
}

configure_make linux x86_64 
