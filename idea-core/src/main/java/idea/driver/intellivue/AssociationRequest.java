package idea.driver.intellivue;

import static idea.driver.intellivue.C.CN_SPDU_SI;

import java.nio.ByteBuffer;

public class AssociationRequest implements Reportable {

	private static byte[] assocreq_session_data = new byte[] { 0x05, 0x08, 0x13, 0x01, 0x00, 0x16, 0x01, 0x02, //
			(byte) 0x80, 0x00, 0x14, 0x02, 0x00, 0x02 };

	private static final byte[] assocreq_pres_header_blob = new byte[] { //
	0x31, (byte) 0x80, (byte) 0xA0, (byte) 0x80, (byte) 0x80, 0x01, //
			0x01, 0x00, 0x00, (byte) 0xA2, (byte) 0x80, (byte) 0xA0, 0x03, 0x00, //
			0x00, 0x01, (byte) 0xA4, (byte) 0x80, 0x30, (byte) 0x80, 0x02, 0x01,//
			0x01, 0x06, 0x04, 0x52, 0x01, 0x00, 0x01, 0x30, //
			(byte) 0x80, 0x06, 0x02, 0x51, 0x01, 0x00, 0x00, 0x00, //
			0x00, 0x30, (byte) 0x80, 0x02, 0x01, 0x02, 0x06, 0x0C, //
			0x2A, (byte) 0x86, 0x48, (byte) 0xCE, 0x14, 0x02, 0x01, 0x00, //
			0x00, 0x00, 0x01, 0x01, 0x30, (byte) 0x80, 0x06, 0x0C, //
			0x2A, (byte) 0x86, 0x48, (byte) 0xCE, 0x14, 0x02, 0x01, 0x00, //
			0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, //
			0x00, 0x00, 0x61, (byte) 0x80, 0x30, (byte) 0x80, 0x02, 0x01, //
			0x01, (byte) 0xA0, (byte) 0x80, 0x60, (byte) 0x80, (byte) 0xA1, (byte) 0x80, 0x06, //
			0x0C, 0x2A, (byte) 0x86, 0x48, (byte) 0xCE, 0x14, 0x02, 0x01, //
			0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, (byte) 0xBE, //
			(byte) 0x80, 0x28, (byte) 0x80, 0x06, 0x0C, 0x2A, (byte) 0x86, 0x48, //
			(byte) 0xCE, 0x14, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01, //
			0x01, 0x02, 0x01, 0x02, (byte) 0x81 };

	private static final byte[] assocreq_pres_trailer_blob = new byte[] { //
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 //
	};

	private static AttributeList supported_aprofiles;

	private static PollProfileSupport profile;

	static {
		supported_aprofiles = new AttributeList();

		profile = new PollProfileSupport();

		PollProfileExt ppe = new PollProfileExt(C.POLL_EXT_PERIOD_NU_1SEC | C.POLL_EXT_PERIOD_RTSA );

		AVAType profile_ext = new AVAType(C.NOM_ATTR_POLL_PROFILE_EXT, ppe.encode(null));
		profile.addOptionalPackages(profile_ext);

		AVAType profile_support = new AVAType( C.NOM_POLL_PROFILE_SUPPORT, profile.encode(null));
		supported_aprofiles.add(profile_support);

	}

	public static ByteBuffer build(ByteBuffer pkt) {
		ByteBuffer sessionData = ByteBuffer.wrap(assocreq_session_data);
		ByteBuffer presHeader = ByteBuffer.wrap(assocreq_pres_header_blob);
		ByteBuffer userData = ByteBuffer.allocate(256);
		ByteBuffer trailer = ByteBuffer.wrap(assocreq_pres_trailer_blob);

		MDSEUserInfoStd.encode(userData, supported_aprofiles);

		//??? debug_parseUserInfo(userData);

		sessionData.position(0);
		presHeader.position(0);
		userData.position(0);
		trailer.position(0);

		int payload_len = sessionData.remaining();
		payload_len += presHeader.remaining();
		payload_len += userData.remaining();
		payload_len += trailer.remaining();
		payload_len += 1; // pres header len
		if (presHeader.remaining() > 255) {
			payload_len += 2;
		}
		int userdata_asnlen = 1; // user data len
		if (userData.remaining() > 127) {
			userdata_asnlen += 2;
		}
		payload_len += userdata_asnlen;

		assert (payload_len < 32000) : "ERROR: assuming li <= 32000";

		int pkt_len = payload_len + 3;
		if (payload_len > 127) {
			pkt_len += 2;
		}
		if (pkt == null) {
			pkt = ByteBuffer.allocate(pkt_len);
		}
		pkt.put(CN_SPDU_SI); // AssocReqSessionHeader
		putLI(pkt, payload_len + 1);
		pkt.put(sessionData);

		// appears to be define in ITU X.217 and also ISO/EIC 8649/8650?
		pkt.put((byte) 0xc1);
		putLI(pkt, presHeader.remaining() + userdata_asnlen + userData.remaining() + trailer.remaining());
		pkt.put(presHeader);

		putASN(pkt, userData.remaining());
		pkt.put(userData);

		pkt.put(trailer);
		pkt.limit(pkt.position());
		pkt.rewind();
		return pkt;
	}

	private static void putLI(ByteBuffer pkt, int li) {
		if (li > 254) {
			pkt.put((byte) 0xff);
			pkt.putShort((short) li);
		} else {
			pkt.put((byte) li);
		}
	}

	private static void putASN(ByteBuffer pkt, int li) {
		if (li > 127) {
			pkt.put((byte) 0x82);
			pkt.putShort((short) li);
		} else {
			pkt.put((byte) li);
		}
	}

	@Override
	public void dump() {
		System.err.println("AssociationRequest");

		System.out.println("DUMP BLOBS!");

		System.out.println("*Supported AProfiles");
		supported_aprofiles.dump();
	}

}
