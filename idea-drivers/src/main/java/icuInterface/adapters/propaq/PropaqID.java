package icuInterface.adapters.propaq;

public class PropaqID {
    /*
    * Fixed Length Control Parameter ID
    */
    public final static byte Reset = 0x01;
    public final static byte Poll = 0x02;
    public final static byte Cancel = 0x03;
    public final static byte Terminate = 0x04;
    public final static byte AutoLink = 0x05;

    /*
    * Variable Length Control Parameter IDs
    */
    public final static byte HostErrorField = (byte)0x80;
    public final static byte ACKControlField = (byte)0x81;

    /*
    * Fixed Length System Parameter IDs
    */
    public final static byte AllAlarmsOnOff = 0x01;
    public final static byte HRPRSource = 0x03;
    public final static byte CurrentHRPRSource = 0x04;
    public final static byte BatteryLevel = 0x05;
    public final static byte ConfiguredParameters = 0x06;
    public final static byte PCOVersionNumber = 0x07;
    public final static byte AlarmsActive = 0x08;
    public final static byte ConfiguredParameters2 = 0x11;
    public final static byte Formats = 0x17;
    public final static byte Language = 0x18;
    public final static byte UserInterfaceNumber = 0x1a;
    public final static byte PCOInativeTime = 0x1c;
    public final static byte CurrentRRBRSource = 0x1d;
    public final static byte PatientMode = 0x20;
    public final static byte SerialTransferRate = 0x21;
    public final static byte MonitorScreenType = 0x22;
    public final static byte ConfiguredParameters3 = 0x26;
    public final static byte CO2Source = 0x28;

    /*
    * Variable Length System Parameter IDs
    */
    public final static byte Time = (byte)0x82;
    public final static byte ModelNumber = (byte)0x83;
    public final static byte SoftwareVersion = (byte)0x84;
    public final static byte SerialNumber = (byte)0x89;
    public final static byte TimeofOperation = (byte)0x98;

    /*
    * Fixed Length Channel Parameter IDs
    */
    public final static byte ECG1 = 0x01;
    public final static byte NIBP = 0x02;
    public final static byte Temperature1 = 0x03;
    public final static byte Temperature2 = 0x04;
    public final static byte INVP1 = 0x05;
    public final static byte INVP2 = 0x06;
    public final static byte SpO2 = 0x07;
    public final static byte Printer = 0x08;
    public final static byte Battery = 0x09;
    public final static byte MainstreamCO2 = 0x0a;
    public final static byte Respiration = 0x0b;
    public final static byte Defibrillator = 0x0c;
    public final static byte ECG2 = 0x0e;
    public final static byte SidestreamCO2 = 0x11;

    /*
    * Variable Length Channel Parameter IDs
    */
    public final static byte ECG1VectorSelect = 0x01;
    public final static byte ECGFilter = 0x02;
    public final static byte NIBPAutoMode = 0x03;
    public final static byte NIBPInterval = 0x04;
    public final static byte NIBPStartStop = 0x05;
    public final static byte NIBPTurbo = 0x06;
    public final static byte INVP1Label = 0x07;
    public final static byte INVP2Label = 0x08;
    public final static byte ECGBandwidth = 0x09;
    public final static byte SpO2ResponseMode = 0x0a;
    public final static byte SpO2CLockSelection = 0x0b;
    public final static byte MiscSensorStatus1 = 0x0c;
    public final static byte NIVP1ZeroingStatus = 0x0d;
    public final static byte NIVP2ZeroingStatus = 0x0e;
    public final static byte CO2UnitsOfMeasure = 0x0f;
    public final static byte CO2ResponseMode = 0x10;
    public final static byte CO2GasCompensation = 0x11;
    public final static byte ApneaDelay = 0x12;
    public final static byte CO2BRSensorStatus = 0x13;
    public final static byte RespirationConfig = 0x14;
    public final static byte ECG2VectorSelect = 0x16;
    public final static byte ECGWireSet = 0x19;
    public final static byte MiscSensorStatus2 = 0x1a;
    public final static byte SSCO2CommandedFlowRate = 0x1b;

    /*
    * Variable Length Sensor Parameter IDs
    */
    public final static byte ManometerPressure = (byte)0x82;
    public final static byte BarometricPressure = (byte)0x83;
    public final static byte MainstreamCO2SensorSerialNumber = (byte)0x84;
    public final static byte SidestreamCO2SensorSerialNumber = (byte)0x89;

    /*
    * Fixed Length Numeric Parameter IDs
    */
    public final static byte HeartRatePulseRate = 0x01;
    public final static byte NIBPSystolic = 0x02;
    public final static byte NIBPDiastolic = 0x03;
    public final static byte NIBPMean = 0x04;
    public final static byte Temperature1YSI = 0x05;
    public final static byte Temperature2YSI = 0x06;
    public final static byte DeltaTemperature = 0x07;
    public final static byte INVP1Systolic = 0x08;
    public final static byte INVP1Diastolic = 0x09;
    public final static byte INVP1Mean = 0x0a;
    public final static byte INVP2Systolic = 0x0b;
    public final static byte INVP2Diastolic = 0x0c;
    public final static byte INVP2Mean = 0x0d;
    public final static byte PercentSPO2 = 0x0e;
    public final static byte SpO2PulseRate = 0x0f;
    public final static byte NIBPPulseRate = 0x10;
    public final static byte INVP1PulseRate = 0x11;
    public final static byte INVP2PulseRate = 0x12;
    public final static byte ECG1HeartRate = 0x13;
    public final static byte EtCO2 = 0x14;
    public final static byte InCO2 = 0x15;
    public final static byte RespirationBreathRate = 0x16;
    public final static byte CO2BreathRate = 0x17;
    public final static byte ImpedancePneumographyRespirationRate = 0x18;
    public final static byte ECG2HeartRate = 0x19;

    /*
    * Variable Length Waveform Parameter IDs
    */
    public final static byte WaveformTransfer1 = 0x01;
    public final static byte AutoModeOnOff = 0x03;
    public final static byte WaveformDisplay = 0x06;

}

