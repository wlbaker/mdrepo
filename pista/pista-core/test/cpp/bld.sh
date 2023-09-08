gcc -std=c11 -o main main.c u3.c u3Stream.c -lm -llabjackusb
g++ -o u3d U3Driver.cxx u3.c u3Stream.c -llabjackusb
