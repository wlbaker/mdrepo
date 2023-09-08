echo "building dll by hand"

CC=x86_64-w64-mingw32-gcc
CFLAGS="--std=c99 -D_USE_MATH_DEFINES"
INCLUDES="-I../include -I./hardware -I. -I./model -I/usr/local/include"

echo "imp731"
${CC} ${CFLAGS} ${INCLUDES} -c hardware/imp731/imp731.c
echo "imp731-api"
${CC} ${CFLAGS} ${INCLUDES} -c hardware/imp731/imp731-api.c

echo "pista"
${CC} ${CFLAGS} ${INCLUDES} -c pista.c
echo "std"
${CC} ${CFLAGS} ${INCLUDES} -c std.c
echo "log"
${CC} ${CFLAGS} ${INCLUDES} -c log.c
echo "mcc-ul"
${CC} ${CFLAGS} ${INCLUDES} -c hardware/mcc-ul/mcc-ul.c
echo "simu"
${CC} ${CFLAGS} ${INCLUDES} -c hardware/simu/simu-api.c

${CC} -shared -o pista.dll pista.o std.o log.o \
	imp731.o imp731-api.o \
	mcc-ul.o \
	simu-api.o \
	hardware/mcc-ul/cbw64.dll \
	-Wl,--out-implib,libpista.a
