
ARCH=`arch`

export CXX=${ARCH}-w64-mingw32-g++
export CC=${ARCH}-w64-mingw32-gcc
export CFLAGS='-I/opt/jdk/jdk1.8.0_72/include  -I/opt/jdk/jdk1.8.0_72/include/win32 -I/usr/java/latest/include -I/usr/java/latest/include/win32'
export CXXFLAGS='-I/opt/jdk/jdk1.8.0_72/include  -I/opt/jdk/jdk1.8.0_72/include/win32 -I/usr/java/latest/include -I/usr/java/latest/include/win32'
export PATH=/usr/java/latest/bin:/usr/${ARCH}-w64-mingw32/sys-root/mingw/bin:/usr/${ARCH}-w64-mingw32/sys-root/mingw/bin:${PATH}

export PKG_CONFIG_PATH=/usr/x86_64-w64-mingw32/sys-root/mingw/lib/pkgconfig

echo HINT\: ./configure  --with-jni-include-path=/c/opt/jdk/jdk1.8.0_72/include --prefix=/mingw64 --disable-mccul
echo ...possibly with --disable-mccul
echo ...READ THE README in pista-core
echo ...README describes dependencies...protobuf-c!...and how to install

