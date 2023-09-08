

#include <stdio.h>
#include <math.h>


int main() {

	double sineLow = 0.040;
	double sineHigh = 0.800;
	double chirpLow = 0.000;
	double chirpHigh = 0.500;

	FILE *fp = stdout;

	for( int i = 0; i < 5000; i++ ) {
		double secs = 0.2 * i;
		double hz = chirpLow + secs*(chirpHigh-chirpLow)/1000;
		double chirp = sin( secs*2.0*M_PI*hz);

		fprintf( fp, "%f, %f, %f\n", secs, hz, chirp );
	}

	return 0;
}
