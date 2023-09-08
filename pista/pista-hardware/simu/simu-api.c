
/*
 * SIMU driver has the following characteristics:
 * -- vitals sent on TICK thread
 * -- waveforms sent on local thread_local
 *
 *  GCC has tightened compliance specifications when c11 or c99 is specified.  One result is that
 * clock_gettime() is not defined, nor is M_PI. Either specify source as g99/g11 or...
 
Defining _POSIX_C_SOURCE=199309L or 200112L on
the gcc command line, or in a header file, might
expose clock_gettime (per the clock_gettime 'man' page).

Note: one difference between gcc and g++ is that the latter uses -D_GNU_SOURCE.

Notes on encoding and decoding:
if (argc == 3) { msg.has_b = 1; msg.b = atoi(argv[2]); }
len = amessage__get_packed_size(&msg);

buf = malloc(len);
amessage__pack(&msg,buf);
free(buf); 

*/ 

#include <stdio.h>    /* printf */
#include <stdint.h>   /* uint64 */
#include <stdlib.h>   /* exit   */
#include <stddef.h>   /* offsetof */

#include <string.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <unistd.h>  /* sleep */

#include "pista.h"
#include "pista-internal.h"
#include "simu-api.h"

#include <math.h>

static int SIMU_wf_tick(  const struct pista_dev_inst *h ); // forward decl


static void buildIntArray(int *dest, int len, double pos, double scale, double freq, double div) {
        double dt = 1.0/len;
        for( int i = 0; i < len; i++ ) {
            *dest = (int) (scale * sin( M_PI*freq*pos/div ) );
            // *dest += i;
            dest++;
            pos += dt;
        }
        
        return;
}

static void buildFloatArray(float *dest, int len, double pos, double scale, double freq, double div) {
        double dt = 1.0/len;
        for( int i = 0; i < len; i++ ) {
            *dest = (float) (scale * sin( M_PI*freq*pos/div) );
            // *dest += i;
            dest++;
            pos += dt;
        }
        
        return;
}


struct pista_dev_driver *SIMU_init( struct pista_context *pista_ctx )
{
    return &simu_driver_info;
}

int SIMU_allocate( struct pista_dev_inst *di ) {
    
    struct SIMU_context *me = PISTA_MALLOC( sizeof(struct SIMU_context) );
    if( me == NULL ) {
        return PISTA_ERR;
    }
    me->enable_tick_vitals = 0;
    me->dtick = 0;

    di->priv = me;
    di->driver = &simu_driver_info;
    di->next = NULL;
    di->model = "multisin";
    di->version = "0.0";

    di->status = PISTA_ST_NOT_CONNECTED;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->event_handler = NULL;
    di->event_priv = NULL;

     // simu__simu_settings__init( &me->s );
    me->s.hzz = 1;  // 1 hz signal
    me->dtick = 0;
    me->scale = 10;
    // printf("ctx=%lx location dtick=%lx\n", me, &me->dtick );

     simu__simu_vitals__init( &me->v );
     simu__simu_waveform__init( &me->w );

    me->w.n_w0 = 10;
    me->w.n_w1 = 20;
    me->w.n_w2 = 40;
    me->w.n_w3 = 100;
    int tot = me->w.n_w0*sizeof(int32_t) + me->w.n_w1*sizeof(int32_t) + me->w.n_w2*sizeof(float) + me->w.n_w3*sizeof(float);

    me->w.w0 = (int*) PISTA_MALLOC( tot );
    memset( me->w.w0, 0, tot );
    me->w.w1 = (int*) (me->w.w0  + me->w.n_w0 );
    me->w.w2 = (float*) (me->w.w1  + me->w.n_w1 );
    me->w.w3 = (float*) (me->w.w2  + me->w.n_w2 );

    pista_set_named_field_spp( &me->w.base, "w0", me->w.n_w0 );
    pista_set_named_field_spp( &me->w.base, "w1", me->w.n_w1 );
    pista_set_named_field_spp( &me->w.base, "w2", me->w.n_w2 );
    pista_set_named_field_spp( &me->w.base, "w3", me->w.n_w3 );

    // 1 pkt/sec means freq == &samples
    pista_set_named_field_freq( &me->w.base, "w0", me->w.n_w0 );
    pista_set_named_field_freq( &me->w.base, "w1", me->w.n_w1 );
    pista_set_named_field_freq( &me->w.base, "w2", me->w.n_w2 );
    pista_set_named_field_freq( &me->w.base, "w3", me->w.n_w3 );


    strcpy( me->si.source_name, "simu" );
    me->si.payload = &me->s;

    strcpy( me->vi.source_name, "simu" );
    me->vi.stream_id = PISTA_DF_MEASUREMENT;
    me->vi.payload_sz = sizeof( me->v );
    me->vi.payload = &me->v;

    strcpy( me->wi.source_name, "simu" );
    me->wi.stream_id = PISTA_DF_WAVEFORM;
    me->wi.payload_sz = sizeof( me->w );
    me->wi.payload = &me->w;

    me->v.tm = 0x1234;
    me->v.v0 = 0;
    me->v.v1 = 1;
    me->v.v2 = 2;
    me->v.v3 = 3;

    pista_dev_register_stream( di, &me->vi );
    pista_dev_register_stream( di, &me->wi );

    return PISTA_OK;
}

