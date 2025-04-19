/****************************************************************/
/******* Author    : Jannah Ahmed               *****************/
/******* Date      : 10/4/2025                  *****************/
/******* File Name : GPIO_Private.h             *****************/
/****************************************************************/

#ifndef GPIO_Private_H
#define GPIO_Private_H

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
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


#define GPIO_PU     1
#define GPIO_PD     0
//---------PORTS---------------
#define PortA    0
#define PortB    1
#define PortC    2
#define PortD    3
#define PortE    4
#define PortF    5
//-----------PINS---------------
#define Pin0 0
#define Pin1 1
#define Pin2 2
#define Pin3 3
#define Pin4 4
#define Pin5 5
#define Pin6 6
#define Pin7 7
///----------------------------

#define GPIO_SET_MODE(port,pin,mode) ((port)->GPIOPCTL |= (mode<<(pin*4)))
#define PA0_U0Rx 1
#define PA1_U0Tx 1
#define PB0_U1Rx 1
#define PB1_U1Tx 1
#define PC4_U1Rx 2
#define PC5_U1Tx 2


/********************************* Helper Functions *******************************/

u8 GPIO_u8Init (u8 Portid);

#endif



