package idea.persistmanager.hdf5;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Date;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5Exception;
import hdf.hdf5lib.exceptions.HDF5LibraryException;
import idea.schema.rp.RpSubject;

public class ImportHeader {

	private String HEADER_DATASET_NAME = "/Header";
	private long dataset_id;

	private long[] curr_dims;
	private long[] max_dims;
	private long file_id;

	H5HeaderDescription h5Header;

	public ImportHeader(long file_id) throws NullPointerException, HDF5Exception {

		this.file_id = file_id;

		h5Header = new H5HeaderDescription();
	}

	public void connect() throws HDF5LibraryException, NullPointerException {
		dataset_id = H5.H5Dopen(file_id, HEADER_DATASET_NAME, HDF5Constants.H5P_DEFAULT);
		long space_id = H5.H5Dget_space(dataset_id);

		curr_dims = new long[1];
		max_dims = new long[1];

		H5.H5Sget_simple_extent_dims(space_id, curr_dims, max_dims);

		if (space_id >= 0)
			H5.H5Sclose(space_id);

	}

	public void disconnect() throws HDF5LibraryException {
		if (dataset_id >= 0)
			H5.H5Dclose(dataset_id);

	}

	public RpSubject next() throws IOException, NullPointerException, HDF5Exception {

		long[] count = { 1 };

		long[] selectedDims = { 1 };

		long fspace = H5.H5Dget_space(dataset_id);
		long mspace = H5.H5Screate_simple(1, selectedDims, null);

		RpSubject header = new RpSubject();
		header.setCompany( "<Not specified>" );
		header.setLocation( "<Not specified>" );
		header.setSurgeryDate( new Date() );

		// set the rectangle selection
		// HDF5 bug: for scalar dataset, H5Sselect_hyperslab gives core dump
		long tid = H5.H5Dget_type(dataset_id);
		long size = H5.H5Tget_size(tid);
		
		for (int pos = 0; pos < curr_dims[0]; pos++) {
			long[] start = { pos };
			H5.H5Sselect_hyperslab( //
					fspace, // file space
					HDF5Constants.H5S_SELECT_SET, // command
					start, // start
					null, // stride
					count, // count
					null); // set block to 1

			byte[] read_data = new byte[(int)size];
			H5.H5Dread(dataset_id, tid, mspace, fspace, HDF5Constants.H5P_DEFAULT, read_data);

			ByteBuffer bb = ByteBuffer.wrap(read_data);
			h5Header.decode(header, bb);

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

		// header.sa

		return header;
	}

	public void rewind() {
		// you can't rewind the header...is is atomic
	}

}
