
#include <iostream>
#include <string>
#include "pista-cl.h"

using namespace pistax;

void PistaService::discovery_eventfunc( const void *priv, const struct pista_discovery_info *pdi ) {

    PistaDiscoveryHandler *h = (PistaDiscoveryHandler *)priv;

    if( h != NULL ) {
        h->discovery( pdi->tm, pdi->event_type, pdi->name, pdi->url );
    }

    return;
}   

PistaService::PistaService( pista_discovery_service *c_service ) {
	this->c_service= c_service;
}

const char *PistaService::name( ) {
	return c_service->name;
}

const char *PistaService::longname( ) {
	return c_service->longname;
}


void PistaService::attach( discoveryfunc_t discovery_func, void *discovery_priv) {
    pista_set_discovery_handler( c_service, discovery_func, discovery_priv );
}

void PistaService::attach( PistaDiscoveryHandler *h ) {
    attach( discovery_eventfunc, h );
}

int PistaService::start() {
    return pista_service_start( c_service );
}

int PistaService::stop() {
    return pista_service_stop( c_service );
}

int PistaService::tick( ) {
    return pista_service_tick( c_service );
}



