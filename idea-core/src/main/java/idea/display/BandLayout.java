package idea.display;

import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class BandLayout {
	private LinkedList<WaveformData> waves;
	private byte bandNumber;
	private byte bandAttribute;
	private int  weight;

	public BandLayout(byte b, byte c) {
		this( b, c, null);
	}

	public BandLayout( byte band_number, byte band_attribute, WaveformData[] wsd ) {
		this.setBandNumber(band_number);
		this.setBandAttribute( band_attribute );
		if( wsd != null ) {
			this.waves = new LinkedList<WaveformData>( Arrays.asList( wsd ) );
		}
	}

	public int getWaveCount() {
		if( waves == null ) {
			return 0;
		}
		return waves.size();
	}

	public WaveformData getWave(int i) {
		if( waves == null ) {
			return null;
		}
		if( i >= waves.size() ) {
			return null;
		}
		return waves.get(i);
	}

	public int getNumWaves() {
		if( waves == null ) {
			return 0;
		}
		return waves.size();
	}

	public void setWaves(int index, WaveformData wf ) {
		waves.set(index, wf);
	}

	public void addWaveform(WaveformData wf) {
		if( waves == null ) {
			waves = new LinkedList<WaveformData>();
		}
		waves.add(wf);
	}

	public WaveformData addWaveform(RpMetric m) {
		WaveformData wf = new WaveformData();
		wf.setLoc( m.getLocation() );
		wf.setWaveSampleRate( (short)(int) m.getSampleRate() );
		this.addWaveform( wf );
		return wf;
		
	}
	
	public void removeWaveform(String loc) {
		 Iterator<WaveformData> ii = waves.iterator();
		 while( ii.hasNext() ) {
			 WaveformData setup = ii.next();
			 if( loc.equals(setup.getLoc() ) ) {
				 ii.remove();
			 }
		 }
	}

	public WaveformData getWaveFromLoc(String loc) {
		 Iterator<WaveformData> ii = waves.iterator();
		 while( ii.hasNext() ) {
			 WaveformData setup = ii.next();
			 if( loc.equals(setup.getLoc() ) ) {
				 return setup;
			 }
		 }
		 
		 return null;
	}

	
}