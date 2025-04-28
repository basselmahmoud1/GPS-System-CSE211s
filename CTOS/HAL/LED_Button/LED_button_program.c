/****************************************************************/
/*      Author  : Jannah Ahmed                             ********/
/******* Date      : 28/4/2025                        ************/
/******* File Name : LED_button_program.c             ************/
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "LED_button_interface.h"
#include "LED_button_private.h"
#include "LED_button_config.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../MCAL/GPIO/GPIO_Private.h"

void LED_voidInit(void)
{
    GPIO_u8ConfigPin(LED_PORT, LED_PIN, GPIO_OUTPUT, GPIO_OUT_LOW, 0);
}

void LED_voidTurnOn(void)
{
    GPIO_u8SetPinValue(LED_PORT, LED_PIN, GPIO_OUT_HIGH);
}

void LED_voidTurnOff(void)
{
    GPIO_u8SetPinValue(LED_PORT, LED_PIN, GPIO_OUT_LOW);
}

void Button_voidInit(void)
{
    GPIO_u8ConfigPin(BUTTON_PORT, BUTTON_PIN, GPIO_INPUT, 0, GPIO_PU); // Pull-up
}

u8 Button_u8IsPressed(void)
{
    u8 Local_u8ButtonState = 1; // Default high because of pull-up
    GPIO_u8GetPinValue(BUTTON_PORT, BUTTON_PIN, &Local_u8ButtonState);
    return (Local_u8ButtonState == 0); // Return 1 if pressed (LOW), 0 if not
}
