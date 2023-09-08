
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stddef.h>   /* offsetof */

#include "pista.h"
#include "pista-internal.h"

// #include "lws_config.h"
#include <stdbool.h>

#ifdef _WIN32
#define random rand
#include "gettimeofday.h"
#else
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#endif

#include "skeleton.h"

static struct pista_data_packet *parseVitalsPacket( const char *buf, int len );

void SKELETON_process_pkt( const struct pista_dev_inst *h, const char *buf, int len )
{
	// SKELETON_context *me = (SKELETON_context *)h->priv;

    struct pista_data_packet *sendable = parseVitalsPacket( buf, len );

    if( h->event_handler != NULL && sendable != NULL ) {
        sendable->tm = pista_get_current_time_with_ms();
        h->event_handler( h->event_priv, sendable );
    }

	return;
}

static struct pista_data_packet *parseStreamPacket( const char *buf, int len ) 
{
            printf("FIXME: skeleton/parseVitalsPacket!\n");
            return NULL;
}

static struct pista_data_packet *parseVitalsPacket( const char *buf, int len )
{
            printf("FIXME: skeleton/parseVitalsPacket!\n");
            return NULL;
}

int SKELETON_destroy(struct pista_dev_inst *di) {
    SKELETON_context *me=(SKELETON_context *)di->priv;

    return PISTA_OK;
}


/*
 * send generic connection message
 * move to internal pista library
 */

void pista_util_send_connection( struct pista_dev_inst *h, int code ) {
    printf("sending connection info...\n");
    if( h->event_handler != NULL ) {
        struct pista_data_packet cni;
        cni.tm = pista_get_current_time_with_ms();
        cni.stream_id = PISTA_DF_CONNECTION;
        cni.payload_sz = 0;
        cni.payload = NULL;

        h->status = code; // PISTA_ST_CONNECTED;  // PISTA_ST_NOT_CONNECTED;
        h->event_handler( h->event_priv, &cni );
        printf("sendT...\n");
    }
}

static int SKELETON_prepare_metainfo( struct pista_dev_inst *di, SKELETON_context *me )
{
 	skeleton__vitals__init( &me->v );
 	skeleton__sensors__init( &me->w );

    /*
     * vitals fields
     */
    me->vi.field_cnt = 4;
    me->vi.desc = (struct pista_item_desc *)PISTA_MALLOC( me->vi.field_cnt * sizeof(struct pista_item_desc));
    if( me->vi.desc == NULL ) {
        printf("SKELETON_allocate: alloc error for vi desc\n" );
		return PISTA_ERR;
    }


    int idx = 0;
    pista_set_desc( &me->vi.desc[idx++], "monitor", NULL, NULL, NULL, INT_TYP, offsetof( Skeleton__Vitals, monitored_bits), 1 );
    pista_set_desc( &me->vi.desc[idx++], "alarm", NULL, NULL, NULL, INT_TYP, offsetof( Skeleton__Vitals, alarm_bits), 1 );
    pista_set_desc( &me->vi.desc[idx++], "state", NULL, NULL, NULL, INT_TYP, offsetof( Skeleton__Vitals, datastate_bits), 1 );
    pista_set_desc( &me->vi.desc[idx++], "temp0", NULL, NULL, NULL, INT_TYP, offsetof( Skeleton__Vitals, temp0), 1 );
 
    if( me->vi.field_cnt != idx ) {
        printf("SKELETON_allocate: INTERNAL ERROR: wrong number of fields requested %d != %d\n", me->vi.field_cnt, idx );
		return PISTA_ERR;
    }

    /*
     * waveform fields
     */
    me->wi.field_cnt = 2;
    me->wi.desc = (struct pista_item_desc *)PISTA_MALLOC( me->wi.field_cnt * sizeof(struct pista_item_desc));
    if( me->wi.desc == NULL ) {
        printf("SKELETON_allocate: alloc error for waveform descriptions\n" );
		return PISTA_ERR;
	}

	me->w.n_ecg = 30;
	me->w.n_ibp = 15;

    pista_set_desc( &me->wi.desc[0], "ecg", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Skeleton__Sensors, ecg), me->w.n_ecg );
    pista_set_desc( &me->wi.desc[1], "ibp", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Skeleton__Sensors, ibp), me->w.n_ibp );

	int tot = me->w.n_ecg*sizeof(int32_t);
    tot += me->w.n_ibp*sizeof(int32_t);

	me->w.ecg = (int*) PISTA_MALLOC( tot );
	memset( me->w.ecg, 0, tot );
	me->w.ibp = (int*) (me->w.ecg  + me->w.n_ecg );
	if( me->w.ecg == NULL ) {
        printf("SKELETON_allocate: alloc error for waveform buffer\n" );
		return PISTA_ERR;
	}

    // 1 pkt/sec means freq == &samples
	me->wi.desc[0].freq = 250;  
	me->wi.desc[1].freq = 125;

    printf("SKELETON_allocate: initting packet_data\n" );

    me->vi.stream_id = PISTA_DF_MEASUREMENT;
    me->vi.payload_sz = sizeof( me->v );
    me->vi.payload = &me->v;

    me->wi.stream_id = PISTA_DF_WAVEFORM;
    me->wi.payload_sz = sizeof( me->w );
    me->wi.payload = &me->w;

	di->wf_stream = pista_stream_from_pkt( &me->wi );
	di->m_stream = pista_stream_from_pkt( &me->vi );

	return PISTA_OK;
}

