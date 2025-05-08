#include "UART_interface.h"
#include "LCD_interface.h"
#include "GPIO_interface.h"
#include "SysTick_interface.h"
#include "../LIB/STD_TYPES.h"


///defines

#define Port1_For_Locations PortE
#define Port2_For_Locations PortD

#define Port_Direction_Indication PortB
#define NorthPin Pin4
#define SouthPin Pin5
#define EastPin Pin6
#define WestPin Pin7
#define NumberOfPlaces_First6 6
#define NumberOfPlaces_Rest

//function
void Bonus_void_CheckDirection();