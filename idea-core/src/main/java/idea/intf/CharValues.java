package idea.intf;

/**
 * 
 */
public enum CharValues {
	NUL(0), SOH(1), STX(2), ETX(3), EOT(4), ENQ(5), ACK(6), LF(10), CR(13), NAK(21), ETB(23), QUOTE(34), ESC(27), SUB(26);

	private final int value;

	private CharValues(int value) {
		this.value = value;
	}

	public int getValue() {
		return value;
	}
	
	public byte get() {
		return (byte)value;
	}

	public char getChar() {
		return (char) value;
	}

}

