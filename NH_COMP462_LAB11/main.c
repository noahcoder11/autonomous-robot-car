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

#include "device_drivers/L298N_driver.h"
#include "device_drivers/HCSR04_driver.h"
#include "device_drivers/LSM303_driver.h"
#include "tiva_launchpad_lib.h"
#include "main.h"

/* =========== PIN MAPPING ===========
 * Ultrasonic left:
 * - TRIG: E0
 * - ECHO: C6
 *Ultrasonic right:
 * - TRIG: E4
 * - ECHO: E5
 * Motor Driver:
 * - IN1: GND
 * - IN2: C4
 * - IN3: C5
 * - IN4: GND
 * - ENA: 5V
 * - ENB: 5V
 * Compass:
 * - 3.3V: 3.3V
 * - GND: GND
 * - SCL: D0
 * - SDA: D1
 * Wheel Counter Left
 * - VCC: 5V
 * - GND: GND
 * -
 * Wheel Counter Right
 */

SYSTEM robot_car;
STATE current_state;

#define abs(x) ((x < 0) ? (-x) : (x))

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
    robot_car.timer = TimerInit(3);
    GPIOEnableClock("B");
    GPIOPullupEnable("B23");
    GPIOPinMode("B23", GPIO_IN);
    GPIOAfselEnable("B23", 0x7);
}

// Initialize motor pins
void MotorInit() {
    GPIOEnableClock("C");

    robot_car.pwm_gen = PWMGENInit(0, 3, 0xC0);

    GPIODigitalEnable("C45");
    GPIOPinMode("C45", GPIO_OUT);

    GPIOAfselEnable("C45", 0x4);

    robot_car.motor_driver = L298NInit(&robot_car.pwm_gen);
}

// coarse table interpolation / Lookup
// Fine Table Lookup
// Polynomial approximation
// All of the above

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
    robot_car.sonar_right = HCSR04Init("E0", "C6");
    robot_car.sonar_left = HCSR04Init("E4", "E5");
}

// Initialize compass module
void CompassInit() {
    robot_car.compass = LSM303Init();
}

// Initialize all systems
void SystemInit() {
    robot_car.clock = SysCtlClockFreqSet((SYSCTL_OSC_MAIN | SYSCTL_USE_OSC | SYSCTL_XTAL_16MHZ), 16000000);

    SysTickInit();
    ConfigureUART();
    WheelCounterInit();
    MotorInit();
    ButtonInit();
    UARTprintf("Finished button config\n");
    SonarInit();
    UARTprintf("Finished sonar config\n");
    CompassInit();
    UARTprintf("Finished compass config\n");

    GPIODigitalEnable("F23");
    GPIOPinMode("F23", GPIO_OUT);

    current_state.start_heading = LSM303CalculateHeading(&robot_car.compass);
    current_state.target_heading = current_state.start_heading;
}

int main(void)
 {
    SystemInit();

    UARTprintf("===== Noah Hester, Joseph Shumaker - Lab 10 - Sensor Response =====\r\n");

    SysCtlDelay(one_sec / 3);

    L298NSetPWM(&robot_car.motor_driver, NORMAL_SPEED, NORMAL_SPEED, 2);

    uint16_t count_left, count_right, pass = 0, pwm_a_duty_cycle = 0, pwm_b_duty_cycle = 0;

    while (1) {
        current_state.current_heading = LSM303CalculateHeading(&robot_car.compass);

        // Read timer value
        count_left = ReadTimerA(robot_car.timer);
        count_right = ReadTimerB(robot_car.timer);

        // Read left sonar
        HCSR04ReadDistance(&robot_car.sonar_left);
        // Delay between
        SysCtlDelay(60 * one_milli_sec);
        // Read right sonar
        HCSR04ReadDistance(&robot_car.sonar_right);

        // Left detect and right detect conditions for object detection
        bool left_detect = robot_car.sonar_left.dist < OBJECT_SENSE_DIST;
        bool right_detect = robot_car.sonar_right.dist < OBJECT_SENSE_DIST;

        // Adjust target heading if object is detected
        if(left_detect && !right_detect) {
            UARTprintf("Object detected on left!\n");
            //current_state.target_heading = current_state.start_heading + AVOIDANCE_ANGLE;
        }else if(!left_detect && right_detect) {
            UARTprintf("Object detected on right!\n");
            //current_state.target_heading = current_state.start_heading - AVOIDANCE_ANGLE;
        }else if(left_detect && right_detect) {
            // Check distance traveled
            //current_state.target_heading = current_state.start_heading;
        }else if(!left_detect && !right_detect) {
            // Check cross range error and correct if needed

            current_state.target_heading = current_state.start_heading;
        }

        L298NUpdatePWM(&robot_car.motor_driver);

        if(current_state.current_heading < (current_state.target_heading - CORRECTION_ANGLE) % 360) {
            L298NSetPWM(&robot_car.motor_driver, TURNING_SPEED + TURNING_DIFF, TURNING_SPEED - TURNING_DIFF, 4);
            GPIODigitalWrite("F2", GPIO_HIGH);
            GPIODigitalWrite("F3", GPIO_LOW);
        }else if(current_state.current_heading > (current_state.target_heading + CORRECTION_ANGLE) % 360) {
            L298NSetPWM(&robot_car.motor_driver, TURNING_SPEED - TURNING_DIFF, TURNING_SPEED + TURNING_DIFF, 4);
            GPIODigitalWrite("F2", GPIO_LOW);
            GPIODigitalWrite("F3", GPIO_HIGH);
        }else {
            L298NSetPWM(&robot_car.motor_driver, NORMAL_SPEED, NORMAL_SPEED, 4);
            GPIODigitalWrite("F2", GPIO_LOW);
            GPIODigitalWrite("F3", GPIO_LOW);
        }

        // Read PWM duty cycle
        pwm_a_duty_cycle = ReadPWMADutyCycle(*(robot_car.motor_driver.pwm_interface));
        pwm_b_duty_cycle = ReadPWMBDutyCycle(*(robot_car.motor_driver.pwm_interface));

        UARTprintf("Robot State: current_heading = %d, target_heading = %d, PWM A = %d, PWM B = %d\n", current_state.current_heading, current_state.target_heading, pwm_a_duty_cycle, pwm_b_duty_cycle);

        pass++;

        // 4Hz
        SysCtlDelay(one_sec / 12);
    }
}
