
/* smbus_access read or write markers */
#define I2C_SMBUS_READ  1
#define I2C_SMBUS_WRITE 0

/* SMBus transaction types (size parameter in the above functions)
   Note: these no longer correspond to the (arbitrary) PIIX4 internal codes! */
#define I2C_SMBUS_QUICK             0
#define I2C_SMBUS_BYTE              1
#define I2C_SMBUS_BYTE_DATA         2
#define I2C_SMBUS_WORD_DATA         3
#define I2C_SMBUS_PROC_CALL         4
#define I2C_SMBUS_BLOCK_DATA        5
#define I2C_SMBUS_I2C_BLOCK_BROKEN  6
#define I2C_SMBUS_BLOCK_PROC_CALL   7           /* SMBus 2.0 */
#define I2C_SMBUS_I2C_BLOCK_DATA    8

#define I2C_SMBUS_BLOCK_MAX     32      /* As specified in SMBus standard */
#define I2C_SMBUS_I2C_BLOCK_MAX 32      /* Not specified but we use same structure */
union i2c_smbus_data {
        __u8 byte;
        __u16 word;
        __u8 block[I2C_SMBUS_BLOCK_MAX + 2]; /* block[0] is used for length */
                                                                                /* and one more for PEC */
};



static inline __s32 i2c_smbus_access(int file, char read_write, __u8 command,
                                     int size, union i2c_smbus_data *data)
{
        struct i2c_smbus_ioctl_data args;

        args.read_write = read_write;
        args.command = command;
        args.size = size;
        args.data = data;
        return ioctl(file,I2C_SMBUS,&args);
}




static inline __s32 i2c_smbus_read_byte_data(int file, __u8 command)
{
        union i2c_smbus_data data;
        if (i2c_smbus_access(file,I2C_SMBUS_READ,command,
                             I2C_SMBUS_BYTE_DATA,&data))
                return -1;
        else
                return 0x0FF & data.byte;
}

static inline __s32 i2c_smbus_write_byte_data(int file, __u8 command,
                                              __u8 value)
{
        union i2c_smbus_data data;
        data.byte = value;
        return i2c_smbus_access(file,I2C_SMBUS_WRITE,command,
                                I2C_SMBUS_BYTE_DATA, &data);
}


static inline __s32 i2c_smbus_read_word_data(int file, __u8 command)
{
        union i2c_smbus_data data;
        if (i2c_smbus_access(file,I2C_SMBUS_READ,command,
                             I2C_SMBUS_WORD_DATA,&data))
                return -1;
        else
                return 0x0FFFF & data.word;
}

/* Returns the number of read bytes */
/* Until kernel 2.6.22, the length is hardcoded to 32 bytes. If you
   ask for less than 32 bytes, your code will only work with kernels
   2.6.23 and later. */
static inline __s32 i2c_smbus_read_i2c_block_data(int file, __u8 command,
                                                  __u8 length, __u8 *values)
{
        union i2c_smbus_data data;
        int i;

        if (length > 32)
                length = 32;
        data.block[0] = length;
        if (i2c_smbus_access(file,I2C_SMBUS_READ,command,
                             length == 32 ? I2C_SMBUS_I2C_BLOCK_BROKEN :
                              I2C_SMBUS_I2C_BLOCK_DATA,&data))
                return -1;
        else {
                for (i = 1; i <= data.block[0]; i++)
                        values[i-1] = data.block[i];
                return data.block[0];
        }
}


