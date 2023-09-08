package idea.display;

import lombok.Data;

@Data
public class WaveformData {
	public static byte LINE_STYLE = 0;
	public static byte PHASE_STYLE = 1;  // x = amplitude, y= d(amplitude)/dt
	
	private short sweepSpeed;
	private short waveSampleRate;
	private short rangeMin;
	private short rangeMax;
	private byte signalGroup;
	private byte signalId;
	private byte waveColor;
	private byte scaleDescriptor;
	public byte topOverlay;
	public byte bottomOverlay;
	private byte uom;
	private byte uomExp;
	public byte wlb_style;
	
	private String loc;

	public WaveformData() {
		this(null);
		wlb_style = LINE_STYLE;
	}
	
	public WaveformData(String loc) {
		this.loc = loc;
	}

}