#pragma once
#include <stdint.h>

#define SYSCTL_RCGCTIMER_R (*((volatile unsigned long *) 0x400FE604))
#define SYSCTL_RCGCGPIO_R  (*((volatile unsigned long *) 0x400FE608))
#define SYSCTL_RCGCPWM_R   (*((volatile unsigned long *) 0x400FE640))
#define SYSCTL_RCGCUART_R  (*((volatile unsigned long *) 0x400FE618))
#define SYSCTL_RCGCADC_R   (*((volatile unsigned long *) 0x400FE638))
#define SYSCTL_PRGPIO_R    (*((volatile unsigned long *) 0x400FEA08))
#define SYSCTL_PRUART_R    (*((volatile unsigned long *) 0x400FEA18))
#define SYSCTL_PRADC_R     (*((volatile unsigned long *) 0x400FEA38))
#define SYSCTL_RCC_R       (*((volatile unsigned long *) 0x400FE060))
#define SYSCTL_RIS_R       (*((volatile unsigned long *) 0x400FE050))
#define SYSCTL_RCC2_R      (*((volatile unsigned long *) 0x400FE070))

#define PWM0_BASE 0x40028000
#define PWM1_BASE 0x40029000

#define PWM_CTL      0x000 // Master control
#define PWM_SYNC     0x004 // Sync Control
#define PWM_ENABLE   0x008 // Out enable control
#define PWM_INVERT   0x00C // Invert out polarity
#define PWM_FAULT    0x010 // Fault source
#define PWM_INTEN    0x014 // Interrupt enable
#define PWM_RIS      0x018 // Raw interrupt status
#define PWM_ISC      0x01C // Interrupt status/clear
#define PWM_STATUS   0x020 // Status register
#define PWM_FAULTVAL 0x024 // Fault output value
#define PWM_ENUPD    0x028 // Enable update control

#define PWM_GEN0_BASE 0x040
#define PWM_GEN1_BASE 0x080
#define PWM_GEN2_BASE 0x0C0
#define PWM_GEN3_BASE 0x100

#define PWM_GEN_CTL       0x000
#define PWM_GEN_INTEN     0x004
#define PWM_GEN_RIS       0x008
#define PWM_GEN_ISC       0x00C
#define PWM_GEN_LOAD      0x010
#define PWM_GEN_COUNT     0x014
#define PWM_GEN_CMPA      0x018
#define PWM_GEN_CMPB      0x01C
#define PWM_GEN_GENA      0x020
#define PWM_GEN_GENB      0x024
#define PWM_GEN_DBCTL     0x028
#define PWM_GEN_DBRISE    0x02C
#define PWM_GEN_DBFALL    0x030
#define PWM_GEN_FLTSRC0   0x034
#define PWM_GEN_FLTSRC1   0x038
#define PWM_GEN_MINFLTPER 0x03C

// Analog base addresses
#define ADC0_BASE 0x40038000
#define ADC1_BASE 0x40039000

#define ADC_ACTSS  0x000
#define ADC_RIS    0x004
#define ADC_IM     0x008
#define ADC_ISC    0x00C
#define ADC_OSTAT  0x010
#define ADC_EMUX   0x014
#define ADC_USTAT  0x018
#define ADC_SSPRI  0x020
#define ADC_PSSI   0x028

#define ADC_SSMUX0 0x040
#define ADC_SSMUX1 0x060
#define ADC_SSMUX2 0x080
#define ADC_SSMUX3 0x0A0

#define ADC_SSCTL0 0x044
#define ADC_SSCTL1 0x064
#define ADC_SSCTL2 0x084
#define ADC_SSCTL3 0x0A4

#define ADC_SSFIFO0 0x048
#define ADC_SSFIFO1 0x068
#define ADC_SSFIFO2 0x088
#define ADC_SSFIFO3 0x0A8

#define ADC_SSFSTAT0 0x04C
#define ADC_SSFSTAT1 0x06C
#define ADC_SSFSTAT2 0x08C
#define ADC_SSFSTAT3 0x0AC

#define ADC_SSOP0 0x050
#define ADC_SSOP1 0x070
#define ADC_SSOP2 0x090
#define ADC_SSOP3 0x0B0

#define ADC_TMLB  0x100
#define ADC_PC    0xFC4
#define ADC_CC    0xFC8

// SysTick time interaction register
#define NVIC_ST_CTRL_R    (*((volatile unsigned long *) 0xE000E010))
#define NVIC_ST_RELOAD_R  (*((volatile unsigned long *) 0xE000E014))
#define NVIC_ST_CURRENT_R (*((volatile unsigned long *) 0xE000E018))
#define NVIC_SYS_PRI3_R   (*((volatile unsigned long *) 0xE000ED20))

#define TIMER0_BASE 0x40030000
#define TIMER1_BASE 0x40031000
#define TIMER2_BASE 0x40032000
#define TIMER3_BASE 0x40033000
#define TIMER4_BASE 0x40034000
#define TIMER5_BASE 0x40035000

