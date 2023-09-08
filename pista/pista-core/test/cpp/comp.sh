#!/bin/bash

CXX=g++
CFLAGS="-g -Wall -fPIC -I../../bindings/cxx -I../../include"
LIBS="-lpista -lpistacxx -lprotobuf-c -lpthread"

# CXX=x86_64-w64-mingw32-g++
# CFLAGS="-g -Wall"
# LIBS="-lpista -lprotobuf-c ../../src/hardware/mcc-ul/cbw64.dll -lpthread"

LIB_INCLUDES="-L../../.libs -L/usr/local/lib -L../../src -L../../bindings/cxx/.libs"
LIB_FLAGS="-shared"

echo Building test... 
echo ${CXX} ${CFLAGS} ${INCLUDES} -Wall -c test_cl2.cpp 
${CXX} ${CFLAGS} ${INCLUDES} -c test_cl2.cpp 

echo ${CXX} -o test_cl2 test_cl2.o ${LIB_INCLUDES} ${LIBS}
${CXX} -o test_cl2 test_cl2.o ${LIB_INCLUDES} ${LIBS}

echo run: LD_LIBRARY_PATH=../../.libs:/usr/local/lib ./test_cl2
LD_LIBRARY_PATH=../../.libs::../../bindings/cxx/.libs:/usr/local/lib ./test_cl2

