#include <stdio.h>
#include <pista.h>
#include <string.h>

#include "propaqm.h"


FILE *ftrend;
FILE *fpatient;
FILE *fanno;
FILE *fsnap;
FILE *ftsnap;
FILE *fwaves;

bool firstTrendReport = true;

char *msg1 = "{\"ZOLL\":{\"@SchemaVersion\":9,\"TrendReport\":[{\"TrendRpt\":}]}}";

#pragma GCC diagnostic ignored "-Wpointer-sign"



// static int arr_pos;
#define TABS "\t\t\t\t\t\t\t        "
 
static void dumpVal(FILE *fp, Val *val )
{
    if( fp == NULL ) return;
    // printf( "\"%s\", %d, %d, ", td->dataState, td->alarm, td->dataStatus);
    // if( td->dataStatus > 0 ) {
        // printf("%d,", td->dataStatus );
        if( val->typ == 'I' ) {
            fprintf( fp, "%d", val->ival );
        } else {
            fprintf( fp, "\"%s\"", val->sval );
        }
    // }

}


static void dumpTrendVar(FILE *fp, const char *name, TrendVar *var, bool header_only )
{
    if( fp == NULL ) return;
    if( header_only ) {
            fprintf(fp, "%s", name );
    } else {
        if( var->td.dataStatus == 0 ) {
                dumpVal(fp, &var->td.val );
        }
    // } else {
            // printf("!%d", var->chanState );
    }
    //printf( "\"%s\", %d, %d, %d, ", var->srcLabelVal, var->srcLabel, var->_at_type, var->chanState );
    fprintf(fp, ", " );
}

static void dumpStdHdr( FILE *fp, StdHdr *hdr ) {
    fprintf(fp, "\"%s\", \"%s\", %d, %d", hdr->devDateTime, hdr->GUID, hdr->recId, hdr->msecTime );
}

void PROPAQM_initDumper(FILE *fp)
{
    ftrend = fp;
    fpatient = fp;
    fanno = fp;
    fsnap = fp;
    ftsnap = fp;
    fwaves = fp;
}

void PROPAQM_dump_set_file(const char *name, FILE *fp) {
    if( strncmp( name, "trend", strlen(name) ) == 0) {
        ftrend = fp;
    } else if( strncmp( name, "patient", strlen(name) ) == 0) {
        fpatient = fp;
    } else if( strncmp( name, "annotation", strlen(name) ) == 0) {
        fanno = fp;
    } else if( strncmp( name, "snap", strlen(name) ) == 0) {
        fsnap = fp;
    } else if( strncmp( name, "tsnap", strlen(name) ) == 0) {
        ftsnap = fp;
    } else if( strncmp( name, "waves", strlen(name) ) == 0) {
        fwaves = fp;
    }
}

void PROPAQM_dumpNumericsReport(FILE *fp, StdHdr *hdr, Trend *trend) {
    PROPAQM_dumpTrendReport(fp, hdr, trend, false );
}

