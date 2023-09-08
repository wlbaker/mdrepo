#include <pista.h>
#include "propaqm.h"

#include <signal.h>
#include <getopt.h>

static volatile int force_exit;

void sighandler(int sig)
{
	force_exit = 1;
}

int my_priv = 999;
int test_event_func( void *priv, struct pista_data_packet *pkt ) {
    int *pint = (int *)priv;
    printf("%ld %d.%c!", pkt->tm, *pint, pkt->stream_id);
    if( pkt->stream_id == 'W' ) {
        Propaqm__Sensors *s = (Propaqm__Sensors *)pkt->payload;
        printf("sensors: ");
        for( int i = 0; i < s->n_ecg; i++ ) { printf("%d.", s->ecg[i] ); }
        printf("\n");
    } else if( pkt->stream_id == 'M' ) {
        // Propaqm__Vitals *v = (Propaqm__Vitals *)pkt->payload;
        int tot = pista_get_field_count( pkt );
        for( int i =0 ; i < tot; i++ ) {
            const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, i );
            const char *loc  = pista_get_field_loc( fd );
            // const char *code = pista_get_field_code( fd );
            // const char *desc = pista_get_field_desc( fd );
            int offset = pista_get_field_offset( fd );
            int count = pista_get_field_spp( fd );
            int subtyp = pista_get_field_subtyp( fd );

            void *addr = pkt->payload + offset;
            printf("%s: ", loc );

            switch( subtyp ) {
            case LONG_TYP:
                {
                long long lval = *((long long *)addr);
                printf("%lld", lval );
                }
                break;
            case INT_TYP:
                {
                int ival = *((int *)addr);
                printf("%d", ival );
                }
                break;
            case FLOAT_TYP:
                {
                int fval = *((float *)addr);
                printf("%f", fval );
                }
                break;
            case BYTE_ARR_TYP:
            case STRING_TYP:
                {
                char *src = *((char **)addr);
                while( count-- > 0 ) {
                    char val = *(src++);
                    printf( "%c, ", val );
                }
                }
                break;
            case INT_ARR_TYP:
            case FLOAT_ARR_TYP:
            default:
                printf("unknown typ: %d\n", subtyp );
            }
            printf("\n");
        }
    } else {
        // unknown
    }
    printf("\n");

    return PISTA_OK;
}

int main(int argc, char **argv)
{
    struct pista_context *ctx = NULL;
    struct pista_dev_inst di;

	int n = 0, ret = 0;
    const char *wss_arg = NULL;
    const char *numerics_arg = NULL;

    const char *user = NULL;

	if (argc < 2)
		goto usage;

	while (n >= 0) {
		n = getopt_long(argc, argv, "d:u:w:n:", NULL, NULL);
		if (n < 0)
			continue;
		switch (n) {
		case 'd':
			lws_set_log_level(atoi(optarg), NULL);
			break;
       case 'u':
            user = optarg;
            break;
       case 'w':
            wss_arg = optarg;
            break;
       case 'n':
            numerics_arg = optarg;
            break;
		}
	}

	if (optind >= argc)
		goto usage;

    char *host = argv[optind];


    setbuf( stdout, NULL ); // use this if you want unbuffered stdout for JVM debugging
	signal(SIGINT, sighandler);

	/*
	 * sit there servicing the websocket context to handle incoming
	 * packets, and drawing random circles on the mirror protocol websocket
	 *
	 * nothing happens until the client websocket connection is
	 * asynchronously established... calling lws_client_connect() only
	 * instantiates the connection logically, lws_service() progresses it
	 * asynchronously.
	 */

	// ratelimit_connects(&rl_zoll_ws, 2u); // allow a few seconds for handshaking before requesting url
	// ratelimit_connects(&rl_zoll_rest, 2u); // allow a few seconds for handshaking before requesting url

	// fprintf(stderr, "PISTA version: %s == %s\n", PACKAGE_VERSION, pista_get_version() );
    
    PROPAQM_init( ctx );
    int rc = PROPAQM_allocate(  &di );

    if( rc != PISTA_OK ) {
	    lwsl_err("Could not allocate PROPAQM\n");
    } else {


        if( user != NULL ) {
            PROPAQM_config_set( &di, "user", user); // "zolldata:MDARK2018" );
        }
        PROPAQM_config_set( &di, "host", host); // "AP14E001105.X-Series.device.ZOLL.local" );

        if( wss_arg != NULL ) {
            PROPAQM_config_set( &di, "wss", wss_arg );  // true or false
        }
        if( numerics_arg != NULL ) {
            PROPAQM_config_set( &di, "numerics", numerics_arg );  // true or false
        }

        PROPAQM_set_event_handler( &di, test_event_func, (void *)&my_priv ); // callback

        PROPAQM_dump( &di, 7 );
        PROPAQM_connect( &di );
    
	    while (!force_exit) {
            PROPAQM_tick( &di );
            sleep(1);
	    }
    
        PROPAQM_disconnect( &di );
        PROPAQM_destroy( &di );
    }

	lwsl_err("Exiting\n");

	return ret;

usage:
	fprintf(stderr, "Usage: test_propaq "
				"<server address> "
				"[-u <user>] "
				"[-d <log bitfield>]\n");
	return 1;
}



