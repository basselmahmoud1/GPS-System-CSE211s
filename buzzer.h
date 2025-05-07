/****************************************************************/
/******* Author    : Jannah Ahmed               *****************/
/******* Date      : 7/5/2025                  *****************/
/******* File Name : buzzer.h            *****************/
/****************************************************************/

#ifndef BUZZER_H
#define BUZZER_H

#include "../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

#define BUZZER_PORT PortB /////////////adjust those//////////
#define BUZZER_PIN Pin0

void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void Buzzer_GenerateTone(u32 frequency);
void Buzzer_PlayDestinationTone(u32 frequency);

#endif
