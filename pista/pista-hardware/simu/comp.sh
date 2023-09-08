
CFLAGS="--std=gnu99 -D_USE_MATH_DEFINES"
 
gcc -g ${CFLAGS} -I../../../include -I../.. -I../../model -c simu-api.c 
ar d ../../../.libs/libpista.a simu-api.o
ar q ../../../.libs/libpista.a simu-api.o
# gcc -g ${CFLAGS} -I../../../include -I../.. -I../../model -c ../../dump.c 
# gcc -g ${CFLAGS} -I../../../include -I.. -I../.. -I../../model -c ../../pista-internal.c
gcc -g ${CFLAGS} -I../../../include -I.. -I../.. -I../../model -c test_simu.c
gcc -g -o test_simu test_simu.o -L/usr/lib64 -L../../../.libs -Wl,-Bstatic -lpista -Wl,-Bdynamic -lwebsockets -lcap -lexpat -lcrypto -lz -lssl -lyajl -lserialport -lpthread -lprotobuf-c -lavahi-client -lavahi-common -lm
# gcc -g -fms-extensions -I../../../include -I../.. -DTEST_PARSER -o test_ztr test_ztr.c ztr_parser.c -L../../../.libs -Wl,-Bstatic -lpista -Wl,-Bdynamic -lwebsockets -lexpat -lcrypto -lssl -lyajl -lprotobuf-c -lavahi-client -lavahi-common -lpthread -lm

#MINGW_ARCH=x86_64
#MINGW_ARCH=i686
#CC=${MINGW_ARCH}-w64-mingw32-gcc 
#
#${CC} -DTEST_MAIN -g -D_WIN32 ${CFLAGS} -I../../../include -I../.. -I../../model -c simu-api.c
#${MINGW_ARCH}-w64-mingw32-gcc -g -o test_mn simu-api.o -lm -lwinpthread
#
#/bin/rm -f simu-api.o
