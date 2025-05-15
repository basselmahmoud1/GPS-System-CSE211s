/****************************************************************/
/******* Author    : Bassel Mahmoud               *****************/
/******* Date      : 15/4/2025                    *****************/
/******* File Name : systick_Private.h            *****************/
/****************************************************************/
#ifndef SYSTICK_PRIVATE_H 
#define SYSTICK_PRIVATE_H

#include "../LIB/STD_TYPES.h"
#include "systick_interface.h"


#define SYSTICK ((volatile systic_reg*) (0xE000E000U))
#define control_reg ((volatile STCTRL_reg*) (0xE000E010U))

#define MAIN_CLK_SRC  0
#define PIOSC_CLK_SRC  1

#define SYSTICK_CLK_HZ         16000000U     // SysTick clock frequency
#define SYSTICK_TICKS_PER_US   (SYSTICK_CLK_HZ / 1000000U)  // 16 ticks per µs
#define SYSTICK_TICKS_PER_MS   (SYSTICK_CLK_HZ / 1000U)     // 16000 ticks per ms

void Systick_u8WaitOnTicks (u32 NoOfTicks);


#endif






