package idea.meddaq;

import idea.intf.StreamProducer;
import idea.schema.rp.RpDevice;

import java.util.LinkedList;

import lombok.extern.slf4j.Slf4j;
import idea.analysis.AnalysisPanelInterface;

@Slf4j
public class AppModel {

	// driver-list goes here
	public static int RUN = 2;
	// private RpAnalysis analConfs;

	public static int SIMULATION = 1;

	public static int STOP = 3;

	// WARNING: the model is duplicated here between IDEAServer
	// and AppModel...really should have IDEAServer be the only
	// device list holder
	public static LinkedList<AnalysisPanelInterface> analysisList;
	private static AppModel model = null;
	private static boolean capturing;

	private AppModel() {
		// only self-invoked via getInstance()
	}

	public static AppModel getInstance() {
		if (model == null) {
			model = new AppModel();
		}
		return model;
	}

	// scripts call this function
	public static StreamProducer getSignalProducer(String name) {
		StreamProducer producer = null;
		MedDAQFrame inst = MedDAQFrame.getInstance();
		
		if (inst == null) {
			log.error("AppModel not initialized");
		} else {
			producer = inst.getSignalProducer(name);
			if (producer == null) {
				producer = getAnalysisProducer(name);
			}
		}

		return producer;
	}

	private static StreamProducer getAnalysisProducer(String name) {
		StreamProducer producer = null;

		StreamProducer[] drivers = getAnalysisDrivers();
		if (drivers != null) {
			for (StreamProducer driver : drivers) {

				if( driver == null ) {
					log.error("null driver in driver list!");
					continue;
				}
				RpDevice conf = driver.getConfiguration();
				if( conf == null ) {
					log.error("no configuration for driver: {}", driver);
					continue;
				}
				String dname = conf.getName();
				if (dname.startsWith(name)) {
					// FIXME: partial name matches are bad
					producer = driver;
					break;
				}
			}
		}
		return producer;
	}

	public static void tick() {

		if (analysisList != null) {
			synchronized (analysisList) {
				for (AnalysisPanelInterface anal : analysisList) {
					if( anal == null ) {
						log.error("null analysis panel");
					} else {
						anal.tick();
					}
				}
			}
		}

	}

	@Deprecated
	public static StreamProducer[] getAnalysisDrivers() {
		if (analysisList == null || analysisList.size() == 0) {
			return null;
		}

		int tot = 0;
		for (AnalysisPanelInterface anal : analysisList) {
			if (anal instanceof StreamProducer) {
				tot++;
			}
			StreamProducer[] producers = anal.getSignalProducers();
			if (producers != null) {
				tot += producers.length;
			}
		}

		int idx = 0;
		StreamProducer[] drivers = new StreamProducer[tot];
		for (AnalysisPanelInterface anal : analysisList) {
			if (anal instanceof StreamProducer) {
				drivers[idx++] = (StreamProducer) anal;
			}
			StreamProducer[] producers = anal.getSignalProducers();
			if (producers != null) {
				for (StreamProducer producer : producers) {
					drivers[idx++] = producer;
				}
			}
		}

		return drivers;
	}

	@Deprecated
	public static StreamProducer[] getDerivedDrivers() {
		if (analysisList == null || analysisList.size() == 0) {
			return null;
		}

		int tot = 0;
		for (AnalysisPanelInterface anal : analysisList) {
			if (anal instanceof StreamProducer) {
				tot++;
			}
		}

		int idx = 0;
		StreamProducer[] drivers = new StreamProducer[tot];
		for (AnalysisPanelInterface anal : analysisList) {
			if (anal instanceof StreamProducer) {
				drivers[idx++] = (StreamProducer) anal;
			}
		}

		return drivers;
	}

	public static void setCapturing(boolean b) {
		capturing = b;
	}

	public static boolean isCapturing() {
		return capturing;
	}

	public static void startGlobalPanel( MedDAQPanel mp) {
			System.err.println("CODE IS A STEP BACKWARDS...REMOVING HACK: NO GLOBAL PANEL");
			// RpAnalysis anal = new RpAnalysis();
			// anal.setAnalysisClass("idea.analysis.EntropySummaryPanel");
			// SignalProducer[] drivers = new SignalProducer[analysisList.size()];
			// analysisList.toArray(drivers);
			// JPanel panel;
			// try {
			// panel = buildAnalysisPanel(archive_consumer, mp, 0, anal, drivers);
			// mp.addGlobalPanel(panel);
			// } catch (Exception e) {
			// e.printStackTrace();
			// }

	}

	public static void addAnalysis(AnalysisPanelInterface p) {
		if( p == null ) {
			log.error("cannot add null analysis panel");
			return;
		}
		if (analysisList == null) {
			analysisList = new LinkedList<AnalysisPanelInterface>();
		}

		analysisList.add( p);
		
	}
	
	public void debugPrint() {
		System.out.println("debug print");
	}

}
