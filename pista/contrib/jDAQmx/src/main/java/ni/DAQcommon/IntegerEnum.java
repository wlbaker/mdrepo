package ni.DAQcommon;

public enum IntegerEnum {
	;
	private int v;

	IntegerEnum(int v) {
		this.v = v;
	}
	
	public int getValue() { return v; }
}
