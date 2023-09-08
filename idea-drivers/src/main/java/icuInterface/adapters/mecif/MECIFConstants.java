package icuInterface.adapters.mecif;

public class MECIFConstants {
	
	/*------------------- some character string lengths ------------------*/

	public static final short SPI_ALERT_LENGTH       = 19;
	public static final short SPI_LABEL_LENGTH       = 7;
	public static final short SPI_RT_UNIT_LENGTH     = 5;
	public static final short SPI_UNIT_LENGTH        = 19;
	public static final short SPI_ENUM_LENGTH        = (9 + 1);
	public static final short CDD_DEV_NAME_LENGTH    = (19 + 1);


	/*---------------------- record identifiers --------------------------*/

	public static final short SPI_ABS_TIME_STAMP     = 1;
	public static final short SPI_ALARM_LIMITS       = 3;
	public static final short SPI_CALIBR_PARAM       = 11;
	public static final short SPI_CW_FIXED           = 12;
	public static final short SPI_GAIN_OFFSET        = 15;
	public static final short SPI_NUMERIC            = 17;
	public static final short SPI_NU_FIXED           = 19;
	public static final short SPI_RANGE              = 24;
	public static final short SPI_UNIT               = 28;
	public static final short SPI_WS_FIXED           = 29;
	public static final short SPI_RT_UNIT            = 35;
	public static final short SPI_ENUM               = 42;

	public static final short SPI_CDD_NU_FIXED              = 128;        /* Cdd of MIP-ASW = */
	public static final short SPI_CDD_SET_FIXED             = 129;        /* Cdd of MIP-ASW = */
	public static final short SPI_CDD_DEV_NAME_FIXED        = 130;        /* Cdd of MIP-ASW = */
	public static final short SPI_CDD_TRANSPARENT_FIXED     = 131;        /* Cdd of MIP-ASW = */
	public static final short SPI_CDD_SYNC                  = 132;        /* Cdd of MIP-ASW = */
	public static final short SPI_CDD_EMPTY_MSG             = 255;        /* Cdd of MIP-ASW = */


	/*---------------------- some special values -------------------------*/

	public static final short SpiNaN1               = 0x007f;
	public static final short SpiNaN2               = (short)0xffff;
	public static final int SpiNaN_32             = 0x007fffff;

	public static final short SPI_INV_LEVEL         = (short)0xffff;

	public static final short SPI_MAX_NUMERICS      = 3;     /* number of spi numerics per messge= */

	/* valid Computer <-> HP CMS commands */
	
	public static final short CONNECT_REQ   	=	1;
	public static final short CONNECT_RSP	=	2;
	public static final short TICK_REQ	=	3;
	public static final short TICK_RSP	=	4;
	public static final short OVERFLOW_NOTIFICATION=	5;
	public static final short ABORT_NOTIFICATION=	6;  // abort the connection...you probably didn't respond to a MIRROR_REQ
	public static final short DISCONNECT_REQ	=	7;
	public static final short DISCONNECT_RSP	=	8;
	public static final short DIRECTORY_REQ	=	9;
	public static final short DIRECTORY_RSP	=	10;
	public static final short PAR_LIST_REQ	=	11;
	public static final short PAR_LIST_RSP	=	12;
	public static final short TUNE_REQ	=	13;    // request a set of streamed data
	public static final short TUNE_RSP	=	14;
	public static final short SINGLE_TUNE_REQ	=	15;   // request a set of data, no streaming 
	public static final short SINGLE_TUNE_RSP	=	16;
	public static final short DETUNE_REQ	=	17;
	public static final short DETUNE_RSP	=	18;
	public static final short DETUNE_ALL_REQ	=	19;
	public static final short DETUNE_ALL_RSP	=	20;
	public static final short QUERY_REQ	=	21;
	public static final short QUERY_RSP	=	22;
	public static final short QUERY_LIST_REQ	=	23;
	public static final short QUERY_LIST_RSP	=	24;
	public static final short MIRROR_REQ	=	25;   // ping
	public static final short MIRROR_RSP	=	26;
	public static final short MISC_LIST_REQ	=	27;
	public static final short MISC_LIST_RSP          = 28;
	public static final short RAW_ENABLE_REQ         = 29;
	public static final short RAW_ENABLE_RSP         = 30;
	public static final short TUNE_TYPE_REQ	=	31;
	public static final short TUNE_TYPE_RSP	=	32;
	public static final short SINGLE_TUNE_TYPE_REQ=	33;
	public static final short SINGLE_TUNE_TYPE_RSP=	34;

	/***********************************************************************
	* SOURCE IDs [32768..49151]                                            *
	***********************************************************************/

	public static final int SRC_CardiacOutput           = 32768;  /* see SPI documents      */
	public static final int SRC_CO2                     = 32769;  /* see SPI documents      */
	public static final int SRC_HeartModule = 32770;  /* see SPI documents      */
	public static final int SRC_InvPress    = 32771;  /* see SPI documents      */
	public static final int SRC_NBP                     = 32772;  /* see SPI documents      */
	public static final int SRC_O2                      = 32773;  /* see SPI documents      */
	public static final int SRC_Pleth                   = 32774;  /* see SPI documents      */
	public static final int SRC_Resp                    = 32775;  /* see SPI documents      */
	public static final int SRC_SaO2                    = 32776;  /* see SPI documents      */
	public static final int SRC_Temp                    = 32777;  /* see SPI documents      */
	public static final int SRC_ThreeChanEcg            = 32778;  /* see SPI documents      */
	public static final int SRC_DeltaTemp               = 32779;  /* see SPI documents      */
	public static final int SRC_Wedge                   = 32780;  /* see SPI documents      */
	public static final int SRC_EcgPacer                = 32781;  /* see SPI documents      */
	public static final int SRC_ThreeChanSt             = 32782;  /* see SPI documents      */
	public static final int SRC_TwoChanEeg              = 32783;  /* !!!!  PRELIMINARY  !!! */
	public static final int SRC_BpTool                  = 32784;  /* see SPI documents      */
	public static final int SRC_Cpp                     = 32785;  /* see SPI documents      */
	public static final int SRC_TcpO2                   = 32786;  /* see SPI documents      */
	public static final int SRC_TcpCO2                  = 32787;  /* see SPI documents      */
	public static final int SRC_Unknown789              = 32789;  /* wlb      */

