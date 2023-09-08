package idea.driver.infinity;

public class NetUnitsOfMeasure {
	
	public static final int UOM_INVALID = 0;
	public static final int UOM_METER = 1;
	public static final int UOM_MM = 2;
	public static final int UOM_INCH = 3;
	public static final int UOM_FOOT = 4;
	public static final int UOM_SECOND = 5;
	public static final int UOM_MINUTE = 6;
	public static final int UOM_HOUR = 7;
	public static final int UOM_DAY = 8;
	public static final int UOM_MMHG = 9;
	public static final int UOM_KPA = 10;
	public static final int UOM_CM_H2O = 11;
	public static final int UOM_GRAM = 12;
	public static final int UOM_KG = 13;
	public static final int UOM_LB = 14;
	public static final int UOM_LITER = 15;
	public static final int UOM_ML = 16;
	public static final int UOM_CENTIGRADE = 17;
	public static final int UOM_FARENHEIT = 18;
	public static final int UOM_KELVIN = 19;
	public static final int UOM_VOLT = 20;
	public static final int UOM_MILLIVOLT = 21;
	public static final int UOM_MICROVOLT = 22;
	public static final int UOM_OHM = 23;
	public static final int UOM_LITERS_PER_MIN = 24;
	public static final int UOM_ML_PER_SEC = 25;
	public static final int UOM_BEATS_PER_MIN = 26;
	public static final int UOM_BREATHS_PER_MIN = 27;
	public static final int UOM_PERCENT = 28;
	public static final int UOM_COUNTS = 29;
	public static final int UOM_UNITLESS = 30;
	public static final int UOM_CUBIC_CM = 31;
	public static final int UOM_MILLIVOLTS_PER_CM = 32;
	public static final int UOM_MM_PER_SEC = 33;
	public static final int UOM_CENTIMETER = 34;
	public static final int UOM_HERTZ = 35;
	public static final int UOM_LITER_PER_MIN_PER_METER_SQUARED = 36;
	public static final int UOM_DYNE_SEC_PER_CM_TO_FIFTH = 37;
	public static final int UOM_DYNE_SEC_METER_SEQUARED_PER_CM_TO_FIFTH = 38;
	public static final int UOM_ML_PER_MIN = 39;
	public static final int UOM_ML_PER_BEAT = 40;
	public static final int UOM_ML_PER_CM_H2O = 41;
	public static final int UOM_CM_H2O_PER_LITER = 42;
	public static final int UOM_CC_PER_MIN = 43;
	public static final int UOM_DELTA_DEGREES_C = 44;
	public static final int UOM_DELTA_DEGREES_F = 45;
	public static final int UOM_BAROMETRIC_PRESSURE = 46;
	public static final int UOM_DECIBEL = 47;
	public static final int UOM_BAR = 48;
	public static final int UOM_PSO = 49;
	public static final int UOM_OUNCE = 50;
	public static final int UOM_ML_PER_METER_SQUARED = 51;
	public static final int UOM_GRAM_METER = 52;
	public static final int UOM_GRAM_METER_PER_METER_SQUARED = 53;
	public static final int UOM_MMHG_PER_MINUTE = 54;
	public static final int UOM_ML_PER_BREATH = 55;
	public static final int UOM_ML_PER_DECILITER = 56;
	public static final int UOM_ML_PER_MIN_PER_METER_SQUARED = 57;
	public static final int UOM_JOULES_PER_LITER_PER_SECOND = 58;
	public static final int UOM_CMH2O_PER_LITER_PER_SECOND = 59;
	public static final int UOM_GRAMS_PER_LITER = 60;
	public static final int UOM_GRAMS_PER_DECI_LITER = 61;
	public static final int UOM_GRAMS_PER_100_ML = 62;
	public static final int UOM_MM_PER_LITER = 63;
	public static final int UOM_MEQ_PER_ML = 64;
	public static final int UOM_MEQ_PER_LITER = 65;
	public static final int UOM_MBAR = 66;
	public static final int UOM_MBAR_TIMES_S_L_10 = 67;
	public static final int UOM_MBAR_L_S = 68;
	public static final int UOM_ON_OFF = 69;
	public static final int UOM_MS_SQUARED_PER_SEC = 70;
	public static final int UOM_BPM_PER_LITER = 71;
	public static final int UOM_LITERS_PER_BAR = 72;
	public static final int UOM_MBAR_PER_LITER_10 = 73;
	public static final int UOM_MILLILITER_PER_KILOGRAM = 74;
	public static final int UOM_MMHG_PER_SEC = 75;
	public static final int UOM_DYNE_SEC_CM_TO_MINUS_5 = 76;
	public static final int UOM_DYNE_SEC_CM_TO_MINUS_5_PER_METER_SQUARED = 77;
	public static final int UOM_PERCENT_PER_HALF_HR = 78;
	public static final int UOM_PSIG = 79;
	public static final int UOM_ML_PER_M2 = 80;
	public static final int UOM_ML_PER_BEAT_PER_M2 = 81;
	
	public static final int UOM_PSVRI = 91;
	
	public static String toText( int uom ) {
	
		String [] uomCodes = Contants.getUOMCodes();
		if( uom >= uomCodes.length ) {
			return "?" + uom;
		}
		return uomCodes[uom];
	}
}
