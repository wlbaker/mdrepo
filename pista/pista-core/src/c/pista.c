
#include <stdlib.h>  // malloc
#include <string.h>  // strcmp
#include <stdio.h>   // debug

#include <pista.h>
#include <pista-internal.h>
#include <ctype.h>
#include <dlfcn.h>

#define LOG_PREFIX "pista-core"

// needed for Java bindings...Java bindings are not conditional
// #if HAVE_LIBSERIALPORT
int pista_install_libserialport() {
    // THIS FUNCTION NOT READY
    return PISTA_ERR;
}
// #endif

#include <unistd.h>  // no QT here

#ifdef WIN32
#include <windows.h>
#else
#include <time.h>     /* clock_gettime */
#endif


#ifndef __BUILD_DATE
#define __BUILD_DATE "experimental"
#endif

PISTA_API int pista_install_driver(struct pista_context *ctx, struct pista_dev_driver *pd ) {
    struct pista_device_private *priv = PISTA_MALLOC( sizeof( struct pista_device_private));
    priv->next = NULL;
    priv->first = NULL;

    pd->priv = priv;

    if( ctx->driver_head == NULL ) {
        ctx->driver_head = pd;
    } else {
        struct pista_device_private *curr = ctx->driver_head->priv;
        while( curr->next != NULL) {
            curr = (struct pista_device_private *)curr->next->priv;
        }
        curr->next = pd;
    }

    return PISTA_OK;
}

PISTA_API void pista_install_service(struct pista_context *ctx, struct pista_discovery_service *service ) {
    service->init(ctx);

    struct pista_service_priv *priv = service->priv;
    priv->next = NULL;

    if( ctx->service_head == NULL ) {
        ctx->service_head = service;
    } else {
        struct pista_service_priv *curr = ctx->service_head->priv;
        while( curr->next != NULL) {
            curr = (struct pista_service_priv *)curr->next->priv;
        }
        curr->next = service;
    }
}

/**
 * The init function allocates a context (handle) for interacting with the PISTA library.
 * This is generally called only once
 */

PISTA_API int pista_init(struct pista_context **ctx)
{

    // printf ("pista_init build=%s\n", __BUILD_DATE );
    // setbuf( stdout, NULL ); // use this if you want unbuffered stdout for JVM debugging

    *ctx = PISTA_MALLOC( sizeof(struct pista_context) );
    (*ctx)->driver_head = NULL;
    (*ctx)->service_head = NULL;

    /*
    _pista_init_driver( *ctx, &simu_driver_info );
    _pista_init_driver( *ctx, &imp731_driver_info );
    _pista_init_driver( *ctx, &medsys3_driver_info );
    _pista_init_driver( *ctx, &ht70_driver_info );
    _pista_init_driver( *ctx, &mccul_driver_info );
    _pista_init_driver( *ctx, &propaqm_driver_info );
    _pista_init_driver( *ctx, &bmp180_driver_info );

#ifdef HAVE_AVAHICLIENT
    _pista_init_service( *ctx, &ppdisc_service_info );
#endif

    */

    return PISTA_OK;
}

PISTA_API int pista_exit(struct pista_context *ctx)
{
    // get semaphore
#ifdef _WIN32
    // HANDLE htid = DestroyThread( tid ); 
#else
    // pthread_destroy( &ctx->ticker_thread, NULL, pista_tick_loop, ctx );
#endif

    struct pista_dev_driver *dev = pista_first_driver( ctx );
    struct pista_dev_inst *nxt;

    ctx->run_ticker = false;

    while( dev != NULL ) {
        struct pista_dev_inst *di = pista_first_inst(dev);
        while( di != NULL ) {
            pista_disconnect( di );
            nxt = pista_next_inst(dev,di);
            pista_release( di ) ;
            di = nxt;
        }
        dev = pista_next_driver( ctx, dev );
    }
    // release semaphore
    //
    return PISTA_OK;
}

/**
 * Plugin management: load 
 */
