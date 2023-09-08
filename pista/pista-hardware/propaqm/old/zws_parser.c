#include <yajl/yajl_parse.h>  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

#include "propaqm.h"

#pragma GCC diagnostic ignored "-Wpointer-sign"

typedef enum {
    zoll_unknown,
    zoll_waveform,
    zoll_alarm,
    zoll_parm,
    zoll_status,
    zoll_althdr, // an underspecified packet type
    zoll_althdr_param,
    zoll_althdr_webcon,
} zoll_pkt_type;

static int depth;
static int array_depth;
static zoll_pkt_type pkt_typ = zoll_unknown;
int PROPAQM_verbose = 0;

static char *key_stack[16];

#define MAX_WAVES 5
static int sampleStatus[MAX_WAVES][30];

void zws_reset()  
{
    depth = 0;
    array_depth = 0;
}

static int zws_parser_null(void * ctx)  
{  
    printf("reform null\n");
    return 1; // yajl_gen_status_ok == yajl_gen_null(g);  
}  
  
static int zws_parser_boolean(void * ctx, int boolean)  
{  
    printf("reform boolean: %d\n", boolean );
    return 1; // yajl_gen_status_ok == yajl_gen_bool(g, boolean);  
}  
  
static int atoi_n( const char *s, size_t l) {
    char buf[24];
    int  val = 0;

    if( l < sizeof(buf) ) {

        memcpy(buf, s, l);
        buf[l] = '\0';
        val = atoi(buf);
    }

    return val;
}

static int zws_parser_number(void * ctx, const char * s, size_t l)  
{  
    const struct pista_dev_inst *h = (struct pista_dev_inst *)ctx;
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    if( pkt_typ == zoll_waveform && depth >= 2) {
        char * key = key_stack[depth];

        if( me->arr_dest != NULL ) {

	    if( me->arr_pos < me->arr_max ) {
            	me->arr_dest[me->arr_pos++] = atoi_n( s, l);
	    } else {
		printf("FIXME: zws_parser_number overrun %d\n", me->arr_pos );
	    }
        }
        if( strcmp( "@WaveNum", key) == 0 ) {
            me->wave_num = atoi_n( s, l);
        }
        if( strcmp( "Status", key) == 0 ) {
            me->wave_status = atoi_n( s, l);
        }
    }
    return 1;
}  
  
static int zws_parser_string(void * ctx, const unsigned char * stringVal,  
                           size_t stringLen)  
{  

    char * key = key_stack[depth];

    if( pkt_typ == zoll_althdr && depth == 2 ) {
        if( strcmp( "Type", key) == 0 
                ) {

            if( strncmp( stringVal, "WebCon", 6) == 0 ) {
                pkt_typ = zoll_althdr_webcon;
            } else if( strncmp( stringVal, "Param", 5) == 0 ) {
                pkt_typ = zoll_althdr_param;
            }
        }
    }

    return 1; // yajl_gen_status_ok == yajl_gen_string(g, stringVal, stringLen);  
}  
  
void clear_waveform_data( PROPAQM_context *me ) {
    me->wave_num = 0;
    me->wave_status = -1;
    me->arr_pos = 0;
    me->arr_dest = NULL;
}
static int zws_parser_map_key(void * ctx, const unsigned char * stringVal,  
                            size_t stringLen)  
{  
    const struct pista_dev_inst *h = (struct pista_dev_inst *)ctx;
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    key_stack[depth] = strndup(stringVal, stringLen);

    if( depth == 1 && pkt_typ == zoll_unknown ) {
        if( strncmp( stringVal, "StdHdr", 6) == 0 ) {
            // ignore
        } else if( strncmp( stringVal, "AltHdr", 6) == 0 ) {
            pkt_typ = zoll_althdr;
        } else if( strncmp( stringVal, "Waveform", 8) == 0 ) {
            pkt_typ = zoll_waveform;
            clear_waveform_data( me );
        } else if( strncmp( stringVal, "AudioAlarm", 10) == 0 ) {
            pkt_typ = zoll_alarm;
        } else if( strncmp( stringVal, "Parm", 4) == 0 ) {
            pkt_typ = zoll_parm;
            printf("PARAM!\n");
        } else if( strncmp( stringVal, "Status", 6) == 0 ) {
            pkt_typ = zoll_status;
        } else if( strncmp( stringVal, "ZOLL", 6) == 0 ) {
            pkt_typ = zoll_status;
        } else {
            printf("  unknown key: %.*s\n", (int)stringLen, stringVal );
        }
    } else if( depth >= 2 && pkt_typ == zoll_althdr ) {
    } else if( depth == 2 && pkt_typ == zoll_waveform ) {
        // printf("  %s sub key: %.*s\n", key_stack[depth-1], (int)stringLen, stringVal );
    }

    //if( PROPAQM_verbose > 0 ) {
        //printf("[%d] %s --> \n", depth, key_stack[depth], pkt_typ );
    //}

    return 1;
}  
  
