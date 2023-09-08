# gcc -g -fms-extensions --std=gnu99 -fPIC -Wall -I/home/bbaker/git/libwebsockets/build/include -I../../../include -I../.. -c propaqm.c
# gcc -g -fms-extensions --std=gnu99 -fPIC -Wall -I/home/bbaker/git/libwebsockets/build/include -I../../../include -I../.. -Wno-pointer-sign -c zws_parser.c
# gcc -g -fms-extensions --std=gnu99 -fPIC -Wall -I/home/bbaker/git/libwebsockets/build/include -I../../../include -I../.. -Wno-pointer-sign -c ztr_parser.c

# echo "*************"
# gcc -Wall -I../.. -Wno-pointer-sign -g -o test-yajl test-yajl.c zws_parser.o ztr_parser.o -l yajl

# echo "Compile *************"
# gcc -g -fms-extensions -fPIC -DTEST_API -Wall -I/home/bbaker/git/libwebsockets/build/include -I../../../include -I../.. -Wno-pointer-sign -c test_propaqm.c
# echo "PRELINK library update *************"
# ar d ../../../.libs/libpista.a propaqm.o
# ar q ../../../.libs/libpista.a propaqm.o
# echo "Link1 *************"
# gcc -g -o test_propaqm test_propaqm.o -L/home/bbaker/git/libwebsockets/build/lib -L ../../../.libs -Wl,-Bstatic -lpista -lwebsockets -Wl,-Bdynamic -lcap -lexpat -lcrypto -lz -lssl -lyajl -lserialport -lpthread -lprotobuf-c -lavahi-client -lavahi-common -lm
echo "Link2 *************"
gcc -Ic:/opt/tools/pista/include -I/usr/local/include -I../../../include -I../.. -c ztr_parser.c
gcc -Ic:/opt/tools/pista/include -I/usr/local/include -I../../../include -I../.. -c zws_parser.c
gcc -g -fms-extensions -I../../../include -I../.. -I/cygdrive/c/opt/tools/pista/include/ -DTEST_PARSER -o test_ztr test_ztr.c ztr_parser.o -lyajl
