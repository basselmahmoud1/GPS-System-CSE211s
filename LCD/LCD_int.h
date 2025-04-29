/****************************************************************/
/******* Author    : Habiba Ahmed               *****************/
/******* Date      : 15/4/2025                  *****************/
/******* File Name : LCD_int.h            *****************/
/****************************************************************/
#ifndef LCD_INT_H_
#define LCD_INT_H_

#include "STD_TYPES.h"

void LCD_voidInit(void);
void LCD_voidSendCommand(u8 command);
void LCD_voidSendString(const u8 *Str );
void LCD_voidMoveCursor(u8 row,u8 col);
void LCD_voidClearScreen(void);

void Delay(u32 milisec);

#endif

