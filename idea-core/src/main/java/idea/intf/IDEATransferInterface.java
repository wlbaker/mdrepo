package idea.intf;

import java.io.IOException;

/*
 * FIXME: Merge with PiSubjectImporter
 */

public interface IDEATransferInterface extends StreamProducer {
	public void connect(  ) throws IOException;
	public void disconnect(  ) throws IOException;
	public int getRequestId();
}
