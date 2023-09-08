
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "pista.h"
#include "pista-internal.h"
#include "medsys3.h"

struct pista_dev_driver *MEDSYS3_init( struct pista_context *pista_ctx) {

    return &medsys3_driver_info;
}

int MEDSYS3_allocate(  struct pista_dev_inst *di ) {
	
	MEDSYS3_context *me = PISTA_MALLOC( sizeof(struct medsys3_context) );
	if( me == NULL ) {
		return PISTA_ERR;
	}
	me->cpos = 0;
	me->tick_time = 0;
	di->priv = me;
    di->driver = &medsys3_driver_info;
    di->next = NULL;
    di->model = "medsys3";
    di->version = "0.0";

	di->status = PISTA_ST_NOT_CONNECTED;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->event_handler = NULL;
    di->event_priv = NULL;

 	medsys3__status__init( &me->s );
 	medsys3__measurement__init( &me->m );
 	medsys3__sigevent__init( &me->a );

    me->s.drug_a = PISTA_MALLOC(MS3_DRUG_LENGTH+1);
    me->s.drug_b = PISTA_MALLOC(MS3_DRUG_LENGTH+1);
    me->s.drug_c = PISTA_MALLOC(MS3_DRUG_LENGTH+1);

    strcpy(me->s.drug_a,"********");
    strcpy(me->s.drug_b,"********");
    strcpy(me->s.drug_c,"********");


    me->si.stream_id = PISTA_DF_SETTINGS;
    me->si.payload_sz = sizeof( me->s );
    me->si.payload = &me->s;

    me->mi.stream_id = PISTA_DF_MEASUREMENT;
    me->mi.payload_sz = sizeof( me->m );
    me->mi.payload = &me->m;

    me->ai.stream_id = PISTA_DF_M2;
    me->ai.payload_sz = sizeof( me->a );
    me->ai.payload = &me->a;

	return PISTA_OK;
}

int MEDSYS3_handle( const struct pista_dev_inst *h, const char *cc, int len )  {
	MEDSYS3_context *me = (MEDSYS3_context *)h->priv;

	while( len-- > 0 ) {
		const char c = *(cc++);
		me->cbuf[me->cpos] = c;
		me->cpos++;
		if( c == CR ) {
			me->cbuf[me->cpos] = 0; // convenience
			if( me->cpos > 2 ) {
                struct pista_data_packet *sendable = NULL;

				sendable = ms3_process_pkt( me, me->cbuf, me->cpos );
  
                if( sendable != NULL && h->event_handler != NULL ) {
                    sendable->tm = pista_get_current_time_with_ms();
                    h->event_handler( h->event_priv, sendable );
                }

			}
			me->cpos = 0;
		}

	}

	return PISTA_OK;
}

int MEDSYS3_destroy(struct pista_dev_inst *h) {
	// stop data flow
	return PISTA_OK;
}

static const char ms3_start_message[] = { 0x11, 1, 'c', 'A', ' ', '8', 'f', '0', 'b', '\r', 0 };
int MEDSYS3_probe( commfunc_t out, void *commfunc_priv ) {
    char dat[ sizeof( ms3_start_message) + 1 ];

    strcpy( dat, ms3_start_message );

    // I cant send const data without modifying the Swig generated code...it copies the java
    // data back to the byte array before returning in case Java changed it, so Swig doesnt
    // really respect the const qualifier.  Stack data works fine.
 
	out( commfunc_priv, dat, strlen(dat) );

	return PISTA_OK;
}

// static const char id[] = { 0x01, 0x69, 0x40, 0x6f, 0x44, 0x46, 0x35, 0x36, '\r' };
int MEDSYS3_verify(const char data[], size_t len) {

    char buf[len+1];
    strncpy( buf, data, len );
    buf[len] = '\0';

    for( int i = 0; i < len; i++ ) {
        if( data[i] == '\r' ) {
            return ms3_verify_pkt( buf, i+1 );
        }
    }
	return PISTA_ERR_NA;
}


int MEDSYS3_tick( const struct pista_dev_inst *di )  {
	MEDSYS3_context *me = (MEDSYS3_context*)di->priv;

	const char *dat = NULL;
	if( me->seq == 0 ) {
        printf("medsys3 basic connect w XON");
		ms3_build_connect(me->sbuf+1, sizeof( me->sbuf) - 1 );
        me->sbuf[0] = 0x11;  // ASCII DC1 -- XON...resume transmission
        dat = me->sbuf;
    } else if( me->seq == 1 ) {
        // current rate....but this might should be "QX00_X00;QX00_X01;QX00_X02!" instead.  dunno
        // query current rate and infusion status
		dat = ms3_build_message(me->sbuf, sizeof( me->sbuf), "QXC0_x00;QXC0_X01;QXC0_X02;QX0F_X00;QX0F_X01;QX0F_X02!" );
    } else if( me->seq == 2 ) {
        // instrument status
		dat = ms3_build_message(me->sbuf, sizeof( me->sbuf), "Qx0D_X00;QX0D_X01;QX0D_X02;QX0D_X03!" ); 
    } else if( me->seq == 3 ) {
        // primary & secondary TVI
		dat = ms3_build_message(me->sbuf, sizeof( me->sbuf), "QX0B_X00;QX0B_X01;QX0B_X02;QX0C_X00;QX0C_X01;QX0C_X02!" );
    } else if( me->seq == 4 ) {
		dat = ms3_build_message(me->sbuf, sizeof( me->sbuf), "QX29_X00;QX29_X01;QX29_X02!" ); // drug name
	} else {
		me->seq = 0;
		// ms3_fire( );
		dat = ms3_build_message(me->sbuf, sizeof( me->sbuf), "QXD1!" ); // query significan events
    }
	me->seq++;

	if( dat != NULL ) {
		(*di->comm_func)( di->comm_priv, dat, strlen(dat) );
	}

	return PISTA_OK;
}

int MEDSYS3_cleanup(struct pista_dev_driver *drv )  {
	if( drv->priv != NULL ) {
		PISTA_FREE( drv->priv );
		drv->priv = NULL;
	}
	return PISTA_OK;
}

// R_PRIV 
struct pista_dev_driver medsys3_driver_info = {
        .name = "medsys3",
        .longname = "pump/MedSystem III",
        .api_version = 1,
        .init = MEDSYS3_init,
        .cleanup = MEDSYS3_cleanup,

         .probe = MEDSYS3_probe,
         .verify = MEDSYS3_verify,
         
        // .config_get = NULL,
        .config_set = NULL, // MEDSYS3_config_set,

        .allocate = MEDSYS3_allocate,
        .destroy = MEDSYS3_destroy,
        .handle = MEDSYS3_handle,

	.tick = MEDSYS3_tick,

        .priv = NULL
};

