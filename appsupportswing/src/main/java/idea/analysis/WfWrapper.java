package idea.analysis;

import idea.schema.rp.RpMetric;

public class WfWrapper {

	private RpMetric wave;

	public WfWrapper(RpMetric wave) {
		this.wave = wave;
	}

	public RpMetric getWave() {
		return wave;
	}

	@Override
	public String toString() {
		Integer rate = wave.getSampleRate();
		String typ;
		if( rate == null || rate == 0 ) {
			typ = "metric";
		} else {
			typ = "wf";
		}
		
		String name = wave.getName();
		if( name == null ) {
			name = wave.getCode();
		}
		if( name == null ) {
			Object loc = wave.getLocation();
			if( loc != null ) name = loc.toString();
		}
		return "[" + typ + "=" + name + "]";
	}
}
