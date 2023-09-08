package ni.DAQcommon;

public enum AOVoltageUnits {
	FromCustomScale(10065), Volts(10348), FromTeds(12516);

	private int v;

	AOVoltageUnits(int v) {
		this.v = v;
	}

	public int getValue() {
		return v;
	}

}