	public static final int SRC_Sdn                     = 32800;  /* see SDN documents      */
	public static final int SRC_Mhi                     = 32801;  /* see MHI documents      */
	public static final int SRC_FeMgr                   = 32802;  /* see MHI documents      */
	public static final int SRC_AlMgr                   = 32803;  /* see ALARM_MGR ERS      */
	public static final int SRC_Arrhy                   = 32804;  /* see SDN documents      */
	public static final int SRC_VCP                     = 32805;  /* see VTP/VCP documents  */
	public static final int SRC_RecMgr                  = 32806;  /* see REC_MGR documents  */
	public static final int SRC_DateTime                = 32807;  /* see DATE & TIME docs   */
	public static final int SRC_Aoc                     = 32808;  /* see MHI AOC docs       */
	public static final int SRC_RestDsp                 = 32809;  /* see MHI documents      */
	public static final int SRC_ErrorHdl                = 32810;  /* see ERROR HANDLER docs */
	public static final int SRC_StatPromptHdl           = 32811;
	public static final int SRC_Loa                     = 32812;  /* see MHI documents      */
	public static final int SRC_RestingTrends           = 32813;  /* see RESTING TRENDS docs*/
	public static final int SRC_ExtendCRG               = 32814;  /* see CRG documents      */
	public static final int SRC_RvtApp                  = 32815;  /* see VTP/VCP documents  */
	public static final int SRC_GlbInfoHdl              = 32816;  /* see GLB INFO HANDL docs*/
	public static final int SRC_OpModHdl                = 32817;  /* see OP MODE HANDL docs */
	public static final int SRC_CalTest                 = 32818;  /* see OP MODE HANDL docs */
	public static final int SRC_NumPos                  = 32819;  /* see MHI documents      */
	public static final int SRC_Excalibur               = 32820;  /* see XCALIBUR documents */
	public static final int SRC_ExcalUpcCalc            = 32821;  /* see XCALIBUR documents */
	public static final int SRC_ExcalUpcTab             = 32822;  /* see XCALIBUR documents */
	public static final int SRC_ExcalUpcTrend           = 32823;  /* see XCALIBUR documents */
	public static final int SRC_ExcalUpcEad1            = 32824;  /* see XCALIBUR documents */
	public static final int SRC_ExcalUpcEad2            = 32825;  /* see XCALIBUR documents */
	public static final int SRC_ExcalUpcEph             = 32826;  /* see XCALIBUR documents */
	public static final int SRC_ExcalEca                = 32827;  /* see XCALIBUR documents */
	public static final int SRC_ExcalEdb                = 32828;  /* see XCALIBUR documents */
	public static final int SRC_ExcalEda                = 32829;  /* see XCALIBUR documents */
	public static final int SRC_ExcalEhc                = 32830;  /* see XCALIBUR documents */
	public static final int SRC_ExcalUpcConfg           = 32832;  /* see XCALIBUR documents */
	public static final int SRC_ExcalEdq                = 32833;  /* see XCALIBUR documents */
	public static final int SRC_ExcalTransf             = 32834;  /* see XCALIBUR documents */
	public static final int SRC_ExcalDrug               = 32835;  /* see XCALIBUR documents */

	public static final int SRC_DelRecMgr               = 32840;
	public static final int SRC_RtRecMgr                = 32841;
	public static final int SRC_RecWaves                = 32842;
	public static final int SRC_StoRecMgr               = 32843;

	public static final int SRC_StripRec                = 32850;  /* see STRIP REC docs     */
	public static final int SRC_SdnRec                  = 32851;
	public static final int SRC_FelpRec                 = 32852;  /* see FE LINK REC docs   */
	public static final int SRC_Unknown859              = 32859;  /* wlb      */

	public static final int SRC_AnalogOut               = 32860;  /* see ANALOG OUTPUT docs */
	public static final int SRC_MipTypeB                = 32861;  /* see MIP documents      */
	public static final int SRC_MipTypeC                = 32862;  /* see MIP documents      */
	public static final int SRC_MipTypeA                = 32863;  /* see MIP documents      */
	public static final int SRC_Rs232Mgr                = 32864;  /* see MECIF documents    */
	public static final int SRC_ParServer               = 32865;  /* see MECIF documents    */
	public static final int SRC_TwServer                = 32866;  /* see MECIF documents    */
	public static final int SRC_LanMgr                  = 32870;  /* see LAN documents      */

	/***********************************************************************
	* CHANNEL IDs [32768..49151]                                           *
	***********************************************************************/

