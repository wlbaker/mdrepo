# gcc -Wall -I../../../include -I../.. -c imp731-api.c
# gcc -Wall --std=c99 -I../../../include -I../.. -c imp731.c
# gcc -Wall --std=c99 -I../../../include -I../.. -c ../../pista-internal.c
gcc -g -Wall --std=c99 -I../../../include -I../.. -c test_imp731.c
# gcc -o test_imp731 test_imp731.o imp731.o imp731-api.o pista-internal.o -L../../../.libs -lpista -lserialport -lyajl -lprotobuf-c -lwebsockets
gcc -g -o test_imp731 test_imp731.o -L../../../.libs -lpista -lserialport -lyajl -lprotobuf-c -L../../../../libwebsockets/build/lib -lwebsockets
# LD_LIBRARY_PATH=../../../.libs:../../../../libwebsockets/build/lib gdb ./test_imp731
LD_LIBRARY_PATH=../../../.libs:../../../../libwebsockets/build/lib ./test_imp731
