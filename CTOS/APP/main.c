/*
 * UART_driver.c
 *
 * Created: 19/04/2025 13:12:07
 * Author : Khaled Ismail
 */ 

#include "../MCAL/UART_interface.h"


int main(void)
{
	char str[100]={0};
		
	while(1)
	{
    UART0_voidReceiveString(str);
	UART0_voidSendString("Data received: ");
	UART0_voidSendString(str);
	UART0_voidSendString("\r\n");
	}
}

