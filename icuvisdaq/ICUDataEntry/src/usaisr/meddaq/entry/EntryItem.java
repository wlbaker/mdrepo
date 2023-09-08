package idea.meddaq.entry;


public class EntryItem {

	private String prompt;
	private String dev;
	private String src_loc;
	private String validation;
	private Object value;
	private boolean visible;
	private double scale;
	private Class<?> valueClass;
	private String dest_loc;
	private boolean manual;

	public EntryItem(String prompt, String dev, String src_loc, String dest_loc, String validation) {
		this.prompt = prompt;
		this.dev = dev;
		this.src_loc = src_loc;
		this.dest_loc = dest_loc;
		this.validation = validation;
	}

	public String getPrompt() {
		return prompt;
	}

	public String getDev() {
		return dev;
	}

	public String getSourceLoc() {
		return src_loc;
	}

	public String getDestLoc() {
		return dest_loc;
	}

	public String getValidation() {
		return validation;
	}

	public String getDevValue() {
		return dev + ":" + src_loc;
	}

	public Object getEntryValue() {
		return value;
	}

	public void setEntryValue(Object value) {
		this.value = value;
	}

	public void setVisible(boolean visible) {
		this.visible = visible;
	}

	public void setValueClass(Class<?> cl) {
		this.valueClass = cl;
	}
	
	public Class<?> getValueClass() {
		return valueClass;
	}

	public void setScale(double scale) {
		this.scale = scale;
	}

	public double getScale() {
		return scale;
	}

	public void setManual(boolean b) {
		this.manual = b;
	}
	
	public boolean isManual() {
		return manual;
	}
}
