package idea.driver.intellivue;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;

public class ConvertParamsToCodeUtil {

	static HashSet<String> s = new HashSet<String>();
	/**
	 * @param args
	 * @throws IOException 
	 */
	public static void main(String[] args) throws IOException {
		File f = new File( "c:/opt/workspace/caddo/icuInterface/ref/intellivue_params.txt");

		BufferedReader r = new BufferedReader( new FileReader(f) );
	
		System.out.println( "package icuInterface.adapters.intellivue;\n\npublic class Numerics {\n");
		String line;
		String prev = "?";
		while( (line = r.readLine()) != null ) {
			line = line.trim();
			if( line.startsWith("Label")) {
				System.out.println( "\t// " + prev );
			}
			if( line.startsWith("NOM")) {
				String [] ar = line.split("[ \r\n\t]+");
				if( ar.length == 1 ) {
					System.out.println( "// NO VALUE: " + ar[0] );
				} else {
					if( s.contains(ar[0])) {
						System.out.print("//");
					}
					System.out.println( "\tpublic final static short " + ar[0] + " = (short)" + ar[1] + ";");
					s.add( ar[0]);
				}
			}
			if( line.startsWith("NLS")) {
				String [] ar = line.split("[ \r\n\t]+");
				System.out.println( "\tpublic final static int " + ar[0] + " = " + ar[1] + ";");
			}
			prev = line;
		}
		r.close();
		
		System.out.println("\n}");
	}

}
