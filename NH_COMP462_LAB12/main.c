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
int pass = 0;

// Handles SysTick Interrupts
void SysTickIntHandler(void) {
    if(current_state.state == START) {
        SystemStart();

        if(GPIODigitalRead("F0") == 0 && GPIODigitalRead("F4") == 0) {
            current_state.state = RUNNING;
        }
    }else if(current_state.state == RUNNING || current_state.state == TURNING) {
        SystemRunning();
    }

    pass++;
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

// Initialize button pins
void ButtonInit() {
    // Initialize button pins as outputs
    GPIOEnableClock("F");
    GPIOUnlock("F0");
    GPIODigitalEnable("F04");
    GPIOPinMode("F04", GPIO_IN);
    GPIOPullupEnable("F04");
}

// Initialize sonar sensors
void SonarInit() {
    // Initialize the ultrasonic sensors
    robot_car.sonar_right = HCSR04Init("E0", "C6");
    robot_car.sonar_left = HCSR04Init("E4", "E5");
}

// Initialize compass module
void CompassInit() {
    // Initialize compass
    robot_car.compass = LSM303Init();
}

// Initialize all systems
void SystemInit() {
    // Set the clock to 16MHz
    robot_car.clock = SysCtlClockFreqSet((SYSCTL_OSC_MAIN | SYSCTL_USE_OSC | SYSCTL_XTAL_16MHZ), 16000000);

    // Initialize systick counter
    SysTickInit();
    // Configure UART0
    ConfigureUART();
    // Initialize wheel counter timer
    WheelCounterInit();
    // Initialize motor driver
    MotorInit();
    // Button setup
    ButtonInit();
    UARTprintf("Finished button config\n");
    // Sonar setup
    SonarInit();
    UARTprintf("Finished sonar config\n");
    // Compass I2C initialization
    CompassInit();
    UARTprintf("Finished compass config\n");

    // Initialize LED outputs
    GPIODigitalEnable("F123");
    GPIOPinMode("F123", GPIO_OUT);

    // Initialize motor pwm to zero
    L298NSetPWM(&robot_car.motor_driver, 0, 0, 0);

    // Set LED to yellow for start state
    GPIODigitalWrite("F2", GPIO_LOW);
    GPIODigitalWrite("F13", GPIO_HIGH);

    // Initialize state and wheel counts
    current_state.state = START;
    current_state.delta_count_left = 0;
    current_state.delta_count_right = 0;
    current_state.old_count_left = 0;
    current_state.old_count_right = 0;
    current_state.count_left = 0;
    current_state.count_right = 0;
}

void SystemStart() {
    // Calculate initial heading
    current_state.start_heading = LSM303CalculateHeading(&robot_car.compass);
    // Set the target heading to the initial heading
    current_state.target_heading = current_state.start_heading;
}

void UpdateWheelCount() {
    // Read timer value
    current_state.old_count_left = current_state.count_left;
    current_state.old_count_right = current_state.count_right;
    current_state.count_left = ReadTimerA(robot_car.timer);
    current_state.count_right = ReadTimerB(robot_car.timer);

    if(pass > 2) {
        current_state.delta_count_right = current_state.count_right - current_state.old_count_right;
        current_state.delta_count_left = current_state.count_left - current_state.old_count_left;
    }
}

void SystemRunning() {
        // Calculate new current heading
        current_state.current_heading = LSM303CalculateHeading(&robot_car.compass);

        UpdateWheelCount();

        if(current_state.state == RUNNING) {
            if(current_state.delta_count_right > current_state.delta_count_left + DELTA_COUNT_THRESH) {
                L298NSetPWM(&robot_car.motor_driver, NORMAL_SPEED, NORMAL_SPEED + DELTA_COUNT_ADJUST, 4);
            }else if (current_state.delta_count_left > current_state.delta_count_right + DELTA_COUNT_THRESH) {
                L298NSetPWM(&robot_car.motor_driver, NORMAL_SPEED + DELTA_COUNT_ADJUST, NORMAL_SPEED, 4);
            }else {
                L298NSetPWM(&robot_car.motor_driver, NORMAL_SPEED, NORMAL_SPEED, 4);
            }
        }

        // Read left sonar
        HCSR04ReadDistance(&robot_car.sonar_left);
        // Delay between
        SysCtlDelay(100 * one_milli_sec);
        // Read right sonar
        HCSR04ReadDistance(&robot_car.sonar_right);

        // Left detect and right detect conditions for object detection
        bool left_detect = robot_car.sonar_left.dist < OBJECT_SENSE_DIST;
        bool right_detect = robot_car.sonar_right.dist < OBJECT_SENSE_DIST;

        // Adjust target heading if object is detected
        if(left_detect && !right_detect) {
            UARTprintf("Object detected on left at %dcm!\n", robot_car.sonar_left.dist);
            current_state.target_heading = current_state.start_heading + AVOIDANCE_ANGLE;
        }else if(!left_detect && right_detect) {
            UARTprintf("Object detected on right at %dcm!\n", robot_car.sonar_right.dist);
            current_state.target_heading = current_state.start_heading - AVOIDANCE_ANGLE;
        }else if(left_detect && right_detect) {
            // Check distance traveled
            current_state.target_heading = current_state.start_heading;
        }else if(!left_detect && !right_detect) {
            // Check cross range error and correct if needed
            current_state.target_heading = current_state.start_heading;
        }

        // Adjust heading to account for 0 - 360 range after sensor changes
        current_state.target_heading = (current_state.target_heading % 360 + 360) % 360;

        // Update the current PWM value to be closer to the target
        L298NUpdatePWM(&robot_car.motor_driver);

        // Calculate the difference in angle between the current and target headings
        int diff = (current_state.target_heading - current_state.current_heading + 540) % 360 - 180;

        // Adjust PWM values to make sure the robot stays on course
        if(diff > CORRECTION_ANGLE) {
            L298NSetPWM(&robot_car.motor_driver, TURNING_SPEED + TURNING_DIFF, TURNING_SPEED, 4);
            GPIODigitalWrite("F1", GPIO_HIGH);
            GPIODigitalWrite("F23", GPIO_LOW);

            current_state.state = TURNING;
        }else if(diff < -CORRECTION_ANGLE) {
            L298NSetPWM(&robot_car.motor_driver, TURNING_SPEED, TURNING_SPEED + TURNING_DIFF, 4);
            GPIODigitalWrite("F1", GPIO_HIGH);
            GPIODigitalWrite("F23", GPIO_LOW);

            current_state.state = TURNING;
        }else {
            L298NSetPWM(&robot_car.motor_driver, NORMAL_SPEED, NORMAL_SPEED, 6);
            GPIODigitalWrite("F3", GPIO_HIGH);
            GPIODigitalWrite("F12", GPIO_LOW);

            current_state.state = RUNNING;
        }

        uint16_t pwm_a_duty_cycle = 0, pwm_b_duty_cycle = 0;

        // Read PWM duty cycle
        pwm_a_duty_cycle = ReadPWMADutyCycle(*(robot_car.motor_driver.pwm_interface));
        pwm_b_duty_cycle = ReadPWMBDutyCycle(*(robot_car.motor_driver.pwm_interface));

        UARTprintf("Robot State: current_heading = %d, target_heading = %d, PWM A = %d, PWM B = %d, delta_left: %d, delta_right: %d\n", current_state.current_heading, current_state.target_heading, pwm_a_duty_cycle, pwm_b_duty_cycle, current_state.delta_count_left, current_state.delta_count_right);
}

int main(void)
 {
    SystemInit();
    SysTickReload(200 * one_milli_sec);
    SysTickRestart();

    UARTprintf("===== Noah Hester, Joseph Shumaker - Lab 12 - Design, Code, and Test The Complete HMI =====\r\n");

    while (current_state.state != END) {

    }
}
