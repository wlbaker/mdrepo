package idea.meddaq;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.prefs.BackingStoreException;
import java.util.prefs.Preferences;

import javax.swing.JPanel;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.TransformerFactoryConfigurationError;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.Text;
import org.xml.sax.SAXException;

import idea.schema.rp.RpSubject;
import idea.gui.wizard.SiteInfo;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;
import idea.repository.io.LocalJAXBRepository;

public class AppSetup {

	private static final String VER_ID = "Iriquois";
	// keys
	public static final String LOCAL_REPOSITORY_DIR = "repositoryDirIriquois";
	public static final String RMT_REPOSITORY_IP = "rmtRepositoryIPIriquois";
	public static final String RMT_REPOSITORY_USER = "rmtRepositoryUserIriquois";
	public static final String RMT_REPOSITORY_PWD = "rmtRepositoryPwIriquois";
	public static final String REPOSITORY_UPLOAD = "uploadIriquois";
	private static final String APP_KEY = "MGDAQ";
	public static final String SIMULATOR_FILE = "simulatorFileIriquois";
	public static final String ANALYSIS_FILE = "analysisFileIriquois";
	
	private static RpSubject header;
	private static boolean client;
	private static String persistanceRoot = null;

	/*
	 * getters
	 */
	public static String getLocalRepositoryDir() {
		return persistReadString(LOCAL_REPOSITORY_DIR, System.getProperty("user.home"));
	}

	public static String getRemoteRepositoryHost() {
		return persistReadString(RMT_REPOSITORY_IP, "www.softhorizons.com");
	}

	public static String getRemoteRepositoryUser() {
		return persistReadString(RMT_REPOSITORY_USER, "bbaker");
	}

	public static String getRemoteRepositoryPwd() {
		return persistReadString(RMT_REPOSITORY_PWD, "madmax");
	}

	public static boolean getAutoUpload() {
		String upload = persistReadString(REPOSITORY_UPLOAD, "false");
		return "true".equals(upload);
	}

	/*
	 * setters
	 */

	public static void setLocalRepositoryDir(String dir) throws BackingStoreException {
		persistWriteString(LOCAL_REPOSITORY_DIR, dir);
		RepositoryInterface local = RepositoryFactory.getLocalRepository();
		if (local instanceof LocalJAXBRepository) {
			LocalJAXBRepository r = (LocalJAXBRepository) local;
			r.setRepositoryDir(new File(AppSetup.getLocalRepositoryDir()) );
		}

	}

	public static void setRemoteRepositoryHost(String host) throws BackingStoreException {
		persistWriteString(RMT_REPOSITORY_IP, host);
	}

	public static void setRemoteRepositoryUser(String user) throws BackingStoreException {
		persistWriteString(RMT_REPOSITORY_USER, user);
	}

	public static void setRemoteRepositoryPwd(String password) throws BackingStoreException {
		persistWriteString(RMT_REPOSITORY_PWD, password);
	}

	public static void setAutoUpload(boolean upload) throws BackingStoreException {
		persistWriteString(REPOSITORY_UPLOAD, upload ? "true" : "false");
	}

	public static String getSimulatorFile() {
		return persistReadString(SIMULATOR_FILE, "");
	}

	public static void setSimulatorFile(String fileName ) throws BackingStoreException {
		persistWriteString(SIMULATOR_FILE, fileName);
	}
	public static String getAnalysisFile() {
		return persistReadString(ANALYSIS_FILE, "");
	}

	public static void setAnalysisFile(String fileName ) throws BackingStoreException {
		persistWriteString(ANALYSIS_FILE, fileName);
	}
	/*
	 * utility
	 * 
	 * YOU DON'T NEED THESE FUNCTIONS: USE PrefUtil()
	 */
	private static String persistReadString(String key, String def) {
		Preferences p = Preferences.userRoot();
		return p.get(APP_KEY + "/" + key, def);
	}

	/*
	 * YOU DON'T NEED THESE FUNCTIONS: USE PrefUtil()
	 */
	private static void persistWriteString(String key, String val) throws BackingStoreException {
		Preferences p = Preferences.userRoot();
		p.put(APP_KEY + "/" + key, val);
		p.flush();
	}

