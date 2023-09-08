
#include <stdio.h>
#include <unistd.h>

#include <time.h>
#include "libserialport.h"

int lspIO_serial_writer( const void *priv, const char *buf, int len ) {
	struct sp_port *port = (struct sp_port *)priv;

	int rc = sp_blocking_write( port, buf, len, 500 );
	if( rc < 0 ) {
		perror("write failure");
	}

    printf("SENT[rc=%d]: ", rc);
    for(int i = 0; i < len; i++ ) {
            if( buf[i] < 32 ) {
                printf("[%2.2x]", (unsigned char)buf[i] );
            } else {
                printf("%c", buf[i] );
            }
    }
    printf("\n");


	return rc;
}


int main(int argc, char* argv[])
{
    char err_buf[64];

	struct sp_port *port;
    const char *port_names[] = { "/dev/ttyS0", NULL };

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
	r = sp_set_baudrate( port, 9600 );
	if( r == SP_OK ) {
		r = sp_set_bits( port, 7 );
	}
	if( r == SP_OK ) {
		r = sp_set_flowcontrol( port, SP_FLOWCONTROL_NONE );
	}
	if( r == SP_OK ) {
		r = sp_set_parity( port, SP_PARITY_ODD );
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

    printf("SET DTR/RTS to on\n");
    struct sp_port_config *config;
    sp_new_config( &config );

    sp_get_config( port, config );
    enum sp_dtr dtr = SP_DTR_INVALID;
    r = sp_get_config_dtr( config, &dtr );
    printf("R=%d DTR=%d\n", r, dtr);
    printf("   ON=%d OFF=%d INVALID=%d FLOW=%d\n", SP_DTR_ON, SP_DTR_OFF, SP_DTR_INVALID, SP_DTR_FLOW_CONTROL );
    sleep(1);

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
        sleep(1);
    }
    sp_free_config( config );

	
	printf("EMULATING MEDSYS3\n");
	printf("==============\n");

	char cc[2];
	cc[1] = '\0';
	time_t tm, last = 0;
	for(;;) {

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
        }
	}

err:
	sp_free_port( port );
	return r;
}
