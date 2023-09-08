package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class SaFixedValSpec16 implements Reportable {
	short sa_fixed_val_id;
	int sa_fixed_val;

	public static SaFixedValSpec16 parse(ByteBuffer bb) {
		SaFixedValSpec16 spec16 = new SaFixedValSpec16();

		spec16.sa_fixed_val_id = bb.getShort();
		spec16.sa_fixed_val = bb.getShort();
		if (spec16.sa_fixed_val < 0) {
			spec16.sa_fixed_val += 65536;
		}

		return spec16;
	}

	@Override
	public void dump() {
		System.out.println("  SaFixedValSpec16");
		System.out.println("       sa_fixed_val_id: " + sa_fixed_val_id);
		System.out.println("          sa_fixed_val: 0x" + Integer.toHexString(sa_fixed_val));
	}

	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return "spec(" + Integer.toHexString(sa_fixed_val_id) + " mask=" + Integer.toHexString(sa_fixed_val ) + ")" ;
	}
	

}
