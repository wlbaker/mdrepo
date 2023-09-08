package ni.DAQcommon;

public enum SampleQuantityMode {
    ContinuousSamples( 10123 ),
    FiniteSamples( 10178 ),
    HardwareTimedSinglePoint( 12522 );
    
    private int v;

    SampleQuantityMode(int v) {
		this.v = v;
	}

	public int getValue() {
		return v;
	}
}
