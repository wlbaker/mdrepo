
#ifndef PISTA_PROPAQM_PROTOCOL_H_
#define PISTA_PROPAQM_PROTOCOL_H_

#include <stdint.h>
#include "pista.h"
#include "pista-internal.h"

#include "propaqm.pb-c.h"

#include <stdbool.h>
#include "libwebsockets.h"
#include <yajl/yajl_parse.h>  


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _StdHdr
{
    int elapsedTime;
    int msecTime;
    int recId;
    char devDateTime[22];
    char GUID[34];
} StdHdr;

typedef struct _NewCase 
{
    StdHdr hdr;
    char caseLabel[64];
    int _at_TdrRecVer;
    char UniqueCaseId[34];
} NewCase;

typedef struct _AnnotationEvt
{
    StdHdr hdr;
    char _at_EvtName[64];
    int treatmentSummary;
    int devEvtCode;
    char xidCode[32];
    char payload[32];
    int _at_TdrRecVer;
} AnnotationEvt;

typedef struct _Val
{
    char typ;
	int  ival;
	char sval[16];
	int _at_units;
	char _at_unitsVal[20];
} Val;

typedef struct _TrendData
{
     int alarm;
     int dataStatus;
     Val val;
     char dataState[32];
} TrendData;

typedef struct _TrendVar
{
    TrendData td;
    char srcLabelVal[32];
    int srcLabel;
    int _at_type;
    int chanState;
} TrendVar;

typedef struct _TrendVarSpo2
{
	TrendVar spco;
	TrendVar spmet;
	TrendVar pvi;
	TrendVar pi;
	TrendVar spoc;
	TrendVar sphb;
} TrendVarSpo2;

typedef struct _TrendVarSDM
{
	int chanState;
	int dispForm;
	TrendVar map;
	TrendVar sys;
	TrendVar dia;
	int time;
} TrendVarSDM;

typedef struct _Trend
{
    char ltaStateVal[16];
    int  ltaState;
    TrendVar temp[3];
    TrendVar hr;
    TrendVar fico2;
    TrendVarSpo2 spo2;
    int patMode;
    TrendVarSDM nibp;
    TrendVarSDM ibp[3];
    TrendVar etco2;
    TrendVar resp;
} Trend;

typedef struct _TrendRpt
{
    StdHdr hdr;
    int CntId;
    char TrendStatus[64];
    int _at_TdrRecVer;
    int DevEvtCode;
    char xidCode[16];
    // global Trend trend;
} TrendRpt;

typedef struct _NumericsReport
{
    StdHdr hdr;
    int CntId;
    char TrendStatus[64];
    int _at_TdrRecVer;
    int DevEvtCode;
    char xidCode[16];
    // global Trend trend;
} NumericsReport;

typedef struct _DataChannel
{
    int chanType;
    int scalar;
    int valueDataType;
    int scalarType;
} DataChannel;

typedef struct _PatientData // official
{
    Val weight;
    Val height;
    char firstName[32];
    char middleName[32];
    char lastName[32];
    char patientId[32];
    char roomNo[16];
    char patientMode[16];
    char sex[16];
    int age;
    int patMode;
    int gender;
} PatientData;

typedef struct _PatientInfo // official
{
    StdHdr hdr;
    PatientData patientData;
    int _at_TdrRecVer;
} PatientInfo;

typedef struct _DataChannels
{
    StdHdr hdr;
    int nchannels;
    DataChannel channel[64];
} DataChannels;

typedef struct _WaveRec
{
    int waveType;
    int frameSize;
    int _at_dataType;
    int sampleTime;
    int  n_samples;
    int  *unpackedSamples;
} WaveRec;

typedef struct _WaveSetting
{
    char unitsVal[16];
    int waveType;
    // traceScale
    // responseFilt
    int units;
    int generalData;
    // dataSrc
    char wavetypeVar[16];
} WaveSetting;

typedef struct _Waveform
{
    int status;
    char statusVal[16];
    int _at_waveNum;
    WaveRec rec;
    WaveSetting waveSetting;
    int offset;
} Waveform;

typedef struct _ContinWaveRec
{
    StdHdr hdr;
    int nexport_waves;
    Waveform waveform[3];
    char headerData[64];
    int  notchSetting;
    int  patMode;
    int  ecgLeadLabels;
    int _at_TdrRecVer;
} ContinWaveRec;

typedef struct _SnapshotRpt
{
    StdHdr hdr;
    int  ecgLeadLbl;
    int  devEvtCode;
    int nexport_waves;
    Waveform waveform[3];
    int preEventSampleTime;
    char hdrData[16];
    char snapshotId[34];
    char uniqueCaseId[34];
    char treatmentLbl[34];
    int  notchSetting;
    int  pacerState;
    int  syncState;
    int  patMode;
    int  snapshotType;
    int _at_TdrRecVer;
} SnapshotRpt;

typedef struct _PrtTrace
{
    StdHdr hdr;
} PrtTrace;

typedef struct _SysLogEntry
{
    StdHdr hdr;
} SysLogEntry;

typedef struct _DeviceConfiguration
{
    StdHdr hdr;
} DeviceConfiguration;

typedef struct _TreatmentSnapshotEvt
{
    StdHdr hdr;
    char _at_EventName[16];
    char treatmentLbl[16];
    int  treatmentSummary;
    int  devEvtCode;
    char xidCode[16];
    char payload[32];
    int  _at_TdrRecVer;
} TreatmentSnapshotEvt;

