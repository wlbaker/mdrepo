package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class SystemSpecEntry implements Reportable {

	private short component_capab_id;
	private byte[] value;

	private SystemSpecEntry() {
	}

	public static SystemSpecEntry[] parseArray(ByteBuffer bb) {
		short count = bb.getShort();
		short len = bb.getShort();
		SystemSpecEntry[] specs = null;
		if (count > 0) {
			specs = new SystemSpecEntry[count];
			for (int i = 0; i < count; i++) {
				specs[i] = parse(bb);
			}
		}
		return specs;
	}

	private static SystemSpecEntry parse(ByteBuffer bb) {
		SystemSpecEntry spec = new SystemSpecEntry();
		spec.component_capab_id = bb.getShort();
		int len = bb.getShort();
		spec.value = new byte[len];
		bb.get(spec.value);
		return spec;
	}

	@Override
	public void dump() {
		System.out.println( "SystemSpecEntry");
		System.out.println(     "  component_capab_id=" + component_capab_id);
		if( value != null ) {
			String s = new String( value );
			System.out.println( "               value=" + s);
		};
	}

}
