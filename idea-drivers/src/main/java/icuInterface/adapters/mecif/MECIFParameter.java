package icuInterface.adapters.mecif;

import idea.schema.rp.RpMetric;

public class MECIFParameter {

	private static final long serialVersionUID = 1L;

	String key;
	int sourceId;
	int channelId;
	public short msgType;
	byte channelNo;
	byte sourceNo;
	byte layer;

	// singleReqId is used as a temporary to determine which code to associate with this device parameter
	private int singleReqId;  
	private String code;  // determined by SINGLE_TUNE_REQ
	//private MetricDescription desc;

	public MECIFParameter(int sourceId, int channelId, short msgType, byte chNo, byte sourceNo, byte layer, RpMetric desc ) {
		//this.desc = desc;
		this.sourceId = sourceId;
		this.channelId = channelId;
		this.msgType = msgType;
		this.channelNo = chNo;
		this.sourceNo = sourceNo;
		this.layer = layer;
		
		key = "" + sourceId + ":" + channelId; 
	}

	@Override
	public String toString() {
		return key;
	}

	public int getSourceId() {
		return sourceId;
	}

	public int getChannelId() {
		// TODO Auto-generated method stub
		return channelId;
	}

	public short getMessageType() {
		return msgType;
	}

	public byte getLayer() {
		return layer;
	}

	public byte getChannelNo() {
		return channelNo;
	}

	public byte getSourceNo() {
		return sourceNo;
	}

	public Object getKey() {
		return key;
	}

	//public MetricDescription getMetricDescription() {
	//	return desc;
	//}

	public String getCode() {
		if( code == null ) {
			return key;
		}
		return code;
	}
	
	public void setCode( String code ) {
		this.code = code;
	}
	
	public int getSingleReqId() {
		return singleReqId;
	}
	
	public void setSingleReqId( int singleReqId ) {
		this.singleReqId = singleReqId;
	}
}
