
// #include <ctime>
#include <iostream>
#include <unistd.h>
// #include <protobuf-c/protobuf-c.h>

#include "pista-cl.h"

using namespace std;

class DumpingEventHandler : public PistaEventHandler {
	int event( PistaDev *dev, PistaDataPacket *pkt ) {
		cout << "dumping event handler got data block [" << pkt->getStreamID() << "]" << endl;
		for( int i = 0; i < pkt->getDescriptorCount() ; i++ ) {
			int count = pkt->getDescriptorSize( i );
			int typ = pkt->getDescriptorSubtyp( i );

	    	cout << "  " << pkt->getDescriptorLoc(i);
			if( typ == FLOAT_ARR_TYP ) {
				float *arr = pkt->getFloatArray( i );
				cout << "--fltarr =" << count << " [0]=" << arr[0] << " [1]=" << arr[1] << endl;
			} else if (typ == INT_ARR_TYP ) {
				int *arr = pkt->getIntArray( i );
				cout << "--intarr =" << count << " [0]=" << arr[0] << " [1]=" << arr[1] << endl;
			} else if (typ == INT_TYP ) {
				int val = pkt->getInt( i );
				cout << "--int    =" << val << endl;
			} else if (typ == FLOAT_TYP ) {
				float val = pkt->getFloat( i );
				cout << "--float =" << val << endl;
			} else {
				cout << "   skipping typ=" << typ << endl;
			}
		}
		return 0;
	}
};

int main(int argc, char* argv[])
{
	const char *driver_name="lju3";
	driver_name="mccul";
	driver_name="simu";
	driver_name="bmp180";

	cout << "creating pista context" << endl;
	PistaCl &cl = PistaCl::getInstance( );
	cl.run( );

	cout << "creating driver: " << driver_name << endl;
	PistaDriver *driver = cl.driver(driver_name);

	cout << "creating device" << endl;
	PistaDev *dev = driver->allocate();

	PistaEventHandler *h = new DumpingEventHandler();

	dev->attach(h);
	int rc = dev->connect();
	if( rc != PISTA_OK ) {
		cerr << "Could not connect.... rc=" << rc << endl;
		return -1;
	}

	::sleep(10);
	cout << "finished wait" << endl;


	dev->disconnect();

	// driver->release( dev );
	cl.stop( );

    cout << "sleeping 10 sec...." << endl;

	::sleep(10);
	cout << "finished" << endl;

}

