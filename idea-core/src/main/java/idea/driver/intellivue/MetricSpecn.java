package idea.driver.intellivue;

import java.nio.ByteBuffer;

import lombok.Data;

@Data
public class MetricSpecn implements Reportable {
	
	int update_period;
	short category;
	short access;
	short structure;
	short relevance;
	
	public static MetricSpecn parse(ByteBuffer bb) {
		MetricSpecn spec = new MetricSpecn();
		
		spec.update_period = bb.getInt();   // 8192 == 1 sec
		spec.category = bb.getShort();      // manual, calculated, adjusted patient temp, etc
		spec.access = bb.getShort();        // intermittend, periodic, episodic, noncontinuous
		spec.structure = bb.getShort();     // simple/compound...and number of components...0 if simple
		spec.relevance = bb.getShort();     // 16bit wide field for Philips internal use only
		
		if( spec.category != 1 && spec.category != 5 ) {
			System.out.println("debug MetricSpecn: category=" + spec.category );
		}

		return spec;
	}

	@Override
	public void dump() {
		System.out.print("Metric Specn     spn  rel time/ctg/access/struc/relev: ");
		System.out.print(update_period + "/c" + category + "/a" + access + "/s" + structure + "/r" + relevance);
		System.out.println();
	
	}

	@Override
	public String toString() {
		return "specn(p=" + update_period + "/c=" + category + "/a=" + access + "/s=" + structure + "/r=" + relevance;
	}
}
