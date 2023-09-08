echo compiling
javac -cp ../gen test/Test1.java
echo running
# PATH=/cygdrive/c/opt/jdk/jdk1.8.0_72/bin:/cygdrive/c/Windows/SysWOW64:/cygdrive/c/Windows/System32 java -Djava.library.path=.\;c:/cygwin64/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ -cp .\;../gen test/Test1
# PATH=${PATH} java -Djava.library.path=.\;c:/cygwin64/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ -cp .\;../gen test/Test1
java -Djava.library.path=.\;c:/cygwin64/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ -cp .\;../gen test/Test1
