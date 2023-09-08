package dsi;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import idea.persistance.pnmwav.Pnmwav;
import idea.persistance.pnmwav.Pnmwav.PnmDatachunk;
import idea.persistance.pnmwav.Pnmwav.PnmTag;

class ChannelDef {
	int channelId;
	int ticks_per_sample;
	public BufferedWriter out;
	public int count;
}

public class PnmwavKscTest {

	private static List<ChannelDef> channels = null;
	private static String tz;
	private static String subject;
	private static long tm0;

	public static void main(String[] args) throws IOException {
		String fileName = "C:\\opt\\study\\EP-RESUS\\3901\\dsi\\3901.2019.20190918135152.PnmWav";
		Pnmwav r = Pnmwav.fromFile(fileName);

		System.out.println("header tags:");
		for (PnmTag tag : r.header().headerPayload().tags()) {
			dumpTag(tag);
			switch (tag.tagId()) {
			case FT_LOCAL_TIME_ZONE_ID:
				tz = (String) tag.payload();
				break;
			case FT_SUBJECT_NAME:
				subject = (String) tag.payload();
				break;
			case FT_EARLIEST_FILE_TIME:
				tm0 = ((Long) tag.payload()).longValue();
				break;
			}
		}

		long datablockStartTime = -1;
		ArrayList<Short> datablockData = null;

		ChannelDef ch = null;
		ArrayList<PnmTag> filetags = r.channelTags().tags();
		Iterator<PnmTag> it = filetags.iterator();
		boolean insideChannelList = false;
		int fileset_idx = 0;
		System.out.println("\nchannel list tags:\n");
		while (it.hasNext()) {
			PnmTag tag = it.next();
			// dumpTag(tag);

			switch (tag.tagId()) {
			case FT_CHAN_LIST_BEGIN:
				System.out.println(">> END OF CHANNEL LIST\n\n");
				closeOutput();
				channels = new LinkedList<ChannelDef>();
				fileset_idx++;
				insideChannelList = true;
				break;
			case FT_CHAN_BEGIN:
				System.out.println("  >> begin channel def: " + tag.payload());
				ch = new ChannelDef();
				break;
			case FT_CHAN_END:
				System.out.println("  >> end channel def");
				channels.add(ch);
				ch = null;
				break;
			case FT_CHANNEL_ID:
				int ch_id = ((Long) tag.payload()).intValue();
				if (insideChannelList) {
					ch.channelId = ch_id;
				} else {
					ch = findChannel(ch_id);
				}
				break;
			case FT_TICKS_PER_SAMPLE:
				ch.ticks_per_sample = ((Long) tag.payload()).intValue();
				break;
			case FT_CHAN_LIST_END:
				System.out.println(">> END OF CHANNEL LIST\n\n");
				insideChannelList = false;
				break;
			case FT_DATA_CHUNK:
				// System.out.print(" >> DATA_CHUNK: " + ch.channelId);
				PnmDatachunk chunk = (PnmDatachunk) tag.payload();
				datablockData = chunk.v();
//				System.out.print("[" + datablockData.size() + "]");
//				for (int i = 0; i < 10 && i < datablockData.size(); i++) {
//					System.out.format(" %5d", datablockData.get(i));
//				}
//				System.out.println();
				break;
			case FT_START_TIME:
				datablockStartTime = ((Long) tag.payload()).longValue();
				break;
			case FT_DATA_BLOCK_END:
				dumpDatablock(ch, datablockStartTime - tm0, datablockData, fileset_idx > 1 );
				datablockData = null;
				datablockStartTime = -1;
				ch = null;
			default:
			}
		}

		closeOutput();
	}

	private static ChannelDef findChannel(int ch_id) {
		for (ChannelDef ch : channels) {
			if (ch.channelId == ch_id) {
				return ch;
			}
		}
		return null;
	}

	private static void closeOutput() throws IOException {
		if (channels != null) {
			for (ChannelDef ch : channels) {
				if (ch.out != null) {
					ch.out.close();
					ch.out = null;
				}
			}
		}
		channels = null;
	}

	private static void dumpDatablock(ChannelDef ch, long tm, ArrayList<Short> data, boolean append) throws IOException {

		// StringBuffer sb = new StringBuffer();
		if (ch.out == null) {
//			int idx = 0;
//			do {
//				idx++;
			File f = new File("c:/tmp/str" + ch.channelId + ".dat");
//			} while (f.exists());
			if (append == false && f.exists()) {
				f.delete();
			}
			ch.out = new BufferedWriter(new FileWriter(f, append));
			if (!append) {
				ch.out.write("TM\tV" + ch.channelId + "\n");
			}
			ch.count++;
		}
		long dt = ch.ticks_per_sample;
		BufferedWriter out = ch.out;
		for (Short s : data) {
			String line = String.format("%d\t%d\n", tm / 1000, s);
			// sb.append( line );
			out.write(line);
			tm += dt;
		}
		System.out
				.println(ch.channelId + "\t" + tm + "\t" + "\t" + data.size() + "\t" + dt + "\t" + ch.ticks_per_sample);
		if (ch.channelId == 2) {
			System.out.println();
		}

	}

	private static void dumpTag(PnmTag tag) {
		String tagName = String.format("%-30s", tag.tagId().toString());
		System.out.print("  ");
		System.out.print(tagName);
		if (tag.tagLen() > 0) {
			System.out.print("  payload[" + tag.tagLen() + "]=" + tag.payload());
			Object o = tag.payload();
			if (o instanceof byte[]) {
				byte[] bb = (byte[]) o;
				for (byte b : bb) {
					int ival = b;
					if (ival < 0) {
						ival += 256;
					}
					System.out.print(String.format(" %02x", ival));
				}
			}
		}
		System.out.println();
	}

}
