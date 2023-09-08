package idea.repository;

import java.io.File;
import java.io.IOException;
import java.util.List;

import idea.persistence.PiSubjectImporter;
import idea.schema.rp.RpFile;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;

public interface RepositoryInterface {
	
	/*
	 * stateful, but unconnected interfaces
	 */
	public List<RpStudy> getStudyList( String status ) throws Exception;
	public boolean createStudy( RpStudy study ) throws Exception;
	public boolean createLink(File file) throws IOException;  // maybe only local repositories??

	
	/*
	 * after connection
	 */
	public List<RpSubject> getSubjectList( RpStudy study ) throws Exception;
	
	public RpStudy getStudy(String studyId) throws Exception;
	public void removeStudy(RpStudy study) throws Exception;
	
	public List<PiSubjectImporter> getImporters( RpStudy study );
	/*
	 * session management...somewhat H5'ish inspired
	 * ...dont really need data collection sessions in the SQL environment, but no harm
	 */
	public List<String> getSessionList(String studyId, String subjectId ) throws Exception;
	public File createSession( RpSubject hd, String sessionName, String sessionDescription ) throws Exception;
	public void removeSession( String studyId, String sessionName ) throws Exception;
	
	/* what is this for?? remove?? return void?? */
	public void getSessionInfo( String studyID, String sessionID );
	public List<RpFile> getSessionFilesList(String studyId, String subjectId, String sessionId) throws Exception;
	
	/*
	 * value???
	 */
	public File getRoot( );  //? directory?
	public String getName();
	
}
