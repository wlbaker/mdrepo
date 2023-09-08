package idea.qrsdet;

import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

class DetectorDescription {

	private String key;
	private String descr;

	DetectorDescription(String key, String descr) {
		this.key = key;
		this.descr = descr;
	}

	public String getKey() {
		return key;
	}

	public String getDescr() {
		return descr;
	}
}

@Slf4j
public class DetectorFactory {

	private DetectorDescription[] detectorDescr = new DetectorDescription[] {
			new DetectorDescription("CAT", "CAT: Combined Adaptive Threshold"),
			new DetectorDescription("PT1", "PT1: PanTompkins 1"), //
			new DetectorDescription("PT2", "PT2: QRS2"), //
			new DetectorDescription("FB", "FB: Filter Banks"), //
			new DetectorDescription("FIXED", "FIXED: Fixed width evenly spaced"), //
			new DetectorDescription("CL", "CL: Curve Length"), //
			new DetectorDescription("MOBD", "MOBD: Multiplication of Backward Difference"), //
			new DetectorDescription("ONSET", "ONSET: Slope Sum Function") //
		};

	public static AbstractDetector createDetector(String detectorName, RpMetric desc) {
		AbstractDetector detector = null;

		int sampleRate = desc.getSampleRate();

		if ("CAT".equalsIgnoreCase(detectorName)) {
			detector = new DetectorCAT(sampleRate);
		} else if ("HT".equalsIgnoreCase(detectorName) || "PT1".equalsIgnoreCase(detectorName)) {
			detector = new DetectorPanTompkinsModified(sampleRate);
		} else if ("PT2".equalsIgnoreCase(detectorName)) {
			detector = new DetectorQrs2(sampleRate);
		} else if ("FB".equalsIgnoreCase(detectorName) || "ATNL".equalsIgnoreCase(detectorName)) {
			detector = new DetectorFilterBanksOnly(sampleRate);
		} else if ("CL".equalsIgnoreCase(detectorName) || "ZMJ".equalsIgnoreCase(detectorName)) {
			detector = new DetectorCurveLength(sampleRate);
		} else if ("MOBD".equalsIgnoreCase(detectorName)) {
			detector = new DetectorNonlinearMOBD(sampleRate);
		} else if ("EMD".equalsIgnoreCase(detectorName)) {
			detector = new DetectorNonlinearMOBD(sampleRate);
		} else if ("ONSET".equalsIgnoreCase(detectorName)) {
			detector = new DetectorABPOnset(sampleRate);
		} else if ("FIXED".equalsIgnoreCase(detectorName)) {
			detector = new DetectorFixedWidth(sampleRate);
		} else {
			log.error("DETECTOR PROBLEM: unknown detector: {}", detectorName);
		}

		if (desc != null) {
			detector.setSignalLoc(desc.getLocation());
		}
		return detector;
	}

	public DetectorDescription[] getDetectorDescr() {
		return detectorDescr;
	}

}
