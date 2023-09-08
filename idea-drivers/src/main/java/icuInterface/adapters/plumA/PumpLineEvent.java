package icuInterface.adapters.plumA;

public class PumpLineEvent {
	
	private String category;
	private int lgID;
	private long tm;
	private String lineID;
	private double rate;
	private double vtbi;

	public String getCategory() {
		return category;
	}
	public void setCategory(String category) {
		this.category = category;
	}
	public int getLgID() {
		return lgID;
	}
	public void setLgID(int lgID) {
		this.lgID = lgID;
	}
	public long getTm() {
		return tm;
	}
	public void setTm(long tm) {
		this.tm = tm;
	}
	public void setLine(String lineID) {
		this.lineID = lineID;
	}
	public void setRate(double rate) {
		this.rate = rate;
	}
	public void setVTBI(double vtbi) {
		this.vtbi = vtbi;
	}
}
