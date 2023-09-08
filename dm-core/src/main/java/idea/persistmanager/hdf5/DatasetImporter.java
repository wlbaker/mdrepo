package idea.persistmanager.hdf5;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.List;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5Exception;
import idea.conf.DeviceConfiguration;
import idea.message.StreamID;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DatasetImporter extends H5ImportBaseImpl {

	private static int model_idx = 1;

	private Class<? extends PersistentItem> modelClass;
	private String datasetName;

	H5DatasetCODEC codec;

	private StreamID sid;

	private RpStream stream_hints;

	private String parentName;

	private DeviceConfiguration conf;

	public DatasetImporter(long file_id, String parentName, String datasetName) {
		super(file_id);
		this.parentName = parentName;
		this.datasetName = "/" + datasetName;
		if (parentName != null) {
			this.datasetName = "/" + parentName + this.datasetName;
		}
	}

	public void setStreamHint(RpStream stream) {

		this.stream_hints = stream;
	}

	@Override
	public void connect() throws IOException {
		try {
			super.connect(datasetName); // opens the H5 dataset and assignes value to dataset_id

			if (dataset_id == 0) {
				log.error("Cannot open dataset: {}", datasetName);
				return; // maybe should even be an exception similar to file-not-found
			}
			if (stream_hints == null) {
				conf = H5Util.readMetaAttribute(dataset_id, datasetName);
				if (conf == null) {
					// some datasets don't have the SIGNALS attribute. Annotations. Tranlog. Maybe
					// Alarms.
				} else {
					List<RpStream> streams = conf.getStreams();
					if (streams == null || streams.size() != 1) {
						log.error("Incorrect number of streams from ATTRIBUTE: {}", streams);
					} else {
						stream_hints = streams.get(0);
					}
				}
			}

			if (codec == null && dataset_id != 0) {
				// last resort
				codec = H5Util.readDescriptionsFromDataset(dataset_id, stream_hints);
				stream_hints = null; // dont need this anymore
			}

			if (codec == null) {
				return; // empty dataset or does not exist
			}

			int sid_code = H5Util.readIntAttribute(dataset_id, "streamID");
			if (sid_code == 0) {
				// Handle backward compatibility
				String s_name = datasetName;
				int idx = datasetName.lastIndexOf('/');
				if (idx > 0) {
					s_name = datasetName.substring(idx + 1);
				}
				StreamID streamID = StreamID.fromName(s_name);
				if (streamID != null) {
					sid_code = streamID.getCode();
				} else {
					if (s_name.equalsIgnoreCase("annotations")) {
						sid_code = StreamID.ANNOTATION.getCode();
					} else if (s_name.equalsIgnoreCase("settings")) {
						sid_code = StreamID.SETTINGS.getCode();
					} else if (s_name.equalsIgnoreCase("numerics")) {
						sid_code = StreamID.MEASUREMENT.getCode();
					} else if (s_name.equalsIgnoreCase("waveforms")) {
						sid_code = StreamID.WAVEFORM.getCode();
					} else if (s_name.equalsIgnoreCase("tranlog")) {
						sid_code = StreamID.TRANLOG.getCode();
					} else if (s_name.equalsIgnoreCase("header")) {
						log.error("need a new stream id for header");
						sid_code = StreamID.MEASUREMENT_2.getCode();
					} else {
						log.error("UNKNOWN STREAM IDEA FOR NAME=" + s_name);
						sid_code = StreamID.MEASUREMENT_3.getCode();
					}
				}
			}

			sid = StreamID.fromCode(sid_code);
			if (sid == null) {
				throw new IOException("Invalid signal ID: " + sid_code);
			}

			modelClass = ModelUtil.findCachedModel(Arrays.asList(codec.getMetrics()));

			if (modelClass == null) {

				String modelName = "";
				if (parentName != null)
					modelName += parentName;
				modelName += datasetName;
				modelName = modelName.replace("/", "");
				modelName = modelName.replace("_0", "");
				modelName = "idea.model.auto.Auto" + modelName + model_idx;
				model_idx++;

				try {
					modelClass = ModelUtil.createDynamicModel(modelName, Arrays.asList(codec.getMetrics()));
				} catch (Exception e) {
					log.error("could not creating dynamic model", e);
				}
			}
		} catch (IOException e) {
			throw e; // don't wrap exception
		} catch (Exception e) {
			throw new IOException(e);
		}
	}

	@Override
	public PersistentItem next() throws IOException {
		try {
			return _next(); // a shim
		} catch (NullPointerException e) {
			throw new IOException(e);
		} catch (HDF5Exception e) {
			throw new IOException(e);
		}
	}

	@Override
	public ArchiveMetaData getMeta() throws IOException {
		if (codec == null) {
			return null;
		}
		ArchiveMetaData meta = null;
		if (codec.numberMembers > 1 && "tstamp".contentEquals(codec.memberNames[0])) {
			try {
				meta = _getMeta(codec.getMemoryTID());
			} catch (Exception e) {
				throw new IOException(e);
			}
		}

		return meta;
	}

	private PersistentItem _next() throws IOException, NullPointerException, HDF5Exception {

		if (curr_dims == null || pos >= curr_dims[0]) {
			return null;
		}

		long[] start = { pos };
		long[] count = { 1 };

		long[] selectedDims = { 1 };

		long fspace = H5.H5Dget_space(dataset_id);
		long mspace = H5.H5Screate_simple(1, selectedDims, null);

		long memory_tid = codec.getMemoryTID();
		long size = H5.H5Tget_size(memory_tid);
		byte[] read_data = new byte[(int) size];

//		if (log.isDebugEnabled()) {
//			H5Util.dumpTypeInfo("     MEMORY TID: ", codec.getMemoryTID());
//			H5Util.dumpTypeInfo("       FILE TID: ", codec.getFileTID() );
//			int file_tid = H5.H5Dget_type(dataset_id);
//			H5Util.dumpTypeInfo("ACTUAL FILE TID: ", file_tid );
//			H5.H5Tclose(file_tid);
//		}

		// error here how to deal with annotation data items?
		// error here how to deal with alarm data items?
		PersistentItem item;
		do {
			item = null;
			if (pos >= curr_dims[0]) {
				break;
			}
			H5.H5Sselect_hyperslab( //
					fspace, // file space
					HDF5Constants.H5S_SELECT_SET, // command
					start, // start
					null, // stride
					count, // count
					null); // set block to 1

			// memory space/type does not have to match the file space/type very closely.
			// fields will be
			// matched up based on name, and missing fields are ignored,
			int err = H5.H5Dread(dataset_id, memory_tid, mspace, fspace, HDF5Constants.H5P_DEFAULT, read_data);
			if (err < 0)
				break;
			ByteBuffer bb = ByteBuffer.wrap(read_data);

			item = ModelUtil.getModelFromDataClass(modelClass);
			item.setStreamID(sid.getCode());
			item.setSource(this);

			codec.decode(item, bb);
			item.setOid(pos);
			pos++;
		} while (pos <= 1 && item.getTm() == null);

		try {
			H5.H5Sclose(fspace);
		} catch (Exception ex2) {
		}
		try {
			H5.H5Sclose(mspace);
		} catch (Exception ex2) {
		}
//		try {
//			H5.H5Tclose(file_tid);
//		} catch (HDF5Exception ex2) {
//		}

		return item;
	}

	public void rewind() {
		pos = 0;
	}

	@Override
	public String getName() {
		return datasetName;
	}

	public long getDatasetId() {
		return dataset_id;
	}

	public PersistentItem read(int pos) {
		PersistentItem message = null;
		try {
			this.pos = pos;
			message = _next();
		} catch (NullPointerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (HDF5Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return message;
	}

	public void skip(int count) {
		this.pos += count;
	}

	public void update(int block_pos, PersistentItem block) throws NullPointerException, HDF5Exception {
		long[] selectedDims = { 1 };

		long fspace = H5.H5Dget_space(dataset_id);
		long mspace = H5.H5Screate_simple(1, selectedDims, null);
		long tid = H5.H5Dget_type(dataset_id);
		H5.H5Sget_simple_extent_dims(fspace, curr_dims, max_dims);

		if (block_pos < 0) {
			// it is hard to determin position since buffered reads occur in the H5 files
			// themselves. Needs to be
			// carried with the persistentitem itself. Transient.
			block_pos = (int) block.getOid();
		}
		long[] start = { block_pos };
		long[] count = { 1 };

		int size = (int) H5.H5Tget_size(tid);

		H5.H5Sselect_hyperslab( //
				fspace, // file space
				HDF5Constants.H5S_SELECT_SET, // command
				start, // start
				null, // stride
				count, // count
				null); // set block to 1

		// H5.H5Dread(dataset_id, tid, mspace, fspace, HDF5Constants.H5P_DEFAULT,
		// read_data);

		byte[] read_data = new byte[size];
		ByteBuffer bb = ByteBuffer.wrap(read_data);
		codec.encode(block, bb);

		H5.H5Sselect_hyperslab( //
				fspace, // file space
				HDF5Constants.H5S_SELECT_SET, // command
				start, // start
				null, // stride
				count, // count
				null); // set block to 1
		H5.H5Dwrite(dataset_id, tid, mspace, fspace, HDF5Constants.H5P_DEFAULT, read_data);

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

	@Override
	public Class<? extends PersistentItem> getModel(StreamID sid) {
		if (!sid.equals(this.sid)) {
			return null;
		}
		return modelClass;
	}

	@Override
	public StreamID[] getStreams() {
		return new StreamID[] { sid };
	}

	@Override
	public RpDevice getStaticCapabilities() {
		return conf;
	}

	public StreamID getStreamID() {
		return sid;
	}

	public RpMetric[] getMetrics() {
		return codec.getMetrics();
	}

}
