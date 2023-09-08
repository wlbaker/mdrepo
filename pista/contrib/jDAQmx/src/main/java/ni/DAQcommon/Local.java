package ni.DAQcommon;

public abstract class Local {

    public abstract String[] getTasks();
    public abstract String[] getPhysicalChannels( );
    

    /*
	        public string[] getScales();
	        public string[] getSwitchChannels();
	        public string[] getSwitchRelays();
	        public string[] getSwitchTopologies { get; }
	        //?? public virtual bool setSynchronizeCallbacks( boolean val )

	        void addDaqWarningListener(DaqWarningEventArgs e);
	        void removeDaqWarningListener(DaqWarningEventArgs e);
	        
	        public void clearLastDaqWarning();
	        public void closeSwitchRelays(string relays, bool waitForSettling);
	        public void connectSwitchChannels(string connectionList, bool waitForSettling);
	        public void connectSwitchChannels(string switchChannel1, string switchChannel2, bool waitForSettling);
	        public void connectTerminals(string sourceTerminal, string destinationTerminal);
	        public void connectTerminals(string sourceTerminal, string destinationTerminal, SignalRoutingModifiers signalModifiers);
	        public Task createSwitchScanTask(string taskName, string scanList);
	        public Task createWatchdogTimerTask(string taskName, string device, double timeout, string[] physicalChannels, WatchdogDOExpirationState[] expirationStates);
	        public void deleteGlobalChannel(string persistedName);
	        public void deleteScale(string persistedName);
	        public void deleteTask(string persistedName);
	        public void disconnectAll(string switchDevice, bool waitForSettling);
	        public void disconnectSwitchChannels(string disconnectionList, bool waitForSettling);
	        public void disconnectSwitchChannels(string switchChannel1, string switchChannel2, bool waitForSettling);
	        public void disconnectTerminals(string sourceTerminal, string destinationTerminal);
	  */      

	        /*
	        public SavedChannelInfo getSavedChannelInfo(string persistedName);
	        public SavedScaleInfo getSavedScaleInfo(string persistedName);
	        public SavedTaskInfo getSavedTaskInfo(string persistedName);
	        public long getSwitchRelayCount(string relay);
	        public long[] getSwitchRelayCounts(string relays);
	        public SwitchRelayPosition getSwitchRelayPosition(string relay);
	        public SwitchRelayPosition[] getSwitchRelayPositions(string relays);
	        public string[] getTerminals(TerminalTypes terminalTypes);
	        public Device loadDevice(string deviceName);
	        public PhysicalChannel loadPhysicalChannel(string physicalChannelName);
	        public Scale loadScale(string persistedName);
	        public SwitchChannel loadSwitchChannel(string switchChannelName);
	        public Task loadTask(string persistedName);
	        public void openSwitchRelays(string relays, bool waitForSettling);
	        public void saveGlobalChannel(Channel channel);
	        public void saveGlobalChannel(Channel channel, string author, SaveOptions options);
	        public void saveGlobalChannelAs(Channel channel, string persistedName);
	        public void saveGlobalChannelAs(Channel channel, string persistedName, string author, SaveOptions options);
	        public void saveScale(Scale scale);
	        public void saveScale(Scale scale, string author, SaveOptions options);
	        public void saveScaleAs(Scale scale, string persistedName);
	        public void saveScaleAs(Scale scale, string persistedName, string author, SaveOptions options);
	        public void saveTask(Task task);
	        public void saveTask(Task task, string author, SaveOptions options);
	        public void saveTaskAs(Task task, string persistedName);
	        public void saveTaskAs(Task task, string persistedName, string author, SaveOptions options);
	        public void setDevicePowerUpState(string deviceName, string[] virtualChannels, DigitalPowerUpState[] powerUpStates);
	        public void setDevicePowerUpState(string deviceName, string[] voltageChannels, double[] voltageValues, string[] currentChannels, double[] currentValues);
	        public void setLogicFamilyPowerUpState(string deviceName, LogicFamily logicFamily);
	        public string switchFindPath(string switchChannel1, string switchChannel2);
	        public string switchFindPath(string switchChannel1, string switchChannel2, Enum switchPathStatus);
	        public void tristateOutputTerminal(string outputTerminal);
	        */
	    	
}