PISTA_API int pista_load_plugin( struct pista_context *pctx, const char *s_name, const char *s_lib ) {

    struct pista_dev_driver *(*init_func)( struct pista_context *ctx );
    char lib_buf[256];

    char s_upper_name[16] = { '\0' };
    char s_lower_name[16] = { '\0' };
    {
        strncpy( s_upper_name, s_name, 15);
        strncpy( s_lower_name, s_name, 15);
        char *p = s_upper_name;
        while( *p != '\0' ) {
            *p = toupper(*p);
            p++;
        }
        p = s_lower_name;
        while( *p != '\0' ) {
            *p = tolower(*p);
            p++;
        }
    }
    if( s_lib == NULL ) {
        char *plugin_dir = getenv("PISTA_PLUGIN_DIR");

#ifdef WIN32
        if( plugin_dir == NULL ) {
            plugin_dir = "/usr/local/bin";
        }
        strcpy( lib_buf, plugin_dir );
        strcat( lib_buf, "/libpista-");
        strcat( lib_buf, s_lower_name );
        strcat( lib_buf, ".dll" );
#else
        if( plugin_dir == NULL ) {
            plugin_dir = "/usr/local/bin";
        }
        strcpy( lib_buf, plugin_dir );
        strcat( lib_buf, "/libpista-");
        strcat( lib_buf, s_lower_name );
        strcat( lib_buf, ".so" );
#endif
        s_lib = lib_buf;
    }
    void *lib = dlopen( s_lib, RTLD_LAZY  );
    if( lib == NULL ) {
        pista_err("could not find lib: %s ERR=%s\n", s_lib, dlerror() );
        return PISTA_ERR;
    }

    char sym_name[256];
    strcpy( sym_name, s_upper_name );
    strcat( sym_name, "_init" );
    init_func = dlsym( lib, sym_name );

    if( init_func == NULL ) {
        printf("Could not find init_func: %s\n", sym_name );
    } else {

        struct pista_dev_driver *drv = init_func( pctx );
        pista_install_driver( pctx, drv );
    }

    return PISTA_OK;
}


/**
 * Functions for device enumeration and lookup
 */

PISTA_API struct pista_dev_inst *pista_first_inst( struct pista_dev_driver *dev )
{
    struct pista_device_private *priv = dev->priv;
    return priv->first;
}

PISTA_API struct pista_dev_inst *pista_next_inst( struct pista_dev_driver *dev, struct pista_dev_inst *di )
{
    return di = di->next;
}

/**
 * Functions for service enumeration and lookup:
 *
 * pista_first_service
 * pista_next_service
 */

PISTA_API struct pista_discovery_service *pista_first_service( struct pista_context *ctx )
{
    return ctx->service_head;
}

PISTA_API struct pista_discovery_service *pista_next_service( struct pista_context *ctx, struct pista_discovery_service *service )
{
    struct pista_service_priv *curr = (struct pista_service_priv *)service->priv;
    return curr->next;
}

PISTA_API struct pista_discovery_service *pista_find_service( struct pista_context *ctx, const char *name)
{
    struct pista_discovery_service *curr = ctx->service_head;
    while( curr != NULL ) {
        if( strcmp(curr->name, name) == 0 ) {
            break;
        }
        struct pista_service_priv *priv = curr->priv;
        curr = priv->next;
    }

    return curr;
}

PISTA_API struct pista_discovery_service *pista_service_by_idx( struct pista_context *ctx, int idx)
{
    struct pista_discovery_service *curr = ctx->service_head;
    while( curr != NULL ) {
        if( idx == 0 ) {
            break;
        }
        struct pista_service_priv *priv = curr->priv;
        curr = priv->next;
        idx--;
    }

    return curr;
}

PISTA_API int pista_service_count( struct pista_context *ctx)
{
    int count = 0;
    struct pista_discovery_service *curr = ctx->service_head;
    while( curr != NULL ) {
        count++;
        struct pista_service_priv *priv = curr->priv;
        curr = priv->next;
    }

    return count;
}

/**
 * Functions for driver enumeration and lookup:
 *
 * pista_first_driver
 * pista_next_driver
 */

PISTA_API struct pista_dev_driver *pista_first_driver( struct pista_context *ctx )
{
    return ctx->driver_head;
}

