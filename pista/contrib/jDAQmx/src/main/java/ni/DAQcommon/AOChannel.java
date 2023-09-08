package ni.DAQcommon;

public abstract class AOChannel extends Channel {

	private long _taskHandle;
	private String _channelName;

	protected abstract long createVoltageChannel(long taskHandle, String physicalChannelName, String nameToAssignChannel, AOTerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AOVoltageUnits units) throws DaqException;

	protected AOChannel( long taskHandle, String channelName, String assignName, AOTerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AOVoltageUnits units ) throws DaqException {
		super(ChannelType.AO);
		this._channelName = channelName;
		this._taskHandle  = taskHandle;
		
		createVoltageChannel( taskHandle, channelName, assignName, terminalConfiguration, minimumValue, maximumValue, units );
	}

	/*
	public AOCurrentUnits CurrentUnits { get; set; }
    public string CustomScaleName { get; set; }
    public bool DacAllowConnectReferenceToGround { get; set; }
    public bool DacConnectReferenceToGround { get; set; }
    public string DacOffsetExternalSource { get; set; }
    public AODacOffsetSource DacOffsetSource { get; set; }
    public double DacOffsetValue { get; set; }
    public double DacRangeHigh { get; set; }
    public double DacRangeLow { get; set; }
    public string DacReferenceExternalSource { get; set; }
    public AODacReferenceSource DacReferenceSource { get; set; }
    public double DacReferenceValue { get; set; }
    public AODataTransferMechanism DataTransferMechanism { get; set; }
    public AODataTransferRequestCondition DataTransferRequestCondition { get; set; }
    public double[] DeviceScalingCoefficients { get; }
    public bool EnhancedImageRejectionEnable { get; set; }
    public double FunctionGenerationAmplitude { get; set; }
    public double FunctionGenerationFMDeviation { get; set; }
    public double FunctionGenerationFrequency { get; set; }
    public AOFunctionGenerationModulationType FunctionGenerationModulationType { get; set; }
    public double FunctionGenerationOffset { get; set; }
    public double FunctionGenerationSquareDutyCycle { get; set; }
    public AOFunctionGenerationType FunctionGenerationType { get; set; }
    public double Gain { get; set; }
    public AOIdleOutputBehavior IdleOutputBehavior { get; set; }
    public double LoadImpedance { get; set; }
    public double Maximum { get; set; }
    public bool MemoryMappingEnable { get; set; }
    public double Minimum { get; set; }
    public double OutputImpedance { get; set; }
    public AOOutputType OutputType { get; }
    public bool ReglitchEnable { get; set; }
    public double Resolution { get; }
    public AOResolutionUnits ResolutionUnits { get; set; }
    public AOTerminalConfiguration TerminalConfiguration { get; set; }
    public long UsbTransferRequestSize { get; set; }
    public bool UseOnlyOnBoardMemory { get; set; }
    public double VoltageCurrentLimit { get; set; }
    public AOVoltageUnits VoltageUnits { get; set; }
	*/
}
