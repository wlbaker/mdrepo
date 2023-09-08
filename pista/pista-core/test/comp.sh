ulimit -c unlimited
gcc -I../include -I../src -c tt.c
gcc -o tt tt.o -L../.libs -lpista -lserialport -lprotobuf-c
LD_LIBRARY_PATH=../.libs ./tt
