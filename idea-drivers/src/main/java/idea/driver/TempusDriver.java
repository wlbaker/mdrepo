package idea.driver;


import java.io.IOException;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.Tempus_Vitals;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

/**
 * Class to implement callback methods from Tempus Listener API. 
 */
@Slf4j
public class TempusDriver extends AbstractStreamProducer implements AdapterInterface {
    
	private static final String driverName = "monitor/TempusPRO";


	private static DeviceCapabilities static_cap;

	private static Tempus_Vitals vitals = new Tempus_Vitals();
	static {

		static_cap = new DeviceCapabilities(TempusDriver.class);

		static_cap.addStream(StreamID.MEASUREMENT, Tempus_Vitals.class);

	}
	
	Gson gson = new Gson();
	private RpDevice conf;

	public static SocketDeviceConfiguration createConfigInstance() {
		SocketDeviceConfiguration conf = new SocketDeviceConfiguration(TempusDriver.class);
		conf.setPort(9900);
		conf.setName("Tempus");
		return conf;
	}
	
	public TempusDriver(RpDevice conf) {
		this.conf = conf;
    }
    
	public Tempus_Vitals jsonToTempusVitals(String s) {
		Tempus_Vitals tv = new Tempus_Vitals();
		
		JsonElement jelement = new JsonParser().parse(s);
		JsonObject job = jelement.getAsJsonObject();

		JsonObject vitals_root = (JsonObject) job.get("vitals");
		JsonArray vitals_arr = (JsonArray) vitals_root.get("$values");
		for (int i = 0; i < vitals_arr.size(); i++) {
			JsonObject v = (JsonObject) vitals_arr.get(i);
			JsonObject signs_root = (JsonObject) v.get("signs");
			JsonArray signs_arr = signs_root.get("$values").getAsJsonArray();
			for (int j = 0; j < signs_arr.size(); j++) {
				JsonObject sign = signs_arr.get(j).getAsJsonObject();
				JsonElement code = sign.get("code");
				JsonElement name = sign.get("name");
				JsonElement value = sign.get("val");
				JsonElement unit = sign.get("units");
				JsonElement src = sign.get("src");
				populate(tv,  (src == null) ? null : src.getAsString(), //
						name.getAsString(), //
						(code == null) ? null : code.getAsString(), //
						value.getAsDouble(), //
						unit.getAsString() );
			}
		}

		return tv;
	}

	private void populate(Tempus_Vitals tv, String src, String name, String code, double value, String unit) {
		if( name.equals("Sys") || name.equals("Dia") || name.equals("Mean")) {
			src = src.replace(":", "_");
			name = src + name;
		}
		RpMetric m = IntfUtil.getMetricByLoc(tv, name);
		if( m == null ) {
			System.err.print(" @Metric(loc=\"" + name + "\"" );
			if( code != null && code.length() > 0) System.err.print( ", code=\"" + code + "\")" );
			System.err.println( ", unit=\"" + unit + "\")" );
			
			System.err.println(" Double " + name + ";" );
			
		} else {
			IntfUtil.setScaledValue(tv, m, value);
		}
	}

    /**
     * This method is called when live vital data is sent by the tempus
     */
    public void onVitalReceived(int deviceNumber, String vitalMessage) {
    	// decode && fire event
		vitals = jsonToTempusVitals(vitalMessage);
		fireStreamEvent(0, this, StreamID.MEASUREMENT, vitals );

    }

	@Override
	public void connect() throws IOException {
		log.error("TempusDriver does not initiate connection");
	}

	@Override
	public void disconnect() throws IOException {
		log.error("TempusDriver does not understand disconnection");
	}

	@Override
	public DeviceConfiguration getStaticCapabilities() {
		return static_cap;
	}

	@Override
	public int tick() {
		// TODO Auto-generated method stub
		return 0;
	}


}
