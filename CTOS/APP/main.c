#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "stdio.h"

void Delay(u32 millisec)
{
    volatile int i=0;
    int j=0;
    for(;j<millisec;j++)
        for(i=0;i<10000;i++);
}

int main(void){
		u8 PinValue;
		u8 result;
    GPIO_u8ConfigPORT(PortA,GPIO_OUTPUT,0xFF,0);
    GPIO_u8ConfigPin(PortB,Pin3,GPIO_INPUT,0,GPIO_PD);
    GPIO_u8ConfigPin(PortB,Pin2,GPIO_INPUT,0,GPIO_PU);
    GPIO_u8ConfigPin(PortC,Pin0,GPIO_OUTPUT,GPIO_OUT_HIGH,0);
    GPIO_u8ConfigPin(PortC,Pin1,GPIO_OUTPUT,GPIO_OUT_LOW,0);
		GPIO_u8SetMode(PortB,Pin0,PB0_U1Rx);
    while(1)
    {
        GPIO_u8SetPortValue(PortA,GPIO_OUT_HIGH);
        Delay(1000);
        GPIO_u8SetPinValue(PortA,Pin1,GPIO_OUT_LOW);
        Delay(1000);
        //Test for GetPinValue

        result=GPIO_u8GetPinValue(PortA,Pin1,&PinValue);

        if (result==NOERR)  // Check if the read was successful
        {
            if(PinValue==1)
                printf("Pin A1 is HIGH\n");
            else
                printf("Pin A1 is LOW\n");
        }
        else
            printf("Error reading pin!\n"); //ERROR
    }
    //Testing


}

