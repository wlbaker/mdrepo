
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "pista.h"
#include "pista-internal.h"
#include "ht70.h"

struct pista_dev_driver *HT70_init( struct pista_context *pista_ctx ) {

	return &ht70_driver_info;
}

int HT70_allocate( struct pista_dev_inst *di ) {
	
	struct HT70_context *me = PISTA_MALLOC( sizeof(struct HT70_context) );
	if( me == NULL ) {
		return PISTA_ERR;
	}
    me->p = NULL;
    me->depth = 0;
    ht70_install_parser( me );

	me->tick_time = 0;
	di->priv = me;
    di->driver = &ht70_driver_info;
    di->next = NULL;
    di->model = "ht70";
    di->version = "0.0";

	di->status = PISTA_ST_NOT_CONNECTED;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->event_handler = NULL;
    di->event_priv = NULL;

 	ht70__status__init( &me->s );
 	ht70__breath__init( &me->m );
 	ht70__alarms__init( &me->a );
 	ht70__sensors__init( &me->w );

    me->si.stream_id = PISTA_DF_SETTINGS;
    me->si.payload_sz = sizeof( me->s );
    me->si.payload = &me->s;

    me->mi.stream_id = PISTA_DF_MEASUREMENT;
    me->mi.payload_sz = sizeof( me->m );
    me->mi.payload = &me->m;

    me->ai.stream_id = PISTA_DF_ALARM;
    me->ai.payload_sz = sizeof( me->a );
    me->ai.payload = &me->a;

    me->wi.stream_id = PISTA_DF_WAVEFORM;
    me->wi.payload_sz = sizeof( me->w );
    me->wi.payload = &me->w;
    pista_set_named_field_spp( &me->w.base, "PAW", 50);
    pista_set_named_field_freq( &me->w.base, "PAW", 50);
    pista_set_named_field_spp( &me->w.base, "FLOW", 50);
    pista_set_named_field_freq( &me->w.base, "FLOW", 50);
    //.me->wi.desc[0].spp = 50;
    //.me->wi.desc[0].freq = 50;
    //.me->wi.desc[1].spp = 50;
    //.me->wi.desc[1].freq = 50;
    me->w.pawwave = PISTA_MALLOC( sizeof(int) * 50);
    me->w.flowwave = PISTA_MALLOC( sizeof(int) * 50);
    // pista_dump_java(&me->si);
    // pista_dump_java(&me->mi);
    // pista_dump_java(&me->ai);

	return PISTA_OK;
}

int HT70_handle( const struct pista_dev_inst *h, const char *cc, int len )  {
	struct HT70_context *me = (struct HT70_context *)h->priv;

	int code = ht70_process_pkt( me, cc, len );
  
    if( me->fire_alarm ) {
        if( h->event_handler != NULL ) {
            me->ai.tm = pista_get_current_time_with_ms();
            h->event_handler( h->event_priv, &me->ai );
        }
        me->fire_alarm = false;
    }
    if( me->fire_status ) {
		// printf("s");
        if( h->event_handler != NULL ) {
            me->si.tm = pista_get_current_time_with_ms();
            h->event_handler( h->event_priv, &me->si );
        }
        me->fire_status = false;
    }
    if( me->fire_measurement ) {
		// printf("m");
        if( h->event_handler != NULL ) {
            me->mi.tm = pista_get_current_time_with_ms();
            h->event_handler( h->event_priv, &me->mi );
        }
        me->fire_measurement = false;
    }
    if( me->fire_waveform ) {
		// printf("w");
        if( h->event_handler != NULL ) {
            me->mi.tm = pista_get_current_time_with_ms();
            h->event_handler( h->event_priv, &me->wi );
        }
        me->fire_waveform = false;
    }

    if( me->reset || (code == XML_STATUS_ERROR) ) {
        printf("ht70: reset or XML_STATUS_ERROR\n");
        ht70_install_parser( me );
    }

	return PISTA_OK;
}


int HT70_destroy(struct pista_dev_inst *h) {
	// stop data flow
	return PISTA_OK;
}

int HT70_probe( commfunc_t out, void *commfunc_priv ) {

    // HT70 is deaf

	return PISTA_OK;
}

int HT70_verify(const char data[], size_t len) {

    char buf[len+1];
    strncpy( buf, data, len );
    buf[len] = '\0';

    printf("ht70 - verify: " );
#ifdef DEBUG_VERBOSE
    for( int i = 0; i < len; i++ ) {
        int ch = data[i];
        if( ch < 0 ) {
            ch += 256;
        }
        if( ch >= ' ' && ch <= '}' ) {
            putchar(ch);
        } else {
            printf("[%2.2x]", ch );
        }
    }
#endif
    printf(" " );
    if( strstr( buf, "<cpc " ) != NULL ) {
        printf("C OK\n");
        return PISTA_OK;
    } else if( strstr( buf, "<s name=" ) != NULL ) {
        printf("S OK\n");
        return PISTA_OK;
    } else if( strstr( buf, "<m name=" ) != NULL ) {
        printf("M OK\n");
        return PISTA_OK;
    } else if( strstr( buf, "<a name=" ) != NULL ) {
        printf("A OK\n");
        return PISTA_OK;
    }

    printf("NAK\n");
	return PISTA_ERR_NA;
}

int HT70_tick( const struct pista_dev_inst *di )  {
	// struct HT70_context *me = (struct HT70_context*)di->priv;

	return PISTA_OK;
}

int HT70_cleanup(struct pista_dev_driver *drv )  {
	if( drv->priv != NULL ) {
		PISTA_FREE( drv->priv );
		drv->priv = NULL;
	}
	return PISTA_OK;
}

// R_PRIV 
struct pista_dev_driver ht70_driver_info = {
        .name = "ht70",
        .longname = "ventilator/HT70",
        .api_version = 1,
        .init = HT70_init,
        .cleanup = HT70_cleanup,

         .probe = HT70_probe,
         .verify = HT70_verify,
         
        // .config_get = NULL,
        .config_set = NULL, // HT70_config_set,

        .allocate = HT70_allocate,
        .destroy = HT70_destroy,
        .handle = HT70_handle,

	.tick = HT70_tick,

        .priv = NULL
};

