#include "GPIO_interface.h"
#include "gps_interface.h"
#include "GPIO_private.h"
#include "bonus_interface.h"

void Bonus_void_CheckDirection(Landmark landmark){
u8 input,Latitude,longtiude;
f64 distance,lat_diff,long_diff;
u8 gps_location[100];
u8 Place_index; 
   //////////////////////////////6pins on Port1_For_Locations->for 6 places////////////////
   for(Place_Index=0;Place_index<NumberOfPlaces_First6;Place_index++){
        GPIO_u8ConfigPin(Port1_For_Locations,Place_index,GPIO_INPUT,0,GPIO_PD);
        if(GPIO_u8GetPinValue(Port1_For_Locations,Place_index,&input)&&input==GPIO_OUT_HIGH)
        UART0_voidReceiveString(gps_location);
        GPS_u8_ExtractInfo(gps_location,&Latitude,&longitude);
        lat_diff=GPS_f64convertToDegrees(landmark[Place_index].latitude)-Latitude;
        long_diff=GPS_f64convertToDegrees(landmark[Place_index].longitude)-longtiude;
        if(lat_diff>0)
        GPIO_u8ConfigPin(Port_Direction_Indication,NorthPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0); //indication to go north
        Systick_voidDelay_ms(1000);
        GPIO_u8ConfigPin(Port_Direction_Indication,NorthPin,GPIO_OUTPUT,GPIO_OUT_LOW,0);
        else 
        GPIO_u8ConfigPin(Port_Direction_Indication,SouthPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0); //indication to go south
        Systick_voidDelay_ms(1000);
        GPIO_u8ConfigPin(Port_Direction_Indication,SouthPin,GPIO_OUTPUT,GPIO_OUT_LOW,0);
        if(long_diff>0)
        GPIO_u8ConfigPin(Port_Direction_Indication,EastPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0); //indication to go east
        Systick_voidDelay_ms(1000);
        GPIO_u8ConfigPin(Port_Direction_Indication,EastPin,GPIO_OUTPUT,GPIO_OUT_LOW,0);
        else 
        GPIO_u8ConfigPin(Port_Direction_Indication,WestPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0); //indication to go west
        Systick_voidDelay_ms(1000);
        GPIO_u8ConfigPin(Port_Direction_Indication,WestPin,GPIO_OUTPUT,GPIO_OUT_LOW,0);
   }
////////////////////////5pins->5places left////////////////////////////////////////
   for(Place_index=0;Place_index<NumberOfPlaces_Rest;Place_index++)
        {
        GPIO_u8ConfigPin(Port2_For_Locations,Place_index,GPIO_INPUT,0,GPIO_PD);
        if(GPIO_u8GetPinValue(Port2_For_Locations,Place_index,&input)&&input==GPIO_OUT_HIGH)
        UART0_voidReceiveString(gps_location);
        GPS_u8_ExtractInfo(gps_location,&Latitude,&longitude);
        f32 lat_diff=GPS_f64convertToDegrees(landmark[Place_index].latitude)-Latitude;
        f32 long_diff=GPS_f64convertToDegrees(landmark[Place_index].longitude)-longtiude;
        if(lat_diff>0)
        GPIO_u8ConfigPin(Port_Direction_Indication,NorthPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0); //indication to go north
        Systick_voidDelay_ms(1000);
        GPIO_u8ConfigPin(Port_Direction_Indication,NorthPin,GPIO_OUTPUT,GPIO_OUT_LOW,0);
        else 
        GPIO_u8ConfigPin(Port_Direction_Indication,SouthPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0); //indication to go south
        Systick_voidDelay_ms(1000);
        GPIO_u8ConfigPin(Port_Direction_Indication,SouthPin,GPIO_OUTPUT,GPIO_OUT_LOW,0);
        if(long_diff>0)
        GPIO_u8ConfigPin(Port_Direction_Indication,EastPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0); //indication to go east
        Systick_voidDelay_ms(1000);
        GPIO_u8ConfigPin(Port_Direction_Indication,EastPin,GPIO_OUTPUT,GPIO_OUT_LOW,0);
        else 
        GPIO_u8ConfigPin(Port_Direction_Indication,WestPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0); //indication to go west
        Systick_voidDelay_ms(1000);
        GPIO_u8ConfigPin(Port_Direction_Indication,WestPin,GPIO_OUTPUT,GPIO_OUT_LOW,0);
   }
}