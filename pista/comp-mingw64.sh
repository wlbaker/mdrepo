#!/bin/sh

echo "Although build scripts have been generated, it may be necessary to build dependencies found in the \"deps\" directory."
echo "*"
echo "************************WARNING************************"
echo "*"
echo "ISSUE #1: It may be necessary to add msys64 explicitly to the PKG_CONFIG_PATH, ie, "
echo "export PKG_CONFIG_PATH=/mingw64/lib/pkgconfig:/mingw64/share/pkgconfig:/msys64/mingw64/lib/pkgconfig"
echo "ISSUE #2: cmake may still pick up the wrong version of pkg-config msys2 instead of mingw64, this will cause errors"
echo "          one possible fix: patch FindPkgConfig.cmake add line before execute_process:"
echo "          set(ENV{PKG_CONFIG_PATH} \"/mingw64/lib/pkgconfig:/mingw64/share/pkgconfig:/lib/pkgconfig\")"

if [[ -z "${DISTRIB_PATH}" ]]; then
  DISTRIB_PATH=/mingw64/usr
fi


/mingw64/bin/cmake --verbose -E PKG_CONFIG_PATH \
  -DCMAKE_INSTALL_PREFIX="${DISTRIB_PATH}" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_MODULE_PATH=macros \
  "-GNinja" CMakeLists.txt 

# 052319  -DCMAKE_PREFIX_PATH="${DISTRIB_PATH}/lib/pkgconfig"  \
# 052319  -DCMAKE_PREFIX_PATH="${DISTRIB_PATH}/cmake/lib/pkgconfig"  \

# "-GMinGW Makefiles" CMakeLists.txt 
# "-GUnix Makefiles" CMakeLists.txt 

# -H/C/opt/git/pista/pista-core -B/C/opt/git/pista/.externalNativeBuild/pista-core/mingw64/debug/x86_64 \
#-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=/C/opt/git/pista/build/intermediates/mingw64/debug/obj/x86_64 \
#-DCMAKE_C_COMPILER=gcc   \
#-DCMAKE_CXX_COMPILER=g++ \
#-DCMAKE_MAKE_PROGRAM=/usr/bin/make.exe \
