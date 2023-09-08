package idea.persistmanager;

import java.io.File;

import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;

public class H5CompositeWithMeta {
	private ArchiveMetaData meta;
	private File file;
	private PiSubjectImporter importer;
	private String subject;

	public H5CompositeWithMeta(File file, ArchiveMetaData meta) {
		this.file = file;
		this.meta = meta;
	}

	public ArchiveMetaData getMeta() {
		return meta;
	}

	public File getFile() {

		return file;
	}

	public void setMeta(ArchiveMetaData meta) {
		this.meta = meta;
	}

	public PiSubjectImporter getImporter() {
		return importer;
	}

	public void setImporter(PiSubjectImporter importer) {
		this.importer = importer;

	}

	public void setSubject(String subject) {
		this.subject = subject;
	}
	public String getSubject() {
		return subject;
	}
}

