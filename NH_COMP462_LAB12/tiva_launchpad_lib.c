/**
 * tiva_launchpad_lib.c
 * for final project in COMP 462
 * 10-6-25 Noah Hester
 */

#include <stdint.h>
#include <stdbool.h>
#include "tiva_launchpad_lib.h"

PORT_INFO GetPortInfo(char p_char) {
    PORT_INFO port;
    unsigned long base;

    port.name = p_char;

    switch(p_char) {
        case 'A':
            base = GPIO_PORTA_BASE;
            port.clk = 0x01UL;
            break;
        case 'B':
            base = GPIO_PORTB_BASE;
            port.clk = 0x02UL;
            break;
        case 'C':
            base = GPIO_PORTC_BASE;
            port.clk = 0x04UL;
            break;
        case 'D':
            base = GPIO_PORTD_BASE;
            port.clk = 0x08UL;
            break;
        case 'E':
            base = GPIO_PORTE_BASE;
            port.clk = 0x10UL;
            break;
        case 'F':
            base = GPIO_PORTF_BASE;
            port.clk = 0x20UL;
            break;
    }

    port.data  = (volatile unsigned long *) (base + GPIO_DATA);
    port.dir   = (volatile unsigned long *) (base + GPIO_DIR);
    port.afsel = (volatile unsigned long *) (base + GPIO_AFSEL);
    port.pur   = (volatile unsigned long *) (base + GPIO_PUR);
    port.den   = (volatile unsigned long *) (base + GPIO_DEN);
    port.cr    = (volatile unsigned long *) (base + GPIO_CR);
    port.amsel = (volatile unsigned long *) (base + GPIO_AMSEL);

    port.lock  = (volatile unsigned long *) (base + GPIO_LOCK);
    port.pctl  = (volatile unsigned long *) (base + GPIO_PCTL);

    return port;
}

UART_INFO GetUARTInfo(uint32_t uart_num) {
    UART_INFO info;
    unsigned long base;
    info.id = uart_num;

    switch(uart_num) {
        case 0:
            base = UART0_BASE;
            break;
        case 1:
            base = UART1_BASE;
            break;
        case 2:
            base = UART2_BASE;
            break;
        case 3:
            base = UART3_BASE;
            break;
        case 4:
            base = UART4_BASE;
            break;
        case 5:
            base = UART5_BASE;
            break;
        case 6:
            base = UART6_BASE;
            break;
        case 7:
            base = UART7_BASE;
            break;
    }

    info.dr   = (volatile unsigned long *) (base + UART_DR);
    info.fr   = (volatile unsigned long *) (base + UART_FR);
    info.ibrd = (volatile unsigned long *) (base + UART_IBRD);
    info.fbrd = (volatile unsigned long *) (base + UART_FBRD);
    info.lcrh = (volatile unsigned long *) (base + UART_LCRH);
    info.ctl  = (volatile unsigned long *) (base + UART_CTL);
    info.cc   = (volatile unsigned long *) (base + UART_CC);

    return info;
}

