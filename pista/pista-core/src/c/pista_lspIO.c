
#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pista.h"

int lspIO_serial_writer( const void *hh, const char *buf, int len ) {
    const struct pista_dev_inst *h = (const struct pista_dev_inst *)hh;
	struct sp_port *port = h->comm_priv;

	int rc = sp_blocking_write( port, buf, len, 500 );

	return ( rc == len ) ? PISTA_OK : PISTA_ERR;
}

int lspIO_event_callback( const struct pista_dev_inst *h, int event_id, void *message ) {
	printf("[EVENT=%d]", event_id);

	return PISTA_OK;
}

static struct sp_port *lspIO_allocate( const char *portName ) {
	struct sp_port *port;
	int rc = sp_get_port_by_name( portName, &port );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not find port %s: [%d]\n", portName, rc);
		return NULL;
	}

	rc = sp_open( port, SP_MODE_READ_WRITE );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not open port %s: [%d]\n", portName, rc);
		return NULL;
	}

	return port;
}

int pista_config_lspIO( struct pista_dev_inst *di, int baud, char parity, int datab, int stopb, int flow ) {
	struct sp_port *port = di->comm_priv;
	
	int rc = sp_set_baudrate( port, baud );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not set baud: %d\n", rc);
	}

	rc = sp_set_parity( port, SP_PARITY_NONE );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not set parity: %d\n", rc);
	}

	rc = sp_set_bits( port, datab );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not set data bits: %d\n", rc);
	}
	rc = sp_set_stopbits( port, stopb );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not set stop bits: %d\n", rc);
	}
	rc = sp_set_flowcontrol( port, SP_FLOWCONTROL_NONE );
	if( rc != SP_OK ) {
		fprintf(stderr, "Could not set flow control: %d\n", rc);
	}

	return rc;
}

void lspIO_release( void *port ) {

}

PISTA_API int pista_attach_lspIO( struct pista_dev_inst *dev, const char *port_name ) {

    struct sp_port *port = lspIO_allocate( port_name );
    if( port == NULL ) {
        printf("Could not allocate lspIO %s: %d\n", port_name, PISTA_ERR );
        return PISTA_ERR;
    }

       	dev->comm_func   = lspIO_serial_writer;
        dev->comm_priv  = port;

   		dev->status = PISTA_ST_NOT_CONNECTED;

    int rc = sp_flush( port, SP_BUF_BOTH );
    if( rc != 0 ) {
        printf("attach/flush error: %d\n", rc );
    }
    printf("lspIO allocate port: 0x%p\n", port );

    return PISTA_OK;
}

PISTA_API int pista_poll_lspIO( struct pista_dev_inst *di ) {

 	struct sp_port *port = (struct sp_port *)di->comm_priv;
    if( port == NULL ) {
        printf("poll error\n");
        return PISTA_ERR;
    }
    printf("lspIO poll port: 0x%p\n", port );

	int nn = sp_input_waiting( port );
    printf("waiting: %d\n", nn );
    if( nn < 0 ) {
        return PISTA_ERR;
    } else if (nn > 0 ) {

        char buf[128];
        do {
            int len = (nn > 128) ? 128 : nn;
	        int n = sp_blocking_read( port, buf, len, 0 );
            fflush(stdout);
            if( n <= 0 ) {
                // printf("n=%d OS-ERR=%d - %s\n", n, sp_last_error_code(), sp_last_error_message() );
                break;
            }
            nn -= n;
            di->driver->handle( di, buf, n );
        } while( nn > 0 );
    }

    return PISTA_OK;
}

void lspIO_test( struct pista_dev_inst *di ) {
        struct sp_port *port = (struct sp_port *)di->comm_priv;
	struct pista_dev_driver *dev = di->driver;

	char buf[128];

	time_t t0 = 0;
	int ticks = 0;
	do {
		int n = sp_blocking_read( port, buf, 128, 1000 );
		printf("*" );
		fflush(stdout);
		if( n > 0 ) {
			dev->handle( di, buf, n );
		}
		int dt = time(NULL) - t0;
		if( dt > 1 ) {
			dev->tick( di );
			t0 = time(NULL);
			printf("TICK\n");
			ticks++;
		}
	} while( ticks < 100 );

}

PISTA_API int pista_detach_lspIO( struct pista_dev_inst *di) {
        struct sp_port *port = (struct sp_port *)di->comm_priv;
	// struct pista_dev_driver *dev = di->driver;

	return sp_close( port );
}
