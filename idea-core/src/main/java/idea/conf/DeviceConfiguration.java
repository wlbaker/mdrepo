package idea.conf;

//note: might wrap up all the device configurations with a single "setConnectionValue()"

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.StringStringMap;

import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Set;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DeviceConfiguration extends RpDevice {

	/**
	 * 
	 */

	private boolean proxy = false;

	private String cached_configName;

	public DeviceConfiguration(String deviceClass) {
		setDeviceClass(deviceClass);
	}

	public DeviceConfiguration(Class<?> cl) {
		if (cl != null) {
			setDeviceClass(cl.getCanonicalName());
			setName(cl.getCanonicalName());
		}
	}

	public DeviceConfiguration(RpDevice conf) {
		if (conf != null) {
			this.setName(conf.getName());
			this.setRevNo(conf.getRevNo());
			this.setDeviceClass(conf.getDeviceClass());
			this.setModelName(conf.getModelName());
			this.setDriverName(conf.getDriverName());

			log.error("FIXME: RpDevice fields not copied!");
			// BETA2 FIXME: copy device config: params?
		}
	}

	public void putParam(String key, String value) {
		if( param == null ) {
			param = new StringStringMap();
		}
		param.put(key, value);
	}

	public String getParam(String key) {
		if( param == null ) {
			return null;
		}
		return param.get(key);
	}

	public Set<String> getKeys() {
		if( param == null ) {
			return null;
		}
		return param.keySet();
	}

	public void setProxy(boolean proxy) {
		this.proxy = proxy;
	}

	public boolean isProxy() {
		return proxy;
	}

	public void addDevice(DeviceConfiguration conf) {
		getDevices().add(conf);
	}

	public void reset() {
		log.error("FIXME: RESET");
	}

	public RpDevice getSubDevice(String name) {
		if (devices == null || devices.size() == 0) {
			return null;
		}

		RpDevice conf = null;
		synchronized (devices) {
			for (Object device : devices) {  // why doesn't it see generics of list?
				RpDevice dev = (RpDevice) device;  // cast should not be necessary!
				if (name.equals(dev.getName())) {
					conf = dev;
					break;
				}
			}
		}

		return conf;
	}

	public void replace_desc(StreamID sid, RpMetric desc, CompositeDescription cd) {
		RpStream stream = getStream(sid);

		Iterator<RpMetric> it = stream.getMetric().iterator();
		while (it.hasNext()) {
			RpMetric ref = it.next();
			if (ref.getLocation().equals(desc.getLocation())) {
				it.remove();
				break;
			}
		}
		stream.getMetric().add(desc);

	}

	public RpStream getStream(StreamID sid) {
		return IntfUtil.getStream(this, sid);
	}

	public void addStream(RpStream s) {
		this.getStreams().add(s);
	}

	public void addStream(StreamID sid, Class<? extends PersistentItem> cl) {

		RpStream s = new RpStream();
		s.setName(sid.getName());
		s.setPIClass( cl );
		if( cl != null ) {
			/*
			 * The model is just the text version of the class name, needed for serialization for
			 * file storage and network transfer.
			 */
			s.setModel(cl.getName());
		}
		RpMetric[] metrics = IntfUtil.getMetrics(cl);
		if( metrics == null ) {
			log.error("No metrics for class: {}", cl);
		} else {
			s.getMetric().addAll(Arrays.asList(metrics));
		}
		// TEMPORARY adapter routine...

		addStream(s);
	}

}