ADC_INFO GetADCInfo(uint32_t adc_num) {
    ADC_INFO info;
    unsigned long base;
    info.id = adc_num;

    switch(adc_num) {
        case 0:
            base = ADC0_BASE;
            break;
        case 1:
            base = ADC1_BASE;
            break;
    }

    info.actss = (volatile unsigned long *) (base + ADC_ACTSS);
    info.ris = (volatile unsigned long *) (base + ADC_RIS);
    info.im = (volatile unsigned long *) (base + ADC_IM);
    info.isc = (volatile unsigned long *) (base + ADC_ISC);
    info.ostat = (volatile unsigned long *) (base + ADC_OSTAT);
    info.emux = (volatile unsigned long *) (base + ADC_EMUX);
    info.ustat = (volatile unsigned long *) (base + ADC_USTAT);
    info.sspri = (volatile unsigned long *) (base + ADC_SSPRI);
    info.pssi = (volatile unsigned long *) (base + ADC_PSSI);
    info.ssmux0 = (volatile unsigned long *) (base + ADC_SSMUX0);
    info.ssmux1 = (volatile unsigned long *) (base + ADC_SSMUX1);
    info.ssmux2 = (volatile unsigned long *) (base + ADC_SSMUX2);
    info.ssmux3 = (volatile unsigned long *) (base + ADC_SSMUX3);

    info.ssctl0 = (volatile unsigned long *) (base + ADC_SSCTL0);
    info.ssctl1 = (volatile unsigned long *) (base + ADC_SSCTL1);
    info.ssctl2 = (volatile unsigned long *) (base + ADC_SSCTL2);
    info.ssctl3 = (volatile unsigned long *) (base + ADC_SSCTL3);

    info.ssfifo0 = (volatile unsigned long *) (base + ADC_SSFIFO0);
    info.ssfifo1 = (volatile unsigned long *) (base + ADC_SSFIFO1);
    info.ssfifo2 = (volatile unsigned long *) (base + ADC_SSFIFO2);
    info.ssfifo3 = (volatile unsigned long *) (base + ADC_SSFIFO3);

    info.ssfstat0 = (volatile unsigned long *) (base + ADC_SSFSTAT0);
    info.ssfstat1 = (volatile unsigned long *) (base + ADC_SSFSTAT1);
    info.ssfstat2 = (volatile unsigned long *) (base + ADC_SSFSTAT2);
    info.ssfstat3 = (volatile unsigned long *) (base + ADC_SSFSTAT3);

    info.ssop0 = (volatile unsigned long *) (base + ADC_SSOP0);
    info.ssop1 = (volatile unsigned long *) (base + ADC_SSOP1);
    info.ssop2 = (volatile unsigned long *) (base + ADC_SSOP2);
    info.ssop3 = (volatile unsigned long *) (base + ADC_SSOP3);

    info.tmlb = (volatile unsigned long *) (base + ADC_TMLB);
    info.pc = (volatile unsigned long *) (base + ADC_PC);
    info.cc = (volatile unsigned long *) (base + ADC_CC);

    return info;
}

PWM_INFO GetPWMInfo(uint32_t pwm_num) {
    PWM_INFO info;
    unsigned long base;
    info.id = pwm_num;

    switch(pwm_num) {
        case 0:
            base = PWM0_BASE;
            break;
        case 1:
            base = PWM1_BASE;
            break;
    }

    info.base = base;

    info.ctl = (volatile unsigned long *) (base + PWM_CTL);
    info.sync = (volatile unsigned long *) (base + PWM_SYNC);
    info.enable = (volatile unsigned long *) (base + PWM_ENABLE);
    info.invert = (volatile unsigned long *) (base + PWM_INVERT);
    info.fault = (volatile unsigned long *) (base + PWM_FAULT);
    info.inten = (volatile unsigned long *) (base + PWM_INTEN);

    info.ris = (volatile unsigned long *) (base + PWM_RIS);
    info.isc = (volatile unsigned long *) (base + PWM_ISC);
    info.status = (volatile unsigned long *) (base + PWM_STATUS);
    info.faultval = (volatile unsigned long *) (base + PWM_FAULTVAL);
    info.enupd = (volatile unsigned long *) (base + PWM_ENUPD);
    info.inten = (volatile unsigned long *) (base + PWM_INTEN);

    return info;
}

PWM_GEN_INFO GetPWMGENInfo(PWM_INFO pwm, uint32_t gen_num) {
    PWM_GEN_INFO info;
    unsigned long base;
    info.id = gen_num;

    switch(gen_num) {
        case 0:
            base = pwm.base + PWM_GEN0_BASE;
            break;
        case 1:
            base = pwm.base + PWM_GEN1_BASE;
            break;
        case 2:
            base = pwm.base + PWM_GEN2_BASE;
            break;
        case 3:
            base = pwm.base + PWM_GEN3_BASE;
            break;
    }

    info.ctl = (volatile unsigned long *) (base + PWM_GEN_CTL);
    info.gena = (volatile unsigned long *) (base + PWM_GEN_GENA);
    info.genb = (volatile unsigned long *) (base + PWM_GEN_GENB);
    info.cmpa = (volatile unsigned long *) (base + PWM_GEN_CMPA);
    info.cmpb = (volatile unsigned long *) (base + PWM_GEN_CMPB);
    info.load = (volatile unsigned long *) (base + PWM_GEN_LOAD);

    return info;
}

