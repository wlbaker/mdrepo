package ni.DAQcommon;

public enum PropertyFilterType {
	All(0), ConfiguredDevices(1), DevicesInTask(2);

	private int v;

	PropertyFilterType(int v) {
		this.v = v;
	}
	
	public int getValue() { return v; }
}
