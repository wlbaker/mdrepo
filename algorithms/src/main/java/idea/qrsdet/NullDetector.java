package idea.qrsdet;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Date;

import idea.analysis.event.BeatBlock;

public class NullDetector extends AbstractStreamProducer {

	private FileReader strm;
	private BufferedReader reader;
	long tm;
	int col;

	public NullDetector(File infile, Date sampleDate, int sampleRate, int col ) throws FileNotFoundException {
		this.col = col;
		strm = new FileReader(infile);
		reader = new BufferedReader(strm);

		if( sampleDate != null ) {
			tm = sampleDate.getTime();
		}
		
		try {
			reader.mark(100);
			String line = reader.readLine();
			String[] ar = line.split("\t");
			Double.parseDouble(ar[col]);            // if not a number (header), then skip with exception
			reader.reset();                       // if it made it this far, it was a number
		} catch (NumberFormatException e) {
			// header row
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public boolean next() throws IOException {
		String line = reader.readLine();

		boolean ok = (line != null);
		if (ok) {
			String[] ar = line.split("\t");
			double interval = Double.parseDouble(ar[col]);
			int i_interval = (int) (interval + 0.5);

			BeatBlock block = new BeatBlock( this );
			block.setSamp_interval(i_interval);  // NOTE: Recently changed from INT to DOUBLE
			block.setTm( new Date(tm) );

			tm += i_interval;

			fireStreamEvent(0, this, StreamID.MEASUREMENT_2, block );
		}

		return ok;
	}

	public void dispose() throws IOException {
		reader.close();
		strm.close();

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		DeviceCapabilities caps = new DeviceCapabilities( this.getClass() );
		caps.addStream(StreamID.MEASUREMENT, BeatBlock.class);
		caps.setName("NULLDET");
		return caps;
	}


}
