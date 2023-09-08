package idea.driver.tempus;

import TempusListener.IListenerStatusEventHandler;
import TempusListener.Log.ILog;
import TempusListener.Log.LogType;
import TempusListener.Log.TempusLogger;


/**
 * This class handles and displays status of the listener while transferring data
 *
 */
public class ListenerStatusEventHandler implements IListenerStatusEventHandler{
	private ILog log = TempusLogger.GetInstance().GetLogger();
	
	@Override
	public void ListenerStatusMessage(int statusCode, String strInfo) {
		switch (statusCode)
        {
            case 8:
            	log.LogMessage("STATUS CALLBACK 008, MaxConnReached Info >> " + strInfo, LogType.InfoLog);
                break;
            case 109:
            	log.LogMessage("STATUS CALLBACK 109, ResponseTimeout Info >> " + strInfo, LogType.InfoLog);
                break;
            case 50:
            	log.LogMessage("STATUS CALLBACK 50, Stopped Info >> " + strInfo, LogType.InfoLog);
                break;
            case 111:
            	log.LogMessage("STATUS CALLBACK 111, SystemException Info >> " + strInfo, LogType.InfoLog);
                break;
            default:
            	log.LogMessage("STATUS CALLBACK " + statusCode + ", Info >> " + strInfo, LogType.InfoLog);
                break;
        }
	}

}
