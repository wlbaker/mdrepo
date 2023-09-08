package idea.tsoffline;

import lombok.extern.slf4j.Slf4j;
import idea.tsoffline.model.OfflineDevice;

@Slf4j
public class Patcher {

	public static void patchHdf5Devices(int version, OfflineDevice[] devs) {
//		if( devs == null ) {
//			log.warn("no devices to patch");
//			return;
//		}
//		for( OfflineDevice dev : devs ) {
//			String cl = dev.getDeviceClass();
//			if( cl == null && dev.getName().startsWith("Drager" )) {
//				dev.setDeviceClass("idea.driver.infinity");
//			}
//			
//			if( cl == null ) {
//				continue;
//			}
//			
//			if( cl.equals( "idea.driver.infinity" )) {
//				OfflineStream str = dev.getStream(StreamID.WAVEFORM);
//				if( str == null ) {
//					continue;
//				}
//				for( OfflineSignal m : str.getCachedSignals() ) {
//					String unit_name = m.getUnitName();
//					if( "mmHg".equals(unit_name)) {
//						m.setUnit( new RpLinearUnit(0.1666, 0, "mmHg") );
//					}
//				}
//			}
//		}
		
	}

}