	public static SiteInfo readSiteInfo(String fileName) throws ParserConfigurationException, SAXException, IOException {
		SiteInfo siteInfo = new SiteInfo();
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();

		// Using factory get an instance of document builder
		DocumentBuilder db = dbf.newDocumentBuilder();

		// parse using builder to get DOM representation of the XML file
		Document dom = db.parse(fileName);

		Element docEle = dom.getDocumentElement();

		siteInfo.setCompany(getTextValue(docEle, "company"));
		siteInfo.setOrganization(getTextValue(docEle, "organization"));
		siteInfo.setLocation(getTextValue(docEle, "location"));

		return siteInfo;
	}

	private static String getTextValue(Element ele, String tagName) {
		String textVal = null;
		NodeList nl = ele.getElementsByTagName(tagName);
		if (nl != null && nl.getLength() > 0) {
			Element el = (Element) nl.item(0);
			textVal = el.getFirstChild().getNodeValue();
		}

		return textVal;
	}

	public static void saveSiteSetup(String fileName, SiteInfo siteInfo) throws IOException,
			ParserConfigurationException {
		// get an instance of factory
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();

		// get an instance of builder
		DocumentBuilder db = dbf.newDocumentBuilder();

		// create an instance of DOM
		Document dom = db.newDocument();

		// create the root element
		Element rootEle = dom.createElement("site");
		Node ele = createTextElement(dom, "company", siteInfo.getCompany());
		rootEle.appendChild(ele);

		ele = createTextElement(dom, "organization", siteInfo.getOrganization());
		rootEle.appendChild(ele);
		ele = createTextElement(dom, "location", siteInfo.getLocation());
		rootEle.appendChild(ele);
		dom.appendChild(rootEle);

		FileOutputStream fout = new FileOutputStream(new File(fileName));

		// output DOM XML to console 
        Transformer transformer;
		try {
			transformer = TransformerFactory.newInstance().newTransformer();
	        transformer.setOutputProperty(OutputKeys.INDENT, "yes"); 
	        DOMSource source = new DOMSource(dom);
	        StreamResult console = new StreamResult(fout);
	        transformer.transform(source, console);
		} catch (TransformerFactoryConfigurationError | TransformerException e) {
			throw new IOException(e);
		} finally {
			fout.close();
		}
	}

	private static Node createTextElement(Document dom, String key, String val) {

		Element keyEle = dom.createElement(key);
		Text valEle = dom.createTextNode(val);
		keyEle.appendChild(valEle);

		return keyEle;

	}

	public static JPanel getStudyQuestionaire(String studyDir) throws Exception {

		JPanel o;
		// Create a File object on the root of the directory containing the
		// class file
		File file = new File(studyDir);

		// Convert File to a URL
		URL url = file.toURL(); // file:/c:/myclasses/
		URL[] urls = new URL[] { url };

		// Create a new class loader with the directory
		ClassLoader cl = new URLClassLoader(urls);

		// Load in the class; MyClass.class should be located in
		// the directory file:/c:/myclasses/com/mycompany
		Class<?> cls = cl.loadClass("idea.study.BurnStudyPanel");

		Constructor<?> mid = cls.getConstructor();

		Object[] args = new Object[] {};
		o = (JPanel) mid.newInstance(args);

		return o; // kv;
	}

	public static void setRpSubject(RpSubject header) {
		AppSetup.header = header;
	}

	public static RpSubject getRpSubject() {
		return header;
	}

	public static File getLocalStudyDir() {
		String fn = header.getBaseFileName();
		if( fn == null ) {
			fn = header.getStudyTitle();
		}

		return new File( AppSetup.getLocalRepositoryDir(), fn );
	}
	public static File getLocalSubjectDir() {
		String subject = header.getMedicalId();
		if( subject == null ) {
			subject = "SUBJECT";
		}
		return new File( AppSetup.getLocalStudyDir(), subject ) ;
	}


	public static File getStudyDetailFileName() {
		return new File( AppSetup.getLocalSubjectDir(), "detail-" + header.getMedicalId() + ".xml");
	}

	public static void setClient(boolean b) {
		AppSetup.client = b;
	}

	public static boolean isClient() {
		return client;
	}

	public static Preferences getPreferences() {
		Preferences pref = null;

		if (persistanceRoot != null) {
			pref = Preferences.userRoot().node(persistanceRoot);
		} else {
			pref = Preferences.userRoot().node("global");
		}

		return pref;
	}

}
