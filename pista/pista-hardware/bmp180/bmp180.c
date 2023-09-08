/*
 * bmp180.c
 *
 * Interface for the Bosch BMP180 temperature/pressure
 *
 */

#include <sys/ioctl.h>
#include <string.h> // memset
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>  // open
// #include <linux/i2c.h>
#include <linux/i2c-dev.h>
// #include <i2c/smbus.h>

#include <stdint.h>
#include "bmp180.h"
#include "pista-internal.h"

#ifdef I2C_SMBUS_READ
// assume i2c-dev.h has the expected kernel definitions
#else
// ...easy to add for convenience in user space
#include "smbutil.h"
#endif

#include <math.h>

#define LOG_PREFIX "bmp180"

#define MAX_BUS 64

#define BMP180_ADDR 0x77 // 7-bit address

#define	BMP180_REG_CONTROL 0xF4
#define	BMP180_REG_RESULT 0xF6

#define	BMP180_COMMAND_TEMPERATURE 0x2E
#define	BMP180_COMMAND_PRESSURE0 0x34
#define	BMP180_COMMAND_PRESSURE1 0x74
#define	BMP180_COMMAND_PRESSURE2 0xB4
#define	BMP180_COMMAND_PRESSURE3 0xF4

#define BMP180__BUFFER 256

static void parse_calibration_data( struct bmp180_context *ctx, const char *dataBuffer );
static int bmp180_read_calibration(struct bmp180_context *ctx);

/*
 */

int bmp180_connect(struct bmp180_context *ctx) {

    char namebuf[MAX_BUS];
    unsigned long funcs;

    snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", ctx->bus);

	pista_info("bmp180_connect() = %d --> %s", ctx->bus, namebuf );

    if ((ctx->file = open(namebuf, O_RDWR)) < 0){
            pista_err( "Failed to open BMP180 Sensor on %s", namebuf );
            return ctx->file;
    }

    if (ioctl(ctx->file, I2C_FUNCS, &funcs) < 0){
            pista_err( "Failed to get funcs on %s", namebuf );
            return -1;
    }

    if (ioctl(ctx->file, I2C_SLAVE, ctx->address) < 0){
            pista_err( "I2C_SLAVE address failed: %d", ctx->address );
            return -2;
    }

    return bmp180_read_calibration(ctx);
}

int bmp180_read_calibration(struct bmp180_context *ctx){

    int res = -3;

	char dataBuffer[BMP180__BUFFER];
    for(int pos =0; pos < BMP180__BUFFER; pos++ ) {
    	res = i2c_smbus_read_byte_data(ctx->file, pos);
	    if( res < 0 ) {
    		pista_err( "CALIB FAIL: %d", res );
            break;
	    }
	    dataBuffer[pos] = res;
    }


    if( res >= 0 ) {
        if (dataBuffer[0xd0]==0x55){
	        parse_calibration_data(ctx, dataBuffer);
            res = 0;
        } else {
    	    pista_err( "CANNOT FIND BMP180!");
            res = -3;
        }
    }

    return res;
}

#define buf_int( buf, off )  (int16_t)( buf[off]<<8 | buf[off+1] )
#define buf_uint( buf, off ) (uint16_t)( buf[off]<<8 | buf[off+1] )

static void parse_calibration_data( struct bmp180_context *ctx, const char *buf ) {

	int16_t AC1 = buf_int( buf, 0xAA );
	int16_t AC2 = buf_int( buf, 0xAC );
	int16_t AC3 = buf_int( buf, 0xAE );
	uint16_t AC4 = buf_uint( buf, 0xB0 );
	uint16_t AC5 = buf_uint( buf, 0xB2 );
	uint16_t AC6 = buf_uint( buf, 0xB4 );

	int16_t VB1 = buf_int( buf, 0xB6 );
	int16_t VB2 = buf_int( buf, 0xB8 );

	// int16_t MB = buf_int( buf, 0xBA ); // hm...unused
	int16_t MC = buf_int( buf, 0xBC );
	int16_t MD = buf_int( buf, 0xBE );

	float c3 = 160.0 * pow(2,-15) * AC3;
	float c4 = pow(10,-3) * pow(2,-15) * AC4;
	float b1 = pow(160,2) * pow(2,-30) * VB1;
	ctx->c5 = (pow(2,-15) / 160) * AC5;
	ctx->c6 = AC6;
	ctx->mc = (pow(2,11) / pow(160,2)) * MC;
	ctx->md = MD / 160.0;
	ctx->x0 = AC1;
	ctx->x1 = 160.0 * pow(2,-13) * AC2;
	ctx->x2 = pow(160,2) * pow(2,-25) * VB2;
	ctx->y0 = c4 * pow(2,15);
	ctx->y1 = c4 * c3;
	ctx->y2 = c4 * b1;
	ctx->p0 = (3791.0 - 8.0) / 1600.0;
	ctx->p1 = 1.0 - 7357.0 * pow(2,-20);
	ctx->p2 = 3038.0 * 100.0 * pow(2,-36);

#ifdef DEBUG
    printf("CALIB\n");
    printf("  AC1=%d\n", AC1 );
    printf("  AC2=%d\n", AC2 );
    printf("  AC3=%d\n", AC3 );
    printf("  AC4=%d\n", AC4 );
    printf("  AC5=%d\n", AC5 );
    printf("  AC6=%d\n", AC6 );

    printf("  VB1=%d\n", VB1 );
    printf("  VB2=%d\n", VB2 );

    // printf("  MB=%d\n", MB );
    printf("  MB=%d\n", MC );
    printf("  MD=%d\n", MD );

    printf("  mc=%f\n", ctx->mc );
    printf("  md=%f\n", ctx->md );

    printf("  x0=%f\n", ctx->x0 );
    printf("  x1=%f\n", ctx->x1 );
    printf("  x2=%f\n", ctx->x2 );

    printf("  y0=%f\n", ctx->y0 );
    printf("  y1=%f\n", ctx->y1 );
    printf("  y2=%f\n", ctx->y2 );

    printf("  p0=%f\n", ctx->p0 );
    printf("  p1=%f\n", ctx->p1 );
    printf("  p2=%f\n", ctx->p2 );
#endif
}

