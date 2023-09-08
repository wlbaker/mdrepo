echo compiling
javac -cp ../gen test/Test1.java
echo running
echo PATH=${PATH} java -Djava.library.path=.\;c:/cygwin64/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ -cp .\;../gen test/Test1
java -Djava.library.path=.\;c:/cygwin64/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ -cp .\;../gen test/Test1
