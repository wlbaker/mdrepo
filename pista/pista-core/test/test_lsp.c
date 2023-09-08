
#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pista.h"

extern struct pista_dev_driver imp731_driver_info;

int main(int argc, char *argv[] ) {

	struct pista_context     *ctx = NULL;
	struct pista_dev_driver  *d = &imp731_driver_info;
	struct pista_dev_inst    *di;

	d->init( ctx, d );                  // when the driver is loaded

	di = PISTA_MALLOC( sizeof( struct pista_dev_inst ) );
	d->allocate( d, di );               // create instance specific buffers

	lspIO_attach( di, "/dev/ttyUSB0", 115200, 8, 1, 'N', 0 );
	lspIO_test( di );
	lspIO_detach( di );

	d->detach( di );

	d->cleanup( d );

	sp_free_port( port );

	return 0;
}

