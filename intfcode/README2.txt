
Note: ROS claims to use DDS as its transport mechanism
-------------
mkdir build-rts
cd build-rts
cp USER_QOS_PROFILES.xml build-rts
cmake -DCMAKE_MODULE_PATH=../ice-hello-world  ../ice-hello-world
make
./helloworld pub
