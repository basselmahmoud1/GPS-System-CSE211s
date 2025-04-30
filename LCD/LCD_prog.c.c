/****************************************************************/
/******* Author    : Habiba Ahmed               *****************/
/******* Date      : 15/4/2025                  *****************/
/******* File Name : LCD_prog.c            *****************/
/****************************************************************/
#include "GPIO_interface.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "LCD_config.h"
#include "LCD_int.h"
#include "LCD_priv.h"
#include "systick_interface.h"

#define HIGH    1
#define LOW     0


void LCD_voidInit(void){
    // control pins config
    GPIO_u8ConfigPin(LCD_CONTROL_PORT,LCD_RS_PIN,GPIO_OUTPUT,LOW,0);
    GPIO_u8ConfigPin(LCD_CONTROL_PORT,LCD_RW_PIN,GPIO_OUTPUT,LOW,0);
    GPIO_u8ConfigPin(LCD_CONTROL_PORT,LCD_E_PIN,GPIO_OUTPUT,LOW,0);
    // data pins config
    GPIO_u8ConfigPin(LCD_DATA_PORT,LCD_D4_PIN,GPIO_OUTPUT,LOW,0);
    GPIO_u8ConfigPin(LCD_DATA_PORT,LCD_D5_PIN,GPIO_OUTPUT,LOW,0);
    GPIO_u8ConfigPin(LCD_DATA_PORT,LCD_D6_PIN,GPIO_OUTPUT,LOW,0);
    GPIO_u8ConfigPin(LCD_DATA_PORT,LCD_D7_PIN,GPIO_OUTPUT,LOW,0);
    //delay more than 30 ms
    Systick_voidDelay_ms(40);
    //RS = 0
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,LOW);
    //RW = 0
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
    WriteHalfPort(2);
    SendEnablePulse();
    // set LCD 2 line 16 char 5x7
    LCD_voidSendCommand(0x28);
    Systick_voidDelay_us(45);
    //display, cusror , blink set on
    LCD_voidSendCommand(LCD_DIS_ON_SETUP);
    Systick_voidDelay_us(45);
    //clear display
    LCD_voidSendCommand(LCD_CLR);
    Systick_voidDelay_ms(2);
    //ENtry Moder
    LCD_voidSendCommand(LCD_SHIFT_INC);
    // send message for checking
    LCD_voidSendString("Intialized");
}

void LCD_voidSendCommand(u8 command){
    //RS = 0
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,LOW);
    //RW = 0
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
    //command send
    //most sig bits
    WriteHalfPort(command>>4);
    SendEnablePulse();
    // least sign bits
    WriteHalfPort(command);
    SendEnablePulse();
}

void LCD_voidSendData(u8 data){
    //RS = 1
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,HIGH);
    //RW = 0
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
    //data send
    //most sig bits
    WriteHalfPort(data>>4);
    SendEnablePulse();
    // least sign bits
    WriteHalfPort(data);
    SendEnablePulse();

}

void LCD_voidSendString(const u8 *Str ){
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


/*************Helping Functions****************/

static void SendEnablePulse(){
    // send enable pulse
    GPIO_u8SetPinValue (LCD_CONTROL_PORT , LCD_E_PIN ,HIGH);
    Systick_voidDelay_ms(2);///
    GPIO_u8SetPinValue (LCD_CONTROL_PORT , LCD_E_PIN ,LOW);
}

static void WriteHalfPort(u8 value){
    GPIO_u8SetPinValue(LCD_DATA_PORT,LCD_D4_PIN,GetBit(value,0));
    GPIO_u8SetPinValue(LCD_DATA_PORT,LCD_D5_PIN,GetBit(value,1));
    GPIO_u8SetPinValue(LCD_DATA_PORT,LCD_D6_PIN,GetBit(value,2));
    GPIO_u8SetPinValue(LCD_DATA_PORT,LCD_D7_PIN,GetBit(value,3));
}

