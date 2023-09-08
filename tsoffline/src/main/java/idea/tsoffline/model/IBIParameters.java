package idea.tsoffline.model;

import lombok.Data;

@Data
// @EqualsAndHashCode(callSuper=false)
public class IBIParameters extends DerivedParamsBase {
	private int minIBI;
	private int maxIBI;
	private int flowThreshold;
}
