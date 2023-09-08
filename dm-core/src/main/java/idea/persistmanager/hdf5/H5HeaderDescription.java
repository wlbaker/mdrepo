package idea.persistmanager.hdf5;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import hdf.hdf5lib.HDF5Constants;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public final class H5HeaderDescription {

	// Using Java Externalization will add a two-byte object header in
	// the stream, which needs to be called out in the datatypes.

	public static final int KEY_MAXSTRINGSIZE = 80;
	public static final int VALUE_MAXSTRINGSIZE = 160;

	public static int numberMembers = 2;
	public static int[] memberDims = { 1, 1 };

	public static String[] memberNames = { "key", "value" };
	public static long[] memberMemTypes = { HDF5Constants.H5T_C_S1, HDF5Constants.H5T_C_S1 };
	public static long[] memberFileTypes = { HDF5Constants.H5T_C_S1, HDF5Constants.H5T_C_S1 };
	public static int[] memberStorage = { KEY_MAXSTRINGSIZE, VALUE_MAXSTRINGSIZE };

	private RpSubject header;

	public H5HeaderDescription() {
		header = new RpSubject();
	}

	public H5HeaderDescription(RpSubject header) {
		this.header = header;
	}

	public RpSubject getSubjectInfo() {
		return header;
	}

	// Data size is the storage size for the members not the object.
	// Java Externalization also adds a 4-byte "Magic Number" to the
	// beginning
	// of the data stream
	public static int getTotalDataSize(int qty) {
		int data_size = 0;
		for (int indx = 0; indx < numberMembers; indx++) {
			data_size += memberStorage[indx] * memberDims[indx];
		}
		return qty * data_size;
	}

	public static int getDataSize() {
		int data_size = 0;
		for (int indx = 0; indx < numberMembers; indx++)
			data_size += memberStorage[indx] * memberDims[indx];
		return data_size;
	}

	public static int getOffset(int memberItem) {
		int data_offset = 0;
		for (int indx = 0; indx < memberItem; indx++)
			data_offset += memberStorage[indx];
		return data_offset;
	}

	// Each data member field must be shown how to be written and read.
	// Strings need to be handled by bytes.
	public void decode(RpSubject header, ByteBuffer bb) {

		byte[] tempbuf = new byte[KEY_MAXSTRINGSIZE + VALUE_MAXSTRINGSIZE];

		while (bb.hasRemaining()) {
			for (int indx = 0; indx < KEY_MAXSTRINGSIZE; indx++) {
				tempbuf[indx] = bb.get();
			}
			String key = new String(tempbuf).trim();
			for (int indx = 0; indx < VALUE_MAXSTRINGSIZE; indx++) {
				tempbuf[indx] = bb.get();
			}
			String value = new String(tempbuf).trim();

			if ("company".equals(key)) {
				header.setCompany(value);
			} else if ("organization".equals(key)) {
				header.setOrganization(value);
			} else if ("studyTitle".equals(key)) {
				header.setStudyTitle(value);
			} else if ("location".equals(key)) {
				header.setLocation(value);
			} else if ("sampleDate".equals(key)) {
				if (value == null) {
					header.setSurgeryDate(null);
				} else {
					try {
						// maybe it is just a long
						long l = Long.parseLong(value);
						header.setSurgeryDate(new Date(l));
					} catch (Exception e) {
						// ok, not a long, try a default format date
						try {
							DateFormat df = new SimpleDateFormat("E MMM d HH:mm:ss z yyyy");
							header.setSurgeryDate(df.parse(value));
						} catch (ParseException e1) {
							// ok not full either. Dunno.
							e1.printStackTrace();
						}
					}
				}
			} else if ("subjectNumber".equals(key)) {
				header.setSeqNo(value);
			} else if ("medicalId".equals(key)) {
				header.setMedicalId(value);
			} else if ("operator".equals(key)) {
				header.setOperator(value);
			} else if ("notes".equals(key)) {
				header.setNotes(value);
			} else {
				log.error("ignoring import header field: {}  value: {}", key, value);
			}
		}

		return;
	}

	public byte[] encode(ByteBuffer bb, String key, String value) throws IOException {

		// assert() there must be NUM_FIELDS number of fields....currently 9

		if (value == null || value.length() == 0) {
			return null; // don't save null values
		}

		for (int indx = 0; indx < KEY_MAXSTRINGSIZE; indx++) {
			if (indx < key.length())
				bb.put((byte) key.charAt(indx));
			else
				bb.put((byte) 0);
		}
		for (int indx = 0; indx < VALUE_MAXSTRINGSIZE; indx++) {
			if (indx < value.length())
				bb.put((byte) value.charAt(indx));
			else
				bb.put((byte) 0);
		}

		return bb.array();
	}

}
