package idea.driver.intellivue;

import java.nio.ByteBuffer;
import java.util.LinkedList;
import java.util.List;

public class SampleArrayFixedValueSpecn implements Reportable {

	List<SaFixedValSpec16> arr = new LinkedList<SaFixedValSpec16>();
	
	public static SampleArrayFixedValueSpecn parse(ByteBuffer bb) {
		SampleArrayFixedValueSpecn specn = new SampleArrayFixedValueSpecn();
		
		short count = bb.getShort();
		short length = bb.getShort();
		for( int i = 0; i < count ; i++ ) {
			
			 SaFixedValSpec16 spec16 = SaFixedValSpec16.parse( bb );
		
			 specn.arr.add(spec16);
		}
		return specn;
	}

	public List<SaFixedValSpec16> getSpecs() {
		return arr;
	}
	
	@Override
	public void dump() {
		System.out.println( "SampleArrayFixedValSpecn");
		for( SaFixedValSpec16 spec16 : arr ) {
			spec16.dump();
		}
		
	}

}
