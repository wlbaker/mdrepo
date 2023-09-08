/*****************************************************************

File:                         mcc-ul.c

Description:                  Driver for Measurement Computing Corporation A/D devices

Special Requirements:         Board 0 must have an A/D converter.
                              Analog signals on an input channel.

*******************************************************************/




#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>   /* offsetof */


#include <unistd.h>

#include "pista.h"
#include "pista-internal.h"
//?? #include <windows.h>

#ifndef _WIN32
#define _WIN32  1
#endif

#include "cbw.h"
#include "model/mccul.pb-c.h"

#define LOG_PREFIX "mccul"

typedef Mccul__McculSettings mccul_settings;

typedef struct _mccul_priv {
    /*
     * internal run state variables
     */

    int board_num;
    unsigned options;

    long sample_count; // a diagnostic tool

    long curr_index;
    long scans_per_pkt;
    long pkt_sz;
    long buf_sz;
    HANDLE mem_handle;
    short status;
    float     revision;

    /*
     * data exchange buffers
     */

    Mccul__McculSettings settings;
    Mccul__McculIsensor  isensor;
    Mccul__McculFsensor fsensor;

    struct pista_data_packet s_pkt;
    struct pista_data_packet i_pkt;
    struct pista_data_packet f_pkt;

    /*
     * convenience arrays...very convenient!
     */

    int   *idest[16];
    float *fdest[16];

} mccul_priv;



// forward declaration
static int MCCUL_init( struct pista_context *pista_ctx, struct pista_dev_driver *drv );
static int MCCUL_handle_data_available( struct pista_dev_inst *di, int len );
static int MCCUL_allocate( struct pista_dev_driver *drv, struct pista_dev_inst *di );
static int MCCUL_connect( struct pista_dev_inst *di );
static int MCCUL_disconnect( struct pista_dev_inst *di );

void __stdcall callbackFunc( int boardNum, unsigned eventTyp, unsigned eventData, void *userData ) {
	int stat;
	short status;
	long currCount;
	long currIndex;
    	struct pista_dev_inst *di = userData;

	long tid = GetCurrentThreadId();

	switch( eventTyp ) {
	case ON_DATA_AVAILABLE:
		{
		// printf("DAT[%d,%d]\n", tid, eventData );  // total number of samples
		mccul_priv *pp = (mccul_priv *)di->priv;
		pp->sample_count += pp->pkt_sz;
		if( pp->sample_count != (long)eventData ) {
			printf("internal error: count mismatch %d != %d\n", eventData, pp->sample_count );
		}

		MCCUL_handle_data_available( di, pp->scans_per_pkt );
		}
		break;
	case ON_SCAN_ERROR:
		printf("ERR[%d]: ??\n", eventData );
		break;
	default:
		printf("UNKNOWN eventType: %d\n", eventTyp );
		break;
	}

}



static int MCCUL_init( struct pista_context *pista_ctx, struct pista_dev_driver *drv ) {


    mccul_priv *pp = drv->priv;


    int ret = cbDeclareRevision(&pp->revision);
    if( ret ) {
    	printf ( "MCCUL_init cbDeclareRevision failed with rc=%d.", ret);
    }

    cbErrHandling (PRINTALL, DONTSTOP);

	printf("MCCUL_init driver=%lx\n", drv );

    return PISTA_OK;
}

static void init_idata(int **idest, void *payload, struct pista_item_desc *descs, int low_chan, int high_chan, int freq, int spp)
{
	for( int i = 0; i < 16; i++ ) {
		if( idest[i] != NULL ) PISTA_FREE( idest[i] );

		struct pista_item_desc *desc = &descs[i];
		desc->spp = spp;
		desc->freq = freq;
		int **ch_dat = (int **)(payload + desc->offset);
		if( i >= low_chan && i <= high_chan ) {
			*ch_dat = (int *)PISTA_MALLOC( sizeof(int) * spp);
		} else {
			*ch_dat = NULL;
		}
		idest[i] = *ch_dat;
	}
}

static void init_fdata(float **fdest, void *payload, struct pista_item_desc *descs, int low_chan, int high_chan, int freq, int spp)
{
	for( int i = 0; i < 16; i++ ) {
		if( fdest[i] != NULL ) PISTA_FREE( fdest[i] );

		struct pista_item_desc *desc = &descs[i];
		desc->spp = spp;
		desc->freq = freq;
		float **ch_dat = (float **)(payload + desc->offset);
		if( i >= low_chan && i <= high_chan ) {
			*ch_dat = (float *)PISTA_MALLOC( sizeof(float) * spp);
		} else {
			*ch_dat = NULL;
		}
		fdest[i] = *ch_dat;
	}
}


