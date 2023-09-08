/*
 * bmp180.h
 *
 * Bosch BMP180 Temperature/Pressure module
 *
 */

#ifndef BMP180_H_
#define BMP180_H_


#include <stdint.h>


struct bmp180_context {

	int file;
	int bus, address;

	float temperature;
	float pressure;

		int16_t AC1,AC2,AC3,VB1,VB2,MB,MC,MD;
		uint16_t AC4,AC5,AC6; 
		float    c5,c6,mc,md,x0,x1,x2,y0,y1,y2,p0,p1,p2;
		char _error;

};

int bmp180_connect( struct bmp180_context *ctx);

char bmp180_startTemperature(struct bmp180_context *ctx);
char bmp180_getTemperature(struct bmp180_context *ctx, float *T);
char bmp180_startPressure(struct bmp180_context *ctx, char oversampling);
char bmp180_getPressure(struct bmp180_context *ctx, float *p, float t);
float bmp180_sealevel(struct bmp180_context *ctx, float P, float A);
float bmp180_altitude(struct bmp180_context *ctx, float P, float P0);


int bmp180_disconnect( struct bmp180_context *ctx);


#endif

