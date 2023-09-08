// #include <iostream>
#include "boost/asio.hpp"

#include "pista-cl.h"

using namespace boost::asio;

/* ****************************************************************************
 * BoostIO
 * ****************************************************************************/

static io_service io;

BoostCOMM::BoostCOMM( const char *portName ) {

	// protected member variables
	vp = new serial_port( io, portName );

}

int BoostCOMM::open( ) { } 
int BoostCOMM::write( const char data[], size_t len) { }

int BoostCOMM::config( int baud, int datab, int stopb, char parity) {
	serial_port *port = (serial_port *)vp;
	port->set_option( serial_port_base::baud_rate( baud ) );
	port->set_option( serial_port_base::character_size( datab ) );

	port->set_option( serial_port_base::stop_bits( serial_port_base::stop_bits::one ) );


	/*
	var p = serial_port_base::parity::none;
	switch( parity ) {
	case 'E':
	case 'e':
		p = serial_port_base::parity::even;
		break;
	case 'O':
	case 'o':
		p = serial_port_base::parity::odd;
		break;
	case 'N':
	case 'n':
		p = serial_port_base::parity::none;
		break;
	}
	port->set_option( serial_port_base::parity( p ) );
	*/
	port->set_option( serial_port_base::parity( serial_port_base::parity::none ) );

	port->set_option( serial_port_base::flow_control( serial_port_base::flow_control::none ) );

	return 0;
}

int BoostCOMM::close( ) {
	serial_port *port = (serial_port *)vp;
	
	port->close();
}

void BoostCOMM::test( PistaDev *dev ) {
	serial_port *port = (serial_port *)vp;

	char cc[2];
	cc[1] = '\0';
	for(;;) {
		read(*port, buffer(&cc[0],1));
		dev->handle( cc, 1 );	
		dev->tick( );
	}

}

