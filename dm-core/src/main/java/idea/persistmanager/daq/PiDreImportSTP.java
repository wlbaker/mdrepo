package idea.persistmanager.daq;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import lombok.extern.slf4j.Slf4j;


@Slf4j
public class PiDreImportSTP {

	boolean verbose = false;

	static String decodeString(ByteBuffer bb) {
		int len = bb.getInt();
		int rt = len;
		StringBuffer buf = new StringBuffer();
		while (len-- > 0) {
			buf.append((char) bb.get());
		}

		return buf.toString();
	}

	static void encodeString( OutputStream out, String s) throws IOException {
		ByteBuffer bb = ByteBuffer.allocate( s.length() + 4);
		bb.putInt( s.length() );
		
		for ( int i = 0; i < s.length(); i++ ) {
			bb.put( (byte) s.charAt(i));
		}

		out.write( bb.array() );
	}

	static void encodeInt( OutputStream out, int val) throws IOException {
		ByteBuffer bb = ByteBuffer.allocate( 4);
		bb.putInt( val );

		out.write( bb.array() );
	}

	static void encodeByte( OutputStream out, int val) throws IOException {
		ByteBuffer bb = ByteBuffer.allocate( 1);
		bb.put( (byte)val );

		out.write( bb.array() );
	}

	static void encodeBytes( OutputStream out, byte [] buf) throws IOException {
		
		ByteBuffer bb = ByteBuffer.allocate( buf.length );
		for ( int i = 0; i < buf.length; i++ ) {
			bb.put( buf[i]);
		}

		out.write( bb.array() );
	}

	static void dump_block_to_array(ByteBuffer bb, int count, float[] farr) {
		for (int i = 0; i < count; i++) {
			float f = bb.getFloat();
			farr[i] = f;
			System.out.printf(" %4.2f", f);

			if (i % 16 == 15)
				System.out.println();
		}
	}

	static void decodeFloatBlock(ByteBuffer bb, float[] dest) {
		for (int i = 0; i < dest.length; i++) {
			dest[i] = bb.getFloat();
		}
	}

	static void encodeFloatBlock(OutputStream out, float[] dest) throws IOException {
		ByteBuffer bb = ByteBuffer.allocate( 4 * dest.length );  // sizeof(float) * count
		
		for (int i = 0; i < dest.length; i++) {
			bb.putFloat( dest[i] );
		}
		out.write(bb.array());
	}

	static void decodeDoubleBlock(ByteBuffer bb, float [] dest) {
		for (int i = 0; i < dest.length; i++) {
			double f = bb.getDouble();
			dest[i] = (float)f;
		}
	}

	static void encodeDoubleBlock(ByteBuffer bb, float [] dest) {
		for (int i = 0; i < dest.length; i++) {
			bb.putDouble( (double)dest[i] );
		}
	}

	static void dump_int4_to_array(ByteBuffer bb, int count, int[] arr) {
		for (int i = 0; i < count; i++) {
			int val = bb.getInt();
			arr[i] = val;
			if (val == -1) {
				return;
			}
			System.out.printf(" %4.4d", val);
			if (i % 8 == 7)
				System.out.println();
		}
	}

	static void dump_int4(ByteBuffer bb, int count) {
		for (int i = 0; i < count; i++) {
			int val = bb.getInt();
			if (val == -1) {
				return;
			}
			System.out.printf(" %4.4d", val);
			if (i % 8 == 7)
				System.out.println();
		}
	}

	static void dump_colors_102(ByteBuffer bb) {
		int seq = 1;

		int sz = bb.getInt();
		if (sz != 32) {
			System.out.printf("EXPECTING INT ARRAY SZ 32 != %d\n", sz);
		}
		for (int i = 0; i < sz; i++) {
			int c0 = bb.get();
			if (c0 == -1) {
				return;
			}
			if (c0 != 0) {
				System.out.printf("ERROR IN COLOR [c0=%d] ", c0);
			}
			int c1 = bb.get();
			int c2 = bb.get();
			int c3 = bb.get();

			System.out.printf("%d: rgb=%2d-%2d-%2d\n", seq++, c1, c2, c3);
		}
	}

