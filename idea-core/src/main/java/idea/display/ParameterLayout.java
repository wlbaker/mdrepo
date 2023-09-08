package idea.display;

import java.io.Serializable;

import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class ParameterLayout implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	@Getter private byte id;
	@Getter @Setter private byte format;
	@Getter @Setter private byte foreground;
	@Getter @Setter private byte background;
	
	@Getter @Setter private byte orientation;
	
	@Getter private int row;
	@Getter private int column;
	
	public FieldData [] fields;

	private boolean selected;

	public ParameterLayout( byte pbox_format, int n_fields ) {
		this.format = pbox_format;
		this.fields = new FieldData[n_fields];
	}
	
	public ParameterLayout( byte pbox_format, FieldData [] paramSetup ) {
		this.format = pbox_format;
		this.fields = paramSetup;
	}
	
	public ParameterLayout( byte pbox_id, byte pbox_format, byte foreground, FieldData [] paramSetup ) {
		this.id = pbox_id;
		this.format = pbox_format;
		this.foreground = foreground;
		this.fields = paramSetup;
	}

	public FieldData[] getFieldData() {
		return fields;
	}

	public FieldData getField(int field_idx) {
		if( fields == null || field_idx < 0 || field_idx >= fields.length ) {
			log.error("Parameter FieldData not available: " + field_idx);
			return null;
		}

		return fields[field_idx];
	}
	
	public void setField(int field_idx, FieldData val) {
		fields[field_idx] = val;
	}

	public int getFieldCount() {
		if( fields == null ) {
			return 0;
		}
		return fields.length;
	}

	public void setSelected(boolean b) {
		this.selected = b;
	}
	
	public boolean isSelected () {
		return selected;
	}


}