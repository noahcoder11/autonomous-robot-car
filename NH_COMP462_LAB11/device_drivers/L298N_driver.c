#include "L298N_driver.h"


// Set new target PWM value and step size
void setPWM(PWM *pwm, int target, int stepSize) {
    if (pwm) {
        if(pwm->target == target) return;

        // Set new PWM target value
        pwm->target = target;

        if(pwm->current > target) pwm->step = -stepSize;
        else pwm->step = stepSize;
    }else {
        UARTprintf("ERROR: Invalid PWM object.\n");
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

L298N L298NInit(PWM_GEN_INFO* pwm) {
    L298N device;
    device.motorLeft.current = 0;
    device.motorLeft.target = 0;
    device.motorLeft.step = 0;
    device.motorRight.current = 0;
    device.motorRight.target = 0;
    device.motorRight.step = 0;

    device.pwm_interface = pwm;

    return device;
}

void L298NSetPWM(L298N* device, int leftTarget, int rightTarget, int stepSize) {
    setPWM(&(device->motorLeft), leftTarget, stepSize);
    setPWM(&(device->motorRight), rightTarget, stepSize);
}

int L298NUpdatePWM(L298N* device) {
    stepPWM(&(device->motorLeft));
    stepPWM(&(device->motorRight));

    SetPWMADutyCycle(*(device->pwm_interface), device->motorLeft.current);
    SetPWMBDutyCycle(*(device->pwm_interface), device->motorRight.current);
}