	static int decodeAscii(ByteBuffer bb, int count, byte[] buf, boolean variable_length) {

		int consec_zero = 0;

		int pos = 0;
		int ii = 0;
		for (; pos < count; pos++) {
			if (bb.hasRemaining() == false) {
				break;
			}
			byte ch = bb.get();

			buf[ii++] = ch;
			if (ch < ' ' || ch > '~') {
				System.out.printf("[%2x] ", ch);
			} else {
				System.out.printf("%c    ", ch);
			}
			if (pos % 16 == 15)
				System.out.println();

			if (ch == 0 && variable_length) {
				consec_zero++;
			} else {
				consec_zero = 0;
			}

			if (consec_zero == 4) {
				break;
			}
		}
		System.out.println();

		return pos;
	}

	static int parse_accessories(byte[] input, boolean with_seq) {

		ByteBuffer bb = ByteBuffer.wrap(input);
		int seq = 0;
		do {
			int nch = bb.getInt();

			if (nch == 0) {
				System.out.printf("empty accessories\n");
				break;
			}

			if (with_seq) {
				System.out.printf("%2d ", ++seq);
			}

			System.out.printf("string[%d]: ", nch);
			for (int i = 0; i < nch; i++) {
				System.out.printf("%c", (char) bb.get());

			}
			System.out.println();

			int port = bb.get();
			System.out.printf(" PORT: [%d]\n", port);

			int opt = 0; // only used for accessories
			int nopt = bb.getInt(); // only used for accessories // 4 bytes, big
									// endian...number of options

			for (int i = 0; i < nopt; i++) {
				int opt_val = bb.getInt();
				System.out.printf("OPT %d/%d: %d\n", opt++, nopt, opt_val);
			}

			// 4 bytes, big endian--label string
			nch = bb.getInt();

			System.out.printf("  LABEL [%d]: ", nch);
			for (int i = 0; i < nch; i++) {
				System.out.printf("%c", (char) bb.get());

			}
			System.out.println();

		} while (true);

		return seq;
	}

	static int parse_strings(byte[] input, boolean with_seq) {

		ByteBuffer bb = ByteBuffer.wrap(input);
		int seq = 0;
		do {
			int nch = bb.getInt();

			if (nch == 0) {
				break;
			}

			if (with_seq) {
				System.out.printf("%2d ", ++seq);
			}

			System.out.printf("string[%d]: ", nch);
			for (int i = 0; i < nch; i++) {
				System.out.printf("%c", bb.get());

			}
			System.out.println();

		} while (true);

		return seq;
	}

	public static void encode_01(File dest, STP stp) throws IOException {

		final FileOutputStream out = new FileOutputStream(dest);

		encodeInt( out, 1);  // h0
		encodeInt( out, 400);  // h1

		encodeFloatBlock(out, stp.signal);
		encodeFloatBlock(out, stp.unitHigh);
		encodeFloatBlock(out, stp.unitLow);
		encodeFloatBlock(out, stp.vHigh);
		encodeFloatBlock(out, stp.vLow);
		encodeFloatBlock(out, stp.precision);
		encodeFloatBlock(out, stp.fdevinfo);
		encodeFloatBlock(out, stp.channel);

		encodeBytes( out, stp.ascii0 );
		encodeFloatBlock(out, stp.colorAssign);
		encodeFloatBlock(out, stp.b1);
		encodeFloatBlock(out, stp.b2);
		encodeFloatBlock(out, stp.b3);
		encodeFloatBlock(out, stp.b4);
		encodeFloatBlock(out, stp.b5);
		encodeFloatBlock(out, stp.b6);
		encodeFloatBlock(out, stp.b7);
		encodeFloatBlock(out, stp.b8);
		
		encodeInt( out, stp.h3);
		
		for (int i = 0; i < stp.labels.length; i++) {
			encodeString(out, stp.labels[i]);
		}
		for (int i = 0; i < stp.config.length; i++) {
			encodeString(out, stp.config[i]);
		}
		for (int i = 0; i < stp.label_graph.length; i++) {
			encodeString(out, stp.label_graph[i]);
		}
		
		encodeInt( out, stp.h5);

		encodeBytes(out, stp.ascii1);

		encodeInt( out, stp.h6);
		encodeByte( out, stp.skip);

		encodeBytes(out, stp.ascii2);
		
		return;
	}

