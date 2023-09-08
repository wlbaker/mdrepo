package idea.persistence;

import java.util.Date;

public class StudyDefinition {
	private String studyTitle;
	private String PI;
	private Date startDate;
	private Date completionDate;
	private String status;
	
	// URL ref...to retrieve hardware setup info???
	// I really want an associated document for this purpose
	private String ref;

	public String getStudyTitle() {
		return studyTitle;
	}

	public void setStudyTitle(String studyTitle) {
		this.studyTitle = studyTitle;
	}

	public String getPI() {
		return PI;
	}

	public void setPI(String pI) {
		PI = pI;
	}

	public Date getStartDate() {
		return startDate;
	}

	public void setStartDate(Date startDate) {
		this.startDate = startDate;
	}

	public Date getCompletionDate() {
		return completionDate;
	}

	public void setCompletionDate(Date completionDate) {
		this.completionDate = completionDate;
	}

	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getRef() {
		return ref;
	}

	public void setRef(String ref) {
		this.ref = ref;
	}    

	
}
