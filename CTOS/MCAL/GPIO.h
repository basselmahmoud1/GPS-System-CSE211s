#include "../LIB/std_types.h"
/*
#define --> REG address 
#define --> Value 

#define pin2 2
*/

typedef enum LED_color
{
    RED, //red =0  
    Green, // green =1 
    Blue // blue =2 
}LED_color;



u8 GPIO_u8setPortDir (u32 portid ,u8 pinid);
