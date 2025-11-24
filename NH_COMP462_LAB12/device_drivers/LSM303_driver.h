#pragma once
#include <stdint.h>

// Assuming that each axis data is 2 bytes and we are reading all three axes
#define COMPASS_I2C_ADDRESS 0x1E  // Assuming the I2C address of the compass is 0x1E
#define COMPASS_REGISTER    0x03  // Assuming we are reading from register 0x03
#define DATA_BYTES_PER_AXIS 2
#define TOTAL_DATA_BYTES    (3 * DATA_BYTES_PER_AXIS)

#define ACCEL_I2C_ADDRESS   0x19  // Assuming the I2C address of the Accelerometer is 0x19
#define ACCEL_REGISTER      0x28  // Assuming we are reading from register 0..5

typedef struct lsm303 {
    int16_t ax, ay, az;
    int16_t mx, my, mz;
    uint8_t data[6];

    int heading;
} LSM303;

LSM303 LSM303Init(void);

void LSM303ReadCompass(LSM303*);

void LSM303ReadAccelerometer(LSM303*);

int LSM303CalculateHeading(LSM303* device);
