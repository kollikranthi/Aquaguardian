#include "interrupt.h"

/* External Interrupt 0 handler: request configuration mode and clear the IRQ. */
void eint0_isr(void) __irq
{
    config_mode = 1;
    EXTINT = (1 << 0);
    VICVectAddr = 0;
}

/* Maps P0.1 to EINT0 and configures the VIC for a falling-edge interrupt. */
void InitEINT0(void)
{
    PINSEL0 &= ~(3 << (1 * 2));
    PINSEL0 |= CONFIG_SW_PINSEL;

    VICIntEnable = (1 << EINT0_VIC_CHNO);
    VICVectCntl0 = (1 << 5) | EINT0_VIC_CHNO;
    VICVectAddr0 = (unsigned long)eint0_isr;

    EXTMODE  |= (1 << 0);
    EXTPOLAR &= ~(1 << 0);
}
