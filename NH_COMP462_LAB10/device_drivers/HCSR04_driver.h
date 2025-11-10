#pragma once
#include <stdint.h>

typedef struct hcsr04 {
    char* trig;
    char* echo;
    uint32_t dist;
} HCSR04;

HCSR04 HCSR04Init(char *, char *);

uint32_t HCSR04ReadDistance(HCSR04*);