static int MCCUL_allocate( struct pista_dev_driver *drv, struct pista_dev_inst *di ) {
	
	mccul_priv *me = PISTA_MALLOC( sizeof(mccul_priv) );
	if( me == NULL ) {
		return PISTA_ERR;
	}

    	me->board_num = 0;
    	me->revision = (float)CURRENTREVNUM;
    	me->options = CONVERTDATA + BACKGROUND + CONTINUOUS;
    	me->pkt_sz = 0;
    	me->buf_sz = 0;
    	me->mem_handle = 0;
    	me->status = IDLE;
    	me->curr_index = 0;

	di->priv = me;
	di->driver = drv;  // WARNING: this should have been done by the caller
    di->next = NULL;
    // di->vendor = "internal";
    di->model = "mccul";
    di->version = "0.0";

	di->status = PISTA_ST_NOT_CONNECTED;

	memset( &me->settings, 0, sizeof( me->settings) );
	memset( &me->isensor, 0, sizeof( me->isensor) );
	memset( &me->fsensor, 0, sizeof( me->fsensor) );

 	mccul__mccul_settings__init( &me->settings );
 	mccul__mccul_isensor__init( &me->isensor );
 	mccul__mccul_fsensor__init( &me->fsensor );

    me->s_pkt.payload_sz = sizeof(Mccul__McculSettings );
    me->i_pkt.payload_sz = sizeof(Mccul__McculIsensor);
    me->f_pkt.payload_sz = sizeof(Mccul__McculFsensor);

    me->s_pkt.payload = &me->settings;
    me->i_pkt.payload = &me->isensor;
    me->f_pkt.payload = &me->fsensor;


	me->s_pkt.stream_id = PISTA_DF_SETTINGS;
	me->i_pkt.stream_id = PISTA_DF_MEASUREMENT;
	me->f_pkt.stream_id = PISTA_DF_WAVEFORM;

	me->settings.low_chan = 0;  // default settings: 2 channels, 100hz
	me->settings.high_chan = 1;
    	me->settings.hzz = 100;
    	me->settings.gain = BIP5VOLTS;

	me->scans_per_pkt = (int)me->settings.hzz;
	if( me->scans_per_pkt < 1 ) me->scans_per_pkt = 1;

    me->i_pkt.field_cnt = 16;
    me->i_pkt.desc = (struct pista_item_desc *)PISTA_MALLOC( me->i_pkt.field_cnt * sizeof(struct pista_item_desc));

    pista_set_desc( &me->i_pkt.desc[0], "ch0", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch0),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[1], "ch1", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch1),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[2], "ch2", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch2),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[3], "ch3", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch3),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[4], "ch4", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch4),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[5], "ch5", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch5),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[6], "ch6", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch6),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[7], "ch8", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch7),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[8], "ch8", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch8),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[9], "ch9", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch9),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[10], "ch10", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch10),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[11], "ch11", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch11),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[12], "ch12", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch12),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[13], "ch13", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch13),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[14], "ch14", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch14),me->scans_per_pkt );
    pista_set_desc( &me->i_pkt.desc[15], "ch15", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Mccul__McculIsensor, ch15),me->scans_per_pkt );

    me->f_pkt.field_cnt = 16;
    me->f_pkt.desc = (struct pista_item_desc *)PISTA_MALLOC( me->f_pkt.field_cnt * sizeof(struct pista_item_desc));

    pista_set_desc( &me->f_pkt.desc[0], "ch0", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch0),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[1], "ch1", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch1),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[2], "ch2", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch2),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[3], "ch3", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch3),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[4], "ch4", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch4),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[5], "ch5", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch5),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[6], "ch6", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch6),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[7], "ch8", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch7),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[8], "ch8", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch8),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[9], "ch9", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch9),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[10], "ch10", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch10),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[11], "ch11", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch11),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[12], "ch12", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch12),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[13], "ch13", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch13),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[14], "ch14", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch14),me->scans_per_pkt );
    pista_set_desc( &me->f_pkt.desc[15], "ch15", NULL, NULL, NULL, FLOAT_ARR_TYP, offsetof( Mccul__McculFsensor, ch15),me->scans_per_pkt );


	di->wf_stream = pista_stream_from_pkt( &me->f_pkt );
	di->m_stream = pista_stream_from_pkt( &me->i_pkt );

	for( int i = 0; i < 16; i++ ) {
		me->idest[i] = NULL;
		me->fdest[i] = NULL;
	}
	return PISTA_OK;
}

