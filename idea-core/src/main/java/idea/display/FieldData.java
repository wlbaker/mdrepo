package idea.display;

import lombok.Data;

@Data
public class FieldData  {
	
	private String loc;
	private byte uom;
	private byte foreground = 0;
	
	public FieldData(String loc, byte uom) {
		this.loc = loc;
		this.uom = uom;
	}

	public byte getForeground() {
		return foreground;
	}


}
