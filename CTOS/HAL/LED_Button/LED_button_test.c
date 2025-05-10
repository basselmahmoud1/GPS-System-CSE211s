#include "LCD_int.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "systick_interface.h"
#include "LED_button_interface.h"

int main(){
	//LCD_voidInit();
	Systick_u8Init(SYSTICK_ENABLE,MAX_SYSTICK_TICKS);
	Button_voidInit();
	LED_voidInit();

while (1){
	if(Button_u8IsPressed()){
		LED_voidTurnOn();
		Systick_voidDelay_ms(1000);
		LED_voidTurnOff();
	}
}
}

