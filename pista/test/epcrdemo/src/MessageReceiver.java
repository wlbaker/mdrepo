
import java.io.FileWriter;
import java.text.SimpleDateFormat;
import java.util.Calendar;

import TempusListener.FileConfig;
import TempusListener.IMessageReceiver;
import TempusListener.Log.ILog;
import TempusListener.Log.LogType;
import TempusListener.Log.TempusLogger;

/**
 * Class to implement callback methods from Tempus Listener API. 
 */
public class MessageReceiver implements IMessageReceiver {
    private ILog log = TempusLogger.GetInstance().GetLogger();
    private FileWriter vitalWriter;
    private FileWriter patientWriter;
    FileConfig config=null;
    
    public MessageReceiver(FileConfig config) {
    	this.config=config;
    	String dateString = new SimpleDateFormat("yyyyMMddHHmmss").format(Calendar.getInstance().getTime());
        String currentPatientFile = config.Location + "\\" + dateString+"-PatientData.txt";
	    String currentVitalFile = config.Location + "\\" + dateString + "-Vitals.txt";
	    try {
			vitalWriter = new FileWriter(currentVitalFile, true);
			patientWriter = new FileWriter(currentPatientFile, true);
		} catch (Exception ex) {
			log.LogMessage("Error in tempus connection: " + ex.getMessage(),LogType.WarnLog);
		}
    }
    
    /**
     * This API method is called whenever a device is connected to the tempus for streaming.
     * @see TempusListener.IMessageReceiver#onTempusConnection(int, java.lang.String)
     */
    @Override
    public void onTempusConnection(int deviceNumber, String deviceName) {
        log.LogMessage("Tempus Connection : " + deviceName,LogType.InfoLog);
    }

    /**
     * This API method is called whenever patient data is sent by the Tempus. 
     * @see TempusListener.IMessageReceiver#onPatientDataReceived(int, java.lang.String)
     */
    @Override
    public void onPatientDataReceived(int deviceNumber, String patientDataMessage) {
        log.LogMessage("Patient Data : " + patientDataMessage,LogType.InfoLog);
        try {
	        if (patientWriter!=null) {
	        	patientWriter.write(deviceNumber+":");
	        	patientWriter.write(patientDataMessage);
	        	patientWriter.write("\r\n");
	        	patientWriter.flush();
	        }
        }
        catch(Exception ex) 
        {
        	log.LogMessage("Error in patient data: " + ex.getMessage(),LogType.WarnLog);
        }
    }

    /**
     * This method is called when live vital data is sent by the tempus
     */
    @Override
    public void onVitalReceived(int deviceNumber, String vitalMessage) {
        log.LogMessage("Real Time Vitals : " + vitalMessage,LogType.InfoLog);
        try {
	        if (vitalWriter!=null) {
	        	vitalWriter.write(deviceNumber+":");
	        	vitalWriter.write(vitalMessage);
	        	vitalWriter.write("\r\n");
	        	vitalWriter.flush();
	        }
        }
        catch(Exception ex) 
        {
        	log.LogMessage("Error in vital data: " + ex.getMessage(),LogType.WarnLog);
        }
    }

    /**
     * This method is called whenever Tempus device is disconnected.
     */
    @Override
    public void onTempusDisconnection(int deviceNumber, String disconnectMessage) {
        log.LogMessage("Tempus Disconnection : " + disconnectMessage,LogType.InfoLog);
    }
}
