#include "lcd.h"
#include "delay.h"

/* Places a byte on the LCD data pins and pulses the enable line. */
void WriteLCD(u8 byte)
{
    WRITEBYTE(IOPIN0, LCD_DATA, byte);
    IOCLR0 = (1 << LCD_RW);
    IOSET0 = (1 << LCD_EN);
    delay_us(1);
    IOCLR0 = (1 << LCD_EN);
    delay_ms(2);
}

/* Sends an instruction byte to the LCD. */
void CmdLCD(u8 cmd)
{
    IOCLR0 = (1 << LCD_RS);
    WriteLCD(cmd);
}

/* Sends a character byte to be displayed on the LCD. */
void CharLCD(u8 asciiVal)
{
    IOSET0 = (1 << LCD_RS);
    WriteLCD(asciiVal);
}

/* Prints a null-terminated string one character at a time. */
void StrLCD(s8 *str)
{
    while (*str)
        CharLCD(*str++);
}

/* Converts an unsigned integer to decimal digits and displays it. */
void U32LCD(u32 n)
{
    u8 a[10];
    s32 i = 0;

    if (n == 0)
    {
        CharLCD('0');
    }
    else
    {
        /* Store digits in reverse order, then print them in forward order. */
        while (n > 0)
        {
            a[i] = (n % 10) + '0';
            n /= 10;
            i++;
        }
        for (--i; i >= 0; i--)
            CharLCD(a[i]);
    }
}

/* Configures the LCD data/control pins and sends the initialization sequence. */
void InitLCD(void)
{
    IODIR0 |= ((0xFF << LCD_DATA) | (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN));

    delay_ms(15);
    CmdLCD(0x30);
    delay_ms(4);
    delay_us(100);
    CmdLCD(0x30);
    delay_us(100);
    CmdLCD(0x30);
    CmdLCD(MODE_8BIT_2LINE);
    CmdLCD(DSP_ON_CUR_OFF);
    CmdLCD(CLEAR_LCD);
    CmdLCD(SHIFT_CUR_RIGHT);
}

/* Writes custom character patterns into the LCD's Character Generator RAM. */
void BuildCGRAM(u8 *p, u8 nBytes)
{
    u8 i;

    CmdLCD(GOTO_CGRAM_START);
    IOSET0 = (1 << LCD_RS);
    for (i = 0; i < nBytes; i++)
    {
        WriteLCD(p[i]);
    }
    CmdLCD(GOTO_LINE1_POS0);
}
