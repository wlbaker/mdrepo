
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
//#include "gettimeofday.h"
#define gettimeofday(a,b) mingw_gettimeofday(a,b)
#else
#ifdef HAVE_UNISTD_H
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#else
#define random rand
#include "gettimeofday.h"
#endif
#endif

#include <openssl/x509_vfy.h>
#include "propaqm.h"

// #define DEBUG

const char *zoll_heartbeat = "{\"command\": \"heartbeat\", \"params\": {\"state\": true}}";

// Forward declarations
yajl_handle propaq_yajl_recover( struct pista_dev_inst *di, //
        yajl_handle hand, yajl_callbacks *callbacks, char *json, int jsonLen );

static int propaqm_send_hb( struct lws *wsi );

// functions
static bool is_true( const char *val ) {
    bool ok = false;
    if( val == NULL ) {
        // leave as false
    } else if( strcmp(val,"true") ==0 ) {
        ok = true;
    } else if( strcmp(val,"1") ==0 ) {
        ok = true;
    } else if( strcmp(val,"0") ==0 ) {
        ok = false;
    } else if( strcmp(val,"false") ==0 ) {
        ok = false;
    } else {
        fprintf(stderr,"Invalid true/false value: %s\n", val );
    }

    return ok;
}

/**
 * Device instances generate events while parsing device specific data.
 */

// duplicate function of...pista_set_event_handler...so I don't have to call -lpista
// PISTA_API int pista_set_event_handler( struct pista_dev_inst *di, eventfunc_t handler, void *cb_data )
int PROPAQM_set_event_handler( struct pista_dev_inst *di, eventfunc_t handler, void *cb_data )
{
    di->event_handler = handler;
    di->event_priv = cb_data;

    return PISTA_OK;
}

static int PROPAQM_handle( const struct pista_dev_inst *h, const char *buf, int len )  {
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    int stat = yajl_parse(me->ztr_hand, (const unsigned char *)buf, len );
    if (stat != yajl_status_ok) {
        unsigned char *message= yajl_get_error(me->ztr_hand, 1, (const unsigned char *)buf, len );
        lwsl_notice("propaq: ERR PARSING: %.*s\n", len, message );

        stat = yajl_complete_parse(me->ztr_hand);
        yajl_free_error(me->ztr_hand, message);
        yajl_free( me->ztr_hand );  

        ztr_reset();

        me->ztr_hand = yajl_alloc(&ztr_callbacks, NULL, (void *)h );  
        yajl_config(me->ztr_hand, yajl_allow_multiple_values, 1);  
    }

    return PISTA_OK;
}

int PROPAQM_destroy(struct pista_dev_inst *di) {
    PROPAQM_context *me=(PROPAQM_context *)di->priv;

    lws_context_destroy(me->context);

    if( me->ztr_hand ) yajl_free(me->ztr_hand);  
    // if( me->zws_hand ) yajl_free(me->zws_hand);  

    return PISTA_OK;
}


/*
 * This demo shows how to connect multiple websockets simultaneously to a
 * websocket server (there is no restriction on their having to be the same
 * server just it simplifies the demo).
 *
 *  zoll-increment-protocol:  we connect to the server and print the number
 *                we are given
 *
 */

enum demo_protocols {

    PROTOCOL_ZOLL_WEBSOCKET,
    PROTOCOL_LWS_MIRROR,

    /* always last */
    DEMO_PROTOCOL_COUNT
};

/*
 * send generic connection message
 * move to internal pista library
 */

static int 
propaqm_send_hb( struct lws *wsi ) {

    /*
     * lws_write requires LWS_PRE bytes BEFORE the pointer passed
     */

    unsigned char bbuf[ 128 + LWS_PRE];
    memset( bbuf, '\0', sizeof( bbuf ) );
    unsigned char *buf = &bbuf[LWS_PRE];
    int l = sprintf((char *)buf, "%s", zoll_heartbeat );

    lwsl_notice("%p WRITE HEARTBEAT: %d %s\n", wsi, l, buf);
    int n = lws_write(wsi, buf, l, LWS_WRITE_TEXT);

    if (n < 0) {
        return -1;
    } else if (n == 0 ) {
        lwsl_err("HB Invalid state for binning: state\n");
    } else if (n < l) {
        lwsl_err("HB Partial write %d < %d\n", n, l);
        return -1;
    }
    return 0;
}


