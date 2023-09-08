
#include <stdio.h>
#include <unistd.h>

#include <pista.h>
#include <pista-internal.h>

#include "libserialport.h"

static bool verbose = false;

int lspIO_serial_writer( const void *priv, const char *buf, int len ) {
	 struct sp_port *port = (struct sp_port *)priv;
    
	int rc = sp_blocking_write( port, buf, len, 500 );
	if( rc < 0 ) {
		perror("write failure");
	}

    printf("SENT[rc=%d --> %lx]: ", rc, (unsigned long)port);
    for(int i = 0; i < len; i++ ) {
            if( buf[i] < 32 ) {
                printf("[%2.2x]", (unsigned char)buf[i] );
            } else {
                printf("%c", buf[i] );
            }
    }
    printf("\n");


	return ( rc == len ) ? PISTA_OK : PISTA_ERR;
}


int run_serial( struct pista_dev_driver *driver, struct pista_dev_inst *pdi )
{
    char err_buf[64];

	struct sp_port *port;
    const char *port_names[] = { "/dev/ttyUSB0", "/dev/ttyUSB1", NULL };

	enum sp_return r;
   
    const char *port_name;
    int idx = 0;
    while( (port_name = port_names[idx++]) != NULL ) {
        r = sp_get_port_by_name(port_name, &port);
	    if( r != SP_OK ) {
            sprintf(err_buf, "Could not enumerate: %s", port_name );
		    perror( err_buf );

		    continue;
	    }

	    r = sp_open(port, SP_MODE_READ | SP_MODE_WRITE );
	    if( r != SP_OK ) {
            sprintf(err_buf, "Could not open: %s", port_name );
		    perror(err_buf);

            continue;
	    }

        break;
    }

    printf("port name=%s\n", port_name );
    if( port_name == NULL ) {
        goto err;
    }


    printf("OPENED PORT=%lx\n", (unsigned long)port );

	// init
	r = sp_set_baudrate( port, 38400 );
	if( r == SP_OK ) {
		r = sp_set_bits( port, 8 );
	}
	if( r == SP_OK ) {
		r = sp_set_flowcontrol( port, SP_FLOWCONTROL_NONE );
	}
	if( r == SP_OK ) {
		r = sp_set_parity( port, SP_PARITY_NONE );
	}
	if( r == SP_OK ) {
		r = sp_set_stopbits( port, 1);
	}
	if( r == SP_OK ) {
		r = sp_set_dtr( port, SP_DTR_ON );
	}
	//if( r == SP_OK ) {
		//r = sp_set_cts( port, SP_CTS_FLOW_CONTROL );
	//}
	if( r == SP_OK ) {
		r = sp_set_rts( port, SP_RTS_ON );
	}
	if( r != SP_OK ) {
		goto err;
	}

	char cc[40];
	cc[1] = '\0';
	time_t tm, last = 0;

       	pdi->comm_func   = lspIO_serial_writer;
        pdi->comm_priv  = port;

	for(;;) {

		int n = sp_blocking_read(port, cc, sizeof(cc), 1000);
        if( n == 0 ) printf("*");
		if( n > 0 ) {
            if(verbose) {
                printf("recv: ");
                for( int i = 0; i < n; i++) {
                    if( cc[i] >= 0x20 ) {
                        printf("%c", cc[i]);
                    } else {
                        printf("%%%2.2d", cc[i]);
                    }
                }
                printf("\n");
            }
		    driver->handle( pdi, cc, n );	
		}
		if( n < 0) {
			perror("read err");
			break;
		}
	    time ( &tm );

        // const char start_message[] = { 1, 'c', 'A', ' ', '8', 'f', '0', 'b', '\r', 0 };
        if( tm > last ) {

            /*
	        int rc = sp_blocking_write( port, start_message, 9, 500 );

            printf("SENT[rc=%d]: ", rc);
            for(int i = 0; i < rc; i++ ) {
                if( start_message[i] < 32 ) {
                    printf("[%2.2x]", (unsigned char)start_message[i] );
                } else {
                    printf("%c", start_message[i] );
                }
            }
            */
		    driver->tick( pdi );
            last = tm + 1;
        }
	}

err:
	sp_free_port( port );
	return r;
}

int main(int argc, char* argv[])
{
    struct pista_context *ctx;
    pista_init( &ctx );
    struct pista_dev_driver *driver = pista_find_driver( ctx, "ht70" );

    if( driver == NULL ) {
	fprintf(stderr, "Could not find driver for HT70!\n");
	return 16;
    }

    struct pista_dev_inst di;
    pista_allocate( driver, &di );

   		di.status = PISTA_ST_NOT_CONNECTED;

	printf("READING HT70\n");
	printf("==============\n");
	// driver->connect( &di );
    pista_connect( &di );

	if( argc == 1 ) {
		run_serial( driver, &di );
	} else {
	}

	driver->disconnect( &di );
}

