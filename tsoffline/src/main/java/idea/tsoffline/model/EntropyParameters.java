package idea.tsoffline.model;

import lombok.Data;

@Data
public class EntropyParameters  extends DerivedParamsBase {
	private int window;
	private int embedding;
	private int lag;
	private double tolerance;
	private boolean baselineRemoval;
}
