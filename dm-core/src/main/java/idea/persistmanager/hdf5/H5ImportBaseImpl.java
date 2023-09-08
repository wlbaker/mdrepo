package idea.persistmanager.hdf5;

import java.io.IOException;
import java.util.Date;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5Exception;
import hdf.hdf5lib.exceptions.HDF5LibraryException;
import idea.intf.AbstractStreamProducer;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public abstract class H5ImportBaseImpl extends AbstractStreamProducer implements PiDatastreamImporter {
	protected long dataset_id;
	protected int pos = 0;

	// protected int space_id;
	long[] curr_dims, max_dims;
	private long file_id;

	public H5ImportBaseImpl(long fileId) {
		this.file_id = fileId;
	}

	protected void connect(String datasetName) throws HDF5LibraryException, NullPointerException {
		try {
			log.error("parent,dataset={}", datasetName);
			dataset_id = H5.H5Dopen(file_id, datasetName, HDF5Constants.H5P_DEFAULT);
		} catch (Exception ex) {
			// BETA2: Actually tell about the error and log it...because this is an error
			// BETA2: FIXME: depends on correct iteration of members of the group
			log.error("Connect error for {}: ", datasetName, ex);
			return;
		}

		
		long space_id = H5.H5Dget_space(dataset_id);

		if( log.isDebugEnabled() ) {
			log.debug("connect for: {} = {}", datasetName, dataset_id);
			int ext_typ = H5.H5Sget_simple_extent_type( space_id );
			log.debug("ext_typ = {}  ??simple={}", ext_typ, HDF5Constants.H5S_SIMPLE );
		}

		curr_dims = new long[1];
		max_dims = new long[1];

		H5.H5Sget_simple_extent_dims(space_id, curr_dims, max_dims);

		if (space_id >= 0)
			H5.H5Sclose(space_id);

	}

	public void disconnect() throws IOException {

		if (dataset_id <= 0) {
			log.debug("attempting to close already closed dataset?");
			
			return;
		}

		try {
			if (dataset_id >= 0)
				H5.H5Dclose(dataset_id);
			dataset_id = 0;
		} catch (Exception ex) {
			throw new IOException(ex);
		}

	}

	public void rewind() {
		pos = 0;
	}

	@Override
	public void seek(long startTime) throws IOException {
		try {
			_seek(startTime);
		} catch (Exception e) {
			throw new IOException(e);
		}

	}

	public void _seek(long startTime) throws NullPointerException, HDF5Exception {

		if (dataset_id <= 0) {
			return; // no opened or does not exist
		}

		pos = 0;

		long[] selectedDims = { 1 };

		long fspace = H5.H5Dget_space(dataset_id);
		long mspace = H5.H5Screate_simple(1, selectedDims, null);
		long tid = H5.H5Dget_type(dataset_id);
		H5.H5Sget_simple_extent_dims(fspace, curr_dims, max_dims);

		long incr_size = curr_dims[0] / 2;
		pos += incr_size;
		if (incr_size == 0) { // happens if only one record in the file
			incr_size = 1;
		}
		while (pos < curr_dims[0] && pos >= 0) {
			if (incr_size > 1) {
				incr_size /= 2;
			}
			long ts = H5Util.getRecordTime(dataset_id, fspace, mspace, tid, pos);
			if (ts == startTime) {
				break;
			} else if (ts < startTime) {
				pos += incr_size;
				if (incr_size == 1) {
					break;
				}
			} else {
				pos -= incr_size;
			}
		}
		
		if( pos < 0 ) {
			pos = 0;  // wlb 30-July-2012 beginning of file
		}

		try {
			H5.H5Sclose(fspace);
		} catch (Exception ex2) {
		}
		try {
			H5.H5Sclose(mspace);
		} catch (Exception ex2) {
		}
		try {
			H5.H5Tclose(tid);
		} catch (HDF5Exception ex2) {
		}

	}

	protected ArchiveMetaData _getMeta( long tid) throws NullPointerException, HDF5Exception {
		long[] selectedDims = { 1 };

		long fspace = H5.H5Dget_space(dataset_id);
		long mspace = H5.H5Screate_simple(1, selectedDims, null);
		// int tid = H5.H5Dget_type(dataset_id);

		ArchiveMetaData meta = new ArchiveMetaData();
		meta.setStartTime(null);
		meta.setStopTime(null);

		long last_pos = curr_dims[0] - 1;

		if (last_pos >= 0) {
			long startTime = H5Util.getRecordTime(dataset_id, fspace, mspace, tid, 0);
			if (startTime > 0) {
				meta.setStartTime(new Date(startTime));
			}

			long endTime = H5Util.getRecordTime(dataset_id, fspace, mspace, tid, last_pos);
			if (endTime > 0) {
				meta.setStopTime(new Date(endTime));
			}
		}

		try {
			H5.H5Sclose(fspace);
		} catch (Exception ex2) {
		}
		try {
			H5.H5Sclose(mspace);
		} catch (Exception ex2) {
		}
//		try {
//			H5.H5Tclose(tid);
//		} catch (HDF5Exception ex2) {
//		}

		return meta;
	}

	public int getPos() {
		return pos;
	}

	public void update(int ppos, PersistentItem drager_block) throws NullPointerException, HDF5Exception {
		long[] selectedDims = { 1 };

		long fspace = H5.H5Dget_space(dataset_id);
		long mspace = H5.H5Screate_simple(1, selectedDims, null);
		long tid = H5.H5Dget_type(dataset_id);
		H5.H5Sget_simple_extent_dims(fspace, curr_dims, max_dims);

		if( ppos < 0 ) {
			ppos = (int) drager_block.getOid();
		}
		H5Util.setRecordTime(dataset_id, fspace, mspace, tid, ppos, drager_block.getTime() );
		
		try {
			H5.H5Sclose(fspace);
		} catch (Exception ex2) {
		}
		try {
			H5.H5Sclose(mspace);
		} catch (Exception ex2) {
		}
		try {
			H5.H5Tclose(tid);
		} catch (HDF5Exception ex2) {
		}
	}
}
