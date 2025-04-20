/*
 * UART_interface.h
 *
 * Created: 17/04/2025 12:43:50
 *  Author: Khaled Ismail
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "../LIB/std_types.h"

void UART0_voidInitialize();
u8 UART0_u8ReceiveByte();
void UART0_voidSendByte(u8 Data_To_Be_Sent);
void UART0_voidReceiveString(u8 *String);
void UART0_voidSendString(u8 *String);

#endif /* UART_INTERFACE_H_ */