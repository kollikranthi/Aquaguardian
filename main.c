#include "app.h"
#include "config.h"
#include "delay.h"
#include "gpio.h"
#include "hydration.h"
#include "interrupt.h"
#include "lcd.h"
#include "reminder.h"
#include "rtc.h"
#include "ui.h"

/* Main application loop: monitors time, water intake, reminders and settings. */
int main(void)
{
    /* Initialize GPIO, keypad, interrupt, RTC and LCD peripherals. */
    System_Init();

    while (1)
    {
        /* Reset the daily progress when the RTC date changes. */
        if (DOM != PreviousDay)
        {
            PreviousDay = DOM;
            ResetDailyState();
        }

        /* Read the manual drinking button until the daily target is reached. */
        if (goal_done == 0)
        {
            CheckWaterSwitch();
        }

        /* Update the clock and dashboard once the RTC second changes. */
        if (SEC != PreviousSec)
        {
            PreviousSec = SEC;

            /* Display the current time in HH:MM:SS format. */
            CmdLCD(GOTO_LINE1_POS0);
            if (HOUR < 10) CharLCD('0');
            U32LCD(HOUR);
            CharLCD(':');
            if (MIN < 10) CharLCD('0');
            U32LCD(MIN);
            CharLCD(':');
            if (SEC < 10) CharLCD('0');
            U32LCD(SEC);

            /* Display the weekday abbreviation beside the clock. */
            CmdLCD(GOTO_LINE1_POS0 + 9);
            StrLCD(week[DOW]);
            StrLCD("  ");

            /* Count down to the next reminder while the target is incomplete. */
            if (goal_done == 0)
            {
                if (RemainingIntervalSec > 0)
                {
                    RemainingIntervalSec--;
                }

                /* Trigger a reminder when the countdown reaches zero. */
                if (RemainingIntervalSec == 0)
                {
                    Reminder();

                    /* Restart the countdown after the alert has finished. */
                    RemainingIntervalSec = IntervalTotalSec;
                    PreviousSec = SEC;
                    CmdLCD(CLEAR_LCD);
                }

                RenderDashboardLine2();
            }
        }

        /* Show success feedback and stop further daily tracking at the target. */
        if ((WaterTaken >= TotalGlass) && (goal_done == 0))
        {
            goal_done = 1;

            CmdLCD(CLEAR_LCD);
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("GOAL COMPLETED!");
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("100% DONE!");

            IOSET0 = (1 << LED_G_PIN) | (1 << BUZZER_PIN);
            delay_s(3);
            IOCLR0 = (1 << LED_G_PIN) | (1 << BUZZER_PIN);

            CmdLCD(CLEAR_LCD);
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("REST FOR TODAY  ");
        }

        /* Enter configuration mode when the EINT0 interrupt sets the flag. */
        if (config_mode)
        {
            IOCLR0 = (1 << BUZZER_PIN) | (1 << LED_Y_PIN);
            EnterConfigMode();
            config_mode = 0;

            CmdLCD(CLEAR_LCD);
            PreviousSec = SEC;
            RenderDashboardLine2();
        }

        /* Short pause between iterations of the main loop. */
        delay_ms(20);
    }
}
