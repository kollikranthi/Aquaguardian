#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "aquaguardian.h"

/* Configures External Interrupt 0 for entering configuration mode. */
void InitEINT0(void);

/* Interrupt service routine for External Interrupt 0. */
void eint0_isr(void) __irq;

#endif
