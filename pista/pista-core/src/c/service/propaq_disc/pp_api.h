
#ifndef PISTA_PPDISC_PROTOCOL_H_
#define PISTA_PPDISC_PROTOCOL_H_

#include <stdint.h>
#include "pista.h"
#include "pista-internal.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <avahi-common/simple-watch.h>
#include <avahi-common/error.h>
#include <avahi-common/malloc.h>
#include <avahi-common/domain.h>
#include <avahi-common/llist.h>
#include <avahi-client/client.h>
#include <avahi-client/lookup.h>

typedef struct ServiceInfo ServiceInfo;

typedef struct ppdisc_context {
    PISTA_SERVICE_PRIVATE;

    struct pista_discovery_service *service;

    AvahiSimplePoll *simple_poll;
    AvahiClient *client;
    ServiceInfo *services;

    char *domain;
    char *stype;
    int resolve;
    int no_fail;
    int browsing;
} PPDISC_context;

struct ServiceInfo {
    PPDISC_context *me;

    AvahiIfIndex interface;
    AvahiProtocol protocol;
    char *name, *type, *domain;

    AvahiServiceResolver *resolver;

	char url[ AVAHI_ADDRESS_STR_MAX + 20 ];
    AVAHI_LLIST_FIELDS(ServiceInfo, info);
};

void PPDISC_process_pkt( const struct pista_discovery_service *h, const char *recv_buf, int len );

extern struct pista_discovery_service ppdisc_service_info;

struct pista_context;


int PPDISC_init( struct pista_context *pista_ctx, struct pista_discovery_service *svc );
int PPDISC_set_callback( const struct pista_discovery_service *service, discoveryfunc_t handler, void *priv );
int PPDISC_start( const struct pista_discovery_service *svc );
int PPDISC_tick( const struct pista_discovery_service *svc );
int PPDISC_stop( const struct pista_discovery_service *svc );
int PPDISC_cleanup( const struct pista_discovery_service *svc );

#ifdef __cplusplus
}
#endif

#endif
