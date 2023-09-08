package idea.driver.intellivue;

public class Numerics {
	// HR Heart Rate
	public final static int NLS_NOM_ECG_CARD_BEAT_RATE = 0x00024182;
	public final static short NOM_ECG_CARD_BEAT_RATE = (short)0x4182;
	public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// btbHR Cardiac Beat-to-Beat Rate
	public final static int NLS_NOM_ECG_CARD_BEAT_RATE_BTB = 0x0002418A;
	public final static short NOM_ECG_CARD_BEAT_RATE_BTB = (short)0x418A;
	// PVC Premature Ventricular Contractions
	public final static int NLS_NOM_ECG_V_P_C_CNT = 0x00024261;
	public final static short NOM_ECG_V_P_C_CNT = (short)0x4261;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// ST ST generic label
	public final static int NLS_NOM_ECG_AMPL_ST = 0x00020300;
	public final static short NOM_ECG_AMPL_ST_I = (short)0x0301;
	public final static short NOM_ECG_AMPL_ST_II = (short)0x0302;
	public final static short NOM_ECG_AMPL_ST_III = (short)0x033D;
	public final static short NOM_ECG_AMPL_ST_AVR = (short)0x033E;
	public final static short NOM_ECG_AMPL_ST_AVL = (short)0x033F;
	public final static short NOM_ECG_AMPL_ST_AVF = (short)0x0340;
	public final static short NOM_ECG_AMPL_ST_V = (short)0x0343;
	public final static short NOM_ECG_AMPL_ST_MCL = (short)0x034B;
	public final static short NOM_ECG_AMPL_ST_V1 = (short)0x0303;
	public final static short NOM_ECG_AMPL_ST_V2 = (short)0x0304;
	public final static short NOM_ECG_AMPL_ST_V3 = (short)0x0305;
	public final static short NOM_ECG_AMPL_ST_V4 = (short)0x0306;
	public final static short NOM_ECG_AMPL_ST_V5 = (short)0x0307;
	public final static short NOM_ECG_AMPL_ST_V6 = (short)0x0308;
	public final static short NOM_ECG_AMPL_ST_AS = (short)0x0365;
	public final static short NOM_ECG_AMPL_ST_ES = (short)0x0364;
	public final static short NOM_ECG_AMPL_ST_AI = (short)0x0366;
	public final static short NOM_DIM_MILLI_M = (short)0x0512;
	// STindx ST Index
	public final static int NLS_NOM_ECG_AMPL_ST_INDEX = 0x0002F03D;
	public final static short NOM_ECG_AMPL_ST_INDEX = (short)0xF03D;
	//public final static short NOM_DIM_MILLI_M = (short)0x0512;
	// QTc
	public final static int NLS_NOM_ECG_TIME_PD_QTc = 0x00023F24;
	public final static short NOM_ECG_TIME_PD_QTc = (short)0x3F24;
	public final static short NOM_DIM_MILLI_SEC = (short)0x0892;
	// DeltaQTc
	public final static int NLS_NOM_ECG_TIME_PD_QTc_DELTA = 0x0002F156;
	public final static short NOM_ECG_TIME_PD_QTc_DELTA = (short)0xF156;
	//public final static short NOM_DIM_MILLI_SEC = (short)0x0892;
	// QT
	public final static int NLS_NOM_ECG_TIME_PD_QT_GL = 0x00023F20;
	public final static short NOM_ECG_TIME_PD_QT_GL = (short)0x3F20;
	//public final static short NOM_DIM_MILLI_SEC = (short)0x0892;
	// QT-HR QT HEARTRATE
	public final static int NLS_NOM_ECG_TIME_PD_QT_HEART_RATE = 0x0002F154;
	public final static short NOM_ECG_TIME_PD_QT_HEART_RATE = (short)0xF154;
	// NO VALUE: NOM_DIM_BEATS_PER_MIN
	// QT Bsl
	public final static int NLS_NOM_ECG_TIME_PD_QT_BASELINE = 0x0002F155;
	public final static short NOM_ECG_TIME_PD_QT_BASELINE = (short)0xF155;
	//public final static short NOM_DIM_MILLI_SEC = (short)0x0892;
	// QTHRBl QT BASELINE HEARTRATE
	public final static int NLS_NOM_ECG_TIME_PD_QT_BASELINE_HEART_RATE = 0x0002F157;
	public final static short NOM_ECG_TIME_PD_QT_BASELINE_HEART_RATE = (short)0xF157;
	//public final static short NOM_DIM_MILLI_SEC = (short)0x0892;
	// Pulse Pulse Rate
	public final static int NLS_NOM_PULS_RATE = 0x0002480A;
	public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// SpO2 Arterial Oxigen Saturation
	public final static int NLS_NOM_PULS_OXIM_SAT_O2 = 0x00024BB8;
	public final static short NOM_PULS_OXIM_SAT_O2 = (short)0x4BB8;
	public final static short NOM_DIM_PERCENT = (short)0x0220;
	// Pulse Pulse Rate from Plethysmogram
	public final static int NLS_NOM_PULS_OXIM_PULS_RATE = 0x00024822;
	public final static short NOM_PLETH_PULS_RATE = (short)0x4822;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// SpO2pr Oxigen Saturation
	public final static int NLS_NOM_PULS_OXIM_SAT_O2_PRE_DUCTAL = 0x0002F1C0;
	public final static short NOM_PULS_OXIM_SAT_O2_PRE_DUCTAL = (short)0xF1C0;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// Pulse Pulse Rate from Plethysmogram (pre ductal)
	public final static int NLS_SPO2_NAMES_PULS_OXIM_PULS_RATE_PRE_DUCTAL = 0x8015543D;
	//public final static short NOM_PLETH_PULS_RATE = (short)0x4822;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// SpO2po Oxigen Saturation
	public final static int NLS_NOM_PULS_OXIM_SAT_O2_POST_DUCTAL = 0x0002F1D4;
	public final static short NOM_PULS_OXIM_SAT_O2_POST_DUCTAL = (short)0xF1D4;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// Pulse Pulse Rate from Plethysmogram (post ductal)
	public final static int NLS_SPO2_NAMES_PULS_OXIM_PULS_RATE_POST_DUCTAL = 0x80155440;
	//public final static short NOM_PLETH_PULS_RATE = (short)0x4822;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// %SpO2T SpO2 parameter label as sourced by the Telemetry system
	public final static int NLS_NOM_PULS_OXIM_SAT_O2_TELE = 0x0002F09C;
	public final static short NOM_PULS_OXIM_SAT_O2_TELE = (short)0xF09C;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// PulseT Pulse parameter label as sourced by the Telemetry system
	public final static int NLS_NOM_PULS_OXIM_PULS_RATE_TELE = 0x0002F09D;
	public final static short NOM_PULS_OXIM_PULS_RATE_TELE = (short)0xF09D;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// SpO2 r Arterial Oxigen Saturation (right)
	public final static int NLS_NOM_PULS_OXIM_SAT_O2_ART_RIGHT = 0x00024BCC;
	public final static short NOM_PULS_OXIM_SAT_O2_ART_RIGHT = (short)0x4BCC;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// Pulse Pulse Rate from Plethysmogram (right)
	public final static int NLS_SPO2_NAMES_PULS_OXIM_PULS_RATE_RIGHT = 0x80155402;
	//public final static short NOM_PLETH_PULS_RATE = (short)0x4822;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// SpO2 l Arterial Oxigen Saturation (left)
	public final static int NLS_NOM_PULS_OXIM_SAT_O2_ART_LEFT = 0x00024BC8;
	public final static short NOM_PULS_OXIM_SAT_O2_ART_LEFT = (short)0x4BC8;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// Pulse Pulse Rate from Plethysmogram (left)
	public final static int NLS_SPO2_NAMES_PULS_OXIM_PULS_RATE_LEFT = 0x80155401;
	//public final static short NOM_PLETH_PULS_RATE = (short)0x4822;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// DeltaSpO2 Difference between two SpO2 Values (like Left - Right)
	public final static int NLS_NOM_PULS_OXIM_SAT_O2_DIFF = 0x00024BC4;
	public final static short NOM_PULS_OXIM_SAT_O2_DIFF = (short)0x4BC4;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// Perf Perfusion Indicator
	public final static int NLS_NOM_PULS_OXIM_PERF_REL = 0x00024BB0;
	public final static short NOM_PULS_OXIM_PERF_REL = (short)0x4BB0;
	public final static short NOM_DIM_DIMLESS = (short)0x0200;
	// PerfPr Relative Perfusion Left
	public final static int NLS_NOM_PULS_OXIM_PERF_REL_PRE_DUCTAL = 0x0002F22C;
	public final static short NOM_PULS_OXIM_PERF_REL_PRE_DUCTAL = (short)0xF22C;
	//public final static short NOM_DIM_DIMLESS = (short)0x0200;
	// PerfPo Relative Perfusion Left
	public final static int NLS_NOM_PULS_OXIM_PERF_REL_POST_DUCTAL = 0x0002F1DC;
	public final static short NOM_PULS_OXIM_PERF_REL_POST_DUCTAL = (short)0xF1DC;
	//public final static short NOM_DIM_DIMLESS = (short)0x0200;
	// Perf T Perf from Telemetry
	public final static int NLS_NOM_PULS_OXIM_PERF_REL_TELE = 0x0002F12C;
	public final static short NOM_PULS_OXIM_PERF_REL_TELE = (short)0xF12C;
	//public final static short NOM_DIM_DIMLESS = (short)0x0200;
	// Perf r Relative Perfusion Right label
	public final static int NLS_NOM_PULS_OXIM_PERF_REL_RIGHT = 0x0002F08B;
	public final static short NOM_PULS_OXIM_PERF_REL_RIGHT = (short)0xF08B;
	//public final static short NOM_DIM_DIMLESS = (short)0x0200;
	// Perf l Relative Perfusion Left
	public final static int NLS_NOM_PULS_OXIM_PERF_REL_LEFT = 0x0002F08A;
	public final static short NOM_PULS_OXIM_PERF_REL_LEFT = (short)0xF08A;
	//public final static short NOM_DIM_DIMLESS = (short)0x0200;
	// NBP non-invasive blood pressure
	public final static int NLS_NOM_PRESS_BLD_NONINV = 0x00024A04;
	public final static short NOM_PRESS_BLD_NONINV = (short)0x4A04;
	public final static short NOM_PRESS_BLD_NONINV_SYS = (short)0x4A05;
	public final static short NOM_PRESS_BLD_NONINV_DIA = (short)0x4A06;
	public final static short NOM_PRESS_BLD_NONINV_MEAN = (short)0x4A07;
	public final static short NOM_DIM_MMHG = (short)0x0F20;
	public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse from NBP
	public final static int NLS_NOM_PRESS_BLD_NONINV_PULS_RATE = 0x0002F0E5;
	public final static short NOM_PRESS_BLD_NONINV_PULS_RATE = (short)0xF0E5;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// ABP Arterial Blood Pressure (ABP)
	public final static int NLS_NOM_PRESS_BLD_ART_ABP = 0x00024A14;
	public final static short NOM_PRESS_BLD_ART_ABP = (short)0x4A14;
	public final static short NOM_PRESS_BLD_ART_ABP_SYS = (short)0x4A15;
	public final static short NOM_PRESS_BLD_ART_ABP_DIA = (short)0x4A16;
	public final static short NOM_PRESS_BLD_ART_ABP_MEAN = (short)0x4A17;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from ABP
	public final static int NLS_PRESS_NAMES_PULSE_FROM_ABP = 0x80035402;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// ART Arterial Blood Pressure (ART)
	public final static int NLS_NOM_PRESS_BLD_ART = 0x00024A10;
	public final static short NOM_PRESS_BLD_ART = (short)0x4A10;
	public final static short NOM_PRESS_BLD_ART_SYS = (short)0x4A11;
	public final static short NOM_PRESS_BLD_ART_DIA = (short)0x4A12;
	public final static short NOM_PRESS_BLD_ART_MEAN = (short)0x4A13;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from ART
	public final static int NLS_PRESS_NAMES_PULSE_FROM_ART = 0x80035403;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// Ao Arterial Blood Pressure in the Aorta (Ao)
	public final static int NLS_NOM_PRESS_BLD_AORT = 0x00024A0C;
	public final static short NOM_PRESS_BLD_AORT = (short)0x4A0C;
	public final static short NOM_PRESS_BLD_AORT_SYS = (short)0x4A0D;
	public final static short NOM_PRESS_BLD_AORT_DIA = (short)0x4A0E;
	public final static short NOM_PRESS_BLD_AORT_MEAN = (short)0x4A0F;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from Ao
	public final static int NLS_PRESS_NAMES_PULSE_FROM_AO = 0x80035404;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// PAP Pulmonary Arterial Pressure (PAP)
	public final static int NLS_NOM_PRESS_BLD_ART_PULM = 0x00024A1C;
	public final static short NOM_PRESS_BLD_ART_PULM = (short)0x4A1C;
	public final static short NOM_PRESS_BLD_ART_PULM_SYS = (short)0x4A1D;
	public final static short NOM_PRESS_BLD_ART_PULM_DIA = (short)0x4A1E;
	public final static short NOM_PRESS_BLD_ART_PULM_MEAN = (short)0x4A1F;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from PAP
	public final static int NLS_PRESS_NAMES_PULSE_FROM_PAP = 0x80035405;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// CVP Central Venous Pressure (CVP)
	public final static int NLS_NOM_PRESS_BLD_VEN_CENT = 0x00024A44;
	public final static short NOM_PRESS_BLD_VEN_CENT = (short)0x4A44;
	public final static short NOM_PRESS_BLD_VEN_CENT_SYS = (short)0x4A45;
	public final static short NOM_PRESS_BLD_VEN_CENT_DIA = (short)0x4A46;
	public final static short NOM_PRESS_BLD_VEN_CENT_MEAN = (short)0x4A47;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from CVP
	public final static int NLS_PRESS_NAMES_PULSE_FROM_CVP = 0x80035406;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// RAP Right Atrial Pressure (RAP)
	public final static int NLS_NOM_PRESS_BLD_ATR_RIGHT = 0x00024A34;
	public final static short NOM_PRESS_BLD_ATR_RIGHT = (short)0x4A34;
	public final static short NOM_PRESS_BLD_ATR_RIGHT_SYS = (short)0x4A35;
	public final static short NOM_PRESS_BLD_ATR_RIGHT_DIA = (short)0x4A36;
	public final static short NOM_PRESS_BLD_ATR_RIGHT_MEAN = (short)0x4A37;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from RAP
	public final static int NLS_PRESS_NAMES_PULSE_FROM_RAP = 0x80035407;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// LAP Left Atrial Pressure (LAP)
	public final static int NLS_NOM_PRESS_BLD_ATR_LEFT = 0x00024A30;
	public final static short NOM_PRESS_BLD_ATR_LEFT = (short)0x4A30;
	public final static short NOM_PRESS_BLD_ATR_LEFT_SYS = (short)0x4A31;
	public final static short NOM_PRESS_BLD_ATR_LEFT_DIA = (short)0x4A32;
	public final static short NOM_PRESS_BLD_ATR_LEFT_MEAN = (short)0x4A33;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from LAP
	public final static int NLS_PRESS_NAMES_PULSE_FROM_LAP = 0x80035408;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// ICP Intra-cranial Pressure (ICP)
	public final static int NLS_NOM_PRESS_INTRA_CRAN = 0x00025808;
	public final static short NOM_PRESS_INTRA_CRAN = (short)0x5808;
	public final static short NOM_PRESS_INTRA_CRAN_SYS = (short)0x5809;
	public final static short NOM_PRESS_INTRA_CRAN_DIA = (short)0x580A;
	public final static short NOM_PRESS_INTRA_CRAN_MEAN = (short)0x580B;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from ICP
	public final static int NLS_PRESS_NAMES_PULSE_FROM_ICP = 0x80035409;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// UAP Umbilical Arterial Pressure (UAP)
	public final static int NLS_NOM_PRESS_BLD_ART_UMB = 0x00024A28;
	public final static short NOM_PRESS_BLD_ART_UMB = (short)0x4A28;
	public final static short NOM_PRESS_BLD_ART_UMB_SYS = (short)0x4A29;
	public final static short NOM_PRESS_BLD_ART_UMB_DIA = (short)0x4A2A;
	public final static short NOM_PRESS_BLD_ART_UMB_MEAN = (short)0x4A2B;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from UAP
	public final static int NLS_PRESS_NAMES_PULSE_FROM_UAP = 0x8003540A;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// UVP Umbilical Venous Pressure (UVP)
	public final static int NLS_NOM_PRESS_BLD_VEN_UMB = 0x00024A48;
	public final static short NOM_PRESS_BLD_VEN_UMB = (short)0x4A48;
	public final static short NOM_PRESS_BLD_VEN_UMB_SYS = (short)0x4A49;
	public final static short NOM_PRESS_BLD_VEN_UMB_DIA = (short)0x4A4A;
	public final static short NOM_PRESS_BLD_VEN_UMB_MEAN = (short)0x4A4B;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from UVP
	public final static int NLS_PRESS_NAMES_PULSE_FROM_UVP = 0x8003540B;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// FAP Femoral Arterial Pressure (FAP)
	public final static int NLS_NOM_PRESS_BLD_ART_FEMORAL = 0x0002F0BC;
	public final static short NOM_PRESS_BLD_ART_FEMORAL_SYS = (short)0xF0BD;
	public final static short NOM_PRESS_BLD_ART_FEMORAL_DIA = (short)0xF0BE;
	public final static short NOM_PRESS_BLD_ART_FEMORAL_MEAN = (short)0xF0BF;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from FAP
	public final static int NLS_PRESS_NAMES_PULSE_FROM_FAP = 0x80035434;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// BAP Brachial Arterial Blood Pressure (BAP)
	public final static int NLS_NOM_PRESS_BLD_ART_BRACHIAL = 0x0002F0C0;
	public final static short NOM_PRESS_BLD_ART_BRACHIAL_SYS = (short)0xF0C1;
	public final static short NOM_PRESS_BLD_ART_BRACHIAL_DIA = (short)0xF0C2;
	public final static short NOM_PRESS_BLD_ART_BRACHIAL_MEAN = (short)0xF0C3;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from BAP
	public final static int NLS_PRESS_NAMES_PULSE_FROM_BAP = 0x80035437;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// IC1 Intracranial Pressure 1 (IC1)
	public final static int NLS_NOM_PRESS_INTRA_CRAN_1 = 0x0002F0B4;
	public final static short NOM_PRESS_INTRA_CRAN_1_DIA = (short)0xF0B6;
	public final static short NOM_PRESS_INTRA_CRAN_1_SYS = (short)0xF0B5;
	public final static short NOM_PRESS_INTRA_CRAN_1_MEAN = (short)0xF0B7;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from IC1
	public final static int NLS_PRESS_NAMES_PULSE_FROM_IC1 = 0x8003542E;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// IC2 Intracranial Pressure 2 (IC2)
	public final static int NLS_NOM_PRESS_INTRA_CRAN_2 = 0x0002F0B8;
	public final static short NOM_PRESS_INTRA_CRAN_2_SYS = (short)0xF0B9;
	public final static short NOM_PRESS_INTRA_CRAN_2_DIA = (short)0xF0BA;
	public final static short NOM_PRESS_INTRA_CRAN_2_MEAN = (short)0xF0BB;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from IC2
	public final static int NLS_PRESS_NAMES_PULSE_FROM_IC2 = 0x80035431;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// P unspecific pressure
	public final static int NLS_NOM_PRESS_BLD = 0x00024A00;
	public final static short NOM_PRESS_BLD = (short)0x4A00;
	public final static short NOM_PRESS_BLD_SYS = (short)0x4A01;
	public final static short NOM_PRESS_BLD_DIA = (short)0x4A02;
	public final static short NOM_PRESS_BLD_MEAN = (short)0x4A03;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from unspecific Pressure
	public final static int NLS_PRESS_NAMES_PULSE_FROM_P = 0x80035401;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// P1 Generic Pressure 1 (P1)
	public final static int NLS_NOM_PRESS_GEN_1 = 0x0002F0A4;
	public final static short NOM_PRESS_GEN_1 = (short)0xF0A4;
	public final static short NOM_PRESS_GEN_1_SYS = (short)0xF0A5;
	public final static short NOM_PRESS_GEN_1_DIA = (short)0xF0A6;
	public final static short NOM_PRESS_GEN_1_MEAN = (short)0xF0A7;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from P1
	public final static int NLS_PRESS_NAMES_PULSE_FROM_P1 = 0x80035422;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// P2 Generic Pressure 2 (P2)
	public final static int NLS_NOM_PRESS_GEN_2 = 0x0002F0A8;
	public final static short NOM_PRESS_GEN_2 = (short)0xF0A8;
	public final static short NOM_PRESS_GEN_2_SYS = (short)0xF0A9;
	public final static short NOM_PRESS_GEN_2_DIA = (short)0xF0AA;
	public final static short NOM_PRESS_GEN_2_MEAN = (short)0xF0AB;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from P2
	public final static int NLS_PRESS_NAMES_PULSE_FROM_P2 = 0x80035425;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// P3 Generic Pressure 3 (P3)
	public final static int NLS_NOM_PRESS_GEN_3 = 0x0002F0AC;
	public final static short NOM_PRESS_GEN_3 = (short)0xF0AC;
	public final static short NOM_PRESS_GEN_3_SYS = (short)0xF0AD;
	//public final static short NOM_PRESS_GEN_3 = (short)0xF0AC;
	public final static short NOM_PRESS_GEN_3_MEAN = (short)0xF0AF;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from P3
	public final static int NLS_PRESS_NAMES_PULSE_FROM_P3 = 0x80035428;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// P4 Generic Pressure 4 (P4)
	public final static int NLS_NOM_PRESS_GEN_4 = 0x0002F0B0;
	public final static short NOM_PRESS_GEN_4 = (short)0xF0B0;
	public final static short NOM_PRESS_GEN_4_SYS = (short)0xF0B1;
	public final static short NOM_PRESS_GEN_4_DIA = (short)0xF0B2;
	public final static short NOM_PRESS_GEN_4_MEAN = (short)0xF0B3;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// Pulse Pulse derived from P4
	public final static int NLS_PRESS_NAMES_PULSE_FROM_P4 = 0x8003542B;
	//public final static short NOM_PULS_RATE = (short)0x480A;
	//public final static short NOM_DIM_BEAT_PER_MIN = (short)0x0AA0;
	// IUP Intra-Uterine Pressure
	public final static int NLS_NOM_PRESS_INTRA_UTERAL = 0x0002F0D8;
	//public final static short NOM_PRESS_BLD = (short)0x4A00;
	// PAWP Pulmonary Artery Wedge Pressure
	public final static int NLS_NOM_PRESS_BLD_ART_PULM_WEDGE = 0x00024A24;
	public final static short NOM_PRESS_BLD_ART_PULM_WEDGE = (short)0x4A24;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// CPP Cerebral Perfusion Pressure
	public final static int NLS_NOM_PRESS_CEREB_PERF = 0x00025804;
	public final static short NOM_PRESS_CEREB_PERF = (short)0x5804;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// PPV Pulse Pressure Variation
	public final static int NLS_NOM_PULS_PRESS_VAR = 0x0002F0E3;
	public final static short NOM_PULS_PRESS_VAR = (short)0xF0E3;
	// CCO Continuous Cardiac Output
	public final static int NLS_NOM_OUTPUT_CARD_CTS = 0x00024BDC;
	public final static short NOM_OUTPUT_CARD_CTS = (short)0x4BDC;
	public final static short NOM_DIM_X_L_PER_MIN = (short)0x0C00;
	// CCI Continuous Cardiac Output Index
	public final static int NLS_NOM_OUTPUT_CARD_INDEX_CTS = 0x0002F047;
	public final static short NOM_OUTPUT_CARD_INDEX_CTS = (short)0xF047;
	public final static short NOM_DIM_X_L_PER_MIN_PER_M_SQ = (short)0x0B20;
	// SV Stroke Volume
	public final static int NLS_NOM_VOL_BLD_STROKE = 0x00024B84;
	public final static short NOM_VOL_BLD_STROKE = (short)0x4B84;
	public final static short NOM_DIM_MILLI_L = (short)0x0652;
	// SI Stroke Index
	public final static int NLS_NOM_VOL_BLD_STROKE_INDEX = 0x0002F048;
	public final static short NOM_VOL_BLD_STROKE_INDEX = (short)0xF048;
	public final static short NOM_DIM_MILLI_L_PER_M_SQ = (short)0x0592;
	// SVV Stroke Volume Variation
	public final static int NLS_NOM_VOL_BLD_STROKE_VAR = 0x0002F049;
	public final static short NOM_VOL_BLD_STROKE_VAR = (short)0xF049;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// dPmax Index of Left Ventricular Contractility
	public final static int NLS_NOM_GRAD_PRESS_BLD_AORT_POS_MAX = 0x00024C25;
	public final static short NOM_GRAD_PRESS_BLD_AORT_POS_MAX = (short)0x4C25;
	// C.O. Cardiac Output
	public final static int NLS_NOM_OUTPUT_CARD = 0x00024B04;
	public final static short NOM_OUTPUT_CARD = (short)0x4B04;
	//public final static short NOM_DIM_X_L_PER_MIN = (short)0x0C00;
	// C.I. Cardiac Index
	public final static int NLS_NOM_OUTPUT_CARD_INDEX = 0x0002490C;
	public final static short NOM_OUTPUT_CARD_INDEX = (short)0x490C;
	//public final static short NOM_DIM_X_L_PER_MIN_PER_M_SQ = (short)0x0B20;
	// ITBV Intrathoracic Blood Volume
	public final static int NLS_NOM_VOL_BLD_INTRA_THOR = 0x0002F040;
	public final static short NOM_VOL_BLD_INTRA_THOR = (short)0xF040;
	//public final static short NOM_DIM_MILLI_L = (short)0x0652;
	// ITBVI Intrathoracic Blood Volume Index
	public final static int NLS_NOM_VOL_BLD_INTRA_THOR_INDEX = 0x0002F041;
	public final static short NOM_VOL_BLD_INTRA_THOR_INDEX = (short)0xF041;
	//public final static short NOM_DIM_MILLI_L_PER_M_SQ = (short)0x0592;
	// EVLW Extravascular Lung Water
	public final static int NLS_NOM_VOL_LUNG_WATER_EXTRA_VASC = 0x0002F042;
	public final static short NOM_VOL_LUNG_WATER_EXTRA_VASC = (short)0xF042;
	//public final static short NOM_DIM_MILLI_L = (short)0x0652;
	// EVLWI Extravascular Lung Water Index
	public final static int NLS_NOM_VOL_LUNG_WATER_EXTRA_VASC_INDEX = 0x0002F043;
	public final static short NOM_VOL_LUNG_WATER_EXTRA_VASC_INDEX = (short)0xF043;
	public final static short NOM_DIM_MILLI_L_PER_KG = (short)0x0C72;
	// GEDV Global End Diastolic Volume
	public final static int NLS_NOM_VOL_GLOBAL_END_DIA = 0x0002F044;
	public final static short NOM_VOL_GLOBAL_END_DIA = (short)0xF044;
	//public final static short NOM_DIM_MILLI_L = (short)0x0652;
	// GEDVI Global End Diastolic Volume Index
	public final static int NLS_NOM_VOL_GLOBAL_END_DIA_INDEX = 0x0002F045;
	public final static short NOM_VOL_GLOBAL_END_DIA_INDEX = (short)0xF045;
	//public final static short NOM_DIM_MILLI_L_PER_M_SQ = (short)0x0592;
	// CFI Cardiac Function Index
	public final static int NLS_NOM_CARD_FUNC_INDEX = 0x0002F046;
	public final static short NOM_CARD_FUNC_INDEX = (short)0xF046;
	//public final static short NOM_DIM_DIMLESS = (short)0x0200;
	// PVPI Pulmonary Vascular Permeability Index
	public final static int NLS_NOM_PERM_VASC_PULM_INDEX = 0x0002F106;
	public final static short NOM_PERM_VASC_PULM_INDEX = (short)0xF106;
	// GEF Global Ejection Fraction
	public final static int NLS_NOM_FRACT_EJECT = 0x0002F105;
	public final static short NOM_FRACT_EJECT = (short)0xF105;
	// SNR Signal to Noise ratio
	public final static int NLS_NOM_SNR = 0x0002F101;
	public final static short NOM_SNR = (short)0xF101;
	// RLShnt Right-to-Left Heart Shunt
	public final static int NLS_NOM_SHUNT_RIGHT_LEFT = 0x0002F14A;
	public final static short NOM_SHUNT_RIGHT_LEFT = (short)0xF14A;
	// NO VALUE: NOM_DIM_MILLI_SECOND
	// SaO2 Oxygen Saturation
	public final static int NLS_NOM_SAT_O2_ART = 0x00024B34;
	public final static short NOM_SAT_O2_ART = (short)0x4B34;
	// SvO2 Mixed Venous Oxygen Saturation
	public final static int NLS_NOM_SAT_O2_VEN = 0x00024B3C;
	public final static short NOM_SAT_O2_VEN = (short)0x4B3C;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// ScvO2 Central Venous Oxygen Saturation
	public final static int NLS_NOM_SAT_O2_VEN_CENT = 0x0002F100;
	public final static short NOM_SAT_O2_VEN_CENT = (short)0xF100;
	// SO2 O2 Saturation
	public final static int NLS_NOM_SAT_O2 = 0x00024B2C;
	public final static short NOM_SAT_O2 = (short)0x4B2C;
	// NO VALUE: NOM_DIM_PERCENT
	// SO2 l Oxygen Saturation Left Side
	public final static int NLS_NOM_SAT_O2_LEFT = 0x0002F89D;
	//public final static short NOM_SAT_O2_ART = (short)0x4B34;
	// SO2 r Oxygen Saturation Right Side
	public final static int NLS_NOM_SAT_O2_RIGHT = 0x0002F89E;
	//public final static short NOM_SAT_O2_ART = (short)0x4B34;
	// SO2 1 O2 Saturation 1 (generic)
	public final static int NLS_NOM_SAT_O2_GEN_1 = 0x0002F962;
	public final static short NOM_SAT_O2_GEN_1 = (short)0xF962;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// SO2 2 O2 Saturation 2 (generic)
	public final static int NLS_NOM_SAT_O2_GEN_2 = 0x0002F963;
	public final static short NOM_SAT_O2_GEN_2 = (short)0xF963;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// SO2 3 O2 Saturation 3 (generic)
	public final static int NLS_NOM_SAT_O2_GEN_3 = 0x0002F964;
	public final static short NOM_SAT_O2_GEN_3 = (short)0xF964;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// SO2 4 O2 Saturation 4 (generic)
	public final static int NLS_NOM_SAT_O2_GEN_4 = 0x0002F965;
	public final static short NOM_SAT_O2_GEN_4 = (short)0xF965;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// LI Light Intenisty. SvO2
	public final static int NLS_NOM_INTENS_LIGHT = 0x0002F072;
	public final static short NOM_INTENS_LIGHT = (short)0xF072;
	// DO2 Oxygen Availability DO2
	public final static int NLS_NOM_SAT_O2_DELIVER = 0x0002F06D;
	public final static short NOM_SAT_O2_DELIVER = (short)0xF06D;
	// DO2I Oxygen Availability Index
	public final static int NLS_NOM_SAT_O2_DELIVER_INDEX = 0x0002F06E;
	public final static short NOM_SAT_O2_DELIVER_INDEX = (short)0xF06E;
	// O2ER Oxygen Extraction Ratio
	public final static int NLS_NOM_RATIO_SAT_O2_CONSUMP_DELIVER = 0x0002F06F;
	public final static short NOM_RATIO_SAT_O2_CONSUMP_DELIVER = (short)0xF06F;
	// Qs/Qt Percent Alveolarvenous Shunt Qs/Qt
	public final static int NLS_NOM_RATIO_ART_VEN_SHUNT = 0x0002F070;
	public final static short NOM_RATIO_ART_VEN_SHUNT = (short)0xF070;
	// AaDO2 Alveolar- Arterial Oxygen Difference
	public final static int NLS_NOM_SAT_DIFF_O2_ART_ALV = 0x00024B40;
	public final static short NOM_SAT_DIFF_O2_ART_ALV = (short)0x4B40;
	// Sp-vO2 Difference between Spo2 and SvO2
	public final static int NLS_NOM_SAT_DIFF_O2_ART_VEN = 0x0002F06C;
	public final static short NOM_SAT_DIFF_O2_ART_VEN = (short)0xF06C;
	// tcGas Generic Term for the Transcutaneous Gases
	public final static int NLS_NOM_GAS_TCUT = 0x0002F051;
	public final static short NOM_GAS_TCUT = (short)0xF051;
	// tcpO2 Transcutaneous Oxygen Partial Pressure
	public final static int NLS_NOM_O2_TCUT = 0x000250D0;
	public final static short NOM_O2_TCUT = (short)0x50D0;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// tcpCO2 Transcutaneous Carbon Dioxide Partial Pressure
	public final static int NLS_NOM_CO2_TCUT = 0x000250CC;
	public final static short NOM_CO2_TCUT = (short)0x50CC;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// SitTim NOM_DIM_MIN
	public final static int NLS_NOM_TIME_TCUT_SENSOR = 0x0002F03E;
	public final static short NOM_TIME_TCUT_SENSOR = (short)0xF03E;
	// SensrT Sensor Temperature
	public final static int NLS_NOM_TEMP_TCUT_SENSOR = 0x0002F03F;
	public final static short NOM_TEMP_TCUT_SENSOR = (short)0xF03F;
	public final static short NOM_DIM_DEGC = (short)0x17A0;
	public final static short NOM_DIM_FAHR = (short)0x1140;
	// HeatPw NOM_DIM_MILLI_WATT
	public final static int NLS_NOM_HEATING_PWR_TCUT_SENSOR = 0x0002F076;
	public final static short NOM_HEATING_PWR_TCUT_SENSOR = (short)0xF076;
	// CO2 CO2 concentration
	public final static int NLS_NOM_AWAY_CO2 = 0x000250AC;
	public final static short NOM_AWAY_CO2 = (short)0x50AC;
	public final static short NOM_AWAY_CO2_ET = (short)0x50B0;
	public final static short NOM_AWAY_CO2_INSP_MIN = (short)0x50BA;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// RRspir Respiration Rate from Spirometry
	public final static int NLS_NOM_AWAY_RESP_RATE_SPIRO = 0x0002F0E2;
	public final static short NOM_AWAY_RESP_RATE_SPIRO = (short)0xF0E2;
	public final static short NOM_DIM_RESP_PER_MIN = (short)0x0AE0;
	// awRR Airway Respiration Rate
	public final static int NLS_NOM_AWAY_RESP_RATE = 0x00025012;
	public final static short NOM_AWAY_RESP_RATE = (short)0x5012;
	//public final static short NOM_DIM_RESP_PER_MIN = (short)0x0AE0;
	// O2 Generic oxigen measurement label
	public final static int NLS_NOM_CONC_AWAY_O2 = 0x00025164;
	public final static short NOM_CONC_AWAY_O2 = (short)0x5164;
	public final static short NOM_CONC_AWAY_O2_ET = (short)0x5378;
	public final static short NOM_CONC_AWAY_O2_INSP = (short)0x5284;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// FIO2 Fractional Inspired Oxygen FIO2
	public final static int NLS_NOM_VENT_CONC_AWAY_O2_INSP = 0x00027498;
	public final static short NOM_VENT_CONC_AWAY_O2_INSP = (short)0x7498;
	// RR Respiration Rate
	public final static int NLS_NOM_RESP_RATE = 0x0002500A;
	public final static short NOM_RESP_RATE = (short)0x500A;
	//public final static short NOM_DIM_RESP_PER_MIN = (short)0x0AE0;
	// 130
	public final static int NLS_NOM_IMPED_TTHOR = 0x000250E4;
	public final static short NOM_IMPED_TTHOR = (short)0x50E4;
	// VCO2 CO2 Production
	public final static int NLS_NOM_FLOW_CO2_PROD_RESP = 0x000250E0;
	public final static short NOM_FLOW_CO2_PROD_RESP = (short)0x50E0;
	// VCO2ti CO2 Tidal Production
	public final static int NLS_NOM_FLOW_CO2_PROD_RESP_TIDAL = 0x0002F882;
	public final static short NOM_FLOW_CO2_PROD_RESP_TIDAL = (short)0xF882;
	// Pplat Plateau Pressure
	public final static int NLS_NOM_PRESS_RESP_PLAT = 0x000250E8;
	public final static short NOM_PRESS_RESP_PLAT = (short)0x50E8;
	// AWP Airway Pressure Wave
	public final static int NLS_NOM_PRESS_AWAY = 0x000250F0;
	public final static short NOM_PRESS_AWAY = (short)0x50F0;
	// AWPmin Airway Pressure Minimum
	public final static int NLS_NOM_PRESS_AWAY_MIN = 0x000250F2;
	public final static short NOM_PRESS_AWAY_MIN = (short)0x50F2;
	// CPAP Continuous Positive Airway Pressure
	public final static int NLS_NOM_PRESS_AWAY_CTS_POS = 0x000250F4;
	public final static short NOM_PRESS_AWAY_CTS_POS = (short)0x50F4;
	// iPEEP Intrinsic PEEP Breathing Pressure
	public final static int NLS_NOM_PRESS_AWAY_END_EXP_POS_INTRINSIC = 0x00025100;
	public final static short NOM_PRESS_AWAY_END_EXP_POS_INTRINSIC = (short)0x5100;
	// AWPin Airway Pressure Wave - measured in the inspiratory path
	public final static int NLS_NOM_PRESS_AWAY_INSP = 0x00025108;
	public final static short NOM_PRESS_AWAY_INSP = (short)0x5108;
	// PIP Positive Inspiratory ressure
	public final static int NLS_NOM_PRESS_AWAY_INSP_MAX = 0x00025109;
	public final static short NOM_PRESS_AWAY_INSP_MAX = (short)0x5109;
	// MnAwP Mean Airway Pressure. Printer Context
	public final static int NLS_NOM_PRESS_AWAY_INSP_MEAN = 0x0002510B;
	public final static short NOM_PRESS_AWAY_INSP_MEAN = (short)0x510B;
	// I:E 1: Inpired:Expired Ratio
	public final static int NLS_NOM_RATIO_IE = 0x00025118;
	public final static short NOM_RATIO_IE = (short)0x5118;
	// Vd/Vt Ratio of Deadspace to Tidal Volume Vd/Vt
	public final static int NLS_NOM_RATIO_AWAY_DEADSP_TIDAL = 0x0002511C;
	public final static short NOM_RATIO_AWAY_DEADSP_TIDAL = (short)0x511C;
	// 131
	public final static int NLS_NOM_RES_AWAY = 0x00025120;
	public final static short NOM_RES_AWAY = (short)0x5120;
	// TV Tidal Volume
	public final static int NLS_NOM_VOL_AWAY_TIDAL = 0x0002513C;
	public final static short NOM_VOL_AWAY_TIDAL = (short)0x513C;
	// TVexp expired Tidal Volume
	public final static int NLS_NOM_VOL_AWAY_EXP_TIDAL = 0x0002F0E1;
	public final static short NOM_VOL_AWAY_EXP_TIDAL = (short)0xF0E1;
	// TVin inspired Tidal Volume
	public final static int NLS_NOM_VOL_AWAY_INSP_TIDAL = 0x0002F0E0;
	public final static short NOM_VOL_AWAY_INSP_TIDAL = (short)0xF0E0;
	// MINVOL Airway Minute Volum Inspiratory
	public final static int NLS_NOM_VOL_MINUTE_AWAY = 0x00025148;
	public final static short NOM_VOL_MINUTE_AWAY = (short)0x5148;
	public final static short NOM_VOL_MINUTE_AWAY_EXP = (short)0x514C;
	public final static short NOM_VOL_MINUTE_AWAY_INSP = (short)0x5150;
	//public final static short NOM_DIM_X_L_PER_MIN = (short)0x0C00;
	// PlatTi Plateau Time
	public final static int NLS_NOM_TIME_PD_RESP_PLAT = 0x0002F0FF;
	public final static short NOM_TIME_PD_RESP_PLAT = (short)0xF0FF;
	// SpMV Spontaneous Minute Volume
	public final static int NLS_NOM_VENT_VOL_MINUTE_AWAY_SPONT = 0x0002F091;
	public final static short NOM_VENT_VOL_MINUTE_AWAY_SPONT = (short)0xF091;
	// DeltaO2 relative Dead Space
	public final static int NLS_NOM_VENT_CONC_AWAY_O2_DELTA = 0x00025168;
	public final static short NOM_VENT_CONC_AWAY_O2_DELTA = (short)0x5168;
	// PECO2 Partial O2 Venous
	public final static int NLS_NOM_VENT_AWAY_CO2_EXP = 0x0002517C;
	public final static short NOM_VENT_AWAY_CO2_EXP = (short)0x517C;
	// AWFin Airway Flow Wave - measured in the inspiratory path
	public final static int NLS_NOM_VENT_FLOW_INSP = 0x0002518C;
	public final static short NOM_VENT_FLOW_INSP = (short)0x518C;
	// VQI Ventilation Perfusion Index
	public final static int NLS_NOM_VENT_FLOW_RATIO_PERF_ALV_INDEX = 0x00025190;
	public final static short NOM_VENT_FLOW_RATIO_PERF_ALV_INDEX = (short)0x5190;
	// Poccl Occlusion Pressure
	public final static int NLS_NOM_VENT_PRESS_OCCL = 0x0002519C;
	public final static short NOM_VENT_PRESS_OCCL = (short)0x519C;
	// PEEP Positive End-Expiratory Pressure PEEP
	public final static int NLS_NOM_VENT_PRESS_AWAY_END_EXP_POS = 0x000251A8;
	public final static short NOM_VENT_PRESS_AWAY_END_EXP_POS = (short)0x51A8;
	// Vd Dead Space Volume Vd
	public final static int NLS_NOM_VENT_VOL_AWAY_DEADSP = 0x000251B0;
	public final static short NOM_VENT_VOL_AWAY_DEADSP = (short)0x51B0;
	// relVd relative Dead Space
	public final static int NLS_NOM_VENT_VOL_AWAY_DEADSP_REL = 0x000251B4;
	public final static short NOM_VENT_VOL_AWAY_DEADSP_REL = (short)0x51B4;
	// TrpVol Lung Volume Trapped
	public final static int NLS_NOM_VENT_VOL_LUNG_TRAPD = 0x000251B8;
	public final static short NOM_VENT_VOL_LUNG_TRAPD = (short)0x51B8;
	// Leak Leakage
	public final static int NLS_NOM_VENT_VOL_LEAK = 0x00025370;
	public final static short NOM_VENT_VOL_LEAK = (short)0x5370;
	// ALVENT Alveolar Ventilation ALVENT
	public final static int NLS_NOM_VENT_VOL_LUNG_ALV = 0x00025374;
	public final static short NOM_VENT_VOL_LUNG_ALV = (short)0x5374;
	// VC Vital Lung Capacity
	public final static int NLS_NOM_CAPAC_VITAL = 0x00025080;
	public final static short NOM_CAPAC_VITAL = (short)0x5080;
	// COMP generic label Lung Compliance
	public final static int NLS_NOM_COMPL_LUNG = 0x00025088;
	public final static short NOM_COMPL_LUNG = (short)0x5088;
	// Cdyn Dynamic Lung Compliance
	public final static int NLS_NOM_COMPL_LUNG_DYN = 0x0002508C;
	public final static short NOM_COMPL_LUNG_DYN = (short)0x508C;
	// Cstat Static Lung Compliance
	public final static int NLS_NOM_COMPL_LUNG_STATIC = 0x00025090;
	public final static short NOM_COMPL_LUNG_STATIC = (short)0x5090;
	// PIF Inspiratory Peak Flow
	public final static int NLS_NOM_FLOW_AWAY_INSP_MAX = 0x000250DD;
	public final static short NOM_FLOW_AWAY_INSP_MAX = (short)0x50DD;
	// PEF Expiratory Peak Flow
	public final static int NLS_NOM_FLOW_AWAY_EXP_MAX = 0x000250D9;
	public final static short NOM_FLOW_AWAY_EXP_MAX = (short)0x50D9;
	// BIS Bispectral Index
	public final static int NLS_NOM_EEG_BISPECTRAL_INDEX = 0x0002F04E;
	public final static short NOM_EEG_BISPECTRAL_INDEX = (short)0xF04E;
	//public final static short NOM_DIM_DIMLESS = (short)0x0200;
	// SQI Signal Quality Index
	public final static int NLS_NOM_EEG_BIS_SIG_QUAL_INDEX = 0x0002F04D;
	public final static short NOM_EEG_BIS_SIG_QUAL_INDEX = (short)0xF04D;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// EMG Electromyography
	public final static int NLS_NOM_EMG_ELEC_POTL_MUSCL = 0x0002593C;
	public final static short NOM_EMG_ELEC_POTL_MUSCL = (short)0x593C;
	public final static short NOM_DIM_DECIBEL = (short)0x1920;
	// TP Total Power
	public final static int NLS_NOM_EEG_PWR_SPEC_TOT = 0x000259B8;
	public final static short NOM_EEG_PWR_SPEC_TOT = (short)0x59B8;
	//public final static short NOM_DIM_DECIBEL = (short)0x1920;
	// TP1 Total Power channel 1
	public final static int NLS_EEG_NAMES_CHAN_TP1 = 0x800F5403;
	//public final static short NOM_EEG_PWR_SPEC_TOT = (short)0x59B8;
	public final static short NOM_DIM_NANO_WATT = (short)0x0FD4;
	// TP2 Total Power channel 2
	public final static int NLS_EEG_NAMES_CHAN_TP2 = 0x800F5404;
	//public final static short NOM_EEG_PWR_SPEC_TOT = (short)0x59B8;
	//public final static short NOM_DIM_NANO_WATT = (short)0x0FD4;
	// SR Suppression Ratio
	public final static int NLS_NOM_EEG_RATIO_SUPPRN = 0x0002F04A;
	public final static short NOM_EEG_RATIO_SUPPRN = (short)0xF04A;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// SEF Spectral Edge Frequency
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE = 0x00025988;
	public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE = (short)0x5988;
	public final static short NOM_DIM_HZ = (short)0x09C0;
	// MDF Mean Dominant Frequency
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN = 0x0002597C;
	public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN = (short)0x597C;
	//public final static short NOM_DIM_HZ = (short)0x09C0;
	// PPF Peak Power Frequency
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK = 0x00025984;
	public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK = (short)0x5984;
	//public final static short NOM_DIM_HZ = (short)0x09C0;
	// Frequ1 generic label for EEG channel 1
	public final static int NLS_EEG_NAMES_CHAN_FREQ1 = 0x800F5413;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE = (short)0x5988;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN = (short)0x597C;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK = (short)0x5984;
	//public final static short NOM_DIM_HZ = (short)0x09C0;
	// Frequ2 generic label for EEG channel 2
	public final static int NLS_EEG_NAMES_CHAN_FREQ2 = 0x800F5414;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE = (short)0x5988;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN = (short)0x597C;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK = (short)0x5984;
	//public final static short NOM_DIM_HZ = (short)0x09C0;
	// Prcnt1 generic label for EEG channel 1
	public final static int NLS_EEG_NAMES_CHAN_PCNT1 = 0x800F5415;
	public final static short NOM_EEG_PWR_SPEC_ALPHA_REL = (short)0x59D4;
	public final static short NOM_EEG_PWR_SPEC_BETA_REL = (short)0x59D8;
	public final static short NOM_EEG_PWR_SPEC_DELTA_REL = (short)0x59DC;
	public final static short NOM_EEG_PWR_SPEC_THETA_REL = (short)0x59E0;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// Prcnt2 generic label for EEG channel 2
	public final static int NLS_EEG_NAMES_CHAN_PCNT2 = 0x800F5416;
	//public final static short NOM_EEG_PWR_SPEC_ALPHA_REL = (short)0x59D4;
	//public final static short NOM_EEG_PWR_SPEC_BETA_REL = (short)0x59D8;
	//public final static short NOM_EEG_PWR_SPEC_DELTA_REL = (short)0x59DC;
	//public final static short NOM_EEG_PWR_SPEC_THETA_REL = (short)0x59E0;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// AAI A-Line ARX Index
	public final static int NLS_NOM_ELEC_EVOK_POTL_CRTX_ACOUSTIC_AAI = 0x0002F873;
	public final static short NOM_ELEC_EVOK_POTL_CRTX_ACOUSTIC_AAI = (short)0xF873;
	// BSI Burst Suppression Indicator
	public final static int NLS_NOM_EEG_BURST_SUPPRN_INDEX = 0x0002F840;
	public final static short NOM_EEG_BURST_SUPPRN_INDEX = (short)0xF840;
	// Temp Unspecific Temperature
	public final static int NLS_NOM_TEMP = 0x00024B48;
	public final static short NOM_TEMP = (short)0x4B48;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Trect Rectal Temperature
	public final static int NLS_NOM_TEMP_RECT = 0x0002E004;
	public final static short NOM_TEMP_RECT = (short)0xE004;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// 135
	public final static int NLS_NOM_TEMP_BLD = 0x0002E014;
	public final static short NOM_TEMP_BLD = (short)0xE014;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tcore Core (Body) Temperature
	public final static int NLS_NOM_TEMP_CORE = 0x00024B60;
	public final static short NOM_TEMP_CORE = (short)0x4B60;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tskin Skin Temperature
	public final static int NLS_NOM_TEMP_SKIN = 0x00024B74;
	public final static short NOM_TEMP_SKIN = (short)0x4B74;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tesoph Esophagial Temperature
	public final static int NLS_NOM_TEMP_ESOPH = 0x00024B64;
	public final static short NOM_TEMP_ESOPH = (short)0x4B64;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tnaso Naso pharyngial Temperature
	public final static int NLS_NOM_TEMP_NASOPH = 0x00024B6C;
	public final static short NOM_TEMP_NASOPH = (short)0x4B6C;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tart Areterial Temperature
	public final static int NLS_NOM_TEMP_ART = 0x00024B50;
	public final static short NOM_TEMP_ART = (short)0x4B50;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tven Venous Temperature
	public final static int NLS_NOM_TEMP_VEN = 0x00024B7C;
	public final static short NOM_TEMP_VEN = (short)0x4B7C;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tvesic Temperature of the Urine fluid
	public final static int NLS_NOM_TEMP_VESICAL = 0x0002F0C4;
	public final static short NOM_TEMP_VESICAL = (short)0xF0C4;
	// Ttymp Tympanic Temperature
	public final static int NLS_NOM_TEMP_TYMP = 0x00024B78;
	public final static short NOM_TEMP_TYMP = (short)0x4B78;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tcereb Cerebral Temperature
	public final static int NLS_NOM_TEMP_CEREBRAL = 0x0002F0C5;
	public final static short NOM_TEMP_CEREBRAL = (short)0xF0C5;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tamb Ambient Temperature
	public final static int NLS_NOM_TEMP_AMBIENT = 0x0002F0C6;
	public final static short NOM_TEMP_AMBIENT = (short)0xF0C6;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tairwy Airway Temperature
	public final static int NLS_NOM_TEMP_AWAY = 0x00024B54;
	public final static short NOM_TEMP_AWAY = (short)0x4B54;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tinj Injectate Temperature
	public final static int NLS_NOM_TEMP_INJ = 0x00024B68;
	public final static short NOM_TEMP_INJ = (short)0x4B68;
	// T1Core Core Temperature 1 (generic)
	public final static int NLS_NOM_TEMP_CORE_GEN_1 = 0x0002F966;
	public final static short NOM_TEMP_CORE_GEN_1 = (short)0xF966;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// T2Core Core Temperature 2 (generic)
	public final static int NLS_NOM_TEMP_CORE_GEN_2 = 0x0002F967;
	public final static short NOM_TEMP_CORE_GEN_2 = (short)0xF967;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// DeltaTemp Difference Temperature
	public final static int NLS_NOM_TEMP_DIFF = 0x0002E018;
	public final static short NOM_TEMP_DIFF = (short)0xE018;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// Tbody Patient Temperature
	public final static int NLS_NOM_TEMP_BODY = 0x00024B5C;
	//public final static short NOM_TEMP = (short)0x4B48;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// 137
	public final static int NLS_NOM_TEMP_RECT_PRED = 0x0002F114;
	public final static short NOM_TEMP_RECT_PRED = (short)0xF114;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// pToral Predictive Oral Temperature
	public final static int NLS_NOM_TEMP_ORAL_PRED = 0x0002F110;
	public final static short NOM_TEMP_ORAL_PRED = (short)0xF110;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// pTaxil Predictive Axillary Temperature
	public final static int NLS_NOM_TEMP_AXIL_PRED = 0x0002F118;
	public final static short NOM_TEMP_AXIL_PRED = (short)0xF118;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// T1 Generic Temperature 1 (T1)
	public final static int NLS_NOM_TEMP_GEN_1 = 0x0002F0C7;
	public final static short NOM_TEMP_GEN_1 = (short)0xF0C7;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// T2 Generic Temperature 2 (T2)
	public final static int NLS_NOM_TEMP_GEN_2 = 0x0002F0C8;
	public final static short NOM_TEMP_GEN_2 = (short)0xF0C8;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// T3 Generic Temperature 3 (T3)
	public final static int NLS_NOM_TEMP_GEN_3 = 0x0002F0C9;
	public final static short NOM_TEMP_GEN_3 = (short)0xF0C9;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// T4 Generic Temperature 4 (T4)
	public final static int NLS_NOM_TEMP_GEN_4 = 0x0002F0CA;
	public final static short NOM_TEMP_GEN_4 = (short)0xF0CA;
	//public final static short NOM_DIM_DEGC = (short)0x17A0;
	//public final static short NOM_DIM_FAHR = (short)0x1140;
	// N2 generic N2 label
	public final static int NLS_NOM_CONC_AWAY_N2 = 0x0002537C;
	public final static short NOM_CONC_AWAY_N2 = (short)0x537C;
	public final static short NOM_CONC_AWAY_N2_ET = (short)0x5380;
	public final static short NOM_CONC_AWAY_N2_INSP = (short)0x5384;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// N2O generic Nitrous Oxide label
	public final static int NLS_NOM_CONC_AWAY_N2O = 0x000251F0;
	public final static short NOM_CONC_AWAY_N2O = (short)0x51F0;
	public final static short NOM_CONC_AWAY_N2O_ET = (short)0x522C;
	public final static short NOM_CONC_AWAY_N2O_INSP = (short)0x5280;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// ISO generic Isoflurane label
	public final static int NLS_NOM_CONC_AWAY_ISOFL = 0x000251E8;
	public final static short NOM_CONC_AWAY_ISOFL = (short)0x51E8;
	public final static short NOM_CONC_AWAY_ISOFL_ET = (short)0x5224;
	public final static short NOM_CONC_AWAY_ISOFL_INSP = (short)0x5278;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// SEV generic Sevoflurane label
	public final static int NLS_NOM_CONC_AWAY_SEVOFL = 0x000251E4;
	public final static short NOM_CONC_AWAY_SEVOFL = (short)0x51E4;
	public final static short NOM_CONC_AWAY_SEVOFL_ET = (short)0x5220;
	public final static short NOM_CONC_AWAY_SEVOFL_INSP = (short)0x5274;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// ENF generic Enflurane label
	public final static int NLS_NOM_CONC_AWAY_ENFL = 0x000251DC;
	public final static short NOM_CONC_AWAY_ENFL = (short)0x51DC;
	public final static short NOM_CONC_AWAY_ENFL_ET = (short)0x5218;
	public final static short NOM_CONC_AWAY_ENFL_INSP = (short)0x526C;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// HAL generic Halothane label
	public final static int NLS_NOM_CONC_AWAY_HALOTH = 0x000251E0;
	public final static short NOM_CONC_AWAY_HALOTH = (short)0x51E0;
	public final static short NOM_CONC_AWAY_HALOTH_ET = (short)0x521C;
	public final static short NOM_CONC_AWAY_HALOTH_INSP = (short)0x5270;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// DES generic Desflurane label
	public final static int NLS_NOM_CONC_AWAY_DESFL = 0x000251D8;
	public final static short NOM_CONC_AWAY_DESFL = (short)0x51D8;
	public final static short NOM_CONC_AWAY_DESFL_ET = (short)0x5214;
	public final static short NOM_CONC_AWAY_DESFL_INSP = (short)0x5268;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// AGT generic Agent label
	public final static int NLS_NOM_CONC_AWAY_AGENT = 0x00025388;
	public final static short NOM_CONC_AWAY_AGENT = (short)0x5388;
	public final static short NOM_CONC_AWAY_AGENT_ET = (short)0x538C;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// inAGT Generic Inspired Agent Concentration
	public final static int NLS_NOM_CONC_AWAY_AGENT_INSP = 0x00025390;
	public final static short NOM_CONC_AWAY_AGENT_INSP = (short)0x5390;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// AGT1 generic Agent1 label
	public final static int NLS_GASES_NAMES_CONC_AWAY_AGENT1 = 0x805A5401;
	//public final static short NOM_CONC_AWAY_AGENT_ET = (short)0x538C;
	//public final static short NOM_CONC_AWAY_AGENT_INSP = (short)0x5390;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// AGT2 generic Agent2 label
	public final static int NLS_GASES_NAMES_CONC_AWAY_AGENT2 = 0x805A5402;
	//public final static short NOM_CONC_AWAY_AGENT_ET = (short)0x538C;
	//public final static short NOM_CONC_AWAY_AGENT_INSP = (short)0x5390;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// MAC Minimum Alveolar Concentration
	public final static int NLS_NOM_CONC_AWAY_MAC = 0x0002F099;
	public final static short NOM_CONC_AWAY_MAC = (short)0xF099;
	// MAC Airway MAC Concentration
	public final static int NLS_NOM_CONC_AWAY_SUM_MAC = 0x0002F05D;
	public final static short NOM_CONC_AWAY_SUM_MAC_ET = (short)0xF05E;
	public final static short NOM_CONC_AWAY_SUM_MAC_INSP = (short)0xF05F;
	// SVR Systemic Vascular Resistance
	public final static int NLS_NOM_RES_VASC_SYS = 0x00024B28;
	public final static short NOM_RES_VASC_SYS = (short)0x4B28;
	public final static short NOM_DIM_X_DYNE_PER_SEC_PER_CM5 = (short)0x1020;
	// SVRI Systemic Vascular Resistance Index
	public final static int NLS_NOM_RES_VASC_SYS_INDEX = 0x00024900;
	public final static short NOM_RES_VASC_SYS_INDEX = (short)0x4900;
	// LVSW Left Ventricular Stroke Volume
	public final static int NLS_NOM_WK_LV_STROKE = 0x00024B9C;
	public final static short NOM_WK_LV_STROKE = (short)0x4B9C;
	// LVSWI Left Ventricular Stroke Volume Index
	public final static int NLS_NOM_WK_LV_STROKE_INDEX = 0x00024904;
	public final static short NOM_WK_LV_STROKE_INDEX = (short)0x4904;
	// RVSW Right Ventricular Stroke Volume
	public final static int NLS_NOM_WK_RV_STROKE = 0x00024BA4;
	public final static short NOM_WK_RV_STROKE = (short)0x4BA4;
	// RVSWI Right Ventricular Stroke Work Index
	public final static int NLS_NOM_WK_RV_STROKE_INDEX = 0x00024908;
	public final static short NOM_WK_RV_STROKE_INDEX = (short)0x4908;
	// PVR Pulmonary vascular Resistance
	public final static int NLS_NOM_RES_VASC_PULM = 0x00024B24;
	public final static short NOM_RES_VASC_PULM = (short)0x4B24;
	// PVRI Pulmonary vascular Resistance PVRI
	public final static int NLS_NOM_RES_VASC_PULM_INDEX = 0x0002F067;
	public final static short NOM_RES_VASC_PULM_INDEX = (short)0xF067;
	// LCW Left Cardiac Work
	public final static int NLS_NOM_WK_CARD_LEFT = 0x00024B90;
	public final static short NOM_WK_CARD_LEFT = (short)0x4B90;
	// LCWI Left Cardiac Work Index
	public final static int NLS_NOM_WK_CARD_LEFT_INDEX = 0x0002F068;
	public final static short NOM_WK_CARD_LEFT_INDEX = (short)0xF068;
	// RCW Right Cardiac Work
	public final static int NLS_NOM_WK_CARD_RIGHT = 0x00024B94;
	public final static short NOM_WK_CARD_RIGHT = (short)0x4B94;
	// RCWI Right Cardiac Work Index
	public final static int NLS_NOM_WK_CARD_RIGHT_INDEX = 0x0002F069;
	public final static short NOM_WK_CARD_RIGHT_INDEX = (short)0xF069;
	// VO2 Oxygen Consumption VO2
	public final static int NLS_NOM_SAT_O2_CONSUMP = 0x00024B00;
	public final static short NOM_SAT_O2_CONSUMP = (short)0x4B00;
	// GCS Glasgow Coma Score
	public final static int NLS_NOM_SCORE_GLAS_COMA = 0x00025880;
	public final static short NOM_SCORE_GLAS_COMA = (short)0x5880;
	// EyeRsp SubScore of the GCS: Eye Response
	public final static int NLS_NOM_SCORE_EYE_SUBSC_GLAS_COMA = 0x00025882;
	public final static short NOM_SCORE_EYE_SUBSC_GLAS_COMA = (short)0x5882;
	// MotRsp SubScore of the GCS: Motoric Response
	public final static int NLS_NOM_SCORE_MOTOR_SUBSC_GLAS_COMA = 0x00025883;
	public final static short NOM_SCORE_MOTOR_SUBSC_GLAS_COMA = (short)0x5883;
	// VblRsp SubScore of the GCS: Verbal Response
	public final static int NLS_NOM_SCORE_SUBSC_VERBAL_GLAS_COMA = 0x00025884;
	public final static short NOM_SCORE_SUBSC_VERBAL_GLAS_COMA = (short)0x5884;
	// HC Head Circumferince
	public final static int NLS_NOM_CIRCUM_HEAD = 0x00025900;
	public final static short NOM_CIRCUM_HEAD = (short)0x5900;
	// PRL Pupil Reaction Left eye - light reaction of left eye's pupil
	public final static int NLS_NOM_TIME_PD_PUPIL_REACT_LEFT = 0x00025924;
	public final static short NOM_TIME_PD_PUPIL_REACT_LEFT = (short)0x5924;
	// PRR Pupil Reaction Righteye - light reaction of right eye's pupil
	public final static int NLS_NOM_TIME_PD_PUPIL_REACT_RIGHT = 0x00025928;
	public final static short NOM_TIME_PD_PUPIL_REACT_RIGHT = (short)0x5928;
	// pHa pH in arterial Blood
	public final static int NLS_NOM_CONC_PH_ART = 0x00027004;
	public final static short NOM_CONC_PH_ART = (short)0x7004;
	// PaCO2 Partial Pressure of arterial Carbon Dioxide
	public final static int NLS_NOM_CONC_PCO2_ART = 0x00027008;
	public final static short NOM_CONC_PCO2_ART = (short)0x7008;
	// PaO2 Partial O2 arterial
	public final static int NLS_NOM_CONC_PO2_ART = 0x0002700C;
	public final static short NOM_CONC_PO2_ART = (short)0x700C;
	// Hb Hemoglobin in arterial Blood
	public final static int NLS_NOM_CONC_HB_ART = 0x00027014;
	public final static short NOM_CONC_HB_ART = (short)0x7014;
	// CaO2 Arterial Oxygen Content CaO2
	public final static int NLS_NOM_CONC_HB_O2_ART = 0x00027018;
	public final static short NOM_CONC_HB_O2_ART = (short)0x7018;
	// pHv pH in venous Blood
	public final static int NLS_NOM_CONC_PH_VEN = 0x00027034;
	public final static short NOM_CONC_PH_VEN = (short)0x7034;
	// PvCO2 Partial CO2 in the venous blood
	public final static int NLS_NOM_CONC_PCO2_VEN = 0x00027038;
	public final static short NOM_CONC_PCO2_VEN = (short)0x7038;
	// PvO2 Partial O2 Venous
	public final static int NLS_NOM_CONC_PO2_VEN = 0x0002703C;
	public final static short NOM_CONC_PO2_VEN = (short)0x703C;
	// CvO2 Venous Oxygen Content
	public final static int NLS_NOM_CONC_HB_O2_VEN = 0x00027048;
	public final static short NOM_CONC_HB_O2_VEN = (short)0x7048;
	// UrNa Natrium in Urine
	public final static int NLS_NOM_CONC_NA_URINE = 0x0002706C;
	public final static short NOM_CONC_NA_URINE = (short)0x706C;
	// SerNa Natrium in Serum
	public final static int NLS_NOM_CONC_NA_SERUM = 0x000270D8;
	public final static short NOM_CONC_NA_SERUM = (short)0x70D8;
	// pH pH in the Blood Plasma
	public final static int NLS_NOM_CONC_PH_GEN = 0x00027104;
	public final static short NOM_CONC_PH_GEN = (short)0x7104;
	// HCO3 Hydrocarbon concentration in Blood Plasma
	public final static int NLS_NOM_CONC_HCO3_GEN = 0x00027108;
	public final static short NOM_CONC_HCO3_GEN = (short)0x7108;
	// Na Natrium (Sodium)
	public final static int NLS_NOM_CONC_NA_GEN = 0x0002710C;
	public final static short NOM_CONC_NA_GEN = (short)0x710C;
	// K Kalium (Potassium)
	public final static int NLS_NOM_CONC_K_GEN = 0x00027110;
	public final static short NOM_CONC_K_GEN = (short)0x7110;
	// Glu Glucose
	public final static int NLS_NOM_CONC_GLU_GEN = 0x00027114;
	public final static short NOM_CONC_GLU_GEN = (short)0x7114;
	// PCO2 Partial CO2
	public final static int NLS_NOM_CONC_PCO2_GEN = 0x00027140;
	public final static short NOM_CONC_PCO2_GEN = (short)0x7140;
	// PO2 Partial O2.
	public final static int NLS_NOM_CONC_PO2_GEN = 0x00027174;
	public final static short NOM_CONC_PO2_GEN = (short)0x7174;
	// Hct Haematocrit
	public final static int NLS_NOM_CONC_HCT_GEN = 0x00027184;
	public final static short NOM_CONC_HCT_GEN = (short)0x7184;
	// BE Base Excess of Blood
	public final static int NLS_NOM_BASE_EXCESS_BLD_ART = 0x0002716C;
	public final static short NOM_BASE_EXCESS_BLD_ART = (short)0x716C;
	// VO2I Oxygen Consumption Index VO2I
	public final static int NLS_NOM_SAT_O2_CONSUMP_INDEX = 0x0002F06A;
	public final static short NOM_SAT_O2_CONSUMP_INDEX = (short)0xF06A;
	// PB Barometric Pressure = Ambient Pressure
	public final static int NLS_NOM_PRESS_AIR_AMBIENT = 0x0002F06B;
	public final static short NOM_PRESS_AIR_AMBIENT = (short)0xF06B;
	// InjVol Injectate Volume (Cardiac Output)
	public final static int NLS_NOM_VOL_INJ = 0x0002F079;
	public final static short NOM_VOL_INJ = (short)0xF079;
	// ETVI ExtraVascular Thermo Volume Index. Cardiac Output.
	public final static int NLS_NOM_VOL_THERMO_EXTRA_VASC_INDEX = 0x0002F07A;
	public final static short NOM_VOL_THERMO_EXTRA_VASC_INDEX = (short)0xF07A;
	// CompCt Generic Numeric Calculation Constant
	public final static int NLS_NOM_NUM_CALC_CONST = 0x0002F07B;
	public final static short NOM_METRIC_NOS = (short)0xEFFF;
	// Cl Chloride
	public final static int NLS_NOM_CONC_CHLORIDE_GEN = 0x00027168;
	public final static short NOM_CONC_CHLORIDE_GEN = (short)0x7168;
	// BUN Blood Urea Nitrogen
	public final static int NLS_NOM_CONC_BLD_UREA_NITROGEN = 0x0002F08F;
	public final static short NOM_CONC_BLD_UREA_NITROGEN = (short)0xF08F;
	// BEecf Base Excess of Extra-Cellular Fluid
	public final static int NLS_NOM_CONC_BASE_EXCESS_ECF = 0x0002F090;
	public final static short NOM_CONC_BASE_EXCESS_ECF = (short)0xF090;
	// Ca-vO2 Arteriovenous Oxygen Difference Ca-vO2
	public final static int NLS_NOM_CONC_DIFF_HB_O2_ATR_VEN = 0x0002F092;
	public final static short NOM_CONC_DIFF_HB_O2_ATR_VEN = (short)0xF092;
	// CathCt Generic Numeric Calculation Constant
	public final static int NLS_NOM_NUM_CATHETER_CONST = 0x0002F07C;
	public final static short NOM_NUM_CATHETER_CONST = (short)0xF07C;
	// BSA Body Surface Area
	public final static int NLS_NOM_AREA_BODY_SURFACE = 0x0002F071;
	public final static short NOM_AREA_BODY_SURFACE = (short)0xF071;
	// Weight Patient Weight
	public final static int NLS_NOM_PAT_WEIGHT = 0x0002F093;
	public final static short NOM_PAT_WEIGHT = (short)0xF093;
	// Height Patient Height
	public final static int NLS_NOM_PAT_HEIGHT = 0x0002F094;
	public final static short NOM_PAT_HEIGHT = (short)0xF094;
	// P5 Generic Pressure 5 (P5)
	public final static int NLS_NOM_PRESS_GEN_5 = 0x0002F3F4;
	public final static short NOM_PRESS_GEN_5 = (short)0xF3F4;
	public final static short NOM_PRESS_GEN_5_SYS = (short)0xF3F5;
	public final static short NOM_PRESS_GEN_5_DIA = (short)0xF3F6;
	public final static short NOM_PRESS_GEN_5_MEAN = (short)0xF3F7;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// P6 Generic Pressure 6 (P6)
	public final static int NLS_NOM_PRESS_GEN_6 = 0x0002F3F8;
	public final static short NOM_PRESS_GEN_6 = (short)0xF3F8;
	public final static short NOM_PRESS_GEN_6_SYS = (short)0xF3F9;
	public final static short NOM_PRESS_GEN_6_DIA = (short)0xF3FA;
	public final static short NOM_PRESS_GEN_6_MEAN = (short)0xF3FB;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// P7 Generic Pressure 7 (P7)
	public final static int NLS_NOM_PRESS_GEN_7 = 0x0002F3FC;
	public final static short NOM_PRESS_GEN_7 = (short)0xF3FC;
	public final static short NOM_PRESS_GEN_7_SYS = (short)0xF3FD;
	//public final static short NOM_PRESS_GEN_7 = (short)0xF3FC;
	public final static short NOM_PRESS_GEN_7_MEAN = (short)0xF3FF;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// P8 Generic Pressure 8 (P8)
	public final static int NLS_NOM_PRESS_GEN_8 = 0x0002F400;
	public final static short NOM_PRESS_GEN_8 = (short)0xF400;
	public final static short NOM_PRESS_GEN_8_SYS = (short)0xF401;
	public final static short NOM_PRESS_GEN_8_DIA = (short)0xF402;
	public final static short NOM_PRESS_GEN_8_MEAN = (short)0xF403;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// BUN/cr BUN Creatinine Ratio
	public final static int NLS_NOM_RATIO_BUN_CREA = 0x0002F88F;
	public final static short NOM_RATIO_BUN_CREA = (short)0xF88F;
	// TFC Thoracic Fluid Content
	public final static int NLS_NOM_VOL_FLUID_THORAC = 0x0002F8C5;
	public final static short NOM_VOL_FLUID_THORAC = (short)0xF8C5;
	// TFI Thoracic Fluid Content Index
	public final static int NLS_NOM_VOL_FLUID_THORAC_INDEX = 0x0002F8C6;
	public final static short NOM_VOL_FLUID_THORAC_INDEX = (short)0xF8C6;
	// ACI Accelerated Cardiac Index
	public final static int NLS_NOM_OUTPUT_CARD_INDEX_ACCEL = 0x0002F889;
	public final static short NOM_OUTPUT_CARD_INDEX_ACCEL = (short)0xF889;
	// HI Heart Contractility Index
	public final static int NLS_NOM_CARD_CONTRACT_HEATHER_INDEX = 0x0002F81C;
	public final static short NOM_CARD_CONTRACT_HEATHER_INDEX = (short)0xF81C;
	// CH2O Free Water Clearance
	public final static int NLS_NOM_FREE_WATER_CLR = 0x0002F884;
	public final static short NOM_FREE_WATER_CLR = (short)0xF884;
	// COsm Osmolar Clearance
	public final static int NLS_NOM_CREA_OSM = 0x0002F83F;
	public final static short NOM_CREA_OSM = (short)0xF83F;
	// CreaCl Creatinine Clearance
	public final static int NLS_NOM_CONC_CREA_CLR = 0x0002F16C;
	public final static short NOM_CONC_CREA_CLR = (short)0xF16C;
	// FeNa Fractional Excretion of Sodium
	public final static int NLS_NOM_FRACT_EXCR_NA = 0x0002F194;
	public final static short NOM_FRACT_EXCR_NA = (short)0xF194;
	// IMV Intermittent Mandatory Ventilation
	public final static int NLS_NOM_VENT_MODE_MAND_INTERMIT = 0x0002D02A;
	public final static short NOM_VENT_MODE_MAND_INTERMIT = (short)0xD02A;
	// PlOsm Plasma Osmolarity
	public final static int NLS_NOM_PLASMA_OSM = 0x0002F16B;
	public final static short NOM_PLASMA_OSM = (short)0xF16B;
	// SCrea Serum Creatinine
	public final static int NLS_NOM_CONC_CREA_SER = 0x0002F827;
	public final static short NOM_CONC_CREA_SER = (short)0xF827;
	// U/POsm Urine Plasma Osmolarity Ratio
	public final static int NLS_NOM_RATIO_URINE_SER_OSM = 0x0002F898;
	public final static short NOM_RATIO_URINE_SER_OSM = (short)0xF898;
	// U/SCr Urine Serum Creatinine Ratio
	public final static int NLS_NOM_RATIO_CONC_URINE_CREA_SER = 0x0002F892;
	public final static short NOM_RATIO_CONC_URINE_CREA_SER = (short)0xF892;
	// UrCrea Urine Creatinine
	public final static int NLS_NOM_CONC_CREA_URINE = 0x0002F196;
	public final static short NOM_CONC_CREA_URINE = (short)0xF196;
	// UrK Urine Potassium
	public final static int NLS_NOM_CONC_K_URINE = 0x0002F197;
	public final static short NOM_CONC_K_URINE = (short)0xF197;
	// UrKEx Urinary Potassium Excretion
	public final static int NLS_NOM_CONC_K_URINE_EXCR = 0x0002F198;
	public final static short NOM_CONC_K_URINE_EXCR = (short)0xF198;
	// UrNa/K Urine Sodium/Potassium Ratio
	public final static int NLS_NOM_RATIO_CONC_URINE_NA_K = 0x0002F893;
	public final static short NOM_RATIO_CONC_URINE_NA_K = (short)0xF893;
	// UrNaEx Urine Sodium Excretion
	public final static int NLS_NOM_CONC_NA_EXCR = 0x0002F830;
	public final static short NOM_CONC_NA_EXCR = (short)0xF830;
	// UrOsm Urine Osmolarity
	public final static int NLS_NOM_CONC_OSM_URINE = 0x0002F199;
	public final static short NOM_CONC_OSM_URINE = (short)0xF199;
	// UrVol Urine Volume
	public final static int NLS_NOM_VOL_URINE_BAL_PD = 0x00026824;
	public final static short NOM_VOL_URINE_BAL_PD = (short)0x6824;
	// NsLoss Nitrogen Balance
	public final static int NLS_NOM_NSLOSS = 0x0002F16D;
	public final static short NOM_NSLOSS = (short)0xF16D;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// Length Length for neonatal/pediatric
	public final static int NLS_NOM_BIRTH_LENGTH = 0x0002F818;
	public final static short NOM_BIRTH_LENGTH = (short)0xF818;
	// G.Age Gestational age for neonatal
	public final static int NLS_NOM_AGE_GEST = 0x0002F811;
	public final static short NOM_AGE_GEST = (short)0xF811;
	// BSA(B) BSA formula: Boyd
	public final static int NLS_NOM_AREA_BODY_SURFACE_ACTUAL_BOYD = 0x0002F812;
	//public final static short NOM_AREA_BODY_SURFACE = (short)0xF071;
	// BSA(D) BSA formula: Dubois
	public final static int NLS_NOM_AREA_BODY_SURFACE_ACTUAL_DUBOIS = 0x0002F813;
	//public final static short NOM_AREA_BODY_SURFACE = (short)0xF071;
	// PVcP Pressure Ventilation Control Pressure
	public final static int NLS_NOM_VENT_PRESS_AWAY_PV = 0x0002F8BC;
	public final static short NOM_VENT_PRESS_AWAY_PV = (short)0xF8BC;
	// Rdyn Dynamic Lung Resistance
	public final static int NLS_NOM_RES_AWAY_DYN = 0x0002F899;
	public final static short NOM_RES_AWAY_DYN = (short)0xF899;
	// NgInsP Negative Inspiratory Pressure
	public final static int NLS_NOM_PRESS_AWAY_NEG_MAX = 0x000250F9;
	public final static short NOM_PRESS_AWAY_NEG_MAX = (short)0x50F9;
	// SpPkFl Spontaneous Peak Flow
	public final static int NLS_NOM_FLOW_AWAY_MAX_SPONT = 0x0002F87D;
	public final static short NOM_FLOW_AWAY_MAX_SPONT = (short)0xF87D;
	// SpAWRR Spontaneous Airway Respiration Rate
	public final static int NLS_NOM_AWAY_RESP_RATE_SPONT = 0x0002F815;
	public final static short NOM_AWAY_RESP_RATE_SPONT = (short)0xF815;
	// PlGain Pleth Gain
	public final static int NLS_NOM_PULS_OXIM_PLETH_GAIN = 0x0002F88D;
	public final static short NOM_PULS_OXIM_PLETH_GAIN = (short)0xF88D;
	// fgAGT Fresh gas Anesthetic Agent
	public final static int NLS_NOM_FLOW_AWAY_AGENT = 0x0002F876;
	//public final static short NOM_CONC_AWAY_AGENT = (short)0x5388;
	// O2EI Oxygen Extraction Index
	public final static int NLS_NOM_EXTRACT_O2_INDEX = 0x0002F875;
	public final static short NOM_EXTRACT_O2_INDEX = (short)0xF875;
	// REF Right Heart Ejection Fraction
	public final static int NLS_NOM_RIGHT_HEART_FRACT_EJECT = 0x0002F89B;
	public final static short NOM_RIGHT_HEART_FRACT_EJECT = (short)0xF89B;
	// EDV End Diastolic Volume
	public final static int NLS_NOM_VOL_VENT_L_END_DIA = 0x00024C00;
	//public final static short NOM_VOL_GLOBAL_END_DIA = (short)0xF044;
	// ESV End Systolic Volume
	public final static int NLS_NOM_VOL_VENT_L_END_SYS = 0x00024C04;
	public final static short NOM_VOL_VENT_L_END_SYS = (short)0x4C04;
	// EDVI End Diastolic Volume Index
	public final static int NLS_NOM_VOL_VENT_L_END_DIA_INDEX = 0x0002F8D0;
	//public final static short NOM_VOL_GLOBAL_END_DIA_INDEX = (short)0xF045;
	// ESVI End Systolic Volume Index
	public final static int NLS_NOM_VOL_VENT_L_END_SYS_INDEX = 0x0002F8D1;
	public final static short NOM_VOL_VENT_L_END_SYS_INDEX = (short)0xF8D1;
	// RiseTi Rise Time
	public final static int NLS_NOM_VENT_TIME_PD_RAMP = 0x0002F8BD;
	public final static short NOM_VENT_TIME_PD_RAMP = (short)0xF8BD;
	// HFVAmp High Frequency Ventilation Amplitude
	public final static int NLS_NOM_VENT_AMPL_HFV = 0x0002F8B1;
	public final static short NOM_VENT_AMPL_HFV = (short)0xF8B1;
	// UrUrea Urine Urea
	public final static int NLS_NOM_CONC_UREA_URINE = 0x0002F195;
	public final static short NOM_CONC_UREA_URINE = (short)0xF195;
	// UrpH pH value in the Urine
	public final static int NLS_NOM_CONC_PH_URINE = 0x00027064;
	public final static short NOM_CONC_PH_URINE = (short)0x7064;
	// tCO2 total of CO2 - result of Blood gas Analysis
	public final static int NLS_NOM_CONC_CO2_TOT = 0x0002F825;
	public final static short NOM_CONC_CO2_TOT = (short)0xF825;
	// tBili total Bilirubin
	public final static int NLS_NOM_CONC_BILI_TOT = 0x0002F177;
	public final static short NOM_CONC_BILI_TOT = (short)0xF177;
	// SerGlu Glucose in Serum
	public final static int NLS_NOM_CONC_GLU_SER = 0x0002F82A;
	public final static short NOM_CONC_GLU_SER = (short)0xF82A;
	// UrGlu Glucose in Urine
	public final static int NLS_NOM_CONC_GLU_URINE = 0x0002F19F;
	public final static short NOM_CONC_GLU_URINE = (short)0xF19F;
	// dBili direct Bilirubin
	public final static int NLS_NOM_CONC_BILI_DIRECT = 0x0002F17A;
	public final static short NOM_CONC_BILI_DIRECT = (short)0xF17A;
	// SerCa Calcium in Serum
	public final static int NLS_NOM_CONC_CA_SER = 0x0002F824;
	public final static short NOM_CONC_CA_SER = (short)0xF824;
	// tSerCa total of Calcium in Serum
	public final static int NLS_NOM_CONC_tCA_SER = 0x0002F15D;
	public final static short NOM_CONC_tCA_SER = (short)0xF15D;
	// SerMg Magnesium in Serum
	public final static int NLS_NOM_CONC_MG_SER = 0x0002F15C;
	public final static short NOM_CONC_MG_SER = (short)0xF15C;
	// SerPho Phosphat in Serum
	public final static int NLS_NOM_CONC_P_SER = 0x0002F15E;
	public final static short NOM_CONC_P_SER = (short)0xF15E;
	// SerK Kalium (Potassium) in Serum
	public final static int NLS_NOM_CONC_K_SER = 0x0002F82F;
	public final static short NOM_CONC_K_SER = (short)0xF82F;
	// SerCl Clorid in Serum
	public final static int NLS_NOM_CONC_CHLOR_SER = 0x0002F15F;
	public final static short NOM_CONC_CHLOR_SER = (short)0xF15F;
	// SerAlb Albumine in Serum
	public final static int NLS_NOM_CONC_ALB_SER = 0x0002F163;
	public final static short NOM_CONC_ALB_SER = (short)0xF163;
	// UrCl Clorid in Urine
	public final static int NLS_NOM_CONC_CHLOR_URINE = 0x0002F19A;
	public final static short NOM_CONC_CHLOR_URINE = (short)0xF19A;
	// SerGlo Globulin in Serum
	public final static int NLS_NOM_CONC_GLO_SER = 0x0002F829;
	public final static short NOM_CONC_GLO_SER = (short)0xF829;
	// SerPro (Total) Protein in Serum
	public final static int NLS_NOM_CONC_PROT_SER = 0x0002F178;
	public final static short NOM_CONC_PROT_SER = (short)0xF178;
	// SrUrea Serum Urea
	public final static int NLS_NOM_UREA_SER = 0x0002F8AD;
	public final static short NOM_UREA_SER = (short)0xF8AD;
	// WBC White Blood Count (leucocyte count)
	public final static int NLS_NOM_WB_CNT = 0x0002F168;
	public final static short NOM_WB_CNT = (short)0xF168;
	// RBC Red Blood Count (erithrocyte count)
	public final static int NLS_NOM_RB_CNT = 0x0002F169;
	public final static short NOM_RB_CNT = (short)0xF169;
	// Plts Platelets (thrombocyte count)
	public final static int NLS_NOM_PLTS_CNT = 0x0002F167;
	public final static short NOM_PLTS_CNT = (short)0xF167;
	// MCV Mean Corpuscular Volume
	public final static int NLS_NOM_VOL_CORP_MEAN = 0x0002F8C4;
	public final static short NOM_VOL_CORP_MEAN = (short)0xF8C4;
	// MCH Mean Corpuscular Hemoglobin. Is the erithrocyte hemoglobin content
	public final static int NLS_NOM_HB_CORP_MEAN = 0x0002F885;
	public final static short NOM_HB_CORP_MEAN = (short)0xF885;
	// MCHC Mean Corpuscular Hemoglobin Concentration
	public final static int NLS_NOM_CONC_HB_CORP_MEAN = 0x0002F82C;
	public final static short NOM_CONC_HB_CORP_MEAN = (short)0xF82C;
	// PTT Partial Thromboplastin Time
	public final static int NLS_NOM_TIME_PD_PTT = 0x0002F8A5;
	public final static short NOM_TIME_PD_PTT = (short)0xF8A5;
	// PT Prothrombin Time
	public final static int NLS_NOM_TIME_PD_PT = 0x0002F18B;
	public final static short NOM_TIME_PD_PT = (short)0xF18B;
	// TT Thrombin Time
	public final static int NLS_NOM_TIME_PD_THROMBIN = 0x0002F191;
	public final static short NOM_TIME_PD_THROMBIN = (short)0xF191;
	// AP Alkalische Phosphatase
	public final static int NLS_NOM_CONC_AP = 0x0002F185;
	public final static short NOM_CONC_AP = (short)0xF185;
	// alphaA Alpha Amylase
	public final static int NLS_NOM_CONC_ALPHA_AMYLASE = 0x0002F186;
	public final static short NOM_CONC_ALPHA_AMYLASE = (short)0xF186;
	// CHE Cholesterinesterase
	public final static int NLS_NOM_CONC_CHE = 0x0002F182;
	public final static short NOM_CONC_CHE = (short)0xF182;
	// SerCK Creatinin Kinase
	public final static int NLS_NOM_CONC_CREA_KIN_SER = 0x0002F180;
	public final static short NOM_CONC_CREA_KIN_SER = (short)0xF180;
	// CK-MB Creatine Cinase of type muscle-brain
	public final static int NLS_NOM_CONC_CREA_KIN_MB = 0x0002F181;
	public final static short NOM_CONC_CREA_KIN_MB = (short)0xF181;
	// CK-MM Creatine Cinase of type muscle
	public final static int NLS_NOM_CONC_CREA_KIN_MM = 0x0002F17F;
	public final static short NOM_CONC_CREA_KIN_MM = (short)0xF17F;
	// GGT Gamma GT = Gamma Glutamyltranspeptidase
	public final static int NLS_NOM_CONC_GGT = 0x0002F189;
	public final static short NOM_CONC_GGT = (short)0xF189;
	// GOT Glutamic Oxaloacetic Transaminase
	public final static int NLS_NOM_CONC_GOT = 0x0002F188;
	public final static short NOM_CONC_GOT = (short)0xF188;
	// GPT Glutamic-Pyruvic-Transaminase
	public final static int NLS_NOM_CONC_GPT = 0x0002F187;
	public final static short NOM_CONC_GPT = (short)0xF187;
	// Fe Ferrum
	public final static int NLS_NOM_CONC_FE_GEN = 0x0002F160;
	public final static short NOM_CONC_FE_GEN = (short)0xF160;
	// Chol Cholesterin
	public final static int NLS_NOM_CONC_CHOLESTEROL = 0x0002F16E;
	public final static short NOM_CONC_CHOLESTEROL = (short)0xF16E;
	// TGL Triglyzeride
	public final static int NLS_NOM_CONC_TGL = 0x0002F16F;
	public final static short NOM_CONC_TGL = (short)0xF16F;
	// UrPro (Total) Protein in Urine
	public final static int NLS_NOM_CONC_PRO_URINE = 0x0002F19B;
	public final static short NOM_CONC_PRO_URINE = (short)0xF19B;
	// UrCa Calzium in Urine
	public final static int NLS_NOM_CONC_CA_URINE = 0x0002F19C;
	public final static short NOM_CONC_CA_URINE = (short)0xF19C;
	// CO-Hb Carboxy Hemoglobin
	public final static int NLS_NOM_CONC_HB_CO_GEN = 0x00027180;
	public final static short NOM_CONC_HB_CO_GEN = (short)0x7180;
	// HbF Fetal Hemoglobin
	public final static int NLS_NOM_CONC_HB_FETAL = 0x0002F165;
	public final static short NOM_CONC_HB_FETAL = (short)0xF165;
	// Met-Hb MetHemoglobin
	public final static int NLS_NOM_CONC_HB_MET_GEN = 0x0002717C;
	public final static short NOM_CONC_HB_MET_GEN = (short)0x717C;
	// tPro Total Protein
	public final static int NLS_NOM_CONC_PROT_TOT = 0x0002F179;
	public final static short NOM_CONC_PROT_TOT = (short)0xF179;
	// LDH Lactate Dehydrogenase
	public final static int NLS_NOM_CONC_LDH = 0x0002F17B;
	public final static short NOM_CONC_LDH = (short)0xF17B;
	// AST Aspartin - Aminotransferase
	public final static int NLS_NOM_CONC_AST = 0x0002F184;
	public final static short NOM_CONC_AST = (short)0xF184;
	// ALP Alveolarproteinose Rosen-Castleman-Liebow- Syndrom
	public final static int NLS_NOM_CONC_ALP = 0x0002F81D;
	public final static short NOM_CONC_ALP = (short)0xF81D;
	// RC Reticulocyte Count
	public final static int NLS_NOM_RET_CNT = 0x0002F16A;
	public final static short NOM_RET_CNT = (short)0xF16A;
	// CT Coagulation Time
	public final static int NLS_NOM_TIME_PD_COAGULATION = 0x0002F192;
	public final static short NOM_TIME_PD_COAGULATION = (short)0xF192;
	// ESR Erithrocyte sedimentation rate
	public final static int NLS_NOM_ES_RATE = 0x0002F17C;
	public final static short NOM_ES_RATE = (short)0xF17C;
	// KCT Kaolin cephalin time
	public final static int NLS_NOM_TIME_PD_KAOLIN_CEPHALINE = 0x0002F8A4;
	public final static short NOM_TIME_PD_KAOLIN_CEPHALINE = (short)0xF8A4;
	// Rexp Expiratory Resistance
	public final static int NLS_NOM_RES_AWAY_EXP = 0x00025124;
	public final static short NOM_RES_AWAY_EXP = (short)0x5124;
	// ExpTi Expiratory Time
	public final static int NLS_NOM_TIME_PD_EXP = 0x0002F8A1;
	public final static short NOM_TIME_PD_EXP = (short)0xF8A1;
	// Rinsp Inspiratory Resistance
	public final static int NLS_NOM_RES_AWAY_INSP = 0x00025128;
	public final static short NOM_RES_AWAY_INSP = (short)0x5128;
	// eeFlow Expiratory Peak Flow
	public final static int NLS_NOM_FLOW_AWAY_EXP_ET = 0x0002F87A;
	public final static short NOM_FLOW_AWAY_EXP_ET = (short)0xF87A;
	// Pmax Maximum Pressure during a breathing cycle
	public final static int NLS_NOM_VENT_PRESS_AWAY_INSP_MAX = 0x0002F8BB;
	//public final static short NOM_PRESS_AWAY_INSP_MAX = (short)0x5109;
	// AccVol Infusion Pump Accumulated volume. Measured value
	public final static int NLS_NOM_VOL_INFUS_ACTUAL_TOTAL = 0x000268FC;
	public final static short NOM_VOL_INFUS_ACTUAL_TOTAL = (short)0x68FC;
	// i-eN2O Inspired - EndTidal N2O
	public final static int NLS_NOM_VENT_CONC_AWAY_N2O_DELTA = 0x0002F8B7;
	public final static short NOM_VENT_CONC_AWAY_N2O_DELTA = (short)0xF8B7;
	// i-eHAL Inspired - EndTidal Halothane
	public final static int NLS_NOM_VENT_CONC_AWAY_HALOTH_DELTA = 0x0002F8B5;
	public final static short NOM_VENT_CONC_AWAY_HALOTH_DELTA = (short)0xF8B5;
	// i-eENF Inspired - EndTidal Enfluran
	public final static int NLS_NOM_VENT_CONC_AWAY_ENFL_DELTA = 0x0002F8B4;
	public final static short NOM_VENT_CONC_AWAY_ENFL_DELTA = (short)0xF8B4;
	// i-eISO Inspired - EndTidal Isofluran
	public final static int NLS_NOM_VENT_CONC_AWAY_ISOFL_DELTA = 0x0002F8B6;
	public final static short NOM_VENT_CONC_AWAY_ISOFL_DELTA = (short)0xF8B6;
	// i-eSEV Inspired - EndTidal Sevofluran
	public final static int NLS_NOM_VENT_CONC_AWAY_SEVOFL_DELTA = 0x0002F8B9;
	public final static short NOM_VENT_CONC_AWAY_SEVOFL_DELTA = (short)0xF8B9;
	// i-eDES Inspired - EndTidal Desfluran
	public final static int NLS_NOM_VENT_CONC_AWAY_DESFL_DELTA = 0x0002F8B3;
	public final static short NOM_VENT_CONC_AWAY_DESFL_DELTA = (short)0xF8B3;
	// i-eAGT Inspired - EndTidal Agent
	public final static int NLS_NOM_VENT_CONC_AWAY_AGENT_DELTA = 0x0002F8B2;
	public final static short NOM_VENT_CONC_AWAY_AGENT_DELTA = (short)0xF8B2;
	// cktO2 O2 measured in the Patient Circuit
	public final static int NLS_NOM_VENT_CONC_AWAY_O2_CIRCUIT = 0x0002F8B8;
	public final static short NOM_VENT_CONC_AWAY_O2_CIRCUIT = (short)0xF8B8;
	// MMV Mandatory Minute Volume
	public final static int NLS_NOM_VENT_VOL_MINUTE_AWAY_MAND = 0x000251CC;
	public final static short NOM_VENT_VOL_MINUTE_AWAY_MAND = (short)0x51CC;
	// RRaw Airway Respiration Rate. Used by the Ohmeda Ventilator.
	public final static int NLS_NOM_VENT_RESP_RATE = 0x00025022;
	//public final static short NOM_AWAY_RESP_RATE = (short)0x5012;
	// HFMVin Inspired High Frequency Mandatory Minute Volume
	public final static int NLS_NOM_VOL_MINUTE_AWAY_INSP_HFV = 0x0002F8CD;
	public final static short NOM_VOL_MINUTE_AWAY_INSP_HFV = (short)0xF8CD;
	// DCO2 High Frequency Gas Transport Coefficient value
	public final static int NLS_NOM_COEF_GAS_TRAN = 0x000251D4;
	public final static short NOM_COEF_GAS_TRAN = (short)0x51D4;
	// SpTVex Spontaenous Expired Tidal Volume
	public final static int NLS_NOM_VOL_AWAY_EXP_TIDAL_SPONT = 0x0002F8C2;
	public final static short NOM_VOL_AWAY_EXP_TIDAL_SPONT = (short)0xF8C2;
	// SpTV Spontaneuous Tidal Volume
	public final static int NLS_NOM_VENT_VOL_TIDAL_SPONT = 0x0002F0F3;
	public final static short NOM_VENT_VOL_TIDAL_SPONT = (short)0xF0F3;
	// MTV Mandatory Tidal Volume
	public final static int NLS_NOM_VENT_VOL_TIDAL_MAND = 0x0002F0F2;
	public final static short NOM_VENT_VOL_TIDAL_MAND = (short)0xF0F2;
	// HFTVin Inspired High Frequency Tidal Volume
	public final static int NLS_NOM_VENT_VOL_AWAY_INSP_TIDAL_HFV = 0x0002F8BE;
	public final static short NOM_VENT_VOL_AWAY_INSP_TIDAL_HFV = (short)0xF8BE;
	// HFVTV High Frequency Fraction Ventilation Tidal Volume
	public final static int NLS_NOM_VENT_VOL_TIDAL_HFV = 0x0002F8BF;
	public final static short NOM_VENT_VOL_TIDAL_HFV = (short)0xF8BF;
	// extHR denotes a Heart Rate received from an external device
	public final static int NLS_NOM_CARD_BEAT_RATE_EXT = 0x0002F81B;
	//public final static short NOM_ECG_CARD_BEAT_RATE = (short)0x4182;
	// Rf-I ST Reference Value for Lead I
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_I = 0x0002F411;
	public final static short NOM_ECG_AMPL_ST_BASELINE_I = (short)0xF411;
	// Rf-II ST Reference Value for Lead II
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_II = 0x0002F412;
	public final static short NOM_ECG_AMPL_ST_BASELINE_II = (short)0xF412;
	// Rf-III ST Reference Value for Lead III
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_III = 0x0002F44D;
	public final static short NOM_ECG_AMPL_ST_BASELINE_III = (short)0xF44D;
	// Rf-aVR ST Reference Value for Lead aVR
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_AVR = 0x0002F44E;
	public final static short NOM_ECG_AMPL_ST_BASELINE_AVR = (short)0xF44E;
	// Rf-aVL ST Reference Value for Lead aVL
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_AVL = 0x0002F44F;
	public final static short NOM_ECG_AMPL_ST_BASELINE_AVL = (short)0xF44F;
	// Rf-aVF ST Reference Value for Lead aVF
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_AVF = 0x0002F450;
	public final static short NOM_ECG_AMPL_ST_BASELINE_AVF = (short)0xF450;
	// Rf-V1 ST Reference Value for Lead V1
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_V1 = 0x0002F413;
	public final static short NOM_ECG_AMPL_ST_BASELINE_V1 = (short)0xF413;
	// Rf-V2 ST Reference Value for Lead V2
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_V2 = 0x0002F414;
	public final static short NOM_ECG_AMPL_ST_BASELINE_V2 = (short)0xF414;
	// Rf-V3 ST Reference Value for Lead V3
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_V3 = 0x0002F415;
	public final static short NOM_ECG_AMPL_ST_BASELINE_V3 = (short)0xF415;
	// Rf-V4 ST Reference Value for Lead V4
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_V4 = 0x0002F416;
	public final static short NOM_ECG_AMPL_ST_BASELINE_V4 = (short)0xF416;
	// Rf-V5 ST Reference Value for Lead V5
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_V5 = 0x0002F417;
	public final static short NOM_ECG_AMPL_ST_BASELINE_V5 = (short)0xF417;
	// Rf-V6 ST Reference Value for Lead V6
	public final static int NLS_NOM_ECG_AMPL_ST_BASELINE_V6 = 0x0002F418;
	public final static short NOM_ECG_AMPL_ST_BASELINE_V6 = (short)0xF418;
	// LT %AL Percent Alpha - Left (LT) Side
	public final static int NLS_NOM_EEG_PWR_SPEC_ALPHA_REL_LEFT = 0x0002F859;
	//public final static short NOM_EEG_PWR_SPEC_ALPHA_REL = (short)0x59D4;
	// LT %BE Percent Beta - Left Side
	public final static int NLS_NOM_EEG_PWR_SPEC_BETA_REL_LEFT = 0x0002F85F;
	//public final static short NOM_EEG_PWR_SPEC_BETA_REL = (short)0x59D8;
	// LT %DL Percent Delta - Left Side
	public final static int NLS_NOM_EEG_PWR_SPEC_DELTA_REL_LEFT = 0x0002F867;
	//public final static short NOM_EEG_PWR_SPEC_DELTA_REL = (short)0x59DC;
	// LT %TH Percent Theta - Left Side
	public final static int NLS_NOM_EEG_PWR_SPEC_THETA_REL_LEFT = 0x0002F86D;
	//public final static short NOM_EEG_PWR_SPEC_THETA_REL = (short)0x59E0;
	// LT AL Absolute Alpha - Left Side
	public final static int NLS_NOM_EEG_PWR_SPEC_ALPHA_ABS_LEFT = 0x0002F855;
	public final static short NOM_EEG_PWR_SPEC_ALPHA_ABS_LEFT = (short)0xF855;
	// LT BE Absolute Beta - Left Side
	public final static int NLS_NOM_EEG_PWR_SPEC_BETA_ABS_LEFT = 0x0002F85B;
	public final static short NOM_EEG_PWR_SPEC_BETA_ABS_LEFT = (short)0xF85B;
	// LT DL Absolute Delta - Left Side
	public final static int NLS_NOM_EEG_PWR_SPEC_DELTA_ABS_LEFT = 0x0002F863;
	public final static short NOM_EEG_PWR_SPEC_DELTA_ABS_LEFT = (short)0xF863;
	// LT TH Absolute Theta - Left Side
	public final static int NLS_NOM_EEG_PWR_SPEC_THETA_ABS_LEFT = 0x0002F869;
	public final static short NOM_EEG_PWR_SPEC_THETA_ABS_LEFT = (short)0xF869;
	// LT MDF Mean Dominant Frequency - Left Side
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN_LEFT = 0x0002F849;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN = (short)0x597C;
	// LT MPF Median Power Frequency - Left Side
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_MEDIAN_LEFT = 0x0002F84B;
	public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_MEDIAN_LEFT = (short)0xF84B;
	// LT PPF Peak Power Frequency - Left Side
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK_LEFT = 0x0002F84F;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK = (short)0x5984;
	// LT SEF Spectral Edge Frequency - Left Side
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE_LEFT = 0x0002F853;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE = (short)0x5988;
	// LT TP Total Power - Left Side
	public final static int NLS_NOM_EEG_PWR_SPEC_TOT_LEFT = 0x0002F871;
	//public final static short NOM_EEG_PWR_SPEC_TOT = (short)0x59B8;
	// LSCALE Scale of the Left Channel EEG wave
	public final static int NLS_NOM_EEG_ELEC_POTL_CRTX_GAIN_LEFT = 0x0002F841;
	public final static short NOM_EEG_ELEC_POTL_CRTX_GAIN_LEFT = (short)0xF841;
	// RT %AL Percent Alpha - Right (RT) Side
	public final static int NLS_NOM_EEG_PWR_SPEC_ALPHA_REL_RIGHT = 0x0002F85A;
	//public final static short NOM_EEG_PWR_SPEC_ALPHA_REL = (short)0x59D4;
	// RT %BE Percent Beta - Right Side
	public final static int NLS_NOM_EEG_PWR_SPEC_BETA_REL_RIGHT = 0x0002F860;
	//public final static short NOM_EEG_PWR_SPEC_BETA_REL = (short)0x59D8;
	// RT %DL Percent Delta - Right Side
	public final static int NLS_NOM_EEG_PWR_SPEC_DELTA_REL_RIGHT = 0x0002F868;
	//public final static short NOM_EEG_PWR_SPEC_DELTA_REL = (short)0x59DC;
	// RT %TH Percent Theta - Right Side
	public final static int NLS_NOM_EEG_PWR_SPEC_THETA_REL_RIGHT = 0x0002F86E;
	//public final static short NOM_EEG_PWR_SPEC_THETA_REL = (short)0x59E0;
	// RT AL Absolute Alpha - Right Side
	public final static int NLS_NOM_EEG_PWR_SPEC_ALPHA_ABS_RIGHT = 0x0002F856;
	public final static short NOM_EEG_PWR_SPEC_ALPHA_ABS_RIGHT = (short)0xF856;
	// RT BE Absolute Beta - Right Side
	public final static int NLS_NOM_EEG_PWR_SPEC_BETA_ABS_RIGHT = 0x0002F85C;
	public final static short NOM_EEG_PWR_SPEC_BETA_ABS_RIGHT = (short)0xF85C;
	// RT DL Absolute Delta - Right Side
	public final static int NLS_NOM_EEG_PWR_SPEC_DELTA_ABS_RIGHT = 0x0002F864;
	public final static short NOM_EEG_PWR_SPEC_DELTA_ABS_RIGHT = (short)0xF864;
	// RT TH Absolute Theta - Right Side
	public final static int NLS_NOM_EEG_PWR_SPEC_THETA_ABS_RIGHT = 0x0002F86A;
	public final static short NOM_EEG_PWR_SPEC_THETA_ABS_RIGHT = (short)0xF86A;
	// RT MDF Mean Dominant Frequency - Right Side
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN_RIGHT = 0x0002F84A;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN = (short)0x597C;
	// RT MPF Median Power Frequency - Right Side
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_MEDIAN_RIGHT = 0x0002F84C;
	public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_MEDIAN_RIGHT = (short)0xF84C;
	// RT PPF Peak Power Frequency - Right Side
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK_RIGHT = 0x0002F850;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK = (short)0x5984;
	// RT SEF Spectral Edge Frequency - Right Side
	public final static int NLS_NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE_RIGHT = 0x0002F854;
	//public final static short NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE = (short)0x5988;
	// RT TP Total Power - Right Side
	public final static int NLS_NOM_EEG_PWR_SPEC_TOT_RIGHT = 0x0002F872;
	//public final static short NOM_EEG_PWR_SPEC_TOT = (short)0x59B8;
	// RSCALE Scale of the Right Channel EEG wave
	public final static int NLS_NOM_EEG_ELEC_POTL_CRTX_GAIN_RIGHT = 0x0002F842;
	public final static short NOM_EEG_ELEC_POTL_CRTX_GAIN_RIGHT = (short)0xF842;
	// DPosP Duration Above Base Pressure
	public final static int NLS_NOM_VENT_TIME_PD_PPV = 0x00025360;
	public final static short NOM_VENT_TIME_PD_PPV = (short)0x5360;
	// RRsync Sync Breath Rate
	public final static int NLS_NOM_RESP_BREATH_ASSIST_CNT = 0x0002F89A;
	public final static short NOM_RESP_BREATH_ASSIST_CNT = (short)0xF89A;
	// fgDES fresh gas agent for DESflurane
	public final static int NLS_NOM_FLOW_AWAY_DESFL = 0x0002F878;
	//public final static short NOM_CONC_AWAY_DESFL = (short)0x51D8;
	// fgSEV fresh gas agent for SEVoflurane
	public final static int NLS_NOM_FLOW_AWAY_SEVOFL = 0x0002F880;
	//public final static short NOM_CONC_AWAY_SEVOFL = (short)0x51E4;
	// fgHAL fresh gas agent for HALothane
	public final static int NLS_NOM_FLOW_AWAY_HALOTH = 0x0002F87B;
	//public final static short NOM_CONC_AWAY_HALOTH = (short)0x51E0;
	// fgENF fresh gas agent for ENFlurane
	public final static int NLS_NOM_FLOW_AWAY_ENFL = 0x0002F879;
	//public final static short NOM_CONC_AWAY_ENFL = (short)0x51DC;
	// fgISO fresh gas agent for ISOflurane
	public final static int NLS_NOM_FLOW_AWAY_ISOFL = 0x0002F87C;
	//public final static short NOM_CONC_AWAY_ISOFL = (short)0x51E8;
	// fgN2O N2O concentration in the fresh gas line
	public final static int NLS_NOM_FLOW_AWAY_N2O = 0x0002F87E;
	//public final static short NOM_CONC_AWAY_N2O = (short)0x51F0;
	// fgO2 Oxygen concentration in the fresh gas line
	public final static int NLS_NOM_FLOW_AWAY_O2 = 0x0002F87F;
	//public final static short NOM_CONC_AWAY_O2 = (short)0x5164;
	// fgAir Fresh Gas Flow of Air
	public final static int NLS_NOM_FLOW_AWAY_AIR = 0x0002F877;
	public final static short NOM_FLOW_AWAY_AIR = (short)0xF877;
	// fgFlow Total Fresh Gas Flow
	public final static int NLS_NOM_FLOW_AWAY_TOT = 0x0002F881;
	public final static short NOM_FLOW_AWAY_TOT = (short)0xF881;
	// AGTLev Liquid level in the anesthetic agent bottle
	public final static int NLS_NOM_VOL_LVL_LIQUID_BOTTLE_AGENT = 0x0002F8C7;
	public final static short NOM_VOL_LVL_LIQUID_BOTTLE_AGENT = (short)0xF8C7;
	// ISOLev Liquid level in the ISOflurane bottle
	public final static int NLS_NOM_VOL_LVL_LIQUID_BOTTLE_ISOFL = 0x0002F8CB;
	public final static short NOM_VOL_LVL_LIQUID_BOTTLE_ISOFL = (short)0xF8CB;
	// ENFLev Liquid level in the ENFlurane bottle
	public final static int NLS_NOM_VOL_LVL_LIQUID_BOTTLE_ENFL = 0x0002F8C9;
	public final static short NOM_VOL_LVL_LIQUID_BOTTLE_ENFL = (short)0xF8C9;
	// HALLev Liquid level in the HALothane bottle
	public final static int NLS_NOM_VOL_LVL_LIQUID_BOTTLE_HALOTH = 0x0002F8CA;
	public final static short NOM_VOL_LVL_LIQUID_BOTTLE_HALOTH = (short)0xF8CA;
	// DESLev Liquid level in the DESflurane bottle
	public final static int NLS_NOM_VOL_LVL_LIQUID_BOTTLE_DESFL = 0x0002F8C8;
	public final static short NOM_VOL_LVL_LIQUID_BOTTLE_DESFL = (short)0xF8C8;
	// SEVLev Liquid level in the SEVoflurane bottle
	public final static int NLS_NOM_VOL_LVL_LIQUID_BOTTLE_SEVOFL = 0x0002F8CC;
	public final static short NOM_VOL_LVL_LIQUID_BOTTLE_SEVOFL = (short)0xF8CC;
	// UrVSht Urimeter - Urine Shift Volume.
	public final static int NLS_NOM_VOL_URINE_SHIFT = 0x0002F8CF;
	public final static short NOM_VOL_URINE_SHIFT = (short)0xF8CF;
	// UrFl Urimeter - Urine Flow.
	public final static int NLS_NOM_FLOW_URINE_INSTANT = 0x0002680C;
	public final static short NOM_FLOW_URINE_INSTANT = (short)0x680C;
	// iCa ionized Calcium
	public final static int NLS_NOM_CONC_CA_GEN = 0x00027118;
	public final static short NOM_CONC_CA_GEN = (short)0x7118;
	// 'Hb Calculated Hemoglobin
	public final static int NLS_NOM_CONC_HB_ART_CALC = 0x0002F82B;
	//public final static short NOM_CONC_HB_ART = (short)0x7014;
	// pHc pH value in the capillaries
	public final static int NLS_NOM_CONC_PH_CAP = 0x0002F158;
	public final static short NOM_CONC_PH_CAP = (short)0xF158;
	// &pH Adjusted pH at &Patient Temperature
	public final static int NLS_NOM_CONC_PH_GEN_ADJ = 0x0002F838;
	public final static short NOM_CONC_PH_GEN_ADJ = (short)0xF838;
	// &pHa Adjusted pH in the arterial Blood
	public final static int NLS_NOM_CONC_PH_ART_ADJ = 0x0002F836;
	//public final static short NOM_CONC_PH_ART = (short)0x7004;
	// &pHv Adjusted pH value in the venous Blood
	public final static int NLS_NOM_CONC_PH_VEN_ADJ = 0x0002F839;
	//public final static short NOM_CONC_PH_VEN = (short)0x7034;
	// &pHc Adjusted pH value in the capillaries
	public final static int NLS_NOM_CONC_PH_CAP_ADJ = 0x0002F837;
	public final static short NOM_CONC_PH_CAP_ADJ = (short)0xF837;
	// PcO2 Partial O2 in the capillaries
	public final static int NLS_NOM_CONC_PO2_CAP = 0x0002F15A;
	public final static short NOM_CONC_PO2_CAP = (short)0xF15A;
	public final static int NLS_NOM_CONC_PO2_GEN_ADJ = 0x0002F83D;
	//public final static short NOM_CONC_PO2_GEN = (short)0x7174;
	// &PaO2 Adjusted PaO2 at Patient Temperature on the arterial blood
	public final static int NLS_NOM_CONC_PO2_ART_ADJ = 0x0002F83B;
	public final static short NOM_CONC_PO2_ART_ADJ = (short)0xF83B;
	// &PvO2 Adjusted PvO2 at Patient Temperature
	public final static int NLS_NOM_CONC_PO2_VEN_ADJ = 0x0002F83E;
	//public final static short NOM_CONC_PO2_VEN = (short)0x703C;
	// &PcO2 Adjusted PcO2 at Patient Temperature
	public final static int NLS_NOM_CONC_PO2_CAP_ADJ = 0x0002F83C;
	public final static short NOM_CONC_PO2_CAP_ADJ = (short)0xF83C;
	// PcCO2 Partial CO2 in the capillaries
	public final static int NLS_NOM_CONC_PCO2_CAP = 0x0002F159;
	public final static short NOM_CONC_PCO2_CAP = (short)0xF159;
	// &PCO2 Computed PCO2 at Patient Temperature
	public final static int NLS_NOM_CONC_PCO2_GEN_ADJ = 0x0002F834;
	//public final static short NOM_CONC_PCO2_GEN = (short)0x7140;
	// &PaCO2 Computed PaCO2 at Patient Temperature on the arterial blood
	public final static int NLS_NOM_CONC_PCO2_ART_ADJ = 0x0002F832;
	public final static short NOM_CONC_PCO2_ART_ADJ = (short)0xF832;
	// &PvCO2 Computed PvCO2 at Patient Temperature
	public final static int NLS_NOM_CONC_PCO2_VEN_ADJ = 0x0002F835;
	//public final static short NOM_CONC_PCO2_VEN = (short)0x7038;
	// &PcCO2 Computed PcO2 at Patient Temperature
	public final static int NLS_NOM_CONC_PCO2_CAP_ADJ = 0x0002F833;
	public final static short NOM_CONC_PCO2_CAP_ADJ = (short)0xF833;
	// 'tCO2 Calculated total CO2
	public final static int NLS_NOM_CONC_CO2_TOT_CALC = 0x0002F826;
	public final static short NOM_CONC_CO2_TOT_CALC = (short)0xF826;
	// 'SO2 Calculated SO2
	public final static int NLS_NOM_SAT_O2_CALC = 0x0002F89C;
	//public final static short NOM_SAT_O2_ART = (short)0x4B34;
	// 'SaO2 Calculated SaO2
	public final static int NLS_NOM_SAT_O2_ART_CALC = 0x0002F164;
	public final static short NOM_SAT_O2_ART_CALC = (short)0xF164;
	// 'SvO2 Calculated SvO2
	public final static int NLS_NOM_SAT_O2_VEN_CALC = 0x0002F166;
	//public final static short NOM_SAT_O2_VEN = (short)0x4B3C;
	// 'ScO2 Calculated ScO2
	public final static int NLS_NOM_SAT_O2_CAP_CALC = 0x0002F1A0;
	public final static short NOM_SAT_O2_CAP_CALC = (short)0xF1A0;
	// 'HCO3 Calculated HCO3
	public final static int NLS_NOM_CONC_HCO3_GEN_CALC = 0x0002F82E;
	//public final static short NOM_CONC_HCO3_GEN = (short)0x7108;
	// 'BEecf Calculated Base Excess
	public final static int NLS_NOM_CONC_BASE_EXCESS_ECF_CALC = 0x0002F821;
	//public final static short NOM_CONC_BASE_EXCESS_ECF = (short)0xF090;
	// 'AnGap Calculated AnionGap
	public final static int NLS_NOM_CONC_AN_GAP_CALC = 0x0002F1A1;
	public final static short NOM_CONC_AN_GAP_CALC = (short)0xF1A1;
	// Urea Urea used by the i-Stat
	public final static int NLS_NOM_CONC_UREA_GEN = 0x0002F172;
	public final static short NOM_CONC_UREA_GEN = (short)0xF172;
	// 'BE,B Calculated Base Excess in Blood
	public final static int NLS_NOM_BASE_EXCESS_BLD_ART_CALC = 0x0002F817;
	//public final static short NOM_BASE_EXCESS_BLD_ART = (short)0x716C;
	// iMg ionized Magnesium
	public final static int NLS_NOM_CONC_MG_ION = 0x0002F15B;
	public final static short NOM_CONC_MG_ION = (short)0xF15B;
	// Crea Creatinine - Measured Value by the i-Stat Module
	public final static int NLS_NOM_CONC_CREA = 0x0002F173;
	public final static short NOM_CONC_CREA = (short)0xF173;
	// 'B/Cre Ratio BUN/Creatinine. Calculated value by the i-Stat module
	public final static int NLS_NOM_RATIO_CONC_BLD_UREA_NITROGEN_CREA_CALC = 0x0002F890;
	public final static short NOM_RATIO_CONC_BLD_UREA_NITROGEN_CREA_CALC = (short)0xF890;
	// 'U/Cre Ratio Urea/Creatinine. Calculated value by the i-Stat module
	public final static int NLS_NOM_RATIO_CONC_URINE_CREA_CALC = 0x0002F891;
	public final static short NOM_RATIO_CONC_URINE_CREA_CALC = (short)0xF891;
	// Lact Lactate. SMeasured value by the i-Stat module
	public final static int NLS_NOM_CONC_LACT = 0x0002F174;
	public final static short NOM_CONC_LACT = (short)0xF174;
	// Elapse Time to Elapse Counter
	public final static int NLS_NOM_TIME_PD_FROM_LAST_MSMT = 0x0002F8A2;
	public final static short NOM_TIME_PD_FROM_LAST_MSMT = (short)0xF8A2;
	public final static short NOM_DIM_SEC = (short)0x0880;
	// Air T Air Temperature in the Incubator
	public final static int NLS_NOM_TEMP_AIR_INCUB = 0x0002F12A;
	public final static short NOM_TEMP_AIR_INCUB = (short)0xF12A;
	// 161
	public final static int NLS_NOM_HUMID = 0x0002F103;
	public final static short NOM_HUMID = (short)0xF103;
	// Power Power requ'd to set the Air&Pat Temp in the incubator
	public final static int NLS_NOM_HEATING_PWR_INCUBATOR = 0x0002F886;
	public final static short NOM_HEATING_PWR_INCUBATOR = (short)0xF886;
	// BagWgt Weight of the Urine Disposable Bag
	public final static int NLS_NOM_WEIGHT_URINE_COL = 0x0002F8D3;
	public final static short NOM_WEIGHT_URINE_COL = (short)0xF8D3;
	// tUrVol Total Urine Volume of the current measurement period
	public final static int NLS_NOM_VOL_URINE_BAL_PD_INSTANT = 0x0002F8CE;
	public final static short NOM_VOL_URINE_BAL_PD_INSTANT = (short)0xF8CE;
	// UrDens Density of the Urine fluid
	public final static int NLS_NOM_FLUID_DENS_URINE = 0x0002F19D;
	public final static short NOM_FLUID_DENS_URINE = (short)0xF19D;
	// Age actual patient age. measured in years
	public final static int NLS_NOM_AGE = 0x0002F810;
	public final static short NOM_AGE = (short)0xF810;
	// U/O Daily Urine output
	public final static int NLS_NOM_FLOW_URINE_PREV_24HR = 0x0002F883;
	public final static short NOM_FLOW_URINE_PREV_24HR = (short)0xF883;
	// BagVol Current fluid (Urine) in the Urine Bag
	public final static int NLS_NOM_VOL_URINE_COL = 0x00026830;
	public final static short NOM_VOL_URINE_COL = (short)0x6830;
	// PtVent Parameter which informs whether the Patient is ventilated
	public final static int NLS_NOM_VENT_ACTIVE = 0x0002F8B0;
	public final static short NOM_VENT_ACTIVE = (short)0xF8B0;
	// PaFIO2 PaO2 to FIO2 ratio. Expressed in mmHg to % ratio
	public final static int NLS_NOM_RATIO_PaO2_FIO2 = 0x0002F894;
	public final static short NOM_RATIO_PaO2_FIO2 = (short)0xF894;
	// SpRR Spontaneous Respiration Rate
	public final static int NLS_NOM_RESP_RATE_SPONT = 0x0002F828;
	public final static short NOM_RESP_RATE_SPONT = (short)0xF828;
	// MRR Mandatory Respiratory Rate
	public final static int NLS_NOM_VENT_RESP_RATE_MAND = 0x0002F0F1;
	public final static short NOM_VENT_RESP_RATE_MAND = (short)0xF0F1;
	// inAGTs Inspired secondary Anesthetic Agent
	public final static int NLS_NOM_CONC_AWAY_AGENT_INSP_SEC = 0x0002F81F;
	//public final static short NOM_CONC_AWAY_AGENT_INSP = (short)0x5390;
	// etAGTs EndTidal secondary Anesthetic Agent
	public final static int NLS_NOM_CONC_AWAY_AGENT_ET_SEC = 0x0002F81E;
	//public final static short NOM_CONC_AWAY_AGENT_ET = (short)0x538C;
	// TOFcnt Train Of Four (TOF) count - Number of TOF responses.
	public final static int NLS_NOM_TRAIN_OF_FOUR_CNT = 0x0002F8AB;
	public final static short NOM_TRAIN_OF_FOUR_CNT = (short)0xF8AB;
	// TOFrat Train Of Four (TOF) ratio
	public final static int NLS_NOM_RATIO_TRAIN_OF_FOUR = 0x0002F897;
	public final static short NOM_RATIO_TRAIN_OF_FOUR = (short)0xF897;
	// Twitch Twitch height of the 1Hz/0.1Hz stimulation response
	public final static int NLS_NOM_TWITCH_AMPL = 0x0002F8AC;
	public final static short NOM_TWITCH_AMPL = (short)0xF8AC;
	// PTC Post Tetatic Count stimulation
	public final static int NLS_NOM_PTC_CNT = 0x0002F88B;
	public final static short NOM_PTC_CNT = (short)0xF88B;
	// RemTi Remaining Time until next stimulation
	public final static int NLS_NOM_TIME_PD_EVOK_REMAIN = 0x0002F8A0;
	public final static short NOM_TIME_PD_EVOK_REMAIN = (short)0xF8A0;
	// TOF1 TrainOf Four (TOF) first response value TOF1
	public final static int NLS_NOM_TRAIN_OF_FOUR_1 = 0x0002F8A7;
	public final static short NOM_TRAIN_OF_FOUR_1 = (short)0xF8A7;
	// TOF2 TrainOf Four (TOF) first response value TOF2
	public final static int NLS_NOM_TRAIN_OF_FOUR_2 = 0x0002F8A8;
	public final static short NOM_TRAIN_OF_FOUR_2 = (short)0xF8A8;
	// TOF3 TrainOf Four (TOF) first response value TOF3
	public final static int NLS_NOM_TRAIN_OF_FOUR_3 = 0x0002F8A9;
	public final static short NOM_TRAIN_OF_FOUR_3 = (short)0xF8A9;
	// TOF4 TrainOf Four (TOF) first response value TOF4
	public final static int NLS_NOM_TRAIN_OF_FOUR_4 = 0x0002F8AA;
	public final static short NOM_TRAIN_OF_FOUR_4 = (short)0xF8AA;
	// sRepTi Setting: Preset Train Of Four (Slow TOF) repetition time
	public final static int NLS_NOM_SETT_TIME_PD_TRAIN_OF_FOUR = 0x0402F8A6;
	public final static short NOM_SETT_TIME_PD_TRAIN_OF_FOUR = (short)0xF8A6;
	// ACT Activated Clotting Time. Measured value by the i-Stat module
	public final static int NLS_NOM_TIME_PD_ACT = 0x0002F18A;
	public final static short NOM_TIME_PD_ACT = (short)0xF18A;
	// aPTTWB aPTT Whole Blood
	public final static int NLS_NOM_TIME_PD_aPTT_WB = 0x0002F18D;
	public final static short NOM_TIME_PD_aPTT_WB = (short)0xF18D;
	//public final static short NOM_DIM_SEC = (short)0x0880;
	// aPTTPE aPTT Plasma Equivalent Time
	public final static int NLS_NOM_TIME_PD_aPTT_PE = 0x0002F18E;
	public final static short NOM_TIME_PD_aPTT_PE = (short)0xF18E;
	//public final static short NOM_DIM_SEC = (short)0x0880;
	// PTTrat Activated Partial Thromboplastin Time Ratio
	public final static int NLS_NOM_RATIO_TIME_PD_PTT = 0x0002F896;
	public final static short NOM_RATIO_TIME_PD_PTT = (short)0xF896;
	// PT WB Prothrombin Time (Blood)
	public final static int NLS_NOM_TIME_PD_PT_WB = 0x0002F18F;
	public final static short NOM_TIME_PD_PT_WB = (short)0xF18F;
	//public final static short NOM_DIM_SEC = (short)0x0880;
	// PT PE Prothrombin Time (Plasma)
	public final static int NLS_NOM_TIME_PD_PT_PE = 0x0002F190;
	public final static short NOM_TIME_PD_PT_PE = (short)0xF190;
	//public final static short NOM_DIM_SEC = (short)0x0880;
	// PTrat Prothrombin Time Ratio
	public final static int NLS_NOM_RATIO_TIME_PD_PT = 0x0002F895;
	public final static short NOM_RATIO_TIME_PD_PT = (short)0xF895;
	// PT INR Prothrombin Time - International Normalized Ratio
	public final static int NLS_NOM_PT_INTL_NORM_RATIO = 0x0002F18C;
	public final static short NOM_PT_INTL_NORM_RATIO = (short)0xF18C;
	// cTnI Cardiac Troponin I
	public final static int NLS_NOM_CARDIAC_TROPONIN_I = 0x0002F0F4;
	public final static short NOM_CARDIAC_TROPONIN_I = (short)0xF0F4;
	// CPB Cardio Pulmonary Bypass Flag
	public final static int NLS_NOM_CARDIO_PULMONARY_BYPASS_MODE = 0x0002F0F5;
	public final static short NOM_CARDIO_PULMONARY_BYPASS_MODE = (short)0xF0F5;
	// BNP Cardiac Brain Natriuretic Peptide
	public final static int NLS_NOM_BNP = 0x0002F0F6;
	public final static short NOM_BNP = (short)0xF0F6;
	// InsTi Spontaneous Inspiration Time
	public final static int NLS_NOM_TIME_PD_INSP = 0x0002F8A3;
	public final static short NOM_TIME_PD_INSP = (short)0xF8A3;
	// C20/C Overdistension Index
	public final static int NLS_NOM_C20_PER_C_INDEX = 0x0002F81A;
	public final static short NOM_C20_PER_C_INDEX = (short)0xF81A;
	// TC Time Constant
	public final static int NLS_NOM_AWAY_TC = 0x0002F816;
	public final static short NOM_AWAY_TC = (short)0xF816;
	// r Correlation Coefficient
	public final static int NLS_NOM_AWAY_CORR_COEF = 0x0002F814;
	public final static short NOM_AWAY_CORR_COEF = (short)0xF814;
	// RVrat Rate Volume Ratio
	public final static int NLS_NOM_RATIO_AWAY_RATE_VOL_AWAY = 0x0002F88E;
	public final static short NOM_RATIO_AWAY_RATE_VOL_AWAY = (short)0xF88E;
	// iCa(N) ionized Calcium Normalized
	public final static int NLS_NOM_CONC_CA_GEN_NORM = 0x0002F822;
	public final static short NOM_CONC_CA_GEN_NORM = (short)0xF822;
	// TVPSV Tidal Volume (TV) in Pressure Support Ventilation mode
	public final static int NLS_NOM_VOL_AWAY_TIDAL_PSV = 0x0002F8C3;
	public final static short NOM_VOL_AWAY_TIDAL_PSV = (short)0xF8C3;
	// RSBI Rapid Shallow Breathing Index
	public final static int NLS_NOM_BREATH_RAPID_SHALLOW_INDEX = 0x0002F819;
	public final static short NOM_BREATH_RAPID_SHALLOW_INDEX = (short)0xF819;
	// sAWRR Setting: Airway Respiratory Rate
	public final static int NLS_NOM_SETT_AWAY_RESP_RATE = 0x04025012;
	//public final static short NOM_AWAY_RESP_RATE = (short)0x5012;
	// sTV Setting: Tidal Volume
	public final static int NLS_NOM_SETT_VOL_AWAY_TIDAL = 0x0402513C;
	//public final static short NOM_VOL_AWAY_TIDAL = (short)0x513C;
	// sPIF Setting: Peak Inspiratory Flow
	public final static int NLS_NOM_SETT_FLOW_AWAY_INSP_MAX = 0x040250DD;
	//public final static short NOM_PRESS_AWAY_INSP_MAX = (short)0x5109;
	// sFIO2 Setting: Inspired Oxygen Concentration
	public final static int NLS_NOM_SETT_VENT_CONC_AWAY_O2_INSP = 0x04027498;
	//public final static short NOM_VENT_CONC_AWAY_O2_INSP = (short)0x7498;
	// sPltTi Setting: Plateau Time
	public final static int NLS_NOM_SETT_TIME_PD_RESP_PLAT = 0x0402F0FF;
	public final static short NOM_SETT_TIME_PD_RESP_PLAT = (short)0xF0FF;
	// sSghR Setting: Sigh Rate
	public final static int NLS_NOM_SETT_VENT_SIGH_RATE = 0x0402F93C;
	public final static short NOM_SETT_VENT_SIGH_RATE = (short)0xF93C;
	// sSghTV Setting: Sigh Tidal Volume
	public final static int NLS_NOM_SETT_VENT_VOL_TIDAL_SIGH = 0x0402F8C0;
	public final static short NOM_SETT_VENT_VOL_TIDAL_SIGH = (short)0xF8C0;
	// sSghNr Setting: Multiple Sigh Number
	public final static int NLS_NOM_SETT_VENT_SIGH_MULT_RATE = 0x0402F93B;
	public final static short NOM_SETT_VENT_SIGH_MULT_RATE = (short)0xF93B;
	// sATV Setting: Apnea Tidal Volume
	public final static int NLS_NOM_SETT_VOL_AWAY_TIDAL_APNEA = 0x0402F951;
	public final static short NOM_SETT_VOL_AWAY_TIDAL_APNEA = (short)0xF951;
	// sARR Setting: Apnea Respiration Rate
	public final static int NLS_NOM_SETT_AWAY_RESP_RATE_APNEA = 0x0402F8DE;
	public final static short NOM_SETT_AWAY_RESP_RATE_APNEA = (short)0xF8DE;
	// sAPkFl Setting: Apnea Peak Flow
	public final static int NLS_NOM_SETT_FLOW_AWAY_INSP_APNEA = 0x0402F8ED;
	public final static short NOM_SETT_FLOW_AWAY_INSP_APNEA = (short)0xF8ED;
	// sAFIO2 Setting: Apnea Inspired O2 Concentration
	public final static int NLS_NOM_SETT_VENT_CONC_AWAY_O2_INSP_APNEA = 0x0402F917;
	public final static short NOM_SETT_VENT_CONC_AWAY_O2_INSP_APNEA = (short)0xF917;
	// sPSV Setting: Pressure Support Ventilation
	public final static int NLS_NOM_SETT_VENT_PRESS_AWAY_PV = 0x0402F8BC;
	public final static short NOM_SETT_VENT_PRESS_AWAY_PV = (short)0xF8BC;
	// sEnSgh Setting: Enable Sigh
	public final static int NLS_NOM_SETT_VENT_MODE_SIGH = 0x0402F923;
	public final static short NOM_SETT_VENT_MODE_SIGH = (short)0xF923;
	// sO2Suc Setting: Suction Oxygen Concentration
	public final static int NLS_NOM_SETT_VENT_O2_SUCTION_MODE = 0x0402F928;
	public final static short NOM_SETT_VENT_O2_SUCTION_MODE = (short)0xF928;
	// sBasFl Setting: Flow-by Base Flow
	public final static int NLS_NOM_SETT_VENT_AWAY_FLOW_BASE = 0x0402F910;
	public final static short NOM_SETT_VENT_AWAY_FLOW_BASE = (short)0xF910;
	// sSenFl Setting: Flow-by Sensitivity Flow
	public final static int NLS_NOM_SETT_VENT_AWAY_FLOW_SENSE = 0x0402F911;
	public final static short NOM_SETT_VENT_AWAY_FLOW_SENSE = (short)0xF911;
	// sPVinT Setting: Pressure Ventilation Inspiratory Time
	public final static int NLS_NOM_SETT_VENT_TIME_PD_INSP_PV = 0x0402F943;
	public final static short NOM_SETT_VENT_TIME_PD_INSP_PV = (short)0xF943;
	// sAPVcP Setting: Apnea Pressure Ventilation Control Pressure
	public final static int NLS_NOM_SETT_VENT_PRESS_AWAY_PV_APNEA = 0x0402F933;
	public final static short NOM_SETT_VENT_PRESS_AWAY_PV_APNEA = (short)0xF933;
	// sAPVRR Setting: Apnea Pressure Ventilation Respiration Rate
	public final static int NLS_NOM_SETT_VENT_RESP_RATE_PV_APNEA = 0x0402F93A;
	public final static short NOM_SETT_VENT_RESP_RATE_PV_APNEA = (short)0xF93A;
	// sAPVTi Setting: Apnea Pressure Ventilation Inspiratory Time
	public final static int NLS_NOM_SETT_VENT_TIME_PD_INSP_PV_APNEA = 0x0402F944;
	public final static short NOM_SETT_VENT_TIME_PD_INSP_PV_APNEA = (short)0xF944;
	// sAPVO2 Setting: Apnea Pressure Ventilation Oxygen Concentration
	public final static int NLS_NOM_SETT_VENT_CONC_AWAY_O2_INSP_PV_APNEA = 0x0402F918;
	public final static short NOM_SETT_VENT_CONC_AWAY_O2_INSP_PV_APNEA = (short)0xF918;
	// sAPVhP Setting: Apnea Pressure Ventilation High Airway Pressure
	public final static int NLS_NOM_SETT_VENT_PRESS_AWAY_MAX_PV_APNEA = 0x0402F931;
	public final static short NOM_SETT_VENT_PRESS_AWAY_MAX_PV_APNEA = (short)0xF931;
	// sPVI Setting: Pressure Ventilation I component of I:E Ratio
	public final static int NLS_NOM_SETT_RATIO_IE_INSP_PV = 0x0402F902;
	public final static short NOM_SETT_RATIO_IE_INSP_PV = (short)0xF902;
	// sPVE Setting: Pressure Ventilation E component of I:E Ratio
	public final static int NLS_NOM_SETT_RATIO_IE_EXP_PV = 0x0402F900;
	public final static short NOM_SETT_RATIO_IE_EXP_PV = (short)0xF900;
	// sAPVI Setting: Apnea Pressure Ventilation I component of I:E Ratio
	public final static int NLS_NOM_SETT_RATIO_IE_INSP_PV_APNEA = 0x0402F903;
	public final static short NOM_SETT_RATIO_IE_INSP_PV_APNEA = (short)0xF903;
	// sAPVE Setting: Apnea Pressure Ventilation E component of I:E Ratio
	public final static int NLS_NOM_SETT_RATIO_IE_EXP_PV_APNEA = 0x0402F901;
	public final static short NOM_SETT_RATIO_IE_EXP_PV_APNEA = (short)0xF901;
	// sCycTi Setting: Cycle Time
	public final static int NLS_NOM_SETT_TIME_PD_MSMT = 0x0402F909;
	public final static short NOM_SETT_TIME_PD_MSMT = (short)0xF909;
	// sIPPV Setting: Ventilation Frequency in IPPV Mode
	public final static int NLS_NOM_SETT_VENT_RESP_RATE_MODE_PPV_INTERMIT_PAP = 0x0402F939;
	public final static short NOM_SETT_VENT_RESP_RATE_MODE_PPV_INTERMIT_PAP = (short)0xF939;
	// sIMV Setting: Ventilation Frequency in IMV Mode
	public final static int NLS_NOM_SETT_VENT_RESP_RATE_MODE_MAND_INTERMITT = 0x0402F938;
	//public final static short NOM_VENT_MODE_MAND_INTERMIT = (short)0xD02A;
	// sPEEP Setting: PEEP/CPAP
	public final static int NLS_NOM_SETT_VENT_PRESS_AWAY_END_EXP_POS = 0x040251A8;
	//public final static short NOM_VENT_PRESS_AWAY_END_EXP_POS = (short)0x51A8;
	// sSPEEP Setting: Pressure Support PEEP
	public final static int NLS_NOM_SETT_VENT_PRESS_AWAY_END_EXP_POS_INTERMIT = 0x0402F92C;
	public final static short NOM_SETT_VENT_PRESS_AWAY_END_EXP_POS_INTERMIT = (short)0xF92C;
	// sMV Setting: Minute Volume
	public final static int NLS_NOM_SETT_VOL_MINUTE_AWAY = 0x04025148;
	//public final static short NOM_VOL_MINUTE_AWAY = (short)0x5148;
	// sO2Mon Setting: O2 Monitoring
	public final static int NLS_NOM_SETT_VENT_ANALY_CONC_GAS_O2_MODE = 0x0402F90E;
	public final static short NOM_SETT_VENT_ANALY_CONC_GAS_O2_MODE = (short)0xF90E;
	// sO2Cal Setting: O2 Calibration
	public final static int NLS_NOM_SETT_VENT_O2_CAL_MODE = 0x0402F926;
	public final static short NOM_SETT_VENT_O2_CAL_MODE = (short)0xF926;
	// sPmax Setting: Maximum Pressure
	public final static int NLS_NOM_SETT_VENT_PRESS_AWAY_INSP_MAX = 0x0402F8BB;
	//public final static short NOM_PRESS_AWAY_INSP_MAX = (short)0x5109;
	// sInsTi Setting: Inspiratory Time
	public final static int NLS_NOM_SETT_VENT_TIME_PD_INSP = 0x0402F941;
	public final static short NOM_SETT_VENT_TIME_PD_INSP = (short)0xF941;
	// sExpTi Setting: Exhaled Time
	public final static int NLS_NOM_SETT_VENT_TIME_PD_EXP = 0x0402F93F;
	public final static short NOM_SETT_VENT_TIME_PD_EXP = (short)0xF93F;
	// sIE 1: Setting: Inspiration to Expiration Ratio.
	public final static int NLS_NOM_SETT_RATIO_IE = 0x04025118;
	//public final static short NOM_RATIO_IE = (short)0x5118;
	// sALMRT Setting: Alarm Percentage on Rise Time.
	public final static int NLS_NOM_SETT_VENT_TIME_PD_RAMP_AL = 0x0402F946;
	public final static short NOM_SETT_VENT_TIME_PD_RAMP_AL = (short)0xF946;
	// sCPAP Setting: Continuous Positive Airway Pressure Value
	public final static int NLS_NOM_SETT_PRESS_AWAY_CTS_POS = 0x040250F4;
	//public final static short NOM_PRESS_AWAY_CTS_POS = (short)0x50F4;
	// sFlow Setting: Flow
	public final static int NLS_NOM_SETT_VENT_FLOW = 0x0402F91B;
	public final static short NOM_SETT_VENT_FLOW = (short)0xF91B;
	// sPIP Setting: Positive Inspiratory Pressure
	public final static int NLS_NOM_SETT_PRESS_AWAY_INSP_MAX = 0x04025109;
	//public final static short NOM_PRESS_AWAY_INSP_MAX = (short)0x5109;
	// sPmin Setting: Low Inspiratory Pressure
	public final static int NLS_NOM_SETT_PRESS_AWAY_MIN = 0x040250F2;
	public final static short NOM_SETT_PRESS_AWAY_MIN = (short)0x50F2;
	// sHFVFl Setting: High Freqyency Ventilation Flow
	public final static int NLS_NOM_SETT_FLOW_AWAY_HFV = 0x0402F8EB;
	public final static short NOM_SETT_FLOW_AWAY_HFV = (short)0xF8EB;
	// sHFVRR Setting: High Frequency Ventilation Respiration Rate
	public final static int NLS_NOM_SETT_AWAY_RESP_RATE_HFV = 0x0402F8DF;
	public final static short NOM_SETT_AWAY_RESP_RATE_HFV = (short)0xF8DF;
	// sO2 Enumeration Type - denotes type of Instrument.
	public final static int NLS_NOM_SETT_CONC_AWAY_O2 = 0x04025164;
	//public final static short NOM_CONC_AWAY_O2 = (short)0x5164;
	// sCMV Setting: Controlled mechanical ventilation
	public final static int NLS_NOM_SETT_VENT_MODE_MAND_CTS_ONOFF = 0x0402F922;
	public final static short NOM_SETT_VENT_MODE_MAND_CTS_ONOFF = (short)0xF922;
	// sSIMV Setting: Synchronized intermittent mandatory ventilation
	public final static int NLS_NOM_SETT_VENT_MODE_SYNC_MAND_INTERMIT = 0x0402F924;
	public final static short NOM_SETT_VENT_MODE_SYNC_MAND_INTERMIT = (short)0xF924;
	// sMMV Setting: Mandatory Minute Volume
	public final static int NLS_NOM_SETT_VENT_VOL_MINUTE_AWAY_MAND = 0x040251CC;
	public final static short NOM_SETT_VENT_VOL_MINUTE_AWAY_MAND = (short)0x51CC;
	// sDRate Setting: Infusion Pump Delivery Rate
	public final static int NLS_NOM_SETT_FLOW_FLUID_PUMP = 0x04026858;
	public final static short NOM_SETT_FLOW_FLUID_PUMP = (short)0x6858;
	// sPin Setting: Pressure Ventilation Control Pressure
	public final static int NLS_NOM_SETT_PRESS_AWAY_INSP = 0x04025108;
	public final static short NOM_SETT_PRESS_AWAY_INSP = (short)0x5108;
	// sRRaw Setting: Airway Respiration Rate. Used by the Ohmeda Ventilator.
	public final static int NLS_NOM_SETT_VENT_RESP_RATE = 0x04025022;
	//public final static short NOM_AWAY_RESP_RATE = (short)0x5012;
	// sInsFl Setting: Inspiratory Flow.
	public final static int NLS_NOM_SETT_FLOW_AWAY_INSP = 0x0402F8EC;
	public final static short NOM_SETT_FLOW_AWAY_INSP = (short)0xF8EC;
	// sExpFl Setting: Expiratory Flow
	public final static int NLS_NOM_SETT_FLOW_AWAY_EXP = 0x0402F8EA;
	public final static short NOM_SETT_FLOW_AWAY_EXP = (short)0xF8EA;
	// sTrVol Setting: Trigger Flow/Volume
	public final static int NLS_NOM_SETT_VENT_VOL_LUNG_TRAPD = 0x040251B8;
	public final static short NOM_SETT_VENT_VOL_LUNG_TRAPD = (short)0x51B8;
	// sAADel Setting: Apnea Ventilation Delay
	public final static int NLS_NOM_SETT_APNEA_ALARM_DELAY = 0x0402F8D9;
	public final static short NOM_SETT_APNEA_ALARM_DELAY = (short)0xF8D9;
	// sHFVAm Setting: HFV Amplitude (Peak to Peak Pressure)
	public final static int NLS_NOM_SETT_HFV_AMPL = 0x0402F8F3;
	public final static short NOM_SETT_HFV_AMPL = (short)0xF8F3;
	// sMVDel Setting: Minute Volume Alarm Delay
	public final static int NLS_NOM_SETT_VOL_MINUTE_ALARM_DELAY = 0x0402F953;
	public final static short NOM_SETT_VOL_MINUTE_ALARM_DELAY = (short)0xF953;
	// sTrgFl Setting: Flow Trigger - delivered by the Evita 2 Vuelink Driver
	public final static int NLS_NOM_SETT_VENT_FLOW_INSP_TRIG = 0x0402F91D;
	public final static short NOM_SETT_VENT_FLOW_INSP_TRIG = (short)0xF91D;
	// sPincR Setting: Pressure Increase Rate
	public final static int NLS_NOM_SETT_VENT_AWAY_PRESS_RATE_INCREASE = 0x0402F912;
	public final static short NOM_SETT_VENT_AWAY_PRESS_RATE_INCREASE = (short)0xF912;
	// sVmax Setting: Volume Warning - delivered by the Evita 2 Vuelink Driver
	public final static int NLS_NOM_SETT_VENT_VOL_LIMIT_AL_HI_ONOFF = 0x0402F949;
	public final static short NOM_SETT_VENT_VOL_LIMIT_AL_HI_ONOFF = (short)0xF949;
	// loPmax Setting: Low Maximum Airway Pressure Alarm Setting.
	public final static int NLS_NOM_SETT_PRESS_AWAY_INSP_MAX_LIMIT_LO = 0x0402F8FB;
	public final static short NOM_SETT_PRESS_AWAY_INSP_MAX_LIMIT_LO = (short)0xF8FB;
	// sTVap Setting: Applied Tidal Volume.
	public final static int NLS_NOM_SETT_VOL_AWAY_TIDAL_APPLIED = 0x0402F952;
	public final static short NOM_SETT_VOL_AWAY_TIDAL_APPLIED = (short)0xF952;
	// sSens Setting: Assist Sensitivity. Used by the Bear 1000 ventilator.
	public final static int NLS_NOM_SETT_SENS_LEVEL = 0x0402F904;
	public final static short NOM_SETT_SENS_LEVEL = (short)0xF904;
	// sBkgFl Setting: Background Flow Setting. Range is 2 - 30 l/min
	public final static int NLS_NOM_SETT_VENT_AWAY_FLOW_BACKGROUND = 0x0402F90F;
	public final static short NOM_SETT_VENT_AWAY_FLOW_BACKGROUND = (short)0xF90F;
	// sAGT Setting: Vaporizer concentration.
	public final static int NLS_NOM_SETT_FLOW_AWAY_AGENT = 0x0402F876;
	//public final static short NOM_CONC_AWAY_AGENT = (short)0x5388;
	// sISO Setting: Vaporizer concentration for ISOflurane
	public final static int NLS_NOM_SETT_CONC_AWAY_ISOFL = 0x040251E8;
	//public final static short NOM_CONC_AWAY_ISOFL = (short)0x51E8;
	// sENF Setting: Vaporizer concentration for ENFlurane
	public final static int NLS_NOM_SETT_CONC_AWAY_ENFL = 0x040251DC;
	//public final static short NOM_CONC_AWAY_ENFL = (short)0x51DC;
	// sHAL Setting: Vaporizer concentration for HALothane
	public final static int NLS_NOM_SETT_CONC_AWAY_HALOTH = 0x040251E0;
	//public final static short NOM_CONC_AWAY_HALOTH = (short)0x51E0;
	// sDES Setting: Vaporizer concentration for DESflurane
	public final static int NLS_NOM_SETT_CONC_AWAY_DESFL = 0x040251D8;
	//public final static short NOM_CONC_AWAY_DESFL = (short)0x51D8;
	// sSEV Setting: Vaporizer concentration for SEVoflurane
	public final static int NLS_NOM_SETT_CONC_AWAY_SEVOFL = 0x040251E4;
	//public final static short NOM_CONC_AWAY_SEVOFL = (short)0x51E4;
	// sfgAir Setting: Total fresh gas Air flow on the mixer
	public final static int NLS_NOM_SETT_FLOW_AWAY_AIR = 0x0402F877;
	public final static short NOM_SETT_FLOW_AWAY_AIR = (short)0xF877;
	// sfgO2 Setting: Fresh gas oxygen Flow on the mixer
	public final static int NLS_NOM_SETT_FLOW_AWAY_O2 = 0x0402F87F;
	//public final static short NOM_CONC_AWAY_O2 = (short)0x5164;
	// sfgFl Setting: Total fresh gas Flow on the mixer
	public final static int NLS_NOM_SETT_FLOW_AWAY_TOT = 0x0402F881;
	public final static short NOM_SETT_FLOW_AWAY_TOT = (short)0xF881;
	// sfgN2O Setting: fresh gas N2O flow on the mixer
	public final static int NLS_NOM_SETT_FLOW_AWAY_N2O = 0x0402F87E;
	//public final static short NOM_CONC_AWAY_N2O = (short)0x51F0;
	// sGasPr Setting: Gas Sample point for the oxygen measurement
	public final static int NLS_NOM_SETT_VENT_GAS_PROBE_POSN = 0x0402F920;
	public final static short NOM_SETT_VENT_GAS_PROBE_POSN = (short)0xF920;
	// sO2Pr Setting: Gas sample point for oxygen measurement
	public final static int NLS_NOM_SETT_VENT_O2_PROBE_POSN = 0x0402F927;
	public final static short NOM_SETT_VENT_O2_PROBE_POSN = (short)0xF927;
	// sTVin Setting: inspired Tidal Volume
	public final static int NLS_NOM_SETT_VOL_AWAY_INSP_TIDAL = 0x0402F0E0;
	public final static short NOM_SETT_VOL_AWAY_INSP_TIDAL = (short)0xF0E0;
	// sTemp Desired Environmental Temperature
	public final static int NLS_NOM_SETT_TEMP = 0x04024B48;
	public final static short NOM_SETT_TEMP = (short)0x4B48;
	// sUrTi Setting: Preset period of time for the UrVol numeric
	public final static int NLS_NOM_SETT_URINE_BAL_PD = 0x0402F8AF;
	public final static short NOM_SETT_URINE_BAL_PD = (short)0xF8AF;
	// sTlow Setting: part of the Evita 4 Airway Pressure Release Ventilation Mode
	public final static int NLS_NOM_SETT_VENT_TIME_PD_EXP_APRV = 0x0402F940;
	public final static short NOM_SETT_VENT_TIME_PD_EXP_APRV = (short)0xF940;
	// sThigh Setting: part of the Evita 4 Airway Pressure Release Ventilation Mode
	public final static int NLS_NOM_SETT_VENT_TIME_PD_INSP_APRV = 0x0402F942;
	public final static short NOM_SETT_VENT_TIME_PD_INSP_APRV = (short)0xF942;
	// sPlow Setting: part of the Evita 4 Airway Pressure Release Ventilation Mode
	public final static int NLS_NOM_SETT_VENT_PRESS_AWAY_EXP_APRV = 0x0402F92D;
	public final static short NOM_SETT_VENT_PRESS_AWAY_EXP_APRV = (short)0xF92D;
	// sPhigh Setting: part of the Evita 4 Airway Pressure Release Ventilation Mode
	public final static int NLS_NOM_SETT_VENT_PRESS_AWAY_INSP_APRV = 0x0402F92E;
	public final static short NOM_SETT_VENT_PRESS_AWAY_INSP_APRV = (short)0xF92E;
	// sVolas Setting: Volume Assist level for the CPAP mode
	public final static int NLS_NOM_SETT_VENT_VOL_AWAY_ASSIST = 0x0402F948;
	public final static short NOM_SETT_VENT_VOL_AWAY_ASSIST = (short)0xF948;
	// sFlas Setting: Flow Assist level for the CPAP mode
	public final static int NLS_NOM_SETT_VENT_FLOW_AWAY_ASSIST = 0x0402F91C;
	public final static short NOM_SETT_VENT_FLOW_AWAY_ASSIST = (short)0xF91C;
	// sCurnt Setting: Preset stimulation current
	public final static int NLS_NOM_SETT_EVOK_CURR = 0x0402F8E7;
	public final static short NOM_SETT_EVOK_CURR = (short)0xF8E7;
	// sChrge Setting: Preset stimulation charge
	public final static int NLS_NOM_SETT_EVOK_CHARGE = 0x0402F8E6;
	public final static short NOM_SETT_EVOK_CHARGE = (short)0xF8E6;
	// sPulsD Setting: Preset stimulation impulse duration
	public final static int NLS_NOM_SETT_TIME_PD_EVOK = 0x0402F908;
	public final static short NOM_SETT_TIME_PD_EVOK = (short)0xF908;
	// sfmax Setting: Panting Limit
	public final static int NLS_NOM_SETT_VENT_RESP_RATE_LIMIT_HI_PANT = 0x0402F937;
	public final static short NOM_SETT_VENT_RESP_RATE_LIMIT_HI_PANT = (short)0xF937;
	// highP Alarm Limit: High Pressure
	public final static int NLS_NOM_SETT_VENT_PRESS_AWAY_LIMIT_HI = 0x0402F930;
	public final static short NOM_SETT_VENT_PRESS_AWAY_LIMIT_HI = (short)0xF930;
	// loPEEP Alarm Limit: Low PEEP/CPAP
	public final static int NLS_NOM_VENT_PRESS_AWAY_END_EXP_POS_LIMIT_LO = 0x0002F8BA;
	public final static short NOM_VENT_PRESS_AWAY_END_EXP_POS_LIMIT_LO = (short)0xF8BA;
	// sustP Alarm Limit: Sustained Pressure Alarm Limit.
	public final static int NLS_NOM_SETT_VENT_PRESS_AWAY_SUST_LIMIT_HI = 0x0402F935;
	public final static short NOM_SETT_VENT_PRESS_AWAY_SUST_LIMIT_HI = (short)0xF935;
	// lowMV Alarm Limit: Low Minute Volume Alarm Limit
	public final static int NLS_NOM_SETT_VENT_VOL_MINUTE_AWAY_LIMIT_LO = 0x0402F94C;
	public final static short NOM_SETT_VENT_VOL_MINUTE_AWAY_LIMIT_LO = (short)0xF94C;
	// lowO2 Alarm Limit: Low Oxygen (O2) Alarm Limit
	public final static int NLS_NOM_SETT_VENT_CONC_AWAY_O2_LIMIT_LO = 0x0402F91A;
	public final static short NOM_SETT_VENT_CONC_AWAY_O2_LIMIT_LO = (short)0xF91A;
	// highO2 Alarm Limit. High Oxygen (O2) Alarm Limit
	public final static int NLS_NOM_SETT_VENT_CONC_AWAY_O2_LIMIT_HI = 0x0402F919;
	public final static short NOM_SETT_VENT_CONC_AWAY_O2_LIMIT_HI = (short)0xF919;
	// highMV Alarm Limit: High Minute Volume Alarm Limit
	public final static int NLS_NOM_SETT_VENT_VOL_MINUTE_AWAY_LIMIT_HI = 0x0402F94B;
	public final static short NOM_SETT_VENT_VOL_MINUTE_AWAY_LIMIT_HI = (short)0xF94B;
	// lowTV Alarm Limit: Low Tidal Volume Alarm Limit
	public final static int NLS_NOM_SETT_VENT_VOL_TIDAL_LIMIT_LO = 0x0402F94E;
	public final static short NOM_SETT_VENT_VOL_TIDAL_LIMIT_LO = (short)0xF94E;
	// highTV Alarm Limit: High Tidal Volume Alarm Limit
	public final static int NLS_NOM_SETT_VENT_VOL_TIDAL_LIMIT_HI = 0x0402F94D;
	public final static short NOM_SETT_VENT_VOL_TIDAL_LIMIT_HI = (short)0xF94D;
	// Num 1 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM1 = 0x80AAF064;
	// Num 2 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM2 = 0x80AAF066;
	// Num 3 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM3 = 0x80AAF068;
	// Num 4 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM4 = 0x80AAF06A;
	// Num 5 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM5 = 0x80AAF06C;
	// Num 6 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM6 = 0x80AAF06E;
	// Num 7 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM7 = 0x80AAF070;
	// Num 8 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM8 = 0x80AAF072;
	// Num 9 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM9 = 0x80AAF074;
	// Num 10 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM10 = 0x80AAF076;
	// Num 11 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM11 = 0x80AAF078;
	// Num 12 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM12 = 0x80AAF07A;
	// Num 13 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM13 = 0x80AAF07C;
	// Num 14 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM14 = 0x80AAF07E;
	// Num 15 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM15 = 0x80AAF080;
	// Num 16 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM16 = 0x80AAF082;
	// Num 17 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM17 = 0x80AAF084;
	// Num 18 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM18 = 0x80AAF086;
	// Num 19 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM19 = 0x80AAF088;
	// Num 20 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM20 = 0x80AAF08A;
	// Num 21 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM21 = 0x80AAF08C;
	// Num 22 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM22 = 0x80AAF08E;
	// Num 23 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM23 = 0x80AAF090;
	// Num 24 Placeholder for Vuelink Flex Text
	public final static int NLS_VUELINK_FLX1_NPS_TEXT_NUM24 = 0x80AAF092;
	// PCT Procalcitonin
	public final static int NLS_NOM_CONC_PCT = 0x0002F17D;
	public final static short NOM_CONC_PCT = (short)0xF17D;
	public final static short NOM_DIM_PICO_G_PER_ML = (short)0x0875;
	public final static short NOM_DIM_NANO_G_PER_L = (short)0x0814;
	// Quick Thromboplastine Time
	public final static int NLS_NOM_TIME_PD_THROMBOPLAS = 0x0002F193;
	public final static short NOM_TIME_PD_THROMBOPLAS = (short)0xF193;
	//public final static short NOM_DIM_SEC = (short)0x0880;
	// HDL High Density Lipoprotein
	public final static int NLS_NOM_CONC_HDL = 0x0002F170;
	public final static short NOM_CONC_HDL = (short)0xF170;
	public final static short NOM_DIM_MILLI_MOLE_PER_L = (short)0x1272;
	public final static short NOM_DIM_MILLI_G_PER_DL = (short)0x0852;
	// LDL Low Density Lipoprotein
	public final static int NLS_NOM_CONC_LDL = 0x0002F171;
	public final static short NOM_CONC_LDL = (short)0xF171;
	// NO VALUE: NOM_DIM_MILLI_MOL_PER_L
	//public final static short NOM_DIM_MILLI_G_PER_DL = (short)0x0852;
	// CRP C-reactive Protein
	public final static int NLS_NOM_CONC_CRP = 0x0002F183;
	public final static short NOM_CONC_CRP = (short)0xF183;
	public final static short NOM_DIM_MILLI_G_PER_L = (short)0x0812;
	//public final static short NOM_DIM_MILLI_G_PER_DL = (short)0x0852;
	// UrHb Hemoglobin (Urine)
	public final static int NLS_NOM_CONC_HB_URINE = 0x0002F19E;
	public final static short NOM_CONC_HB_URINE = (short)0xF19E;
	public final static short NOM_DIM_X_G_PER_DL = (short)0x0840;
	public final static short NOM_DIM_X_G_PER_L = (short)0x0800;
	//public final static short NOM_DIM_MILLI_MOLE_PER_L = (short)0x1272;
	// ApneaD Apnea Time
	public final static int NLS_NOM_TIME_PD_APNEA = 0x00025130;
	public final static short NOM_TIME_PD_APNEA = (short)0x5130;
	// FICO2 Airway CO2 inspiration
	public final static int NLS_NOM_VENT_CONC_AWAY_CO2_INSP = 0x00025160;
	public final static short NOM_VENT_CONC_AWAY_CO2_INSP = (short)0x5160;
	// NO VALUE: NOM_DIM_PERCENT
	// HLMfl
	public final static int NLS_NOM_FLOW_PUMP_HEART_LUNG_MAIN = 0x0002F974;
	public final static short NOM_FLOW_PUMP_HEART_LUNG_MAIN = (short)0xF974;
	// SlvPfl
	public final static int NLS_NOM_FLOW_PUMP_HEART_LUNG_SLAVE = 0x0002F975;
	public final static short NOM_FLOW_PUMP_HEART_LUNG_SLAVE = (short)0xF975;
	// SucPfl
	public final static int NLS_NOM_FLOW_PUMP_HEART_LUNG_SUCTION = 0x0002F976;
	public final static short NOM_FLOW_PUMP_HEART_LUNG_SUCTION = (short)0xF976;
	// AuxPfl
	public final static int NLS_NOM_FLOW_PUMP_HEART_LUNG_AUX = 0x0002F977;
	public final static short NOM_FLOW_PUMP_HEART_LUNG_AUX = (short)0xF977;
	// PlePfl
	public final static int NLS_NOM_FLOW_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = 0x0002F978;
	public final static short NOM_FLOW_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = (short)0xF978;
	// SplPfl
	public final static int NLS_NOM_FLOW_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = 0x0002F979;
	public final static short NOM_FLOW_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = (short)0xF979;
	// DeltaP Blood Pressure difference
	public final static int NLS_NOM_PRESS_BLD_DIFF = 0x0002F968;
	public final static short NOM_PRESS_BLD_DIFF = (short)0xF968;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// DeltaP1 Blood Pressure difference 1 (generic)
	public final static int NLS_NOM_PRESS_BLD_DIFF_GEN_1 = 0x0002F96C;
	public final static short NOM_PRESS_BLD_DIFF_GEN_1 = (short)0xF96C;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// DeltaP2 Blood Pressure difference 2 (generic)
	public final static int NLS_NOM_PRESS_BLD_DIFF_GEN_2 = 0x0002F970;
	public final static short NOM_PRESS_BLD_DIFF_GEN_2 = (short)0xF970;
	//public final static short NOM_DIM_MMHG = (short)0x0F20;
	//public final static short NOM_DIM_KILO_PASCAL = (short)0x0F03;
	// AxOnTi
	public final static int NLS_NOM_TIME_PD_PUMP_HEART_LUNG_AUX_SINCE_START = 0x0002F97A;
	public final static short NOM_TIME_PD_PUMP_HEART_LUNG_AUX_SINCE_START = (short)0xF97A;
	// AxOffT
	public final static int NLS_NOM_TIME_PD_PUMP_HEART_LUNG_AUX_SINCE_STOP = 0x0002F97B;
	public final static short NOM_TIME_PD_PUMP_HEART_LUNG_AUX_SINCE_STOP = (short)0xF97B;
	// AxDVol
	public final static int NLS_NOM_VOL_DELIV_PUMP_HEART_LUNG_AUX = 0x0002F97C;
	public final static short NOM_VOL_DELIV_PUMP_HEART_LUNG_AUX = (short)0xF97C;
	// AxTVol
	public final static int NLS_NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_AUX = 0x0002F97D;
	public final static short NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_AUX = (short)0xF97D;
	// AxPlTi
	public final static int NLS_NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_AUX = 0x0002F97E;
	public final static short NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_AUX = (short)0xF97E;
	// CpOnTi
	public final static int NLS_NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN_SINCE_START = 0x0002F97F;
	public final static short NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN_SINCE_START = (short)0xF97F;
	// CpOffT
	public final static int NLS_NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN_SINCE_STOP = 0x0002F980;
	public final static short NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN_SINCE_STOP = (short)0xF980;
	// CpDVol
	public final static int NLS_NOM_VOL_DELIV_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = 0x0002F981;
	public final static short NOM_VOL_DELIV_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = (short)0xF981;
	// CpTVol
	public final static int NLS_NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = 0x0002F982;
	public final static short NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = (short)0xF982;
	// CpPlTi
	public final static int NLS_NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = 0x0002F983;
	public final static short NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = (short)0xF983;
	// CsOnTi
	public final static int NLS_NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE_SINCE_START = 0x0002F984;
	public final static short NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE_SINCE_START = (short)0xF984;
	// CsOffT
	public final static int NLS_NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE_SINCE_STOP = 0x0002F985;
	public final static short NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE_SINCE_STOP = (short)0xF985;
	// CsDVol
	public final static int NLS_NOM_VOL_DELIV_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = 0x0002F986;
	public final static short NOM_VOL_DELIV_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = (short)0xF986;
	// 177
	public final static int NLS_NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = 0x0002F987;
	public final static short NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = (short)0xF987;
	// CsPlTi
	public final static int NLS_NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = 0x0002F988;
	public final static short NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = (short)0xF988;
	// StO2 O2 Saturation (tissue)
	public final static int NLS_NOM_SAT_O2_TISSUE = 0x0002F960;
	public final static short NOM_SAT_O2_TISSUE = (short)0xF960;
	//public final static short NOM_DIM_PERCENT = (short)0x0220;
	// CSI
	public final static int NLS_NOM_CEREB_STATE_INDEX = 0x0002F961;
	public final static short NOM_CEREB_STATE_INDEX = (short)0xF961;
	// Tin/Tt
	public final static int NLS_NOM_RATIO_INSP_TOTAL_BREATH_SPONT = 0x0002F990;
	public final static short NOM_RATIO_INSP_TOTAL_BREATH_SPONT = (short)0xF990;
	// PEinsp Respiration Pressure Plateau
	public final static int NLS_NOM_VENT_PRESS_RESP_PLAT = 0x00025368;
	public final static short NOM_VENT_PRESS_RESP_PLAT = (short)0x5368;
	// tPEEP
	public final static int NLS_NOM_VENT_PRESS_AWAY_END_EXP_POS_TOTAL = 0x0002F991;
	public final static short NOM_VENT_PRESS_AWAY_END_EXP_POS_TOTAL = (short)0xF991;
	public final static short NOM_DIM_MILLI_BAR = (short)0x0F72;
	// Cpav
	public final static int NLS_NOM_COMPL_LUNG_PAV = 0x0002F992;
	public final static short NOM_COMPL_LUNG_PAV = (short)0xF992;
	// Epav
	public final static int NLS_NOM_ELAS_LUNG_PAV = 0x0002F995;
	public final static short NOM_ELAS_LUNG_PAV = (short)0xF995;
	// Rpav
	public final static int NLS_NOM_RES_AWAY_PAV = 0x0002F993;
	public final static short NOM_RES_AWAY_PAV = (short)0xF993;
	// Rtot
	public final static int NLS_NOM_RES_AWAY_EXP_TOTAL = 0x0002F994;
	public final static short NOM_RES_AWAY_EXP_TOTAL = (short)0xF994;
	// RSBInm
	public final static int NLS_NOM_BREATH_RAPID_SHALLOW_INDEX_NORM = 0x0002F996;
	public final static short NOM_BREATH_RAPID_SHALLOW_INDEX_NORM = (short)0xF996;

}
