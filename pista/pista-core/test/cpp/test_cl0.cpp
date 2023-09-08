
#include <ctime>
#include <iostream>
#include <iomanip>
#include "boost/asio.hpp"

#include "imp731.h"

using namespace std;
using namespace boost::asio;


int boost_serial_writer( HHANDLE h, const char *buf, int len) {
	serial_port *port = (serial_port *)h;

 	write( *port, buffer( buf, len ) );

	return 0;
}

int main(int argc, char* argv[])
{

	// protected member variables
	io_service io;
	serial_port port( io, "/dev/ttyUSB0");


	// init
	port.set_option( serial_port_base::baud_rate( 115200 ) );
	port.set_option( serial_port_base::character_size( 8 ) );
	port.set_option( serial_port_base::flow_control( serial_port_base::flow_control::none ) );
	port.set_option( serial_port_base::parity( serial_port_base::parity::none ) );
	port.set_option( serial_port_base::stop_bits( serial_port_base::stop_bits::one ) );
	
	PistaDev dev = new PistaDev( );
	dev.setIO( boost_serial_writer, &port );
	dev.setEvent( NULL, NULL );

	cout << "SYNC_READING" << endl;
	cout << "============" << endl;

	int pkt = 1;
	// int crc_seed = 0;
	char cc[2];
	cc[1] = '\0';
	for(;;) {
		read(port, buffer(&cc[0],1));
		IMP731_handle( hDevice, cc, 1 );	
		IMP731_tick( hDevice );
		
	}

}
