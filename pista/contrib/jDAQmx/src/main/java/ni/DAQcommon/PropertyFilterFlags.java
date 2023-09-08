package ni.DAQcommon;

public enum PropertyFilterFlags {
	None( 0 ), Volatile( 1 );

	private int v;

	PropertyFilterFlags(int v) {
		this.v = v;
	}

	public int getValue() { return v; }
}