#define TIMER_CFG      0x000
#define TIMER_TAMR     0x004
#define TIMER_TBMR     0x008
#define TIMER_CTL      0x00C
#define TIMER_TAMATCHR 0x030
#define TIMER_TBMATCHR 0x034
#define TIMER_TAPMR    0x040
#define TIMER_TBPMR    0x044
#define TIMER_TAR      0x048
#define TIMER_TBR      0x04C
#define TIMER_TAV      0x050
#define TIMER_TBV      0x054

// UART Base Addresses
#define UART0_BASE 0x4000C000
#define UART1_BASE 0x4000D000
#define UART2_BASE 0x4000E000
#define UART3_BASE 0x4000F000
#define UART4_BASE 0x40010000
#define UART5_BASE 0x40011000
#define UART6_BASE 0x40012000
#define UART7_BASE 0x40013000

// UART offset addresses
#define UART_DR   0x000
#define UART_RSR  0x004
#define UART_FR   0x018
#define UART_IBRD 0x024 // Integer Baud Rate Divisor
#define UART_FBRD 0x028 // Fractional Baud Rate Divisor
#define UART_LCRH 0x02C // Line Control High
#define UART_CTL  0x030 // Control
#define UART_CC   0xFC8 // Clock Configuration

// GPIO Base Addresses
#define GPIO_PORTA_BASE 0x40004000
#define GPIO_PORTB_BASE 0x40005000
#define GPIO_PORTC_BASE 0x40006000
#define GPIO_PORTD_BASE 0x40007000
#define GPIO_PORTE_BASE 0x40024000
#define GPIO_PORTF_BASE 0x40025000

// GPIO offset addresses
#define GPIO_DATA  0x3FC
#define GPIO_DIR   0x400
#define GPIO_AFSEL 0x420
#define GPIO_PUR   0x510
#define GPIO_DEN   0x51C
#define GPIO_CR    0x524
#define GPIO_AMSEL 0x528
// Pin Control
#define GPIO_PCTL  0x52C
// Lock Register (ONLY PORTS C, D, F!)
#define GPIO_LOCK  0x520

// GPIO I/O Definitions
#define GPIO_IN   0
#define GPIO_OUT  1
#define GPIO_LOW  0
#define GPIO_HIGH 1

// Define PORT locking key
#define GPIO_LOCK_KEY 0x4C4F434B

// Left on-board switch
#define PORTF_SW1 0x10UL
// Right on-board switch
#define PORTF_SW2 0x01UL

// SysTick control bits (ARM)
#define ST_CTRL_ENABLE  0x01
#define ST_CTRL_INTEN   0x02
#define ST_CTRL_CLK_SRC 0x04

#define one_sec          16000000
#define one_tenth_sec    1600000
#define one_milli_sec    16000
#define one_micro_second 16

// Port info structure
typedef struct portInfo {
    char name;
    volatile unsigned long *data;
    volatile unsigned long *dir;
    volatile unsigned long *afsel;
    volatile unsigned long *pur;
    volatile unsigned long *den;
    volatile unsigned long *cr;
    volatile unsigned long *amsel;
    unsigned long clk;

    volatile unsigned long *lock;
    volatile unsigned long *pctl;
} PORT_INFO;

typedef struct uartInfo {
    uint32_t id;
    volatile unsigned long *dr;
    volatile unsigned long *fr;
    volatile unsigned long *ibrd; // Integer baud rate divisor
    volatile unsigned long *fbrd; // Fractional baud rate divisor
    volatile unsigned long *lcrh; // Line control high
    volatile unsigned long *ctl;  // Control
    volatile unsigned long *cc;

} UART_INFO;

typedef struct adcInfo {
    uint32_t id;
    volatile unsigned long *actss;
    volatile unsigned long *ris;
    volatile unsigned long *im;
    volatile unsigned long *isc;
    volatile unsigned long *ostat;
    volatile unsigned long *emux;
    volatile unsigned long *ustat;
    volatile unsigned long *sspri;
    volatile unsigned long *pssi;
    volatile unsigned long *ssmux0;
    volatile unsigned long *ssmux1;
    volatile unsigned long *ssmux2;
    volatile unsigned long *ssmux3;

    volatile unsigned long *ssctl0;
    volatile unsigned long *ssctl1;
    volatile unsigned long *ssctl2;
    volatile unsigned long *ssctl3;

    volatile unsigned long *ssfifo0;
    volatile unsigned long *ssfifo1;
    volatile unsigned long *ssfifo2;
    volatile unsigned long *ssfifo3;

    volatile unsigned long *ssfstat0;
    volatile unsigned long *ssfstat1;
    volatile unsigned long *ssfstat2;
    volatile unsigned long *ssfstat3;

    volatile unsigned long *ssop0;
    volatile unsigned long *ssop1;
    volatile unsigned long *ssop2;
    volatile unsigned long *ssop3;

    volatile unsigned long *tmlb;
    volatile unsigned long *pc;
    volatile unsigned long *cc;
} ADC_INFO;