	public static final int CHA_AWRR                  = 32768;  /* see SPI documents      */
	public static final int CHA_BeatDetect            = 32769;  /* see SPI documents      */
	public static final int CHA_CO2                   = 32770;  /* see SPI documents      */
	public static final int CHA_CuffPress             = 32771;  /* see SPI documents      */
	public static final int CHA_ETCO2                 = 32772;  /* see SPI documents      */
	public static final int CHA_EarlySyst             = 32773;  /* see SPI documents      */
	public static final int CHA_Ecg                   = 32774;  /* see SPI documents      */
	public static final int CHA_FIO2                  = 32775;  /* see SPI documents      */
	public static final int CHA_General               = 32776;  /* see SPI documents      */
	public static final int CHA_HeartRate             = 32777;  /* see SPI documents      */
	public static final int CHA_IMCO2                 = 32778;  /* see SPI documents      */
	public static final int CHA_OxygenSatur           = 32779;  /* see SPI documents      */
	public static final int CHA_Pleth                 = 32780;  /* see SPI documents      */
	public static final int CHA_Press                 = 32781;  /* see SPI documents      */
	public static final int CHA_PressNum              = 32782;  /* see SPI documents      */
	public static final int CHA_Pulse                 = 32783;  /* see SPI documents      */
	public static final int CHA_PulseRate             = 32784;  /* see SPI documents      */
	public static final int CHA_RelativePerf          = 32785;  /* see SPI documents      */
	public static final int CHA_RespDetect            = 32786;  /* see SPI documents      */
	public static final int CHA_Temp                  = 32787;  /* see SPI documents      */
	public static final int CHA_CardiacOutput         = 32788;  /* see SPI documents      */
	public static final int CHA_Resp                  = 32789;  /* see SPI documents      */
	public static final int CHA_St                    = 32790;  /* see SPI documents      */
	public static final int CHA_Eeg                   = 32791;  /* !!!!  PRELIMINARY  !!! */
	public static final int CHA_TcpO2                 = 32792;  /* see SPI documents      */
	public static final int CHA_TcpCO2                = 32793;  /* see SPI documents      */
	public static final int CHA_SiteTime              = 32794;  /* see SPI documents      */

	public static final int CHA_Arrhy                 = 32800;  /* see SDN documents      */
	public static final int CHA_Overview              = 32801;  /* see SDN documents      */
	public static final int CHA_AutoAlDsp             = 32802;  /* see SDN documents      */
	public static final int CHA_EctSta                = 32803;  /* see SDN documents      */
	public static final int CHA_RhySta                = 32804;  /* see SDN documents      */
	public static final int CHA_Vpb                   = 32805;  /* see SDN documents      */
	public static final int CHA_SdnText               = 32806;  /* see SDN documents      */
	public static final int CHA_SdnTime               = 32807;  /* see SDN documents      */

	public static final int CHA_Text                  = 32809;
	public static final int CHA_Config                = 32810;
	public static final int CHA_Device                = 32811;
	public static final int CHA_Fast                  = 32812;
	public static final int CHA_Slow                  = 32813;
	public static final int CHA_Control               = 32814;
	public static final int CHA_Scan                  = 32815;
	public static final int CHA_Sort                  = 32816;
	public static final int CHA_Async                 = 32817;
	public static final int CHA_Sync                  = 32818;
	public static final int CHA_Test                  = 32819;
	public static final int CHA_AlRes                 = 32820;  /* see ALARM_MGR ERS      */
	public static final int CHA_AlStat                = 32821;  /* see ALARM_MGR ERS      */
	public static final int CHA_AlText                = 32822;  /* see ALARM_MGR ERS      */
	public static final int CHA_InText                = 32823;  /* see ALARM_MGR ERS      */
	public static final int CHA_NumEnh                = 32824;  /* see ALARM_MGR ERS      */
	public static final int CHA_NurseRelay            = 32825;  /* see ALARM_MGR ERS      */
	public static final int CHA_RemSil                = 32826;  /* see ALARM_MGR ERS      */
	public static final int CHA_ToHil                 = 32827;  /* see ALARM_MGR ERS      */
	public static final int CHA_ToFields              = 32828;
	public static final int CHA_MhiKeys               = 32829;
	public static final int CHA_MipWave               = 32830;  /* see MIP documents      */
	public static final int CHA_MipNum                = 32831;  /* see MIP documents      */
	public static final int CHA_RemSus                = 32832;  /* see ALARM_MGR ERS      */

	public static final int CHA_VCP                   = 32840;  /* see VTP/VCP documents  */
	public static final int CHA_LVT                   = 32841;  /* see VTP/VCP documents  */
	public static final int CHA_RVT                   = 32842;  /* see VTP/VCP documents  */
	public static final int CHA_DBQ                   = 32843;  /* see VTP/VCP documents  */

	public static final int CHA_Etm                   = 32844;  /* see EXCALIBUR docs     */
	public static final int CHA_Etb                   = 32845;  /* see EXCALIBUR docs     */
	public static final int CHA_UpcCalc               = 32846;  /* see EXCALIBUR docs     */
	public static final int CHA_Ead1                  = 32847;  /* see EXCALIBUR docs     */
	public static final int CHA_Eph                   = 32849;  /* see EXCALIBUR docs     */
	public static final int CHA_Edb                   = 32850;  /* see EXCALIBUR docs     */
	public static final int CHA_Eda                   = 32851;  /* see EXCALIBUR docs     */
	public static final int CHA_Ehc                   = 32852;  /* see EXCALIBUR docs     */
	public static final int CHA_Eup                   = 32853;  /* see EXCALIBUR docs     */
	public static final int CHA_Eca                   = 32854;  /* see EXCALIBUR docs     */
	public static final int CHA_Edq                   = 32855;  /* see EXCALIBUR docs     */
	public static final int CHA_Edt                   = 32856;  /* see EXCALIBUR docs     */

