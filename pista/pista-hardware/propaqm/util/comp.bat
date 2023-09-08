gcc -I.. -I../../../pista-core/include -o ty.exe test-yajl.c ztr_dump.o ztr_parser.o zws_parser.o extra.o pista-internal.o -lyajl 
gcc -I.. -I../../../pista-core/include -c pista-internal.c 
gcc -I.. -I../../../pista-core/include -c extra.c 
gcc -I.. -I../../../pista-core/include -c ..\zws_parser.c 
gcc -I.. -I../../../pista-core/include -c ..\ztr_dump.c 
gcc -I.. -I../../../pista-core/include -c ..\ztr_parser.c 
