package idea.process;

import icuInterface.events.ConnectionItem;
import idea.intf.AdapterInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;

import java.util.Map;

import javax.script.ScriptEngine;
import javax.script.ScriptException;

import lombok.extern.slf4j.Slf4j;
import idea.JavascriptUtil;
import idea.analysis.AnalysisPanelInterface;
import idea.analysis.CosmosAnalysisPanel;
import idea.meddaq.AppModel;


@Slf4j
public class BannerProcess implements AnalysisPanelInterface, StreamConsumer {

	private RpAnalysis anal;
	ScriptEngine engine;
	private String listen1Name;
	private String destName;
	private String startupScript;
	private String triggerScript;
	private String timeoutScript;
	private String alarmScript;
	private String tickScript;
	AdapterInterface dest = null;
	private int tick;
//	private NullDevice ticker;  // this device only exists here to proxy the tick() function call

	private static final RpAnalysis analysisInfo;
	static { 
		analysisInfo = new RpAnalysis();
		analysisInfo.setName("Script");
		analysisInfo.setAnalysisClass( BannerProcess.class.getCanonicalName() );
		// analysisInfo.
	}

	public BannerProcess(StreamProducer[] drivers, RpAnalysis anal) {
		this.anal = anal;

		engine = JavascriptUtil.initEngine();
		AppModel app = AppModel.getInstance();
		engine.put("app", app);

		Map<String,String> params = anal.getParam();
		for (String key : params.keySet()) {
			String val = params.get(key);
			if (key.equals("listen1")) {
				listen1Name = val;
			} else if (key.equals("dest")) {
				destName = val;
			} else if (key.equals("startup_script")) {
				startupScript = val;
			} else if (key.equals("trigger_script")) {
				triggerScript = val;
			} else if (key.equals("timeout_script")) {
				timeoutScript = val;
			} else if (key.equals("alarm_script")) {
				alarmScript = val;
			} else if (key.equals("tick_script")) {
				tickScript = val;
			}
		}
		
//		DeviceConfiguration nconf = new DeviceConfiguration(NullDevice.class);
//		nconf.setName("banner_dummy");
//		ticker = new NullDevice(nconf) {
//
//			@Override
//			public void tick() {
//				super.tick();
//			}
//			
//		};

		try {
			wire(drivers);
		} catch (ScriptException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void wire(StreamProducer[] drivers) throws ScriptException {

		for (StreamProducer driver : drivers) {
			RpDevice conf = driver.getConfiguration();

			String driverName = null;
			if (conf != null && conf.getName() != null) {
				driverName = conf.getName();
				if (driverName.length() == 0) {
					driverName = null;
				}

			}

			if (driverName == null) {
				log.error("error wiring banner process: driver name not found");
			} else {
				engine.put(driverName, driver);
				if (driverName.equals(destName)) {
					engine.put("dest", driver);
				} else if (driverName.equals(listen1Name)) {
					engine.put("trigger", driver);
					driver.addStreamListener(StreamID.MEASUREMENT, this);
					driver.addStreamListener(StreamID.CONNECTION, this);
				}
			}

		}

		if (startupScript != null && startupScript.length() > 0) {
			log.warn("unfortunately...dest device is probably not connected");
			engine.eval(startupScript);
		}
	}

	@Override
	public void clear() {
		// TODO Auto-generated method stub

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (triggerScript == null || triggerScript.length() == 0) {
			return;
		}

		try {
			AppModel app = AppModel.getInstance();
			engine.put("app", app);
			engine.put("bbt", null );

			if (sid == StreamID.MEASUREMENT) {
				tick = 0;
				if (triggerScript != null && triggerScript.length() > 0) {
					engine.put("block", item);
					engine.eval(triggerScript);
				}
			} else if (sid == StreamID.CONNECTION) {
				tick = 0;
				ConnectionItem cev = (ConnectionItem) item;
				cev.getStatus();
				if (startupScript != null && startupScript.length() > 0) {
					engine.put("cevt", cev);
					engine.eval(startupScript);
				}
			}
		} catch (ScriptException e) {
			String name = "<dev?>";
			if (anal != null) {
				name = anal.getName();
			}
			log.error("{} --> banner script error: {}", name, e.getMessage());
		} catch (RuntimeException e) {
			log.error("RT --> banner script error: {}", e.getMessage());
		}
	}

	@Override
	public void autoscale() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public StreamProducer[] getSignalProducers() {
		//SignalProducer[] producers = new SignalProducer[] { ticker };
		//return producers;
		return null;
	}

	@Override
	public void tick() {
		tick++;
		
		if( tickScript == null || tickScript.length() == 0 ) {
			
			if( tick > 10 ) {
				clear();
			}
		} else {
			try {
				AppModel app = AppModel.getInstance();
				engine.put("app", app);
				engine.put("bbt", null );
				engine.eval(tickScript);
			} catch (ScriptException e) {
				String name = "<dev?>";
				if (anal != null) {
					name = anal.getName();
				}
				log.error(name + " --> tick script error: {}", name, e.getMessage());
			}

		}
	}

	public static RpAnalysis getAnalysisInfo() {
		return analysisInfo;
	}
}
