#ifndef KEYPAD_H
#define KEYPAD_H

#include "aquaguardian.h"

/* Initializes the 4x4 matrix keypad GPIO pins. */
void Init_KPM(void);

/* Checks whether any keypad column is active. */
u32 colscan(void);

/* Finds the active keypad row. */
u32 rowcheck(void);

/* Finds the active keypad column. */
u32 colcheck(void);

/* Scans the keypad and returns the pressed key character. */
u32 keyscan(void);

/* Reads a number; C deletes a digit, e confirms, and d skips. */
u32 ReadNum(u32 default_val, u8 *skipped_flag);

#endif
