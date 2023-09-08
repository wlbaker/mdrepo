package idea.display;

import java.util.Date;

import idea.intf.IDEAClient;
import idea.intf.StreamProducer;

public interface RefreshablePanel {

	public void refresh(IDEAClient idea, Date dt);
	public void update();
	public void clear();
	
	public void reset( StreamProducer driver );
}
