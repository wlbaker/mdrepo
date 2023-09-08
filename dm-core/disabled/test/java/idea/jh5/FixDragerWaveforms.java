package idea.jh5;


import java.io.File;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.util.Arrays;

import idea.persistmanager.hdf5.H5Util;
import lombok.extern.slf4j.Slf4j;
import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5LibraryException;

@Slf4j
public class FixDragerWaveforms {

	private static final int RANK1 = 1;
	private static int nrecs = 0;

	private static int numberMembers = 12;
	private static long dest_filetype_id;
	private static long dest_dataspace_id;
	private static long dest_dataset_id;
	private static boolean IS_9717_STEP1;

	public static void main(String[] args) throws Exception {
		File share = new File("\\\\ameda7aisr0107\\ISR_CANCIOLAB_4");
		// File root = new File("/home/bbaker/tmp/recap");
		File root = new File( share, "\\00-PROTOCOLS\\A-16-004 RECAP");

		// 9619
		File source = new File(root,"RECAP idea\\Feb282017_9619\\2017_02_28_08.50.06\\0000.h5");
		File dest = new File(root,"RECAP idea\\Feb282017_9619\\2017_02_28_08.50.06\\0001.h5");
		 int [] seq = { 0, 1, 2,3,8,5,7, 9,6,11,10,4 };
		
		// 9243
//		File source = new File(root,"RECAP idea\\Mar022017_9243\\9243\\2017_03_02_08.24.17\\0000.h5");
//		File dest = new File(root,"RECAP idea\\Mar022017_9243\\9243\\2017_03_02_08.24.17\\0001.h5");
//	    int [] seq = { 0, 1, 2,3, 8, 5, 6, 9, 7, 11, 10, 4 };
		
		// 9614
//		File source = new File(root,"RECAP idea\\Mar072017_9614\\2017_03_07_10.11.30\\0000.h5");
//		File dest = new File(root,"RECAP idea\\Mar072017_9614\\2017_03_07_10.11.30\\0001.h5");
		// int [] seq = { 0, 1, 2,3,8, 7,6, 9,5,4,10,11 };
		
		
		// 7996
		//File source = new File(root,"RECAP idea\\Mar082017_7996\\2017_03_08_08.36.34\\0000.h5");
		//File dest = new File(root,"RECAP idea\\Mar082017_7996\\2017_03_08_08.36.34\\0001.h5");
		//int [] seq = { 0, 1, 2,3, 10, 6, 7, 11,9,4,8,5 };
		
		// 9613
		//File source = new File(root,"RECAP idea\\Mar092017_9613\\2017_03_09_08.29.41\\0000.h5");
		//File dest = new File(root,"RECAP idea\\Mar092017_9613\\2017_03_09_08.29.41\\0001.h5");
		//int [] seq = { 0, 1, 2,3, 9, 8, 5, 6, 4, 7, 10, 11 };
		
		// 9484
//		File source = new File(root,"RECAP idea\\Apr122017_9484\\9484\\2017_04_12_08.32.31\\0000.h5");
//		File dest = new File(root,"RECAP idea\\Apr122017_9484\\9484\\2017_04_12_08.32.31\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 6, 7, 9, 5, 4, 10, 11 };
		
		// 9480
//		File source = new File(root,"RECAP idea\\Apr202017_9480\\9480\\2017_04_20_09.25.08\\0000.h5");
//		File dest = new File(root,"RECAP idea\\Apr202017_9480\\9480\\2017_04_20_09.25.08\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 6, 7, 9, 5, 4, 10, 11 };

		// 9482
//		File source = new File(root,"RECAP idea\\Apr262017_9482\\9482\\2017_04_26_08.43.29\\0000.h5");
//		File dest = new File(root,"RECAP idea\\Apr262017_9482\\9482\\2017_04_26_08.43.29\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 6, 7, 9, 5, 4, 10, 11 };
		
		// 9680 -- broken pieces
//		File source = new File(root,"RECAP idea\\May032017_9680\\9680\\2017_05_03_12.48.01\\0000.h5");
//		File dest = new File(root,"RECAP idea\\May032017_9680\\9680\\2017_05_03_12.48.01\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 5, 7, 9, 6, 4, 10, 11 };
		
		// 9665
//		File source = new File(root,"RECAP idea\\May042017_9665\\9665\\2017_05_04_08.49.11\\0000.h5");
//		File dest = new File(root,"RECAP idea\\May042017_9665\\9665\\2017_05_04_08.49.11\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 5, 7, 9, 6, 4, 10, 11 };

		// 9666
//		File source = new File(root,"RECAP idea\\May102017_9666\\9666\\2017_05_10_08.45.36\\0000.h5");
//		File dest = new File(root,"RECAP idea\\May102017_9666\\9666\\2017_05_10_08.45.36\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 5, 7, 9, 6, 4, 10, 11 };
		
		// 9670
//		File source = new File(root,"RECAP idea\\May162017_9670\\9670\\2017_05_16_08.25.38\\0000.h5");
//		File dest = new File(root,"RECAP idea\\May162017_9670\\9670\\2017_05_16_08.25.38\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 5, 9, 12, 7, 8, 4, 10, 11 };
//		int [] seq = { 0, 1, 2,3, 8, 5, 7, 9, 6, 4, 10, 11 };
		
		// 9674
//		File source = new File(root,"RECAP idea\\May172017_9674\\9674\\2017_05_17_09.16.56\\0000.h5");
//		File dest = new File(root,"RECAP idea\\May172017_9674\\9674\\2017_05_17_09.16.56\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 5, 7, 9, 6, 4, 10, 11 };
		
		// 9641
//		File source = new File(root,"RECAP idea\\May182017_9641\\9641\\2017_05_18_08.04.20\\0000.h5");
//		File dest = new File(root,"RECAP idea\\May182017_9641\\9641\\2017_05_18_08.04.20\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 5, 10, 11, 6, 7, 4, 8, 9 };
//		IS_9641_STEP1 = true;
		
		// 9649
//		File source = new File(root,"RECAP idea\\May232017_9649\\9649\\2017_05_23_07.54.30\\0000.h5");
//		File dest = new File(root,"RECAP idea\\May232017_9649\\9649\\2017_05_23_07.54.30\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 5, 10, 11, 6, 7, 4, 8, 9 };
//		IS_9649_STEP1 = true;

		// 9682
//		File source = new File(root,"RECAP idea\\May242017_9682\\9682\\2017_05_24_08.06.10\\0000.h5");
//		File dest = new File(root,"RECAP idea\\May242017_9682\\9682\\2017_05_24_08.06.10\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 6, 7, 9, 5, 4, 10, 11 };
		
		// 9644??
//		File source = new File(root,"RECAP idea\\May302017_9644\\9644\\2017_05_30_08.29.39\\0000_ori_h5");
//		File dest = new File(root,"RECAP idea\\May302017_9644\\9644\\2017_05_30_08.29.39\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 4, 5, 6, 7, 8, 9, 10, 10 };
//		IS_9644_STEP1 = true;

		// 9669
//		File source = new File(root,"RECAP idea\\May312017_9669\\9669\\2017_05_31_08.44.10\\0000.h5");
//		File dest = new File(root,"RECAP idea\\May312017_9669\\9669\\2017_05_31_08.44.10\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 6, 7, 9, 5, 4, 10, 10 };

		// 9717
//		File source = new File(root,"RECAP idea\\Jun012017_9717\\9717\\2017_06_01_09.11.00\\0000.h5");
//		File dest = new File(root,"RECAP idea\\Jun012017_9717\\9717\\2017_06_01_09.11.00\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 6, 5, 11, 7, 8, 4, 9, 10 };
//		IS_9717_STEP1 = true;
		
//		// 9683
//		File source = new File(root,"RECAP idea\\Jun062017_9683\\9683\\2017_06_06_08.49.11\\0000.h5");
//		File dest = new File(root,"RECAP idea\\Jun062017_9683\\9683\\2017_06_06_08.49.11\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 5, 7, 9, 6, 4, 10, 11 };

		// 9681
//		File source = new File(root,"RECAP idea\\Jun072017_9681\\9681\\2017_06_07_09.09.03\\0000.h5");
//		File dest = new File(root,"RECAP idea\\Jun072017_9681\\9681\\2017_06_07_09.09.03\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 6, 7, 9, 5, 4, 10, 11 };

		// 9713
//		File source = new File(root,"RECAP idea\\9713\\2017_06_08_08.41.59\\0000.h5");
//		File dest = new File(root,"RECAP idea\\9713\\2017_06_08_08.41.59\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 6, 7, 9, 5, 4, 10, 11 };
		
		// 9718
//		File source = new File(root,"RECAP idea\\9718\\2017_06_13_08.04.45\\0000.h5");
//		File dest = new File(root,"RECAP idea\\9718\\2017_06_13_08.04.45\\0001.h5");
//		int [] seq = { 0, 1, 2,3, 8, 5, 7, 9, 6, 4, 10, 11 };

	    if( !source.exists() ) {
			log.error("Could not open source file: {}", source );
			return;
		}

		if( dest.exists() ) {
			Files.delete( dest.toPath() );
		}
		Files.copy(source.toPath(), dest.toPath());

		long source_fid = -1;
		long dest_fid = -1;
		// Open file using the default properties.
		try {
			source_fid = H5.H5Fopen(source.getPath(), HDF5Constants.H5F_ACC_RDONLY, HDF5Constants.H5P_DEFAULT);
			dest_fid = H5.H5Fopen(dest.getPath(), HDF5Constants.H5F_ACC_RDWR, HDF5Constants.H5P_DEFAULT);
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}

		String datasetName = "/Drager_1/waveform";
		// String datasetName2 = "/Drager_1/waveform2";
		deleteDragerWaveforms(dest_fid, datasetName);
		createDragerWaveformDataset(dest_fid, datasetName);
		
		fixDrager(seq, datasetName, source_fid, dest.getPath());
		

		H5.H5Tclose( dest_filetype_id );
		H5.H5Sclose( dest_dataspace_id );
		H5.H5Dclose( dest_dataset_id );

		H5.H5Fclose(dest_fid);
		H5.H5Fclose(source_fid);
		
		System.out.println( "# now run:\nh5repack -f GZIP=1 0001.h5 0002.h5");
	}