PISTA_API struct pista_dev_driver *pista_next_driver( struct pista_context *ctx, struct pista_dev_driver *dev )
{
    struct pista_device_private *curr = (struct pista_device_private *)dev->priv;
    return curr->next;
}

PISTA_API struct pista_dev_driver *pista_find_driver( struct pista_context *ctx, const char *name)
{
    struct pista_dev_driver *curr = ctx->driver_head;
    while( curr != NULL ) {
        if( strcmp(curr->name, name) == 0 ) {
            break;
        }
        struct pista_device_private *priv = curr->priv;
        curr = priv->next;
    }

    return curr;
}

PISTA_API struct pista_dev_driver *pista_dev_by_idx( struct pista_context *ctx, int idx)
{
    struct pista_dev_driver *curr = ctx->driver_head;
    while( curr != NULL ) {
        if( idx == 0 ) {
            break;
        }
        struct pista_device_private *priv = curr->priv;
        curr = priv->next;
        idx--;
    }

    return curr;
}

PISTA_API int pista_dev_count( struct pista_context *ctx)
{
    int count = 0;
    struct pista_dev_driver *curr = ctx->driver_head;
    while( curr != NULL ) {
        count++;
        struct pista_device_private *priv = curr->priv;
        curr = priv->next;
    }

    return count;
}

/**
 * Tick is provided so that most drivers do not need to implement their own thread
 * for maintenance operations.  The tick method is called approximately once/second from
 * the loop inside *pista_run*.
 * This allows a cooperative threading model.
 */

PISTA_API int pista_tick( struct pista_context *ctx )
{
    // printf("tick STARTING\n" );
    struct pista_dev_driver *curr = pista_first_driver( ctx );
    while( curr != NULL ) {
        // printf("ticking driver %s\n", curr->name );

        struct pista_dev_inst *di = pista_first_inst( curr );
        while( di != NULL ) {
            // printf("ticking inst %s\n", di->model );
            curr->tick( di );
            di = di->next;
        }
        curr = pista_next_driver( ctx, curr );
    }
    // printf("tick DONE\n" );

    return PISTA_OK;
}

PISTA_API int pista_probe( struct pista_dev_driver *dev, commfunc_t writefunc, void *writefunc_priv )
{
    int rc = PISTA_OK;
    if( dev->probe != NULL ) {
        rc = dev->probe( writefunc, writefunc_priv );
    }

    return rc;
}

PISTA_API int pista_verify( struct pista_dev_driver *dev, const char data[], size_t len)
{
    int rc = PISTA_ERR_NA;
    if( dev->verify != NULL ) {
        rc = dev->verify( data, len);
    }

    return rc;
}

PISTA_API int pista_dev_register_stream( struct pista_dev_inst *di, struct pista_data_packet *pkt )
{
    pkt->next_stream = di->stream_head;
    di->stream_head = pkt;

    return PISTA_OK;
}

PISTA_API int pista_dev_inst_count( struct pista_dev_driver *dev )
{
    int count = 0;
    struct pista_device_private *dpriv = dev->priv;

    if( dpriv != NULL ) {
        struct pista_dev_inst *di = dpriv->first;
        while( di != NULL ) {
            di = di->next;
            count++;
        }
    }

    return count;
}

PISTA_API struct pista_dev_inst *pista_dev_inst_from_idx( struct pista_dev_driver *dev, int idx )
{
    int pos = 0;
    struct pista_dev_inst *di = NULL;
    struct pista_device_private *dpriv = dev->priv;

    if( dpriv != NULL ) {
        di = dpriv->first;
        while( di != NULL && pos < idx ) {
            di = di->next;
            pos++;
        }
    }

    return di;
}

PISTA_API int pista_dev_register_inst( struct pista_dev_driver *dev, struct pista_dev_inst *di )
{
    struct pista_device_private *dpriv = dev->priv;
    if( dpriv == NULL ) {
        printf("pista_dev_register_inst: invalid registration\n");
    } else {
        di->next = dpriv->first;
        dpriv->first = di;
    }

    return PISTA_OK;
}

