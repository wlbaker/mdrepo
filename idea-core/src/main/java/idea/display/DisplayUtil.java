package idea.display;

import static java.awt.Color.CYAN;
import static java.awt.Color.GREEN;
import static java.awt.Color.MAGENTA;
import static java.awt.Color.ORANGE;
import static java.awt.Color.RED;
import static java.awt.Color.WHITE;
import static java.awt.Color.YELLOW;

import java.awt.Color;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map.Entry;

import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DisplayUtil {

	private static HashMap<Byte, Color> colors = new HashMap<Byte, Color>();

	static {
		colors.put((byte) 0, Color.BLACK);
		colors.put((byte) 1, Color.BLACK);
		colors.put((byte) 2, WHITE); // confirmed
		colors.put((byte) 3, RED);   // confirmed
		colors.put((byte) 4, MAGENTA);  // unconfirmed
		colors.put((byte) 5, YELLOW);
		colors.put((byte) 10, GREEN);
		colors.put((byte) 11, Color.CYAN);  // blue for text
		colors.put((byte) 12, ORANGE);
		colors.put((byte) 14, CYAN);
		colors.put((byte) 20, Color.CYAN);  // blue for waveforms
		colors.put((byte) 99, Color.DARK_GRAY);
	}

	private static HashMap<String, ParameterLayout> params = new HashMap<>();

	static {
		params.put("00: Default", new ParameterLayout((byte) 0, 3));
		params.put("01: ECG HR", new ParameterLayout((byte) 1, 3));
		params.put("02: SPO2 & PLS", new ParameterLayout((byte) 2, 2));
		params.put("04: ABP", new ParameterLayout((byte) 4, 3));
		params.put("08: RESP", new ParameterLayout((byte) 8, 3));
		params.put("09: TEMP", new ParameterLayout((byte) 9, 2));
		params.put("19: MULTIGAS", new ParameterLayout((byte)19, 6));
		params.put("20: PCCI", new ParameterLayout((byte) 20, 3));
		params.put("33: GEDVI", new ParameterLayout((byte) 33, 3));
		params.put("80: Philips", new ParameterLayout((byte) 80, 2));
		params.put("81: Philips", new ParameterLayout((byte) 81, 7));
		params.put("91: Evita F1", new ParameterLayout((byte) 91, 1));
		params.put("92: Evita F2", new ParameterLayout((byte) 92, 2));
		params.put("95: Evita Dial", new ParameterLayout((byte) 95, 1));
		params.put("96: Evita i2E", new ParameterLayout((byte) 96, 2));
	}

	public static Color getColorFromDrager(byte foreground) {
		Color color = colors.get(foreground);
		if (color == null) {
			log.debug("Could not find color: {}", foreground);
			color = MAGENTA;
		}
		return color;
	}

	public static byte getDragerFromColor(Color color) {
		for (Entry<Byte, Color> entry : colors.entrySet()) {

			if (color == entry.getValue()) {
				return entry.getKey();
			}
		}

		return 0;
	}

	public static WaveformData getBandSignal(BandLayout band, RpMetric metric) {
		List<WaveformData> waves = band.getWaves();
		if (waves == null) {
			return null;
		}
		for (WaveformData wave : waves) {
			if (metric.getLocation().equals(wave.getLoc())) {
				return wave;
			}
		}
		return null;
	}

	public static Color[] getColors() {
		Collection<Color> vals = colors.values();

		Color[] rt = new Color[vals.size()];
		return vals.toArray(rt);
	}


	public static String[] getFormatNames() {
		Collection<String> vals = params.keySet();
		List<String> lvals = new LinkedList<>(vals);
		Collections.sort( lvals );
		String[] names = new String[lvals.size()];

		return lvals.toArray(names);
	}
	
	public static ParameterLayout getFormatByName(String name) {

		return params.get(name);
	}

	public static ParameterLayout[] getFormatLayouts() {
		Collection<ParameterLayout> vals = params.values();
		ParameterLayout[] param_formats = new ParameterLayout[vals.size()];

		return vals.toArray(param_formats);
	}

}
