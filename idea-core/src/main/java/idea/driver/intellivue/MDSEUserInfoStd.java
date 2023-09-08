package idea.driver.intellivue;

import static idea.driver.intellivue.C.COLD_START;
import static idea.driver.intellivue.C.FUNCTIONAL_UNITS;
import static idea.driver.intellivue.C.MDDL_VERSION1;
import static idea.driver.intellivue.C.NOMEN_VERSION;
import static idea.driver.intellivue.C.SYST_CLIENT;

import java.nio.ByteBuffer;

public class MDSEUserInfoStd implements Reportable {
	
	private int mddl_version;
	private int nomen_version;
	private int functional_unit;
	private int syst;
	private int cold_start;
	private AttributeList options;
	private AttributeList supported_profiles;

	public static void encode(ByteBuffer bb, AttributeList supported_aprofiles ) {
		//		typedef struct MDSEUserInfoStd {
		//			ProtocolVersion protocol_version;         // u_32
		//			NomenclatureVersion nomenclature_version; // u_32
		//			FunctionalUnits functional_units;         // u_32
		//			SystemType system_type;                   // u_32
		//			StartupMode startup_mode;                 // u_32
		//			AttributeList option_list; 
		//			AttributeList supported_aprofiles;
		//		} MDSEUserInfoStd;

		bb.putInt(MDDL_VERSION1);
		bb.putInt(NOMEN_VERSION);
		bb.putInt(FUNCTIONAL_UNITS);
		bb.putInt(SYST_CLIENT); // client must set sys type client
		bb.putInt(COLD_START); // startup mode...probably ignored by device

		// attribute list: no options are currently supported
		bb.putShort((short) 0); // attribute list count
		bb.putShort((short) 0); // attribute list length

		supported_aprofiles.encode(bb);
		bb.limit( bb.position() );
	}

	public static MDSEUserInfoStd parse(ByteBuffer bb) {
		MDSEUserInfoStd std = new MDSEUserInfoStd();
		std.mddl_version = bb.getInt();
		std.nomen_version = bb.getInt();
		std.functional_unit = bb.getInt();
		std.syst = bb.getInt();
		std.cold_start = bb.getInt();
		
		std.options = AttributeList.parse(bb);
		std.supported_profiles = AttributeList.parse(bb);
		
		return std;
	}

	@Override
	public void dump() {
		System.out.println("MDSEUserInfoStd");
		System.out.println( "     mddl_version : 0x" + Integer.toHexString(mddl_version));
		System.out.println( "    nomen_version : 0x" + Integer.toHexString(nomen_version ));
		System.out.println( "  functional_unit : 0x" + Integer.toHexString(functional_unit ));
		System.out.println( "             syst : 0x" + Integer.toHexString(syst));
		System.out.println( "       cold_start : 0x" + Integer.toHexString(cold_start) );
		
		System.out.println( "*OPTIONS: ");		
		options.dump();
		
		System.out.println( "*SUPPORTED_PROFILES: ");		
		supported_profiles.dump();
		
	}


}
