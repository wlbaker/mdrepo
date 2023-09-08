package idea.tsoffline;

/*
 * This data type is used to determine what is saved in the session file.
 */
public enum TimeseriesType {
	
	TT_DATA,       // Data is not saved, it comes from the raw data files
	TT_ANNOTATION, // All annotations are saved in the session
	TT_FORMULA,    // The formula is saved, but no the data points themselves
	TT_SCRIPT,      // Kinda like a formula, but really an R script
	TT_TRACE       // Kinda like a formula.  Derived data.
}
