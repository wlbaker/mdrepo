
#include "U3Driver.h"

int main( int argc, char *argv[] ) {

	U3Driver driver;

	driver.setConfig();

	driver.connect();
	for( int i =0; i < 20; i++ ) {
		driver.read();
	}
	driver.disconnect();
}
