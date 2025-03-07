package idea;

import icuInterface.RpUtil;
import icuInterface.adapters.MrClockDriver;
import idea.display.BandLayout;
import idea.display.DisplayUtil;
import idea.display.FieldData;
import idea.display.ParameterLayout;
import idea.display.WaveformData;
import idea.display.editor.DisplayEditorManager;
import idea.display.elegant.ElegantDisplayForm;
import idea.driver.AlphaDisplay;
import idea.driver.InfinityDriver;
import idea.driver.IntellivueSerialDriver;
import idea.driver.NullDevice;
import idea.driver.intellivue.IntellivueDriver;
import idea.intf.AdapterInterface;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.DisplayConfig;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpDisplay;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

import javax.swing.JPanel;
import jakarta.xml.bind.JAXBException;

import org.pistax.PistaAdapter;

import lombok.extern.slf4j.Slf4j;
import idea.adapters.gui.BardUrimeterPanel;
import idea.adapters.gui.CCOPanel;
import idea.adapters.gui.CovidienKangarooEPumpPanel;
import idea.adapters.gui.EvitaModeIndicationPanel;
import idea.adapters.gui.InfusionPanel;
import idea.adapters.gui.ManualEntryPanel;
import idea.adapters.gui.MultiChannelInfusionPump;
import idea.adapters.gui.VentilatorPanel;
import idea.display.gl.GLInstrumentDisplay;
import idea.meddaq.AppSetup;
import idea.repository.io.LocalJAXBRepository;

