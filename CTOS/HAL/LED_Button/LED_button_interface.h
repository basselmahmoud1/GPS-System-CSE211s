/****************************************************************/
/*      Author  : Jannah Ahmed                             ********/
/******* Date      : 28/4/2025                        ************/
/******* File Name : LED_button_interface.h           ************/
/****************************************************************/

#ifndef LED_BUTTON_INTERFACE_H
#define LED_BUTTON_INTERFACE_H

#include "../../LIB/STD_TYPES.h"

// LED Functions
void LED_voidInit(void);
void LED_voidTurnOn(void);
void LED_voidTurnOff(void);

// Button Functions
void Button_voidInit(void);
u8 Button_u8IsPressed(void);

#endif
