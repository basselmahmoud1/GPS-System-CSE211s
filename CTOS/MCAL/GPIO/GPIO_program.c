/****************************************************************/
/******* Author    : Maya Ahmed                 *****************/
/******* Date      : 11/4/2025                  *****************/
/******* File Name : GPIO_program.c             *****************/
/****************************************************************/
#include "GPIO_Private.h"
#include "GPIO_interface.h"

//Initializes and unlocks a GPIO port and enables digital functionality.
u8 GPIO_u8Init(u8 Portid)
{
	volatile REG_PORT *port;
	u8 ERR_STATE = ERR;
	switch (Portid)
	{
		case PortA:
		GPIO_RCGCGPIO->PortA_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortA_REG))
		;
		port = GPIO_PORTA;
		break;
		case PortB:
		GPIO_RCGCGPIO->PortB_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortB_REG))
		;
		port = GPIO_PORTB;
		break;
		case PortC:
		GPIO_RCGCGPIO->PortC_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortC_REG))
		;
		port = GPIO_PORTC;
		break;
		case PortD:
		GPIO_RCGCGPIO->PortD_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortD_REG))
		;
		port = GPIO_PORTD;
		break;
		case PortE:
		GPIO_RCGCGPIO->PortE_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortE_REG))
		;
		port = GPIO_PORTE;
		break;
		case PortF:
		GPIO_RCGCGPIO->PortF_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortF_REG))
		;
		port = GPIO_PORTF;
		break;
		default:
		ERR_STATE = ERR;
		return ERR_STATE;
	} // unlock
	port->GPIOLOCK = GPIO_LOCK_KEY;
	port->GPIOCR = GPIO_PORT_ENABLE;
	port->GPIOAFSEL = GPIO_PORT_DISABLE;
	port->GPIOPCTL = GPIO_PORT_DISABLE;
	port->GPIOAMSEL = GPIO_PORT_DISABLE;
	port->GPIODEN = GPIO_PORT_ENABLE;

	ERR_STATE = NOERR;
	return ERR_STATE;
}


//Configure a single pin on the specified port.
u8 GPIO_u8ConfigPin(u8 PortId, u8 PinId, u8 PinDir, u8 PinValue, u8 InputState)
{
	volatile REG_PORT *port;
	u8 ERR_STATE = ERR;
	GPIO_u8Init(PortId);
	switch (PortId)
	{
		case PortA:
		port = GPIO_PORTA;
		break;
		case PortB:
		port = GPIO_PORTB;
		break;
		case PortC:
		port = GPIO_PORTC;
		break;
		case PortD:
		port = GPIO_PORTD;
		break;
		case PortE:
		port = GPIO_PORTE;
		break;
		case PortF:
		port = GPIO_PORTF;
		break;
		default:
		return ERR;
	}

	// Configure pin direction
	if (PinDir == GPIO_OUTPUT)
	{
		SetBit(port->GPIODIR, PinId); // Set pin as output
		if (PinValue == GPIO_OUT_HIGH)
		SetBit(port->GPIO_RW, PinId);
		else if (PinValue == GPIO_OUT_LOW)
		ClrBit(port->GPIO_RW, PinId);
	}
	else if (PinDir == GPIO_INPUT)
	{
		ClrBit(port->GPIODIR, PinId); // Set pin as input
		if (InputState == GPIO_PU)
		SetBit(port->GPIOPUR, PinId); // Enable pull-up
		else if (InputState == GPIO_PD)
		SetBit(port->GPIOPDR, PinId); // Enable pull-down
	}

	ERR_STATE = NOERR;
	return ERR_STATE;
}

//Configures an entire port for either input or output mode.
u8 GPIO_u8ConfigPORT(u8 PortId ,u8 PortDir , u8 PortValue , u8 InputState){
	u8 ERR_state = ERR;
	volatile REG_PORT* port;
	switch (PortId)
	{
		case PortA: port=GPIO_PORTA; break;
		case PortB: port=GPIO_PORTB; break;
		case PortC: port=GPIO_PORTC; break;
		case PortD: port=GPIO_PORTD; break;
		case PortE: port=GPIO_PORTE; break;
		case PortF: port=GPIO_PORTF; break;
		default: return ERR_state; // Invalid port
	}   GPIO_u8Init(PortId);
	if(PortDir==GPIO_INPUT){ //if the portdir=0
		port->GPIODIR=GPIO_PORT_INPUT; //put 0
		if(InputState==GPIO_PU) //if it's pullup
		port->GPIOPUR=GPIO_PORT_ENABLE;
		else if(InputState==GPIO_PD)
		port->GPIOPDR=GPIO_PORT_ENABLE;
	}

	else if(PortDir==GPIO_OUTPUT)// if the portdir=1
	port->GPIODIR=GPIO_PORT_OUTPUT; //put 1
	port->GPIO_RW=PortValue&GPIO_PORT_ENABLE;
	ERR_state = NOERR;
	return ERR_state;

}


