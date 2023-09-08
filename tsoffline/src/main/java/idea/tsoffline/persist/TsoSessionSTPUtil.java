package idea.tsoffline.persist;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import idea.ts.TsoSession;

@Slf4j
public class TsoSessionSTPUtil {

	@Getter
	private String[] sigLabel;

	@Getter
	private String[] configInfo;

	@Getter
	private String[] graphSigs;

	boolean verbose = false;

	static String read_string(ByteBuffer bb) {
		int len = bb.getInt();

		StringBuffer buf = new StringBuffer();
		while (len-- > 0) {
			buf.append((char) bb.get());
		}

		return buf.toString();
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

	static void dump_block(ByteBuffer bb, int count) {
		for (int i = 0; i < count; i++) {
			float f = bb.getFloat();
			System.out.printf(" %4.2f", f);
			if (i % 16 == 15)
				System.out.println();
		}
	}

	static void dump_block_double(ByteBuffer bb, int count) {
		for (int i = 0; i < count; i++) {
			double f = bb.getDouble();
			System.out.printf(" %4.2f", f);
			if (i % 16 == 15)
				System.out.println();
		}
	}

	static void dump_int4_to_array(ByteBuffer bb, int count, int[] arr) {
		for (int i = 0; i < count; i++) {
			int val = bb.getInt();
			arr[i] = val;
//			if (val == -1) {
//				return;
//			}
			System.out.printf(" %4d", val);
			if (i % 8 == 7)
				System.out.println();
		}
	}

	static void dump_int4(ByteBuffer bb, int count) {
		for (int i = 0; i < count; i++) {
			int val = bb.getInt();
			// if (val == -1) {
			// return;
			// }
			System.out.printf(" %4d", val);
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

	static int dump_ascii(ByteBuffer bb, int count, byte[] buf, boolean variable_length) {

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

	static int parse_accessories(ByteBuffer bb, int count) {

		int seq = 0;
		while( count > 0 ) {
			System.out.printf("%2d ", ++seq);
			
			String dev_name = read_string(bb);
			System.out.print( dev_name );

			byte ch = bb.get();
			int icount = bb.getInt();

			// options
			while( icount > 0 ) {
				icount--;
				System.out.format( " %d", bb.getInt() );
			}
			

			int port = bb.getInt();
			System.out.printf(" PORT: [%d][%d]\n", (int)ch, port);

			count--;

		};

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

	void decode_01(ByteBuffer bb) {

		int sz;

		System.out.printf("\n%4x Signal??\n", bb.position());
		dump_block(bb, 16);

		System.out.printf("\n%4x unitHIGH\n", bb.position());
		dump_block(bb, 16);

		System.out.printf("\n%4x unitLOW\n", bb.position());
		dump_block(bb, 16);
		System.out.printf("\n%4x vHIGH\n", bb.position());
		dump_block(bb, 16);

		System.out.printf("\n%4x vLOW\n", bb.position());
		dump_block(bb, 16);

		System.out.printf("\n%4x Precision???\n", bb.position());
		dump_block(bb, 16);

		System.out.printf("\n%4x DEVICE\n", bb.position());
		float[] fdevinfo = new float[9];
		dump_block_to_array(bb, 9, fdevinfo);
		System.out.printf("\n");
		System.out.printf("* DEVICE ID: %f\n", fdevinfo[0]);
		System.out.printf("* Sample Rate: %f\n", fdevinfo[1]);
		System.out.printf("* ?Source Data: %f\n", fdevinfo[2]);
		System.out.printf("* ?Accessory: %f\n", fdevinfo[3]);
		System.out.printf("* ?Config/NRSE: %f\n", fdevinfo[4]);
		System.out.printf("* Seq No: %f\n", fdevinfo[5]);
		System.out.printf("* Data Set Size(sec): %f\n", fdevinfo[6]);
		System.out.printf("* Timed Save (sec): %f\n", fdevinfo[7]);
		System.out.printf("* Auto Save (sec): %f\n", fdevinfo[8]);
		// System.out.printf("* Marker Number: %f\n", fdevinfo[9]);

		System.out.printf("\n%4x Channel??\n", bb.position());
		dump_block(bb, 16);

		System.out.printf("\n%4x X0-Color table?\n", bb.position());
		byte[] buf = new byte[1024];
		sz = dump_ascii(bb, 20 * 4, buf, false);
		System.out.printf("--> sz = %d\n", sz);

		System.out.printf("\n%4x COLOR ASSIGN\n", bb.position());
		dump_block(bb, 19);

		System.out.printf("\n%4x B1\n", bb.position());
		dump_block(bb, 32);

		System.out.printf("\n%4x B2\n", bb.position());
		dump_block(bb, 32);

		System.out.printf("\n%4x B3\n", bb.position());
		dump_block(bb, 32);

		System.out.printf("\n%4x B4\n", bb.position());
		dump_block(bb, 32);

		System.out.printf("\n%4x B5\n", bb.position());
		dump_block(bb, 32);

		System.out.printf("\n%4x B6\n", bb.position());
		dump_block(bb, 32);

		System.out.printf("\n%4x B7\n", bb.position());
		dump_block(bb, 32);

		System.out.printf("\n%4x B8\n", bb.position());
		dump_block(bb, 16);

		int h3 = bb.getInt();
		System.out.printf("\n**** h3=%d\n", h3);

		System.out.printf("\n%4x LABELS\n", bb.position());
		sigLabel = new String[50];
		for (int i = 0; i < 49; i++) {
			sigLabel[i] = read_string(bb);
			System.out.printf("%2d ", i + 1);
			if (sigLabel[i].length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", sigLabel[i]);
			}
		}

		System.out.printf("\n%4x CONFIG-BB\n", bb.position());
		configInfo = new String[28];
		for (int i = 0; i < 27; i++) {
			configInfo[i] = read_string(bb);
			System.out.printf("%2d ", i + 1);
			if (configInfo[i].length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", configInfo[i]);
			}
		}

		System.out.printf("\n%4x LABEL/GRAPH\n", bb.position());
		int n_strings = 0;
		graphSigs = new String[124];
		for (n_strings = 0; n_strings < 124; n_strings++) {
			String sbuf = read_string(bb);
			System.out.printf("%2d ", n_strings + 1);
			if (sbuf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", sbuf);
				graphSigs[n_strings] = sbuf;
			}
		}

		// printf("\n%4x BINARY2-AA\n", bb.position() );
		// dump_ascii( fp, 21*16+6, buf, false );
		// parse_strings( buf, false );

		int h5 = bb.getInt();
		System.out.printf("\n**** h5=0x%x == 0xb0\n", h5);

		System.out.printf("\n%4x BINARY3-AA\n", bb.position());
		dump_ascii(bb, 16 * 11, buf, false);

		int h6 = bb.getInt();
		System.out.printf("\n**** h6=0x%x == 0x18\n", h6);
		bb.get(); // FIXME!!!

		System.out.printf("\n%4x COMS-AA\n", bb.position());
		dump_ascii(bb, 21 * 40, buf, false);

	}

	static String layout_text[] = { "1 - One Graph", "2 - Two Bottom", "3 - Two Equal", "4 - Two Top",
			"5 - Three Bottom", "6 - Three Equal", "7 - Three Top", "8 - Four Graphs", "9 - Custom", };

	static String filter_text[] = { "None", "Butterworth", "Chebyshev", "Elliptic", "Bessel", "Running Average" };

	static String format_text[] = { "Scaled Ascii (TXT)", "Scaled Binary (SGL)", "Unscaled Binary (I16)",
			"Voltage Ascii (TXT)", "Voltage Binary (SGL)" };

	static String limit_text[] = { "+/- 10.0", "+/- 5.0", "+/- 2.5", "+/- 2.0", "+/- 1.0", "+/- 0.5", "+/- 0.25",
			"+/- 0.20", "+/- 0.10", "+/- 0.05" };

	static void decode_102(ByteBuffer bb) {
		// unsigned char buf[4*1024];
		int sz;

		int h3 = bb.getInt();
		System.out.printf("\n**** h3=%d\n", h3);

		System.out.printf("\n%4x Units High\n", bb.position());
		dump_block_double(bb, 16);

		System.out.printf("\n%4x Units Low\n", bb.position());
		dump_block_double(bb, 16);

		System.out.printf("\n%4x Volts High\n", bb.position());
		dump_block_double(bb, 16);

		System.out.printf("\n%4x Volts Low\n", bb.position());
		dump_block_double(bb, 16);

		System.out.printf("\n%4x SETTINGS\n", bb.position());
		double sample_rate = bb.getDouble();
		double two = bb.getDouble();
		double unk = bb.getDouble();
		System.out.printf(" * sample rate: %f\n", sample_rate);
		System.out.printf(" *         two: %f\n", two);
		System.out.printf(" *         unk: %f\n", unk);

		System.out.printf("\n%4x Band (fh)\n", bb.position());
		dump_block_double(bb, 16);

		System.out.printf("\n%4x Cutoff (fh)\n", bb.position());
		dump_block_double(bb, 16);
		System.out.printf("\n%4x GRAPH RANGES\n", bb.position());
		dump_block_double(bb, 8);
		System.out.printf("\n%4x OTHER DOUBLES\n", bb.position());
		dump_block_double(bb, 120 - 16 - 8 - 3);

		int h4 = bb.getInt();
		System.out.printf("\n**** h4=%d\n", h4);

		System.out.printf("\n%4x SIGNAL LABELS\n", bb.position());
		for (int i = 0; i < 49; i++) {
			String sbuf = read_string(bb);
			System.out.printf("%2d ", i + 1);
			if (sbuf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", sbuf);
			}
		}

		System.out.printf("\n%4x CONFIG-AA\n", bb.position());
		for (int i = 0; i < 8; i++) {
			String sbuf = read_string(bb);
			System.out.printf("%2d ", i + 1);
			if (sbuf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", sbuf);
			}
		}

		System.out.printf("\n%4x SIGS TO RECORD\n", bb.position());
		for (int i = 0; i < 28; i++) {
			String buf = read_string(bb);
			System.out.printf("%2d ", i + 1);
			if (buf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", buf);
			}
		}

		System.out.printf("\n%4x SIGS TO GRAPH\n", bb.position());
		for (int n_strings = 0; n_strings < 16; n_strings++) {
			String sbuf = read_string(bb);
			System.out.printf("%2d ", n_strings + 1);
			if (sbuf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", sbuf);
			}
		}

		System.out.printf("\n%4x HR SOURCES AND VITALS MESSAGES\n", bb.position());
		for (int n_strings = 0; n_strings < 16; n_strings++) {
			String sbuf = read_string(bb);
			System.out.printf("%2d ", n_strings + 1);
			if (sbuf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", sbuf);
			}
		}

		byte[] buf = new byte[1024];

		System.out.printf("\n%4x BINARY2-BB\n", bb.position());
		dump_ascii(bb, 21 * 16, buf, false);
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
		int[] arr = new int[91];
		dump_int4_to_array(bb, 10 * 8 + 11, arr);
		System.out.printf("\n");
		System.out.printf("* GRAPH LAYOUT/STYLE: %s\n", layout_text[arr[1]]);

		System.out.printf("\n%4x NOTES\n", bb.position());
		//? dump_colors_102(bb);
		int field_count = bb.getInt();
		dump_strings(bb, field_count);

		int i4_count = bb.getInt();
		dump_int4(bb, i4_count);

		int acc_count = bb.getInt();
		System.out.printf("\n**** acc=%d\n", acc_count);
		
//		int pos = bb.position();
//		dump_ascii( bb, 10*64, buf,false);
//		dump_ascii( bb, 10*64, buf,false);
//		dump_ascii( bb, 4*64, buf,false);
//		dump_ascii( bb, 4*64, buf,false);
// 		bb.position(pos);

		parse_accessories(bb, acc_count);

		System.out.println();
	}

	private static void dump_strings(ByteBuffer bb, int count) {
		for (int n_strings = 0; n_strings < count; n_strings++) {
			String sbuf = read_string(bb);
			System.out.printf("%2d ", n_strings + 1);
			if (sbuf.length() == 0) {
				System.out.printf("EMPTY\n");
			} else {
				System.out.printf("%s\n", sbuf);
			}
		}
	}

	private TsoSession readSession(byte[] data) {
		int h0, h1;
		float f;

		ByteBuffer bb = ByteBuffer.wrap(data);

		TsoSession session = new TsoSession();

		h0 = bb.getInt();
		h1 = bb.getInt();

		if (h0 == 1) {
			System.out.printf("DECODE %2d.%2d\n", h0, h1);
			decode_01(bb);
		} else {
			bb.rewind();
			StringBuffer tag = new StringBuffer();

			for (int count = 0; count < 32 - 1; count++) {
				char ch = (char) bb.get();
				if (ch == '\r') {
				} else if (ch == '\n') {
					break;
				} else {
					tag.append(ch);
				}
			}
			if (tag.toString().equals("DAQmx Setup 102")) {
				System.out.printf("DECODE 102: %s\n", tag);
				decode_102(bb);
			} else {
				System.out.printf("Unknown setup tag: %s\n", tag);
			}
		}

		return session;
	}

	public TsoSession readSessionFile(File f) throws IOException {

		Path path = Paths.get(f.getAbsolutePath());
		byte[] data = Files.readAllBytes(path);
		TsoSession session = readSession(data);

		return session;
	}

}
