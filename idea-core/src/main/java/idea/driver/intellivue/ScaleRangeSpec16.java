package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class ScaleRangeSpec16 implements Reportable {
	float lower_absolute_value;
	float upper_absolute_value;
	short lower_scaled_value;
	short upper_scaled_value;
	
	public static ScaleRangeSpec16 parse( ByteBuffer bb ) {
		ScaleRangeSpec16 spec = new ScaleRangeSpec16();
		
		spec.lower_absolute_value = IntellivueUtil.parsePhilipsFloat(bb);
		spec.upper_absolute_value = IntellivueUtil.parsePhilipsFloat(bb);
		spec.lower_scaled_value = bb.getShort();
		spec.upper_scaled_value = bb.getShort();
		
		return spec;
	}

	@Override
	public void dump() {
		System.out.println("ScaleRangeSpec16");
		System.out.println("  lower_absolute_value: " + lower_absolute_value);
		System.out.println("  upper_absolute_value: " + upper_absolute_value);
		System.out.println("    lower_scaled_value: " + lower_scaled_value);
		System.out.println("    upper_scaled_value: " + upper_scaled_value);
	}
}
