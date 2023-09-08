package idea.model;

import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPrecisionUnit;
import idea.schema.rp.RpUnit;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import javassist.CannotCompileException;
import javassist.ClassClassPath;
import javassist.ClassPool;
import javassist.CtClass;
import javassist.CtField;
import javassist.CtMethod;
import javassist.CtNewMethod;
import javassist.Modifier;
import javassist.NotFoundException;
import javassist.bytecode.AnnotationsAttribute;
import javassist.bytecode.ClassFile;
import javassist.bytecode.ConstPool;
import javassist.bytecode.annotation.Annotation;
import javassist.bytecode.annotation.DoubleMemberValue;
import javassist.bytecode.annotation.IntegerMemberValue;
import javassist.bytecode.annotation.MemberValue;
import javassist.bytecode.annotation.StringMemberValue;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class ModelUtil {
	private static Map<String, Class<?>> measurement_map;
	private static Map<String, Class<?>> sensor_map;

	private static List<Class<? extends PersistentItem>> cache = new LinkedList<Class<? extends PersistentItem>>();
	static {
		measurement_map = new HashMap<String, Class<?>>();

		// added Java-9 the help the class loader find the PersistentItem class
		ClassPool cp = ClassPool.getDefault();
		cp.insertClassPath(new ClassClassPath(PersistentItem.class));
	}

	public static Class<? extends PersistentItem> createDynamicModel( //
			final String className, // fully qualified class name
			Collection<? extends RpMetric> properties) throws Exception {

		ClassPool pool = ClassPool.getDefault();
		CtClass cc = pool.makeClass(className);

		ClassFile cf = cc.getClassFile();
		ConstPool cp = cf.getConstPool();

		// set the superclass
		String pi_name = PersistentItem.class.getCanonicalName();
		cc.setSuperclass(pool.get(pi_name));

		// create the static field for cached metrics
		String md_array = RpMetric[].class.getCanonicalName();
		CtClass java_typ = pool.get(md_array);
		CtField f = new CtField(java_typ, "metrics", cc);
		// f.setModifiers(Modifier.PROTECTED | Modifier.STATIC);
		f.setModifiers(Modifier.PUBLIC | Modifier.STATIC);
		cc.addField(f);
		CtMethod abstract_getter = CtNewMethod.getter("getMetrics", f);
		abstract_getter.setModifiers(Modifier.PUBLIC);
		cc.addMethod(abstract_getter);

		// create the entity annotation
		AnnotationsAttribute attr = new AnnotationsAttribute(cp, AnnotationsAttribute.visibleTag);
		Annotation entity = new Annotation("javax.persistence.Entity", cp);
		attr.addAnnotation(entity);

		// Annotation table = new Annotation("javax.persistence.Table", cp);
		// table.addMemberValue("name", new
		// StringMemberValue("PUT_SHORT_NAME_HERE", cp) );
		// attr.addAnnotation(table);

		cf.addAttribute(attr);

		for (RpMetric p : properties) {
			java_typ = null;
			String anno_typ = null;
			Integer subt = p.getSubtyp();
			if (subt == null) {
				log.error("MISSING SUBTYP: " + p);
				continue;
			}
			switch (subt) {
			case DataTyp.BOOLEAN_TYP:
				java_typ = pool.get("java.lang.Boolean");
				anno_typ = "idea.persistence.Metric";
				break;
			case DataTyp.BYTE_TYP:
				java_typ = pool.get("java.lang.Byte");
				anno_typ = "idea.persistence.Metric";
				break;
			case DataTyp.INT_TYP:
				java_typ = pool.get("java.lang.Integer");
				anno_typ = "idea.persistence.Metric";
				break;
			case DataTyp.LONG_TYP:
				java_typ = pool.get("java.lang.Long");
				anno_typ = "idea.persistence.Metric";
				break;
			case DataTyp.FLOAT_TYP:
				java_typ = pool.get("java.lang.Float");
				anno_typ = "idea.persistence.Metric";
				break;
			case DataTyp.DOUBLE_TYP:
				java_typ = pool.get("java.lang.Double");
				anno_typ = "idea.persistence.Metric";
				break;
			case DataTyp.INT_ARR_TYP:
				java_typ = pool.get("int[]");
				anno_typ = "idea.persistence.Waveform";
				break;
			case DataTyp.FLOAT_ARR_TYP:
				java_typ = pool.get("float[]");
				anno_typ = "idea.persistence.Waveform";
				break;
			case DataTyp.DOUBLE_ARR_TYP:
				java_typ = pool.get("double[]");
				anno_typ = "idea.persistence.Waveform";
				break;
			case DataTyp.STRING_TYP:
				java_typ = pool.get("java.lang.String");
				anno_typ = "idea.persistence.Text";
				break;
			default:
				log.error("TYPE NOT IMPLEMENTED: {}", subt);
			}

			// typ = CtClass.intType;
			String rev_fieldName = null;
			{
				String fieldName = p.getCode();
				if (fieldName == null) {
					fieldName = p.getLocation();
				}
				fieldName = normalizeFieldName(fieldName);

				rev_fieldName = fieldName;
				for (int i = 0; i < 10; i++) {
					f = new CtField(java_typ, rev_fieldName, cc);
					f.setModifiers(Modifier.PRIVATE);
					try {
						cc.addField(f);
						break; // success
					} catch (Exception e) {
						log.error("COULD NOT ADD FIELD typ={}: {}", java_typ, e.getMessage());
					}
					// try again
					rev_fieldName = fieldName + i;
					// 070617 WARNING: alters caller data, but duplicate LOCs are bad JUJU
					p.setLocation(rev_fieldName);
					// 070617: if getter/setter point to anything...it's the wrong thing!
					p.getter = null;
					p.setter = null;
				}
			}

			String propertyName = getPropertyName(rev_fieldName);
			String getterName = "get" + propertyName; // NOT RIGHT
			String setterName = "set" + propertyName; // NOT RIGHT

			CtMethod getter = CtNewMethod.getter(getterName, f);
			getter.setModifiers(Modifier.PUBLIC);
			cc.addMethod(getter);

			CtMethod setter = CtNewMethod.setter(setterName, f);
			setter.setModifiers(Modifier.PUBLIC);
			cc.addMethod(setter);

			// add the Metric attribute
			attr = new AnnotationsAttribute(cp, AnnotationsAttribute.visibleTag);
			Annotation m = new Annotation(anno_typ, cp);
			// 24JULY17: wlb
			m.addMemberValue("loc", new StringMemberValue(p.getLocation(), cp));
			String code = p.getCode();
			if (code != null) {
				m.addMemberValue("code", new StringMemberValue(code, cp));
			}
			if (p.getName() != null) {
				m.addMemberValue("desc", new StringMemberValue(p.getName(), cp));
			}
			if (subt == DataTyp.INT_ARR_TYP || subt == DataTyp.FLOAT_ARR_TYP || subt == DataTyp.DOUBLE_ARR_TYP) {
				Integer spp = p.getSamplesPerPacket();
				Integer freq = p.getSampleRate();
				if (spp == null)
					spp = 0; // required by Wave annotation, but maybe shouldnt
								// be
				if (freq == null)
					freq = 0;
				m.addMemberValue("spp", new IntegerMemberValue(cp, spp));
				m.addMemberValue("freq", new IntegerMemberValue(cp, freq));
				attr.addAnnotation(m);
			} else if (subt == DataTyp.STRING_TYP) {
				m.addMemberValue("length", new IntegerMemberValue(cp, p.getSamplesPerPacket()));
			}
			RpUnit unit = p.getUnit();
			if (unit != null) {
				m.addMemberValue("unit", new StringMemberValue(unit.getUnitName(), cp));
				if (unit instanceof RpLinearUnit) {
					// ...CANT ADD "m" to Metric. Hmm!
					// m.addMemberValue("m", new
					// StringMemberValue(unit.getUnitName(), cp));
					RpLinearUnit lu = (RpLinearUnit) unit;
					// m.addMemberValue("m", new StringMemberValue(lu.getM(),
					// cp));
					// m.addMemberValue("b", new
					// StringMemberValue(unit.getUnitName(), cp));
					double mm = lu.getM();
					double bb = lu.getB();
					if (mm == 0.1 && bb == 0) {
						m.addMemberValue("precision", new IntegerMemberValue(cp, 1));
					} else if (mm == 0.01 && bb == 0) {
						m.addMemberValue("precision", new IntegerMemberValue(cp, 2));
					} else if (mm == 0.001 && bb == 0) {
						m.addMemberValue("precision", new IntegerMemberValue(cp, 3));
					} else {
						m.addMemberValue("m", new DoubleMemberValue(mm, cp));
						m.addMemberValue("b", new DoubleMemberValue(bb, cp));
					}
				} else if (unit instanceof RpPrecisionUnit) {
					RpPrecisionUnit pu = (RpPrecisionUnit) unit;
					// 050917 WLB: Changed from StringMemberValue due to export
					// problem
					m.addMemberValue("precision", new IntegerMemberValue(cp, pu.getPrecision()));
				}
			}
			attr.addAnnotation(m);

			f.getFieldInfo().addAttribute(attr);

			// CtClass clazz = ....;
			// ClassFile classFile = clazz.getClassFile();
			// ConstPool cp = classFile.getConstPool();
			//
			// annotation.addMemberValue("catalog", new
			// StringMemberValue("idea",cp));
			//
			// attr.setAnnotation(theAnnotation);
			// f.setAttribute(name, data)

		}

		Class<? extends PersistentItem> cl = (Class<? extends PersistentItem>) cc.toClass();
		RpMetric[] metrics = IntfUtil.getMetrics(cl);
		Field mf = cl.getDeclaredField("metrics");
		mf.set(cl, metrics);

		cache.add(cl);
		return cl;
	}

	private static String getPropertyName(String fieldName) {
		String propertyName = fieldName.substring(0, 1).toUpperCase();
		propertyName += fieldName.substring(1);
		return propertyName;
	}

	public static void _addModelForDataset(String groupName, StreamID streamId, Class<?> cl) {

		if (streamId == StreamID.MEASUREMENT) {
			measurement_map.put(groupName, cl); // PhilipsMP5.class);
		} else {
			System.err.println("Ignoring add model for dataset: " + groupName + " " + streamId);
		}
	}

	public static Class<? extends PersistentItem> wrap(String className)
			throws CannotCompileException, NotFoundException, NoSuchFieldException, SecurityException,
			IllegalArgumentException, IllegalAccessException {
		ClassPool pool = ClassPool.getDefault();
		CtClass cc = pool.get(className);

		ClassFile cf = cc.getClassFile();
		ConstPool cp = cf.getConstPool();

		// set the superclass
		String pi_name = PersistentItem.class.getCanonicalName();
		// DOIT cc.setSuperclass(pool.get(pi_name));

		// create the static field for cached metrics
		{
			String md_array = RpMetric[].class.getCanonicalName();
			CtClass java_typ = pool.get(md_array);
			CtField f = new CtField(java_typ, "metrics", cc);
			// f.setModifiers(Modifier.PROTECTED | Modifier.STATIC);
			f.setModifiers(Modifier.PUBLIC | Modifier.STATIC);
			cc.addField(f);
			CtMethod abstract_getter = CtNewMethod.getter("getMetrics", f);
			abstract_getter.setModifiers(Modifier.PUBLIC);
			cc.addMethod(abstract_getter);
		}

		// create the entity annotation
		AnnotationsAttribute attr = new AnnotationsAttribute(cp, AnnotationsAttribute.visibleTag);
		Annotation entity = new Annotation("javax.persistence.Entity", cp);
		attr.addAnnotation(entity);
		cf.addAttribute(attr);

		for (CtField f : cc.getDeclaredFields()) {
			System.out.println("FIELD: " + f);
			String anno_typ = null;
			String loc = f.getName();
			String code = loc;
			System.out.println("  typ=" + f.getType());
			// case DataTyp.BYTE_TYP:
			// java_typ = pool.get("java.lang.Byte");
			// anno_typ = "idea.persistence.Metric";
			// break;
			// case DataTyp.INT_TYP:
			// java_typ = pool.get("java.lang.Integer");
			// anno_typ = "idea.persistence.Metric";
			// break;
			// default:
			// log.error("TYPE NOT IMPLEMENTED: {}", subt);

			String rev_fieldName = f.getName();

			String propertyName = getPropertyName(rev_fieldName);
			String getterName = "get" + propertyName; // NOT RIGHT
			String setterName = "set" + propertyName; // NOT RIGHT

			// try {
			// CtMethod getter = CtNewMethod.getter(getterName, f);
			// getter.setModifiers(Modifier.PUBLIC);
			// cc.addMethod(getter);
			// } catch (Exception e) {
			// log.error("Could not add getter: " + getterName);
			// }
			//
			// try {
			// CtMethod setter = CtNewMethod.setter(setterName, f);
			// setter.setModifiers(Modifier.PUBLIC);
			// cc.addMethod(setter);
			// } catch (Exception e) {
			// log.error("Could not add setter: " + setterName);
			// }

			// add the Metric attribute
			if (anno_typ == null) {
				// ignore
			} else {
				attr = new AnnotationsAttribute(cp, AnnotationsAttribute.visibleTag);
				Annotation m = new Annotation(anno_typ, cp);
				m.addMemberValue("loc", new StringMemberValue(loc, cp));
				if (code != null) {
					m.addMemberValue("code", new StringMemberValue(code, cp));
				}
				attr.addAnnotation(m);
				f.getFieldInfo().addAttribute(attr);
			}
			// if (p.getName() != null) {
			// m.addMemberValue("desc", new StringMemberValue(p.getName(), cp));
			// }
			// if (subt == DataTyp.INT_ARR_TYP || subt == DataTyp.FLOAT_ARR_TYP)
			// {
			// m.addMemberValue("spp", new IntegerMemberValue(cp, spp));
			// m.addMemberValue("freq", new IntegerMemberValue(cp, freq));
			// attr.addAnnotation(m);
			// } else if (subt == DataTyp.STRING_TYP) {
			// TextDescription td = (TextDescription) p;
			// m.addMemberValue("length", new IntegerMemberValue(cp,
			// td.getLen()));
			// }
			// RpUnit unit = p.getUnit();
			// if (unit != null) {
			// m.addMemberValue("unit", new
			// StringMemberValue(unit.getUnitName(), cp));
			// if (unit instanceof RpLinearUnit) {
			// // ...CANT ADD "m" to Metric. Hmm!
			// // m.addMemberValue("m", new
			// StringMemberValue(unit.getUnitName(), cp));
			// RpLinearUnit lu = (RpLinearUnit) unit;
			// // m.addMemberValue("m", new StringMemberValue(lu.getM(), cp));
			// // m.addMemberValue("b", new
			// StringMemberValue(unit.getUnitName(), cp));
			// if (lu.getM() == 0.1) {
			// m.addMemberValue("precision", new IntegerMemberValue(cp, 1));
			// } else if (lu.getM() == 0.01) {
			// m.addMemberValue("precision", new IntegerMemberValue(cp, 2));
			// } else if (lu.getM() == 0.001) {
			// m.addMemberValue("precision", new IntegerMemberValue(cp, 3));
			// } else {
			// m.addMemberValue("m", new DoubleMemberValue(lu.getM(), cp));
			// m.addMemberValue("b", new DoubleMemberValue(lu.getB(), cp));
			// }
			// } else if (unit instanceof RpPrecisionUnit) {
			// RpPrecisionUnit pu = (RpPrecisionUnit) unit;
			// m.addMemberValue("precision", new
			// StringMemberValue(pu.getPrecision(), cp));
			// }
			// }

		}

		Class<? extends PersistentItem> cl = (Class<? extends PersistentItem>) cc.toClass();
		RpMetric[] metrics = IntfUtil.getMetrics(cl);
		Field mf = cl.getDeclaredField("metrics");
		mf.set(cl, metrics);

		cache.add(cl);
		return cl;
	}

	public static Class<?> _getModelForDataset(String groupClass, String datasetName) {
		Class<?> persistClass = null;

		if (groupClass != null) {
			groupClass = normalizeGroupClassName(groupClass);
		}

		if ("annotations".equalsIgnoreCase(datasetName)) {
			persistClass = idea.model.Annotation.class;
		} else if ("alarms".equalsIgnoreCase(datasetName)) {
			persistClass = Alarm.class;
		} else if ("tranlog".equalsIgnoreCase(datasetName)) { // special case
			persistClass = measurement_map.get(datasetName);
		} else if ("numerics".equalsIgnoreCase(datasetName)) {
			persistClass = measurement_map.get(groupClass);
		} else if ("waveform".equalsIgnoreCase(datasetName)) {
			persistClass = sensor_map.get(groupClass);
		} else {
			persistClass = null;
		}

		if (persistClass == null) {
			log.error("NO PERSISTENT CLASS FOR {} / {}", groupClass, datasetName);
		}

		return persistClass;
	}

	public static PersistentItem getModelFromDataClass(Class<?> persistClass) {
		PersistentItem item = null;
		if (persistClass == null) {
			log.error("No class for persistent item");
		} else {
			Constructor<?> m;
			try {
				m = persistClass.getConstructor();
				Object o = m.newInstance();

				item = (PersistentItem) o;
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return item;
	}

	public static StreamID _getStreamIDForDataset(String groupClass, String datasetName) {
		StreamID sid = null;

		if ("annotations".equalsIgnoreCase(datasetName)) {
			sid = StreamID.ANNOTATION;
		} else if ("alarms".equalsIgnoreCase(datasetName)) {
			sid = StreamID.ALARM;
		} else if ("tranlog".equalsIgnoreCase(datasetName)) { // special case
			sid = null;
		} else if ("numerics".equalsIgnoreCase(datasetName)) {
			sid = StreamID.MEASUREMENT;
		} else if ("waveform".equalsIgnoreCase(datasetName)) {
			sid = StreamID.WAVEFORM;
		} else {
			sid = null;
		}

		if (sid == null) {
			log.error("NO StreamID FOR {} / {}", groupClass, datasetName);
		}

		return sid;
	}

	public static Class<? extends PersistentItem> findCachedModel(Collection<? extends RpMetric> req) {

		//
		// Package can-t see dynamically created packages
		//
		// Package pkg = Package.getPackage(pkg_name);
		// ArrayList<Class<?>> cache = PlatformUtil.getClassesForPackage(pkg);

		Class<? extends PersistentItem> found = null;

		outer: for (Class<? extends PersistentItem> cl : cache) {
			RpMetric[] provide = IntfUtil.getMetrics(cl);

			if (req.size() != provide.length) {
				// System.out.println("skip: " + cl + " sz=" + provide.length +
				// " 0=" + provide[0].getLocation() );
				continue;
			}

			int idx = 0;
			for (RpMetric m : req) {
				// System.out.println(" check: " + provide[idx].getLocation() );
				if (!m.getLocation().equals(provide[idx].getLocation())) {
					// System.out.println("faile!" );
					continue outer; // match not found yet, try the next class
				}
				idx++;
			}

			found = cl; // full match candidate
			break; // all the fields matched! this one is a keeper
		}

		// System.out.println("found match: " + found );
		return found;
	}

	/*
	 * routines to normalize names to be used for classes and fields.
	 */
	private static String normalizeGroupClassName(String groupClass) {
		groupClass = groupClass.replace("_0", "");
		groupClass = groupClass.replace("+", " ");
		int idx = groupClass.indexOf("_");
		if (idx > 0) {
			groupClass = groupClass.substring(0, idx);
		}
		idx = groupClass.indexOf(" ");
		if (idx > 0) {
			groupClass = groupClass.substring(0, idx);
		}
		return groupClass;
	}

	public static String normalizeFieldName(String fieldName) {
		fieldName.toLowerCase();
		fieldName = fieldName.replace('.', '$');
		fieldName = fieldName.replace('/', '$');
		return fieldName;
	}

}
