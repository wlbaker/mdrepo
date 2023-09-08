
#include <stdio.h>
#include <pista.h>
#include <string.h>

#include "propaqm.h"


PISTA_API int64_t pista_get_current_time_with_ms (void)
{
    int64_t            ms; /* Milliseconds */
#ifdef _WIN32
    /* see http://stackoverflow.com/questions/1695288 */

    FILETIME ft_now;
    GetSystemTimeAsFileTime(&ft_now);
    ms = (LONGLONG)ft_now.dwLowDateTime + ((LONGLONG)(ft_now.dwHighDateTime) << 32LL);  /* since jan1 1601 */
    ms += 116444736000000000LL;  /* since jan 1 1970 */
    ms /= 10000;                 /* 100-ns intervals to millis */
#else
    struct timespec tspec;
    clock_gettime(CLOCK_REALTIME, &tspec);
    ms = 1000L*tspec.tv_sec + (int)(tspec.tv_nsec / 1000000 ); /* Convert nanoseconds to milliseconds */
#endif
    return ms;
}

struct pista_dev_driver propaqm_driver_info = {
        .name = "propaqm",
        .longname = "monitor/Propaq X-Series",
        .api_version = 1,

        .priv = NULL
};

int PROPAQM_init( struct pista_context *pista_ctx, struct pista_dev_driver *drv ) {

     *drv = propaqm_driver_info;
    drv->priv = NULL;

    return PISTA_OK;
}

int PROPAQM_allocate( struct pista_dev_driver *drv, struct pista_dev_inst *di )
{

    PROPAQM_context *propaq = (PROPAQM_context *)PISTA_MALLOC( sizeof(PROPAQM_context) );
    if( propaq == NULL ) {
        printf("PROPAQM_allocate: alloc error for private data\n" );
        return PISTA_ERR;
    }
    memset( propaq, 0, sizeof( PROPAQM_context) );

    propaq->enable_wss = true;
    propaq->enable_numerics = true;

    //
    // init JSON parsers
    //
    //propaq->zws_hand = yajl_alloc(&zws_callbacks, NULL, (void *)di );  
    propaq->ztr_hand = yajl_alloc(&ztr_callbacks, NULL, (void *)di );  

    //yajl_config(propaq->zws_hand, yajl_allow_multiple_values, 1);  
    yajl_config(propaq->ztr_hand, yajl_allow_multiple_values, 1);  


    // save our local info
    di->priv = propaq;
    di->driver = drv;
    di->next = NULL;
    di->model = "PropaqM";
    di->version = "0.0";

    di->status = PISTA_ST_NOT_CONNECTED;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->event_handler = NULL;
    di->event_priv = NULL;

    // PROPAQM_prepare_metainfo(di, propaq );

    // pista_dev_register_inst( drv, di );

    return PISTA_OK;
}

int main( int argc, char *argv[] ) {

    struct pista_context *ctx = NULL;
    struct pista_dev_inst di;
    struct pista_dev_driver drv;

    ftrend = stdout;
    fpatient = stdout;
    fanno = stdout;
    fsnap = stdout;
    ftsnap = stdout;
    fwaves = stdout;

    //memset( me, 0, sizeof( PROPAQM_context) );
    //memset( &di, 0, sizeof( struct pista_dev_inst ) );
    //di.priv = me;

    PROPAQM_init( ctx, &drv );
    int rc = PROPAQM_allocate( &drv, &di );
    if( rc != PISTA_OK ) {
        printf("Error allocating PropaqM data structure.\n");
        return 2;
    }
    PROPAQM_context *me = (PROPAQM_context *)di.priv;

    me->ztr_hand = yajl_alloc(&ztr_callbacks, NULL, (void *)&di );  
    yajl_config(me->ztr_hand, yajl_allow_multiple_values, 1);  

    // char *ftrend_name = "z_trend.csv";
    // char *fpatient_name = "z_patient.csv";
  
    bool close_files = false;
    //
    // prepare libwebsocket
    int verbose = 0;

    for( int arg_no = 1; arg_no < argc; arg_no++ ) {
        if( strcmp( argv[arg_no], "-v" ) == 0 ) {
                verbose++;
                continue;
        }
        if( strcmp( argv[arg_no], "+w" ) == 0 ) {
                export_waves = true;
                continue;
        }
        if( strcmp( argv[arg_no], "+e" ) == 0 ) {
                export_events = true;
                continue;
        }
        if( strcmp( argv[arg_no], "-w" ) == 0 ) {
                export_waves = false;
                continue;
        }
        if( strcmp( argv[arg_no], "-e" ) == 0 ) {
                export_events = false;
                continue;
        }
        if( strcmp( argv[arg_no], "--autoname" ) == 0 ) {
            ftrend = fopen("z_trend.csv", "a");
            fpatient = fopen("z_patient.csv", "a");
            fanno = fopen("z_anno.csv", "a");
            fsnap = fopen("z_snap.csv", "a");
            ftsnap = fopen("z_tsnap.csv", "a");
            fwaves = fopen("z_wave.csv", "a");
            close_files = true;
            continue;
        }
	PROPAQM_ztr_set_verbose(verbose);

        char lineptr[61];
        FILE *fp =fopen(argv[arg_no],"r");
        size_t n = 0;
        lineptr[60] = '\0';

        // while( getline(&lineptr, &n, fp) > 0 ) {
        while( (n = fread(lineptr, 60, 1, fp) > 0) ) {
            char *ptr = lineptr;
            if( verbose > 2 ) {
                fprintf(stdout,"LINE[%I64d=%I64d]: %s", n, strlen(lineptr), lineptr );
            }

            int stat = yajl_parse(me->ztr_hand, (unsigned char *)ptr, strlen(ptr) );
            if (stat != yajl_status_ok) {
                printf("ERR PARSING TEST DATA\n");

                unsigned char *message= yajl_get_error(me->ztr_hand, 1, (unsigned char *)ptr, strlen(ptr) );
                printf("%s\n", message);

                stat = yajl_complete_parse(me->ztr_hand);
                yajl_free_error(me->ztr_hand, message);
                yajl_free( me->ztr_hand );  

                ztr_reset();

                me->ztr_hand = yajl_alloc(&ztr_callbacks, NULL, (void *)&di );  
                yajl_config(me->ztr_hand, yajl_allow_multiple_values, 1);  
            }

        }
        fclose(fp);
    }
    fprintf(stdout,"Dumping streams:\n");
    // pista_dump( &di, PISTA_DUMP_STREAMS );
    fprintf(stdout,"Done\n");

    if( close_files ) {
        fclose( ftrend );
        fclose( fpatient );
        fclose( fanno );
        fclose( fsnap );
        fclose( ftsnap );
        fclose( fwaves );
    }
    return 0;
}

