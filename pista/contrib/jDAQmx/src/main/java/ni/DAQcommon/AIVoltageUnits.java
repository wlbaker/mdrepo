package ni.DAQcommon;

public enum AIVoltageUnits {
	FromCustomScale(10065), Volts(10348), FromTeds(12516);

	private int v;

	AIVoltageUnits(int v) {
		this.v = v;
	}

	public int getValue() {
		return v;
	}

}
