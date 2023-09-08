package idea.jh5;

import java.io.File;
import java.io.IOException;
import java.io.PrintStream;

import icuInterface.PlatformUtil;
import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5Exception;

public class HDF5ReadGroup {
	public static void getHeaderAndNotes( File f, String datasetName) throws IOException, NullPointerException, HDF5Exception {

		PrintStream out = System.out;
		
		String fileName = f.getCanonicalPath();
		
		long file_id = H5.H5Fopen(fileName, HDF5Constants.H5F_ACC_RDONLY, HDF5Constants.H5P_DEFAULT);
		long dataset_id = H5.H5Dopen(file_id, datasetName, HDF5Constants.H5P_DEFAULT);

		long space_id = H5.H5Dget_space(dataset_id);

		long[] curr_dims = new long[1];
		long[] max_dims = new long[1];

		H5.H5Sget_simple_extent_dims(space_id, curr_dims, max_dims);

		if (space_id >= 0)
			H5.H5Sclose(space_id);

		long[] count = { 1 };
		long[] selectedDims = { 1 };

		long fspace = H5.H5Dget_space(dataset_id);
		long mspace = H5.H5Screate_simple(1, selectedDims, null);
		long tid = H5.H5Dget_type(dataset_id);
		long size = H5.H5Tget_size(tid);

		byte[] rec = new byte[(int) size];

		// curr_dims[0] = 12;
		for (long pos = 0; pos < curr_dims[0]; pos++) {
			long[] start = { pos };

			// set the rectangle selection
			// HDF5 bug: for scalar dataset, H5Sselect_hyperslab gives core dump
			H5.H5Sselect_hyperslab( //
					fspace, // file space
					HDF5Constants.H5S_SELECT_SET, // command
					start, // start
					null, // stride
					count, // count
					null); // set block to 1

			H5.H5Dread(dataset_id, tid, mspace, fspace, HDF5Constants.H5P_DEFAULT, rec);


			System.out.print(".");
			System.out.flush();
			if (pos % 60 == 0 && pos > 0) {
				System.out.print("  ");
				System.out.print(pos);
				System.out.println();
			}

		}
		out.close();  // only one H5 file per directory

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
		H5.H5Dclose(dataset_id);
		H5.H5Fclose(file_id);
	}

	public static void main( String [] args ) throws NullPointerException, IOException, HDF5Exception {
		PlatformUtil.init();
		PlatformUtil.loadLibrary("hdf5");
		PlatformUtil.loadLibrary("hdf5_java");
		
		// File f = new File("Z:/00-PROTOCOLS/A-16-004 RECAP/RECAP idea/Jun062017_9683/9683/2017_06_06_08.49.11/0000.h5");
		File f = new File("c:/tmp/0000.h5");
				
		if( !f.exists() ) {
			System.err.println("Cannot find file to test: " + f );
			return;
		}
		getHeaderAndNotes( f, "/Drager_1/numerics");
	}

}
