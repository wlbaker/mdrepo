package idea.repository.io;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.InputStream;
import java.util.GregorianCalendar;
import java.util.LinkedList;
import java.util.List;

import jakarta.xml.bind.JAXBContext;
import jakarta.xml.bind.JAXBElement;
import jakarta.xml.bind.JAXBException;
import jakarta.xml.bind.Marshaller;
import jakarta.xml.bind.Unmarshaller;

import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiImporterUtil;
import idea.schema.rp.ObjectFactory;
import idea.schema.rp.RpDisplay;
import idea.schema.rp.RpFile;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;
import mslinks.LinkInfo;
import mslinks.ShellLink;
import mslinks.data.CNRLink;
import idea.repository.DaqUtil;
import idea.repository.RepositoryInterface;

@Slf4j
public class LocalJAXBRepository implements RepositoryInterface {

	static ObjectFactory factory;
	static JAXBContext jaxbContext;

	private File repositoryDir;
	private String name;

	static {
		try {
			factory = ObjectFactory.class.newInstance();
			jaxbContext = JAXBContext.newInstance("idea.schema.rp");

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public LocalJAXBRepository(File repositoryDir) {
		this(null, repositoryDir);
	}

	public LocalJAXBRepository(String name, File repositoryDir) {
		this.name = name;
		this.repositoryDir = repositoryDir;
	}

	@Override
	public String getName() {
		return name;
	}

	public File getRepositoryDir() {
		return this.repositoryDir;
	}

	public void setRepositoryDir(File repositoryDir) {
		this.repositoryDir = repositoryDir;
	}

	@Override
	public boolean createStudy(RpStudy study) throws Exception {

		String id = study.getIdentifier();
		if (id == null) {
			id = study.getTitle();
			study.setIdentifier(id);
		}
		String link = study.getRepositoryLink();
		File studyf = null;
		if (link == null || link.length() == 0) {
			File f = repositoryDir;
			File subf = new File(f, id);
			if (!subf.exists()) {
				subf.mkdirs();
			}
			studyf = new File(subf, "study.xml");
		} else {
			studyf = new File(link, "study.xml");
		}

		Marshaller marshaller = jaxbContext.createMarshaller();
		marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, Boolean.TRUE);

		JAXBElement<RpStudy> out = factory.createRpStudyImpl(study);

		marshaller.marshal(out, studyf);

		return true;
	}

	@Override
	public File createSession(RpSubject hd, String sessionName, String sessionDescription) {
		File base = repositoryDir;
		File studydir = new File(base, hd.getStudyTitle());
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
	public List<RpSubject> getSubjectList(RpStudy study) {
		List<RpSubject> subjects = new LinkedList<RpSubject>();

		String studyDir = study.getRepositoryLink();
		File f = new File(studyDir); // this is inside the H5 file
		if (f.isDirectory()) {
			String[] subs = f.list();

			for (String sub : subs) {
				File subf = new File(f, sub);
				if (subf.isDirectory()) {

					RpSubject subject = readSubjectHeader(subf);
					if (subject == null) {
						subject = new RpSubject();
						subject.setBaseFileName(subf.getName());
					}
					subjects.add(subject);
				}
			}
		}

		return subjects;
	}

	private RpSubject readSubjectHeader(File subf) throws RuntimeException {
		RpSubject subject = null;
		File headerFile = new File(subf, "subject.xml");
		if (headerFile.exists()) {
			// then read it.
			log.error("FIXME: unimplemented handling for subject.xml");
		} else {
			// look for a guy drew style header file
			FilenameFilter filter = new FilenameFilter() {

				@Override
				public boolean accept(File dir, String name) {
					return name.endsWith("hdr");
				}
			};

			String[] hdrs = subf.list(filter);
			for (String hdr : hdrs) {
				if (hdr.indexOf('&') > 0) {
					// skip corina derived fragment recs 
					continue;
				}
				File file = new File(subf, hdr);
				try {
					subject = DaqUtil.readDaqHeader(file);
				} catch (IOException e) {
					throw new NullPointerException("cannot read daq header");
				}
			}
		}
		return subject;
	}

	@Override
	public List<String> getSessionList(String studyId, String subjectId) {
		List<String> defs = null;

		File f = repositoryDir; // this is inside the H5 file
		f = new File(f, studyId);
		f = new File(f, subjectId);
		if (f.isDirectory()) {
			defs = new LinkedList<String>();
			File[] subs = f.listFiles();

			for (File sub : subs) {
				if (sub.isDirectory()) {
					defs.add(sub.getName());
				} else {
					defs.add("File:" + sub.getName());
				}
			}
		}

		return defs;
	}

	@Override
	public List<RpStudy> getStudyList(String status) throws Exception {
		List<RpStudy> defs = null;

		File f = repositoryDir;
		if (f.isDirectory()) {
			Unmarshaller marshaller = jaxbContext.createUnmarshaller();

			defs = new LinkedList<RpStudy>();
			String[] subs = f.list();

			for (String sub : subs) {
				File original = new File(f, sub);
				File subf = original;
				boolean isLink = false;
				if (subf.isFile()) {
					isLink = subf.getPath().endsWith(".lnk");
					if (isLink) {
						ShellLink link = new ShellLink(subf);
						String lname = link.getName();
						LinkInfo linfo = link.getLinkInfo();
						String lbase = linfo.getLocalBasePath();
						if (lbase != null) {
							subf = new File(lbase);
						} else {
							CNRLink cnrlink = linfo.getCommonNetworkRelativeLink();
							String netName = cnrlink.getNetName();
							String suffix = linfo.getCommonPathSuffix();
							subf = new File(netName, suffix);
						}
					}
				}
				if (subf.isDirectory()) {
					File study_file = new File(subf, "study.xml");
					if (study_file.canRead()) {
						JAXBElement<RpStudy> env = (JAXBElement<RpStudy>) marshaller.unmarshal(study_file);
						RpStudy study = env.getValue();

						//study.setIdentifier(subf.getName());
						//study.setTitle(subf.getName());

						study.setRepositoryId(original.getPath());
						study.setRepositoryLink(subf.getPath());
						defs.add(study);
					} else {
						RpStudy study = new RpStudy();

						study.setIdentifier("AUTOID." + subf.getName());
						// study.setTitle("??: " + subf.getName());

						study.setRepositoryId(original.getPath());
						study.setRepositoryLink(subf.getPath());
						defs.add(study);
					}
				}
			}
		}

		return defs;
	}

	@Override
	public void removeSession(String studyName, String sessionName) {
		// TODO Auto-generated method stub

	}

	@Override
	public RpStudy getStudy(String studyName) throws Exception {
		RpStudy study = null;

		File f = repositoryDir;
		if (f.isDirectory()) {

			File subf = new File(f, studyName);
			if (subf.isDirectory()) {
				File studyf = new File(subf, "study.xml");
				study = createStudyFromFile(studyf);
			}
		}

		return study;
	}

	@Override
	public void removeStudy(RpStudy study) throws Exception {
		boolean ok = false;

		File file = new File(study.getRepositoryId());
		if (file.isDirectory()) {

			deleteDirectory(file);
			ok = true;
		} else if (file.getPath().endsWith("lnk")) {
			ok = file.delete(); // delete the link
		} else {
			ok = false;
		}

		if (ok == false) {
			throw (new Exception("Delete failed for study: " + study.getRepositoryId()));
		}

	}

	static private boolean deleteDirectory(File path) {
		if (path.exists()) {
			File[] files = path.listFiles();
			for (int i = 0; i < files.length; i++) {
				if (files[i].isDirectory()) {
					deleteDirectory(files[i]);
				} else {
					files[i].delete();
				}
			}
		}
		return (path.delete());
	}

	public static RpStudy createStudyFromStream(InputStream stream) throws JAXBException {
		Unmarshaller marshaller = jaxbContext.createUnmarshaller();

		JAXBElement<RpStudy> env = (JAXBElement<RpStudy>) marshaller.unmarshal(stream);
		return env.getValue();
	}

	public static RpDisplay createDisplayFromStream(InputStream stream) throws JAXBException {
		Unmarshaller marshaller = jaxbContext.createUnmarshaller();

		JAXBElement<RpDisplay> env = (JAXBElement<RpDisplay>) marshaller.unmarshal(stream);
		return env.getValue();
	}

	public static RpStudy createStudyFromFile(File f) throws JAXBException {

		RpStudy study = null;
		if (f.canRead()) {
			Unmarshaller marshaller = jaxbContext.createUnmarshaller();

			JAXBElement<RpStudy> env = (JAXBElement<RpStudy>) marshaller.unmarshal(f);
			study = env.getValue();

		}

		return study;

	}

	@Override
	public List<RpFile> getSessionFilesList(String studyID, String subjectID, String sessionID) {
		File f = repositoryDir;
		f = new File(f, studyID);
		f = new File(f, subjectID);
		f = new File(f, sessionID);

		List<RpFile> files = new LinkedList<RpFile>();
		if (f.exists()) {
			_getSessionFilesList(f, f, files);
		}

		return files;
	}

	public void _getSessionFilesList(File root, File parent, List<RpFile> files) {

		// DatatypeFactory xmlFactory = null;
		//try {
		//	xmlFactory = DatatypeFactory.newInstance();
		//} catch (DatatypeConfigurationException e) {
			// TODO Auto-generated catch block
		//	e.printStackTrace();
		//}

		String root_path = root.getPath();
		root_path = root_path.replace('\\', '/'); // this is necessary

		File[] subdirs = parent.listFiles();
		for (File f : subdirs) {
			if (f.isDirectory()) {
				_getSessionFilesList(root, f, files);
			} else {
				RpFile rpf = new RpFile();
				String path = f.getPath();
				path = path.replace('\\', '/'); // this is necessary

				rpf.setName(path.substring(root_path.length() + 1)); // remove the root reference
				rpf.setParent(root_path.substring(repositoryDir.getPath().length() + 1)); // remove the root reference
				// Calendar cal = Calendar.getInstance();
				// cal.setTimeInMillis( f.lastModified() );
				GregorianCalendar xcal = new GregorianCalendar();
				xcal.setTimeInMillis(f.lastModified());
				rpf.setModifyDate(xcal.getTime());
				rpf.setSize((int) f.length());
				files.add(rpf);
			}
		}

		return;
	}

	@Deprecated
	public File getSessionFile(RpStudy study, RpSubject subject, String sessionId, String name) throws IOException {
		File f = repositoryDir;
		f = new File(f, study.getIdentifier());
		f = new File(f, subject.getIdentifier());
		f = new File(f, sessionId);
		f = new File(f, name);

		return f;
	}

	public void setRepositoryName(String name) {
		this.name = name;
	}

	@Override
	public boolean createLink(File dest) throws IOException {
		String name = dest.getName();

		File f = new File(repositoryDir, name + ".lnk");
		int idx = 0;
		while (f.exists()) {
			idx++;
			f = new File(repositoryDir, name + "(" + idx + ").lnk");
		}

		ShellLink link = ShellLink.createLink(dest.getPath());
		link.saveTo(f.getPath());

		return true;
	}

	@Override
	public List<PiSubjectImporter> getImporters(RpStudy study) {
		List<PiSubjectImporter> importers = new LinkedList<PiSubjectImporter>();

		String dir = study.getRepositoryId();
		if (dir != null) {
			File f = new File(dir);
			if (f.exists() && f.isFile()) {
				// use this file
			} else {
				dir = null;
			}
		}

		if (dir == null) {
			dir = study.getRepositoryLink();
			if (dir == null) {
				dir = study.getRepositoryId();
			}
		}
		File f = new File(dir);
		if (f.isDirectory()) {
			File[] files = f.listFiles();

			boolean has_h5 = false;
			for (File subf : files) {
				if (subf.isDirectory()) {
					has_h5 = (has_h5 == false) ? hasH5(subf) : true;
				} else {
					String name = subf.getName().toLowerCase();
					if (name.endsWith("db")) {
						// add db files
						safe_add(importers, PiImporterUtil.getImporterFromFile(subf));
					} else if (name.endsWith("dat")) {
						safe_add(importers, PiImporterUtil.getImporterFromFile(subf));
					} else {
						log.warn("skipping unknown file: {}", subf);
					}
				}
			}

			if (has_h5) {
				safe_add(importers, PiImporterUtil.getImporterFromFile(f));
			}
		} else if (f.isFile()) {
			safe_add(importers, PiImporterUtil.getImporterFromFile(f));
		}

		return importers;
	}

	private void safe_add(List<PiSubjectImporter> importers, PiSubjectImporter importer) {
		if (importer != null) {
			importers.add(importer);
		}

	}

	/*
	 * 
	 * recurse through directories looking for an h5 file
	 * 
	 */

	private boolean hasH5(File subf) {
		boolean has_h5 = false;
		File[] files = subf.listFiles();
		
		// listFiles doesnt return an empty list.
		if (files != null) {
			for (File f : files) {

				if (f.isDirectory()) {
					has_h5 = hasH5(f);
				} else {
					has_h5 = f.getName().endsWith("h5");
				}
				if (has_h5) {
					break;
				}

			}
		}
		return has_h5;
	}

	public void createDisplay(File displayFile, RpDisplay display) {
		Marshaller marshaller;
		
		try {
			marshaller = jaxbContext.createMarshaller();
			marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT,  Boolean.TRUE );
			
			JAXBElement<RpDisplay> out = factory.createRpDisplayImpl( display );
			marshaller.marshal( out, displayFile );
		} catch (JAXBException e) {
			throw new RuntimeException(e);
		}
	}

}
