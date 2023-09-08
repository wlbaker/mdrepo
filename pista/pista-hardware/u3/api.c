
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#include "pista.h"
#include "pista-internal.h"
#include "api.h"

static int U3API_init( struct pista_context *pista_ctx, struct pista_dev_driver *drv ) {

	drv->priv = NULL;

	return PISTA_OK;
}

static int U3API_allocate( struct pista_dev_driver *drv, struct pista_dev_inst *di ) {
	
	struct U3_context *me = PISTA_MALLOC( sizeof(struct U3_context) );
	if( me == NULL ) {
		return PISTA_ERR;
	}
	di->priv = me;

	di->status = PISTA_ST_NOT_CONNECTED;

 	u3__u3_settings__init( &me->s );  // PROTOBUF_C_MESSAGE_INIT (&u3__u3_settings__descriptor);
	me->s.hzz = 100;
	me->s.rps = 1;
	me->s.ms  = 500;
	me->s.fin_mask = 7;
	me->s.ein_mask = 0;
	me->s.fout_mask = 0;
	me->s.eout_mask = 0;
	U3_CDM_apply_settings( me );

	return PISTA_OK;
}


//void U3API_setCDataModel(U3CDataModel *cdm) {
	//this->cdm = *cdm;
//}

void U3API_dump( struct U3_context *cdm, int32_t **dbuf ) {
	printf("CDM=%lx\n", cdm);
	for(int i=0; i < 2; i++) {
		printf("DUMP channel%d: %lx\n", i, dbuf[i] );

		for( int k = 0; k < 5; k++) {
			printf("    AIDBUF%d: %f\n", k, dbuf[i][k] );
		}
	}
}

static int U3API_dev_start(const struct pista_dev_inst *h ) {
    struct U3_context *cdm = (struct U3_context *)h->priv;

	if( U3_openUSBConnection(cdm, -1) != 0 ) goto done;
	U3_getCalibrationInfo( cdm );
	if( U3_configIO( cdm, 255, 255) ) goto close;

	U3_streamStop(cdm); // stop existing streams, if any.  ignore err

	if( U3_streamConfig( cdm) ) goto close;

	if( U3_streamStart(cdm) ) goto close;

	return PISTA_OK;

close:
	U3_closeUSBConnection(cdm);
	cdm->hDevice = NULL;

done:
	printf("******************** CONNECT ERR");
	return -1;
}

static int U3API_dev_stop(const struct pista_dev_inst *h ) {
    struct U3_context *me = (struct U3_context *)h->priv;

	return U3_streamStop(me);
}


static int U3API_cleanup(struct pista_dev_driver *drv )  {
    if( drv->priv != NULL ) {
        PISTA_FREE( drv->priv );
        drv->priv = NULL;
    }
    return PISTA_OK;
}

static int U3API_destroy(struct pista_dev_inst *h ) {
    struct U3_context *me = (struct U3_context *)h->priv;

	int rc = U3_streamStop(me); // maybe warn if rc is not 0, but this is not an error

	U3_closeUSBConnection(me);

	PISTA_FREE(me);
	h->priv = NULL;

	return rc;
}

static void *U3API_config_get(const struct pista_dev_inst *h ) {
    struct U3_context *me = (struct U3_context *)h->priv;

    return &me->s;
}

static int U3API_config_set(const struct pista_dev_inst *h, void *config ) {
    struct U3_context *me = (struct U3_context *)h->priv;

	me->s = *(U3__U3Settings *)config;
	U3_CDM_apply_settings( me ); // , 100, 1, 500, 0x07, 0 );

    return PISTA_OK;
}



static int U3API_handle( const struct pista_dev_inst *h, const char *cc, int len )  {
    struct U3_context *me = (struct U3_context *)h->priv;

}

static int U3API_tick( const struct pista_dev_inst *inst )  {
    struct U3_context *me = (struct U3_context*)inst->priv;

	int rc = U3_streamData( me );
	if( rc == PISTA_OK && inst->event_func != NULL) {
		inst->event_func( inst, 99, me->u3f );
	}
	return rc;
	
}

struct pista_dev_driver u3_driver_info = {
        .name = "lju3",
        .longname = "Labjack U3",
        .api_version = 1,
        .init = U3API_init,
        .cleanup = U3API_cleanup,

        /* .config_get = NULL, */
        .config_get = U3API_config_get,
        .config_set = U3API_config_set,

        .dev_start = U3API_dev_start,
        .dev_stop  = U3API_dev_stop,

        .allocate = U3API_allocate,
        .destroy = U3API_destroy,
        .handle = U3API_handle,

        .tick = U3API_tick,

        .priv = NULL
};



