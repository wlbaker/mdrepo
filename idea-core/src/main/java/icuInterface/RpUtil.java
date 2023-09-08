package icuInterface;

import icuInterface.conf.dev.PhidgetDeviceConfiguration;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.conf.DeviceConfiguration;
import idea.display.BandLayout;
import idea.display.ParameterLayout;
import idea.display.FieldData;
import idea.display.WaveformData;
import idea.driver.NullDevice;
import idea.message.StreamID;
import idea.model.DisplayConfig;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpBandData;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpDisplay;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPboxData;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpUnit;
import idea.schema.rp.RpWaveformSetup;
import idea.schema.rp.StringStringMap;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.List;
import java.util.Map.Entry;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class RpUtil {

	public static RpMetric createRpMetric(String m) {

		RpMetric locRp = new RpMetric();
		locRp.setLocation(m);

		return locRp;
	}

	public static boolean hasMetric(List<RpMetric> list, RpMetric mdesc) {
		boolean found = false;
		for (RpMetric metric : list) {
			if (metric.getLocation().equals(mdesc.getLocation())) {
				found = true;
				break;
			}
		}

		return found;
	}

	public static boolean hasWaveform(RpDevice dev, RpMetric desc) {
		RpStream stream = RpUtil.getStream(dev, StreamID.WAVEFORM);
		boolean hasIt = false;
		if (stream != null) {
			RpMetric m = RpUtil.getMetric(stream.getMetric(), desc.getLocation());
			hasIt = (m != null);
		}
		return hasIt;
	}

	private static RpMetric getMetric(List<RpMetric> metrics, String loc) {
		for (RpMetric metric : metrics) {
			if (loc.equals(metric.getLocation())) {
				return metric;
			}
		}
		return null;
	}

	@Deprecated
	public static boolean hasWaveform(List<RpMetric> list, RpMetric wdesc) {
		boolean found = false;
		for (RpMetric wave : list) {
			if (wave.getLocation().equals(wdesc.getLocation())) {
				found = true;
				break;
			}
		}

		return found;
	}

	public static void resetDC(RpDevice conf) {
		for (RpStream stream : (List<? extends RpStream>)conf.getStreams()) {
			List<RpMetric> metrics = stream.getMetric();
			while (metrics.size() > 0)
				metrics.remove(0);
		}
	}

	public static void removeDevice(List<RpDevice> devices, RpDevice dev) {
		devices.remove(dev);
	}

	@Deprecated
	public static DeviceConfiguration createDeviceConfiguration(RpDevice device, boolean with_globals) {

		log.warn("DEPRICATED call to createDeviceConfiguration");
		DeviceConfiguration conf = null;

		String s_cl = device.getDeviceClass();
		Class<?> cl = null;

		if (s_cl == null) {
			// this must be a sub-device. create a generic configuration
			conf = new DeviceConfiguration(s_cl);
		} else {

			try {
				cl = Class.forName(s_cl);
			} catch (ClassNotFoundException e) {
				log.error("Class not found/substituting NullDevice: {}", s_cl);
				cl = NullDevice.class;
			}
			try {
				Method m = cl.getMethod("createConfigInstance", null);
				conf = (DeviceConfiguration) m.invoke(null, null);
			} catch (Exception e) {
				log.error("createConfigInstance", e);
			}
		}

		if (device.getDevices() != null) {
			for (RpDevice sub_dev : (List<? extends RpDevice>)device.getDevices()) {
				DeviceConfiguration sub_conf = createDeviceConfiguration(sub_dev, false);
				conf.addDevice(sub_conf);
			}
		}

		for (RpStream stream : (List<? extends RpStream>)device.getStreams()) {
			conf.addStream(stream);
		}

		conf.setName(device.getName());
		conf.setModelName(device.getModelName());
		conf.setDriverName(device.getDriverName());

		if (conf instanceof SerialDeviceConfiguration) {
			SerialDeviceConfiguration sdc = (SerialDeviceConfiguration) conf;
			sdc.setPort(device.getConnectionValue());
		}
		if (conf instanceof SocketDeviceConfiguration) {
			SocketDeviceConfiguration sdc = (SocketDeviceConfiguration) conf;
			sdc.setHost(device.getConnectionValue());
		}
		if (conf instanceof PhidgetDeviceConfiguration) {
			PhidgetDeviceConfiguration sdc = (PhidgetDeviceConfiguration) conf;
			int serNo = 0;
			try {
				serNo = Integer.parseInt(device.getConnectionValue());
			} catch (Exception e) {
				// ignore...probably says "no phidget" / "any phidget"
			}
			sdc.setSerNo(serNo);
		}

		boolean copySettings = true;

		StringStringMap params = device.getParam();
		if (params != null) {
			for (Entry<String, String> param : params.entrySet()) {
				String key = param.getKey();
				Object value = param.getValue();
				try {
					if (copySettings) {
						conf.putParam(key, value.toString());
					}
					applyParameter(conf, key, value);
				} catch (Exception e) {
					log.warn("could not apply parameter: {} value: {}", key, value);
				}
			}
		}

		return conf;
	}

	private static void applyParameter(Object o, String key, Object value) throws Exception {

		Class<?> clazz = o.getClass();

		byte[] bytes = key.getBytes();
		bytes[0] = (byte) Character.toUpperCase(bytes[0]);
		String methodName = "set" + new String(bytes);

		Method method;
		try {
			method = clazz.getMethod(methodName, value.getClass());
			method.invoke(o, value);
		} catch (NoSuchMethodException e) {
			try {
				method = clazz.getMethod(methodName, Integer.class);
				method.invoke(o, Integer.parseInt(value.toString()));
			} catch (Exception e2) {
				method = clazz.getMethod(methodName, Double.class);
				method.invoke(o, Double.parseDouble(value.toString()));
			}
		}
	}

	public static DeviceConfiguration createGlobalDeviceConfiguration(RpDevice device) {

		DeviceConfiguration conf = null;

		String s_cl = device.getDeviceClass();
		Class<?> cl = null;

		if (s_cl == null) {
			// this must be a sub-device. create a generic configuration
			conf = new DeviceConfiguration(s_cl);
		} else {

			try {
				cl = Class.forName(s_cl);
				Method m = cl.getMethod("createConfigInstance", null);
				conf = (DeviceConfiguration) m.invoke(null, null);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

		conf.setName(device.getName());
		conf.setModelName(device.getModelName());
		conf.setDriverName(device.getDriverName());

		return conf;
	}

	public static RpHardware createHardware(PiDatastreamImporter[] devices) {
		RpHardware hw_conf = new RpHardware();
		hw_conf.setName("fromDevices");
		List<RpDevice> hw_devs = hw_conf.getDevices();
		for (PiDatastreamImporter device : devices) {
			RpDevice dev = RpUtil.createDeviceFromImporter(device);
			hw_devs.add(dev);
		}
		return hw_conf;
	}

	private static RpDevice createDeviceFromImporter(PiDatastreamImporter device) {
		RpDevice hw_dev = new RpDevice();
		for (StreamID sid : device.getStreams()) {
			RpStream stream = new RpStream();
			stream.setName(sid.getName());
			Class<? extends PersistentItem> model = device.getModel(sid);
			stream.getMetric().addAll(Arrays.asList(IntfUtil.getMetrics(model)));
		}
		return hw_dev;
	}

	public static DisplayConfig parseDisplay(RpDisplay rp_disp) {
		DisplayConfig disp = new DisplayConfig();

		disp.setVertPboxes((short) rp_disp.getVertPBoxes());
		disp.setOpmode((short) rp_disp.getOpmode());

		List<RpBandData> rp_bands = rp_disp.getBandData();
		for (RpBandData rp_band : rp_bands) {

			List<RpWaveformSetup> rp_waves = rp_band.getWaveformSetup();
			WaveformData[] waves = null;
			if (rp_waves != null) {
				waves = new WaveformData[rp_waves.size()];

				int wv_idx = 0;
				for (RpWaveformSetup rp_wave : rp_waves) {
					String loc = rp_wave.getLoc();
					WaveformData wave = new WaveformData(loc);
					String color = rp_wave.getWaveColor();
					if (color != null) {
						wave.setWaveColor(Byte.parseByte(color));
					}
					wave.setRangeMin((short) rp_wave.getRangeMin());
					wave.setRangeMax((short) rp_wave.getRangeMax());

					if (wave.getRangeMin() == wave.getRangeMax()) {
						// use some safe defaults if these are not set
						wave.setRangeMin((short) 0);
						wave.setRangeMax((short) 100);
					}
					waves[wv_idx] = wave;
					wv_idx++;
				}
			}
			BandLayout band = new BandLayout((byte) rp_band.getBandNum(), (byte) rp_band.getBandAttr(), waves);
			band.setWeight( rp_band.getBandWeight() );
			disp.addBand(band);
		}

		List<RpPboxData> rp_boxes = rp_disp.getPboxData();
		if (rp_boxes != null) {
			disp.clearPBoxes();
			int pb_idx = 0;
			for (RpPboxData rp_box : rp_boxes) {
				List<RpMetric> rp_params = rp_box.getParamSetup();
				FieldData[] params = null;
				if (rp_params != null) {
					params = new FieldData[rp_params.size()];

					int p_idx = 0;
					for (RpMetric rp_param : rp_params) {
						String loc = rp_param.getLocation().toString();
						RpUnit unit = rp_param.getUnit();
						byte uom = 0;
						if (unit != null) {
							uom = 99; // FIXME: This is incorrect...maybe need standard list of units?
						}

						params[p_idx] = new FieldData(loc, uom);
						p_idx++;
					}
				}
				ParameterLayout box = new ParameterLayout((byte) rp_box.getPboxId(), (byte) rp_box.getPboxFormat(),
						(byte) rp_box.getForeground(), params);
				disp.addParamBox(box);
			}
		}

		return disp;
	}

	public static RpDisplay createDisplay(DisplayConfig disp) {
		RpDisplay rp_disp = new RpDisplay();

		rp_disp.setVertPBoxes(disp.getVertPboxes());
		rp_disp.setOpmode(disp.getOpmode());

		// rp_disp.setName("fromDevices");
		List<BandLayout> bands = disp.getBands();

		if (disp.getNumPBoxes() > 0) {
			List<RpPboxData> list = rp_disp.getPboxData();
			for (ParameterLayout box : disp.getParameterBoxs()) {
				list.add(RpUtil.createPboxData(box));
			}
		}

		List<RpBandData> rp_bands = rp_disp.getBandData();
		for (BandLayout band : bands) {
			RpBandData rp_band = new RpBandData();
			rp_bands.add(rp_band);

			rp_band.setBandNum(band.getBandNumber());

			List<RpWaveformSetup> rp_waves = rp_band.getWaveformSetup();
			if (band.getWaveCount() > 0) {
				for (WaveformData wave : band.getWaves()) {
					RpWaveformSetup rp_wave = new RpWaveformSetup();
					rp_wave.setLoc(wave.getLoc());
					rp_wave.setRangeMin(wave.getRangeMin());
					rp_wave.setRangeMax(wave.getRangeMin());
					rp_wave.setWaveColor("" + (int) wave.getWaveColor());
					rp_waves.add(rp_wave);
				}
			}

		}
		return rp_disp;
	}

	private static RpPboxData createPboxData(ParameterLayout box) {
		RpPboxData pbox = new RpPboxData();
		pbox.setForeground(box.getForeground());
		pbox.setPboxFormat(box.getFormat());

		List<RpMetric> list = pbox.getParamSetup(); //

		for (FieldData param : box.getFieldData()) {
			// MetricDescription m = param.getMetricDescription();
			String loc = param.getLoc();
			if (loc == null) {
				System.err.println("skipping param in pbox: no description");
			} else {
				list.add(RpUtil.createRpMetric(loc));
			}
		}
		return pbox;
	}

	/*
	 * 
	 * Converts XMLGregorianCalendar to java.util.Date in Java
	 * 
	 */

	// public static Date toDate(XMLGregorianCalendar calendar) {
	//
	// if (calendar == null) {
	//
	// return null;
	//
	// }
	//
	// return calendar.toGregorianCalendar().getTime();
	//
	// }

	public static List<? extends RpMetric> getMetrics(RpDevice dev, StreamID sid) {
		RpStream stream = RpUtil.getStream(dev, sid);
		List<RpMetric> metrics = null;
		if (stream != null) {
			metrics = stream.getMetric();
		}
		return metrics;
	}

	public static RpStream getStream(RpDevice dev, StreamID sid) {
		if (dev == null) {
			return null;
		}

		List<RpStream> streams = dev.getStreams();

		for (RpStream stream : streams) {
			String stream_name = stream.getName();
			if (stream_name == null) {
				log.warn("Unnamed stream, assuming waveform");
				stream_name = StreamID.WAVEFORM.getName();
			}
			if (sid.getName().equals(stream_name)) {
				return stream;
			}
		}

		return null;
	}

	public static void addMetric(RpDevice dev, StreamID sid, RpMetric metric) {
		RpStream s = getStream(dev, sid);
		if( s == null ) {
			s = new RpStream();
			s.setName( StreamID.MEASUREMENT.getName() );
			dev.getStreams().add(s);
		}
		s.getMetric().add(metric);
	}

	public static RpMetric createRpMetric(String loc, String code, String name, RpUnit unit, int subtyp) {
		RpMetric metric = new RpMetric();
		metric.setLocation(loc);
		metric.setCode(code);
		metric.setName(name);
		metric.setUnit(unit);
		metric.setSubtyp(subtyp);
		return metric;
	}

	public static RpMetric createRpMetric(String loc, String code, String name, int rate, int spp, RpUnit unit) {
		RpMetric metric = new RpMetric();
		metric.setLocation(loc);
		metric.setCode(code);
		metric.setName(name);
		metric.setUnit(unit);
		metric.setSampleRate(rate);
		metric.setSamplesPerPacket(spp);
		// metric.setSubtyp(subtyp);
		return metric;
	}

	public static RpMetric getMetricFromStreamID(RpDevice conf, StreamID waveform, String loc) {
		RpMetric metric = null;

		RpStream stream = getStreamFromName(conf.getStreams(), waveform.getName());
		if (stream != null) {
			metric = getMetricFromStream(stream, loc);
		}
		return metric;
	}

	public static RpMetric getMetricFromStream(final RpStream stream, final String loc) {
		if (stream != null) {
			for (RpMetric metric : (List<? extends RpMetric>)stream.getMetric()) {
				if (loc.equals(metric.getLocation())) {
					return metric;
				}
			}
		}
		return null;
	}

	public static RpStream getStreamFromName(final List<RpStream> streams, final String name) {
		if (streams == null) {
			return null;
		}
		for (RpStream stream : streams) {
			if (name.equals(stream.getName())) {
				return stream;
			}
		}
		return null;
	}

	public static void setParam(RpDevice conf, String key, String val) {
		StringStringMap params = conf.getParam();
		if (params == null) {
			params = new StringStringMap();
			conf.setParam(params);
		}
		params.put(key, val);

	}

	public static void setParam(RpStudy conf, String key, String val) {
		StringStringMap params = conf.getParam();
		if (params == null) {
			params = new StringStringMap();
			conf.setParam(params);
		}
		params.put(key, val);
	}

	public static void setParam(RpAnalysis anal, String key, String val) {
		StringStringMap params = anal.getParam();
		if (params == null) {
			params = new StringStringMap();
			anal.setParam(params);
		}
		params.put(key, val);

	}

	public static String getParam(RpDevice conf, String key) {
		StringStringMap params = conf.getParam();
		if (params == null) {
			params = new StringStringMap();
			conf.setParam(params);
		}

		String val = params.get(key);
		if (val == null) {
			if (conf instanceof SerialDeviceConfiguration) {
				SerialDeviceConfiguration sd = (SerialDeviceConfiguration) conf;
				if ("port".equals(key)) {
					val = sd.getPort();
				}
			}
		}

		return val;
	}

	public static String getParam(RpStudy conf, String key) {
		StringStringMap params = conf.getParam();
		if (params == null) {
			params = new StringStringMap();
			conf.setParam(params);
		}

		return params.get(key);
	}

	public static RpAnalysis getAnalysisInfo(Class<?> c) {
		Field field;

		if (c == null) {
			return null;
		}

		RpAnalysis analysis = null;

		try {
			field = c.getDeclaredField("analysisInfo");
			if (field.isAccessible() == false) {
				field.setAccessible(true);
			}
			analysis = (RpAnalysis) field.get(c);
			analysis.setAnalysisClass(c.getCanonicalName());
		} catch (Exception e) {
			log.debug("no analysis field for class: {}", c); // really not a problem
			return null;
		}

		return analysis;

	}

	public static String getConnectionPort(RpDevice conf) {
		String portName = RpUtil.getParam(conf, "port");
		if (portName == null) {
			portName = conf.getConnectionValue();
		}
		return portName;
	}

	public static double getDoubleParam(RpDevice conf, String key) {
		double d = Double.NaN;
		String val = RpUtil.getParam(conf, key);
		if (val != null) {
			d = Double.parseDouble(val);
		}
		return d;
	}

	public static RpDevice getDeviceByName(RpStudy study, String key) {
		RpHardware hw = study.getHardware().get(0);
		List<RpDevice> devs = hw.getDevices();
		if( devs != null ) {
			for( RpDevice dev : devs ) {
				if( dev.getName().equals(key)) {
					return dev;
				}
			}
		}
		return null;
	}

	public static RpAnalysis clone(RpAnalysis anal) {
		RpAnalysis clone = new RpAnalysis();
		clone.setAnalysisClass( anal.getAnalysisClass() );
		clone.setName( anal.getName() );
		StringStringMap map = anal.getParam();
		if( map != null ) {
			clone.setParam( RpUtil.clone(map) );
		}
		
		return clone;
	}

	private static StringStringMap clone(StringStringMap map) {
		StringStringMap clone = new StringStringMap();
		clone.putAll( map );
		return clone;
	}

}
