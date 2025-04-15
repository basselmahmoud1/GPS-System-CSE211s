/*
											Author:Maya Ahmed  
											Date:11/4/2025               
*/
#include "GPIO_Private.h"
#include "GPIO_interface.h"
u8 GPIO_u8Init(PORT Portid){
	volatile REG_PORT* port;
	switch (Portid)
    {
        case PortA:  
						GPIO_RCGCGPIO->PortA = GPIO_CLK_ENABLE;
				    while (!(GPIO_PRGPIO->PortA));
						port=GPIO_PORTA; break;
        case PortB: 
						GPIO_RCGCGPIO->PortB = GPIO_CLK_ENABLE;
						while (!(GPIO_PRGPIO->PortB));
						port=GPIO_PORTB; break;
        case PortC: 
						GPIO_RCGCGPIO->PortC = GPIO_CLK_ENABLE;
						while (!(GPIO_PRGPIO->PortC));
						port=GPIO_PORTC; break;
        case PortD: 
						GPIO_RCGCGPIO->PortD = GPIO_CLK_ENABLE;
						while (!(GPIO_PRGPIO->PortD));
						port=GPIO_PORTD; break;
        case PortE: 
						GPIO_RCGCGPIO->PortE = GPIO_CLK_ENABLE;
						while (!(GPIO_PRGPIO->PortE));
						port=GPIO_PORTE; break;
        case PortF: 
						GPIO_RCGCGPIO->PortF = GPIO_CLK_ENABLE;
						while (!(GPIO_PRGPIO->PortF));
						port=GPIO_PORTF; break;
        default: return 1; // Invalid port
    } //unlock  
				port->GPIOLOCK=GPIO_LOCK_KEY;
				port->GPIOCR=GPIO_PORT_ENABLE;
				port->GPIOAFSEL=GPIO_PORT_DISABLE;
				port->GPIOPCTL=GPIO_PORT_DISABLE;
				port->GPIOAMSEL=GPIO_PORT_DISABLE;
				port->GPIODEN=GPIO_PORT_ENABLE;
	
		//-------------------
		return 0;
	}
u8 GPIO_u8ConfigPORT(PORT PortId ,u8 PortDir , u8 PortValue , u8 InputState){
	volatile REG_PORT* port;
		switch (PortId)
    {
        case PortA: port=GPIO_PORTA; break;
        case PortB: port=GPIO_PORTB; break;
        case PortC: port=GPIO_PORTC; break;
        case PortD: port=GPIO_PORTD; break;
        case PortE: port=GPIO_PORTE; break;
        case PortF: port=GPIO_PORTF; break;
        default: return 1; // Invalid port
    }
		if(PortDir==GPIO_INPUT){ //if the portdir=0
				port->GPIODIR=GPIO_PORT_INPUT; //put 0
			if(InputState==GPIO_PU) //if it's pullup
				port->GPIOPUR=GPIO_PORT_ENABLE;
			else if(InputState==GPIO_PD)
				port->GPIOPDR=GPIO_PORT_ENABLE;
}
		
		else if(PortDir==GPIO_OUTPUT)// if the portdir=1
		port->GPIODIR=GPIO_PORT_OUTPUT; //put 1
		if(PortValue==GPIO_OUT_HIGH)
			port->GPIO_WRITE=GPIO_PORT_OUT_HIGH;
		else if(PortValue==GPIO_OUT_LOW)
			port->GPIO_WRITE=GPIO_PORT_OUT_LOW;
		return 0;
		
	}
u8 GPIO_u8SetPinValue(PORT PortId ,PIN PinId,u8 PinValue)
{		volatile REG_PORT* port;
		switch (PortId)
    {
        case PortA: port=GPIO_PORTA; break;
        case PortB: port=GPIO_PORTB; break;
        case PortC: port=GPIO_PORTC; break;
        case PortD: port=GPIO_PORTD; break;
        case PortE: port=GPIO_PORTE; break;
        case PortF: port=GPIO_PORTF; break;
        default: return 1; // Invalid port
    }
		if (PinValue==GPIO_OUT_HIGH)
        SET_BIT(port->GPIO_WRITE,PinId);
    
    else if (PinValue == GPIO_OUT_LOW)   
        CLR_BIT(port->GPIO_WRITE,PinId);
		return 0; //
}
u8 GPIO_u8SetPortValue(PORT PortId,u8 PortValue)
{
    volatile REG_PORT* port;
    switch (PortId)
    {
        case PortA: port=GPIO_PORTA; break;
        case PortB: port=GPIO_PORTB; break;
        case PortC: port=GPIO_PORTC; break;
        case PortD: port=GPIO_PORTD; break;
        case PortE: port=GPIO_PORTE; break;
        case PortF: port=GPIO_PORTF; break;
        default: return 1; // Invalid port
    }
    port->GPIO_WRITE=PortValue&GPIO_PORT_ENABLE;
				return 0;
}
u8 GPIO_u8SetMode(PORT PortId,PIN PinId)
{    volatile REG_PORT* port;
    switch (PortId)
    {
        case PortA: port=GPIO_PORTA; break;
        case PortB: port=GPIO_PORTB; break;
        case PortC: port=GPIO_PORTC; break;
        case PortD: port=GPIO_PORTD; break;
        case PortE: port=GPIO_PORTE; break;
        case PortF: port=GPIO_PORTF; break;
        default: return 1; // Invalid port
    }
    SET_BIT(port->GPIOAFSEL,PinId);
		return 0;
}

int main(void) {
    // test code or just to make it build
    return 0;
}