	static STP decode_01(ByteBuffer bb) {

		STP stp = new STP();

		decodeFloatBlock(bb, stp.signal);
		decodeFloatBlock(bb, stp.unitHigh);
		decodeFloatBlock(bb, stp.unitLow);
		decodeFloatBlock(bb, stp.vHigh);
		decodeFloatBlock(bb, stp.vLow);
		decodeFloatBlock(bb, stp.precision);
		decodeFloatBlock(bb, stp.fdevinfo);		
		decodeFloatBlock(bb, stp.channel);

		stp.ascii0 = new byte[20*4];
		decodeAscii(bb, stp.ascii0.length, stp.ascii0, false);

		decodeFloatBlock(bb, stp.colorAssign);
		decodeFloatBlock(bb, stp.b1);
		decodeFloatBlock(bb, stp.b2);
		decodeFloatBlock(bb, stp.b3);
		decodeFloatBlock(bb, stp.b4);
		decodeFloatBlock(bb, stp.b5);
		decodeFloatBlock(bb, stp.b6);
		decodeFloatBlock(bb, stp.b7);
		decodeFloatBlock(bb, stp.b8);

		stp.h3 = bb.getInt();

		for (int i = 0; i < stp.labels.length; i++) {
			stp.labels[i] = decodeString(bb);
		}

		for (int i = 0; i < stp.config.length; i++) {
			stp.config[i] = decodeString(bb);
		}

		int n_strings = 0;
		for (n_strings = 0; n_strings < stp.label_graph.length; n_strings++) {
			stp.label_graph[n_strings] = decodeString(bb);
		}

		stp.h5 = bb.getInt(); // 0xb0

		stp.ascii1 = new byte[16*11];
		decodeAscii(bb, stp.ascii1.length, stp.ascii1, false);

		stp.h6 = bb.getInt(); // 0x18
		stp.skip = bb.get(); // FIXME!!!

		stp.ascii2 = new byte[10*40 + 1];
		decodeAscii(bb, stp.ascii2.length, stp.ascii2, false);

		return stp;
	}

	static String layout_text[] = { "1 - One Graph", "2 - Two Bottom", "3 - Two Equal", "4 - Two Top",
			"5 - Three Bottom", "6 - Three Equal", "7 - Three Top", "8 - Four Graphs", "9 - Custom", };

	static String filter_text[] = { "None", "Butterworth", "Chebyshev", "Elliptic", "Bessel", "Running Average" };

	static String format_text[] = { "Scaled Ascii (TXT)", "Scaled Binary (SGL)", "Unscaled Binary (I16)",
			"Voltage Ascii (TXT)", "Voltage Binary (SGL)" };

	static String limit_text[] = { "+/- 10.0", "+/- 5.0", "+/- 2.5", "+/- 2.0", "+/- 1.0", "+/- 0.5", "+/- 0.25",
			"+/- 0.20", "+/- 0.10", "+/- 0.05" };

