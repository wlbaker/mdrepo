#!/bin/sh

echo "Windows *************"
# gcc -Ic:/opt/tools/pista/include -I/usr/local/include -I../../../include -I../.. -c ztr_parser.c
# CC=x86_64-w64-mingw32-gcc
CC=gcc
${CC} -Wall -std=c11 -g -fms-extensions -I../../../include -I../.. -c ztr_dump.c 
${CC} -Wall -std=c11 -g -fms-extensions -I../../../include -I../.. -c ztr_parser.c 
${CC} -Wall -std=c11 -g -fms-extensions -I../../../include -I../.. -o test_ztr test_ztr.c ztr_parser.o ztr_dump.o -lyajl
