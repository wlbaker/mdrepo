
#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <check.h>

#include "pista.h"
#include "model/imp731.pb-c.h"

extern struct pista_dev_driver imp731_driver_info;

int comm_callback( const struct pista_dev_inst *h, const char *buf, int len ) {
	struct sp_port *port = h->comm_priv;

	int rc = sp_blocking_write( port, buf, len, 500 );

	return ( rc == len ) ? PISTA_OK : PISTA_ERR;
}

int event_callback( void *priv, struct pista_data_packet  *pkt) {
    const struct pista_dev_inst *h = priv;
	printf("[EVENT=0x%lx 0x%lx %d]\n", priv, pkt, pkt->stream_id );

    if( pkt->stream_id == PISTA_DF_WAVEFORM ) {
        Imp731__Sensors *s = pkt->payload;
        for( int i = 0; i < 10; i++ ) {
            printf("%d/%d: %d %d %d %d\n", i, s->n_w0, s->w0[i], s->w1[i], s->w2[i], s->w3[i] );
        }
    }
	return PISTA_OK;
}

int main(int argc, char *argv[] ) {

    char *driver_name="imp731";

	char buf[128];

	struct sp_port *port;
	int rc = sp_get_port_by_name( "/dev/ttyUSB0", &port );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not find port /dev/ttyUSB0\n");
		return rc;
	}

	rc = sp_open( port, SP_MODE_WRITE );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not find port /dev/ttyUSB0\n");
		return rc;
	}

	rc = sp_set_baudrate( port, 115200 );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not set baud\n");
		return rc;
	}

	rc = sp_set_parity( port, SP_PARITY_NONE );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not set parity\n");
		return rc;
	}

	rc = sp_set_bits( port, 8 );
	rc = sp_set_stopbits( port, 1 );
	rc = sp_set_flowcontrol( port, SP_FLOWCONTROL_NONE );

	struct pista_context     *ctx = NULL;
    pista_init( &ctx );
	// d->init( ctx, d );                  // when the driver is loaded

    
	struct pista_dev_driver  *d = pista_find_driver( ctx, driver_name );
    if( d == NULL ) {
		fprintf(stderr, "Could not find driver: %s\n", driver_name);
		return PISTA_ERR;
    }


    struct pista_dev_inst *di = malloc( sizeof( struct pista_dev_inst ) );
    pista_allocate( d, di );
	if( di == NULL ) {
		return PISTA_ERR;
	}

    pista_set_comm_handler( di, comm_callback, port);
	pista_set_event_handler( di, event_callback, di );

	time_t t0 = 0;
	int ticks = 0;
	do {
		int n = sp_blocking_read( port, buf, 128, 1000 );
		fflush(stdout);
		if( n > 0 ) {
			d->handle( di, buf, n );
		}
		int dt = time(NULL) - t0;
		if( dt > 1 ) {
			d->tick( di );
            // pista_tick( ctx );
			t0 = time(NULL);
			printf("TICK\n");
			ticks++;
		}
	} while( ticks < 100 );

	d->destroy( di );

	d->cleanup( d );

	sp_free_port( port );

	return 0;
}

