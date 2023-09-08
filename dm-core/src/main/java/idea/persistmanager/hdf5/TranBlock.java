package idea.persistmanager.hdf5;

import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class TranBlock extends PersistentItem {
	protected static RpMetric[] metrics;
	static {
		metrics = IntfUtil.getMetrics(TranBlock.class);
	}

	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public TranBlock() {
		this.setStreamID(StreamID.WAVEFORM.getCode());
	}


	@Metric(loc = "fpos", code = "", unit = "", subtyp=DataTyp.LONG_TYP)
	private long fpos;
	@Metric(loc = "ftyp", code = "", unit = "", subtyp=DataTyp.BYTE_TYP)
	private byte ftyp;
	
	@Text(loc = "fname", code = "", unit = "", subtyp=DataTyp.STRING_TYP, length=8 )
	private String name;
	
}