	private static void deleteDragerWaveforms(long dest_fid, String datasetName) throws Exception {

		H5.H5Ldelete(dest_fid, datasetName, HDF5Constants.H5P_DEFAULT);

	}

	public static int[] memberDims = new int[] {
			1, // tstamp
			40, // "EKG0", //
			40, // "EKG1", //
			40, // "EKG2", //
			20, // "ABP", //
			20, // "SPO2", //
			10, // "MGM.CO2", //
			20, // "PA", //
			20, // "CVP", //
			40, // "EKG3", //
			20, // "GP1" //
			20, // "GP2" //

	};

	public static String[] memberNames = {
			"tstamp", //
			"EKG0", //
			"EKG1", //
			"EKG2", //
			"ABP", //
			"SPO2", //
			"MGM.CO2", //
			"PA", //
			"CVP", //
			"EKG3", //
			"GP1", //
			"GP2" //
	};

	public static String[] memberLocs = memberNames;
	public static long[] memberFileTypes = new long[] {
			HDF5Constants.H5T_STD_I64BE,  // tstamp
			HDF5Constants.H5T_STD_I32BE, // "EKG0",
			HDF5Constants.H5T_STD_I32BE, // "EKG1", //
			HDF5Constants.H5T_STD_I32BE, // "EKG2", //
			HDF5Constants.H5T_STD_I32BE, // "ABP", //
			HDF5Constants.H5T_STD_I32BE, // "SPO2", //
			HDF5Constants.H5T_STD_I32BE, // "MGM.CO2", //
			HDF5Constants.H5T_STD_I32BE, // "PA", //
			HDF5Constants.H5T_STD_I32BE, // "CVP", //
			HDF5Constants.H5T_STD_I32BE, // "EKG3", //
			HDF5Constants.H5T_STD_I32BE, // "GP1" //
			HDF5Constants.H5T_STD_I32BE // "GP2" //
	};

