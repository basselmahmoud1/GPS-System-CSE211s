/****************************************************************/
/******* Author    : Habiba Ahmed               *****************/
/******* Date      : 14/4/2025                  *****************/
/******* File Name : LCD_int.h            *****************/
/****************************************************************/
#ifndef LCD_INT_H_
#define LCD_INT_H_

void LCD_voidInit(void);
void LCD_voidSendCommand(u8 comm);
void LCD_voidSendData(u8 data);
void LCD_voidSendString(const u8 *Str);
void LCD_voidMoveCursor(u8 row,u8 col);
void LCD_voidClearScreen(void);

void Delay(u32 milisec);
#endif