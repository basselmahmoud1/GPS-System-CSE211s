/****************************************************************/
/******* Author    : Habiba Ahmed               *****************/
/******* Date      : 15/4/2025                  *****************/
/******* File Name : LCD_priv.h            *****************/
/****************************************************************/

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

static void Enable_set(void);
static void Enable_clr(void);
static void WriteHalfPort(u8 value);

#define LCD_CLR                  0x01
#define LCD_HOME                 0x02
#define LCD_SHIFT_RIGHT          0X1C
#define LCD_SHIFT_LEFT           0X18 
#define LCD_SHIFT_INC            0x06
#define Stabilize_4_Bit_CMD      0x33
#define Four_Bits_Data_Mode      0x32
#define Two_Line_Four_Bit_Mode   0x28
#define Disp_On_CMD              0x0C


#endif