	public static int[] memberStorage = new int[] {
			8, // tstamp
			4, // "EKG0", //
			4, // "EKG1", //
			4, // "EKG2", //
			4, // "ABP", //
			4, // "SPO2", //
			4, // "MGM.CO2", //
			4, // "PA", //
			4, // "CVP", //
			4, // "EKG3", //
			4, // "GP1" //
			4 // "GP2" //
	};
	private static boolean IS_9641_STEP1;
	private static boolean IS_9649_STEP1;
	private static boolean IS_9644_STEP1;

	private static void createDragerWaveformDataset(long dest_fid, String datasetName) throws Exception {
		long[] chunk_dims = new long[] { 64 };
		long[] init_dims = new long[] { 1 };
		long[] max_dims = new long[] { HDF5Constants.H5S_UNLIMITED };

		dest_filetype_id =

				H5Util.createTypes(getDataSize(), memberDims, memberNames, memberFileTypes, memberStorage);

		dest_dataspace_id = H5.H5Screate_simple(RANK1, init_dims, max_dims);

		long cparms = H5.H5Pcreate(HDF5Constants.H5P_DATASET_CREATE);
		int status = H5.H5Pset_chunk(cparms, RANK1, chunk_dims);
		H5.H5Pset_deflate(cparms, 9);
		dest_dataset_id = H5.H5Dcreate(dest_fid, datasetName, dest_filetype_id, dest_dataspace_id, HDF5Constants.H5P_DEFAULT, cparms, HDF5Constants.H5P_DEFAULT);
		H5.H5Pclose(cparms);

	}