PISTA_API int pista_dev_unregister_inst( struct pista_dev_driver *dev, struct pista_dev_inst *di )
{
    struct pista_device_private *dpriv = dev->priv;

    struct pista_dev_inst *prev = NULL;
    struct pista_dev_inst *curr = dpriv->first;
    while( curr != NULL) {
        if( curr == di ) {
            // remove "curr" from the linked list
            if( prev == NULL ) {
                dpriv->first = di->next;
            } else {
                prev->next = di->next;
            }
            // found it...done
            break;
        }
        // not found...continue iterating through the list
        prev = curr;
    }
    di->next = dpriv->first;
    dpriv->first = di;

    return PISTA_OK;
}

/*
 * 
 * */

PISTA_API int pista_allocate( struct pista_dev_driver *drv, struct pista_dev_inst *di )
{
    di->driver = drv;
    di->next = NULL;
    di->model = "N/A";
    di->version = "0.0";
    di->event_handler = NULL;
    di->event_priv = NULL;
    di->comm_func = NULL;
    di->comm_priv = NULL;
    di->stream_head = NULL;
    int rc = drv->allocate( di );
    pista_dev_register_inst( drv, di );

    return rc;
}

/**
 * Release the resources associated with a specific device.
 */

PISTA_API int pista_release( struct pista_dev_inst *di ) 
{
    struct pista_dev_driver *dev = di->driver;
    dev->destroy( di );

    return PISTA_OK;
}

/**
 * Device instances generate events while parsing device specific data.
 */

PISTA_API int pista_set_event_handler( struct pista_dev_inst *di, eventfunc_t handler, void *cb_data )
{
    di->event_handler = handler;
    di->event_priv = cb_data;

    return PISTA_OK;
}

/**
 * Device instances receive data through the parse() method, but occasionally it is necessary to send data
 * back to the device.  Data sent back to the device typically includes configuration commands or message
 * acknowledgements.  This functions provides a handle to the device instance for writing a sequence of
 * bytes back to the device.
 */

PISTA_API int pista_set_comm_handler( struct pista_dev_inst *di, commfunc_t writer, void *cb_data )
{
    di->comm_func = writer;
    di->comm_priv = cb_data;

    return PISTA_OK;
}

/**
 * Start a specific discovery service.
 */
PISTA_API int pista_service_start( struct pista_discovery_service *service ) {
    int rc = PISTA_ERR;
    if( service->start != NULL ) {
        rc = service->start( service );
    }
    return rc;
}

/**
 * Stop a specific discovery service.
 */
PISTA_API int pista_service_stop( struct pista_discovery_service *service ) {
    int rc = PISTA_ERR;
    if( service->stop != NULL ) {
        rc = service->stop( service );
    }
    return rc;
}

/**
 * Pass control to the discovery service using the cooperative thread.
 */
PISTA_API int pista_service_tick( struct pista_discovery_service *service ) {
    int rc = PISTA_ERR;
    if( service->tick != NULL ) {
        rc = service->tick( service );
    }
    return rc;
}

/**
 * When a device is discovered using the discovery service, this function provides the callback mechanism for who should be notified.
 */
PISTA_API int pista_set_discovery_handler( struct pista_discovery_service *service, discoveryfunc_t discovery, void *discovery_priv ) {
    struct pista_service_priv *priv = service->priv;

    printf("storing discovery me=%p, callback: %p\n", priv, discovery);
    priv->discovery_callback = discovery;
    priv->discovery_priv = discovery_priv;

    return PISTA_OK;
}

/**
 * Get the status of the device instance.
 *
 * Returns: ...
 */
PISTA_API enum pista_dev_status pista_get_status( struct pista_dev_inst *di )
{
    return di->status;
}

PISTA_API const char *pista_get_version() {
    return Pista_VERSION;
}

PISTA_API int pista_connect( struct pista_dev_inst *di )
{
    int rc = PISTA_ERR;

    if( di == NULL ) {
        printf("ERR: NULL DI in pista_connect.\n");
        return PISTA_ERR;
    }
    struct pista_dev_driver *dev = di->driver;

    if( dev == NULL ) {
        printf("ERR: NULL DEV in pista_connect.\n");
        return PISTA_ERR;
    } else {
        // printf("DEBUG:  pista_connect %lx %lx.\n", (long unsigned int)dev, (long unsigned int)di);
        if( dev->connect != NULL ) {
            rc = dev->connect( di );
        }
    }
    return rc;
}

