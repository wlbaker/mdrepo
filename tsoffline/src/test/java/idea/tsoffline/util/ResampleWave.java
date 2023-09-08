package idea.tsoffline.util;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintStream;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistmanager.PiHdf5Importer;
import idea.schema.rp.RpMetric;

;

public class ResampleWave {

	PiHdf5Importer in;
	
	
	public void resample( PrintStream out, String sourceFile, long startTime, long endTime, int srcFreq, int destFreq, int [] cols ) throws IOException {
		
		in = new PiHdf5Importer( new File(sourceFile) );
		
		in.connect();
		PersistentItem next;
		
		do {
			next = in.next();
			if( next.getTime() >= startTime ) {
				break;
			}
		} while( next != null && next.getStreamID() != StreamID.WAVEFORM.getCode() );
		
		double delta = ((double)srcFreq) / destFreq;
		
		int idx = 0;
		int delta_pos = 0;
		while( true ) {
			
			RpMetric[] items = next.getMetrics();
			// int [] vals
			int abs_pos = (int)(delta * idx);
			
			int pos = abs_pos - delta_pos;
			
			int [] samples = (int[]) IntfUtil.getRawValue(next, items[0]);
			if( pos >= samples.length ) {
				
				delta_pos += samples.length;
				pos -= samples.length;
				
				do {
					next = in.next();
					if( next == null ) {
						System.err.println( "out of data!");
						System.exit(0);
					}
				} while( next.getStreamID() != StreamID.WAVEFORM.getCode() );
				
			}
			
			if( cols == null ) {
				cols = new int[items.length];
				for( int i =0; i < items.length ; i++ ) {
					cols[i] = i;
				}
			}
			// out.print( abs_pos + "\t" );
			for( int i =0; i < cols.length ; i++ ) {
				int col = cols[i];
				if( i > 0 ) {
					out.print( '\t' );
				}
				int [] vals = (int[]) IntfUtil.getRawValue(next, items[col]);
				out.print( vals[pos]);
			}
			out.println();
			
			idx++;
		}
	}
	/**
	 * @param args
	 * @throws FileNotFoundException 
	 * @throws IOException 
	 */
	public static void main(String[] args) throws FileNotFoundException {
		
		long startTime = 0;
		long endTime = 0;
		
		if( args.length < 3 ) {
			System.out.println("merge <file1.h5> srcfreq destfreq");
			System.out.println("- start-time=" + startTime );
			System.out.println("- end-time=" + endTime );
			System.out.println("- output=<text>");
			
			System.exit(0);
		}
		
		String source = args[0];
		int srcFreq = Integer.parseInt( args[1] );
		int destFreq = Integer.parseInt( args[2] );
		
		int [] cols = null;
		if( args.length > 3 ) {
			cols = new int[args.length - 3];
			int idx = 0;
			for( int i = 3; i < args.length ; i++ ) {
				cols[idx++] = Integer.parseInt( args[i]);
			}
		}
		ResampleWave r = new ResampleWave();
		
		PrintStream out = System.out;
		try {
			r.resample(out, source, startTime, endTime, srcFreq, destFreq, cols );
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


}