/*
 * zoll_websocket protocol
 *
 * since this also happens to be protocols[0], some callbacks that are not
 * bound to a specific protocol also turn up here.
 */

static int
callback_zoll_websocket(struct lws *wsi, enum lws_callback_reasons reason,
            void *user, void *in, size_t len)
{
    struct pista_dev_inst *h = (struct pista_dev_inst*)lws_context_user( lws_get_context(wsi) );
    PROPAQM_context *propaq = (PROPAQM_context *)h->priv;

#ifdef DEBUG
    printf("%d.", reason); fflush(stdout);
#endif

    switch (reason) {

       case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
            
            if( wsi == propaq->wsi_zoll_rest ) {
                char **p = (char **)in;

                *p += sprintf(*p,
                            "Accept: application/json\r\n"
                            "Content-Type: application/json\r\n"
                            "Client-Id: 12345\r\n"
                                    "Authorization: Basic %s\x0d\x0a", propaq->encoded_auth );
            }
            break;

    case LWS_CALLBACK_CLIENT_ESTABLISHED:
        pista_util_send_connection(h, PISTA_ST_CONNECTED );
        propaq->tick = 0;
        break;

    case LWS_CALLBACK_CLOSED:
        if (wsi == propaq->wsi_zoll_ws) {
            propaq->wsi_zoll_ws = NULL;
        }
        if (wsi == propaq->wsi_zoll_rest) {
            propaq->wsi_zoll_rest = NULL;
        }
        break;

    case LWS_CALLBACK_CLIENT_RECEIVE:  /* this one called by the web service */
        ((char *)in)[len] = '\0';
        {
#ifdef DEBUG
            lwsl_notice("dat! %.*s", len, (char *)in);  // ifdef debug
#endif
            PROPAQM_handle( h, (const char *)in, len ); // parse!
        }
    break;

    /* because we are protocols[0] ... */

    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
        pista_util_send_connection( h, PISTA_ST_ERROR );
        if (wsi == propaq->wsi_zoll_ws) {
            lwsl_err("propaqm: LWS_CALLBACK_CLIENT_CONNECTION_ERROR on WSS interface\n");
            propaq->wsi_zoll_ws = NULL;
        }
        if (wsi == propaq->wsi_zoll_rest) {
            lwsl_err("propaqm: LWS_CALLBACK_CLIENT_CONNECTION_ERROR on REST interface\n");
            propaq->wsi_zoll_rest = NULL;
        }
        break;

    case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
        //if ((strcmp(in, "deflate-stream") == 0) && deny_deflate) {
            //lwsl_notice("denied deflate-stream extension\n");
            //return 1;
        //}
        if ((strcmp(in, "x-webkit-deflate-frame") == 0))
            return 1;
        if ((strcmp(in, "deflate-frame") == 0))
            return 1;
        break;

        /*
         * prepare a buffer and start http parsing
         */

    case LWS_CALLBACK_RECEIVE_CLIENT_HTTP:
        {
            int sz =  1024;

            char buffer[sz + LWS_PRE];
            char *px = buffer + LWS_PRE;
            int lenx = sizeof(buffer) - LWS_PRE;

            /*
             * Often you need to flow control this by something
             * else being writable.  In that case call the api
             * to get a callback when writable here, and do the
             * pending client read in the writeable callback of
             * the output.
             */
            int rc;
            if ((rc = lws_http_client_read(wsi, &px, &lenx)) < 0) {
                // no worth reporting...maybe no more data
                // lwsl_info("propaqm: got an error in lws_http_client_read! rc=%d len=%d\n", rc, lenx);
                return 0;  // June 2018: was -1
            }

        }
        break;

    case LWS_CALLBACK_COMPLETED_CLIENT_HTTP:
        propaq->wsi_zoll_rest = NULL;
        // force_exit = 1;
        break;

    /*
     * handle chunks of parsed data
     */
    case LWS_CALLBACK_RECEIVE_CLIENT_HTTP_READ:
        {
            yajl_status stat;  

            // printf("> %.*s\n", (int)len, (char *)in );
            stat = yajl_parse(propaq->ztr_hand, (unsigned char *)in, len);  
            if (stat != yajl_status_ok) {
                printf("ERR PARSING HTTP-JSON ZTR PARSER\n");
                propaq->ztr_hand = propaq_yajl_recover( h, propaq->ztr_hand, &ztr_callbacks, in, len );
                ztr_reset();
            }
        }
        break;

        /*
         * We expect to receive unrequested CLIENT_WRITEABLE messages which we should ignore, as per doc.
         * See: libwesockets/README.coding.md section Do not rely on only your own WRITEABLE requests...
        */

    case LWS_CALLBACK_CLIENT_WRITEABLE:
        lwsl_notice("HB\n");
        if( propaq->send_zoll_heartbeat ) {
            return propaqm_send_hb( wsi );
        }

        break;

    case LWS_CALLBACK_OPENSSL_PERFORM_SERVER_CERT_VERIFICATION:
        X509_STORE_CTX_set_error((X509_STORE_CTX*)user, X509_V_OK);
        break;


    default:
        break;

    }

    return 0;
}

