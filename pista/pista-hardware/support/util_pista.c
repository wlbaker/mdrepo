
/**
 * Callback routines for pista context
 */

#include <stdlib.h>  // malloc
#include <string.h>  // strcmp
#include <stdio.h>   // debug

#include <stdint.h> 
#include <inttypes.h>   //for our uint64_t and PRIu64

#include <pista.h>
#include <pista-internal.h>
#include <ctype.h>


#ifdef WIN32
#include <windows.h>
#else
#include <time.h>     /* clock_gettime */
#endif

#define LOG_PREFIX "pista_util"

static int64_t _pista_time_delta = 0;

PISTA_API void pista_set_current_time_delta( int64_t delta )
{
    _pista_time_delta = delta;
}

PISTA_API int64_t pista_get_current_time_with_ms (void)
{
    int64_t            ms; /* Milliseconds */
#ifdef _WIN32
    /* unix time: see http://stackoverflow.com/questions/1695288 */

    FILETIME ft_now;
    GetSystemTimeAsFileTime(&ft_now);
    ms = (LONGLONG)ft_now.dwLowDateTime + ((LONGLONG)(ft_now.dwHighDateTime) << 32LL);  /* since jan1 1601 */
    ms += 116444736000000000LL;  /* since jan 1 1970 */
    ms /= 10000;                 /* 100-ns intervals to millis */
#else
    struct timespec tspec;
    clock_gettime(CLOCK_REALTIME, &tspec);
	// pista_warn("tspec[%u,%u,%u: %u]= %ld. %lu", sizeof( time_t), sizeof(long), sizeof(long long), sizeof(ms), tspec.tv_sec, tspec.tv_nsec );
	ms = tspec.tv_sec;
	// pista_warn("ms0= %" PRIu64, ms);
	ms = ms * 1000;
    ms = ms + (int)(tspec.tv_nsec / 1000000 ); /* Convert nanoseconds to milliseconds */
	// pista_warn("ms= %" PRIu64 " + " %" PRIu64, ms, _pista_time_delta );
#endif
    return ms + _pista_time_delta;
}

PISTA_API void pista_util_send_connection( struct pista_dev_inst *h, int code ) {
    if( h->status != code ) {
        if( h->event_handler != NULL ) {
            struct pista_data_packet cni;
            long tm = pista_get_current_time_with_ms();
            pista_init_data_packet( &cni, tm, "propaqm", PISTA_DF_CONNECTION, 0, NULL );

			struct pista_dev_inst *hh = (struct pista_dev_inst *)h;
            hh->status = code; // PISTA_ST_CONNECTED;  // PISTA_ST_NOT_CONNECTED;
            h->event_handler( h->event_priv, &cni );
        }
    }
}


/*
 * PISTA private functions
 */
PISTA_API int pista_init_data_packet( struct pista_data_packet *pkt, long tm, char *driver_name, int stream_id, int payload_sz, void *payload )
{
    pkt->tm         = tm;
    strcpy( pkt->source_name, driver_name );
    pkt->stream_id  = stream_id;
    pkt->payload_sz = payload_sz;
    pkt->payload    = payload;

    return PISTA_OK;
}