@Slf4j
public class AdapterGui {
	public static Component buildDevicePanel(StreamProducer driver, RpDevice conf) throws JAXBException, IOException {
		String modelName = conf.getModelName();

		// this happens for the IDEA sub-devices
		Class<? extends StreamProducer> cl = null;
		String cl_name = conf.getDeviceClass();

		if (cl_name != null) {
			try {
				cl = (Class<? extends AdapterInterface>) Class.forName(cl_name);
			} catch (ClassNotFoundException e) {
				// ignore...stick with NullDeviceClass
				System.err.println("Requested class not identified: " + cl_name);
			}
		}

		if (cl == null && driver != null) {
			cl = driver.getClass();
		}

		boolean create_display = true;

		Component form = null;
		String name = cl.getName();
		
		// if (name.endsWith("InfinityDriver")) {
		// InputStream stream =
		// cl.getClassLoader().getResourceAsStream("idea/resources/default_deltaDisplay.xml");
		// if (stream != null && stream.available() > 0) {
		// RpDisplay rp_display =
		// LocalJAXBRepository.createDisplayFromStream(stream);
		//
		// DisplayConfig display = RpUtil.parseDisplay(rp_display);
		// form = new DragerMonitorForm(driver, display);
		// } else
		if (name.equals("BardUrimeter")) {
			form = new BardUrimeterPanel(driver, conf);
		} else if (name.equals("KangarooDriver")) {
			form = new CovidienKangarooEPumpPanel(driver, conf);
		} else if (name.equals("AS50Driver")) {
			form = new InfusionPanel(driver, conf);
			// } else if (name.equals("C2Driver")) {
			// form = new InfusionPanel(driver, conf);
		} else if (name.equals("BodyGuardDriver")) {
			form = new InfusionPanel(driver, conf);
		} else if (name.equals("PlumADataportDriver")) {
			form = new MultiChannelInfusionPump(driver, conf, 3);
		} else if (name.equals("PlumAPlusEthDriver")) {
			// form = new PlumAPanel(driver, conf);
			form = new MultiChannelInfusionPump(driver, conf, 3);
		} else if (driver instanceof NullDevice) {
			form = new ManualEntryPanel(driver);
		} else if (driver instanceof AlphaDisplay) {
			form = null; // no display for this one
			create_display = false;
		} else if (driver instanceof MrClockDriver) {
			form = null; // no display for this one
			create_display = false;
		} else if (name.equals("icuInterface.adapters.V500Driver")) {
			form = new VentilatorPanel(driver, conf);
		} else if (PistaAdapter.class.isAssignableFrom(cl) ) {
			DisplayConfig display = buildDefaultDisplay(conf);
			GLInstrumentDisplay gl_form = new GLInstrumentDisplay( driver, display );
			// DisplayConfigForm dform = new DisplayConfigForm(driver, d);
			// form = new Impact731Panel(driver, conf);
			form = new DisplayEditorManager( gl_form );

		} else if (IntellivueDriver.class.isAssignableFrom(cl) || IntellivueSerialDriver.class.isAssignableFrom(cl)) {

			ElegantDisplayForm dform = new ElegantDisplayForm(driver, null);
			Double minRange = 100.0;
			dform.setScaleMinimumRange(minRange); // fix problem with
													// scale-out-too-far
			form = dform;

			JPanel panel = new EvitaModeIndicationPanel();
			dform.addContentPane(panel, BorderLayout.NORTH);

			String[][] displayInfo = { { "[DBG]", "idea/resources/default_mp2ABPOnly.xml" }, //
					{ "[ABP]", "idea/resources/default_mp2ABP.xml" }, //
					{ "[ECG]", "idea/resources/default_mp5Display.xml" }, //
					{ "MP2", "idea/resources/default_mp2Display.xml" }, //
					{ "MP5", "idea/resources/default_mp5Display.xml" }, //
					{ "MP70", "idea/resources/default_mp70Display.xml" } //
			};

			for (String[] info : displayInfo) {
				String displayName = info[0];
				String displayFile = info[1];
				InputStream stream = cl.getClassLoader().getResourceAsStream(displayFile);

				if (stream != null && stream.available() > 0) {
					RpDisplay rp_display = LocalJAXBRepository.createDisplayFromStream(stream);

					DisplayConfig display = RpUtil.parseDisplay(rp_display);
					// dform.addDisplay(displayName, display);
					dform.setDisplay(display);
					
					GuiUtil.showMessage("FIXME: only one display layout supported in this version");
					break;
				}
			}

		} else if (name.endsWith("EvitaDriver") || name.endsWith("V500Driver")) {
			InputStream stream = cl.getClassLoader().getResourceAsStream("idea/resources/default_evitaDisplay.xml");
			if (stream != null && stream.available() > 0) {
				RpDisplay rp_display = LocalJAXBRepository.createDisplayFromStream(stream);

				DisplayConfig display = RpUtil.parseDisplay(rp_display);
				
				// ATTEMPT to try the opengl display instead of the elegant display
				// ElegantDisplayForm dform = new ElegantDisplayForm(driver, display);
				// Double minRange = 100.0;
				// dform.setScaleMinimumRange(minRange); // fix problem with scale-out-too-far
				// JPanel panel = new EvitaModeIndicationPanel();
				// dform.addContentPane(panel, BorderLayout.NORTH);
				GLInstrumentDisplay gl_form = new GLInstrumentDisplay( driver, display );
				form = new DisplayEditorManager( gl_form );

			} else {
				form = new VentilatorPanel(driver, conf);
			}

		} else if ("AS50".equals(modelName)) {
			form = new InfusionPanel(driver, conf);
		} else if ("PC-2TX".equals(modelName)) {
			form = new InfusionPanel(driver, conf);
		} else if ("DeltaXL".equals(modelName)) { // duplicate!
			form = new ElegantDisplayForm(driver, null );
		} else if (name.endsWith("IFMoutDriver") && "EV1000".equals(modelName)) {
			// dont have an EV1000 display at the moment
		} else if (name.endsWith("IFMoutDriver")) {
			form = new CCOPanel(driver, conf);
		} else if (name.endsWith("IFMoutDriver")) { // UNUSED...ALTERNATE

			InputStream stream = cl.getClassLoader()
					.getResourceAsStream("idea/resources/default_vigilanceDisplay.xml");
			if (stream != null && stream.available() > 0) {
				RpDisplay rp_display = LocalJAXBRepository.createDisplayFromStream(stream);

				DisplayConfig display = RpUtil.parseDisplay(rp_display);
				ElegantDisplayForm dform = new ElegantDisplayForm(driver, display);
				Double minRange = 100.0;
				dform.setScaleMinimumRange(minRange); // fix problem with
														// scale-out-too-far
				form = dform;
			}
		} else if (name.equals("SentecSerDriver") || name.equals("SentecEthDriver")) {
			InputStream stream = cl.getClassLoader().getResourceAsStream("idea/resources/default_sentecDisplay.xml");
			if (stream != null && stream.available() > 0) {
				RpDisplay rp_display = LocalJAXBRepository.createDisplayFromStream(stream);

				DisplayConfig display = RpUtil.parseDisplay(rp_display);
				display.setLeftLayout(true);
				
				ElegantDisplayForm dform = new ElegantDisplayForm(driver, display);
				Double minRange = 100.0;
				dform.setScaleMinimumRange(minRange); // fix problem with scale-out-too-far
				form = dform;
			}
		}

		if (form == null && create_display) {
			
			Object t = new GLInstrumentDisplay(conf);
			GLInstrumentDisplay gl_display = (GLInstrumentDisplay) t; 
			form= gl_display; // new DisplayEditorManager( gl_display );

			gl_display.setName( name );  // names are used for saving the display
			
			//
			// check for a default display form
			//
			
			File dir = AppSetup.getLocalStudyDir();
			String formName = gl_display.getName();
			formName += ".dsp";
			File displayFile = new File(dir, formName);

			
			DisplayConfig display = null;
			if ( displayFile.exists() ) {
				FileInputStream stream = new FileInputStream(displayFile );
				RpDisplay rp_display = LocalJAXBRepository.createDisplayFromStream(stream);

				display = RpUtil.parseDisplay(rp_display);
				gl_display.setDisplay( display, true, false );
			}
			
			if( display == null && driver instanceof InfinityDriver ) {
				// FIXME: a little hackish!
				display = ((InfinityDriver)driver).getDisplay();
				gl_display.setDisplay( display, true, false );
			}

			if( display == null ) {
				display = buildDefaultDisplay(conf);
				gl_display.setDisplay( display, false, false );
			}
			
		}
		return form;
	}


