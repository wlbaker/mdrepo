
#include <windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "pista.h"
#include "pista-internal.h"
#include "api.h"


#define SHOW_ERROR(ecode) MessageBox(HWND_DESKTOP,olDaGetErrorString(ecode,\
                  str,STRLEN),"Error", MB_ICONEXCLAMATION | MB_OK);

#define CHECKERROR(ecode) if ((me->status = (ecode)) != OLNOERROR)\
                  {\
                  SHOW_ERROR(me->status);\
                  olDaReleaseDASS(me->hdass);\
                  olDaTerminate(me->hdrvr);\
                  return ((UINT)NULL);}

#define CLOSEONERROR(ecode) if ((me->status = (ecode)) != OLNOERROR)\
                  {\
                  SHOW_ERROR(me->status);\
                  olDaReleaseDASS(me->hdass);\
                  olDaTerminate(me->hdrvr);\
                  EndDialog(hDlg, TRUE);\
                  return (TRUE);}

BOOL CALLBACK
GetDriver( LPSTR lpszName, LPSTR lpszEntry, LPARAM lParam )
/*
 * this is a callback function of olDaEnumBoards, it gets the 
 * strings of the Open Layers me->and attempts to initialize
 * the me->  If successful, enumeration is halted.
 * */
{
   LPBOARD lpme = (LPBOARD)(LPVOID)lParam;

   /* fill in me->strings */

   lstrcpyn(lpme->name,lpszName,STRLEN);
   lstrcpyn(lpme->entry,lpszEntry,STRLEN);

   /* try to open me->*/

   lpme->status = olDaInitialize(lpszName,&lpme->hdrvr);
   if   (lpme->hdrvr != NULL)
      return FALSE;          /* false to stop enumerating */
   else
      return TRUE;           /* true to continue          */
}