typedef struct _DefibFireEvt
{
    StdHdr hdr;
    char errors[16];
    char warnings[16];
    int  devEvtCode;
    int  energyDel;
    int  patImpedance;
    int  initialCurrent;
    int  schedule;
    int  shockCnt;
    int  treatmentSummary;
    int  energySel;
    int  patientTti;
    int  chargeTime;
    char xidCode[16];
    int  _at_TdrRecVer;
} DefibFireEvt;

typedef struct _DefibTrace
{
    StdHdr hdr;
} DefibTrace;

typedef struct _FullDisclosureRecord
{
    NewCase new_case;
    AnnotationEvt anno;
    TrendRpt      meta;
    DataChannels  channels;
    PatientInfo patientInfo;
    ContinWaveRec export_waves;
    //SysLogRec
    //DefibTrace
} FullDisclosureRecord;

typedef struct propaqm_context {

#ifdef _WIN32
    HANDLE htid;
#else
    pthread_t propaqm_thread;
#endif
    bool run_thread;
    int  tick;


    const char *user;
    const char *host;

    char host_ip[32];

    unsigned int rl_heartbeat;
	unsigned int rl_zoll_ws;
	unsigned int rl_zoll_rest;

    struct lws *wsi_zoll_ws;
    struct lws *wsi_zoll_rest;

    char comet_uripath[100];
    char encoded_auth[64];
    char double_encoded_auth[64];
    bool send_zoll_heartbeat;

    yajl_handle zws_hand;  
    yajl_handle ztr_hand;  

	struct lws_client_connect_info comet_ci;
	struct lws_client_connect_info wf_ci;
	struct lws_client_connect_info rest_ci;
	struct lws_context *context;

    struct pista_data_packet vi;
    struct pista_data_packet wi;

 	Propaqm__Vitals v;
 	Propaqm__Sensors w;

    /*
     * state variables for the waveform parser
     */
    int arr_pos;
    int arr_max;
    int *arr_dest;

    int wave_num;  // current wave number
    int wave_status;

    bool enable_wss;
    bool enable_numerics;

    /*
     * state variables for the trend parser
     */
    char *ztr_keystack[16];
    NewCase dNewCase;
    ContinWaveRec dContinWave;
    AnnotationEvt dAnnotationEvt;
    DeviceConfiguration dDevice;
    DefibFireEvt      dDefibEvt;
    SysLogEntry         dSysLog;
    DefibTrace dDefibTrace;
    PrtTrace      dPrt;
    PatientInfo   dPatient;
    SnapshotRpt   dSnapshot;
    TreatmentSnapshotEvt dTreatment;
    TrendRpt   dTrendRpt;
    NumericsReport dNumericsReport;
    Trend      dTrend;

    Waveform  *dWaveform;
    TrendVar  *dTrendVar;
    Val       *dVal;
    char *dString;
    int  *dInt;
    int  *bufPtr;
    int   bufAvail;

    int   dIdx;
    int   dWaveIdx;
    int   dStringSize;

    StdHdr *dStdHdr;

} PROPAQM_context;


void PROPAQM_process_pkt( const struct pista_dev_inst *h, const char *recv_buf, int len );

extern struct pista_dev_driver propaqm_driver_info;


// privates
// extern int atoi_n( const char *buf, size_t len );
extern yajl_callbacks zws_callbacks;
extern yajl_callbacks ztr_callbacks;

void zws_reset();
void ztr_reset();

int PROPAQ_discovery_init( void *discovery_callback, void *discovery_private );
int PROPAQ_discovery_tick( );
int PROPAQ_discovery_destroy( );

struct pista_dev_driver *PROPAQM_init( struct pista_context *pista_ctx );
int PROPAQM_allocate( struct pista_dev_inst *di );
int PROPAQM_connect( struct pista_dev_inst *di );
int PROPAQM_tick( const struct pista_dev_inst *di );
int PROPAQM_disconnect( struct pista_dev_inst *di );
int PROPAQM_destroy(struct pista_dev_inst *di);
int PROPAQM_config_set(const struct pista_dev_inst *h, const char *key, const void *settings );
int PROPAQM_set_event_handler( struct pista_dev_inst *di, eventfunc_t handler, void *cb_data );
int PROPAQM_dump(const struct pista_dev_inst *h, pista_dump_flags flags);


int PROPAQM_ztr_set_verbose(int verbose);

void PROPAQM_initDumper(FILE *fp);
void PROPAQM_dump_set_file(const char *name, FILE *fp);
void PROPAQM_dumpAnnotation( AnnotationEvt *anno );
void PROPAQM_dumpSnapshot( FILE *fp, SnapshotRpt *snap );
void PROPAQM_dumpWaveforms( ContinWaveRec *cw ) ;
void PROPAQM_dumpPatientInfo( PatientInfo *pi );
void PROPAQM_dumpTrendReport(FILE *fp, StdHdr *hdr, Trend *trend, bool headers_only);
void PROPAQM_dumpNumericsReport(FILE *fp, StdHdr *hdr, Trend *trend );
void PROPAQM_dumpNewCase( NewCase *nc );
void PROPAQM_dumpDefibFireEv( DefibFireEvt *df );
void PROPAQM_dumpTreatmentShapshotEvt( TreatmentSnapshotEvt *tmt );


extern FILE *ftrend;
extern FILE *fpatient;
extern FILE *fanno;
extern FILE *fsnap;
extern FILE *ftsnap;
extern FILE *fwaves;

extern bool firstTrendReport;
extern bool export_waves;
extern bool export_events;

#ifdef __cplusplus
}
#endif

#endif
