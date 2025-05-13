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
#include "GPIO_Private.h"

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

    Systick_u8Init(SYSTICK_ENABLE,MAX_SYSTICK_TICKS);
    //delay more than 30 ms
    Systick_voidDelay_ms(40);
    LCD_voidSendCommand(0x33);
    // set LCD 2 line 16 char 5x7
    LCD_voidSendCommand(0x32);
    Systick_voidDelay_ms(1);
    LCD_voidSendCommand(0x28);
    Systick_voidDelay_ms(1);
    LCD_voidSendCommand(LCD_CLR);
    //display, cusror , blink set on
    Systick_voidDelay_ms(1);
    //clear display
    LCD_voidSendCommand(0x0C);
    Systick_voidDelay_ms(2);
    //ENtry Moder
    // send message for checking
    LCD_voidSendCommand(0x0C);
    LCD_voidSendString("Intialized");
}

void LCD_voidSendCommand(u8 command){
    //RS = 0
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,LOW);
    //RW = 0
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
    //command send
    Enable_set();
    Systick_voidDelay_ms(2);
    //most sig bits
    Enable_set();
    WriteHalfPort(command>>4);
    Enable_clr();
    // least sign bits
    Enable_set();
    WriteHalfPort(command);
    Enable_clr();
}

void LCD_voidSendData(u8 data){
    //RS = 1
    //RS = 0
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,HIGH);
    //RW = 0
    GPIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
    //command send
    Enable_set();
    Systick_voidDelay_ms(2);
    //most sig bits
	Enable_set();
    WriteHalfPort(data>>4);
	Enable_clr();
    // least sign bits
	Enable_set();
    WriteHalfPort(data);
	Enable_clr();

}

void LCD_voidSendString(const u8 *Str ){
    u8 counter = 0;
    while(Str[counter] != '\0')
    {
        LCD_voidSendData(Str[counter]);
        counter++;
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

void LCD_voidSendNumber( u16 number){
//	@todo: implement using recursion
	u16 local_u16tmp = 0 ;
	u8 counter = 0;
	while(number%10 == 0){
		counter++;
		number/=10;
	}
	while(number > 0){
		local_u16tmp = local_u16tmp *10 + number%10;
		number /=10;
	}
	while(local_u16tmp>0) {
			LCD_voidSendData((local_u16tmp%10)+'0');
			local_u16tmp /=10;
		}
	for (u8 i =0; i <counter; i++){
		LCD_voidSendData('0');
	}
}

void LCD_voidClearScreen(void){
    LCD_voidSendCommand(LCD_CLR);
}


/*************Helping Functions****************/

static void Enable_set(){
    // send enable pulse
    
    GPIO_u8SetPinValue (LCD_CONTROL_PORT , LCD_E_PIN ,HIGH);
}
static void Enable_clr(){
    // send enable pulse
    GPIO_u8SetPinValue (LCD_CONTROL_PORT , LCD_E_PIN ,LOW);
        Systick_voidDelay_ms(2);
///
}

static void WriteHalfPort(u8 value){
    GPIO_u8SetPinValue(LCD_DATA_PORT,LCD_D4_PIN,GetBit(value,0));
    GPIO_u8SetPinValue(LCD_DATA_PORT,LCD_D5_PIN,GetBit(value,1));
    GPIO_u8SetPinValue(LCD_DATA_PORT,LCD_D6_PIN,GetBit(value,2));
    GPIO_u8SetPinValue(LCD_DATA_PORT,LCD_D7_PIN,GetBit(value,3));

}

