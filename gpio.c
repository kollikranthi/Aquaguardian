#include "gpio.h"

/* Sets the water switch as input and LEDs/buzzer as outputs. */
void InitGPIO(void)
{
    IODIR0 &= ~(1 << SW_PIN);
    IODIR0 |= (1 << LED_Y_PIN) | (1 << LED_G_PIN) | (1 << LED_R_PIN) | (1 << BUZZER_PIN);
    AllOutputsOff();
}

/* Clears the output bits for all LEDs and the buzzer. */
void AllOutputsOff(void)
{
    IOCLR0 = (1 << LED_Y_PIN) | (1 << LED_G_PIN) | (1 << LED_R_PIN) | (1 << BUZZER_PIN);
}
