package icuInterface;

import idea.conf.CompositeDescription;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Enumeration;
import java.util.List;
import java.util.Properties;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class LoggingUtil {

	static int idx = 0;

	public static PrintStream getLoggingOutputStream(Class<?> clazz) {

		PrintStream out = null;

		String ddir = System.getProperty("devicelog_dir");
		if (ddir == null) {
			ddir = System.getenv("devicelog_dir");
		}
		if (ddir != null) {
			String fname = System.getProperty("devicelog_file");

			if (fname == null) {
				SimpleDateFormat fmt = new SimpleDateFormat("yyyy-MM-dd");
				fname = clazz.getCanonicalName() + "-" + fmt.format(new Date()) + ".log";
			}
			File f = new File(ddir, fname);

			try {

				OutputStream ostream;
				try {
					if (f.exists()) {
						f.delete();
					}
					ostream = new FileOutputStream(f);
				} catch (IOException e) {
					// if delete fails, try to append
					ostream = new FileOutputStream(f, true);
				}
				out = new PrintStream(ostream);
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}
		return out;
	}

	public static void dumpSocketData(PrintStream out, long dt, byte[] b, int len) {
		out.print("# [socket] dt=");
		out.print(dt);
		out.print(" idx=");
		out.print(++idx);
		out.println();
		out.print("[in] :");
		out.print(encode(b, 0, len));
		out.println();
		out.flush();
	}

	public static String encode(byte[] r) {
		return encode(r, 0, r.length);
	}

	/**
	 * Encode a message as a string for logging to a file. The input is a byte
	 * array, with possible offset and length.
	 * 
	 * @param r
	 * @param off
	 * @param len
	 * @return String of encoded message.
	 */
	public static String encode(byte[] r, int off, int len) {
		StringBuilder resultStr = new StringBuilder();
		while (off < len) {
			byte b = r[off++];

			int ch = b;
			if (ch < 0) {
				ch += 256;
			}
			if (isUnsafe(ch)) {
				resultStr.append('%');
				resultStr.append(toHex(ch / 16));
				resultStr.append(toHex(ch % 16));
			} else {
				resultStr.append((char) ch);
			}
		}
		return resultStr.toString();
	}

	public static char toHex(int ch) {
		return (char) (ch < 10 ? '0' + ch : 'A' + ch - 10);
	}

	private static char fromHex(int ch) {
		ch = Character.toUpperCase(ch);
		return (char) (ch < 'A' ? ch - '0' : ch - 'A' + 10);
	}

	private static boolean isUnsafe(int ch) {
		if (ch > 126 || ch < ' ')
			return true;
		return "%\r\n\t".indexOf(ch) >= 0;
	}

	/**
	 * @param line:
	 *            message recorded to log with partial hex encoding
	 * @return byte[] of decoded message
	 * 
	 *         Parse/decode of the log allows for messages to be replayed,
	 *         especially when they are broadcast messages that do not require
	 *         an inquire message.
	 */
	public static byte[] parse(String line) {
		final String IN_PATTERN = "[in] :";
		if (!line.startsWith(IN_PATTERN)) {
			return null;
		}

		int idx = 0;
		int count = 0;
		while ((idx = line.indexOf('%', idx)) > 0) {
			idx++;
			count++;
		}

		byte[] dat = new byte[line.length() - IN_PATTERN.length() - count * 2];
		byte[] source = line.getBytes();
		idx = 0;
		for (int i = IN_PATTERN.length(); i < source.length; i++) {
			byte ch = source[i];
			if (ch == '%') {
				int v = fromHex(source[++i]) * 16;
				v += fromHex(source[++i]);
				ch = (byte) v;
			}
			dat[idx++] = ch;
		}
		return dat;
	}

	public static void dumpConfiguration(PrintStream out, StreamProducer p) {
		if (out == null) {
			return;
		}
		RpDevice conf = p.getConfiguration();

		if (conf != null) {
			out.print("[conf] :");
			out.print(encode(conf.toString().getBytes()));
			out.println();
			out.flush();

		}

	}

	public static void dumpEvent(PrintStream out, long dt, int jobId, Object src, StreamID sid, PersistentItem block) {
		assert (out != null) : "check before calling";

		out.print("# [fire] dt=");
		out.print(dt);
		out.print(" idx=");
		out.print(++idx);
		out.print(" job=");
		out.print(jobId);
		out.println();
		out.print("[fire] :");
		out.print(sid.getName());
		out.print(":");

		IntfUtil.dump(out, block);
	}

	public static void dumpBinaryData(PrintStream out, byte[] arr) {
		for (int i = 0; i < arr.length; i++) {
			if (i % 16 == 0) {
				out.println();
			}
			int val = arr[i];
			if (val < 0) {
				val += 256;
			}
			if (val < 16) {
				out.print("0");
			}
			out.print(Integer.toHexString(val));
			out.print(" ");
		}

		out.println();

	}

	public static void dumpCapabilities(PrintStream out, int i, RpDevice caps) {
		out.println("************************** CAPABILITIES rev=" + caps.getRevNo());
		List<RpStream> streams = caps.getStreams();
		if (streams == null) {
			out.println("!!EMPTY!!");
			return;
		}

		for (RpStream stream : streams) {
			out.println(stream.getName() + ": ");
			List<RpMetric> metrics = stream.getMetric();
			if (metrics != null) {
				for (RpMetric m : metrics) {
					dumpMetric(out, m);
					if (m instanceof CompositeDescription) {
						CompositeDescription cd = (CompositeDescription) m;
						RpMetric[] subs = cd.getMetrics();
						if (subs != null && subs.length > 0) {
							for (RpMetric sub : subs) {
								out.print("    sub: ");
								dumpMetric(out, sub);
							}
						}
					}
				}
			}
		}

	}

	private static void dumpMetric(PrintStream out, RpMetric m) {
		out.print("  ");
		out.print(m.getLocation() + "/" + m.getCode() + "/" + m.getName());
		out.print("  subtyp: " + m.getSubtyp());
		out.print("  rate/spp: " + m.getSampleRate() + "/" + m.getSamplesPerPacket());
		out.println();
	}

	public static void dump(ByteBuffer bb, int off, int len) {

		int pos = bb.position();
		int i = 0;
		bb.position(0);
		int consec_zero = 0;
		while (bb.remaining() > 0 && len > 0) {
			len--;
			int ch = bb.get();
			System.out.print(" ");
			if (ch < 0) {
				ch += 256;
				// System.out.print("(byte)");
			}
			System.out.print("0x");
			if (ch < 16) {
				System.out.print("0");
			}
			System.out.format("%x,", ch);

			i++;
			if (i % 16 == 0) {
				System.out.println();
			}

			if (ch == 0) {
				consec_zero++;
			} else {
				consec_zero = 0;
			}

			if (consec_zero > 32)
				break;
		}
		System.out.println();

		bb.position(pos);
	}

	public static void dump(ByteBuffer pkt) {
		LoggingUtil.dump(pkt, 0, pkt.limit());
	}

	public static void writeInfo(String string) {
		log.info(string);
	}

	public static void dumpLibraryPath(PrintStream out) {

		out.println("OS=" + PlatformUtil.getOSID());

		String p = System.getProperty("java.library.path");

		String sep = File.pathSeparator;
		if (";".equals(sep)) {
			// windows: keep the colons
		} else {
			// sometimes configs for linux are inadvertently copied from Windows
			sep = "[:;]";
		}
		String[] arr = p.split(sep);
		p = "";
		for (String r : arr) {
			File f = new File(r);
			if (f.exists()) {
				out.print("  [FOUND]: ");
			} else {
				out.print("[MISSING]: ");
			}
			out.println(r);
		}

	}

	public static void dumpSystemProperties(PrintStream out) {
		Properties props = System.getProperties();

		Enumeration<?> enames = props.propertyNames();

		while (enames.hasMoreElements()) {
			String name = (String) enames.nextElement();
			out.print(name);
			out.print("=");
			out.println(props.getProperty(name));
		}
	}

}