	public static final int CHA_Recorder              = 32860;  /* see REC_MGR documents  */
	public static final int CHA_Delayed               = 32861;  /* see REC_MGR documents  */
	public static final int CHA_Realtime              = 32862;  /* see REC_MGR documents  */
	public static final int CHA_Recording             = 32863;

	public static final int CHA_DateTime              = 32870;  /* see DATE & TIME docs   */
	public static final int CHA_Settings              = 32871;  /* see SETTINGS TRANSFER  */


	/*-------- additional Channel Ids for TELEMETRY [3xxxx..33399] -------*/

	public static final int CHA_Stored                = 32880;  /* see MAGIC documents    */
	public static final int CHA_InopCtl               = 32890;  /* see MAGIC documents    */
	public static final int CHA_InopRd                = 32891;  /* see MAGIC documents    */


	/*----- additional Channel Ids for CENTRAL STATION [33400..33999] ----*/

	public static final int CHA_Gbn1                  = 33440;  /* see GENESIS documents  */
	public static final int CHA_Gbn2                  = 33441;  /* see GENESIS documents  */
	public static final int CHA_Gbn3                  = 33442;  /* see GENESIS documents  */
	public static final int CHA_Gbn4                  = 33443;  /* see GENESIS documents  */
	public static final int CHA_Gbn5                  = 33444;  /* see GENESIS documents  */
	public static final int CHA_Gbn6                  = 33445;  /* see GENESIS documents  */
	public static final int CHA_Gbn7                  = 33446;  /* see GENESIS documents  */
	public static final int CHA_Gbn8                  = 33447;  /* see GENESIS documents  */
	public static final int CHA_Gbn9                  = 33448;  /* see GENESIS documents  */
	public static final int CHA_Gbn10                 = 33449;  /* see GENESIS documents  */
	public static final int CHA_Gbn11                 = 33450;  /* see GENESIS documents  */
	public static final int CHA_Gbn12                 = 33451;  /* see GENESIS documents  */
	public static final int CHA_NoGbn                 = 33452;  /* see GENESIS documents  */
	public static final int CHA_DelayAssign           = 33453;  /* see GENESIS documents  */
	public static final int CHA_DelayDeassign         = 33454;  /* see GENESIS documents  */


	/*---------- additional Channel Ids for NOMAD [34000..34199] ---------*/


	/*-------- additional Channel Ids for CATH LAB [34200..34399] --------*/


	public static final int CHA_Unspec                = 49151;  /* unspecified channel    */


	/***********************************************************************
	* TYPE IDs [1..65534]                                                  *
	***********************************************************************/

	public static final short TYP_SpiPS                     = 1;  /* see SPI documents      */
	public static final short TYP_SpiCW                     = 2;  /* see SPI documents      */
	public static final short TYP_SpiWS                     = 3;  /* see SPI documents      */
	public static final short TYP_SpiEV                     = 4;  /* see SPI documents      */
	public static final short TYP_SpiBV                     = 5;  /* see SPI documents      */
	public static final short TYP_SpiBS                     = 6;  /* see SPI documents      */
	public static final short TYP_SpiNU                     = 7;  /* see SPI documents      */
	public static final short TYP_SpiST                     = 8;  /* see SPI documents      */
	public static final short TYP_SpiPR                     = 9;  /* see SPI documents      */
	public static final short TYP_SpiAL                    = 10;  /* see SPI documents      */
	public static final short TYP_SpiIN                    = 11;  /* see SPI documents      */
	public static final short TYP_SpiOR                    = 13;  /* see SPI documents      */
	public static final short TYP_SpiOP                    = 14;  /* see SPI documents      */
	public static final short TYP_SpiTR                    = 15;  /* see SPI documents      */
	public static final short TYP_SpiAN                    = 16;  /* see SPI documents      */
	public static final short TYP_SpiMX                    = 17;  /* see SPI documents      */
	public static final short TYP_SpiIC                    = 18;  /* see SPI documents      */

	public static final short TYP_SdnBedlb                 = 20;  /* see SDN documents      */
	public static final short TYP_SdnPni                   = 21;  /* see SDN documents      */
	public static final short TYP_SdnTime                  = 22;  /* see SDN documents      */
	public static final short TYP_SdnCW                    = 23;  /* see SDN documents      */

	public static final short TYP_Data                     = 25;  /* see TPL documents      */
	public static final short TYP_Req                      = 26;  /* see TPL documents      */
	public static final short TYP_Rsp                      = 27;  /* see TPL documents      */

	public static final short TYP_Key                      = 30;  /* see MHI documents      */

	public static final short TYP_AppOpnReq                = 40;  /* see VTP/VCP documents  */
	public static final short TYP_AppClsReq                = 41;  /* see VTP/VCP documents  */
	public static final short TYP_AppOpnChk                = 42;  /* see VTP/VCP documents  */
	public static final short TYP_AppClsChk                = 43;  /* see VTP/VCP documents  */
	public static final short TYP_Wv1Ctl                   = 44;  /* see VTP/VCP documents  */
	public static final short TYP_Wv2Ctl                   = 45;  /* see VTP/VCP documents  */
	public static final short TYP_LVTCtl                   = 46;  /* see VTP/VCP documents  */
	public static final short TYP_VTWvAnnot                = 47;  /* see VTP/VCP documents  */

