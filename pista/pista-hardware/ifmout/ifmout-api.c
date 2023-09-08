
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// #include <sys/types.h>  // pid_t
// #include <sys/syscall.h>

#include "pista.h"
#include "pista-internal.h"

#include "model/ifmout.pb-c.h"

#include "ifmout-api.h"

static int IFMOUT_init( struct pista_context *pista_ctx, struct pista_dev_driver *drv ) {

	drv->priv = NULL;
    
	return PISTA_OK;
}

static int IFMOUT_allocate( struct pista_dev_driver *drv, struct pista_dev_inst *di ) {
	
	struct IFMOUT_context *me = PISTA_MALLOC( sizeof(struct IFMOUT_context) );
	if( me == NULL ) {
        printf("IFMOUT_allocate: alloc error for private data\n" );
		return PISTA_ERR;
	}

    // printf("IFMOUT_allocate: %lx\n", (unsigned long)me );
	me->tick_seq  = 0;
	me->tick_time = 0;

    memset( &me->ctx, 0, sizeof(me->ctx) );
	me->ctx.bus = 2;
	me->ctx.address = 0x77;

	di->priv = me;
    di->driver = drv;
    di->next = NULL;
    di->model = "IFMOUT";
    di->version = "0.0";

	di->status = PISTA_ST_NOT_CONNECTED;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->event_handler = NULL;
    di->event_priv = NULL;


    // printf("IFMOUT_allocate: initting protobuf structures\n" );
 	ifmout__measurement__init( &me->m );

    // printf("IFMOUT_allocate: creating si descs\n" );
    me->mi.field_cnt = 2;
    me->mi.desc = (struct pista_item_desc *)PISTA_MALLOC( me->mi.field_cnt * sizeof(struct pista_item_desc));
    if( me->mi.desc == NULL ) {
        printf("IFMOUT_allocate: alloc error for mi desc\n" );
		return PISTA_ERR;
    }

    pista_set_desc( &me->mi.desc[0], "t", NULL, NULL, NULL, FLOAT_TYP, offsetof( Bmp180__Measurement, t), 1 );
    pista_set_desc( &me->mi.desc[1], "p", NULL, NULL, NULL, FLOAT_TYP, offsetof( Bmp180__Measurement, p), 1 );

    me->mi.stream_id = PISTA_DF_MEASUREMENT;
    me->mi.payload_sz = sizeof( me->m );
    me->mi.payload = &me->m;

	di->m_stream = pista_stream_from_pkt( &me->mi );

	return PISTA_OK;
}

static int IFMOUT_set_option(const struct pista_dev_inst *h, const char *key, const void *value ) {
	struct IFMOUT_context *me = (struct IFMOUT_context *)h->priv;

	printf("IFMOUT -- set %s = %s\n", key, value );
    int rc = PISTA_OK;
    if( strcmp(key,"bus") == 0 ) {
        me->ctx.bus = atoi( value );
    } else if( strcmp(key,"address") == 0 ) {
        me->ctx.address = atoi( value );
    } else if( strcmp(key,"connection") == 0 ) {
        me->ctx.bus = atoi( value );
    } else {
        rc = PISTA_ERR;
    }

	return rc;
}

static int IFMOUT_get_option_i(const struct pista_dev_inst *h, const char *key, int *val ) {
	struct IFMOUT_context *me = (struct IFMOUT_context *)h->priv;

    int rc = PISTA_OK;
    
    if( strcmp(key,"bus") == 0 ) {
        *val = me->ctx.bus;
    } else if( strcmp(key,"address") == 0 ) {
        *val = me->ctx.address;
    } else {
        rc = PISTA_ERR;
    }

	return rc;
}

static int IFMOUT_connect(struct pista_dev_inst *h) {
	struct IFMOUT_context *me = (struct IFMOUT_context *)h->priv;

	printf("IFMOUT -- connect\n");
	int rc = ifmout_connect(&me->ctx);

    if( rc == 0 ) {
	    ifmout_startTemperature(&me->ctx);
        me->tick_seq = 0;
    }

    return (rc == 0) ? PISTA_OK : PISTA_ERR;
}

static int IFMOUT_disconnect(struct pista_dev_inst *h) {
	struct IFMOUT_context *me = (struct IFMOUT_context *)h->priv;

	ifmout_disconnect(&me->ctx);

    return PISTA_OK;
}


static int IFMOUT_destroy(struct pista_dev_inst *h) {
	// struct IFMOUT_context *me = (struct IFMOUT_context *)h->priv;
	return PISTA_OK;
}

static int IFMOUT_tick( const struct pista_dev_inst *h )  {
	struct IFMOUT_context *me = (struct IFMOUT_context*)h->priv;

	time_t rawtime;
	time ( &rawtime );
 
	if( rawtime - me->tick_time < 2 ) {
		return -1;
	}

	me->tick_time = rawtime;

    if( me->tick_seq == 0 ) {
		ifmout_getTemperature(&me->ctx, &me->m.t);
		ifmout_startPressure(&me->ctx, 3);
        me->tick_seq = 1;
    } else {
		ifmout_getPressure(&me->ctx, &me->m.p, me->m.t);
		ifmout_startTemperature(&me->ctx);

        me->tick_seq = 0;

    	struct pista_data_packet *sendable = &me->mi;
    	if( sendable != NULL && h->event_handler != NULL ) {
        	sendable->tm = pista_get_current_time_with_ms();
        	h->event_handler( h->event_priv, sendable );
    	}
    }
	// printf("ifmout-tick complete=%x\n", tid );

	return PISTA_OK;
}

static int IFMOUT_cleanup(struct pista_dev_driver *drv )  {
	if( drv->priv != NULL ) {
		PISTA_FREE( drv->priv );
		drv->priv = NULL;
	}
	return PISTA_OK;
}

// R_PRIV 
struct pista_dev_driver ifmout_driver_info = {
        .name = "ifmout",
        .longname = "monitor/Cardiac Output Monitor",
        .api_version = 1,
        .init = IFMOUT_init,
        .cleanup = IFMOUT_cleanup,

        .config_set = IFMOUT_set_option,
        //.config_get = IFMOUT_get_option_i,
        //.config_get = IFMOUT_get_option_p,
        //.config_get = IFMOUT_get_option_f,

        .allocate = IFMOUT_allocate,
        .connect = IFMOUT_connect,
        .disconnect = IFMOUT_disconnect,
        .destroy = IFMOUT_destroy,

	.tick = IFMOUT_tick,

        .priv = NULL
};