	public static int getDataSize() {
		int data_size = 0;
		for (int indx = 0; indx < numberMembers; indx++)
			data_size += memberStorage[indx] * memberDims[indx];
		return data_size;
	}

	public static long put(byte[] write_data) throws HDF5LibraryException, NullPointerException {
		long[] size = { ++nrecs };
		
		assert( dest_dataset_id >= 0 ) : "DATASET NOT CREATED/CONNECTED!";
		
		H5.H5Dset_extent(dest_dataset_id, size);

		long hspace = H5.H5Dget_space(dest_dataset_id);

		try {
			long[] start = { nrecs - 1 };
			long[] count = { 1 };

			H5.H5Sselect_hyperslab(hspace, HDF5Constants.H5S_SELECT_SET, start, null, count, null);
			H5.H5Dwrite(dest_dataset_id, dest_filetype_id, dest_dataspace_id, hspace, HDF5Constants.H5P_DEFAULT, write_data);
		} finally {
			H5.H5Sclose(hspace);
		}

		return nrecs - 1;
	}


	public static void fixDrager(int[] seq, String datasetName, long source_fid, String fname) throws Exception {
		long source_dsid = -1;

		source_dsid = H5.H5Dopen(source_fid, datasetName, HDF5Constants.H5P_DEFAULT);

		long[] count = { 1 };
		long[] selectedDims = { 1 };

		long fspace = H5.H5Dget_space(source_dsid);
		long mspace = H5.H5Screate_simple(1, selectedDims, null);

		long tid = H5.H5Dget_type(source_dsid);
		long size = H5.H5Tget_size(tid);
		byte[] read_data = new byte[(int)size];
		byte[] prev_data = new byte[(int)size];
		if (log.isDebugEnabled()) {
			H5Util.dumpTypeInfo("SOURCE", tid);
		}
		
		long[] curr_dims, max_dims;
		curr_dims = new long[1];
		max_dims = new long[1];
		H5.H5Sget_simple_extent_dims(fspace, curr_dims, max_dims);
		

		
		for (long pos = 0; pos < curr_dims[0]; pos++) {
			long[] start = { pos };
			if( pos % 80 == 0 ) {
				System.out.println();
			}

			H5.H5Sselect_hyperslab( //
					fspace, // file space
					HDF5Constants.H5S_SELECT_SET, // command
					start, // start
					null, // stride
					count, // count
					null); // set block to 1

			prev_data = Arrays.copyOf(read_data, read_data.length);
			int err = H5.H5Dread(source_dsid, tid, mspace, fspace, HDF5Constants.H5P_DEFAULT, read_data);
			if (err < 0)
				break;

			byte [] shuffle_data = shuffle(seq, read_data );
			if( check_data(pos, seq, shuffle_data, read_data) == true ) {
				System.out.print(".");
			} else {
				System.out.print("RESET AT LINE: " + pos);
				seq = reset_seq(seq, read_data, prev_data);
				shuffle_data = shuffle(seq, read_data );
				if( check_data(pos, seq, shuffle_data, read_data) == false ) {
					log.error("INTERNAL ERROR...could not shuffle");
					System.exit(0);
				}
			}
			put( shuffle_data);
		}

		H5.H5Sclose(fspace);
		H5.H5Sclose(mspace);
		H5.H5Tclose(tid);

		H5.H5Dclose(source_dsid);

		System.out.print("\n# Seq:");
		for( int s : seq ) {
			System.out.print(" ");
			System.out.print(s);
		}
		System.out.println("\n# Done");
		return;
	}

