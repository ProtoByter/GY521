#pragma once
//
//    FILE: GY521.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for I2C GY521 accelerometer-gyroscope sensor
//     URL: https://github.com/RobTillaart/GY521
//
// HISTORY:
// see GY521.cpp file
//

#include "Arduino.h"
#include "Wire.h"

#define GY521_LIB_VERSION (F("0.1.1"))

#ifndef GY521_THROTTLE_TIME
#define GY521_THROTTLE_TIME   10   // milliseconds
#endif

// ERRORCODES getRaw()
#define GY521_OK                0
#define GY521_THROTTLED         1
#define GY521_ERROR_READ       -1
#define GY521_ERROR_WRITE      -2


class GY521
{
public:
    GY521(uint8_t address = 0x69); // 0x68 or 0x69

    bool wakeup();
    // throttle to force delay between reads.
    void setThrottle(bool throttle = true) { _throttle = throttle; };
    bool getThrottle() { return _throttle; };
    int read();

    // as = 0,1,2,3 ==> 2g 4g 8g 16g
    void  setAccelSensitivity(uint8_t as);
    float getAccelX()   { return _ax; };
    float getAccelY()   { return _ay; };
    float getAccelZ()   { return _az; };
    float getAngleX()   { return _aax; };
    float getAngleY()   { return _aay; };
    float getAngleZ()   { return _aaz; };

    float getTemperature() { return _temperature; };

    // gs = 0,1,2,3  ==>  250, 500, 1000, 2000 degrees/second
    void  setGyroSensitivity(uint8_t gs);
    float getGyroX()    { return _gx; };
    float getGyroY()    { return _gy; };
    float getGyroZ()    { return _gz; };

    float getPitch()    { return _pitch; };
    float getRoll()     { return _roll; };
    float getYaw()      { return _yaw; };

    uint32_t lastTime() { return _lastTime; };

    // generic worker to get access to all fucntionality
    uint8_t setRegister(uint8_t reg, uint8_t value);
    uint8_t getRegister(uint8_t reg);

    // callibration errors
    float    axe = 0, aye = 0, aze = 0;  // accelerometer errors
    float    gxe = 0, gye = 0, gze = 0;  // gyro errors

private:
    uint8_t  _address;                // I2C address
    bool     _throttle = true;        // to prevent reading too fast
    uint32_t _lastTime = 0;           // to measure duration for math & throttle

    uint8_t  _afs = 0;                // sensitivity factor
    float    _raw2g = 1/16384.0;      // raw data to gravity g's
    float    _ax, _ay, _az;           // accelerometer raw
    float    _aax, _aay, _aaz;        // accelerometer processed

    uint8_t  _gfs = 0;
    float    _raw2dps = 1/131;
    float    _gx, _gy, _gz;           // gyro raw
    float    _gax, _gay, _gaz;        // gyro processed.
    float    _pitch, _roll, _yaw;     // used by user

    float    _temperature = 0;
};


// END OF FILE