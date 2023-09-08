/*
 * bma180.h
 *
 * Definition of a class to interface with the Bosch BMA180 3 Axis Accelerometer
 * over the I2C bus
 *
 */

#ifndef BMA180ACCELEROMETER_H_
#define BMA180ACCELEROMETER_H_


#define BMA180_I2C_BUFFER 256

typedef enum {
	PLUSMINUS_1_G 		= 0,
	PLUSMINUS_1POINT5_G = 1,
	PLUSMINUS_2G 		= 2,
	PLUSMINUS_3G 		= 3,
	PLUSMINUS_4G 		= 4,
	PLUSMINUS_8G 		= 5,
	PLUSMINUS_16G 		= 6
} BMA180_RANGE;

typedef enum {
	BW_10HZ 	= 0,
	BW_20HZ 	= 1,
	BW_40HZ 	= 2,
	BW_75HZ 	= 3,
	BW_150HZ 	= 4,
	BW_300HZ 	= 5,
	BW_600HZ 	= 6,
	BW_12OOHZ 	= 7,
	BW_HIGHPASS = 8,
	BW_BANDPASS = 9
} BMA180_BANDWIDTH;

typedef enum {
	MODE_LOW_NOISE = 0,
	MODE_LOW_POWER = 3
} BMA180_MODECONFIG;


struct bma180_context {

	int I2CBus, I2CAddress;
	char dataBuffer[BMA180_I2C_BUFFER];

	int accelX;
	int accelY;
	int accelZ;

	double pitch;  //in degrees
	double roll;   //in degrees

	float temperature; //accurate to 0.5C
	BMA180_RANGE range;
	BMA180_BANDWIDTH bandwidth;
	BMA180_MODECONFIG modeConfig;

};

int bma180_writeI2CDeviceByte(struct bma180_context *ctx, char address, char value);
void bma180_calculatePitchAndRoll(struct bma180_context *ctx);
int bma180_convertAccel(struct bma180_context *ctx, int msb_reg_addr, int lsb_reg_addr);

void bma180_init( struct bma180_context *ctx, int bus, int address);
void bma180_displayMode(struct bma180_context *ctx, int iterations);

int  bma180_readFullSensorState(struct bma180_context *ctx );
// The following do physical reads and writes of the sensors
int bma180_setRange(struct bma180_context *ctx, BMA180_RANGE range);
BMA180_RANGE bma180_getRange(struct bma180_context *ctx );
int bma180_setBandwidth(struct bma180_context *ctx, BMA180_BANDWIDTH bandwidth);
BMA180_BANDWIDTH bma180_getBandwidth(struct bma180_context *ctx );
int bma180_setModeConfig(struct bma180_context *ctx, BMA180_MODECONFIG mode);
BMA180_MODECONFIG bma180_getModeConfig(struct bma180_context *ctx );
float bma180_getTemperature(struct bma180_context *ctx );

int bma180_destroy( struct bma180_context *ctx);


#endif

