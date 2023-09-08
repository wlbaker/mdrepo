rm -f test_ht70 test_ht70.o ht70.o


if [ "${CC}x" = "x" ]; then 
	CC=gcc
fi

echo CC set to ${CC}

#
# build emu_h70
#
# ${CC} -g -Wall --std=c99 -o emu_ht70 emu_ht70.c -lserialport


${CC} -g -Wall --std=c99 -I../../../include -I../.. -c test_ht70.c
if [ $? -eq 0 ]; then

    # ${CC} -g -o test_ht70 test_ht70.c -I../../../include -L../../../.libs -lpista -lserialport -lprotobuf-c -lwebsockets -lyajl -lavahi-core -lavahi-common -lavahi-client  -lexpat
    ${CC} -g -o test_ht70 test_ht70.c -I../../../include -L../../../.libs -lpista -lserialport -lprotobuf-c -lyajl -lexpat -lwebsockets

    if [ $? -eq 0 ]; then
    	echo "Compile complete.  Attempting to run..."
    	echo ""
    	echo "try: run < sample-1.xml"
    	LD_LIBRARY_PATH=../../../.libs:/usr/local/lib gdb ./test_ht70
    fi
fi
