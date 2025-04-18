/****************************************************************/
/******* Author    : Jannah Ahmed               *****************/
/******* Date      : 10/4/2025                  *****************/
/******* File Name : GPIO_Private.h             *****************/
/****************************************************************/

#ifndef GPIO_Private_H
#define GPIO_Private_H

#include "../LIB/stdtypes.h"
#include "../LIB/BitMath.h"
#include "GPIO_interface.h"

/********************************* BASE ADDRESS OF EACH PORT *******************************/
#define GPIO_PORTA      ((volatile REG_PORT*) (0x40004000U))
#define GPIO_PORTB      ((volatile REG_PORT*) (0x40005000U))
#define GPIO_PORTC      ((volatile REG_PORT*) (0x40006000U))
#define GPIO_PORTD      ((volatile REG_PORT*) (0x40007000U))
#define GPIO_PORTE      ((volatile REG_PORT*) (0x40024000U))
#define GPIO_PORTF      ((volatile REG_PORT*) (0x40025000U))
#define GPIO_RCGCGPIO   (((volatile CLK_Enable*)     (0x400FE608U)))   // Used to set the CLK for the PORT
#define GPIO_PRGPIO     (((volatile CLK_Enable*)     (0x400FE608U)))   // Used to check on the CLK of the PORT ON or OFF 
#define SYSCTL_RCGCGPIO_R       (*((volatile u32 *)0x400FE608))
#define SYSCTL_PRGPIO_R         (*((volatile u32 *)0x400FEA08))

/********************************* Helper Functions *******************************/

u8 GPIO_u8Init (u8 Portid);

#endif

