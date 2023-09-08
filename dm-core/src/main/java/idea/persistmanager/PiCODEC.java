package idea.persistmanager;

import java.io.IOException;
import java.nio.ByteBuffer;

import idea.model.PersistentItem;

public interface PiCODEC {
	void encode(PersistentItem item, ByteBuffer baos);
	PersistentItem decode(PersistentItem block, ByteBuffer bb) throws IOException;
}
