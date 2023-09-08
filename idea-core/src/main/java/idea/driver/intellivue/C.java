package idea.driver.intellivue;

public class C {
	public final static int CURR_MSG_SIZE = 32;
	public final static int NDO_PDS_BED_CONFIG = 123;
	public final static int NDO_PDS_DISPLAY_SETUP = 124;

	// ro_type values for ROapdus
	public final static short ROIV_APDU = 1; // invoke
	public final static short RORS_APDU = 2; // result set
	public final static short ROER_APDU = 3; // er?
	public final static short ROLRS_APDU = 5; // linked result set

	// ROLRS Identifier
	public final static int RORLS_FIRST = 1; /* set in the first message */
	public final static int RORLS_NOT_FIRST_NOT_LAST = 2;
	public final static int RORLS_LAST = 3; /*
											 * last RORLSapdu, one RORSapdu to
											 * follow
											 */

	// ROSE Commands
	public final static short CMD_EVENT_REPORT = 0;
	public final static short CMD_CONFIRMED_EVENT_REPORT = 1;
	public final static short CMD_GET = 3;
	public final static short CMD_SET = 4;
	public final static short CMD_CONFIRMED_SET = 5;
	public final static short CMD_CONFIRMED_ACTION = 7;

	// ROER Error Values
	public final static int NO_SUCH_OBJECT_CLASS = 0;
	public final static int NO_SUCH_OBJECT_INSTANCE = 1;
	public final static int ACCESS_DENIED = 2;
	public final static int GET_LIST_ERROR = 7;
	public final static int SET_LIST_ERROR = 8;
	public final static int NO_SUCH_ACTION = 9;
	public final static int PROCESSING_FAILURE = 10;
	public final static int INVALID_ARGUMENT_VALUE = 15;
	public final static int INVALID_SCOPE = 16;
	public final static int INVALID_OBJECT_INSTANCE = 17;

	// SaFlags values
	public final static short SMOOTH_CURVE = (short) 0x8000;
	public final static short DELAYED_CURVE = 0x4000;
	public final static short STATIC_SCALE = 0x2000;
	public final static short SA_EXT_VAL_RANGE = 0x1000;

	// MeasurementState
	public final static short INVALID = (short) 0x8000;
	public final static short QUESTIONABLE = 0x4000;
	public final static short UNAVAILABLE = 0x2000;
	public final static short CALIBRATION_ONGOING = 0x1000;
	public final static short TEST_DATA = 0x0800;
	public final static short DEMO_DATA = 0x0400;
	public final static short VALIDATED_DATA = 0x0080;
	public final static short EARLY_INDICATION = 0x0040;
	public final static short MSMT_ONGOING = 0x0020;
	public final static short MSMT_STATE_IN_ALARM = 0x0002;
	public final static short MSMT_STATE_AL_INHIBITED = 0x0001;

	// Protocol Identification
	// The IDs for the protocol identification are from the Infrastructure
	// nomenclature partition.
	public final static short NOM_POLL_PROFILE_SUPPORT = 1; // attribute id for polling profile
	public final static short NOM_MDIB_OBJ_SUPPORT = 258; // supported objects
															// for the active
															// profile
	public final static short NOM_ATTR_POLL_PROFILE_EXT = (short) 61441; // id for poll profile extensions opt. package

	public final static short NOM_MOC_VMO = 1; // VMO
	public final static short NOM_MOC_VMO_METRIC_NU = 6; // Numeric
	public final static short NOM_MOC_VMO_METRIC_SA_RT = 9; // Realtime Sample
															// Array
	public final static short NOM_MOC_VMS_MDS = 0x21;
	public final static short NOM_MOC_VMS_MDS_COMPOS_SINGLE_BED = 0x23;

	public final static short NOM_MOC_PT_DEMOG = 42; // Patient Demographics
	public final static short NOM_MOC_VMO_AL_MON = 54; // Alert Monitor
	public final static short NOM_NOTI_MDS_CONNECT_INDIC = 0x0986;

	// public final static short NOM_ACT_POLL_MDIB_DATA =3094;
	public final static short NOM_ACT_POLL_MDIB_DATA = 0x0C16; // Poll Action
	public final static short NOM_NOTI_MDS_CREAT = 3334; // MDS Create
	public final static short NOM_NOTI_CONN_INDIC = 3351; // Connect Indication
	public final static short NOM_DEV_METER_CONC_SKIN_GAS = 4264; // Skin Gas
	public final static short NOM_DEV_METER_FLOW_BLD = 4284;
	public final static short NOM_ACT_POLL_MDIB_DATA_EXT = (short) 0xf13b;

