package idea.repository.io;

import idea.persistence.PiSubjectImporter;

import java.io.File;
import java.io.IOException;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import lombok.extern.slf4j.Slf4j;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONTokener;
import org.restlet.data.MediaType;
import org.restlet.data.Reference;
import org.restlet.representation.Representation;
import org.restlet.resource.ClientResource;

import idea.repository.GettableResource;
import idea.repository.RepositoryInterface;
import idea.schema.rp.RpFile;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;

@Slf4j
public class RemoteJSONRepository implements RepositoryInterface {

	private String uri;

	public RemoteJSONRepository(String uri) {

		this.uri = uri;

	}

	@Override
	public List<RpStudy> getStudyList(String status) throws Exception {
		List<RpStudy> list = null;

		ClientResource cr = new ClientResource(uri);
		// Get the Contact object
		GettableResource resource = cr.wrap(GettableResource.class);
		Representation r = resource.retrieve();

		if (r != null) {
			list = new LinkedList<RpStudy>();

			Representation json = cr.get(MediaType.APPLICATION_JSON);

			JSONArray arr = new JSONArray(new JSONTokener(json.getReader()));
			arr = arr.getJSONArray(0);
			for (int i = 0; i < arr.length(); i++) {
				JSONObject o = (JSONObject) arr.get(i);
				System.out.println("o= " + o.getClass() + " --> " + o);
				String id = o.getString("identifier");
				String title = o.getString("title");
				String pi = o.getString("pi");
				String startDate = o.getString("startDate");
				RpStudy s = new RpStudy();
				s.setIdentifier(id);
				s.setTitle(title);
				s.setPi(pi);
				// s.setStartDate(arg0);
				list.add(s);
			}

		}
		return list;
	}

	@Override
	public boolean createStudy(RpStudy study) throws Exception {
		log.error("createStudy unsupported");

		return false;
	}

	@Override
	public File createSession(RpSubject hd, String sessionName, String sessionDescription) throws Exception {
		// TODO Auto-generated method stub
		return null;
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
		// TODO Auto-generated method stub
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
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<String> getSessionList(String studyId, String subjectId) throws Exception {
		List<String> list = null;

		ClientResource cr = new ClientResource(uri + "/" + Reference.encode(studyId) + "/"
				+ Reference.encode(subjectId));
		// Get the Contact object
		GettableResource resource = cr.wrap(GettableResource.class);
		Representation r = resource.retrieve();

		if (r != null) {
			list = new LinkedList<String>();

			Representation json = cr.get(MediaType.APPLICATION_JSON);

			JSONArray arr = new JSONArray(new JSONTokener(json.getReader()));
			for (int i = 0; i < arr.length(); i++) {
				Object o = (Object) arr.get(i);
				System.out.println("o= " + o.getClass() + " --> " + o);
				String id = (String) o; // o.getString("identifier");
				list.add(id);
			}

		}
		return list;
	}

	@Override
	public List<RpSubject> getSubjectList(RpStudy study) throws JSONException, IOException {
		List<RpSubject> list = null;

		String studyId = study.getIdentifier();
		ClientResource cr = new ClientResource(uri + "/" + Reference.encode(studyId));
		// Get the Contact object
		GettableResource resource = cr.wrap(GettableResource.class);
		Representation r = resource.retrieve();

		if (r != null) {
			list = new LinkedList<RpSubject>();

			Representation json = cr.get(MediaType.APPLICATION_JSON);

			JSONArray arr = new JSONArray(new JSONTokener(json.getReader()));
			for (int i = 0; i < arr.length(); i++) {
				Object o = arr.get(i);
				System.out.println("o= " + o.getClass() + " --> " + o);
				String id = (String) o; // o.getString("identifier");
				// String startDate = o.getString("startDate");
				RpSubject s = new RpSubject();
				s.setIdentifier(id);
				list.add(s);
			}

		}
		return list;
	}

	@Override
	public List<RpFile> getSessionFilesList(String studyId, String subjectId, String sessionId) throws JSONException,
			IOException {
		List<RpFile> list = null;

		ClientResource cr = new ClientResource(uri + "/" + Reference.encode(studyId) + "/"
				+ Reference.encode(subjectId) + "/" + Reference.encode(sessionId));
		// Get the Contact object
		GettableResource resource = cr.wrap(GettableResource.class);
		Representation r = resource.retrieve();

		if (r != null) {
			list = new LinkedList<RpFile>();

			Representation json = cr.get(MediaType.APPLICATION_JSON);

			JSONArray arr = new JSONArray(new JSONTokener(json.getReader()));
			for (int i = 0; i < arr.length(); i++) {
				JSONObject o = (JSONObject) arr.get(i);
				System.out.println("o= " + o.getClass() + " --> " + o);
				String name = o.getString("name");
				String parent = o.getString("parent");
				String modifyDate = o.getString("modifyDate");
				int sz = o.getInt("size");
				RpFile f = new RpFile();
				f.setName(name);
				f.setSize(sz);
				f.setParent(parent);

				f.setModifyDate(new Date(Date.parse(modifyDate)));

				list.add(f);
			}

		}
		return list;
	}

	@Override
	public boolean createLink(File dest) throws IOException {
		log.error("unimplemented");
		throw new IOException("createLink: unimplemented");
	}

	@Override
	public List<PiSubjectImporter> getImporters(RpStudy study) {
		return null;
	}

}
