
#include <libwebsockets.h>
#include <string.h>
#include <signal.h>

#include <netdb.h>
#include <sys/socket.h>

static int interrupted, bad = 1, status;
static struct lws *client_wsi;

char encoded_auth[256];

static int
callback_https(struct lws *wsi, enum lws_callback_reasons reason,
	      void *user, void *in, size_t len)
{
	switch (reason) {

       case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
            
        // if( wsi == propaq->wsi_zoll_rest ) 
        {
                char **p = (char **)in;

                *p += sprintf(*p,
                            "Accept: application/json\r\n"
                            "Content-Type: application/json\r\n"
                            "Client-Id: 12345\r\n"
                                    "Authorization: Basic %s\x0d\x0a", encoded_auth );
        }
        break;

	/* because we are protocols[0] ... */
	case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		lwsl_err("CLIENT_CONNECTION_ERROR: %s\n",
			 in ? (char *)in : "(null)");
		client_wsi = NULL;
		break;

	case LWS_CALLBACK_ESTABLISHED_CLIENT_HTTP:
		status = lws_http_client_http_response(wsi);
		lwsl_user("Connected with server response: %d\n", status);
		break;

	/* chunks of chunked content, with header removed */
	case LWS_CALLBACK_RECEIVE_CLIENT_HTTP_READ:
		// lwsl_user("RECEIVE_CLIENT_HTTP_READ: read %d\n", (int)len);
		{
			const char *p = in;

			while (len--)
				if (*p < 0x7f)
					putchar(*p++);
				else
					putchar('.');
		}
		return 0; /* don't passthru */

	case LWS_CALLBACK_RECEIVE_CLIENT_HTTP:
		{
			char buffer[1024 + LWS_PRE];
			char *px = buffer + LWS_PRE;
			int lenx = sizeof(buffer) - LWS_PRE;

			if (lws_http_client_read(wsi, &px, &lenx) < 0)
				return -1;
		}
		return 0; // don't passthru

	case LWS_CALLBACK_COMPLETED_CLIENT_HTTP:
		lwsl_user("LWS_CALLBACK_COMPLETED_CLIENT_HTTP\n");
		client_wsi = NULL;
		bad = status != 200;
		lws_cancel_service(lws_get_context(wsi)); /* abort poll wait */
		break;

	case LWS_CALLBACK_CLOSED_CLIENT_HTTP:
		client_wsi = NULL;
		bad = status != 200;
		lws_cancel_service(lws_get_context(wsi)); /* abort poll wait */
		break;

    case LWS_CALLBACK_OPENSSL_PERFORM_SERVER_CERT_VERIFICATION:
        X509_STORE_CTX_set_error((X509_STORE_CTX*)user, X509_V_OK);
        break;


	default:
		break;
	}

	return lws_callback_http_dummy(wsi, reason, user, in, len);
}

static const struct lws_protocols protocols[] = {
	{
		"https",
		callback_https,
		0,
		0,
	},
	{ NULL, NULL, 0, 0 }
};

static void
sigint_handler(int sig)
{
	interrupted = 1;
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
    strcat( buf, uri_path );
    ci->path = uri_path;
    ci->port = 443;

    char *uri = strdup(buf);  // need data from the heap, not the stack! uri parser doesnt allocate!

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

const char* wlb_lws_cmdline_option(int argc, const char **argv, const char *val) {

    for(int i = 1; i < argc; i++ ) {
        if( strcmp(argv[i],val) == 0 ) return val;
    }

    return NULL;
}

int main(int argc, const char **argv)
{
	struct lws_context_creation_info info;
	struct lws_client_connect_info i;
	struct lws_context *context;
	const char *p;
	int n = 0, logs = LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE
		   /*
		    * For LLL_ verbosity above NOTICE to be built into lws,
		    * lws must have been configured and built with
		    * -DCMAKE_BUILD_TYPE=DEBUG instead of =RELEASE
		    *
		    * | LLL_INFO   | LLL_PARSER  | LLL_HEADER | LLL_EXT |
		    *   LLL_CLIENT | LLL_LATENCY | LLL_DEBUG
		    */ ;
    char cached_address[32];

	signal(SIGINT, sigint_handler);

	if ((p = wlb_lws_cmdline_option(argc, argv, "-d")))
		logs = atoi(p);

	lws_set_log_level(logs, NULL);
	lwsl_user("LWS minimal http client [-d<verbosity>] [-l] [-z] [--h1]\n");

	memset(&info, 0, sizeof info); /* otherwise uninitialized garbage */
	info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
	info.port = CONTEXT_PORT_NO_LISTEN; /* we do not run any server */
	info.protocols = protocols;

#if defined(LWS_WITH_MBEDTLS)
	/*
	 * OpenSSL uses the system trust store.  mbedTLS has to be told which
	 * CA to trust explicitly.
	 */
	info.client_ssl_ca_filepath = "./warmcat.com.cer";
#endif

	context = lws_create_context(&info);
	if (!context) {
		lwsl_err("lws init failed\n");
		return 1;
	}

	memset(&i, 0, sizeof i); /* otherwise uninitialized garbage */
	i.context = context;
	i.ssl_connection = LCCSCF_USE_SSL;

    const char *user="zolldata:MDARK2018";
    const char *host="192.168.50.100";

    memset( encoded_auth, '\0', sizeof(encoded_auth) );
    char double_encoded_auth[256];
    {  // create the double-encoded credentials used by all services
        char buff[256];
        int rc = lws_b64_encode_string(user, strlen(user), encoded_auth, sizeof( encoded_auth ) );
        strcpy( buff, "Basic " );
        strcat( buff, encoded_auth );
        rc = lws_b64_encode_string(buff, strlen(buff), double_encoded_auth, sizeof( double_encoded_auth ) );
    }

	i.path = "/";
	if (wlb_lws_cmdline_option(argc, argv, "-l")) {
		i.port = 7681;
		i.address = "localhost";
		i.ssl_connection |= LCCSCF_ALLOW_SELFSIGNED;
    } else if (wlb_lws_cmdline_option(argc, argv, "-z")) {
		i.port = 443;
		i.address = "192.168.50.55";
        i.address = "AI17A005890.X-Series.device.ZOLL.local";
		i.ssl_connection |= LCCSCF_ALLOW_SELFSIGNED;
		i.ssl_connection |= LCCSCF_ALLOW_EXPIRED;
		i.ssl_connection |= LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
        i.path = "/Numerics/current?now";

        struct hostent *server = gethostbyname( i.address );
        if( server ) {
            printf("addr type: %d\n", server->h_addrtype );
            printf("addr len : %d\n", server->h_length );
            unsigned char *addr = server->h_addr;
            sprintf( cached_address, "%u.%u.%u.%u", addr[0], addr[1], addr[2], addr[3] );
            i.address = cached_address;
        }
        printf("address=%s\n", i.address );

	} else {
		i.port = 443;
		i.address = "warmcat.com";
	}


	if (wlb_lws_cmdline_option(argc, argv, "--h1"))
		i.alpn = "http/1.1";

	i.host = i.address;
	i.origin = i.address;
	i.method = "GET";

	i.protocol = protocols[0].name;
	i.pwsi = &client_wsi;

    // prepare_uri( context, &i, "https://", host, "/Numerics/current?now" );
	lws_client_connect_via_info(&i);

	while (n >= 0 && client_wsi && !interrupted) {
		n = lws_service(context, 1000);
    }

	lws_context_destroy(context);
	lwsl_user("Completed: %s\n", bad ? "failed" : "OK");

	return bad;
}
/*

*/
