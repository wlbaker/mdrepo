package idea.driver.intellivue;

import java.util.HashMap;

import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpUnit;

class UnitCodes {

	private static HashMap<Short, String> map = new HashMap<Short, String>();
	
	static {
		map.put((short) 0, "NOS"); // ( no dimension ) NOM_DIM_NOS
		map.put((short) 2, "/"); // ( / ) NOM_DIM_DIV
		map.put((short) 512, "-"); // ( no dimension ) NOM_DIM_DIMLESS
		map.put((short) 544, "%"); // ( percentage ) NOM_DIM_PERCENT

		map.put((short) 576, "ppth"); // ( parts per thousand ) NOM_DIM_PARTS_PER_THOUSAND
		map.put((short) 608, "ppm"); // ( parts per million ) NOM_DIM_PARTS_PER_MILLION
		map.put((short) 864, "mol/mol"); // ( mole per mole ) NOM_DIM_X_MOLE_PER_MOLE
		map.put((short) 672, "ppb"); // ( parts per billion ) NOM_DIM_PARTS_PER_BILLION
		map.put((short) 704, "ppt"); // ( parts per trillion ) NOM_DIM_PARTS_PER_TRILLION
		map.put((short) 992, "pH"); // ( pH ) NOM_DIM_PH
		map.put((short) 1024, "drop"); // ( vital signs count drop ) NOM_DIM_DROP
		map.put((short) 1056, "rbc"); // ( vital signs count red blood cells ) NOM_DIM_RBC
		map.put((short) 1088, "beat"); // ( vital signs count beat ) NOM_DIM_BEAT
		map.put((short) 1120, "breath"); // ( vital signs count breath ) NOM_DIM_BREATH
		map.put((short) 1152, "cell"); // ( vital signs count cells ) NOM_DIM_CELL
		map.put((short) 1184, "cough"); // ( vital signs count cough ) NOM_DIM_COUGH
		map.put((short) 1216, "sigh"); // ( vital signs count sigh ) NOM_DIM_SIGH
		map.put((short) 1248, "%PCV"); // ( percent of packed cell volume ) NOM_DIM_PCT_PCV
		map.put((short) 1280, "m"); // ( meter ) NOM_DIM_X_M
		map.put((short) 1297, "cm"); // ( centimeter ) NOM_DIM_CENTI_M
		map.put((short) 1298, "mm"); // ( millimeter ) NOM_DIM_MILLI_M
		map.put((short) 1299, "m"); // ( micro-meter ) NOM_DIM_MICRO_M
		map.put((short) 1376, "in"); // ( inch ) NOM_DIM_X_INCH
		map.put((short) 1426, "ml/m2"); // ( used e.g. for SI and ITBVI ) NOM_DIM_MILLI_L_PER_M_SQ
		map.put((short) 1440, "/m"); // ( per meter ) NOM_DIM_PER_X_M
		map.put((short) 1458, "/mm"); // ( per millimeter ) NOM_DIM_PER_MILLI_M
		map.put((short) 1472, "m2"); // ( used e.g. for BSA calculation ) NOM_DIM_SQ_X_M
		map.put((short) 1504, "in2"); // ( used e.g. for BSA calculation ) NOM_DIM_SQ_X_INCH
		map.put((short) 1568, "m3"); // ( cubic meter ) NOM_DIM_CUBIC_X_M
		map.put((short) 1585, "cm3"); // ( cubic centimeter ) NOM_DIM_CUBIC_CENTI_M
		map.put((short) 1600, "l"); // ( liter ) NOM_DIM_X_L
		map.put((short) 1618, "ml"); // ( milli-liters used e.g. for EVLW ITBV SV ) NOM_DIM_MILLI_L
		map.put((short) 1650, "ml/breath"); // ( milli-liter per breath ) NOM_DIM_MILLI_L_PER_BREATH
		map.put((short) 1681, "/cm3"); // ( per cubic centimeter ) NOM_DIM_PER_CUBIC_CENTI_M
		map.put((short) 1696, "/l"); // ( per liter ) NOM_DIM_PER_X_L
		map.put((short) 1716, "1/nl"); // ( per nano-liter ) NOM_DIM_PER_NANO_LITER
		map.put((short) 1728, "g"); // ( gram ) NOM_DIM_X_G
		map.put((short) 1731, "kg"); // ( kilo-gram ) NOM_DIM_KILO_G
		map.put((short) 1746, "mg"); // ( milli-gram ) NOM_DIM_MILLI_G
		map.put((short) 1747, "g"); // ( micro-gram ) NOM_DIM_MICRO_G
		map.put((short) 1748, "ng"); // ( nono-gram ) NOM_DIM_NANO_G
		map.put((short) 1760, "lb"); // ( pound ) NOM_DIM_X_LB
		map.put((short) 1792, "oz"); // ( ounce ) NOM_DIM_X_OZ
		map.put((short) 1824, "/g"); // ( per gram ) NOM_DIM_PER_X_G
		map.put((short) 1856, "g-m"); // ( used e.g. for LVSW RVSW ) NOM_DIM_X_G_M
		map.put((short) 1859, "kg-m"); // ( used e.g. for RCW LCW ) NOM_DIM_KILO_G_M
		map.put((short) 1888, "g-m/m2"); // ( used e.g. for LVSWI and RVSWI ) NOM_DIM_X_G_M_PER_M_SQ
		map.put((short) 1891, "kg-m/m2"); // ( used e.g. for LCWI and RCWI ) NOM_DIM_KILO_G_M_PER_M_SQ
		map.put((short) 1923, "kg-m2"); // ( gram meter squared ) NOM_DIM_KILO_G_M_SQ
		map.put((short) 1955, "kg/m2"); // ( kilo-gram per square meter ) NOM_DIM_KG_PER_M_SQ
		map.put((short) 1987, "kg/m3"); // ( kilo-gram per cubic meter ) NOM_DIM_KILO_G_PER_M_CUBE
		map.put((short) 2016, "g/cm3"); // ( gram per cubic meter ) NOM_DIM_X_G_PER_CM_CUBE
		map.put((short) 2034, "mg/cm3"); // ( milli-gram per cubic centimeter ) NOM_DIM_MILLI_G_PER_CM_CUBE
		map.put((short) 2035, "g/cm3"); // ( micro-gram per cubic centimeter ) NOM_DIM_MICRO_G_PER_CM_CUBE
		map.put((short) 2036, "ng/cm3"); // ( nano-gram per cubic centimeter ) NOM_DIM_NANO_G_PER_CM_CUBE
		map.put((short) 2048, "g/l"); // ( gram per liter ) NOM_DIM_X_G_PER_L
		map.put((short) 2112, "g/dl"); // ( used e.g. for Hb ) NOM_DIM_X_G_PER_DL
		map.put((short) 2130, "mg/dl"); // ( milli-gram per deciliter ) NOM_DIM_MILLI_G_PER_DL
		map.put((short) 2144, "g/ml"); // ( gram per milli-liter ) NOM_DIM_X_G_PER_ML
		map.put((short) 2162, "mg/ml"); // ( milli-gram per milli-liter ) NOM_DIM_MILLI_G_PER_ML
		map.put((short) 2163, "g/ml"); // ( micro-gram per milli-liter ) NOM_DIM_MICRO_G_PER_ML
		map.put((short) 2164, "ng/ml"); // ( nano-gram per milli-liter ) NOM_DIM_NANO_G_PER_ML
		map.put((short) 2176, "sec"); // ( seconds ) NOM_DIM_SEC
		map.put((short) 2194, "msec"); // ( milli-seconds ) NOM_DIM_MILLI_SEC
		map.put((short) 2195, "sec"); // ( micro-seconds ) NOM_DIM_MICRO_SEC
		map.put((short) 2208, "min"); // ( minutes ) NOM_DIM_MIN
		map.put((short) 2240, "hrs"); // ( hours ) NOM_DIM_HR
		map.put((short) 2272, "days"); // ( days ) NOM_DIM_DAY
		map.put((short) 2304, "weeks"); // ( weeks ) NOM_DIM_WEEKS
		map.put((short) 2336, "months"); // ( months ) NOM_DIM_MON
		map.put((short) 2368, "years"); // ( years ) NOM_DIM_YR
		map.put((short) 2400, "TOD"); // ( time of day ) NOM_DIM_TOD
		map.put((short) 2432, "date"); // ( date ) NOM_DIM_DATE
		map.put((short) 2464, "/sec"); // ( per second ) NOM_DIM_PER_X_SEC
		map.put((short) 2496, "Hz"); // ( hertz ) NOM_DIM_HZ
		map.put((short) 2528, "/min"); // ( per minute used e.g. for the PVC count numerical value ) NOM_DIM_PER_MIN
		map.put((short) 2560, "/hour"); // ( per hour ) NOM_DIM_PER_HR
		map.put((short) 2592, "/day"); // ( per day ) NOM_DIM_PER_DAY
		map.put((short) 2624, "/week"); // ( per week ) NOM_DIM_PER_WK
		map.put((short) 2656, "/month"); // ( per month ) NOM_DIM_PER_MO
		map.put((short) 2688, "/year"); // ( per year ) NOM_DIM_PER_YR
		map.put((short) 2720, "bpm"); // ( beats per minute used e.g. for HR/PULSE ) NOM_DIM_BEAT_PER_MIN
		map.put((short) 2752, "puls/min"); // ( puls per minute ) NOM_DIM_PULS_PER_MIN
		map.put((short) 2784, "rpm"); // ( respiration breathes per minute ) NOM_DIM_RESP_PER_MIN
		map.put((short) 2816, "m/sec"); // ( meter per second ) NOM_DIM_X_M_PER_SEC
		map.put((short) 2834, "mm/sec"); // ( speed for recordings ) NOM_DIM_MILLI_M_PER_SEC
		map.put((short) 2848, "l/min/m2"); // ( used for CI ) NOM_DIM_X_L_PER_MIN_PER_M_SQ
		map.put((short) 2866, "ml/min/m2"); // ( used for DO2I VO2I O2AVI ) NOM_DIM_MILLI_L_PER_MIN_PER_M_SQ
		map.put((short) 2880, "m2/sec"); // ( square meter per second ) NOM_DIM_SQ_X_M_PER_SEC
		map.put((short) 2897, "cm2/sec"); // ( square centimeter per second ) NOM_DIM_SQ_CENTI_M_PER_SEC
		map.put((short) 2912, "m3/sec"); // ( cubic meter per second ) NOM_DIM_CUBIC_X_M_PER_SEC
		map.put((short) 2929, "cm3/sec"); // ( cubic centimeter per second ) NOM_DIM_CUBIC_CENTI_M_PER_SEC
		map.put((short) 3040, "l/sec"); // ( liter per second ) NOM_DIM_X_L_PER_SEC
		map.put((short) 3072, "l/min"); // ( liter per minutes ) NOM_DIM_X_L_PER_MIN
		map.put((short) 3088, "dl/min"); // ( deciliter per second ) NOM_DIM_DECI_L_PER_MIN
		map.put((short) 3090, "ml/min"); // ( used for DO2 VO2 ALVENT ) NOM_DIM_MILLI_L_PER_MIN
		map.put((short) 3104, "l/hour"); // ( liter per hour ) NOM_DIM_X_L_PER_HR
		map.put((short) 3122, "ml/hour"); // ( milli-liter per hour ) NOM_DIM_MILLI_L_PER_HR
		map.put((short) 3136, "l/day"); // ( liter per day ) NOM_DIM_X_L_PER_DAY
		map.put((short) 3154, "ml/day"); // ( milli-liter per day ) NOM_DIM_MILLI_L_PER_DAY
		map.put((short) 3186, "ml/kg"); // ( used e.g. for EVLWI ) NOM_DIM_MILLI_L_PER_KG
		map.put((short) 3299, "kg/sec"); // ( kilo-gram per second ) NOM_DIM_KILO_G_PER_SEC
		map.put((short) 3328, "g/min"); // ( gram per minute ) NOM_DIM_X_G_PER_MIN
		map.put((short) 3331, "kg/min"); // ( kilo-gram per minute ) NOM_DIM_KILO_G_PER_MIN
		map.put((short) 3346, "mg/min"); // ( milli-gram per minute ) NOM_DIM_MILLI_G_PER_MIN
		map.put((short) 3347, "g/min"); // ( micro-gram per minute ) NOM_DIM_MICRO_G_PER_MIN
		map.put((short) 3348, "ng/min"); // ( nano-gram per minute ) NOM_DIM_NANO_G_PER_MIN
		map.put((short) 3360, "g/hour"); // ( gram per hour ) NOM_DIM_X_G_PER_HR
		map.put((short) 3363, "kg/hour"); // ( kilo-gram per hour ) NOM_DIM_KILO_G_PER_HR
		map.put((short) 3378, "mg/hour"); // ( milli-gram per hour ) NOM_DIM_MILLI_G_PER_HR
		map.put((short) 3379, "g/hour"); // ( micro-gram per hour ) NOM_DIM_MICRO_G_PER_HR
		map.put((short) 3380, "ng/hr"); // ( nano-gram per hour ) NOM_DIM_NANO_G_PER_HR
		map.put((short) 3395, "kg/day"); // ( kilo-gram per day ) NOM_DIM_KILO_G_PER_DAY
		map.put((short) 3456, "g/kg/min"); // ( gram per kilo-gram per minute ) NOM_DIM_X_G_PER_KG_PER_MIN
		map.put((short) 3474, "mg/kg/min"); // ( milli-gram per kilo-gram per minute ) NOM_DIM_MILLI_G_PER_KG_PER_MIN
		map.put((short) 3475, "g/kg/min"); // ( micro-gram per kilo-gram per minute ) NOM_DIM_MICRO_G_PER_KG_PER_MIN
		map.put((short) 3476, "ng/kg/min"); // ( nano-gram per kilo-gram per minute ) NOM_DIM_NANO_G_PER_KG_PER_MIN
		map.put((short) 3488, "g/kg/hour"); // ( gram per kilo-gram per hour ) NOM_DIM_X_G_PER_KG_PER_HR
		map.put((short) 3506, "mg/kg/hour"); // ( mili-gram per kilo-gram per hour ) NOM_DIM_MILLI_G_PER_KG_PER_HR
		map.put((short) 3507, "g/kg/hour"); // ( micro-gram per kilo-gram per hour ) NOM_DIM_MICRO_G_PER_KG_PER_HR
		map.put((short) 3508, "ng/kg/hour"); // ( nano-gram per kilo-gram per hour ) NOM_DIM_NANO_G_PER_KG_PER_HR
		map.put((short) 3555, "kg/l/sec"); // ( kilo-gram per liter per second ) NOM_DIM_KILO_G_PER_L_SEC
		map.put((short) 3683, "kg/m/sec"); // ( kilo-gram per meter per second ) NOM_DIM_KILO_G_PER_M_PER_SEC
		map.put((short) 3715, "kg-m/sec"); // ( kilo-gram meter per second ) NOM_DIM_KILO_G_M_PER_SEC
		map.put((short) 3744, "N-s"); // ( newton seconds ) NOM_DIM_X_NEWTON_SEC
		map.put((short) 3776, "N"); // ( newton ) NOM_DIM_X_NEWTON
		map.put((short) 3840, "Pa"); // ( pascal ) NOM_DIM_X_PASCAL
		map.put((short) 3842, "hPa"); // ( hekto-pascal ) NOM_DIM_HECTO_PASCAL
		map.put((short) 3843, "kPa"); // ( kilo-pascal ) NOM_DIM_KILO_PASCAL
		map.put((short) 3872, "mmHg"); // ( mm mercury ) NOM_DIM_MMHG
		map.put((short) 3904, "cmH2O"); // ( centimeter H20 ) NOM_DIM_CM_H2O
		map.put((short) 3954, "mBar"); // ( milli-bar ) NOM_DIM_MILLI_BAR
		map.put((short) 3968, "J"); // ( Joules ) NOM_DIM_X_JOULES
		map.put((short) 4000, "eV"); // ( electronvolts ) NOM_DIM_EVOLT
		map.put((short) 4032, "W"); // ( watt ) NOM_DIM_X_WATT
		map.put((short) 4050, "mW"); // ( milli-watt ) NOM_DIM_MILLI_WATT
		map.put((short) 4052, "nW"); // ( nano-watt ) NOM_DIM_NANO_WATT
		map.put((short) 4053, "pW"); // ( pico-watt ) NOM_DIM_PICO_WATT
		map.put((short) 4128, "Dyn-sec/cm^5"); // ( dyne second per cm^5 ) NOM_DIM_X_DYNE_PER_SEC_PER_CM5
		map.put((short) 4160, "A"); // ( ampere ) NOM_DIM_X_AMPS
		map.put((short) 4178, "mA"); // ( milli-ampereused e.g. for the battery indications ) NOM_DIM_MILLI_AMPS
		map.put((short) 4192, "C"); // ( coulomb ) NOM_DIM_X_COULOMB
		map.put((short) 4211, "C"); // ( micro-coulomb ) NOM_DIM_MICRO_COULOMB
		map.put((short) 4256, "V"); // ( volts ) NOM_DIM_X_VOLT
		map.put((short) 4274, "mV"); // ( milli-volt ) NOM_DIM_MILLI_VOLT
		map.put((short) 4275, "\\u00b4V"); // ( micro-volt ) NOM_DIM_MICRO_VOLT
		map.put((short) 4288, "Ohm"); // ( Ohm ) NOM_DIM_X_OHM
		map.put((short) 4291, "kOhm"); // ( kilo-ohm ) NOM_DIM_OHM_K
		map.put((short) 4352, "F"); // ( farad ) NOM_DIM_X_FARAD
		map.put((short) 4384, "K"); // ( kelvin ) NOM_DIM_KELVIN
		map.put((short) 4416, "F"); // ( degree-fahrenheit ) NOM_DIM_FAHR
		map.put((short) 4480, "cd"); // ( candela ) NOM_DIM_X_CANDELA
		map.put((short) 4530, "mOsm"); // ( milli-osmole ) NOM_DIM_MILLI_OSM
		map.put((short) 4544, "mol"); // ( mole ) NOM_DIM_X_MOLE
		map.put((short) 4562, "mmol"); // ( milli-mole ) NOM_DIM_MILLI_MOLE
		map.put((short) 4594, "mEq"); // ( milli-equivalents ) NOM_DIM_MILLI_EQUIV
		map.put((short) 4626, "mOsm/l"); // ( milli-osmole per liter ) NOM_DIM_MILLI_OSM_PER_L
		map.put((short) 4722, "mmol/l"); // ( used for HB ) NOM_DIM_MILLI_MOLE_PER_L
		map.put((short) 4723, "mol/l"); // ( micro-mol per liter ) NOM_DIM_MICRO_MOLE_PER_L
		map.put((short) 4850, "mEq/l"); // ( milli-equivalents per liter ) NOM_DIM_MILLI_EQUIV_PER_L
		map.put((short) 5202, "mEq/day"); // ( milli-equivalents per day ) NOM_DIM_MILLI_EQUIV_PER_DAY
		map.put((short) 5472, "i.u."); // ( international unit ) NOM_DIM_X_INTL_UNIT
		map.put((short) 5490, "mi.u."); // ( mili-international unit ) NOM_DIM_MILLI_INTL_UNIT
		map.put((short) 5504, "i.u./cm3"); // ( international unit per cubic centimeter )
											// NOM_DIM_X_INTL_UNIT_PER_CM_CUBE
		map.put((short) 5522, "mi.u./cm3"); // ( mili-international unit per cubic centimeter )
		// NOM_DIM_MILLI_INTL_UNIT_PER_CM_CUBE
		map.put((short) 5600, "i.u./ml"); // ( international unit per milli-liter ) NOM_DIM_X_INTL_UNIT_PER_ML
		map.put((short) 5664, "i.u./min"); // ( international unit per minute ) NOM_DIM_X_INTL_UNIT_PER_MIN
		map.put((short) 5618, "mi.u./ml"); // ( milli-international unit per milli-liter )
											// NOM_DIM_MILLI_INTL_UNIT_PER_ML
		map.put((short) 5682, "mi.u./min"); // ( milli-international unit per minute ) NOM_DIM_MILLI_INTL_UNIT_PER_MIN
		map.put((short) 5696, "i.u./hour"); // ( international unit per hour ) NOM_DIM_X_INTL_UNIT_PER_HR
		map.put((short) 5714, "mi.u./hour"); // ( milli-international unit per hour ) NOM_DIM_MILLI_INTL_UNIT_PER_HR
		map.put((short) 5792, "i.u./kg/min"); // ( international unit per kilo-gram per minute )
		// NOM_DIM_X_INTL_UNIT_PER_KG_PER_MIN
		map.put((short) 5810, "mi.u./kg/min"); // ( milli-international unit per kilo-gram per minute )
		// NOM_DIM_MILLI_INTL_UNIT_PER_KG_PER_MIN
		map.put((short) 5824, "i.u./kg/hour"); // ( international unit per kilo-gram per hour )
		// NOM_DIM_X_INTL_UNIT_PER_KG_PER_HR
		map.put((short) 5842, "mi.u./kg/hour"); // ( milli-international unit per kilo-gram per hour )
		// NOM_DIM_MILLI_INTL_UNIT_PER_KG_PER_HR
		map.put((short) 5906, "ml/cmH2O"); // ( milli-liter per centimeter H2O ) NOM_DIM_MILLI_L_PER_CM_H2O
		map.put((short) 5920, "cmH2O/l/sec"); // ( centimeter H2O per second ) NOM_DIM_CM_H2O_PER_L_PER_SEC
		map.put((short) 5970, "ml2/sec"); // ( milli-liter per second ) NOM_DIM_MILLI_L_SQ_PER_SEC
		map.put((short) 5984, "cmH2O/%"); // ( centimeter H2O per percent ) NOM_DIM_CM_H2O_PER_PERCENT
		map.put((short) 6016, "DS*m2/cm5"); // ( used for SVRI and PVRI ) NOM_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5
		map.put((short) 6048, "C"); // ( degree-celsius ) NOM_DIM_DEGC
		map.put((short) 6144, "cmH2O/l"); // ( centimeter H2O per liter ) NOM_DIM_CM_H2O_PER_L
		map.put((short) 6176, "mmHg/%"); // ( milli-meter mercury per percent ) NOM_DIM_MM_HG_PER_PERCENT
		map.put((short) 6211, "kPa/%"); // ( kilo-pascal per percent ) NOM_DIM_KILO_PA_PER_PERCENT
		map.put((short) 6272, "l/mmHg"); // (liter per mmHg) NOM_DIM_X_L_PER_MM_HG
		map.put((short) 6290, "ml/mmHg"); // (milli-liter per milli-meter Hg) NOM_DIM_MILLI_L_PER_MM_HG
		map.put((short) 6098, "mAh"); // ( milli-ampere per hour used e.g. for the battery indications )
										// NOM_DIM_MILLI_AMP_HR
		map.put((short) 6418, "ml/dl"); // ( used for CaO2 CvO2 Ca-vO2 ) NOM_DIM_MILLI_L_PER_DL
		map.put((short) 6432, "dB"); // ( decibel ) NOM_DIM_DECIBEL
		map.put((short) 6464, "g/mg"); // ( gram per milli-gram ) NOM_DIM_X_G_PER_MILLI_G
		map.put((short) 6482, "mg/mg"); // ( milli-gram per milli-gram ) NOM_DIM_MILLI_G_PER_MILLI_G
		map.put((short) 6496, "bpm/l"); // ( beats per minute per liter ) NOM_DIM_BEAT_PER_MIN_PER_X_L
		map.put((short) 6514, "bpm/ml"); // ( beats per minute per milli-liter ) NOM_DIM_BEAT_PER_MIN_PER_MILLI_L
		map.put((short) 6528, "1/(min*l)"); // ( per minute per liter ) NOM_DIM_PER_X_L_PER_MIN
		map.put((short) 6560, "m/min"); // ( meter per minute ) NOM_DIM_X_M_PER_MIN
		map.put((short) 6577, "cm/min"); // ( speed for recordings ) NOM_DIM_CENTI_M_PER_MIN
		map.put((short) 2165, "pg/ml"); // ( pico-gram per milli-liter ) NOM_DIM_PICO_G_PER_ML
		map.put((short) 2067, "ug/l"); // ( micro-gram per liter ) NOM_DIM_MICRO_G_PER_L
		map.put((short) 2068, "ng/l"); // ( nano-gram per liter ) NOM_DIM_NANO_G_PER_L
		map.put((short) 1682, "/mm3"); // ( per cubic millimeter ) NOM_DIM_PER_CUBIC_MILLI_M
		map.put((short) 1586, "mm3"); // ( cubic milli-meter ) NOM_DIM_CUBIC_MILLI_M
		map.put((short) 5568, "u/l"); // ( intl. units per liter ) NOM_DIM_X_INTL_UNIT_PER_L
		map.put((short) 5573, "/l"); // ( 10^6 intl. units per liter ) NOM_DIM_MEGA_INTL_UNIT_PER_L
		map.put((short) 4946, "mol/kg"); // ( mole per kilo-gram ) NOM_DIM_MILLI_MOL_PER_KG
		map.put((short) 2131, "mcg/dl"); // ( micro-gram per deci-liter ) NOM_DIM_MICRO_G_PER_DL
		map.put((short) 2066, "mg/l"); // ( milli-gram per liter ) NOM_DIM_MILLI_G_PER_L
		map.put((short) 1715, "/ul"); // ( micro-liter ) NOM_DIM_PER_MICRO_L
		map.put((short) 61440, "complx"); // ( - ) NOM_DIM_COMPLEX
		map.put((short) 61441, "count"); // ( count as a dimension ) NOM_DIM_COUNT
		map.put((short) 61442, "part"); // ( part ) NOM_DIM_PART
		map.put((short) 61443, "puls"); // ( puls ) NOM_DIM_PULS
		map.put((short) 61444, "V"); // p-p ( micro-volt peak to peak ) NOM_DIM_UV_PP
		map.put((short) 61445, "V2"); // ( micor-volt square ) NOM_DIM_UV_SQ
		map.put((short) 61447, "lumen"); // ( lumen ) NOM_DIM_LUMEN
		map.put((short) 61448, "lb/in2"); // ( pound per square inch ) NOM_DIM_LB_PER_INCH_SQ
		map.put((short) 61449, "mmHg/s"); // ( milli-meter mercury per second ) NOM_DIM_MM_HG_PER_SEC
		map.put((short) 61450, "ml/s"); // ( milli-liter per second ) NOM_DIM_ML_PER_SEC
		map.put((short) 61451, "bpm/ml"); // ( beat per minute per milli-liter ) NOM_DIM_BEAT_PER_MIN_PER_ML_C
		map.put((short) 61536, "J/day"); // ( joule per day ) NOM_DIM_X_JOULE_PER_DAY
		map.put((short) 61539, "kJ/day"); // ( kilo joule per day ) NOM_DIM_KILO_JOULE_PER_DAY
		map.put((short) 61540, "MJ/day"); // ( mega joule per day ) NOM_DIM_MEGA_JOULE_PER_DAY
		map.put((short) 61568, "cal"); // ( calories ) NOM_DIM_X_CALORIE
		map.put((short) 61571, "kcal"); // ( kilo calories ) NOM_DIM_KILO_CALORIE
		map.put((short) 61572, "10**6"); // cal ( million calories ) NOM_DIM_MEGA_CALORIE
		map.put((short) 61600, "cal/day"); // ( calories per day ) NOM_DIM_X_CALORIE_PER_DAY
		map.put((short) 61603, "kcal/day"); // ( kilo-calories per day ) NOM_DIM_KILO_CALORIE_PER_DAY
		map.put((short) 61604, "Mcal/day"); // ( mega calories per day ) NOM_DIM_MEGA_CALORIE_PER_DAY
		map.put((short) 61632, "cal/ml"); // ( calories per milli-liter ) NOM_DIM_X_CALORIE_PER_ML
		map.put((short) 61635, "kcal/ml"); // ( kilo calories per ml ) NOM_DIM_KILO_CALORIE_PER_ML
		map.put((short) 61664, "J/ml"); // ( Joule per milli-liter ) NOM_DIM_X_JOULE_PER_ML
		map.put((short) 61667, "kJ/ml"); // ( kilo-joules per milli-liter ) NOM_DIM_KILO_JOULE_PER_ML
		map.put((short) 61696, "RPM"); // ( revolutions per minute ) NOM_DIM_X_REV_PER_MIN
		map.put((short) 61728, "l/(mn*l*kg)"); // ( per minute per liter per kilo ) NOM_DIM_PER_L_PER_MIN_PER_KG
		map.put((short) 61760, "l/mbar"); // ( liter per milli-bar ) NOM_DIM_X_L_PER_MILLI_BAR
		map.put((short) 61778, "ml/mbar"); // ( milli-liter per milli-bar ) NOM_DIM_MILLI_L_PER_MILLI_BAR
		map.put((short) 61792, "l/kg/hr"); // ( liter per kilo-gram per hour ) NOM_DIM_X_L_PER_KG_PER_HR
		map.put((short) 61810, "ml/kg/hr"); // ( milli-liter per kilogram per hour ) NOM_DIM_MILLI_L_PER_KG_PER_HR
		map.put((short) 61824, "bar/l/s"); // ( bar per liter per sec ) NOM_DIM_X_BAR_PER_LITER_PER_SEC
		map.put((short) 61842, "mbar/l/s"); // ( milli-bar per liter per sec ) NOM_DIM_MILLI_BAR_PER_LITER_PER_SEC
		map.put((short) 61856, "bar/l"); // ( bar per liter ) NOM_DIM_X_BAR_PER_LITER
		map.put((short) 61874, "mbar/l"); // ( bar per liter ) NOM_DIM_MILLI_BAR_PER_LITER
		map.put((short) 61888, "V/mV"); // ( volt per milli-volt ) NOM_DIM_VOLT_PER_MILLI_VOLT
		map.put((short) 61920, "cmH2O/uV"); // ( cm H2O per micro-volt ) NOM_DIM_CM_H2O_PER_MICRO_VOLT
		map.put((short) 61952, "J/l"); // ( joule per liter ) NOM_DIM_X_JOULE_PER_LITER
		map.put((short) 61984, "l/bar"); // ( liter per bar ) NOM_DIM_X_L_PER_BAR
		map.put((short) 62016, "m/mV"); // ( meter per milli-volt ) NOM_DIM_X_M_PER_MILLI_VOLT
		map.put((short) 62034, "mm/mV"); // ( milli-meter per milli-volt ) NOM_DIM_MILLI_M_PER_MILLI_VOLT
		map.put((short) 62048, "l/min/kg"); // ( liter per minute per kilo-gram ) NOM_DIM_X_L_PER_MIN_PER_KG
		map.put((short) 62066, "ml/min/kg"); // ( milli-liter per minute per kilo-gram ) NOM_DIM_MILLI_L_PER_MIN_PER_KG
		map.put((short) 62080, "Pa/l/s"); // ( pascal per liter per sec ) NOM_DIM_X_PASCAL_PER_L_PER_SEC
		map.put((short) 62082, "hPa/l/s"); // ( hPa per liter per sec ) NOM_DIM_HECTO_PASCAL_PER_L_PER_SEC
		map.put((short) 62083, "kPa/l/s"); // ( kPa per liter per sec ) NOM_DIM_KILO_PASCAL_PER_L_PER_SEC
		map.put((short) 62112, "ml/Pa"); // ( milli-liter per pascal ) NOM_DIM_MILLI_L_PER_X_PASCAL
		map.put((short) 62114, "ml/hPa"); // ( milli-liter per hecto-pascal ) NOM_DIM_MILLI_L_PER_HECTO_PASCAL
		map.put((short) 62115, "ml/kPa"); // ( milli-liter per kilo-pascal ) NOM_DIM_MILLI_L_PER_KILO_PASCAL
		map.put((short) 62144, "mmHg/l/s"); // ( mm ) NOM_DIM_MM_HG_PER_X_L_PER_SEC
	}
	
	public static RpUnit getUnit( Short unitCode ) {
		String s = map.get( unitCode );
		if( s == null ) {
			s = "UNK";
		}
		
		return new RpLinearUnit(1.0, 0, s );
	}
}