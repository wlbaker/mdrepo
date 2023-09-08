package idea.tsoffline.model;

public enum FormulaOp {
	Add, Subtract, Divide, Mean, Derivative, Duplicate;

	public static FormulaOp[] asArray() {
		return new FormulaOp [] { //
				FormulaOp.Add, //
				FormulaOp.Subtract, //
				FormulaOp.Divide, //
				FormulaOp.Mean, //
				FormulaOp.Derivative, //
				FormulaOp.Duplicate //
				};
	
	}
	
	public static FormulaOp fromString(String s) {
		if( "add".equalsIgnoreCase(s)) return Add;
		if( "subtract".equalsIgnoreCase(s)) return Subtract;
		if( "divide".equalsIgnoreCase(s)) return Divide;
		if( "mean".equalsIgnoreCase(s)) return Mean;
		if( "derivative".equalsIgnoreCase(s)) return Derivative;
		if( "duplicate".equalsIgnoreCase(s)) return Duplicate;
		return null;
	}
};