	public static final short TYP_Edb                      = 50;  /* see EXCALIBUR docs     */
	public static final short TYP_Eda                      = 51;  /* see EXCALIBUR docs     */
	public static final short TYP_Ehc                      = 52;  /* see EXCALIBUR docs     */
	public static final short TYP_Eup                      = 53;  /* see EXCALIBUR docs     */
	public static final short TYP_Eca                      = 54;  /* see EXCALIBUR docs     */
	public static final short TYP_Edt                      = 55;  /* see EXCALIBUR docs     */
	public static final short TYP_Eph                      = 56;  /* see EXCALIBUR docs     */
	public static final short TYP_Dyn                      = 58;  /* see EXCALIBUR docs     */
	public static final short TYP_Bdcst                    = 59;  /* see EXCALIBUR docs     */
	public static final short TYP_Etm                      = 60;  /* see EXCALIBUR docs     */
	public static final short TYP_Etb                      = 61;  /* see EXCALIBUR docs     */
	public static final short TYP_UpcCalc                  = 62;  /* see EXCALIBUR docs     */
	public static final short TYP_Ead1                     = 63;  /* see EXCALIBUR docs     */
	public static final short TYP_Edq                      = 65;  /* see EXCALIBUR docs     */

	public static final short TYP_Change                   = 68;
	public static final short TYP_Error                    = 69;
	public static final short TYP_Status                   = 70;
	public static final short TYP_Control                  = 71;
	public static final short TYP_Info                     = 72;
	public static final short TYP_Input                    = 73;
	public static final short TYP_Output                   = 74;

	public static final short TYP_Capability               = 75;  /* see LOG REC COMM docs  */
	public static final short TYP_RecOpReq                 = 76;  /* see LOG REC COMM docs  */
	public static final short TYP_RecOpChk                 = 77;  /* see LOG REC COMM docs  */
	public static final short TYP_Config                   = 78;  /* see RECORD WAVES docs  */

	public static final short TYP_MhiOSAl                  = 80;  /* see MHI documents     */
	public static final short TYP_MhiOSCapt                = 81;  /* see MHI documents     */
	public static final short TYP_MhiOSInstr               = 82;  /* see MHI documents      */
	public static final short TYP_MhiOSMark                = 83;  /* see MHI documents      */
	public static final short TYP_MhiOSMon                 = 84;  /* see MHI documents      */
	public static final short TYP_MhiOSOvw                 = 85;  /* see MHI documents      */
	public static final short TYP_MhiOSPar                 = 86;  /* see MHI documents      */
	public static final short TYP_MhiOSPat                 = 87;  /* see MHI documents      */
	public static final short TYP_MhiOSRec                 = 88;  /* see MHI documents      */
	public static final short TYP_Numerics                 = 90;  /* see MHI documents      */
	public static final short TYP_Speeds                   = 91;  /* see MHI documents      */
	public static final short TYP_TraceMode                = 92;  /* see MHI documents      */
	public static final short TYP_Waves                    = 93;  /* see MHI documents      */
	public static final short TYP_Colors                   = 94;  /* see MHI documents      */

	public static final short TYP_MakInternal             = 100;  /* see MAK documents      */

	public static final short TYP_RVTAppl                 = 120;  /* see VTP/VCP documents  */
	public static final short TYP_RVTGen                  = 121;  /* see VTP/VCP documents  */
	public static final short TYP_RVTDspCmplt             = 122;  /* see VTP/VCP documents  */
	public static final short TYP_RVTAppStChk             = 123;  /* see VTP/VCP documents  */
	public static final short TYP_RVTSesUpdChk            = 124;  /* see VTP/VCP documents  */
	public static final short TYP_RVTDspUpdChk            = 125;  /* see VTP/VCP documents  */
	public static final short TYP_RVTDspCtlChk            = 126;  /* see VTP/VCP documents  */
	public static final short TYP_RVTWvAnnReq             = 127;  /* see VTP/VCP documents  */

	public static final short TYP_Isu                     = 128;  /* preliminary MAGIC sdn  */
	public static final short TYP_PicCtl                  = 132;  /* preliminary MAGIC sdn  */
	public static final short TYP_CtlReq                  = 134;  /* MAGIC MUA module       */
	public static final short TYP_CtlChk                  = 135;  /* MAGIC MUA module       */
	public static final short TYP_MUAChk                  = 136;  /* MAGIC MUA module       */
	public static final short TYP_LdSetCtl                = 137;  /* MAGIC MUA module       */
	public static final short TYP_ExtMonCtl               = 138;  /* MAGIC MUA module       */
	public static final short TYP_Vcp                     = 141;  /* MAGIC MUA module       */
	public static final short TYP_Vtp                     = 142;  /* MAGIC MUA module       */
	public static final short TYP_BedCtl                  = 144;  /* MAGIC MUA module       */
	public static final short TYP_DlyReq                  = 150;  /* see MAGIC Recorder ES  */
	public static final short TYP_DlyChk                  = 151;  /* see MAGIC Recorder ES  */
	public static final short TYP_StoredReq               = 152;  /* see MAGIC Recorder ES  */
	public static final short TYP_StoredChk               = 153;  /* see MAGIC Recorder ES  */
	public static final short TYP_AnnotReq                = 154;  /* see MAGIC Recorder ES  */
	public static final short TYP_StopReq                 = 156;  /* see MAGIC Recorder ES  */
	public static final short TYP_StopChk                 = 157;  /* see MAGIC Recorder ES  */
	public static final short TYP_StopNotif               = 158;  /* see MAGIC Recorder ES  */
	public static final short TYP_ClrReq                  = 160;  /* see MAGIC Inop docs    */
	public static final short TYP_ClrChk                  = 161;  /* see MAGIC Inop docs    */
	public static final short TYP_FilterReq               = 162;  /* see MAGIC Inop docs    */
	public static final short TYP_FilterChk               = 163;  /* see MAGIC Inop docs    */
	public static final short TYP_DataReq                 = 164;  /* see MAGIC Inop docs    */
	public static final short TYP_DataChk                 = 165;  /* see MAGIC Inop docs    */
	public static final short TYP_TotalsReq               = 166;  /* see MAGIC Inop docs    */
	public static final short TYP_TotalsChk               = 167;  /* see MAGIC Inop docs    */

