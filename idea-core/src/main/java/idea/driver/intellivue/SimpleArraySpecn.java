package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class SimpleArraySpecn implements Reportable {

	// typedef u_16 SaFlags;
	public static final short SMOOTH_CURVE =(short) 0x8000;
	public static final short DELAYED_CURVE =0x4000;
	public static final short STATIC_SCALE =0x2000;
	public static final short SA_EXT_VAL_RANGE =0x1000;
	
	private short array_size;
	private short sampleType_size;
	private short sampleType_bits;
	private int flags;
	
	public static SimpleArraySpecn parse(ByteBuffer bb) {
		SimpleArraySpecn specn = new SimpleArraySpecn();

		specn.array_size = bb.getShort();
		specn.sampleType_size = bb.get();
		specn.sampleType_bits = bb.get();
		specn.flags = bb.getShort();
		if( specn.flags < 0 ) {
			specn.flags += 0x10000;
		}

		return specn;
	}

	public short getArraySize() {
		return array_size;
	}

	@Override
	public void dump() {
		System.out.println( "Simple Array Specification");
		System.out.println("         array_size: " + array_size);
		System.out.println("    sampleType_size: " + sampleType_size);
		System.out.println("    sampleType_bits: 0x" + Integer.toHexString(sampleType_bits));
		System.out.println("              flags: 0x" + Integer.toHexString(flags));
	}

	public short getSignificantBits() {
		return sampleType_bits;
	}

}