static int MCCUL_connect( struct pista_dev_inst *di ) {
    BOOL HighResAD = FALSE;
    int  ADRes;

    mccul_priv *pp = di->priv;
    mccul_settings *s = &pp->settings;

    pp->sample_count = 0;

    long hzz = s->hzz;
    int n_chans = s->high_chan - s->low_chan + 1; 

    pp->scans_per_pkt = hzz;
    pp->pkt_sz = hzz * n_chans;
    pp->buf_sz = 4*pp->pkt_sz;

	printf("%s: hzz=%d low-chan=%d high-chan=%d\n", LOG_PREFIX, s->hzz, s->low_chan, s->high_chan );

    init_idata(pp->idest, pp->i_pkt.payload, pp->i_pkt.desc, pp->settings.low_chan, pp->settings.high_chan,pp->settings.hzz, pp->scans_per_pkt );
    init_fdata(pp->fdest, pp->f_pkt.payload, pp->f_pkt.desc, pp->settings.low_chan, pp->settings.high_chan,pp->settings.hzz, pp->scans_per_pkt );

	/* Get the resolution of A/D */
	cbGetConfig(BOARDINFO, pp->board_num, 0, BIADRES, &ADRes);
	printf("%s: a2d res: %d\n", LOG_PREFIX, ADRes );
	
	/* check If the resolution of A/D is higher than 16 bit.
       If it is, then the A/D is high resolution. */
	if(ADRes > 16)
		HighResAD = TRUE;

	/*  set aside memory to hold data */
	if(HighResAD) {
		pp->mem_handle = (HANDLE)cbWinBufAlloc32(pp->buf_sz);
	} else {
		pp->mem_handle = (HANDLE)cbWinBufAlloc(pp->buf_sz);
	}

    if (!pp->mem_handle)    /* Make sure it is a valid pointer */
        {
        printf("%s: out of memory [req=%d]\n", LOG_PREFIX, pp->buf_sz );
	return -1;
        }

    // install my callback handler
    // read docs carefully, eventParam is number of samples/event
    cbEnableEvent( pp->board_num, ON_DATA_AVAILABLE, pp->pkt_sz - 1, callbackFunc, (void *)di ); 


    /* Collect the values with cbAInScan() in BACKGROUND mode, CONTINUOUSLY
        Parameters:
             board_num    :the number used by CB.CFG to describe this board
             low_chan     :low channel of the scan
             high_chan    :high channel of the scan
             Count       :the total number of A/D samples to collect
             Rate        :sample rate in samples per second
             Gain        :the gain for the board
             ADData[]    :the array for the collected data values
             Options     :data collection options */

    int ret = cbAInScan (pp->board_num, s->low_chan, s->high_chan, pp->buf_sz, &hzz, s->gain, pp->mem_handle, pp->options);
    if( ret ) {
	printf("%s: could not start scan rc=%d\n", LOG_PREFIX, ret );
    } else {
    	pp->status = RUNNING;
    }
    if( hzz != s->hzz ) {
	printf("%s: HZ reset?  %d != %d\n -- NOT REFLECTED IN pp->pkt_sz -- TOO BIG and EVENT SPEED !!!", LOG_PREFIX, hzz, s->hzz );
    }


    printf ("%s: connected\n", LOG_PREFIX );
    return PISTA_OK;
}

static int MCCUL_disconnect( struct pista_dev_inst *di ) {

    mccul_priv *pp = di->priv;
    pp->status = IDLE;

    int ret = cbStopBackground (pp->board_num,AIFUNCTION);
    if( ret ) {
	printf( "MCCUL_disconnect: could not disconnect rc=%d\n", ret );
    }
    return PISTA_OK;
}