static int zws_parser_start_map(void * ctx)  
{  
    if( depth == 0 ) {
        pkt_typ = zoll_unknown;
    }
    depth++;
    return 1;
}  
  
int64_t tm0 = 0;
  
static int zws_parser_end_map(void * ctx)  
{  
    const struct pista_dev_inst *h = (struct pista_dev_inst *)ctx;
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    depth--;
    if( depth == 0 ) {
       struct pista_data_packet *sendable = NULL;

       if( pkt_typ == zoll_unknown ) {
           printf("ERR: unknown packet\n");
       } else if( pkt_typ == zoll_althdr ) {
           printf("ERR: ignoring unspecified zws althdr packet\n");
       } else {
            if( pkt_typ == zoll_waveform ) {
                // printf("w");
                sendable = &me->wi;
            } else if( pkt_typ == zoll_althdr_param ) {
                // printf("p");
            } else if( pkt_typ == zoll_alarm ) {
                // printf("a");
            } else if( pkt_typ == zoll_status ) {
                // printf("s");
            } else {
                printf("FIRE REQ UNKNOWN: %d\n", pkt_typ );
            }

       }
       
       if( sendable != NULL && h->event_handler != NULL ) {
            int64_t tm = pista_get_current_time_with_ms();
            if( tm0 == 0 ) {
                tm0 = tm;
            }
            if( pkt_typ == zoll_waveform ) {
                int64_t exp_tm = me->wi.tm + (1000 * 30 / 250);
                if( exp_tm < tm && abs( tm - exp_tm ) < 2000 ) {
                    tm = exp_tm;
                }
            }
            sendable->tm = tm;

            struct pista_data_packet pkt;
            pista_init_data_packet( &pkt, 0, "propaqm", PISTA_DF_WAVEFORM, sizeof( me->w ), &me->w );
            h->event_handler( h->event_priv, sendable );
       }

       pkt_typ = zoll_unknown;
    }
    return 1;
}  
  
static int zws_parser_start_array(void * ctx)  
{  
    const struct pista_dev_inst *h = (struct pista_dev_inst *)ctx;
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    array_depth++;

    me->arr_dest = NULL;
    char *key = key_stack[depth];

    if( pkt_typ == zoll_waveform && depth == 3 ) {
        if( strcmp( key, "UnpackedSamples" ) == 0 ) {
            me->arr_pos = 0;
            if( me->wave_num == 1 ) {
                me->arr_dest = me->w.ecg;
		me->arr_max = me->w.n_ecg;
            } else if( me->wave_num == 2 ) {
                me->arr_dest = me->w.co2;
		me->arr_max = me->w.n_co2;
            } else {
		me->arr_dest = NULL;
		me->arr_max = 0;
                fprintf(stderr,"zws_parser invalid wave number for parser: %d\n", me->wave_num );
            }
        } else if( strcmp( key, "SampleStatus" ) == 0 ) {
	    if( me->wave_num < MAX_WAVES ) {
            	me->arr_pos = 0;
		me->arr_max = 30;
            	me->arr_dest = sampleStatus[me->wave_num];
	    } else {
		me->arr_dest = NULL;
		me->arr_max = 0;
	    	printf("FIXME: sampleStatus=%d\n", me->wave_num );
	    }
        }
    }
    return 1;
}  
  
static int zws_parser_end_array(void * ctx)  
{  
    const struct pista_dev_inst *h = (struct pista_dev_inst *)ctx;
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    array_depth--;
    me->arr_dest = NULL;
    return 1;
}  
  
yajl_callbacks zws_callbacks = {  
    zws_parser_null,  
    zws_parser_boolean,  
    NULL,  
    NULL,  
    zws_parser_number,  
    zws_parser_string,  
    zws_parser_start_map,  
    zws_parser_map_key,  
    zws_parser_end_map,  
    zws_parser_start_array,  
    zws_parser_end_array  
};  

