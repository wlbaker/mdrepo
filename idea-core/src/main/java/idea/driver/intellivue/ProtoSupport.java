package idea.driver.intellivue;

import static idea.driver.intellivue.C.AP_ID_DATA_OUT;

import java.nio.ByteBuffer;

public class ProtoSupport {

	private static int verbose = 0;
	private short dataOutPort;

	public static ProtoSupport parse(ByteBuffer bb) {

		ProtoSupport proto = new ProtoSupport();
		int count = bb.getShort();
		int len = bb.getShort();
		for (int i = 0; i < count; i++) {
			short appl_proto = bb.getShort(); // confirmed, u_16
			short trans_proto = bb.getShort(); // confirmed, u_16, only
												// supported is TP_IP_UDP=1
			short port_number = bb.getShort();
			short port_options = bb.getShort(); // possible value: 0x8000 -->
												// wireless
			if( verbose  > 0 ) {
				System.out.println( "pcol: " + appl_proto + "," + trans_proto + "," + port_number + "," + port_options);
			}
			if (appl_proto == AP_ID_DATA_OUT) {
				// USE THIS ONE!
				proto.dataOutPort = port_number;
			}
		}
		return proto;
	}

	public int getPort() {
		return dataOutPort;
	}

}
