package idea.persistmanager.hdf5;

import java.nio.ByteBuffer;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5Exception;
import hdf.hdf5lib.exceptions.HDF5LibraryException;
import idea.model.PersistentItem;
import idea.persistence.PiDatastreamExporter;
import idea.persistmanager.PiConstants;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class H5DatastreamExporter implements PiDatastreamExporter {

	private static final int RANK1 = 1;
	private long[] chunk_dims;
	private long dataspace_id = -1;
	private long dataset_id = -1;

	private long filetype_id = -1;

	private int nrecs;

	H5DatasetCODEC codec;
	private String datasetName;
	private long file_id;
	// private long parent_id;
	private int streamID;

	public H5DatastreamExporter(long file_id, String datasetName, int sid, H5DatasetCODEC codec) {
		this.file_id = file_id;
		this.datasetName = datasetName;
		this.codec = codec;
		this.streamID = sid;

		// BETA2: FIXME: In the case that we are connecting to an existing dataset for
		// export,
		// we don't know the codec until the dataset is opened!
	}

	public H5DatastreamExporter(long file_id, String datasetName, int sid, RpMetric[] metrics, boolean ts_ind,
			boolean null_ind) throws HDF5Exception {

		this.file_id = file_id;
		this.datasetName = datasetName;
		this.streamID = sid;
		codec = new H5DatasetCODEC(PiConstants.HDF5_EX_VERSION, metrics, ts_ind, null_ind); // exporter always creates
																							// null indicators

		// BETA2: FIXME: In the case that we are connecting to an existing dataset for
		// export,
		// we don't know the codec until the dataset is opened!
	}

	public void connect(long parent_id) throws NullPointerException, HDF5Exception {

		// created in connect so that it can be destroyed in disconnect
		chunk_dims = new long[] { 64 };
		long[] init_dims = new long[] { 1 };
		long[] max_dims = new long[] { HDF5Constants.H5S_UNLIMITED };

		H5.H5Fflush(file_id, HDF5Constants.H5F_SCOPE_LOCAL);
		H5.H5Fflush(file_id, HDF5Constants.H5F_SCOPE_GLOBAL);
		nrecs = 0; // reset below if file exists
		// String datasetSuffixName = "M2";
		// if( H5.H5Oexists_by_name(file_id, datasetSuffixName,
		// HDF5Constants.H5P_DEFAULT) ) {
		if (false) {
			dataset_id = H5.H5Dopen(file_id, datasetName, HDF5Constants.H5P_DEFAULT);

			// I don't know if this is closed automatically when the dataset is closed or
			// not?
			filetype_id = H5.H5Dget_type(dataset_id);
			codec.setFileTID(filetype_id);

			dataspace_id = H5.H5Dget_space(dataset_id); // the right thing!
			// dataspace_id = H5.H5Screate_simple(RANK1, init_dims, max_dims);

			H5.H5Sget_simple_extent_dims(dataspace_id, init_dims, max_dims);

			nrecs = (int) init_dims[0];

			log.debug("H5.H5Dopen( {} ) dataset_id={}", datasetName, dataset_id);

		} else {
			// this one is closed automatically when the codec is closed
			filetype_id = codec.getFileTID();

			dataspace_id = H5.H5Screate_simple(RANK1, init_dims, max_dims);

			long cparms = H5.H5Pcreate(HDF5Constants.H5P_DATASET_CREATE);
			int status = H5.H5Pset_chunk(cparms, RANK1, chunk_dims);
			// H5.H5Pset_deflate(cparms, 9);
			dataset_id = H5.H5Dcreate(file_id, datasetName, filetype_id, dataspace_id, HDF5Constants.H5P_DEFAULT,
					cparms, HDF5Constants.H5P_DEFAULT);
			H5.H5Pclose(cparms);

			if( streamID != 0) {
			H5Util.writeIntAttribute(dataset_id, "streamID", (int) streamID);
			}
			
			log.debug("H5.H5Dcreate( {} ) dataset_id={}", datasetName, dataset_id);
			H5Util.writeTypesAndAttributes(dataset_id, codec.getMetrics());

		}

	}

	public void disconnect() throws HDF5LibraryException {
		log.debug("H5.H5Dclose( {} ) dataset_id={}", datasetName, dataset_id);

		codec.destroy();
		if (dataset_id >= 0)
			H5.H5Dclose(dataset_id);

		if (dataspace_id >= 0)
			H5.H5Sclose(dataspace_id);

		// If filetype comes from the codec, then is is closed automatically with the
		// codec, but
		// that onely happens on file creation. What happens when the file is opened as
		// an
		// existing file?

		// DO NOT CLOSE filetype_id, see notes.
		// H5.H5Tclose(filetype_id);

		dataset_id = -1;
		dataspace_id = -1;
		filetype_id = -1;

	}

	public long put(PersistentItem block) throws HDF5LibraryException, NullPointerException {
		byte[] write_data = encodeMetric(block);
		long[] size = { ++nrecs };

		assert (dataset_id >= 0) : "DATASET NOT CREATED/CONNECTED!";

		try {
			H5.H5Dset_extent(dataset_id, size);
		} catch (Throwable t) {
			t.printStackTrace();
			return 0;
		}

		long hspace = H5.H5Dget_space(dataset_id);

		// System.out.println(datasetName + " put: " + IntfUtil.getMetrics(block)[1]);

		try {
			long[] start = { nrecs - 1 };
			long[] count = { 1 };

			H5.H5Sselect_hyperslab(hspace, HDF5Constants.H5S_SELECT_SET, start, null, count, null);
			H5.H5Dwrite(dataset_id, filetype_id, dataspace_id, hspace, HDF5Constants.H5P_DEFAULT, write_data);

			block.setOid(nrecs - 1);
		} finally {
			H5.H5Sclose(hspace);
		}

		return nrecs - 1;
	}

	private byte[] encodeMetric(PersistentItem block) {
		int capacity = codec.getTotalDataSize(1, block);

		byte[] write_data = new byte[capacity];
		ByteBuffer bb = ByteBuffer.wrap(write_data);
		codec.encode(block, bb);

		return write_data;
	}

	public void writeAttribute(String name, String value) throws NullPointerException, HDF5Exception {
		H5Util.writeStringAttribute(dataset_id, name, value);
	}

}
