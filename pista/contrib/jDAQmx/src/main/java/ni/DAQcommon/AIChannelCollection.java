package ni.DAQcommon;

import java.util.LinkedList;



public abstract class AIChannelCollection {

	private LinkedList<AIChannel> ll;
	protected long _taskHandle;
	
	public AIChannelCollection( long taskHandle ) {
		this._taskHandle = taskHandle;
		ll = new LinkedList<AIChannel>();
	}
	
    public int getCount() { return ll.size(); };

    public abstract AIChannel createVoltageChannel(String physicalChannelName, String nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AIVoltageUnits units) throws DaqException;
    
    
	/*
    public virtual AIChannel All { get; }
    public virtual int ICollection_Count { get; }
    public virtual bool IsSynchronized { get; }
    public virtual object SyncRoot { get; }

    public virtual AIChannel this[long index] { get; }
    public virtual AIChannel this[string virtualChannelName] { get; }

    public AIChannel CreateAccelerometerChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration configuration, double minimumValue, double maximumValue, double sensitivity, AIAccelerometerSensitivityUnits sensitivityUnits, AIExcitationSource currentExcitationSource, double currentExcitationValue, AIAccelerationUnits units);
    public AIChannel CreateAccelerometerChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration configuration, double minimumValue, double maximumValue, double sensitivity, AIAccelerometerSensitivityUnits sensitivityUnits, AIExcitationSource currentExcitationSource, double currentExcitationValue, string customScaleName);
    public AIChannel CreateBuiltInSensorTemperatureChannel(string physicalChannelName, string nameToAssignChannel, AITemperatureUnits units);
    public AIChannel CreateCurrentChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AICurrentUnits units);
    public AIChannel CreateCurrentChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, string customScaleName);
    public AIChannel CreateCurrentChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, double externalShuntResistorValue, AICurrentUnits units);
    public AIChannel CreateCurrentChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, double externalShuntResistorValue, string customScaleName);
    public AIChannel CreateCurrentRmsChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AICurrentAcrmsUnits units);
    public AIChannel CreateCurrentRmsChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, string customScaleName);
    public AIChannel CreateCurrentRmsChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, double externalShuntResistorValue, AICurrentAcrmsUnits units);
    public AIChannel CreateCurrentRmsChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, double externalShuntResistorValue, string customScaleName);
    public AIChannel CreateEddyCurrentProximityProbeChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, double sensitivity, AIEddyCurrentProximityProbeSensitivityUnits sensitivityUnits, AIEddyCurrentProximityProbeUnits units);
    public AIChannel CreateEddyCurrentProximityProbeChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, double sensitivity, AIEddyCurrentProximityProbeSensitivityUnits sensitivityUnits, string customScaleName);
    public AIChannel CreateFrequencyVoltageChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, double thresholdVoltage, double hysteresis, AIFrequencyUnits units);
    public AIChannel CreateFrequencyVoltageChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, double thresholdVoltage, double hysteresis, string customScaleName);
    public AIChannel CreateLvdtChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, double sensitivity, AILvdtSensitivityUnits sensitivityUnits, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double voltageExcitationFrequency, AIACExcitationWireMode voltageExcitationWireMode, AILvdtUnits units);
    public AIChannel CreateLvdtChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, double sensitivity, AILvdtSensitivityUnits sensitivityUnits, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double voltageExcitationFrequency, AIACExcitationWireMode voltageExcitationWireMode, string customScaleName);
    public AIChannel CreateMicrophoneChannel(string physicalChannelName, string nameToAssignChannel, double microphoneSensitivity, double maximumSoundPressureLevel, AITerminalConfiguration terminalConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue, AISoundPressureUnits units);
    public AIChannel CreateMicrophoneChannel(string physicalChannelName, string nameToAssignChannel, double microphoneSensitivity, double maximumSoundPressureLevel, AITerminalConfiguration terminalConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue, string customScaleName);
    public AIChannel CreateResistanceChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIResistanceConfiguration resistanceConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue, AIResistanceUnits units);
    public AIChannel CreateResistanceChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIResistanceConfiguration resistanceConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue, string customScaleName);
    public AIChannel CreateRtdChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AITemperatureUnits units, AIRtdType type, AIResistanceConfiguration resistanceConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue, double r0);
    public AIChannel CreateRvdtChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, double sensitivity, AIRvdtSensitivityUnits sensitivityUnits, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double voltageExcitationFrequency, AIACExcitationWireMode voltageExcitationWireMode, AIRvdtUnits units);
    public AIChannel CreateRvdtChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, double sensitivity, AIRvdtSensitivityUnits sensitivityUnits, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double voltageExcitationFrequency, AIACExcitationWireMode voltageExcitationWireMode, string customScaleName);
    public AIChannel CreateStrainGageChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIStrainGageConfiguration strainGageConfiguration, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double gageFactor, double initialBridgeVoltage, double nominalGageResistance, double poissonRatio, double leadWireResistance, AIStrainUnits units);
    public AIChannel CreateStrainGageChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIStrainGageConfiguration strainGageConfiguration, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double gageFactor, double initialBridgeVoltage, double nominalGageResistance, double poissonRatio, double leadWireResistance, string customScaleName);
    public AIChannel CreateTedsAccelerometerChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIExcitationSource currentExcitationSource, double currentExcitationValue, AIAccelerationUnits units);
    public AIChannel CreateTedsAccelerometerChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIExcitationSource currentExcitationSource, double currentExcitationValue, string customScaleName);
    public AIChannel CreateTedsCurrentChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AICurrentUnits units);
    public AIChannel CreateTedsCurrentChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, string customScaleName);
    public AIChannel CreateTedsCurrentChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, double externalShuntResistorValue, AICurrentUnits units);
    public AIChannel CreateTedsCurrentChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, double externalShuntResistorValue, string customScaleName);
    public AIChannel CreateTedsLvdtChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double voltageExcitationFrequency, AIACExcitationWireMode voltageExcitationWireMode, AILvdtUnits units);
    public AIChannel CreateTedsLvdtChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double voltageExcitationFrequency, AIACExcitationWireMode voltageExcitationWireMode, string customScaleName);
    public AIChannel CreateTedsMicrophoneChannel(string physicalChannelName, string nameToAssignChannel, double maximumSoundPressureLevel, AITerminalConfiguration terminalConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue, AISoundPressureUnits units);
    public AIChannel CreateTedsMicrophoneChannel(string physicalChannelName, string nameToAssignChannel, double maximumSoundPressureLevel, AITerminalConfiguration terminalConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue, string customScaleName);
    public AIChannel CreateTedsResistanceChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIResistanceConfiguration resistanceConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue, AIResistanceUnits units);
    public AIChannel CreateTedsResistanceChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIResistanceConfiguration resistanceConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue, string customScaleName);
    public AIChannel CreateTedsRtdChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AITemperatureUnits units, AIResistanceConfiguration resistanceConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue);
    public AIChannel CreateTedsRvdtChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double voltageExcitationFrequency, AIACExcitationWireMode voltageExcitationWireMode, AIRvdtUnits units);
    public AIChannel CreateTedsRvdtChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double voltageExcitationFrequency, AIACExcitationWireMode voltageExcitationWireMode, string customScaleName);
    public AIChannel CreateTedsStrainGageChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double initialBridgeVoltage, double leadWireResistance, AIStrainUnits units);
    public AIChannel CreateTedsStrainGageChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double initialBridgeVoltage, double leadWireResistance, string customScaleName);
    public AIChannel CreateTedsThermistorIExChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AITemperatureUnits units, AIResistanceConfiguration resistanceConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue);
    public AIChannel CreateTedsThermistorVExChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AITemperatureUnits units, AIResistanceConfiguration resistanceConfiguration, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double r1);
    public AIChannel CreateTedsThermocoupleChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AITemperatureUnits units);
    public AIChannel CreateTedsThermocoupleChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AITemperatureUnits units, double cjcValue);
    public AIChannel CreateTedsThermocoupleChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AITemperatureUnits units, string cjcChannel);
    public AIChannel CreateTedsVoltageChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AIVoltageUnits units);
    public AIChannel CreateTedsVoltageChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, string customScaleName);
    public AIChannel CreateTedsVoltageChannelWithExcitation(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration configuration, double minimumValue, double maximumValue, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, AIVoltageUnits units);
    public AIChannel CreateTedsVoltageChannelWithExcitation(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration configuration, double minimumValue, double maximumValue, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, string customScaleName);
    public AIChannel CreateThermistorIExChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AITemperatureUnits units, AIResistanceConfiguration resistanceConfiguration, AIExcitationSource currentExcitationSource, double currentExcitationValue, double a, double b, double c);
    public AIChannel CreateThermistorVExChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AITemperatureUnits units, AIResistanceConfiguration resistanceConfiguration, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, double a, double b, double c, double r1);
    public AIChannel CreateThermocoupleChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIThermocoupleType thermocoupleType, AITemperatureUnits units);
    public AIChannel CreateThermocoupleChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIThermocoupleType thermocoupleType, AITemperatureUnits units, double cjcValue);
    public AIChannel CreateThermocoupleChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AIThermocoupleType thermocoupleType, AITemperatureUnits units, string cjcChannel);
    public AIChannel CreateVoltageChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, string customScaleName);
    public AIChannel CreateVoltageChannelWithExcitation(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration configuration, double minimumValue, double maximumValue, AIBridgeConfiguration bridgeConfiguration, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, bool useExcitationForScaling, AIVoltageUnits units);
    public AIChannel CreateVoltageChannelWithExcitation(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration configuration, double minimumValue, double maximumValue, AIBridgeConfiguration bridgeConfiguration, AIExcitationSource voltageExcitationSource, double voltageExcitationValue, bool useExcitationForScaling, string customScaleName);
    public AIChannel CreateVoltageRmsChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AIVoltageAcrmsUnits units);
    public AIChannel CreateVoltageRmsChannel(string physicalChannelName, string nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, string customScaleName);
    public virtual IEnumerator GetEnumerator();
    */

    protected void addChannel( AIChannel ch ) {
    	ll.add( ch );
    }
    
}
