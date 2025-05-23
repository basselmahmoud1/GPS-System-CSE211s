/*
 * UART_program.c
 *
 * Created: 17/04/2025 12:43:07
 *  Author: Khaled Ismail
 */ 


#include "tm4c123gh6pm.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/GPIO/GPIO_interface.h"
#include "../MCAL/GPIO/GPIO_private.h"
#include "UART_configuration.h"
#include "UART_interface.h"
#include "UART_private.h"

void UART0_voidConfig(void)
{
	//config CLK
	f64 UART_CLK = 16000000.0 / (16 * BaudRate);
	UART0_IBRD_R= (u32)UART_CLK;                                   //integer part
	UART0_FBRD_R= (u32)((UART_CLK - (u32)UART_CLK) * 64 + 0.5);    //fraction part
	
	//configuring
	UART0_LCRH_R &= Clear_LineCtrlConfig;
	UART0_LCRH_R |= LineCtrlConfig;
}

void UART0_voidInitialize(void)
{
	volatile REG_PORT* port = GPIO_PORTA;
	
	SetBit(SYSCTL_RCGCUART_R,UART_0);
	//while (!GetBit(SYSCTL_PRUART_R, UART_0));  //not nesesary because the next cycles are gpio related (the clock have time to be ready)
	GPIO_u8Init(PortA);

	// Configure UART0 pins
	SetBit(port->GPIOAFSEL, UART0_RX_PIN);
	SetBit(port->GPIOAFSEL, UART0_TX_PIN);
	SetBit(port->GPIODEN, UART0_RX_PIN);
	SetBit(port->GPIODEN, UART0_TX_PIN);
	ClrBit(port->GPIOAMSEL, UART0_RX_PIN);
	ClrBit(port->GPIOAMSEL, UART0_TX_PIN);
	
	//the following should be set with reseting but just for being sure
	port->GPIOPCTL = (port->GPIOPCTL & ~0xFF) | 0x11;
	
	//disabling UART
	ClrBit(UART0_CTL_R, UART_EN_PinID);
	
	UART0_voidConfig();
	
	//enabling UART
	SetBit(UART0_CTL_R, UART_EN_PinID);
}


u8 UART0_u8ReceiveByte(void)
{
	while (GetBit(UART0_FR_R,RXFE));   //checking if there is data to receive
	return UART0_DR_R;
}

void UART0_voidSendByte(u8 Data_To_Be_Sent)
{
	while (GetBit(UART0_FR_R,TXFF));
	UART0_DR_R= Data_To_Be_Sent;
}

void UART0_voidReceiveString(u8 *String)
{
	u8 x = 0;
	u8 y=1;
	while (1)
	{
		y = UART0_u8ReceiveByte();
		if ( y == '\n' ) break;  //stop on Enter
		String[x++] = y;
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

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void UART1_voidConfig(void)
{
	//config CLK
	f64 UART_CLK = 16000000.0 / (16 * BaudRate);
	UART1_IBRD_R= (u32)UART_CLK;                                   //integer part
	UART1_FBRD_R= (u32)((UART_CLK - (u32)UART_CLK) * 64 + 0.5);    //fraction part
	
	//configuring
	UART1_LCRH_R &= Clear_LineCtrlConfig;
	UART1_LCRH_R |= LineCtrlConfig;
}

void UART1_voidInitialize(void)
{
	volatile REG_PORT* port = GPIO_PORTB;
	
	SetBit(SYSCTL_RCGCUART_R,UART_1);
	//while (!GetBit(SYSCTL_PRUART_R, UART_1));  //not nesesary because the next cycles are gpio related (the clock have time to be ready)
	GPIO_u8Init(PortB);

	// Configure UART0 pins
	SetBit(port->GPIOAFSEL, UART1_RX_PIN);
	SetBit(port->GPIOAFSEL, UART1_TX_PIN);
	SetBit(port->GPIODEN, UART1_RX_PIN);
	SetBit(port->GPIODEN, UART1_TX_PIN);
	ClrBit(port->GPIOAMSEL, UART1_RX_PIN);
	ClrBit(port->GPIOAMSEL, UART1_TX_PIN);
	
	//the following should be set with reseting but just for being sure
	port->GPIOPCTL = (port->GPIOPCTL & ~0xFF) | 0x11;
	
	//disabling UART
	ClrBit(UART1_CTL_R, UART_EN_PinID);
	
	UART1_voidConfig();
	
	//enabling UART
	SetBit(UART1_CTL_R, UART_EN_PinID);
}

u8 UART1_u8ReceiveByte(void)
{
	while (GetBit(UART1_FR_R,RXFE));   //checking if there is data to receive
	return UART1_DR_R;
}

void UART1_voidSendByte(u8 Data_To_Be_Sent)
{
	while (GetBit(UART1_FR_R,TXFF));
	UART1_DR_R= Data_To_Be_Sent;
}

void UART1_voidReceiveString(u8 *String)
{
    u8 x = 0;
    u8 y;

    while (1)
    {
        y = UART1_u8ReceiveByte();
        if ( y == '\n' ) break;  // Stop on Enter
        String[x++] = y;
    }
    String[x] = '\0';  // Null-terminate
}
void UART1_voidSendString(u8 *String)
{
	while (*String)
	{
		UART1_voidSendByte(*String++);
	}
}
