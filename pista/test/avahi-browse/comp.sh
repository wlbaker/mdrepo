rm -f b b.o b2.o b2
gcc -std=c11 -g -c b2.c
gcc -std=c11 -g b2.o -o b -L /usr/lib/arm-linux-gnueabihf -lavahi-common -lavahi-client
# gdb --args ./b --domain=X-Series.device.ZOLL.local _workstation._tcp
./b -t --domain=X-Series.device.ZOLL.local _workstation._tcp
