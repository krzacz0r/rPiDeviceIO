#ifndef BPS_TYPES_H
#define BPS_TYPES_H

#include <cstdint>

/*-----------------------------------------------------------------------
BAROMETER DATA TYPES
-----------------------------------------------------------------------*/
struct Temperature
{
    float value = 0.f;
};

/*-----------------------------------------------------------------------
THERMOMETER DATA TYPES
-----------------------------------------------------------------------*/
struct Pressure
{
    int32_t value = 0;
};


#endif // BPS_TYPES_H
