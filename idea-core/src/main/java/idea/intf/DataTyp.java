package idea.intf;

public class DataTyp {
	public static final int INT_TYP = 1;
	public static final int LONG_TYP = 2;
	public static final int DOUBLE_TYP = 3;
	public static final int BYTE_TYP = 4;
	public static final int STRING_TYP = 5;
	public static final int OBJ_TYP = 6;
	public static final int FLOAT_TYP = 7;
	public static final int INT_ARR_TYP = 14;
	public static final int OBJ_ARR_TYP = 16;
	public static final int DOUBLE_ARR_TYP = 19;
	public static final int FLOAT_ARR_TYP = 23;
	public static final int INVALID_ARR_TYP = 0xff;
	public static final int INVALID_TYP = 0xfe;
	public static final int BOOLEAN_TYP = 0x20;

	public static int fromType(Class<?> type) {
		int dt = INVALID_TYP;

		if (float[].class == type) {
			dt = FLOAT_ARR_TYP;
		} else if (int[].class == type) {
			dt = INT_ARR_TYP;
		} else if (double[].class == type) {
			dt = DOUBLE_ARR_TYP;
		} else if (int.class == type) {
			dt = INT_TYP;
		} else if (Integer.class == type) {
			dt = INT_TYP;
		} else if (long.class == type) {
			dt = LONG_TYP;
		} else if (Long.class == type) {
			dt = LONG_TYP;
		} else if (double.class == type) {
			dt = DOUBLE_TYP;
		} else if (Double.class == type) {
			dt = DOUBLE_TYP;
		} else if (float.class == type) {
			dt = FLOAT_TYP;
		} else if (Float.class == type) {
			dt = FLOAT_TYP;
		} else if (byte.class == type) {
			dt = BYTE_TYP;
		} else if (Byte.class == type) {
			dt = BYTE_TYP;
		} else if (boolean.class == type) {
			dt = BOOLEAN_TYP;
		} else if (Boolean.class == type) {
			dt = BOOLEAN_TYP;
		} else if (String.class == type) {
			dt = STRING_TYP;
		} else {
			dt = OBJ_TYP;
		}
		return dt;
	}
}