typedef struct timerInfo {
    uint32_t id;
    volatile unsigned long *cfg;
    volatile unsigned long *tamr;
    volatile unsigned long *tbmr;
    volatile unsigned long *ctl;
    volatile unsigned long *tamatchr;
    volatile unsigned long *tbmatchr;
    volatile unsigned long *tapmr;
    volatile unsigned long *tbpmr;
    volatile unsigned long *tar;
    volatile unsigned long *tbr;
} TIMER_INFO;

typedef struct pinInfo {
    PORT_INFO port;
    unsigned long pins;
} PIN_INFO;

typedef struct pwmInfo {
    uint32_t id;
    volatile unsigned long base;
    volatile unsigned long *ctl;
    volatile unsigned long *sync;
    volatile unsigned long *enable;
    volatile unsigned long *invert;
    volatile unsigned long *fault;
    volatile unsigned long *inten;
    volatile unsigned long *ris;
    volatile unsigned long *isc;
    volatile unsigned long *status;
    volatile unsigned long *faultval;
    volatile unsigned long *enupd;
} PWM_INFO;

typedef struct genInfo {
    uint32_t id;
    volatile unsigned long *ctl;
    volatile unsigned long *gena;
    volatile unsigned long *genb;
    volatile unsigned long *cmpa;
    volatile unsigned long *cmpb;
    volatile unsigned long *load;
} PWM_GEN_INFO;

static char* UARTPortMapping[8] = {"A01", "B01", "D67", "C67", "C45", "E45", "D45", "E01"};
static char* I2CPortMapping[8] = {"B23", "A67", "E45", "C67", "D01"};
static const int MAX_PWM = 16000;

PWM_INFO GetPWMInfo(uint32_t pwm_num);
PWM_GEN_INFO GetGENInfo(uint32_t gen_num);

PORT_INFO GetPortInfo(char);

UART_INFO GetUARTInfo(uint32_t);

PIN_INFO ParseGPIOString(char *);

// Enable the clock for the GPIO ports specified as character in the string
// i.e. GPIOPortEnableClock("ABC"); enables clock for ports A, B and C
void GPIOEnableClock(char *);

void UARTEnableClock(uint32_t);

// Unlock specific pins for certain registers (Port C, Port D, and Port F)
void GPIOUnlock(char *);

// Set the I/O mode of pins in a port
void GPIOPinMode(char *, int);

// Set pins as digital enables
void GPIODigitalEnable(char *);

// Set pins as analog enabled
void GPIOAnalogEnable(char *);

// Set pin pullup resistors
void GPIOPullupEnable(char *);

// Set digital GPIO HIGH or LOW
void GPIODigitalWrite(char *, int);

// Enable alternate function and peripheral (i.e. timer, GPIO, ADC, etc...)
void GPIOAfselEnable(char* gpio_str, uint8_t peripheral);

// Read masked register
unsigned long GPIODigitalRead(char *);

// Initialize a UART connection
UART_INFO UARTInit(uint32_t, uint32_t, uint32_t);

// Initialize an ADC unit
ADC_INFO ADCInit(uint32_t adc_num);

// Initialize a timer
TIMER_INFO TimerInit(uint32_t timer_num);

// Read the timer A value
uint16_t ReadTimerA(TIMER_INFO timer);

// Read timer B value
uint16_t ReadTimerB(TIMER_INFO timer);

// Initialize a PWM generator
PWM_GEN_INFO PWMGENInit(uint32_t pwm_num, uint32_t gen_num, uint32_t channels);

// Set the PWM generator A cmp register
void SetPWMGENA(PWM_GEN_INFO gen_info, int pulse_width);

// Set the PWM generator B cmp register
void SetPWMGENB(PWM_GEN_INFO gen_info, int pulse_width);

void SetPWMADutyCycle(PWM_GEN_INFO gen_info, int duty_cycle);

void SetPWMBDutyCycle(PWM_GEN_INFO gen_info, int duty_cycle);

// Read the PWM generator A cmp register
uint16_t ReadPWMGENA(PWM_GEN_INFO gen_info);

// Read the PWM generator B cmp register
uint16_t ReadPWMGENB(PWM_GEN_INFO gen_info);

// Read PWM A and compute current duty cycle
uint16_t ReadPWMADutyCycle(PWM_GEN_INFO gen_info);

// Read PWM B and compute current duty cycle
uint16_t ReadPWMBDutyCycle(PWM_GEN_INFO gen_info);

char UARTReadChar(UART_INFO);

void UARTPutChar(UART_INFO, char);

//void UARTprintf(UART_INFO, char*);

// Initialize SysTick counter
void SysTickInit();

// Reload the systick handler trigger value
void SysTickReload(uint32_t);

// Restart the systick counter
void SysTickRestart(void);

static inline void EnableInterrupts(void){ __asm(" CPSIE  I"); }
static inline void DisableInterrupts(void){ __asm(" CPSID  I"); }
