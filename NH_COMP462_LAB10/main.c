// main.c
// for project COMP-462 / Test of PWM and Wheel Counter / Lab 9
// 2-Nov-2025 NH implemented sensor integration
//

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"   // <-- GPIO_PA0_U0RX, GPIO_PA1_U0TX
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#include "device_drivers/HCSR04_driver.h"
#include "device_drivers/LSM303_driver.h"
#include "tiva_launchpad_lib.h"

/* =========== PIN MAPPING ===========
 * Ultrasonic left:
 * - TRIG: E0
 * - ECHO: C4
 *Ultrasonic right:
 * - TRIG: E4
 * - ECHO: E5
 * Motor Driver:
 * - IN1: GND
 * - IN2: F2
 * - IN3: F3
 * - IN4: GND
 * - ENA: 5V
 * - ENB: 5V
 * Compass:
 * - 3.3V: 3.3V
 * - GND: GND
 * - SCL: D0
 * - SDA: D1
 * Wheel Counter Left
 * -
 */

typedef struct pwmData {
    int current;
    int target;
    int step;
} PWM;

// Timer for wheel counters
TIMER_INFO timer3;
// PWM generator
PWM_GEN_INFO pwm1gen3;
// Initialize abstracted PWM type for motors
PWM motorA, motorB = { 0, 0, 0 };

char* left_button, *right_button;

// Sonar sensors
HCSR04 sonar_left, sonar_right;
// Compass module
LSM303 compass;

// Set new target PWM value and step size
void setPWM(PWM *pwm, int target, int stepSize) {
    if (pwm) {
        if(pwm->target == target) return;

        // Set new PWM target value
        pwm->target = target;
        pwm->step = stepSize;
    }else {
        UARTprintf(stderr, "ERROR: Invalid PWM object.\n");
    }
}

// Step a PWM value forwards toward its target value
int stepPWM(PWM *pwm) {
    // Step PWM forward
    pwm->current += pwm->step;

    // Adjust in case of overshooting
    if(pwm->step > 0) {
        if(pwm->current > pwm->target) {
            pwm->current = pwm->target;
            return 0;
        }else {
            return 1;
        }
    }else if(pwm->step < 0) {
        if(pwm->current < pwm->target) {
            pwm->current = pwm->target;
            return 0;
        }else {
            return 1;
        }
    }

    return 0;
}

// Handles SysTick Interrupts
void SysTickIntHandler(void) {
    return;
}

// Configure UART0
static void ConfigureUART(void) {
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC); // 16 MHz internal
    UARTStdioConfig(0, 115200, 16000000);             // PIOSC as clock
}
// Initialize wheel counter registers and pins
void WheelCounterInit() {
    timer3 = TimerInit(3);
    GPIOEnableClock("B");
    GPIOPullupEnable("B23");
    GPIOPinMode("B23", GPIO_IN);
    GPIOAfselEnable("B23", 0x7);
}
// Initialize motor pins
void MotorInit() {
    GPIOEnableClock("AF");
    pwm1gen3 = PWMGENInit(1, 3, 0xC0);

    GPIODigitalEnable("F23");
    GPIOPinMode("F23", GPIO_OUT);
    GPIODigitalEnable("A23");
    GPIOPinMode("A23", GPIO_OUT);
    GPIODigitalWrite("A23", GPIO_HIGH);

    GPIOAfselEnable("F23", 0x5);
}
// Initialize button pins
void ButtonInit() {
    GPIOEnableClock("F");
    GPIOUnlock("F0");
    GPIODigitalEnable("F04");
    GPIOPinMode("F04", GPIO_IN);
    GPIOPullupEnable("F04");
}
// Initialize sonar sensors
void SonarInit() {
    sonar_right = HCSR04Init("E0", "C4");
    sonar_left = HCSR04Init("E4", "E5");
}
// Initialize compass module
void CompassInit() {
    compass = LSM303Init();
}
// Initialize all systems
void SystemInit() {
    uint32_t sysclk = SysCtlClockFreqSet((SYSCTL_OSC_MAIN | SYSCTL_USE_OSC | SYSCTL_XTAL_16MHZ), 16000000);

    SysTickInit();
    ConfigureUART();
    WheelCounterInit();
    MotorInit();
    ButtonInit();
    UARTprintf("Finished button config\n");
    SonarInit();
    UARTprintf("Finished sonar config\n");
    //CompassInit();
    UARTprintf("Finished compass config\n");
}

int main(void)
 {
    SystemInit();

    UARTprintf("===== Noah Hester, Joseph Shumaker - Lab 10 - Sensor Response =====\r\n");

    SysCtlDelay(one_sec / 3);

    SetPWMGENA(pwm1gen3, MAX_PWM);
    SetPWMGENB(pwm1gen3, MAX_PWM);

    setPWM(&motorA, 50, 5);
    setPWM(&motorB, 50, 5);

    uint16_t count_left, count_right, pass = 0, pwm_a_duty_cycle = 0, pwm_b_duty_cycle = 0;

    while (1) {
        UARTprintf("stepping pwm\n");

        stepPWM(&motorA);
        stepPWM(&motorB);

        SetPWMADutyCycle(pwm1gen3, motorA.current);
        SetPWMBDutyCycle(pwm1gen3, motorB.current);

        UARTprintf("trigger check\n");

        bool right_trigger = (GPIODigitalRead("F0") == 0);//(sonar_right->dist >= 0 && sonar_right->dist <= 100);
        bool left_trigger = (GPIODigitalRead("F4") == 0);//(sonar_left->dist >= 0 && sonar_right->left <= 100);

        if(left_trigger && !right_trigger) {
            UARTprintf("Left\n");
            setPWM(&motorA, 25, 5);
            setPWM(&motorB, 75, 5);
        }else if(right_trigger && !left_trigger) {
            UARTprintf("Right\n");
            setPWM(&motorA, 75, 5);
            setPWM(&motorB, 25, 5);
        }else if(right_trigger && left_trigger) {
            // Check if distance traveled is far enough to be at the end
        }else if(!right_trigger && !left_trigger) {
            setPWM(&motorA, 50, 5);
            setPWM(&motorB, 50, 5);
        }

        // Read timer value
        //count_left = ReadTimerA(timer3);
        //count_right = ReadTimerB(timer3);
        // Read PWM duty cycle
        pwm_a_duty_cycle = ReadPWMADutyCycle(pwm1gen3);
        pwm_b_duty_cycle = ReadPWMBDutyCycle(pwm1gen3);

        UARTprintf("------------------------- Pass: %d -------------------------\n", pass);
        UARTprintf("PWM         | PWM A Duty Cycle: %d, PWM B Duty Cycle: %d\n", pwm_a_duty_cycle, pwm_b_duty_cycle);
        //UARTprintf("------------------------------------------------------------\n");
        //UARTprintf("WHEEL COUNT | Left Count (A):   %d, Right Count (B):  %d\n", count_left, count_right);
        //UARTprintf("------------------------------------------------------------\n");
        //UARTprintf("SONAR       | Sonar Right:      %d, Sonar Left:       %d\n", sonar_right.dist, sonar_left.dist);
        //UARTprintf("------------------------------------------------------------\n");
        //UARTprintf("COMPASS     | Compass: X: %d, Y: %d, Z: %d, Heading: %d\n", compass.mx, compass.my, compass.mz, compass.heading);
        UARTprintf("------------------------------------------------------------\n\n");

        pass++;

        // 4Hz
        SysCtlDelay(one_sec / 12);
    }
}
