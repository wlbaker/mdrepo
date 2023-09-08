
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "pista.h"
#include "pista-internal.h"
#include "imp731.h"
#include "imp731.pb-c.h"

struct pista_dev_driver *IMP731_init( struct pista_context *pista_ctx ) {

	return &imp731_driver_info;
}

static int IMP731_allocate( struct pista_dev_inst *di ) {
	
	struct IMP731_context *me = PISTA_MALLOC( sizeof(struct IMP731_context) );
	if( me == NULL ) {
        printf("IMP731_allocate: alloc error for private data\n" );
		return PISTA_ERR;
	}
	me->cpos = 0;
	me->tick_time = 0;

	me->w_offset = 0;
	me->packet_cnt = 0;
	me->status_cnt = 0;

	// me->s.hzz = 1;  // 1 hz signal
	// me->scale = 10;

	di->priv = me;
    di->driver = &imp731_driver_info;
    di->next = NULL;
    di->model = "731emv";
    di->version = "0.0";

	di->status = PISTA_ST_NOT_CONNECTED;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->event_handler = NULL;
    di->event_priv = NULL;

    // printf("IMP731_allocate: initting protobuf structures\n" );
 	imp731__ident__init( &me->i );
 	imp731__breath__init( &me->b );
 	imp731__status__init( &me->s );
 	imp731__sensors__init( &me->w );

    // printf("IMP731_allocate: allocating wf data\n" );
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
        	printf("IMP731_allocate: alloc error for waveform buffer\n" );
		return PISTA_ERR;
	}

    printf("IMP731_allocate: initting packet_data\n" );
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
    //printf("IMP731_allocate: saving stream info\n" );
	pista_dev_register_stream( di, &me->wi );
	pista_dev_register_stream( di, &me->bi );
	pista_dev_register_stream( di, &me->si );

	return PISTA_OK;
}

static int IMP731_handle( const struct pista_dev_inst *h, const char *cc, int len )  {
	struct IMP731_context *me = (struct IMP731_context *)h->priv;

	while( len-- > 0 ) {
		const char c = *(cc++);
		if( c == STX ) {
            me->cpos = 0;
        }
        if( me->cpos > (sizeof( me->cbuf ) - 2) || me->cpos < 0 ) {
                printf("OVERFLOW CPOS=%d\n", me->cpos );
                me->cpos = 0;
        }
		me->cbuf[me->cpos] = c;
		me->cpos++;
		if( c == ETX ) {
			me->cbuf[me->cpos] = 0; // convenience
			if( me->cpos > 2 ) {
				IMP731_process_pkt( h, me->cbuf, me->cpos );
			}
			me->cpos = 0;
		}

	}

	return PISTA_OK;
}

static int IMP731_config_set(const struct pista_dev_inst *h, const char *key, const void *settings ) {

	return PISTA_OK;
}

static int IMP731_destroy(struct pista_dev_inst *h) {
	// stop data flow
	return PISTA_OK;
}

static int IMP731_probe(commfunc_t out, void *commfunc_priv )  {
	return PISTA_OK;
}

// GUI status command, received unsolicited, even when the unit is off
static const char id[] = { 0x02, 0xfa, 0x31, 0x20 }; // 0x36, 0x43, 0x20 }; 

static int IMP731_verify(const char data[], size_t len)  {
    // printf("imp731 - verify %I64ld %p: ", len, data);

    len -= sizeof(id);
    for( int i = 0; i < len; i++ ) {
        if( data[i] == 0x02 ) {
            if( memcmp( &data[i], id, sizeof(id)) == 0 ) {
                printf("OK\n");
                return PISTA_OK;
            }
        }
    }
    printf("NAK\n");
	return PISTA_ERR_NA;
}

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


static int IMP731_tick( const struct pista_dev_inst *dri )  {
	struct IMP731_context *me = (struct IMP731_context*)dri->priv;

	time_t rawtime;
	time ( &rawtime );

    const char *dat;
	if( rawtime - me->tick_time > 5 ) {
	    me->tick_time = rawtime;
	    dat = IMP731_get_id(me->sbuf, CRC_SEND_SEED );
	} else {
	    dat = IMP731_get_emv_info(me->sbuf, CRC_SEND_SEED );
    }

	if( dat != NULL) {
        if( dri->comm_func == NULL ) {
            printf("IMP731_tick: NO COMM FUNC\n");
        }  else {
		    (*dri->comm_func)( dri->comm_priv, dat, strlen(dat) );
        }
	} else {
        // printf("no GET_ID\n");
    }

	return PISTA_OK;
}

static int IMP731_cleanup(struct pista_dev_driver *drv )  {
	if( drv->priv != NULL ) {
		PISTA_FREE( drv->priv );
		drv->priv = NULL;
	}
	return PISTA_OK;
}

// R_PRIV 
struct pista_dev_driver imp731_driver_info = {
        .name = "imp731",
        .longname = "ventilator/Impact 731 Series",
        .api_version = 1,
        .init = IMP731_init,
        .cleanup = IMP731_cleanup,

        // .config_get = NULL,
        .config_set = IMP731_config_set,

        .allocate = IMP731_allocate,
        .destroy = IMP731_destroy,
        .handle = IMP731_handle,

        .probe = IMP731_probe,
        .verify = IMP731_verify,

	.tick = IMP731_tick,

        .priv = NULL
};

