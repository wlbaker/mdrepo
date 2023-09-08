package ni.DAQcommon;

public abstract class DaqStream {
	private Task _task;

	protected DaqStream( Task task ) {
		this._task = task;
	}
	
    public int getNumberOfInputChannels() {
    	return _task.getAIChannels().getCount();
    }
    public int getNumberOfOutputChannels() {
    	return _task.getAOChannels().getCount();
    }
    
    public abstract void configureInputBuffer(long bufferSize);
    public abstract void configureOutputBuffer(long bufferSize);
    
    //? public int getCount() { return ll.size(); };

	/*
    public long NumberOfOutputChannels { get; }
    public long AvailableSamplesPerChannel { get; }
    public DaqBuffer Buffer { get; }
    public string ChannelsToRead { get; set; }
    public string[] CommonModeRangeErrorChannels { get; }
    public bool CommonModeRangeErrorChannelsExist { get; }
    public long CurrentReadPosition { get; }
    public long CurrentWritePosition { get; }
    public long DigitalLinesPerInputChannel { get; }
    public long DigitalLinesPerOutputChannel { get; }
    public string LoggingFilePath { get; set; }
    public LoggingMode LoggingMode { get; set; }
    public bool NextWriteIsLast { get; set; }
    public string[] OpenThermocoupleChannels { get; }
    public bool OpenThermocoupleChannelsExist { get; }
    public long OutputBufferSpaceAvailable { get; }
    public string[] OverloadedInputChannels { get; }
    public bool OverloadedInputChannelsExist { get; }
    public bool ReadAllAvailableSamples { get; set; }
    public bool ReadAutoStart { get; set; }
    public int ReadOffset { get; set; }
    public string[] ReadOpenCurrentLoopChannels { get; }
    public bool ReadOpenCurrentLoopChannelsExist { get; }
    public string[] ReadOvercurrentChannels { get; }
    public bool ReadOvercurrentChannelsExist { get; }
    public ReadOverwriteMode ReadOverwriteMode { get; set; }
    public long ReadRawDataWidth { get; }
    public ReadRelativeTo ReadRelativeTo { get; set; }
    public double ReadSleepTime { get; set; }
    public ReadWaitMode ReadWaitMode { get; set; }
    public string TdmsLoggingGroupName { get; set; }
    public TdmsLoggingOperation TdmsLoggingOperation { get; set; }
    public int Timeout { get; set; }
    public long TotalSamplesAcquiredPerChannel { get; }
    public long TotalSamplesGeneratedPerChannel { get; }
    public WaveformAttributeModes WaveformAttributeMode { get; set; }
    public int WriteOffset { get; set; }
    public string[] WriteOpenCurrentLoopChannels { get; }
    public bool WriteOpenCurrentLoopChannelsExist { get; }
    public string[] WriteOvercurrentChannels { get; }
    public bool WriteOvercurrentChannelsExist { get; }
    public bool WriteOvertemperatureChannelsExist { get; }
    public string[] WritePowerSupplyFaultChannels { get; }
    public bool WritePowerSupplyFaultChannelsExist { get; }
    public long WriteRawDataWidth { get; }
    public WriteRegenerationMode WriteRegenerationMode { get; set; }
    public WriteRelativeTo WriteRelativeTo { get; set; }
    public double WriteSleepTime { get; set; }
    public WriteWaitMode WriteWaitMode { get; set; }

    public byte[] ReadRaw(int samplesPerChannel);
    public void WriteRaw(bool autoStart, byte[] data);
	*/
 	
}
