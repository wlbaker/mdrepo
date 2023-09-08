package idea.model;

import icuInterface.RpUtil;
import icuInterface.UnitUtil;
import icuInterface.message.NumericBlock;
import idea.conf.CompositeDescription;
import idea.conf.DeviceCapabilities;
import idea.intf.DataTyp;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.persistence.CompositeMetric;
import idea.persistence.Metric;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.Text;
import idea.persistence.Waveform;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPrecisionUnit;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpUnit;
import idea.schema.rp.StringStringMap;

import java.io.PrintStream;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import javax.persistence.JoinColumn;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class IntfUtil {

	public static void bindMetricToField(RpMetric desc, PersistentItem parent)
			throws SecurityException, NoSuchMethodException {
		Class<? extends PersistentItem> c = parent.getClass();
		Field[] fields = c.getDeclaredFields();
		for (Field field : fields) {
			Metric m = field.getAnnotation(Metric.class);
			if (m != null && m.loc().equals(desc.getLocation())) {
				desc.getter = _getGetter(c, field);
				desc.setter = _getSetter(c, field);
				return;
			}
			Waveform w = field.getAnnotation(Waveform.class);
			if (w != null && w.loc().equals(desc.getLocation())) {
				desc.getter = _getGetter(c, field);
				desc.setter = _getSetter(c, field);
				return;
			}
			Text t = field.getAnnotation(Text.class);
			if (t != null && t.loc().equals(desc.getLocation())) {
				desc.getter = _getGetter(c, field);
				desc.setter = _getSetter(c, field);
				return;
			}
			JoinColumn jc = field.getAnnotation(JoinColumn.class);
			if (jc != null && jc.name().equals(desc.getCode())) {
				desc.getter = _getGetter(c, field);
				desc.setter = _getSetter(c, field);
				return;
			}

		}

		log.error("COULD NOT BIND FIELD: {} LOC: {}", desc, desc.getLocation());
		return;
	}

	public static RpMetric[] getMetrics(PersistentItem item) {
		Class<? extends PersistentItem> cl = item.getClass();

		return getMetrics(cl);
	}

	public static RpMetric[] getMetrics(Class<?> c) {
		Field field;

		if (c == null) {
			return null;
		}

		RpMetric[] metrics = null;

		try {
			field = c.getDeclaredField("metrics");
			if (field.isAccessible() == false) {
				field.setAccessible(true);
			}
			metrics = (RpMetric[]) field.get(c);
		} catch (Exception e) {
			log.error("no metrics field for class: {}", c, e);
			return null;
		}

		if (metrics == null) {
			metrics = buildMetrics(c);
			try {
				field.set(c, metrics);
			} catch (Exception e) {
				log.error("could not assign array to metrics field", e);
			}
		}

		return metrics;
	}

	public static String getDriverName(Class<?> c) {
		Field field;

		if (c == null) {
			return null;
		}

		String deviceName = null;

		try {
			field = c.getDeclaredField("driverName");
			if (field.isAccessible() == false) {
				field.setAccessible(true);
			}
			deviceName = (String) field.get(c);
		} catch (NoClassDefFoundError e) {
			log.error("Runtime error accessing class: {}", c, e);
		} catch (Exception e) {
			log.warn("no deviceName for class: {}", c);
		}

		if (deviceName == null) {
			deviceName = c.getSimpleName() + ": " + c.getName();
		}

		return deviceName;
	}

	public static RpMetric[] buildMetrics(Class<?> c) {
		LinkedList<RpMetric> ll = new LinkedList<RpMetric>();

		Field[] fields = c.getDeclaredFields();
		for (Field field : fields) {
			RpMetric desc = null;
			CompositeMetric cm = field.getAnnotation(CompositeMetric.class);
			if (field.isSynthetic()) {
				// ignore!
			} else if (cm != null) {
				String code = cm.code();
				if (code == null || code.length() == 0) {
					code = cm.loc();
				}
				CompositeDescription cd = new CompositeDescription(cm.loc(), code, cm.desc());
				desc = cd;
				Class<?> typ = field.getType();
				cd.setSamplesPerPacket(cm.max_count());

				if (typ.isArray()) {
					Class<?> obj_cl = typ.getComponentType();
					if (obj_cl == int.class) {
						cd.setSubtyp(DataTyp.INT_ARR_TYP);
					} else {
						cd.setSubtyp(DataTyp.OBJ_ARR_TYP);
						RpMetric[] obj_metrics = IntfUtil.getMetrics(obj_cl);
						cd.setMetrics(obj_metrics);
					}
					cd.setModel(obj_cl);
				} else {
					cd.setSubtyp(DataTyp.OBJ_TYP);
					RpMetric[] sub_metrics = IntfUtil.getMetrics(typ);
					cd.setMetrics(sub_metrics);
					cd.setSamplesPerPacket(1);
					cd.setModel(typ);
				}
			} else {
				Metric m = field.getAnnotation(Metric.class);
				Waveform w = field.getAnnotation(Waveform.class);
				Text t = field.getAnnotation(Text.class);
				JoinColumn jc = field.getAnnotation(JoinColumn.class);
				if (m != null) {

					double out_m = 1;
					double out_b = 0;
					if (m.m() != 0) {
						out_m = m.m();
						out_b = m.b();
					} else {
						int p = m.precision();
						while (p > 0) {
							out_m /= 10.0;
							p--;
						}
						while (p < 0) {
							out_m *= 10.0;
							p++;
						}
					}

					RpUnit output_unit = buildUnit(m.m(), m.b(), m.precision(), m.unit());
					desc = new RpMetric();
					desc = new RpMetric(m.loc(), m.code(), m.desc(), output_unit, DataTyp.fromType(field.getType()));
				} else if (w != null) {
					RpUnit output_unit = buildUnit(w.m(), w.b(), w.precision(), w.unit());
					desc = new RpMetric(w.loc(), w.code(), w.desc(), output_unit, DataTyp.fromType(field.getType()));
					// , w.freq(), w.spp(), output_unit);
					desc.setSampleRate(w.freq());
					desc.setSamplesPerPacket(w.spp());
				} else if (t != null) {
					desc = new RpMetric(t.loc(), t.code(), t.desc(), null, DataTyp.fromType(field.getType()));
					desc.setSamplesPerPacket(t.length());
				} else if (jc != null) {
					desc = new RpMetric();
					desc.setLocation(field.getName());   // loc is the name specified in the join column
					desc.setCode(jc.name()); // name is the field name
					
					log.error("FIXME: need to dig into class to get the @Table(name=)");
					desc.setName(  field.getDeclaringClass().getSimpleName() );
					desc.setSubtyp(DataTyp.fromType(field.getType()));
				}
			}
			if (desc != null) {
				String code = desc.getCode();
				if (code == null || code.length() == 0) {
					desc.setCode(desc.getLocation());
				}
				String name = desc.getName();
				if (name.length() == 0) {
					desc.setName(null);
				}
				ll.add(desc);
			}
		}

		if (ll.size() == 0) {
			return null;
		}

		RpMetric[] metrics = new RpMetric[ll.size()];
		ll.toArray(metrics);
		return metrics;
	}

	private static RpUnit buildUnit(double m, double b, int precision, String uom) {
		RpUnit u;
		if (m != 0.0) {
			u = new RpLinearUnit(m, b, uom);
		} else {
			u = new RpPrecisionUnit(precision, uom);
		}
		return u;
	}

	public static Method[] getGetters(Class<?> c) {
		LinkedList<Method> ll = new LinkedList<Method>();

		Field[] fields = c.getDeclaredFields();
		for (Field field : fields) {
			try {
				ll.add(_getGetter(c, field));
			} catch (NoSuchMethodException e) {
			} catch (Exception ee) {
				ee.printStackTrace();
			}
		}

		if (ll.size() == 0) {
			return null;
		}

		Method[] metrics = new Method[ll.size()];
		ll.toArray(metrics);
		return metrics;
	}

	private static Method _getGetter(Class<?> c, Field field) throws SecurityException, NoSuchMethodException {
		Method[] methods = c.getMethods();

		String fieldName = field.getName();

		String getterName;

		if (field.getType().getName().equals("boolean")) {
			getterName = "is" + Character.toUpperCase(fieldName.charAt(0)) + fieldName.substring(1);
		} else {
			getterName = "get" + Character.toUpperCase(fieldName.charAt(0)) + fieldName.substring(1);
		}

		Method getter = null;
		try {
			getter = c.getMethod(getterName);
		} catch (NoSuchMethodException nsm) {
			log.error("Could not find method: {}", getterName);
			for (Method m : methods) {
				log.error("Candidate: {}", m.getName());
			}
			throw (nsm);
		}

		return getter;
	}

	private static Method _getSetter(Class<?> c, Field field) throws SecurityException, NoSuchMethodException {
		String fieldName = field.getName();
		String setterName = "set" + Character.toUpperCase(fieldName.charAt(0)) + fieldName.substring(1);
		Method setter = null; // = c.getMethod(setterName, String.class );
		Method[] methods = c.getMethods();
		if (methods != null) {
			for (Method method : methods) {
				if (setterName.equals(method.getName())) {
					setter = method;
					break;
				}
			}
		}

		return setter;
	}

	public static void dump(Object o) {
		dump(System.out, o);
	}

	public static void dump(PrintStream out, Object o) {

		if (o == null) {
			out.println("NULLBLOCK");
			return;
		}

		Class<?> c = o.getClass();

		Field[] fields = c.getDeclaredFields();
		for (Field field : fields) {
			Object value = null;
			String fieldName = field.getName();
			out.print("name=" + fieldName + "  ");
			try {
				value = field.get(o);
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				String getterName = "get" + Character.toUpperCase(fieldName.charAt(0)) + fieldName.substring(1);
				Method getter;
				try {
					getter = c.getMethod(getterName);
					value = getter.invoke(o);
				} catch (NoSuchMethodException e1) {
				} catch (Exception ee) {
					ee.printStackTrace();
				}
			}
			out.print("" + value);
			Metric m = field.getAnnotation(Metric.class);
			if (m != null) {
				RpUnit output_unit = new RpLinearUnit(-1, 0, m.unit());
				RpMetric desc = RpUtil.createRpMetric(m.loc(), m.code(), m.desc(), output_unit, m.subtyp());
				out.print(" code=" + desc.getCode());
				out.print(" name=" + desc.getName());
				RpUnit unit = desc.getUnit();
				out.print(" uom=" + unit.getUnitName());
				if (unit instanceof RpLinearUnit) {
					RpLinearUnit lin = (RpLinearUnit) unit;
					out.print(" m=" + lin.getM());
					out.print(" b=" + lin.getB());
				} else {
					out.print(" typ=" + unit.getClass());
				}
			}
			out.println();
		}

	}

	private static void dump2(PrintStream out, Object block) {
		Class<?> cl = block.getClass();
		Field[] fields = cl.getDeclaredFields();
		for (Field field : fields) {
			if ("caps".equals(field.getName())) {
				continue;
			}
			try {
				Object val = field.get(block);
				out.println("[+] " + field.getName() + " = " + val);
			} catch (IllegalAccessException e) {
				// e.printStackTrace();
				String name = field.getName();
				byte[] b = name.getBytes();
				b[0] = (byte) Character.toUpperCase((char) b[0]);
				String s_getter = "get" + new String(b);
				try {
					Method m = cl.getMethod(s_getter, (Class[]) null);
					Object o = m.invoke(block, new Object[0]);
					out.println("[+] " + field.getName() + " = " + o);
				} catch (NoSuchMethodException e1) {
					out.println("# no getter: " + field.getName());
				} catch (Exception e2) {
					out.println("# exception: " + e2.getMessage());
				}
			}
		}
	}

	private static Field _getFieldByLoc(Object o, String loc) {
		Field field = null;
		Class<?> c = o.getClass();

		Field[] fields = c.getDeclaredFields();
		for (Field f : fields) {
			Object value = null;
			Metric m = f.getAnnotation(Metric.class);
			if (m == null) {
				if (loc.equals(f.getName())) {
					field = f;
					break;
				}
			} else {
				if (loc.equals(m.loc())) {
					field = f;
					break;
				}

			}
		}

		return field;
	}

	@Deprecated
	public static Number getScaledValueByLoc(Object src, String loc) {

		Class<?> c = src.getClass();

		Object o = null;
		try {
			Field field = _getFieldByLoc(src, loc);
			Method getter = _getGetter(c, field);

			o = getter.invoke(src);

			log.error("IntfUtil.getScaledValueByLoc is BROKEN -- use getScaledValue()");
			// if (o != null && md != null) {
			// MeasureUnit unit = md.getUnit();
			// if (unit != null && o instanceof Number) {
			// Object d = unit.getValue((Number) o);
			// if (d != null) {
			// o = d;
			// }
			// }
			// }
			// FIXME: THIS IS AN ERROR
			if (loc.startsWith("SAMPEN")) {
				o = ((Number) o).doubleValue() / 100;
			} else if (loc.startsWith("MSE")) {
				o = ((Number) o).doubleValue() / 100;
			} else if (loc.startsWith("QSE")) {
				o = ((Number) o).doubleValue() / 100;
			} else if (loc.startsWith("MS")) {
				o = ((Number) o).doubleValue() / 100;
			}
		} catch (Exception e) {
			// IGNORE
		}
		return (Number) o;
	}

	public static Object getRawValueByLoc(PersistentItem block, String loc) {

		Object o = null;
		try {
			Method getter = null;
			RpMetric m = block.getMetric(loc);
			if (m != null) {
				getter = m.getter;
			}

			if (getter == null) {
				Field field = _getFieldByLoc(block, loc);
				Class<?> c = block.getClass();
				getter = _getGetter(c, field);
				if (m != null) {
					m.getter = getter;
				}
			}

			o = getter.invoke(block);
		} catch (Exception e) {
			// IGNORE
		}
		return o;
	}

	public static long getTime(Object block) {
		long tm;

		if (block instanceof PersistentItem) {
			PersistentItem pi = (PersistentItem) block;
			tm = pi.getTm().getTime();
		} else if (block instanceof NumericBlock) {
			NumericBlock nb = (NumericBlock) block;
			tm = nb.getTime();
		} else {
			tm = -1;
			log.error("CANNOT GET TIME FROM BLOCK");
		}
		return tm;
	}

	public static Date getTimeAsDate(Object block) {
		Date dt;

		if (block instanceof PersistentItem) {
			PersistentItem pi = (PersistentItem) block;
			dt = pi.getTm();
		} else if (block instanceof NumericBlock) {
			NumericBlock nb = (NumericBlock) block;
			dt = new Date(nb.getTime());
		} else {
			dt = null;
			log.error("CANNOT GET TIME FROM BLOCK");
		}
		return dt;
	}

	// public static void setValue(PersistentItem item, RpMetric metric, String
	// val) {
	// if (metric.getSubtyp() == DataTyp.INT_TYP) {
	// double d = Double.parseDouble(val);
	// metric.setValue(item, (int) d);
	// } else {
	// metric.setValue(item, val);
	// }
	// }

	public static void setScaledValue(PersistentItem block, RpMetric metric, double val) {

		RpUnit unit = metric.getUnit();
		val = unit.inverse(val);
		setValue(block, metric, val);
	}

	public static void setValue(PersistentItem block, String loc, Object val) {
		RpMetric metric = block.getMetric(loc);
		setValue(block, metric, val);
	}

	public static void setValue(PersistentItem block, RpMetric metric, Object val) {
		Method setter = metric.setter;
		if (setter == null) {

			try {
				bindMetricToField(metric, block);
			} catch (Exception e) {
				log.error("FATAL: Could not bind!", e);
			}
			setter = metric.setter;

			log.debug("ASSIGNING setter {}: {} {}", block.getClass(), metric.getLocation(), setter);
		}
		try {
			if (metric.getSubtyp() == DataTyp.INT_TYP) {
				if (val instanceof Short) {
					// dont even warn...just do it
					int ival = (Short) val;
					setter.invoke(block, ival);
				} else if (val instanceof Byte) {
					// dont even warn...just do it
					int ival = (Byte) val;
					setter.invoke(block, ival);
				} else {
					setter.invoke(block, val);
				}
			} else if (metric.getSubtyp() == DataTyp.BYTE_TYP) {
				if (val instanceof Integer) {
					// dont even warn...just do it
					byte btval = (byte) ((int) (Integer) val);
					setter.invoke(block, btval);
				} else {
					setter.invoke(block, val);
				}
			} else if (metric.getSubtyp() == DataTyp.FLOAT_TYP) {
				if (val instanceof Integer) {
					log.warn("setting float from int");
					float fval = (Integer) val;
					setter.invoke(block, fval);
				} else if (val instanceof Double) {
					double fval = (Double) val;
					setter.invoke(block, (float) fval);
				} else {
					setter.invoke(block, val);
				}
			} else if (metric.getSubtyp() == DataTyp.DOUBLE_TYP) {
				if (val instanceof Integer) {
					log.warn("setting double from int");
					double fval = (Integer) val;
					setter.invoke(block, fval);
				} else if (val instanceof Float) {
					double fval = (Float) val;
					setter.invoke(block, fval);
				} else {
					setter.invoke(block, val);
				}
			} else if (setter == null) {
				bindMetricToField(metric, block); // repeated for debug purposes
				log.error("Setter not available: {}", metric);
			} else {
				// covers multiple types: DataTyp.INT_ARR_TYP, etc
				setter.invoke(block, val);
			}
		} catch (IllegalArgumentException e) {
			String className = (val == null) ? "[null]" : val.getClass().toString();
			log.error("illegal for setter, class: {} value={} setter={}", //
					className, //
					val, //
					setter.getName(), //
					e);
			if (val != null) {
				String message = "block typ {}, setter declaring={} expecting args: ";
				String sep = "";
				for (Class<?> t : setter.getParameterTypes()) {
					message += sep;
					message += t.getTypeName();
					sep = ", ";
				}
				log.error(message, block.getClass(), setter.getDeclaringClass());
			}
		} catch (Exception e) {
			log.error("setValue", e);
		}

	}

	@Deprecated
	public static void setValue(PersistentItem block, RpMetric metric, Triplet triplet) {
		Object parent = block;
		log.error("FIXME: Are triplets supported as such?");
		// metric.setValue(parent, triplet);
	}

	public static Object getScaledValue(PersistentItem parent, RpMetric metric) {
		Object val = null;

		try {
			val = getRawValue(parent, metric);
			if (val != null && val instanceof Number) {
				RpUnit u = metric.getUnit();
				val = u.transform_d(((Number) val).doubleValue());
			}
		} catch (Exception e) {
			log.error("getScaledValue", e);
		}

		return val;
	}

	public static Object getRawValue(PersistentItem parent, RpMetric metric) {
		if (metric == null) {
			return null;
		}
		Method getter = metric.getter;
		Object val = null;
		if (getter == null) {

			try {
				bindMetricToField(metric, parent);
				getter = metric.getter;
				if (getter == null) {
					log.error("FATAL: Could not assign getter...calling again to trace!");
					bindMetricToField(metric, parent);
				}
			} catch (Exception e) {
				log.error("FATAL: Could not bind!", e);
				return null;
			}

			// log.debug("ASSIGNING getter {}: {} {}", parent.getClass(),
			// metric.getLocation(), getter);
		}

		try {
			val = getter.invoke(parent);
		} catch (ClassCastException e) {
			log.error("FATAL: -- raw get problem??", e);
			System.err.println("FIXME: ClassCastEx exit for debugging purposes: " + getter + " parent: " + parent);
		} catch (IllegalArgumentException e) {
			log.error("FATAL: not a getter on this data type", e);
			System.err.println("FIXME: IllegalArgEx exit for debugging purposes: " + getter + " parent: " + parent);
		} catch (Exception e) {
			log.error("FATAL: could not save.", e);
		}

		return val;
	}

	public static void clear(PersistentItem pi) {
		RpMetric[] metrics = getMetrics(pi);
		if (metrics == null) {
			log.error("unexpected null metrics in IntfUtil.clear()");
			return;
		}
		for (RpMetric metric : metrics) {
			IntfUtil.setValue(pi, metric, (Object) null);
		}

	}

	public static RpMetric getMetricByLoc(final RpStream stream, final String loc) {
		if (stream == null) {
			return null;
		}
		for (RpMetric desc : (List<? extends RpMetric>) stream.getMetric()) {
			if (loc.equals(desc.getLocation())) {
				return desc;
			}
		}
		return null;
	}

	public static RpMetric getMetricByCode(final RpStream stream, final String code) {
		if (stream == null) {
			return null;
		}
		for (RpMetric desc : (List<? extends RpMetric>) stream.getMetric()) {
			if (code.equals(desc.getCode())) {
				return desc;
			}
		}
		return null;
	}

	public static RpMetric getMetricByLoc(PersistentItem item, String loc) {
		RpMetric[] metrics = getMetrics(item);
		if (metrics == null) {
			log.error("null metrics for: {}", item.getClass());
			return null;
		}
		for (RpMetric desc : metrics) {
			if (loc.equals(desc.getLocation())) {
				return desc;
			}
		}
		return null;
	}

	public static RpStream getStream(RpDevice dev, StreamID sid) {
		String name = sid.getName();
		for (RpStream stream : (List<? extends RpStream>) dev.getStreams()) {
			if (name.equals(stream.getName())) {
				return stream;
			}
		}
		return null;
	}

	public static void setParam(RpDevice dc, String key, String value) {
		StringStringMap params = dc.getParam();
		if (params == null) {
			params = new StringStringMap();
			dc.setParam(params);
		}
		params.put(key, value);

	}

	public static RpMetric[] getMetrics(PiDatastreamImporter dev, StreamID sid) {
		Class<? extends PersistentItem> clazz = dev.getModel(sid);
		return IntfUtil.getMetrics(clazz);
	}

	public static RpDevice getSubDevice(RpDevice conf, String deviceId) {
		for (RpDevice dev : (List<? extends RpDevice>) conf.getDevices()) {
			if (deviceId.equals(dev.getName())) {
				return dev;
			}
		}
		return null;
	}

	public static void setScaledValue(PersistentItem block, String loc, double val) {
		RpMetric metric = block.getMetric(loc);
		IntfUtil.setScaledValue(block, metric, val);
	}

	public static DeviceCapabilities getStaticCapabilities(Class<? extends StreamProducer> c) {
		Field field;

		if (c == null) {
			return null;
		}

		DeviceCapabilities caps = null;

		try {
			field = c.getDeclaredField("caps");
			if (field.isAccessible() == false) {
				field.setAccessible(true);
			}
			caps = (DeviceCapabilities) field.get(c);
		} catch (Exception e) {
			log.error("no caps field for class: {}", c, e);
		}

		return caps;
	}

}
