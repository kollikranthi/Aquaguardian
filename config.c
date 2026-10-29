#include "config.h"
#include "delay.h"
#include "keypad.h"
#include "lcd.h"
#include "ui.h"

/* Presents the configuration menu and applies valid user selections. */
void EnterConfigMode(void)
{
    u32 k;
    u32 temp;

    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
    StrLCD("CONFIG MODE");
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("PRESS 'e' TO SET");

    k = keyscan();

    if (k == 'e')
    {
        CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("1:TIME 2:INT");
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("3:TARGET");

        k = keyscan();

        /* Select which setting the user wants to change. */
        switch (k)
        {
            case '1':
                /* Read and validate the RTC hour. */
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("ENTER HH: ");
                DisplayCurrentTime();
                CmdLCD(GOTO_LINE1_POS0 + 10);
                temp = ReadNum(HOUR, &skipped);
                if (!skipped) HOUR = (temp > 23) ? 23 : temp;

                /* Read and validate the RTC minute. */
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("ENTER MM: ");
                DisplayCurrentTime();
                CmdLCD(GOTO_LINE1_POS0 + 10);
                temp = ReadNum(MIN, &skipped);
                if (!skipped) MIN = (temp > 59) ? 59 : temp;

                /* Read and validate the RTC second. */
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("ENTER SS: ");
                DisplayCurrentTime();
                CmdLCD(GOTO_LINE1_POS0 + 10);
                temp = ReadNum(SEC, &skipped);
                if (!skipped) SEC = (temp > 59) ? 59 : temp;

                RemainingIntervalSec = IntervalTotalSec;
                PreviousSec = SEC;
                break;

            case '2':
                /* Read the reminder interval hours. */
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("INT HH: ");
                DisplayInterval();
                CmdLCD(GOTO_LINE1_POS0 + 8);
                temp = ReadNum(IntervalHour, &skipped);
                if (!skipped) IntervalHour = (temp > 23) ? 23 : temp;

                /* Read the reminder interval minutes. */
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("INT MM: ");
                DisplayInterval();
                CmdLCD(GOTO_LINE1_POS0 + 8);
                temp = ReadNum(IntervalMin, &skipped);
                if (!skipped) IntervalMin = (temp > 59) ? 59 : temp;

                /* Read the reminder interval seconds. */
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("INT SS: ");
                DisplayInterval();
                CmdLCD(GOTO_LINE1_POS0 + 8);
                temp = ReadNum(IntervalSec, &skipped);
                if (!skipped) IntervalSec = (temp > 59) ? 59 : temp;

                /* Convert the configured interval to total seconds. */
                IntervalTotalSec = ((u32)IntervalHour * 3600UL) +
                                   ((u32)IntervalMin * 60UL) +
                                   (u32)IntervalSec;

                /* Prevent a zero-length interval by using a 15-second fallback. */
                if (IntervalTotalSec == 0)
                {
                    IntervalHour = 0;
                    IntervalMin  = 0;
                    IntervalSec  = 15;
                    IntervalTotalSec = 15;
                }

                RemainingIntervalSec = IntervalTotalSec;
                PreviousSec = SEC;
                break;

            case '3':
                /* Read and constrain the daily water-glass target. */
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("TARGET: ");
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("OLD: ");
                U32LCD(TotalGlass);
                CmdLCD(GOTO_LINE1_POS0 + 8);

                temp = ReadNum(TotalGlass, &skipped);
                if (!skipped)
                {
                    if (temp == 0) temp = 1;
                    if (temp > 20) temp = 20;
                    TotalGlass = (u8)temp;

                    /* Reset progress counters after changing the target. */
                    WaterTaken     = 0;
                    RemainingGlass = TotalGlass;
                    MissCount      = 0;
                    goal_done      = 0;
                }
                break;

            default:
                /* Inform the user when an unsupported menu key is pressed. */
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("INVALID CHOICE");
                delay_s(1);
                break;
        }
    }
}
