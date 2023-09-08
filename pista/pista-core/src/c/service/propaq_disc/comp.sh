rm -f pp_api.o pp_discover.o test_ppdisc.o

gcc -g --std=gnu99 -fPIC -Wall -I../../../include -I../.. -c pp_api.c
gcc -g --std=gnu99 -fPIC -Wall -I../../../include -I../.. -c pp_discover.c

echo "C *************"
gcc -g -fPIC -DTEST_API -Wall -I/usr/local/include -I../../../include -I../.. -Wno-pointer-sign -c test_ppdisc.c
echo "L *************"
gcc -g -o test_ppdisc test_ppdisc.o pp_api.o pp_discover.o -L ../../../.libs -lavahi-client -lavahi-common
