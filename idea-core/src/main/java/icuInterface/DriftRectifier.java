package icuInterface;

import lombok.Getter;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DriftRectifier {

	private int tolorence_ms;
	private int drift_increment;
	private long expected_tm;
	private int drift_allow;
	private int verbose;
	@Getter private boolean broken;

	public DriftRectifier(int tolorence_ms, int drift_allow, int drift_increment) {
		this.tolorence_ms = tolorence_ms;
		this.drift_allow = drift_allow;
		this.drift_increment = drift_increment;
	}

	public long getRectifiedTime(long new_tm) {

		long tm = expected_tm;
		long drift = new_tm - tm;

		long delta = 0;
		
		broken = false; 
		if (drift > drift_allow) {
			delta = (drift > drift_increment) ? drift_increment : drift;
		} else if (drift < -drift_allow) {
			delta = (drift < -drift_increment) ? -drift_increment : drift;
		}
		tm += delta;

		if (drift > tolorence_ms || drift < -tolorence_ms) { // allow up to a
			log.debug("DRIFT drift={} delta={}", drift, delta);
			drift = new_tm - expected_tm;
			// int idrift = (int) (new_tm - expected_tm);
			// log.warn(" int-delta: " + idrift);
			broken = true;
			tm = new_tm;
		}

		return tm;
	}

	public void setNextExpectedTime(long tm) {

		if (verbose > 0) {
			System.out.println("NEXT EXPECTED SET TO=" + tm);
		}

		expected_tm = tm;
	}

	public long getNextExpectedTime() {
		return expected_tm;
	}

}
