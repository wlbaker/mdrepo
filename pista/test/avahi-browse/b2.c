
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

#include <avahi-common/simple-watch.h>
#include <avahi-common/error.h>
#include <avahi-common/malloc.h>
#include <avahi-common/domain.h>
#include <avahi-common/llist.h>
// #include <avahi-common/i18n.h>
#include <avahi-client/client.h>
#include <avahi-client/lookup.h>

char buf[64];
const char * avahi_strerror( int a ) {
    sprintf(buf, "ERR-%d", a );
    return buf;
}

typedef enum {
    COMMAND_BROWSE_SERVICES,
} Command;

typedef struct Config {
    int verbose;
    char *domain;
    char *stype;
    Command command;
    int resolve;
    int no_fail;
} Config;

typedef struct ServiceInfo ServiceInfo;

struct ServiceInfo {
    AvahiIfIndex interface;
    AvahiProtocol protocol;
    char *name, *type, *domain;

    AvahiServiceResolver *resolver;
    Config *config;

    AVAHI_LLIST_FIELDS(ServiceInfo, info);
};

static AvahiSimplePoll *simple_poll = NULL;
static AvahiClient *client = NULL;
static ServiceInfo *services = NULL;
static int browsing = 0;

static ServiceInfo *find_service(AvahiIfIndex interface, AvahiProtocol protocol, const char *name, const char *type, const char *domain) {
    ServiceInfo *i;

    for (i = services; i; i = i->info_next)
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

static void print_service_line(Config *config, char c, AvahiIfIndex interface, AvahiProtocol protocol, const char *name, const char *type, const char *domain, int nl) {
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
            char address[AVAHI_ADDRESS_STR_MAX], *t;

            avahi_address_snprint(address, sizeof(address), a);

            t = avahi_string_list_to_string(txt);

            print_service_line(i->config, '=', interface, protocol, name, type, domain, 0);

                printf("   hostname = [%s]\n"
                       "   address = [%s]\n"
                       "   port = [%u]\n"
                       "   txt = [%s]\n",
                       host_name,
                       address,
                       port,
                       t);

            avahi_free(t);

            break;
        }

        case AVAHI_RESOLVER_FAILURE:

            fprintf(stderr, "Failed to resolve service '%s' of type '%s' in domain '%s': %s\n", name, type, domain, avahi_strerror(avahi_client_errno(client)));
            break;
    }


    avahi_service_resolver_free(i->resolver);
    i->resolver = NULL;

}

static ServiceInfo *add_service(Config *c, AvahiIfIndex interface, AvahiProtocol protocol, const char *name, const char *type, const char *domain) {
    printf("*** ADD SERVICE CALLED: %s %s %s ***\n", name, type, domain);
    ServiceInfo *i;

    i = avahi_new(ServiceInfo, 1);

    if (!(i->resolver = avahi_service_resolver_new(client, interface, protocol, name, type, domain, AVAHI_PROTO_UNSPEC, 0, service_resolver_callback, i))) {
        avahi_free(i);
        fprintf(stderr, "Failed to resolve service '%s' of type '%s' in domain '%s': %s\n", name, type, domain, avahi_strerror(avahi_client_errno(client)));
        return NULL;
    }


    i->interface = interface;
    i->protocol = protocol;
    i->name = avahi_strdup(name);
    i->type = avahi_strdup(type);
    i->domain = avahi_strdup(domain);
    i->config = c;

    AVAHI_LLIST_PREPEND(ServiceInfo, info, services, i);

    return i;
}