int SKELETON_init( struct pista_context *pista_ctx, struct pista_dev_driver *drv ) {

	drv->priv = NULL;

	return PISTA_OK;
}

int SKELETON_allocate( struct pista_dev_driver *drv, struct pista_dev_inst *di )
{

	SKELETON_context *skeleton = (SKELETON_context *)PISTA_MALLOC( sizeof(SKELETON_context) );
	if( skeleton == NULL ) {
        printf("SKELETON_allocate: alloc error for private data\n" );
		return PISTA_ERR;
	}
    printf("SKELETON_allocate: %lx\n", (long)skeleton );
    memset( skeleton, 0, sizeof( SKELETON_context) );

    // save our local info
    di->priv = skeleton;
    di->driver = drv;
    di->next = NULL;
    di->model = "Skeleton";
    di->version = "0.1";

	di->status = PISTA_ST_NOT_CONNECTED;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->event_handler = NULL;
    di->event_priv = NULL;

    return PISTA_OK;
}

#ifdef _WIN32
DWORD WINAPI skeleton_wf_loop( LPVOID cb_data ) 
#else
static void * skeleton_wf_loop( void *cb_data ) 
#endif
{
    const struct pista_dev_inst *h = cb_data;
    /* During the BACKGROUND operation, tick*/
    SKELETON_context *me = (SKELETON_context *)h->priv;

    sleep(3);
    do {

    send dummy packet!
        sleep(1);

    } while( me->run_thread );

    return 0;
}


void skeleton_startthread( struct pista_dev_inst *h ) { // = (SKELETON_context *)di->priv;
    SKELETON_context *me = (SKELETON_context *)h->priv;

    printf("skeleton_startthread\n" );
    if( h->status != PISTA_ST_CONNECTED ) {
        h->status = PISTA_ST_CONNECTED;
        me->run_thread = true;

#ifdef _WIN32
    DWORD tid = 0;
    me->htid = CreateThread(
        NULL,          // default security attributes
        0,             // default stack
        skeleton_wf_loop,  // thread func
        h, // argument to thread func
        0, // use default creation
        &tid );  // returned thread identifier
#else
        // cdm->mp = PTHREAD_MUTEX_INITIALIZER; 
        /* initialize a mutex to its default value */
        // ret = pthread_mutex_init(&cdm->mp, NULL);

        // ret = pthread_mutexattr_init(&cdm->mattr);
        // ret = pthread_mutexattr_setpshared(&cdm->mattr, PTHREAD_PROCESS_PRIVATE);
        // ?? when ?? pthred_mutexattr_destroy(&cdm->mattr);
        pthread_create( &me->skeleton_thread, NULL, skeleton_wf_loop, h );
#endif
    }
}
 
int SKELETON_connect( struct pista_dev_inst *di )
{
    SKELETON_context *me = (SKELETON_context *)di->priv;

    skeleton_startthread( di );
   
    return PISTA_OK;
}


int SKELETON_tick( const struct pista_dev_inst *di ) {

	// nothing to do hear...everything of interest handled on other thread

    return PISTA_OK;
}

int SKELETON_disconnect( struct pista_dev_inst *di ) {
	SKELETON_context *me = (SKELETON_context *)di->priv;

    di->status = PISTA_ST_NOT_CONNECTED;
    me->run_thread = false;
    return PISTA_OK;
}



static int SKELETON_handle( const struct pista_dev_inst *h, const char *cc, int len )  {
	// SKELETON_context *me = (SKELETON_context *)h->priv;

	SKELETON_process_pkt( h, cc, len );

	return PISTA_OK;
}

int SKELETON_config_set(const struct pista_dev_inst *h, const char *key, const void *settings ) {
	SKELETON_context *me = (SKELETON_context *)h->priv;

    if( strcmp("connection",key) == 0 ) {
        // me->host = strdup(settings);
        fprintf(stderr,"INFO: set host %s\n", me->host );
    } else if( strcmp("user", key) == 0 ) {
        // me->user = strdup(settings);
        fprintf(stderr,"INFO: set user %s\n", me->user );
    } else if( strcmp("host", key) == 0 ) {
        // me->host = strdup(settings);
        fprintf(stderr,"INFO: set host %s\n", me->host );
    } else {
        fprintf(stderr,"ERR: config option not recognized %s=%s\n", key, (char *)settings );
    }

	return PISTA_OK;
}

static int SKELETON_cleanup(struct pista_dev_driver *drv )  {
	if( drv->priv != NULL ) {
		PISTA_FREE( drv->priv );
		drv->priv = NULL;
	}
	return PISTA_OK;
}

// R_PRIV 
struct pista_dev_driver skeleton_driver_info = {
        .name = "skeleton",
        .longname = "monitor/skeleton",
        .api_version = 1,
        .init = SKELETON_init,
        .cleanup = SKELETON_cleanup,

        // .config_get = NULL,
        .config_set = SKELETON_config_set,

        .allocate = SKELETON_allocate,
        .destroy = SKELETON_destroy,
		.connect = SKELETON_connect,
		.disconnect = SKELETON_disconnect,

        .handle = SKELETON_handle,
	    .tick = SKELETON_tick,

        .priv = NULL
};

