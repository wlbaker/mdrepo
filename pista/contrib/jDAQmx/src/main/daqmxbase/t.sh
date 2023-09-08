cd ../../build/rhel/daqmxbase
g++ -g -L/usr/local/natinst/nidaqmxbase/lib -shared -o libjDAQmxBase.so BaseLocal.o BaseTask.o BaseAIChannel.o BaseTiming.o BaseAnalogMultiChannelReader.o BaseDaqStream.o jDAQmxBase.o ../jniUtil.o -lnidaqmxbase
echo lib built
cp /home/bbaker/t/nijava/jdaqmx-c/build/rhel/daqmxbase/libjDAQmxBase.so /home/bbaker/workspace/dataRepository/ICUInterface/lib/rhel54/
echo lib installed
