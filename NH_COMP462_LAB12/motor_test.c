#include <stdint.h>
#include <stdbool.h>

#include "tiva_launchpad_lib.h"


// PWM Init
// Enable PWM Clock
// Bit 20 of RCC reg to select freq divider
// PWMn_CTL register for enabling generator


void motor_test(void)
{
    GPIOEnableClock("BE");
    GPIODigitalEnable("E5");
    GPIODigitalEnable("B1");
    GPIOPinMode("E5", GPIO_OUT);
    GPIOPinMode("B1", GPIO_OUT);


    UART_INFO uart0 = UARTInit(0, 115200, 16000000);

    //uint32_t value = 0;
    //char str[20];

    GPIODigitalWrite("E5", GPIO_HIGH);
    GPIODigitalWrite("B1", GPIO_HIGH);

    while(1) {
        //value = ADCInSeq3(adc0);
        //snprintf(str, sizeof(str), "%d\n\r", (int)value);

        UARTprintf(uart0, "test\n\r");
    }
}
