#!/bin/sh

if [[ -z "${DISTRIB_PATH}" ]]; then
  DISTRIB_PATH=/mingw64/usr
fi


echo "Building SWIG bindings for distribution: ${DISTRIB_PATH}"

export JAVA_HOME=/c/opt/jdk/latest

#-DCMAKE_MODULE_PATH=macros \
/mingw64/bin/cmake --verbose \
  -DCMAKE_INSTALL_PREFIX="${DISTRIB_PATH}" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH="${DISTRIB_PATH}/lib/pkgconfig"  \
  "-GNinja" CMakeLists.txt 

# "-GMinGW Makefiles" CMakeLists.txt 
# "-GUnix Makefiles" CMakeLists.txt 

# -H/C/opt/git/pista/pista-core -B/C/opt/git/pista/.externalNativeBuild/pista-core/mingw64/debug/x86_64 \
#-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=/C/opt/git/pista/build/intermediates/mingw64/debug/obj/x86_64 \
#-DCMAKE_C_COMPILER=gcc   \
#-DCMAKE_CXX_COMPILER=g++ \
#-DCMAKE_MAKE_PROGRAM=/usr/bin/make.exe \