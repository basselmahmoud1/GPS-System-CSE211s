/**********************************************************************/
/******* Authors   : Habiba Ahmed              *****************/
/******* Date      : 14/4/2025                       *****************/
/******* File Name : LCD_prog.c                     *****************/
/****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "LCD_config.h"
#include "LCD_priv.h"
#include "LCD_int.h"

#define HIGH    1
#define LOW     0

static void LCD_voidSendEnablePulse(){
    // send enable pulse
    GPIO_u8SetPinValue (LCD_CONTROL_PORT , LCD_E_PIN ,HIGH);
    Delay(10);
    GPIO_u8SetPinValue (LCD_CONTROL_PORT , LCD_E_PIN ,LOW);
}

void LCD_voidInit(void){
    Delay(40);
    // send instruction 0011 1000
    LCD_voidSendCommand(LCD_FUN_SET_TWOLINE_5x7);
    // DISPLAY AND CURSOR
    LCD_voidSendCommand(LCD_DIS_ON_SETUP);
    //SEND CLEAR
    LCD_voidSendCommand(LCD_CLR);
    Delay(2);
    //shift and increment mode
    LCD_voidSendCommand(LCD_SHIFT_INC);
}

void LCD_voidSendCommand(u8 command){
    //Rs to low
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,LOW);
    //Rw to low
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
    //copy command to data port
    GPIO_u8SetPortValue(LCD_DATA_PORT,command);
    LCD_voidSendEnablePulse();
}

void LCD_voidSendData(u8 data){
    //print characters
    // RS -> 1
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,HIGH);
    //RW ->0
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
    //SET DATA PORT TO DATA VALUES
    GPIO_u8SetPortValue(LCD_DATA_PORT,data);
    LCD_voidSendEnablePulse();
}

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

void Delay (u32 millisec)
{
    volatile int i = 0;
		int j = 0;
	for (; j < millisec ; j++)
    {
        for(i = 0; i< 10000 ; i++);
    }
}

