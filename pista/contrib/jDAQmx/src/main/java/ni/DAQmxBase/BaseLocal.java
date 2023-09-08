package ni.DAQmxBase;

import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.Local;

public class BaseLocal extends Local {

	private native void _init ();
	
	private static BaseLocal local;

	private BaseLocal() {
		_init();
	}

	public static Local getInstance() {
		if( local == null ) {
			local = new BaseLocal();
		}
		return local;
	}
	
	/*
	        public string[] getScales();
	        public string[] getSwitchChannels();
	        public string[] getSwitchRelays();
	        public string[] getSwitchTopologies { get; }
	        public virtual bool SynchronizeCallbacks { get; set; }

	        public event DaqWarningEventHandler DaqWarning;
	        public void ClearLastDaqWarning();
	        public void CloseSwitchRelays(string relays, bool waitForSettling);
	        public void ConnectSwitchChannels(string connectionList, bool waitForSettling);
	        public void ConnectSwitchChannels(string switchChannel1, string switchChannel2, bool waitForSettling);
	        public void ConnectTerminals(string sourceTerminal, string destinationTerminal);
	        public void ConnectTerminals(string sourceTerminal, string destinationTerminal, SignalRoutingModifiers signalModifiers);
	        public Task CreateSwitchScanTask(string taskName, string scanList);
	        public Task CreateWatchdogTimerTask(string taskName, string device, double timeout, string[] physicalChannels, WatchdogDOExpirationState[] expirationStates);
	        public void DeleteGlobalChannel(string persistedName);
	        public void DeleteScale(string persistedName);
	        public void DeleteTask(string persistedName);
	        public void DisconnectAll(string switchDevice, bool waitForSettling);
	        public void DisconnectSwitchChannels(string disconnectionList, bool waitForSettling);
	        public void DisconnectSwitchChannels(string switchChannel1, string switchChannel2, bool waitForSettling);
	        public void DisconnectTerminals(string sourceTerminal, string destinationTerminal);
	  */      
	        public String[] getTasks() { return null; }
	        public native String[] getPhysicalChannels( ); // PhysicalChannelTypes physicalChannelTypes, PhysicalChannelAccess physicalChannelAccess);


	        /*
	        public SavedChannelInfo GetSavedChannelInfo(string persistedName);
	        public SavedScaleInfo GetSavedScaleInfo(string persistedName);
	        public SavedTaskInfo GetSavedTaskInfo(string persistedName);
	        public long GetSwitchRelayCount(string relay);
	        public long[] GetSwitchRelayCounts(string relays);
	        public SwitchRelayPosition GetSwitchRelayPosition(string relay);
	        public SwitchRelayPosition[] GetSwitchRelayPositions(string relays);
	        public string[] GetTerminals(TerminalTypes terminalTypes);
	        public Device LoadDevice(string deviceName);
	        public PhysicalChannel LoadPhysicalChannel(string physicalChannelName);
	        public Scale LoadScale(string persistedName);
	        public SwitchChannel LoadSwitchChannel(string switchChannelName);
	        public Task LoadTask(string persistedName);
	        protected internal void OnDaqWarning(DaqWarningEventArgs e);
	        public void OpenSwitchRelays(string relays, bool waitForSettling);
	        public void SaveGlobalChannel(Channel channel);
	        public void SaveGlobalChannel(Channel channel, string author, SaveOptions options);
	        public void SaveGlobalChannelAs(Channel channel, string persistedName);
	        public void SaveGlobalChannelAs(Channel channel, string persistedName, string author, SaveOptions options);
	        public void SaveScale(Scale scale);
	        public void SaveScale(Scale scale, string author, SaveOptions options);
	        public void SaveScaleAs(Scale scale, string persistedName);
	        public void SaveScaleAs(Scale scale, string persistedName, string author, SaveOptions options);
	        public void SaveTask(Task task);
	        public void SaveTask(Task task, string author, SaveOptions options);
	        public void SaveTaskAs(Task task, string persistedName);
	        public void SaveTaskAs(Task task, string persistedName, string author, SaveOptions options);
	        public void SetDevicePowerUpState(string deviceName, string[] virtualChannels, DigitalPowerUpState[] powerUpStates);
	        public void SetDevicePowerUpState(string deviceName, string[] voltageChannels, double[] voltageValues, string[] currentChannels, double[] currentValues);
	        public void SetLogicFamilyPowerUpState(string deviceName, LogicFamily logicFamily);
	        public string SwitchFindPath(string switchChannel1, string switchChannel2);
	        public string SwitchFindPath(string switchChannel1, string switchChannel2, Enum switchPathStatus);
	        public void TristateOutputTerminal(string outputTerminal);
	        */
	    	
}
