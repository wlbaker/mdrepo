/*
 * bma180.c
 *
 * Interface for the Bosch BMA180 3 Axis Accelerometer
 * over the I2C bus
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
#include "bmp180.h"


// #define _USE_MATH_DEFINES 
#include <math.h>

#define MAX_BUS 64


#define ACC_X_LSB 	0x02
#define ACC_X_MSB 	0x03
#define ACC_Y_LSB 	0x04
#define ACC_Y_MSB 	0x05
#define ACC_Z_LSB 	0x06
#define ACC_Z_MSB 	0x07
#define TEMP	  	0x08  //Temperature
#define RANGE	  	0x35  //bits 3,2,1
#define BANDWIDTH 	0x20  //bits 7,6,5,4
#define MODE_CONFIG 0x30  //bits 1,0


int bma180_getAccelX(struct bma180_context *ctx) { return ctx->accelX; }
int bma180_getAccelY(struct bma180_context *ctx) { return ctx->accelY; }
int bma180_getAccelZ(struct bma180_context *ctx) { return ctx->accelZ; }

float bma180_getPitch(struct bma180_context *ctx) { return ctx->pitch; }  // in degrees
float bma180_getRoll(struct bma180_context *ctx) { return ctx->roll; }  // in degrees

void bma180_init(struct bma180_context *ctx, int bus, int address) {
	ctx->I2CBus = bus;
	ctx->I2CAddress = address;
	memset( ctx->dataBuffer, '.', sizeof( ctx->dataBuffer ) );
	bma180_readFullSensorState(ctx);
}

int bma180_readFullSensorState(struct bma180_context *ctx){

    unsigned long funcs;

    char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", ctx->I2CBus);

    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            fprintf(stderr, "Failed to open BMA180 Sensor on %s\n", namebuf );
            return 1;
    }

    if (ioctl(file, I2C_FUNCS, &funcs) < 0){
            fprintf(stderr, "Failed to get funcs on %s\n", namebuf );
            return 1;
    }

    if (ioctl(file, I2C_SLAVE, ctx->I2CAddress) < 0){
            fprintf(stderr, "I2C_SLAVE address failed: %d\n", ctx->I2CAddress );
            return 2;
    }

    // According to the BMA180 datasheet on page 59, you need to send the first address
    // in write mode and then a stop/start condition is issued. Data bytes are
    // transferred with automatic address increment.

    if( i2c_smbus_write_byte( file, 0 ) ) {
    	fprintf(stderr, "Failed to Reset Address in readFullSensorState()\n");
    }


    for(int pos =0; pos < BMA180_I2C_BUFFER; pos++ ) {
    	int res = i2c_smbus_read_byte_data(file, pos);
	if( res < 0 ) {
    		fprintf(stderr, "FAIL[%d]: %d!\n", pos, res );
	}
	ctx->dataBuffer[pos] = res;

	if( pos % 16 == 0 ) {
    		printf( "\n" );
	}
    	printf( " %2.2x", res );
	fflush(stdout);

    }

    close(file);

    if (ctx->dataBuffer[0]!=0x03){
    	fprintf(stderr, "MAJOR FAILURE: DATA WITH BMA180 HAS LOST SYNC!\n");
    } else {
    	ctx->accelX = bma180_convertAccel(ctx, ACC_X_MSB, ACC_X_LSB);
    	ctx->accelY = bma180_convertAccel(ctx, ACC_Y_MSB, ACC_Y_LSB);
    	ctx->accelZ = bma180_convertAccel(ctx, ACC_Z_MSB, ACC_Z_LSB);
    	bma180_calculatePitchAndRoll(ctx);

    	printf( "Pitch: %f  Roll: %f\n", ctx->pitch, ctx->roll);
    }
    exit(0);
    return 0;
}

void bma180_calculatePitchAndRoll(struct bma180_context *ctx) {

	double axSQ = ctx->accelX * ctx->accelX;
	double aySQ = ctx->accelY * ctx->accelY;
	double azSQ = ctx->accelZ * ctx->accelZ;

	ctx->pitch = 180 * atan(ctx->accelX/sqrt(aySQ + azSQ))/M_PI;
	ctx->roll = 180 * atan(ctx->accelY/sqrt(axSQ + azSQ))/M_PI;
}


int bma180_convertAccel(struct bma180_context *ctx, int msb_reg_addr, int lsb_reg_addr){
	short temp = ctx->dataBuffer[msb_reg_addr];
	temp = (temp<<8) | ctx->dataBuffer[lsb_reg_addr];
	temp = temp>>2;
	temp = ~temp + 1;

	return temp;
}

void bma180_displayMode(struct bma180_context *ctx, int iterations){

    for(int i=0; i<iterations; i++) {
	    bma180_readFullSensorState(ctx);
	    printf("Rotation (%d, %d, %d)\n", ctx->accelX, ctx->accelY, ctx->accelZ);
    }
}

//  Temperature in 2's complement has a resolution of 0.5K/LSB
//  80h is lowest temp - approx -40C and 00000010 is 25C in 2's complement
//  ctx value is offset at room temperature - 25C and accurate to 0.5K

float bma180_getTemperature(struct bma180_context *ctx){

	int offset = -40;  // -40 degrees C
	bma180_readFullSensorState(ctx);
	char temp = ctx->dataBuffer[TEMP]; // = -80C 0b10000000  0b00000010; = +25C
	//char temp = ctx->readI2CDeviceByte(TEMP);
	//ctx->readFullSensorState();
    //char temp = ctx->dataBuffer[TEMP];
	float temperature;
	if(temp&0x80)	{
		temp = ~temp + 0b00000001;
		ctx->temperature = 128 - temp;
	}
	else {
		ctx->temperature = 128 + temp;
	}
	ctx->temperature = offset + ((float)ctx->temperature*0.5f);

	printf( "The temperature is %f\n", ctx->temperature );
	int temp_off = ctx->dataBuffer[0x37]>>1;
	printf( "Temperature offset raw value is: %d\n", temp_off );

	return temperature;
}

BMA180_RANGE bma180_getRange(struct bma180_context *ctx){
	bma180_readFullSensorState(ctx);
	char temp = ctx->dataBuffer[RANGE];
	//char temp = ctx->readI2CDeviceByte(RANGE);  //bits 3,2,1
	temp = temp & 0b00001110;
	temp = temp>>1;
	//cout << "The current range is: " << (int)temp << endl;
	ctx->range = (BMA180_RANGE) temp;
	return ctx->range;
}

int bma180_setRange(struct bma180_context *ctx, BMA180_RANGE range){
	//char current = ctx->readI2CDeviceByte(RANGE);  //bits 3,2,1
	bma180_readFullSensorState(ctx);
	char current = ctx->dataBuffer[RANGE];
	char temp = range << 1; //move value into bits 3,2,1
	current = current & 0b11110001; //clear the current bits 3,2,1
	temp = current | temp;
	if(bma180_writeI2CDeviceByte(ctx, RANGE, temp)!=0){
		fprintf(stderr, "Failure to update RANGE value\n");
		return 1;
	}
	return 0;
}

BMA180_BANDWIDTH bma180_getBandwidth(struct bma180_context *ctx ) {
	bma180_readFullSensorState(ctx );
	char temp = ctx->dataBuffer[BANDWIDTH];   //bits 7->4

	//char temp = ctx->readI2CDeviceByte(BANDWIDTH);  //bits 7,6,5,4
//	cout << "The value of bandwidth returned is: " << (int)temp << endl;
	temp = temp & 0b11110000;
	temp = temp>>4;

//	cout << "The current bandwidth is: " << (int)temp << endl;
	ctx->bandwidth = (BMA180_BANDWIDTH) temp;
	return ctx->bandwidth;
}

int bma180_setBandwidth(struct bma180_context *ctx, BMA180_BANDWIDTH bandwidth){
	//char current = ctx->readI2CDeviceByte(BANDWIDTH);  //bits 7,6,5,4
	bma180_readFullSensorState(ctx );
    char current = ctx->dataBuffer[BANDWIDTH];   //bits 7->4
	char temp = bandwidth << 4; //move value into bits 7,6,5,4
	current = current & 0b00001111; //clear the current bits 7,6,5,4
	temp = current | temp;
	if(bma180_writeI2CDeviceByte(ctx, BANDWIDTH, temp)!=0){
		fprintf(stderr, "Failure to update BANDWIDTH value\n");
		return 1;
	}
	return 0;
}

BMA180_MODECONFIG bma180_getModeConfig(struct bma180_context *ctx ){
	//char temp = ctx->dataBuffer[MODE_CONFIG];   //bits 1,0
	//char temp = ctx->readI2CDeviceByte(MODE_CONFIG);  //bits 1,0

	bma180_readFullSensorState(ctx );
    char temp = ctx->dataBuffer[MODE_CONFIG];
	temp = temp & 0b00000011;

	//cout << "The current mode config is: " << (int)temp << endl;
	ctx->modeConfig = (BMA180_MODECONFIG) temp;
	return ctx->modeConfig;
}

int bma180_writeI2CDeviceByte(struct bma180_context *ctx, char address, char value){

    printf( "Starting BMA180 I2C sensor state write\n");
    char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", ctx->I2CBus);
    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            fprintf(stderr, "Failed to open BMA180 Sensor on %s I2C Bus\n", namebuf);
            return(1);
    }
    if (ioctl(file, I2C_SLAVE, ctx->I2CAddress) < 0){
            fprintf(stderr, "I2C_SLAVE address %d failed\n", ctx->I2CAddress );
            return(2);
    }

    // need to set the ctrl_reg0 ee_w bit. With that set the image registers change properly.
    // need to do this or can't write to 20H ... 3Bh
    // Very Important... wrote a 0x10 to 0x0D and it worked!!!
    //   char buf[2];
    //     buf[0] = BANDWIDTH;
    //     buf[1] = 0x28;
    //     buf[2] = 0x65;
    //  if ( write(file,buf,2) != 2) {
    //	  cout << "Failure to write values to I2C Device " << endl;
    //  }

    char buffer[2];
	buffer[0] = address;
   	buffer[1] = value;

    if ( write(file, buffer, 2) != 2) {
        fprintf(stderr, "Failure to write values to I2C Device address.\n" );
        return(3);
    }
    close(file);

    printf("Finished BMA180 I2C sensor state write\n" );
    return 0;
}

/*
char readI2CDeviceByte(char address){

  //  cout << "Starting BMA180 I2C sensor state byte read" << endl;
    char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            cout << "Failed to open BMA180 Sensor on " << namebuf << " I2C Bus" << endl;
            return(1);
    }
    if (ioctl(file, I2C_SLAVE, ctx->I2CAddress) < 0){
            cout << "I2C_SLAVE address " << ctx->I2CAddress << " failed..." << endl;
            return(2);
    }

    // According to the BMA180 datasheet on page 59, you need to send the first address
    // in write mode and then a stop/start condition is issued. Data bytes are
    // transferred with automatic address increment.
    char buf[1] = { 0x00 };
    if(write(file, buf, 1) !=1){
    	cout << "Failed to Reset Address in readFullSensorState() " << endl;
    }

    char buffer[1];
    	buffer[0] = address;
    if ( read(file, buffer, 2) != 2) {
        cout << "Failure to read value from I2C Device address." << endl;
    }
    close(file);
   // cout << "Finished BMA180 I2C sensor state read" << endl;
    return buffer[0];
}*/


int bma180_destroy( struct bma180_context *ctx) {
	// TODO Auto-generated destructor stub
	return 0;
}

