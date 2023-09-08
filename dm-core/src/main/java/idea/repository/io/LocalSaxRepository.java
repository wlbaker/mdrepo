package idea.repository.io;

import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import icuInterface.RpUtil;
import idea.message.StreamID;
import idea.persistence.PiSubjectImporter;
import idea.schema.rp.ObjectFactory;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpFile;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;
import mslinks.ShellLink;
import idea.repository.RepositoryInterface;

@Slf4j
class RpSaxHandler extends DefaultHandler {

	RpStudy study;
	LinkedList<String> stack = new LinkedList<String>();
	String element;
	RpHardware hw;
	RpDevice device;
	RpMetric metric;
	RpUnit unit;
	private static int verbose = 0;

	@Override
	public void startElement(String uri, String localName, String qName,
			Attributes attributes) throws SAXException {

		// String path = stack.peek();

		// if ("hardware".equals(path)) {
		// element = qName;
		// stack.push("hardware");
		// } else if ("devices".equals(path)) {
		// element = qName;
		// stack.push("devices");
		// } else {
		
		if( verbose  > 0 ) {
		System.out.println("push:" + qName );
		}
		
		element = qName;

		if (qName.equalsIgnoreCase("title")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("pi")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("startDate")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("name")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("modelName")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("deviceClass")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("connectionType")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("connectionValue")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("global")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("visible")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("location")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("unit")) {
			unit = getUnit(metric);
		} else if (qName.equalsIgnoreCase("m")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("b")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("subtyp")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("code")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("samples-per-packet")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("sample-rate")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("unitName")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("rp-study-impl")) {
			study = new RpStudy();
			element = null;
		} else if (qName.equalsIgnoreCase("hardware")) {
			hw = new RpHardware();
			study.getHardware().add(hw);
			stack.push(qName);
			element = null;
		} else if (qName.equalsIgnoreCase("devices")) {
			device = new RpDevice();
			hw.getDevices().add(device);
			stack.push(qName);
			element = null;
		} else if (qName.equalsIgnoreCase("metrics")) {
			metric = new RpMetric();
			RpUtil.addMetric( device, StreamID.MEASUREMENT, metric);
			stack.push(qName);
			element = null;
		} else if (qName.equalsIgnoreCase("settings")) {
			metric = new RpMetric();
			RpUtil.addMetric( device, StreamID.SETTINGS, metric);
			stack.push(qName);
			element = null;
		} else if (qName.equalsIgnoreCase("waveforms")) {
			metric = new RpMetric();
			metric.setSampleRate( new Integer(-1));
			metric.setSamplesPerPacket( new Integer(-1));
			RpUtil.addMetric( device, StreamID.WAVEFORM, metric);
			stack.push(qName);
			element = null;
		} else if (qName.equalsIgnoreCase("analysis")) {
			stack.push(qName);
			element = null;
		} else {
			log.warn("unknown qname: " + qName);
		}
		// }

	}

	@Override
	public void endElement(String uri, String localName, String qName)
			throws SAXException {

		if (qName.equalsIgnoreCase("title")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("pi")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("startDate")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("name")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("modelName")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("deviceClass")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("connectionType")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("connectionValue")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("global")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("visible")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("location")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("unit")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("m")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("b")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("subtyp")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("code")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("samples-per-packet")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("sample-rate")) {
			// valid...ignore
		} else if (qName.equalsIgnoreCase("hardware")) {
			stack.pop();
			hw = null;
			element = null;
		} else if (qName.equalsIgnoreCase("devices")) {
			stack.pop();
			device = null;
			element = null;
		} else if (qName.equalsIgnoreCase("metrics")) {
			stack.pop();
			metric = null;
			element = null;
		} else if (qName.equalsIgnoreCase("waveforms")) {
			stack.pop();
			metric = null;
			element = null;
		} else if (qName.equalsIgnoreCase("analysis")) {
			stack.pop();
			element = null;
		} else if (qName.equalsIgnoreCase("unitName") ) {
		} else if (qName.equalsIgnoreCase("value") ) {
		} else if (qName.equalsIgnoreCase("key") ) {
		} else if (qName.equalsIgnoreCase("param") ) {
		} else if (qName.equalsIgnoreCase("driverName") ) {
		} else if (qName.equalsIgnoreCase("protocol") ) {
		} else if (qName.equalsIgnoreCase("rp-repository") ) {
		} else if (qName.equalsIgnoreCase("rp-study-impl") ) {
			//
		} else {
			log.warn("local-sas end element ignored: {}", qName);
		}

	}

