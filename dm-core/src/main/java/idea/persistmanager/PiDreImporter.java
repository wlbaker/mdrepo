package idea.persistmanager;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

/**
 * 
 * A quick way to make a dataset using R:<p>
 * 
 a <- rep(rep(0:10, times=30, each=100), 1 )
 b <- rep(rep(0:10, times=60, each=50), 1 )
 b <- b * 2
 zero <- rep(0, length(b))
 threeh <- rep( c(300:1), times=10, each=11)
 two80 <- threeh*280/300
 minus148 <- b - 148
 write.table(data.frame(zero,a,b,threeh, two80, minus148), file="/opt/study/demo/demo.dat", row.names=FALSE, sep="\t", eol="\r\n" )
 * 
 * NOTE: Performance of RandomAccessFile is PITIFUL.  Avoid it when possible.
 * 
 */

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.persistence.PiDatastreamImporter;
import idea.persistmanager.daq.PiDreImportDevice;
import idea.persistmanager.daq.PiDreImportSTP;
import idea.persistmanager.daq.STP;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class PiDreImporter extends AbstractStreamProducer implements PiSubjectImporter {

	PiDreImportDevice dev;
	File stpFile;
	File dataFile;
	List<File> annoFiles = new LinkedList<File>();
	List<File> vitalsFiles = new LinkedList<File>();
	List<File> wavesFiles = new LinkedList<File>();

	private String devName;

	public PiDreImporter(File file, String devName) {

		String name = (file == null) ? "" : file.getName();
		this.devName = devName;

		if (name.toLowerCase().endsWith("stp")) {
			stpFile = file;
		} else {
			dataFile = file;
			
			// FIXME: might not be a waveform!
			if( dataFile != null ) {
				addWavesFile(file);
			}
		}

	}

	public void addAnnotationFile(File file) {
		annoFiles.add(file);
	}

	public void addVitalsFile(File file) {
		vitalsFiles.add(file);
	}

	public void addWavesFile(File file) {
		wavesFiles.add(file);
	}

	@Override
	public RpSubject getSubjectInfo() {
		return dev.getSubjectInfo();
	}

	@Override
	public void disconnect() {
		try {
			if (dev != null)
				dev.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	@Override
	public long getTimeInMillis() {
		return dev.getTimeInMillis();
	}

	@Override
	public PersistentItem next() throws IOException {

		PersistentItem message = dev.next();

		return message;
	}

	/*
	*/

	// public DeviceConfiguration[] getDeviceConfiguration() {
	// DeviceConfiguration[] ar = new DeviceConfiguration[1];
	// ar[0] = dev.getConfiguration();
	//
	// return ar;
	// }

	@Override
	public void connect() { // FIXME: I think connect really should be able to
							// throw an IOException
		try {

			STP stp = null;

			if (dataFile == null) {
				stp = PiDreImportSTP.readSessionFile(stpFile);

				/*
				 * The DAT file indicated in CONFIG is near meaningless...might
				 * not exist...might not be right file...
				 */
				// String dataFileName = stp.config[ stp.config.length - 2];
				// if( File.separatorChar == '\\') {
				// dataFileName = dataFileName.replace('/', '\\'); // convert
				// unix to windows
				// } else {
				// dataFileName = dataFileName.replace('\\', '/'); // convert
				// windows to unix
				// }
				String dataFileName = stpFile.getName().replace("_s_", "_w_");
				dataFileName = dataFileName.replace("stp", "dat");
				File tmp = new File(dataFileName);
				dataFileName = tmp.getName(); // clip off the parent path
				dataFile = new File(stpFile.getParent(), dataFileName);
			}

			dev = new PiDreImportDevice(dataFile, devName);
			dev.setSTP(stp);
			dev.connect(); // reads meta info

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public PiDatastreamImporter[] getDevices() {
		PiDatastreamImporter[] devs = new PiDatastreamImporter[1];
		devs[0] = dev;
		return devs;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArchiveMetaData getMetaData() throws IOException {
		return dev.getMeta();
	}

	@Override
	public void rewind() throws IOException {
		for (PiDatastreamImporter dev : getDevices()) {
			dev.rewind();
		}

	}

	@Override
	public PiDatastreamImporter getDatastreamImporter(String name, StreamID sid) {
		log.warn("DRE: annotation importer is _not_ implemented for DreWorkstation and ignores STREAMID.");

		if (name.equals(dev.getName())) {
			return dev;
		}
		return null;
	}

	@Override
	public void seek(long startTime) throws IOException {
		dev.seek(startTime);

	}

	public void addFilePattern(File dir, String pat) {
		FilenameFilter filter = new FilenameFilter() {

			public boolean accept(File directory, String fileName) {

				boolean ok = fileName.startsWith(pat);
				if (ok) {
					ok = fileName.endsWith(".dat");
				}
				return ok;
			}
		};

		File[] myFiles = dir.listFiles(filter);

		if (myFiles != null) {
			for (File f : myFiles) {
				this.addWavesFile(f);
			}
		}

	}

}
