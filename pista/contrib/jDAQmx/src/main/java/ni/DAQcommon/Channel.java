package ni.DAQcommon;


public class Channel {
	
	private ChannelType typ;
	
	protected Channel( ChannelType typ ) {
		this.typ = typ;
	}
    public ChannelType getType() { return typ; }
	/*
    public string Description { get; set; }
    public bool IsGlobal { get; }
    public string PhysicalName { get; set; }
    public string VirtualName { get; }
    public override sealed void Dispose();
    protected virtual void Dispose(bool __p1);
	*/
}