	public final static short NOM_ATTR_AL_MON_P_AL_LIST = 0x0902; // Device
																// P-Alarm List
	public final static short NOM_ATTR_AL_MON_T_AL_LIST = 0x0904; // Device
																// T-Alarm List
	public final static short NOM_ATTR_ALTITUDE = 0x090C; // Altitude
	public final static short NOM_ATTR_AREA_APPL = 0x090D; // Application Area
	public final static short NOM_ATTR_COLOR = 0x0911; // Color
	public final static short NOM_ATTR_DEV_AL_COND = 0x0916; // Device Alert
															// Condition
	public final static short NOM_ATTR_DISP_RES = 0x0917; // Display Resolution
	public final static short NOM_ATTR_GRID_VIS_I16 = 0x091A; // Visual Grid
	public final static short NOM_ATTR_ID_ASSOC_NO = 0x091D; // Association Invoke
															// Id
	public final static short NOM_ATTR_ID_BED_LABEL = 0x091E; // Bed Label
	public final static short NOM_ATTR_ID_HANDLE = 0x0921; // Object Handle
	public final static short NOM_ATTR_ID_LABEL = 0x0924; // Label
	public final static short NOM_ATTR_ID_LABEL_STRING = 0x0927; // Label String
	public final static short NOM_ATTR_ID_MODEL = 0x0928; // System Model
	public final static short NOM_ATTR_ID_PROD_SPECN = 0x092D; // Product
																// Specification
	public final static short NOM_ATTR_ID_TYPE = 0x092F; // Object Type
	public final static short NOM_ATTR_LINE_FREQ = 0x0935; // Line Frequency
	public final static short NOM_ATTR_LOCALIZN = 0x0937; // System Localization
	public final static short NOM_ATTR_METRIC_INFO_LABEL = 0x093C; // Metric Info
																	// Label
	public final static short NOM_ATTR_METRIC_INFO_LABEL_STR = 0x093D; // Metric
																		// Info
																		// Label
																		// String
	public final static short NOM_ATTR_METRIC_SPECN = 0x093F; // Metric
															// Specification
	public final static short NOM_ATTR_METRIC_STAT = 0x0940; // Metric State
	public final static short NOM_ATTR_MODE_MSMT = 0x0945; // Measure Mode
	public final static short NOM_ATTR_MODE_OP = 0x0946; // Operating Mode
	public final static short NOM_ATTR_NOM_VERS = 0x0948; // Nomenclature Version
	public final static short NOM_ATTR_NU_CMPD_VAL_OBS = 0x094B; // Compound
																// Numeric
																// Observed
																// Value
	public final static short NOM_ATTR_NU_VAL_OBS = 0x0950; // Numeric Observed
															// Value
	public final static short NOM_ATTR_PT_BSA = 0x0956; // Patient BSA
	public final static short NOM_ATTR_PT_DEMOG_ST = 0x0957; // Pat Demo State
	public final static short NOM_ATTR_PT_DOB = 0x0958; // Patient Date of Birth
	public final static short NOM_ATTR_PT_ID = 0x095A; // Patient ID
	public final static short NOM_ATTR_PT_NAME_FAMILY = 0x095C; // Family Name
	public final static short NOM_ATTR_PT_NAME_GIVEN = 0x095D; // Given Name
	public final static short NOM_ATTR_PT_SEX = 0x0961; // Patient Sex
	public final static short NOM_ATTR_PT_TYPE = 0x0962; // Patient Type
	public final static short NOM_ATTR_SA_CALIB_I16 = 0x0964; // Sample Array
															// Calibration
															// Specification
	public final static short NOM_ATTR_SA_CMPD_VAL_OBS = 0x0967; // Compound
																// Sample Array
																// Observed
																// Value
	public final static short NOM_ATTR_SA_RANGE_PHYS_I16 = 0x096A; // Sample Array
																	// Physiological
																	// Range
	public final static short NOM_ATTR_SA_SPECN = 0x096D; // Sample Array
														// Specification
	public final static short NOM_ATTR_SA_VAL_OBS = 0x096E; // Sample Array
															// Observed Value
	public final static short NOM_ATTR_SCALE_SPECN_I16 = 0x096F; // Scale and
																// Range
																// Specification
	public final static short NOM_ATTR_STD_SAFETY = 0x0982; // Safety Standard
	public final static short NOM_ATTR_SYS_ID = 0x0984; // System ID
	public final static short NOM_ATTR_SYS_SPECN = 0x0985; // System Specification
	public final static short NOM_ATTR_SYS_TYPE = 0x0986; // System Type
	public final static short NOM_ATTR_TIME_ABS = 0x0987; // Date and Time
	public final static short NOM_ATTR_TIME_PD_SAMP = 0x098D; // Sample Period
	public final static short NOM_ATTR_TIME_REL = 0x098F; // Relative Time
	public final static short NOM_ATTR_TIME_STAMP_ABS = 0x0990; // Absolute Time
																// Stamp
	public final static short NOM_ATTR_TIME_STAMP_REL = 0x0991; // Relative Time
																// Stamp
	public final static short NOM_ATTR_UNIT_CODE = 0x0996; // Unit Code
	public final static short NOM_ATTR_VAL_ENUM_OBS = 0x099E; // Enumeration
															// Observed Value
	public final static short NOM_ATTR_VMS_MDS_STAT = 0x09A7; // MDS Status
	public final static short NOM_ATTR_PT_AGE = 0x09D8; // Patient Age
	public final static short NOM_ATTR_PT_HEIGHT = 0x09DC; // Patient Height
	public final static short NOM_ATTR_PT_WEIGHT = 0x09DF; // Patient Weight
	public final static short NOM_ATTR_SA_FIXED_VAL_SPECN = 0x0A16; // Sample
																	// Array
																	// Fixed
																	// Values
																	// Specification
	public final static short NOM_ATTR_PT_PACED_MODE = 0x0A1E; // Patient Paced
																// Mode
	public final static short NOM_ATTR_PT_ID_INT = (short) 0xF001; // Internal Patient ID
	public final static short NOM_SAT_O2_TONE_FREQ = (short)0xF008; // Private Attribute
	public final static short NOM_ATTR_CMPD_REF_LIST = (short) 0xF009; // Private
																// Attribute
	public final static short NOM_ATTR_NET_ADDR_INFO = (short) 0xF100; // IP Address
																// Information
	public final static short NOM_ATTR_PCOL_SUPPORT = (short) 0xF101; // Protocol Support
	public final static short NOM_ATTR_PT_NOTES1 = (short) 0xF129; // Notes1
	public final static short NOM_ATTR_PT_NOTES2 = (short) 0xF12A; // Notes2
	public final static short NOM_ATTR_TIME_PD_POLL = (short) 0xF13E; // Time for Periodic
															// Polling
	public final static short NOM_ATTR_PT_BSA_FORMULA = (short) 0xF1EC; // Patient BSA
																// Formula
	public final static short NOM_ATTR_MDS_GEN_INFO = (short) 0xF1FA; // Mds General
															// System Info
	public final static short NOM_ATTR_POLL_OBJ_PRIO_NUM = (short) 0xF228; // no of
																	// prioritized
																	// objects
																	// for poll
																	// request
	public final static short NOM_ATTR_UNDOC_F237 = (short) 0xF237;
	public final static short NOM_ATTR_POLL_NU_PRIO_LIST = (short) 0xF239; // Numeric
																	// Object
																	// Priority
																	// List
	public final static short NOM_ATTR_POLL_RTSA_PRIO_LIST = (short) 0xF23A; // Wave
																	// Object
																	// Priority
																	// List
	public final static short NOM_ATTR_METRIC_MODALITY = (short) 0xF294; // Metric
																// Modality

	/*
	 * The attributes are arranged in the following attribute groups:
	 */

	public final static short NOM_ATTR_GRP_AL_MON = 0x0801; // Alert Monitor
															// Group
	public final static short NOM_ATTR_GRP_METRIC_VAL_OBS = 0x0803; // Metric
																	// Observed
																	// Value
																	// Group
	public final static short NOM_ATTR_GRP_PT_DEMOG = 0x0807; // Patient
																// Demographics
																// Attribute
																// Group
	public final static short NOM_ATTR_GRP_SYS_APPL = 0x080A; // System
																// Application
																// Attribute
																// Group
	public final static short NOM_ATTR_GRP_SYS_ID = 0x080B; // System
															// Identification
															// Attribute Group
	public final static short NOM_ATTR_GRP_SYS_PROD = 0x080C; // System
																// Production
																// Attribute
																// Group
	public final static short NOM_ATTR_GRP_VMO_DYN = 0x0810; // VMO Dynamic
																// Attribute
																// Group
	public final static short NOM_ATTR_GRP_VMO_STATIC = 0x0811; // VMO Static
																// Attribute
																// Group

	/*
	 * ApplProtocolId
	 */

	public final static int AP_ID_ACSE = 1;
	public final static int AP_ID_DATA_OUT = 5;

	/*
	 * TransProtoId
	 */
	public final static int TP_ID_UDP = 1;

	/*
	 * ProtoOptions;
	 */
	public final static int P_OPT_WIRELESS = 0x8000;

	/* ****************************************************************
	 * 
	 * Session headers Fields and Subfiends
	 * 
	 * 
	 * ***************************************************************
	 */
	public final static byte CN_SPDU_SI = 0x0d; // Session Connect for
												// Association Request
	public final static byte AC_SPDU_SI = 0x0e; // Session Accept for
												// Association Response
	public final static byte RF_SPDU_SI = 0x0e; // Session Refuse
	public final static byte FN_SPDU_SI = 0x09; // Session Finish -- release
												// request
	public final static byte DN_SPDU_SI = 0x0a; // Session Disconnect --
												// contains release response
	public final static byte AB_SPDU_SI = 0x19; // Session Abort
	public final static byte SESS_UNDOC_12 = 0x0c; // UNDOC: startup...another session already open
	public final static byte SESS_DATA_EXPORT = (byte)0xe1; // 

	public final static int MDDL_VERSION1 = 0x80000000;
	public final static int NOMEN_VERSION = 0x40000000;

	// p68: no additional protocol functions have been defined yet
	public final static int FUNCTIONAL_UNITS = 0x00000000;

	public final static int SYST_CLIENT = 0x80000000;
	public final static int SYST_SERVER = 0x00800000;

	// typedef u_32 StartupMode;
	public final static int HOT_START = 0x80000000;
	public final static int WARM_START = 0x40000000;
	public final static int COLD_START = 0x20000000;

	// typedef u_32 PollProfileRevision;
	public final static int POLL_PROFILE_REV_0 = 0x80000000;

	public final static int RELTIME_1SEC = 2500; // convenience value

	// typedef u_32 PollProfileOptions;
	public final static int P_OPT_DYN_CREATE_OBJECTS = 0x40000000;
	public final static int P_OPT_DYN_DELETE_OBJECTS = 0x20000000;

	// typedef u_32 PollProfileExtOptions;
	public final static int POLL_EXT_PERIOD_NU_1SEC = 0x80000000;
	public final static int POLL_EXT_PERIOD_NU_AVG_12SEC = 0x40000000;
	public final static int POLL_EXT_PERIOD_NU_AVG_60SEC = 0x20000000;
	public final static int POLL_EXT_PERIOD_NU_AVG_300SEC = 0x10000000;
	public final static int POLL_EXT_PERIOD_RTSA = 0x08000000;
	public final static int POLL_EXT_ENUM = 0x04000000;
	public final static int POLL_EXT_NU_PRIO_LIST = 0x02000000;
	public final static int POLL_EXT_DYN_MODALITIES = 0x01000000;

