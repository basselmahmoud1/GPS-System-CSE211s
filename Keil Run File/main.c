 #include "GPIO_interface.h"
 #include "GPIO_private.h"
 #include "stdio.h"
 #include "UART_interface.h"
 #include "systick_interface.h"
 #include "STD_TYPES.h"
 #include "GPS.h"
 #include "LCD_int.h"
 #include "buzzer.h"

 #define Check_Location_Port PortD
 #define Check_Location_Pin Pin7


 
 int main(void)
 {
		u8 Compass_Pin_Value=1;
		u32 i=0;
		u8 Check_Location_Pin_Value;
		u8 *gps_string;	
		struct GPRMC_formate GPS_parsed;
		
	Systick_u8Init(SYSTICK_ENABLE,MAX_SYSTICK_TICKS);
 	LCD_voidInit();
	UART1_voidInitialize();
 
	LCD_voidClearScreen();
	LCD_voidSendString("*WELCOME*");
	
	//wait until GPS is ready sending true reading
	while(GPS_u8ParsGpsString(gps_string,&GPS_parsed)==Recieve_ERR)	UART1_voidReceiveString(gps_string); 
		
	 
	// Alerting that the GPS is ready
	Buzzer_Init();
	Buzzer_On();
	for(i=0 ; i < 1000 ;i++)
	{
		Buzzer_GenerateTone(500);
	}
	LCD_voidClearScreen();
	Buzzer_Off();
			
	GPIO_u8ConfigPin(Civil_Compass_Port,Civil_Compass_Pin,GPIO_INPUT,0,GPIO_PU); 
	GPIO_u8ConfigPin(HallA_Compass_Port,HallA_Compass_Pin,GPIO_INPUT,0,GPIO_PU);
	GPIO_u8ConfigPin(Acoustics_Building_Compass_Port,Acoustics_Building_Compass_Pin,GPIO_INPUT,0,GPIO_PU);
	GPIO_u8ConfigPin(Gate2_Compass_Port,Gate2_Compass_Pin,GPIO_INPUT,0,GPIO_PU); //
	
 	GPIO_u8ConfigPin(Check_Location_Port,Check_Location_Pin,GPIO_INPUT,0,GPIO_PD);
	
 	while(1)	
 	{
		
 		GPIO_u8GetPinValue(Check_Location_Port,Check_Location_Pin,&Check_Location_Pin_Value); 		
		if(Check_Location_Pin_Value==1)			
 		{
				//wait till bottomn is released
			while(Check_Location_Pin_Value) GPIO_u8GetPinValue(Check_Location_Port,Check_Location_Pin,&Check_Location_Pin_Value);
			GPS_voidCheckTheNearest();
			Systick_voidDelay_ms(2000);
 		}		
		///////////////////////
		GPIO_u8GetPinValue(Civil_Compass_Port,Civil_Compass_Pin,&Compass_Pin_Value);
		if(Compass_Pin_Value==0)			
 		{
					//wait till bottomn is released
					while(!Compass_Pin_Value) GPIO_u8GetPinValue(Civil_Compass_Port,Civil_Compass_Pin,&Compass_Pin_Value);
					Bonus_void_CheckDirection(Civil_Building);
 		}
		/////////////////////////
		GPIO_u8GetPinValue(HallA_Compass_Port,HallA_Compass_Pin,&Compass_Pin_Value);
		if(Compass_Pin_Value==0)			
 		{
					//wait till bottomn is released
					while(!Compass_Pin_Value) GPIO_u8GetPinValue(HallA_Compass_Port,HallA_Compass_Pin,&Compass_Pin_Value);
					Bonus_void_CheckDirection(Hall_A);
 		}
		/////////////////////////
		GPIO_u8GetPinValue(Acoustics_Building_Compass_Port,Acoustics_Building_Compass_Pin,&Compass_Pin_Value);
		if(Compass_Pin_Value==0)			
 		{
					//wait till bottomn is released
					while(!Compass_Pin_Value) GPIO_u8GetPinValue(Acoustics_Building_Compass_Port,Acoustics_Building_Compass_Pin,&Compass_Pin_Value);
					Bonus_void_CheckDirection(Acoustics_Building);
 		}
		/////////////////////////
		GPIO_u8GetPinValue(Gate2_Compass_Port,Gate2_Compass_Pin,&Compass_Pin_Value);
		if(Compass_Pin_Value==0)			
 		{
					//wait till bottomn is released
					while(!Compass_Pin_Value) GPIO_u8GetPinValue(Gate2_Compass_Port,Gate2_Compass_Pin,&Compass_Pin_Value);
					Bonus_void_CheckDirection(Gate_2);
 		}
 	}  

 }