PIN_INFO ParseGPIOString(char* gpio_str) {
    int i = 0;
    PIN_INFO info;
    info.pins = 0x00;

    info.port = GetPortInfo(gpio_str[0]);

    for(i = 1; gpio_str[i] != '\0'; i++) {
        int pin = gpio_str[i] - '0';

        info.pins |= 1 << pin;
    }

    return info;
}

TIMER_INFO GetTimerInfo(uint32_t timer_num) {
    TIMER_INFO info;
    unsigned long base;
    info.id = timer_num;

    switch(timer_num) {
        case 0:
            base = TIMER0_BASE;
            break;
        case 1:
            base = TIMER1_BASE;
            break;
        case 2:
            base = TIMER2_BASE;
            break;
        case 3:
            base = TIMER3_BASE;
            break;
        case 4:
            base = TIMER4_BASE;
            break;
        case 5:
            base = TIMER5_BASE;
            break;
    }

    info.cfg      = (volatile unsigned long *) (base + TIMER_CFG);
    info.tamr     = (volatile unsigned long *) (base + TIMER_TAMR);
    info.tbmr     = (volatile unsigned long *) (base + TIMER_TBMR);
    info.ctl      = (volatile unsigned long *) (base + TIMER_CTL);
    info.tamatchr = (volatile unsigned long *) (base + TIMER_TAMATCHR);
    info.tbmatchr = (volatile unsigned long *) (base + TIMER_TBMATCHR);
    info.tapmr    = (volatile unsigned long *) (base + TIMER_TAPMR);
    info.tbpmr    = (volatile unsigned long *) (base + TIMER_TBPMR);
    info.tar      = (volatile unsigned long *) (base + TIMER_TAV);
    info.tbr      = (volatile unsigned long *) (base + TIMER_TBV);

    return info;
}

void GPIOEnableClock(char* ports) {
    unsigned long portClkEnable = 0;
    int i;

    for(i = 0; ports[i] != '\0'; i++) {
        PORT_INFO port = GetPortInfo(ports[i]);
        portClkEnable |= port.clk;
    }

    SYSCTL_RCGCGPIO_R |= portClkEnable;

    while(!(SYSCTL_PRGPIO_R & portClkEnable));
}

void GPIOUnlock(char* gpio_str) {
    PIN_INFO p_info = ParseGPIOString(gpio_str);

    if(p_info.port.name == 'C' || p_info.port.name == 'D' || p_info.port.name == 'F') {
        *(p_info.port.lock) = GPIO_LOCK_KEY;
        *(p_info.port.cr) = p_info.pins;
    }
}

void GPIOPinMode(char* gpio_str, int mode) {
    PIN_INFO p_info = ParseGPIOString(gpio_str);

    if(mode == GPIO_IN) {
        *(p_info.port.dir) &= ~(p_info.pins);
    }else {
        *(p_info.port.dir) |= p_info.pins;
    }
}

void GPIODigitalEnable(char* gpio_str) {
    PIN_INFO p_info = ParseGPIOString(gpio_str);
    unsigned long pctl_mask = 0xFFFFFFFF;

    int i;

    for(i = 0; i < 8; i++) {
        if(p_info.pins & (1 << i)) {
            pctl_mask &= ~(0xF << (i * 4));
        }
    }

    *(p_info.port.amsel) &= ~(p_info.pins);
    *(p_info.port.afsel) &= ~(p_info.pins);
    *(p_info.port.den) |= p_info.pins;
    *(p_info.port.pctl) &= pctl_mask;
}

void GPIOAfselEnable(char* gpio_str, uint8_t peripheral) {
    PIN_INFO p_info = ParseGPIOString(gpio_str);
    *(p_info.port.afsel) |= p_info.pins;
    *(p_info.port.den) |= p_info.pins;
    *(p_info.port.amsel) &= ~p_info.pins;

    uint32_t pctl_unset_mask = 0x00000000, pctl_set_mask = 0x00000000;

    int i;

    for(i = 0; i < 8; i++) {
        if(p_info.pins & (1 << i)) {
            pctl_unset_mask |= 0xF << (i * 4);
            pctl_set_mask |= (peripheral & 0xF) << (i * 4);
        }
    }

    *(p_info.port.pctl) &= ~pctl_unset_mask;
    *(p_info.port.pctl) |= pctl_set_mask;
}

