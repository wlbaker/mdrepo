
#include <iostream>
#include <libserialport.h>

#include "config.h"
#include "pista-cl.h"


LspCOMM::LspCOMM( const char *portName ) {
   	int rc = sp_get_port_by_name( portName, &port );
   	if( rc != SP_OK ) {
       	std::cerr << "Could not find port " << portName << std::endl;
		// throw error
   	}
    
    std::cout << "lspcomm port allocated: " << port << std::endl;
}


LspCOMM::~LspCOMM() {

    std::cout << "lspcomm destructor called: " << port << std::endl;
}

int LspCOMM::config( int baud, int datab, int stopb, char parity ) {
	
	int rc = sp_set_baudrate( port, baud );
	if( rc != SP_OK ) {
		std::cerr << "Could not set baud\n" << std::endl;
		return PISTA_ERR;
	}

	rc = sp_set_parity( port, SP_PARITY_NONE );
	if( rc != SP_OK ) {
		std::cerr << "Could not set parity\n" << std::endl;
		return PISTA_ERR;
	}

	rc = sp_set_bits( port, datab );
	rc = sp_set_stopbits( port, stopb );
	rc = sp_set_flowcontrol( port, SP_FLOWCONTROL_NONE );

	return( rc == SP_OK ) ? PISTA_OK : PISTA_ERR;
}

int LspCOMM::open( ) {

   	int rc = sp_open( port, SP_MODE_WRITE );
   	if( rc != SP_OK ) {
       	std::cerr << "Could not open port " << port << std::endl;
		// throw error
   	}

	return ( rc == SP_OK ) ? PISTA_OK : PISTA_ERR;
}

int LspCOMM::write( const char buf[], size_t len) { 
    std::cout << "lspcomm writing: " << port << std::endl;

	int rc = sp_blocking_write( port, buf, len, 500); 
	return ( rc == len ) ? PISTA_OK : PISTA_ERR;
}

int LspCOMM::close( ) { 
	int rc = sp_close( port ); 
	return ( rc == SP_OK ) ? PISTA_OK : PISTA_ERR;
}

void LspCOMM::test( PistaDev *dev ) {
	// struct pista_dev_driver *dev = di->driver;
#ifdef _DEBUG_TEST

	char buf[128];

	time_t t0 = 0;
	int ticks = 0;
	do {
		int n = sp_blocking_read( port, buf, 128, 1000 );
		std::cout << "*" << n << "*" << std::flush;

        if( n <= 0 ) {
            std::cerr << "NO DATA: " << n << std::endl;
            break;
        }
		if( n > 0 ) {
			dev->handle( buf, n );
		}
		int dt = time(NULL) - t0;
		if( dt > 1 ) {
			dev->tick( );
			t0 = time(NULL);
			ticks++;
		}
	} while( ticks < 100 );
#endif

}
