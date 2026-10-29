#ifndef LCD_H
#define LCD_H

#include "aquaguardian.h"

/* Sends a byte to the LCD data bus. */
void WriteLCD(u8 byte);

/* Sends a command to the LCD controller. */
void CmdLCD(u8 cmd);

/* Displays one character on the LCD. */
void CharLCD(u8 asciiVal);

/* Displays a null-terminated string on the LCD. */
void StrLCD(s8 *str);

/* Displays an unsigned integer as decimal digits. */
void U32LCD(u32 n);

/* Initializes the LCD in 8-bit, two-line mode. */
void InitLCD(void);

/* Writes custom character bitmap data into LCD CGRAM. */
void BuildCGRAM(u8 *p, u8 nBytes);

#endif