PISTA_API int pista_disconnect( struct pista_dev_inst *di )
{
    if( di == NULL ) {
        printf("ERR: NULL DI in pista_disconnect.\n");
        return PISTA_ERR;
    }
    struct pista_dev_driver *dev = di->driver;
    if( dev == NULL ) {
        printf("ERR: NULL DEV in pista_disconnect.\n");
        return PISTA_ERR;
    } else {
        if( dev->disconnect != NULL ) {
            dev->disconnect( di );
        }
    }

    return PISTA_OK;
}

#ifdef _WIN32
DWORD WINAPI pista_tick_loop( LPVOID priv )
#else
static void *pista_tick_loop( void *priv ) 
#endif
{
    struct pista_context *ctx = (struct pista_context *)priv;

    /* During the BACKGROUND operation, tick*/

    sleep(1);
    while( ctx->run_ticker ) {

    // get semaphore
        pista_tick( ctx );
    // release semaphore
        sleep(1);  //  check run flag AFTER sleep and BEFORE tick...saves a spurios tick
    }

   return 0;
}

PISTA_API int pista_run(struct pista_context *ctx)
{
    ctx->run_ticker = true;
#ifdef _WIN32
    DWORD tid = 0;
    HANDLE htid = CreateThread( 
        NULL,          // default security attributes
        0,             // default stack
        pista_tick_loop,  // thread func
        ctx, // argument to thread func
        0, // use default creation
        &tid );  // returned thread identifier
#else
    pthread_create( &ctx->ticker_thread, NULL, pista_tick_loop, ctx );
#endif

    return PISTA_OK;
}


PISTA_API const struct pista_data_packet *pista_get_stream_by_idx( const struct pista_dev_inst *di, int idx )
{
    struct pista_data_packet *stream = di->stream_head;
    while( idx > 0 && stream != NULL ) {
        idx--;
        stream = stream->next_stream;
    }

    return stream;
}

/**
 * The SID is the Stream ID, and can be one of enum [pista_packettype].  FIXME...how do I point to an enum?
 */

PISTA_API const struct pista_data_packet *pista_get_stream_by_sid( const struct pista_dev_inst *di, int stream_id )
{
    struct pista_data_packet *stream = di->stream_head;
    while( stream != NULL ) {
        if( stream->stream_id == stream_id ) {
            break;
        }
        stream = stream->next_stream;
    }

    return stream;
}

PISTA_API int pista_get_stream_count( const struct pista_dev_inst *di )
{
    int count = 0;

    struct pista_data_packet *stream = di->stream_head;
    while( stream != NULL ) {
        count++;
        stream = stream->next_stream;
    }

    return count;
}

// PISTA_API const struct pista_item_desc *pista_stream_get_desc( const struct pista_stream_desc *str, int idx )
// {
    // return &str->desc[idx];
// }

PISTA_API int pista_set_dev_option( struct pista_dev_inst *di, const char *key, const void *value )
{
    struct pista_dev_driver *drv = di->driver;

    if( drv->config_set == NULL ) {
        return PISTA_ERR_NA;
    }

    return drv->config_set( di, key, value );
}

PISTA_API int pista_dump( struct pista_dev_inst *di, pista_dump_flags flags )
{
    struct pista_dev_driver *drv = di->driver;

    if( drv == NULL || drv->dump == NULL ) {
        return PISTA_ERR_NA;
    }

    return drv->dump( di, flags );
}

PISTA_API void *pista_get_dev_option( struct pista_dev_inst *di, const char *key )
{
    struct pista_dev_driver *drv = di->driver;
    if( drv->config_get == NULL ) {
        return NULL;
    }

    return drv->config_get( di, key );
}

PISTA_API struct pista_data_packet *pista_poll( struct pista_dev_inst *di, int sid )
{
    struct pista_dev_driver *drv = di->driver;
    if( drv->poll == NULL ) {
        return NULL;
    }

    return drv->poll( di, sid );
}

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

