#include "device_drivers/L298N_driver.h"
#include "device_drivers/HCSR04_driver.h"
#include "device_drivers/LSM303_driver.h"
#include "tiva_launchpad_lib.h"

typedef struct system {
    // Timer for wheel counters
    TIMER_INFO timer;
    // Initialize abstracted PWM type for motors
    L298N motor_driver;
    PWM_GEN_INFO pwm_gen;

    // Sonar sensors
    HCSR04 sonar_left;
    HCSR04 sonar_right;
    // Compass module
    LSM303 compass;

    uint32_t clock;
} SYSTEM;

typedef struct state {
    int current_heading;
    int target_heading;
    int start_heading;

} STATE;

const int AVOIDANCE_ANGLE = 30;
const int CORRECTION_ANGLE = 10;
const int OBJECT_SENSE_DIST = 20;
const int NORMAL_SPEED = 30;
const int TURNING_SPEED = 15;
const int TURNING_DIFF = 3;