//GetPinValue Description: Get the reading of a specified input pin.
u8 GPIO_u8GetPinValue(u8 PortId, u8 PinId, u8 *InputReading)
{
	volatile REG_PORT *port;
	u8 ERR_STATE = ERR;

	if (InputReading == NULL)
	return ERR;

	switch (PortId)
	{
		case PortA:
		port = GPIO_PORTA;
		break;
		case PortB:
		port = GPIO_PORTB;
		break;
		case PortC:
		port = GPIO_PORTC;
		break;
		case PortD:
		port = GPIO_PORTD;
		break;
		case PortE:
		port = GPIO_PORTE;
		break;
		case PortF:
		port = GPIO_PORTF;
		break;
		default:
		return ERR;
	}

	*InputReading = GetBit(port->GPIO_RW, PinId);
	ERR_STATE = NOERR;
	return ERR_STATE;
}

//Sets a specific pin’s digital output as high or low
u8 GPIO_u8SetPinValue(u8 PortId ,u8 PinId,u8 PinValue)
{	u8 ERR_state = ERR;
	volatile REG_PORT* port;
	switch (PortId)
	{
		case PortA: port=GPIO_PORTA; break;
		case PortB: port=GPIO_PORTB; break;
		case PortC: port=GPIO_PORTC; break;
		case PortD: port=GPIO_PORTD; break;
		case PortE: port=GPIO_PORTE; break;
		case PortF: port=GPIO_PORTF; break;
		default: return ERR_state; // Invalid port
	}
	if (PinValue==GPIO_OUT_HIGH)
	SetBit(port->GPIO_RW,PinId);

	else if (PinValue == GPIO_OUT_LOW)
	ClrBit(port->GPIO_RW,PinId);
	ERR_state = NOERR;
	return ERR_state;
}

//Sets the output value of an entire port.
u8 GPIO_u8SetPortValue(u8 PortId,u8 PortValue)
{   u8 ERR_state = ERR;
	volatile REG_PORT* port;
	switch (PortId)
	{
		case PortA: port=GPIO_PORTA; break;
		case PortB: port=GPIO_PORTB; break;
		case PortC: port=GPIO_PORTC; break;
		case PortD: port=GPIO_PORTD; break;
		case PortE: port=GPIO_PORTE; break;
		case PortF: port=GPIO_PORTF; break;
		default: return ERR_state; // Invalid port
	}
	port->GPIO_RW=PortValue&GPIO_PORT_ENABLE;
	ERR_state = NOERR;
	return ERR_state;
}

// Enables alternate function mode for a specific pin and sets the GPIOPCTL register according to mode applied
u8 GPIO_u8SetMode(u8 Portid,u8 PinId,u8 Mode)
{   u8 ERR_state = ERR;
	volatile REG_PORT* port;

	switch (Portid)
	{
		case PortA:
		GPIO_RCGCGPIO->PortA_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortA_REG))
		;
		port = GPIO_PORTA;
		break;
		case PortB:
		GPIO_RCGCGPIO->PortB_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortB_REG))
		;
		port = GPIO_PORTB;
		break;
		case PortC:
		GPIO_RCGCGPIO->PortC_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortC_REG))
		;
		port = GPIO_PORTC;
		break;
		case PortD:
		GPIO_RCGCGPIO->PortD_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortD_REG))
		;
		port = GPIO_PORTD;
		break;
		case PortE:
		GPIO_RCGCGPIO->PortE_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortE_REG))
		;
		port = GPIO_PORTE;
		break;
		case PortF:
		GPIO_RCGCGPIO->PortF_REG = GPIO_CLK_ENABLE;
		while (!(GPIO_PRGPIO->PortF_REG))
		;
		port = GPIO_PORTF;
		break;
		default:
		ERR_state = ERR;
		return ERR_state;
	}
	SetBit(port->GPIOAFSEL,PinId);
	GPIO_SET_MODE(port, PinId, Mode); // set the pctl register

	ERR_state = NOERR;
	return ERR_state;
}

