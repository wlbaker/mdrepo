JAVA_SDK=/usr/lib/jvm/java-8-oracle
rm x/*

echo swig -c++ -java -outdir x example.i
swig -c++ -java -outdir x example.i
echo gcc -I${JAVA_SDK}/include -I${JAVA_SDK}/include/linux -fPIC -c example_wrap.cxx
gcc -I${JAVA_SDK}/include -I${JAVA_SDK}/include/linux -fPIC -c example_wrap.cxx
echo g++ -fPIC -c example.cxx
g++ -fPIC -c example.cxx
echo gcc -shared example.o example_wrap.o -o libexample.so
g++ -shared example.o example_wrap.o -o libexample.so
cd x
echo javac *.java
javac *.java
cd ..
echo javac -cp .:./x runme.java
javac -cp .:./x runme.java
# echo java -Djava.library.path=.:/usr/lib64/rxtx -cp .:./x runme
# java -Djava.library.path=.:/usr/lib64/rxtx -cp .:./x runme
echo java -Djava.library.path=.:/usr/lib/jni -cp .:./x runme
java -Djava.library.path=.:/usr/lib/jni -cp .:./x runme