static void remove_service(Config *c, ServiceInfo *i) {
    printf("*** REMOVE SERVICE CALLED ***\n");
    assert(c);
    assert(i);

    AVAHI_LLIST_REMOVE(ServiceInfo, info, services, i);

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

    Config *c = userdata;

    assert(b);
    assert(c);

    printf("SERVICE BROWSER CALLBACK: %d\n", event);
    switch (event) {
        case AVAHI_BROWSER_NEW: {
            printf("== AVAHI_BROWSER_NEW\n");

            if (find_service(interface, protocol, name, type, domain))
                return;

            add_service(c, interface, protocol, name, type, domain);

            print_service_line(c, '+', interface, protocol, name, type, domain, 1);
            break;

        }

        case AVAHI_BROWSER_REMOVE: {
            printf("== AVAHI_BROWSER_REMOVE\n");
            ServiceInfo *info;

            if (!(info = find_service(interface, protocol, name, type, domain)))
                return;

            remove_service(c, info);

            print_service_line(c, '-', interface, protocol, name, type, domain, 1);
            break;
        }

        case AVAHI_BROWSER_FAILURE:
            printf("== AVAHI_BROWSER_FAILURE\n");
            fprintf(stderr, "service_browser failed: %s\n", avahi_strerror(avahi_client_errno(client)));
            avahi_simple_poll_quit(simple_poll);
            break;

        case AVAHI_BROWSER_CACHE_EXHAUSTED:
            printf("== AVAHI_BROWSER_CACHE_EXHAUSTED\n");
            break;

        case AVAHI_BROWSER_ALL_FOR_NOW:
            printf("== AVAHI_BROWSER_ALL_FOR_NOW\n");
            break;
    }
}

static void browse_service_type(Config *c, const char *stype, const char *domain) {
    AvahiServiceBrowser *b;
    AvahiStringList *i;

    assert(c);
    assert(client);
    assert(stype);

    printf("browse_service_type: %s %s\n", stype, domain );

    if (!(b = avahi_service_browser_new(
              client,
              AVAHI_IF_UNSPEC,
              AVAHI_PROTO_UNSPEC,
              stype,
              domain,
              0,
              service_browser_callback,
              c))) {

        fprintf(stderr, "avahi_service_browser_new() failed: %s\n", avahi_strerror(avahi_client_errno(client)));
        avahi_simple_poll_quit(simple_poll);
    }

}

static void service_type_browser_callback(
    AvahiServiceTypeBrowser *b,
    AVAHI_GCC_UNUSED AvahiIfIndex interface,
    AVAHI_GCC_UNUSED AvahiProtocol protocol,
    AvahiBrowserEvent event,
    const char *type,
    const char *domain,
    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
    void *userdata) {

    Config *c = userdata;

    assert(b);
    assert(c);

    switch (event) {

        case AVAHI_BROWSER_NEW:
            browse_service_type(c, type, domain);
            break;

        case AVAHI_BROWSER_REMOVE:
            /* We're dirty and never remove the browser again */
            break;

        case AVAHI_BROWSER_FAILURE:
            fprintf(stderr, "service_type_browser failed: %s\n", avahi_strerror(avahi_client_errno(client)));
            avahi_simple_poll_quit(simple_poll);
            break;

        case AVAHI_BROWSER_CACHE_EXHAUSTED:
            break;

        case AVAHI_BROWSER_ALL_FOR_NOW:
            break;
    }
}

static void domain_browser_callback(
    AvahiDomainBrowser *b,
    AVAHI_GCC_UNUSED AvahiIfIndex interface,
    AVAHI_GCC_UNUSED AvahiProtocol protocol,
    AvahiBrowserEvent event,
    const char *domain,
    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
    void *userdata) {

    Config *c = userdata;

    assert(b);
    assert(c);

    switch (event) {

        case AVAHI_BROWSER_NEW:
        case AVAHI_BROWSER_REMOVE: {
            char ifname[IF_NAMESIZE];

                printf("%c %4s %4s %s\n",
                       event == AVAHI_BROWSER_NEW ? '+' : '-',
                       interface != AVAHI_IF_UNSPEC ? if_indextoname(interface, ifname) : "n/a",
                       protocol != AVAHI_PROTO_UNSPEC ? avahi_proto_to_string(protocol) : "n/a",
                       domain);
            break;
        }

        case AVAHI_BROWSER_FAILURE:
            fprintf(stderr, ("domain_browser failed: %s\n"), avahi_strerror(avahi_client_errno(client)));
            avahi_simple_poll_quit(simple_poll);
            break;

        case AVAHI_BROWSER_CACHE_EXHAUSTED:
            break;

    }
}