static int MCCUL_handle_data_available( struct pista_dev_inst *di, int scans ) {
	mccul_priv *me=(mccul_priv *)di->priv;

	WORD *ADData = (WORD*)me->mem_handle;

	me->curr_index %= me->buf_sz;
	// printf("aDD[%d,%d] %lx + %d =", scans, me->buf_sz, ADData, me->curr_index );
	ADData += me->curr_index;
	// printf("%lx:", ADData );

	me->curr_index += me->pkt_sz;
	me->curr_index %= me->buf_sz;

	float **fdest = me->fdest;
	int   **idest = me->idest;


	int idx = 0;
	int gain = me->settings.gain;

	int chan;
	float val;

	int low_chan = me->settings.low_chan;
	int high_chan = me->settings.high_chan;

	while( scans-- > 0 ) {
		for(chan = low_chan; chan <= high_chan; chan++) {
			USHORT dat = *(ADData++);
			if( idest[chan] != NULL ) {
				idest[chan][idx]  = dat;
			}
			// if( idx < 10 ) printf(" %4.2f,",  val );
			if( fdest[chan] != NULL ) {
    				cbToEngUnits (me->board_num, gain, dat, &val);
				fdest[chan][idx]  = val;
			}
		}
		idx++;
	}
	// printf("\n");

    long dt = pista_get_current_time_with_ms();
    if( di->event_handler != NULL ) {

    	me->f_pkt.tm = dt;
        di->event_handler(di->event_priv, &me->f_pkt );
    }

	return PISTA_OK;
}

static int MCCUL_config_set(const struct pista_dev_inst *di, const char *key, const void *settings ) {
	mccul_priv *me=(mccul_priv *)di->priv;
    	mccul_settings *s = &me->settings;

	if( key == NULL ) {
		// reserved for a setup structure
		printf("%s: unknown option - full config\n", LOG_PREFIX );
	} else if ( !strcmp("hzz", key )) {
    		int hzz = (int)atoi( (char *)settings );
		if( hzz < 1 ) hzz = 1;
		s->hzz = hzz;
		me->scans_per_pkt = hzz;
		for( int i = 0; i < 16; i++ ) {
    		    me->f_pkt.desc[i].freq = me->f_pkt.desc[i].spp = hzz;
    		    me->i_pkt.desc[i].freq = me->i_pkt.desc[i].spp = hzz;
		}

	} else if ( !strcmp("low-chan", key )) {
    		s->low_chan = (int)atoi( (char *)settings );
	} else if ( !strcmp("high-chan", key )) {
    		s->high_chan = (int)atoi( (char *)settings );
	} else if ( !strcmp("gain", key )) {
		printf("%s: ignoring gain setting.\n", LOG_PREFIX );
    		// ? BIP5VOLTS;
    		// s->gain = (int)settings;
	} else {
		printf("%s: unknown option - %s\n", LOG_PREFIX, key );
	}
	return PISTA_OK;
}

static int MCCUL_destroy(struct pista_dev_inst *h) {
	// stop data flow
	return PISTA_OK;
}

static int MCCUL_tick( const struct pista_dev_inst *dri )  {

	return PISTA_OK;
}

static int MCCUL_cleanup(struct pista_dev_driver *drv )  {
	if( drv->priv != NULL ) {
		PISTA_FREE( drv->priv );
		drv->priv = NULL;
	}
	return PISTA_OK;
}

// R_PRIV 
struct pista_dev_driver mccul_driver_info = {
        .name = "mccul",
        .longname = "Measurement Corporation UL Device",
        .api_version = 1,
        .init = MCCUL_init,
        .cleanup = MCCUL_cleanup,

        .config_get = NULL,
        .config_set = MCCUL_config_set,

        .allocate = MCCUL_allocate,
        .destroy = MCCUL_destroy,

	.connect = MCCUL_connect,
	.disconnect = MCCUL_disconnect,
        .handle = NULL, // MCCUL_handle,

	.tick = MCCUL_tick,

        .priv = NULL
};

#ifdef TEST_API

void main ()
{

    long loop = 0;

    struct pista_context *ctx = NULL;
    struct pista_dev_driver drv;
    struct pista_dev_inst di;


    long tid = GetCurrentThreadId();
    printf ("%d ---------------------------------------------------------\n", tid);

    setbuf( stdout, NULL ); // use this if you want unbuffered stdout for JVM debugging

    MCCUL_init( ctx, &drv );
    MCCUL_allocate( &drv, &di );
    MCCUL_connect( &di );


    /* During the BACKGROUND operation, check the status */
    while ( loop < 30 ) {

	    loop++;
	    sleep(1);
	    // printf("beep.\n");
        //
        MCCUL_tick( &di );

    }
    printf ("Data collection terminated.\n");
    sleep(1);

    MCCUL_disconnect( &di );
    MCCUL_destroy( &di );

    printf ("Stopped and released\n");
}

#endif