char bmp180_startTemperature(struct bmp180_context *ctx)
// Begin a temperature reading.
// Will return delay in ms to wait, or 0 if  error
{
	int rc;
	if( (rc = i2c_smbus_write_byte_data(ctx->file, BMP180_REG_CONTROL, BMP180_COMMAND_TEMPERATURE)) != 0 ) {
#ifdef DEBUG
		fprintf(stderr,"FAIL[%d]: temp request returned error.\n", rc);
#endif
	}

	return 0;
}


char bmp180_getTemperature(struct bmp180_context *ctx, float *T)
// Retrieve a previously-started temperature reading.
// Requires begin() to be called once prior to retrieve calibration parameters.
// Requires startTemperature() to have been called prior and sufficient time elapsed.
// T: external variable to hold result.
// Returns 1 if successful, 0 if  error.
{
	float tu, a;
	
 	int res = i2c_smbus_read_word_data(ctx->file, BMP180_REG_RESULT );
	if (res) // good read, calculate temperature
	{
		tu = ((res<<8) & 0xFF00) | ((res>>8) & 0xFF);

		//example from Bosch datasheet
		//tu = 27898;

		//example from http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf
		//tu = 0x69EC;
		
		a = ctx->c5 * (tu - ctx->c6);
		*T = a + (ctx->mc / (a + ctx->md));

#ifdef DEBUG
        printf("TU=%f\n", tu );
		printf("a: %f\n", a);
		printf("T: %f\n", *T);
        printf("T=%f\n", *T );
        printf("getTemp=%f\n", *T );
#endif
	}

	return res;
}

char bmp180_startPressure(struct bmp180_context *ctx, char oversampling)
// Begin a pressure reading.
// Oversampling: 0 to 3, higher numbers are slower, higher-res outputs.
// Will return delay in ms to wait, or 0 if  error.
{
	int delay = -1;
        int cmd = -1;
	switch (oversampling)
	{
		case 0:
			cmd = BMP180_COMMAND_PRESSURE0;
			delay = 5;
		break;
		case 1:
			cmd = BMP180_COMMAND_PRESSURE1;
			delay = 8;
		break;
		case 2:
			cmd = BMP180_COMMAND_PRESSURE2;
			delay = 14;
		break;
		case 3:
			cmd = BMP180_COMMAND_PRESSURE3;
			delay = 26;
		break;
		default:
			cmd = BMP180_COMMAND_PRESSURE0;
			delay = 5;
		break;
	}

	int rc;
	if( ( rc = i2c_smbus_write_byte_data(ctx->file, BMP180_REG_CONTROL, cmd )) != 0  ) {
#ifdef DEBUG
		fprintf(stderr,"FAIL[%d]: pressure request returned error.\n", rc);
#endif
	}

	return delay;
}


char bmp180_getPressure(struct bmp180_context *ctx, float *P, float T)
// Requires retrieval of calibration parameters (on init)
// Retrieve a previously started pressure reading, calculate abolute pressure in mbars.
// Requires startPressure() to have been called prior and sufficient time elapsed.
// Requires recent temperature reading to accurately calculate pressure.

// P: external variable to hold pressure.
// T: previously-calculated temperature.
// Returns > 0 for success, 0 for  error.

// Note that calculated pressure value is absolute mbars, to compensate for altitude call sealevel().
{
	float pu,s,x,y,z;
	__u8 data[3];
	int rc;
	
	if ( (rc = i2c_smbus_read_i2c_block_data(ctx->file, BMP180_REG_RESULT, 3,data)) ) {
		pu = (data[0] * 256.0) + data[1] + (data[2]/256.0);

		//example from Bosch datasheet
		//pu = 23843;

		//example from http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf, pu = 0x982FC0;	
		//pu = (0x98 * 256.0) + 0x2F + (0xC0/256.0);
		
		s = T - 25.0;
		x = (ctx->x2 * pow(s,2)) + (ctx->x1 * s) + ctx->x0;
		y = (ctx->y2 * pow(s,2)) + (ctx->y1 * s) + ctx->y0;
		z = (pu - x) / y;
		*P = (ctx->p2 * pow(z,2)) + (ctx->p1 * z) + ctx->p0;

#ifdef DEBUG
    printf("--> T=%f\n", T );
        printf("PU=%f\n", pu );
        printf(" S=%f\n", s );
        printf(" x=%f\n", x );
        printf(" y=%f\n", y );
        printf(" z=%f\n", z );
        printf("P=%f\n", *P );
#endif
	}

	return rc;
}


float bmp180_sealevel(struct bmp180_context *ctx, float P, float A)
// Given a pressure P (mb) taken at a specific altitude (meters),
// return the equivalent pressure (mb) at sea level.
// This produces pressure readings that can be used for weather measurements.
{
	return(P/pow(1-(A/44330.0),5.255));
}


float bmp180_altitude(struct bmp180_context *ctx, float P, float P0)
// Given a pressure measurement P (mb) and the pressure at a baseline P0 (mb),
// return altitude (meters) above baseline.
{
	return(44330.0*(1-pow(P/P0,1/5.255)));
}

int bmp180_disconnect( struct bmp180_context *ctx) {

	if( ctx->file != 0 ) {
		close( ctx->file );
		ctx->file = 0;
	}

	return 0;
}

