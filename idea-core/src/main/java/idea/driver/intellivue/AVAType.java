package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class AVAType {

	private short attribute_id;
	private Object value;

	public AVAType(short attribute_id, Object value) {
		this.attribute_id = attribute_id;
		this.value = value;
	}

	public ByteBuffer encode(ByteBuffer bb) {
		if (bb == null) {
			bb = ByteBuffer.allocate(sizeof());
		}
		bb.putShort(attribute_id);
		if (value == null) {
			bb.putShort((short) 0); //len);
		} else if (value instanceof Short) {
			bb.putShort((short) 2);
			bb.putShort((Short) value);
		} else if (value instanceof Integer) {
			bb.putShort((short) 4);
			bb.putInt((Integer) value);
		} else if (value instanceof ByteBuffer) {
			ByteBuffer data = (ByteBuffer) value;
			bb.putShort((short) data.remaining());
			bb.put(data);
			data.rewind();
		}

		return bb;
	}

	public short getAttributeId() {
		return attribute_id;
	}

	public short sizeof() {
		short siz = 4;
		if (value == null) {
		} else if (value instanceof Short) {
			siz += 2;
		} else if (value instanceof Integer) {
			siz += 4;
		} else if (value instanceof ByteBuffer ) {
			ByteBuffer data = (ByteBuffer)value;
			siz += data.remaining();
		}
		return siz;
	}

	public Object getValue() {
		return value;
	}

	@Override
	public String toString() {
		int a = attribute_id;
		if( a < 0 ) {
			 a += 0x10000;
		}
		String txt = "[AVA typ=0x" + Integer.toHexString(a) + " val=" + value + "]";
		return txt;
	}
	
	

}