	@Override
	public void characters(char ch[], int start, int length)
			throws SAXException {

		String path = stack.peek();

		String val = new String(ch, start, length);
		val = val.trim();
		if( val.length() == 0 ) {
			return;
		}

		if (element == null) {
			// this is ok...just means no data in current element
		} else if ("hardware".equals(path)) {
			if ("name".equals(element)) {
				hw.setName(val);
			} else {
				log.warn("unknown hw element: " + element);
			}
		} else if ("metrics".equals(path) || "waveforms".equals(path)) {
			if ("name".equals(element)) {
				metric.setName(val);
			} else if ("code".equals(element)) {
				metric.setCode(val);
			} else if ("location".equals(element)) {
				metric.setLocation(val);  // all locations are now assumed to be strings
			} else if ("unit".equals(element)) {
				unit.setUnitName( val );
			} else if ("unitName".equals(element)) {
				unit.setUnitName( val );
			} else if ("m".equals(element)) {
				((RpLinearUnit)unit).setM( Double.parseDouble(val) );
			} else if ("b".equals(element)) {
				((RpLinearUnit)unit).setB( Double.parseDouble(val) );
			} else if ("subtyp".equals(element)) {
				metric.setSubtyp( Integer.parseInt(val) );
			} else if ("sample-rate".equals(element)) {
				metric.setSampleRate(Integer.parseInt(val) );
			} else if ("samples-per-packet".equals(element)) {
				metric.setSamplesPerPacket(Integer.parseInt(val) );
			} else if ("visible".equals(element)) {
				log.warn("OBSOLETE metric element: {}", element);;
			} else if ("global".equals(element)) {
				log.warn("OBSOLETE metric element: {}", element);;
			} else {
				log.warn("unknown metric element: {}", element);
			}
		} else if ("devices".equals(path)) {
			if ("name".equals(element)) {
				device.setName(val);
			} else if ("modelName".equals(element)) {
				device.setModelName(val);
			} else if ("deviceClass".equals(element)) {
				device.setDeviceClass(val);
			} else if ("connectionType".equals(element)) {
				RpConnType typ = null;
				if ("RS_232".equals(val)) {
					typ = RpConnType.RS_232;
				} else if ("Ethernet".equalsIgnoreCase(val)) {
					typ = RpConnType.ETHERNET;
				} else if ("SEALINK".equalsIgnoreCase(val)) {
					log.error("SEALINK not implemented");
					typ = RpConnType.SEALINK;
				} else if ("DAQMX".equalsIgnoreCase(val)) {
					typ = RpConnType.DA_QMX;
				} else if ("PHIDGET".equalsIgnoreCase(val)) {
					typ = RpConnType.PHIDGET;
				} else {
					log.warn("unknown connection type for device: {}", val);
				}
				device.setConnectionType(typ);
			} else if ("connectionValue".equals(element)) {
				device.setConnectionValue(val);
			} else {
				log.warn("unknown devices element: {}", element);
			}
		} else if ("identifier".equals(element)) {
			// ignore
		} else if ("startDate".equals(element)) {
			// ignore
		} else if ("title".equals(element)) {
			study.setTitle(val);
		} else if ("pi".equals(element)) {
			study.setPi(val);
		} else {
			log.warn("(chars) ignoring element: {} val={}", element, val);
		}

	}

	private RpUnit getUnit(RpMetric metric) {
		RpLinearUnit unit = (RpLinearUnit) metric.getUnit();
		if( unit == null ) {
			unit = new RpLinearUnit();
			unit.setM( 1.0 );
			unit.setB( 0.0 );
			unit.setUnitName( "<?>");
			metric.setUnit(unit);
		}
		
		return unit;
	}
}

