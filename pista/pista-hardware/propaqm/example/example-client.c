#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <libwebsockets.h>

#define KGRN "\033[0;32;32m"
#define KCYN "\033[0;36m"
#define KRED "\033[0;32;31m"
#define KYEL "\033[1;33m"
#define KBLU "\033[0;32;34m"
#define KCYN_L "\033[1;36m"
#define KBRN "\033[0;33m"
#define RESET "\033[0m"

static int destroy_flag = 0;
static int connection_flag = 0;
static int writeable_flag = 0;

static void INT_HANDLER(int signo) {
    destroy_flag = 1;
}

struct session_data {
    int fd;
};

struct pthread_routine_tool {
    struct lws_context *context;
    struct lws *wsi;
};

static int websocket_write_back(struct lws *wsi_in, char *str, int str_size_in) 
{
    if (str == NULL || wsi_in == NULL)
        return -1;

    int n;
    int len;
    char *out = NULL;

    if (str_size_in < 1) 
        len = strlen(str);
    else
        len = str_size_in;

    out = (char *)malloc(sizeof(char)*(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING));
    //* setup the buffer*/
    memcpy (out + LWS_SEND_BUFFER_PRE_PADDING, str, len );
    //* write out*/
    n = lws_write(wsi_in, out + LWS_SEND_BUFFER_PRE_PADDING, len, LWS_WRITE_TEXT);

    printf(KBLU"[websocket_write_back] %s\n"RESET, str);
    //* free the buffer*/
    free(out);

    return n;
}


static int ws_service_callback(
                         struct lws *wsi,
                         enum lws_callback_reasons reason, void *user,
                         void *in, size_t len)
{

    printf("%d.",reason);
    fflush(stdout);
    switch (reason) {

        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            lwsl_notice(KYEL"[Main Service] Connect with server success.\n"RESET);
            connection_flag = 1;
            break;

        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            lwsl_notice(KRED"[Main Service] Connect with server error.\n"RESET);
            destroy_flag = 1;
            connection_flag = 0;
            break;

        case LWS_CALLBACK_CLOSED:
            printf(KYEL"[Main Service] LWS_CALLBACK_CLOSED\n"RESET);
            destroy_flag = 1;
            connection_flag = 0;
            break;

        case LWS_CALLBACK_CLIENT_RECEIVE:
            printf(KCYN_L"[Main Service] Client recvived:%s\n"RESET, (char *)in);

            if (writeable_flag)
                destroy_flag = 1;

            break;
        case LWS_CALLBACK_CLIENT_WRITEABLE :
            printf(KYEL"[Main Service] On writeable is called. send byebye message\n"RESET);
            websocket_write_back(wsi, "Byebye! See you later", -1);
            writeable_flag = 1;
            break;

        default:
            break;
    }

    return 0;
}

static void *pthread_routine(void *tool_in)
{
    struct pthread_routine_tool *tool = tool_in;

    lwsl_notice(KBRN"[pthread_routine] Good day. This is pthread_routine.\n"RESET);

    //* waiting for connection with server done.*/
    while(!connection_flag)
        usleep(1000*20);

    //*Send greeting to server*/
    printf(KBRN"[pthread_routine] Server is ready. send a greeting message to server.\n"RESET); 
    websocket_write_back(tool->wsi, "Good day", -1);

    printf(KBRN"[pthread_routine] sleep 2 seconds then call onWritable\n"RESET);
    sleep(1);
    printf(KBRN"------------------------------------------------------\n"RESET);
    sleep(1);
    //printf(KBRN"[pthread_routine] sleep 2 seconds then call onWritable\n"RESET);

    //*involked wriable*/
    printf(KBRN"[pthread_routine] call on writable.\n"RESET);   
    lws_callback_on_writable(tool->wsi);

}

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
    strcat( buf, ":5000" );
    strcat( buf, uri_path );
    ci->path = buf; // uri_path;
    ci->port = 443;

    char *uri = strdup(buf);  // need data from the heap, not the stack! uri parser doesnt allocate!
    lwsl_notice("early uri=%s port=%d\n", uri, ci->port  );

    int retval = lws_parse_uri(uri, &prot, &ci->address, &ci->port, &p);

    ci->context = context;
    ci->ssl_connection = 2; // self signed certificates
    ci->host = ci->address;
    ci->origin = NULL;
    ci->ietf_version_or_minus_one = ietf_version;
    ci->client_exts = exts;

    lwsl_notice("prepare uri=%s port=%d\n", uri, ci->port  );

    return retval;
}

