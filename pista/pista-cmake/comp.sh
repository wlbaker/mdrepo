# -HC:/Users/ccsta/git/pista/pista-cmake/app -BC:/Users/ccsta/git/pista/pista-cmake/app/.externalNativeBuild/cmake/debug/x86_64 \
source ../deps/_shared.sh

set -x

export ANDROID_ABI=x86_64

${ANDROID_SDK}/cmake/3.6.4111459/bin/cmake --stacktrace --verbose --scan \
    -DProtobuf_LIBRARY=${DISTRIB_PATH}/${ABI}/lib/libprotobuf.so \
    -DProtobuf_INCLUDE_DIR=${DISTRIB_PATH}/${ABI}/include \
    -DProtobuf_PROTOC_LIBRARY="${DISTRIB_PATH}/${ABI}/lib/libprotoc.so" \
    -DANDROID_ABI=${ANDROID_ABI} \
    -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=`pwd`/../distribution/libs/${ANDROID_ABI} \
    -DCMAKE_BUILD_TYPE=Debug \
    -DANDROID_NDK=${ANDROID_SDK}/ndk-bundle \
    -DCMAKE_CXX_FLAGS= \
    -DCMAKE_TOOLCHAIN_FILE=${ANDROID_SDK}/ndk-bundle/build/cmake/android.toolchain.cmake \
    -DCMAKE_MAKE_PROGRAM=${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja \
    "-GAndroid Gradle - Ninja" app/CMakeLists.txt 

cd app
${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja
cd ..
set +x
