#include <stdbool.h>
#include "LSM303_driver.h"
#include "driverlib/i2c.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "../i_trig.h"

const int x_offset = 52;
const int y_offset = 12;

void InitializeI2C(void){
    UARTprintf("\nInitializing I2C...\n");
    // Enable the peripherals for I2C3 and GPIOD
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Wait for the peripherals to be ready
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C3) || !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));
    UARTprintf("Peripherals ready...\n");

    // Corrected pin configuration for I2C3
    GPIOPinConfigure(GPIO_PD0_I2C3SCL);
    GPIOPinConfigure(GPIO_PD1_I2C3SDA);
    GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);
    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);

    // Initialize and configure the I2C3 master module
    I2CMasterInitExpClk(I2C3_BASE, SysCtlClockGet(), false);  // false = standard mode (100kbps)
    UARTprintf("I2C Initialization Complete...\n");
}

void ConfigureCompass(void){
    UARTprintf("\nConfiguring compass...");
    // Set the slave address and specify that the next operation is a write
    I2CMasterSlaveAddrSet(I2C3_BASE, COMPASS_I2C_ADDRESS, false);

    // Write to Configuration Register A
    I2CMasterDataPut(I2C3_BASE, 0x00);  // Address of Configuration Register A
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C3_BASE));
    I2CMasterDataPut(I2C3_BASE, 0x14);  // Configuration data DR=5=30 hZ
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C3_BASE));

    // Write to Configuration Register B
    I2CMasterDataPut(I2C3_BASE, 0x01);  // Address of Configuration Register B
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C3_BASE));
    I2CMasterDataPut(I2C3_BASE, 0x00);  // Configuration data gn=0=1300
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C3_BASE));

    // Write to Mode Register
    I2CMasterDataPut(I2C3_BASE, 0x02);  // Address of Mode Register
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C3_BASE));
    I2CMasterDataPut(I2C3_BASE, 0x00);  // Configuration data MD=0 = continuous
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C3_BASE));
    UARTprintf("Done.");
}

void ConfigureAccelerometer(void) {
    UARTprintf("\nConfiguring accelerometer...");
    // Set the slave address and specify that the next operation is a write
    I2CMasterSlaveAddrSet(I2C3_BASE, ACCEL_I2C_ADDRESS, false);

    // Write to Control Register 1 0x20 0x47
    I2CMasterDataPut(I2C3_BASE, 0x20);  // Address of Configuration Register A
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C3_BASE));
    I2CMasterDataPut(I2C3_BASE, 0x47);  //
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C3_BASE));

    // Write to Control Register 2 0x21 0x00
    I2CMasterDataPut(I2C3_BASE, 0x21);  // Address of Configuration Register B
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C3_BASE));
    I2CMasterDataPut(I2C3_BASE, 0x00);  // Configuration data gn=0=1300
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C3_BASE));

    // Write to control register 3 0x22 0x00
    I2CMasterDataPut(I2C3_BASE, 0x22);  // Address of Mode Register
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C3_BASE));
    I2CMasterDataPut(I2C3_BASE, 0x00);  // Configuration data MD=0 = continuous
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C3_BASE));

    // Write to Control Register 4 0x23 0x00
    I2CMasterDataPut(I2C3_BASE, 0x23);  // Address of Configuration Register A
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C3_BASE));
    I2CMasterDataPut(I2C3_BASE, 0x00);  //
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C3_BASE));

    // Write to Control Register 5 0x24 0x00
    I2CMasterDataPut(I2C3_BASE, 0x24);  // Address of Configuration Register B
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C3_BASE));
    I2CMasterDataPut(I2C3_BASE, 0x00);  // Configuration data gn=0=1300
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C3_BASE));

    // Write to control register 6 0x25 0x00
    I2CMasterDataPut(I2C3_BASE, 0x25);  // Address of Mode Register
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C3_BASE));
    I2CMasterDataPut(I2C3_BASE, 0x00);  // Configuration data MD=0 = continuous
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C3_BASE));
    UARTprintf("Done");
}

LSM303 LSM303Init(void){
    LSM303 device;
    device.ax = 0;
    device.ay = 0;
    device.az = 0;
    device.mx = 0;
    device.my = 0;
    device.mz = 0;
    device.heading = 0;

    InitializeI2C();
    ConfigureCompass();
    ConfigureAccelerometer();

    return device;
}

