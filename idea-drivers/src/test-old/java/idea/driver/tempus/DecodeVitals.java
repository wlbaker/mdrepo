package idea.driver.tempus;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Map.Entry;
import java.util.Set;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.stream.JsonReader;

import idea.model.IntfUtil;
import idea.model.dev.Tempus_Vitals;
import idea.schema.rp.RpMetric;

public class DecodeVitals {

	private Tempus_Vitals jsonToTempusVitals(String s) {
		Tempus_Vitals tv = new Tempus_Vitals();
		
		JsonElement jelement = new JsonParser().parse(s);
		JsonObject job = jelement.getAsJsonObject();

		System.out.println("VITALS=");
		JsonObject vitals_root = (JsonObject) job.get("vitals");
		// Set<Entry<String, JsonElement>> keys = vitals_root.entrySet();
		// for( Entry<String, JsonElement> entry : keys ) {
		// JsonElement v = entry.getValue() ;
		// System.out.println("* key=" + entry.getKey() + " value=" + v );
		// dump(v);
		// }
		//

		System.out.println("VALUES=");
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

	public static void main(String[] args) throws IOException, URISyntaxException {
		DecodeVitals v = new DecodeVitals();

		String fileName = "/idea/driver/tempus/vitals.json";
		fileName = "vitals.json";
		String message= new String(Files.readAllBytes(Paths.get(v.getClass().getResource(fileName).toURI())));

		v.jsonToTempusVitals(message);
	}

}
