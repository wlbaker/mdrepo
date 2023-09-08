package idea.display;

import java.awt.Color;
import java.awt.Stroke;
import java.awt.geom.AffineTransform;

import icuInterface.UnitUtil;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

public @Slf4j
class StripSetup {
	boolean did_autoscale = false;
	boolean do_autoscale = true;
	private boolean show_current_value = true;
	private int AUTOSCALE_PTS = 500;

	protected Color color;
	protected double freq;

	// remember the drawing position for this wave
	private int x;
	private double y;

	private AffineTransform trans;

	private double[] autoscale_data;
	private int autoscale_pos = 0;

	private Double scale_min_y;
	private Double scale_max_y;
	private Double scale_min_range;

	private RpMetric desc;

	private boolean verbose = false;
	private Stroke stroke;
	private double sys;
	private double dia;

	public StripSetup(RpMetric desc2, Color color, double freq, double scale1, double scale2) {
		this.desc = desc2;
		this.color = color;
		this.freq = freq;

		this.scale_min_y = scale1;
		this.scale_max_y = scale2;

		AUTOSCALE_PTS = (int) (5 * freq); // appx 5 secs of data

		if( AUTOSCALE_PTS < 200 ) {
			AUTOSCALE_PTS = 200;
			log.error("FREQ == 0 not expected: {}", desc2 );
		}
		autoscale_data = new double[AUTOSCALE_PTS];
	}

	public void setScaleMinimumRange(Double range) {
		this.scale_min_range = range;
	}

	public Color getColor() {
		return color;
	}
	
	public boolean showCurrentValue() {
		return show_current_value;
	}
	
	public double getSysValue() {
		return sys;
	}
	
	public double getDiaValue() {
		return dia;
	}
	
	public double getCurrentValue() {
		double t = 0;
		sys = dia = autoscale_data[0];
		for( double v : autoscale_data ) {
			t += v;
			if( v < dia ) {
				dia = v;
			}
			if( v > sys ) {
				sys = v;
			}
		}
		double v = t / AUTOSCALE_PTS;
		if( desc != null ) {
			RpUnit unit = desc.getUnit();
			if( unit != null ) {
				v = UnitUtil.getValue(unit, v );
				dia = UnitUtil.getValue(unit, dia );
				sys = UnitUtil.getValue(unit,sys);
			}
		}
		return v;
	}

	public void setColor(Color color) {
		this.color = color;
	}

	public Object getLoc() {
		return desc.getLocation();
	}

	public void setInitialX(int x) {
		this.x = x;
	}

	public void setInitialY(double y) {
		this.y = y;
	}

	public int getInitialX() {
		return x;
	}

	public double getInitialY() {
		return y;
	}

	// public void addData( int [] values ) {
	// buffer.addData( values );
	// }
	public void autoScale(int h) {
		double as_min = Double.MAX_VALUE;
		double as_max = -Double.MAX_VALUE;
		for (double d : autoscale_data) {
			if (d > as_max) {
				as_max = d;
			}
			if (d < as_min) {
				as_min = d;
			}

		}

		double range = as_max - as_min;
		if (scale_min_range != null) {
			if (range < scale_min_range) {
				double halfRange = (scale_min_range - range) / 2.0;
				as_max += halfRange;
				as_min -= halfRange;
			}
		} else {

			if (range == 0.0)
				range = 1.0;
			as_max += 0.1 * range;
			as_min -= 0.1 * range;
		}

		if (scale_min_y != null) {
			if (as_min > scale_min_y) {
				as_min = scale_min_y;
			}
		}
		if (scale_max_y != null) {
			if (as_max < scale_max_y) {
				as_max = scale_max_y;
			}
		}

		boolean flip = true;
		if (flip) {
			double t = as_min;
			as_min = as_max;
			as_max = t;
		}

		// if (scale_min_y == null) {
		scale_min_y = as_min;
		scale_max_y = as_max;
		// }

		if (verbose) {
			log.debug("autoscaled: {} --> {}", scale_min_y, scale_max_y);
		}

		resetTrans();
	}

	public AffineTransform makeTrans(int bufferMs, int w, int h, double freq) {
		double pts = 2 * bufferMs * freq / 1000;
		double m00, m10, m01, m11, m02, m12;

		m00 = w / pts;
		m10 = 0.0;
		m01 = 0.0;
		m02 = 0.0;
		if (scale_max_y == null || scale_min_y == null) {
			m11 = 1;
			m12 = 0.0;
		} else {
			m11 = h / (scale_max_y - scale_min_y);
			m12 = -scale_min_y * m11;
		}
		// m12 = 50;
		AffineTransform trans = new AffineTransform(m00, m10, m01, m11, m02, m12);

		if (verbose) {
			log.debug("made trans w/scale={} to {} for " + desc, scale_min_y);
		}
		return trans;
	}

	public void resetTrans() {
		trans = null;
	}

	public AffineTransform getTrans(int visibleMs, int w, int h) {
		if (trans == null) {
			if (visibleMs < 1000) {
				log.error("resetting invalid visible time: {}", visibleMs);
				visibleMs = 10000;
			}
			trans = makeTrans(visibleMs, w, h, freq);

			if (log.isDebugEnabled()) {
				log.debug("makeTrans: " + visibleMs + " w:" + w + " h:" + h + " freq:" + freq + " trans=" + trans);
			}
		}

		return trans;
	}

	public void addAutoscaleData(int h, double d) {
		autoscale_data[autoscale_pos++] = d;
		autoscale_pos %= AUTOSCALE_PTS;

		if (autoscale_pos == 0) {
			if (did_autoscale == false) { // scale_max_y == null || scale_min_y
				// == null || scale_min_y ==
				// scale_max_y) {
				if (do_autoscale) {
					autoScale(h);
				}
				did_autoscale = true;
			}
		}
	}

	public double getScaleMin() {
		return scale_min_y;
	}

	public double getScaleMax() {
		return scale_max_y;
	}

	public String getCode() {
		return desc.getCode();
	}

	public double getFreq() {
		return freq;
	}

	public RpMetric getDescription() {
		return desc;
	}

	public void enableAutoscale(boolean b) {
		do_autoscale = b;
	}

	public Stroke getStroke() {
		return stroke;
	}

	public void setStroke(Stroke stroke) {
		this.stroke = stroke;
	}

}

