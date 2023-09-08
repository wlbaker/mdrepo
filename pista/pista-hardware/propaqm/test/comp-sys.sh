#!/bin/sh

CCOPTS="-g --std=gnu99 -fPIC -I../../.. -I../../../pista-core/include -I.."
# CCOPTS=${CCOPTS} -fms-extensions -Wall

echo "*"
gcc ${CCOPTS} -c ../propaqm.c

echo "*"
gcc ${CCOPTS} -c ../propaqm.pb-c.c

echo "gcc ${CCOPTS} -Wno-pointer-sign -c ztr_parser.c"
gcc ${CCOPTS} -Wno-pointer-sign -c ../ztr_parser.c

echo "compiling ztr_dump.c"
gcc ${CCOPTS} -Wno-pointer-sign -c ../ztr_dump.c
echo "*"

echo "compiling pista-fields.c"
gcc ${CCOPTS} -Wno-pointer-sign -c ../../../pista-core/src/c/pista-internal.c
echo "*"

# echo "*************"
# gcc -Wall -I../.. -Wno-pointer-sign -g -o test-yajl test-yajl.c zws_parser.o ztr_parser.o -l yajl

echo "C test_propaqm.c" 
gcc -fms-extensions ${CCOPTS} -Wno-pointer-sign -c test_propaqm.c
# echo "PRELINK library update *************"
# ar d ../../../.libs/libpista.a propaqm.o ztr_parser.o ztr_dump.o zws_parser.o
# ar q ../../../.libs/libpista.a propaqm.o ztr_parser.o ztr_dump.o zws_parser.o
echo "L *************"
gcc -g -o test_propaqm test_propaqm.o propaqm.o propaqm.pb-c.o ztr_parser.o ztr_dump.o pista-internal.o -L/usr/lib64 -L/usr/local/lib -L../../.. -lx-support -Wl,-Bdynamic -lwebsockets -lcap -lexpat -lcrypto -lz -lssl -lyajl -lserialport -lpthread -lprotobuf-c -lavahi-client -lavahi-common -lm