void LSM303ReadCompass(LSM303* device){
    int index = 0;

    // Set the slave address and specify that the next operation is a write
    I2CMasterSlaveAddrSet(I2C3_BASE, COMPASS_I2C_ADDRESS, false);

    // Place the register to be read into the data register
    I2CMasterDataPut(I2C3_BASE, COMPASS_REGISTER);

    // Perform a single send operation to the slave
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_SEND);

    // Wait for the send operation to complete
    while(I2CMasterBusy(I2C3_BASE));

    // Check for errors after writing to the register
    if(I2CMasterErr(I2C3_BASE) != I2C_MASTER_ERR_NONE){
        return;
    }

    // Set the slave address and specify that the next operation is a read
    I2CMasterSlaveAddrSet(I2C3_BASE, COMPASS_I2C_ADDRESS, true);

    // Perform a burst receive, starting with the first byte
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

    // Wait for the receive operation to complete
    while(I2CMasterBusy(I2C3_BASE));

    // Read the first byte
    device->data[index++] = I2CMasterDataGet(I2C3_BASE);

    // Read the middle bytes
    for(; index < TOTAL_DATA_BYTES - 1; ++index){
        // Continue the burst receive
        I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        while(I2CMasterBusy(I2C3_BASE));
        device->data[index] = I2CMasterDataGet(I2C3_BASE);
    }

    // Finish the burst receive
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(I2C3_BASE));
    device->data[index] = I2CMasterDataGet(I2C3_BASE);

    // Check for errors after reading the data
    if(I2CMasterErr(I2C3_BASE) != I2C_MASTER_ERR_NONE){
        return;
    }

    // Assume the data is in the format X MSB, X LSB, Z MSB, Z LSB, Y MSB, Y LSB
    device->mx = (device->data[0] << 8) | device->data[1];
    device->mz = (device->data[2] << 8) | device->data[3];
    device->my = (device->data[4] << 8) | device->data[5];
}

void LSM303ReadAccelerometer(LSM303* device) {
    int index = 0;
    // Set the slave address and specify that the next operation is a write
    I2CMasterSlaveAddrSet(I2C3_BASE, ACCEL_I2C_ADDRESS, false);

    // Place the register to be read into the data register
    I2CMasterDataPut(I2C3_BASE, ACCEL_REGISTER | 0x80); // MSB means auto-incr

    // Perform a single send operation to the slave
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_SEND);

    // Wait for the send operation to complete
    while(I2CMasterBusy(I2C3_BASE));

    // Check for errors after writing to the register
    if(I2CMasterErr(I2C3_BASE) != I2C_MASTER_ERR_NONE){
        return;
    }

    // Set the slave address and specify that the next operation is a read
    I2CMasterSlaveAddrSet(I2C3_BASE, ACCEL_I2C_ADDRESS, true);

    // Perform a burst receive, starting with the first byte
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

    // Wait for the receive operation to complete
    while(I2CMasterBusy(I2C3_BASE));

    // Read the first byte
    device->data[index++] = I2CMasterDataGet(I2C3_BASE);

    // Read the middle bytes
    for(; index < TOTAL_DATA_BYTES - 1; ++index){
        // Continue the burst receive
        I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        while(I2CMasterBusy(I2C3_BASE));
        device->data[index] = I2CMasterDataGet(I2C3_BASE);
    }

    // Finish the burst receive
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(I2C3_BASE));
    device->data[index] = I2CMasterDataGet(I2C3_BASE);

    // Check for errors after reading the data
    if(I2CMasterErr(I2C3_BASE) != I2C_MASTER_ERR_NONE){
        return;
    }

    // Assume the data is in the format X LSB, X MSB, Y LSB, Y MSB, Z LSB, Z MSB
    device->ax = (device->data[1] << 8) | (device->data[0]);
    device->ay = (device->data[3] << 8) | (device->data[2]);
    device->az = (device->data[5] << 8) | (device->data[4]);
}

int LSM303CalculateHeading(LSM303* device) {
    LSM303ReadCompass(device);
    device->heading = i_atan2(device->my, device->mx); // Calculate heading in degrees using the x and y values and offsets

    return device->heading;
}
