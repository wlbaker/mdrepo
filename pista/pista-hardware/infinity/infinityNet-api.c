
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "pista.h"
#include "pista-internal.h"
#include "infinityNet.h"
// #include "infinityNet.pb-c.h"

extern struct pista_dev_driver infinityNet_driver_info;

struct pista_dev_driver *INFINITYNET_init( struct pista_context *pista_ctx ) {

	return &infinityNet_driver_info;
}

static int INFINITYNET_allocate( struct pista_dev_driver *drv, struct pista_dev_inst *di ) {
	
	struct INFINITYNET_context *me = PISTA_MALLOC( sizeof(struct INFINITYNET_context) );
	if( me == NULL ) {
        printf("INFINITYNET_allocate: alloc error for private data\n" );
		return PISTA_ERR;
	}
	me->tick_time = 0;

	me->w_offset = 0;
	me->packet_cnt = 0;
	me->status_cnt = 0;

	// me->s.hzz = 1;  // 1 hz signal
	// me->scale = 10;

	di->priv = me;
    di->driver = drv;
    di->next = NULL;
    di->model = "*generic*";
    di->version = "0.0";

	di->status = PISTA_ST_NOT_CONNECTED;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->event_handler = NULL;
    di->event_priv = NULL;

    /*
 	infinityNet__ident__init( &me->i );
 	infinityNet__breath__init( &me->b );
 	infinityNet__status__init( &me->s );
 	infinityNet__sensors__init( &me->w );

	me->w.n_w0 = 100;
	me->w.n_w1 = 100;
	me->w.n_w2 = 100;
	me->w.n_w3 = 100;

    pista_set_named_field_spp( &me->w.base, "w0", me->w.n_w0 );
    pista_set_named_field_spp( &me->w.base, "w1", me->w.n_w1 );
    pista_set_named_field_spp( &me->w.base, "w2", me->w.n_w2 );
    pista_set_named_field_spp( &me->w.base, "w3", me->w.n_w3 );

    // 1 pkt/sec means freq == &samples
    pista_set_named_field_freq( &me->w.base, "w0", me->w.n_w0 );
    pista_set_named_field_freq( &me->w.base, "w1", me->w.n_w1 );
    pista_set_named_field_freq( &me->w.base, "w2", me->w.n_w2 );
    pista_set_named_field_freq( &me->w.base, "w3", me->w.n_w3 );

	int tot = me->w.n_w0*sizeof(int32_t);
    tot += me->w.n_w1*sizeof(int32_t);
    tot += me->w.n_w2*sizeof(int32_t);
    tot += me->w.n_w3*sizeof(int32_t);

	me->w.w0 = (int*) PISTA_MALLOC( tot );
	memset( me->w.w0, 0, tot );
	me->w.w1 = (int*) (me->w.w0  + me->w.n_w0 );
	me->w.w2 = (int*) (me->w.w1  + me->w.n_w1 );
	me->w.w3 = (int*) (me->w.w2  + me->w.n_w2 );
	if( me->w.w0 == NULL ) {
        	printf("INFINITYNET_allocate: alloc error for waveform buffer\n" );
		return PISTA_ERR;
	}

    printf("INFINITYNET_allocate: initting packet_data\n" );
    me->ii.stream_id = PISTA_DF_IDENT;
    me->ii.payload_sz = sizeof( me->i );
    me->ii.payload = &me->i;

    me->si.stream_id = PISTA_DF_SETTINGS;
    me->si.payload_sz = sizeof( me->s );
    me->si.payload = &me->s;

    me->bi.stream_id = PISTA_DF_MEASUREMENT;
    me->bi.payload_sz = sizeof( me->b );
    me->bi.payload = &me->b;

    me->wi.stream_id = PISTA_DF_WAVEFORM;
    me->wi.payload_sz = sizeof( me->w );
    me->wi.payload = &me->w;

	// di->s_stream = pista_stream_from_pkt( &me->si );
    //printf("INFINITYNET_allocate: saving stream info\n" );
	pista_dev_register_stream( di, &me->wi );
	pista_dev_register_stream( di, &me->bi );
	pista_dev_register_stream( di, &me->si );
    */

	return PISTA_OK;
}

static int INFINITYNET_handle( const struct pista_dev_inst *h, const char *cc, int len )  {
	struct INFINITYNET_context *me = (struct INFINITYNET_context *)h->priv;

    infinityNet_parsePacket( cc, len );
	return PISTA_OK;
}

static int INFINITYNET_config_set(const struct pista_dev_inst *h, const char *key, const void *settings ) {

	return PISTA_OK;
}

static int INFINITYNET_destroy(struct pista_dev_inst *h) {
	return PISTA_OK;
}

static int INFINITYNET_probe(commfunc_t out, void *commfunc_priv )  {
	return PISTA_OK;
}

static int INFINITYNET_verify(const char data[], size_t len)  {
	return PISTA_ERR_NA;
}

/*
static void dump_pkt( const char *msg, const char *buf, int len) {
	printf( "%s: ", msg);
	for(int i=0; i < len; i++) {
		char ch = buf[i];
		if( ch >= 0x20 && ch < 0xfe ) {
   			printf("%c", ch);
		} else {
			printf("[%02x]", (unsigned char)ch);
		}
	}
	printf("\n");
}
*/


static int INFINITYNET_tick( const struct pista_dev_inst *dri )  {
	struct INFINITYNET_context *me = (struct INFINITYNET_context*)dri->priv;

    // nothing to do for multicast reader


	return PISTA_OK;
}

static int INFINITYNET_cleanup(struct pista_dev_driver *drv )  {
	if( drv->priv != NULL ) {
		PISTA_FREE( drv->priv );
		drv->priv = NULL;
	}
	return PISTA_OK;
}

// R_PRIV 
struct pista_dev_driver infinityNet_driver_info = {
        .name = "infinityNet",
        .longname = "monitor/Drager Infinity Series",
        .api_version = 1,
        .init = INFINITYNET_init,
        .cleanup = INFINITYNET_cleanup,

        // .config_get = NULL,
        .config_set = INFINITYNET_config_set,

        .allocate = INFINITYNET_allocate,
        .destroy = INFINITYNET_destroy,
        .handle = INFINITYNET_handle,

        // .probe = INFINITYNET_probe,
        // .verify = INFINITYNET_verify,

	    .tick = INFINITYNET_tick,

        .priv = NULL
};

