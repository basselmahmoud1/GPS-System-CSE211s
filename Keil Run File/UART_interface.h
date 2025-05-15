/*
 * UART_interface.h
 *
 * Created: 17/04/2025 12:43:50
 *  Author: Khaled Ismail
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "STD_TYPES.h"

void UART0_voidInitialize(void);
u8 UART0_u8ReceiveByte(void);
void UART0_voidSendByte(u8 Data_To_Be_Sent);
void UART0_voidReceiveString(u8 *String);
void UART0_voidSendString(u8 *String);

void UART1_voidInitialize(void);
u8 UART1_u8ReceiveByte(void);
void UART1_voidSendByte(u8 Data_To_Be_Sent);
void UART1_voidReceiveString(u8 *String);
void UART1_voidSendString(u8 *String);

#endif /* UART_INTERFACE_H_ */
