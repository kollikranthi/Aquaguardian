#ifndef DELAY_H
#define DELAY_H

#include "aquaguardian.h"

/* Busy-wait delay routines; their timing depends on CPU clock configuration. */
void delay_us(u32 tdly);
void delay_ms(u32 tdly);
void delay_s(u32 tdly);

#endif
