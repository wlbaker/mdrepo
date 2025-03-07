package idea.tsoffline.persist;

import java.awt.Color;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.Date;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;

import javax.swing.JFrame;
import javax.swing.text.MutableAttributeSet;
import jakarta.xml.bind.JAXBContext;
import jakarta.xml.bind.JAXBElement;
import jakarta.xml.bind.Marshaller;
import jakarta.xml.bind.Unmarshaller;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.util.PAffineTransform;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.ts.ObjectFactory;
import idea.ts.TsFilter;
import idea.ts.TsoAnnotationEntryType;
import idea.ts.TsoAnnotationInfoType;
import idea.ts.TsoAttributeType;
import idea.ts.TsoCalibration;
import idea.ts.TsoDeviceType;
import idea.ts.TsoPhase;
import idea.ts.TsoPrefs;
import idea.ts.TsoSession;
import idea.ts.TsoSignalLayerType;
import idea.tsoffline.AppFrame;
import idea.tsoffline.ColorManager;
import idea.tsoffline.HPPathLayer;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.model.OfflineSignal;

@Slf4j
public class TsoSessionXMLUtil {

	// keys
	static ObjectFactory factory;
	static JAXBContext jaxbContext;

	static {
		try {
			factory = ObjectFactory.class.newInstance();
			jaxbContext = JAXBContext.newInstance("idea.ts");

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static TsoSession readSessionFile(File f_session) throws Exception {
		Unmarshaller marshaller = jaxbContext.createUnmarshaller();

		if (!f_session.exists()) {
			throw new FileNotFoundException(f_session.getPath());
		}
		FileInputStream fin = new FileInputStream(f_session);

		TsoSession session = null;
		try {
			// BUGFIX: the unmarshaller can take a File, but with a really messy
			// file name it will fail
			// to open the file. This one failed when the file name had a #
			// sign.

			// File name was: 6. HCM - (Smith-Watts)\BAMC Case #3961 repeated
			// HCM (R,E, hifi-fluid pullback, BB) TT-F DT-F\....xml

			JAXBElement<TsoSession> env = (JAXBElement<TsoSession>) marshaller.unmarshal(fin);
			session = (TsoSession) env.getValue();

			// apply one small fix to session file: normalize field loc's
			List<TsoDeviceType> devs = session.getTsoDevices();
			if (devs != null) {
				for (TsoDeviceType dev : devs) {
					List<TsoSignalLayerType> sigs = dev.getSignalLayer();
					if (sigs != null) {
						for (TsoSignalLayerType sig : sigs) {
							// FIXME: NORMALIZED FIELD NAMES
							// sig.setLoc(ModelUtil.normalizeFieldName(sig.getLoc()));
						}
					}
				}
			}
		} finally {
			fin.close();
		}
		return session;
	}

	public static void writeSessionFile(File f, TsoSession session) throws Exception {

		File parent = f.getParentFile();
		parent.mkdirs();

		Marshaller marshaller = jaxbContext.createMarshaller();

		marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, Boolean.TRUE);

		JAXBElement<TsoSession> out = factory.createTsosessionImpl(session);

		marshaller.marshal(out, f);
	}
	
	/**
	 * There are two data models in this application: the Picasso model and the Tso model.
	 * Picasso has no inherent serialization/deserialization capabilities.
	 * This routine converts from Picasso to Tso for serialization.
	 * 
	 * @param canvas
	 * @return
	 */

	public static TsoSession createSessionFromCanvas(TsPSwingCanvas canvas) {
		TsoSession session = new TsoSession();

		long startTime = canvas.getStartTime();
		long endTime = canvas.getStopTime();
		session.setDataStart(new Date(startTime));
		session.setDataEnd(new Date(endTime));

		canvas.getDisplayBands(session.getTsoBands());

		PLayer activeLayer = canvas.getActiveLayer();
		if (activeLayer != null) {
			session.setActiveSignal(activeLayer.getName());
		}

		PCamera cam = canvas.getSignalCamera();
		PAffineTransform vt = cam.getViewTransform();
		session.setXScale(vt.getScaleX());
		session.setXTranslate(vt.getTranslateX());

		/*
		 * save filter definitions
		 */
		List<TsFilter> dest = session.getTsoFilters();
		TsoPrefs prefs = AppFrame.getInstance().getPrefs();
		saveFilters(prefs.getFilters(), dest);

		/*
		 * save annotations
		 */
		List<TsoAnnotationInfoType> sessionAnnos = session.getTsoAnnotations();
		List<HPSplitableLayer> annos = canvas.getAnnotationModel();
		for (HPSplitableLayer info : annos) {
			TsoAnnotationInfoType tsoInfo = new TsoAnnotationInfoType();
			PLayer layer = info;
			tsoInfo.setLayerName(layer.getName());
			Color color = (Color) info.getPaint();
			tsoInfo.setColor( ColorManager.asBytes(color) );
			tsoInfo.setSource(info.getSource());
			tsoInfo.setVisible(layer.getVisible());

			tsoGetAttributes(layer, tsoInfo.getAttributes());

			List<TsoAnnotationEntryType> entries = tsoInfo.getAnnotationEntry();

			ListIterator<PNode> it = layer.getChildrenIterator();
			while (it != null && it.hasNext()) {
				PNode node = it.next();
				double delta_tm = node.getX();
				double y = node.getY();

				Object o = node.getAttribute("item");
				if (o == null) {
					log.error("NO ITEM ATTRIBUTE IN ANNOTAITON: {}/{}", layer.getName(), node);
				} else if (o instanceof TsoAnnotationEntryType) {
					String code = (String) node.getAttribute("txt");
					if (code == null) {
						code = "?";
					}

					long tm = startTime + (long) (1000 * delta_tm);

					TsoAnnotationEntryType entry = new TsoAnnotationEntryType(); // (TsoAnnotationEntryType) o;

					/*
					 * This is redundanty...copying information from the PNode that should have
					 * already been saved in the entry.
					 */
					Date date = new Date(tm);
					entry.setTm(date);
					entry.setOffset(delta_tm);
					entry.setValue(y);
					entry.setCode(code);

					tsoGetAttributes(node, entry.getAttributes());
					entries.add(entry);
				} else {
					log.error("INTERNAL ERROR: unknown item for annotation {}", o);
				}
			}
			sessionAnnos.add(tsoInfo);
		}

		/*
		 * save phase info
		 */
		List<TsoPhase> sessionPhases = session.getTsoPhases();
		PLayer phaseLayer = canvas.getPhaseLayer();
		if (phaseLayer != null) {
			ListIterator<PNode> it = phaseLayer.getChildrenIterator();
			while (it != null && it.hasNext()) {
				PNode node = it.next();
				long start_tm = startTime + (long) (1000 * node.getX() );
				long end_tm = start_tm + (long) (1000 * node.getWidth() );
				
				TsoPhase phase = new TsoPhase();
				phase.setName( node.getName() );
				phase.setStartTm(new Date(start_tm) );
				phase.setStopTm(new Date(end_tm) );
				phase.setColor( ColorManager.asBytes((Color)node.getPaint()) );
				sessionPhases.add(phase);
			}
		}

		/*
		 * save devices
		 */
		List<TsoDeviceType> tsoDevices = session.getTsoDevices();
		for (PCamera camera : canvas.getBandCameras()) {
			saveCamera(tsoDevices, camera);
		}
		saveCamera(tsoDevices, null); // save signals that are not displayed

		return session;
	}

	private static void tsoGetAttributes(PNode layer, List<TsoAttributeType> attrs) {
		Enumeration ee = layer.getClientPropertyKeysEnumeration();
		while (ee != null && ee.hasMoreElements()) {
			String key = (String) ee.nextElement();
			if ("txt".equals(key)) {
				continue; // ignore...save already
			} else if ("item".equals(key)) {
				continue; // ignore...save already
			} else if ("@filter".equals(key)) {
				log.error("Unexpected filter attribute");
				continue;
			} else if ("modified".equals(key)) {
				continue; // ignore...not modified after save!
			}

			if ("dev_name".equals(key)) {
				log.warn("ignoring dev_name attribute: {}/{}", layer.getName(), layer.getAttribute(key));
				continue; // ignoring...why? don't recall how dev_name is used.
			}
			if ("sig_name".equals(key)) {
				log.warn("ignoring sig_name attribute -- duplicate of loc?: {}/{}", layer.getName(),
						layer.getAttribute(key));
				continue; // ignoring...why? don't recall how dev_name is used.
			}
			if ("sig_loc".equals(key)) {
				log.warn("ignoring sig_loc attribute -- saved as loc: {}/{}", layer.getName(), layer.getAttribute(key));
				continue; // ignoring...why? don't recall how dev_name is used.
			}
			if ("sid_name".equals(key)) {
				log.warn("ignoring sig_name: {}/{}", layer.getName(), layer.getAttribute(key));
				continue; // ignoring...why? don't recall how dev_name is used.
			}
			if ("sig".equals(key)) {
				log.warn("ignoring sig attribute: {}/{}", layer.getName(), layer.getAttribute(key));
				continue; // ignoring...why? don't recall how dev_name is used.
			}
			if ("sid".equals(key)) {
				log.warn("ignoring sid attribute: {}/{}", layer.getName(), layer.getAttribute(key));
				continue; // ignoring...why? don't recall how dev_name is used.
			}

			TsoAttributeType t = new TsoAttributeType();
			t.setKey(key);
			Object v = layer.getAttribute(key);
			if (v instanceof OfflineSignal) {
				v = ((OfflineSignal) v).getAlias();
				t.setTyp("OfflineSignal");
			} else if (v instanceof String) {
				// no typ specified...String
			} else if (v instanceof Map) {
				t.setTyp("Map");
				Map<String, Object> map = (Map<String, Object>) v;
				List<TsoAttributeType> subattrs = t.getAttribute();
				tsoGetAttributes(subattrs, map);
				v = null;
			} else {
				t.setTyp(v.getClass().getSimpleName());
			}
			if (v != null) {
				t.setValue(v.toString());
			}
			attrs.add(t);
		}
	}

	private static void tsoGetAttributes(List<TsoAttributeType> subattrs, Map<String, Object> map) {
		for (String key : map.keySet()) {

			Object v = map.get(key);
			TsoAttributeType t = new TsoAttributeType();
			t.setKey(key);

			t.setTyp(v.getClass().getSimpleName());
			t.setValue(v.toString()); // works for either doubles or strings

			subattrs.add(t);
		}
	}

	protected static void saveFilters(List<TsFilter> src, List<TsFilter> dest) {

		while (dest.isEmpty() == false) {
			dest.remove(0);
		}

		if (src != null) {
			dest.addAll(src);
		}

	}

	protected static void saveCamera(List<TsoDeviceType> tsoDevices, PCamera bcamera) {
		List<PLayer> layers = null;
		Integer band_id = null;
		if (bcamera == null) {
		} else {
			layers = bcamera.getLayersReference();
			MutableAttributeSet props = bcamera.getClientProperties();
			band_id = (Integer) props.getAttribute(TsPSwingCanvas.BAND_ID);
		}

		Map<String, TsoDeviceType> map = new HashMap<String, TsoDeviceType>();
		if (layers != null) {

			for (PLayer layer : layers) {
				// layer is of type HPSplitableLayer
				HPSplitableLayer parent = (HPSplitableLayer)layer;
				
				log.error("FIXME: cycle through children for split layers!");
				HPPathLayer child = (HPPathLayer) layer.getChild(0);
				if( child == null ) {
					// phase layer...ignore...saved elsewhere
					continue;
				}
				// stored
				// in
				// background
				// load
				if (parent.getTyp() == TimeseriesType.TT_ANNOTATION) {
					log.error("INTERNAL ERROR: annotation signal...should not be here: {}", child.getName());
					continue;
				}

				String sigLoc = parent.getLocation();
				String sid = (String) layer.getAttribute("sid");

				// dev_name attribute stored in background load
				String devName = (String) layer.getAttribute("dev_name");
				if (parent.getTyp() == TimeseriesType.TT_FORMULA) {
					devName = "@Formula";
				}
				if (devName == null) {
					log.error("INTERNAL ERROR: No device name for signal {}", parent.getName());
					devName = "@Unknown";
				}
				TsoDeviceType dev = map.get(devName);
				if (dev == null) {
					dev = new TsoDeviceType();
					dev.setDeviceName(devName);
					tsoDevices.add(dev);
					map.put(devName, dev);
				}
				List<TsoSignalLayerType> signals = dev.getSignalLayer();
				TsoSignalLayerType tso_sig = new TsoSignalLayerType();
				tso_sig.setLoc(sigLoc);
				tso_sig.setBandId(band_id);

				tso_sig.setVisible(layer.getVisible());
				tso_sig.setName(parent.getName());

				tsoGetAttributes(layer, tso_sig.getAttributes());

				Color color = parent.getDefaultColor();
				if (color != null) {
					byte[] tso_color = new byte[3];
					tso_color[0] = (byte) color.getRed();
					tso_color[1] = (byte) color.getGreen();
					tso_color[2] = (byte) color.getBlue();
					tso_sig.setColor(tso_color);
				}

				tso_sig.setSidName(sid);

				TimeseriesType ttyp = parent.getTyp();
				tso_sig.setTtype(ttyp.toString());

				signals.add(tso_sig);

				saveCalibration(tso_sig, layer);
			}
		}

	}

	private static void saveCalibration(TsoSignalLayerType tso_sig, PLayer layer) {
		if (layer instanceof HPPathLayer) {
			saveCalibrationOneLayer(tso_sig, layer);
		} else {
			for (int i = 0; i < layer.getChildrenCount(); i++) {
				PLayer child = (PLayer) layer.getChild(i);
				saveCalibrationOneLayer(tso_sig, child);
			}
		}
	}

	private static void saveCalibrationOneLayer(TsoSignalLayerType tso_sig, PLayer layer) {
		PAffineTransform tran = layer.getTransformReference(false);
		if (tran == null || layer.getChildrenCount() == 0) {
			// nothing to save
			return;
		}
		double startx = layer.getChild(0).getX();
		double gain = tran.getScaleY();
		double shift = tran.getTranslateX();
		double offset = tran.getTranslateY();

		if (gain == 1 && shift == 0 && offset == 0) {
			// ignore
		} else {
			TsoCalibration calib = new TsoCalibration();
			calib.setStartTime((int) (1000 * startx));
			calib.setGain(gain);
			calib.setShift(shift);
			calib.setOffset(offset);
			tso_sig.getCalibration().add(calib);
		}
	}

	public static void saveXMLSession(File f_session, JFrame frame, TsPSwingCanvas canvas, String dataFile)
			throws Exception {

		String ori_name = f_session.getAbsolutePath();

		Path f_ori = f_session.toPath();

		Path f_backup = Paths.get(ori_name.substring(0, ori_name.lastIndexOf('.')) + ".xBAK");

		try {
			Files.deleteIfExists(f_backup);
			if (Files.exists(f_ori)) {
				Files.move(f_ori, f_backup, StandardCopyOption.REPLACE_EXISTING);
			}
		} catch (Exception e) {
			GuiUtil.showError("Could not save backup file: " + f_backup, e);
			return;
		}

		f_session = new File(ori_name);

		TsoSession session = TsoSessionXMLUtil.createSessionFromCanvas(canvas);
		session.setDataFile(dataFile);

		session.setFrameX( frame.getX() );
		session.setFrameY( frame.getY() );
		session.setFrameWidth( frame.getWidth() );
		session.setFrameHeight( frame.getHeight() );
		session.setFrameState(frame.getExtendedState());
		TsoSessionXMLUtil.writeSessionFile(f_session, session);

	}

}
