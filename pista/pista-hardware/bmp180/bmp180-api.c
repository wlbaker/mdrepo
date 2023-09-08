
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// #include <sys/types.h>  // pid_t
// #include <sys/syscall.h>

#include "pista.h"
#include "pista-internal.h"

#include "bmp180-api.h"

struct pista_dev_driver *BMP180_init( struct pista_context *pista_ctx ) {

	// drv->priv = NULL;
    
    return &bmp180_driver_info;
}

int BMP180_allocate( struct pista_dev_inst *di ) {
	
	struct BMP180_context *me = PISTA_MALLOC( sizeof(struct BMP180_context) );
	if( me == NULL ) {
        printf("BMP180_allocate: alloc error for private data\n" );
		return PISTA_ERR;
	}

    // printf("BMP180_allocate: %lx\n", (unsigned long)me );
	me->tick_seq  = 0;
	me->tick_time = 0;

    memset( &me->ctx, 0, sizeof(me->ctx) );
	me->ctx.bus = 2;
	me->ctx.address = 0x77;

	di->priv = me;
    di->driver = &bmp180_driver_info;
    di->next = NULL;
    di->model = "BMP180";
    di->version = "0.0";

	di->status = PISTA_ST_NOT_CONNECTED;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->event_handler = NULL;
    di->event_priv = NULL;


    // printf("BMP180_allocate: initting protobuf structures\n" );
 	bmp180__measurement__init( &me->m );

    // printf("BMP180_allocate: creating si descs\n" );
    //me->mi.field_cnt = 2;
    //me->mi.desc = (struct pista_item_desc *)PISTA_MALLOC( me->mi.field_cnt * sizeof(struct pista_item_desc));
    //if( me->mi.desc == NULL ) {
        //printf("BMP180_allocate: alloc error for mi desc\n" );
		//return PISTA_ERR;
    //}

    //pista_set_desc( &me->mi.desc[0], "t", NULL, NULL, NULL, FLOAT_TYP, offsetof( Bmp180__Measurement, t), 1 );
    //pista_set_desc( &me->mi.desc[1], "p", NULL, NULL, NULL, FLOAT_TYP, offsetof( Bmp180__Measurement, p), 1 );

    me->mi.stream_id = PISTA_DF_MEASUREMENT;
    me->mi.payload_sz = sizeof( me->m );
    me->mi.payload = &me->m;

    pista_dev_register_stream( di, &me->mi );

	return PISTA_OK;
}

int BMP180_set_option(const struct pista_dev_inst *h, const char *key, const void *value ) {
	struct BMP180_context *me = (struct BMP180_context *)h->priv;

	printf("BMP180 -- set %s = %s\n", key, value );
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

static int BMP180_get_option_i(const struct pista_dev_inst *h, const char *key, int *val ) {
	struct BMP180_context *me = (struct BMP180_context *)h->priv;

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

int BMP180_connect(struct pista_dev_inst *h) {
	struct BMP180_context *me = (struct BMP180_context *)h->priv;

	printf("BMP180 -- connect\n");
	int rc = bmp180_connect(&me->ctx);

    if( rc == 0 ) {
	    bmp180_startTemperature(&me->ctx);
        me->tick_seq = 0;
    }

    return (rc == 0) ? PISTA_OK : PISTA_ERR;
}

int BMP180_disconnect(struct pista_dev_inst *h) {
	struct BMP180_context *me = (struct BMP180_context *)h->priv;

	bmp180_disconnect(&me->ctx);

    return PISTA_OK;
}


int BMP180_destroy(struct pista_dev_inst *h) {
	// struct BMP180_context *me = (struct BMP180_context *)h->priv;
	return PISTA_OK;
}

int BMP180_tick( const struct pista_dev_inst *h )  {
	struct BMP180_context *me = (struct BMP180_context*)h->priv;

	time_t rawtime;
	time ( &rawtime );
 
    // pid_t tid = syscall(SYS_gettid);
	if( rawtime - me->tick_time < 2 ) {
	    // printf("bmp180-tick skip=%x, %ld  [%lx,%lx]\n", tid, rawtime - me->tick_time, h, me);
		return -1;
	}
	// printf("bmp180-tick start=%x, %ld  [%lx,%lx]\n", tid, rawtime - me->tick_time, h, me);

	me->tick_time = rawtime;

    if( me->tick_seq == 0 ) {
		bmp180_getTemperature(&me->ctx, &me->m.t);
		bmp180_startPressure(&me->ctx, 3);
        me->tick_seq = 1;
    } else {
		bmp180_getPressure(&me->ctx, &me->m.p, me->m.t);
		bmp180_startTemperature(&me->ctx);

        me->tick_seq = 0;
		// printf( "Current temp and pressure: %f,%f\n", me->m.t, me->m.p );

    	struct pista_data_packet *sendable = &me->mi;
    	if( sendable != NULL && h->event_handler != NULL ) {
        	sendable->tm = pista_get_current_time_with_ms();
        	h->event_handler( h->event_priv, sendable );
    	}
    }
	// printf("bmp180-tick complete=%x\n", tid );

	return PISTA_OK;
}

static int BMP180_cleanup(struct pista_dev_driver *drv )  {
	if( drv->priv != NULL ) {
		PISTA_FREE( drv->priv );
		drv->priv = NULL;
	}
	return PISTA_OK;
}

// R_PRIV 
struct pista_dev_driver bmp180_driver_info = {
        .name = "bmp180",
        .longname = "misc/BMP810 I2C Ambient Sensor",
        .api_version = 1,
        .init = BMP180_init,
        .cleanup = BMP180_cleanup,

        .config_set = BMP180_set_option,
        //.config_get = BMP180_get_option_i,
        //.config_get = BMP180_get_option_p,
        //.config_get = BMP180_get_option_f,

        .allocate = BMP180_allocate,
        .connect = BMP180_connect,
        .disconnect = BMP180_disconnect,
        .destroy = BMP180_destroy,

	.tick = BMP180_tick,

        .priv = NULL
};

