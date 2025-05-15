/******************************************************************/
/******* Author    : Bassel Mahmoud               *****************/
/******* Date      : 15/4/2025                    *****************/
/******* File Name : systick_interface.h          *****************/
/******************************************************************/

#ifndef SYSTICK_INTERFACE_H 
#define SYSTICK_INTERFACE_H

#include "STD_TYPES.h"

typedef struct 
{
    u32 unused0[4];
    u32 STCTRL ;
    u32 STRELOAD;
    u32 STCURRENT;
}systic_reg;

typedef struct {
    u32 ENABLE : 1;   
    u32 INTEN : 1;   
    u32 CLK_SRC : 1;   
    u32 RESERVED: 13;   
    u32 COUNT : 1;      
    u32 RESERVED1 : 15; 
}STCTRL_reg;

#define  SYSTICK_ENABLE  1
#define  SYSTICK_DISABLE 0
#define MAX_SYSTICK_TICKS   0x00FFFFFF

/*
*   Enable --> Takes 2 values for which the it enable or disable the systick timer
*   NoOfTicks --> this variable takes the no of ticks that will be loaded to the RELOAD REG at the start of operation
*/
u8 Systick_u8Init (u8 Enable , u32 NoOfTicks ) ; 
/*
*   Dealy_ms --> takes the no of milli seconds the Systick will wait
*/
void Systick_voidDelay_ms(u32 Delay_ms);

void Systick_voidDelay_us(u32 Delay_us);


#endif