static int DT_init( struct pista_context *pista_ctx, struct pista_dev_driver *drv ) {

	drv->priv = NULL;

	// DISCOVERY
	//
	CHECKERROR (olDaEnumBoards(GetDriver,(LPARAM)(LPBOARD)&me->);

    /* check for error within callback function */

    CHECKERROR (me->status);

    if (me->hdrvr == NULL){
      std::cerr << " No Open Layer me->!!!" << std::endl;
      return PISTA_ERR;
    }


   /* get handle to first available ADC sub system */
   CHECKERROR(olDaGetDevCaps(me->hdrvr,OLDC_ADELEMENTS,&numberADs));

    while(1) { //   Enumerate through all the A/D subsystems select the first available one...
   {
        ec=olDaGetDASS(me->hdrvr,OLSS_AD,currentAD,&me->hdass);
        if (ec!=OLNOERROR)
        {
        // busy subsys etc...
        currentAD++;
        if (currentAD>numberADs)
        {
            std::cerr << "No Available A/D Subsystems!" << std::endl;
            return PISTA_ERR;
        }

        }
        else
        break;

   }

	// olDaGetDASS();
	// olDaSetDataFlow();

	return PISTA_OK;
}

static int DT_allocate( struct pista_dev_driver *drv, struct pista_dev_inst *di ) {
	
	struct DT_context *me = PISTA_MALLOC( sizeof(struct DT_context) );
	if( me == NULL ) {
		return PISTA_ERR;
	}
	di->priv = me;

	di->status = PISTA_ST_NOT_CONNECTED;

 	dt__dt_settings__init( &me->s );  // PROTOBUF_C_MESSAGE_INIT (&u3__u3_settings__descriptor);
	me->s.hzz = 100;
	me->s.rps = 1;
	me->s.ms  = 500;
	me->s.in_mask  = 0x0f;  // first 4 channels

	me->s.gain = 1.0;  // first 4 channels

    me->n_channels = 0;
    me->channel_map = NULL;

    /*
     *       Set up the ADC - multiple wrap so we can get buffer reused
     *             window messages.
     *                
     */

    CHECKERROR (olDaGetSSCapsEx(me->hdass,OLSSCE_MAXTHROUGHPUT,&me->cap.max_hzz));
    CHECKERROR (olDaGetSSCaps(me->hdass,OLSSC_NUMDMACHANS,&me->cap.dma));
    CHECKERROR (olDaGetSSCaps(me->hdass,OLSSC_SUP_PROGRAMGAIN,&me->cap.gainsup));
    CHECKERROR (olDaGetSSCaps(me->hdass,OLSSC_SUP_NUMCHANNELS,&me->cap.nchannels));

	return PISTA_OK;
}

static unsigned int bitCount (unsigned int value) {
    unsigned int count = 0;
    while (value > 0) {           // until all bits are zero
        if ((value & 1) == 1)     // check lower bit
            count++;
        value >>= 1;              // shift bits, removing lower bit
    }
    return count;
}

static int DT_dev_start(const struct pista_dev_inst *h ) {
    struct DT_context *me = (struct DT_context *)h->priv;


   UINT dma  = min (1, me->cap.dma);            /* try for one dma channel   */
   double freq = min (1000.0, me->cap.freq);      /* try for 1000hz throughput */

   UINT mask = me->s.in_mask;
   me->n_channels = bitCount( me->s.in_flags);
   me->channel_map = new int[ me->n_channels ];

   CHECKERROR (olDaSetChannelListSize(me->hdass, me->n_channels ));
   CHECKERROR (olDaSetDataFlow(me->hdass,OL_DF_CONTINUOUS));
   CHECKERROR (olDaSetWrapMode(me->hdass,OL_WRP_MULTIPLE));
   CHECKERROR (olDaSetClockFrequency(me->hdass,freq));
   CHECKERROR (olDaSetDmaUsage(me->hdass,dma));

   for( int i = 0; i < me->cap.nchannels ; i++ ) {
		if( mask & 0x01 ) {
		
			channel = i;
   			CHECKERROR (olDaSetChannelListEntry(me->hdass,0,channel));
		}
		mask = mask >> 1;
   }

   /* only set the gain if the board it */

   if (me->cap.gainsup) {
      CHECKERROR (olDaSetGainListEntry(me->hdass,0,me->s.gain));
      CHECKERROR (olDaSetGainListEntry(me->hdass,1,me->s.gain));
   }


   CHECKERROR (olDaConfig(me->hdass));

   UINT size = (UINT)freq/1;     /* 1 second buffer */

   /* allocate the input buffers */
   /* Put the buffer to the ADC  */

	UINT samplesize;
    CHECKERROR(olDaGetResolution(me->hdass,&samplesize));
    if (samplesize > 16)
        samplesize=4; /*4 bytes... e.g. 24 bits = 4 btyes */
    else
        samplesize=2;             /* e.g. 16 or 12 bits = 2 bytes */

	HBUF hBuffer;
   for (i=0;i<NUM_BUFFERS;i++)
   {
      CHECKERROR (olDmCallocBuffer(0,0,(ULNG) size,samplesize,&hBuffer));
      CHECKERROR (olDaPutBuffer(me->hdass, hBuffer));
   }

   /*
 *       get the input buffers from the ADC subsystem and
 *             free the input buffers
 *                */

   CHECKERROR (olDaFlushBuffers(me->hdass));

   for (i=0;i<NUM_BUFFERS;i++)
   {
      CHECKERROR (olDaGetBuffer(me->hdass, &hBuffer));
      CHECKERROR (olDmFreeBuffer(hBuffer));
   }

	return PISTA_OK;

close:
	// DT_closeUSBConnection(cdm);
	// cdm->hDevice = NULL;

	return PISTA_ERR;
}

static int DT_dev_stop(const struct pista_dev_inst *h ) {
    struct DT_context *me = (struct DT_context *)h->priv;

    if( me->channel_map != NULL ) {
		me->channel_map = delete [] me->channel_map;
	}
	me->n_channels = 0;
	me->channel_map = NULL;

	return DT_streamStop(me);
}


static int DT_cleanup(struct pista_dev_driver *drv )  {
   if( drv->priv != NULL ) {
        PISTA_FREE( drv->priv );
        drv->priv = NULL;
   }

   return PISTA_OK;
}

static int DT_destroy(struct pista_dev_inst *h ) {
    struct DT_context *me = (struct DT_context *)h->priv;

    /* release the subsystem and the board */
    CHECKERROR (olDaReleaseDASS(me->hdass));
    CHECKERROR (olDaTerminate(me->hdrvr));

	PISTA_FREE(me);
	h->priv = NULL;

	return rc;
}

static void *DT_config_get(const struct pista_dev_inst *h ) {
    struct DT_context *me = (struct DT_context *)h->priv;

    return &me->s;
}

static int DT_config_set(const struct pista_dev_inst *h, void *config ) {
    struct DT_context *me = (struct DT_context *)h->priv;

	me->s = *(DT__DTSettings *)config;
	DT_CDM_apply_settings( me ); // , 100, 1, 500, 0x07, 0 );

    return PISTA_OK;
}


static int DT_handle_dma( const struct pista_dev_inst *h, const char *cc, int len )  {
	/* get buffer off done list */

	UINT encoding=0,resolution=0;
	HBUF  hBuffer = NULL;
    PDWORD  pBuffer32 = NULL;

    CHECKERROR (olDaGetBuffer(board.hdass, &hBuffer));

    /* if there is a buffer */

    if( hBuffer ) {

             /* get sub system information for code/volts conversion */

       CLOSEONERROR (olDaGetRange(board.hdass,&max,&min));
       CLOSEONERROR (olDaGetEncoding(board.hdass,&encoding));
       CLOSEONERROR (olDaGetResolution(board.hdass,&resolution));

       /* get max samples in input buffer */

       CLOSEONERROR (olDmGetValidSamples( hBuffer, &samples ) );

       /* get pointer to the buffer */
       if (resolution > 16) {
            CLOSEONERROR (olDmGetBufferPtr( hBuffer,(LPVOID*)&pBuffer32));
            /* get last sample in buffer */
            value = pBuffer32[samples-2];
            value2 = pBuffer32[samples-1];
       } else {
            CLOSEONERROR (olDmGetBufferPtr( hBuffer,(LPVOID*)&pBuffer));
            /* get last sample in buffer */
            value = pBuffer[samples-2];
            value2 = pBuffer[samples-1];
       }
       /* put buffer back to ready list */

       CHECKERROR (olDaPutBuffer(board.hdass, hBuffer));
       /*  convert value to volts */

       if (encoding != OL_ENC_BINARY) {
       		/* convert to offset binary by inverting the sign bit */

            value ^= 1L << (resolution-1);
            value &= (1L << resolution) - 1;     /* zero upper bits */
            value2 ^= 1L << (resolution-1);
            value2 &= (1L << resolution) - 1;     /* zero upper bits */

       }

       volts = ((float)max-(float)min)/(1L<<resolution)*value + (float)min;
       volts2 = ((float)max-(float)min)/(1L<<resolution)*value2 + (float)min;

       /* display value */

       sprintf(str,"%.3f Volts",volts);
            // sprintf(str,"%i hex",value);
            //            SetDlgItemText (hDlg, IDD_VALUE, str);
            //                        sprintf(str,"%.3f Volts",volts2);
            //                                    SetDlgItemText (hDlg, IDD_VALUE2, str);
	}
            
}

static int DT_tick( const struct pista_dev_inst *inst )  {
    struct DT_context *me = (struct DT_context*)inst->priv;

	int rc = DT_streamData( me );
	if( rc == PISTA_OK && inst->event_func != NULL) {
		inst->event_func( inst, 99, me->u3f );
	}
	return rc;
	
}

struct pista_dev_driver dt_driver_info = {
        .name = "dt",
        .longname = "DataTranslation",
        .api_version = 1,
        .init = DT_init,
        .cleanup = DT_cleanup,

        /* .config_get = NULL, */
        .config_get = DT_config_get,
        .config_set = DT_config_set,

        .dev_start = DT_dev_start,
        .dev_stop  = DT_dev_stop,

        .allocate = DT_allocate,
        .destroy = DT_destroy,
        .handle = NULL,

        .tick = DT_tick,

        .priv = NULL
};

