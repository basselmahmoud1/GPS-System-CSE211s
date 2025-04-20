/*
 * UART_private.h
 *
 * Created: 17/04/2025 12:44:34
 *  Author: Khaled Ismail
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

//taken from tm4c123gh6pm

////////////
//#define SYSCTL_RCGCUART_R       (*((volatile unsigned long *)0x400FE618)) //taken from tm4c123gh6pm
#define UART_0					0
#define UART_1					1
#define UART_2					2
#define UART_3					3
#define UART_4					4
#define UART_5					5
#define UART_6					6
#define UART_7					7
////////////


///////////////////
//#define UART0_FR_R              (*((volatile unsigned long *)0x4000C018)) //taken from tm4c123gh6pm
#define TXFE 7 
#define RXFF 6
#define TXFF 5
#define RXFE 4
#define BUSY 3
#define CTS	 0
////////////////////////

#define UART0_RX_PIN  0  // PA0
#define UART0_TX_PIN  1  // PA1

#define UART_EN_PinID 0

#define Clear_LineCtrlConfig 0xFFFFFF00

/*
defined in tm4c123gh6pm
#define UART0_DR_R              (*((volatile unsigned long *)0x4000C000))
#define UART0_RSR_R             (*((volatile unsigned long *)0x4000C004))
#define UART0_ECR_R             (*((volatile unsigned long *)0x4000C004))
#define UART0_FR_R              (*((volatile unsigned long *)0x4000C018))
#define UART0_ILPR_R            (*((volatile unsigned long *)0x4000C020))
#define UART0_IBRD_R            (*((volatile unsigned long *)0x4000C024))
#define UART0_FBRD_R            (*((volatile unsigned long *)0x4000C028))
#define UART0_LCRH_R            (*((volatile unsigned long *)0x4000C02C))
#define UART0_CTL_R             (*((volatile unsigned long *)0x4000C030))
#define UART0_IFLS_R            (*((volatile unsigned long *)0x4000C034))
#define UART0_IM_R              (*((volatile unsigned long *)0x4000C038))
#define UART0_RIS_R             (*((volatile unsigned long *)0x4000C03C))
#define UART0_MIS_R             (*((volatile unsigned long *)0x4000C040))
#define UART0_ICR_R             (*((volatile unsigned long *)0x4000C044))
#define UART0_DMACTL_R          (*((volatile unsigned long *)0x4000C048))
#define UART0_9BITADDR_R        (*((volatile unsigned long *)0x4000C0A4))
#define UART0_9BITAMASK_R       (*((volatile unsigned long *)0x4000C0A8))
#define UART0_PP_R              (*((volatile unsigned long *)0x4000CFC0))
#define UART0_CC_R              (*((volatile unsigned long *)0x4000CFC8))
*/


#endif /* UART_PRIVATE_H_ */