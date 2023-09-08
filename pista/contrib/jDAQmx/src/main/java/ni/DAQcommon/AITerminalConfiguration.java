package ni.DAQcommon;

public enum AITerminalConfiguration {
		DEFAULT( -1 ),
        Nrse( 10078),
        Rse( 10083),
        Differential( 10106 ),
        Pseudodifferential(12529);
        
    	private int v;

    	AITerminalConfiguration(int v) {
    		this.v = v;
    	}
    	
    	public int getValue() { return v; }
}