	static STP decode_102(ByteBuffer bb) {
		// unsigned char buf[4*1024];
		STP stp = new STP();
		
		int sz;

		stp.h3 = bb.getInt();
		decodeDoubleBlock(bb, stp.unitHigh);
		decodeDoubleBlock(bb, stp.unitLow);
		decodeDoubleBlock(bb, stp.vHigh);
		decodeDoubleBlock(bb, stp.vLow);

		System.out.printf("\n%4x SETTINGS\n", bb.position());
		double sample_rate = bb.getDouble();
		double two = bb.getDouble();
		double unk = bb.getDouble();
		System.out.printf(" * sample rate: %f\n", sample_rate);
		System.out.printf(" *         two: %f\n", two);
		System.out.printf(" *         unk: %f\n", unk);

		decodeDoubleBlock(bb, stp.channel );//???
		decodeDoubleBlock(bb, stp.vLow );  //???
		decodeDoubleBlock(bb, stp.vHigh);  //???
		decodeDoubleBlock(bb, stp.other_102 );

		stp.h4_102 = bb.getInt();

		for (int i = 0; i < stp.labels.length; i++) {
			stp.labels[i] = decodeString(bb);
		}

		System.out.printf("\n%4x CONFIG-AA\n", bb.position());
		for (int i = 0; i < 8; i++) {
			String sbuf = decodeString(bb);
			System.out.printf("%2d ", i + 1);
			if (sbuf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", sbuf);
			}
		}

		System.out.printf("\n%4x SIGS TO RECORD\n", bb.position());
		for (int i = 0; i < 28; i++) {
			String buf = decodeString(bb);
			System.out.printf("%2d ", i + 1);
			if (buf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", buf);
			}
		}

		System.out.printf("\n%4x SIGS TO GRAPH\n", bb.position());
		for (int n_strings = 0; n_strings < 16; n_strings++) {
			String sbuf = decodeString(bb);
			System.out.printf("%2d ", n_strings + 1);
			if (sbuf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", sbuf);
			}
		}

		System.out.printf("\n%4x HR SOURCES AND VITALS MESSAGES\n", bb.position());
		for (int n_strings = 0; n_strings < 16; n_strings++) {
			String sbuf = decodeString(bb);
			System.out.printf("%2d ", n_strings + 1);
			if (sbuf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", sbuf);
			}
		}

		byte[] buf = new byte[1024];

		System.out.printf("\n%4x BINARY2-BB\n", bb.position());
		decodeAscii(bb, 21 * 16, buf, false);
		parse_strings(buf, false);

		int timed_save = bb.get();
		int auto_save = bb.get();
		int continuous_save = bb.get();
		int enable_marker = bb.get();
		int zero0 = bb.get();
		int zero1 = bb.get();

		System.out.printf("\nSave/File info\n");
		System.out.printf("Timed Save: %d\n", timed_save);
		System.out.printf("Auto Save: %d\n", auto_save);
		System.out.printf("Continuous Save: %d\n", continuous_save);
		System.out.printf("Enable Marker: %d\n", enable_marker);
		System.out.printf("z0,z1: %d,%d\n", zero0, zero1);

		int h5 = bb.getInt();
		System.out.printf("\n**** h5=%d\n", h5);

		System.out.printf("\n%4x BINARY3xx\n", bb.position());
		dump_int4(bb, 10);
		System.out.printf("\n%4x UNK1\n", bb.position());
		dump_int4(bb, 1);
		System.out.printf("\n%4x CHANNELS\n", bb.position());
		dump_int4(bb, 16);
		System.out.printf("\n%4x LIMITS\n", bb.position());
		int[] limits = new int[16];
		dump_int4_to_array(bb, 16, limits);
		for (int i = 0; i < 16; i++) {
			System.out.printf(" * LIM SIG%d: %s\n", i, limit_text[limits[i]]);
		}

		System.out.printf("\n%4x DEVINFO3\n", bb.position());
		int[] devinfo = new int[9];
		dump_int4_to_array(bb, 9, devinfo);
		System.out.printf("\n");
		System.out.printf("* DEVICE ID: %d\n", devinfo[0]);
		System.out.printf("* NRSE/RSE: %d\n", devinfo[2]);
		System.out.printf("* Recording Mode: %s\n", format_text[devinfo[3]]);
		System.out.printf("* Seq No: %d\n", devinfo[4]);
		System.out.printf("* Data Set Size(sec): %d\n", devinfo[5]);
		System.out.printf("* Timed Save (sec): %d\n", devinfo[6]);
		System.out.printf("* Auto Save (sec): %d\n", devinfo[7]);
		System.out.printf("* Marker Number: %d\n", devinfo[8]);
		// printf( "* Opt 1: %d\n", devinfo[9] );
		// printf( "* Opt 2: %d\n", devinfo[10] );
		// printf( "* Opt 3: %d\n", devinfo[11] );
		// printf( "* Opt 4: %d\n", devinfo[12] );

		System.out.printf("\n%4x Filter Type\n", bb.position());
		int[] filter = new int[16];
		dump_int4_to_array(bb, 16, filter);
		System.out.printf("\n");
		for (int i = 0; i < 16; i++) {
			System.out.printf("* FILTER [%d]: %s\n", i, filter_text[filter[i]]);
		}

		System.out.printf("\n%4x Other?\n", bb.position());
		int[] other = new int[48 + 7];
		dump_int4_to_array(bb, 48 - 3 + 7, other);

		System.out.printf("\n%4x BINARY3b\n", bb.position());
		int[] arr = new int[92];
		dump_int4_to_array(bb, 10 * 8 + 12, arr);
		System.out.printf("\n");
		System.out.printf("* GRAPH LAYOUT/STYLE: %d\n", layout_text[arr[1]]);

		System.out.printf("\n%4x COLOR MAP\n", bb.position());
		dump_colors_102(bb);

		System.out.printf("\n%4x ACCESSORIES\n", bb.position());
		int acc_code = bb.getInt();
		System.out.printf("\n**** acc=%d\n", acc_code);
		if (acc_code != 16) {
			System.out.printf("\nERR ACC CODE=%d != 16\n", acc_code);
		}
		decodeAscii(bb, 4 * 100, buf, false);
		parse_accessories(buf, false);

		System.out.println();

		return stp;
	}