void GPIOAnalogEnable(char* gpio_str) {
    PIN_INFO p_info = ParseGPIOString(gpio_str);

    *(p_info.port.amsel) |= p_info.pins;
    *(p_info.port.afsel) |= p_info.pins;
    *(p_info.port.den) &= ~(p_info.pins);
}

void GPIOPullupEnable(char* gpio_str) {
    PIN_INFO p_info = ParseGPIOString(gpio_str);

    *(p_info.port.pur) |= p_info.pins;
}

void GPIODigitalWrite(char* gpio_str, int value) {
    PIN_INFO p_info = ParseGPIOString(gpio_str);

    if(value == GPIO_LOW) {
        *(p_info.port.data) &= ~(p_info.pins);
    }else {
        *(p_info.port.data) |= p_info.pins;
    }
}

unsigned long GPIODigitalRead(char* gpio_str) {
    PIN_INFO p_info = ParseGPIOString(gpio_str);

    return *(p_info.port.data) & p_info.pins;
}

UART_INFO UARTInit(uint32_t uart_num, uint32_t baud, uint32_t clock) {

    SYSCTL_RCGCUART_R |= 1 << uart_num;

    char* GPIO_string = UARTPortMapping[uart_num];

    PIN_INFO p_info = ParseGPIOString(GPIO_string);
    UART_INFO uart_info = GetUARTInfo(uart_num);

    char ports[2] = { p_info.port.name, '\0' };

    GPIOEnableClock(ports);
    *(uart_info.ctl) &= ~0x0001;

    float baud_divisor = (float) clock / (float) (baud << 4);
    int ibrd = (int) baud_divisor;
    *(uart_info.ibrd) = ibrd;
    *(uart_info.fbrd) = (int) ((baud_divisor - (float) ibrd) * 64);
    *(uart_info.lcrh) = 0x0070;
    *(uart_info.ctl)  = 0x0301;

    GPIOAfselEnable(GPIO_string, 0x1);

    return uart_info;
}

char UARTReadChar(UART_INFO uart) {
    while((*(uart.fr) & 0x0010) != 0);
    return (char) (*(uart.dr) & 0xFF);
}

void UARTPutChar(UART_INFO uart, char data) {
    while((*(uart.fr) & 0x0020) != 0);
    *(uart.dr) = data;
}

/*void UARTprintf(UART_INFO uart, char* fstring) {
    int i = 0;

    while(fstring[i] != '\0') {
        UARTPutChar(uart, fstring[i]);
        i++;
    }
}*/

ADC_INFO ADCInit(uint32_t adc_num) {
    SYSCTL_RCGCADC_R |= 1 << adc_num;
    ADC_INFO adc_info = GetADCInfo(adc_num);

    *(adc_info.pc) = 0x01;
    *(adc_info.sspri) = 0x0123;
    *(adc_info.actss) &= ~0x0008;
    *(adc_info.emux) &= ~0xF000;
    *(adc_info.ssmux3) = *(adc_info.ssmux3) & 0xFFFFFFF0;

    *(adc_info.ssctl3) = 0x0006;
    *(adc_info.im) &= ~0x0008;
    *(adc_info.actss) |= 0x0008;

    return adc_info;
}

PWM_GEN_INFO PWMGENInit(uint32_t pwm_num, uint32_t gen_num, uint32_t channels) {
    SYSCTL_RCGCPWM_R |= 1 << pwm_num;
    SYSCTL_RCC_R &= ~0x00100000;

    PWM_INFO pwm_info = GetPWMInfo(pwm_num);
    PWM_GEN_INFO gen_info = GetPWMGENInfo(pwm_info, gen_num);

    *(gen_info.ctl) &= ~0x3;
    *(gen_info.gena) = 0x00000008C;
    *(gen_info.genb) = 0x00000080C;
    *(gen_info.load) = MAX_PWM;
    *(gen_info.cmpa) = MAX_PWM - 1;
    *(gen_info.cmpb) = MAX_PWM - 1;
    *(gen_info.ctl) = 1;
    *(pwm_info.enable) |= channels;

    return gen_info;
}