int main(int argc, char *argv[] )
{
    char *host = NULL;
    char *user = NULL;

    if( argc == 3 ) {
        host = argv[1];
        user = argv[1];
    } else {
        printf("usage: <prog> <host> <user>\n");
        return 0;
    }

    //* register the signal SIGINT handler */
    struct sigaction act;
    act.sa_handler = INT_HANDLER;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction( SIGINT, &act, 0);


    struct lws_context *context = NULL;
    struct lws_context_creation_info info;
    struct lws *wsi = NULL;
    struct lws_protocols protocols[2];

    memset(&info, 0, sizeof info);
    info.port = CONTEXT_PORT_NO_LISTEN;
    info.iface = NULL;
    info.protocols = protocols;
    info.ssl_cert_filepath = NULL;
    info.ssl_private_key_filepath = NULL;
    info.extensions = lws_get_internal_extensions();
    info.gid = -1;
    info.uid = -1;
    info.options = 0;

    protocols[0].name  = "zoll-wss";
    protocols[0].callback = &ws_service_callback;
    protocols[0].per_session_data_size = sizeof(struct session_data);
    protocols[0].rx_buffer_size = 0;
    protocols[0].id = 0;
    protocols[0].user = NULL;

    protocols[1].name  = NULL;
    protocols[1].callback = NULL;
    protocols[1].per_session_data_size = 0;
    protocols[1].rx_buffer_size = 0;
    protocols[1].id = 0;
    protocols[1].user = NULL;

    context = lws_create_context(&info);
    printf(KRED"[Main] context created.\n"RESET);

    if (context == NULL) {
        printf(KRED"[Main] context is NULL.\n"RESET);
        return -1;
    }

    char buff[256];
    char encoded_auth[256];
    char double_encoded_auth[256];

        int rc = lws_b64_encode_string(user, strlen(user), encoded_auth, sizeof( encoded_auth ) );
        strcpy( buff, "Basic " );
        strcat( buff, encoded_auth );
        rc = lws_b64_encode_string(buff, strlen(buff), double_encoded_auth, sizeof( double_encoded_auth ) );


        strcpy( buff, "/Comet");
        strcat( buff, "?auth=" );;
        strcat( buff, double_encoded_auth );
        lwsl_notice("COMET URI=%s\n", buff );

    struct lws_client_connect_info comet_ci;
    struct lws_client_connect_info cix;
    memset(&comet_ci, 0, sizeof(comet_ci));
    memset(&cix, 0, sizeof(cix));
    prepare_uri( context, &comet_ci, "wss://", host, buff );
    comet_ci.protocol = NULL; // protocols[0].name;
    comet_ci.port = 5000;

    lwsl_notice("PROPAQM: starting wss thread\n");

    lws_set_log_level(LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_INFO | LLL_DEBUG, NULL);

    
    cix.context = context;
    cix.address = "localhost";
    cix.port    = "5000";
    cix.ssl_connection = 2; // self signed certificates
    cix.host = "localhost:5000";
    cix.origin = NULL;
    cix.protocol = protocols[0].name;
    cix.ietf_version_or_minus_one = ietf_version;
    cix.client_exts = exts;

    // wsi = lws_client_connect_via_info(&comet_ci);
    wsi = lws_client_connect_via_info(&cix);
    // wsi = lws_client_connect(context, "localhost", 5000, 0, "/", "localhost:5000", NULL, protocols[0].name, -1);
    //
    if (wsi == NULL) {
        printf(KRED"[Main] wsi create error.\n"RESET);
        return -1;
    }

    lwsl_notice(KGRN"[Main] wsi create success.\n"RESET);

    struct pthread_routine_tool tool;
    tool.wsi = wsi;
    tool.context = context;

    pthread_t pid;
    pthread_create(&pid, NULL, pthread_routine, &tool);
    pthread_detach(pid);

    while(!destroy_flag)
    {
        lws_service(context, 50);
    }

    lws_context_destroy(context);

    return 0;
}
