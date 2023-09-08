package icuInterface;

public class CommParams {
	private int baud;
	private int datab;
	private int stopb;
	private char parity;

	public CommParams( int baud, int datab, int stopb, char parity ) {
		this.baud = baud;
		this.datab = datab;
		this.stopb = stopb;
		this.parity = parity;
	}
}
