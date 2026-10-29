#ifndef AQUAGUARDIAN_H
#define AQUAGUARDIAN_H

#include <LPC21xx.h>

/* AquaGuardian - Smart Water Drinking Reminder System
 * Target microcontroller: LPC2148
 */

/* Use 1 for a short testing interval; use 0 for the normal one-hour interval. */
#define DEMO_MODE 0

/* Short aliases for commonly used integer and floating-point types. */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef signed char        s8;
typedef signed short       s16;
typedef signed int         s32;
typedef float              f32;

/* Reads one bit or a four-bit nibble from a register/value. */
#define READBIT(WORD, BITPOS)             (((WORD) >> (BITPOS)) & 1)
#define READNIBBLE(WORD, STARTBIT)        (((WORD) >> (STARTBIT)) & 0x0F)

/* Replaces one byte or nibble in a register/value while preserving other bits. */
#define WRITEBYTE(WORD, STARTBIT, BYTE) \
    (WORD = (((WORD) & ~((u32)0xFF << (STARTBIT))) | (((u32)(BYTE) & 0xFF) << (STARTBIT))))

#define WRITENIBBLE(WORD, STARTBIT, NIBBLE) \
    (WORD = (((WORD) & ~((u32)0x0F << (STARTBIT))) | (((u32)(NIBBLE) & 0x0F) << (STARTBIT))))

/* LPC2148 Port 0 pin assignments for the buzzer, button and status LEDs. */
#define BUZZER_PIN       0   /* P0.0 - Buzzer output */
#define SW_PIN          20   /* P0.20 - Manual water button, active low */
#define LED_Y_PIN       21   /* P0.21 - Reminder active indicator */
#define LED_G_PIN       22   /* P0.22 - Goal achieved indicator */
#define LED_R_PIN       23   /* P0.23 - Missed reminder indicator */

/* LCD connections on Port 0. */
#define LCD_DATA         8   /* P0.8 to P0.15 - LCD data bus */
#define LCD_RS           5   /* P0.16 - Register select */
#define LCD_RW           6   /* P0.17 - Read/write */
#define LCD_EN           7   /* P0.18 - Enable */

/* Keypad row and column connections on Port 1. */
#define ROW0            16
#define ROW1            17
#define ROW2            18
#define ROW3            19
#define COL0            20
#define COL1            21
#define COL2            22
#define COL3            23

/* External interrupt 0 configuration. */
#define EINT0_VIC_CHNO   14
#define CONFIG_SW_PINSEL 0x0000000C

/* HD44780-compatible LCD command constants. */
#define CLEAR_LCD        0x01
#define RET_CUR_HOME     0x02
#define SHIFT_CUR_RIGHT  0x06
#define SHIFT_CUR_LEFT   0x07
#define DSP_OFF          0x08
#define DSP_ON_CUR_OFF   0x0C
#define DSP_ON_CUR_ON    0x0E
#define DSP_ON_CUR_BLK   0x0F
#define SHIFT_DSP_LEFT   0x11
#define SHIFT_DSP_RIGHT  0x14
#define MODE_8BIT_2LINE  0x38
#define GOTO_LINE1_POS0  0x80
#define GOTO_LINE2_POS0  0xC0
#define GOTO_CGRAM_START 0x40

/* Shared application state, defined in app.c and used by other modules. */
extern volatile u8 config_mode;
extern u8 TotalGlass;
extern u8 WaterTaken;
extern u8 RemainingGlass;
extern u8 MissCount;
extern u8 goal_done;
extern u8 skipped;

extern u32 IntervalHour;
extern u32 IntervalMin;
extern u32 IntervalSec;
extern u32 IntervalTotalSec;
extern u32 RemainingIntervalSec;

extern u8 PreviousSec;
extern u8 PreviousDay;

extern s8 week[][4];
extern u8 Glass[40];

#endif
