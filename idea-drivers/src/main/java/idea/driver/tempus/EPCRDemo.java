package idea.driver.tempus;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;

import com.google.gson.Gson;

import TempusListener.FileConfig;
import TempusListener.IMessageReceiver;
import TempusListener.TempusConnection;
import TempusListener.TempusListenerStatus;
import idea.driver.TempusDriver;
//-----------------------------------------------------------------------
//<copyright file="EPCRDemo.java" company="Remote Diagnostic Technologies">
//  Copyright @ Remote Diagnostic Technologies Ltd. 2016.
//</copyright>
//-----------------------------------------------------------------------
/**
 * This class is a demonstration program to display the use Tempus Listener API
 */
public class EPCRDemo {

	// {"$type":"Vitals",
	//   "vitals":{"$type":"Vital[]","$values":
	//         [{"$type":"Vital","type":"Real Time","tempusNumber":600035,"incidentGUID":"B4709138-B3C2-5B9D-B511-BDFF8FB554A0","captureTime":"2016-08-10 15:26:22",
	//         "signs":{"$type":"VitalSign[]","$values":
	//                [
	//					{"$type":"VitalSign","code":"","name":"HR","val":"80.0","alert":"0","units":"/min","src":"ECG"}
	//                ]
	//          }
	//          }]
	//   }
	// ,"crc":"f3fc"}
	
	public static void parseVitals( String vitals ) {
		
	}
	public static void main(String[] args) {

		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(new File("./ref/config.txt"))));
			StringBuilder builder = new StringBuilder();
			String line=null;
			while ((line=reader.readLine())!=null) 
			{
				builder.append(line);
			}
			Gson gson = new Gson();
			FileConfig fc = gson.fromJson(builder.toString(), FileConfig.class);
			
			//Create a new configuration object. For parameters and their usage refer to the integration Guide
			
			/*FileConfig fc = new FileConfig();
			fc.Location="c:/Users/Public/DataLocation/Android";
			fc.IPAddr="Any";
			fc.Password="12345678";
			fc.Port=52512;
			fc.Name="EPCR1";
			fc.EnableEncryption=false;
			fc.IV="!QAZ2WSX!QAZ2WSX";
			fc.Encryption="FULL";
			fc.Cipher="SYM_AES_256";
			fc.Key="5TGB8YHN7UJM(IKL5TGB8YHN7UJM(IKT";
			fc.MaxConcurrentConnections=50;*/

			System.out.println("Java: " + System.getProperty("java.home"));
			//Create API instance and set listener status event handler. 
			TempusConnection tc = new TempusConnection();
			tc.SetListenerStatusEventHandler(new ListenerStatusEventHandler() {

				@Override
				public void ListenerStatusMessage(int statusCode, String strInfo) {
					System.out.println("[" + statusCode + "] message: " + strInfo );
					
					// TODO Auto-generated method stub
					super.ListenerStatusMessage(statusCode, strInfo);
					
				} 
				
			}
			);
			
			
			//Initialize the API with the config settings.
			int errorState = tc.InitTempusListener(fc.toString());
			if (errorState!=0) {
				//Check if there are any errors in initialization
				TempusListenerStatus status = tc.GetStatus();
				System.out.println(status.StatusCode+":"+status.StatusText);
				System.exit(0);
			}
			//Setup live streaming
			//Set message receiver implementation to handle callback methods from listener
			// tc.SetMessageReceiver(new MessageReceiver(fc));
			tc.SetMessageReceiver( new IMessageReceiver() {

				@Override
				public void onPatientDataReceived(int arg0, String arg1) {
					System.out.println("[" + arg0 + "] p-data: " + arg1 );
				}

				@Override
				public void onTempusConnection(int arg0, String arg1) {
					System.out.println("[" + arg0 + "] connect: " + arg1 );
				}

				@Override
				public void onTempusDisconnection(int arg0, String arg1) {
					System.out.println("[" + arg0 + "] disconnect: " + arg1 );
				}

				@Override
				public void onVitalReceived(int arg0, String arg1) {
					System.out.println("[" + arg0 + "] vitals=" + arg1 );
				}

				@Override
				public void onEventsReceived(int arg0, String arg1) {
					// TODO Auto-generated method stub
					
				}

				@Override
				public void onRTDisplaySpecReceived(int arg0, String arg1) {
					// TODO Auto-generated method stub
					
				}

				@Override
				public void onRTWaveformReceived(int arg0, String arg1) {
					// TODO Auto-generated method stub
					
				} } );
			
			//Enable realtime streaming on the listener
			tc.EnableRTStreaming("wn27fKmvJqe3yGNn");
			
			//Start the listener
			tc.StartTempusListener();
			for( int i = 0; i < 1000; i++ ) {
				System.out.println("tick");
				Thread.sleep(1000);
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