void PROPAQM_dumpTrendReport(FILE *fp, StdHdr *hdr, Trend *trend, bool headers_only) {
    if( fp == NULL ) return;
        if( headers_only ) {
                fprintf( fp, "\"0000-00-00T00:00:00\", \"Record ID\", \"msec\", " );
            fprintf( fp, ", \"NTrend Report\", LTA_StateVal, LTA_State, PAT_MODE,");        
        } else {
            dumpStdHdr( fp, hdr );
            fprintf( fp, ", \"NTrend Report\", ");        
            fprintf( fp, "\"%s\", %d, %d, ", trend->ltaStateVal, trend->ltaState, trend->patMode);
        }

        for( int i = 0; i < 3; i++ ) {
            char name[12];
            sprintf(name, "TEMP%d", i );
            dumpTrendVar( fp, name, &trend->temp[i], headers_only );
        }
        dumpTrendVar( fp, "Hr", &trend->hr, headers_only );
        dumpTrendVar( fp, "FiCO2", &trend->fico2, headers_only );

        dumpTrendVar( fp, "SpCO", &trend->spo2.spco, headers_only );
        dumpTrendVar( fp, "SpMet", &trend->spo2.spmet, headers_only );
        dumpTrendVar( fp, "PVI", &trend->spo2.pvi, headers_only );
        dumpTrendVar( fp, "PI", &trend->spo2.pi, headers_only );
        dumpTrendVar( fp, "SpOC", &trend->spo2.spoc, headers_only );
        dumpTrendVar( fp, "SpHb", &trend->spo2.sphb, headers_only );

        dumpTrendVar( fp, "NIBP.sys", &trend->nibp.sys, headers_only );
        dumpTrendVar( fp, "NIBP.dia", &trend->nibp.dia, headers_only );
        dumpTrendVar( fp, "NIBP.map", &trend->nibp.map, headers_only );

        for( int i = 0; i < 3; i++ ) {
            char name[12];
            sprintf(name, "IBP%d.sys", i );
            dumpTrendVar( fp, name, &trend->ibp[i].sys, headers_only );
            sprintf(name, "IBP%d.dia", i );
            dumpTrendVar( fp, name, &trend->ibp[i].dia, headers_only );
            sprintf(name, "IBP%d.map", i );
            dumpTrendVar( fp, name, &trend->ibp[i].map, headers_only );
        }

        dumpTrendVar( fp, "EtCO2", &trend->etco2, headers_only );
        dumpTrendVar( fp, "Resp", &trend->resp, headers_only );

        fprintf( fp,"\n");
}

void PROPAQM_dumpPatientInfo( PatientInfo *pi ) {
    if( fpatient == NULL ) return;
	PatientData *pd = &pi->patientData;

	FILE *fp = fpatient;
        dumpStdHdr( fp, &pi->hdr );
        //if( headers_only ) {
                //printf( "\"0000-00-00T00:00:00\", \"Record ID\", \"msec\", " );
            //printf(", \"Trend Report\", LTA_StateVal, LTA_State, PAT_MODE,");        
        //} else {
            fprintf(fp,", \"Patient Data\", ");        
        //}

        dumpVal(fp, &pd->weight );
        fprintf(fp, ", ");
        dumpVal(fp, &pd->height );
        fprintf(fp, ", ");
        fprintf(fp,  "\"%s\", ", pd->firstName );
        fprintf(fp,  "\"%s\", ", pd->middleName );
        fprintf(fp,  "\"%s\", ", pd->lastName );
        fprintf(fp,  "%d, ", pd->age);
        fprintf(fp,  "\"%s\", ", pd->patientId );
        fprintf(fp,  "\"%s\", ", pd->roomNo );
        fprintf(fp,  "\"%s\", ", pd->patientMode );
        fprintf(fp,  "\"%s\", ", pd->sex );
        fprintf(fp,  "%d, ", pd->patMode);
        fprintf(fp,  "%d, ", pd->gender);
        fprintf(fp, "\n");
}

static void dumpWaveform( FILE *fp, Waveform *wf ) 
{
    if( fp == NULL ) return;
    // WaveSetting *setting  = &wf->waveSetting;
    //   char unitsVal[16];
    //   int waveType;
    //   int units;
    //   int generalData;
    //   char wavetypeVar[16];

    fprintf( fp, "\"%s\", %d, %d, ", "WF", wf->_at_waveNum, wf->status );
    fprintf( fp, "\"%s\", %d, %d, ", wf->statusVal, wf->_at_waveNum, wf->offset );
    WaveRec *rec = &wf->rec;

    int n_samples = rec->n_samples;
    fprintf( fp, "%d, %d, %d, %d", rec->waveType, rec->sampleTime, rec->frameSize, rec->n_samples );
    // int rec->_at_dataType;

    int *v = rec->unpackedSamples;
    for( int i =0; i < n_samples; i++ ) {
            fprintf(fp, ", %d", *v);
            v++;
    }
    fprintf(fp, "\n");

}

