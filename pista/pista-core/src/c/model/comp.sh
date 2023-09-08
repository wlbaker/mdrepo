#!/bin/sh

gcc -std=c11 -I.. -c propaqm.pb-c.c
gcc -std=c11 -I.. -c dump-model.c
gcc -o dump-model dump-model.o propaqm.pb-c.o -lprotobuf-c
