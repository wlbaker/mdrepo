package idea.analysis.tools;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;

public class ResampleRRI {

	public static void main(String[] args) throws IOException {
		args = new String[] { "c:/tmp/random_rri.txt", "20", "1" };
		
		resample( args[0], Integer.parseInt(args[1]), args[0] + "-" + args[1], Integer.parseInt(args[2]), "\t");
	}
	
	public static void resample(String infile, int resample_ms, String outFile, int col, String delimit ) throws IOException {

		
		// take a time series of RRI's (ms) and use linear interpolation to
		// create samples every
		// resample_rate(ms) point

		int [] rri = new int[2];

		FileReader strm = new FileReader(infile);
		BufferedReader reader = new BufferedReader(strm);
		
		PrintStream out = new PrintStream(outFile);

		int pos = 0;
		int end = 0;
		int start = 0;
		
		boolean ok = true;
		while( true ) {
			
			if( pos >= end ) {
				String line = reader.readLine();

				ok = (line != null);
				if( !ok ) {
					break;
				}
				
				String[] ar = line.split( delimit );
				rri[0] = rri[1];
				double d = Double.parseDouble(ar[col]);
				rri[1] = (int)(d+0.1);
				start += rri[0];
				end += rri[1];
				continue;
			}
			
			int delta_x = rri[1];
			int delta_y = rri[1] - rri[0];
			int x = pos - start;
			
			int incr = 0;
			if( delta_y != 0 ) {
				incr = delta_y * x / delta_x;
			}
			
			out.print( pos );
			out.print( "\t" );
			out.print( (rri[0] + incr) );
			out.println();
			
			pos += resample_ms;
		}

		reader.close();
		strm.close();
		out.close();
	}

	public static double [] resample( double [] rris, int resample_ms )  {

		return resample( rris, resample_ms, 0, rris.length );
	}
	
	public static double[] resample(double[] rris, int resample_ms, int start_idx, int end_idx) {
		
		// take a time series of RRI's (ms) and use linear interpolation to
		// create samples every
		// resample_rate(ms) point

		double [] rri = new double[2];

		ArrayList<Double> out = new ArrayList<Double>();

		int pos = 0;
		int end = 0;
		int src_idx = start_idx;
		int start = 0;
		
		while( true ) {
			
			if( pos >= end ) {
				if( src_idx >= end_idx ) {
					break;
				}
				double d = rris[ src_idx++ ];

				rri[0] = rri[1];
				rri[1] = (int)(d+0.1);
				start += rri[0];
				end += rri[1];
				continue;
			}
			
			double delta_x = rri[1];
			double delta_y = rri[1] - rri[0];
			double x = pos - start;
			
			double incr = 0;
			if( delta_y != 0 ) {
				incr = delta_y * x / delta_x;
			}
			
			out.add( (rri[0] + incr) );
			
			pos += resample_ms;
		}

		double [] d = new double[out.size()];
		for( int idx = 0; idx < d.length ; idx++ ) {
			d[idx] = out.get(idx);
		}
		
		return d;
	}

}
