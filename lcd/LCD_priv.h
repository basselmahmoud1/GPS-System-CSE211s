/****************************************************************/
/******* Author    : Habiba Ahmed               *****************/
/******* Date      : 14/4/2025                  *****************/
/******* File Name : LCD_priv.h            *****************/
/****************************************************************/

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

static void LCD_voidSendEnablePulse();

#define LCD_CLR                  0x01
#define LCD_HOME                 0x02
#define LCD_SHIFT_RIGHT          0X1C
#define LCD_SHIFT_LEFT           0X18
#define LCD_FUN_SET_TWOLINE_5x7  0x38
#define LCD_DIS_ON_SETUP         0x0F
#define LCD_SHIFT_INC            0x06
#define LCD_RETURN_HOME          0x02


#endif