	public static final short TYP_VolCtl                  = 168;  /* see NOMAD documents    */


	/*------- additional Type Ids for CENTRAL STATION [1000..1999] -------*/

	public static final short TYP_DemoReq                = 1000;  /* Patient demograph. req.*/
	public static final short TYP_Demographics           = 1001;  /* Patient demographics   */
	public static final short TYP_SdnBranch              = 1002;  /* SDN branch number      */
	public static final short TYP_SdnDspAssign           = 1003;  /* SDN display sector
	                                               assignment             */
	public static final short TYP_SdnUnitStat            = 1004;  /* SDN unit status        */
	public static final short TYP_PerseusMap             = 1005;  /* Perseus channel map    */
	public static final short TYP_GbnAssign              = 1006;
	public static final short TYP_GbnUnassign            = 1007;
	public static final short TYP_FiltTime               = 1008;  /* filtered SDN time      */
	public static final short TYP_Csa                    = 1009;  /* SDN Central Station
	                                               arrhythmia             */
	public static final short TYP_GbnInfo                = 1010;  /* Gbn Information        */
	public static final short TYP_GbnOnOff               = 1011;
	public static final short TYP_LbnGbnMap              = 1012;
	public static final short TYP_NetCensus              = 1013;  /* SDN Network Census     */
	public static final short TYP_SdnOnline              = 1014;  /* SDN Online Notification*/
	public static final short TYP_TuneWv                 = 1015;  /* Tune SDN Wave          */
	public static final short TYP_TuneWvAck              = 1016;  /* Tune SDN Wave Ack      */
	public static final short TYP_StWvStop               = 1017;
	public static final short TYP_SdnBL                  = 1018;  /* SDN Bed Label          */
	public static final short TYP_PkdSdnBL               = 1019;  /* Packed SDN Bed Label   */
	public static final short TYP_PkdSdnPni              = 1020;  /* Packed SDN Patient Name*/
	public static final short TYP_SdnAS                  = 1021;  /* SDN alert status       */
	public static final short TYP_SdnAT                  = 1022;  /* SDN alarm text         */
	public static final short TYP_PkdSdnAT               = 1023;  /* Packed SDN alarm text  */
	public static final short TYP_SdnIT                  = 1024;  /* SDN inop text          */
	public static final short TYP_PkdSdnIT               = 1025;  /* Packed SDN inop text   */
	public static final short TYP_SdnAR                  = 1026;  /* SDN alarm reset        */
	public static final short TYP_SdnWV                  = 1027;  /* SDN wave value         */
	public static final short TYP_PkdSdnWV               = 1028;  /* Packed SDN wave value  */
	public static final short TYP_SdnWSD                 = 1029;  /* SDN wave support data  */
	public static final short TYP_PkdSdnWSD              = 1030;  /* Packed SDN wave support
	                                               Data                   */
	public static final short TYP_SdnPV                  = 1031;  /* SDN parameter value    */
	public static final short TYP_SdnPSD                 = 1032;  /* SDN parameter support
	                                               data                   */
	public static final short TYP_PkdSdnPSD              = 1033;  /* Packed SDN PSD         */
	public static final short TYP_Isb                    = 1034;  /* SDN instrument status
	                                                - bed                 */
	public static final short TYP_Isr                    = 1035;  /* SDN instrument status
	                                                - recorder            */
	public static final short TYP_PkdIsr                 = 1036;  /* Packed SDN IS-R        */
	public static final short TYP_PkdIsu                 = 1037;  /* Packed SDN IS-U        */
	public static final short TYP_MaintStatus            = 1038;  /* SDN Maintenance Status */
	public static final short TYP_PkdCsa                 = 1039;  /* Packed Central Station
	                                               arrhythmia             */
	public static final short TYP_SdnSwHdr               = 1040;  /* SDN stored wave hdrs   */
	public static final short TYP_SdnBackoff             = 1041;  /* SDN backoff            */
	public static final short TYP_RecReq                 = 1042;  /* Record request         */
	public static final short TYP_RecOp                  = 1043;  /* Record operate         */
	public static final short TYP_TxReq                  = 1044;
	public static final short TYP_Ws                     = 1045;
	public static final short TYP_DataCap                = 1046;
	public static final short TYP_AnnotData              = 1047;
	public static final short TYP_FormName               = 1048;
	public static final short TYP_PerConf                = 1049;
	public static final short TYP_SectorAssign           = 1050;
	public static final short TYP_DisplayForm            = 1051;
	public static final short TYP_HRLimits               = 1052;
	public static final short TYP_Discharge              = 1053;

	
	public String[] RealtimeUnitCode = { "", // 0 - [ Blank unit string ]
			"cm", // 1 - [ centimeter ]
			"kg", // 2 - [ kilograms ]
			"mOsm", // 3 - [ milli-osmoles ]
			"hrs", // 4 - [ hours ]
			"\011Emin", // 5 [ liter per minute; used for MINVOL, C.O. ]
			"ml", // 6 [ milli-liter ]
			null, // 7
			null, // 8
			null, // 9
			"m\011A", // 10 [ square meters; used for the Body Surface Area ]
			"bpm", // 11 [ beats per minute; used for HR, PULSE ]
			"mmHg", // 12 [ unit for pressures ]
			null, "%", // 14 [ percentage ]
			null, null, null, "cm\0120O", // 18 [ cmH2O; used for pressure units
			// ]
			"rpm", // 19 [ respirations per minute ]
			null, // 20
			null, // 21
			null, // 22
			null, // 23
			null, // 24
			null, // 25
			null, // 26
			null, // 27
			"\011C", // 28 [ degrees Celsius ]
			"kPa", // 29 [ kilo-Pascal; used for gas and pressure parameters ]
			"hPa", // 30 [ hecto-Pascal; unit for pressures ]
			"mbar", // 31 [ millibar; unit for pressures ]
			null, // 32
			"\011D", // 33 [ degrees Fahrenheit ]
			"ml/h", // 34 [ milli-liters per hour ]
			null, // 35
			null, // 36
			null, // 37
			null, // 38
			null, // 39
			null, // 40
			null, // 41
			null, // 42
			"g", // 43 [ grams; used for weight ]
			"in\011A", // 44 [ sqare inches; used for Body Surface Area ]
			"1mV", // 45 [ Unit indication near the 1mV bar in the ECG waves ]
			"1Ohm", // 46 [ Unit indication near the gain bar in the RESP wave ]
			"Ohms", // 47 [ Unit indication for the Z0 display ]
			"min", // 48 [ minutes ]
			"m", // 49 [ meter ]
			"mm", // 50 [ millimeters for ST Segment analysis ]
			"mV", // 51 [ millivolts for ST Segment analysis ]
			null, // 52
			"sec", // 53 [ seconds ]
			"V", // 54 [ Volts ]
			"l", // 55 [ liter; used for TV, VC ]
			null, // 56
			"l/sec", // 57 [ l/sec; used for AWF ]
			null, // 58
			"Hz", // 59 [ Hertz - used for the HF Ventilation Frequency and for
			// EEG ]
			"uV", // 60 [ microvolts for ST Analysis ]
			"pW", // 61 [ picowatt: Used by the EEG parameter ]
			"nW", // 62 [ nanowatt: Used by the EEG parameter ]
			null, // 63
			"%PCV", // 64 [ % of packed cell volume. Used by the HCT
			// (Hematocrit) parameter ]
			"g/l", // 65 [ Used by the Hemoglobin parameter (HGB) ]
			null, // 66
			null, // 67
			null, // 68
			"1/nl", // 69 [ Unit for the WBC (Wide Blood Cell) parameter. ]
			"mEq", // 70 [ Milli-Equivalents unit. ]
			null, // 71
			null, // 72
			null, // 73
			"mmol", // 74 [ Milli-Mol. Used by various blood parameters. ]
			null, // 75
			null, // 76
			null, // 77
			null, // 78
			null, // 79
			"kOhm", // 80 [ kilo Ohms (unit indication for eeg electrode
			// impedance). ]
			null, // 81
			"mA", // 82 [ Milli-Ampere - Used by the TOF Watch parameter. ]
			"uC", // 83 [ Micro-Coulomb - Used by the TOF Watch parameters. ]
			"usec", // 84 [ Micro-Seconds - Used by the TOF Watch parameter. ]
			"dB", // 85 [ Decibel - Used by the Aspect A-2000 box. ]
			"msec" // 86 [ Milli-Seconds. ]
	};

