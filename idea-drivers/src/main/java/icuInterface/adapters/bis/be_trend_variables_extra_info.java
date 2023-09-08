package icuInterface.adapters.bis;

import java.nio.ByteBuffer;

import lombok.Data;

@Data
public class be_trend_variables_extra_info extends be_trend_variables_info {
	short burst_per_min; // ranges from 0 to 30
	short rfu1; // reserved for future use
	short rfu2;
	short rfu3;
	short rfu4;
	short rfu5;

	public be_trend_variables_extra_info(ByteBuffer bb) {
		super( bb );
		burst_per_min = bb.getShort();
		rfu1 = bb.getShort();
		rfu2 = bb.getShort();
		rfu3 = bb.getShort();
		rfu4 = bb.getShort();
		rfu5 = bb.getShort();
	}
}
