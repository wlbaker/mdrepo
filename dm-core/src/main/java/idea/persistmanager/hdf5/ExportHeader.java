package idea.persistmanager.hdf5;

import java.io.IOException;
import java.nio.ByteBuffer;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5Exception;
import hdf.hdf5lib.exceptions.HDF5LibraryException;
import idea.schema.rp.RpSubject;

public class ExportHeader {

	private long dataset_id;
	private long dataspace_id;

	private long filetype_id;
	private int num_fields;

	public ExportHeader() { }

	public void connectNew(long fileId) throws NullPointerException, HDF5Exception {
		
			
			long t80 = H5.H5Tcopy( HDF5Constants.H5T_C_S1 );
			H5.H5Tset_size(t80, 80);
				
			long t160 = H5.H5Tcopy( HDF5Constants.H5T_C_S1 );
			H5.H5Tset_size(t160, 160);
		
			H5HeaderDescription.memberFileTypes[0] = t80;
			H5HeaderDescription.memberFileTypes[1] = t160;
					
	filetype_id = H5Util
				.createTypes(H5HeaderDescription.getDataSize(), H5HeaderDescription.memberDims,
						H5HeaderDescription.memberNames, H5HeaderDescription.memberFileTypes,
						H5HeaderDescription.memberStorage);
		
		int RANK = 1;
		long[] init_dims = { 1 };
		long[] max_dims = { HDF5Constants.H5S_UNLIMITED };
		long[] chunk_dims = { 10 };

		dataspace_id = H5.H5Screate_simple(RANK, init_dims, max_dims);

		long cparms = H5.H5Pcreate(HDF5Constants.H5P_DATASET_CREATE);
		H5.H5Pset_chunk(cparms, 1, chunk_dims);
		// H5.H5Pset_deflate(cparms, 1);

		dataset_id = H5.H5Dcreate(fileId, "Header", filetype_id, dataspace_id, HDF5Constants.H5P_DEFAULT, cparms, HDF5Constants.H5P_DEFAULT);
	}

	public void connectExisting(int fileId) throws NullPointerException, HDF5Exception {
		openDataset(fileId, "Header");
	}

	private void openDataset(int file_id, String annoFile) throws NullPointerException, HDF5Exception {

		dataset_id = H5.H5Dopen(file_id, annoFile, HDF5Constants.H5P_DEFAULT);
		filetype_id = H5.H5Dget_type(dataset_id);
	}

	public void disconnect() throws HDF5LibraryException {
		H5.H5Dclose(dataset_id);
		if (dataspace_id != 0) {
			H5.H5Sclose(dataspace_id);
		}

		if (filetype_id != 0) {
			H5.H5Tclose(filetype_id);
		}

		dataset_id = 0;
		dataspace_id = 0;
		filetype_id = 0;
	}

	public void putStudyHeader(RpSubject header) {

		if (header != null) {
			try {
				H5HeaderDescription d = new H5HeaderDescription(header);

				num_fields = 0;
				encodeAndWritePair(d, "company", header.getCompany() );
				encodeAndWritePair(d, "organization", header.getOrganization() );
				encodeAndWritePair(d, "studyTitle", header.getStudyTitle() );

				encodeAndWritePair(d, "location", header.getLocation() );
				encodeAndWritePair(d, "sampleDate", "" + header.getSurgeryDate() );
				encodeAndWritePair(d, "subjectNumber", header.getSeqNo() );

				encodeAndWritePair(d, "medicalId", header.getMedicalId());
				encodeAndWritePair(d, "operator", header.getOperator() );
				encodeAndWritePair(d, "notes", header.getNotes() );

			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	private void encodeAndWritePair(H5HeaderDescription d, String key, String value) throws IOException,
			NullPointerException, HDF5Exception {
		int capacity = H5HeaderDescription.getTotalDataSize(1);

		ByteBuffer bb = ByteBuffer.allocate(capacity);

		System.out.println("saving: " + key + " value: " + value);
		byte[] write_data = d.encode(bb, key, value);

		if (write_data != null) {
			put_data(write_data);
			num_fields++;
		}

		// return write_data;
	}

	public void put_data(byte[] write_data) throws NullPointerException, HDF5Exception {

		long[] size = { num_fields + 1 };
		H5.H5Dset_extent(dataset_id, size);

		long hspace = H5.H5Dget_space(dataset_id);

		long[] start = { num_fields };
		long[] count = { 1 };

		H5.H5Sselect_hyperslab(hspace, HDF5Constants.H5S_SELECT_SET, start, null, count, null);
		H5.H5Dwrite(dataset_id, filetype_id, dataspace_id, hspace, HDF5Constants.H5P_DEFAULT, write_data);

		H5.H5Sclose(hspace);

	}

}
