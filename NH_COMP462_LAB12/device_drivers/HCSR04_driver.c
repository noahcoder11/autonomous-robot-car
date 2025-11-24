#include <stdbool.h>
#include "tiva_launchpad_lib.h"
#include "driverlib/sysctl.h"
#include "HCSR04_driver.h"

HCSR04 HCSR04Init(char* trig, char* echo) {
    HCSR04 sensor = { trig, echo };

    char str[3];
    str[0] = sensor.trig[0];
    str[1] = sensor.echo[0];
    str[2] = '\0';

    // Enable clock on the ports
    GPIOEnableClock(str);

    // Unlock the pins if needed
    GPIOUnlock(sensor.trig);
    GPIOUnlock(sensor.echo);

    GPIODigitalEnable(sensor.trig);
    GPIODigitalEnable(sensor.echo);

    GPIOPinMode(sensor.trig, GPIO_OUT);
    GPIOPinMode(sensor.echo, GPIO_IN);

    sensor.dist = 4000000;

    return sensor;
}

uint32_t HCSR04ReadDistance(HCSR04* sensor) {
    uint32_t start_t, rise_t, fall_t, delta_t, dist;

    GPIODigitalWrite(sensor->trig, GPIO_HIGH);

    SysCtlDelay(10 * one_micro_second);

    GPIODigitalWrite(sensor->trig, GPIO_LOW);

    start_t = NVIC_ST_CURRENT_R; // Started waiting for echo

    while (GPIODigitalRead(sensor->echo) == 0) {
        if((start_t - NVIC_ST_CURRENT_R) > one_tenth_sec) {
            return -1;
        }
    }

    rise_t = NVIC_ST_CURRENT_R;

    while (GPIODigitalRead(sensor->echo) != 0) {
        if((rise_t - NVIC_ST_CURRENT_R) > 35 * one_milli_sec) {
            return -1;
        }
    }

    fall_t = NVIC_ST_CURRENT_R;

    delta_t = rise_t - fall_t;

    sensor->dist = (34UL * delta_t) / 32000UL;

    return dist;
}
