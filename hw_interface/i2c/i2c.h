#ifndef I2C_H
#define I2C_H

#include "deviceio.h"

class I2C: public DeviceIO<unsigned char, unsigned char>
{
public:
    explicit I2C(const unsigned char& addr);
    virtual ~I2C();

    ///DeviceIO
    //Max length is 32 bytes
    virtual bool read(const unsigned char& reg, unsigned char* io_buf, uint8_t len) override final;
    virtual bool write(const unsigned char& reg, unsigned char* io_buf, uint8_t len) override final;

    virtual int32_t read(const unsigned char& reg) final;
    virtual int32_t write(const unsigned char& reg, const unsigned char& val) final;
    //~DeviceIO

private:
    int32_t setup();

private:
    unsigned char _addr;
    int _file_i2c = 0;
};

#endif // I2C_H
