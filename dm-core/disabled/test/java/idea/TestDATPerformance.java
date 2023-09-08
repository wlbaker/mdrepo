package idea;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class TestDATPerformance {

	public void testDecode() {
		byte[] bytes = new byte[150 * 1024 * 1024];
		Arrays.fill(bytes, (byte) '\n');

		for (int i = 0; i < 10; i++) {
		    long start = System.nanoTime();
		    CharBuffer b2 = StandardCharsets.UTF_8.decode(ByteBuffer.wrap(bytes));
		    long time = System.nanoTime() - start;
		    System.out.printf("Time to decode %,d MB was %,d ms%n",
		            bytes.length / 1024 / 1024, time / 1000000);
		}
	}
	
	public void testInputStream(String filename, int bufferSize ) throws IOException {
		BufferedInputStream inputStream = new BufferedInputStream(new FileInputStream(filename));
		try {
		  byte[] byteBuffer = new byte[bufferSize];
		  int numberOfBytes;
		  do {
		    numberOfBytes = inputStream.read(byteBuffer, 0, bufferSize);
		  } while (numberOfBytes >= 0);
		}
		finally {
		  inputStream.close();
		}
	}

	public void testBufferedReader(String filename, int bufferSize ) throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader(filename), bufferSize);
		try {
		  char[] charBuffer = new char[bufferSize];
		  int numberOfChars;
		  do {
		    numberOfChars = reader.read(charBuffer, 0, bufferSize);
		  } while (numberOfChars >= 0);
		}
		finally {
		  reader.close();
		}
	}

	public void testRandomReader(String filename, int bufferSize ) throws IOException {
		RandomAccessFile reader = new RandomAccessFile(filename, "r"); 
		try {
		  byte[] byteBuffer = new byte[bufferSize];
		  int numberOfChars;
		  do {
		    numberOfChars = reader.read(byteBuffer, 0, bufferSize);
		  } while (numberOfChars >= 0);
		}
		finally {
		  reader.close();
		}
	}

	public void testRandomReadline(String filename ) throws IOException {
		RandomAccessFile reader = new RandomAccessFile(filename, "r"); 
		try {
		  String line;
		  do {
		    line = reader.readLine();
		  } while (line != null);
		}
		finally {
		  reader.close();
		}
	}

	public void testBufferedLineReader(String filename, int bufferSize ) throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader(filename), bufferSize);
		try {
		  String line;
		  do {
		    line = reader.readLine();
		  } while (line != null);
		}
		finally {
		  reader.close();
		}
	}

	public void testXXBufferedLineReader(String filename, int bufferSize ) throws IOException {
		FileInputStream fis = new FileInputStream(filename);
		BufferedInputStream bis = new BufferedInputStream( fis, bufferSize);
		
		BufferedReader reader = new BufferedReader( new InputStreamReader(bis) );
		try {
		  String line;
		  do {
		    line = reader.readLine();
		  } while (line != null);
		}
		finally {
		  reader.close();
		}
	}

	public static void main(String [] args) throws IOException {
		
		TestDATPerformance t = new TestDATPerformance();
		t. testDecode();
		
		String fileName = "c:/opt/study/rubal/BAMC 2719.002.dat";
		
		for( int i = 0; i < 3; i++ ) {
			long start = System.nanoTime();
			t.testBufferedReader(fileName, 4096);
			long time = System.nanoTime() - start;
		    System.out.printf("Time for bufferedReader %,d ms%n", time / 1000000);
		}
		
		for( int i = 0; i < 3; i++ ) {
			long start = System.nanoTime();
			t.testInputStream(fileName, 4096);
			long time = System.nanoTime() - start;
		    System.out.printf("Time for inputstream %,d ms%n", time / 1000000);
		}
		
		for( int i = 0; i < 3; i++ ) {
			long start = System.nanoTime();
			t.testRandomReader(fileName, 4096);
			long time = System.nanoTime() - start;
		    System.out.printf("Time for random %,d ms%n", time / 1000000);
		}
		
//		for( int i = 0; i < 3; i++ ) {
//			long start = System.nanoTime();
//			t.testRandomReadline(fileName);
//			long time = System.nanoTime() - start;
//		    System.out.printf("Time for random READ LINE %,d ms%n", time / 1000000);
//		}
		
		for( int i = 0; i < 3; i++ ) {
			long start = System.nanoTime();
			t.testBufferedLineReader(fileName, 4096);
			long time = System.nanoTime() - start;
		    System.out.printf("Time for buffere READ LINE %,d ms%n", time / 1000000);
		}
		for( int i = 0; i < 3; i++ ) {
			long start = System.nanoTime();
			t.testXXBufferedLineReader(fileName, 4096);
			long time = System.nanoTime() - start;
		    System.out.printf("Time for xx buffered READ LINE %,d ms%n", time / 1000000);
		}
	}
}