yajl_handle propaq_yajl_recover( struct pista_dev_inst *di, //
        yajl_handle hand, yajl_callbacks *callbacks, char *json, int jsonLen ) {

    unsigned char *message= yajl_get_error(hand, 1, (unsigned char *)json, jsonLen );
    printf("%s\n", message);

    yajl_free_error(hand, message);
    yajl_free( hand );  

    hand = yajl_alloc(callbacks, NULL, (void *)di );  
    yajl_config(hand, yajl_allow_multiple_values, 1);  

    return hand;
}

/* list of supported protocols and callbacks */

static struct lws_protocols protocols[] = {
    {
        "zoll-wss", // "chat",
        callback_zoll_websocket,
        0,
        20,
    },
    { NULL, NULL, 0, 0 } /* end */
};

static const struct lws_extension exts[] = {
    {
        "permessage-deflate",
        lws_extension_callback_pm_deflate,
        "permessage-deflate; client_no_context_takeover"  // "permessage-deflate; client_max_window_bits"
    },
    {
        "deflate-frame",
        lws_extension_callback_pm_deflate,
        "deflate_frame"
    },
    { NULL, NULL, NULL /* terminator */ }
};



static int ratelimit_connects(unsigned int *last, unsigned int secs)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (tv.tv_sec - (*last) < secs)
        return 0;

    *last = tv.tv_sec;

    return 1;
}

// extern char *strdup( const char *);

static int prepare_uri( 
    struct lws_context *context,
    struct lws_client_connect_info *ci, 
    const char *pfx, const char *host, const char *uri_path 
    ) {

    const char *prot;
    const char *p;
    char buf[256];
    int ietf_version = -1;

    strcpy( buf, pfx );
    strcat( buf, host );
    strcat( buf, uri_path );
    ci->path = uri_path;
    ci->port = 443;

    char *uri = strdup(buf);  // need data from the heap, not the stack! uri parser doesnt allocate!

    int retval = lws_parse_uri(uri, &prot, &ci->address, &ci->port, &p);

    ci->context = context;
    // ci->ssl_connection = 2; // self signed certificates
	ci->ssl_connection = LCCSCF_USE_SSL;
		ci->ssl_connection |= LCCSCF_ALLOW_SELFSIGNED;
		ci->ssl_connection |= LCCSCF_ALLOW_EXPIRED;
		ci->ssl_connection |= LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
    ci->host = ci->address;
    ci->origin = NULL;
    ci->ietf_version_or_minus_one = ietf_version;
    ci->client_exts = exts;

    lwsl_notice("prepare uri=%s port=%d\n", uri, ci->port  );

    return retval;
}

