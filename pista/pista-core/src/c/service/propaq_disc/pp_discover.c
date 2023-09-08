
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <locale.h>
#include <ctype.h>

#include <unistd.h>

#include "pista.h"
#include "pista-internal.h"

#include "pp_api.h"


static ServiceInfo *find_service(PPDISC_context *me, AvahiIfIndex interface, AvahiProtocol protocol, const char *name, const char *type, const char *domain) {
    ServiceInfo *i;

    for (i = me->services; i; i = i->info_next)
        if (i->interface == interface &&
            i->protocol == protocol &&
            strcasecmp(i->name, name) == 0 &&
            avahi_domain_equal(i->type, type) &&
            avahi_domain_equal(i->domain, domain))

            return i;

    return NULL;
}

static char *make_printable(const char *from, char *to) {
    const char *f;
    char *t;

    for (f = from, t = to; *f; f++, t++)
        *t = isprint(*f) ? *f : '_';

    *t = 0;

    return to;
}

static void print_service_line( char c, AvahiIfIndex interface, AvahiProtocol protocol, const char *name, const char *type, const char *domain, int nl) {
    char ifname[IF_NAMESIZE];

        char label[AVAHI_LABEL_MAX];
        make_printable(name, label);

        printf("%c %6s %4s %s %s %s\n",
               c,
               interface != AVAHI_IF_UNSPEC ? if_indextoname(interface, ifname) : "n/a",
               protocol != AVAHI_PROTO_UNSPEC ? avahi_proto_to_string(protocol) : "n/a",
               label, type, domain);

    fflush(stdout);
}

static void service_resolver_callback(
    AvahiServiceResolver *r,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    AvahiResolverEvent event,
    const char *name,
    const char *type,
    const char *domain,
    const char *host_name,
    const AvahiAddress *a,
    uint16_t port,
    AvahiStringList *txt,
    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
    void *userdata) {

    ServiceInfo *i = userdata;

    assert(r);
    assert(i);

    switch (event) {
        case AVAHI_RESOLVER_FOUND: {
            char address[AVAHI_ADDRESS_STR_MAX];

            avahi_address_snprint(address, sizeof(address), a);

            // t = avahi_string_list_to_string(txt);

            print_service_line( '=', interface, protocol, name, type, domain, 0);

                printf("   hostname = [%s]\n"
                       "   address = [%s]\n"
                       "   port = [%u]\n",
                       host_name,
                       address,
                       port );

            //   txt = [%s], t

				sprintf(i->url, "propaq://%s:%d", address, port );

                struct pista_discovery_info di;
                di.tm = pista_get_current_time_with_ms();
                di.event_type = PISTA_DEV_DISCOVER;
                di.name = i->name;
                di.url = i->url;

                if( i->me->discovery_callback != NULL ) {
	                i->me->discovery_callback( i->me->discovery_priv, &di );
                }

            // avahi_free(t);

            break;
        }

        case AVAHI_RESOLVER_FAILURE:

            fprintf(stderr, "Failed to resolve service '%s' of type '%s' in domain '%s'\n", name, type, domain );
            break;
    }


    avahi_service_resolver_free(i->resolver);
    i->resolver = NULL;

}

static ServiceInfo *add_service(PPDISC_context *me, AvahiIfIndex interface, AvahiProtocol protocol, const char *name, const char *type, const char *domain) {
    ServiceInfo *i;

    i = avahi_new(ServiceInfo, 1);

    if (!(i->resolver = avahi_service_resolver_new(me->client, interface, protocol, name, type, domain, AVAHI_PROTO_UNSPEC, 0, service_resolver_callback, i))) {
        avahi_free(i);
        fprintf(stderr, "Failed to resolve service '%s' of type '%s' in domain '%s': %d\n", name, type, domain, avahi_client_errno(i->me->client));
        return NULL;
    }


    memset( i->url, '\0', sizeof(i->url));
    i->interface = interface;
    i->protocol = protocol;
    i->name = avahi_strdup(name);
    i->type = avahi_strdup(type);
    i->domain = avahi_strdup(domain);
    i->me = me;

    AVAHI_LLIST_PREPEND(ServiceInfo, info, me->services, i);

    return i;
}

static void remove_service(PPDISC_context *me, ServiceInfo *i) {
    assert(me);
    assert(i);

        struct pista_discovery_info di;
        di.tm = pista_get_current_time_with_ms();
        di.event_type = PISTA_DEV_LOST;
        di.name = i->name;
        di.url  = i->url;

    if( me->discovery_callback != NULL ) {
	    me->discovery_callback( me->discovery_priv, &di );
    }

    AVAHI_LLIST_REMOVE(ServiceInfo, info, me->services, i);

    if (i->resolver)
        avahi_service_resolver_free(i->resolver);

    avahi_free(i->name);
    avahi_free(i->type);
    avahi_free(i->domain);
    avahi_free(i);
}

