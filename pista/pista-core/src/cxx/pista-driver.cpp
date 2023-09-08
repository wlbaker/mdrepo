
#include <iostream>
#include <string>
#include "pista-cl.h"

using namespace pistax;

PistaDriver::PistaDriver( pista_dev_driver *c_driver ) {
	this->c_driver= c_driver;
}

const char *PistaDriver::name( ) {
	return c_driver->name;
}

const char *PistaDriver::longname( ) {
	return c_driver->longname;
}

PistaDev *PistaDriver::allocate() {
    // std::cout << "ALLOCATE: " << c_driver->name << std::endl << std::flush;

    pista_dev_inst *di = new pista_dev_inst;
    pista_allocate( c_driver, di );

    return new PistaDev( di );
}

void PistaDriver::release(PistaDev *dev) {
    pista_release( dev->c_inst() );
	delete dev;
}

pista_dev_driver *PistaDriver::c_inst() {
	return c_driver;
}

// also defined in pista-dev.cpp
extern "C" int driver_binding_commfunc( const void *priv, const char *buf, int len) {
    PistaCommHandler *comm = (PistaCommHandler *)priv;
    return comm->write( buf, len );
}   

int PistaDriver::probe( PistaCommHandler *h ) {
    return pista_probe( c_driver, driver_binding_commfunc, h );
}

int PistaDriver::verify( const char data[], size_t len, int data_len ) {
	return pista_verify( c_driver, data, data_len );
}