@Slf4j
public class LocalSaxRepository implements RepositoryInterface {

	static ObjectFactory factory;

	private File repositoryDir;

	private String name;

	static {
		try {
			factory = ObjectFactory.class.newInstance();

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public LocalSaxRepository(String name, File repositoryDir) {
		this.name = name;
		this.repositoryDir = repositoryDir;
	}

	public String getRepositoryDir() {
		return this.repositoryDir.getPath();
	}

	public void setRepositoryDir(String repositoryDir) {
		this.repositoryDir = new File(repositoryDir);
	}

	@Override
	public boolean createStudy(RpStudy study) throws Exception {

		File subf = new File(repositoryDir, study.getTitle());
		subf.mkdirs();
		File studyf = new File(subf, "study.xml");
		// Marshaller marshaller = jaxbContext.createMarshaller();
		// marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT,
		// Boolean.TRUE);
		//
		// JAXBElement<RpStudy> out = factory.createRpStudyImpl(study);
		//
		// marshaller.marshal(out, studyf);
		
		return true;
	}

	@Override
	public File createSession(RpSubject hd, String sessionName,
			String sessionDescription) {
		File studydir = new File(repositoryDir, hd.getStudyTitle());
		File sessiondir = new File(studydir, sessionName);

		sessiondir.mkdirs();

		return sessiondir;
	}

	@Override
	public File getRoot() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void getSessionInfo(String studyID, String sessionID) {
		// TODO Auto-generated method stub

	}

	@Override
	public List<RpStudy> getStudyList(String status) throws Exception {
		List<RpStudy> defs = null;

		if (repositoryDir.isDirectory()) {

			defs = new LinkedList<RpStudy>();
			String[] subs = repositoryDir.list();

			for (String sub : subs) {
				File subf = new File(repositoryDir, sub);
				if (subf.isDirectory()) {
					File studyf = new File(subf, "study.xml");
					if (studyf.canRead()) {
						RpStudy study = parseStudy(studyf);

						defs.add(study);
					}
				}
			}
		}

		return defs;
	}

	private RpStudy parseStudy(File studyf)
			throws ParserConfigurationException, SAXException, IOException {
		SAXParserFactory factory = SAXParserFactory.newInstance();
		SAXParser saxParser = factory.newSAXParser();

		RpSaxHandler handler = new RpSaxHandler();

		saxParser.parse(studyf, handler);

		return handler.study;
	}

	@Override
	public void removeSession(String studyName, String sessionName) {
		// TODO Auto-generated method stub

	}

	@Override
	public RpStudy getStudy(String studyName) throws Exception {
		RpStudy study = null;

		if (repositoryDir.isDirectory()) {

			File subf = new File(repositoryDir, studyName);

			if (subf.isDirectory()) {
				File studyf = new File(subf, "study.xml");
				if (studyf.canRead()) {
					study = parseStudy(studyf);
				} else {
					log.warn("Could not read study file: {}", studyf );
				}
				
			} else {
				log.warn("Could not find study directory: {}", subf );
			}
		} else {
			log.warn("Could not find directory: {}", repositoryDir );
		}

		return study;
	}

	@Override
	public void removeStudy(RpStudy study){
			throw (new NullPointerException("LocalSaxRepository: Unimplemented feature, use JAXB method"));
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public List<String> getSessionList(String studyId, String subjectId) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<RpSubject> getSubjectList(RpStudy study) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<RpFile> getSessionFilesList(String studyId, String subjectId, String sessionId) {
		// TODO Auto-generated method stub
		return null;
	}
	@Override
	public boolean createLink(File dest ) throws IOException {
		String name = dest.getName();
		File f = new File(repositoryDir, name + ".lnk");
		if( f.exists() ) {
			return false;
		}
		
		ShellLink link = ShellLink.createLink( dest.getPath() );
		link.saveTo( f.getPath() );
		
		return true;
	}

	@Override
	public List<PiSubjectImporter> getImporters(RpStudy study) {
		return null;
	}


}