	public String[] UnitCode = { "", // 0 [ Blank unit string ]
			"cm", // 1 [ centimeter ]
			"kg", // 2 [ kilograms ]
			"mOsm", // 3 [ milli-osmoles ]
			"hours", // 4 [ hours ]
			"l/min", // 5 [ liter per minute; used for MINVOL, C.O. ]
			"ml", // 6 [ milli-liter; used for Tv, Vd, SV ]
			"DS/cm\011B", // 7 [ dyne-sec/cm^5 used for SVR, PVR ]
			"kg-m", // 8 [ used for LCW, RCW ]
			"g-m", // 9 [ used for LVSW, RVSW ]
			"m\011A", // 10 [ sqare meter; used for Body Surface Area ]
			"bpm", // 11 [ beats per minute; used for HR, PULSE ]
			"mmHg", // 12 [ mmHg; used for PRESS, CO2, ]
			"", // 13 [ unitless fraction = blank string ]
			"%", // 14 [ percentage; used for O2, SpO2 ]
			"g/dl", // 15 [ gram per dezi-liter; used for HGB ]
			"ml/dl", // 16 [ milli-liter per dezi-liter; used for CaO2, CvO2,
			// avDO2 ]
			"ml/min", // 17 [ milli-liter per minute; used for O2AV, VO2, ALVENT
			// ]
			"cmH\011FO", // 18 [ cmH2O; used for airway pressures ]
			"rpm", // 19 [ respirations per minute; used for RESP rate ]
			"ml/cmH\011FO", // 21 [ milli-liter per cmH2O ]
			"mEq/l", // 22 [ milli-equivalents per liter ]
			"mg/dl", // 23 [ milli-gram per dezi-liter ]
			"mOsm/l", // 24 [ milli-osmoles per liter ]
			"ml/day", // 25 [ milli-liter per day ]
			"mEq/day", // 26 [ milli-equivalents per day ]
			"ml/min/m\011A", // 27 [ milli-liter per minute per square meter ]
			"\011C", // 28 [ degrees Celsius ]
			"kpa", // 29 [ kilo-Pascal; used for PRESS, CO2 ]
			"hpa", // 30 [ hecto-Pascal; used for PRESS, CO2 ]
			"mbar", // 31 [ millibar ]
			"mmol/l", // 32 [ millimoles per liter; used for Hgb ]
			"\011D", // 33 [ degrees Fahrenheit ]
			"ml/h", // 34 [ milli-liters per hour ]
			"oz", // 35 [ ounce; used for weigth ]
			"lb", // 36 [ pound; used for weigth ]
			"in", // 37 [ inch; used for heigth ]
			"l/min/m\011A", // 38 [ liter per minute per square meter; used for
			// C.I. ]
			"ml/m\011A", // 39 [ milli-liter per square meter; used for SVI ]
			"DSm\011A/cm\011B", // 40 [ used for SVRI, PVRI ]
			"kg-m/m\011A", // 41 [ used for LCWI, RCWI ]
			"g-m/m\011A", // 42 [ used for LVSWI, RVSWI ]
			"g", // 43 [ grams; used for weight ]
			"in\011A", // 44 [ sqare inches; used for Body Surface Area ]
			"1mV", // 45 [ Unit indication near the 1mV bar in the ECG waves ]
			"1Ohm", // 46 [ Unit indication near the gain bar in the RESP wave ]
			"Ohms", // 47 [ Unit indication for the Z0 display ]
			"min", // 48 [ minutes ]
			"m", // 49 [ meter ]
			"mm", // 50 [ millimeters for ST Segment analysis ]
			"mV", // 51 [ millivolts for ST Segment analysis ]
			"weeks", // 52 [ weeks; used for gestational age ]
			"sec ", // 53 [ seconds ]
			"V", // 54 [ Volts ]
			"l", // 55 [ liter; used for TV, VC ]
			"cmH\011FO/\011Es", // 56 [ cmH2O/l/sec; used for Lung Resistance ]
			"l/sec", // 57 [ l/sec; used for AWF ]
			"ml\011A/sec", // 58 [ ml^2/sec - used for High Frequency (HF)
			// Transport : DCO2 ]
			"Hz", // 59 Coefficient[ Hertz - used for the HF Ventilation
			// Frequency and for EEG ]
			"uV", // 60 [ microvolts for ST Analysis ]
			"pW", // 61 [ picowatt: Used by the EEG parameter ]
			"nW", // 62 [ nanowatt: Used by the EEG parameter ]
			"uV p-p", // 63 [ microvolts Peak to Peak ]
			"%PCV", // 64 [ % of packed cell volume. Used by the HCT
			// (Hematocrit) parameter ]
			"g/l", // 65 [ Used by the Hemoglobin parameter (HGB) ]
			"mg/cm\0121", // 66 [ Unit for the density of the urine ]
			"Years", // 67 [ Year(s). Used by the "Age" parameter ]
			"l/day", // 68 [ Daily Urine Output. ]
			"1/nl", // 69 [ Unit for the WBC (Wide Blood Cell) parameter. ]
			"mEq", // 70 [ Milli-Equivalents unit. ]
			"umol/l", // 71 [ Micro-Mol per liter. ]
			"mmHg/%", // 72 [ Ratio of mmHg unit to the % unit. ]
			"kPa/%", // 73 [ Ratio of kPa unit to the % unit. ]
			"mmol", // 74 [ Milli-Mol. Used by various blood parameters. ]
			"cmH\011FOa/%", // 75 [ Ratio of cmH2O unit to the % unit. ]
			"mol/mol", // 76 [ Ratio of mol to the mol unit. Used by the
			// BUN/Creatinine and Urea Creatinine ratio parameters.
			// ]
			"mg/mg", // 77 [ Ratio of milligramm to milligramm unit. Used by the
			// BUN/Creatinine and Urea/Creatinine ratio parameters.
			// ]
			"cm\0120O*s/l", // 78[ Is identical with the cmH2O/l/sec (see item
			"cmH\011FO/1", // 79 [ cmH2O/l
			"kOhm", // 80 [ kilo Ohms (unit indication for eeg electrode
			// impedance). ]
			"ml/kg", // 81 [ Milli-liter per kilogram. Used by the EVLWI
			// parameter delivered by the pCCO measurement. ]
			"mA", // 82 [ Milli-Ampere - Used by the TOF Watch parameter. ]
			"uC", // 83 [ Micro-Coulomb - Used by the TOF Watch parameters. ]
			"usec", // 84 [ Micro-Seconds - Used by the TOF Watch parameter. ]
			"dB", // 85 [ Decibel - Used by the Aspect A-2000 box. ]
			"msec", // 86 [ Milli-Seconds. ]
			"10*bpm/ml" // 87 [ Beats per minute / Milli-liter. Is used by the
	// Draeger Babylog to indicate the rate/volume ratio. ]
	};

	public String[] ErrorMessages = { null, // 0
			"window size overflow (RX RS232 -> TX MPB)", // 1
			"TX buffer overflow (RX MPB -> TX RS232)", // 2
			"RS232 HW-handshake malfunction", // 3
			"MPB RX FIFO overflow (not used)", // 4
			"RS232 RX parity error", // 5
			"reserved for Computer rx_error: ABORT connection", // 6
			"reserved for Computer rx_error: lifetick timeout ", // 7
			"reserved for Computer rx_error: lifetick failed", // 8
			"reserved for Computer rx_error: no rsp on MIRROR_REQ", // 9
			"reserved for Computer rx_error: no rsp on DIRECTORY_REQ", // 10
			null, // 11
			"reserved for Computer rx_error: no rsp on CONNECT_REQ", // 12
			"reserved for Computer rx_error: no rsp on DISCONNECT_REQ", // 13
			"reserved for Computer rx_error: message lost", // 14
			"reserved for Computer rx_error: invalid command", // 15
			null, null, null, null, // 16-19
			"RS232 restart: MPB RX FIFO overflow", // 20
			"RS232 restart: unspecific RS232 card fatal error" // 21
	};

}
