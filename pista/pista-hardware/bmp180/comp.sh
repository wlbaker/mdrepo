gcc -DDEBUG -Wall -std=gnu99 -c bmp180.c
gcc -c test_bmp180.c
gcc -o test_bmp180 test_bmp180.o bmp180.o -lm
