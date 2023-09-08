
#include <stdio.h>

#include "imp731.h"
#include "libserialport.h"

int send_to_device( HHANDLE h, const char *buf, int len) {
	struct sp_port *port = (struct sp_port *)h;

	// printf("writing: %8.8lx %d: %.*s\n", port, len, len, buf );
 	enum sp_return r = sp_blocking_write( port, buf, len, 1000 );
	if( r < 0 ) {
		perror("write failure");
	}

	return 0;
}

int main(int argc, char* argv[])
{

	struct sp_port *port;

	enum sp_return r = sp_get_port_by_name("/dev/ttyUSB0", &port);
	if( r != SP_OK ) {
		perror("Could not enumerate ttyUSB0");
		return -1;
	}

	r = sp_open(port, SP_MODE_READ | SP_MODE_WRITE );
	if( r != SP_OK ) {
		perror("Could not open port");
		goto err;
	}

	// init
	r = sp_set_baudrate( port, 115200 );
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
	if( r != SP_OK ) {
		goto err;
	}
	
	CHANDLE hDevice = IMP731_init( port, send_to_device );

	printf("READING IMP731\n");
	printf("==============\n");

	int pkt = 1;
	// int crc_seed = 0;
	char cc[2];
	cc[1] = '\0';
	for(;;) {
		int n = sp_blocking_read(port, cc, 1, 1000);
		if( n > 0 ) {
			IMP731_handle( hDevice, cc, 1 );	
		}
		if( n < 0) {
			perror("read err");
			break;
		}
		IMP731_tick( hDevice );
		
	}

	IMP731_close( hDevice );
err:
	sp_free_port( port );
	return r;
}
