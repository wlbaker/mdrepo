package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class RemoteOperationError {
	public final static short NO_SUCH_OBJECT_CLASS = 0;
	public final static short  NO_SUCH_OBJECT_INSTANCE = 1;
	public final static short  ACCESS_DENIED = 2;
	public final static short  GET_LIST_ERROR = 7;
	public final static short  SET_LIST_ERROR = 8;
	public final static short  NO_SUCH_ACTION = 9;
	public final static short  PROCESSING_FAILURE = 10;
	public final static short  INVALID_ARGUMENT_VALUE = 15;
	public final static short  INVALID_SCOPE = 16;
	public final static short  INVALID_OBJECT_INSTANCE = 17;

	public short invoke_id;
	public short error_value;
	private short length;
	
	private RemoteOperationError() {
		
	}
	
	public static RemoteOperationError parse(ByteBuffer bb) {
		
		RemoteOperationError roer = new RemoteOperationError();
		roer.invoke_id = bb.getShort();
		roer.error_value = bb.getShort();
		roer.length = bb.getShort();
			
		return roer;
	}

}
