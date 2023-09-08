package idea.discovery;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Map.Entry;
import java.util.Set;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

public class TestTempusDiscovery {

	public static void main(String[] args) throws IOException {

		Path path = Paths.get("src/test/java/idea/discovery/tempus_vitalspkt.txt");
		byte[] data = Files.readAllBytes(path);

		String s = new String(data);
		JsonObject jsonObject = new JsonParser().parse(s).getAsJsonObject();

		Set<Entry<String, JsonElement>> entries = jsonObject.entrySet();
		for (Entry<String, JsonElement> entry : entries) {
			String key = entry.getKey();
			JsonElement value = entry.getValue();
			if ("vitals".equals(key)) {
				JsonObject vitals = (JsonObject) value;
				JsonArray values$ = (JsonArray) vitals.get("$values");
				System.out.println("NEW VITALS RECORD");
				for (int i = 0; i < values$.size(); i++) {
					JsonObject kkey = (JsonObject) values$.get(i);
					System.out.println("kkey=" + kkey);
					JsonObject signs = (JsonObject) kkey.get("signs");
					JsonArray vvalues$ = (JsonArray) signs.get("$values");
					System.out.println("vitals values=" + vvalues$);
					for (int j = 0; j < vvalues$.size(); j++) {
						JsonObject vitals_entry = (JsonObject) vvalues$.get(j);
						JsonElement src = vitals_entry.get("src");
						JsonElement name = vitals_entry.get("name");
						JsonElement val = vitals_entry.get("val");
						System.out.println(
								"vitals-entry=" + src.getAsString() + "." + name.getAsString() + " --> " + val.getAsDouble());
					}
				}
			}
			System.out.println("entry: " + entry.getKey() + " value=" + value + " cl=" + value.getClass());
		}
		return;
	}
}
