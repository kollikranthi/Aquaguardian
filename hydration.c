#include "hydration.h"
#include "delay.h"
#include "lcd.h"
#include "ui.h"

/* Detects a button press, debounces it, and logs one glass of water. */
void CheckWaterSwitch(void)
{
    if (((IOPIN0 >> SW_PIN) & 1) == 0)
    {
        /* Wait briefly and verify the active-low button press. */
        delay_ms(20);
        if (((IOPIN0 >> SW_PIN) & 1) == 0)
        {
            /* Update progress only while the daily target is not reached. */
            if (WaterTaken < TotalGlass)
            {
                WaterTaken++;
                RemainingGlass = TotalGlass - WaterTaken;
                RemainingIntervalSec = IntervalTotalSec;
            }

            /* Refresh the dashboard and wait until the button is released. */
            RenderDashboardLine2();
            while (((IOPIN0 >> SW_PIN) & 1) == 0);
        }
    }
}
