package idea.chart;

import java.awt.Color;

class WaveformData {
	protected String loc;
	protected Color color;
	protected double freq;
	private int style;

	private double secWidth = 6;

	double lastX;
	double lastY;
	private String code;

	// IntSignalBuffer buffer;

	public WaveformData(String code, String loc, Color color, double freq, int style) {
		this.code = code;
		this.loc = loc;
		this.color = color;
		this.freq = freq;
		this.style = style;
	}

	public Color getColor() {
		return color;
	}

	public void setColor(Color color) {
		this.color = color;
	}

	public String getLoc() {
		return loc;
	}

	public int getStyle() {
		return style;
	}

	public void setSecWidth(double secWidth) {
		this.secWidth = secWidth;
	}

	public double getSecWidth() {
		return secWidth;
	}

	public String getCode() {
		return code;
	}

	// public void addData( int [] values ) {
	// buffer.addData( values );
	// }
}
