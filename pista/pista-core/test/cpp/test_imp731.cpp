
#include <ctime>
#include <iostream>
#include <iomanip>
#include "boost/asio.hpp"

#include "imp731.h"

using namespace std;
using namespace boost::asio;


char TEST1[] = "?1 6C 00 00 00 02 00 0A 00 00 ";  // A8
char TEST2[] = "?1 6C 00 00 00 02 00 09 00 00 ";  // 32
char TEST3[] = "?1 1B 00 00 00 02 00 04 00 00 ";  // 72
char TEST4[] = "?1 1B 00 00 00 02 00 03 00 00 ";  // F4
char TEST5[] = "?2 00000000 ";  // eb

void test_integrity() {
	int pos = 0;
/*
	TEST1[pos] = 2;
	TEST2[pos] = 2;
	TEST3[pos] = 2;
	TEST4[pos] = 2;
	TEST5[pos] = 2;
	pos++;
*/
	TEST1[pos] = GUI_STATUS;
	TEST2[pos] = GUI_STATUS;
	TEST3[pos] = GUI_STATUS;
	TEST4[pos] = GUI_STATUS;
	TEST5[pos] = HOST_MSG_ENABLE;
	pos++;

	cout << hex;
	for( int initial = 0; initial < 256; initial++ ) {
		int test1_crc = calcCRC( initial, TEST1, sizeof(TEST1) - 1 );
		int test2_crc = calcCRC( initial, TEST2, sizeof(TEST2) - 1);
		int test3_crc = calcCRC( initial, TEST3, sizeof(TEST3) - 1);
		int test4_crc = calcCRC( initial, TEST4, sizeof(TEST4) - 1);
		int test5_crc = calcCRC( initial, TEST5, sizeof(TEST5) - 1);
	
		if(test1_crc == 0xa8) {
			cout << "0x" << initial << " TEST1_CRC=" << test1_crc << " PASS" << endl;
		}
		if(test2_crc == 0x32) {
			cout << "0x" << initial << " TEST2_CRC=" << test2_crc << " PASS" << endl;
		}
		if(test3_crc == 0x72) {
			cout << "0x" << initial << " TEST3_CRC=" << test3_crc << " PASS" << endl;
		}
		if(test4_crc == 0xf4) {
			cout << "0x" << initial << " TEST4_CRC=" << test4_crc << " PASS" << endl;
		}
		if(test5_crc == 0xeb) {
			cout << "0x" << initial << " TEST5_CRC=" << test5_crc << " PASS" << endl;
		}
	}

	int test5_crc = calcCRC( CRC_SEND_SEED, TEST5, sizeof(TEST5) - 1 );
	if( test5_crc != 0xeb) {
		cout << "FAIL: CRC_SEND_SEED 0x" << hex << CRC_SEND_SEED << endl;
		// return 0;
	} else {
		cout << "PASS: CRC_SEND_SEED" << endl;
	}

	int test1_crc = calcCRC( CRC_RECV_SEED, TEST1, sizeof(TEST1) - 1 );
	if( test1_crc != 0xa8) {
		cout << "FAIL: CRC_RECV_SEED 0x" << hex << CRC_RECV_SEED << endl;
		// return 0;
	} else {
		cout << "PASS: CRC_RECV_SEED" << endl;
	}

}


int send_to_device( HHANDLE h, const char *buf, int len) {
	serial_port *port = (serial_port *)h;

 	write( *port, buffer( buf, len ) );

	return 0;
}

int main(int argc, char* argv[])
{

	test_integrity();

	// protected member variables
	io_service io;
	serial_port port( io, "/dev/ttyUSB0");


	// init
	port.set_option( serial_port_base::baud_rate( 115200 ) );
	port.set_option( serial_port_base::character_size( 8 ) );
	port.set_option( serial_port_base::flow_control( serial_port_base::flow_control::none ) );
	port.set_option( serial_port_base::parity( serial_port_base::parity::none ) );
	port.set_option( serial_port_base::stop_bits( serial_port_base::stop_bits::one ) );
	
	CHANDLE hDevice = IMP731_init( &port, send_to_device );

    // options.setBaudrate(115200);
    // options.setTimeout(seconds(3));
    // serial.exceptions(ios::badbit | ios::failbit); //Important!

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
	//read( port
    //serial>>s;
    //cout<<s<<endl;
}
