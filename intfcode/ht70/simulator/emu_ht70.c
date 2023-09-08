
#include <stdio.h>
#include <unistd.h>

// #include <time.h>
#include "libserialport.h"

int lspIO_serial_writer( const void *priv, const char *buf, int len ) {
	struct sp_port *port = (struct sp_port *)priv;

	int rc = sp_blocking_write( port, buf, len, 500 );
	if( rc < 0 ) {
		perror("write failure");
	}

    printf("SENT[rc=%d]\n", rc);
    /*
    for(int i = 0; i < len; i++ ) {
            if( buf[i] < 32 ) {
                printf("[%2.2x]", (unsigned char)buf[i] );
            } else {
                printf("%c", buf[i] );
            }
    }
    printf("\n");
    */

	return rc;
}

void sendfile( struct sp_port *port, FILE *fp ) {
    char buf[256];
    int  n;

    while( (n = fread( buf, 1, 256, fp )) > 0 ) {
        lspIO_serial_writer( port, buf, n );
    }
}


void send_status_message( struct sp_port *port ) {

    const char * input_name = "sample-1.xml";

    FILE *fp = fopen( input_name , "r");
    if( fp == NULL ) {
        fprintf(stderr,"Could not find input file: %s\n", input_name );
    } else {
	    sendfile(port, fp );
        fclose(fp);
    }

	return;
}

void showAvailablePorts()
{
	printf("Available ports: \n");
	struct sp_port **pports;
	enum sp_return ret = sp_list_ports( &pports );
	if( ret != SP_OK ) {
		printf("Error retrieving ports: %d\n", ret );
		return;
	}

	int idx = 0;
	struct sp_port *port = pports[idx++];
	while( port != NULL ) {
		char *name = sp_get_port_name( port );
		char *desc = sp_get_port_description( port );
		if( name == NULL ) break;
		if( desc == NULL ) desc = "?";
		printf("  %-14.14s %-30.30s\n", name, desc );

		port = pports[idx++];
	}

	return;
}


int main(int argc, char* argv[])
{
    char err_buf[64];

    struct sp_port *port;
    struct sp_port *port2;

    if( argc == 1 ) {
	printf("Usage: <prog> <port>\n\n");
	showAvailablePorts();
	return 2;
    }

    char *port_name = argv[1];
    enum sp_return r = sp_get_port_by_name(port_name, &port);

    if( r != SP_OK ) {
        sprintf(err_buf, "Could not find port: %s", port_name );
        perror( err_buf );

        return 1;
    }

    printf("OPENING port name=%s\n", port_name );
    fflush(stdout);
    r = sp_open(port, SP_MODE_READ | SP_MODE_WRITE );
    if( r != SP_OK ) {
        sprintf(err_buf, "Could not open: %s", port_name );
        perror(err_buf);
        fflush(stdout);

        return 1;
    }

    printf("READY port name=%s\n", port_name );
    if( port_name == NULL ) {
        goto err;
    }
    fflush(stdout);

    printf("OPENED PORT=%lx\n", (unsigned long)port );
    fflush(stdout);

    // r = sp_get_port_by_name(port_name, &port2);
    port2 = port;

	// init
	r = sp_set_baudrate( port2, 38400 );
	if( r == SP_OK ) {
		r = sp_set_bits( port2, 8 );
	}
	if( r == SP_OK ) {
		r = sp_set_flowcontrol( port2, SP_FLOWCONTROL_NONE );
	}
	if( r == SP_OK ) {
		r = sp_set_parity( port2, SP_PARITY_NONE );
	}
	if( r == SP_OK ) {
		r = sp_set_stopbits( port2, 1);
	}
	if( r == SP_OK ) {
		r = sp_set_dtr( port2, SP_DTR_ON );
	}
	//if( r == SP_OK ) {
		//r = sp_set_cts( port, SP_CTS_FLOW_CONTROL );
	//}
	if( r == SP_OK ) {
		r = sp_set_rts( port2, SP_RTS_ON );
	}
	if( r != SP_OK ) {
    		printf("CONFIG ERR %d,%d, N, %d: %d\n", 38400, 8, 1, r );
		goto err;
	}
    	printf("CONFIG %d,%d, N, %d\n", 38400, 8, 1 );

    printf("SET DTR/RTS to on\n");
    struct sp_port_config *config;
    sp_new_config( &config );

    sp_get_config( port, config );
    enum sp_dtr dtr = SP_DTR_INVALID;
    r = sp_get_config_dtr( config, &dtr );
    printf("R=%d DTR=%d\n", r, dtr);
    printf("   ON=%d OFF=%d INVALID=%d FLOW=%d\n", SP_DTR_ON, SP_DTR_OFF, SP_DTR_INVALID, SP_DTR_FLOW_CONTROL );
    fflush(stdout);

    for( int ii = 0; ii < 3 ; ii++ ) {
		if( ii % 2 == 0 ) {
            printf("set on\n");
            r = sp_set_dtr( port, SP_DTR_ON );
            if( r == SP_OK ) r = sp_set_rts( port, SP_RTS_ON );
        } else {
            printf("set off\n");
            r = sp_set_dtr( port, SP_DTR_OFF );
            if( r == SP_OK ) r = sp_set_rts( port, SP_RTS_OFF );
        }
	    if( r != SP_OK ) {
            printf("err");
        }
        // sleep(1);
    }
    sp_free_config( config );

	
	printf("EMULATING HT70\n");
	printf("==============\n");
        fflush(stdout);

	char cc[2];
	cc[1] = '\0';
	time_t tm, last = 0;
	for(;;) {
		printf("*");
		fflush(stdout);

		int n = sp_blocking_read(port, cc, 1, 1000);
		if( n > 0 ) {
            if( cc[0] < 32 ) {
                printf("[%2.2x]", (unsigned char)cc[0] );
                fflush(stdout);
            } else {
                printf("%c", cc[0] );
                fflush(stdout);
            }
			// driver->handle( &di, cc, 1 );	
		}
		if( n < 0) {
			perror("read err");
			break;
		}
	    time ( &tm );
        //printf("%ld > %ld\n", tm, last);
        if( tm > last ) {
		    // driver->tick( &di );
            last = tm + 1;

			send_status_message( port );
            sleep(10);
        }
	}

err:
	sp_free_port( port );
	return r;
}
