/***************************************************************/
/******* Author    : Bassel Mahmoud            *****************/
/******* Date      : 15/4/2025                 *****************/
/******* File Name : systick_program.c         *****************/
/***************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "systick_Private.h"
#include "systick_interface.h"

u8 Systick_u8Init (u8 Enable , u32 NoOfTicks ) 
{
    u8 ERR_state = ERR;
    if(Enable == SYSTICK_DISABLE)
        control_reg->ENABLE = SYSTICK_DISABLE ;
    else if(Enable == SYSTICK_ENABLE && NoOfTicks <= MAX_SYSTICK_TICKS){
        control_reg->ENABLE = SYSTICK_DISABLE ;
        SYSTICK->STRELOAD = NoOfTicks - 1;
        SYSTICK->STCURRENT = 1 ; // writing any value to STCURRENT clear the systick timer config
        control_reg->INTEN = SYSTICK_DISABLE ;  // We Disable the interrupt by default !
#if (Systick_CLK_SOURCE==MAIN_CLK_SRC)
        control_reg->CLK_SRC = 1 ;
#elif (Systick_CLK_SOURCE==PIOSC_CLK_SRC)
        control_reg->CLK_SRC = 0 ;
#else
        return ERR_state;
#endif
        control_reg->ENABLE = SYSTICK_ENABLE ; 
    }
    else
        return ERR_state;
    ERR_state = NOERR ; 
    return ERR_state;

}

void Systick_voidWaitOnTicks (u32 NoOfTicks)
{
    
    control_reg->ENABLE = SYSTICK_DISABLE ;
    SYSTICK->STRELOAD = NoOfTicks - 1  ;
    SYSTICK->STCURRENT = 1 ; // writing any value to STCURRENT clear the systick timer config
    control_reg->ENABLE = SYSTICK_ENABLE ; 
    while (!(control_reg->COUNT));
}

void Systick_voidDelay_ms(u32 Delay_ms)
{
    u32 i;
    for (i = 0; i < Delay_ms; i++)
    {
        Systick_u8WaitOnTicks(SYSTICK_TICKS_PER_MS); // Delay 1 millisecond
    }
}

void Systick_u8Delay_us (u32 Delay_us) 
{
    u32 i;
    for (i = 0; i < Delay_us; i++)
    {
        Systick_u8WaitOnTicks(SYSTICK_TICKS_PER_US); // Delay 1 microsecond
    }
}