static int PROPAQM_prepare_metainfo( struct pista_dev_inst *di, PROPAQM_context *me )
{
     propaqm__vitals__init( &me->v );
     propaqm__sensors__init( &me->w );

    /*
     * vitals fields
     */


    /*
     * waveform fields
     */

    me->w.n_ecg = 30;
    me->w.n_co2 = 15;

    //NO_DESC pista_set_desc( &me->wi.desc[0], "ecg", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Propaqm__Sensors, ecg), me->w.n_ecg );
    //NO_DESC pista_set_desc( &me->wi.desc[1], "co2", NULL, NULL, NULL, INT_ARR_TYP, offsetof( Propaqm__Sensors, co2), me->w.n_co2 );

    int tot = me->w.n_ecg*sizeof(int32_t);
    tot += me->w.n_co2*sizeof(int32_t);

    me->w.ecg = (int*) PISTA_MALLOC( tot );
    memset( me->w.ecg, 0, tot );
    me->w.co2 = (int*) (me->w.ecg  + me->w.n_ecg );
    if( me->w.ecg == NULL ) {
            printf("PROPAQM_prepare_metainfo: alloc error for waveform buffer\n" );
        return PISTA_ERR;
    }

    // 1 pkt/sec means freq == &samples
    //NO_DESC me->wi.desc[0].freq = 250;  
    //NO_DESC me->wi.desc[1].freq = 125;

    //NO_DESC di->wf_stream = pista_stream_from_pkt( &me->wi );
    //NO_DESC di->m_stream = pista_stream_from_pkt( &me->vi );

    return PISTA_OK;
}

struct pista_dev_driver *PROPAQM_init( struct pista_context *pista_ctx ) {

    PROPAQM_initDumper( NULL );

    return &propaqm_driver_info;
}

int PROPAQM_allocate( struct pista_dev_inst *di )
{
    PROPAQM_context *me = (PROPAQM_context *)PISTA_MALLOC( sizeof(PROPAQM_context) );
    if( me == NULL ) {
        fprintf(stderr, "PROPAQM_allocate: alloc error for private data\n" );
        return PISTA_ERR;
    }
    printf("PROPAQM_allocate: %p\n", me );

    memset( me , 0, sizeof( PROPAQM_context) );

    me->enable_wss = true;
    me->enable_numerics = true;


    //
    // prepare libwebsocket
    //
    struct lws_context_creation_info info;
    memset( &info, 0, sizeof info);

    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;
    info.gid = -1;
    info.uid = -1;
    info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
    info.user = di; // user data...pointer to pista_dev_inst

    printf("PROPAQM_allocate: info size=%ld\n", sizeof(info) );

    struct lws_context *lcontext = lws_create_context(&info);
    me->context = lcontext;

    if ( lcontext == NULL) {
        fprintf(stderr, "Creating libwebsocket context failed\n");
        PISTA_FREE( me );
        return PISTA_ERR;
    }

    //
    // init JSON parser
    //
    // me->zws_hand = yajl_alloc(&zws_callbacks, NULL, (void *)di );  
    me->ztr_hand = yajl_alloc(&ztr_callbacks, NULL, (void *)di );  

    // yajl_config(me->zws_hand, yajl_allow_multiple_values, 1);  
    yajl_config(me->ztr_hand, yajl_allow_multiple_values, 1);  


    // save our local info
    di->priv = me;
    di->driver = &propaqm_driver_info;
    di->next = NULL;
    di->model = "PropaqM";
    di->version = "0.0";

    di->status = PISTA_ST_NOT_CONNECTED;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->event_handler = NULL;
    di->event_priv = NULL;

    PROPAQM_prepare_metainfo(di, me );

    me->vi.stream_id = PISTA_DF_MEASUREMENT;
    me->vi.payload_sz = sizeof( me->v );
    me->vi.payload = &me->v;

    me->wi.stream_id = PISTA_DF_WAVEFORM;
    me->wi.payload_sz = sizeof( me->w );
    me->wi.payload = &me->w;

    pista_dev_register_stream( di, &me->wi );
    pista_dev_register_stream( di, &me->vi );

    return PISTA_OK;
}

