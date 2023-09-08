package icuInterface.events;

import java.util.EventObject;

public class SecurityEventObsolete extends EventObject {

	private static final long serialVersionUID = 1519789946653270221L;
	private boolean accept;
	
	public SecurityEventObsolete(Object source, boolean accept ) {
		super(source);
		this.setLogin( accept );
	}

	public void setLogin(boolean accept) {
		this.accept = accept;
	}

	public boolean isAccept () {
		return accept;
	}

	@Override
	public String toString() {
		return "[Security: " + accept + "]";
	}
	

}