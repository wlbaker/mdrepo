rm test_ms3 test_ms3.o
# gcc --std=c99 -o emu_ms3 emu_ms3.c -lserialport
gcc -g -Wall --std=c99 -I../../../include -I../.. -c test_ms3.c
gcc -g -o test_ms3 test_ms3.o -L../../../.libs -lpista -lserialport -lyajl -lprotobuf-c -L../../../../libwebsockets/build/lib -lwebsockets
# LD_LIBRARY_PATH=../../../.libs:../../../../libwebsockets/build/lib gdb ./test_ms3
LD_LIBRARY_PATH=../../../.libs:../../../../libwebsockets/build/lib ./test_ms3
