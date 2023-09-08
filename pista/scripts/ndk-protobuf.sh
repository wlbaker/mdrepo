
pushd .
CXX=arm-linux-androideabi-g++
CC=arm-linux-androideabi-gcc


NDK_PATH=/opt/tools/Android/Sdk/ndk-bundle

PLATFORM_PREFIX=/opt/tools/android-19

PATH=${PLATFORM_PREFIX}/bin:${PATH}

cd /opt/tools
protobuf_file="protobuf-2.6.1.tar.gz"
if [ -f "${protobuf_file}" ]
then
	echo "${protobuf_file} found."
else
	wget https://github.com/google/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.gz
fi

# strip .tar.gz
root_file=`basename ${protobuf_file} .tar.gz`
# root_file="${root_file%.*}"

if [ -f "${root_file}" ]
then
	echo "${root_file} found."
else
	tar xzvf protobuf-2.6.1.tar.gz
fi

cd ${root_file}
CC=${CC} CXX=${CXX} ./configure --prefix=/home/bbaker/git/pista/platform/android-19 --build=x86_64-redhat-linux --host=arm-linux-androideabi --with-protoc=/usr/bin/protoc

# CFLAGS="-I ${INST_PATH}/include" CXXFLAGS="-I ${INST_PATH}/include" ./configure --build=x86_64-redhat-linux --host=arm-linux-androideabi --prefix=/home/bbaker/git/pista/platform/android-19/ --disable-libserialport --disable-python --disable-java

#cd /opt/tools
#wget https://github.com/protobuf-c/protobuf-c/releases/download/v1.2.1/protobuf-c-1.2.1.tar.gz
#tar xzvf protobuf-c-1.2.1.tar.gz
