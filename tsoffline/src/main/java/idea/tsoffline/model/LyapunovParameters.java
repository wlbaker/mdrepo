package idea.tsoffline.model;

import lombok.Data;

@Data
public class LyapunovParameters extends DerivedParamsBase {
	private int window;
	private int embedding;
	private double dt;
	private int windowIncrement;
	private int lag;
	private int divergeT;
	private int exclusionWindow;
}
