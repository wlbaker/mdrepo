
#include "pista-cl.h"

#include <stdio.h>

using namespace pistax;
// #include <iostream>

extern "C" int binding_eventfunc( void *priv, struct pista_data_packet *pkt ) {

    int ok = -1;

    PistaDev *dev = (PistaDev*)priv;
    if( dev == NULL ) {
        printf("pista-dev.cpp: BINDING ERROR: priv[device] is NULL\n");

    } else {

        PistaDataPacket cxxpkt(pkt);
        ok = dev->sendEvent( &cxxpkt );
    }

    return ok;
}   

extern "C" int binding_commfunc( const void *priv, const char *buf, int len) {
    PistaCommHandler *comm = (PistaCommHandler *)priv;
    return comm->write( buf, len );
}   


PistaDev::PistaDev( pista_dev_inst *di ) { 
    this->di = di; 
}

void PistaDev::attach( commfunc_t writer, void *writer_priv) {
    pista_set_comm_handler( di, writer, writer_priv );
}

void PistaDev::attach( eventfunc_t event_func, void *event_priv) {
    pista_set_event_handler( di, event_func, event_priv );
}

int PistaDev::sendEvent( PistaDataPacket *pkt ) {
    int ok = -1;
    if( event_h == NULL ) {
        printf("pista-dev: event handler is NULL\n");
    } else {
        ok = event_h->event( this, pkt );
    }
    return ok;
}

void PistaDev::attach( PistaEventHandler *h ) {
    event_h = h;
    attach( binding_eventfunc, this );
}

void PistaDev::attach( PistaCommHandler *h ) {
    comm_h = h;
    attach( binding_commfunc, h );
}

pista_dev_inst *PistaDev::c_inst( ) {
	return di;
}

int PistaDev::dump( pista_dump_flags flags ) {
    return pista_dump( c_inst(), flags);
}

int PistaDev::connect( ) {
    return pista_connect( di );
}

int PistaDev::disconnect( ) {
    return pista_disconnect( di );
}

int PistaDev::handle( const char data[], size_t len ) {
	return di->driver->handle( di, data, len );
}

PistaDataPacket *PistaDev::poll( int sid ) {
	pista_data_packet *c_pkt = pista_poll( di, sid );
	if( c_pkt == NULL ) {
		return NULL;
	}
	return new PistaDataPacket( c_pkt );
}

pista_dev_status PistaDev::getStatus( ) {
	return pista_get_status( di );
}

PistaStream PistaDev::getStream( int stream_id )
{
	const pista_data_packet *pkt= pista_get_stream_by_sid( di, stream_id );
	return PistaStream( pkt );
}

int PistaDev::setOption( const char *key, const char *val)
{
	return pista_set_dev_option( di, key, val );
}