	private static DisplayConfig buildDefaultDisplay(RpDevice conf) {
		DisplayConfig display = new DisplayConfig();
		int tot_band_weight = 0;

		RpStream stream = RpUtil.getStream(conf, StreamID.WAVEFORM);
		if (stream != null) {
			List<RpMetric> waves = stream.getMetric();
			if (waves != null && waves.size() > 0 ) {
				int band_weight = 6 / waves.size();
				
				byte color = 1;
				for (RpMetric wave : waves) {
					WaveformData wf_setup = new WaveformData();
					wf_setup.setLoc(wave.getLocation());
					wf_setup.setRangeMin((short)-100);
					wf_setup.setRangeMax((short)100);
					wf_setup.setWaveColor( color++ );
					wf_setup.setWaveSampleRate((short)50);

					BandLayout band = new BandLayout((byte) 0, (byte) 0, null);
					band.addWaveform(wf_setup);
					band.setWeight( band_weight );
					tot_band_weight += band_weight;
					display.addBand(band);
				}
			}
		}
		
		stream = RpUtil.getStream(conf, StreamID.MEASUREMENT);
		display.setVertPboxes((short)0);
		if (stream != null) {

			List<RpMetric> metrics = stream.getMetric();

			if (metrics != null && metrics.size() > 0 ) {
				
				int vert_columns = 0;
				int param_rows = metrics.size() / 7;
				if( param_rows > 4 ) {
					vert_columns++;
				}
				if( param_rows > 2 ) {
					vert_columns++;
				}
				// consider multiple display columns
				display.setVertPboxes((short)(vert_columns * tot_band_weight) );
				for (RpMetric metric : metrics) {
					FieldData [] params = new FieldData[1];
					params[0] = new FieldData( metric.getLocation(), (byte)0);
					
					ParameterLayout box = new ParameterLayout((byte) 0, (byte) 0, (byte) 0, params);
					box.setForeground( 	DisplayUtil.getDragerFromColor(Color.WHITE ) );
					display.addParamBox(box);
				}
			}
		}
		return display;
	}


}
