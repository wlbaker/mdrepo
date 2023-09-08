package util;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReformatDefines {

	public static void main( String [] args ) throws IOException {
		String line;
		FileReader fr = new FileReader( "/tmp/in.txt");
		
		BufferedReader br = new BufferedReader(fr);
		while( (line = br.readLine()) != null ) {
			line = line.trim();
			args = line.split("[ \r\n\t]");
			
			String symbol = args[0];
			System.out.println( "case " + symbol + ": message=\"" + symbol + "\"; break;" );
		}
	}
}