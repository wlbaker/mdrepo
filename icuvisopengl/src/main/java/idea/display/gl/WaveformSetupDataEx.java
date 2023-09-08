package idea.display.gl;

import java.awt.Color;

import idea.display.DisplayUtil;
import idea.display.WaveformData;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class WaveformSetupDataEx {

	
	private String code;

	private RpUnit unit;
	private WaveformData wave;
	
	public WaveformSetupDataEx(WaveformData wave, RpUnit unit ) {

		this.wave = wave;
		this.unit = unit;
	}

	public RpUnit getUnit() {
		return unit;
	}
	
	public Color getColor() {
		return DisplayUtil.getColorFromDrager( wave.getWaveColor() );
	}
	
	public String getLoc() {
		return wave.getLoc();
	}

	public double getRangeMin() {
		return wave.getRangeMin();
	}

	public double getRangeMax() {
		return wave.getRangeMax();
	}

	public String getCode() {
		if( code == null ) {
			return wave.getLoc();
		}
		return code;
	}

	public void setCode(String code) {
		this.code = code;
	}

	public void setUnit(RpUnit unit) {
		this.unit = unit;
	}

	public WaveformData getWave() {
		return wave;
	}

}