	public final static short NOM_PART_OBJ = 1; /* Object Oriented Elements */
	public final static short NOM_PART_SCADA = 2; /* Physiological Measurements */
	public final static short NOM_PART_EVT = 3; /* Events for Alerts */
	public final static short NOM_PART_DIM = 4; /* Units of Measurement */
	public final static short NOM_PART_PGRP = 6; /*
												 * Identification of Parameter
												 * Groups
												 */
	public final static short NOM_PART_INFRASTRUCT = 8; /*
														 * Infrastructure
														 * Elements
														 */

	public final static short NOM_PART_EMFC = 1025; /* EMFC */
	public final static short NOM_PART_SETTINGS = 1026; /* Settings */

	// typedef u_16 SimpleColour;
	public final static int COL_BLACK = 0;
	public final static int COL_RED = 1;
	public final static int COL_GREEN = 2;
	public final static int COL_YELLOW = 3;
	public final static int COL_BLUE = 4;
	public final static int COL_MAGENTA = 5;
	public final static int COL_CYAN = 6;
	public final static int COL_WHITE = 7;
	public final static int COL_PINK = 20;
	public final static int COL_ORANGE = 35;
	public final static int COL_LIGHT_GREEN = 50;
	public final static int COL_LIGHT_RED = 65;

	public final static int NOM_ECG_LEAD_I = 1;
	public final static int NOM_ECG_LEAD_II = 2;
	public final static int NOM_ECG_LEAD_LA = 21;
	public final static int NOM_ECG_LEAD_RA = 22;
	public final static int NOM_ECG_LEAD_LL = 23;
	public final static int NOM_ECG_LEAD_fI = 24;
	public final static int NOM_ECG_LEAD_fE = 25;
	public final static int NOM_ECG_LEAD_fA = 27;
	public final static int NOM_ECG_LEAD_C = 66;
	public final static int NOM_ECG_LEAD_C1FR = 82;
	public final static int NOM_ECG_LEAD_C2FR = 83;
	public final static int NOM_ECG_LEAD_C3FR = 84;
	public final static int NOM_ECG_LEAD_C4FR = 85;
	public final static int NOM_ECG_LEAD_C5FR = 87;
	public final static int NOM_ECG_LEAD_C6FR = 88;
	public final static int NOM_ECG_LEAD_C7FR = 89;
	public final static int NOM_ECG_LEAD_C8FR = 90;
	public final static int NOM_ECG_LEAD_ES = 100;
	public final static int NOM_ECG_LEAD_AS = 101;
	public final static int NOM_ECG_LEAD_AI = 102;
	public final static int NOM_ECG_LEAD_RL = 115;
	public final static int NOM_ECG_LEAD_EASI_S = 116;
	public final static int NOM_ECG_ELEC_POTL = 256;
	public final static int NOM_ECG_ELEC_POTL_I = 257;
	public final static int NOM_ECG_ELEC_POTL_II = 258;
	public final static int NOM_ECG_ELEC_POTL_V1 = 259;
	public final static int NOM_ECG_ELEC_POTL_V2 = 260;
	public final static int NOM_ECG_ELEC_POTL_V3 = 261;
	public final static int NOM_ECG_ELEC_POTL_V4 = 262;
	public final static int NOM_ECG_ELEC_POTL_V5 = 263;
	public final static int NOM_ECG_ELEC_POTL_V6 = 264;
	public final static int NOM_ECG_ELEC_POTL_III = 317;
	public final static int NOM_ECG_ELEC_POTL_AVR = 318;
	public final static int NOM_ECG_ELEC_POTL_AVL = 319;
	public final static int NOM_ECG_ELEC_POTL_AVF = 320;
	public final static int NOM_ECG_ELEC_POTL_V = 323;
	public final static int NOM_ECG_ELEC_POTL_MCL = 331;
	public final static int NOM_ECG_ELEC_POTL_MCL1 = 332;
	public final static int NOM_ECG_AMPL_ST = 768;
	public final static int NOM_ECG_AMPL_ST_I = 769;
	public final static int NOM_ECG_AMPL_ST_II = 770;
	public final static int NOM_ECG_AMPL_ST_V1 = 771;
	public final static int NOM_ECG_AMPL_ST_V2 = 772;
	public final static int NOM_ECG_AMPL_ST_V3 = 773;
	public final static int NOM_ECG_AMPL_ST_V4 = 774;
	public final static int NOM_ECG_AMPL_ST_V5 = 775;
	public final static int NOM_ECG_AMPL_ST_V6 = 776;
	public final static int NOM_ECG_AMPL_ST_III = 829;
	public final static int NOM_ECG_AMPL_ST_AVR = 830;
	public final static int NOM_ECG_AMPL_ST_AVL = 831;
	public final static int NOM_ECG_AMPL_ST_AVF = 832;
	public final static int NOM_ECG_AMPL_ST_V = 835;
	public final static int NOM_ECG_AMPL_ST_MCL = 843;
	public final static int NOM_ECG_AMPL_ST_ES = 868;
	public final static int NOM_ECG_AMPL_ST_AS = 869;
	public final static int NOM_ECG_AMPL_ST_AI = 870;
	public final static int NOM_ECG_CARD_BEAT_RATE = 16770;
	public final static int NOM_ECG_V_P_C_CNT = 16993;
	public final static int NOM_ECG_V_P_C_FREQ = 17000;
	public final static int NOM_PULS_RATE = 18442;
	public final static int NOM_PLETH_PULS_RATE = 18466;
	public final static int NOM_RES_VASC_SYS_INDEX = 18688;
	public final static int NOM_WK_LV_STROKE_INDEX = 18692;
	public final static int NOM_WK_RV_STROKE_INDEX = 18696;
	public final static int NOM_OUTPUT_CARD_INDEX = 18700;
	public final static int NOM_PRESS_BLD = 18944;
	public final static int NOM_PRESS_BLD_SYS = 18945;
	public final static int NOM_PRESS_BLD_DIA = 18946;
	public final static int NOM_PRESS_BLD_MEAN = 18947;
	public final static int NOM_PRESS_BLD_NONINV = 18948;
	public final static int NOM_PRESS_BLD_NONINV_SYS = 18949;
	public final static int NOM_PRESS_BLD_NONINV_DIA = 18950;
	public final static int NOM_PRESS_BLD_NONINV_MEAN = 18951;
	public final static int NOM_PRESS_BLD_AORT = 18956;
	public final static int NOM_PRESS_BLD_AORT_SYS = 18957;
	public final static int NOM_PRESS_BLD_AORT_DIA = 18958;
	public final static int NOM_PRESS_BLD_AORT_MEAN = 18959;
	public final static int NOM_PRESS_BLD_ART = 18960;
	public final static int NOM_PRESS_BLD_ART_SYS = 18961;
	public final static int NOM_PRESS_BLD_ART_DIA = 18962;
	public final static int NOM_PRESS_BLD_ART_MEAN = 18963;
	public final static int NOM_PRESS_BLD_ART_ABP = 18964;
	public final static int NOM_PRESS_BLD_ART_ABP_SYS = 18965;
	public final static int NOM_PRESS_BLD_ART_ABP_DIA = 18966;
	public final static int NOM_PRESS_BLD_ART_ABP_MEAN = 18967;
	public final static int NOM_PRESS_BLD_ART_PULM = 18972;
	public final static int NOM_PRESS_BLD_ART_PULM_SYS = 18973;
	public final static int NOM_PRESS_BLD_ART_PULM_DIA = 18974;
	public final static int NOM_PRESS_BLD_ART_PULM_MEAN = 18975;
	public final static int NOM_PRESS_BLD_ART_PULM_WEDGE = 18980;
	public final static int NOM_PRESS_BLD_ART_UMB = 18984;
	public final static int NOM_PRESS_BLD_ART_UMB_SYS = 18985;
	public final static int NOM_PRESS_BLD_ART_UMB_DIA = 18986;
	public final static int NOM_PRESS_BLD_ART_UMB_MEAN = 18987;
	public final static int NOM_PRESS_BLD_ATR_LEFT = 18992;
	public final static int NOM_PRESS_BLD_ATR_LEFT_SYS = 18993;
	public final static int NOM_PRESS_BLD_ATR_LEFT_DIA = 18994;
	public final static int NOM_PRESS_BLD_ATR_LEFT_MEAN = 18995;
	public final static int NOM_PRESS_BLD_ATR_RIGHT = 18996;
	public final static int NOM_PRESS_BLD_ATR_RIGHT_SYS = 18997;
	public final static int NOM_PRESS_BLD_ATR_RIGHT_DIA = 18998;
	public final static int NOM_PRESS_BLD_ATR_RIGHT_MEAN = 18999;
	public final static int NOM_PRESS_BLD_VEN_CENT = 19012;
	public final static int NOM_PRESS_BLD_VEN_CENT_SYS = 19013;
	public final static int NOM_PRESS_BLD_VEN_CENT_DIA = 19014;
	public final static int NOM_PRESS_BLD_VEN_CENT_MEAN = 19015;
	public final static int NOM_PRESS_BLD_VEN_UMB = 19016;
	public final static int NOM_PRESS_BLD_VEN_UMB_SYS = 19017;
	public final static int NOM_PRESS_BLD_VEN_UMB_DIA = 19018;
	public final static int NOM_PRESS_BLD_VEN_UMB_MEAN = 19019;
	public final static int NOM_SAT_O2_CONSUMP = 19200;
	public final static int NOM_OUTPUT_CARD = 19204;
	public final static int NOM_RES_VASC_PULM = 19236;
	public final static int NOM_RES_VASC_SYS = 19240;
	public final static int NOM_SAT_O2 = 19244;
	public final static int NOM_SAT_O2_ART = 19252;
	public final static int NOM_SAT_O2_VEN = 19260;
	public final static int NOM_SAT_DIFF_O2_ART_ALV = 19264;
	public final static int NOM_TEMP = 19272;
	public final static int NOM_TEMP_ART = 19280;
	public final static int NOM_TEMP_AWAY = 19284;
	public final static int NOM_TEMP_CORE = 19296;
	public final static int NOM_TEMP_ESOPH = 19300;
	public final static int NOM_TEMP_NASOPH = 19308;
	public final static int NOM_TEMP_SKIN = 19316;
	public final static int NOM_TEMP_TYMP = 19320;
	public final static int NOM_TEMP_VEN = 19324;
	public final static int NOM_VOL_BLD_STROKE = 19332;
	public final static int NOM_WK_CARD_LEFT = 19344;
	public final static int NOM_WK_CARD_RIGHT = 19348;
	public final static int NOM_WK_LV_STROKE = 19356;
	public final static int NOM_WK_RV_STROKE = 19364;
	public final static int NOM_PULS_OXIM_PERF_REL = 19376;
	public final static int NOM_PLETH = 19380;
	public final static int NOM_PULS_OXIM_SAT_O2 = 19384;
	public final static int NOM_PULS_OXIM_SAT_O2_DIFF = 19396;
	public final static int NOM_PULS_OXIM_SAT_O2_ART_LEFT = 19400;
	public final static int NOM_PULS_OXIM_SAT_O2_ART_RIGHT = 19404;
	public final static int NOM_OUTPUT_CARD_CTS = 19420;
	public final static int NOM_VOL_VENT_L_END_SYS = 19460;
	public final static int NOM_GRAD_PRESS_BLD_AORT_POS_MAX = 19493;
	public final static int NOM_RESP = 20480;
	public final static int NOM_RESP_RATE = 20490;
	public final static int NOM_AWAY_RESP_RATE = 20498;
	public final static int NOM_CAPAC_VITAL = 20608;
	public final static int NOM_COMPL_LUNG = 20616;
	public final static int NOM_COMPL_LUNG_DYN = 20620;
	public final static int NOM_COMPL_LUNG_STATIC = 20624;
	public final static int NOM_CONC_AWAY_CO2 = 20628;
	public final static int NOM_CONC_AWAY_CO2_ET = 20636;
	public final static int NOM_CONC_AWAY_CO2_INSP_MIN = 20646;
	public final static int NOM_AWAY_CO2 = 20652;
	public final static int NOM_AWAY_CO2_ET = 20656;
	public final static int NOM_AWAY_CO2_INSP_MIN = 20666;
	public final static int NOM_CO2_TCUT = 20684;
	public final static int NOM_O2_TCUT = 20688;
	public final static int NOM_FLOW_AWAY = 20692;
	public final static int NOM_FLOW_CO2_PROD_RESP = 20704;
	public final static int NOM_IMPED_TTHOR = 20708;
	public final static int NOM_PRESS_RESP_PLAT = 20712;
	public final static int NOM_PRESS_AWAY = 20720;
	public final static int NOM_PRESS_AWAY_MIN = 20722;
	public final static int NOM_PRESS_AWAY_CTS_POS = 20724;
	public final static int NOM_PRESS_AWAY_NEG_MAX = 20729;
	public final static int NOM_PRESS_AWAY_END_EXP_POS_INTRINSIC = 20736;
	public final static int NOM_PRESS_AWAY_INSP = 20744;
	public final static int NOM_PRESS_AWAY_INSP_MAX = 20745;
	public final static int NOM_PRESS_AWAY_INSP_MEAN = 20747;
	public final static int NOM_RATIO_IE = 20760;
	public final static int NOM_RATIO_AWAY_DEADSP_TIDAL = 20764;
	public final static int NOM_RES_AWAY = 20768;
	public final static int NOM_RES_AWAY_EXP = 20772;
	public final static int NOM_RES_AWAY_INSP = 20776;
	public final static int NOM_TIME_PD_APNEA = 20784;
	public final static int NOM_VOL_AWAY_TIDAL = 20796;
	public final static int NOM_VOL_MINUTE_AWAY = 20808;
	public final static int NOM_VENT_CONC_AWAY_CO2_INSP = 20832;
	public final static int NOM_CONC_AWAY_O2 = 20836;
	public final static int NOM_VENT_CONC_AWAY_O2_DELTA = 20840;
	public final static int NOM_VENT_AWAY_CO2_EXP = 20860;
	public final static int NOM_VENT_PRESS_AWAY_END_EXP_POS = 20904;
	public final static int NOM_VENT_VOL_AWAY_DEADSP = 20912;
	public final static int NOM_VENT_VOL_LUNG_TRAPD = 20920;
	public final static int NOM_VENT_CONC_AWAY_O2_INSP = 29848;
	public final static int NOM_VENT_FLOW_RATIO_PERF_ALV_INDEX = 20880;
	public final static int NOM_VENT_FLOW_INSP = 20876;
	public final static int NOM_VENT_PRESS_OCCL = 20892;
	public final static int NOM_VENT_VOL_AWAY_DEADSP_REL = 20916;
	public final static int NOM_VENT_VOL_MINUTE_AWAY_MAND = 20940;
	public final static int NOM_COEF_GAS_TRAN = 20948;
	public final static int NOM_CONC_AWAY_DESFL = 20952;
	public final static int NOM_CONC_AWAY_ENFL = 20956;
	public final static int NOM_CONC_AWAY_HALOTH = 20960;
	public final static int NOM_CONC_AWAY_SEVOFL = 20964;
	public final static int NOM_CONC_AWAY_ISOFL = 20968;
	public final static int NOM_CONC_AWAY_N2O = 20976;
	public final static int NOM_CONC_AWAY_DESFL_ET = 21012;
	public final static int NOM_CONC_AWAY_ENFL_ET = 21016;
	public final static int NOM_CONC_AWAY_HALOTH_ET = 21020;
	public final static int NOM_CONC_AWAY_SEVOFL_ET = 21024;
	public final static int NOM_CONC_AWAY_ISOFL_ET = 21028;
	public final static int NOM_CONC_AWAY_N2O_ET = 21036;
	public final static int NOM_CONC_AWAY_DESFL_INSP = 21096;
	public final static int NOM_CONC_AWAY_ENFL_INSP = 21100;
	public final static int NOM_CONC_AWAY_HALOTH_INSP = 21104;
	public final static int NOM_CONC_AWAY_SEVOFL_INSP = 21108;
	public final static int NOM_CONC_AWAY_ISOFL_INSP = 21112;
	public final static int NOM_CONC_AWAY_N2O_INSP = 21120;
	public final static int NOM_CONC_AWAY_O2_INSP = 21124;
	public final static int NOM_VENT_TIME_PD_PPV = 21344;
	public final static int NOM_VENT_PRESS_RESP_PLAT = 21352;
	public final static int NOM_VENT_VOL_LEAK = 21360;
	public final static int NOM_VENT_VOL_LUNG_ALV = 21364;
	public final static int NOM_CONC_AWAY_O2_ET = 21368;
	public final static int NOM_CONC_AWAY_N2 = 21372;
	public final static int NOM_CONC_AWAY_N2_ET = 21376;
	public final static int NOM_CONC_AWAY_N2_INSP = 21380;
	public final static int NOM_CONC_AWAY_AGENT = 21384;
	public final static int NOM_CONC_AWAY_AGENT_ET = 21388;
	public final static int NOM_CONC_AWAY_AGENT_INSP = 21392;
	public final static int NOM_PRESS_CEREB_PERF = 22532;
	public final static int NOM_PRESS_INTRA_CRAN = 22536;
	public final static int NOM_PRESS_INTRA_CRAN_SYS = 22537;
	public final static int NOM_PRESS_INTRA_CRAN_DIA = 22538;
	public final static int NOM_PRESS_INTRA_CRAN_MEAN = 22539;
	public final static int NOM_SCORE_GLAS_COMA = 22656;
	public final static int NOM_SCORE_EYE_SUBSC_GLAS_COMA = 22658;
	public final static int NOM_SCORE_MOTOR_SUBSC_GLAS_COMA = 22659;
	public final static int NOM_SCORE_SUBSC_VERBAL_GLAS_COMA = 22660;
	public final static int NOM_CIRCUM_HEAD = 22784;
	public final static int NOM_TIME_PD_PUPIL_REACT_LEFT = 22820;
	public final static int NOM_TIME_PD_PUPIL_REACT_RIGHT = 22824;
	public final static int NOM_EEG_ELEC_POTL_CRTX = 22828;
	public final static int NOM_EMG_ELEC_POTL_MUSCL = 22844;
	public final static int NOM_EEG_FREQ_PWR_SPEC_CRTX_DOM_MEAN = 22908;
	public final static int NOM_EEG_FREQ_PWR_SPEC_CRTX_PEAK = 22916;
	public final static int NOM_EEG_FREQ_PWR_SPEC_CRTX_SPECTRAL_EDGE = 22920;
	public final static int NOM_EEG_PWR_SPEC_TOT = 22968;
	public final static int NOM_EEG_PWR_SPEC_ALPHA_REL = 22996;
	public final static int NOM_EEG_PWR_SPEC_BETA_REL = 23000;
	public final static int NOM_EEG_PWR_SPEC_DELTA_REL = 23004;
	public final static int NOM_EEG_PWR_SPEC_THETA_REL = 23008;
	public final static int NOM_FLOW_URINE_INSTANT = 26636;
	public final static int NOM_VOL_URINE_BAL_PD = 26660;
	public final static int NOM_VOL_URINE_COL = 26672;
	public final static int NOM_VOL_INFUS_ACTUAL_TOTAL = 26876;
	public final static int NOM_CONC_PH_ART = 28676;
	public final static int NOM_CONC_PCO2_ART = 28680;
	public final static int NOM_CONC_PO2_ART = 28684;
	public final static int NOM_CONC_HB_ART = 28692;
	public final static int NOM_CONC_HB_O2_ART = 28696;
	public final static int NOM_CONC_PO2_VEN = 28732;
	public final static int NOM_CONC_PH_VEN = 28724;
	public final static int NOM_CONC_PCO2_VEN = 28728;
	public final static int NOM_CONC_HB_O2_VEN = 28744;
	public final static int NOM_CONC_PH_URINE = 28772;
	public final static int NOM_CONC_NA_URINE = 28780;
	public final static int NOM_CONC_NA_SERUM = 28888;
	public final static int NOM_CONC_PH_GEN = 28932;
	public final static int NOM_CONC_HCO3_GEN = 28936;
	public final static int NOM_CONC_NA_GEN = 28940;
	public final static int NOM_CONC_K_GEN = 28944;
	public final static int NOM_CONC_GLU_GEN = 28948;
	public final static int NOM_CONC_CA_GEN = 28952;
	public final static int NOM_CONC_PCO2_GEN = 28992;
	public final static int NOM_CONC_CHLORIDE_GEN = 29032;
	public final static int NOM_BASE_EXCESS_BLD_ART = 29036;
	public final static int NOM_CONC_PO2_GEN = 29044;
	public final static int NOM_CONC_HCT_GEN = 29060;
	public final static int NOM_VENT_MODE_MAND_INTERMIT = 53290;
	public final static int NOM_TEMP_RECT = 57348;
	public final static int NOM_TEMP_BLD = 57364;
	public final static int NOM_TEMP_DIFF = 57368;
	public final static int NOM_METRIC_NOS = 61439;
	public final static int NOM_ECG_AMPL_ST_INDEX = 61501;
	public final static int NOM_VOL_BLD_INTRA_THOR = 61504;
	public final static int NOM_VOL_BLD_INTRA_THOR_INDEX = 61505;
	public final static int NOM_VOL_LUNG_WATER_EXTRA_VASC = 61506;
	public final static int NOM_VOL_LUNG_WATER_EXTRA_VASC_INDEX = 61507;
	public final static int NOM_VOL_GLOBAL_END_DIA = 61508;
	public final static int NOM_VOL_GLOBAL_END_DIA_INDEX = 61509;
	public final static int NOM_CARD_FUNC_INDEX = 61510;
	public final static int NOM_OUTPUT_CARD_INDEX_CTS = 61511;
	public final static int NOM_VOL_BLD_STROKE_INDEX = 61512;
	public final static int NOM_VOL_BLD_STROKE_VAR = 61513;
	public final static int NOM_EEG_RATIO_SUPPRN = 61514;
	public final static int NOM_ELECTRODE_IMPED = 61515;
	public final static int NOM_EEG_BIS_SIG_QUAL_INDEX = 61517;
	public final static int NOM_EEG_BISPECTRAL_INDEX = 61518;
	public final static int NOM_GAS_TCUT = 61521;
	public final static int NOM_CONC_AWAY_SUM_MAC = 61533;
	public final static int NOM_CONC_AWAY_SUM_MAC_ET = 61534;
	public final static int NOM_CONC_AWAY_SUM_MAC_INSP = 61535;
	public final static int NOM_RES_VASC_PULM_INDEX = 61543;
	public final static int NOM_WK_CARD_LEFT_INDEX = 61544;
	public final static int NOM_WK_CARD_RIGHT_INDEX = 61545;
	public final static int NOM_SAT_O2_CONSUMP_INDEX = 61546;
	public final static int NOM_PRESS_AIR_AMBIENT = 61547;
	public final static int NOM_SAT_DIFF_O2_ART_VEN = 61548;
	public final static int NOM_SAT_O2_DELIVER = 61549;
	public final static int NOM_SAT_O2_DELIVER_INDEX = 61550;
	public final static int NOM_RATIO_SAT_O2_CONSUMP_DELIVER = 61551;
	public final static int NOM_RATIO_ART_VEN_SHUNT = 61552;
	public final static int NOM_AREA_BODY_SURFACE = 61553;
	public final static int NOM_INTENS_LIGHT = 61554;
	public final static int NOM_RATE_DIFF_CARD_BEAT_PULSE = 61560;
	public final static int NOM_VOL_INJ = 61561;
	public final static int NOM_VOL_THERMO_EXTRA_VASC_INDEX = 61562;
	public final static int NOM_NUM_CATHETER_CONST = 61564;
	public final static int NOM_PULS_OXIM_PERF_REL_LEFT = 61578;
	public final static int NOM_PULS_OXIM_PERF_REL_RIGHT = 61579;
	public final static int NOM_PULS_OXIM_PLETH_RIGHT = 61580;
	public final static int NOM_PULS_OXIM_PLETH_LEFT = 61581;
	public final static int NOM_CONC_BLD_UREA_NITROGEN = 61583;
	public final static int NOM_CONC_BASE_EXCESS_ECF = 61584;
	public final static int NOM_VENT_VOL_MINUTE_AWAY_SPONT = 61585;
	public final static int NOM_CONC_DIFF_HB_O2_ATR_VEN = 61586;
	public final static int NOM_PAT_WEIGHT = 61587;
	public final static int NOM_PAT_HEIGHT = 61588;
	public final static int NOM_CONC_AWAY_MAC = 61593;
	public final static int NOM_PULS_OXIM_PLETH_TELE = 61595;
	public final static int NOM_PULS_OXIM_SAT_O2_TELE = 61596;
	public final static int NOM_PULS_OXIM_PULS_RATE_TELE = 61597;
	public final static int NOM_PRESS_BLD_NONINV_TELE = 61600;
	public final static int NOM_PRESS_BLD_NONINV_TELE_SYS = 61601;
	public final static int NOM_PRESS_BLD_NONINV_TELE_DIA = 61602;
	public final static int NOM_PRESS_BLD_NONINV_TELE_MEAN = 61603;
	public final static int NOM_PRESS_GEN_1 = 61604;
	public final static int NOM_PRESS_GEN_1_SYS = 61605;
	public final static int NOM_PRESS_GEN_1_DIA = 61606;
	public final static int NOM_PRESS_GEN_1_MEAN = 61607;
	public final static int NOM_PRESS_GEN_2 = 61608;
	public final static int NOM_PRESS_GEN_2_SYS = 61609;
	public final static int NOM_PRESS_GEN_2_DIA = 61610;
	public final static int NOM_PRESS_GEN_2_MEAN = 61611;
	public final static int NOM_PRESS_GEN_3 = 61612;
	public final static int NOM_PRESS_GEN_3_SYS = 61613;
	public final static int NOM_PRESS_GEN_3_DIA = 61614;
	public final static int NOM_PRESS_GEN_3_MEAN = 61615;
	public final static int NOM_PRESS_GEN_4 = 61616;
	public final static int NOM_PRESS_GEN_4_SYS = 61617;
	public final static int NOM_PRESS_GEN_4_DIA = 61618;
	public final static int NOM_PRESS_GEN_4_MEAN = 61619;
	public final static int NOM_PRESS_INTRA_CRAN_1 = 61620;
	public final static int NOM_PRESS_INTRA_CRAN_1_SYS = 61621;
	public final static int NOM_PRESS_INTRA_CRAN_1_DIA = 61622;
	public final static int NOM_PRESS_INTRA_CRAN_1_MEAN = 61623;
	public final static int NOM_PRESS_INTRA_CRAN_2 = 61624;
	public final static int NOM_PRESS_INTRA_CRAN_2_SYS = 61625;
	public final static int NOM_PRESS_INTRA_CRAN_2_DIA = 61626;
	public final static int NOM_PRESS_INTRA_CRAN_2_MEAN = 61627;
	public final static int NOM_PRESS_BLD_ART_FEMORAL = 61628;
	public final static int NOM_PRESS_BLD_ART_FEMORAL_SYS = 61629;
	public final static int NOM_PRESS_BLD_ART_FEMORAL_DIA = 61630;
	public final static int NOM_PRESS_BLD_ART_FEMORAL_MEAN = 61631;
	public final static int NOM_PRESS_BLD_ART_BRACHIAL = 61632;
	public final static int NOM_PRESS_BLD_ART_BRACHIAL_SYS = 61633;
	public final static int NOM_PRESS_BLD_ART_BRACHIAL_DIA = 61634;
	public final static int NOM_PRESS_BLD_ART_BRACHIAL_MEAN = 61635;
	public final static int NOM_TEMP_VESICAL = 61636;
	public final static int NOM_TEMP_CEREBRAL = 61637;
	public final static int NOM_TEMP_AMBIENT = 61638;
	public final static int NOM_TEMP_GEN_1 = 61639;
	public final static int NOM_TEMP_GEN_2 = 61640;
	public final static int NOM_TEMP_GEN_3 = 61641;
	public final static int NOM_TEMP_GEN_4 = 61642;
	public final static int NOM_PRESS_INTRA_UTERAL = 61656;
	public final static int NOM_TIME_PD_RESP_PLAT = 61695;
	public final static int NOM_SNR = 61697;
	public final static int NOM_HUMID = 61699;
	public final static int NOM_FRACT_EJECT = 61701;
	public final static int NOM_PERM_VASC_PULM_INDEX = 61702;
	public final static int NOM_TEMP_ORAL = 61704;
	public final static int NOM_TEMP_AXIL = 61708;
	public final static int NOM_TEMP_ORAL_PRED = 61712;
	public final static int NOM_TEMP_RECT_PRED = 61716;
	public final static int NOM_TEMP_AXIL_PRED = 61720;
	public final static int NOM_TEMP_AIR_INCUB = 61738;
	public final static int NOM_PULS_OXIM_PERF_REL_TELE = 61740;
	public final static int NOM_TEMP_PRED = 61760;
	public final static int NOM_SHUNT_RIGHT_LEFT = 61770;
	public final static int NOM_ECG_TIME_PD_QT_HEART_RATE = 61780;
	public final static int NOM_ECG_TIME_PD_QT_BASELINE = 61781;
	public final static int NOM_ECG_TIME_PD_QTc_DELTA = 61782;
	public final static int NOM_ECG_TIME_PD_QT_BASELINE_HEART_RATE = 61783;
	public final static int NOM_CONC_PH_CAP = 61784;
	public final static int NOM_CONC_PCO2_CAP = 61785;
	public final static int NOM_CONC_PO2_CAP = 61786;
	public final static int NOM_SAT_O2_CAP = 61793;
	public final static int NOM_CONC_MG_ION = 61787;
	public final static int NOM_CONC_MG_SER = 61788;
	public final static int NOM_CONC_tCA_SER = 61789;
	public final static int NOM_CONC_P_SER = 61790;
	public final static int NOM_CONC_CHLOR_SER = 61791;
	public final static int NOM_CONC_FE_GEN = 61792;
	public final static int NOM_CONC_AN_GAP = 61794;
	public final static int NOM_CONC_AN_GAP_CALC = 61857;
	public final static int NOM_CONC_ALB_SER = 61795;
	public final static int NOM_SAT_O2_ART_CALC = 61796;
	public final static int NOM_SAT_O2_VEN_CALC = 61798;
	public final static int NOM_SAT_O2_CAP_CALC = 61856;
	public final static int NOM_CONC_HB_CO_GEN = 29056;
	public final static int NOM_CONC_HB_FETAL = 61797;
	public final static int NOM_CONC_HB_MET_GEN = 29052;
	public final static int NOM_PLTS_CNT = 61799;
	public final static int NOM_WB_CNT = 61800;
	public final static int NOM_RB_CNT = 61801;
	public final static int NOM_RET_CNT = 61802;
	public final static int NOM_PLASMA_OSM = 61803;
	public final static int NOM_CONC_CREA_CLR = 61804;
	public final static int NOM_NSLOSS = 61805;
	public final static int NOM_CONC_CHOLESTEROL = 61806;
	public final static int NOM_CONC_TGL = 61807;
	public final static int NOM_CONC_HDL = 61808;
	public final static int NOM_CONC_LDL = 61809;
	public final static int NOM_CONC_UREA_GEN = 61810;
	public final static int NOM_CONC_CREA = 61811;
	public final static int NOM_CONC_LACT = 61812;
	public final static int NOM_CONC_BILI_TOT = 61815;
	public final static int NOM_CONC_PROT_SER = 61816;
	public final static int NOM_CONC_PROT_TOT = 61817;
	public final static int NOM_CONC_BILI_DIRECT = 61818;
	public final static int NOM_CONC_LDH = 61819;
	public final static int NOM_ES_RATE = 61820;
	public final static int NOM_CONC_PCT = 61821;
	public final static int NOM_CONC_CREA_KIN_MM = 61823;
	public final static int NOM_CONC_CREA_KIN_SER = 61824;
	public final static int NOM_CONC_CREA_KIN_MB = 61825;
	public final static int NOM_CONC_CHE = 61826;
	public final static int NOM_CONC_CRP = 61827;
	public final static int NOM_CONC_AST = 61828;
	public final static int NOM_CONC_AP = 61829;
	public final static int NOM_CONC_ALPHA_AMYLASE = 61830;
	public final static int NOM_CONC_GPT = 61831;
	public final static int NOM_CONC_GOT = 61832;
	public final static int NOM_CONC_GGT = 61833;
	public final static int NOM_TIME_PD_ACT = 61834;
	public final static int NOM_TIME_PD_PT = 61835;
	public final static int NOM_PT_INTL_NORM_RATIO = 61836;
	public final static int NOM_TIME_PD_aPTT_WB = 61837;
	public final static int NOM_TIME_PD_aPTT_PE = 61838;
	public final static int NOM_TIME_PD_PT_WB = 61839;
	public final static int NOM_TIME_PD_PT_PE = 61840;
	public final static int NOM_TIME_PD_THROMBIN = 61841;
	public final static int NOM_TIME_PD_COAGULATION = 61842;
	public final static int NOM_TIME_PD_THROMBOPLAS = 61843;
	public final static int NOM_FRACT_EXCR_NA = 61844;
	public final static int NOM_CONC_UREA_URINE = 61845;
	public final static int NOM_CONC_CREA_URINE = 61846;
	public final static int NOM_CONC_K_URINE = 61847;
	public final static int NOM_CONC_K_URINE_EXCR = 61848;
	public final static int NOM_CONC_OSM_URINE = 61849;
	public final static int NOM_CONC_GLU_URINE = 61855;
	public final static int NOM_CONC_CHLOR_URINE = 61850;
	public final static int NOM_CONC_PRO_URINE = 61851;
	public final static int NOM_CONC_CA_URINE = 61852;
	public final static int NOM_FLUID_DENS_URINE = 61853;
	public final static int NOM_CONC_HB_URINE = 61854;
	public final static int NOM_ENERGY_BAL = 61861;
	public final static int NOM_ECG_AMPL_ST_BASELINE_I = 62481;
	public final static int NOM_ECG_AMPL_ST_BASELINE_II = 62482;
	public final static int NOM_ECG_AMPL_ST_BASELINE_V1 = 62483;
	public final static int NOM_ECG_AMPL_ST_BASELINE_V2 = 62484;
	public final static int NOM_ECG_AMPL_ST_BASELINE_V3 = 62485;
	public final static int NOM_ECG_AMPL_ST_BASELINE_V4 = 62486;
	public final static int NOM_ECG_AMPL_ST_BASELINE_V5 = 62487;
	public final static int NOM_ECG_AMPL_ST_BASELINE_V6 = 62488;
	public final static int NOM_ECG_AMPL_ST_BASELINE_III = 62541;
	public final static int NOM_ECG_AMPL_ST_BASELINE_AVR = 62542;
	public final static int NOM_ECG_AMPL_ST_BASELINE_AVL = 62543;
	public final static int NOM_ECG_AMPL_ST_BASELINE_AVF = 62544;
	public final static int NOM_AGE = 63504;
	public final static int NOM_AGE_GEST = 63505;
	public final static int NOM_AWAY_CORR_COEF = 63508;
	public final static int NOM_AWAY_RESP_RATE_SPONT = 63509;
	public final static int NOM_AWAY_TC = 63510;
	public final static int NOM_BIRTH_LENGTH = 63512;
	public final static int NOM_BREATH_RAPID_SHALLOW_INDEX = 63513;
	public final static int NOM_C20_PER_C_INDEX = 63514;
	public final static int NOM_CARD_CONTRACT_HEATHER_INDEX = 63516;
	public final static int NOM_CONC_ALP = 63517;
	public final static int NOM_CONC_CA_GEN_NORM = 63522;
	public final static int NOM_CONC_CA_SER = 63524;
	public final static int NOM_CONC_CO2_TOT = 63525;
	public final static int NOM_CONC_CO2_TOT_CALC = 63526;
	public final static int NOM_CONC_CREA_SER = 63527;
	public final static int NOM_RESP_RATE_SPONT = 63528;
	public final static int NOM_CONC_GLO_SER = 63529;
	public final static int NOM_CONC_GLU_SER = 63530;
	public final static int NOM_CONC_HB_CORP_MEAN = 63532;
	public final static int NOM_CONC_K_SER = 63535;
	public final static int NOM_CONC_NA_EXCR = 63536;
	public final static int NOM_CONC_PCO2_ART_ADJ = 63538;
	public final static int NOM_CONC_PCO2_CAP_ADJ = 63539;
	public final static int NOM_CONC_PH_CAP_ADJ = 63543;
	public final static int NOM_CONC_PH_GEN_ADJ = 63544;
	public final static int NOM_CONC_PO2_ART_ADJ = 63547;
	public final static int NOM_CONC_PO2_CAP_ADJ = 63548;
	public final static int NOM_CREA_OSM = 63551;
	public final static int NOM_EEG_BURST_SUPPRN_INDEX = 63552;
	public final static int NOM_EEG_ELEC_POTL_CRTX_GAIN_LEFT = 63553;
	public final static int NOM_EEG_ELEC_POTL_CRTX_GAIN_RIGHT = 63554;
	public final static int NOM_EEG_FREQ_PWR_SPEC_CRTX_MEDIAN_LEFT = 63563;
	public final static int NOM_EEG_FREQ_PWR_SPEC_CRTX_MEDIAN_RIGHT = 63564;
	public final static int NOM_EEG_PWR_SPEC_ALPHA_ABS_LEFT = 63573;
	public final static int NOM_EEG_PWR_SPEC_ALPHA_ABS_RIGHT = 63574;
	public final static int NOM_EEG_PWR_SPEC_BETA_ABS_LEFT = 63579;
	public final static int NOM_EEG_PWR_SPEC_BETA_ABS_RIGHT = 63580;
	public final static int NOM_EEG_PWR_SPEC_DELTA_ABS_LEFT = 63587;
	public final static int NOM_EEG_PWR_SPEC_DELTA_ABS_RIGHT = 63588;
	public final static int NOM_EEG_PWR_SPEC_THETA_ABS_LEFT = 63593;
	public final static int NOM_EEG_PWR_SPEC_THETA_ABS_RIGHT = 63594;
	public final static int NOM_ELEC_EVOK_POTL_CRTX_ACOUSTIC_AAI = 63603;
	public final static int NOM_EXTRACT_O2_INDEX = 63605;
	public final static int NOM_FLOW_AWAY_AIR = 63607;
	public final static int NOM_FLOW_AWAY_EXP_ET = 63610;
	public final static int NOM_FLOW_AWAY_MAX_SPONT = 63613;
	public final static int NOM_FLOW_AWAY_TOT = 63617;
	public final static int NOM_FLOW_CO2_PROD_RESP_TIDAL = 63618;
	public final static int NOM_FLOW_URINE_PREV_24HR = 63619;
	public final static int NOM_FREE_WATER_CLR = 63620;
	public final static int NOM_HB_CORP_MEAN = 63621;
	public final static int NOM_HEATING_PWR_INCUBATOR = 63622;
	public final static int NOM_OUTPUT_CARD_INDEX_ACCEL = 63625;
	public final static int NOM_PTC_CNT = 63627;
	public final static int NOM_PULS_OXIM_PLETH_GAIN = 63629;
	public final static int NOM_RATIO_AWAY_RATE_VOL_AWAY = 63630;
	public final static int NOM_RATIO_BUN_CREA = 63631;
	public final static int NOM_RATIO_CONC_BLD_UREA_NITROGEN_CREA_CALC = 63632;
	public final static int NOM_RATIO_CONC_URINE_CREA_CALC = 63633;
	public final static int NOM_RATIO_CONC_URINE_CREA_SER = 63634;
	public final static int NOM_RATIO_CONC_URINE_NA_K = 63635;
	public final static int NOM_RATIO_PaO2_FIO2 = 63636;
	public final static int NOM_RATIO_TIME_PD_PT = 63637;
	public final static int NOM_RATIO_TIME_PD_PTT = 63638;
	public final static int NOM_RATIO_TRAIN_OF_FOUR = 63639;
	public final static int NOM_RATIO_URINE_SER_OSM = 63640;
	public final static int NOM_RES_AWAY_DYN = 63641;
	public final static int NOM_RESP_BREATH_ASSIST_CNT = 63642;
	public final static int NOM_RIGHT_HEART_FRACT_EJECT = 63643;
	public final static int NOM_TIME_PD_EVOK_REMAIN = 63648;
	public final static int NOM_TIME_PD_EXP = 63649;
	public final static int NOM_TIME_PD_FROM_LAST_MSMT = 63650;
	public final static int NOM_TIME_PD_INSP = 63651;
	public final static int NOM_TIME_PD_KAOLIN_CEPHALINE = 63652;
	public final static int NOM_TIME_PD_PTT = 63653;
	public final static int NOM_TRAIN_OF_FOUR_1 = 63655;
	public final static int NOM_TRAIN_OF_FOUR_2 = 63656;
	public final static int NOM_TRAIN_OF_FOUR_3 = 63657;
	public final static int NOM_TRAIN_OF_FOUR_4 = 63658;
	public final static int NOM_TRAIN_OF_FOUR_CNT = 63659;
	public final static int NOM_TWITCH_AMPL = 63660;
	public final static int NOM_UREA_SER = 63661;
	public final static int NOM_VENT_ACTIVE = 63664;
	public final static int NOM_VENT_AMPL_HFV = 63665;
	public final static int NOM_VENT_CONC_AWAY_AGENT_DELTA = 63666;
	public final static int NOM_VENT_CONC_AWAY_DESFL_DELTA = 63667;
	public final static int NOM_VENT_CONC_AWAY_ENFL_DELTA = 63668;
	public final static int NOM_VENT_CONC_AWAY_HALOTH_DELTA = 63669;
	public final static int NOM_VENT_CONC_AWAY_ISOFL_DELTA = 63670;
	public final static int NOM_VENT_CONC_AWAY_N2O_DELTA = 63671;
	public final static int NOM_VENT_CONC_AWAY_O2_CIRCUIT = 63672;
	public final static int NOM_VENT_CONC_AWAY_SEVOFL_DELTA = 63673;
	public final static int NOM_VENT_PRESS_AWAY_END_EXP_POS_LIMIT_LO = 63674;
	public final static int NOM_VENT_PRESS_AWAY_PV = 63676;
	public final static int NOM_VENT_TIME_PD_RAMP = 63677;
	public final static int NOM_VENT_VOL_AWAY_INSP_TIDAL_HFV = 63678;
	public final static int NOM_VENT_VOL_TIDAL_HFV = 63679;
	public final static int NOM_VOL_AWAY_EXP_TIDAL_SPONT = 63682;
	public final static int NOM_VOL_AWAY_TIDAL_PSV = 63683;
	public final static int NOM_VOL_CORP_MEAN = 63684;
	public final static int NOM_VOL_FLUID_THORAC = 63685;
	public final static int NOM_VOL_FLUID_THORAC_INDEX = 63686;
	public final static int NOM_VOL_LVL_LIQUID_BOTTLE_AGENT = 63687;
	public final static int NOM_VOL_LVL_LIQUID_BOTTLE_DESFL = 63688;
	public final static int NOM_VOL_LVL_LIQUID_BOTTLE_ENFL = 63689;
	public final static int NOM_VOL_LVL_LIQUID_BOTTLE_HALOTH = 63690;
	public final static int NOM_VOL_LVL_LIQUID_BOTTLE_ISOFL = 63691;
	public final static int NOM_VOL_LVL_LIQUID_BOTTLE_SEVOFL = 63692;
	public final static int NOM_VOL_MINUTE_AWAY_INSP_HFV = 63693;
	public final static int NOM_VOL_URINE_BAL_PD_INSTANT = 63694;
	public final static int NOM_VOL_URINE_SHIFT = 63695;
	public final static int NOM_VOL_VENT_L_END_SYS_INDEX = 63697;
	public final static int NOM_WEIGHT_URINE_COL = 63699;
	public final static int NOM_SAT_O2_TISSUE = 63840;
	public final static int NOM_CEREB_STATE_INDEX = 63841;
	public final static int NOM_SAT_O2_GEN_1 = 63842;
	public final static int NOM_SAT_O2_GEN_2 = 63843;
	public final static int NOM_SAT_O2_GEN_3 = 63844;
	public final static int NOM_SAT_O2_GEN_4 = 63845;
	public final static int NOM_TEMP_CORE_GEN_1 = 63846;
	public final static int NOM_TEMP_CORE_GEN_2 = 63847;
	public final static int NOM_PRESS_BLD_DIFF = 63848;
	public final static int NOM_PRESS_BLD_DIFF_GEN_1 = 63852;
	public final static int NOM_PRESS_BLD_DIFF_GEN_2 = 63856;
	public final static int NOM_FLOW_PUMP_HEART_LUNG_MAIN = 63860;
	public final static int NOM_FLOW_PUMP_HEART_LUNG_SLAVE = 63861;
	public final static int NOM_FLOW_PUMP_HEART_LUNG_SUCTION = 63862;
	public final static int NOM_FLOW_PUMP_HEART_LUNG_AUX = 63863;
	public final static int NOM_FLOW_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = 63864;
	public final static int NOM_FLOW_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = 63865;
	public final static int NOM_TIME_PD_PUMP_HEART_LUNG_AUX_SINCE_START = 63866;
	public final static int NOM_TIME_PD_PUMP_HEART_LUNG_AUX_SINCE_STOP = 63867;
	public final static int NOM_VOL_DELIV_PUMP_HEART_LUNG_AUX = 63868;
	public final static int NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_AUX = 63869;
	public final static int NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_AUX = 63870;
	public final static int NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN_SINCE_START = 63871;
	public final static int NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN_SINCE_STOP = 63872;
	public final static int NOM_VOL_DELIV_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = 63873;
	public final static int NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = 63874;
	public final static int NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_CARDIOPLEGIA_MAIN = 63875;
	public final static int NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE_SINCE_START = 63876;
	public final static int NOM_TIME_PD_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE_SINCE_STOP = 63877;
	public final static int NOM_VOL_DELIV_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = 63878;
	public final static int NOM_VOL_DELIV_TOTAL_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = 63879;
	public final static int NOM_TIME_PD_PLEGIA_PUMP_HEART_LUNG_CARDIOPLEGIA_SLAVE = 63880;
	public final static int NOM_RATIO_INSP_TOTAL_BREATH_SPONT = 63888;
	public final static int NOM_VENT_PRESS_AWAY_END_EXP_POS_TOTAL = 63889;
	public final static int NOM_COMPL_LUNG_PAV = 63890;
	public final static int NOM_RES_AWAY_PAV = 63891;
	public final static int NOM_RES_AWAY_EXP_TOTAL = 63892;
	public final static int NOM_ELAS_LUNG_PAV = 63893;
	public final static int NOM_BREATH_RAPID_SHALLOW_INDEX_NORM = 63894;
	public static final short MDS_GEN_SYSTEM_INFO_SYSTEM_PULSE_CHOSEN = 1;
	
	public static final short UNK_F2E1 = (short)0xf2e1;
	public static final short UNK_F2E2 = (short)0xf2e2;
	public static final short UNK_F2E3 = (short)0xf2e3;
	public static final short UNK_F1EC = (short)0xf1ec;

}
