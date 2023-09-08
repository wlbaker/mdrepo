package idea.model;

import idea.display.BandLayout;
import idea.display.ParameterLayout;
import idea.message.StreamID;
import idea.schema.rp.RpMetric;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

import javax.persistence.Transient;

import lombok.Data;

@Data
public class DisplayConfig extends PersistentItem implements Serializable {

	@Override
	public RpMetric[] getMetrics() {
		return null;
	}

	@Transient
	private List<ParameterLayout> parameterBoxs;
	@Transient
	private short pbox1Pos;
	@Transient
	private short vertPboxes;
	@Transient
	private short opmode;
	@Transient
	private List<BandLayout> bands;
	private boolean leftLayout;

	public DisplayConfig() {
		super( StreamID.DISPLAY );
	}
	
	/*
	 * BAND: Utility routines
	 */
	@Transient
	public int getNumBands() {
		if( bands == null ) {
			return 0;
		}
		return bands.size();
	}

	public void addBand(BandLayout band) {
		if( bands == null ) {
			bands = new LinkedList<BandLayout>();
		}
		bands.add( band );
	}

	public BandLayout getBand(int i) {
		return bands.get(i);
	}

	/*
	 * PBOXES: Utility routines
	 */
	public int getNumPBoxes() {
		if( parameterBoxs == null ) {
			return 0;
		}
		return parameterBoxs.size();
	}

	public void clearPBoxes() {
		if( parameterBoxs != null ) {
			parameterBoxs.clear();
		}
	}

	public void addParamBox(ParameterLayout box) {
		if( parameterBoxs == null ) {
			parameterBoxs = new LinkedList<ParameterLayout>();
		}
		parameterBoxs.add( box );
		
	}

	public ParameterLayout getPBox(int idx) {
		if( parameterBoxs == null ) {
			return null;
		}
		if( idx >= parameterBoxs.size() ) {
			return null;
		}
		return parameterBoxs.get(idx);
	}

	public void setLeftLayout(boolean b) {
		this.leftLayout = b;
	}
	
	public boolean isLeftLayout( ) {
		return leftLayout;
	}
	
}
