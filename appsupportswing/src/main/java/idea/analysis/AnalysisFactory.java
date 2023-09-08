package idea.analysis;

import java.io.IOException;
import java.lang.reflect.Constructor;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JPanel;

import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStudy;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;

@Slf4j
public class AnalysisFactory {

	private static List<RpAnalysis> analyses = new LinkedList<RpAnalysis>();

	static {
		try {
		scanPkg("idea.analysis");
		} catch (Exception e ) {
			GuiUtil.showError("E: Could not scan idea.analysis", e);
		} catch (Throwable e ) {
			GuiUtil.showError("T: Could not scan idea.analysis", e);
		}
	}

	/*
	 * Build the analysis setup panel.
	 * 
	 * If the class names ends in "Form" and it is not found, we will search for "Panel" as well.
	 */

	public static JPanel buildSetupPanel(String cl, RpStudy study, RpAnalysis anal) throws Exception {

		JPanel panel = null;
		
		if( cl == null ) {
			cl = anal.getAnalysisClass() + "SetupPanel";
			cl = cl.replace("PanelSetupPanel", "SetupPanel");
		}
		if( cl.equals("idea.analysis.EntropyFilterSetupPanel") ) {
			cl = "idea.analysis.DetectorSetupPanel";
		}
		if( cl.equals("idea.analysis.ECGBeatSegmentFilterSetupPanel") ) {
			cl = "idea.analysis.ECGSegmentationSetupPanel";
		}

		try {
			Class<?> clazz = Class.forName(cl);
			Constructor<?> mid = clazz.getConstructor(RpStudy.class, RpAnalysis.class);
			panel = (JPanel) mid.newInstance(study, anal);
		} catch (ClassNotFoundException e) {
			log.error("Setup class not found: {}", cl, e);
		} catch (Exception e) {
			log.error("could not build setup panel", e);
			throw e;
		}
		
		return panel;
	}

	public static JPanel buildSetupPanel(WizardMasterInterface wiz, String cl, RpStudy study, RpAnalysis anal) {

		JPanel panel = null;
		
		if( cl == null ) {
			cl = anal.getAnalysisClass() + "SetupPanel";
			cl = cl.replace("PanelSetupPanel", "SetupPanel");
		}
		if( cl.equals("idea.analysis.ECGBeatSegmentFilterSetupPanel") ) {
			cl = "idea.analysis.ECGSegmentationSetupPanel";
		}

		try {
			Class<?> clazz = Class.forName(cl);
			Constructor<?> mid = clazz.getConstructor(WizardMasterInterface.class, RpStudy.class, RpAnalysis.class);
			panel = (JPanel) mid.newInstance(wiz, study, anal);
		} catch (ClassNotFoundException e) {
			log.error("Setup class not found: {}", cl, e);
		} catch (Exception e) {
			log.error("could not build setup panel", e);
		}
		return panel;
	}

	/*
	 * FIXME: buildAnalysisProducer may be a misnomer.  It is very unrelated to the 
	 * buildAnalysisPanel below.
	 */
	public static StreamProducer buildAnalysisProducer(String cl, RpStudy study, RpAnalysis anal) {

		StreamProducer panel = null;
		
		if( cl == null ) {
			cl = anal.getAnalysisClass();
		}

		try {
			Class<?> clazz = Class.forName(cl);
			Constructor<?> mid = clazz.getConstructor( RpAnalysis.class);
			panel = (StreamProducer) mid.newInstance(anal);
		} catch (ClassNotFoundException e) {
			log.error("Could not build analysis producer: {}", cl, e);
		} catch (Exception e) {
			log.error("could not build analysis producer", e);
		}
		return panel;
	}

	/*
	 * The archiver is automatically added as a listener to any created drivers.  Archiver can be null.
	 */
	public static AnalysisPanelInterface buildAnalysisPanel(StreamConsumer anal_consumer, RpAnalysis anal, StreamProducer[] drivers)
			throws Exception {

		Object p = null;
		String name = anal.getName();

		String cls = anal.getAnalysisClass();
		
		// COMPAT: fixme, need to handle this in the import procedure
		if( "idea.analysis.ProtocolDataPanel".equals(cls)) {
			cls = "idea.mg_daq.entry.StudypointEntryPanel";
		}
		if( "idea.analysis.EntropyFilter".equals(cls)) {
			cls = "idea.analysis.EntropyAnalysis2Panel";
		}

		StreamProducer[] producers = null;

		Class<?> clazz = Class.forName(cls);
		Class<?> cl_drivers = StreamProducer[].class;
		Constructor<?> mid = clazz.getConstructor(cl_drivers, RpAnalysis.class);
		p = mid.newInstance(drivers, anal);

		if (p instanceof AnalysisPanelInterface) {
			producers = ((AnalysisPanelInterface) p).getSignalProducers();
		}

		if (producers == null && p instanceof StreamProducer) {
			producers = new StreamProducer[] { (StreamProducer) p };
		}

		if (producers != null && anal_consumer != null) {
			for (StreamProducer producer : producers) {
				if (producer == null) {
					log.error("EMPTY PRODUCER IN LIST?");
					continue;
				}
				RpDevice conf = producer.getConfiguration();
				if (conf == null) {
					log.error("*** NO CONFIGURATION IN APP MODEL: {} ***", producer);
				} else {
					if (conf.getName() == null) {
						log.error("NO PRODUCER NAME FOR ANALYSIS: {}", producer);
					}

					producer.addStreamListener(null, anal_consumer);

				}
			}
		}

		JPanel panel = null;
		if (p == null) {
			// ignore
		} else if (p instanceof JPanel) {
			panel = (JPanel) p;
			panel.setName(name);
		}

		return (AnalysisPanelInterface) panel;
	}

	public static List<RpAnalysis> getAnalyses() {
		return analyses;
	}

	public static void registerAnalysis( RpAnalysis anal ) {
		analyses.add( anal );
	}
	
	private static void scanPkg(String pkgName) {
		ArrayList<Class<?>> clzzs;
		try {
			clzzs = PlatformUtil.getClassesForPackage(pkgName);
			for (Class<?> cl : clzzs) {
				RpAnalysis anal = RpUtil.getAnalysisInfo(cl);
				if (anal != null) {
					analyses.add(anal);
				}
			}
		} catch (IOException e) {
			log.error("could not load package resources: {}", pkgName);
		}
	}

}
