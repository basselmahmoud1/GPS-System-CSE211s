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
		u8 PinValue_sw1,PinValue_sw2;
		u8 PinValue;
		u8 sw_1,sw_2,value;
	//configure leds as output ,initially low
		GPIO_u8ConfigPin(PortF,Pin1,GPIO_OUTPUT,GPIO_OUT_LOW,0);
		GPIO_u8ConfigPin(PortF,Pin2,GPIO_OUTPUT,GPIO_OUT_LOW,0);
		GPIO_u8ConfigPin(PortF,Pin3,GPIO_OUTPUT,GPIO_OUT_LOW,0);
	//configure swithces as input
		GPIO_u8ConfigPin(PortF,Pin0,GPIO_INPUT,0,GPIO_PU);
		GPIO_u8ConfigPin(PortF,Pin4,GPIO_INPUT,0,GPIO_PU);
	//set portb as output and portd as input
		GPIO_u8ConfigPORT(PortB,GPIO_OUTPUT,0x0F,0);
		GPIO_u8ConfigPORT(PortD,GPIO_INPUT,0,GPIO_PD);
	//testing setmode function
		GPIO_u8SetMode(PortA,Pin0,PA0_U0Rx);
		GPIO_u8SetMode(PortA,Pin1,PA1_U0Tx);


    while(1)
    {

        sw_1=GPIO_u8GetPinValue(PortF,Pin0,&PinValue_sw1);
        sw_2=GPIO_u8GetPinValue(PortF,Pin4,&PinValue_sw2);

        if (sw_1==NOERR&&PinValue_sw1==0){ //if switch1 is pressed , light red
            GPIO_u8SetPinValue(PortF,Pin1,GPIO_OUT_HIGH);
						Delay(1000);
						GPIO_u8SetPinValue(PortF,Pin1,GPIO_OUT_LOW); }

        if (sw_2==NOERR&&PinValue_sw2==0){// if switch2 is pressed , light blue
            GPIO_u8SetPinValue(PortF,Pin2,GPIO_OUT_HIGH);
						Delay(1000);
						GPIO_u8SetPinValue(PortF,Pin2,GPIO_OUT_LOW);}


			if(sw_1==NOERR&&sw_2==NOERR)     // if both swithces pressed ,light green
			{
						if(!(PinValue_sw1&&PinValue_sw2))
					   GPIO_u8SetPinValue(PortF,Pin3,GPIO_OUT_HIGH);
						Delay(1000);
						GPIO_u8SetPinValue(PortF,Pin3,GPIO_OUT_LOW);
						}

			GPIO_u8SetPinValue(PortB,Pin1,GPIO_OUT_LOW); //changing PortB pin1 from high to low
			Delay(1000);
			value=GPIO_u8GetPinValue(PortB,Pin1,&PinValue);
			if(value==NOERR&&PinValue==0){
				  GPIO_u8SetPinValue(PortF,Pin0,GPIO_OUT_LOW); //light red if PortB pin1 changed from high to low
					Delay(1000);
					GPIO_u8SetPinValue(PortF,Pin0,GPIO_OUT_LOW);}

			//testing PORTD pins
			value=GPIO_u8GetPinValue(PortD,Pin0,&PinValue);
			if(value==NOERR&&PinValue==1){
				  GPIO_u8SetPinValue(PortF,Pin0,GPIO_OUT_LOW); //light red if portd pin0 is high
					Delay(1000);
					GPIO_u8SetPinValue(PortF,Pin0,GPIO_OUT_LOW);}

			value=GPIO_u8GetPinValue(PortD,Pin1,&PinValue);
			if(value==NOERR&&PinValue==1){
				  GPIO_u8SetPinValue(PortF,Pin1,GPIO_OUT_LOW); //light blue if portd pin1 is high
					Delay(1000);
					GPIO_u8SetPinValue(PortF,Pin1,GPIO_OUT_LOW);}

			value=GPIO_u8GetPinValue(PortD,Pin5,&PinValue);
			if(value==NOERR&&PinValue==1){
				  GPIO_u8SetPinValue(PortF,Pin2,GPIO_OUT_LOW); //light green if PortD pin5 is high
					Delay(1000);
					GPIO_u8SetPinValue(PortF,Pin2,GPIO_OUT_LOW);}

					GPIO_u8SetPortValue(PortB,0x0);   			//testing setportvalue function
				}


}