#ifdef _WIN32
DWORD WINAPI simu_wf_loop( LPVOID cb_data ) 
#else
static void * simu_wf_loop( void *cb_data ) 
#endif
{
    const struct pista_dev_inst *h = cb_data;
    /* During the BACKGROUND operation, tick*/
    struct SIMU_context *cdm = (struct SIMU_context *)h->priv;

    do {
        sleep(1);
    if( !cdm->run_thread ) break;
        SIMU_wf_tick( h );
    } while( cdm->run_thread );

    return 0;
}

int SIMU_connect(struct pista_dev_inst *h ) {
    struct SIMU_context *cdm = (struct SIMU_context *)h->priv;

    if( h->status != PISTA_ST_CONNECTED ) {
        h->status = PISTA_ST_CONNECTED;
        cdm->enable_tick_vitals++;
        cdm->run_thread = true;

#ifdef _WIN32
    DWORD tid = 0;
    cdm->htid = CreateThread( 
        NULL,          // default security attributes
        0,             // default stack
        simu_wf_loop,  // thread func
        h, // argument to thread func
        0, // use default creation
        &tid );  // returned thread identifier
#else
        // cdm->mp = PTHREAD_MUTEX_INITIALIZER; 
        /* initialize a mutex to its default value */ 
        // ret = pthread_mutex_init(&cdm->mp, NULL);
        
        // ret = pthread_mutexattr_init(&cdm->mattr);
        // ret = pthread_mutexattr_setpshared(&cdm->mattr, PTHREAD_PROCESS_PRIVATE);
        // ?? when ?? pthread_mutexattr_destroy(&cdm->mattr);
        pthread_create( &cdm->simu_thread, NULL, simu_wf_loop, h );
#endif
    }

    return PISTA_OK;
}

int SIMU_disconnect(struct pista_dev_inst *h ) {
    struct SIMU_context *cdm = (struct SIMU_context *)h->priv;

    printf("SIMU_disconnect\n");
    cdm->enable_tick_vitals--;
    if( cdm->enable_tick_vitals == 0 ) {
        h->status = PISTA_ST_NOT_CONNECTED;
        cdm->run_thread = false;
    }

    return PISTA_OK;
}

static int SIMU_cleanup(struct pista_dev_driver *drv )  {
    if( drv->priv != NULL ) {
        PISTA_FREE( drv->priv );
        drv->priv = NULL;
    }
    return PISTA_OK;
}

int SIMU_destroy(struct pista_dev_inst *h ) {
    struct SIMU_context *me = (struct SIMU_context *)h->priv;

    PISTA_FREE(me);
    h->priv = NULL;

    return PISTA_OK;
}

void *SIMU_config_get(const struct pista_dev_inst *h, const char *key ) {
    struct SIMU_context *me = (struct SIMU_context *)h->priv;

    return &me->s;
}

