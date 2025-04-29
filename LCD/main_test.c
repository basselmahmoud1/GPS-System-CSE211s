#include "LCD_int.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

int main(){
	LCD_voidInit();
while (1){
	LCD_voidSendString("hall");
	LCD_voidMoveCursor(1,10);
	LCD_voidSendString("gate 2");
	LCD_voidClearScreen();
	LCD_voidMoveCursor(0,6);
	LCD_voidSendString("r5");
}

}

