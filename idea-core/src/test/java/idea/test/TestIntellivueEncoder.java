package idea.test;

import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.driver.IntellivueUDPDriver;
import idea.driver.intellivue.AttributeList;
import idea.driver.intellivue.C;
import idea.driver.intellivue.IntellivueDriver;
import idea.driver.intellivue.PollMdibDataReq;
import idea.driver.intellivue.SinglePollDataRequest;

import java.io.PrintStream;
import java.nio.ByteBuffer;

public class TestIntellivueEncoder {
	
	private static void dump(String title, ByteBuffer bb) {
		System.out.println( "/*");
		System.out.println( " *");
		System.out.println( " * " + title );
		System.out.println( " *");
		System.out.println( " */");
		System.out.println();
		dump( System.out, bb.array(), bb.remaining() );
		System.out.println();
	}

	private static void dump(PrintStream out, byte[] array, int len) {
		out.println("dumping packet");
		for (int i = 0; i < len; i++) {
			if ((i > 0) && (i % 20 == 0)) {
				out.println();
			}

			int byt = array[i];
			if (byt < 0)
				byt += 256;
			
			out.print("0x");
			if( byt < 16 ) {
				out.print("0");
			}
			out.print(Integer.toHexString(byt));
			if (byt > 0x20 && byt < 0x80) {
				out.print("(");
				out.print((char) byt);
				out.print(")");
			}
			out.print(" ");
		}
		out.println();

	}


	public static void main(String[] args) {
		SocketDeviceConfiguration conf = IntellivueUDPDriver.createConfigInstance();
		conf.setHost("192.168.1.123");

		IntellivueDriver d = new IntellivueUDPDriver(null);

		AttributeList empty = new AttributeList();

		
		ByteBuffer mdib = PollMdibDataReq.encode(null, (short)1, C.NOM_PART_OBJ,
				C.NOM_MOC_PT_DEMOG, (short) 0, empty);
		mdib.rewind();

		ByteBuffer bb = SinglePollDataRequest.encode(null, C.NOM_MOC_PT_DEMOG, mdib );

		ByteBuffer bout = ByteBuffer.allocate( bb.remaining() + 8 );
		bout.putShort( (short) 0xe100 );
		bout.putShort( (short) 2 );
		bout.putShort( C.ROIV_APDU );
		bout.putShort( (short) bb.remaining() );
		bout.put( bb );
		bout.rewind();
		dump( "Single Poll Data Request", bout );
		
//		bb = ExtendedPollDataRequest.build( null, C.NOM_MOC_VMO_METRIC_NU, (short)0  );
//		dump( "Extended Poll Data Request", bb );
	}


}
