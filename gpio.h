#ifndef GPIO_H
#define GPIO_H

#include "aquaguardian.h"

/* Configures the GPIO directions used by the application. */
void InitGPIO(void);

/* Turns off all status LEDs and the buzzer. */
void AllOutputsOff(void);

#endif
