
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "pista.h"
#include "pista-internal.h"

#include "pista.h"
#include "pista-internal.h"

#include "pp_api.h"



// #define DEBUG


int PPDISC_init( struct pista_context *pista_ctx, struct pista_discovery_service *svc ) {


    PPDISC_context *me = avahi_new(PPDISC_context,1);
    svc->priv = me;

	me->service = svc;

    me->simple_poll = NULL;
    me->client = NULL;
    me->services = NULL;

	me->discovery_callback = NULL; // discovery_callback;
	me->discovery_priv = NULL; // discovery_private;
    me->browsing = 0;
    me->domain = "X-Series.device.ZOLL.local";
    me->stype = "_workstation._tcp";

    me->resolve = 1;
    me->no_fail = 1;

	return PISTA_OK;
}

struct pista_discovery_service ppdisc_service_info = {
        .name = "ppdisc",
        .longname = "discovery/Propaq M Series Discovery Service",
        .api_version = 1,

        .init = PPDISC_init,
        .cleanup = PPDISC_cleanup,

		.start = PPDISC_start,
	    .tick = PPDISC_tick,
		.stop  = PPDISC_stop,

        .priv = NULL
};