	public static STP readSession(byte[] data) {
		int h0, h1;
		float f;

		ByteBuffer bb = ByteBuffer.wrap(data);

		h0 = bb.getInt();
		h1 = bb.getInt();

		STP stp = null;
		if (h0 == 1) {
			System.out.printf("DECODE %2d.%2d\n", h0, h1);
			stp = decode_01(bb);
		} else {
			bb.rewind();
			StringBuffer tag = new StringBuffer();

			for (int count = 0; count < 32 - 1; count++) {
				char ch = (char) bb.get();
				if (ch == '\r') {
					ch = 0;
				}
				if (ch == '\n') {
					break;
				}
				tag.append(ch);
			}
			if (tag.toString().equals("DAQmx Setup 102")) {
				System.out.printf("DECODE 102: %s\n", tag);
				stp = decode_102(bb);
			} else {
				System.out.printf("Unknown setup tag: %s\n", tag);
			}
		}

		return stp;
	}

	public static STP readSessionFile(File f) throws IOException {

		Path path = Paths.get(f.getAbsolutePath());
		byte[] data = Files.readAllBytes(path);

		STP stp = readSession(data);

		return stp;
	}

	public static void main(String[] args) throws IOException {
		// File f = new File("/opt/study/rubal/BAMC 2719.002.stp");
		File share = new File("\\\\amedfsbamc0106\\ResearchData");
		File folder = new File(share, "\\HiFi Research\\5. ISR - (Baker & Salinas)\\BAMC 485 (Normal) R-Ex");
		// File stp = new File( folder, "4685(rest)_160830_1556_s_001.stp");
		File inFile = new File(folder, "4685(exercise)_160830_1616_s_001.stp");
		STP stp = readSessionFile(inFile);
		
		File outFile = new File(folder, "out.stp");
		encode_01( outFile, stp );
	}
}
