/****************************************************************/
/******* Author    : Maya Ahmed                 *****************/
/******* Date      : 11/4/2025                  *****************/
/******* File Name : GPIO_program.c             *****************/
/****************************************************************/
#include "GPIO_Private.h"
#include "GPIO_interface.h"
u8 GPIO_u8Init(PORT Portid)
{
    volatile REG_PORT *port;
    u8 ERR_STATE = ERR;
    switch (Portid)
    {
    case PortA:
        GPIO_RCGCGPIO->PortA = GPIO_CLK_ENABLE;
        while (!(GPIO_PRGPIO->PortA))
            ;
        port = GPIO_PORTA;
        break;
    case PortB:
        GPIO_RCGCGPIO->PortB = GPIO_CLK_ENABLE;
        while (!(GPIO_PRGPIO->PortB))
            ;
        port = GPIO_PORTB;
        break;
    case PortC:
        GPIO_RCGCGPIO->PortC = GPIO_CLK_ENABLE;
        while (!(GPIO_PRGPIO->PortC))
            ;
        port = GPIO_PORTC;
        break;
    case PortD:
        GPIO_RCGCGPIO->PortD = GPIO_CLK_ENABLE;
        while (!(GPIO_PRGPIO->PortD))
            ;
        port = GPIO_PORTD;
        break;
    case PortE:
        GPIO_RCGCGPIO->PortE = GPIO_CLK_ENABLE;
        while (!(GPIO_PRGPIO->PortE))
            ;
        port = GPIO_PORTE;
        break;
    case PortF:
        GPIO_RCGCGPIO->PortF = GPIO_CLK_ENABLE;
        while (!(GPIO_PRGPIO->PortF))
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

/*
Config Pin Description: Configure a single pin on the specified port.
Parameters:

 *  PortId : take the PortID from the enum PORT (ex: PORTA , PORTB ..etc)
 *  PinId  : take the pinID from the enum PIN   (ex: Pin0 , Pin1 ..etc)
 *  PinDir : Take the 2 possible values : GPIO_INPUT or GPIO_OUTPUT
 *  PinValue : Take the 2 possible Values : GPIO_OUT_HIGH or GPIO_OUT_LOW
 *  InputState : Take the 2 possible Values : GPIO_PU (PULL UP) or GPIO_PD (PULL Down)
 *
 * Returns NOERR on success
*/

u8 GPIO_u8ConfigPin(PORT PortId, PIN PinId, u8 PinDir, u8 PinValue, u8 InputState)
{
    volatile REG_PORT *port;
    u8 ERR_STATE = ERR;

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
        SET_BIT(port->GPIODIR, PinId); // Set pin as output
        if (PinValue == GPIO_OUT_HIGH)
            SET_BIT(port->GPIO_WRITE, PinId);
        else if (PinValue == GPIO_OUT_LOW)
            CLR_BIT(port->GPIO_WRITE, PinId);
    }
    else if (PinDir == GPIO_INPUT)
    {
        CLR_BIT(port->GPIODIR, PinId); // Set pin as input
        if (InputState == GPIO_PU)
            SET_BIT(port->GPIOPUR, PinId); // Enable pull-up
        else if (InputState == GPIO_PD)
            SET_BIT(port->GPIOPDR, PinId); // Enable pull-down
    }

    ERR_STATE = NOERR;
    return ERR_STATE;
}

u8 GPIO_u8ConfigPORT(PORT PortId, u8 PortDir, u8 PortValue, u8 InputState)
{
    volatile REG_PORT *port;
    u8 ERR_STATE = ERR;
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
        ERR_STATE = ERR;
        return ERR_STATE;
    }
    if (PortDir == GPIO_INPUT)
    {                                    // if the portdir=0
        port->GPIODIR = GPIO_PORT_INPUT; // put 0
        if (InputState == GPIO_PU)       // if it's pullup
            port->GPIOPUR = GPIO_PORT_ENABLE;
        else if (InputState == GPIO_PD)
            port->GPIOPDR = GPIO_PORT_ENABLE;
    }

    else if (PortDir == GPIO_OUTPUT)      // if the portdir=1
        port->GPIODIR = GPIO_PORT_OUTPUT; // put 1
    if (PortValue == GPIO_OUT_HIGH)
        port->GPIO_WRITE = GPIO_PORT_OUT_HIGH;
    else if (PortValue == GPIO_OUT_LOW)
        port->GPIO_WRITE = GPIO_PORT_OUT_LOW;
    ERR_STATE = NOERR;
    return ERR_STATE;
}

/*
GetPinValue Description: Get the reading of a specified input pin.
Parameters:

 *  PortId : take the PortID from the enum PORT (ex: PORTA , PORTB ..etc)
 *  PinId  : take the pinID from the enum PIN   (ex: Pin0 , Pin1 ..etc)
 *  InputReading : Take an pointer to the value  passed by the user to get the value of the
 *
 * Returns NOERR on success
*/

u8 GPIO_u8GetPinValue(PORT PortId, PIN PinId, u8 *InputReading)
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

    *InputReading = GET_BIT(port->GPIODATA, PinId);
    ERR_STATE = NOERR;
    return ERR_STATE;
}

u8 GPIO_u8SetPinValue(PORT PortId, PIN PinId, u8 PinValue)
{
    volatile REG_PORT *port;
    u8 ERR_STATE = ERR;

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
        ERR_STATE = ERR;
        return ERR_STATE;
    }
    if (PinValue == GPIO_OUT_HIGH)
        SET_BIT(port->GPIO_WRITE, PinId);

    else if (PinValue == GPIO_OUT_LOW)
        CLR_BIT(port->GPIO_WRITE, PinId);
    ERR_STATE = NOERR;
    return ERR_STATE;
}
u8 GPIO_u8SetPortValue(PORT PortId, u8 PortValue)
{
    volatile REG_PORT *port;
    u8 ERR_STATE = ERR;

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
        ERR_STATE = ERR;
        return ERR_STATE;
    }
    port->GPIO_WRITE = PortValue & GPIO_PORT_ENABLE;
    return 0;
}
u8 GPIO_u8SetMode(PORT PortId, PIN PinId)
{
    volatile REG_PORT *port;
    u8 ERR_STATE = ERR;

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
        ERR_STATE = ERR;
        return ERR_STATE;
    }
    SET_BIT(port->GPIOAFSEL, PinId);
    ERR_STATE = NOERR;
    return ERR_STATE;
}
