/****************************************************************/
/******* Author    : Jannah Ahmed               *****************/
/******* Date      : 10/4/2025                  *****************/
/******* File Name : GPIO_inteface.h            *****************/
/****************************************************************/

#ifndef GPIO_Interface
#define GPIO_Interface

#include "STD_TYPES.h"

typedef struct {
    u32 GPIODATA;       // can be used for reading
    u32 unused0[254] ;
    u32 GPIO_RW;     // this is the address which write on the all port
    u32 GPIODIR;        // handle the direction of the port
    u32 unused1[7] ;
    u32 GPIOAFSEL;
    u32 unused2[59] ;
    u32 GPIOPUR;
    u32 GPIOPDR;
    u32 GPIOSLR;
    u32 GPIODEN;
    u32 GPIOLOCK;
    u32 GPIOCR;
    u32 GPIOAMSEL;
    u32 GPIOPCTL;
}REG_PORT;

typedef struct {
    u32 PortA_REG : 1;
    u32 PortB_REG : 1;
    u32 PortC_REG : 1;
    u32 PortD_REG : 1;
    u32 PortE_REG : 1;
    u32 PortF_REG : 1;
    u32 RESERVED : 26;
}CLK_Enable;
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

#define GPIO_INPUT       0
#define GPIO_OUTPUT      1

#define GPIO_OUT_HIGH   1
#define GPIO_OUT_LOW    0

/*
 *  PortId : take the PortID from the #define of PORTS (ex: PortA , PortB ..etc)
 *  PinId  : take the pinID from the #define of PINS   (ex: Pin0 , Pin1 ..etc)
 *  PinDir : Take the 2 possible values : GPIO_INPUT or GPIO_OUTPUT
 *  PinValue : Take the 2 possible Values : GPIO_OUT_HIGH or GPIO_OUT_LOW
 *  InputState : Take the 2 possible Values : GPIO_PU (PULL UP) or GPIO_PD (PULL Down)
 *  InputReading : Take an pointer to the value  passed by the user to get the value of the
*/
u8 GPIO_u8ConfigPin  (u8 PortId , u8 PinId ,u8 PinDir , u8 PinValue , u8 InputState );
u8 GPIO_u8ConfigPORT (u8 PortId ,u8 PortDir , u8 PortValue , u8 InputState );
u8 GPIO_u8GetPinValue (u8 PortId , u8 PinId , u8* InputReading);

u8 GPIO_u8SetPinValue (u8 PortId , u8 PinId , u8 PinValue);
u8 GPIO_u8SetPortValue (u8 PortId , u8 PortValue);

// API That is used to chose the AFSEL
u8 GPIO_u8SetMode (u8 PortId , u8 PinId,u8 Mode);

#endif

