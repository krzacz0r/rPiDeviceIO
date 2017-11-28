#include "i2c.h"

#include <errno.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>

using namespace std;

I2C::I2C(const unsigned char& addr):
    _addr(addr)
{
    if(setup())
    {
        throw runtime_error("Can`t setup I2C!");
    }
}

I2C::~I2C()
{
}

int32_t I2C::setup()
{
    //----- OPEN THE I2C BUS -----
    char *filename = (char*)"/dev/i2c-1";
    if((_file_i2c = open(filename, O_RDWR)) < 0)
    {
        cerr << "Failed to open the I2C bus" << endl;
        cerr << "errno = " << errno << endl;

        return errno;
    }

    if(ioctl(_file_i2c, I2C_SLAVE, _addr) < 0)
    {
        cerr << "Failed to acquire bus access and/or talk to slave" << endl;
        cerr << "errno = " << errno << endl;

        return errno;
    }

    return 0;
}

bool I2C::read(const unsigned char& reg, unsigned char* buf, uint8_t len)
{
    uint8_t res = i2c_smbus_read_i2c_block_data(_file_i2c, reg, len, buf);

    if(res != len)
    {
        cerr << "Failed to read from the I2C bus" << endl;
        cerr << "I2C bus error code is " << res << endl;
    }

    return res == len;
}

bool I2C::write(const unsigned char& reg, unsigned char* buf, uint8_t len)
{
    int32_t res = i2c_smbus_write_i2c_block_data(_file_i2c, reg, len, buf);

    if(res < 0)
    {
        cerr << "Failed to write to the I2C bus" << endl;
        cerr << "I2C bus error code is " << res << endl;
    }

    return res == 0;
}

//TODO: I2C bus error handling
