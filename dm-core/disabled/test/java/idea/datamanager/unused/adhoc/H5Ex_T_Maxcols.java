/************************************************************

  This example shows how to read and write compound
  datatypes to a dataset.  The program first writes
  compound structures to a dataset with a dataspace of DIM0,
  then closes the file.  Next, it reopens the file, reads
  back the data, and outputs it to the screen.

  This file is intended for use with HDF5 Library verion 1.6

 ************************************************************/

package idea.datamanager.unused.adhoc;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;

public class H5Ex_T_Maxcols {
	private static String FILENAME = "c:/tmp/h5ex_t_maxcols.h5";
	private static String DATASETNAME = "DS1";
	private static final int DIM0 = 4;
	private static final int RANK = 1;

	private static void CreateDataset() {
		long file_id = -1;
		long filetype_id = -1;
		long dataspace_id = -1;
		long dataset_id = -1;
		long[] dims = { DIM0 };
		byte[] dset_data = null;

		// Create a new file using default properties.
		try {
			file_id = H5.H5Fcreate(FILENAME, HDF5Constants.H5F_ACC_TRUNC,
					HDF5Constants.H5P_DEFAULT, HDF5Constants.H5P_DEFAULT);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Create the compound datatype for the file. Because the standard
		// types we are using for the file may have different sizes than
		// the corresponding native types, we must manually calculate the
		// offset of each member.
		try {
			filetype_id = H5.H5Tcreate( HDF5Constants.H5T_COMPOUND, 424);
			if (filetype_id >= 0) {
//				H5.H5Tinsert( filetype_id, "tstamp", 0, 50331699);
//				H5.H5Tinsert( filetype_id, "TIME.", 8, 50331697);
//				H5.H5Tinsert( filetype_id, "TEMP (�C ).", 12, 50331697);
//				H5.H5Tinsert( filetype_id, "HR.", 16, 50331697);
//				H5.H5Tinsert( filetype_id, "ABP/S.", 20, 50331697);
//				H5.H5Tinsert( filetype_id, "ABP/D.", 24, 50331697);
//				H5.H5Tinsert( filetype_id, "ABP/M.", 28, 50331697);
//				H5.H5Tinsert( filetype_id, "PAP/S.", 32, 50331697);
//				H5.H5Tinsert( filetype_id, "PAP/D.", 36, 50331697);
//				H5.H5Tinsert( filetype_id, "PAP/M.", 40, 50331697);
//				H5.H5Tinsert( filetype_id, "CVP.", 44, 50331697);
//				H5.H5Tinsert( filetype_id, "CO.", 48, 50331697);
//				H5.H5Tinsert( filetype_id, "FI02.", 52, 50331697);
//				H5.H5Tinsert( filetype_id, "Tidal Vol.", 56, 50331697);
//				H5.H5Tinsert( filetype_id, "RR.", 60, 50331697);
//				H5.H5Tinsert( filetype_id, "MV.", 64, 50331697);
//				H5.H5Tinsert( filetype_id, "Plateau.", 68, 50331697);
				H5.H5Tinsert( filetype_id, "PIP.", 72, 50331697);
				H5.H5Tinsert( filetype_id, "Pmean.", 76, 50331697);
				H5.H5Tinsert( filetype_id, "PEEP.", 80, 50331697);
				H5.H5Tinsert( filetype_id, "Compliance.", 84, 50331697);
				H5.H5Tinsert( filetype_id, "Resistance.", 88, 50331697);
				H5.H5Tinsert( filetype_id, "VC02.", 92, 50331697);
				H5.H5Tinsert( filetype_id, "VO2.", 96, 50331697);
				H5.H5Tinsert( filetype_id, "RQ.", 100, 50331697);
				H5.H5Tinsert( filetype_id, "NaCl.", 104, 50331697);
				H5.H5Tinsert( filetype_id, "D5W.", 108, 50331697);
				H5.H5Tinsert( filetype_id, "Glucose.", 112, 50331697);
				H5.H5Tinsert( filetype_id, "EtC02 Cosmo.", 116, 50331697);
				H5.H5Tinsert( filetype_id, "EtC02 Oridion.", 120, 50331697);
				H5.H5Tinsert( filetype_id, "EtC02 Drager.", 124, 50331697);
				H5.H5Tinsert( filetype_id, "Clock time.", 128, 50331697);
				H5.H5Tinsert( filetype_id, "Ph.", 132, 50331697);
				H5.H5Tinsert( filetype_id, "PCO2.", 136, 50331697);
				H5.H5Tinsert( filetype_id, "PO2.", 140, 50331697);
				H5.H5Tinsert( filetype_id, "BE.", 144, 50331697);
				H5.H5Tinsert( filetype_id, "HCO3.", 148, 50331697);
				H5.H5Tinsert( filetype_id, "SO2.", 152, 50331697);
				H5.H5Tinsert( filetype_id, "Na.", 156, 50331697);
				H5.H5Tinsert( filetype_id, "K.", 160, 50331697);
				H5.H5Tinsert( filetype_id, "Hct.", 164, 50331697);
				H5.H5Tinsert( filetype_id, "Hb.", 168, 50331697);
				H5.H5Tinsert( filetype_id, "CL.", 172, 50331697);
				H5.H5Tinsert( filetype_id, "Lac.", 176, 50331697);
				H5.H5Tinsert( filetype_id, "CoHb.", 180, 50331697);
				H5.H5Tinsert( filetype_id, "ACT.", 184, 50331697);
				H5.H5Tinsert( filetype_id, "Spn Hct.", 188, 50331697);
				H5.H5Tinsert( filetype_id, "UA DIP.", 192, 50331697);
				H5.H5Tinsert( filetype_id, "PfHb.", 196, 50331697);
				H5.H5Tinsert( filetype_id, "Oxi Stress.", 200, 50331697);
				H5.H5Tinsert( filetype_id, "Chem.", 204, 50331697);
				H5.H5Tinsert( filetype_id, "CBC.", 208, 50331697);
				H5.H5Tinsert( filetype_id, "BUN/Creat.", 212, 50331697);
				H5.H5Tinsert( filetype_id, "Cytokine.", 216, 50331697);
				H5.H5Tinsert( filetype_id, "pT/pTT.", 220, 50331697);
				H5.H5Tinsert( filetype_id, "CT.", 224, 50331697);
				H5.H5Tinsert( filetype_id, "Bronch.", 228, 50331697);
				H5.H5Tinsert( filetype_id, "BAL.", 232, 50331697);
				H5.H5Tinsert( filetype_id, "MIGET.", 236, 50331697);
//				H5.H5Tinsert( filetype_id, "Clock time.", 240, 50331697);
//				H5.H5Tinsert( filetype_id, "Ph.", 244, 50331697);
//				H5.H5Tinsert( filetype_id, "PCO2.", 248, 50331697);
//				H5.H5Tinsert( filetype_id, "P02.", 252, 50331697);
//				H5.H5Tinsert( filetype_id, "BE.", 256, 50331697);
//				H5.H5Tinsert( filetype_id, "HCO3.", 260, 50331697);
//				H5.H5Tinsert( filetype_id, "SO2.", 264, 50331697);
//				H5.H5Tinsert( filetype_id, "Na.", 268, 50331697);
				H5.H5Tinsert( filetype_id, "K.", 272, 50331697);
				H5.H5Tinsert( filetype_id, "Hct.", 276, 50331697);
				H5.H5Tinsert( filetype_id, "Hb.", 280, 50331697);
				H5.H5Tinsert( filetype_id, "CL.", 284, 50331697);
				H5.H5Tinsert( filetype_id, "Ph.", 288, 50331697);
				H5.H5Tinsert( filetype_id, "PCO2.", 292, 50331697);
				H5.H5Tinsert( filetype_id, "P02.", 296, 50331697);
				H5.H5Tinsert( filetype_id, "BE.", 300, 50331697);
				H5.H5Tinsert( filetype_id, "HCO3.", 304, 50331697);
				H5.H5Tinsert( filetype_id, "SO2.", 308, 50331697);
				H5.H5Tinsert( filetype_id, "Na.", 312, 50331697);
				H5.H5Tinsert( filetype_id, "K.", 316, 50331697);
				H5.H5Tinsert( filetype_id, "Hct.", 320, 50331697);
				H5.H5Tinsert( filetype_id, "Hb.", 324, 50331697);
				H5.H5Tinsert( filetype_id, "CL.", 328, 50331697);
				H5.H5Tinsert( filetype_id, "Clock time.", 332, 50331697);
				H5.H5Tinsert( filetype_id, "Ph.", 336, 50331697);
				H5.H5Tinsert( filetype_id, "PCO2.", 340, 50331697);
				H5.H5Tinsert( filetype_id, "P02.", 344, 50331697);
				H5.H5Tinsert( filetype_id, "BE.", 348, 50331697);
				H5.H5Tinsert( filetype_id, "HCO3.", 352, 50331697);
				H5.H5Tinsert( filetype_id, "SO2.", 356, 50331697);
				H5.H5Tinsert( filetype_id, "Na.", 360, 50331697);
				H5.H5Tinsert( filetype_id, "K.", 364, 50331697);
				H5.H5Tinsert( filetype_id, "Hct.", 368, 50331697);
				H5.H5Tinsert( filetype_id, "Hb.", 372, 50331697);
				H5.H5Tinsert( filetype_id, "CL.", 376, 50331697);
				H5.H5Tinsert( filetype_id, "Ph.", 380, 50331697);
				H5.H5Tinsert( filetype_id, "PCO2.", 384, 50331697);
				H5.H5Tinsert( filetype_id, "P02.", 388, 50331697);
				H5.H5Tinsert( filetype_id, "BE.", 392, 50331697);
				H5.H5Tinsert( filetype_id, "HCO3.", 396, 50331697);
				H5.H5Tinsert( filetype_id, "SO2.", 400, 50331697);
				H5.H5Tinsert( filetype_id, "Na.", 404, 50331697);
				H5.H5Tinsert( filetype_id, "K.", 408, 50331697);
				H5.H5Tinsert( filetype_id, "Hct.", 412, 50331697);
				H5.H5Tinsert( filetype_id, "Hb.", 416, 50331697);
				H5.H5Tinsert( filetype_id, "CL.", 420, 50331697);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Create dataspace. Setting maximum size to NULL sets the maximum
		// size to be the current size.
		try {
			dataspace_id = H5.H5Screate_simple(RANK, dims, null);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Create the dataset.
		try {
			if ((file_id >= 0) && (dataspace_id >= 0) && (filetype_id >= 0))
				dataset_id = H5.H5Dcreate(file_id, DATASETNAME, filetype_id,
						dataspace_id, HDF5Constants.H5P_DEFAULT, HDF5Constants.H5P_DEFAULT, HDF5Constants.H5P_DEFAULT);
		}
		catch (Exception e) {
			e.printStackTrace();
		}


		// End access to the dataset and release resources used by it.
		try {
			if (dataset_id >= 0)
				H5.H5Dclose(dataset_id);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Terminate access to the data space.
		try {
			if (dataspace_id >= 0)
				H5.H5Sclose(dataspace_id);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Terminate access to the file type.
		try {
			if (filetype_id >= 0)
				H5.H5Tclose(filetype_id);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Close the file.
		try {
			if (file_id >= 0)
				H5.H5Fclose(file_id);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

	}


	public static void main(String[] args) {
		H5Ex_T_Maxcols.CreateDataset();
	}

}
