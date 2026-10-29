#ifndef UI_H
#define UI_H

#include "aquaguardian.h"

/* Displays the current RTC time on the LCD's second line. */
void DisplayCurrentTime(void);

/* Displays the configured reminder interval. */
void DisplayInterval(void);

/* Displays water taken, remaining glasses, missed reminders and progress icon. */
void RenderDashboardLine2(void);

#endif