#ifdef _WIN32
DWORD WINAPI propaqm_wf_loop( LPVOID cb_data ) 
#else
static void * propaqm_wf_loop( void *cb_data ) 
#endif
{
    const struct pista_dev_inst *h = cb_data;
    /* During the BACKGROUND operation, tick*/
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    bool first = true;
    me->wsi_zoll_rest = NULL;
    do {
        /*
        lwsl_notice("thread loop\n");
        if (!me->wsi_zoll_ws && ratelimit_connects(&me->rl_zoll_ws, 2u)) {
            // me->comet_ci.protocol = protocols[PROTOCOL_ZOLL_WEBSOCKET].name;
            me->comet_ci.protocol = NULL;
            me->wsi_zoll_ws = lws_client_connect_via_info(&me->comet_ci);
            //propaqm_send_hb( me->wsi_zoll_ws );
        }
        if (first && me->wsi_zoll_ws && ratelimit_connects(&me->rl_heartbeat, 3u)) {
#ifdef DEBUG
          lwsl_notice("PROPAQM: set callback on writable\n");
#endif
            me->send_zoll_heartbeat = true;
            lws_callback_on_writable(me->wsi_zoll_ws);
            first = false;
        }
        */
    
        // for numerics, uncomment
        if (!me->wsi_zoll_rest && ratelimit_connects(&me->rl_zoll_rest, 2u)) {
            me->wsi_zoll_rest = lws_client_connect_via_info(&me->rest_ci);
        }
    
        lws_service(me->context, 500);

    } while( me->run_thread );

    return 0;
}


