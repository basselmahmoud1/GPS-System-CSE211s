/****************************************************************/
/******* Author    : Maya Ahmed                 *****************/
/******* Date      : 25/4/2025                  *****************/
/******* File Name :main.c             *****************/
/****************************************************************/


#include "GPIO_interface.h"
#include "GPIO_private.h"

//void SystemInit(){}

void Delay(u32 millisec)
{
    volatile int i=0;
    int j=0;
    for(;j<millisec;j++)
        for(i=0;i<10000;i++);
}
	int main(void){
		u8 PinValue_pb1,PinValue_pb2;
		u8 PinValue;
		u8 pb_1,pb_2,m;
	//configure PortB pin0,1 as output ,initially low
        GPIO_u8ConfigPin(PortF,Pin1,GPIO_OUTPUT,GPIO_OUT_HIGH,0);
		GPIO_u8ConfigPin(PortB,Pin0,GPIO_OUTPUT,GPIO_OUT_LOW,0);
		GPIO_u8ConfigPin(PortB,Pin1,GPIO_OUTPUT,GPIO_OUT_LOW,0);
//configure PortA pin2,3 as input --->for pb
		GPIO_u8ConfigPin(PortA,Pin2,GPIO_INPUT,0,GPIO_PD);
		GPIO_u8ConfigPin(PortA,Pin3,GPIO_INPUT,0,GPIO_PU);
//test pin value
			GPIO_u8ConfigPin(PortB,Pin2,GPIO_OUTPUT,GPIO_OUT_LOW,0);
	//set portd
		GPIO_u8ConfigPORT(PortD,GPIO_OUTPUT,0x0F,0); //pin0,1,2,3
    while(1)
    {
				GPIO_u8SetPortValue(PortD,0x0);
				Delay(1000);

				for(;m<3;m++)
				{
				GPIO_u8SetPinValue(PortB,Pin2,GPIO_OUT_HIGH);
				Delay(1000);
				GPIO_u8SetPinValue(PortB,Pin2,GPIO_OUT_HIGH);	}

        pb_1=GPIO_u8GetPinValue(PortA,Pin2,&PinValue_pb1);
				pb_2=GPIO_u8GetPinValue(PortA,Pin3,&PinValue_pb1);

        if (pb_1==NOERR&&PinValue_pb1==1){ //if pb is pressed , light red
            GPIO_u8SetPinValue(PortB,Pin0,GPIO_OUT_HIGH);
						Delay(1000);
						GPIO_u8SetPinValue(PortB,Pin0,GPIO_OUT_LOW);
						Delay(1000);}
        if (pb_2==NOERR&&PinValue_pb2==1){ //if pb isn't pressed , light red
            GPIO_u8SetPinValue(PortB,Pin1,GPIO_OUT_HIGH);
						Delay(1000);
						GPIO_u8SetPinValue(PortB,Pin1,GPIO_OUT_LOW);
						Delay(1000);}
				}


}

