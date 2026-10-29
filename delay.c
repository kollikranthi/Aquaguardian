#include "delay.h"

/* Creates an approximate microsecond busy-wait delay. */
void delay_us(u32 tdly)
{
    tdly *= 12;
    while (tdly--);
}

/* Creates an approximate millisecond busy-wait delay. */
void delay_ms(u32 tdly)
{
    tdly *= 12000;
    while (tdly--);
}

/* Creates an approximate second busy-wait delay. */
void delay_s(u32 tdly)
{
    tdly *= 12000000;
    while (tdly--);
}
