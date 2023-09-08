
# gcc -DTEST_API -g -D_WIN32 --std=c99 -I../../../include -I../.. -I../../model -c mcc-ul.c
# gcc -g -o test_cy mcc-ul.o ./cbw64.dll

/bin/rm -f api.o
x86_64-w64-mingw32-gcc -g -D_WIN32 -mwindows --std=c99 -I../../../include -I../.. -I../../model -c mcc-ul.c
x86_64-w64-mingw32-gcc -g -mwindows -o test_mn mcc-ul.o ./cbw64.dll
/bin/rm -f mcc-ul.o

# gcc -Wall --std=c99 -I../../../include -I../.. -c test_ul.c
# gcc -o test_ul test_ul.o mcc-ul.o api.o
