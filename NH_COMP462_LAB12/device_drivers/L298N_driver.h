#pragma once
#include "../tiva_launchpad_lib.h"

typedef struct pwmData {
    int current;
    int target;
    int step;
} PWM;

typedef struct l298n {
    PWM motorLeft;
    PWM motorRight;
    PWM_GEN_INFO* pwm_interface;
} L298N;

void setPWM(PWM *pwm, int target, int stepSize);

int stepPWM(PWM *pwm);

L298N L298NInit(PWM_GEN_INFO* pwm);

void L298NSetPWM(L298N* device, int leftTarget, int rightTarget, int stepSize);

int L298NUpdatePWM(L298N* device);
