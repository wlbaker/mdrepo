package ni.DAQcommon;


public abstract class AIChannel extends Channel implements IFilteredTypeDescriptor {

	private long _taskHandle;
	private String _channelName;

	protected abstract long createVoltageChannel(long taskHandle, String physicalChannelName, String nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AIVoltageUnits units) throws DaqException;

	protected AIChannel( long taskHandle, String channelName, String assignName, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AIVoltageUnits units ) throws DaqException {
		super(ChannelType.AI);
		this._channelName = channelName;
		this._taskHandle  = taskHandle;
		
		createVoltageChannel( taskHandle, channelName, assignName, terminalConfiguration, minimumValue, maximumValue, units );
	}


	@Override
	public ICustomTypeDescriptor getFilteredTypeDescriptor(
			PropertyFilterType filterType) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ICustomTypeDescriptor getFilteredTypeDescriptor(
			PropertyFilterType filterType, PropertyFilterFlags filterFlags) {
		// TODO Auto-generated method stub
		return null;
	}


    public native double getAccelerationDecibelReference();
    public native void setAccelerationDecibelReference( double val );
    
//    public AIAccelerationUnits AccelerationUnits { get; set; }
//    public double AccelerometerSensitivity { get; set; }
//    public AIAccelerometerSensitivityUnits AccelerometerSensitivityUnits { get; set; }
//    public double ACExcitationFrequency { get; set; }
//    public bool ACExcitationSyncEnable { get; set; }
//    public AIACExcitationWireMode ACExcitationWireMode { get; set; }
//    public AIAdcTimingMode AdcTimingMode { get; set; }
//    public double Attenuation { get; set; }
//    public AIAutoZeroMode AutoZeroMode { get; set; }
//    public int BridgeBalanceCoarsePot { get; set; }
//    public int BridgeBalanceFinePot { get; set; }
//    public AIBridgeConfiguration BridgeConfiguration { get; set; }
//    public double BridgeInitialVoltage { get; set; }
//    public double BridgeNominalResistance { get; set; }
//    public bool BridgeShuntCalibrationEnable { get; set; }
//    public double BridgeShuntCalibrationGainAdjust { get; set; }
//    public AIBridgeShuntCalibrationSelect BridgeShuntCalibrationSelect { get; set; }
//    public bool CalibrationApplyIfExpired { get; set; }
//    public DateTime CalibrationDate { get; set; }
//    public string CalibrationDescription { get; set; }
//    public bool CalibrationEnable { get; set; }
//    public DateTime CalibrationExpirationDate { get; set; }
//    public bool CalibrationHasValidInfo { get; }
//    public string CalibrationOperatorName { get; set; }
//    public double[] CalibrationPolynomialForwardCoefficients { get; set; }
//    public double[] CalibrationPolynomialReverseCoefficients { get; set; }
//    public AIChannelCalibrationScaleType CalibrationScaleType { get; set; }
//    public double[] CalibrationTablePreScaledValues { get; set; }
//    public double[] CalibrationTableScaledValues { get; set; }
//    public double[] CalibrationVerificationAcquiredValues { get; set; }
//    public double[] CalibrationVerificationReferenceValues { get; set; }
//    public AICoupling Coupling { get; set; }
//    public AICurrentAcrmsUnits CurrentAcrmsUnits { get; set; }
//    public AICurrentShuntLocation CurrentShuntLocation { get; set; }
//    public double CurrentShuntResistance { get; set; }
//    public AICurrentUnits CurrentUnits { get; set; }
//    public string CustomScaleName { get; set; }
//    public long DataTransferCustomThreshold { get; set; }
//    public AIDataTransferMechanism DataTransferMechanism { get; set; }
//    public AIDataTransferRequestCondition DataTransferRequestCondition { get; set; }
//    public double DCOffset { get; set; }
//    public double[] DeviceScalingCoefficients { get; }
//    public bool DitherEnable { get; set; }
//    public double EddyCurrentProximityProbeSensitivity { get; set; }
//    public AIEddyCurrentProximityProbeSensitivityUnits EddyCurrentProximityProbeSensitivityUnits { get; set; }
//    public AIEddyCurrentProximityProbeUnits EddyCurrentProximityProbeUnits { get; set; }
//    public bool EnhancedAliasRejectionEnable { get; set; }
//    public double ExcitationActualValue { get; set; }
//    public AIExcitationDCOrAC ExcitationDCOrAC { get; set; }
//    public AIExcitationSource ExcitationSource { get; set; }
//    public double ExcitationValue { get; set; }
//    public AIExcitationVoltageOrCurrent ExcitationVoltageOrCurrent { get; set; }
//    public bool ForceReadFromChannel { get; set; }
//    public double FrequencyHysteresis { get; set; }
//    public double FrequencyThresholdVoltage { get; set; }
//    public AIFrequencyUnits FrequencyUnits { get; set; }
//    public double Gain { get; set; }
//    public double Impedance { get; set; }
//    public string InputSource { get; set; }
//    public bool IsTeds { get; }
//    public double LeadWireResistance { get; set; }
//    public long LossyLsbRemovalCompressedSampleSize { get; set; }
//    public double LowpassCutoffFrequency { get; set; }
//    public bool LowpassEnable { get; set; }
//    public AILowpassSwitchedCapacitorClockSource LowpassSwitchedCapacitorClockSource { get; set; }
//    public long LowpassSwitchedCapacitorExternalClockDivisor { get; set; }
//    public double LowpassSwitchedCapacitorExternalClockFrequency { get; set; }
//    public long LowpassSwitchedCapacitorOutputClockDivisor { get; set; }
//    public double LvdtSensitivity { get; set; }
//    public AILvdtSensitivityUnits LvdtSensitivityUnits { get; set; }
//    public AILvdtUnits LvdtUnits { get; set; }
//    public double Maximum { get; set; }
//    public double MaximumSoundPressureLevel { get; set; }
//    public AIMeasurementType MeasurementType { get; }
//    public bool MemoryMappingEnable { get; set; }
//    public double MicrophoneSensitivity { get; set; }
//    public double Minimum { get; set; }
//    public double ProbeAttenuation { get; set; }
//    public double RangeHigh { get; set; }
//    public double RangeLow { get; set; }
//    public AIRawDataCompressionType RawDataCompressionType { get; set; }
//    public AIRawSampleJustification RawSampleJustification { get; }
//    public long RawSampleSize { get; }
//    public AIResistanceConfiguration ResistanceConfiguration { get; set; }
//    public AIResistanceUnits ResistanceUnits { get; set; }
//    public double Resolution { get; }
//    public AIResolutionUnits ResolutionUnits { get; }
//    public double RtdA { get; set; }
//    public double RtdB { get; set; }
//    public double RtdC { get; set; }
//    public double RtdR0 { get; set; }
//    public AIRtdType RtdType { get; set; }
//    public double RvdtSensitivity { get; set; }
//    public AIRvdtSensitivityUnits RvdtSensitivityUnits { get; set; }
//    public AIRvdtUnits RvdtUnits { get; set; }
//    public bool SampleAndHoldEnable { get; set; }
//    public double SoundPressureDecibelReference { get; set; }
//    public AISoundPressureUnits SoundPressureUnits { get; set; }
//    public AIStrainGageConfiguration StrainGageConfiguration { get; set; }
//    public double StrainGageGageFactor { get; set; }
//    public double StrainGagePoissonRatio { get; set; }
//    public AIStrainUnits StrainUnits { get; set; }
//    public string TedsUnits { get; }
//    public AITemperatureUnits TemperatureUnits { get; set; }
//    public AITerminalConfiguration TerminalConfiguration { get; set; }
//    public double ThermistorA { get; set; }
//    public double ThermistorB { get; set; }
//    public double ThermistorC { get; set; }
//    public double ThermistorR1 { get; set; }
//    public string ThermocoupleCjcChannel { get; }
//    public AIThermocoupleCjcSource ThermocoupleCjcSource { get; }
//    public double ThermocoupleCjcValue { get; set; }
//    public AIThermocoupleScaleType ThermocoupleScaleType { get; set; }
//    public AIThermocoupleType ThermocoupleType { get; set; }
//    public long UsbTransferRequestSize { get; set; }
//    public bool UseExcitationForScaling { get; set; }
//    public bool UseMultiplexedExcitation { get; set; }
//    public AIVoltageAcrmsUnits VoltageAcrmsUnits { get; set; }
//    public double VoltageDecibelReference { get; set; }
//    public AIVoltageUnits VoltageUnits { get; set; }
//
//    public void PerformBridgeOffsetNullingCalibration();
//    public void PerformBridgeOffsetNullingCalibration(bool skipUnsupportedChannels);
//    public void PerformBridgeShuntCalibration(double shuntResistorValue, ShuntElementLocation shuntResistorLocation, double bridgeResistance);
//    public void PerformBridgeShuntCalibration(double shuntResistorValue, ShuntElementLocation shuntResistorLocation, double bridgeResistance, bool skipUnsupportedChannels);
//    public void PerformStrainShuntCalibration(double shuntResistorValue, ShuntElementLocation shuntResistorLocation);
//    public void PerformStrainShuntCalibration(double shuntResistorValue, ShuntElementLocation shuntResistorLocation, bool skipUnsupportedChannels);
}
