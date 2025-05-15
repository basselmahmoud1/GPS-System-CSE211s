/****************************************************************/
/******* Author    : Jannah Ahmed               *****************/
/******* Date      : 7/5/2025                  *****************/
/******* File Name : buzzer.c            *****************/
/****************************************************************/

#include "buzzer.h"
#include "systick_interface.h"
#include "GPIO_Private.h"
#include "UART_interface.h"
extern struct GPRMC_formate current_position;

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
	 u32 period = 1000 / (frequency);
    Systick_u8Init(SYSTICK_ENABLE, MAX_SYSTICK_TICKS);
    // Calculate the period for the given frequency
    Buzzer_On();                    // Turn on buzzer
         Systick_voidDelay_ms(period / 2); // Wait for half the period
    Buzzer_Off();                   // Turn off buzzer
         Systick_voidDelay_ms(period / 2); // Wait for the other half of the period
}

/// deciding the tone to be played from a specific frequency////////////////////////////////
void Buzzer_PlayDestinationTone(u32 frequency)
{
    Buzzer_GenerateTone(frequency);
}

////////////////////////////////////////////////////////////////////////////////////////////
///// Checking if valid and playing sound ///////////////////////////////////////////////////
/*
void Buzzer_ActivateOnValidGPS(void)
{
    u8 uart_data[100];
    u8 valid_msg_received = 0;
    u8 freq = 1000;
    u8 i;
    u8 state;

    Systick_u8Init(SYSTICK_ENABLE, MAX_SYSTICK_TICKS);

    while (!valid_msg_received)
    {
        UART_u8ReceiveString(uart_data);

        // strcpy(gps_string, "$GPRMC,202519.00,A,3003.911667,N,3116.805000,E");
        // state = GPS_u8ParsGpsString(uart_data, &current_position);
        state = GPS_u8ParsGpsString((char *)uart_data, &current_position);

        if (state != Recieve_ERR)
        {
            valid_msg_received = 1;
        }
    }

    for (i = 0; i < 5; i++)
    {

        Buzzer_GenerateTone(freq);
     Systick_voidDelay_ms(1);
        freq = freq + 500;
        // Buzzer_GenerateTone(1500);
        // Systick_u8Delay_us(500);
        // Buzzer_GenerateTone(2000);
        // Systick_u8Delay_us(500);
    }
}
*/
