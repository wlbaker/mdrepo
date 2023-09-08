package idea.repository.io;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.LinkedList;
import java.util.List;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.SAXException;

import idea.persistence.PiSubjectImporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpFile;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;
import idea.repository.RepositoryInterface;
import idea.repository.io.sax.DeviceSaxHandler;

@Slf4j
public class DeviceRepository implements RepositoryInterface {

	private String name;
	private String resource;

	public DeviceRepository(String name, String resource) {
		this.name = name;
		this.resource = resource;


	}

	private void load_resources() throws IOException, ParserConfigurationException, SAXException {
		if (resource.startsWith("classpath:")) {
			String resourcePath = resource.substring("classpath:".length());
			InputStream stream = getClass().getClassLoader().getResourceAsStream(resourcePath);
			if (stream != null && stream.available() > 0) {
				RpStudy study = parse_resources(stream);
			}
			log.error("FIXME: incomplete");
		} else {
			log.error("dont know how to handle this resource: " + resource);
		}

	}

	private static RpStudy parse_resources(InputStream in_stream) throws ParserConfigurationException, SAXException, IOException {
		SAXParserFactory factory = SAXParserFactory.newInstance();
		SAXParser saxParser = factory.newSAXParser();

		DeviceSaxHandler handler = new DeviceSaxHandler();

		saxParser.parse(in_stream, handler);

		return handler.study;
	}

	@Override
	public List<RpStudy> getStudyList(String status) throws Exception {
		LinkedList<RpStudy> studies = new LinkedList<RpStudy>();
		// studies.add(study);
		return studies;
	}

	@Override
	public boolean createStudy(RpStudy study) throws Exception {
		System.out.println("createStudy");
		return false;
	}

	

	@Override
	public void removeSession(String studyName, String sessionName) throws Exception {
		// TODO Auto-generated method stub

	}

	@Override
	public void getSessionInfo(String studyID, String sessionID) {
		// TODO Auto-generated method stub

	}

	@Override
	public File getRoot() {
		return null;
	}

	@Override
	public RpStudy getStudy(String studyName) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void removeStudy(RpStudy study) throws Exception {
		// TODO Auto-generated method stub

	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public List<String> getSessionList(String studyId, String subjectId) throws Exception {
		System.err.println("fixme: unimplemented getSessionList");
		return null;
	}

	@Override
	public List<RpSubject> getSubjectList(RpStudy study) {
		
		LinkedList<RpSubject> subjects = new LinkedList<RpSubject>();

		List<RpHardware> hws = study.getHardware();
		if (hws != null && hws.size() > 0) {
			RpHardware hw = hws.get(0);
			for (RpDevice device : hw.getDevices()) {
				RpSubject subject = new RpSubject();
				subject.setIdentifier(device.getName());
				subjects.add(subject);
			}
		}
		return subjects;
	}

	@Override
	public List<RpFile> getSessionFilesList(String studyId, String subjectId, String sessionId) {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public boolean createLink(File dest ) throws IOException {
		log.error("FIXME: createLink");
		throw new IOException("createLink: unimplemented");
		
		// return false;
	}

	@Override
	public List<PiSubjectImporter> getImporters(RpStudy study) {
		log.error("FIXME: connect to the device and get the study info");
		return null;
	}

	@Override
	public File createSession(RpSubject hd, String sessionName, String sessionDescription) throws Exception {
		log.error("FIXME: createSession");
		return null;
	}

}
