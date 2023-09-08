package ni.DAQcommon;

public enum TaskAction {
        Start( 0 ),
        Stop( 1 ),
        Verify( 2 ),
        Commit( 3 ),
        Reserve( 4 ),
        Unreserve( 5 ),
        Abort( 6 );
        
        private int v;

        TaskAction(int v) {
    		this.v = v;
    	}

    	public int getValue() {
    		return v;
    	}
}
