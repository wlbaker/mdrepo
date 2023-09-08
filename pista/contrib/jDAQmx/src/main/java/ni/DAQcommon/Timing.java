package ni.DAQcommon;


public abstract class Timing { 
	private long _taskHandle;

	protected Timing( long taskHandle ) {
		this._taskHandle = taskHandle;
	}

	public abstract void configureSampleClock(String signalSource, double rate, SampleClockActiveEdge activeEdge, SampleQuantityMode sampleMode, int samplesPerChannel);
	
	/*
        public AIConvertActiveEdge AIConvertActiveEdge { get; set; }
        public double AIConvertMaximumRate { get; }
        public double AIConvertRate { get; set; }
        public string AIConvertSource { get; set; }
        public long AIConvertTimebaseDivisor { get; set; }
        public AIConvertTimebaseSource AIConvertTimebaseSource { get; set; }
        public string ChangeDetectionDIFallingEdgePhysicalChannels { get; set; }
        public string ChangeDetectionDIRisingEdgePhysicalChannels { get; set; }
        public bool ChangeDetectionDITristate { get; set; }
        public bool ChangeDetectionOverflowed { get; }
        public double DelayFromSampleClock { get; set; }
        public DelayFromSampleClockUnits DelayFromSampleClockUnits { get; set; }
        public bool DigitalFilterEnable { get; set; }
        public double DigitalFilterMinimumPulseWidth { get; set; }
        public double DigitalFilterTimebaseRate { get; set; }
        public string DigitalFilterTimebaseSource { get; set; }
        public bool DigitalSynchronizationEnable { get; set; }
        public double HandshakeDelayAfterTransfer { get; set; }
        public HandshakeSampleInputDataCondition HandshakeSampleInputDataCondition { get; set; }
        public HandshakeStartCondition HandshakeStartCondition { get; set; }
        public ImplicitUnderflowBehavior ImplicitUnderflowBehavior { get; set; }
        public double MasterTimebaseRate { get; set; }
        public string MasterTimebaseSource { get; set; }
        public bool OnDemandAOIsSimultaneous { get; set; }
        public double ReferenceClockRate { get; set; }
        public string ReferenceClockSource { get; set; }
        public SampleClockActiveEdge SampleClockActiveEdge { get; set; }
        public bool SampleClockDigitalFilterEnable { get; set; }
        public double SampleClockDigitalFilterMinimumPulseWidth { get; set; }
        public double SampleClockDigitalFilterTimebaseRate { get; set; }
        public string SampleClockDigitalFilterTimebaseSource { get; set; }
        public bool SampleClockDigitalSynchronizationEnable { get; set; }
        public double SampleClockMaximumRate { get; }
        public SampleClockOverrunBehavior SampleClockOverrunBehavior { get; set; }
        public double SampleClockRate { get; set; }
        public string SampleClockSource { get; set; }
        public string SampleClockTerminal { get; }
        public SampleClockTimebaseActiveEdge SampleClockTimebaseActiveEdge { get; set; }
        public long SampleClockTimebaseDivisor { get; set; }
        public long SampleClockTimebaseMasterTimebaseDivisor { get; set; }
        public double SampleClockTimebaseRate { get; set; }
        public string SampleClockTimebaseSource { get; set; }
        public string SampleClockTimebaseTerminal { get; }
        public SampleClockUnderflowBehavior SampleClockUnderflowBehavior { get; set; }
        public SampleQuantityMode SampleQuantityMode { get; set; }
        public long SamplesPerChannel { get; set; }
        public long SampleTimingEngine { get; set; }
        public SampleTimingType SampleTimingType { get; set; }
        public SinglePoint SinglePoint { get; }
        public double SynchronizationPulseMinimumDelayToStart { get; set; }
        public string SynchronizationPulseSource { get; set; }
        public double SynchronizationPulseTime { get; }
        public Timing this[string deviceNames] { get; }
        public void ConfigureChangeDetection(string diRisingEdgePhysicalChannels, string diFallingEdgePhysicalChannels, SampleQuantityMode sampleMode);
        public void ConfigureChangeDetection(string diRisingEdgePhysicalChannels, string diFallingEdgePhysicalChannels, SampleQuantityMode sampleMode, int samplesPerChannel);
        public void ConfigureHandshaking(SampleQuantityMode sampleMode);
        public void ConfigureHandshaking(SampleQuantityMode sampleMode, int samplesPerChannel);
        public void ConfigureHandshakingBurstExportClock(string sampleClockOutputTerminal, double rate, DigitalLevelPauseTriggerCondition pauseCondition, ReadyForTransferEventLevelActiveLevel level, SampleClockPulsePolarity pulsePolarity, SampleQuantityMode sampleMode, int samplesPerChannel);
        public void ConfigureHandshakingBurstImportClock(string signalSource, double rate, SampleClockActiveEdge activeEdge, DigitalLevelPauseTriggerCondition pauseCondition, ReadyForTransferEventLevelActiveLevel level, SampleQuantityMode sampleMode, int samplesPerChannel);
        public void ConfigureImplicit(SampleQuantityMode sampleMode);
        public void ConfigureImplicit(SampleQuantityMode sampleMode, int samplesPerChannel);
        public void ConfigurePipelinedSampleClock(string signalSource, double rate, SampleClockActiveEdge activeEdge, SampleQuantityMode sampleMode, int samplesPerChannel);
        protected virtual void Dispose(bool __p1);
    */

    
}
