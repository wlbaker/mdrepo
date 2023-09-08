package idea.message;

import java.util.HashMap;
import java.util.Map;

import lombok.extern.slf4j.Slf4j;

class Z {
	static Map<String,StreamID> map = new HashMap<>();
}

@Slf4j
public enum StreamID {
	MEASUREMENT('M', "numerics"), SETTINGS('S', "settings"), DDDEMOGRAPHICS('D', "demographics"),  // 
	WAVEFORM('W', "waveform"), ANNOTATION('A', "annot"), ALARM('L', "alarms"), //
	AUDIO('U', "Audio"),  //
	TRANLOG('T', "tranlog"), CAPABILITIES('C', "cap"), CONNECTION('N',"conx"), DISPLAY('X', "disp"), 
	IDENTIFICATION('I', "ident"), MANAGEMENT('Y',"manag"), SECURITY('Z',"sec"), MEASUREMENT_2('2',"M2"), MEASUREMENT_3('3',"M3"), TRACE('t',"TRACE"),
	S0( 0, "N0"),
	S1( 1, "N1"),
	S2( 2, "N2"),
	S3( 3, "N3"),
	S4( 4, "N4"),
	S5( 5, "N5"),
	S6( 6, "N6"),
	S7( 7, "N7"),
	S8( 8, "N8"),
	S9( 9, "N9"),
	S10( 10, "N10"),
	STATUS(11,"status")
	;
	

	private int code;
	private String name;

	StreamID(int code, String name) {
		this.code = code;
		this.name = name;
		Z.map.put( name, this);
	}

	public int getCode() {
		return this.code;
	}

	public String getName() {
		return this.name;
	}

	public static StreamID fromName(String name) {		
		StreamID sid = Z.map.get( name);
		
		return sid;
	}

	public static StreamID fromCode(int sid) {
		for( StreamID v : Z.map.values() ) {
			if( sid == v.getCode() ) {
				return v;
			}
		}
		
//		String name = "" + sid;
//		StreamID v = new StreamID( sid, name );
//		Z.map.put( key,  v);
		log.error("Could not find StreamID: {}", sid );
		
		return null;
	}
}
