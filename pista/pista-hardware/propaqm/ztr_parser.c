#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include <yajl/yajl_parse.h>  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h>

#include <stdint.h>  
#include <inttypes.h>  

#include "propaqm.h"

#pragma GCC diagnostic ignored "-Wpointer-sign"

static int depth = 0;
static int verbose = 0;

#define IGNORE_INT me->dInt = &ignore;
#define IGNORE_STRING ;

#define LOG_PREFIX "ztr_parser"

static int   ignore;  // a temporary destination to PROPAQM_dumpflag intentionally ignored int values
static char  ignoreString[32];
static bool  parse_array = false;
static int   sampleBuf[6000];

bool export_events = true;
bool export_waves = true;
bool PROPAQM_dumpflag = false;


// static int arr_pos;
#define TABS "\t              "

static int atoi_n( const char *s, size_t l) {
    char buf[24];
    int  val = 0;

    if( l < sizeof(buf) ) {

        memcpy(buf, s, l);
        buf[l+1] = '\0';
        val = atoi(buf);
    }

    return val;
}

#ifdef _WIN32
static char *strndup(char *stringVal, int stringLen) 
{
	char *v = malloc( stringLen + 1 );
	strncpy( v, stringVal, stringLen );
	v[stringLen] = '\0';

	return v;
}
#endif

int PROPAQM_ztr_set_verbose(int v) 
{
        verbose = v;
        return PISTA_OK;
}

void ztr_reset() {
    depth = 0;
}

static int ztr_parser_null(void * ctx)  
{  
    printf("reform null\n");
    return 1; // yajl_gen_status_ok == yajl_gen_null(g);  
}  
  
static int ztr_parser_boolean(void * ctx, int boolean)  
{  
    printf("reform boolean: %d\n", boolean );
    return 1; // yajl_gen_status_ok == yajl_gen_bool(g, boolean);  
}  
  
static int ztr_parser_number(void * ctx, const char * s, size_t l)  
{  
    const struct pista_dev_inst *h = (struct pista_dev_inst *)ctx;
    PROPAQM_context *me = (PROPAQM_context *)h->priv;
    char * key = me->ztr_keystack[depth];

    if( verbose > 1 ) {
        printf("DEBUG: key=%s val=%.*s\n", key, l, s );
    }

    if( depth < 1 ) {
        // ignore
    } else if(me->dInt != NULL ) {
        *me->dInt = atoi_n( s, l);
        me->dInt = NULL;
    } else if(me->dVal != NULL ) {

        if( strcmp("#text", key) == 0 ) {
            me->dVal->ival = atoi_n( s, l);
            me->dVal->typ  = 'I';
        } else if( strcmp("@Units", key) == 0 ) { 
            me->dVal->_at_units = atoi_n( s, l);
        } else {
            // printf("DEBUG: Angry Child does not know where to put numbers: [%d]%.*s.\n", (int)l, (int)l, s);
        }
    } else if(parse_array) { // && me->bufPtr != NULL && me->dWaveform != NULL ) {
        if( me->bufPtr == NULL ) {
            printf("[ZERO");
            for( int i = 0; i <= depth; i++ ) {
                printf(".%s", me->ztr_keystack[i] );
            }
            printf("]");
        } else {
            if( me->bufAvail <= 0 ) {
                lwsl_err("OUT OF ROOM in ztr_parser");
                exit(2);
            }
            if( me->dWaveform == NULL ) {
                lwsl_err("INTERNAL ERROR ztr_parser");
                exit(3);
            }
            *(me->bufPtr++) = atoi_n( s, l);
            me->bufAvail--;
            me->dWaveform->rec.n_samples++;
        }
    } else {
        if( verbose > 2 ) {
            lwsl_notice("[%d] Could not find number destination %s = %.*s\n", depth, key, (int)l, s );
        }
    }

    return 1;
}  
  
static int ztr_parser_string(void * ctx, const unsigned char *s, size_t l)  
{  

    const struct pista_dev_inst *h = (struct pista_dev_inst *)ctx;
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    char * key = me->ztr_keystack[depth];

    if( verbose > 1 ) {
        lwsl_notice("parse-string %.*s%s=%.*s\n", depth, TABS, key, (int)l, s );
    }

    if( me->dString != NULL) {
        if( l >= me->dStringSize ) {
            lwsl_warn("WARNING: clipping string: %s = %.*s\n", key, (int)l, s);
            l = me->dStringSize - 1;
        }
        strncpy( me->dString, s, l );
        me->dString[l+1] = '\0';

        me->dString = NULL;
    } else {
        char *top = NULL;
        if( depth > 0 ) {
                top = me->ztr_keystack[depth-1];
        }
        if( verbose > 0 ) {
                lwsl_warn("[%d] UNKNOWN DESTINATION for parse-string %s.%s=%.*s\n", depth, top, key, (int)l, s );
        }
    }

    return 1;
}  
  
