#ifndef APP_H
#define APP_H

#include "aquaguardian.h"

/* Initializes the peripherals and application state. */
void System_Init(void);

/* Resets the daily water-drinking counters and outputs. */
void ResetDailyState(void);

#endif