static void client_callback(AvahiClient *c, AvahiClientState state, AVAHI_GCC_UNUSED void * userdata) {
    Config *config = userdata;

    /* This function might be called when avahi_client_new() has not
     * returned yet.*/
    client = c;

    switch (state) {
        case AVAHI_CLIENT_FAILURE:

            if (config->no_fail && avahi_client_errno(c) == AVAHI_ERR_DISCONNECTED) {
                int error;

                /* We have been disconnected, so let reconnect */

                fprintf(stderr, "Disconnected, reconnecting ...\n");

                avahi_client_free(client);
                client = NULL;

                while (services)
                    remove_service(config, services);

                browsing = 0;

                if (!(client = avahi_client_new(avahi_simple_poll_get(simple_poll), AVAHI_CLIENT_NO_FAIL, client_callback, config, &error))) {
                    fprintf(stderr, "Failed to create client object: %s\n", avahi_strerror(error));
                    avahi_simple_poll_quit(simple_poll);
                }

            } else {
                fprintf(stderr, "Client failure, exiting: %s\n", avahi_strerror(avahi_client_errno(c)));
                avahi_simple_poll_quit(simple_poll);
            }

            break;

        case AVAHI_CLIENT_S_REGISTERING:
        case AVAHI_CLIENT_S_RUNNING:
        case AVAHI_CLIENT_S_COLLISION:

            if (!browsing) {
                browse_service_type(config, config->stype, config->domain);
                browsing++;
            }

            break;

        case AVAHI_CLIENT_CONNECTING:

                fprintf(stderr, "Waiting for daemon ...\n");

            break;
    }
}


static int set_zoll_options(Config *c ) {
    int o;

    const char *xseries_domain = "X-Series.device.ZOLL.local";
    const char *stype = "_workstation._tcp";
    assert(c);

    c->command = COMMAND_BROWSE_SERVICES;
    c->verbose =
        c->resolve =
        c->no_fail = 0;

    c->verbose = 1;
    c->domain = avahi_strdup(xseries_domain);
    c->resolve = 1;
    c->no_fail = 1;

    c->stype = avahi_strdup(stype);

    return 0;
}

int main(int argc, char *argv[]) {
    int ret = 1, error;
    Config config;

    set_zoll_options(&config );


    if (!(simple_poll = avahi_simple_poll_new())) {
        fprintf(stderr, "Failed to create simple poll object.\n");
        goto fail;
    }

    if (!(client = avahi_client_new(avahi_simple_poll_get(simple_poll), config.no_fail ? AVAHI_CLIENT_NO_FAIL : 0, client_callback, &config, &error))) {
        fprintf(stderr, "Failed to create client object: %s\n", avahi_strerror(error));
        goto fail;
    }

	int cnt = 0;
    // avahi_simple_poll_loop(simple_poll);
    for( int i = 0; i < 10000; i++ ) {
		cnt++;
        for(int j = 0; j < 5; j++ ) {
            ret = avahi_simple_poll_iterate(simple_poll, 0);
            if( ret != 0 ) printf("iterate ret=%d\n", ret );
        }
        sleep(1);
		printf(".");
		if( cnt > 80 ) {
			printf("\n");
			cnt = 0;
		}
		fflush(stdout);
    }
    ret = 0;

fail:

    while (services)
        remove_service(&config, services);

    if (client)
        avahi_client_free(client);

    if (simple_poll)
        avahi_simple_poll_free(simple_poll);

    avahi_free(config.domain);
    avahi_free(config.stype);

    return ret;
}

