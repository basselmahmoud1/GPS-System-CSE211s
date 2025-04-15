/****************************************************************/
/******* Author    : Jannah Ahmed               *****************/
/******* Date      : 10/4/2025                  *****************/
/******* File Name : GPIO_inteface.h            *****************/
/****************************************************************/

#ifndef GPIO_Interface
#define GPIO_Interface

#include "../LIB/stdtypes.h"

typedef struct {
    u32 GPIODATA;       // can be used for reading 
    u32 unused0[254] ;
    u32 GPIO_WRITE;     // this is the address which write on the all port 
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
    u32 PortA : 1;   
    u32 PortB : 1;   
    u32 PortC : 1;   
    u32 PortF : 1;   
    u32 PortD : 1;   
    u32 PortE : 1;   
    u32 RESERVED : 26; 
}CLK_Enable;

#define GPIO_LOCK_KEY    0x4C4F434B

#define GPIO_INPUT       0 
#define GPIO_OUTPUT      1 

#define GPIO_CLK_ENABLE       1 
#define GPIO_CLK_DISABLE      0

#define GPIO_PORT_ENABLE     0XFF 
#define GPIO_PORT_DISABLE    0 

#define GPIO_PORT_OUTPUT     0XFF 
#define GPIO_PORT_INPUT    0 

#define GPIO_OUT_HIGH   1
#define GPIO_OUT_LOW    0

#define GPIO_PORT_OUT_HIGH   0xFF
#define GPIO_PORT_OUT_LOW    0


#define GPIO_PU     1
#define GPIO_PD     0


typedef enum {
    PortA , 
    PortB , 
    PortC ,
    PortD , 
    PortE ,
    PortF 
}PORT ; 

typedef enum {
    Pin0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7
}PIN;



/*
 *  PortId : take the PortID from the enum PORT (ex: PORTA , PORTB ..etc) 
 *  PinId  : take the pinID from the enum PIN   (ex: Pin0 , Pin1 ..etc) 
 *  PinDir : Take the 2 possible values : GPIO_INPUT or GPIO_OUTPUT
 *  PinValue : Take the 2 possible Values : GPIO_OUT_HIGH or GPIO_OUT_LOW
 *  InputState : Take the 2 possible Values : GPIO_PU (PULL UP) or GPIO_PD (PULL Down)
 *  InputReading : Take an pointer to the value  passed by the user to get the value of the
*/ 
u8 GPIO_u8ConfigPin  (PORT PortId , PIN PinId ,u8 PinDir , u8 PinValue , u8 InputState );
u8 GPIO_u8ConfigPORT (PORT PortId ,u8 PortDir , u8 PortValue , u8 InputState );
u8 GPIO_u8GetPinValue (PORT PortId , PIN PinId , u8* InputReading);

u8 GPIO_u8SetPinValue (PORT PortId , PIN PinId , u8 PinValue);
u8 GPIO_u8SetPortValue (PORT PortId , u8 PortValue);

// API That is used to chose the AFSEL 
u8 GPIO_u8SetMode (PORT PortId , PIN PinId);

#endif

