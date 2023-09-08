package ni.DAQcommon;


public abstract class Task {
	protected long _taskHandle;
	
	private AIChannelCollection aicc;
	private AOChannelCollection aocc;
	private Timing timing;
	private DaqStream stream;

	protected abstract long createTask( String name );

	protected abstract Timing createTiming(long taskHandle);
	protected abstract AIChannelCollection createAIChannelCollection(long taskHandle);
	protected abstract AOChannelCollection createAOChannelCollection(long taskHandle);
	protected abstract DaqStream createDaqStream();
	
	protected Task(String name) {
		_taskHandle = createTask( name );
		
		stream = createDaqStream();
		aicc = createAIChannelCollection( _taskHandle );
		aocc = createAOChannelCollection( _taskHandle );
		timing = createTiming( _taskHandle );
		// debug( stream );
	}


	public abstract AnalogMultiChannelReader createAnalogMultiChannelReader();
	public abstract AnalogMultiChannelWriter createAnalogMultiChannelWriter();
	
	public DaqStream getStream() {
		return stream;
	}

	public AIChannelCollection getAIChannels() {
		return aicc;
	}

	public AOChannelCollection getAOChannels() {
		return null;
	}

	public Timing getTiming() {
		return timing;
	}

	public void control(TaskAction mode) {
	}

	public abstract void start();

	public abstract void stop();
	public abstract void dispose();

	// public void WaitUntilDone();
	// public void WaitUntilDone(int millisecToWait);
	// public void WaitUntilDone(TimeSpan timeout);
	//   
	// public CIChannelCollection CIChannels { get; }
	// public COChannelCollection COChannels { get; }
	// public string[] Devices { get; }
	// public DIChannelCollection DIChannels { get; }
	// public DOChannelCollection DOChannels { get; }
	// public ExportSignals ExportSignals { get; }
	// public bool IsDone { get; }
	// public SwitchScan SwitchScan { get; }
	// public virtual bool SynchronizeCallbacks { get; set; }
	// public Triggers Triggers { get; }
	// public Watchdog Watchdog { get; }
	// public event CounterOutputEventHandler CounterOutput;
	// public event DigitalChangeDetectionEventHandler DigitalChangeDetection;
	// public event TaskDoneEventHandler Done;
	// public event SampleClockEventHandler SampleClock;
	// public event SampleCompleteEventHandler SampleComplete;
	// public Channel AddGlobalChannel(string channelName);
	// protected virtual void Dispose(bool __p1);
	// protected internal virtual void OnCounterOutput(CounterOutputEventArgs
	// e);
	// protected internal virtual void
	// onDigitalChangeDetection(DigitalChangeDetectionEventArgs e);
	// protected internal virtual void onDone(TaskDoneEventArgs e);
	// protected internal virtual void onSampleClock(SampleClockEventArgs e);
	// protected internal virtual void onSampleComplete(SampleCompleteEventArgs
	// e);
	//	
}
