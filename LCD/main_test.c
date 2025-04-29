#include "LCD_int.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "systick_interface.h"
int main(){
	LCD_voidInit();
while (1){
	LCD_voidSendString("hall");
	Systick_voidDelay_ms(1000);
	LCD_voidMoveCursor(1,10);
	LCD_voidSendString("gate 2");
	Systick_voidDelay_ms(1000);
	LCD_voidClearScreen();
	Systick_voidDelay_ms(2000);
	LCD_voidMoveCursor(0,6);
	LCD_voidSendString("r5");
}

}

