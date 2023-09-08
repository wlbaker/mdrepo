
#include <stdio.h>

#include <linux/i2c-dev.h>

int void read_adc( int file ) {

    char buf[10] = {0};
    float data;
    char channel;

    for (int i = 0; i<4; i++) {
        // Using I2C Read
        if (read(file,buf,2) != 2) {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to read from the i2c bus.\n");
            buffer = g_strerror(errno);
            printf(buffer);
            printf("\n\n");
        } else {
            data = (float)((buf[0] & 0b00001111)<<8)+buf[1];
            data = data/4096*5;
            channel = ((buf[0] & 0b00110000)>>4);
            printf("Channel %02d Data:  %04f\n",channel,data);
        }
    }
}

int main(int argc, char *argv[] ) {

    int file;
    int adapter_nr = 2; /* probably dynamically determined */
    char filename[20];
       
    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
	if (file < 0) {
                   /* ERROR HANDLING; you can check errno to see what went wrong */
       exit(1);
    }

    int addr = 0x40; /* The I2C address */

    if (ioctl(file, I2C_SLAVE, addr) < 0) {
            /* ERROR HANDLING; you can check errno to see what went wrong */
            exit(1);
    }

    __u8 reg = 0x10; /* Device register to access */
    __s32 res;
    char buf[10];

    /* Using SMBus commands */
    res = i2c_smbus_read_word_data(file, reg);
    if (res < 0) {
      /* ERROR HANDLING: i2c transaction failed */
    } else {
      /* res contains the read word */
    }

    /* Using I2C Write, equivalent of 
     i2c_smbus_write_word_data(file, reg, 0x6543) */
    buf[0] = reg;
    buf[1] = 0x43;
    buf[2] = 0x65;
    if (write(file, buf, 3) != 3) {
      /* ERROR HANDLING: i2c transaction failed */
    }

    /* Using I2C Read, equivalent of i2c_smbus_read_byte(file) */
    if (read(file, buf, 1) != 1) {
      /* ERROR HANDLING: i2c transaction failed */
    } else {
      /* buf[0] contains the read byte */
    }
}


