#include <stdio.h>
#include <unistd.h>  // sleep functions
#include "bmp180.h"

int main(int argc, char *argv[]){

	float T, P;

	struct bmp180_context bmp180;
	bmp180.bus = 1;
	bmp180.address = 0x77;
	bmp180_connect(&bmp180 );

	for(;;) {
		bmp180_startTemperature(&bmp180);
		sleep(1);
		bmp180_getTemperature(&bmp180, &T);
		bmp180_startPressure(&bmp180, 3);
		sleep(1);
		bmp180_getPressure(&bmp180, &P, T);

		sleep(1);

		printf( "Current temp and pressure: %f,%f\n", T, P );
	}

	bmp180_disconnect(&bmp180);

	return 0;
}