static int ztr_parser_map_key(void * ctx, const unsigned char * stringVal,  
                            size_t stringLen)  
{  
    const struct pista_dev_inst *h = (struct pista_dev_inst *)ctx;
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    me->ztr_keystack[depth] = strndup((char *)stringVal, stringLen);

    if( depth == 0 ) {
        // initialize values
        memset( &me->v, 0, sizeof(me->v));
    } else {
            char *subkey = me->ztr_keystack[depth-1];
        if( subkey == NULL ) {
            if( verbose ) {
                    printf("[%d] NULL KEY\n", depth);
            }
        } else if( strcmp("ZOLL", subkey) == 0 ) {
            me->dInt = NULL;
            if( strncmp( "@SchemaVersion", stringVal, stringLen ) == 0 ) {
                // me->dInt = &zoll.schemaVersion;
                IGNORE_INT;
            }
        } else if( strcmp("NewCase", subkey) == 0 ) {
            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dNewCase.hdr;
            } else if( strncmp( "CaseLabel", stringVal, stringLen ) == 0 ) {
                me->dString = me->dNewCase.caseLabel;
                me->dStringSize = sizeof( me->dNewCase.caseLabel);
            } else if( strncmp( "UniqueCaseId", stringVal, stringLen ) == 0 ) {
                me->dString = me->dNewCase.UniqueCaseId;
                me->dStringSize = sizeof( me->dNewCase.UniqueCaseId);
            } else if( strncmp( "@TdrRecVer", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dNewCase._at_TdrRecVer;
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("StdHdr", subkey) == 0 ) {
            if( me->dStdHdr == NULL ) {
                // ignore
            } else if( strncmp( "GUID", stringVal, stringLen ) == 0 ) {
                me->dString = me->dStdHdr->GUID;
                me->dStringSize = sizeof( me->dStdHdr->GUID );
            } else if( strncmp( "ElapsedTime", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dStdHdr->elapsedTime;
            } else if( strncmp( "RecId", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dStdHdr->recId;
            } else if( strncmp( "DevDateTime", stringVal, stringLen ) == 0 ) {
                me->dString = me->dStdHdr->devDateTime;
                me->dStringSize = sizeof( me->dStdHdr->devDateTime );
            } else if( strncmp( "MsecTime", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dStdHdr->msecTime;
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }

        } else if( strcmp("AnnotationEvt", subkey) == 0 ) {
            if( strncmp( "@EvtName", stringVal, stringLen ) == 0 ) {
                me->dString = me->dAnnotationEvt._at_EvtName;
                me->dStringSize = sizeof( me->dAnnotationEvt._at_EvtName );
            } else if( strncmp( "TreatmentSummary", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dAnnotationEvt.treatmentSummary;
            } else if( strncmp( "DevEvtCode", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dAnnotationEvt.devEvtCode;
            } else if( strncmp( "XidCode", stringVal, stringLen ) == 0 ) {
                me->dString = me->dAnnotationEvt.xidCode;
                me->dStringSize = sizeof( me->dAnnotationEvt.xidCode);
            } else if( strncmp( "Payload", stringVal, stringLen ) == 0 ) {
                me->dString = me->dAnnotationEvt.payload;
                me->dStringSize = sizeof( me->dAnnotationEvt.payload);
            } else if( strncmp( "@TdrRecVer", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dAnnotationEvt._at_TdrRecVer;
            } else if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dAnnotationEvt.hdr;
            } else if( strncmp( "CableId", stringVal, stringLen ) == 0 ) {
               // ignore
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }

        } else if( strcmp("Ibp", subkey) == 0 ) {
            if( strncmp( "Map", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.ibp[me->dIdx].map;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "Dia", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.ibp[me->dIdx].dia;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "Sys", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.ibp[me->dIdx].sys;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "chanState", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrend.ibp[me->dIdx].chanState;
                *(me->dInt) = 0;
            } else if( strncmp( "dispForm", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrend.ibp[me->dIdx].dispForm;
                *(me->dInt) = 0;
            } else if( strncmp( "Time", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrend.ibp[me->dIdx].time;
                *(me->dInt) = 0;
            } else if( strncmp( "SrcLabelVal", stringVal, stringLen ) == 0 ) {
                me->dString = ignoreString;
                me->dStringSize = sizeof( ignoreString );
            } else if( strncmp( "SrcLabel", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "ChanState", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "DispForm", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "@ChanNum", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "@Seq", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "IbpDataSrc", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("Nibp", subkey) == 0 ) {
            if( strncmp( "Map", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.nibp.map;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "Dia", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.nibp.dia;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "Sys", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.nibp.sys;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "chanState", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrend.nibp.chanState;
                *(me->dInt) = 0;
            } else if( strncmp( "dispForm", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrend.nibp.dispForm;
                *(me->dInt) = 0;
            } else if( strncmp( "Time", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrend.nibp.time;
                *(me->dInt) = 0;
            } else if( strncmp( "ChanState", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "DispForm", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("Spo2", subkey) == 0 ) {
            if( strncmp( "SpCo", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.spo2.spco;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "SpMet", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.spo2.spmet;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "PVI", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.spo2.pvi;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "PI", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.spo2.pi;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "SpOC", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.spo2.spoc;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "SpHb", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.spo2.sphb;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "ChanState", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "HighLimOn", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "LowLimOn", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "TrendData", stringVal, stringLen ) == 0 ) {
                // printf("FIXME: %s/%.*s\n", subkey, stringLen, stringVal );
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("Trend", subkey) == 0 ) {
            if( strncmp( "LtaState", stringVal, stringLen ) == 0 ) {   // subtile...this has to come before LtaStateVal
                me->dInt = &me->dTrend.ltaState;
            } else if( strncmp( "LtaStateVal", stringVal, stringLen ) == 0 ) {
                me->dString = me->dTrend.ltaStateVal;
                me->dStringSize = sizeof( me->dTrend.ltaStateVal);
            } else if( strncmp( "PatMode", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrend.patMode;
            } else if( strncmp( "Temp", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.temp[0];
                me->dTrendVar->td.val.ival = 0;
                me->dIdx = -1;
            } else if( strncmp( "Hr", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.hr;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "Fico2", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.fico2;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "Spo2", stringVal, stringLen ) == 0 ) {
                // handle seperately
            } else if( strncmp( "Nibp", stringVal, stringLen ) == 0 ) {
                // handle seperately
            } else if( strncmp( "Ibp", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.ibp[0].map;
                me->dTrendVar->td.val.ival = 0;
                me->dIdx = -1;
            } else if( strncmp( "Etco2", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.etco2;
                me->dTrendVar->td.val.ival = 0;
            } else if( strncmp( "Resp", stringVal, stringLen ) == 0 ) {
                me->dTrendVar = &me->dTrend.resp;
                me->dTrendVar->td.val.ival = 0;
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("PatientInfo", subkey) == 0 ) {
            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dPatient.hdr;
            } else if( strncmp( "PatientData", stringVal, stringLen ) == 0 ) {
                    // handled independently
            } else if( strncmp( "@TdrRecVer", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dPatient._at_TdrRecVer;
                *(me->dInt) = 0;
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("TreatmentSnapshotEvt", subkey) == 0 ) {
            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dTreatment.hdr;
            } else if( strncmp( "Payload", stringVal, stringLen ) == 0 ) {
                me->dString = me->dTreatment.payload;
                me->dStringSize = sizeof( me->dTreatment.payload);
            } else if( strncmp( "XidCode", stringVal, stringLen ) == 0 ) {
                me->dString = me->dTreatment.xidCode;
                me->dStringSize = sizeof( me->dTreatment.xidCode);
            } else if( strncmp( "TreatmentLbl", stringVal, stringLen ) == 0 ) {
                me->dString = me->dTreatment.treatmentLbl;
                me->dStringSize = sizeof( me->dTreatment.treatmentLbl );
            } else if( strncmp( "@EvtName", stringVal, stringLen ) == 0 ) {
                me->dString = me->dTreatment._at_EventName;
                me->dStringSize = sizeof( me->dTreatment._at_EventName );
            } else if( strncmp( "@TdrRecVer", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTreatment._at_TdrRecVer;
                *(me->dInt) = 0;
            } else if( strncmp( "TreatmentSummary", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTreatment.treatmentSummary;
                *(me->dInt) = 0;
            } else if( strncmp( "DevEvtCode", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTreatment.devEvtCode;
            } else {
                printf("TSE MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("DefibFireEvt", subkey) == 0 ) {
            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dDefibEvt.hdr;
            } else if( strncmp( "Errors", stringVal, stringLen ) == 0 ) {
                me->dString = me->dDefibEvt.errors;
                me->dStringSize = sizeof( me->dDefibEvt.errors );
            } else if( strncmp( "Warnings", stringVal, stringLen ) == 0 ) {
                me->dString = me->dDefibEvt.warnings;
                me->dStringSize = sizeof( me->dDefibEvt.warnings);
            } else if( strncmp( "XidCode", stringVal, stringLen ) == 0 ) {
                me->dString = me->dDefibEvt.xidCode;
                me->dStringSize = sizeof( me->dDefibEvt.xidCode );
            } else if( strncmp( "DevEvtCode", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dDefibEvt.devEvtCode;
                *(me->dInt) = 0;
            } else if( strncmp( "EnergyDel", stringVal, stringLen ) == 0 ) {  // Both!
                me->dInt = &me->dDefibEvt.energyDel;
                *(me->dInt) = 0;
            } else if( strncmp( "PatImpedance", stringVal, stringLen ) == 0 ) {  // Both!
                me->dInt = &me->dDefibEvt.patImpedance;
                *(me->dInt) = 0;
            } else if( strncmp( "InitialCurrent", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dDefibEvt.initialCurrent;
                *(me->dInt) = 0;
            } else if( strncmp( "Schedule", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dDefibEvt.schedule;
                *(me->dInt) = 0;
            } else if( strncmp( "ShockCnt", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dDefibEvt.shockCnt;
                *(me->dInt) = 0;
            } else if( strncmp( "TreatmentSummary", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dDefibEvt.treatmentSummary;
                *(me->dInt) = 0;
            } else if( strncmp( "EnergySel", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dDefibEvt.energySel;
                *(me->dInt) = 0;
            } else if( strncmp( "PatientTti", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dDefibEvt.patientTti;
                *(me->dInt) = 0;
            } else if( strncmp( "ChargeTime", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dDefibEvt.chargeTime;
                *(me->dInt) = 0;
            } else if( strncmp( "@TdrRecVer", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dDefibEvt._at_TdrRecVer;
                *(me->dInt) = 0;
            } else {
                printf("DEFIB MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
            }
        } else if( strcmp("PatientData", subkey) == 0 ) {
            if( strncmp( "Weight", stringVal, stringLen ) == 0 ) {
                me->dVal = &me->dPatient.patientData.weight;
                me->dVal->ival = 0;
            } else if( strncmp( "Height", stringVal, stringLen ) == 0 ) {
                me->dVal = &me->dPatient.patientData.height;
                me->dVal->ival = 0;
            } else if( strncmp( "FirstName", stringVal, stringLen ) == 0 ) {
                me->dString = me->dPatient.patientData.firstName;
                me->dStringSize = sizeof( me->dPatient.patientData.firstName);
            } else if( strncmp( "MiddleName", stringVal, stringLen ) == 0 ) {
                me->dString = me->dPatient.patientData.middleName;
                me->dStringSize = sizeof( me->dPatient.patientData.middleName);
            } else if( strncmp( "LastName", stringVal, stringLen ) == 0 ) {
                me->dString = me->dPatient.patientData.lastName;
                me->dStringSize = sizeof( me->dPatient.patientData.lastName);
            } else if( strncmp( "RoomNo", stringVal, stringLen ) == 0 ) {
                me->dString = me->dPatient.patientData.roomNo;
                me->dStringSize = sizeof( me->dPatient.patientData.roomNo);
            } else if( strncmp( "PatientId", stringVal, stringLen ) == 0 ) {
                me->dString = me->dPatient.patientData.patientId;
                me->dStringSize = sizeof( me->dPatient.patientData.patientId);
            } else if( strncmp( "Sex", stringVal, stringLen ) == 0 ) {
                me->dString = me->dPatient.patientData.sex;
                me->dStringSize = sizeof( me->dPatient.patientData.sex);
            } else if( strncmp( "Age", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dPatient.patientData.age;
                *(me->dInt) = 0;
            } else if( strncmp( "PatientMode", stringVal, stringLen ) == 0 ) {  // Both!
                me->dInt = &me->dPatient.patientData.patMode;
                *(me->dInt) = 0;
            } else if( strncmp( "PatMode", stringVal, stringLen ) == 0 ) {  // Both!
                me->dInt = &me->dPatient.patientData.patMode;
                *(me->dInt) = 0;
            } else if( strncmp( "Gender", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dPatient.patientData.gender;
                *(me->dInt) = 0;
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
            }
        } else if( strcmp("DefibTrace", subkey) == 0 ) {
            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dDefibTrace.hdr;
            } else {
                // printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
            }
        } else if( strcmp("PrtTrace", subkey) == 0 ) {
            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dPrt.hdr;
            } else {
                // printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
            }
        } else if( strcmp("SysLogEntry", subkey) == 0 ) {
            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dSysLog.hdr;
            } else {
                // printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
            }
        } else if( strcmp("SwVer", subkey) == 0 ) {
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
        } else if( strcmp("Error", subkey) == 0 ) {
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
        } else if( strcmp("WaveRec", subkey) == 0 ) {
            if( strncmp( "UnpackedSamples", stringVal, stringLen ) == 0 ) {
                if( me->dWaveIdx >= 1 && me->dWaveIdx <= 3 ) {
                    parse_array = true;
                    me->dWaveform = &me->dContinWave.waveform[ me->dWaveIdx - 1 ];  // map key
                    me->dWaveform->rec.unpackedSamples = me->bufPtr;
                    me->dWaveform->rec.n_samples = 0;
                } else {
                    printf("PARSING ERROR: Unpacked Samples waveidx=%d\n", me->dWaveIdx );
                    me->dWaveform = NULL;
                }
            } else if( strncmp( "SampleStatus", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "WaveType", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "FrameSize", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "SampleTime", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "WaveTypeVar", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "@DataType", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else {
                printf("WR MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
            }
        } else if( strcmp("Waveform", subkey) == 0 ) {
            if( strncmp( "Status", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "StatusVal", stringVal, stringLen ) == 0 ) {
                // me->dString = me->dWave.statusValue;
                // me->dStringSize = sizeof( me->dWaveRec.statusValue );
            } else if( strncmp( "@WaveNum", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dWaveIdx;
                *(me->dInt) = 0;
            } else if( strncmp( "WaveSetting", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "WaveRec", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "Offset", stringVal, stringLen ) == 0 ) {
                // ignore
            } else {
                printf("WF MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
            }
        } else if( strcmp("ContinWaveRec", subkey) == 0 ) {
            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dContinWave.hdr;
            } else if( strncmp( "Waveform", stringVal, stringLen ) == 0 ) {
                me->bufPtr = sampleBuf;                            // continuous "parser map key" 
                me->bufAvail = sizeof(sampleBuf)/sizeof(int);
                // ignore
            } else if( strncmp( "HeaderData", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "NotchSetting", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "PatMode", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "EcgLeadLabels", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "@TdrRecVer", stringVal, stringLen ) == 0 ) {
                // ignore
            } else {
                printf("CWR MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
            }

        } else if( strcmp("FullDisclosureRecord", subkey) == 0 ) {  // map key
            if( strncmp( "NewCase", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "AnnotationEvt", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "TrendRpt", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "DataChannels", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "PatientInfo", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "ContinWaveRec", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "DefibTrace", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "PrtTrace", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "SysLogEntry", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp("TreatmentSnapshotEvt", stringVal, stringLen) == 0 ) {
                // ignore
            } else if( strncmp("SnapshotRpt", stringVal, stringLen) == 0 ) {
                // ignore
            } else if( strncmp("DefibFireEvt", stringVal, stringLen) == 0 ) {
                // ignore
            } else if( strncmp("DeviceConfiguration", stringVal, stringLen) == 0 ) {
                // ignore
            } else if( strncmp("Aed", stringVal, stringLen) == 0 ) {
                // ignore...unimpl
            } else if( strncmp("TraceConfigs", stringVal, stringLen) == 0 ) {
                // ignore...unimpl
            } else if( strncmp("InstrumentPacket", stringVal, stringLen) == 0 ) {
                // ignore...unimpl
            } else if( strncmp("CaseSummary", stringVal, stringLen) == 0 ) {
                // ignore...unimpl
            } else if( strncmp("AlarmLimits", stringVal, stringLen) == 0 ) {
                // ignore...unimpl
            } else if( strncmp("AlarmEvt", stringVal, stringLen) == 0 ) {
                // ignore...unimpl
            } else if( strncmp("AedContinAnalysis", stringVal, stringLen) == 0 ) {
                // ignore...unimpl
            } else if( strncmp("DisplayInfo", stringVal, stringLen) == 0 ) {
                // ignore...unimpl
            } else {
                printf("Full Disclosure Rec MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
            }
        } else if( strcmp("DeviceConfiguration", subkey) == 0 ) {
            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dDevice.hdr;
            } else if( strncmp( "Waveform", stringVal, stringLen ) == 0 ) {
                // ignore
            } else {
                // printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof(ignoreString);
            }
        } else if( strcmp("OptionConfig", subkey ) == 0 ) {  // device  config
                // printf("ignoring OptionConfig var %.*s\n", stringLen, stringVal );
                IGNORE_INT; // all variables: Co2, Ibp3, Temp, ImpResp, Prt...

        } else if( strcmp("SnapshotRpt", subkey) == 0 ) {
            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dSnapshot.hdr;
            } else if( strncmp( "PreEventSampleTime", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dSnapshot.preEventSampleTime;
            } else if( strncmp( "HdrData", stringVal, stringLen ) == 0 ) {
                me->dString = me->dSnapshot.hdrData;
                me->dStringSize = sizeof( me->dSnapshot.hdrData );
            } else if( strncmp( "SnapshotId", stringVal, stringLen ) == 0 ) {
                me->dString = me->dSnapshot.snapshotId;
                me->dStringSize = sizeof( me->dSnapshot.snapshotId );
            } else if( strncmp( "UniqueCaseId", stringVal, stringLen ) == 0 ) {
                me->dString = me->dSnapshot.uniqueCaseId;
                me->dStringSize = sizeof( me->dSnapshot.uniqueCaseId );
            } else if( strncmp( "TreatmentLbl", stringVal, stringLen ) == 0 ) {
                me->dString = me->dSnapshot.treatmentLbl;
                me->dStringSize = sizeof( me->dSnapshot.treatmentLbl );
            } else if( strncmp( "Trend", stringVal, stringLen ) == 0 ) {
                // global
            } else if( strncmp( "Waveform", stringVal, stringLen ) == 0 ) {
                me->bufPtr = sampleBuf;                         // snapshot "parser map key"
                me->bufAvail = sizeof(sampleBuf)/sizeof(int);
            } else if( strncmp( "ChartSpeed", stringVal, stringLen ) == 0 ) {
                // ignore
            } else if( strncmp( "NotchSetting", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dSnapshot.notchSetting;
            } else if( strncmp( "PacerState", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dSnapshot.pacerState;
            } else if( strncmp( "SyncState", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dSnapshot.syncState;
            } else if( strncmp( "PatMode", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dSnapshot.patMode;
            } else if( strncmp( "EcgLeadLbl", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dSnapshot.ecgLeadLbl;
            } else if( strncmp( "DevEvtCode", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dSnapshot.devEvtCode;
            } else if( strncmp( "SnapshotType", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dSnapshot.snapshotType;
            } else if( strncmp( "@TdrRecVer", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dSnapshot._at_TdrRecVer;
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("Val", subkey) == 0 ) {
            if( strncmp( "@Units", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrendVar->td.val._at_units;
            } else if( strncmp( "@UnitsVal", stringVal, stringLen ) == 0 ) {
                me->dString = me->dTrendVar->td.val._at_unitsVal;
                me->dStringSize = sizeof( me->dTrendVar->td.val._at_unitsVal );
            } else if( strncmp( "@Mode", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "@ModeVal", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
                me->dString = ignoreString;
                me->dStringSize = sizeof( ignoreString );
            } else if( strncmp( "#text", stringVal, stringLen ) == 0 ) {
                                        // always written to me->dTrendVar->td.
                me->dVal = &me->dTrendVar->td.val;
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("TrendData", subkey) == 0 ) {
            if( strncmp( "Alarm", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrendVar->td.alarm;
            } else if( strncmp( "DataStatus", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrendVar->td.dataStatus;
            } else if( strncmp( "DataState", stringVal, stringLen ) == 0 ) {
                me->dString = me->dTrendVar->td.dataState;
                me->dStringSize = sizeof( me->dTrendVar->td.dataState );
            } else if( strncmp( "Val", stringVal, stringLen ) == 0 ) {
                me->dVal = &me->dTrendVar->td.val;
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("TrendRpt", subkey) == 0 ) {

            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dTrendRpt.hdr;
            } else if( strncmp( "CntId", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "@TdrRecVer", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "DevEvtCode", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "Trend", stringVal, stringLen ) == 0 ) {
                // global
            } else if( strncmp( "TrendStatus", stringVal, stringLen ) == 0 ) {
                // WARNING: this is not completely handled!
                me->dString = ignoreString;
                me->dStringSize = sizeof( ignoreString );
            } else if( strncmp( "XidCode", stringVal, stringLen ) == 0 ) {
                me->dString = me->dTrendRpt.xidCode;
                me->dStringSize = sizeof( me->dTrendRpt.xidCode );
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("NumericsReport", subkey) == 0 ) {

            if( strncmp( "StdHdr", stringVal, stringLen ) == 0 ) {
                me->dStdHdr = &me->dNumericsReport.hdr;
            } else if( strncmp( "CntId", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "@TdrRecVer", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "DevEvtCode", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "Trend", stringVal, stringLen ) == 0 ) {
                // global
            } else if( strncmp( "AudioAlarmActive", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "AudioAlarmTrigger", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "Co2ScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "Co2xid", stringVal, stringLen ) == 0 ) {
                IGNORE_STRING;
            } else if( strncmp( "DeltaScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "DeltaXid", stringVal, stringLen ) == 0 ) {
                IGNORE_STRING;
            } else if( strncmp( "HrScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "HrXid", stringVal, stringLen ) == 0 ) {
                IGNORE_STRING;
            } else if( strncmp( "Ibp1ScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "Ibp1Xid", stringVal, stringLen ) == 0 ) {
                IGNORE_STRING;
            } else if( strncmp( "Ibp2ScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "Ibp2Xid", stringVal, stringLen ) == 0 ) {
                IGNORE_STRING;
            } else if( strncmp( "Ibp3ScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "Ibp3Xid", stringVal, stringLen ) == 0 ) {
                IGNORE_STRING;
            } else if( strncmp( "NibpScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "NibpXid", stringVal, stringLen ) == 0 ) {
                IGNORE_STRING;
            } else if( strncmp( "PIScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "PVIScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "RespScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "RespXid", stringVal, stringLen ) == 0 ) {
                IGNORE_STRING;
            } else if( strncmp( "SpHbScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "SpOCScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "SpcoScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "SpmetScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "Spo2ScaleFactor", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "Spo2Xid", stringVal, stringLen ) == 0 ) {
                IGNORE_STRING;
            } else if( strncmp( "Numerics", stringVal, stringLen ) == 0 ) {
                // simple ignore
            } else if( strncmp( "TrendStatus", stringVal, stringLen ) == 0 ) {
                // WARNING: this is not completely handled!
                me->dString = ignoreString;
                me->dStringSize = sizeof( ignoreString );
            } else if( strncmp( "XidCode", stringVal, stringLen ) == 0 ) {
                me->dString = me->dTrendRpt.xidCode;
                me->dStringSize = sizeof( me->dTrendRpt.xidCode );
            } else {
                printf("MISSING: %s/%.*s\n", subkey, (int)stringLen, stringVal );
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;
            }
        } else if( strcmp("DataChannel", subkey) == 0 ) {
            IGNORE_INT;
        } else {
            //bool lastHr = foundHr;
                   //foundHr = ( strcmp("Hr", subkey) == 0 );
                   //if( lastHr != foundHr ) {
                    //printf("DEBUG: Hr found or lost: %d key=%s\n", foundHr, subkey);
            //}
            
            // the TrendData vars slip through the cracks...handle that case as default
            if( strncmp( "SrcLabelVal", stringVal, stringLen ) == 0 ) {
                me->dString = me->dTrendVar->srcLabelVal;
                me->dStringSize = sizeof( me->dTrendVar->srcLabelVal );
            } else if( strncmp( "SrcLabel", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrendVar->srcLabel;
            } else if( strncmp( "@Type", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrendVar->_at_type;
            } else if( strncmp( "ChanState", stringVal, stringLen ) == 0 ) {
                me->dInt = &me->dTrendVar->chanState;
            } else if( strncmp( "Monitoring", stringVal, stringLen ) == 0 ) {
                IGNORE_INT;
            } else if( strncmp( "TrendData", stringVal, stringLen ) == 0 ) {
                // ignore...handled independendently
            } else {
                me->dInt = NULL;
                me->dString = NULL;
                me->dStringSize = 0;
                me->dStdHdr = NULL;

                if( verbose > 0 ) {
                           printf("[%d] %.*s%s sub key: %.*s\n", depth, depth, TABS, subkey, (int)stringLen, stringVal );
                }
            }
        }
    }

    return 1;
}  
  
static int ztr_parser_start_map(void * ctx)  
{  
    const struct pista_dev_inst *h = (struct pista_dev_inst *)ctx;
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    char * key = me->ztr_keystack[depth];

    if( key == NULL ) {
        // ignore?
    } else if( strcmp( key, "" ) == 0 ) {
        // ignore?
    } else if( strcmp( key, "Temp" ) == 0 ) {
        me->dIdx++;
        me->dTrendVar = &me->dTrend.temp[me->dIdx];
        // WARNING: 
    } else if( strcmp( key, "Ibp" ) == 0 ) {
        me->dIdx++;
        me->dTrendVar = &me->dTrend.ibp[me->dIdx].map;
    } else if( strcmp( key, "AnnotationEvt" ) == 0 ) {
        memset( &me->dAnnotationEvt, 0, sizeof( me->dAnnotationEvt ) );
    } else if (strcmp( key, "NewCase") == 0 ) {
        memset( &me->dNewCase, 0, sizeof( me->dNewCase) );
    } else {
        if( verbose > 2 ) {
            printf("No special handling for: %s\n", key);
        }
    }

    if( verbose > 0 ) {
            printf("[%d]%.*s * start-map: %s\n", depth, depth, TABS, key);
    }
    depth++;

    return 1;
}  
  
static int varVal( TrendVar *var ) {
    Val *val = &var->td.val;
    char *dataState = var->td.dataState;

    if( strcmp( dataState, "unmonitored") == 0 ) {
        return 0;
    }
    if( val->typ == 'I' ) {
        return val->ival;
    }

    fprintf(stderr,"UNEXPECTED val typ=%d\n", val->typ );
    return -1;
}

static int ztr_parser_end_map(void * ctx)  
{  
    const struct pista_dev_inst *inst = (struct pista_dev_inst *)ctx;
    PROPAQM_context *me = (PROPAQM_context *)inst->priv;

    depth--;
    if( depth < 0) {
        printf("[**DZ**]");
        depth = 0;
    }
    char * key = me->ztr_keystack[depth];
    if( verbose > 0 ) {
        printf("[%d]%.*s * end-map: %s\n", depth, depth, TABS, key);
    }

    if( key == NULL ) {
        // should only happen ad depth==0
        /*
        printf("[NK");
        for( int i = 0; i <= depth; i++ ) {
            printf(".%s", me->ztr_keystack[i] );
        }
        printf("]");
        */
    } else if( strcmp(key,"AnnotationEvt") == 0 ) {
        if( PROPAQM_dumpflag ) {
	        PROPAQM_dumpAnnotation( &me->dAnnotationEvt );
        }
    } else if( strcmp(key, "TreatmentSnapshotEvt") == 0 ) {
        if( PROPAQM_dumpflag ) {
	        PROPAQM_dumpTreatmentShapshotEvt( &me->dTreatment );
        }
    } else if( strcmp(key, "DefibFireEvt") == 0 ) {
        if( verbose ) printf("[%d] ", depth );
        if( PROPAQM_dumpflag ) {
	        PROPAQM_dumpDefibFireEv( &me->dDefibEvt );
        }
    } else if( strcmp(key, "DefibTrace") == 0 ) {
        // WLB FIXME
        if( verbose ) printf("[%d] ", depth );
        if( PROPAQM_dumpflag ) {
	        // PROPAQM_dumpDefibFireEv( &me->dDefibEvt );
        }
    } else if( strcmp(key,"PatientInfo") == 0 ) {
        if( PROPAQM_dumpflag ) {
            PROPAQM_dumpPatientInfo( &me->dPatient );
        }
        // fire...
    	//if( inst->event_handler != NULL ) {
            //struct pista_data_packet pkt;
            //pista_init_data_packet( &pkt, 0, "propaqm", PISTA_DF_DEMOGRAPHICS, sizeof( me->demog ), &me->demog );
            //inst->event_handler(inst->event_priv, &pkt );
    	//}
    } else if( strcmp(key,"NewCase") == 0 ) {
        if( verbose ) printf("[%d] ", depth );
        if( PROPAQM_dumpflag ) {
            PROPAQM_dumpNewCase( &me->dNewCase );
        }
    } else if( strcmp(key,"TrendRpt") == 0 ) {
        if( PROPAQM_dumpflag ) {
            if( firstTrendReport ) {
                PROPAQM_dumpTrendReport(ftrend, &me->dTrendRpt.hdr, &me->dTrend, true);
                firstTrendReport = false;
            }
            PROPAQM_dumpTrendReport(ftrend, &me->dTrendRpt.hdr, &me->dTrend, false );
        }
    } else if( strcmp(key,"NumericsReport") == 0 ) {

        if( PROPAQM_dumpflag ) {
            PROPAQM_dumpNumericsReport(ftrend, &me->dNumericsReport.hdr, &me->dTrend );
        }
        // fire.....maybe for full patient report?
    	//if( inst->event_handler != NULL ) {
            //struct pista_data_packet pkt;
            //pista_init_data_packet( &pkt, 0, "propaqm", PISTA_DF_MEASUREMENT, sizeof( me->v ), &me->v );
            //inst->event_handler(inst->event_priv, &pkt );
    	//}
    } else if( strcmp(key,"SnapshotRpt") == 0 ) {
        me->bufPtr = NULL;   // end map SnapshotRpt
        if( PROPAQM_dumpflag ) {
            PROPAQM_dumpSnapshot( fsnap, &me->dSnapshot );
        }
    } else if( strcmp(key,"ContinWaveRec") == 0 ) {
        me->bufPtr = NULL;   // end map ContinWaveRec
        if( PROPAQM_dumpflag ) {
            PROPAQM_dumpWaveforms( &me->dContinWave );
        }
        me->bufPtr = NULL;
        me->dWaveform = NULL;
    } else if( strcmp(key,"StdHdr") == 0 ) {
            // do nothing
    } else if( strcmp(key,"PrtTrace") == 0 ) {
            // do nothing
    } else if( strcmp(key,"FullDisclosureRecord") == 0 ) {  // end map

            // do nothing
    } else if( strcmp(key,"FullDisclosure") == 0 ) {
            // do nothing
    } else if( strcmp(key,"PatientData") == 0 ) {
            // do nothing
    } else if( strcmp(key,"CaseSummary") == 0 ) {
            // do nothing
    } else if( strcmp(key,"SysLogEntry") == 0 ) {
            // do nothing
    } else if( strcmp(key,"SwVer") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Error") == 0 ) {
            // do nothing
    } else if( strcmp(key,"WaveRec") == 0 ) {
            me->dWaveform = NULL;
            // do nothing
    } else if( strcmp(key,"Waveform") == 0 ) {
            // do nothing
    } else if( strcmp(key,"WaveSetting") == 0 ) {
            // do nothing
    } else if( strcmp(key,"TrendData") == 0 ) {
            // do nothing
    } else if( strcmp(key,"TraceScale") == 0 ) {
            // do nothing
    } else if( strcmp(key,"ResponseFilt") == 0 ) {
            // do nothing
    } else if( strcmp(key,"DataSrc") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Multiplier") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Val") == 0 ) {
        me->dVal = NULL;
            // do nothing
    } else if( strcmp(key,"Sys") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Dia") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Map") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Temp") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Hr") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Fico2") == 0 ) {
            // do nothing
    } else if( strcmp(key,"SpCo") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Range") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Resp") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Trend") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Etco2") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Ibp") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Nibp") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Spo2") == 0 ) {
            // do nothing
    } else if( strcmp(key,"SpHb") == 0 ) {
            // do nothing
    } else if( strcmp(key,"SpOC") == 0 ) {
            // do nothing
    } else if( strcmp(key,"PI") == 0 ) {
            // do nothing
    } else if( strcmp(key,"PVI") == 0 ) {
            // do nothing
    } else if( strcmp(key,"SpMet") == 0 ) {
            // do nothing
    } else if( strcmp(key,"InstrumentValue") == 0 ) {
            // do nothing
    } else if( strcmp(key,"CentTermVolts") == 0 ) {
            // do nothing
    } else if( strcmp(key,"TrendStatus") == 0 ) {
            // do nothing
    } else if( strcmp(key,"DataChannel") == 0 ) {
            // do nothing
    } else if( strcmp(key,"DataChannels") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Aed") == 0 ) {
            // do nothing
    } else if( strcmp(key,"TraceConfig") == 0 ) {
            // do nothing
    } else if( strcmp(key,"TraceConfigs") == 0 ) {
            // do nothing
    } else if( strcmp(key,"Weight") == 0 ) {
        me->dVal = NULL;
            // do nothing
    } else if( strcmp(key,"Height") == 0 ) {
        me->dVal = NULL;
            // do nothing
    } else if( strcmp(key,"AnalysisResults") == 0 ) {  // Aed
            // do nothing
    } else if( strcmp(key,"AnalysisResult") == 0 ) {  // Aed
            // do nothing
    } else if( strcmp(key,"AnalysisEvts") == 0 ) {  // Aed
            // do nothing
    } else if( strcmp(key,"Analysis") == 0 ) {
            // do nothing
    } else if( strcmp(key,"CprEvts") == 0 ) {  // Aed
            // do nothing
    } else if( strcmp(key,"ElectrodeRls") == 0 ) {
            // do nothing
    } else if( strcmp(key,"ModeEvts") == 0 ) {
            // do nothing
    } else if( strcmp(key,"DefibEvts") == 0 ) {
            // do nothing
    } else if( strcmp(key,"DefibFireEvt") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"OptionConfig") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"DeviceConfiguration") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"InstrumentPacket") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"MultileadImpedances") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"SoftwareVersions") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"ZOLL") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"Numerics") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"HighLimOn") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"LowLimOn") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"AlarmLimits") == 0 ) { 
            // do nothing
    } else if( strcmp(key,"AlarmEvt") == 0 ) { 
            // do nothing
    } else if( strcmp(key, "AedContinAnalysis") == 0 ) {
            // do nothing
    } else if( strcmp(key, "DisplayInfo") == 0 ) {
            // do nothing
    } else {
        printf("UNEXPECTED MAP END: %s\n", key );
    }

    if( depth == 0 ) {
       if( me == NULL ) {
            // no structure to store trend/vitals data
            pista_err("ztr_parser: INTERNAL ERROR NO SELF");
       } else if( inst->event_handler == NULL ) {
            // no one is listening
            pista_err("ztr_parser: FIXME NO EVENT LISTENER");
       } else if( inst->event_priv == NULL ) {
            // no EVENT PRIV!
            pista_err("ztr_parser: FIXME ZTR-H-PRIV");
       } else {
	    // This is a clear sign that we are connected (successfully) to the target device.
            pista_util_send_connection(inst, PISTA_ST_CONNECTED );
            me->tick = 0;

            uint64_t tm_ms =    pista_get_current_time_with_ms();
            uint64_t tm_ms2;
            lwsl_notice("ztr_parser FIXME: tm_ms=%" PRIu64, tm_ms );
            if( tm_ms < 100 * 3600 * 1000 ) {
                // if tm LT 100 hrs, then clock faile and use Zoll device time
                if( me->dStdHdr != NULL && me->dStdHdr->devDateTime != NULL ) {
		            struct tm a_tm;

                    /* First clear the result structure.  */
                    memset (&a_tm, '\0', sizeof (a_tm));

                    /* Try the ISO format first.  */
                    char *cp = strptime (me->dStdHdr->devDateTime, "%Y-%m-%dT%H:%M:%S", &a_tm);
                    time_t t_sec = mktime( &a_tm );
                    tm_ms2 = t_sec * 1000;
                }
                pista_set_current_time_delta( tm_ms2 - tm_ms );
                lwsl_notice("ztr_parser FIXME: set delta=%" PRIu64, tm_ms2 - tm_ms );
                tm_ms = tm_ms2;
            }

            me->v.tm = tm_ms;

            Trend *p = &me->dTrend;
            // int  ltaState;
            me->v.temp0 = varVal( &p->temp[0] );
            me->v.temp1 = varVal( &p->temp[1] );
            me->v.temp2 = varVal( &p->temp[2] );
            me->v.hr    = varVal( &p->hr );
            me->v.patmode  = p->patMode;
            me->v.fico2 = varVal( &p->fico2 );
            me->v.spo2_spco   = varVal( &p->spo2.spco );
            me->v.spo2_spmet  = varVal( &p->spo2.spmet );
            me->v.spo2_pvi    = varVal( &p->spo2.pvi );
            me->v.spo2_pi     = varVal( &p->spo2.pi );
            me->v.spo2_spoc   = varVal( &p->spo2.spoc );
            me->v.spo2_sphb   = varVal( &p->spo2.sphb );
            me->v.spo2_pct   = 0; // varVal( &p->spo2 ); ...probably should not be in dataset
            me->v.nibp_sys  = varVal( &p->nibp.sys );
            me->v.nibp_dia  = varVal( &p->nibp.dia );
            me->v.nibp_map  = varVal( &p->nibp.map );
            me->v.ibp0_sys  = varVal( &p->ibp[0].sys );
            me->v.ibp0_dia  = varVal( &p->ibp[0].dia );
            me->v.ibp0_map  = varVal( &p->ibp[0].map );
            me->v.ibp1_sys  = varVal( &p->ibp[1].sys );
            me->v.ibp1_dia  = varVal( &p->ibp[1].dia );
            me->v.ibp1_map  = varVal( &p->ibp[1].map );
            me->v.ibp2_sys  = varVal( &p->ibp[2].sys );
            me->v.ibp2_dia  = varVal( &p->ibp[2].dia );
            me->v.ibp2_map  = varVal( &p->ibp[2].map );
            me->v.etco2 = varVal( &p->etco2 );
            me->v.resp  = varVal( &p->resp );

            struct pista_data_packet pkt;
            pista_init_data_packet( &pkt, tm_ms, "propaqm", PISTA_DF_MEASUREMENT, sizeof( me->v ), &me->v );

            // fire event_handler( PISTA_DF_MEASUREMENT... pkt )
            inst->event_handler( inst->event_priv, &pkt );
	    memset( p, 0, sizeof( *p ) );
       }
    }

    return 1;
}  
  
static int ztr_parser_start_array(void * ctx)  
{  
    return 1;
}  
  
static int ztr_parser_end_array(void * ctx)  
{  
    parse_array = false;  // selectively turned on, globally turned off
    return 1;
}  
  
yajl_callbacks ztr_callbacks = {  
    ztr_parser_null,  
    ztr_parser_boolean,  
    NULL,  
    NULL,  
    ztr_parser_number,  
    ztr_parser_string,  
    ztr_parser_start_map,  
    ztr_parser_map_key,  
    ztr_parser_end_map,  
    ztr_parser_start_array,  
    ztr_parser_end_array  
};  