int SIMU_config_set(const struct pista_dev_inst *h, const char *key, const void *value ) {
    struct SIMU_context *me = (struct SIMU_context *)h->priv;

    if( strcmp(key, "settings") == 0 ) {
        me->s = *(Simu__SimuSettings *)value;
    } else if( strcmp(key, "scale") == 0 ) {
        me->scale = atoi((const char *)value);
    } else {
        printf("SIMU_config_set: invalid key: %s\n", key );
    }

    return PISTA_OK;
}

int SIMU_dump( const struct pista_dev_inst *h, pista_dump_flags flags )  {
    struct SIMU_context *me = (struct SIMU_context *)h->priv;
    if( flags & PISTA_DUMP_CONFIG ) {
        printf("running: %d\n", me->run_thread );
        printf("packets: %d\n", me->packets );
        printf("dtick: %f\n", me->dtick );
        printf("scale: %f\n", me->scale );
    }
    if( flags & PISTA_DUMP_STREAMS ) {
        printf("FIXME: dump SIMU Numeric Items:\n" );
        // pista_dump_desc( me->vi.desc, me->vi.field_cnt, me->vi.payload );
        printf("FIXME: dump SIMU Waveform Items:\n" );
        // pista_dump_desc( me->wi.desc, me->wi.field_cnt, me->wi.payload );
    }
    
    return PISTA_OK;
}

static int SIMU_wf_tick( const struct pista_dev_inst *h )  {
    struct SIMU_context *me = (struct SIMU_context*)h->priv;
    

    long dt = pista_get_current_time_with_ms();


    buildIntArray(me->w.w0, me->w.n_w0, me->dtick, me->scale, me->s.hzz, 8 );
    buildIntArray(me->w.w1, me->w.n_w1, me->dtick, me->scale, me->s.hzz, 4 );
    buildFloatArray(me->w.w2, me->w.n_w2, me->dtick, me->scale, me->s.hzz, 2 );
    buildFloatArray(me->w.w3, me->w.n_w3, me->dtick, me->scale, me->s.hzz, 1 );
    // printf("ctx=%lx wf_tick location dtick=%lx\n", me, &me->dtick);

    me->dtick += 1;

    if( h->event_handler != NULL ) {
        me->wi.tm = dt;
        h->event_handler(h->event_priv, &me->wi );
    }
    return PISTA_OK;
}

static int SIMU_meas_tick( const struct pista_dev_inst *inst )  {
    struct SIMU_context *me = (struct SIMU_context*)inst->priv;


    long dt = pista_get_current_time_with_ms();

    me->v.tm = dt;  // current time
    me->vi.tm = dt;

    me->v.v0 = (me->v.v0 + 1)%100;
    me->v.v1 = (me->v.v1 + 1)%10;
    me->v.v2 = (me->v.v2 + 1)%5;
    me->v.v3 = (me->v.v3 + 1)%2;

    if( inst->event_handler != NULL ) {
        me->vi.tm = dt;
        inst->event_handler(inst->event_priv, &me->vi );
    }
    return PISTA_OK;
}

struct pista_data_packet *SIMU_poll( const struct pista_dev_inst *inst, int sid )  {
    struct SIMU_context *me = (struct SIMU_context*)inst->priv;
    struct pista_data_packet *pkt = NULL;

    if( sid == 'M' ) {
        SIMU_meas_tick(inst);
        pkt = &(me->vi);
    } else if( sid == 'W' ) {
        SIMU_wf_tick(inst);
        pkt = &(me->wi);
    } else if( sid == 'S' ) {
        pkt = &(me->si);
    }

    return pkt;
}


struct pista_dev_driver simu_driver_info = {
        .name = "simu",
        .longname = "z/Sine Wave Simulator",
        .api_version = 1,
        .init = SIMU_init,
        .cleanup = SIMU_cleanup,

        /* .config_get = NULL, */
        .config_get = SIMU_config_get,
        .config_set = SIMU_config_set,

        .connect = SIMU_connect,
        .disconnect  = SIMU_disconnect,

        .allocate = SIMU_allocate,
        .destroy = SIMU_destroy,
        .handle = NULL,
        .dump = SIMU_dump,

        .tick = SIMU_meas_tick,
        .poll = SIMU_poll,

        .priv = NULL
};