void SetPWMGENA(PWM_GEN_INFO gen_info, int pulse_width) {
    if(pulse_width < 0) {
        *(gen_info.cmpa) = 0;
    }else if(pulse_width > MAX_PWM) {
        *(gen_info.cmpa) = MAX_PWM;
    }else {
        *(gen_info.cmpa) = pulse_width;
    }
}

void SetPWMADutyCycle(PWM_GEN_INFO gen_info, int duty_cycle) {
    int pulse_width = (100 - duty_cycle) * MAX_PWM / 100;
    SetPWMGENA(gen_info, pulse_width);
}

uint16_t ReadPWMGENA(PWM_GEN_INFO gen_info) {
    return *(gen_info.cmpa);
}

uint16_t ReadPWMADutyCycle(PWM_GEN_INFO gen_info) {
    return ((*(gen_info.load) - *(gen_info.cmpa)) * 100) / *(gen_info.load);
}

uint16_t ReadPWMGENB(PWM_GEN_INFO gen_info) {
    return *(gen_info.cmpb);
}

uint16_t ReadPWMBDutyCycle(PWM_GEN_INFO gen_info) {
    return ((*(gen_info.load) - *(gen_info.cmpb)) * 100) / *(gen_info.load);
}

void SetPWMGENB(PWM_GEN_INFO gen_info, int pulse_width) {
    if(pulse_width < 0) {
        *(gen_info.cmpb) = 0;
    }else if(pulse_width > MAX_PWM) {
        *(gen_info.cmpb) = MAX_PWM;
    }else {
        *(gen_info.cmpb) = pulse_width;
    }
}

void SetPWMBDutyCycle(PWM_GEN_INFO gen_info, int duty_cycle) {
    int pulse_width = (100 - duty_cycle) * MAX_PWM / 100;
    SetPWMGENB(gen_info, pulse_width);
}

TIMER_INFO TimerInit(uint32_t timer_num) {
    SYSCTL_RCGCTIMER_R |= 1 << timer_num;

    TIMER_INFO info = GetTimerInfo(timer_num);

    *(info.ctl) &= ~(1 << 0);
    *(info.cfg) = 0x4;
    *(info.tamr) = (0x3) | (1 << 4);
    *(info.tamatchr) = 0xFFFF;
    *(info.tapmr) = 0x00;
    *(info.ctl) &= ~(0x3 << 2);
    *(info.ctl) |= (0x3 << 2);
    *(info.ctl) |= (1 << 0);

    *(info.ctl) &= ~(1 << 8);
    *(info.tbmr) = (0x3) | (1 << 4);
    *(info.tbmatchr) = 0xFFFF;
    *(info.tbpmr) = 0x00;
    *(info.ctl) &= ~(0x3 << 10);
    *(info.ctl) |= (0x3 << 10);
    *(info.ctl) |= (1 << 8);

    *(info.tar) = 0;
    *(info.tbr) = 0;

    return info;
}

uint16_t ReadTimerA(TIMER_INFO timer) {
    return *(timer.tar);
}

uint16_t ReadTimerB(TIMER_INFO timer) {
    return *(timer.tbr);
}

void SysTickInit() {
    NVIC_ST_CTRL_R = 0; // disable SysTick
    NVIC_ST_RELOAD_R = 0x00ffffff;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x05; // use core clock

    DisableInterrupts();

    NVIC_ST_CTRL_R = 0;
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | (2u << 29);
    NVIC_ST_CTRL_R   = ST_CTRL_CLK_SRC | ST_CTRL_INTEN | ST_CTRL_ENABLE;

    EnableInterrupts();
}

void SysTickReload(uint32_t time) {
    NVIC_ST_RELOAD_R = time;
}

void SysTickRestart() {
    NVIC_ST_CURRENT_R = 0;
}