	private static int[] reset_seq(int[] ori_seq, byte[] read_data, byte[] prev_data) {
		int [] seq = null;
		if( IS_9641_STEP1 ) {
			seq = new int[] { 0, 1, 2,3, 8, 5, 7, 9, 6, 4, 10, 11 };
			IS_9641_STEP1 = false;
			return seq;
		}
		if( IS_9649_STEP1 ) {
			seq = new int[] { 0, 1, 2,3, 8, 5, 6, 9, 7, 4, 10, 11 };
			IS_9649_STEP1 = false;
			return seq;
		}
		if( IS_9644_STEP1 ) {
			seq = new int[] { 0, 1, 2,3, 8, 5, 6, 9, 4, 7, 10, 10 };
			IS_9644_STEP1 = false;
			return seq;
		}
		if( IS_9717_STEP1 ) {
			seq = new int[] { 0, 1, 2,3, 8, 5, 6, 9, 7, 4, 10, 11 };
			IS_9717_STEP1 = false;
			return seq;
		}
				// tstamp 0
		 // "EKG0", //1
		 // "EKG1", //2
		 // "EKG2", //3
		 // "ABP", //4
		 // "SPO2", //5
		 // "MGM.CO2", //6
		 // "PA", //7
		 // "CVP", //8
		 // "EKG3", //9
		 // "GP1" //10
		 // "GP2" //11
		int ts = 0;
		int ekg0 = 1;
		int ekg1 = 2;
		int ekg2 = 3;
		int abp = 4;
		int spo2 = 5;
		int mgm = 6;
		int pa = 7;
		int cvp = 8;
		int ecg3 = 9;
		int gp1 = 10;
		int gp2 = 11;
		ByteBuffer bb = ByteBuffer.wrap(read_data);
		for( ecg3 = 0; ecg3 < memberNames.length ; ecg3++ ) {
			int offset = getSourceOffset(ori_seq, ecg3, false);
			bb.position(offset);
			int val = bb.getInt();
			if( val == 1 ) {
				// we found ecg3
				if( ecg3 == 4) {
					abp = 8;  // best guess?? higher pa
					spo2 = 5;  // wf that goes negative
					mgm = 7;  // only column of length 10 in DAT file
					pa = 9;    // higher than cvp
					cvp = 6;   // low, stable value
					ecg3 = 4;  // redundant
					gp1 = 10;  // positive only value avg around 2500
					gp2 = 11;  // comes and goes, but mostly a constant negative value, -420...-428
					seq = new int[] { ts, ekg0, ekg1, ekg2, abp, spo2, mgm, pa, cvp, ecg3, gp1, gp2 };
					break;
				}
			}
		}
		return seq;
	}

