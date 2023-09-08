package ni.DAQcommon;

public enum AOTerminalConfiguration {
		DEFAULT( -1 ),
        Nrse( 10078),
        Rse( 10083),
        Differential( 10106 ),
        Pseudodifferential(12529);
        
    	private int v;

    	AOTerminalConfiguration(int v) {
    		this.v = v;
    	}
    	
    	public int getValue() { return v; }
}
