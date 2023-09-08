package idea.tsoffline.model;

import idea.schema.rp.RpMetric;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimeseriesType;

public class FormulaSignal extends HPSplitableLayer {

	public String sig1;
	public String sig2;
	public FormulaOp op;

	public FormulaSignal(RpMetric m) {
		super(m, TimeseriesType.TT_FORMULA );
	}

	@Override
	public String toString() {
		String s;
		if (op == null) {
			s = "??";
		} else if (sig2 == null) { // this should actually take care of all cases
			s = op + "( ${" + sig1 + "} )";
		} else if (op.name().equals("Mean")) { // here for historical reasons...unused?
			s = op + "( ${" + sig1 + "} )";
		} else if (op.name().equals("Derivative")) { // here for historical reasons...unused?
			s = op + "( ${" + sig1 + "} )";
		} else {
			s = op + "( ${" + sig1 + "} , ${" + sig2 + "} )";
		}
		return s;
	}

}