	private static boolean check_data(long pos, int[] seq, byte[] shuffle_data, byte[] read_data) {
		int off = getDestOffset( 9);  // field 9 is ECG3...must be 1
		ByteBuffer bb = ByteBuffer.wrap(shuffle_data);
		bb.position(off);
		int val = bb.getInt();
		
		boolean pass = (val == 1);
		if( pass && IS_9641_STEP1 ) {
			pass = ( pos < 1500 ); 
		}
		if( pass && IS_9649_STEP1 ) {
			pass = ( pos < 10864 ); 
		}
		if( pass && IS_9644_STEP1 ) {
			pass = ( pos < 4680 ); 
		}
		if( pass && IS_9717_STEP1 ) {
			pass = ( pos < 3080 ); 
		}
		if( !pass ) {
			dump_src_fields( read_data, seq );
			dump_dest_fields( shuffle_data );
			return false;
		}
		return true;
	}

	private static void dump_src_fields(byte[] read_data, int[] seq) {
		System.out.println("SRC FIELDS...ordered by occurrance");
		for( int i = 0 ; i < memberNames.length; i++) {
			int ii = seq[i];
			int offset = getSourceOffset( seq, ii, false );
			int val = getIntVal( read_data, offset );
			System.out.println("  " + memberNames[i] + "\toffset=" + offset + "\tvalue=" + val );
		}
	}

	private static void dump_dest_fields(byte[] shuffle_data) {
		System.out.println("DEST FIELDS...ordered by occurrance");
		for( int i = 0 ; i < memberNames.length; i++) {
			int offset = getDestOffset( i);
			int val = getIntVal( shuffle_data, offset );
			System.out.println("  " + memberNames[i] + "\toffset=" + offset + "\tvalue=" + val );
		}
	}

	private static int getIntVal(byte[] shuffle_data, int offset) {
		ByteBuffer bb = ByteBuffer.wrap(shuffle_data);
		bb.position(offset);
		return bb.getInt();
	}

	private static int getSourceOffset( int [] seq, int idx, boolean verbose ) {
		int offset = 0;
		if(verbose) {
			System.out.print("\t\t\t\tfield=" + idx );
		}
		for(int i = 0; i < seq.length; i++ ) {
			int ii = seq[i];
			if( ii >= idx ) {
				continue;
			}
			int n = memberDims[i] * memberStorage[i];
			offset += n;
			if( verbose ) {
				System.out.print( "[" + memberNames[i] + " " + n + "/" + ii + "]");
			}
		}
		
		if( verbose ) {
			System.out.println();
		}
		return offset;
	}
	
	private static int getDestOffset(int idx ) {
		int offset = 0;
		for(int i = 0; i < idx; i++ ) {
			int n = memberDims[i] * memberStorage[i];
			offset += n;
		}
		return offset;
	}
	
	private static byte [] shuffle(int [] seq, byte[] read_data) {
		byte [] out = new byte[ read_data.length ];
		int pos = 0;
		for( int i = 0; i < seq.length; i++ ) {
			int idx = seq[i];
			int offset = getSourceOffset(seq, idx, false);
			int n = memberDims[i] * memberStorage[i];
			log.debug("copying field: {} sz={} from sourcepos={} to dest={}", memberNames[i], n, offset, pos);
			if( pos != getDestOffset(i)) {
				log.error("FAILED TO POSITION DATA FIELD {} pos={} needed={}", i, pos, getDestOffset(i));
				System.exit(0);
			}
			for( int j = 0; j < n ; j++) {
				out[pos++] = read_data[j+offset];
			}
		}
		
		return out;
	}

}
