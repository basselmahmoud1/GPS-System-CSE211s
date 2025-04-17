/**********************************************************************/
/******* Authors   : Malak Hesham                      ***************/
/******* Date      : 16/4/2025                         **************/
/******* File Name : LCD_prog.c                        *************/
/******************************************************************/

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../GPIO/GPIO_interface.h"
#include "LCD_config.h"
#include "LCD_priv.h"
#include "LCD_int.h"

#define HIGH    1
#define LOW     0

void LCD_voidSendString(const u8* Str){
    u8 counter = 0;
    while(Str[counter] != '\0')
    {
        LCD_voidSendData(Str[counter]);
        ++counter;
    }

}

void LCD_voidMoveCursor(u8 row,u8 col){
        u8 address;
        // Calculate the address based on the row and column
        if (row == 0) {
            address = col;  // Row 1 (0x00 to 0x0F)
        } else if (row == 1) {
            address = 0x40 + col;  // Row 2 (0x40 to 0x4F)
        } else {
            return;  // Invalid row
        }
        // Set the cursor position (LCD command)
        LCD_voidSendCommand(0x80 | address);

}
void LCD_voidClearScreen(void){
    LCD_voidSendCommand(LCD_CLR);
}