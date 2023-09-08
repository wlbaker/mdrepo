package idea.intf;


public interface MultiplexInterface {

	public StreamProducer [] getSubInterfaces( );
	public StreamProducer getSubInterface( String devName );
	public void setName(String string);
}