void PROPAQM_dumpWaveforms( ContinWaveRec *cw ) 
{
    if( fwaves == NULL ) return;

    dumpStdHdr( fwaves, &cw->hdr );
    fprintf(fwaves, ", \"Continuous Waveform\", ");        
    fprintf(fwaves,  "%d, ", cw->_at_TdrRecVer );
    fprintf(fwaves,  "\"%s\", ", cw->headerData);
    fprintf(fwaves,  "%d, ", cw->notchSetting );
    fprintf(fwaves,  "%d, ", cw->patMode );
    fprintf(fwaves,  "%d, ", cw->ecgLeadLabels );
    fprintf(fwaves, "\n");

    for( int i = 0; i < 3; i++ ) {
            Waveform *wf = &cw->waveform[i];
            dumpWaveform(fwaves, wf);
    }

}

void PROPAQM_dumpSnapshot( FILE *fp, SnapshotRpt *snap )
{

    if( fp == NULL ) return;
    dumpStdHdr( fp, &snap->hdr );
    fprintf(fp, ", \"Snapshot Report\", ");        

        // me->dSnapshot.hdr;
    fprintf(fp, "%d, %d, %d, %d,", 
            snap->ecgLeadLbl, 
            snap->devEvtCode, 
            snap->nexport_waves, 
            snap->preEventSampleTime );
        fprintf(fp, " \"%s\", \"%s\", \"%s\",",
            snap->hdrData,
            snap->snapshotId,
            snap->uniqueCaseId );
        fprintf(fp, " \"%s\", ", snap->treatmentLbl );
        fprintf(fp, "%d, %d, %d, %d\n", 
            snap->notchSetting, 
            snap->pacerState, 
            snap->syncState, 
            snap->patMode);
}


void PROPAQM_dumpAnnotation( AnnotationEvt *anno ) {
    if( fanno == NULL ) return;
    dumpStdHdr( fanno, &anno->hdr );
    fprintf(fanno, ", \"Annotation\", %d, \"%s\", %d, %d, \"%s\", \"%s\"\n",
            anno->_at_TdrRecVer,
            anno->_at_EvtName,
            anno->treatmentSummary,
            anno->devEvtCode,
            anno->xidCode,
            anno->payload
    );        
}

void PROPAQM_dumpTreatmentShapshotEvt( TreatmentSnapshotEvt *tmt ) {
    if( ftsnap == NULL ) return;
    dumpStdHdr( ftsnap, &tmt->hdr );
    fprintf( ftsnap, ", \"Treatment Snapshot\", %d, \"%s\", \"%s\", %d, %d, \"%s\", \"%s\"\n",
        tmt->_at_TdrRecVer,
        tmt->_at_EventName,
        tmt->treatmentLbl,
        tmt->treatmentSummary,
        tmt->devEvtCode,
        tmt->xidCode,
        tmt->payload
    );        
}

void PROPAQM_dumpDefibFireEv( DefibFireEvt *df ) {

    if( fanno == NULL ) return;
    dumpStdHdr( fanno, &df->hdr );
    fprintf(fanno, ", \"Defib\", %d, \"%s\", \"%s\", %d, %d, \"%s\", ",
        df->_at_TdrRecVer,
        df->errors,
        df->warnings,
        df->treatmentSummary,
        df->devEvtCode,
        df->xidCode
    );        
    fprintf(fanno, "%d, %d, %d, %d, %d, %d, %d, %d\n",
        df->energyDel,
        df->patImpedance,
        df->initialCurrent,
        df->schedule,
        df->shockCnt,
        df->energySel,
        df->patientTti,
        df->chargeTime
    );
}

void PROPAQM_dumpNewCase( NewCase *nc ) {
    if( fpatient == NULL ) return;
    dumpStdHdr( fpatient, &nc->hdr );
    fprintf(fpatient, ", \"New Case\",");        
    fprintf(fpatient, " \"%s\", \"%s\"\n", 
        nc->caseLabel, 
        nc->UniqueCaseId
        );
}

