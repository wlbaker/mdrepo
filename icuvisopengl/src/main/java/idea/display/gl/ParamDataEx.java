package idea.display.gl;

import idea.display.FieldData;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;

@Data
public class ParamDataEx {

	private String name;
	@Getter @Setter private String text;
	private int x;
	private int y;
	private int sz;
	private FieldData pdat;
	
	public ParamDataEx(String name, FieldData pdat, int x, int y, int sz) {
		this.name = name;
		this.pdat = pdat;
		this.x = x;
		this.y = y;
		this.sz = sz;
	}

	public String getLoc() {
		if( pdat != null ) {
			return pdat.getLoc();
		}
		return null;
	}

}
