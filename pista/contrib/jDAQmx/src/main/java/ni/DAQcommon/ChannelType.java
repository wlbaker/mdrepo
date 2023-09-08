package ni.DAQcommon;

public enum ChannelType {
    AI( 10100 ), AO( 10102 ), CI( 10131),  CO( 10132 ), DI( 10151 ), DO( 10153);
    
	private int v;

	private ChannelType(int v) {
		this.v = v;
	}

	public int getValue() { return v; }

}
