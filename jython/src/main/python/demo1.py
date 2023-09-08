
import py4j.java_gateway;

gateway = py4j.java_gateway.JavaGateway()

f = gateway.jvm.idea.conf.DeviceFactory
f.scanPkg( "idea.driver" )
f.scanPkg( "icuInterface.adapters" )

drivers = f.getDrivers();

for d in drivers:
    print( "name=" + d.getName() )

s = gateway.jvm.idea.driver.SimuSineStreamProducer
conf = s.createConfigInstance()

for stream in conf.getStreams():
    print("stream: " + stream )

producer = new s(conf);
producer.addStreamListener(StreamID.WAVEFORM, t)
producer.addStreamListener(StreamID.MEASUREMENT, t )

for i = 0; i < 10; i++:
    producer.tick()

print("done!")
