#!/bin/bash

#
# 2016-01-28 WLB: uncomment the lspio-cm and boost-cm lines and add to linker when ready to deal with serial
#

rm -rf .libs
mkdir .libs

AR=ar
RANLIB=ranlib

platform='unknown'
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
    CXX=g++
    CFLAGS="-g -Wall -fPIC"
    LIBS="-lpista -lprotobuf-c"
elif [ \( "$unamestr" == 'cygwin' \) -o \( "$unamestr" == "CYGWIN_NT-6.1" \) ]; then
    CXX=x86_64-w64-mingw32-g++
    CFLAGS="-g -Wall"
    LIBS="-lpista -lprotobuf-c ../../src/hardware/mcc-ul/cbw64.dll -lpthread"
fi

# CFLAGS+=" -DDLL_BUILD"

LIB_INCLUDES="-L../../.libs -L/usr/local/lib -L../../src"
LIB_FLAGS="-shared"
# LIBS="-lpista -lserialport -llabjackusb -lprotobuf-c"

echo Compiling sources...
${CXX} $CFLAGS -I../../include -I. -c pista-cl.cpp
${CXX} $CFLAGS -I../../include -I. -c pista-dev.cpp
${CXX} $CFLAGS -I../../include -I. -c pista-driver.cpp
${CXX} $CFLAGS -I../../include -I. -c pista-evt.cpp
${CXX} $CFLAGS -I../../include -I. -c pista-cm.cpp
${CXX} $CFLAGS -I../../include -I. -c pista-pkt.cpp
${CXX} $CFLAGS -I../../include -I. -c pista-str.cpp
# ${CXX} $CFLAGS -I../../include -I. -c pista-evt-pb.cpp
# ${CXX} $CFLAGS -I../../include -I. -c lspio-cm.cpp
# ${CXX} $CFLAGS -I../../include -I. -c boost-cm.cpp

echo Creating library...
# echo ${CXX} ${LIB_FLAGS} ${LIB_INCLUDES} -o ./.libs/libpistacxx.so pista-cl.o pista-dev.o pista-driver.o pista-evt.o pista-cm.o ${LIBS}
echo ${AR} rc .libs/libpistacxx.a pista-cl.o pista-dev.o pista-driver.o pista-evt.o pista-cm.o pista-str.o
ar rc .libs/libpistacxx.a pista-cl.o pista-dev.o pista-driver.o pista-evt.o pista-cm.o pista-pkt.o pista-str.o
${RANLIB} .libs/libpistacxx.a
 

