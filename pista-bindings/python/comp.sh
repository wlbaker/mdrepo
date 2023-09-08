#!/bin/sh

echo clean...

rm -rf ./build
rm -rf ./__pycache__

/bin/ls -alF

# MCCUL_DLL=../../src/hardware/mcc-ul/cbw64.dll
MCCUL_DLL=
PYTHON2=`which python2`
PYTHON3=`which ipython3`
PYTHON3=`which python3`
PYTHON3_LIBS=`pkg-config --libs python3`
EXPAT_LIBS=`pkg-config --libs expat`

platform=`uname -o`
unamestr=`uname`
SUDO=

if [[ "$unamestr" == 'Linux' ]]; then
	CC=gcc
	CXX=g++
	CFLAGS="-g -Wall -fPIC "
	LIBS="-lpista -lprotobuf-c"
	CXXLIBS="-lpistacxx -lprotobuf-c"
	OS=linux
	SUDO=sudo
elif [ \( "$platform" == 'Msys' \) -a \( "$unamestr" == "MINGW64_NT-10.0" \) ]; then
	CC=x86_64-w64-mingw32-gcc
	CXX=x86_64-w64-mingw32-g++
	CFLAGS="-g -Wall -I/mingw64/include/python3.6m"
	LIBS="-lpista -lprotobuf-c ${MCCUL_DLL} -lpthread -lpython3.6m"
	CXXLIBS="-Wl,-Bstatic -lpista -lpistacxx -lprotobuf-c ${MCCUL_DLL} ${EXPAT_LIBS} -lpthread -Wl,-Bdynamic ${PYTHON3_LIBS} -lyajl"
	PYTHON3=/mingw64/bin/python3
	OS=win32
elif [ \( "$unamestr" == 'cygwin' \) -o \( "$unamestr" == "CYGWIN_NT-6.1" \) ]; then
	CC=x86_64-w64-mingw32-gcc
	CXX=x86_64-w64-mingw32-g++
	CC=gcc
	CXX=g++
	CFLAGS="-g -Wall "
	LIBS="-lpista -lprotobuf-c ${MCCUL_DLL} -lpthread"
	CXXLIBS="-lpista -lpistacxx -lprotobuf-c ${MCCUL_DLL} -lpthread"
	OS=win32
else
	CC=gcc
	CXX=g++
	CFLAGS="-Wall -fPIC "
	LIBS="-lpista -lprotobuf-c"
	CXXLIBS="-lpista -lpistacxx -lprotobuf-c"
	OS=other
	SUDO=sudo
fi

echo os... ${OS}

# PYTHON=${PYTHON2}
# SWIG_FLAGS=
PYTHON=${PYTHON3}
SWIG_FLAGS="-py3 -threads"


CFLAGS="${CFLAGS} -I../cxx -I/usr/local/include/python3.6dm -DSWIG_PYTHON_THREADS"
# PYPISTA_SRC=/Users/william.l.baker2/git/pista/pista-core/bindings/python
# PYPISTA_SRC=`pwd`
PYPISTA_SRC=.

#
# the relative path ../../include is located inside the build directory for out-of-source-tree builds, and
# contains config.h
#

echo swig...
rm -f *wrap* pypista.py pypistax.py *.so
swig ${SWIG_FLAGS} -c++ -I${PYPISTA_SRC}/../../include -I../cxx -python -outcurrentdir ${PYPISTA_SRC}/../pistax.i
if [ $? -ne 0 ]; then
	echo "swig failed"
	return 1
fi
# swig ${SWIG_FLAGS}      -I${PYPISTA_SRC}/../../include -I../../include	 -python -outcurrentdir ${PYPISTA_SRC}/../pista.i

echo "*************************************************"

echo ${CXX} ${CFLAGS} -I../../include -I${PYPISTA_SRC}/../cxx -I${PYPISTA_SRC}/../../include -c pistax_wrap.cxx
${CXX} ${CFLAGS} -I../../include -I${PYPISTA_SRC}/../cxx -I${PYPISTA_SRC}/../../include -c pistax_wrap.cxx
# echo ${CXX} ${CFLAGS} -I../../include     -I${PYPISTA_SRC}/../../include -c pista_wrap.c
# ${CXX} ${CFLAGS} -I../../include     -I${PYPISTA_SRC}/../../include -c pista_wrap.c

echo "*"
echo "* Linking PYPISTAX library"
echo "*"

echo ${CXX} -shared pistax_wrap.o -o libpypistax.so -L../../.libs -L../cxx/.libs ${CXXLIBS}
${CXX} -shared pistax_wrap.o -o libpypistax.so -L../../.libs -L../cxx/.libs ${CXXLIBS} -lversion

echo "*"
echo "* Linking PYPISTA library"
echo "*"


#echo ${CXX} -shared pista_wrap.o  -o libpypista.so  -L../../.libs -L../cxx/.libs ${LIBS}
#${CXX} -shared pista_wrap.o  -o libpypista.so  -L../../.libs -L../cxx/.libs ${LIBS}

echo "*"
echo "* TESTING Python setup.py build/install"
echo "*"

${PYTHON} setup.py build
${SUDO} ${PYTHON} setup.py install

echo "*"
echo "* TESTING LIBRARY LOAD LDD: ${PYTHON} ${SWIG_FLAGS} on OS=${OS}"
echo "*"

TEST_PROG=demo-simu.py
TEST_PROG=demo-propaq.py

if [[ "$OS" == 'win32' ]]; then
	echo "/Windows test uses PATH"
	PATH=${PATH}:../../.libs:../cxx/.libs:. ldd libpypistax.so
else
	echo "Linux test uses LD_LIBRARY_PATH"
	LD_LIBRARY_PATH=/usr/local/lib:../../.libs:../cxx/.libs ldd libpypistax.so
	echo LD_LIBRARY_PATH=/usr/local/lib:../../.libs:../cxx/.libs ${PYTHON} -i ${TEST_PROG}
	LD_LIBRARY_PATH=/usr/local/lib:../../.libs:../cxx/.libs gdb ${PYTHON} -ex "set args -i ${TEST_PROG}"
fi



