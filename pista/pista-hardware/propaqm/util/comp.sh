gcc -O0 -g -I.. -I../../../pista-core/include -c pista-internal.c
gcc -O0 -g -I.. -I../../../pista-core/include -c extra.c
gcc -O0 -g -I.. -I../../../pista-core/include -c ../zws_parser.c
gcc -O0 -g -I.. -I../../../pista-core/include -c ../ztr_dump.c
gcc -O0 -g -I.. -I../../../pista-core/include -c ../ztr_parser.c
gcc -O0 -g -I.. -I../../../pista-core/include -c ../propaqm.c
gcc -O0 -g -I.. -I../../../pista-core/include -c ../propaqm.pb-c.c
gcc -O0 -g -I.. -I../../../pista-core/include -c ../../../pista-core/src/c/log.c
gcc -O0 -g -I.. -I../../../pista-core/include -o ty test-yajl.c ztr_dump.o ztr_parser.o zws_parser.o extra.o pista-internal.o propaqm.o log.o propaqm.pb-c.o -lyajl -lprotobuf-c -lpthread -lwebsockets -lssl3 -lcrypto
