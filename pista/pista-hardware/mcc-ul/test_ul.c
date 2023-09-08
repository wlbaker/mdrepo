
#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pista.h"

extern struct pista_dev_driver mccul_driver_info;

int main(int argc, char *argv[] ) {

	struct pista_context     *ctx = NULL;
	struct pista_dev_driver  *d = &mccul_driver_info;
	struct pista_dev_inst    *di;

	d->init( ctx, d );                  // when the driver is loaded

	di = PISTA_MALLOC( sizeof( struct pista_dev_inst ) );
	d->allocate( d, di );               // create instance specific buffers

	d->attach();  ...???

	d->detach( di );

	d->cleanup( d );

	return 0;
}

