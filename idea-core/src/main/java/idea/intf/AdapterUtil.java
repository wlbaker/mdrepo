package idea.intf;

import icuInterface.RpUtil;
import idea.conf.CompositeDescription;
import idea.conf.DeviceCapabilities;
import idea.message.StreamID;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;

import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class AdapterUtil {

	private static int model_idx = 1;
	
	public static void fix_config(RpDevice cap, RpDevice conf) {

		if (conf == null) {
			return;
		}
		if (cap == null) {
			return;
		}

		List<RpStream> confStreams = conf.getStreams();
		if( confStreams == null || confStreams.size() == 0 ) {
			log.warn("UNSPECIFIED STREAM CONFIG: forcing add streams");
			for( RpStream s : (List<? extends RpStream>)cap.getStreams() ) {
				confStreams.add(s);
			}
		}
		
		for (RpStream stream : (List<? extends RpStream>)conf.getStreams()) {

			RpStream ref_stream = RpUtil.getStreamFromName( cap.getStreams(), stream.getName() );
			if (ref_stream == null) {
				log.error("UNKNOWN REQUESTED STREAM: {}", stream );
				continue;
			}
			
			// override the model name provided in the study file
			stream.setModel( ref_stream.getModel() );
			
			List<RpMetric> metrics = stream.getMetric();
			Iterator<RpMetric> it = metrics.iterator();
			while( it.hasNext() ) {
				RpMetric metric = it.next();
				RpMetric ref = RpUtil.getMetricFromStream(ref_stream, metric.getLocation());

				if (ref == null) {
					log.error("UNKNOWN REQUESTED METRIC: {}", metric.getLocation());
					continue;
				}
				if (ref instanceof CompositeDescription) {
					// metrics[i] = ref;
					metric = ref;
				}
				metric.setUnit(ref.getUnit());
				if( ref.getSampleRate() != null ) {
					if (metric.getSampleRate() != ref.getSampleRate()) {
						log.error("CONFIG FIX: {} sampleRate {} <- {}", ref, metric.getSampleRate(), ref.getSampleRate());
						metric.setSampleRate(ref.getSampleRate());
					}
				}
				if( ref.getSamplesPerPacket() != null ) {
					if (metric.getSamplesPerPacket() != ref.getSamplesPerPacket()) {
						metric.setSamplesPerPacket(ref.getSamplesPerPacket());
					}
				}
				
				metric.setUnit(ref.getUnit());
				
				if( ref.setter != null ) {
					metric.setter = ref.setter;
					metric.getter = ref.getter;
				}
			}
		}
	}

	public static Class<? extends PersistentItem> buildMetricsClass(String modelName, List<? extends RpMetric> m) {
		Class<? extends PersistentItem> modelClass = ModelUtil.findCachedModel( m );

		if (modelClass == null) {
			
			modelName = "idea.model.auto.Auto" + modelName + model_idx;
			model_idx ++;

			try {
				modelClass = ModelUtil.createDynamicModel(modelName, m );
			} catch (Exception e) {
				log.error( "could not creating dynamic model", e );
			}
		}
		
		return modelClass;
	}
	public static void getStaticCapabilities(DeviceCapabilities cap, String[] ports, String pfx) {
		//cap = new DeviceCapabilities(NIDAQmxDriver.class);
		//String[] ports = DaqSystem.getMxLocal().getPhysicalChannels();
		RpLinearUnit mV = new RpLinearUnit(1.0, 0, "mV");
		
		RpMetric [] arr = new RpMetric[ ports.length ];
		int idx = 0;
		for (String port : ports) {
			RpMetric m = new RpMetric(port, pfx + idx, port, mV, DataTyp.FLOAT_ARR_TYP );
			//m.setSampleRate( 200 );
			//m.setSamplesPerPacket(100);
			arr[idx++] = m;
		}
		Class<? extends PersistentItem> cl = AdapterUtil.buildMetricsClass( cap.getName(), Arrays.asList(arr));
		cap.addStream(StreamID.WAVEFORM, cl);

	}

}
