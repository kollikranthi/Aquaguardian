#include "rtc.h"

/* Configures the RTC prescalers and starts the real-time clock. */
void InitRTC(void)
{
    CCR     = (1 << 1);
    PREINT  = 456;
    PREFRAC = 25024;
    CCR     = (1 << 0);
}

/* Sets the initial date/time used when the application starts. */
void SetStartDateTime(void)
{
    HOUR  = 17;
    MIN   = 24;
    SEC   = 0;
    DOM   = 31;
    MONTH = 7;
    YEAR  = 2026;
    DOW   = 5;
}
