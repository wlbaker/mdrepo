package ni.DAQcommon;

public enum SampleClockActiveEdge {
    Falling( 10171 ),
    Rising( 10280 );
    
    private int v;

    SampleClockActiveEdge(int v) {
		this.v = v;
	}

	public int getValue() {
		return v;
	}
}
