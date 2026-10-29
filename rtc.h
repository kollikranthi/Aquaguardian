#ifndef RTC_H
#define RTC_H

#include "aquaguardian.h"

/* Configures and starts the LPC2148 real-time clock. */
void InitRTC(void);

/* Loads the initial date and time values into the RTC registers. */
void SetStartDateTime(void);

#endif