static void service_browser_callback(
    AvahiServiceBrowser *b,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    AvahiBrowserEvent event,
    const char *name,
    const char *type,
    const char *domain,
    AvahiLookupResultFlags flags,
    void *userdata) {

    PPDISC_context *me = userdata;

    assert(b);
    assert(me);

    switch (event) {
        case AVAHI_BROWSER_NEW: {

            if (find_service(me, interface, protocol, name, type, domain))
                return;

            add_service(me, interface, protocol, name, type, domain);

            print_service_line( '+', interface, protocol, name, type, domain, 1);
            break;

        }

        case AVAHI_BROWSER_REMOVE: {
            ServiceInfo *info;

            if (!(info = find_service(me, interface, protocol, name, type, domain)))
                return;

            remove_service(me, info);

            print_service_line( '-', interface, protocol, name, type, domain, 1);
            break;
        }

        case AVAHI_BROWSER_FAILURE:
            fprintf(stderr, "service_browser failed: %d\n", avahi_client_errno(me->client));
            avahi_simple_poll_quit(me->simple_poll);
            break;

        case AVAHI_BROWSER_CACHE_EXHAUSTED:
            break;

        case AVAHI_BROWSER_ALL_FOR_NOW:
            break;
    }
}

static void browse_service_type(PPDISC_context *me, const char *stype, const char *domain) {
    AvahiServiceBrowser *b;

    assert(me);
    assert(me->client);
    assert(stype);

    printf("browse_service_type: %s %s\n", stype, domain );

    if (!(b = avahi_service_browser_new(
              me->client,
              AVAHI_IF_UNSPEC,
              AVAHI_PROTO_UNSPEC,
              stype,
              me->domain,
              0,
              service_browser_callback,
              me))) {

        fprintf(stderr, "avahi_service_browser_new() failed: %d\n", avahi_client_errno(me->client));
        avahi_simple_poll_quit(me->simple_poll);
    }

}

static void client_callback(AvahiClient *c, AvahiClientState state, AVAHI_GCC_UNUSED void * userdata) {
    PPDISC_context *me = userdata;

    /* This function might be called when avahi_client_new() has not
     * returned yet.*/
    if( me->client == NULL ) {
        me->client = c;
    }

    switch (state) {
        case AVAHI_CLIENT_FAILURE:

            if (me->no_fail && avahi_client_errno(c) == AVAHI_ERR_DISCONNECTED) {
                int error;

                /* We have been disconnected, so let reconnect */

                fprintf(stderr, "Disconnected, reconnecting ...\n");

                avahi_client_free(me->client);
                me->client = NULL;

                while (me->services)
                    remove_service(me, me->services);

                me->browsing = 0;

                if (!(me->client = avahi_client_new(avahi_simple_poll_get(me->simple_poll), AVAHI_CLIENT_NO_FAIL, client_callback, me, &error))) {
                    fprintf(stderr, "Failed to create client object: %d\n", error);
                    avahi_simple_poll_quit(me->simple_poll);
                }

            } else {
                fprintf(stderr, "Client failure, exiting: %d\n", avahi_client_errno(c));
                avahi_simple_poll_quit(me->simple_poll);
            }

            break;

        case AVAHI_CLIENT_S_REGISTERING:
        case AVAHI_CLIENT_S_RUNNING:
        case AVAHI_CLIENT_S_COLLISION:

            if (!me->browsing) {
                browse_service_type(me, me->stype, me->domain);
                me->browsing++;
            }

            break;

        case AVAHI_CLIENT_CONNECTING:

                fprintf(stderr, "Waiting for daemon ...\n");

            break;
    }
}



int PPDISC_start(const struct pista_discovery_service *svc) {

    PPDISC_context *me = (PPDISC_context *)svc->priv;
    int ret = 1, error;

    if (!(me->simple_poll = avahi_simple_poll_new())) {
        fprintf(stderr, "Failed to create simple poll object.\n");
        goto fail;
    }

    if (!(me->client = avahi_client_new(avahi_simple_poll_get(me->simple_poll), me->no_fail ? AVAHI_CLIENT_NO_FAIL : 0, client_callback, me, &error))) {
        fprintf(stderr, "Failed to create client object: %d\n", error);
        goto fail;
    }

    ret = PISTA_OK;

	return ret;

fail:

	PPDISC_cleanup(svc);

    return PISTA_ERR;
}

int PPDISC_tick( const struct pista_discovery_service *svc ) {
    PPDISC_context *me = (PPDISC_context *)svc->priv;

	int ret = 0;
    for(int j = 0; j < 5; j++ ) {
        ret = avahi_simple_poll_iterate(me->simple_poll, 0);
        if( ret != 0 ) printf("PPDISC_tick() iteration returned=%d\n", ret );
    }

	return ret;
}

int PPDISC_stop( const struct pista_discovery_service *svc ) {
    PPDISC_context *me = (PPDISC_context *)svc->priv;

    while (me->services)
        remove_service(me, me->services);


    if (me->client)
        avahi_client_free(me->client);

    me->client = NULL;

    if (me->simple_poll)
        avahi_simple_poll_free(me->simple_poll);

    me->simple_poll = NULL;

    return PISTA_OK;
}

int PPDISC_cleanup( const struct pista_discovery_service *svc ) {
    PPDISC_context *me = (PPDISC_context *)svc->priv;

    avahi_free(me);

    return PISTA_OK;
}


