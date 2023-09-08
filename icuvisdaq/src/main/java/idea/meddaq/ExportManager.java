package idea.meddaq;

import icuInterface.RpUtil;
import idea.intf.StreamProducer;
import idea.persistence.PiSubjectExporter;
import idea.persistmanager.PiDreExporter;
import idea.persistmanager.PiHdf5Exporter;
import idea.persistmanager.sql.SQLExporter;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;

import java.io.File;
import java.io.IOException;

import lombok.extern.slf4j.Slf4j;
import idea.datamanager.CompositeExporter;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;

@Slf4j
public class ExportManager {

	private static CompositeExporter exporter; // used for device data
	private static CompositeExporter derived; // used for derived metrics
	private static File archiveDir;

	static {
		exporter = new CompositeExporter();
		derived = new CompositeExporter();
	}

	public static PiSubjectExporter getDataExporter() {
		return exporter;
	}

	public static PiSubjectExporter getDerivedExporter() {
		return derived;
	}

	public static File getArchiveDir() {
		return archiveDir;
	}

	public static void startDeviceCapture(RpStudy study, StreamProducer[] producers, RpSubject header, String base)
			throws Exception {
		startDeviceCapture(study, producers, exporter, header, base);
	}

	public static void startDerivedCapture(RpStudy study, StreamProducer[] producers, RpSubject header, String base)
			throws Exception {
		startDeviceCapture(study, producers, derived, header, base);
	}

	private static void startDeviceCapture(RpStudy study, StreamProducer[] producers, PiSubjectExporter intf,
			RpSubject header, String base) throws Exception {


		RepositoryInterface local = RepositoryFactory.getLocalRepository();
		archiveDir = local.createSession(header, base, "?no description");

		intf.setHeader(header);
		intf.setDestination(archiveDir);

		intf.connect();

		// CREATE the DATA TABLES for the exporter
		if (producers != null) {
			for (StreamProducer producer : producers) {
				if (producer == null) {
					log.error("producer is null");
				} else {
					intf.addDevice(producer.getConfiguration());
				}
			}
		}

	}

	public static void disconnect() throws IOException {
		log.warn("ExportManager is DISCONNECTING");
		if (exporter != null) {
			exporter.disconnect();
		}
		if (derived != null) {
			derived.disconnect();
		}

		archiveDir = null;
	}

	public static void initDB(RpStudy study, RpSubject subject ) {
		exporter.reset();
		derived.reset();

		int n_exporters = 0;
		if ("true".equals(RpUtil.getParam(study, "sql"))) {
			String jdbc = RpUtil.getParam(study, "jdbc");
			exporter.addExporter(new SQLExporter("exporterSQLite", jdbc));
			n_exporters++;
		}
		if ("true".equals(RpUtil.getParam(study, "ascii"))) {
            File dest = new File(study.getRepositoryLink() );
            dest = new File( dest, subject.getMedicalId() );
			exporter.addExporter(new PiDreExporter(subject, dest));
			n_exporters++;
		}

		if (n_exporters == 0 || "true".equals(RpUtil.getParam(study, "hdf5"))) {
            File dest = new File(study.getRepositoryLink() );
            dest = new File( dest, subject.getMedicalId() );
			exporter.addExporter(new PiHdf5Exporter(subject, dest.getPath(), false ));
			n_exporters++;
		}
		
	}

}