static void propaqm_startthread( struct pista_dev_inst *h ) {
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    if( h->status == PISTA_ST_NOT_CONNECTED ) {
        pista_util_send_connection( h, PISTA_ST_STANDBY );
        me->run_thread = true;

#ifdef _WIN32
    DWORD tid = 0;
    me->htid = CreateThread(
        NULL,          // default security attributes
        0,             // default stack
        propaqm_wf_loop,  // thread func
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
        pthread_create( &me->propaqm_thread, NULL, propaqm_wf_loop, h );
#endif
    }
}
 
int PROPAQM_connect( struct pista_dev_inst *di )
{
    PROPAQM_context *me = (PROPAQM_context *)di->priv;

    if( me->user == NULL ) {
        me->user="zolldata:MDARK2018";
    }
    if( me->host == NULL ) {
        me->host="192.168.50.100";
        fprintf(stderr, "ERROR: host not configured, using %s", me->host);
    }
    lwsl_notice("PROPAQM: user=%s", me->user );
    lwsl_notice("PROPAQM: host=%s", me->host );

    {  // create the double-encoded credentials used by all services
        char buff[256];
        int rc = lws_b64_encode_string(me->user, strlen(me->user), me->encoded_auth, sizeof( me->encoded_auth ) );
        strcpy( buff, "Basic " );
        strcat( buff, me->encoded_auth );
        rc = lws_b64_encode_string(buff, strlen(buff), me->double_encoded_auth, sizeof( me->double_encoded_auth ) );
    }

    memset(&me->rest_ci, 0, sizeof(me->rest_ci));
    me->rest_ci.method = "GET";

    struct hostent *server = gethostbyname( me->host );
    if( server ) {
            printf("addr type: %d\n", server->h_addrtype );
            printf("addr len : %d\n", server->h_length );
            unsigned char *addr = server->h_addr;
            sprintf( me->host_ip, "%u.%u.%u.%u", addr[0], addr[1], addr[2], addr[3] );
     }
     printf("address=%s\n", me->host_ip );

    prepare_uri( me->context, &me->rest_ci, "https://", me->host_ip, "/Numerics/current?now" );

    // the rest of the connection is handled in the thread
    if( me->enable_wss ) {

        memset(&me->comet_ci, 0, sizeof(me->comet_ci));

        strcpy( me->comet_uripath, "/Comet");
        strcat( me->comet_uripath, "?auth=" );;
        strcat( me->comet_uripath, me->double_encoded_auth );
        lwsl_notice("COMET URI=%s\n", me->comet_uripath );

        prepare_uri( me->context, &me->comet_ci, "wss://", me->host, me->comet_uripath );
#ifdef DEBUG
        lwsl_notice("PROPAQM: starting wss thread\n");
#endif
    }

    propaqm_startthread( di );
   
    return PISTA_OK;
}


int PROPAQM_tick( const struct pista_dev_inst *di ) {
    PROPAQM_context *me = (PROPAQM_context *)di->priv;

    me->tick++;
    if( me->tick == 20 ) {
        // timeout
        pista_util_send_connection(di, PISTA_ST_STANDBY);
    }
    if( me->tick > 30 ) {
        me->tick = 30;  // max value
    }
    // nothing to do hear...everything of interest handled on other thread

    return PISTA_OK;
}

int PROPAQM_disconnect( struct pista_dev_inst *di ) {
    PROPAQM_context *me = (PROPAQM_context *)di->priv;

    pista_util_send_connection(di, PISTA_ST_NOT_CONNECTED);
    me->run_thread = false;
    return PISTA_OK;
}



int PROPAQM_dump(const struct pista_dev_inst *h, pista_dump_flags flags) {
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    if( flags & PISTA_DUMP_CONFIG ) {
        printf("User: %s\n", me->user );
        printf("Host: %s\n", me->host );
        printf("WSS: %d\n", me->enable_wss );
        printf("Numeric: %d\n", me->enable_numerics );
    }

    return PISTA_OK;
}


int PROPAQM_config_set(const struct pista_dev_inst *h, const char *key, const void *settings ) {
    PROPAQM_context *me = (PROPAQM_context *)h->priv;

    if( strcmp("connection",key) == 0 ) {
        if( settings == NULL ) {
            me->host = NULL;
        } else {
            me->host = strdup(settings);
        }
        lwsl_notice("propaqm: set host %s\n", me->host );
    } else if( strcmp("user", key) == 0 ) {
        if( settings == NULL ) {
            me->user = NULL;
        } else {
            me->user = strdup(settings);
        }
        lwsl_notice("propaqm: set user %s\n", me->user );
    } else if( strcmp("host", key) == 0 ) {
        if( settings == NULL ) {
            me->host = NULL;
        } else {
            me->host = strdup(settings);
        }
        lwsl_notice("propaqm: set host %s\n", me->host );
    } else if( strcmp("wss", key) == 0 ) {
        if( settings == NULL ) {
            me->enable_wss = true;
        } else {
            me->enable_wss = is_true( settings );
        }
        lwsl_notice("propaqm: set wss=%d\n", me->enable_wss );
    } else if( strcmp("numerics", key) == 0 ) {
        if( settings == NULL ) {
            me->enable_numerics = true;
        } else {
            me->enable_numerics = is_true( settings );
        }
        lwsl_notice("propaqm: set numerics=%d\n", me->enable_numerics );
    } else {
        lwsl_err("propaqm: config option not recognized %s=%s\n", key, (char *)settings );
    }

    return PISTA_OK;
}

static int PROPAQM_cleanup( )  {
    struct pista_dev_driver *drv = &propaqm_driver_info;

    if( drv->priv != NULL ) {
        PISTA_FREE( drv->priv );
        drv->priv = NULL;
    }
    return PISTA_OK;
}

// R_PRIV 
struct pista_dev_driver propaqm_driver_info = {
        .name = "propaqm",
        .longname = "monitor/Propaq X-Series",
        .api_version = 1,
        .init = PROPAQM_init,
        .cleanup = PROPAQM_cleanup,

        // .config_get = NULL,
        .config_set = PROPAQM_config_set,

        .allocate = PROPAQM_allocate,
        .destroy = PROPAQM_destroy,
        .connect = PROPAQM_connect,
        .disconnect = PROPAQM_disconnect,

        .dump = PROPAQM_dump,

        .handle = PROPAQM_handle,
        .tick = PROPAQM_tick,

        .priv = NULL
};

