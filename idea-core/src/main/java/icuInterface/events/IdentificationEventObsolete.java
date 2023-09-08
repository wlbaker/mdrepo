package icuInterface.events;

import java.util.EventObject;

public class IdentificationEventObsolete extends EventObject {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String id;

	public IdentificationEventObsolete(Object source, String id) {
		super(source);
		this.id = id;

	}
	
	public String getId() {
		return id;		
	}

}
