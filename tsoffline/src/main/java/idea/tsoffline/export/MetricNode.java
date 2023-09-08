package idea.tsoffline.export;

import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class MetricNode {
	private String name;
	private RpMetric sig;

	public MetricNode(String name, RpMetric sig) {
		this.name = name;
		this.sig = sig;
	}

	@Override
	public String toString() {
		return sig.getAlias();
	}
}
