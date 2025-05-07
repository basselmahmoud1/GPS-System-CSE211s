/****************************************************************/
/******* Author    : Jannah Ahmed               *****************/
/******* Date      : 7/5/2025                  *****************/
/******* File Name : buzzer.c            *****************/
/****************************************************************/

#include "buzzer.h"
#include "../../MCAL/SYSTICK/systick_interface.h"
#include "../MCAL/GPIO_Private.h"

void Buzzer_Init(void)
{
    GPIO_u8ConfigPin(BUZZER_PORT, BUZZER_PIN, GPIO_OUTPUT, GPIO_OUT_LOW, 0); // Assuming buzzer is on the defined port and pin
}

void Buzzer_On(void)
{
    GPIO_u8SetPinValue(BUZZER_PORT, BUZZER_PIN, GPIO_OUT_HIGH);
}

void Buzzer_Off(void)
{
    GPIO_u8SetPinValue(BUZZER_PORT, BUZZER_PIN, GPIO_OUT_LOW);
}

/////////////////////////////generate a tone for the buzzer with a given frequency///////////////////
void Buzzer_GenerateTone(u32 frequency)
{
    u32 period = 1000000 / frequency; // Calculate the period for the given frequency

    while (1)
    {
        Buzzer_On();                    // Turn on buzzer
        Systick_u8Delay_us(period / 2); // Wait for half the period

        Buzzer_Off();                   // Turn off buzzer
        Systick_u8Delay_us(period / 2); // Wait for the other half of the period
    }
}

/// deciding the tone to be played from a specific frequency////////////////////////////////
void Buzzer_PlayDestinationTone(u32 frequency)
{
    Buzzer_GenerateTone(frequency);
}
