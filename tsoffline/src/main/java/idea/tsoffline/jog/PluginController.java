package idea.tsoffline.jog;

import java.io.IOException;
import java.util.List;

import lombok.extern.slf4j.Slf4j;
import purejavahidapi.HidDevice;
import purejavahidapi.HidDeviceInfo;
import purejavahidapi.InputReportListener;
import purejavahidapi.PureJavaHidApi;
import idea.tsoffline.AppModel;
import idea.tsoffline.TsPluginAPI;
import idea.tsoffline.canvas.TsPSwingCanvas;

@Slf4j
public class PluginController implements TsPluginAPI {
	private AppModel app;

	public void initPlugin(AppModel app) throws IOException {
		this.app = app;
		HidDevice shuttle;
		List<HidDeviceInfo> devs = PureJavaHidApi.enumerateDevices();
		
		if( devs == null ) {
			log.error("jog plugin: could not find jog device list");
			return;
		}
		for( HidDeviceInfo info : devs ) {
			System.out.println("HID=" + info.getManufacturerString() + "," + info.getPath());
		}
		if( devs.size() == 0 ) {
			log.error("jog plugin: no available jog devices");
			return;
		}
		shuttle = PureJavaHidApi.openDevice( devs.get(0) );
		shuttle.setInputReportListener( new InputReportListener() {

			private byte prev_b0;
			private byte prev_b1;

			@Override
			public void onInputReport(HidDevice source, byte reportID, byte[] reportData, int reportLength) {
				byte b0 = reportData[0];  // outer ring
				byte b1 = reportData[1];  // circular jog
				byte b3 = reportData[3];  // circular jog
				byte b4 = reportData[4];  // circular jog
				
				boolean button_1 = (b3 & 0x10) != 0;
				boolean button_2 = (b3 & 0x20) != 0;
				boolean button_3 = (b3 & 0x40) != 0;
				boolean button_4 = (b3 & 0x80) != 0;
				boolean button_5 = (b4 & 0x01) != 0;
				
				int dir = (b1 - prev_b1);  // have not checked the boundary cases! 
				for( byte b : reportData ) {
					System.out.printf( "%02X ", b, dir);
				}
				System.out.println();
				
				TsPSwingCanvas canvas = app.getActiveCanvas();
				if( b0 == 0 ) {
					if( dir != 0 ) {
						canvas.moveLeftRight(dir);
					}
				} else {
					dir = (b0 > 0 ) ? 1 : -1; 
					canvas.moveLeftRight( dir );
				}
				
				prev_b0 = b0;
				prev_b1 = b1;
				
			} } );

	}

}
