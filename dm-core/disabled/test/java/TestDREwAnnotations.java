
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import idea.persistmanager.PiDreImporter;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class TestDREwAnnotations {

	public void testDecode() {
		byte[] bytes = new byte[150 * 1024 * 1024];
		Arrays.fill(bytes, (byte) '\n');

		for (int i = 0; i < 10; i++) {
			long start = System.nanoTime();
			CharBuffer b2 = StandardCharsets.UTF_8.decode(ByteBuffer.wrap(bytes));
			long time = System.nanoTime() - start;
			System.out.printf("Time to decode %,d MB was %,d ms%n", bytes.length / 1024 / 1024, time / 1000000);
		}
	}

	public static void main(String[] args) throws IOException {

		TestDREwAnnotations t = new TestDREwAnnotations();

		String dirName = "V:\\HiFi Research\\5. ISR - (Baker & Salinas)\\ISR_HEM1_Rubal\\REBOA-036";

		File dir = new File(dirName);
		if (!dir.exists()) {
			log.error("could not find root directory: " + dir);
			return;
		}

		PiDreImporter importer = new PiDreImporter(null, "DRE");

		String pat = "^REBOA-036_([0-9]+)_([0-9]+)_([vw]?)_([0-9]+)\\.dat$";
		Pattern r = Pattern.compile(pat);

		String [] tt = { "001", "100", "999", "000" };
		Arrays.sort( tt );
		for( String t2 : tt ) {
			System.out.println( t2 );
		}
		
		String [] names = dir.list( );
		Arrays.sort( names );
		for (String name : names ) {
			Matcher m = r.matcher(name);

			if (m.find()) {
				String wv = m.group(3);
				if( wv.equals("w")) {
					System.out.println("WAVEFORM: " + name);					
					importer.addWavesFile( new File(dir, name ));
				} else {
					System.out.println("VITALS: " + name);
					importer.addVitalsFile( new File(dir, name ));
				}
			}
		}

		File f = new File(dir, "REBOA-036 (book).txt");
		if( f.exists() ) {
			importer.addAnnotationFile( f );
		}
		
		f = new File(dir, "REBOA-036 (notes).txt");
		if( f.exists() ) {
			importer.addAnnotationFile( f );
		}
	}
}
