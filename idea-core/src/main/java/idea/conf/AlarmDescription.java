package idea.conf;

import java.io.Serializable;

public class AlarmDescription implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Object location;
	private String code;
	private String name;
	private String unit;
	
	public AlarmDescription(Object location, String code, String name, String unit) {
		this.setLocation(location);
		this.code = code;
		this.name = name;
		this.unit = unit;
	}
	
	public String getName() {
		return name;
	}
	public String getUnit() {
		return unit;
	}

	public void setLocation(Object location) {
		this.location = location;
	}

	public Object getLocation() {
		return location;
	}

	public String getCode() {
		return code;
	}

	public void setUnit(String unit) {
		this.unit = unit;
	}
	
	public void setCode(String code) {
		this.code = code;
	}


	@Override
	public String toString() {
		return "Value " + getLocation() + " " + getName();
	}

	public void setName(String trimmed_name) {
		name = trimmed_name;
	}

}
