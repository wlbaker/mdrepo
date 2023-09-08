package idea.driver.intellivue;

import java.nio.ByteBuffer;


public class MdsCreateInfo {

	private ManagedObjectID mo;
	private AttributeList attribute_list;

	public static MdsCreateInfo parse(ByteBuffer bb) {
		MdsCreateInfo ci = new MdsCreateInfo();
		ci.mo = ManagedObjectID.parse(bb);
		ci.attribute_list = AttributeList.parse(bb);
		return ci;
	}

}
