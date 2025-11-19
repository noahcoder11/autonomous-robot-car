/*#include <stdint.h>
#include <stdbool.h>
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"

#include "tiva_launchpad_lib.h"
#include "device_drivers/HCSR04_driver.h"

int main_test(void)
{
    uint32_t sysClock = MAP_SysCtlClockGet();

    HCSR04 ultra_sensor = HCSR04Init("A4", "B6");

    ConfigureUART(115200, sysClock); // sets PA0/PA1 + UART0 regs

    UARTStdioConfig(0, 115200, sysClock);

    UARTprintf("\r\nAcoustic Sensor Test Program\r\n");

    while (1) {
        uint32_t dist = HCSR04ReadDistance(ultra_sensor);

        UARTprintf("Distance: %d\n", dist);

        MAP_SysCtlDelay((sysClock/3/1000) * 500);
    }
}*/
