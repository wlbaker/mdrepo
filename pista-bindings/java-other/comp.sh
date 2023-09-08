#!/bin/bash

# exit on error
abort()
{
    echo >&2 '
***************
*** ABORTED ***
***************
'
    echo "An error occurred. Exiting..." >&2
    exit 1
}

trap 'abort' 0

set -e
echo clean...

rm -rf gen/org
mkdir -p gen/org/pista gen/org/pistax

builddir=/opt/tools/pista

if [ -z "$JDK_HOME" ]; then
    JDK_HOME=/usr/lib/jvm/java-8-oracle
    JDK_HOME=/usr/java/latest
    echo "Checking ${JDK_HOME} for JDK..." 
fi  

if [ ! -d "$JDK_HOME" ]; then
    JDK_HOME=/opt/jdk/latest
    echo "Checking ${JDK_HOME} for JDK..." 
fi

if [ ! -d "$JDK_HOME" ]; then
    echo "JDK_HOME could not be found."
    abort
fi

echo "JDK_HOME set to default: $JDK_HOME"

platform=`uname -o`
unamestr=`uname`

RXTX_JAR="ref/RXTXcomm.jar:intf:gen"

if [[ "$unamestr" == 'Linux' ]]; then
	CC=gcc
	CXX=g++
	CFLAGS="-g -Wall -fPIC -std=c++14"
	LIBS="-lpistacxx -lpista -lprotobuf-c"
	OS=linux
	PISTAX_SO=libjpistax.so
elif [ \( "$platform" == 'Msys' \) -a \( "$unamestr" == "MINGW64_NT-10.0" \) ]; then
	CC=x86_64-w64-mingw32-gcc
	CXX=x86_64-w64-mingw32-g++
	CFLAGS="-g -Wall"
	LIBS="-Wl,-Bstatic -lpista -lpistacxx -lprotobuf-c ${MCCUL_DLL} -lpthread -lexpat"
	CXXLIBS="-lpistacxx -lprotobuf-c ${MCCUL_DLL} -lpthread"
	RXTX_JAR="ref/RXTXcomm.jar\;intf\;gen"
	OS=win32
	PISTAX_SO=jpistax.dll
elif [ \( "$unamestr" == 'cygwin' \) -o \( "$unamestr" == "CYGWIN_NT-6.1" \) ]; then

	# well..this could be 32bit or 64bit mingw32
	# CC=x86_64-w64-mingw32-gcc
	# CXX=x86_64-w64-mingw32-g++

	CFLAGS="-g -Wall -std=c++14"
	# FIXME LIBS="-lpistacxx -lpista -lprotobuf-c ../../src/hardware/mcc-ul/cbw64.dll -lpthread -lcbw64"
	# /usr/x86_64-w64-mingw32/sys-root/mingw/bin/libgcc_s_seh-1.dll
 	LIBS="-Wl,-Bstatic -lpistacxx -lpista -lprotobuf-c -Wl,-Bdynamic"
	RXTX_JAR="ref/RXTXcomm.jar\;intf\;gen"
	OS=win32
	PISTAX_SO=jpistax.dll
else
	CC=gcc
	CXX=g++
	CFLAGS="-Wall -fPIC"
	LIBS="-lpista -lpistacxx -lprotobuf-c"
	CXXLIBS="-lpistacxx -lprotobuf-c"
	OS=other
	PISTAX_SO=libjpistax.so
fi


export LD_LIBRARY_PATH=.:../../.libs:../cxx:/usr/lib/jni:/usr/lib64/rxtx
export LD_LIBRARY_PATH=../cxx:../../.libs:.:../../src/hardware/mcc-ul:/mingw64/bin


echo swig...
swig -c++ -I../../include -I${builddir}/include -I../cxx -java -package org.pistax -outcurrentdir -outdir gen/org/pistax ../pistax.i
if [ $? -ne 0 ]; then
	echo "swig failed for pistax.i"
	return 1
fi
swig -c++ -I../../include -I${builddir}/include -java -package org.pista  -outcurrentdir -outdir gen/org/pista  ../pista.i
if [ $? -ne 0 ]; then
	echo "swig failed for pista.i"
	return 1
fi

echo ${CC} ${CFLAGS} -I${builddir}/include -I../cxx -I../../include -I${JDK_HOME}/include -I${JDK_HOME}/include/${OS} -c pistax_wrap.cxx
${CC} ${CFLAGS} -I${builddir}/include -I../cxx -I../../include -I${JDK_HOME}/include -I${JDK_HOME}/include/${OS} -c pistax_wrap.cxx
echo ${CXX} -I${builddir}/include -shared pistax_wrap.o -o ${PISTAX_SO} -L../../.libs -L../cxx/.libs -L../../src/hardware/mcc-ul ${LIBS}
${CXX} -I${builddir}/include -shared pistax_wrap.o -o ${PISTAX_SO} -L../../.libs -L../cxx/.libs -L../../src/hardware/mcc-ul ${LIBS}

echo FIXME -- only compiling pistax_wrapper, not pista_wrapper
# ${CC} ${CFLAGS}          -I../../include -I${JDK_HOME}/include -I${JDK_HOME}/include/${OS} -c pista_wrap.cxx
# echo ${CXX} -shared pista_wrap.o  -o libjpista.so  -L../../.libs -L../cxx/.libs -L../../src/hardware/mcc-ul ${LIBS}
# ${CXX} -shared pista_wrap.o  -o libjpista.so  -L../../.libs -L../cxx/.libs -L../../src/hardware/mcc-ul ${LIBS}

echo "LD_LIBRARY_PATH=${LD_LIBRARY_PATH}"
ldd ${PISTAX_SO}
trap : 0

mkdir -p bin

echo ${JDK_HOME}/bin/javac -cp ${RXTX_JAR} -sourcepath gen -d bin gen/org/pista/*.java
${JDK_HOME}/bin/javac -cp ${RXTX_JAR} -sourcepath gen -d bin gen/org/pista/*.java
echo ${JDK_HOME}/bin/javac -cp ${RXTX_JAR} -sourcepath gen -d bin gen/org/pistax/*.java
${JDK_HOME}/bin/javac -cp ${RXTX_JAR} -sourcepath gen -d bin gen/org/pistax/*.java

${JDK_HOME}/bin/jar -cvf jpista.jar -C bin .

# echo javac -cp ${RXTX_JAR} -sourcepath intf test/Test1.java
# javac -cp ${RXTX_JAR} -sourcepath intf test/Test1.java
# LD_LIBRARY_PATH=.:../../../.libs:../../cxx/.libs:/usr/lib/jni:/usr/lib64/rxtx:/usr/local/lib java -cp .:${RXTX_JAR} test.Test1

