package idea.net;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

import org.apache.log4j.Level;
import org.apache.log4j.LogManager;

import icuInterface.PlatformUtil;
import idea.driver.InfinityDriver;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.PiSubjectExporter;
import idea.persistmanager.PiDreExporter;
import idea.persistmanager.PiHdf5Exporter;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class TestUdpListen {

	private int port;

	class Receiver implements StreamConsumer {

		PiSubjectExporter exporter;
		int tot = 0;
		Boolean running = false;

		public Receiver() {

		}

		private void initExporter(String file_name) {

			if (file_name.endsWith("pcapng")) {
				file_name = file_name.substring(0, file_name.length() - 7);
			}
			String h5OutFile = file_name + "Z.h5";
			File f = new File(h5OutFile);
			if (f.exists()) {
				f.delete();
			}

			String datOutFile = file_name;
			f = new File(datOutFile);
			if (f.exists()) {
				for (File ff : f.listFiles()) {
					ff.delete();
				}
				f.delete();
			} else {
				f.mkdir();
			}

			RpSubject header = new RpSubject();
			header.setLocation("idea");
			header.setMedicalId(file_name);
			header.setOperator("WLB");
			header.setStudyTitle("EP-RESUS");
			exporter = new PiHdf5Exporter(header, h5OutFile, false);
			// exporter = new PiDreExporter(header, new File(datOutFile));
			
			log.info("Logging H5 data to: {}", h5OutFile );
		}

		@Override
		public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

			synchronized (running) {
				if (running == false)
					return;

				if (sid == StreamID.CAPABILITIES) {
					// ignore
				} else if (sid == StreamID.CONNECTION) {
					// ignore
				} else if (sid == StreamID.DISPLAY) {
					// ignore
				} else if (sid == StreamID.ALARM) {
					// ignore
				} else if (sid == StreamID.SETTINGS) {
					// ignore
					// System.err.println("got unexpected settings");
				} else if (sid == StreamID.DDDEMOGRAPHICS) {
					// exporter.streamEvent(jobID, source, sid, item);
				} else if (sid == StreamID.MEASUREMENT) {
					// System.out.println("EVENT: " + item);
					exporter.streamEvent(jobID, source, sid, item);
				} else {
					exporter.streamEvent(jobID, source, sid, item);
				}
			}
		}

		public void run(int port) {

			InfinityDriver driver = new InfinityDriver(null);
			driver.setUseDeviceTime(true);
			driver.setVitalsSkipCount(10);
			driver.addStreamListener(null, this);

			DatagramSocket serverSocket = null;
			try {

				serverSocket = new DatagramSocket(port);
				byte[] receiveData = new byte[1024 * 2];
				String sendString = "polo";
				byte[] sendData = sendString.getBytes("UTF-8");

				// System.out.printf("Listening on udp:%s:%d%n",
				// InetAddress.getLocalHost().getHostAddress(), port);
				log.info("Listening on udp:{}:{}", InetAddress.getLoopbackAddress(), port);
				DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

				running = true;
outer:
				while (true) {

					serverSocket.receive(receivePacket);
					// System.out.println("RECEIVED: " + tot);

					byte[] dat = receivePacket.getData();
					int pktLen = receivePacket.getLength();
					if (dat[0] == '!') {
						if (pktLen == 1) {
							break;
						}
						if (pktLen < 160) {
							String cmd = new String(dat, 1, receivePacket.getLength() - 1);
							String[] arr = cmd.split("[\\s]+");
							int idx = 0;
							while (idx < arr.length) {
								if ("".equals(arr[idx])) {
									// ignore
								} else if ("exit".equals(arr[idx])) {
									break outer;
								} else if ("file".equals(arr[idx])) {

									if (exporter != null) {
										exporter.disconnect();
									}

									initExporter(arr[++idx]);
									exporter.connect();

								} else {
									log.error("Unrecognized command: {}", arr[idx]);
									break;
								}
								idx++;
							}
							continue;
						}
					}
					ByteArrayInputStream bais = new ByteArrayInputStream(dat, 0, receivePacket.getLength());

					driver.process(bais, null);

					// now send acknowledgement packet back to sender
					// InetAddress IPAddress = receivePacket.getAddress();
					// DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length,
					// IPAddress,
					// receivePacket.getPort());
					// serverSocket.send(sendPacket);
				}
			} catch (Exception e) {
				log.error("Error parsing command", e);
			} finally {

				synchronized (running) {
					running = false;
					if (serverSocket != null) {
						serverSocket.disconnect();
					}
					if (exporter != null) {
						try {
							exporter.disconnect();
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
				}
				System.out.println("Complete.");

			}
			// should close serverSocket in finally block
		}

	}

	private void run() {
		new Receiver().run(port);
	}

	public static void main(String[] args) {
		LogManager.getRootLogger().setLevel((Level) Level.INFO);
		PlatformUtil.init();
		// System.loadLibrary("hdf5");
		// System.loadLibrary("hdf5_java");

		TestUdpListen l = new TestUdpListen();

		l.port = args.length == 0 ? 9902 : Integer.parseInt(args[0]);

		l.run();
	}

}
