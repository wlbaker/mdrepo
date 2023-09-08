
mkdir build
cd build

\opt\Android-Studio\cmake\3.6.4111459\bin\cmake --verbose ^
-HC:\Users\ccsta\git\pista\pista-core -BC:\Users\ccsta\git\pista\.externalNativeBuild\pista-core\android-26\debug\x86_64 ^
-DANDROID_ABI=x86_64 ^
-DANDROID_PLATFORM=android-26 ^
-DBUILD_PROTO3=true ^
-Dprotobuf_BUILD_TESTS=OFF ^
-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=C:\Users\ccsta\git\pista\build\intermediates\android-26\debug\obj\x86_64 ^
-DCMAKE_BUILD_TYPE=Debug ^
-DANDROID_NDK=C:\opt\Android-Studio\ndk-bundle ^
-DCMAKE_CXX_FLAGS= ^
-DCMAKE_TOOLCHAIN_FILE=C:\opt\Android-Studio\ndk-bundle\build\cmake\android.toolchain.cmake ^
-DCMAKE_MAKE_PROGRAM=C:\opt\Android-Studio\cmake\3.6.4111459\bin\ninja.exe ^
"-GAndroid Gradle - Ninja" ..\CMakeLists.txt 
cd ..
