package idea.datamanager.simu;

import icuInterface.ConnectionStatus;
import icuInterface.message.AbstractItem;
import icuInterface.message.NumericBlock;
import icuInterface.message.WaveformBlock;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.driver.NullDevice;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.MultiplexInterface;
import idea.intf.StreamProducer;
import idea.model.Alarm;
import idea.model.Annotation;
import idea.model.PersistentItem;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiHdf5Importer;

import java.io.IOException;
import java.util.Calendar;
import java.util.Date;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class SimulationDriver extends AbstractStreamProducer implements MultiplexInterface {

	private Thread t;

	private long msDatatime; // when did the actual data collection occur
	private long msNow;
	private long msDelta; // this is current time - simulation start time;

	int pos = 0;

	PiSubjectImporter importer;
	int packetRate;
	DeviceCapabilities cap;

	PersistentItem curr;
	// ServerMessageBase next;

	private ImporterDeviceConfiguration conf;

	private String errorMessage;
	private boolean pause = false;
	private boolean realtime = true;

	// private SimulationTickTask task;

	private boolean running = true;

	private long msInitial;

	class SimulationTickThread implements Runnable {

		@Override
		public void run() {

			try {

				long ms = 0;
				long t1 = 0; // used for latency testing
				long t2 = 0;
				while (running) {

					if (ms > 10000) {
						ms = 0; // no breaks of more than 10 sec
					}
					// you might have multiple events at the same ms time
					if (ms > 0 || pause) {
						try {
							if (pause) {
								// wonder if -1 means sleep forever?
								Thread.sleep(Long.MAX_VALUE);
							} else if (realtime) {
								long a0 = System.currentTimeMillis();
								Thread.sleep(ms);
								long a1 = System.currentTimeMillis();
								int actual = (int) (a1 - a0);
								System.out.println("[s" + ms + "," + actual + "]");
							} else {
								// no pause, don't stop...but be friendly!
								Thread.yield();
								System.out.println("[y]");
							}
						} catch (Exception e2) {
							// OK to be interrupted
							log.warn("interrupted...running={}", running);

							if (!running) {
								// hmm...necessary for some cases, but not this
								// one
								// http://www.javaspecialists.co.za/archive/Issue056.html
								Thread.currentThread().interrupt();
								break;
							}
						}
					}

					t1 = System.currentTimeMillis();
					tick();
					t2 = System.currentTimeMillis();
					if (log.isDebugEnabled()) {
						StreamProducer d = curr.getDriver();
						String devName = "<UNK>";
						if( d != null && d.getConfiguration() != null ) {
							devName = d.getConfiguration().getName();
						}
						log.debug( devName + " " + curr.getClass() + " dt: {}  sleep: {}", (t2 - t1), ms );
					}


					if (curr == null) { // should correspond to end of data
						log.info("SIMULATOR switching to PAUSE state until disconnected");
						pause = true;

						PiDatastreamImporter[] devs = importer.getDevices();
						for (PiDatastreamImporter dev : devs) {
							log.warn("TODO: disconnect device {}", dev);
						}
						setStatus(  ConnectionStatus.NOT_CONNECTED );
						continue;
					} else {

					}
					msDatatime = curr.getTime();

					msNow = System.currentTimeMillis();

					ms = msDatatime + msDelta - msNow;

					if (autoPauseAt > 0 && msDatatime > autoPauseAt) {
						setPause(true);
					}
				}
				// t = new Timer();
				// t.schedule(new SimulationTickTask(), ms);
			} catch (Exception e) {
				log.error("simulation error", e );
			}

			if (running) {
				log.warn("SIMULATOR task TERMINATED PREMATURELY");
			} else {
				log.info("SIMULATOR task TERMINATED CLEANLY");
			}
		}

	};

	public static ImporterDeviceConfiguration createConfigInstance() {
		ImporterDeviceConfiguration conf = new ImporterDeviceConfiguration(SimulationDriver.class);

		conf.setDriverName("SimulatorDriver ");
		return conf;
	}

	public SimulationDriver(DeviceConfiguration conf, PiSubjectImporter importer) {

		this.conf = (ImporterDeviceConfiguration) conf;
		this.importer = importer;

		// I want to retrieve some structure about devices
		// before calling connect to give back to the client...
		// so this routine CHANGES the configuration.

		// importer = ImporterUtil.getImporterFromFile(new
		// File(this.conf.getImporterFile()));
	}

	@Override
	public void connect() throws IOException {

		if (importer == null) {
			throw new IOException(errorMessage);
		}
		importer.connect();

		cap = new DeviceCapabilities(SimulationDriver.class);

		RpMetric[] waveforms = null; //  // getWaveforms(
		if (conf != null) {
			waveforms = conf.getWaveforms();
		}
		// );
		// getWaveforms();
		int tot = 0;
		if (waveforms != null) {
			tot += waveforms.length;

			for (RpMetric desc : waveforms) {
				if (packetRate == 0) {
					System.err.println("--BAD SAMPLE RATE METHOD--");
					this.packetRate = desc.getSampleRate();
				}
				String sigName = desc.getName();
				// cap.addWaveform("?", "?code", sigName, desc.getSampleRate(), desc.getSamplesPerPacket(), "mV");
			}
			cap.setWaveforms(waveforms);
		}

		do {
			curr = importer.next();
			msDatatime = curr.getTime();
		} while (msDatatime == 0); // this really shouldn't happen...but it does
		msInitial = msDatatime;

		resetDeltaTm(0);

		running = true;
		t = new Thread(new SimulationTickThread());
		t.start();

	}

	private void resetDeltaTm(long dtOffset) {

		msDelta = Calendar.getInstance().getTimeInMillis() - msInitial - dtOffset;
		System.out.println("       got [initial=" + msInitial + " dtoffset=" + dtOffset + "] gives [delta=" + msDelta
				+ "]");

	}

	@Override
	public void disconnect() {
		if (t != null) {
			running = false;
			t.interrupt();
			t = null;
		}

		// importer.disconnect();

	}

	private long pauseStart;
	private long autoPauseAt;

	private int dbg_idx;

	public void tick() {

		dbg_idx++;
		if (dbg_idx >= 80) {
			System.out.println();
			dbg_idx = 0;
		}

		try {
			curr = importer.next();
		} catch (Exception ex) {
			setStatus(ConnectionStatus.DATA_NOT_AVAIL);
			pause = true;
		}

	}

	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return conf;
	}

	public PiDatastreamImporter getSimulatorDevice(int idx) {
		PiDatastreamImporter[] devices = importer.getDevices();

		return devices[idx];
	}

	@Override
	public AdapterInterface getSubInterface(String devName) {
		System.err.println("incomplete code in SimulationDriver");
		System.exit(0);
		return null;
	}

	@Override
	public AdapterInterface[] getSubInterfaces() {
		PiDatastreamImporter[] devices = importer.getDevices();

		AdapterInterface[] intfs = new AdapterInterface[devices.length];
		for (int i = 0; i < devices.length; i++) {
			intfs[i] = new NullDevice(null, devices[i].getConfiguration());
		}
		return intfs;
	}

	public void setPause(boolean pause) {
		if (t == null) {
			// only process this message if we are running
			return;
		}
		if (this.pause == pause) {
			// only process this message on state change
			return;
		}

		this.pause = pause;

		Date now = new Date();
		if (pause) {
			pauseStart = now.getTime();
			autoPauseAt = 0; // disable next autopause
		} else {
			long pauseEnd = now.getTime();
			long delta = pauseEnd - pauseStart;

			msDelta += delta; // push my delta further into the future
			System.out.println("additional delta=" + delta);

			t.interrupt();
		}
	}

	public void seek(long tm) throws IOException {
		System.out.println("\nseek tm=" + tm + " == " + new Date(tm));
		importer.seek(tm);

		resetDeltaTm(tm - msInitial);
	}

	public void addTime(int ms) {
		if (pause == true) {
			autoPauseAt = msDatatime + ms;
			setPause(false);
		}
	}

	public PiDatastreamImporter[] getDevices() {
		PiHdf5Importer h5i = (PiHdf5Importer) importer;
		return h5i.getDevices();
	}

	public void setRealtime(boolean realtime) {
		this.realtime = realtime;

		if (realtime) {
			if (curr != null) {
				msDatatime = curr.getTime();
				msInitial = msDatatime;
			}

			resetDeltaTm(0);
			System.out.println("reset tm");
		}

	}

}
