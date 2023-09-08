source deps/_shared.sh

# export ANDROID_SDK=/opt/tools/Android/Sdk
configure_make() {
  ARCH=$1; ABI=$2;

  rm -f CMakeCache.txt

  configure $*

  echo "Configuring PISTA... with ARCH=${ARCH} and ABI=${ABI}"
  set -x

    # -DProtobuf_LIBRARY=${DISTRIB_PATH}/${ABI}/lib/libprotobuf.so \
    # -DProtobuf_PROTOC_LIBRARY="${DISTRIB_PATH}/${ABI}/lib/libprotoc.so" \
    # -DANDROID_API=${ANDROID_API}

  ${ANDROID_SDK}/cmake/3.6.4111459/bin/cmake --verbose \
    -DProtobuf_INCLUDE_DIR=${DISTRIB_PATH}/${ABI}/include \
    -DProtobufC_LIBRARY=${DISTRIB_PATH}/${ABI}/lib/libprotobuf-c.so \
    -DANDROID_ABI=${TARGET_ARCH} \
    -DANDROID_PLATFORM=android-${ANDROID_API} \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${DISTRIB_PATH}/${ABI}" \
    -DCMAKE_MODULE_PATH="macros" \
    -DCMAKE_PREFIX_PATH="${DISTRIB_PATH}/${ABI}/lib/pkgconfig" \
    -DBUILD_SHARED_LIBS=ON \
    -DANDROID_NDK=${ANDROID_SDK}/ndk-bundle \
    -DCMAKE_CXX_FLAGS= \
    -DCMAKE_TOOLCHAIN_FILE=${ANDROID_SDK}/ndk-bundle/build/cmake/android.toolchain.cmake \
    -DCMAKE_MAKE_PROGRAM=${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja \
    "-GAndroid Gradle - Ninja" CMakeLists.txt

  ${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja
  set +x

  if [[ $? -eq 0 ]]; then
    echo "Installing PISTA to distribution directory ..."
    ${ANDROID_SDK}/cmake/3.6.4111459/bin/ninja install
  else
    echo "ERROR RETURN CODE: $?"
  fi
}

for ((i=0; i < ${#ARCHS[@]}; i++))
do
    echo "Preparing $#==0 and ${ARCHS[i]}...ANDROID_API=${ANDROID_API}"
  if [[ $# -eq 0 ]] || [[ "$1" == "${ARCHS[i]}" ]]; then
    # Do not build 64 bit arch if ANDROID_API is less than 21 which is
    # the minimum supported API level for 64 bit.
    [[ ${ANDROID_API} < 21 ]] && ( echo "${ABIS[i]}" | grep 64 > /dev/null ) && continue;
    configure_make "${ARCHS[i]}" "${ABIS[i]}"
  fi
done
