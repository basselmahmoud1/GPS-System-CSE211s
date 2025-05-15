/****************************************************************/
/******* Author    : Jannah Ahmed               *****************/
/******* Date      : 10/4/2025                  *****************/
/******* File Name : GPIO_Private.h             *****************/
/****************************************************************/

#ifndef GPIO_Private_H
#define GPIO_Private_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"
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

#define GPIO_LOCK_KEY    0x4C4F434B

#define GPIO_INPUT       0
#define GPIO_OUTPUT      1

#define GPIO_CLK_ENABLE       1
#define GPIO_CLK_DISABLE      0

#define GPIO_PORT_ENABLE     0XFF
#define GPIO_PORT_DISABLE    0

#define GPIO_PORT_OUTPUT     0XFF
#define GPIO_PORT_INPUT    0

#define GPIO_OUT_HIGH   1
#define GPIO_OUT_LOW    0

#define GPIO_PORT_OUT_HIGH   0xFF
#define GPIO_PORT_OUT_LOW    0




/********************************* Helper Functions *******************************/

u8 GPIO_u8Init (u8 Portid);

#endif
