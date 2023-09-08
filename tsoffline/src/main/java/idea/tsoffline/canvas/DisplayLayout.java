package idea.tsoffline.canvas;

public enum DisplayLayout {
	// OVERLAP("Overlap"), TILED("Tiled"), 
	GD_ONE("One Graph"),
	GD_TWO_BOTTOM("Two Bottom"),
	GD_TWO_EQUAL("Two Equal"),
	GD_TWO_TOP("Two Top"),
	GD_THREE_BOTTOM("Three Bottom"),
	GD_THREE_CENTER("Three Center"),
	GD_THREE_TOP("Three Top"),
	GD_FOUR("Four Graphs"),
	TILED("* CUSTOM *")
	;
	
	private String desc;

	DisplayLayout( String desc ) {
		this.desc = desc;
	}

	@Override
	public String toString() {
		return desc;
	}
	
	
}
