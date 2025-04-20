/*
 * UART_program.c
 *
 * Created: 17/04/2025 12:43:07
 *  Author: Khaled Ismail
 */ 


#include "tm4c123gh6pm.h"
#include "../LIB/std_types.h"
#include "UART_configuration.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "GPIO_interface.h"

void UART0_voidInitialize()
{
	//disabling UART
	CLR_BIT(UART0_CTL_R, UART_EN_PinID);
	
	SET_BIT(SYSCTL_RCGCUART_R,UART_NUM);
	while (!GET_BIT(SYSCTL_PRUART_R, UART_NUM));  // Wait for UART0 to be ready
	GPIO_u8Init(UART_NUM_Port);

	volatile REG_PORT* port = GPIO_PORTA;
	// Configure UART0 pins
	SET_BIT(port->GPIOAFSEL, UART0_RX_PIN);
	SET_BIT(port->GPIOAFSEL, UART0_TX_PIN);
	SET_BIT(port->GPIODEN, UART0_RX_PIN);
	SET_BIT(port->GPIODEN, UART0_TX_PIN);
	CLR_BIT(port->GPIOAMSEL, UART0_RX_PIN);
	CLR_BIT(port->GPIOAMSEL, UART0_TX_PIN);
	
	//the following should be set with reseting but just for being sure
	port->GPIOPCTL = (port->GPIOPCTL & 0xFFFFFF00) | 0x11;
	
	UART0_voidConfig();
	
	//enabling UART
	SET_BIT(UART0_CTL_R, UART_EN_PinID);
}

void UART0_voidConfig()
{
	//config CLK
	f64 UART_CLK = 16000000.0 / (16 * BaudRate);
	UART0_IBRD_R= (u32)UART_CLK;                                   //integer part
	UART0_FBRD_R= (u32)((UART_CLK - (u32)UART_CLK) * 64 + 0.5);    //fraction part
	
	//configuring
	UART0_LCRH_R &= Clear_LineCtrlConfig;
	UART0_LCRH_R |= LineCtrlConfig;
}


u8 UART0_u8ReceiveByte()
{
	while (GET_BIT(UART0_FR_R,RXFE));   //checking if there is data to receive
	return UART0_DR_R;
}

void UART0_voidSendByte(u8 Data_To_Be_Sent)
{
	while (GET_BIT(UART0_FR_R,TXFF));
	UART0_DR_R= Data_To_Be_Sent;
	//while (GET_BIT(UART0_FR_R, UART_FR_BUSY));  //Optional
}

void UART0_voidReceiveString(u8 *String)
{
	u8 x=0;
	while(!GET_BIT(UART0_FR_R,RXFE))
	{
		String[x++]=UART0_u8ReceiveByte();
	}
	String[x] = '\0';
}

void UART0_voidSendString(u8 *String) 
{
	while (*String) 
	{
		UART0_voidSendByte(*String++); 
	}
}




